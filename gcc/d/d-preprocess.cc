/* d-preprocess.cc -- D frontend interface to cpplib.
   Copyright (C) 2024 Free Software Foundation, Inc.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"

#include "dmd/root/dcompat.h"
#include "dmd/root/filename.h"
#include "dmd/errors.h"
#include "dmd/globals.h"

#include "cpplib.h"
#include "cppbuiltin.h"
#include "tree.h"
#include "memmodel.h"
#include "diagnostic.h"
#include "target.h"
#include "tm_p.h"
#include "incpath.h"

#include "d-tree.h"

#ifndef TARGET_SYSTEM_ROOT
# define TARGET_SYSTEM_ROOT NULL
#endif

/* Holds switches parsed by d_cpp_handle_option (), but whose
   handling is deferred to d_cpp_preprocess ().  */
typedef struct
{
  opt_code code;
  const char *arg;
}
d_cpp_deferred_opt_t;

/* Options handled by the compiler that are passed to cpplib.  */
struct d_cpp_option_data
{
  const char *multilib;			/* -imultilib <dir>  */
  const char *prefix;			/* -iprefix <dir>  */
  const char *sysroot;			/* -isysroot <dir>  */

  bool stdinc;				/* -nostdinc  */
  bool verbose;				/* -v  */

  /* Options whose handling is deferred until after cpplib is initialized.  */
  d_cpp_deferred_opt_t *deferred_opt;
  int deferred_opt_count;
}
d_cpp_option;

/* Buffer to write preprocessed content to.  */
static obstack d_cpp_buffer;

/* The first object on d_cpp_buffer, used to free memory.  */
static void *d_cpp_buffer_base;

/* A hash table of macros that have been #defined.  */
struct cpp_hashnode_hasher : nofree_ptr_hash <cpp_hashnode>
{
  static hashval_t hash (cpp_hashnode *node)
  {
    return node->ident.hash_value;
  }

  static bool equal (cpp_hashnode *node1, cpp_hashnode *node2)
  {
    return node1->ident.hash_value == node2->ident.hash_value;
  }
};

static hash_table <cpp_hashnode_hasher> *d_cpp_macros;

/* Callback routines for the parser.  */

static void
cb_define (cpp_reader *, location_t, cpp_hashnode *node)
{
  cpp_hashnode **slot = d_cpp_macros->find_slot (node, NO_INSERT);

  if (slot == NULL)
    {
      slot = d_cpp_macros->find_slot (node, INSERT);
      gcc_assert (slot != NULL && *slot == NULL);
    }

  *slot = node;
}

static void
cb_undef (cpp_reader *, location_t, cpp_hashnode *node)
{
  if (cpp_hashnode **slot = d_cpp_macros->find_slot (node, NO_INSERT))
    d_cpp_macros->clear_slot (slot);
}

/* Called when a line of output is started.  TOKEN is the first token
   of the line, and at end of file will be CPP_EOF.  */

static void
cb_line_change (cpp_reader *, const cpp_token *token, int parsing_args)
{
  if (token->type == CPP_EOF || parsing_args)
    return;

  /* The ImportC parser understands #line markers, append one to buffer.  */
  static unsigned prev_line = 1;
  static const char *prev_file = "";

  if (token->src_loc == UNKNOWN_LOCATION)
    return;

  unsigned src_line = LOCATION_LINE (token->src_loc);
  const char *src_file = LOCATION_FILE (token->src_loc);

  /* Elide a line marker if the difference is just a few extra newlines.  */
  if (src_line >= prev_line && src_line < prev_line + 8
      && strcmp (src_file, prev_file) == 0)
    {
      while (src_line > prev_line)
	{
	  obstack_1grow (&d_cpp_buffer, '\n');
	  prev_line++;
	}
    }
  else
    {
      size_t to_file_len = strlen (src_file);
      unsigned char *to_file_quoted =
	(unsigned char *) alloca (to_file_len * 4 + 1);

      /* cpp_quote_string does not nul-terminate, so we have to do it
	 ourselves.  */
      unsigned char *p = cpp_quote_string (to_file_quoted,
					   (const unsigned char *) src_file,
					   to_file_len);
      *p = '\0';

      char *xformat = xasprintf ("# %u \"%s\"\n", src_line, to_file_quoted);
      obstack_grow (&d_cpp_buffer, xformat, strlen (xformat));
      free (xformat);

      prev_line = src_line;
      prev_file = src_file;
    }
}

