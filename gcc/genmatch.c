/* Generate pattern matching and transform code shared between
   GENERIC and GIMPLE folding code from match-and-simplify description.

   Copyright (C) 2014 Free Software Foundation, Inc.
   Contributed by Richard Biener <rguenther@suse.de>

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

#include "bconfig.h"
#include <new>
#include "system.h"
#include "coretypes.h"
#include <cpplib.h>
#include "errors.h"
#include "hashtab.h"
#include "hash-table.h"
#include "vec.h"


/* Grammar

     capture = '@' number
     op = predicate | expr [capture]
     c_expr = '{' ... '}'
     genexpr = '(' code genop... ')'
     genop = capture | genexpr | c_expr
     transform = 'match_and_transform' name expr genop

     Match and simplify (A + B) - B -> A
     (define_match_and_simplify foo
       (PLUS_EXPR (MINUS_EXPR integral_op_p@0 @1) @1)
       @0)

     Match and simplify (CST + A) + CST to CST' + A
     (define_match_and_simplify bar
       (PLUS_EXPR INTEGER_CST_P@0 (PLUS_EXPR @1 INTEGER_CST_P@2))
       (PLUS_EXPR { int_const_binop (PLUS_EXPR, captures[0], captures[2]); } @1))
*/


#define DEFTREECODE(SYM, STRING, TYPE, NARGS)   SYM,
enum tree_code {
#include "tree.def"
MAX_TREE_CODES
};
#undef DEFTREECODE

#define DEF_BUILTIN(ENUM, N, C, T, LT, B, F, NA, AT, IM, COND) ENUM,
enum built_in_function {
#include "builtins.def"
END_BUILTINS
};
#undef DEF_BUILTIN

/* Hashtable of known pattern operators.  This is pre-seeded from
   all known tree codes and all known builtin function ids.  */

struct id_base : typed_free_remove<id_base>
{
  enum id_kind { CODE, FN } kind;

  id_base (id_kind, const char *);

  hashval_t hashval;
  const char *id;

  /* hash_table support.  */
  typedef id_base value_type;
  typedef id_base compare_type;
  static inline hashval_t hash (const value_type *);
  static inline int equal (const value_type *, const compare_type *);
};

inline hashval_t
id_base::hash (const value_type *op)
{
  return op->hashval;
}
inline int
id_base::equal (const value_type *op1,
			const compare_type *op2)
{
  return (op1->hashval == op2->hashval
	  && strcmp (op1->id, op2->id) == 0);
}

static hash_table<id_base> operators;

id_base::id_base (id_kind kind_, const char *id_)
{
  kind = kind_;
  id = id_;
  hashval = htab_hash_string (id);
}

struct operator_id : public id_base
{
  operator_id (enum tree_code code_, const char *id_, unsigned nargs_)
      : id_base (id_base::CODE, id_),
      code (code_), nargs (nargs_) {}
  unsigned get_required_nargs () const { return nargs; }
  enum tree_code code;
  unsigned nargs;
};

struct fn_id : public id_base
{
  fn_id (enum built_in_function fn_, const char *id_)
      : id_base (id_base::FN, id_), fn (fn_) {}
  enum built_in_function fn;
};

static void
add_operator (enum tree_code code, const char *id,
	      const char *tcc, unsigned nargs)
{
  if (strcmp (tcc, "tcc_unary") != 0
      && strcmp (tcc, "tcc_binary") != 0
      && strcmp (tcc, "tcc_comparison") != 0
      && strcmp (tcc, "tcc_expression") != 0
      /* For {REAL,IMAG}PART_EXPR and VIEW_CONVERT_EXPR.  */
      && strcmp (tcc, "tcc_reference") != 0)
    return;
  operator_id *op = new operator_id (code, id, nargs);
  id_base **slot = operators.find_slot_with_hash (op, op->hashval, INSERT);
  if (*slot)
    fatal ("duplicate id definition");
  *slot = op;
}

static void
add_builtin (enum built_in_function code, const char *id)
{
  fn_id *fn = new fn_id (code, id);
  id_base **slot = operators.find_slot_with_hash (fn, fn->hashval, INSERT);
  if (*slot)
    fatal ("duplicate id definition");
  *slot = fn;
}


