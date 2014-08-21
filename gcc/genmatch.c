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
#include "is-a.h"

/* libccp helpers.  */

static struct line_maps *line_table;

static bool
#if GCC_VERSION >= 4001
__attribute__((format (printf, 6, 0)))
#endif
error_cb (cpp_reader *, int, int, source_location location,
	  unsigned int, const char *msg, va_list *ap)
{
  const line_map *map;
  linemap_resolve_location (line_table, location, LRK_SPELLING_LOCATION, &map);
  expanded_location loc = linemap_expand_location (line_table, map, location);
  fprintf (stderr, "%s:%d:%d error: ", loc.file, loc.line, loc.column);
  vfprintf (stderr, msg, *ap);
  fprintf (stderr, "\n");
  exit (1);
}

static void
#if GCC_VERSION >= 4001
__attribute__((format (printf, 2, 3)))
#endif
fatal_at (const cpp_token *tk, const char *msg, ...)
{
  va_list ap;
  va_start (ap, msg);
  error_cb (NULL, CPP_DL_FATAL, 0, tk->src_loc, 0, msg, &ap);
  va_end (ap);
}

static void
output_line_directive (FILE *f, source_location location)
{
  const line_map *map;
  linemap_resolve_location (line_table, location, LRK_SPELLING_LOCATION, &map);
  expanded_location loc = linemap_expand_location (line_table, map, location);
  /* Other gen programs really output line directives here, at least for
     development it's right now more convenient to have line information
     from the generated file.  Still keep the directives as comment for now
     to easily back-point to the meta-description.  */
  fprintf (f, "/* #line %d \"%s\" */\n", loc.line, loc.file);
}


/* Grammar

     capture = '@' number
     op = predicate | expr [capture]
     c_expr = '{' ... '}'
     genexpr = '(' code genop... ')'
     genop = capture | genexpr | c_expr
     transform = 'match_and_transform' name expr genop

     Match and simplify (A + B) - B -> A
     (simplify foo
       (PLUS_EXPR (MINUS_EXPR integral_op_p@0 @1) @1)
       @0)

     Match and simplify (CST + A) + CST to CST' + A
     (simplify bar
       (PLUS_EXPR INTEGER_CST_P@0 (PLUS_EXPR @1 INTEGER_CST_P@2))
       (PLUS_EXPR { int_const_binop (PLUS_EXPR, captures[0], captures[2]); } @1))
*/


#define DEFTREECODE(SYM, STRING, TYPE, NARGS)   SYM,
enum tree_code {
#include "tree.def"
CONVERT0,
CONVERT1,
CONVERT2,
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
  enum id_kind { CODE, FN, USER_DEFINED } kind;

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

static hash_table<id_base> *operators;

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

template<>
template<>
inline bool
is_a_helper <fn_id *>::test (id_base *id)
{
  return id->kind == id_base::FN;
}

template<>
template<>
inline bool
is_a_helper <operator_id *>::test (id_base *id)
{
  return id->kind == id_base::CODE;
}

static void
add_operator (enum tree_code code, const char *id,
	      const char *tcc, unsigned nargs)
{
  if (strcmp (tcc, "tcc_unary") != 0
      && strcmp (tcc, "tcc_binary") != 0
      && strcmp (tcc, "tcc_comparison") != 0
      && strcmp (tcc, "tcc_expression") != 0
      /* For {REAL,IMAG}PART_EXPR and VIEW_CONVERT_EXPR.  */
      && strcmp (tcc, "tcc_reference") != 0
      /* To have INTEGER_CST and friends as "predicate operators".  */
      && strcmp (tcc, "tcc_constant") != 0)
    return;
  operator_id *op = new operator_id (code, id, nargs);
  id_base **slot = operators->find_slot_with_hash (op, op->hashval, INSERT);
  if (*slot)
    fatal ("duplicate id definition");
  *slot = op;
}

static void
add_builtin (enum built_in_function code, const char *id)
{
  fn_id *fn = new fn_id (code, id);
  id_base **slot = operators->find_slot_with_hash (fn, fn->hashval, INSERT);
  if (*slot)
    fatal ("duplicate id definition");
  *slot = fn;
}

static bool
operator==(id_base &id, enum tree_code code)
{
  if (id.kind != id_base::CODE)
    return false;
  return static_cast <operator_id&>(id).code == code;
}



/* The predicate expression tree structure.  */

struct dt_operand;

struct operand {
  enum op_type { OP_PREDICATE, OP_EXPR, OP_CAPTURE, OP_C_EXPR };
  operand (enum op_type type_) : type (type_) {}
  enum op_type type;
  virtual void gen_transform (FILE *f, const char *, bool, int, const char *) = 0;
};

struct predicate : public operand
{
  predicate (const char *ident_) : operand (OP_PREDICATE), ident (ident_) {}
  const char *ident;
  virtual void gen_transform (FILE *, const char *, bool, int, const char *)
    { gcc_unreachable (); }
};

struct e_operation {
  e_operation (const char *id, bool is_commutative_ = false, bool add_new_id = true);
  id_base *op;
  bool is_commutative;
};


struct expr : public operand
{
  expr (e_operation *operation_)
    : operand (OP_EXPR), operation (operation_), ops (vNULL) {}
  void append_op (operand *op) { ops.safe_push (op); }
  e_operation *operation;
  vec<operand *> ops;
  virtual void gen_transform (FILE *f, const char *, bool, int, const char *);
};

struct c_expr : public operand
{
  struct id_tab {
    const char *id;
    const char *oper;

    id_tab (const char *id_, const char *oper_): id (id_), oper (oper_) {}
  };


  c_expr (cpp_reader *r_, vec<cpp_token> code_, unsigned nr_stmts_,
	  vec<id_tab> ids_ = vNULL)
    : operand (OP_C_EXPR), r (r_), code (code_),
      nr_stmts (nr_stmts_), fname (NULL), ids (ids_) {}
  cpp_reader *r;
  vec<cpp_token> code;
  unsigned nr_stmts;
  char *fname;
  vec<id_tab> ids;

  virtual void gen_transform (FILE *f, const char *, bool, int, const char *);
  void output_code (FILE *f, bool);
};

struct capture : public operand
{
  capture (const char *where_, operand *what_)
      : operand (OP_CAPTURE), where (where_), what (what_) {}
  const char *where;
  operand *what;
  virtual void gen_transform (FILE *f, const char *, bool, int, const char *);
};

template<>
template<>
inline bool
is_a_helper <capture *>::test (operand *op)
{
  return op->type == operand::OP_CAPTURE;
}

template<>
template<>
inline bool
is_a_helper <predicate *>::test (operand *op)
{
  return op->type == operand::OP_PREDICATE;
}

template<>
template<>
inline bool
is_a_helper <c_expr *>::test (operand *op)
{
  return op->type == operand::OP_C_EXPR;
}

template<>
template<>
inline bool
is_a_helper <expr *>::test (operand *op)
{
  return op->type == operand::OP_EXPR;
}

id_base *
get_operator (const char *id)
{
  id_base tem (id_base::CODE, id);

  id_base *op = operators->find_with_hash (&tem, tem.hashval);
  if (op)
    return op; 

   /* Try all-uppercase.  */
  char *id2 = xstrdup (id);
  for (unsigned i = 0; i < strlen (id2); ++i)
    id2[i] = TOUPPER (id2[i]);
  new (&tem) id_base (id_base::CODE, id2);
  op = operators->find_with_hash (&tem, tem.hashval);
  if (op)
    {
      free (id2);
      return op;
    }

  /* Try _EXPR appended.  */
  id2 = (char *)xrealloc (id2, strlen (id2) + sizeof ("_EXPR") + 1);
  strcat (id2, "_EXPR");
  new (&tem) id_base (id_base::CODE, id2);
  op = operators->find_with_hash (&tem, tem.hashval);
  if (op)
    {
      free (id2);
      return op;
    }

  return 0;
}

e_operation::e_operation (const char *id, bool is_commutative_, bool add_new_id)
{
  is_commutative = is_commutative_;
  op = get_operator (id);
  if (op)
    return;

  if (add_new_id == false)
    fatal ("%s is not an operator/built-in function", id);

  op = new id_base (id_base::USER_DEFINED, id);
  operators->find_slot_with_hash (op, op->hashval, INSERT);
}

struct simplify {
  simplify (const char *name_,
	    operand *match_, source_location match_location_,
	    struct operand *result_, source_location result_location_, vec<operand *> ifexpr_vec_ = vNULL)
      : name (name_), match (match_), match_location (match_location_),
      result (result_), result_location (result_location_),
      ifexpr_vec (ifexpr_vec_) {}

  const char *name;
  operand *match; 
  source_location match_location;
  struct operand *result;
  source_location result_location;
  vec<operand *> ifexpr_vec;
};

struct dt_node
{
  enum dt_type { DT_NODE, DT_OPERAND, DT_TRUE, DT_MATCH, DT_SIMPLIFY };

