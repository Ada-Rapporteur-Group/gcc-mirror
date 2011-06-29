/* Routines for reading PPH data.
   Copyright (C) 2011 Free Software Foundation, Inc.
   Contributed by Diego Novillo <dnovillo@google.com>.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tree.h"
#include "langhooks.h"
#include "tree-iterator.h"
#include "tree-pretty-print.h"
#include "lto-streamer.h"
#include "pph-streamer.h"
#include "pph.h"
#include "tree-pass.h"
#include "version.h"
#include "cppbuiltin.h"

/* Wrapper for memory allocation calls that should have their results
   registered in the PPH streamer cache.  DATA is the pointer returned
   by the memory allocation call in ALLOC_EXPR.  IX is the cache slot 
   in STREAM where the newly allocated DATA should be registered at.  */
#define ALLOC_AND_REGISTER(STREAM, IX, DATA, ALLOC_EXPR)	\
    do {							\
      (DATA) = (ALLOC_EXPR);					\
      pph_register_shared_data (STREAM, DATA, IX);		\
    } while (0)

/* Callback for unpacking value fields in ASTs.  BP is the bitpack 
   we are unpacking from.  EXPR is the tree to unpack.  */

void
pph_unpack_value_fields (struct bitpack_d *bp, tree expr)
{
  if (TYPE_P (expr))
    {
      TYPE_LANG_FLAG_0 (expr) = bp_unpack_value (bp, 1);
      TYPE_LANG_FLAG_1 (expr) = bp_unpack_value (bp, 1);
      TYPE_LANG_FLAG_2 (expr) = bp_unpack_value (bp, 1);
      TYPE_LANG_FLAG_3 (expr) = bp_unpack_value (bp, 1);
      TYPE_LANG_FLAG_4 (expr) = bp_unpack_value (bp, 1);
      TYPE_LANG_FLAG_5 (expr) = bp_unpack_value (bp, 1);
      TYPE_LANG_FLAG_6 (expr) = bp_unpack_value (bp, 1);
    }
  else if (DECL_P (expr))
    {
      DECL_LANG_FLAG_0 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_1 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_2 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_3 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_4 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_5 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_6 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_7 (expr) = bp_unpack_value (bp, 1);
      DECL_LANG_FLAG_8 (expr) = bp_unpack_value (bp, 1);
    }

  TREE_LANG_FLAG_0 (expr) = bp_unpack_value (bp, 1);
  TREE_LANG_FLAG_1 (expr) = bp_unpack_value (bp, 1);
  TREE_LANG_FLAG_2 (expr) = bp_unpack_value (bp, 1);
  TREE_LANG_FLAG_3 (expr) = bp_unpack_value (bp, 1);
  TREE_LANG_FLAG_4 (expr) = bp_unpack_value (bp, 1);
  TREE_LANG_FLAG_5 (expr) = bp_unpack_value (bp, 1);
  TREE_LANG_FLAG_6 (expr) = bp_unpack_value (bp, 1);
}


/* Get the section with name NAME and type SECTION_TYPE from FILE_DATA.
   Return a pointer to the start of the section contents and store
   the length of the section in *LEN_P.

   FIXME pph, this does not currently handle multiple sections.  It
   assumes that the file has exactly one section.  */

static const char *
pph_get_section_data (struct lto_file_decl_data *file_data,
		      enum lto_section_type section_type ATTRIBUTE_UNUSED,
		      const char *name ATTRIBUTE_UNUSED,
		      size_t *len)
{
  /* FIXME pph - Stop abusing lto_file_decl_data fields.  */
  const pph_stream *stream = (const pph_stream *) file_data->file_name;
  *len = stream->file_size - sizeof (pph_file_header);
  return (const char *) stream->file_data + sizeof (pph_file_header);
}


/* Free the section data from FILE_DATA of SECTION_TYPE and NAME that
   starts at OFFSET and has LEN bytes.  */

static void
pph_free_section_data (struct lto_file_decl_data *file_data,
		   enum lto_section_type section_type ATTRIBUTE_UNUSED,
		   const char *name ATTRIBUTE_UNUSED,
		   const char *offset ATTRIBUTE_UNUSED,
		   size_t len ATTRIBUTE_UNUSED)
{
  /* FIXME pph - Stop abusing lto_file_decl_data fields.  */
  const pph_stream *stream = (const pph_stream *) file_data->file_name;
  free (stream->file_data);
}


/* Read into memory the contents of the file in STREAM.  Initialize
   internal tables and data structures needed to re-construct the
   ASTs in the file.  */

void
pph_init_read (pph_stream *stream)
{
  struct stat st;
  size_t i, bytes_read, strtab_size, body_size;
  int retcode;
  pph_file_header *header;
  const char *strtab, *body;

  lto_reader_init ();

  /* Read STREAM->NAME into the memory buffer STREAM->FILE_DATA.
     FIXME pph, we are reading the whole file at once.  This seems
     wasteful.  */
  retcode = fstat (fileno (stream->file), &st);
  gcc_assert (retcode == 0);
  stream->file_size = (size_t) st.st_size;
  stream->file_data = XCNEWVEC (char, stream->file_size);
  bytes_read = fread (stream->file_data, 1, stream->file_size, stream->file);
  gcc_assert (bytes_read == stream->file_size);

  /* Set LTO callbacks to read the PPH file.  */
  stream->pph_sections = XCNEWVEC (struct lto_file_decl_data *,
				   PPH_NUM_SECTIONS);
  for (i = 0; i < PPH_NUM_SECTIONS; i++)
    {
      stream->pph_sections[i] = XCNEW (struct lto_file_decl_data);
      /* FIXME pph - Stop abusing fields in lto_file_decl_data.  */
      stream->pph_sections[i]->file_name = (const char *) stream;
    }

  lto_set_in_hooks (stream->pph_sections, pph_get_section_data,
		    pph_free_section_data);

  header = (pph_file_header *) stream->file_data;
  strtab = (const char *) header + sizeof (pph_file_header);
  strtab_size = header->strtab_size;
  body = strtab + strtab_size;
  gcc_assert (stream->file_size >= strtab_size + sizeof (pph_file_header));
  body_size = stream->file_size - strtab_size - sizeof (pph_file_header);

  /* Create an input block structure pointing right after the string
     table.  */
  stream->ib = XCNEW (struct lto_input_block);
  LTO_INIT_INPUT_BLOCK_PTR (stream->ib, body, 0, body_size);
  stream->data_in = lto_data_in_create (stream->pph_sections[0], strtab,
                                        strtab_size, NULL);

  /* Associate STREAM with STREAM->DATA_IN so we can recover it from
     the streamer hooks.  */
  stream->data_in->sdata = (void *) stream;
}


/* Read and return a record marker from STREAM.  When a PPH_RECORD_START
   marker is read, the next word read is an index into the streamer
   cache where the rematerialized data structure should be stored.
   When the writer stored this data structure for the first time, it
   added it to its own streamer cache at slot number *CACHE_IX.

   This way, if the same data structure was written a second time to
   the stream, instead of writing the whole structure again, only the
   index *CACHE_IX is written as a PPH_RECORD_SHARED record.

   Therefore, when reading a PPH_RECORD_START marker, *CACHE_IX will
   contain the slot number where the materialized data should be
   cached at.  When reading a PPH_RECORD_SHARED marker, *CACHE_IX will
   contain the slot number the reader can find the previously
   materialized structure.  */