/* Callback from cpp_error for PFILE to print diagnostics from the
   preprocessor.  The diagnostic is of type LEVEL, with REASON set
   to the reason code if LEVEL is represents a warning, at location
   RICHLOC; MSG is the translated message and AP the arguments.
   Returns true if a diagnostic was emitted, false otherwise.  */

ATTRIBUTE_GCC_DIAG(5,0)
static bool
cb_cpp_diagnostic (cpp_reader *, enum cpp_diagnostic_level level,
		   enum cpp_warning_reason, rich_location *richloc,
		   const char *msg, va_list *ap)
{
  diagnostic_t dlevel;
  bool save_warn_system_headers = global_dc->m_warn_system_headers;

  switch (level)
    {
    case CPP_DL_WARNING_SYSHDR:
      global_dc->m_warn_system_headers = 1;
      /* Fall through.  */
    case CPP_DL_WARNING:
      dlevel = DK_WARNING;
      break;
    case CPP_DL_PEDWARN:
      dlevel = DK_PEDWARN;
      break;
    case CPP_DL_ERROR:
      dlevel = DK_ERROR;
      break;
    case CPP_DL_ICE:
      dlevel = DK_ICE;
      break;
    case CPP_DL_NOTE:
      dlevel = DK_NOTE;
      break;
    case CPP_DL_FATAL:
      dlevel = DK_FATAL;
      break;
    default:
      gcc_unreachable ();
    }

  diagnostic_info diagnostic;
  diagnostic_set_info_translated (&diagnostic, msg, ap,
				  richloc, dlevel);
  bool ret = diagnostic_report_diagnostic (global_dc, &diagnostic);
  if (level == CPP_DL_WARNING_SYSHDR)
    global_dc->m_warn_system_headers = save_warn_system_headers;
  return ret;
}

/* Wrapper around cpp_get_token to skip CPP_PADDING tokens and not consume
   CPP_EOF.  Used by d_lex_availability_macro.  */

static const cpp_token *
get_token_no_padding (cpp_reader *pfile)
{
  for (;;)
    {
      const cpp_token *ret = cpp_peek_token (pfile, 0);
      if (ret->type == CPP_EOF)
	return ret;

      ret = cpp_get_token (pfile);
      if (ret->type != CPP_PADDING)
	return ret;
    }
}

/* Helper for consuming __has_{attribute,builtin,feature,extension}.  */

static void
d_lex_availability_macro (cpp_reader *pfile, const char *builtin)
{
  const cpp_token *token = get_token_no_padding (pfile);
  if (token->type != CPP_OPEN_PAREN)
    {
      cpp_error (pfile, CPP_DL_ERROR,
		 "missing %<(%> after %<__has_%s%>", builtin);
      return;
    }

  token = get_token_no_padding (pfile);
  if (token->type != CPP_NAME)
    {
      cpp_error (pfile, CPP_DL_ERROR,
		 "macro %<__has_%s%> requires an identifier", builtin);
      if (token->type == CPP_CLOSE_PAREN)
	return;
    }

  /* Consume tokens up to the closing parenthesis.  */
  for (unsigned nparen = 1; ; token = get_token_no_padding (pfile))
    {
      if (token->type == CPP_OPEN_PAREN)
	++nparen;
      else if (token->type == CPP_CLOSE_PAREN)
	--nparen;
      else if (token->type == CPP_EOF)
	{
	  cpp_error (pfile, CPP_DL_ERROR,
		     "missing %<)%> after %<__has_%s%>", builtin);
	  return;
	}
      if (!nparen)
	return;
    }
}