/* The predicate expression tree structure.  */

struct operand {
  enum op_type { OP_PREDICATE, OP_EXPR, OP_CAPTURE, OP_C_EXPR };
  operand (enum op_type type_) : type (type_) {}
  enum op_type type;
  virtual void gen_gimple_match (FILE *f, const char *, const char * = NULL) = 0;
  virtual void gen_gimple_transform (FILE *f, const char * = NULL) = 0;
};

struct predicate : public operand
{
  predicate (const char *ident_) : operand (OP_PREDICATE), ident (ident_) {}
  const char *ident;
  virtual void gen_gimple_match (FILE *f, const char *, const char *);
  virtual void gen_gimple_transform (FILE *, const char *) { gcc_unreachable (); }
};

struct e_operation {
  e_operation (const char *id);
  id_base *op;
};


struct expr : public operand
{
  expr (e_operation *operation_)
    : operand (OP_EXPR), operation (operation_), ops (vNULL) {}
  void append_op (operand *op) { ops.safe_push (op); }
  e_operation *operation;
  vec<operand *> ops;
  virtual void gen_gimple_match (FILE *f, const char *, const char *);
  virtual void gen_gimple_transform (FILE *f, const char *);
};

struct c_expr : public operand
{
  c_expr (const char *code_)
    : operand (OP_EXPR), code (code_) {}
  const char *code;
  virtual void gen_gimple_match (FILE *, const char *, const char *) { gcc_unreachable (); }
  virtual void gen_gimple_transform (FILE *f, const char *);
};

struct capture : public operand
{
  capture (const char *where_, operand *what_)
      : operand (OP_CAPTURE), where (where_), what (what_) {}
  const char *where;
  operand *what;
  virtual void gen_gimple_match (FILE *f, const char *, const char *);
  virtual void gen_gimple_transform (FILE *f, const char *);
};


e_operation::e_operation (const char *id)
{
  id_base tem (id_base::CODE, id);
  op = operators.find_with_hash (&tem, tem.hashval);
  if (op)
    return;

  /* Try all-uppercase.  */
  char *id2 = xstrdup (id);
  for (unsigned i = 0; i < strlen (id2); ++i)
    id2[i] = TOUPPER (id2[i]);
  new (&tem) id_base (id_base::CODE, id2);
  op = operators.find_with_hash (&tem, tem.hashval);
  if (op)
    {
      free (id2);
      return;
    }

  /* Try _EXPR appended.  */
  id2 = (char *)xrealloc (id2, strlen (id2) + sizeof ("_EXPR") + 1);
  strcat (id2, "_EXPR");
  new (&tem) id_base (id_base::CODE, id2);
  op = operators.find_with_hash (&tem, tem.hashval);
  if (op)
    {
      free (id2);
      return;
    }

  fatal ("expected operator, got %s", id);
}

struct simplify {
  simplify (const char *name_,
	    struct operand *match_, struct operand *ifexpr_,
	    struct operand *result_)
      : name (name_), match (match_), ifexpr (ifexpr_), result (result_) {}
  const char *name;
  struct operand *match;
  struct operand *ifexpr;
  struct operand *result;
};



/* Code gen off the AST.  */

static void
gen_gimple_match_fail (FILE *f, const char *label)
{
  if (!label)
    fprintf (f, "return NULL_TREE;\n");
  else
    fprintf (f, "goto %s;\n", label);
}

void
predicate::gen_gimple_match (FILE *f, const char *op, const char *label)
{
  fprintf (f, "if (!%s (%s)) ", ident, op);
  gen_gimple_match_fail (f, label);
}