static inline enum pph_record_marker
pph_in_start_record (pph_stream *stream, unsigned *cache_ix)
{
  enum pph_record_marker marker;

  marker = (enum pph_record_marker) pph_in_uchar (stream);

  /* For PPH_RECORD_START and PPH_RECORD_SHARED markers, read the
     streamer cache slot where we should store or find the
     rematerialized data structure (see description above).  */
  if (marker == PPH_RECORD_START || marker == PPH_RECORD_SHARED)
    *cache_ix = pph_in_uint (stream);
  else
    {
      gcc_assert (marker == PPH_RECORD_END);

      /* Initialize CACHE_IX to an invalid index. Even though this
	 is never used in practice, the compiler will throw an error
	 if the optimizer inlines this function in a given build as
	 it will complain that " 'ix' may be used uninitialized".  */
      *cache_ix = -1;
    }

  return marker;
}


/* Return a shared pointer from the streamer cache in STREAM.  This is
   called when pph_in_start_record returns PPH_RECORD_SHARED.  It means
   that the data structure we are about to read has been instantiated
   before and is present in the streamer cache.  */

static void *
pph_in_shared_data (pph_stream *stream, unsigned ix)
{
  return pph_cache_get (stream, ix);
}


/* Register DATA in STREAM's cache slot IX.  This is called when a
   potentially shared data structure is first read from STREAM.
   Subsequent reads of this data structure will get the index from the
   table cache where this data was saved.  */

static void
pph_register_shared_data (pph_stream *stream, void *data, unsigned ix)
{
  pph_cache_insert_at (stream, data, ix);
}


/* Given a type index TYPE_IDX and TYPE_KIND specifying the kind of type,
   return a type from integer_types or global_trees.  */

static tree
pph_get_type_from_index (unsigned type_idx, unsigned type_kind)
{
  if (type_kind == CPP_N_INTEGER)
    return integer_types[type_idx];
  else if (type_kind == CPP_N_FLOATING || type_kind == CPP_N_FRACT)
    return global_trees[type_idx];
  else if (type_kind == CPP_N_IMAGINARY)
    {
      /* We don't need a type for the complex number.  The type is
	 associated with the real and imaginary parts.  */
      return NULL_TREE;
    }
  else
    gcc_unreachable ();
}


/* Load a numeric value from file F.  Return the corresponding tree.  */

static tree
pph_in_number (pph_stream *f)
{
  unsigned type_idx, type_kind;
  tree type, val;

  type_idx = pph_in_uint (f);
  type_kind = pph_in_uint (f);

  type = pph_get_type_from_index (type_idx, type_kind);

  if (type_kind == CPP_N_INTEGER)
    {
      HOST_WIDE_INT v[2];
      pph_in_bytes (f, v, 2 * sizeof (HOST_WIDE_INT));
      val = build_int_cst_wide (type, v[0], v[1]);
    }
  else if (type_kind == CPP_N_FLOATING)
    {
      REAL_VALUE_TYPE r;
      pph_in_bytes (f, &r, sizeof (REAL_VALUE_TYPE));
      val = build_real (type, r);
    }
  else if (type_kind == CPP_N_FRACT)
    {
      FIXED_VALUE_TYPE fv;
      pph_in_bytes (f, &fv, sizeof (FIXED_VALUE_TYPE));
      val = build_fixed (type, fv);
    }
  else if (type_kind == CPP_N_IMAGINARY)
    {
      tree r = pph_in_number (f);
      tree i = pph_in_number (f);
      val = build_complex (NULL_TREE, r, i);
    }
  else
    gcc_unreachable ();

  return val;
}


/* Load the tree value associated with TOKEN to file F.  */

static void
pph_in_token_value (pph_stream *f, cp_token *token)
{
  const char *str;

  switch (token->type)
    {
      case CPP_TEMPLATE_ID:
      case CPP_NESTED_NAME_SPECIFIER:
	break;

      case CPP_NAME:
	str = pph_in_string (f);
	token->u.value = get_identifier (str);
	break;

      case CPP_KEYWORD:
	token->u.value = ridpointers[token->keyword];
	break;

      case CPP_CHAR:
      case CPP_WCHAR:
      case CPP_CHAR16:
      case CPP_CHAR32:
      case CPP_NUMBER:
	token->u.value = pph_in_number (f);
	break;

      case CPP_STRING:
      case CPP_WSTRING:
      case CPP_STRING16:
      case CPP_STRING32:
	str = pph_in_string (f);
	token->u.value = build_string (strlen (str), str);
	break;

      case CPP_PRAGMA:
	/* Nothing to do.  Field pragma_kind has already been loaded.  */
	break;

      default:
	pph_in_bytes (f, &token->u.value, sizeof (token->u.value));
	gcc_assert (token->u.value == NULL);
    }
}


/* Read and return a token from STREAM.  */

static cp_token *
pph_in_token (pph_stream *stream)
{
  cp_token *token = ggc_alloc_cleared_cp_token ();

  /* Do not read the whole structure, the token value has
     dynamic size as it contains swizzled pointers.
     FIXME pph, restructure to allow bulk reads of the whole
     section.  */
  pph_in_bytes (stream, token, sizeof (cp_token) - sizeof (void *));

  /* FIXME pph.  Use an arbitrary (but valid) location to avoid
     confusing the rest of the compiler for now.  */
  token->location = input_location;

  /* FIXME pph: verify that pph_in_token_value works with no tokens.  */
  pph_in_token_value (stream, token);

  return token;
}


/* Read and return a cp_token_cache instance from STREAM.  */

static cp_token_cache *
pph_in_token_cache (pph_stream *stream)
{
  unsigned i, num;
  cp_token *first, *last;

  num = pph_in_uint (stream);
  for (last = first = NULL, i = 0; i < num; i++)
    {
      last = pph_in_token (stream);
      if (first == NULL)
	first = last;
    }

  return cp_token_cache_new (first, last);
}


/* Read all fields in lang_decl_base instance LDB from STREAM.  */

static void
pph_in_ld_base (pph_stream *stream, struct lang_decl_base *ldb)
{
  struct bitpack_d bp;

  bp = pph_in_bitpack (stream);
  ldb->selector = bp_unpack_value (&bp, 16);
  ldb->language = (enum languages) bp_unpack_value (&bp, 4);
  ldb->use_template = bp_unpack_value (&bp, 2);
  ldb->not_really_extern = bp_unpack_value (&bp, 1);
  ldb->initialized_in_class = bp_unpack_value (&bp, 1);
  ldb->repo_available_p = bp_unpack_value (&bp, 1);
  ldb->threadprivate_or_deleted_p = bp_unpack_value (&bp, 1);
  ldb->anticipated_p = bp_unpack_value (&bp, 1);
  ldb->friend_attr = bp_unpack_value (&bp, 1);
  ldb->template_conv_p = bp_unpack_value (&bp, 1);
  ldb->odr_used = bp_unpack_value (&bp, 1);
  ldb->u2sel = bp_unpack_value (&bp, 1);
}


/* Read all the fields in lang_decl_min instance LDM from STREAM.  */