/* Callback for has_attribute.  */

static int
cb_has_attribute (cpp_reader *pfile, bool)
{
  d_lex_availability_macro (pfile, "attribute");
  return 0;
}

/* Callback for has_builtin.  */

static int
cb_has_builtin (cpp_reader *pfile)
{
  d_lex_availability_macro (pfile, "builtin");
  return 0;
}

/* Callback for has_feature.  */

static int
cb_has_feature (cpp_reader *pfile, bool feature)
{
  d_lex_availability_macro (pfile, feature ? "feature" : "extension");
  return 0;
}

/* Write the final definition of a CPP macro NODE defined in PFILE to the
   OutBuffer DEFINES for the ImportC parser to collect and translate into D.  */

static void
d_cpp_append_macro (cpp_hashnode *node, cpp_reader *pfile, OutBuffer &defines)
{
  /* The ImportC parser only handles simple expressions such as numbers and
     strings, as well as straightforward function-like macros.  Filter out any
     other kind of macro definition.  */
  if (!cpp_macro_p (node) || node->value.macro->kind != cmk_macro)
    return;

  cpp_macro *macro = node->value.macro;
  bool print = false;

  /* Look for `#define MACRO string_or_number'.  */
  if (!macro->fun_like && macro->count == 1
      && cpp_token_val_index (&macro->exp.tokens[0]) == CPP_TOKEN_FLD_STR)
    print = true;

  /* Look for `#define MACRO ( expression )'.  */
  if (!macro->fun_like && macro->count > 2
      && macro->exp.tokens[0].type == CPP_OPEN_PAREN
      && macro->exp.tokens[macro->count - 1].type == CPP_CLOSE_PAREN)
    print = true;

  /* Look for `#define MACRO() expression'.  */
  if (macro->fun_like && !macro->variadic && macro->count > 0)
    {
      print = true;
      for (unsigned int i = 0; i < macro->count; i++)
	{
	  /* Don't emit if macro contains CPP-specific tokens, or anything that
	     looks like it might be a statement. */
	  if (macro->exp.tokens[i].type == CPP_HASH
	      || macro->exp.tokens[i].type == CPP_PASTE
	      || macro->exp.tokens[i].type == CPP_SEMICOLON)
	    {
	      print = false;
	      break;
	    }
	}
    }

  if (!print)
    return;

  const char *text = (const char *) cpp_macro_definition (pfile, node);
  defines.write ("#define ", 8);
  defines.write (text, strlen (text));
  /* Each #define line is 0 terminated.  */
  defines.writeByte ('\0');
}

/* Initialize the cpp_callbacks structure of PFILE.  */

static void
d_cpp_init_callbacks (cpp_reader *pfile)
{
  cpp_callbacks *cb = cpp_get_callbacks (pfile);

  cb->diagnostic = cb_cpp_diagnostic;
  cb->line_change = cb_line_change;
  cb->define = cb_define;
  cb->undef  = cb_undef;
  cb->has_attribute = cb_has_attribute;
  cb->has_builtin = cb_has_builtin;
  cb->has_feature = cb_has_feature;

  if (!d_cpp_macros)
    d_cpp_macros = hash_table <cpp_hashnode_hasher>::create_ggc (100);
}

/* Implements lang_hooks.init_options for ImportC, called from d_init_options.
   Initialize libcpp-related options before calling the option handlers.  */

void
d_cpp_init_options (unsigned int decoded_options_count)
{
  d_cpp_option.multilib = NULL;
  d_cpp_option.prefix = NULL;
  d_cpp_option.sysroot = TARGET_SYSTEM_ROOT;

  d_cpp_option.stdinc = true;
  d_cpp_option.verbose = false;

  d_cpp_option.deferred_opt = XNEWVEC (d_cpp_deferred_opt_t,
				       decoded_options_count);
  d_cpp_option.deferred_opt_count = 0;
}

