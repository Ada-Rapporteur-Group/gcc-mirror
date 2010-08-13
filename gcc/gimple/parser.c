/* GIMPLE parser.

   Copyright 2010 Free Software Foundation, Inc.
   Contributed by Sandeep Soni and Diego Novillo.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "cpplib.h"
#include "input.h"
#include "diagnostic.h"
#include "tree.h"
#include "gimple.h"
#include "toplev.h"
#include "parser.h"

/* Consumes a token if the EXPECTED_TOKEN_TYPE is exactly the one we 
   are looking for. The token is obtained by reading it from the reader P.  */
 
static const cpp_token * 
gimple_parse_expect_token (cpp_reader *p, enum cpp_ttype expected_token_type)
{
  const cpp_token *next_token;

  next_token = cpp_peek_token (p, 0);

  /* If the token type does not match then we must report an error,
     otherwise consume the token.  */

  /* FIXME The error reported should be more precise to help 
     diagnostics similar to that reported by other front ends in
     the same case.  */

  if (next_token->type != expected_token_type)
    error ("expected token type %s instead of %s",
	    cpp_type2name (expected_token_type, 0),
	    cpp_type2name (next_token->type, 0));
  else
    next_token = cpp_get_token_with_location (p, &input_location);

  return next_token;
}


/* Helper for gimple_parse_assign_stmt and gimple_parse_cond_stmt.
   Peeks a token by reading from reader P and looks it up to match 
   against the tree codes.  */

static void
gimple_parse_expect_subcode (cpp_reader *p)
{
  const cpp_token *next_token;
  const char *text;
  int i;

  gimple_parse_expect_token (p, CPP_LESS);

  /* Peeks a token and looks it up for a match.  */
 
  next_token = cpp_peek_token (p, 0);
  text = (const char *) cpp_token_as_text (p, next_token);
  for (i = ERROR_MARK; i < LAST_AND_UNUSED_TREE_CODE; i++)
    if (strcasecmp (text, tree_code_name[i]) == 0)
      break;

  /* If none of the tree codes match, then report an error. Otherwise
     consume this token.  */
  if (i == LAST_AND_UNUSED_TREE_CODE)
    error ("Expected token should be one of the tree codes");
  else
    next_token = cpp_get_token (p);

  gimple_parse_expect_token (p, CPP_COMMA);

  /* FIXME From this function we should return the tree code since it
     can be used by the other helper functions to recognize precisely.  */
}

/* Helper for gimple_parse_assign_stmt. The token read from reader P should 
   be the lhs of the tuple.  */

static void 
gimple_parse_expect_lhs (cpp_reader *p)
{  
  const cpp_token *next_token;

  /* Just before the name of the identifier we might get the symbol 
     of dereference too. If we do get it then consume that token, else
     continue recognizing the name.  */
  next_token = cpp_peek_token (p, 0);
  if (next_token->type == CPP_MULT)
    next_token = cpp_get_token (p);

  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_COMMA);
}

/* Helper for gimple_parse_assign_stmt. The token read from reader P should 
   be the first operand in rhs of the tuple.  */

static void 
gimple_parse_expect_rhs1 (cpp_reader *p)
{
  const cpp_token *next_token;
  next_token = cpp_peek_token (p, 0);

  /* Currently there is duplication in the following blocks but there
     would be more stuff added here as we go on.  */

  /* ??? Can there be more possibilities than these ?  */
  if (next_token->type == CPP_MULT)
    {
      next_token = cpp_get_token (p);
      gimple_parse_expect_token (p, CPP_NAME);
    }
  else if (next_token->type == CPP_AND)
    {
      next_token = cpp_get_token (p);
      gimple_parse_expect_token (p, CPP_NAME);    
    }
  else if (next_token->type == CPP_NAME)
      next_token = cpp_get_token (p);
  else if (next_token->type == CPP_NUMBER)
      next_token = cpp_get_token (p);
  else if (next_token->type == CPP_STRING)
      next_token = cpp_get_token (p);      

  gimple_parse_expect_token (p, CPP_COMMA); 
}

/* Helper for gimple_parse_assign_stmt. The token read from reader P should 
   be the second operand in rhs of the tuple.  */

static void 
gimple_parse_expect_rhs2 (cpp_reader *p)
{
  const cpp_token *next_token;
  next_token = cpp_peek_token (p, 0);

  /* ??? Can there be more possibilities than these ?  */

  if (next_token->type == CPP_NAME)
    {
      /* Handle a special case, this can be NULL too. 

      if (!strcasecmp ((const char *) cpp_token_as_text (p, next_token), "Null"));
        {
          
        }  */

      next_token = cpp_get_token (p);
    }
  else if (next_token->type == CPP_NUMBER)
      next_token = cpp_get_token (p);      

  gimple_parse_expect_token (p, CPP_GREATER);  
}