static void
pph_in_ld_min (pph_stream *stream, struct lang_decl_min *ldm)
{
  ldm->template_info = pph_in_tree (stream);
  if (ldm->base.u2sel == 0)
    ldm->u2.access = pph_in_tree (stream);
  else if (ldm->base.u2sel == 1)
    ldm->u2.discriminator = pph_in_uint (stream);
  else
    gcc_unreachable ();
}


/* Read and return a gc VEC of trees from STREAM.  */

static VEC(tree,gc) *
pph_in_tree_vec (pph_stream *stream)
{
  unsigned i, num;
  VEC(tree,gc) *v;

  num = pph_in_uint (stream);
  v = NULL;
  for (i = 0; i < num; i++)
    {
      tree t = pph_in_tree (stream);
      VEC_safe_push (tree, gc, v, t);
    }

  return v;
}


/* Read and return a gc VEC of qualified_typedef_usage_t from STREAM.  */

static VEC(qualified_typedef_usage_t,gc) *
pph_in_qual_use_vec (pph_stream *stream)
{
  unsigned i, num;
  VEC(qualified_typedef_usage_t,gc) *v;

  num = pph_in_uint (stream);
  v = NULL;
  for (i = 0; i < num; i++)
    {
      qualified_typedef_usage_t q;
      q.typedef_decl = pph_in_tree (stream);
      q.context = pph_in_tree (stream);
      /* FIXME pph: also read location.  */
      VEC_safe_push (qualified_typedef_usage_t, gc, v, &q);
    }

  return v;
}


/* Forward declaration to break cyclic dependencies.  */
static struct cp_binding_level *pph_in_binding_level (pph_stream *);

/* Helper for pph_in_cxx_binding.  Read and return a cxx_binding
   instance from STREAM.  */

static cxx_binding *
pph_in_cxx_binding_1 (pph_stream *stream)
{
  struct bitpack_d bp;
  cxx_binding *cb;
  tree value, type;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (cxx_binding *) pph_in_shared_data (stream, ix);

  value = pph_in_tree (stream);
  type = pph_in_tree (stream);
  ALLOC_AND_REGISTER (stream, ix, cb, cxx_binding_make (value, type));
  cb->scope = pph_in_binding_level (stream);
  bp = pph_in_bitpack (stream);
  cb->value_is_inherited = bp_unpack_value (&bp, 1);
  cb->is_local = bp_unpack_value (&bp, 1);

  return cb;
}


/* Read and return an instance of cxx_binding from STREAM.  */

static cxx_binding *
pph_in_cxx_binding (pph_stream *stream)
{
  cxx_binding *curr, *prev, *cb;

  /* Read the current binding first.  */
  cb = pph_in_cxx_binding_1 (stream);

  /* Read the list of previous bindings.  */
  for (curr = cb; curr; curr = prev)
    {
      prev = pph_in_cxx_binding_1 (stream);
      curr->previous = prev;
    }

  return cb;
}


/* Read all the fields of cp_class_binding instance CB to OB.  */

static cp_class_binding *
pph_in_class_binding (pph_stream *stream)
{
  cp_class_binding *cb;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (cp_class_binding *) pph_in_shared_data (stream, ix);

  ALLOC_AND_REGISTER (stream, ix, cb, ggc_alloc_cleared_cp_class_binding ());
  cb->base = pph_in_cxx_binding (stream);
  cb->identifier = pph_in_tree (stream);

  return cb;
}


/* Read and return an instance of cp_label_binding from STREAM.  */

static cp_label_binding *
pph_in_label_binding (pph_stream *stream)
{
  cp_label_binding *lb;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (cp_label_binding *) pph_in_shared_data (stream, ix);

  ALLOC_AND_REGISTER (stream, ix, lb, ggc_alloc_cleared_cp_label_binding ());
  lb->label = pph_in_tree (stream);
  lb->prev_value = pph_in_tree (stream);

  return lb;
}


/* Read and return an instance of cp_binding_level from STREAM.  */

static struct cp_binding_level *
pph_in_binding_level (pph_stream *stream)
{
  unsigned i, num, ix;
  struct cp_binding_level *bl;
  struct bitpack_d bp;
  enum pph_record_marker marker;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (struct cp_binding_level *) pph_in_shared_data (stream, ix);

  ALLOC_AND_REGISTER (stream, ix, bl, ggc_alloc_cleared_cp_binding_level ());

  bl->names = pph_in_chain (stream);
  bl->namespaces = pph_in_chain (stream);

  bl->static_decls = pph_in_tree_vec (stream);

  bl->usings = pph_in_chain (stream);
  bl->using_directives = pph_in_chain (stream);

  num = pph_in_uint (stream);
  bl->class_shadowed = NULL;
  for (i = 0; i < num; i++)
    {
      cp_class_binding *cb = pph_in_class_binding (stream);
      VEC_safe_push (cp_class_binding, gc, bl->class_shadowed, cb);
    }

  bl->type_shadowed = pph_in_tree (stream);

  num = pph_in_uint (stream);
  bl->shadowed_labels = NULL;
  for (i = 0; i < num; i++)
    {
      cp_label_binding *sl = pph_in_label_binding (stream);
      VEC_safe_push (cp_label_binding, gc, bl->shadowed_labels, sl);
    }

  bl->blocks = pph_in_chain (stream);
  bl->this_entity = pph_in_tree (stream);
  bl->level_chain = pph_in_binding_level (stream);
  bl->dead_vars_from_for = pph_in_tree_vec (stream);
  bl->statement_list = pph_in_chain (stream);
  bl->binding_depth = pph_in_uint (stream);

  bp = pph_in_bitpack (stream);
  bl->kind = (enum scope_kind) bp_unpack_value (&bp, 4);
  bl->keep = bp_unpack_value (&bp, 1);
  bl->more_cleanups_ok = bp_unpack_value (&bp, 1);
  bl->have_cleanups = bp_unpack_value (&bp, 1);

  return bl;
}


/* Read in the tree_common fields.  */

static void
pph_in_tree_common (pph_stream *stream, tree t)
{
  /* The 'struct tree_typed typed' base class is handled in LTO.  */
  TREE_CHAIN (t) = pph_in_tree (stream);
}

/* Read and return an instance of struct c_language_function from STREAM.  */

static struct c_language_function *
pph_in_c_language_function (pph_stream *stream)
{
  struct c_language_function *clf;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (struct c_language_function *) pph_in_shared_data (stream,
	                                                               ix);

  ALLOC_AND_REGISTER (stream, ix, clf,
		      ggc_alloc_cleared_c_language_function ());
  clf->x_stmt_tree.x_cur_stmt_list = pph_in_tree_vec (stream);
  clf->x_stmt_tree.stmts_are_full_exprs_p = pph_in_uint (stream);

  return clf;
}


/* Read and return an instance of struct language_function from STREAM.  */