  enum dt_type type;
  unsigned level;
  vec<dt_node *> kids;

  dt_node (enum dt_type type_): type (type_), level (0), kids (vNULL) {} 
  
  dt_node *append_node (dt_node *); 
  dt_node *append_op (operand *, dt_node *parent = 0, unsigned pos = 0); 
  dt_node *append_true_op (dt_node *parent = 0, unsigned pos = 0);
  dt_node *append_match_op (dt_operand *, dt_node *parent = 0, unsigned pos = 0);
  dt_node *append_simplify (simplify *, unsigned, dt_operand **); 

  virtual void gen_gimple (FILE *) {}
  virtual void gen_generic (FILE *) {}
};

struct dt_operand: public dt_node
{
  operand *op;
  dt_operand *match_dop;
  dt_operand *parent;
  unsigned pos;
 
  dt_operand (enum dt_type type, operand *op_, dt_operand *match_dop_, dt_operand *parent_ = 0, unsigned pos_ = 0)
	: dt_node (type), op (op_), match_dop (match_dop_), parent (parent_), pos (pos_) {}

  virtual void gen_gimple (FILE *);
  virtual void gen_generic (FILE *);
  unsigned gen_predicate (FILE *, const char *);
  unsigned gen_match_op (FILE *, const char *);

  unsigned gen_gimple_expr (FILE *);
  unsigned gen_generic_expr (FILE *, const char *);

  char *get_name (char *);
  void gen_opname (char *, unsigned);

  void gen_gimple_kids (FILE *);
  void gen_generic_kids (FILE *);
};


struct dt_simplify: public dt_node
{
  static const unsigned level_max = UINT_MAX;
  static const unsigned capture_max = 6;
  simplify *s; 
  unsigned pattern_no;
  dt_operand *indexes[capture_max]; 
  
  dt_simplify (simplify *s_, unsigned pattern_no_, dt_operand **indexes_)
	: dt_node (DT_SIMPLIFY), s (s_), pattern_no (pattern_no_)
  {
    for (unsigned i = 0; i < capture_max; ++i)
      indexes[i] = indexes_[i];
  }

  virtual void gen_gimple (FILE *f);
  virtual void gen_generic (FILE *f);
};

template<>
template<>
inline bool
is_a_helper <dt_operand *>::test (dt_node *n)
{
  return n->type == dt_node::DT_OPERAND;
}

struct decision_tree
{
  dt_node *root;
  
  void insert (struct simplify *, unsigned); 
  void gen_gimple (FILE *f = stderr);
  void gen_generic (FILE *f = stderr);
  void print (FILE *f = stderr);

  decision_tree () { root = new dt_node (dt_node::DT_NODE); }