void
expr::gen_gimple_match (FILE *f, const char *name, const char *label)
{
  if (operation->op->kind == id_base::CODE)
    {
      operator_id *op = static_cast <operator_id *> (operation->op);
      fprintf (f, "{\n");
      fprintf (f, "if (TREE_CODE (%s) != SSA_NAME) ", name);
      gen_gimple_match_fail (f, label);
      fprintf (f, "gimple def_stmt = SSA_NAME_DEF_STMT (%s);\n", name);
      fprintf (f, "if (!is_gimple_assign (def_stmt)\n"
	       "    || gimple_assign_rhs_code (def_stmt) != %s) ",  op->id);
      gen_gimple_match_fail (f, label);
      if (op->code == REALPART_EXPR
	  || op->code == IMAGPART_EXPR
	  || op->code == VIEW_CONVERT_EXPR
	  || op->code == BIT_FIELD_REF)
	{
	  fprintf (f, "    tree rhs = gimple_assign_rhs1 (def_stmt);\n");
	  for (unsigned i = 0; i < ops.length (); ++i)
	    {
	      fprintf (f, "   {\n");
	      fprintf (f, "     tree op = TREE_OPERAND (rhs, %d);\n", i);
	      fprintf (f, "     if (valueize && TREE_CODE (op) == SSA_NAME)\n");
	      fprintf (f, "       {\n");
	      fprintf (f, "         op = valueize (op);\n");
	      fprintf (f, "         if (!op) ");
	      gen_gimple_match_fail (f, label);
	      fprintf (f, "       }\n");
	      ops[i]->gen_gimple_match (f, "op", label);
	      fprintf (f, "   }\n");
	    }
	}
      else
	{
	  for (unsigned i = 0; i < ops.length (); ++i)
	    {
	      fprintf (f, "   {\n");
	      fprintf (f, "     tree op = gimple_assign_rhs%d (def_stmt);\n", i + 1);
	      fprintf (f, "     if (valueize && TREE_CODE (op) == SSA_NAME)\n");
	      fprintf (f, "       {\n");
	      fprintf (f, "         op = valueize (op);\n");
	      fprintf (f, "         if (!op) ");
	      gen_gimple_match_fail (f, label);
	      fprintf (f, "       }\n");
	      ops[i]->gen_gimple_match (f, "op", label);
	      fprintf (f, "   }\n");
	    }
	}
      fprintf (f, "}\n");
    }
  else
    /* FIXME - implement call support.  */
    gcc_unreachable ();
}

void
expr::gen_gimple_transform (FILE *f, const char *label)
{
  fprintf (f, "({\n");
  fprintf (f, "  if (!seq) ");
  gen_gimple_match_fail (f, label);
  fprintf (f, "  tree ops[%d];\n", ops.length ());
  for (unsigned i = 0; i < ops.length (); ++i)
    {
      fprintf (f, "   ops[%u] = ", i);
      ops[i]->gen_gimple_transform (f, label);
      fprintf (f, ";\n");
    }
  fprintf (f, "  gimple_build (seq, UNKNOWN_LOCATION, %s, TREE_TYPE (ops[0])",
	   operation->op->id);
  for (unsigned i = 0; i < ops.length (); ++i)
    fprintf (f, ", ops[%u]", i);
  fprintf (f, ", valueize);\n");
  fprintf (f, "})");
}

void
c_expr::gen_gimple_transform (FILE *f, const char *)
{
  fputs (code, f);
}

void
capture::gen_gimple_transform (FILE *f, const char *)
{
  fprintf (f, "captures[%s]", this->where);
}

void
capture::gen_gimple_match (FILE *f, const char *op, const char *label)
{
  if (this->what)
    this->what->gen_gimple_match (f, op, label);
  fprintf (f, "if (!captures[%s])\n"
	   "  captures[%s] = %s;\n"
	   "else if (captures[%s] != %s)\n",
	   this->where, this->where, op, this->where, op);
  gen_gimple_match_fail (f, label);
}