static struct language_function *
pph_in_language_function (pph_stream *stream)
{
  struct bitpack_d bp;
  struct language_function *lf;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (struct language_function *) pph_in_shared_data (stream,
								     ix);

  ALLOC_AND_REGISTER (stream, ix, lf, ggc_alloc_cleared_language_function ());
  memcpy (&lf->base, pph_in_c_language_function (stream),
	  sizeof (struct c_language_function));
  lf->x_cdtor_label = pph_in_tree (stream);
  lf->x_current_class_ptr = pph_in_tree (stream);
  lf->x_current_class_ref = pph_in_tree (stream);
  lf->x_eh_spec_block = pph_in_tree (stream);
  lf->x_in_charge_parm = pph_in_tree (stream);
  lf->x_vtt_parm = pph_in_tree (stream);
  lf->x_return_value = pph_in_tree (stream);
  bp = pph_in_bitpack (stream);
  lf->x_returns_value = bp_unpack_value (&bp, 1);
  lf->x_returns_null = bp_unpack_value (&bp, 1);
  lf->x_returns_abnormally = bp_unpack_value (&bp, 1);
  lf->x_in_function_try_handler = bp_unpack_value (&bp, 1);
  lf->x_in_base_initializer = bp_unpack_value (&bp, 1);
  lf->can_throw = bp_unpack_value (&bp, 1);

  /* FIXME pph.  We are not reading lf->x_named_labels.  */

  lf->bindings = pph_in_binding_level (stream);
  lf->x_local_names = pph_in_tree_vec (stream);

  /* FIXME pph.  We are not reading lf->extern_decl_map.  */

  return lf;
}


/* Read all the fields of lang_decl_fn instance LDF from STREAM.  */

static void
pph_in_ld_fn (pph_stream *stream, struct lang_decl_fn *ldf)
{
  struct bitpack_d bp;

  /* Read all the fields in lang_decl_min.  */
  pph_in_ld_min (stream, &ldf->min);

  bp = pph_in_bitpack (stream);
  ldf->operator_code = (enum tree_code) bp_unpack_value (&bp, 16);
  ldf->global_ctor_p = bp_unpack_value (&bp, 1);
  ldf->global_dtor_p = bp_unpack_value (&bp, 1);
  ldf->constructor_attr = bp_unpack_value (&bp, 1);
  ldf->destructor_attr = bp_unpack_value (&bp, 1);
  ldf->assignment_operator_p = bp_unpack_value (&bp, 1);
  ldf->static_function = bp_unpack_value (&bp, 1);
  ldf->pure_virtual = bp_unpack_value (&bp, 1);
  ldf->defaulted_p = bp_unpack_value (&bp, 1);
  ldf->has_in_charge_parm_p = bp_unpack_value (&bp, 1);
  ldf->has_vtt_parm_p = bp_unpack_value (&bp, 1);
  ldf->pending_inline_p = bp_unpack_value (&bp, 1);
  ldf->nonconverting = bp_unpack_value (&bp, 1);
  ldf->thunk_p = bp_unpack_value (&bp, 1);
  ldf->this_thunk_p = bp_unpack_value (&bp, 1);
  ldf->hidden_friend_p = bp_unpack_value (&bp, 1);

  ldf->befriending_classes = pph_in_tree (stream);
  ldf->context = pph_in_tree (stream);

  if (ldf->thunk_p == 0)
    ldf->u5.cloned_function = pph_in_tree (stream);
  else if (ldf->thunk_p == 1)
    ldf->u5.fixed_offset = pph_in_uint (stream);
  else
    gcc_unreachable ();

  if (ldf->pending_inline_p == 1)
    ldf->u.pending_inline_info = pph_in_token_cache (stream);
  else if (ldf->pending_inline_p == 0)
    ldf->u.saved_language_function = pph_in_language_function (stream);
}


/* Read applicable fields of struct function from STREAM.  Associate
   the read structure to DECL.  */

static struct function *
pph_in_struct_function (pph_stream *stream, tree decl)
{
  size_t count, i;
  unsigned ix;
  enum pph_record_marker marker;
  struct function *fn;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;

  /* Since struct function is embedded in every decl, fn cannot be shared.  */
  gcc_assert (marker != PPH_RECORD_SHARED);

  allocate_struct_function (decl, false);
  fn = DECL_STRUCT_FUNCTION (decl);

  input_struct_function_base (fn, stream->data_in, stream->ib);

  /* struct eh_status *eh;					-- zero init */
  /* struct control_flow_graph *cfg;				-- zero init */
  /* struct gimple_seq_d *gimple_body;				-- zero init */
  /* struct gimple_df *gimple_df;				-- zero init */
  /* struct loops *x_current_loops;				-- zero init */
  /* struct stack_usage *su;					-- zero init */
  /* htab_t value_histograms;					-- zero init */
  /* tree decl;							-- zero init */
  /* tree static_chain_decl;					-- in base */
  /* tree nonlocal_goto_save_area;				-- in base */
  /* tree local_decls;						-- in base */
  /* struct machine_function * machine;				-- zero init */

  fn->language = pph_in_language_function (stream);

  count = pph_in_uint (stream);
  if ( count > 0 )
    {
      fn->used_types_hash = htab_create_ggc (37, htab_hash_pointer,
					     htab_eq_pointer, NULL);
      for (i = 0; i < count;  i++)
	{
	  void **slot;
	  tree type = pph_in_tree (stream);
	  slot = htab_find_slot (fn->used_types_hash, type, INSERT);
	  if (*slot == NULL)
	    *slot = type;
	}
    }
  /* else zero initialized */

  /* int last_stmt_uid;						-- zero init */
  /* int funcdef_no;						-- zero init */
  /* location_t function_start_locus;				-- in base */
  /* location_t function_end_locus;				-- in base */
  /* unsigned int curr_properties;				-- in base */
  /* unsigned int last_verified;				-- zero init */
  /* const char *cannot_be_copied_reason;			-- zero init */

  /* unsigned int va_list_gpr_size : 8;				-- in base */
  /* unsigned int va_list_fpr_size : 8;				-- in base */
  /* unsigned int calls_setjmp : 1;				-- in base */
  /* unsigned int calls_alloca : 1;				-- in base */
  /* unsigned int has_nonlocal_label : 1;			-- in base */
  /* unsigned int cannot_be_copied_set : 1;			-- zero init */
  /* unsigned int stdarg : 1;					-- in base */
  /* unsigned int after_inlining : 1;				-- in base */
  /* unsigned int always_inline_functions_inlined : 1;		-- in base */
  /* unsigned int can_throw_non_call_exceptions : 1;		-- in base */
  /* unsigned int returns_struct : 1;				-- in base */
  /* unsigned int returns_pcc_struct : 1;			-- in base */
  /* unsigned int after_tree_profile : 1;			-- in base */
  /* unsigned int has_local_explicit_reg_vars : 1;		-- in base */
  /* unsigned int is_thunk : 1;					-- in base */

  return fn;
}


/* Read all the fields of lang_decl_ns instance LDNS from STREAM.  */

static void
pph_in_ld_ns (pph_stream *stream, struct lang_decl_ns *ldns)
{
  ldns->level = pph_in_binding_level (stream);
}


/* Read all the fields of lang_decl_parm instance LDP from STREAM.  */

static void
pph_in_ld_parm (pph_stream *stream, struct lang_decl_parm *ldp)
{
  ldp->level = pph_in_uint (stream);
  ldp->index = pph_in_uint (stream);
}


/* Read language specific data in DECL from STREAM.  */