  static dt_node *insert_operand (dt_node *, operand *, dt_operand **indexes, unsigned pos = 0, dt_node *parent = 0);
  static dt_node *find_node (vec<dt_node *>&, dt_node *);
  static bool cmp_node (dt_node *, dt_node *);
  static void print_node (dt_node *, FILE *f = stderr, unsigned = 0);
};

DEBUG_FUNCTION void
print_operand (operand *o, FILE *f = stderr, bool flattened = false)
{
  if (capture *c = dyn_cast<capture *> (o))
    {
      fprintf (f, "@%s", c->where);
      if (c->what && flattened == false) 
	{
	  putc (':', f);
	  print_operand (c->what, f, flattened);
	  putc (' ', f);
	}
    }

  else if (predicate *p = dyn_cast<predicate *> (o))
    fprintf (f, "%s", p->ident);

  else if (is_a<c_expr *> (o))
    fprintf (f, "c_expr");

  else if (expr *e = dyn_cast<expr *> (o))
    {
      fprintf (f, "(%s", e->operation->op->id);

      if (flattened == false)
	{
	  putc (' ', f);
	  for (unsigned i = 0; i < e->ops.length (); ++i)
	    {
	      print_operand (e->ops[i], f, flattened);
	      putc (' ', f);
	    }
	}
      putc (')', f);
    }

  else
    gcc_unreachable ();
}

DEBUG_FUNCTION void
print_matches (struct simplify *s, FILE *f = stderr)
{
  fprintf (f, "for expression: ");
  print_operand (s->match, f); 
  putc ('\n', f);
}

void
cartesian_product (const vec< vec<operand *> >& ops_vector, vec< vec<operand *> >& result, vec<operand *>& v, unsigned n)
{
  if (n == ops_vector.length ())
    {
      vec<operand *> xv = v.copy (); 
      result.safe_push (xv);
      return;
    }

  for (unsigned i = 0; i < ops_vector[n].length (); ++i)
    {
      v[n] = ops_vector[n][i];
      cartesian_product (ops_vector, result, v, n + 1);
    }
}
 
void
cartesian_product (const vec< vec<operand *> >& ops_vector, vec< vec<operand *> >& result, unsigned n_ops)
{
  vec<operand *> v = vNULL;
  v.safe_grow_cleared (n_ops);
  cartesian_product (ops_vector, result, v, 0);
}

vec<operand *>
commutate (operand *op)
{
  vec<operand *> ret = vNULL;

  if (op->type == operand::OP_CAPTURE)
    {
      capture *c = static_cast<capture *> (op);
      if (!c->what)
	{
	  ret.safe_push (op);
	  return ret;
	}
      vec<operand *> v = commutate (c->what);
      for (unsigned i = 0; i < v.length (); ++i)
	{
	  capture *nc = new capture (c->where, v[i]);
	  ret.safe_push (nc);
	}
      return ret;	
    }

  if (op->type != operand::OP_EXPR)
    {
      ret.safe_push (op);
      return ret;
    }

  expr *e = static_cast<expr *> (op);
  if (e->ops.length () == 0)
    {
      ret.safe_push (e);
      return ret;
    }

  vec< vec<operand *> > ops_vector = vNULL;
  for (unsigned i = 0; i < e->ops.length (); ++i)
    ops_vector.safe_push (commutate (e->ops[i]));

  vec< vec<operand *> > result = vNULL;
  cartesian_product (ops_vector, result, e->ops.length ());

  for (unsigned i = 0; i < result.length (); ++i)
    {
      expr *ne = new expr (e->operation);
      for (unsigned j = 0; j < result[i].length (); ++j)
	ne->append_op (result[i][j]);
      ret.safe_push (ne);
    }

  if (!e->operation->is_commutative)
    return ret;

  for (unsigned i = 0; i < result.length (); ++i)
    {
      expr *ne = new expr (e->operation);
      // result[i].length () is 2 since e->operation is binary
      for (unsigned j = result[i].length (); j; --j)
	ne->append_op (result[i][j-1]);
      ret.safe_push (ne);
    }

  return ret;
}

void
lower_commutative (simplify *s, vec<simplify *>& simplifiers)
{
  vec<operand *> matchers = commutate (s->match);
  for (unsigned i = 0; i < matchers.length (); ++i)
    {
      simplify *ns = new simplify (s->name, matchers[i], s->match_location,
				   s->result, s->result_location, s->ifexpr_vec);
      simplifiers.safe_push (ns);
    }
}

operand *
lower_opt_convert (operand *o, enum tree_code oper)
{
  if (capture *c = dyn_cast<capture *> (o))  
    {
      if (c->what)
	return new capture (c->where, lower_opt_convert (c->what, oper));
      else
	return c;
    }

  if (!is_a<expr *> (o))
    return o;

  expr *e = as_a<expr *> (o);
  if (*e->operation->op == oper)
    {
      expr *ne = new expr (new e_operation ("CONVERT_EXPR"));
      ne->append_op (lower_opt_convert (e->ops[0], oper));
      return ne; 
    }

  expr *ne = new expr (e->operation);
  for (unsigned i = 0; i < e->ops.length (); ++i)
    ne->append_op (lower_opt_convert (e->ops[i], oper));

  return ne;
}

operand *
remove_opt_convert (operand *o, enum tree_code oper)
{
  if (capture *c = dyn_cast<capture *> (o))
    {
      if (c->what)
	return new capture (c->where, remove_opt_convert (c->what, oper));
      else
	return c;
    }

  if (!is_a<expr *> (o))
    return o;

  expr *e = as_a<expr *> (o);
  if (*e->operation->op == oper)
    return remove_opt_convert (e->ops[0], oper);

  expr *ne = new expr (e->operation);
  for (unsigned i = 0; i < e->ops.length (); ++i)
    ne->append_op (remove_opt_convert (e->ops[i], oper));

  return ne;
}

bool
has_opt_convert (operand *o, enum tree_code oper)
{
  if (capture *c = dyn_cast<capture *> (o))
    {
      if (c->what)
	return has_opt_convert (c->what, oper);
      else
	return false;
    }

  if (!is_a<expr *> (o))
    return false;

  expr *e = as_a<expr *> (o);
  
  if (*e->operation->op == oper)
    return true;

  for (unsigned i = 0; i < e->ops.length (); ++i)
    if (has_opt_convert (e->ops[i], oper))
      return true;

  return false;
}

void
lower_opt_convert (vec<operand *>& v, operand *o, enum tree_code oper) 
{
  if (has_opt_convert (o, oper))
    {
      v.safe_push (lower_opt_convert (o, oper));
      v.safe_push (remove_opt_convert (o, oper));
    }
}

vec<operand *>
lower_opt_convert (operand *o)
{
  vec<operand *> v1 = vNULL, v2;
  
  v1.safe_push (o);
  
  enum tree_code opers[] = { CONVERT0, CONVERT1, CONVERT2 };

  for (unsigned i = 0; i < 3; ++i)
    {
      v2 = vNULL;
      for (unsigned j = 0; j < v1.length (); ++j)
	lower_opt_convert (v2, v1[j], opers[i]);

      if (v2 != vNULL)
	{
	  v1 = vNULL;
	  for (unsigned j = 0; j < v2.length (); ++j)
	    v1.safe_push (v2[j]);
	}
    }
  
  return v1;
}

void
lower_opt_convert (simplify *s, vec<simplify *>& simplifiers)
{
  vec<operand *> matchers = lower_opt_convert (s->match);
  for (unsigned i = 0; i < matchers.length (); ++i)
    {
      simplify *ns = new simplify (s->name, matchers[i], s->match_location,
				   s->result, s->result_location, s->ifexpr_vec);
      simplifiers.safe_push (ns);
    }
}

void
check_operator (id_base *op, unsigned n_ops, const cpp_token *token = 0)
{
  if (!op)
    return;

  if (op->kind != id_base::CODE)
    return;

  operator_id *opr = static_cast<operator_id *> (op);
  if (opr->get_required_nargs () == n_ops)
    return;

  if (token)
    fatal_at (token, "%s expects %u operands, got %u operands", opr->id, opr->get_required_nargs (), n_ops);
  else
    fatal ("%s expects %u operands, got %u operands", opr->id, opr->get_required_nargs (), n_ops);
}
        
operand *
replace_id (operand *o, const char *user_id, const char *oper)
{
  if (o->type == operand::OP_CAPTURE)
    {
      capture *c = static_cast<capture *> (o);
      if (!c->what)
	return c;
      capture *nc = new capture (c->where, replace_id (c->what, user_id, oper));
      return nc;
    }

  if (c_expr *ce = dyn_cast<c_expr *> (o))
    {
      id_base *idb = get_operator (oper);
      vec<c_expr::id_tab> ids = ce->ids.copy ();
      ids.safe_push (c_expr::id_tab (user_id, idb->id));
      return new c_expr (ce->r, ce->code, ce->nr_stmts, ids);
    }

  if (o->type != operand::OP_EXPR)
    return o;

  expr *e = static_cast<expr *> (o);
  expr *ne;

  if (e->operation->op->kind == id_base::USER_DEFINED && strcmp (e->operation->op->id, user_id) == 0)
    {
      struct e_operation *operation = new e_operation (oper, e->operation->is_commutative, false);
      check_operator (operation->op, e->ops.length ());
      ne = new expr (operation);
    }
  else
    ne = new expr (e->operation);

  for (unsigned i = 0; i < e->ops.length (); ++i)
    ne->append_op (replace_id (e->ops[i], user_id, oper));

  return ne;
}
  
void
check_no_user_id (operand *o)
{
  if (o->type == operand::OP_CAPTURE)
    {
      capture *c = static_cast<capture *> (o);
      if (c->what && c->what->type == operand::OP_EXPR)
	{
	  o = c->what;
	  goto check_expr; 
	}
      return; 
    }

  if (o->type != operand::OP_EXPR)
    return;

check_expr:
  expr *e = static_cast<expr *> (o);
  if (e->operation->op->kind == id_base::USER_DEFINED)
    fatal ("%s is not defined in for", e->operation->op->id);

  for (unsigned i = 0; i < e->ops.length (); ++i)
    check_no_user_id (e->ops[i]);
}

void
check_no_user_id (simplify *s)
{
  check_no_user_id (s->match);
  check_no_user_id (s->result);
}

/* Code gen off the AST.  */

void
expr::gen_transform (FILE *f, const char *dest, bool gimple, int depth,
		     const char *in_type)
{
  bool is_conversion = false;
  if (*operation->op == CONVERT_EXPR
      || *operation->op == NOP_EXPR
      || *operation->op == FLOAT_EXPR
      || *operation->op == FIX_TRUNC_EXPR)
    is_conversion = true;

  const char *type;
  char optype[20];
  if (is_conversion)
    /* For conversions we need to build the expression using the
       outer type passed in.  */
    type = in_type;
  else
    {
      /* Other operations are of the same type as their first operand.  */
      sprintf (optype, "TREE_TYPE (ops%d[0])", depth);
      type = optype;
    }
  if (!type)
    fatal ("two conversions in a row");

  fprintf (f, "{\n");
  fprintf (f, "  tree ops%d[%u], res;\n", depth, ops.length ());
  for (unsigned i = 0; i < ops.length (); ++i)
    {
      char dest[32];
      snprintf (dest, 32, "  ops%d[%u]", depth, i);
      ops[i]->gen_transform (f, dest, gimple, depth + 1,
			     is_conversion
			     /* If this op is a conversion its single
			        operand has to know its type itself.  */
			     ? NULL
			     /* For other ops the type is the type
			        we got passed in, or if that is from
				a conversion we can at most use the
				first operand type for all further
				operands.  So (convert (plus @1 (convert @2))
				is possible while
				(convert (plus (convert @1) @2))
				is not unless we somehow discover what
				operand we can generate first and do it
				in the appropriate order.  */
			     : (i == 0 ? in_type : type));
    }

  if (gimple)
    {
      /* ???  Have another helper that is like gimple_build but may
	 fail if seq == NULL.  */
      fprintf (f, "  if (!seq)\n"
	       "    {\n"
	       "      res = gimple_simplify (%s, %s",
	       operation->op->id, type);
      for (unsigned i = 0; i < ops.length (); ++i)
	fprintf (f, ", ops%d[%u]", depth, i);
      fprintf (f, ", seq, valueize);\n");
      fprintf (f, "      if (!res) return false;\n");
      fprintf (f, "    }\n");
      fprintf (f, "  else\n");
      fprintf (f, "    res = gimple_build (seq, UNKNOWN_LOCATION, %s, %s",
	       operation->op->id, type);
      for (unsigned i = 0; i < ops.length (); ++i)
	fprintf (f, ", ops%d[%u]", depth, i);
      fprintf (f, ", valueize);\n");
    }
  else
    {
      if (operation->op->kind == id_base::CODE)
	fprintf (f, "  res = fold_build%d (%s, %s",
		 ops.length(), operation->op->id, type);
      else
	fprintf (f, "  res = build_call_expr (builtin_decl_implicit (%s), %d",
		 operation->op->id, ops.length());
      for (unsigned i = 0; i < ops.length (); ++i)
	fprintf (f, ", ops%d[%u]", depth, i);
      fprintf (f, ");\n");
    }
  fprintf (f, "  %s = res;\n", dest);
  fprintf (f, "}\n");
}

void
c_expr::output_code (FILE *f, bool for_fn)
{
  unsigned stmt_nr = 1;
  for (unsigned i = 0; i < code.length (); ++i)
    {
      const cpp_token *token = &code[i];

      /* Replace captures for code-gen.  */
      if (token->type == CPP_ATSIGN)
	{
	  const cpp_token *n = &code[i+1];
	  if (n->type == CPP_NUMBER
	      && !(n->flags & PREV_WHITE))
	    {
	      if (token->flags & PREV_WHITE)
		fputc (' ', f);
	      fprintf (f, "captures[%s]", n->val.str.text);
	      ++i;
	      continue;
	    }
	}

      if (token->flags & PREV_WHITE)
	fputc (' ', f);

      if (token->type == CPP_NAME)
	{
	  const char *id = (const char *) NODE_NAME (token->val.node.node);
	  unsigned j;
	  for (j = 0; j < ids.length (); ++j)
	    {
	    if (strcmp (id, ids[j].id) == 0)
	      {
		fprintf (f, "%s", ids[j].oper);
		break;
	      }
	    }
	  if (j < ids.length ())
	    continue;
	}

      /* Output the token as string.  */
      char *tk = (char *)cpp_token_as_text (r, token);
      fputs (tk, f);

      if (token->type == CPP_SEMICOLON)
	{
	  stmt_nr++;
	  if (for_fn && stmt_nr == nr_stmts)
	    fputs ("\n return ", f);
	  else
	    fputc ('\n', f);
	}
    }
}


void
c_expr::gen_transform (FILE *f, const char *dest, bool, int, const char *)
{
  /* If this expression has an outlined function variant, call it.  */
  if (fname)
    {
      fprintf (f, "%s = %s (type, captures);\n", dest, fname);
      return;
    }

  /* All multi-stmt expressions should have been outlined.  Expressions
     with nr_stmts == 0 are used for if-expressions.  */
  gcc_assert (nr_stmts <= 1);

  if (nr_stmts == 1)
    fprintf (f, "%s = ", dest);

  output_code (f, false);
}

void
capture::gen_transform (FILE *f, const char *dest, bool, int, const char *)
{
  fprintf (f, "%s = captures[%s];\n", dest, where); 
}

bool
cmp_operand (operand *o1, operand *o2)
{
  if (!o1 || !o2 || o1->type != o2->type)
    return false;

  if (o1->type == operand::OP_PREDICATE)
    {
      predicate *p1 = static_cast<predicate *>(o1);
      predicate *p2 = static_cast<predicate *>(o2);
      return strcmp (p1->ident, p2->ident) == 0;
    }
  else if (o1->type == operand::OP_EXPR)
    {
      expr *e1 = static_cast<expr *>(o1);
      expr *e2 = static_cast<expr *>(o2);
      return strcmp (e1->operation->op->id, e2->operation->op->id) == 0;
    }
  else
    return false;
}


bool
decision_tree::cmp_node (dt_node *n1, dt_node *n2)
{
  if (!n1 || !n2 || n1->type != n2->type)
    return false;


  if (n1 == n2 || n1->type == dt_node::DT_TRUE)
    return true;

  if (n1->type == dt_node::DT_OPERAND)
    return cmp_operand ((static_cast<dt_operand *> (n1))->op, (static_cast<dt_operand *> (n2))->op);

  else if (n1->type == dt_node::DT_MATCH)
    return (static_cast<dt_operand *> (n1))->match_dop == (static_cast<dt_operand *> (n2))->match_dop;

  else
    return false;
}

dt_node *
decision_tree::find_node (vec<dt_node *>& ops, dt_node *p)
{
  for (unsigned i = 0; i < ops.length (); ++i)
    if (decision_tree::cmp_node (ops[i], p))
      return ops[i]; 
  
  return 0;
}

dt_node *
dt_node::append_node (dt_node *n)
{
  dt_node *kid;

  kid = decision_tree::find_node (kids, n);
  if (kid)
    return kid;

  kids.safe_push (n);
  n->level = this->level + 1;

  unsigned len = kids.length ();

  if (len > 1 && kids[len - 2]->type == dt_node::DT_TRUE)
    {
      dt_node *p = kids[len - 2];
      kids[len - 2] = kids[len - 1];
      kids[len - 1] = p;
    }

  return n;
}

dt_node *
dt_node::append_op (operand *op, dt_node *parent, unsigned pos)
{
  dt_operand *parent_ = static_cast<dt_operand *> (parent);
  dt_node *n = new dt_operand (DT_OPERAND, op, 0, parent_, pos);
  dt_node *p = append_node (n);

  if (p != n)
    free (n);

  return p; 
}

dt_node *
dt_node::append_true_op (dt_node *parent, unsigned pos)
{
  dt_operand *parent_ = static_cast<dt_operand *> (parent);
  dt_node *n = new dt_operand (DT_TRUE, 0, 0, parent_, pos);
  dt_node *p = append_node (n);

  if (p != n)
    free (n);

  return p;
}

dt_node *
dt_node::append_match_op (dt_operand *match_dop, dt_node *parent, unsigned pos)
{
  dt_operand *parent_ = static_cast<dt_operand *> (parent);
  dt_node *n = new dt_operand (DT_MATCH, 0, match_dop, parent_, pos);
  dt_node *p = append_node (n);

  if (p != n)
    free (n);

  return p;
}

dt_node *
dt_node::append_simplify (simplify *s, unsigned pattern_no, dt_operand **indexes) 
{
  dt_node *n = new dt_simplify (s, pattern_no, indexes);
  return append_node (n);
}

dt_node *
decision_tree::insert_operand (dt_node *p, operand *o, dt_operand **indexes, unsigned pos, dt_node *parent) 
{
  dt_node *q, *elm = 0;

  if (o->type == operand::OP_CAPTURE)
    {
      capture *c = static_cast<capture *> (o);
      unsigned capt_index = atoi (c->where);

      if (indexes[capt_index] == 0)
	{
	  if (c->what)
	    q = insert_operand (p, c->what, indexes, pos, parent);
	  else
	    {
	      q = elm = p->append_true_op (parent, pos);
	      goto at_assert_elm;
	    }
	  // get to the last capture
	  for (operand *what = c->what; what && is_a<capture *> (what); c = as_a<capture *> (what), what = c->what)
	    ;

	  if (c->what == 0)
	    {
	      unsigned cc_index = atoi (c->where);
	      dt_operand *match_op = indexes[cc_index];

	      dt_operand temp (dt_node::DT_TRUE, 0, 0);
	      elm = decision_tree::find_node (p->kids, &temp);

	      if (elm == 0)
		{
		  dt_operand temp (dt_node::DT_MATCH, 0, match_op);
		  elm = decision_tree::find_node (p->kids, &temp);
		}
	    }
	  else 
	    {
	      dt_operand temp (dt_node::DT_OPERAND, c->what, 0);
	      elm = decision_tree::find_node (p->kids, &temp);
	    }
	    
at_assert_elm:
	gcc_assert (elm);
	gcc_assert (elm->type == dt_node::DT_TRUE || elm->type == dt_node::DT_OPERAND || elm->type == dt_node::DT_MATCH);
	indexes[capt_index] = static_cast<dt_operand *> (elm);
	return q;
      }
      else
	{
	  p = p->append_match_op (indexes[capt_index], parent, pos);
	  if (c->what)
	    return insert_operand (p, c->what, indexes, 0, p);
	  else
	    return p;
	}
    }
  p = p->append_op (o, parent, pos);
  q = p;

  if (o->type == operand::OP_EXPR)
    {
      expr *e = static_cast<expr *> (o);
      for (unsigned i = 0; i < e->ops.length (); ++i)
	q = decision_tree::insert_operand (q, e->ops[i], indexes, i, p);		
    }

  return q;
}

void
decision_tree::insert (struct simplify *s, unsigned pattern_no)
{
  dt_operand *indexes[dt_simplify::capture_max];

  if (s->match->type != operand::OP_EXPR)
    return; 

  for (unsigned j = 0; j < dt_simplify::capture_max; ++j)
    indexes[j] = 0; 

  dt_node *p = decision_tree::insert_operand (root, s->match, indexes);
  p->append_simplify (s, pattern_no, indexes);
}

DEBUG_FUNCTION void
decision_tree::print_node (dt_node *p, FILE *f, unsigned indent)
{
  if (p->type == dt_node::DT_NODE)
    fprintf (f, "root");
  else
    {
      fprintf (f, "|");
      for (unsigned i = 0; i < indent; i++)
	fprintf (f, "-");

      if (p->type == dt_node::DT_OPERAND)
	{
	  dt_operand *dop = static_cast<dt_operand *>(p);
	  print_operand (dop->op, f, true); 
	} 
      else if (p->type == dt_node::DT_TRUE)
	fprintf (f, "true");
      else if (p->type == dt_node::DT_MATCH)
	fprintf (f, "match (%p)", (void *) ((static_cast<dt_operand *>(p))->match_dop));
      else if (p->type == dt_node::DT_SIMPLIFY)
	{
	  dt_simplify *s = static_cast<dt_simplify *> (p);
	  fprintf (f, "simplify_%u { ", s->pattern_no); 
	  for (unsigned i = 0; i < dt_simplify::capture_max; ++i)
	    fprintf (f, "%p, ", (void *) s->indexes[i]);
	  fprintf (f, " } "); 
	}
    }      

  fprintf (stderr, " (%p), %u, %u\n", (void *) p, p->level, p->kids.length ());

  for (unsigned i = 0; i < p->kids.length (); ++i)
    decision_tree::print_node (p->kids[i], f, indent + 2);
}


DEBUG_FUNCTION void
decision_tree::print (FILE *f)
{
  return decision_tree::print_node (root, f);
}

char *
dt_operand::get_name (char *name)
{
  if (parent->level == 1)
    sprintf (name, "op%u", pos);
  else if (parent->type == dt_node::DT_MATCH)
    return parent->get_name (name); 
  else
    sprintf (name, "o%u%u", parent->level, pos);
  return name;
}

void
dt_operand::gen_opname (char *name, unsigned pos)
{
  sprintf (name, "o%u%u", level, pos);
}

unsigned
dt_operand::gen_predicate (FILE *f, const char *opname)
{
  predicate *p = static_cast<predicate *> (op);

  fprintf (f, "if (%s (%s))\n", p->ident, opname);
  fprintf (f, "{\n");
  return 1;
}

unsigned
dt_operand::gen_match_op (FILE *f, const char *opname)
{
  char match_opname[20];
  match_dop->get_name (match_opname);
  fprintf (f, "if (%s == %s || operand_equal_p (%s, %s, 0))\n",
	   opname, match_opname, opname, match_opname);
  fprintf (f, "{\n");
  return 1;
}

unsigned
dt_operand::gen_gimple_expr (FILE *f)
{
  expr *e = static_cast<expr *> (op);
  id_base *id = e->operation->op;
  unsigned n_ops = e->ops.length ();

  for (unsigned i = 0; i < n_ops; ++i)
    {
      char child_opname[20];
      gen_opname (child_opname, i); 

      if (id->kind == id_base::CODE)
	{
	  if (*id == REALPART_EXPR || *id == IMAGPART_EXPR
	      || *id == BIT_FIELD_REF || *id == VIEW_CONVERT_EXPR)
	    {
	      /* ???  If this is a memory operation we can't (and should not)
		 match this.  The only sensible operand types are
		 SSA names and invariants.  */
	      fprintf (f, "tree %s = TREE_OPERAND (gimple_assign_rhs1 (def_stmt), %i);\n",
		       child_opname, i);
	      fprintf (f, "if ((TREE_CODE (%s) == SSA_NAME\n"
		       "&& (%s = do_valueize (valueize, %s)))\n"
		       "|| is_gimple_min_invariant (%s))\n"
		       "{\n", child_opname, child_opname, child_opname,
		       child_opname);
	      continue;
	    }
	  else
	    fprintf (f, "tree %s = gimple_assign_rhs%u (def_stmt);\n",
		     child_opname, i + 1);
	}
      else
	fprintf (f, "tree %s = gimple_call_arg (def_stmt, %u);\n",
		 child_opname, i);
      fprintf (f, "if ((%s = do_valueize (valueize, %s)) != 0)\n",
	       child_opname, child_opname);
      fprintf (f, "{\n");
    }

  return n_ops;
}

unsigned
dt_operand::gen_generic_expr (FILE *f, const char *opname)
{
  expr *e = static_cast<expr *> (op);
  unsigned n_ops = e->ops.length ();

  for (unsigned i = 0; i < n_ops; ++i)
    {
      char child_opname[20];
      gen_opname (child_opname, i);

      if (e->operation->op->kind == id_base::CODE)
	fprintf (f, "tree %s = TREE_OPERAND (%s, %u);\n",
		 child_opname, opname, i);
      else
	fprintf (f, "tree %s = CALL_EXPR_ARG (%s, %u);\n",
		 child_opname, opname, i);
    }

  return 0;
}

void
dt_operand::gen_gimple_kids (FILE *f)
{
  vec<dt_operand *> gimple_exprs = vNULL;
  vec<dt_operand *> generic_exprs = vNULL;
  vec<dt_operand *> fns = vNULL;
  vec<dt_node *> others = vNULL;
  dt_node *true_operand = NULL;
  for (unsigned i = 0; i < kids.length (); ++i)
    {
      if (dt_operand *op = dyn_cast <dt_operand *> (kids[i]))
	{
	  if (expr *e = dyn_cast <expr *> (op->op))
	    {
	      if (e->ops.length () == 0)
		generic_exprs.safe_push (op);
	      else if (e->operation->op->kind == id_base::FN)
		fns.safe_push (op);
	      else
		gimple_exprs.safe_push (op);
	    }
	  else if (op->op->type == operand::OP_PREDICATE)
	    others.safe_push (kids[i]);
	  else
	    gcc_unreachable ();
	}
      else if (kids[i]->type == dt_node::DT_MATCH
	       || kids[i]->type == dt_node::DT_SIMPLIFY)
	others.safe_push (kids[i]);
      else if (kids[i]->type == dt_node::DT_TRUE)
	true_operand = kids[i];
      else
	gcc_unreachable ();
    }

  char buf[128];
  char *kid_opname = buf;
 
  unsigned exprs_len = gimple_exprs.length ();
  unsigned gexprs_len = generic_exprs.length ();
  unsigned fns_len = fns.length ();

  if (exprs_len || fns_len || gexprs_len)
    {
      if (exprs_len)
	gimple_exprs[0]->get_name (kid_opname);
      else if (fns_len)
	fns[0]->get_name (kid_opname);
      else
	generic_exprs[0]->get_name (kid_opname);

      fprintf (f, "switch (TREE_CODE (%s))\n"
	       "{\n", kid_opname);
    }

  if (exprs_len || fns_len)
    {
      fprintf (f, "case SSA_NAME:\n");
      fprintf (f, "{\n");
      fprintf (f, "gimple def_stmt = SSA_NAME_DEF_STMT (%s);\n", kid_opname);

      if (exprs_len)
	{
	  fprintf (f, "if (is_gimple_assign (def_stmt))\n");
	  fprintf (f, "switch (gimple_assign_rhs_code (def_stmt))\n"
		   "{\n");
	  for (unsigned i = 0; i < exprs_len; ++i)
	    {
	      expr *e = as_a <expr *> (gimple_exprs[i]->op);
	      id_base *op = e->operation->op;
	      if (*op == CONVERT_EXPR || *op == NOP_EXPR)
		fprintf (f, "CASE_CONVERT:\n");
	      else
		fprintf (f, "case %s:\n", op->id);
	      fprintf (f, "{\n");
	      gimple_exprs[i]->gen_gimple (f);
	      fprintf (f, "break;\n"
		       "}\n");
	    }
	  fprintf (f, "default:;\n"
		   "}\n");
	}
  
      if (fns_len)
	{
	  if (exprs_len)
	    fprintf (f, "else ");

	  fprintf (f, "if (gimple_call_builtin_p (def_stmt, BUILT_IN_NORMAL))\n"
		   "{\n"
		   "tree fndecl = gimple_call_fndecl (def_stmt);\n"
		   "switch (DECL_FUNCTION_CODE (fndecl))\n"
		   "{\n");

	  for (unsigned i = 0; i < fns_len; ++i)
	    {
	      expr *e = as_a <expr *>(fns[i]->op);
	      fprintf (f, "case %s:\n"
		       "{\n", e->operation->op->id);
	      fns[i]->gen_gimple (f);
	      fprintf (f, "break;\n"
		       "}\n");
	    }

	  fprintf (f, "default:;\n"
		   "}\n"
		   "}\n");
	}

      fprintf (f, "break;\n"
	       "}\n");
    }

  for (unsigned i = 0; i < generic_exprs.length (); ++i)
    {
      expr *e = as_a <expr *>(generic_exprs[i]->op);
      fprintf (f, "case %s:\n"
	       "{\n", e->operation->op->id);

      generic_exprs[i]->gen_gimple (f);
      fprintf (f, "break;\n"
	       "}\n");
    }

  /* Close switch (TREE_CODE ()).  */
  if (exprs_len || fns_len || gexprs_len)
    fprintf (f, "default:;\n"
	     "}\n");

  for (unsigned i = 0; i < others.length (); ++i)
    others[i]->gen_gimple (f);

  if (true_operand)
    true_operand->gen_gimple (f);
}

void
dt_operand::gen_gimple (FILE *f)
{
  char opname[20];
  get_name (opname); 

  unsigned n_braces = 0;
 
  if (type == DT_OPERAND)
    switch (op->type)
      {
	case operand::OP_PREDICATE:
	  n_braces = gen_predicate (f, opname);
	  break;

	case operand::OP_EXPR:
	  n_braces = gen_gimple_expr (f);
	  break;

	default:
	  gcc_unreachable ();
      }
  else if (type == DT_TRUE)
    ;
  else if (type == DT_MATCH)
    n_braces = gen_match_op (f, opname);
  else
    gcc_unreachable ();

  gen_gimple_kids (f);

  for (unsigned i = 0; i < n_braces; ++i)
    fprintf (f, "}\n");
}


void
dt_operand::gen_generic (FILE *f)
{
  char opname[20];
  get_name (opname); 

  unsigned n_braces = 0;
 
  if (type == DT_OPERAND)
    switch (op->type)
      {
	case operand::OP_PREDICATE:
	  n_braces = gen_predicate (f, opname);
	  break;

	case operand::OP_EXPR:
	  n_braces = gen_generic_expr (f, opname);
	  break;

	default:
	  gcc_unreachable ();
      }
  else if (type == DT_TRUE)
    ;
  else if (type == DT_MATCH)
    n_braces = gen_match_op (f, opname);
  else
    gcc_unreachable ();

  unsigned i;

  gen_generic_kids (f);

  for (i = 0; i < n_braces; ++i)
    fprintf (f, "}\n");
}

void
dt_operand::gen_generic_kids (FILE *f)
{
  bool any = false;
  for (unsigned j = 0; j < kids.length (); ++j)
    {
      dt_node *node = kids[j];
      if (node->type == DT_OPERAND)
	{
	  dt_operand *kid = static_cast<dt_operand *>(node);
	  if (kid->op->type == operand::OP_EXPR)
	    any = true;
	}
    }

  if (any)
    {
      char opname[20];
      static_cast <dt_operand *>(kids[0])->get_name (opname); 
      fprintf (f, "switch (TREE_CODE (%s))\n"
	       "{\n", opname);
      for (unsigned j = 0; j < kids.length (); ++j)
	{
	  dt_node *node = kids[j];
	  if (node->type != DT_OPERAND)
	    continue;
	  dt_operand *kid = static_cast<dt_operand *>(node);
	  if (kid->op->type != operand::OP_EXPR)
	    continue;
	  expr *e = static_cast <expr *>(kid->op);
	  if (e->operation->op->kind != id_base::CODE)
	    continue;

	  /* ??? CONVERT */
	  fprintf (f, "case %s:\n"
		   "{\n", e->operation->op->id);
	  kid->gen_generic (f);
	  fprintf (f, "break;\n"
		   "}\n");
	}

      bool first = true;
      for (unsigned j = 0; j < kids.length (); ++j)
	{
	  dt_node *node = kids[j];
	  if (node->type != DT_OPERAND)
	    continue;
	  dt_operand *kid = static_cast<dt_operand *>(node);
	  if (kid->op->type != operand::OP_EXPR)
	    continue;
	  expr *e = static_cast <expr *>(kid->op);
	  if (e->operation->op->kind != id_base::FN)
	    continue;

	  if (first)
	    fprintf (f, "case CALL_EXPR:\n"
		     "{\n"
		     "tree fndecl = get_callee_fndecl (%s);\n"
		     "if (fndecl && DECL_BUILT_IN_CLASS (fndecl) == BUILT_IN_NORMAL)\n"
		     "switch (DECL_FUNCTION_CODE (fndecl))\n"
		     "{\n", opname);
	  first = false;

	  fprintf (f, "case %s:\n"
		   "{\n", e->operation->op->id);
	  kid->gen_generic (f);
	  fprintf (f, "break;\n"
		   "}\n");
	}
      if (!first)
	fprintf (f, "default:;\n"
		 "}\n"
		 "break;\n"
		 "}\n");
      /* Close switch of TREE_CODE.  */
      fprintf (f, "default:;\n"
	       "}\n");
    }

  for (unsigned j = 0; j < kids.length (); ++j)
    {
      dt_node *node = kids[j];
      if (node->type == DT_OPERAND)
	{
	  dt_operand *kid = static_cast<dt_operand *>(node);
	  if (kid->op->type == operand::OP_EXPR)
	    continue;
	}

      node->gen_generic (f);
    }
}


void
dt_simplify::gen_gimple (FILE *f)
{

  fprintf (f, "/* simplify %u */\n", pattern_no);

  fprintf (f, "{\n");
  fprintf (f, "tree captures[%u] ATTRIBUTE_UNUSED = {};\n", dt_simplify::capture_max);

  for (unsigned i = 0; i < dt_simplify::capture_max; ++i)
    if (indexes[i])
      {
	char opname[20];
	fprintf (f, "captures[%u] = %s;\n", i, indexes[i]->get_name (opname));
      }

  if (s->ifexpr_vec != vNULL)
    {
      fprintf (f, "if (");
      // we add in LIFO order, so traverse backwards
      for (unsigned i = s->ifexpr_vec.length (); i; --i)
	{
	  fprintf (f, "(");
	  s->ifexpr_vec[i - 1]->gen_transform (f, NULL, true, 1, "type");
	  fprintf (f, ")");
	  if (i > 1)
	    fprintf (f, " && ");
	}
      fprintf (f, ")\n");
      fprintf (f, "{\n");
    }
      output_line_directive (f, s->result_location);

      if (s->result->type == operand::OP_EXPR)
	{
	  expr *e = static_cast <expr *> (s->result);
	  fprintf (f, "*res_code = %s;\n", e->operation->op->id);
	  for (unsigned j = 0; j < e->ops.length (); ++j)
	    {
	      char dest[32];
	      snprintf (dest, 32, "  res_ops[%d]", j);
	      e->ops[j]->gen_transform (f, dest, true, 1, "type");
	    }
	  /* Re-fold the toplevel result.  It's basically an embedded
	     gimple_build w/o actually building the stmt.  */
	  fprintf (f, "gimple_resimplify%d (seq, res_code, type, "
		   "res_ops, valueize);\n", e->ops.length ());
	}
      else if (s->result->type == operand::OP_CAPTURE
	       || s->result->type == operand::OP_C_EXPR)
	{
	  s->result->gen_transform (f, "res_ops[0]", true, 1, "type");
	  fprintf (f, "*res_code = TREE_CODE (res_ops[0]);\n");
	}
      else
	gcc_unreachable ();

      fprintf (f, "return true;\n");
      if (s->ifexpr_vec != vNULL)
	fprintf (f, "}\n");

  fprintf (f, "}\n");
}


void
dt_simplify::gen_generic (FILE *f)
{

  fprintf (f, "/* simplify %u */\n", pattern_no);

  fprintf (f, "{\n");
  fprintf (f, "tree captures[%u] ATTRIBUTE_UNUSED = {};\n", dt_simplify::capture_max);

  for (unsigned i = 0; i < dt_simplify::capture_max; ++i)
    if (indexes[i])
      {
	char opname[20];
	fprintf (f, "captures[%u] = %s;\n", i, indexes[i]->get_name (opname));
      }

  if (s->ifexpr_vec != vNULL)
    {
      fprintf (f, "if (\n");
      // we add in LIFO order, so traverse backwards
      for (unsigned i = s->ifexpr_vec.length (); i; --i)
        {
          fprintf (f, "(");
          s->ifexpr_vec[i - 1]->gen_transform (f, NULL, false, 1, "type");
          fprintf (f, ")");
          if (i > 1)
            fprintf (f, " && ");
        }
      fprintf (f, ")\n");
      fprintf (f, "{\n");
    }

      output_line_directive (f, s->result_location);

      if (s->result->type == operand::OP_EXPR)
	{
	  expr *e = static_cast <expr *> (s->result);
	  for (unsigned j = 0; j < e->ops.length (); ++j)
	    {
	      fprintf (f, "   tree res_op%d;\n", j);
	      char dest[32];
	      snprintf (dest, 32, "  res_op%d", j);
	      e->ops[j]->gen_transform (f, dest, false, 1, "type");
	    }
	  /* Re-fold the toplevel result.  */
	  if (e->operation->op->kind == id_base::CODE)
	    fprintf (f, "  return fold_build%d (%s, type",
		     e->ops.length (), e->operation->op->id);
	  else
	    fprintf (f, "  return build_call_expr (builtin_decl_implicit (%s), %d",
		     e->operation->op->id, e->ops.length());
	  for (unsigned j = 0; j < e->ops.length (); ++j)
	    fprintf (f, ", res_op%d", j);
	  fprintf (f, ");\n");
	}
      else if (s->result->type == operand::OP_CAPTURE
	       || s->result->type == operand::OP_C_EXPR)
	{
	  fprintf (f, "  tree res;\n");
	  s->result->gen_transform (f, " res", false, 1, "type");
	  fprintf (f, "  return res;\n");
	}
      else
	gcc_unreachable ();

      if (s->ifexpr_vec != vNULL)
	fprintf (f, "}\n");

  fprintf (f, "}\n");
}



void
decision_tree::gen_gimple (FILE *f)
{
  for (unsigned n = 1; n <= 3; ++n)
    {
      fprintf (f, "\nstatic bool\n"
	       "gimple_simplify (code_helper *res_code, tree *res_ops,\n"
	       "                 gimple_seq *seq, tree (*valueize)(tree),\n"
	       "                 code_helper code, tree type");
      for (unsigned i = 0; i < n; ++i)
	fprintf (f, ", tree op%d", i);
      fprintf (f, ")\n");
      fprintf (f, "{\n");

      fprintf (f, "switch (code.get_rep())\n"
	       "{\n");
      for (unsigned i = 0; i < root->kids.length (); i++)
	{
	  dt_operand *dop = static_cast<dt_operand *>(root->kids[i]);
	  expr *e = static_cast<expr *>(dop->op);
	  if (e->ops.length () != n)
	    continue;

	  if (*e->operation->op == CONVERT_EXPR
	      || *e->operation->op == NOP_EXPR)
	    fprintf (f, "CASE_CONVERT:\n");
	  else
	    fprintf (f, "case %s%s:\n",
		     is_a <fn_id *> (e->operation->op) ? "-" : "",
		     e->operation->op->id);
	  fprintf (f, "{\n");
	  dop->gen_gimple_kids (f); 
	  fprintf (f, "break;\n");
	  fprintf (f, "}\n");
	}
      fprintf (f, "default:;\n"
	       "}\n");

      fprintf (f, "return false;\n");
      fprintf (f, "}\n");
    }
}


void
decision_tree::gen_generic (FILE *f)
{
  for (unsigned n = 1; n <= 3; ++n)
    {
      fprintf (f, "\ntree\n"
	       "generic_simplify (enum tree_code code, tree type ATTRIBUTE_UNUSED");
      for (unsigned i = 0; i < n; ++i)
	fprintf (f, ", tree op%d", i);
      fprintf (f, ")\n");
      fprintf (f, "{\n");

      /* ???  For now reject all simplifications on operands with
         side-effects as we are not prepared to properly wrap
	 omitted parts with omit_one_operand and friends.  In
	 principle we can do that automagically for a subset of
	 transforms (and only reject the remaining cases).
	 This fixes for example gcc.c-torture/execute/20050131-1.c.  */
      fprintf (f, "if ((op0 && TREE_SIDE_EFFECTS (op0))");
      for (unsigned i = 1; i < n; ++i)
	fprintf (f, "|| (op%d && TREE_SIDE_EFFECTS (op%d))", i, i);
      fprintf (f, ")\n"
	       "  return NULL_TREE;\n");

      fprintf (f, "switch (code)\n"
	       "{\n");
      for (unsigned i = 0; i < root->kids.length (); i++)
	{
	  dt_operand *dop = static_cast<dt_operand *>(root->kids[i]);
	  expr *e = static_cast<expr *>(dop->op);
	  if (e->ops.length () != n
	      /* Builtin simplifications are somewhat premature on
	         GENERIC.  The following drops patterns with outermost
		 calls.  It's easy to emit overloads for function code
		 though if necessary.  */
	      || e->operation->op->kind != id_base::CODE)
	    continue;

	  operator_id *op_id = static_cast <operator_id *> (e->operation->op);
	  if (op_id->code == NOP_EXPR || op_id->code == CONVERT_EXPR)
	    fprintf (f, "CASE_CONVERT:\n");
	  else
	    fprintf (f, "case %s:\n", e->operation->op->id);
	  fprintf (f, "{\n");
	  dop->gen_generic_kids (f);
	  fprintf (f, "break;\n"
		   "}\n");
	}
      fprintf (f, "default:;\n"
	       "}\n");

      fprintf (f, "return NULL_TREE;\n");
      fprintf (f, "}\n");
    }
}


static void
outline_c_exprs (FILE *f, struct operand *op)
{
  if (op->type == operand::OP_C_EXPR)
    {
      c_expr *e = static_cast <c_expr *>(op);
      static unsigned fnnr = 1;
      if (e->nr_stmts > 1
	  && !e->fname)
	{
	  e->fname = (char *)xmalloc (sizeof ("cexprfn") + 4);
	  sprintf (e->fname, "cexprfn%d", fnnr);
	  fprintf (f, "\nstatic tree\ncexprfn%d (tree type, tree *captures)\n",
		   fnnr);
	  fprintf (f, "{\n");
	  e->output_code (f, true);
	  fprintf (f, "}\n");
	  fnnr++;
	}
    }
  else if (op->type == operand::OP_CAPTURE)
    {
      capture *c = static_cast <capture *>(op);
      if (c->what)
	outline_c_exprs (f, c->what);
    }
  else if (op->type == operand::OP_EXPR)
    {
      expr *e = static_cast <expr *>(op);
      for (unsigned i = 0; i < e->ops.length (); ++i)
	outline_c_exprs (f, e->ops[i]);
    }
}

static void
write_header (FILE *f, vec<simplify *>& simplifiers, const char *head)
{
  fprintf (f, "/* Generated automatically by the program `genmatch' from\n");
  fprintf (f, "   a IL pattern matching and simplification description.  */\n");

  /* Include the header instead of writing it awkwardly quoted here.  */
  fprintf (f, "\n#include \"%s\"\n", head);

  /* Outline complex C expressions to helper functions.  */
  for (unsigned i = 0; i < simplifiers.length (); ++i)
    outline_c_exprs (stdout, simplifiers[i]->result);
}


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

static const cpp_token *
peek_ident (cpp_reader *r, const char *id)
{
  const cpp_token *token = peek (r);
  if (token->type != CPP_NAME)
    return 0;

  const char *t = (const char *) CPP_HASHNODE (token->val.node.node)->ident.str;  
  if (strcmp (id, t) == 0)
    return token;

  return 0;
}

/* Read the next token from R and assert it is of type TK.  */

static const cpp_token *
expect (cpp_reader *r, enum cpp_ttype tk)
{
  const cpp_token *token = next (r);
  if (token->type != tk)
    fatal_at (token, "expected %s, got %s",
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

static void
eat_ident (cpp_reader *r, const char *s)
{
  const cpp_token *token = expect (r, CPP_NAME);
  const char *t = (const char *) CPP_HASHNODE (token->val.node.node)->ident.str;

  if (strcmp (s, t)) 
    fatal_at (token, "expected %s got %s\n", s, t);
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
  const char *id = get_ident (r);
  const cpp_token *token = peek (r);
  if (token->type == CPP_QUERY
      && !(token->flags & PREV_WHITE))
    {
      if (strcmp (id, "convert") == 0)
	id = "convert0";
      else if (strcmp  (id, "convert0") == 0)
	;
      else if (strcmp  (id, "convert1") == 0)
	;
      else
	fatal_at (token, "non-convert operator conditionalized");
      eat_token (r, CPP_QUERY);
    }
  else if (strcmp  (id, "convert0") == 0
	   || strcmp  (id, "convert1") == 0)
    fatal_at (token, "expected '?' after conditional operator");
  return new e_operation (id);
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
  bool is_commutative = false;

  if (token->type == CPP_COLON
      && !(token->flags & PREV_WHITE))
    {
      eat_token (r, CPP_COLON);
      token = peek (r);
      if (token->type == CPP_NAME
	  && !(token->flags & PREV_WHITE))
	{
	  const char *s = get_ident (r);
	  if (s[0] == 'c' && !s[1])
	    is_commutative = true;
	  else
	    fatal_at (token, "predicates or flag %s not recognized", s);
	  token = peek (r);
	}
      else
	fatal_at (token, "expected flag or predicate");
    }

  if (token->type == CPP_ATSIGN
      && !(token->flags & PREV_WHITE))
    op = parse_capture (r, e);
  else
    op = e;
  do
    {
      const cpp_token *token = peek (r);
      if (token->type == CPP_CLOSE_PAREN)
	{
	  check_operator (e->operation->op, e->ops.length (), token); 
	  if (is_commutative)
	    {
	      if (e->ops.length () == 2)
		e->operation->is_commutative = true;
	      else
		fatal_at (token, "only binary operators or function with two arguments can be marked commutative");
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
  vec<cpp_token> code = vNULL;
  unsigned nr_stmts = 0;
  eat_token (r, start);
  if (start == CPP_OPEN_PAREN)
    end = CPP_CLOSE_PAREN;
  else if (start == CPP_OPEN_BRACE)
    end = CPP_CLOSE_BRACE;
  else
    gcc_unreachable ();
  opencnt = 1;
  do
    {
      token = next (r);

      /* Count brace pairs to find the end of the expr to match.  */
      if (token->type == start)
	opencnt++;
      else if (token->type == end
	       && --opencnt == 0)
	break;

      if (token->type == CPP_SEMICOLON)
	nr_stmts++;

      /* Record the token.  */
      code.safe_push (*token);
    }
  while (1);
  return new c_expr (r, code, nr_stmts);
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
	  const char *id = get_ident (r);
	  /* We support zero-operand operator names as predicates.  */
	  id_base *opr = get_operator (id);
	  if (opr)
	    {
	      if (operator_id *code = dyn_cast <operator_id *> (opr))
		{
		  if (code->nargs != 0)
		    fatal_at (token, "using an operator with operands as predicate");
		  /* Parse the zero-operand operator "predicates" as
		     expression.  */
		  op = new expr (new e_operation (id));
		}
	      else
		fatal_at (token, "using an unsupported operator as predicate");
	    }
	  else
	    op = new predicate (id);
	  token = peek (r);
	  if (token->flags & PREV_WHITE)
	    return op;
	}
      else if (token->type != CPP_COLON
	       && token->type != CPP_ATSIGN)
	fatal_at (token, "expected expression or predicate");
      /* optionally followed by a capture and a predicate.  */
      if (token->type == CPP_COLON)
	fatal_at (token, "not implemented: predicate on leaf operand");
      if (token->type == CPP_ATSIGN)
	op = parse_capture (r, op);
    }

  return op;
}

/* Return a reversed copy of V.  */

static vec<operand *>
copy_reverse (vec<operand *> v)
{
  vec<operand *> c = vNULL;
  for (int i = v.length ()-1; i >= 0; --i)
    c.safe_push (v[i]);
  return c;
}

/* Parse
     'simplify' [ <ident> ] <expr> <result-op>
   with
     <result-op> = <op> | <cond-result>
     <cond-result> = '(' 'if' '(' <c-expr> ')' <result-op> ')'
   and fill SIMPLIFIERS with the results.  */

static void
parse_simplify (cpp_reader *r, source_location match_location,
		vec<simplify *>& simplifiers)
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
  const cpp_token *loc = peek (r);
  struct operand *match = parse_op (r);
  if (match->type != operand::OP_EXPR)
    fatal_at (loc, "expected uncaptured expression");

  token = peek (r);

  auto_vec<operand *> ifexprs;
  while (1)
    {
      if (token->type == CPP_OPEN_PAREN)
	{
	  eat_token (r, CPP_OPEN_PAREN);
	  if (peek_ident (r, "if"))
	    {
	      eat_ident (r, "if");
	      ifexprs.safe_push (parse_c_expr (r, CPP_OPEN_PAREN));
	    }
	  else
	    {
	      simplifiers.safe_push
		  (new simplify (id, match, match_location, parse_expr (r),
				 token->src_loc, copy_reverse (ifexprs)));
	      eat_token (r, CPP_CLOSE_PAREN);
	      /* A "default" result closes the enclosing scope.  */
	      if (ifexprs.length () > 0)
		{
		  eat_token (r, CPP_CLOSE_PAREN);
		  ifexprs.pop ();
		}
	      else
		return;
	    }
	}
      else if (token->type == CPP_CLOSE_PAREN)
	{
	  /* Close a scope if requested.  */
	  if (ifexprs.length () > 0)
	    {
	      eat_token (r, CPP_CLOSE_PAREN);
	      ifexprs.pop ();
	      token = peek (r);
	    }
	  else
	    return;
	}
      else
	{
	  simplifiers.safe_push
	      (new simplify (id, match, match_location, parse_op (r),
			     token->src_loc, copy_reverse (ifexprs)));
	  /* A "default" result closes the enclosing scope.  */
	  if (ifexprs.length () > 0)
	    {
	      eat_token (r, CPP_CLOSE_PAREN);
	      ifexprs.pop ();
	    }
	  else
	    return;
	}
      token = peek (r);
    }
}

void parse_pattern (cpp_reader *, vec<simplify *>&);

void
parse_for (cpp_reader *r, source_location, vec<simplify *>& simplifiers) 
{
  const char *user_id = get_ident (r);
  eat_ident (r, "in");

  if (get_operator (user_id) != 0)
    fatal_at (peek (r), "%s is an operator, cannot be used as variable in for", user_id);

  vec<const char *> opers = vNULL;

  const cpp_token *token;
  while (1)
    {
      token = peek (r); 
      if (token->type != CPP_NAME)
	break;
      const char *id = get_ident (r);
      id_base *idb = get_operator (id);
      if (*idb == CONVERT0 || *idb == CONVERT1 || *idb == CONVERT2)
	fatal_at (token, "conditional operators cannot be used inside for");
      opers.safe_push (id);
    }

  if (token->type == CPP_CLOSE_PAREN)
    fatal_at (token, "no pattern defined in for");

  while (1)
    {
      const cpp_token *token = peek (r);
      if (token->type == CPP_CLOSE_PAREN)
	break;
      
      vec<simplify *> for_simplifiers = vNULL;
      parse_pattern (r, for_simplifiers);

      for (unsigned i = 0; i < opers.length (); ++i)
	{
	  id_base *idb = get_operator (opers[i]);	      
	  gcc_assert (idb);

	  for (unsigned j = 0; j < for_simplifiers.length (); ++j)
	    {
	      simplify *s = for_simplifiers[j];
	      operand *match_op = replace_id (s->match, user_id, opers[i]);
	      operand *result_op = replace_id (s->result, user_id, opers[i]);
	      vec<operand *> ifexpr_vec = vNULL;
	      for (unsigned j = 0; j < s->ifexpr_vec.length (); ++j)
		ifexpr_vec.safe_push (replace_id (s->ifexpr_vec[j], user_id, opers[i]));
	      simplify *ns = new simplify (s->name, match_op, s->match_location,
					   result_op, s->result_location, ifexpr_vec);

	      simplifiers.safe_push (ns);
	    }
	}
    }
}

void
parse_if (cpp_reader *r, vec<simplify *>& simplifiers)
{
  operand *ifexpr = parse_c_expr (r, CPP_OPEN_PAREN);

  unsigned pos = (simplifiers != vNULL) ? simplifiers.length () - 1 : 0;

  const cpp_token *token = peek (r);
  if (token->type == CPP_CLOSE_PAREN)
    fatal_at (token, "no pattern defined in if");

  while (1)
    {
      const cpp_token *token = peek (r);
      if (token->type == CPP_CLOSE_PAREN)
	break;
    
      parse_pattern (r, simplifiers);
    }

  for (unsigned i = pos; i < simplifiers.length (); ++i)
    simplifiers[i]->ifexpr_vec.safe_push (ifexpr);
}

static size_t
round_alloc_size (size_t s)
{
  return s;
}

void
parse_pattern (cpp_reader *r, vec<simplify *>& simplifiers)
{
  /* All clauses start with '('.  */
  eat_token (r, CPP_OPEN_PAREN);
  const cpp_token *token = peek (r);
  const char *id = get_ident (r);
  if (strcmp (id, "simplify") == 0)
    parse_simplify (r, token->src_loc, simplifiers);
  else if (strcmp (id, "for") == 0)
    parse_for (r, token->src_loc, simplifiers); 
  else if (strcmp (id, "if") == 0)
    parse_if (r, simplifiers);
  else
    fatal_at (token, "expected 'simplify' or 'for' or 'if'");

  eat_token (r, CPP_CLOSE_PAREN);
}

int
main(int argc, char **argv)
{
  cpp_reader *r;

  progname = "genmatch";

  if (argc < 2)
    return 1;

  bool gimple = true;
  bool verbose = false;
  char *input = argv[argc-1];
  for (int i = 1; i < argc - 1; ++i)
    {
      if (strcmp (argv[i], "-gimple") == 0)
	gimple = true;
      else if (strcmp (argv[i], "-generic") == 0)
	gimple = false;
      else if (strcmp (argv[i], "-v") == 0)
	verbose = true;
      else
	{
	  fprintf (stderr, "Usage: genmatch [-gimple] [-generic] [-v] input\n");
	  return 1;
	}
    }

  line_table = XCNEW (struct line_maps);
  linemap_init (line_table, 0);
  line_table->reallocator = xrealloc;
  line_table->round_alloc_size = round_alloc_size;

  r = cpp_create_reader (CLK_GNUC99, NULL, line_table);
  cpp_callbacks *cb = cpp_get_callbacks (r);
  cb->error = error_cb;

  if (!cpp_read_main_file (r, input))
    return 1;
  cpp_define (r, gimple ? "GIMPLE=1": "GENERIC=1");

  /* Pre-seed operators.  */
  operators = new hash_table<id_base> (1024);
#define DEFTREECODE(SYM, STRING, TYPE, NARGS) \
  add_operator (SYM, # SYM, # TYPE, NARGS);
#define END_OF_BASE_TREE_CODES
#include "tree.def"
add_operator (CONVERT0, "CONVERT0", "tcc_unary", 1);
add_operator (CONVERT1, "CONVERT1", "tcc_unary", 1);
add_operator (CONVERT2, "CONVERT2", "tcc_unary", 1);
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

  while (peek (r)->type != CPP_EOF)
    parse_pattern (r, simplifiers);

  for (unsigned i = 0; i < simplifiers.length (); ++i)
    check_no_user_id (simplifiers[i]);

  vec<simplify *> out_simplifiers0 = vNULL;
  for (unsigned i = 0; i < simplifiers.length (); ++i)
    lower_opt_convert (simplifiers[i], out_simplifiers0);

  vec<simplify *> out_simplifiers = vNULL;
  for (unsigned i = 0; i < out_simplifiers0.length (); ++i)
    lower_commutative (out_simplifiers0[i], out_simplifiers);

  if (verbose)
    for (unsigned i = 0; i < out_simplifiers.length (); ++i)
      print_matches (out_simplifiers[i]);

  decision_tree dt;
  for (unsigned i = 0; i < out_simplifiers.length (); ++i)
    dt.insert (out_simplifiers[i], i);

  if (verbose)
    dt.print (stderr);

  if (gimple)
    {
      write_header (stdout, out_simplifiers, "gimple-match-head.c");
      dt.gen_gimple (stdout);
    }
  else
    {
      write_header (stdout, out_simplifiers, "generic-match-head.c");
      dt.gen_generic (stdout);
    }

  cpp_finish (r, NULL);
  cpp_destroy (r);

  delete operators;

  return 0;
}