/* Implements lang_hooks.init_options_struct for ImportC, called from
   d_init_options_struct.  Handles ImportC specific options.
   Return false if we didn't do anything.  */

bool
d_cpp_handle_option (size_t scode, const char *arg)
{
  opt_code code = (opt_code) scode;
  bool result = true;

  switch (code)
    {
    default:
      result = false;
      break;

    case OPT_idirafter:
      add_path (xstrdup (arg), INC_AFTER, 0, true);
      break;

    case OPT_imultilib:
      d_cpp_option.multilib = arg;
      break;

    case OPT_iprefix:
      d_cpp_option.prefix = arg;
      break;

    case OPT_isysroot:
      d_cpp_option.sysroot = arg;
      break;

    case OPT_iquote:
    case OPT_isystem:
      add_path (xstrdup (arg), INC_BRACKET, 0, true);
      break;

    case OPT_nostdinc:
      d_cpp_option.stdinc = false;
      break;

    case OPT_v:
      d_cpp_option.verbose = true;
      break;

    case OPT_D:
    case OPT_U:
    case OPT_imacros:
    case OPT_include:
      d_cpp_option.deferred_opt[d_cpp_option.deferred_opt_count].code = code;
      d_cpp_option.deferred_opt[d_cpp_option.deferred_opt_count].arg = arg;
      d_cpp_option.deferred_opt_count++;
      break;
    }

  return result;
}

/* Initialize and return a libcpp parser for preprocessing C input sources.  */

static cpp_reader *
d_cpp_init_parser (void)
{
  cpp_reader *pfile = cpp_create_reader (CLK_GNUC11, NULL, line_table);
  gcc_assert (pfile);

  /* The cpp_options-structure defines far more flags than those set here.
     If any other is implemented, see c-opt.c (sanitize_cpp_opts) for
     inter-option dependencies that may need to be enforced.  */
  cpp_options *cpp_option = cpp_get_options (pfile);
  gcc_assert (cpp_option);

  cpp_option->cpp_pedantic = pedantic;

  cpp_post_options (pfile);

  d_cpp_init_callbacks (pfile);

  /* The handler `register_include_chains' can only be called once.  */
  static bool registered_chains = false;

  if (registered_chains)
    cpp_set_include_chains (pfile, get_added_cpp_dirs (INC_QUOTE),
			    get_added_cpp_dirs (INC_BRACKET),
			    get_added_cpp_dirs (INC_EMBED), false);
  else
    {
      register_include_chains (pfile, d_cpp_option.sysroot,
			       d_cpp_option.prefix, d_cpp_option.multilib,
			       d_cpp_option.stdinc, false,
			       d_cpp_option.verbose);
      registered_chains = true;
    }

  return pfile;
}

/* Pass an object-like macro and a value to define it to.  */

static void
d_cpp_define (cpp_reader *pfile, const char *macro, const char *expansion)
{
  size_t mlen = strlen (macro);
  size_t elen = strlen (expansion);
  char *buf = (char *) alloca (mlen + elen + 2);

  sprintf (buf, "%s=%s", macro, expansion);
  cpp_define (pfile, buf);
}

/* Register front-end and target-specific CPP built-ins in PFILE.  */