static void
pph_in_lang_specific (pph_stream *stream, tree decl)
{
  struct lang_decl *ld;
  struct lang_decl_base *ldb;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return;
  else if (marker == PPH_RECORD_SHARED)
    {
      DECL_LANG_SPECIFIC (decl) =
	(struct lang_decl *) pph_in_shared_data (stream, ix);
      return;
    }

  /* Allocate a lang_decl structure for DECL.  */
  retrofit_lang_decl (decl);
  ld = DECL_LANG_SPECIFIC (decl);

  /* Now register it.  We would normally use ALLOC_AND_REGISTER,
     but retrofit_lang_decl does not return a pointer.  */
  pph_register_shared_data (stream, ld, ix);

  /* Read all the fields in lang_decl_base.  */
  ldb = &ld->u.base;
  pph_in_ld_base (stream, ldb);

  if (ldb->selector == 0)
    {
      /* Read all the fields in lang_decl_min.  */
      pph_in_ld_min (stream, &ld->u.min);
    }
  else if (ldb->selector == 1)
    {
      /* Read all the fields in lang_decl_fn.  */
      pph_in_ld_fn (stream, &ld->u.fn);
    }
  else if (ldb->selector == 2)
    {
      /* Read all the fields in lang_decl_ns.  */
      pph_in_ld_ns (stream, &ld->u.ns);
    }
  else if (ldb->selector == 3)
    {
      /* Read all the fields in lang_decl_parm.  */
      pph_in_ld_parm (stream, &ld->u.parm);
    }
  else
    gcc_unreachable ();
}


/* Allocate a tree node with code CODE.  IB and DATA_IN are used to
   read more data from the stream, if needed to build this node.
   Return NULL if we did not want to handle this node.  In that case,
   the caller will call make_node to allocate this tree.  */

tree
pph_alloc_tree (enum tree_code code,
	               struct lto_input_block *ib ATTRIBUTE_UNUSED,
		       struct data_in *data_in)
{
  pph_stream *stream = (pph_stream *) data_in->sdata;

  if (code == CALL_EXPR)
    {
      unsigned nargs = pph_in_uint (stream);
      return build_vl_exp (CALL_EXPR, nargs + 3);
    }

  return NULL_TREE;
}


/* Read all the fields in lang_type_header instance LTH from STREAM.  */

static void
pph_in_lang_type_header (pph_stream *stream,
				  struct lang_type_header *lth)
{
  struct bitpack_d bp;

  bp = pph_in_bitpack (stream);
  lth->is_lang_type_class = bp_unpack_value (&bp, 1);
  lth->has_type_conversion = bp_unpack_value (&bp, 1);
  lth->has_copy_ctor = bp_unpack_value (&bp, 1);
  lth->has_default_ctor = bp_unpack_value (&bp, 1);
  lth->const_needs_init = bp_unpack_value (&bp, 1);
  lth->ref_needs_init = bp_unpack_value (&bp, 1);
  lth->has_const_copy_assign = bp_unpack_value (&bp, 1);
}


/* Read the vector V of tree_pair_s instances from STREAM.  */

static VEC(tree_pair_s,gc) *
pph_in_tree_pair_vec (pph_stream *stream)
{
  unsigned i, num;
  VEC(tree_pair_s,gc) *v;

  num = pph_in_uint (stream);
  for (i = 0, v = NULL; i < num; i++)
    {
      tree_pair_s p;
      p.purpose = pph_in_tree (stream);
      p.value = pph_in_tree (stream);
      VEC_safe_push (tree_pair_s, gc, v, &p);
    }

  return v;
}


/* Read a struct sorted_fields_type instance SFT to STREAM.  REF_P is
   true if the tree nodes should be written as references.  */

static struct sorted_fields_type *
pph_in_sorted_fields_type (pph_stream *stream)
{
  unsigned i, num_fields;
  struct sorted_fields_type *v;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (struct sorted_fields_type *) pph_in_shared_data (stream, ix);

  num_fields = pph_in_uint (stream);
  ALLOC_AND_REGISTER (stream, ix, v, sorted_fields_type_new (num_fields));
  for (i = 0; i < num_fields; i++)
    v->elts[i] = pph_in_tree (stream);

  return v;
}


/* Read all the fields in lang_type_class instance LTC to STREAM.
   REF_P is true if all the trees in the structure should be written
   as references.  */

static void
pph_in_lang_type_class (pph_stream *stream,
				  struct lang_type_class *ltc)
{
  struct bitpack_d bp;
  enum pph_record_marker marker;
  unsigned ix;

  ltc->align = pph_in_uchar (stream);

  bp = pph_in_bitpack (stream);
  ltc->has_mutable = bp_unpack_value (&bp, 1);
  ltc->com_interface = bp_unpack_value (&bp, 1);
  ltc->non_pod_class = bp_unpack_value (&bp, 1);
  ltc->nearly_empty_p = bp_unpack_value (&bp, 1);
  ltc->user_align = bp_unpack_value (&bp, 1);
  ltc->has_copy_assign = bp_unpack_value (&bp, 1);
  ltc->has_new = bp_unpack_value (&bp, 1);
  ltc->has_array_new = bp_unpack_value (&bp, 1);
  ltc->gets_delete = bp_unpack_value (&bp, 2);
  ltc->interface_only = bp_unpack_value (&bp, 1);
  ltc->interface_unknown = bp_unpack_value (&bp, 1);
  ltc->contains_empty_class_p = bp_unpack_value (&bp, 1);
  ltc->anon_aggr = bp_unpack_value (&bp, 1);
  ltc->non_zero_init = bp_unpack_value (&bp, 1);
  ltc->empty_p = bp_unpack_value (&bp, 1);
  ltc->vec_new_uses_cookie = bp_unpack_value (&bp, 1);
  ltc->declared_class = bp_unpack_value (&bp, 1);
  ltc->diamond_shaped = bp_unpack_value (&bp, 1);
  ltc->repeated_base = bp_unpack_value (&bp, 1);
  ltc->being_defined = bp_unpack_value (&bp, 1);
  ltc->java_interface = bp_unpack_value (&bp, 1);
  ltc->debug_requested = bp_unpack_value (&bp, 1);
  ltc->fields_readonly = bp_unpack_value (&bp, 1);
  ltc->use_template = bp_unpack_value (&bp, 2);
  ltc->ptrmemfunc_flag = bp_unpack_value (&bp, 1);
  ltc->was_anonymous = bp_unpack_value (&bp, 1);
  ltc->lazy_default_ctor = bp_unpack_value (&bp, 1);
  ltc->lazy_copy_ctor = bp_unpack_value (&bp, 1);
  ltc->lazy_copy_assign = bp_unpack_value (&bp, 1);
  ltc->lazy_destructor = bp_unpack_value (&bp, 1);
  ltc->has_const_copy_ctor = bp_unpack_value (&bp, 1);
  ltc->has_complex_copy_ctor = bp_unpack_value (&bp, 1);
  ltc->has_complex_copy_assign = bp_unpack_value (&bp, 1);
  ltc->non_aggregate = bp_unpack_value (&bp, 1);
  ltc->has_complex_dflt = bp_unpack_value (&bp, 1);
  ltc->has_list_ctor = bp_unpack_value (&bp, 1);
  ltc->non_std_layout = bp_unpack_value (&bp, 1);
  ltc->is_literal = bp_unpack_value (&bp, 1);
  ltc->lazy_move_ctor = bp_unpack_value (&bp, 1);
  ltc->lazy_move_assign = bp_unpack_value (&bp, 1);
  ltc->has_complex_move_ctor = bp_unpack_value (&bp, 1);
  ltc->has_complex_move_assign = bp_unpack_value (&bp, 1);
  ltc->has_constexpr_ctor = bp_unpack_value (&bp, 1);