/* Parse a gimple_assign tuple that is read from the reader P. For now we 
   only recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void 
gimple_parse_assign_stmt (cpp_reader *p)
{
  gimple_parse_expect_subcode (p);
  gimple_parse_expect_lhs (p);
  gimple_parse_expect_rhs1 (p);
  gimple_parse_expect_rhs2 (p);
}

/* Helper for gimple_parse_cond_stmt. The token read from reader P should
   be the first operand in the tuple.  */
static void
gimple_parse_expect_op1 (cpp_reader *p)
{
  const cpp_token *next_token;
  next_token = cpp_peek_token (p, 0);

  if(next_token->type == CPP_NAME)
    next_token = cpp_get_token (p);
  else if (next_token->type == CPP_NUMBER)
    next_token = cpp_get_token (p);

  gimple_parse_expect_token (p, CPP_COMMA);  
}

/* Helper for gimple_parse_cond_stmt. The token read from reader P should
   be the second operand in the tuple.  */

static void
gimple_parse_expect_op2 (cpp_reader *p)
{
  const cpp_token *next_token;
  next_token = cpp_peek_token (p, 0);

  if(next_token->type == CPP_NAME)
    next_token = cpp_get_token (p);
  else if (next_token->type == CPP_NUMBER)
    next_token = cpp_get_token (p);
  else if (next_token->type == CPP_STRING)
    next_token = cpp_get_token (p);
  else if (next_token->type == CPP_AND)
    {
      next_token = cpp_get_token (p);
      gimple_parse_expect_token (p, CPP_NAME);
    }

  gimple_parse_expect_token (p, CPP_COMMA);  
}

/* Helper for gimple_parse_cond_stmt. The token read from reader P should
   be the true label in the tuple that means the label where the control
   jumps if the condition evaluates to true.  */

static void
gimple_parse_expect_true_label (cpp_reader *p)
{
  gimple_parse_expect_token (p, CPP_LESS);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_GREATER);
  gimple_parse_expect_token (p, CPP_COMMA);  
}

/* Helper for gimple_parse_cond_stmt. The token read from reader P should
   be the false label in the tuple that means the label where the control
   jumps if the condition evaluates to false.  */

static void
gimple_parse_expect_false_label (cpp_reader *p)
{
  gimple_parse_expect_token (p, CPP_LESS);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_RSHIFT);
}

/* Parse a gimple_cond tuple that is read from the reader P. For now we only 
   recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void
gimple_parse_cond_stmt (cpp_reader *p)
{
  gimple_parse_expect_subcode (p);
  gimple_parse_expect_op1 (p);
  gimple_parse_expect_op2 (p);
  gimple_parse_expect_true_label (p);
  gimple_parse_expect_false_label (p);
}

/* Parse a gimple_goto tuple that is read from the reader P. For now we only 
   recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void
gimple_parse_goto_stmt (cpp_reader *p)
{
  gimple_parse_expect_token (p, CPP_LSHIFT);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_RSHIFT);
}

/* Parse a gimple_label tuple that is read from the reader P. For now we only 
   recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void
gimple_parse_label_stmt (cpp_reader *p)
{
  gimple_parse_expect_token (p, CPP_LSHIFT);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_RSHIFT);  
}

/* Parse a gimple_switch tuple that is read from the reader P. For now we only 
   recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void
gimple_parse_switch_stmt (cpp_reader *p)
{
  const cpp_token *next_token;

  gimple_parse_expect_token (p, CPP_LESS);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_COMMA);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_COLON);
  gimple_parse_expect_token (p, CPP_LESS);
  gimple_parse_expect_token (p, CPP_NAME);

  for (;;)
    {
      next_token = cpp_peek_token (p, 0);
      
      if (next_token->type == CPP_GREATER)
        {
          next_token = cpp_get_token (p);
          gimple_parse_expect_token (p, CPP_COMMA);
          gimple_parse_expect_token (p, CPP_NAME);
          gimple_parse_expect_token (p, CPP_NUMBER);
          gimple_parse_expect_token (p, CPP_COLON);
          gimple_parse_expect_token (p, CPP_LESS);
          gimple_parse_expect_token (p, CPP_NAME);  
        }
      else if (next_token->type == CPP_RSHIFT)
        {
          next_token = cpp_get_token (p);
          break;
        }
      else
        error ("Incorrect use of the gimple_switch statement");
    }
}

/* Helper for gimple_parse_call_stmt. The token read from reader P should
   be the name of the function called.  */