static void
d_cpp_define_builtins (cpp_reader *pfile)
{
  /* Initialize CPP built-ins.  */
  cpp_change_file (pfile, LC_RENAME, "<built-in>");
  cpp_force_token_locations (pfile, BUILTINS_LOCATION);

  cpp_init_builtins (pfile, 0);
  define_language_independent_builtin_macros (pfile);

  /* Support the __declspec keyword by turning them into attributes.  */
  if (TARGET_DECLSPEC)
    d_cpp_define (pfile, "__declspec(x)", "__attribute__((x))");

  /* ImportC parser only recognizes C11 keywords where there are non-standard
     alternative keywords.  Redefine extensions to their ANSI equivalent.
     This list was taken from an inspection of c-family/c-common.cc.  */
  d_cpp_define (pfile, "__alignof", "_Alignof");
  d_cpp_define (pfile, "__alignof__", "_Alignof");
  d_cpp_define (pfile, "__const", "const");
  d_cpp_define (pfile, "__const__", "const");
  d_cpp_define (pfile, "__complex", "_Complex");
  d_cpp_define (pfile, "__complex__", "_Complex");
  d_cpp_define (pfile, "__inline", "inline");
  d_cpp_define (pfile, "__inline__", "inline");
  d_cpp_define (pfile, "__restrict", "restrict");
  d_cpp_define (pfile, "__restrict__", "restrict");
  d_cpp_define (pfile, "__signed", "signed");
  d_cpp_define (pfile, "__signed__", "signed");
  d_cpp_define (pfile, "__thread", "_Thread_local");
  d_cpp_define (pfile, "__typeof", "typeof");
  d_cpp_define (pfile, "__typeof__", "typeof");
  d_cpp_define (pfile, "__volatile", "volatile");
  d_cpp_define (pfile, "__volatile__", "volatile");

  /* Built-in macros for stddef.h and stdint.h.  */
  d_cpp_define (pfile, "__SIZE_TYPE__", SIZE_TYPE);
  d_cpp_define (pfile, "__PTRDIFF_TYPE__", PTRDIFF_TYPE);
  d_cpp_define (pfile, "__WCHAR_TYPE__", MODIFIED_WCHAR_TYPE);
  if (strcmp (WINT_TYPE, "wchar_t") == 0)
    d_cpp_define (pfile, "__WINT_TYPE__", WCHAR_TYPE);
  else
    d_cpp_define (pfile, "__WINT_TYPE__", WINT_TYPE);
  d_cpp_define (pfile, "__INTMAX_TYPE__", INTMAX_TYPE);
  d_cpp_define (pfile, "__UINTMAX_TYPE__", UINTMAX_TYPE);
  d_cpp_define (pfile, "__CHAR8_TYPE__", CHAR8_TYPE);
  d_cpp_define (pfile, "__CHAR16_TYPE__", CHAR16_TYPE);
  d_cpp_define (pfile, "__CHAR32_TYPE__", CHAR32_TYPE);
  if (SIG_ATOMIC_TYPE)
    d_cpp_define (pfile, "__SIG_ATOMIC_TYPE__", SIG_ATOMIC_TYPE);
  if (INT8_TYPE)
    d_cpp_define (pfile, "__INT8_TYPE__", INT8_TYPE);
  if (INT16_TYPE)
    d_cpp_define (pfile, "__INT16_TYPE__", INT16_TYPE);
  if (INT32_TYPE)
    d_cpp_define (pfile, "__INT32_TYPE__", INT32_TYPE);
  if (INT64_TYPE)
    d_cpp_define (pfile, "__INT64_TYPE__", INT64_TYPE);
  if (UINT8_TYPE)
    d_cpp_define (pfile, "__UINT8_TYPE__", UINT8_TYPE);
  if (UINT16_TYPE)
    d_cpp_define (pfile, "__UINT16_TYPE__", UINT16_TYPE);
  if (UINT32_TYPE)
    d_cpp_define (pfile, "__UINT32_TYPE__", UINT32_TYPE);
  if (UINT64_TYPE)
    d_cpp_define (pfile, "__UINT64_TYPE__", UINT64_TYPE);
  if (INT_LEAST8_TYPE)
    d_cpp_define (pfile, "__INT_LEAST8_TYPE__", INT_LEAST8_TYPE);
  if (INT_LEAST16_TYPE)
    d_cpp_define (pfile, "__INT_LEAST16_TYPE__", INT_LEAST16_TYPE);
  if (INT_LEAST32_TYPE)
    d_cpp_define (pfile, "__INT_LEAST32_TYPE__", INT_LEAST32_TYPE);
  if (INT_LEAST64_TYPE)
    d_cpp_define (pfile, "__INT_LEAST64_TYPE__", INT_LEAST64_TYPE);
  if (UINT_LEAST8_TYPE)
    d_cpp_define (pfile, "__UINT_LEAST8_TYPE__", UINT_LEAST8_TYPE);
  if (UINT_LEAST16_TYPE)
    d_cpp_define (pfile, "__UINT_LEAST16_TYPE__", UINT_LEAST16_TYPE);
  if (UINT_LEAST32_TYPE)
    d_cpp_define (pfile, "__UINT_LEAST32_TYPE__", UINT_LEAST32_TYPE);
  if (UINT_LEAST64_TYPE)
    d_cpp_define (pfile, "__UINT_LEAST64_TYPE__", UINT_LEAST64_TYPE);
  if (INT_FAST8_TYPE)
    d_cpp_define (pfile, "__INT_FAST8_TYPE__", INT_FAST8_TYPE);
  if (INT_FAST16_TYPE)
    d_cpp_define (pfile, "__INT_FAST16_TYPE__", INT_FAST16_TYPE);
  if (INT_FAST32_TYPE)
    d_cpp_define (pfile, "__INT_FAST32_TYPE__", INT_FAST32_TYPE);
  if (INT_FAST64_TYPE)
    d_cpp_define (pfile, "__INT_FAST64_TYPE__", INT_FAST64_TYPE);
  if (UINT_FAST8_TYPE)
    d_cpp_define (pfile, "__UINT_FAST8_TYPE__", UINT_FAST8_TYPE);
  if (UINT_FAST16_TYPE)
    d_cpp_define (pfile, "__UINT_FAST16_TYPE__", UINT_FAST16_TYPE);
  if (UINT_FAST32_TYPE)
    d_cpp_define (pfile, "__UINT_FAST32_TYPE__", UINT_FAST32_TYPE);
  if (UINT_FAST64_TYPE)
    d_cpp_define (pfile, "__UINT_FAST64_TYPE__", UINT_FAST64_TYPE);
  if (INTPTR_TYPE)
    d_cpp_define (pfile, "__INTPTR_TYPE__", INTPTR_TYPE);
  if (UINTPTR_TYPE)
    d_cpp_define (pfile, "__UINTPTR_TYPE__", UINTPTR_TYPE);

  /* C-only extensions recognized by the parser.  */
  d_cpp_define (pfile, "__attribute", "__attribute__");

  /* `asm' is a D keyword.  */
  d_cpp_define (pfile, "__asm", "asm");
  d_cpp_define (pfile, "__asm__", "asm");

  /* `__extension__' suppresses warnings, there aren't any in ImportC.  */
  d_cpp_define (pfile, "__extension__", "");

  /* Initialize GDC specific built-ins.  */
  d_cpp_define (pfile, "__IMPORTC__", "1");
  d_cpp_define (pfile, "_LANGUAGE_D", "1");

  cpp_stop_forcing_token_locations (pfile);
}