  ltc->primary_base = pph_in_tree (stream);
  ltc->vcall_indices = pph_in_tree_pair_vec (stream);
  ltc->vtables = pph_in_tree (stream);
  ltc->typeinfo_var = pph_in_tree (stream);
  ltc->vbases = pph_in_tree_vec (stream);

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_START)
    {
      ltc->nested_udts = pph_in_binding_table (stream);
      pph_register_shared_data (stream, ltc->nested_udts, ix);
    }
  else if (marker == PPH_RECORD_SHARED)
    ltc->nested_udts = (binding_table) pph_in_shared_data (stream, ix);

  ltc->as_base = pph_in_tree (stream);
  ltc->pure_virtuals = pph_in_tree_vec (stream);
  ltc->friend_classes = pph_in_tree (stream);
  ltc->methods = pph_in_tree_vec (stream);
  ltc->key_method = pph_in_tree (stream);
  ltc->decl_list = pph_in_tree (stream);
  ltc->template_info = pph_in_tree (stream);
  ltc->befriending_classes = pph_in_tree (stream);
  ltc->objc_info = pph_in_tree (stream);
  ltc->sorted_fields = pph_in_sorted_fields_type (stream);
  ltc->lambda_expr = pph_in_tree (stream);
}


/* Read all fields of struct lang_type_ptrmem instance LTP from STREAM.  */

static void
pph_in_lang_type_ptrmem (pph_stream *stream,
				  struct lang_type_ptrmem *ltp)
{
  ltp->record = pph_in_tree (stream);
}


/* Read all the fields in struct lang_type from STREAM.  */

static struct lang_type *
pph_in_lang_type (pph_stream *stream)
{
  struct lang_type *lt;
  enum pph_record_marker marker;
  unsigned ix;

  marker = pph_in_start_record (stream, &ix);
  if (marker == PPH_RECORD_END)
    return NULL;
  else if (marker == PPH_RECORD_SHARED)
    return (struct lang_type *) pph_in_shared_data (stream, ix);

  ALLOC_AND_REGISTER (stream, ix, lt,
		      ggc_alloc_cleared_lang_type (sizeof (struct lang_type)));

  pph_in_lang_type_header (stream, &lt->u.h);
  if (lt->u.h.is_lang_type_class)
    pph_in_lang_type_class (stream, &lt->u.c);
  else
    pph_in_lang_type_ptrmem (stream, &lt->u.ptrmem);

  return lt;
}


/* Add all bindings declared in BL to NS.  */

static void
pph_add_bindings_to_namespace (struct cp_binding_level *bl, tree ns)
{
  tree t, chain;

  /* The chains are built backwards (ref: add_decl_to_level),
     reverse them before putting them back in.  */
  bl->names = nreverse (bl->names);
  bl->namespaces = nreverse (bl->namespaces);

  for (t = bl->names; t; t = chain)
    {
      /* Pushing a decl into a scope clobbers its DECL_CHAIN.
	 Preserve it.  */
      chain = DECL_CHAIN (t);
      pushdecl_into_namespace (t, ns);
    }

  for (t = bl->namespaces; t; t = chain)
    {
      /* Pushing a decl into a scope clobbers its DECL_CHAIN.
	 Preserve it.  */
      chain = DECL_CHAIN (t);

      /* FIXME pph: we should first check to see if it isn't already there.
	 If it is, we should use this function recursively to merge
	 the bindings in T in the corresponding namespace.  */
      pushdecl_into_namespace (t, ns);
    }
}


/* Merge scope_chain bindings from STREAM into global_namespace. */

static void
pph_in_scope_chain (pph_stream *stream)
{
  struct cp_binding_level *pph_bindings;

  pph_bindings = pph_in_binding_level (stream);

  /* Merge the bindings obtained from STREAM in the global namespace.  */
  pph_add_bindings_to_namespace (pph_bindings, global_namespace);
}


/* Wrap a macro DEFINITION for printing in an error.  */

static char *
wrap_macro_def (const char *definition)
{
  char *string;
  if (definition)
    {
      size_t length;
      length = strlen (definition);
      string = (char *) xmalloc (length+3);
      string[0] = '"';
      strcpy (string + 1, definition);
      string[length + 1] = '"';
      string[length + 2] = '\0';
    }
  else
    string = xstrdup ("undefined");
  return string;
}


/* Report a macro validation error in FILENAME for macro IDENT,
   which should have the value EXPECTED but actually had the value FOUND. */

static void
report_validation_error (const char *filename,
			 const char *ident, const char *found,
			 const char *before, const char *after)
{
  char* quote_found = wrap_macro_def (found);
  char* quote_before = wrap_macro_def (before);
  char* quote_after = wrap_macro_def (after);
  error ("PPH file %s fails macro validation, "
         "%s is %s and should be %s or %s\n",
         filename, ident, quote_found, quote_before, quote_after);
  free (quote_found);
  free (quote_before);
  free (quote_after);
}


/* Load the IDENTIFERS for a hunk from a STREAM.  */

static void
pph_in_identifiers (pph_stream *stream, cpp_idents_used *identifiers)
{
  unsigned int j;
  unsigned int max_ident_len, max_value_len, num_entries;
  unsigned int ident_len, before_len, after_len;

  max_ident_len = pph_in_uint (stream);
  identifiers->max_ident_len = max_ident_len;
  max_value_len = pph_in_uint (stream);
  identifiers->max_value_len = max_value_len;
  num_entries = pph_in_uint (stream);
  identifiers->num_entries = num_entries;
  identifiers->entries = XCNEWVEC (cpp_ident_use, num_entries);
  identifiers->strings = XCNEW (struct obstack);

  /* Strings need no alignment.  */
  _obstack_begin (identifiers->strings, 0, 0,
                  (void *(*) (long)) xmalloc,
                  (void (*) (void *)) free);
  obstack_alignment_mask (identifiers->strings) = 0;
  /* FIXME pph: We probably need to free all these things somewhere.  */

  /* Read the identifiers in HUNK. */
  for (j = 0; j < num_entries; ++j)
    {
      const char *s;
      identifiers->entries[j].used_by_directive = pph_in_uint (stream);
      identifiers->entries[j].expanded_to_text = pph_in_uint (stream);
      s = pph_in_string (stream);
      gcc_assert (s);
      ident_len = strlen (s);
      identifiers->entries[j].ident_len = ident_len;
      identifiers->entries[j].ident_str =
        (const char *) obstack_copy0 (identifiers->strings, s, ident_len);

      s = pph_in_string (stream);
      if (s)
	{
	  before_len = strlen (s);
	  identifiers->entries[j].before_len = before_len;
	  identifiers->entries[j].before_str = (const char *)
	      obstack_copy0 (identifiers->strings, s, before_len);
	}
      else
	{
	  /* The identifier table expects NULL entries to have
	     a length of -1U.  */
	  identifiers->entries[j].before_len = -1U;
	  identifiers->entries[j].before_str = NULL;
	}

      s = pph_in_string (stream);
      if (s)
	{
	  after_len = strlen (s);
	  identifiers->entries[j].after_len = after_len;
	  identifiers->entries[j].after_str = (const char *)
	      obstack_copy0 (identifiers->strings, s, after_len);
	}
      else
	{
	  /* The identifier table expects NULL entries to have
	     a length of -1U.  */
	  identifiers->entries[j].after_len = -1U;
	  identifiers->entries[j].after_str = NULL;
	}
    }
}