static void
write_nary_simplifiers (FILE *f, vec<simplify *>& simplifiers, unsigned n)
{
  unsigned label_cnt = 1;

  fprintf (f, "static bool\n"
	   "gimple_match_and_simplify (code_helper code, tree type");
  for (unsigned i = 0; i < n; ++i)
    fprintf (f, ", tree op%d", i);
  fprintf (f, ", code_helper *res_code, tree *res_ops, gimple_seq *seq, tree (*valueize)(tree))\n"
	   "{\n");
  for (unsigned i = 0; i < simplifiers.length (); ++i)
    {
      simplify *s = simplifiers[i];
      /* ???  This means we can't capture the outermost expression.  */
      if (s->match->type != operand::OP_EXPR)
	continue;
      expr *e = static_cast <expr *> (s->match);
      if (e->ops.length () != n)
	continue;
      char fail_label[16];
      snprintf (fail_label, 16, "fail%d", label_cnt++);
      fprintf (f, "  if (code == %s)\n", e->operation->op->id);
      fprintf (f, "    {\n");
      fprintf (f, "      tree captures[4] = {};\n");
      for (unsigned j = 0; j < n; ++j)
	{
	  char op[4] = "op0";
	  op[2] = '0' + j;
	  e->ops[j]->gen_gimple_match (f, op, fail_label);
	}
      if (s->ifexpr)
	{
	  fprintf (f, "  if (!");
	  s->ifexpr->gen_gimple_transform (f, fail_label);
	  fprintf (f, ") goto %s;", fail_label);
	}
      if (s->result->type == operand::OP_EXPR)
	{
	  e = static_cast <expr *> (s->result);
	  fprintf (f, "   *res_code = %s;\n", e->operation->op->id);
	  for (unsigned j = 0; j < e->ops.length (); ++j)
	    {
	      fprintf (f, "  res_ops[%d] = ", j);
	      e->ops[j]->gen_gimple_transform (f, fail_label);
	      fprintf (f, ";\n");
	    }
	  /* Re-fold the toplevel result.  It's basically an embedded
	     gimple_build w/o actually building the stmt.  */
	  fprintf (f, "   gimple_resimplify%d (seq, res_code, type, "
		   "res_ops, valueize);\n", e->ops.length ());
	}
      else if (s->result->type == operand::OP_CAPTURE
	       || s->result->type == operand::OP_C_EXPR)
	{
	  fprintf (f, "      res_ops[0] = ");
	  s->result->gen_gimple_transform (f, fail_label);
	  fprintf (f, ";\n");
	  fprintf (f, "      *res_code = TREE_CODE (res_ops[0]);\n");
	}
      else
	gcc_unreachable ();
      fprintf (f, "      return true;\n");
      fprintf (f, "    }\n");
      fprintf (f, "%s:\n", fail_label);
    }
  fprintf (f, "  return false;\n");
  fprintf (f, "}\n\n");
}

static void
write_gimple (FILE *f, vec<simplify *>& simplifiers)
{
  /* Include the header instead of writing it awkwardly quoted here.  */
  fprintf (f, "#include \"gimple-match-head.c\"\n\n");

  write_nary_simplifiers (f, simplifiers, 1);
  write_nary_simplifiers (f, simplifiers, 2);
  write_nary_simplifiers (f, simplifiers, 3);
}


/* libccp helpers.  */


/* Read the next non-whitespace token from R.  */

static const cpp_token *
next (cpp_reader *r)
{
  const cpp_token *token;
  do
    {
      token = cpp_get_token (r);
    }
  while (token->type == CPP_PADDING
	 && token->type != CPP_EOF);
  return token;
}

/* Peek at the next non-whitespace token from R.  */

static const cpp_token *
peek (cpp_reader *r)
{
  const cpp_token *token;
  unsigned i = 0;
  do
    {
      token = cpp_peek_token (r, i++);
    }
  while (token->type == CPP_PADDING
	 && token->type != CPP_EOF);
  return token;
}

/* Read the next token from R and assert it is of type TK.  */

static const cpp_token *
expect (cpp_reader *r, enum cpp_ttype tk)
{
  const cpp_token *token = next (r);
  if (token->type != tk)
    fatal ("error: expected %s, got %s",
	   cpp_type2name (tk, 0), cpp_type2name (token->type, 0));

  return token;
}

/* Consume the next token from R and assert it is of type TK.  */

static void
eat_token (cpp_reader *r, enum cpp_ttype tk)
{
  expect (r, tk);
}

/* Read the next token from R and assert it is of type CPP_STRING and
   return its value.  */

const char *
get_string (cpp_reader *r)
{
  const cpp_token *token = expect (r, CPP_STRING);
  return (const char *)token->val.str.text;
}