/* Handle deferred options from command-line, and apply them to PFILE.  */

static void
d_cpp_deferred_options (cpp_reader *pfile)
{
  cpp_change_file (pfile, LC_RENAME, "<command-line>");

  for (int i = 0; i < d_cpp_option.deferred_opt_count; i++)
    {
      d_cpp_deferred_opt_t *opt = &d_cpp_option.deferred_opt[i];

      if (opt->code == OPT_D)
	cpp_define (pfile, opt->arg);
      else if (opt->code == OPT_U)
	cpp_undef (pfile, opt->arg);
    }

  /* Handle -imacros after -D, and -U.  */
  for (int i = 0; i < d_cpp_option.deferred_opt_count; i++)
    {
      d_cpp_deferred_opt_t *opt = &d_cpp_option.deferred_opt[i];

      if (opt->code == OPT_imacros
	  && cpp_push_include (pfile, opt->arg))
	cpp_scan_nooutput (pfile);
    }

  /* Handle -include after -imacros and target-specific includes.  */
  for (int i = 0; i < d_cpp_option.deferred_opt_count; i++)
    {
      d_cpp_deferred_opt_t *opt = &d_cpp_option.deferred_opt[i];

      if (opt->code == OPT_include)
	  cpp_push_include (pfile, opt->arg);
    }
}