static void
gimple_parse_expect_function_name (cpp_reader *p)
{
  gimple_parse_expect_token (p, CPP_LESS);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_COMMA);
}

/* Helper for gimple_parse_call_stmt. The token read from reader P should
   be the identifier in which the value is returned.  */

static void
gimple_parse_expect_return_var (cpp_reader *p)
{
  const cpp_token *next_token;

  next_token = cpp_peek_token (p, 0);

  if (next_token->type == CPP_NAME)
    next_token = cpp_get_token (p);
  
  /* There may be no variable in which the return value is collected.
     In that case this field in the tuple will contain NULL. We need 
     to handle it too.  */
}

/* Helper for gimple_parse_call_stmt. The token read from reader P should
   be the argument in the function call.  */

static void
gimple_parse_expect_argument (cpp_reader *p)
{
  const cpp_token *next_token;

  next_token = cpp_peek_token (p, 0);

  if (next_token->type == CPP_NUMBER)
    next_token = cpp_get_token (p);
  else if (next_token->type == CPP_NAME)
    next_token = cpp_get_token (p);
  else if (next_token->type == CPP_MULT)
    {
      next_token = cpp_get_token (p);
      gimple_parse_expect_token (p, CPP_NAME);
    }
  else
    error ("Incorrect way to specify an argument");
}

/* Parse a gimple_call tuple that is read from the reader P. For now we only 
   recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void
gimple_parse_call_stmt (cpp_reader *p)
{
  const cpp_token *next_token;

  gimple_parse_expect_function_name (p);
  gimple_parse_expect_return_var (p);
  
  for (;;)
    {
      next_token = cpp_peek_token (p, 0);
      if (next_token->type == CPP_GREATER)
        {
          next_token = cpp_get_token (p);
          break;
        }
      else if (next_token->type == CPP_COMMA)
        {
          next_token = cpp_get_token (p);
          gimple_parse_expect_argument (p);
        }
    } 
}

/* Parse a gimple_return tuple that is read from the reader P. For now we only 
   recognize the tuple. Refer gimple.def for the format of this tuple.  */

static void
gimple_parse_return_stmt (cpp_reader *p)
{
  gimple_parse_expect_token (p, CPP_LESS);
  gimple_parse_expect_token (p, CPP_NAME);
  gimple_parse_expect_token (p, CPP_GREATER);  
}

/* The TOK read from the reader P is looked up for a match. Calls the 
   corresponding function to do the parsing for the match.  */

static void 
gimple_parse_stmt (cpp_reader *p, const cpp_token *tok)
{
  const char *text;
  int i;
  text = (const char *) cpp_token_as_text (p, tok);
  for (i = GIMPLE_ERROR_MARK; i < LAST_AND_UNUSED_GIMPLE_CODE; i++)
    if (strcasecmp (text, gimple_code_name[i]) == 0)
      break;

  if (i == LAST_AND_UNUSED_GIMPLE_CODE)
    error ("Invalid gimple code used"); 
  else
    {
    switch (i)
      {
        case GIMPLE_ASSIGN:
          gimple_parse_assign_stmt (p);
          break;
        case GIMPLE_COND:
          gimple_parse_cond_stmt (p);
          break;
        case GIMPLE_LABEL:
          gimple_parse_label_stmt (p);
          break;
        case GIMPLE_GOTO:
          gimple_parse_goto_stmt (p);
          break;
        case GIMPLE_SWITCH:
          gimple_parse_switch_stmt (p);
          break;
        case GIMPLE_CALL:
          gimple_parse_call_stmt (p);
          break;
        case GIMPLE_RETURN:
          gimple_parse_return_stmt (p);
          break;
        default:
          break;
      }
    }
}


/* Main entry point for the GIMPLE front end.  */

void
gimple_main (int debug_p ATTRIBUTE_UNUSED)
{
  /* We invoke the parser here.  */
  cpp_reader *p;
  const cpp_token *tok;
  const char *input_file = "/tmp/gimple.txt";
  const char *output_file;

  struct line_maps *line_tab;
  line_tab = ggc_alloc_cleared_line_maps ();
  linemap_init (line_tab);
  p = cpp_create_reader (CLK_GNUC99, ident_hash, line_tab);
  output_file = cpp_read_main_file (p,input_file);
  if (output_file)
    {
      tok = cpp_get_token (p);
      while (tok->type != CPP_EOF)
	{
	  gimple_parse_stmt (p, tok);
	  tok = cpp_get_token (p);
	}
    }
  cpp_finish (p,NULL);
  cpp_destroy (p);   
}