/* Read the next token from R and assert it is of type CPP_NAME and
   return its value.  */

const char *
get_ident (cpp_reader *r)
{
  const cpp_token *token = expect (r, CPP_NAME);
  return (const char *)CPP_HASHNODE (token->val.node.node)->ident.str;
}

/* Read the next token from R and assert it is of type CPP_NUMBER and
   return its value.  */

const char *
get_number (cpp_reader *r)
{
  const cpp_token *token = expect (r, CPP_NUMBER);
  return (const char *)token->val.str.text;
}


/* Parsing.  */

static e_operation *
parse_operation (cpp_reader *r)
{
  return new e_operation (get_ident (r));
}

static struct operand * parse_op (cpp_reader *r);

static struct operand *
parse_capture (cpp_reader *r, operand *op)
{
  eat_token (r, CPP_ATSIGN);
  return new capture (get_number (r), op);
}

/* Parse
     expr = (operation[capture] op...)  */
static struct operand *
parse_expr (cpp_reader *r)
{
  expr *e = new expr (parse_operation (r));
  const cpp_token *token = peek (r);
  operand *op;
  if (token->type == CPP_ATSIGN
      && !(token->flags & PREV_WHITE))
    op = parse_capture (r, e);
  else if (token->type == CPP_COLON
	   && !(token->flags & PREV_WHITE))
    fatal ("not implemented: predicates on expressions");
  else
    op = e;
  do
    {
      const cpp_token *token = peek (r);
      if (token->type == CPP_CLOSE_PAREN)
	{
	  if (e->operation->op->kind == id_base::CODE)
	    {
	      operator_id *opr = static_cast <operator_id *> (e->operation->op);
	      if (e->ops.length () != opr->get_required_nargs ())
		fatal ("got %d operands instead of the required %d",
		       e->ops.length (), opr->get_required_nargs ());
	    }
	  return op;
	}
      e->append_op (parse_op (r));
    }
  while (1);
}

/* Parse [({] .... [})] literally recording everything as string and only
   replacing captures.  */

static operand *
parse_c_expr (cpp_reader *r, cpp_ttype start)
{
  /* ???  Use an obstack to build the string.  */
  const cpp_token *token;
  cpp_ttype end;
  unsigned opencnt;
  char *code;
  eat_token (r, start);
  if (start == CPP_OPEN_PAREN)
    {
      code = xstrdup ("(");
      end = CPP_CLOSE_PAREN;
    }
  else if (start == CPP_OPEN_BRACE)
    {
      code = xstrdup ("({");
      end = CPP_CLOSE_BRACE;
    }
  else
    gcc_unreachable ();
  opencnt = 1;
  do
    {
      token = next (r);

      /* Replace captures for code-gen.  */
      if (token->type == CPP_ATSIGN)
	{
	  const cpp_token *n = peek (r);
	  if (n->type == CPP_NUMBER
	      && !(n->flags & PREV_WHITE))
	    {
	      code = (char *)xrealloc (code, strlen (code)
				       + strlen ("captures[") + 4);
	      if (token->flags & PREV_WHITE)
		strcat (code, " ");
	      strcat (code, "captures[");
	      strcat (code, get_number (r));
	      strcat (code, "]");
	      continue;
	    }
	}

      /* Count brace pairs to find the end of the expr to match.  */
      if (token->type == start)
	opencnt++;
      else if (token->type == end
	       && --opencnt == 0)
	break;

      /* Output the token as string.  */
      char *tk = (char *)cpp_token_as_text (r, token);
      code = (char *)xrealloc (code, strlen (code) + strlen (tk) + 2);
      if (token->flags & PREV_WHITE)
	strcat (code, " ");
      strcat (code, tk);
    }
  while (1);
  if (end == CPP_CLOSE_PAREN)
    {
      code = (char *)xrealloc (code, strlen (code) + 1 + 1);
      strcat (code, ")");
    }
  else if (end == CPP_CLOSE_BRACE)
    {
      code = (char *)xrealloc (code, strlen (code) + 1 + 2);
      strcat (code, "})");
    }
  else
    gcc_unreachable ();
  return new c_expr (code);
}