/* Preprocess the C file SRCFILE, returning the text of the preprocessed file
   as a DArray.  Any `#define' lines encountered are appended to DEFINES.
   LOC is the source location where this callback is requested from.  */

DArray<unsigned char>
d_cpp_preprocess (FileName srcfile, Loc, OutBuffer &defines)
{
  if (global.params.v.verbose)
    message("importc   %s", srcfile.toChars ());

  cpp_reader *pfile = d_cpp_init_parser ();

  /* Initialize the buffer to return from this function.  */
  if (!d_cpp_buffer_base)
    {
      gcc_obstack_init (&d_cpp_buffer);
      d_cpp_buffer_base = obstack_alloc (&d_cpp_buffer, 0);
    }
  else
    {
      obstack_free (&d_cpp_buffer, d_cpp_buffer_base);
      d_cpp_buffer_base = obstack_alloc (&d_cpp_buffer, 0);
    }

  /* Parse the C file.  */
  if (!cpp_read_main_file (pfile, srcfile.toChars ()))
    {
      errorcount++;
      return DArray<unsigned char> ();
    }

  d_cpp_define_builtins (pfile);

  /* Handle deferred options from command-line.  */
  d_cpp_deferred_options (pfile);
  cpp_change_file (pfile, LC_RENAME, srcfile.toChars ());

  /* Do the preprocessing.  */
  bool avoid_paste = false;
  const cpp_token *cpp_source = NULL;
  const cpp_token *cpp_prev = NULL;

  for (;;)
    {
      const cpp_token *token = cpp_get_token (pfile);

      if (token->type == CPP_PADDING)
	{
	  avoid_paste = true;
	  if (cpp_source == NULL
	      || (!(cpp_source->flags & PREV_WHITE)
		  && token->val.source == NULL))
	    cpp_source = token->val.source;

	  continue;
	}

      if (token->type == CPP_EOF)
	break;

      /* Output a space if and only if necessary.  */
      if (avoid_paste)
	{
	  if (cpp_source == NULL)
	    cpp_source = token;

	  if (cpp_source->flags & PREV_WHITE
	      || (cpp_prev && cpp_avoid_paste (pfile, cpp_prev, token))
	      || (cpp_prev == NULL && token->type == CPP_HASH))
	    obstack_1grow (&d_cpp_buffer, ' ');
	}
      else if (token->flags & PREV_WHITE)
	obstack_1grow (&d_cpp_buffer, ' ');

      avoid_paste = false;
      cpp_source = NULL;
      cpp_prev = token;

      unsigned char *text = cpp_token_as_text (pfile, token);
      obstack_grow (&d_cpp_buffer, text, strlen ((const char *) text));
    }

  /* Reached EOF, now dump all macro definitions to `defines'.  */
  for (hash_table <cpp_hashnode_hasher>::iterator iter = d_cpp_macros->begin ();
       iter != d_cpp_macros->end (); ++iter)
    d_cpp_append_macro (*iter, pfile, defines);

  d_cpp_macros->empty ();

  /* Clean-up libcpp state so that multiple invocations of d_cpp_preprocess
     won't conflict with each other.  */
  cpp_finish (pfile, NULL);
  cpp_destroy (pfile);

  char *result = (char *) obstack_finish (&d_cpp_buffer);
  return DArray<unsigned char> (strlen (result), (unsigned char *) result);
}