/* Read contents of PPH file in STREAM.  */

static void
pph_read_file_contents (pph_stream *stream)
{
  bool verified;
  cpp_ident_use *bad_use;
  const char *cur_def;
  cpp_idents_used idents_used;

  pph_in_identifiers (stream, &idents_used);

  /* FIXME pph: This validation is weak.  */
  verified = cpp_lt_verify_1 (parse_in, &idents_used, &bad_use, &cur_def, true);
  if (!verified)
    report_validation_error (stream->name, bad_use->ident_str, cur_def,
                             bad_use->before_str, bad_use->after_str);

  /* Re-instantiate all the pre-processor symbols defined by STREAM.  */
  cpp_lt_replay (parse_in, &idents_used);

  /* Read the bindings from STREAM and merge them with the current bindings.  */
  pph_in_scope_chain (stream);

  if (flag_pph_dump_tree)
    pph_dump_namespace (pph_logfile, global_namespace);

  keyed_classes = pph_in_tree (stream);
  /* FIXME pph: This call replaces the tinfo, we should merge instead.
     See pph_in_tree_vec.  */
  unemitted_tinfo_decls = pph_in_tree_vec (stream);
}


/* Read PPH file FILENAME.  */

void
pph_read_file (const char *filename)
{
  pph_stream *stream;

  if (flag_pph_debug >= 1)
    fprintf (pph_logfile, "PPH: Reading %s\n", filename);

  stream = pph_stream_open (filename, "rb");
  if (stream)
    {
      pph_read_file_contents (stream);
      pph_stream_close (stream);

      if (flag_pph_debug >= 1)
        fprintf (pph_logfile, "PPH: Closing %s\n", filename);
    }
  else
    error ("Cannot open PPH file for reading: %s: %m", filename);
}


/* Read the attributes for a FUNCTION_DECL FNDECL.  If FNDECL had
   a body, mark it for expansion.  */

static void
pph_in_function_decl (pph_stream *stream, tree fndecl)
{
  DECL_INITIAL (fndecl) = pph_in_tree (stream);
  pph_in_lang_specific (stream, fndecl);
  DECL_SAVED_TREE (fndecl) = pph_in_tree (stream);
  DECL_STRUCT_FUNCTION (fndecl) = pph_in_struct_function (stream, fndecl);
  DECL_CHAIN (fndecl) = pph_in_tree (stream);
  if (DECL_SAVED_TREE (fndecl))
    {
      /* FIXME pph - This is somewhat gross.  When we generated the
	 PPH image, the parser called expand_or_defer_fn on FNDECL,
	 which marked it DECL_EXTERNAL (see expand_or_defer_fn_1 for
	 details).

	 However, this is not really an extern definition, so it was
	 also marked not-really-extern (yes, I know...). If this
	 happens, we need to unmark it, otherwise the code generator
	 will toss it out.  */
      if (DECL_NOT_REALLY_EXTERN (fndecl))
	DECL_EXTERNAL (fndecl) = 0;
      expand_or_defer_fn (fndecl);
    }
}


/* Callback for reading ASTs from a stream.  This reads all the fields
   that are not processed by default by the common tree pickler.
   IB, DATA_IN are as in lto_read_tree.  EXPR is the partially materialized
   tree.  */

void
pph_read_tree (struct lto_input_block *ib ATTRIBUTE_UNUSED,
		      struct data_in *data_in, tree expr)
{
  pph_stream *stream = (pph_stream *) data_in->sdata;