/* Parse
     op = predicate | ( expr ) */

static struct operand *
parse_op (cpp_reader *r)
{
  const cpp_token *token = peek (r);
  struct operand *op = NULL;
  if (token->type == CPP_OPEN_PAREN)
    {
      eat_token (r, CPP_OPEN_PAREN);
      op = parse_expr (r);
      eat_token (r, CPP_CLOSE_PAREN);
    }
  else if (token->type == CPP_OPEN_BRACE)
    {
      op = parse_c_expr (r, CPP_OPEN_BRACE);
    }
  else
    {
      /* Remaining ops are either empty or predicates  */
      if (token->type == CPP_NAME)
	{
	  op = new predicate (get_ident (r));
	  token = peek (r);
	  if (token->flags & PREV_WHITE)
	    return op;
	}
      else if (token->type != CPP_COLON
	       && token->type != CPP_ATSIGN)
	fatal ("expected expression or predicate");
      /* optionally followed by a capture and a predicate.  */
      if (token->type == CPP_COLON)
	fatal ("not implemented: predicate on leaf operand");
      if (token->type == CPP_ATSIGN)
	op = parse_capture (r, op);
    }

  return op;
}

/* Parse
     (define_match_and_simplify "<ident>"
        <op> <op>)  */

static simplify *
parse_match_and_simplify (cpp_reader *r)
{
  const cpp_token *token = peek (r);
  const char *id;
  if (token->type == CPP_NAME)
    id = get_ident (r);
  else
    {
      static int cnt;
      char *tem;
      asprintf (&tem, "anon_%d", ++cnt);
      id = tem;
    }
  struct operand *match = parse_op (r);
  token = peek (r);
  /* Conditional if (....)  */
  struct operand *ifexpr = NULL;
  if (token->type == CPP_NAME)
    {
      const char *tem = get_ident (r);
      if (strcmp (tem, "if") != 0)
	fatal ("expected 'if' or expression");
      ifexpr = parse_c_expr (r, CPP_OPEN_PAREN);
    }
  return new simplify (id, match, ifexpr, parse_op (r));
}


static size_t
round_alloc_size (size_t s)
{
  return s;
}

int
main(int argc, char **argv)
{
  cpp_reader *r;
  const cpp_token *token;
  struct line_maps *line_table;

  progname = "genmatch";

  if (argc != 2)
    return 1;

  line_table = XCNEW (struct line_maps);
  linemap_init (line_table);
  line_table->reallocator = xrealloc;
  line_table->round_alloc_size = round_alloc_size;

  r = cpp_create_reader (CLK_GNUC99, NULL, line_table);

  if (!cpp_read_main_file (r, argv[1]))
    return 1;

  /* Pre-seed operators.  */
  operators.create (1024);
#define DEFTREECODE(SYM, STRING, TYPE, NARGS) \
  add_operator (SYM, # SYM, # TYPE, NARGS);
#define END_OF_BASE_TREE_CODES
#include "tree.def"
#undef END_OF_BASE_TREE_CODES
#undef DEFTREECODE

  /* Pre-seed builtin functions.
     ???  Cannot use N (name) as that is targetm.emultls.get_address
     for BUILT_IN_EMUTLS_GET_ADDRESS ... */
#define DEF_BUILTIN(ENUM, N, C, T, LT, B, F, NA, AT, IM, COND) \
  add_builtin (ENUM, # ENUM);
#include "builtins.def"
#undef DEF_BUILTIN

  vec<simplify *> simplifiers = vNULL;

  do
    {
      token = peek (r);
      if (token->type == CPP_EOF)
	break;

      /* All clauses start with '('.  */
      eat_token (r, CPP_OPEN_PAREN);

      const char *id = get_ident (r);
      if (strcmp (id, "match_and_simplify") == 0)
	simplifiers.safe_push (parse_match_and_simplify (r));
      else
	fatal ("expected 'match_and_simplify'");

      eat_token (r, CPP_CLOSE_PAREN);
    }
  while (1);

  write_gimple (stdout, simplifiers);

  cpp_finish (r, NULL);
  cpp_destroy (r);

  return 0;
}