  switch (TREE_CODE (expr))
    {
    /* TREES NEEDING EXTRA WORK */

    /* tcc_declaration */

    case DEBUG_EXPR_DECL:
    case IMPORTED_DECL:
    case LABEL_DECL:
    case RESULT_DECL:
      DECL_INITIAL (expr) = pph_in_tree (stream);
      break;

    case CONST_DECL:
    case FIELD_DECL:
    case NAMESPACE_DECL:
    case PARM_DECL:
    case USING_DECL:
    case VAR_DECL:
      /* FIXME pph: Should we merge DECL_INITIAL into lang_specific? */
      DECL_INITIAL (expr) = pph_in_tree (stream);
      pph_in_lang_specific (stream, expr);
      /* DECL_CHAIN is handled by generic code, except for VAR_DECLs.  */
      if (TREE_CODE (expr) == VAR_DECL)
	DECL_CHAIN (expr) = pph_in_tree (stream);
      break;

    case FUNCTION_DECL:
      pph_in_function_decl (stream, expr);
      break;

    case TYPE_DECL:
      DECL_INITIAL (expr) = pph_in_tree (stream);
      pph_in_lang_specific (stream, expr);
      DECL_ORIGINAL_TYPE (expr) = pph_in_tree (stream);
      break;

    case TEMPLATE_DECL:
      DECL_INITIAL (expr) = pph_in_tree (stream);
      pph_in_lang_specific (stream, expr);
      DECL_TEMPLATE_RESULT (expr) = pph_in_tree (stream);
      DECL_TEMPLATE_PARMS (expr) = pph_in_tree (stream);
      DECL_CONTEXT (expr) = pph_in_tree (stream);
      break;

    /* tcc_type */

    case ARRAY_TYPE:
    case BOOLEAN_TYPE:
    case COMPLEX_TYPE:
    case ENUMERAL_TYPE:
    case FIXED_POINT_TYPE:
    case FUNCTION_TYPE:
    case INTEGER_TYPE:
    case LANG_TYPE:
    case METHOD_TYPE:
    case NULLPTR_TYPE:
    case OFFSET_TYPE:
    case POINTER_TYPE:
    case REAL_TYPE:
    case REFERENCE_TYPE:
    case VECTOR_TYPE:
    case VOID_TYPE:
      TYPE_LANG_SPECIFIC (expr) = pph_in_lang_type (stream);
      break;

    case QUAL_UNION_TYPE:
    case RECORD_TYPE:
    case UNION_TYPE:
      TYPE_LANG_SPECIFIC (expr) = pph_in_lang_type (stream);
      TYPE_BINFO (expr) = pph_in_tree (stream);
      break;

    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case DECLTYPE_TYPE:
    case TEMPLATE_TEMPLATE_PARM:
    case TEMPLATE_TYPE_PARM:
    case TYPENAME_TYPE:
    case TYPEOF_TYPE:
      TYPE_LANG_SPECIFIC (expr) = pph_in_lang_type (stream);
      TYPE_CACHED_VALUES (expr) = pph_in_tree (stream);
      /* Note that we are using TYPED_CACHED_VALUES for it access to 
         the generic .values field of types. */
      break;

    /* tcc_statement */

    case STATEMENT_LIST:
      {
        HOST_WIDE_INT i, num_trees = pph_in_uint (stream);
        for (i = 0; i < num_trees; i++)
	  {
	    tree stmt = pph_in_tree (stream);
	    append_to_statement_list_force (stmt, &expr);
	  }
      }
      break;

    /* tcc_expression */

    /* tcc_unary */

    /* tcc_vl_exp */

    /* tcc_reference */

    /* tcc_constant */

    /* tcc_exceptional */

    case OVERLOAD:
      pph_in_tree_common (stream, expr);
      OVL_FUNCTION (expr) = pph_in_tree (stream);
      break;

    case IDENTIFIER_NODE:
      {
        struct lang_identifier *id = LANG_IDENTIFIER_CAST (expr);
        id->namespace_bindings = pph_in_cxx_binding (stream);
        id->bindings = pph_in_cxx_binding (stream);
        id->class_template_info = pph_in_tree (stream);
        id->label_value = pph_in_tree (stream);
	TREE_TYPE (expr) = pph_in_tree (stream);
      }
      break;

    case BASELINK:
      pph_in_tree_common (stream, expr);
      BASELINK_BINFO (expr) = pph_in_tree (stream);
      BASELINK_FUNCTIONS (expr) = pph_in_tree (stream);
      BASELINK_ACCESS_BINFO (expr) = pph_in_tree (stream);
      break;

    case TEMPLATE_INFO:
      pph_in_tree_common (stream, expr);
      TI_TYPEDEFS_NEEDING_ACCESS_CHECKING (expr)
          = pph_in_qual_use_vec (stream);
      break;

    case TEMPLATE_PARM_INDEX:
      {
        template_parm_index *p = TEMPLATE_PARM_INDEX_CAST (expr);
        pph_in_tree_common (stream, expr);
        p->index = pph_in_uint (stream);
        p->level = pph_in_uint (stream);
        p->orig_level = pph_in_uint (stream);
        p->num_siblings = pph_in_uint (stream);
        p->decl = pph_in_tree (stream);
        /* FIXME pph: Is TEMPLATE_PARM_PARAMETER_PACK using TREE_LANG_FLAG_0
           already handled?  */
      }
      break;

    /* tcc_constant */

    case PTRMEM_CST:
      pph_in_tree_common (stream, expr);
      PTRMEM_CST_MEMBER (expr) = pph_in_tree (stream);
      break;

    /* tcc_exceptional */

    case DEFAULT_ARG:
      pph_in_tree_common (stream, expr);
      DEFARG_TOKENS (expr) = pph_in_token_cache (stream);
      DEFARG_INSTANTIATIONS (expr) = pph_in_tree_vec (stream);
      break;

    case STATIC_ASSERT:
      pph_in_tree_common (stream, expr);
      STATIC_ASSERT_CONDITION (expr) = pph_in_tree (stream);
      STATIC_ASSERT_MESSAGE (expr) = pph_in_tree (stream);
      /* FIXME pph: also STATIC_ASSERT_SOURCE_LOCATION (expr).  */
      break;

    case ARGUMENT_PACK_SELECT:
      pph_in_tree_common (stream, expr);
      ARGUMENT_PACK_SELECT_FROM_PACK (expr) = pph_in_tree (stream);
      ARGUMENT_PACK_SELECT_INDEX (expr) = pph_in_uint (stream);
      break;

    case TRAIT_EXPR:
      pph_in_tree_common (stream, expr);
      TRAIT_EXPR_TYPE1 (expr) = pph_in_tree (stream);
      TRAIT_EXPR_TYPE2 (expr) = pph_in_tree (stream);
      TRAIT_EXPR_KIND (expr) = (enum cp_trait_kind) pph_in_uint (stream);
      break;

    case LAMBDA_EXPR:
      {
        struct tree_lambda_expr *e
            = (struct tree_lambda_expr *)LAMBDA_EXPR_CHECK (expr);
        pph_in_tree_common (stream, expr);
        /* FIXME pph: also e->locus.  */
        e->capture_list = pph_in_tree (stream);
        e->this_capture = pph_in_tree (stream);
        e->return_type = pph_in_tree (stream);
        e->extra_scope = pph_in_tree (stream);
        e->discriminator = pph_in_uint (stream);
      }
      break;


    /* TREES ALREADY HANDLED */

    /* tcc_declaration */

    case TRANSLATION_UNIT_DECL:

    /* tcc_exceptional */

    case TREE_BINFO:
    case TREE_LIST:
    case TREE_VEC:

      break;


    /* TREES UNIMPLEMENTED */

    /* tcc_declaration */

    /* tcc_type */

    case TYPE_ARGUMENT_PACK:
    case TYPE_PACK_EXPANSION:
    case UNBOUND_CLASS_TEMPLATE:

    /* tcc_statement */

    case USING_STMT:
    case TRY_BLOCK:
    case EH_SPEC_BLOCK:
    case HANDLER:
    case CLEANUP_STMT:
    case IF_STMT:
    case FOR_STMT:
    case RANGE_FOR_STMT:
    case WHILE_STMT:
    case DO_STMT:
    case BREAK_STMT:
    case CONTINUE_STMT:
    case SWITCH_STMT:

    /* tcc_expression */

    case NEW_EXPR:
    case VEC_NEW_EXPR:
    case DELETE_EXPR:
    case VEC_DELETE_EXPR:
    case TYPE_EXPR:
    case VEC_INIT_EXPR:
    case THROW_EXPR:
    case EMPTY_CLASS_EXPR:
    case TEMPLATE_ID_EXPR:
    case PSEUDO_DTOR_EXPR:
    case MODOP_EXPR:
    case DOTSTAR_EXPR:
    case TYPEID_EXPR:
    case NON_DEPENDENT_EXPR:
    case CTOR_INITIALIZER:
    case MUST_NOT_THROW_EXPR:
    case EXPR_STMT:
    case TAG_DEFN:
    case OFFSETOF_EXPR:
    case SIZEOF_EXPR:
    case ARROW_EXPR:
    case ALIGNOF_EXPR:
    case AT_ENCODE_EXPR:
    case STMT_EXPR:
    case NONTYPE_ARGUMENT_PACK:
    case EXPR_PACK_EXPANSION:

    /* tcc_unary */

    case CAST_EXPR:
    case REINTERPRET_CAST_EXPR:
    case CONST_CAST_EXPR:
    case STATIC_CAST_EXPR:
    case DYNAMIC_CAST_EXPR:
    case NOEXCEPT_EXPR:
    case UNARY_PLUS_EXPR:

    /* tcc_reference */

    case MEMBER_REF:
    case OFFSET_REF:
    case SCOPE_REF:

    /* tcc_vl_exp */

    case AGGR_INIT_EXPR:


      if (flag_pph_untree)
        fprintf (pph_logfile, "PPH: unimplemented tree node %s\n",
                 tree_code_name[TREE_CODE (expr)]);
      break;


    /* TREES UNRECOGNIZED */

    default:
      if (flag_pph_untree)
        fprintf (pph_logfile, "PPH: unrecognized tree node %s\n",
                 tree_code_name[TREE_CODE (expr)]);
    }
}
