/* Lowering pass of OpenACC

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
#include "tm.h"
#include "gimple.h"
#include "gimple-oacc.h"
#include "tree-inline.h"
#include "diagnostic-core.h"
#include "tree-flow.h"
#include "tree-ssa.h"
#include "expr.h"
#include "tree-pass.h"
#include "splay-tree.h"
#include "cfgloop.h"
#include "gimple-pretty-print.h"
#include "tree-data-ref.h"
#include "tree-scalar-evolution.h"
#include "ssaexpand.h"
#include "gimple-opencl.h"
#include "diagnose-gotos.h"
#include "input.h"
#include "gtype-desc.h"
#include "options.h"

#define OACC_PF_DATAIN  1
#define OACC_PF_EXEC    2
#define OACC_PF_DATAOUT 3


/* A transformation matrix, which is a self-contained ROWSIZE x COLSIZE
   matrix.  Rather than use floats, we simply keep a single DENOMINATOR that
   represents the denominator for every element in the matrix.  */
typedef struct lambda_trans_matrix_s
{
    lambda_matrix matrix;
    int rowsize;
    int colsize;
    int denominator;
} *lambda_trans_matrix;

#define LTM_MATRIX(T) ((T)->matrix)
#define LTM_ROWSIZE(T) ((T)->rowsize)
#define LTM_COLSIZE(T) ((T)->colsize)
#define LTM_DENOMINATOR(T) ((T)->denominator)

/* Allocate a new transformation matrix.  */

static lambda_trans_matrix
lambda_trans_matrix_new (int colsize, int rowsize,
                         struct obstack *lambda_obstack)
{
    lambda_trans_matrix ret;

    ret = (lambda_trans_matrix)
          obstack_alloc (lambda_obstack,
                         sizeof (struct lambda_trans_matrix_s));
    LTM_MATRIX (ret) = lambda_matrix_new (rowsize,
                                          colsize,
                                          lambda_obstack);
    LTM_ROWSIZE (ret) = rowsize;
    LTM_COLSIZE (ret) = colsize;
    LTM_DENOMINATOR (ret) = 1;
    return ret;
}
/* Multiply a vector VEC by a matrix MAT.
   MAT is an M*N matrix, and VEC is a vector with length N.  The result
   is stored in DEST which must be a vector of length M.  */

static void
lambda_matrix_vector_mult (lambda_matrix matrix, int m, int n,
                           lambda_vector vec, lambda_vector dest)
{
    int i, j;

    lambda_vector_clear (dest, m);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            dest[i] += matrix[i][j] * vec[j];
}

/* Return true if TRANS is a legal transformation matrix that respects
   the dependence vectors in DISTS and DIRS.  The conservative answer
   is false.

   "Wolfe proves that a unimodular transformation represented by the
   matrix T is legal when applied to a loop nest with a set of
   lexicographically non-negative distance vectors RDG if and only if
   for each vector d in RDG, (T.d >= 0) is lexicographically positive.
   i.e.: if and only if it transforms the lexicographically positive
   distance vectors to lexicographically positive vectors.  Note that
   a unimodular matrix must transform the zero vector (and only it) to
   the zero vector." S.Muchnick.  */

static bool
lambda_transform_legal_p (lambda_trans_matrix trans,
                          int nb_loops,
                          vec<ddr_p> dependence_relations)
{
    unsigned int i, j;
    lambda_vector distres;
    struct data_dependence_relation *ddr;

    gcc_assert (LTM_COLSIZE (trans) == nb_loops
                && LTM_ROWSIZE (trans) == nb_loops);

    /* When there are no dependences, the transformation is correct.  */
    if (dependence_relations.length () == 0)
        return true;

    ddr = dependence_relations[0];
    if (ddr == NULL)
        return true;

    /* When there is an unknown relation in the dependence_relations, we
       know that it is no worth looking at this loop nest: give up.  */
    if (DDR_ARE_DEPENDENT (ddr) == chrec_dont_know)
        return false;

    distres = lambda_vector_new (nb_loops);

    /* For each distance vector in the dependence graph.  */
    FOR_EACH_VEC_ELT (dependence_relations, i, ddr)
    {
        /* Don't care about relations for which we know that there is no
           dependence, nor about read-read (aka. output-dependences):
           these data accesses can happen in any order.  */
        if (DDR_ARE_DEPENDENT (ddr) == chrec_known
                || (DR_IS_READ (DDR_A (ddr)) && DR_IS_READ (DDR_B (ddr))))
            continue;

        /* Conservatively answer: "this transformation is not valid".  */
        if (DDR_ARE_DEPENDENT (ddr) == chrec_dont_know)
            return false;

        /* If the dependence could not be captured by a distance vector,
           conservatively answer that the transform is not valid.  */
        if (DDR_NUM_DIST_VECTS (ddr) == 0)
            return false;

        /* Compute trans.dist_vect */
        for (j = 0; j < DDR_NUM_DIST_VECTS (ddr); j++)
            {
                lambda_matrix_vector_mult (LTM_MATRIX (trans), nb_loops, nb_loops,
                                           DDR_DIST_VECT (ddr, j), distres);

                if (!lambda_vector_lexico_pos (distres, nb_loops))
                    return false;
            }
    }
    return true;
}

static GTY(()) char *ocl_module;


typedef struct acc_region_t* acc_region;

typedef struct acc_region_t
{
    gimple stmt;
    acc_region parent;
    vec <acc_region>* children;
} acc_region_t;

typedef struct acc_schedule_t* acc_schedule;

typedef struct acc_schedule_t
{
  tree items;
  tree tiling;
  tree group_size;
} acc_schedule_t;

typedef struct acc_kernel_t *acc_kernel;

typedef struct acc_kernel_t
{
  tree func;
  struct tree_niter_desc niter_desc;
  basic_block bb_entry;
  basic_block bb_exit;
  splay_tree params_map;
  tree kernel_handle;
} acc_kernel_t;

typedef struct oacc_context
{
    /* This field must be at the beginning, as we do "inheritance": Some
       callback functions for tree-inline.c (e.g., omp_copy_decl)
       receive a copy_body_data pointer that is up-casted to an
       omp_context pointer.  */
    copy_body_data cb;

    /* The tree of contexts corresponding to the encountered constructs.  */
    struct oacc_context *outer;
    gimple stmt;

    splay_tree param_map;
    splay_tree local_map;
    /* Nesting depth of this context.  Used to beautify error messages re
       invalid gotos.  The outermost ctx is depth 1, with depth 0 being
       reserved for the main body of the function.  */
    int depth;

    /* True if this parallel directive is nested within another.  */
    bool is_nested;
} oacc_context;

static splay_tree all_contexts;
static int nesting_level;
static acc_region root_region;
static int save_opt_level = -1;
static GTY((param1_is(unsigned), param2_is(unsigned))) splay_tree kernels;

static void analyze_gimple(gimple_seq* pseq, oacc_context* ctx);
static void lower_oacc(gimple_seq* pseq, oacc_context* ctx);

static acc_region
new_acc_region(gimple stmt, acc_region parent)
{
    acc_region region;

    region = XCNEW(acc_region_t);
    region->stmt = stmt;
    region->parent = parent;
    vec_alloc(region->children, 3);
    if(parent != NULL)
    {
      parent->children->safe_push(region);
    }

    return region;
}

static void
delete_acc_region(acc_region region)
{
  unsigned i;

  for(i = 0; i < region->children->length(); ++i)
    {
      delete_acc_region((*region->children)[i]);
    }
  vec_free(region->children);
  XDELETE(region);
}

static void
dump_acc_region (FILE* file, acc_region region, size_t spc)
{
    size_t i;

    for(i = 0; i < spc; ++i)
      {
        fprintf(file, " ");
      }

    if(region->stmt != NULL)
      {
        print_gimple_stmt(file, region->stmt, 0, TDF_SLIM);
      }
    else
      {
        fprintf(file, "(NULL)\n");
      }
    for(i = 0; i < region->children->length(); ++i)
      {
        dump_acc_region(file, (*region->children)[i], spc+4);
      }

}

static acc_kernel
new_acc_kernel(tree func)
{
  acc_kernel kernel;

  kernel = XCNEW(acc_kernel_t);
  kernel->func = func;
  kernel->niter_desc.niter = NULL_TREE;
  kernel->bb_entry = kernel->bb_exit = NULL;
  kernel->params_map = splay_tree_new(splay_tree_compare_pointers, 0, 0);
  kernel->kernel_handle = NULL_TREE;
  return kernel;
}

static void
delete_acc_kernel(acc_kernel kernel)
{
  splay_tree_delete(kernel->params_map);
  XDELETE(kernel);
}


static oacc_context*
new_oacc_context(gimple stmt, oacc_context* outer)
{
    oacc_context *ctx = XCNEW(oacc_context);
    splay_tree_insert(all_contexts, (splay_tree_key)stmt, (splay_tree_value)ctx);
    ctx->stmt = stmt;

    if(outer)
        {
            ctx->outer = outer;
            ctx->cb = outer->cb;
            ctx->cb.block = NULL;
            ctx->depth = outer->depth+1;
        }
    else
        {
            ctx->cb.src_fn = current_function_decl;
            ctx->cb.dst_fn = current_function_decl;
            ctx->cb.src_node = cgraph_get_node (current_function_decl);
            gcc_checking_assert (ctx->cb.src_node);
            ctx->cb.dst_node = ctx->cb.src_node;
            ctx->cb.src_cfun = cfun;
            ctx->cb.eh_lp_nr = 0;
            ctx->cb.transform_call_graph_edges = CB_CGE_MOVE;
            ctx->depth = 1;
        }
    ctx->cb.decl_map = pointer_map_create();
    return ctx;
}

static void
delete_oacc_context(splay_tree_value value)
{
    oacc_context *ctx = (oacc_context *) value;

    if(ctx->param_map)
        splay_tree_delete(ctx->param_map);
    if(ctx->local_map)
        splay_tree_delete(ctx->local_map);
    XDELETE(ctx);
}

static int
add_local_to_bind(splay_tree_node n, void* data)
{
    gimple stmt = (gimple)data;
    gimple_bind_append_vars(stmt, (tree)n->value);
    return 0;
}

static int
add_assign_to_bind(splay_tree_node n, void* data)
{
    gimple_seq* assigns = (gimple_seq*)data;
    gimple stmt;

    stmt = gimple_build_assign((tree)n->value, (tree)n->key);
    gimple_seq_add_stmt(assigns, stmt);
    return 0;
}

static void add_locals_to_bind(gimple bind, oacc_context* ctx)
{
    gimple_seq bind_body = gimple_bind_body(bind), assigns = NULL;
    splay_tree_foreach(ctx->local_map, add_local_to_bind, (void*)bind);
    /*
       splay_tree_foreach(ctx->local_map, add_assign_to_bind, (void*)&assigns);
       if(assigns != NULL) {
       gimple_seq_add_seq(&assigns, bind_body);
       gimple_bind_set_body(bind, assigns);
       }
     */
}

static void add_locals(gimple_seq* pbody, oacc_context* ctx)
{
    if(gimple_code(gimple_seq_first(*pbody)) == GIMPLE_BIND)
        {
            add_locals_to_bind(gimple_seq_first(*pbody), ctx);
        }
}

static int
create_call_params(splay_tree_node node, void* data)
{
    vec<tree>* pargs = (vec<tree>*)data;
    if((tree)node->value != NULL_TREE)
        {
            pargs->quick_push((tree)node->key);
        }
    return 0;
}

static tree
get_if_clause_expr (gimple_stmt_iterator *gsi)
{
  gimple gs = gsi_stmt (*gsi);
  tree clause;

  if (gimple_code (gs) == GIMPLE_ACC_KERNELS)
    clause = gimple_acc_kernels_clauses (gs);
  else if (gimple_code (gs) == GIMPLE_ACC_PARALLEL)
    clause = gimple_acc_parallel_clauses (gs);
  else
    gcc_unreachable ();

  while (1)
    {
      if (clause == NULL)
        return NULL_TREE;
      if (ACC_CLAUSE_CODE (clause) == ACC_CLAUSE_IF)
        return ACC_CLAUSE_IF_EXPR (clause);
      clause = ACC_CLAUSE_CHAIN (clause);
    }
}

static void
add_host_version(gimple_stmt_iterator *gsi, gimple_seq orig)
{
    if(gimple_code(gimple_seq_first(orig)) == GIMPLE_BIND)
      {
        orig = gimple_bind_body(orig);
      }
    gsi_insert_seq_after(gsi, orig, GSI_CONTINUE_LINKING);
}

static bool
is_pointer(tree arg)
{
  return TREE_CODE(TREE_TYPE(arg)) == POINTER_TYPE;
}

/* When there is assignment like D.1988 = a.1 + D.1987 where a.1 id pointer
 * we have to add one assignment before the statement:
 * D.1988 = a.1;
 */
static void
add_assingments_to_ptrs (gimple_seq *seq, oacc_context* ctx)
{
  gimple_stmt_iterator gsi;

  for (gsi = gsi_start (*seq); !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gimple stmt = gsi_stmt(gsi);
      gimple_seq inner_seq;
      gimple_stmt_iterator inner_gsi;

      gcc_assert (gimple_code(stmt) == GIMPLE_BIND);
      inner_seq = gimple_bind_body (stmt);
      for (inner_gsi = gsi_start (inner_seq); !gsi_end_p (inner_gsi);
           gsi_next (&inner_gsi))
        {
          gimple inner_stmt = gsi_stmt(inner_gsi);
          if (is_gimple_assign (inner_stmt))
            {
              tree rhs = gimple_assign_rhs1 (inner_stmt);
              if (is_pointer(rhs))
                {
                  tree lhs = gimple_assign_lhs (inner_stmt);
                  tree op = gimple_assign_rhs2 (inner_stmt);

                  /* _oacc_ptr_tmp = a */
                  tree convert_var =
                      (tree) splay_tree_lookup(ctx->local_map,
                                               (splay_tree_key) rhs)->value;
                  gcc_assert (convert_var);
                  gimple convert_stmt = gimple_build_assign (convert_var, rhs);
                  gsi_insert_before (&inner_gsi, convert_stmt, GSI_SAME_STMT);

                  /* D.1988 = _oacc_ptr_tmp + offset */
                  gimple assign_stmt = build_assign (
                      (enum tree_code)inner_stmt->gsbase.subcode,
                      convert_var, op, M_NORMAL);
                  gimple_assign_set_lhs (assign_stmt, lhs);
                  gsi_replace (&inner_gsi, assign_stmt, true);
                }
            }
        }
    }
}


static void
lower_oacc_kernels(gimple_stmt_iterator *gsi, oacc_context* ctx)
{
    struct function *child_cfun;
    tree child_fn, if_clause_expr;
    gimple stmt = gsi_stmt (*gsi);
    gimple_seq body, orig;
    unsigned i;

    orig = gimple_acc_body(stmt);
    if(dump_file)
        {
            fprintf(dump_file, "Original KERNELS body:\n\n");
            print_gimple_seq(dump_file, orig, 0, 0);
        }
    body = gimple_seq_copy(orig);
    lower_oacc(&body, ctx);
    add_assingments_to_ptrs(&body, ctx);
    child_fn = GIMPLE_ACC_CHILD_FN(stmt);

    add_locals(&body, ctx);
    gimple_set_body(child_fn, body);

    child_cfun = DECL_STRUCT_FUNCTION (child_fn);
    DECL_STRUCT_FUNCTION (child_fn)->curr_properties = cfun->curr_properties;
    cgraph_add_new_function (child_fn, false);

    vec<tree> args;
    args.create(16);
    splay_tree_foreach(ctx->param_map, create_call_params, (void*)&args);
    size_t size;
    if (args.length() != 0)
        size = sizeof(struct gimple_statement_acc_kernels)
               + (args.length() - 1) * sizeof(tree);
    else
        size = sizeof(struct gimple_statement_acc_kernels);
    gimple new_stmt = ggc_alloc_gimple_statement_d (size);
    memcpy(new_stmt, stmt, sizeof(struct gimple_statement_acc_kernels));

    gimple_set_num_ops(new_stmt, args.length());
    for(i = 0; i < args.length(); ++i)
        {
            tree arg = args[i];
            if(dump_file)
                {
                    fprintf(dump_file, "argument ");
                    print_generic_expr(dump_file, arg, 0);
                    fprintf(dump_file, " type ");
                    print_generic_expr(dump_file, TREE_TYPE(arg), 0);
                    fprintf(dump_file, "\n");
                }
            gimple_set_op(new_stmt, i, arg);
        }

    gsi_replace (gsi, new_stmt, true);
    if_clause_expr = get_if_clause_expr (gsi);
    if (if_clause_expr)
      {
        location_t locus = gimple_location (stmt);
        tree true_label = create_artificial_label (locus);
        tree false_label = create_artificial_label (locus);
        tree exit_label = create_artificial_label (locus);

        /* if (D.1859) goto <D.1900>; else goto <D.1901>; */
        gimple cond = gimple_build_cond_from_tree (if_clause_expr,
                                                   true_label, false_label);
        gsi_insert_before (gsi, cond, GSI_SAME_STMT);
        /* <D.1900>: */
        gsi_insert_before (gsi, gimple_build_label (true_label), GSI_SAME_STMT);
        /* acc_compute_region_end */
        gsi_insert_after (gsi, gimple_alloc(GIMPLE_ACC_COMPUTE_REGION_END, 0),
                          GSI_CONTINUE_LINKING);
        /* goto <D.1902>; */
        gsi_insert_after (gsi, gimple_build_goto (exit_label),
                          GSI_CONTINUE_LINKING);
        /* <D.1901>; */
        gsi_insert_after (gsi, gimple_build_label (false_label),
                          GSI_CONTINUE_LINKING);

        add_host_version (gsi, orig);

        /* <D.1902>; */
        gsi_insert_after (gsi, gimple_build_label (exit_label),
                          GSI_CONTINUE_LINKING);
      }
    else
      gsi_insert_after(gsi, gimple_alloc(GIMPLE_ACC_COMPUTE_REGION_END, 0),
                       GSI_CONTINUE_LINKING);

    gimple_acc_set_body(new_stmt, NULL);
}

static tree
lower_stmt_cb(gimple_stmt_iterator *gsi, bool *handled_ops_p,
              struct walk_stmt_info *wi)
{
    gimple stmt = gsi_stmt (*gsi);
    oacc_context *ctx = (oacc_context *) wi->info;

    *handled_ops_p = true;

    switch (gimple_code (stmt))
        {
        case GIMPLE_ACC_KERNELS:
        case GIMPLE_ACC_PARALLEL:
            ctx = (oacc_context*)splay_tree_lookup(all_contexts,
                                                   (splay_tree_key)stmt)->value;
            lower_oacc_kernels (gsi, ctx);
            break;
        case GIMPLE_ACC_DATA:
            break;
        case GIMPLE_ACC_CACHE:
            break;
        case GIMPLE_ACC_WAIT:
            break;
        case GIMPLE_ACC_HOST_DATA:
            break;
        case GIMPLE_ACC_LOOP:
            break;
        case GIMPLE_ACC_DECLARE:
            break;
        case GIMPLE_ACC_UPDATE:
            break;

        default:
            *handled_ops_p = false;
            break;
        }
    return NULL_TREE;
}

static tree
lower_op_cb(tree *tp, int *walk_subtrees, void *data)
{
    struct walk_stmt_info *wi = (struct walk_stmt_info *) data;
    oacc_context* ctx = (oacc_context*)wi->info;
    tree t = *tp;

    if(ctx != 0 && is_gimple_variable(t))
        {
            tree t1 = NULL_TREE;
            splay_tree_node v = splay_tree_lookup(ctx->param_map,
                                                (splay_tree_key)t);
            if(v)
                {
                    t1 = (tree)v->value;
                    if(t1 == NULL_TREE)
                        {
                            v = splay_tree_lookup(ctx->local_map,
                                                (splay_tree_key)t);
                            t1 = (tree)v->value;
                        }
                    *tp = t1;
                    if(dump_file)
                        {
                            fprintf(dump_file, "Subst ");
                            print_generic_expr(dump_file, t, 0);
                            fprintf(dump_file, " with ");
                            print_generic_expr(dump_file, t1, 0);
                            fprintf(dump_file, "\n");
                        }
                }
        }
    else if(ctx != 0 && TREE_CODE(t) == LABEL_DECL)
        {
            DECL_CONTEXT(t) = ctx->cb.dst_fn;
        }
    return NULL_TREE;
}

static void
lower_oacc(gimple_seq* pseq, oacc_context* ctx)
{
    struct walk_stmt_info wi;

    memset (&wi, 0, sizeof (wi));
    wi.info = ctx;

    walk_gimple_seq_mod (pseq, lower_stmt_cb, lower_op_cb, &wi);
}

static int
gather_oacc_fn_args(splay_tree_node node, void* data)
{
    vec<tree>* pargs = (vec<tree>*)data;
    tree arg = (tree)node->key;
    if(!is_gimple_reg(arg) || is_pointer(arg))
      pargs->quick_push(arg);
    else
      node->value = (splay_tree_value)NULL_TREE;
    return 0;
}

static tree
normalize_name(tree name)
{
    char *normal, *pn;
    const char *ptr;

    normal = XALLOCAVEC(char, IDENTIFIER_LENGTH(name) + 1);
    pn = normal;
    for(ptr = IDENTIFIER_POINTER(name); *ptr != '\0'; ++ptr)
        {
            if(*ptr == '.' || *ptr == '$')
                {
                    *pn++ = '_';
                }
            else
                {
                    *pn++ = *ptr;
                }
        }
    *pn = '\0';
    return get_identifier(normal);
}

static void
generate_local_reg (splay_tree *local_map, tree arg)
{
    const char *id = "_oacc_param";
    if(DECL_NAME(arg))
      id = IDENTIFIER_POINTER(DECL_NAME(arg));
    tree t1 = create_tmp_reg(TREE_TYPE(arg), id);
    splay_tree_insert(*local_map, (splay_tree_key)arg,
                                  (splay_tree_value)t1);
    if(dump_file)
        {
            fprintf(dump_file, "Create local reg for: ");
            print_generic_expr(dump_file, arg, 0);
            fprintf(dump_file, " reg:");
            print_generic_expr(dump_file, t1, 0);
            fprintf(dump_file, "\n");
        }
}

static int
gather_oacc_fn_locals(splay_tree_node node, void* data)
{
    splay_tree* local_map = (splay_tree*)data;
    tree arg = (tree)node->key;
    if(is_gimple_reg(arg) && !is_pointer (arg))
        generate_local_reg (local_map, arg);
    /* We need to add value to the map, since then we use it in assignment. */
    if(is_pointer (arg))
        generate_local_reg (local_map, (tree)node->value);
    return 0;
}

static int
fix_decl_context(splay_tree_node node, void* data)
{
    tree decl = (tree)data;
    tree loc = (tree)node->value;
    DECL_CONTEXT(loc) = decl;
    return 0;
}

static void
create_oacc_child_function(oacc_context* ctx)
{
    tree name, type, decl, t, t1;
    vec<tree> args, types;
    unsigned i;

    name = clone_function_name(current_function_decl, "_oacc_fn");
    name = normalize_name(name);
    if(dump_file)
        {
            fprintf(dump_file, "new fn name='%s'\n", IDENTIFIER_POINTER(name));
        }

    args.create(16);
    splay_tree_foreach(ctx->param_map, gather_oacc_fn_args, (void*)&args);
    types.create(16);
    for(i = 0; i < args.length(); ++i)
        {
            tree type = TREE_TYPE(args[i]);
            if(dump_file)
                {
                    fprintf(dump_file, "Create parameter type: ");
                    print_generic_expr(dump_file, args[i], 0);
                    fprintf(dump_file, " type=");
                    print_generic_expr(dump_file, type, 0);
                    fprintf(dump_file, "\n");
                }
            types.quick_push(type);
        }
    type = build_function_type_array(void_type_node, types.length(),
                                     types.address());
    decl = build_decl(gimple_location(ctx->stmt), FUNCTION_DECL, name, type);
    ctx->cb.dst_fn = decl;

    TREE_STATIC (decl) = 1;
    TREE_USED (decl) = 1;
    DECL_ARTIFICIAL (decl) = 1;
    DECL_NAMELESS (decl) = 1;
    DECL_IGNORED_P (decl) = 0;
    TREE_PUBLIC (decl) = 0;
    DECL_UNINLINABLE (decl) = 1;
    DECL_EXTERNAL (decl) = 0;
    DECL_CONTEXT (decl) = NULL_TREE;
    DECL_INITIAL (decl) = make_node (BLOCK);

    t = build_decl (DECL_SOURCE_LOCATION (decl),
                    RESULT_DECL, NULL_TREE, void_type_node);
    DECL_ARTIFICIAL (t) = 1;
    DECL_IGNORED_P (t) = 1;
    DECL_CONTEXT (t) = decl;
    DECL_RESULT (decl) = t;

    for(i = args.length(); i > 0; --i)
        {
            const char *id = "_oacc_param";
            if(DECL_NAME(args[i-1]))
                {
                    id = IDENTIFIER_POINTER(DECL_NAME(args[i-1]));
                }
            t = build_decl(DECL_SOURCE_LOCATION (decl), PARM_DECL,
                           create_tmp_var_name(id), types[i-1]);
            if(dump_file)
                {
                    fprintf(dump_file, "Create formal param: ");
                    print_generic_expr(dump_file, t, 0);
                    fprintf(dump_file, " type=");
                    print_generic_expr(dump_file, types[i-1], 0);
                    fprintf(dump_file, "\n");
                }

            DECL_ARTIFICIAL (t) = 1;
            DECL_NAMELESS (t) = 1;
            DECL_ARG_TYPE (t) = types[i-1];
            DECL_CONTEXT(t) = decl;
            TREE_USED (t) = 1;
            TREE_ADDRESSABLE (t) = 1;
            if(i > 0)
                DECL_CHAIN (t) = DECL_ARGUMENTS (decl);
            DECL_ARGUMENTS (decl) = t;
            splay_tree_lookup(ctx->param_map, (splay_tree_key)args[i-1])->value
                = (splay_tree_value)t;
        }

    splay_tree_foreach(ctx->param_map, gather_oacc_fn_locals,
                       (void*)&ctx->local_map);
    splay_tree_foreach(ctx->local_map, fix_decl_context, (void*)decl);

    /* Allocate memory for the function structure.  The call to
       allocate_struct_function clobbers CFUN, so we need to restore
       it afterward.  */
    push_struct_function (decl);
    cfun->function_end_locus = gimple_location (ctx->stmt);
    pop_cfun ();
}

static void
scan_oacc_kernels (gimple_stmt_iterator *gsi, oacc_context *outer_ctx)
{
    struct function *child_cfun;
    tree child_fn;
    oacc_context* ctx;
    //acc_region region, outer_region;;
    gimple stmt = gsi_stmt (*gsi);
    location_t loc = gimple_location (stmt);

    /* Ignore task directives with empty bodies.  */
    if (optimize > 0
            && empty_body_p (gimple_acc_body (stmt)))
        {
            gsi_replace (gsi, gimple_build_nop (), false);
            return;
        }

    ctx = new_oacc_context (stmt, outer_ctx);
    if (nesting_level > 1)
        ctx->is_nested = true;
    ctx->param_map = splay_tree_new (splay_tree_compare_pointers, 0, 0);
    ctx->local_map = splay_tree_new (splay_tree_compare_pointers, 0, 0);

    analyze_gimple(gimple_acc_body_ptr(stmt), ctx);
    create_oacc_child_function(ctx);

    child_fn = ctx->cb.dst_fn;
    GIMPLE_ACC_SET_CHILD_FN(stmt, child_fn);
}

static bool
check_oacc_nesting_restrictions (gimple stmt, oacc_context *ctx)
{
    gimple outer_ctx = ctx->stmt;

    switch(gimple_code(stmt))
      {
      case GIMPLE_ACC_KERNELS:
      case GIMPLE_ACC_PARALLEL:
        if(gimple_code(outer_ctx) == GIMPLE_ACC_KERNELS ||
                gimple_code(outer_ctx) == GIMPLE_ACC_PARALLEL)
            {
              error("invalid nesting of OpenACC parallel/kernels regions");
              return false;
            }
        break;
      case GIMPLE_ACC_LOOP:
        if(gimple_code(outer_ctx) != GIMPLE_ACC_KERNELS &&
                gimple_code(outer_ctx) != GIMPLE_ACC_PARALLEL &&
                gimple_code(outer_ctx) != GIMPLE_ACC_LOOP)
            {
              error("OpenACC 'loop' directive is not nested "
                      "inside compute region");
              return false;
            }
        break;
      case GIMPLE_ACC_CACHE:
        if(gimple_code(outer_ctx) != GIMPLE_ACC_LOOP)
            {
              error("OpenACC 'cache'  directive is not nested "
                      "inside 'loop' directive");
              return false;
            }
      default:
          break;
      }
    return true;
}

static tree
analyze_stmt_cb(gimple_stmt_iterator *gsi, bool *handled_ops_p,
                struct walk_stmt_info *wi)
{
    gimple stmt = gsi_stmt (*gsi);
    oacc_context *ctx = (oacc_context *) wi->info;

    if (gimple_has_location (stmt))
        input_location = gimple_location (stmt);

    /* Check the OpenACC nesting restrictions.  */
    if (ctx != NULL)
        {
            bool remove = false;
            if (is_gimple_acc (stmt))
                remove = !check_oacc_nesting_restrictions (stmt, ctx);
            if (remove)
                {
                    stmt = gimple_build_nop ();
                    gsi_replace (gsi, stmt, false);
                }
        }

    *handled_ops_p = true;

    switch (gimple_code (stmt))
        {
        case GIMPLE_ACC_KERNELS:
        case GIMPLE_ACC_PARALLEL:
            nesting_level++;
            scan_oacc_kernels (gsi, ctx);
            nesting_level--;
            break;
        case GIMPLE_ACC_LOOP:
            break;
        case GIMPLE_ACC_DATA:
            break;
        case GIMPLE_ACC_DECLARE:
            break;
        case GIMPLE_ACC_CACHE:
            break;
        case GIMPLE_ACC_WAIT:
            break;
        case GIMPLE_ACC_HOST_DATA:
            break;
        case GIMPLE_ACC_UPDATE:
            break;

        case GIMPLE_BIND:
        {
            tree var;

            *handled_ops_p = false;
            if (ctx)
              for (var = gimple_bind_vars (stmt); var ; var = DECL_CHAIN (var))
                  insert_decl_map (&ctx->cb, var, var);
        }
        break;
        default:
            *handled_ops_p = false;
            break;
        }
    return NULL_TREE;
}

static tree
analyze_op_cb(tree *tp, int *walk_subtrees, void *data)
{
    struct walk_stmt_info *wi = (struct walk_stmt_info *) data;
    oacc_context* ctx = (oacc_context*)wi->info;
    tree t = *tp;

    if(ctx != 0 && is_gimple_variable(t))
        {
            tree* n = (tree *) pointer_map_contains (ctx->cb.decl_map, t);
            if(!n)
                {
                    splay_tree_node v;
                    v = splay_tree_lookup(ctx->param_map, (splay_tree_key)t);
                    if(!v)
                        {
                            splay_tree_insert(ctx->param_map, (splay_tree_key)t,
                                              (splay_tree_value)t);
                        }
                }
        }

    return NULL_TREE;
}

static void
analyze_gimple(gimple_seq* pseq, oacc_context* ctx)
{
    location_t saved_location;
    struct walk_stmt_info wi;

    memset (&wi, 0, sizeof (wi));
    wi.info = ctx;
    wi.want_locations = true;

    saved_location = input_location;
    walk_gimple_seq_mod (pseq, analyze_stmt_cb, analyze_op_cb, &wi);
    input_location = saved_location;
}

/* generate file name for OpenCL source file */
static char*
generate_ocl_module_name(void)
{
    size_t filename_len = strlen(main_input_filename);
    char* cur_module = XNEWVEC(char, filename_len + 4);
    const char* slash_ptr = strrchr(main_input_filename, '/');
    const char* dot_ptr = strrchr(main_input_filename, '.');

    if(dot_ptr && (!slash_ptr || dot_ptr > slash_ptr))
        {
            int cpy_len = filename_len - strlen(dot_ptr) + 1;
            memcpy(cur_module, main_input_filename, cpy_len);
            cur_module[cpy_len] = '\0';
        }
    else
        {
            strcpy(cur_module, main_input_filename);
            strcpy(cur_module, ".");
        }
    strcat(cur_module, "cl");
    return cur_module;
}

/* set generated OpenCL source file with respect to current source file */
static bool
switch_ocl_module(char* cur_module)
{
    if(ocl_module == NULL
            || strcmp((const char*)ocl_module, (const char*)cur_module) != 0)
        {
            if(access(cur_module, 0) == 0)
                {
                    unlink(cur_module);
                }

            if(ocl_module) ggc_free(ocl_module);
            ocl_module = (char*)ggc_strdup(cur_module);

            return true;
        }

    return false;
}

/* Main entry point for lowering OpenACC.  */
static unsigned int
execute_lower_oacc (void)
{
    gimple_seq func_body = 0;

    char* cur_module = generate_ocl_module_name ();
    if(switch_ocl_module (cur_module))
        {
            if(dump_file)
                {
                  fprintf (dump_file,
                           "main module: '%s', opencl module: '%s'\n",
                           main_input_filename, ocl_module);
                }
        }
    XDELETEVEC(cur_module);


    all_contexts = splay_tree_new (splay_tree_compare_pointers, 0,
                                   delete_oacc_context);
    func_body = gimple_body (current_function_decl);
    nesting_level = 0;
    analyze_gimple (&func_body, NULL);
    gcc_assert (nesting_level == 0);

    if(all_contexts->root)
        {
            struct gimplify_ctx gctx;
            push_gimplify_context(&gctx);
            lower_oacc(&func_body, NULL);
            pop_gimplify_context(NULL);
        }

    if(all_contexts)
        {
            splay_tree_delete(all_contexts);
            all_contexts = NULL;
        }


    return 0;
}

/* OpenACC lowering gate */
static bool
gate_lower_oacc (void)
{
    return (flag_openacc != 0);
}

namespace
{
const pass_data pass_data_lower_oacc =
{
    GIMPLE_PASS,
    "oacclow",				/* name */
    OPTGROUP_NONE,                        /* optinfo_flags */
    gate_lower_oacc,			/* gate */
    execute_lower_oacc,			/* execute */
    TV_NONE,				/* tv_id */
    PROP_gimple_any,			/* properties_required */
    0,					/* properties_provided */
    0,					/* properties_destroyed */
    0,					/* todo_flags_start */
    0                      		/* todo_flags_finish */
};

class pass_lower_oacc : public gimple_opt_pass
{
public:
    pass_lower_oacc(gcc::context *ctxt)
        :
        gimple_opt_pass(pass_data_lower_oacc,
                        ctxt)
    {}

    /* opt_pass methods: */
    bool gate ()
    {
        return gate_lower_oacc();
    }
    unsigned int execute ()
    {
        return execute_lower_oacc ();
    }
};

}

gimple_opt_pass *
make_pass_lower_oacc (gcc::context *ctxt)
{
    return new pass_lower_oacc (ctxt);
}

static gimple
build_call(location_t locus, tree funcdecl, int n, ...)
{
    va_list ap;
    int i;
    tree* args = XALLOCAVEC(tree, n);

    va_start(ap, n);
    for(i = 0; i < n; ++i)
        {
            args[i] = va_arg(ap, tree);
        }
    va_end(ap);

    return gimple_build_call_from_tree(
              build_call_expr_loc_array(locus, funcdecl,
                                       n, args));
}

inline static void
gen_replace(gimple_stmt_iterator* gsi, gimple stmt)
{
    gsi_replace(gsi, stmt, true);
}

inline static void
gen_add(gimple_stmt_iterator* gsi, gimple stmt)
{
    gsi_insert_after(gsi, stmt, GSI_NEW_STMT);
}

static void
mark_kernels_parallel(tree kernel_fn, unsigned collapse)
{
    if(!kernels)
    {
      kernels = splay_tree_new_ggc (splay_tree_compare_pointers,
        ggc_alloc_splay_tree_scalar_scalar_splay_tree_s,
        ggc_alloc_splay_tree_scalar_scalar_splay_tree_node_s);
    }
    splay_tree_insert(kernels, (splay_tree_key)DECL_UID(kernel_fn),
                      (splay_tree_value)collapse);
}

static bool
loop_irreducible_p(struct loop* l)
{
    unsigned i;
    basic_block *bbs;
    bool res = false;

    if(loop_preheader_edge (l)->src->flags & BB_IRREDUCIBLE_LOOP)
        {
            return true;
        }

    bbs = get_loop_body_in_dom_order (l);
    for (i = 0; i < l->num_nodes; i++)
        {
            if (bbs[i]->flags & BB_IRREDUCIBLE_LOOP)
                {
                    res = true;
                    break;
                }
        }
    free (bbs);

    return res;
}

static bool
loop_precheck(struct loop* l)
{
    if(!single_dom_exit(l))
        {
            if(dump_file)
                {
                    fprintf(dump_file, " !single_dom_exit\n");
                }
            return false;
        }
    else if(!can_duplicate_loop_p(l) || loop_irreducible_p(l))
        {
            return false;
        }
    return true;
}

static bool
loop_parallelizable(struct loop* l, struct obstack* pobstack)
{
    vec<loop_p> loop_nest;
    vec<ddr_p> dependence_relations;
    vec<data_reference_p> datarefs;
    lambda_trans_matrix trans;
    bool ret = false;

    /* Check for problems with dependences.  If the loop can be reversed,
       the iterations are independent.  */
    datarefs.create (10);
    dependence_relations.create (10 * 10);
    loop_nest.create (3);
    if(dump_file) fprintf(dump_file, "compute data dependences\n");

    if (! compute_data_dependences_for_loop (l, true, &loop_nest, &datarefs,
            &dependence_relations))
      {
        if (dump_file /**/&& (dump_flags & TDF_DETAILS)/**/)
            fprintf (dump_file, "  FAILED: cannot analyze data dependencies\n");
        ret = false;
        goto end;
      }


    if (dump_file /**/&& (dump_flags & TDF_DETAILS)/**/)
      {
        fprintf(dump_file, "loop_nest %d, ddr %d, datarefs %d\n",
                loop_nest.length(), dependence_relations.length(),
                datarefs.length());
        dump_data_dependence_relations (dump_file, dependence_relations);
      }

    trans = lambda_trans_matrix_new (1, 1, pobstack);
    LTM_MATRIX (trans)[0][0] = -1;

    if(dump_file) fprintf(dump_file, "lambda transform legal\n");
    if (lambda_transform_legal_p (trans, 1, dependence_relations))
        {
            ret = true;
            if (dump_file /*&& (dump_flags & TDF_DETAILS)*/)
                fprintf (dump_file, "  SUCCESS: may be parallelized\n");
        }
    else if (dump_file /*&& (dump_flags & TDF_DETAILS)*/)
        fprintf (dump_file,
                 "  FAILED: data dependencies exist across iterations\n");

end:
    loop_nest.release ();
    free_dependence_relations (dependence_relations);
    free_data_refs (datarefs);
    return ret;
}

static bool
loops_parallelizable_p(struct loop* root,	struct tree_niter_desc* pniter_desc)
{
    if(root->inner == NULL)
        {
            return true;
        }
    if(dump_file)
        {
            fprintf(dump_file, "Testing loop dependencies\n");
        }
    struct loop* ploop;
    struct obstack oacc_obstack;
    bool ret = true;

    gcc_obstack_init (&oacc_obstack);
    for(ploop = root->inner; ploop != NULL; ploop = ploop->next)
        {
            if(dump_file)
                {
                    fprintf(dump_file, "loop %d\n", ploop->num);
                }
            if(!loop_precheck(ploop))
                {
                    ret = false;
                    break;
                }

            if(!loop_parallelizable(ploop, &oacc_obstack))
                {
                    ret = false;
                    break;
                }

            if(ret)
                {

                    estimate_numbers_of_iterations_loop(ploop);
                    HOST_WIDE_INT estimated;
                    estimated = estimated_stmt_executions_int (ploop);
                    if (estimated == -1)
                        estimated = max_stmt_executions_int (ploop);
                    if (dump_file)
                        fprintf (dump_file, "Estimated # of iterations %lld\n",
                                      estimated);

                    edge exit = single_dom_exit (ploop);

                    gcc_assert (exit);

                    if (!number_of_iterations_exit (ploop, exit, pniter_desc,
                          false))
                        {
                            if(estimated != -1)
                                {
                                    pniter_desc->niter = 
                                      build_int_cst(uint32_type_node,
                                                        estimated);
                                }
                            else
                                {
                                    if (dump_file)
                                        fprintf (dump_file,
                                                 "  FAILED: number of "
                                                 "iterations not known\n");
                                    ret = false;
                                }
                        }
                    else
                        {
                            if(dump_file)
                                {
                                    fprintf(dump_file, "niter: ");
                                    print_generic_expr(dump_file,
                                                  pniter_desc->niter, 0);
                                    fprintf(dump_file, "\n");
                                    fprintf(dump_file, "max: %lld\n",
                                                pniter_desc->max.to_shwi());
                                }
                        }
                }
        }
    obstack_free (&oacc_obstack, NULL);


    return ret;
}

static bool
get_loop_iteration_count(struct loop *loop, struct tree_niter_desc *pniter_desc)
{
  HOST_WIDE_INT estimated;

  estimate_numbers_of_iterations_loop(loop);
  estimated = estimated_stmt_executions_int (loop);
  if (estimated == -1)
      estimated = max_stmt_executions_int (loop);
  if (dump_file)
      fprintf (dump_file, "Estimated # of iterations %lld\n",
                    estimated);

  edge exit = single_dom_exit (loop);

  gcc_assert (exit);

  if (!number_of_iterations_exit (loop, exit, pniter_desc,
        false))
      {
          if(estimated != -1)
              {
                  pniter_desc->niter = 
                    build_int_cst(uint32_type_node,
                                      estimated);
              }
          else
              {
                  if (dump_file)
                      fprintf (dump_file,
                               "  FAILED: number of "
                               "iterations not known\n");
                  return false;
              }
      }
  else
      {
          if(dump_file)
              {
                  fprintf(dump_file, "niter: ");
                  print_generic_expr(dump_file,
                                pniter_desc->niter, 0);
                  fprintf(dump_file, "\n");
                  fprintf(dump_file, "max: %lld\n",
                              pniter_desc->max.to_shwi());
              }
      }
  return true;
}

static bool
loop_parallelizable_p(struct loop *loop, struct tree_niter_desc *pniter_desc)
{
  struct obstack oacc_obstack;

  gcc_obstack_init (&oacc_obstack);
  if(!loop_precheck(loop))
    {
      return false;
    }

  if(!loop_parallelizable(loop, &oacc_obstack))
    {
      return false;
    }
  obstack_free (&oacc_obstack, NULL);
  if(!get_loop_iteration_count(loop, pniter_desc))
  {
    return false;
  }
  return true;
}

static tree
clone_function(tree fn, gimple kernel_stmt)
{
  tree name, new_fn = NULL, t;
  struct function *child_cfun;

  name = clone_function_name(fn, "_oacc_fn");
  name = normalize_name(name);
  if(dump_file)
      {
          fprintf(dump_file, "new fn name='%s'\n", IDENTIFIER_POINTER(name));
      }
  new_fn = build_decl(gimple_location(kernel_stmt), FUNCTION_DECL, name,
                    TREE_TYPE(fn));
  TREE_STATIC (new_fn) = 1;
  TREE_USED (new_fn) = 1;
  DECL_ARTIFICIAL (new_fn) = 1;
  DECL_NAMELESS (new_fn) = 1;
  DECL_IGNORED_P (new_fn) = 0;
  TREE_PUBLIC (new_fn) = 0;
  DECL_UNINLINABLE (new_fn) = 1;
  DECL_EXTERNAL (new_fn) = 0;
  DECL_CONTEXT (new_fn) = NULL_TREE;
  DECL_INITIAL (new_fn) = make_node (BLOCK);

  t = build_decl (DECL_SOURCE_LOCATION (new_fn),
                  RESULT_DECL, NULL_TREE, void_type_node);
  DECL_ARTIFICIAL (t) = 1;
  DECL_IGNORED_P (t) = 1;
  DECL_CONTEXT (t) = new_fn;
  DECL_RESULT (new_fn) = t;

  return new_fn;
}

static void
map_parameters(tree orig_fn, acc_kernel kernel, gimple kernel_stmt)
{
  unsigned i;
  tree t, param;
  vec<tree> params;

  params.create(3);
  for(param = DECL_ARGUMENTS(orig_fn); param;
    param = DECL_CHAIN(param))
  {
    params.safe_push(param);
  }

  for(i = params.length(); i > 0; --i)
    {
      param = params[i-1];
      const char *id = "_oacc_param";

      if(DECL_NAME(param))
        {
          id = IDENTIFIER_POINTER(DECL_NAME(param));
        }
      t = build_decl(DECL_SOURCE_LOCATION(kernel->func), PARM_DECL,
                      create_tmp_var_name(id), TREE_TYPE(param));
      if(dump_file)
          {
              fprintf(dump_file, "Create formal param: ");
              print_generic_expr(dump_file, t, 0);
              fprintf(dump_file, " type=");
              print_generic_expr(dump_file, TREE_TYPE(param), 0);
              fprintf(dump_file, "\n");
          }
      DECL_ARTIFICIAL (t) = 1;
      DECL_NAMELESS (t) = 1;
      DECL_ARG_TYPE (t) = TREE_TYPE(param);
      DECL_CONTEXT(t) = kernel->func;
      TREE_USED (t) = 1;
      TREE_ADDRESSABLE (t) = 1;
      if(i > 0)
          DECL_CHAIN (t) = DECL_ARGUMENTS (kernel->func);
      DECL_ARGUMENTS (kernel->func) = t;
      splay_tree_insert(kernel->params_map, (splay_tree_key)param,
                                (splay_tree_value)t);
      if(dump_file)
          {
              fprintf(dump_file, "Map ");
              print_generic_expr(dump_file, param, 0);
              fprintf(dump_file, " to ");
              print_generic_expr(dump_file, t, 0);
              fprintf(dump_file, "\n");
          }
    }
  push_struct_function (kernel->func);
  cfun->function_end_locus = gimple_location(kernel_stmt);
  pop_cfun ();
}

static tree
map_params_cb(tree *tp, int *walk_subtrees, void *data)
{
  struct walk_stmt_info *wi = (struct walk_stmt_info *) data;
  splay_tree param_map = (splay_tree)wi->info;
  tree t = *tp;

  if(is_gimple_variable(t))
  {
    splay_tree_node v;
    v = splay_tree_lookup(param_map, (splay_tree_key)t);
    if(v)
    {
      *tp = (tree)(v->value);
      if(dump_file)
      {
        fprintf(dump_file, "Map param ");
        print_generic_expr(dump_file, t, 0);
        fprintf(dump_file, " to param ");
        print_generic_expr(dump_file, *tp, 0);
        fprintf(dump_file, "\n");
      }
    }
  }
  return NULL_TREE;
}

static void
dump_dominators(FILE* fp, basic_block node, int indent)
{
  int i;
  basic_block son;

  for(i = 0; i < indent; ++i)
    fprintf(fp, " ");
  fprintf(fp, "%d\n", node->index);
  for(son = first_dom_son (CDI_DOMINATORS, node);
      son;
      son = next_dom_son(CDI_DOMINATORS, son))
    dump_dominators(fp, son, indent+2);
}

static void
dump_ssa(FILE *fp)
{
  int i;

  fprintf(fp, "#SSA names: %d\n", num_ssa_names);
  for(i = 0; i < num_ssa_names; ++i)
  {
    tree var = ssa_name(i);
    fprintf(fp, "%d ", i);
    if(var == NULL_TREE)
    {
      fprintf(fp, "(NULL)");
    }
    else
    {
      print_generic_expr(fp, var, 0);
      if(SSA_NAME_IN_FREE_LIST (var))
      {
        fprintf(fp, " IN_FREE_LIST");
      }
    }
    fprintf(fp, "\n");
  }
}

static void
dump_fn_body(FILE* dump_file, const char* title)
{
    tree var;
    unsigned i;
    basic_block bb;

    fprintf(dump_file, "==============================\n%s"
            "\n========================\n", title);

    fprintf(dump_file, "#SSA names: %d\n", num_ssa_names);
    print_generic_decl(dump_file, current_function_decl, 0);
    fprintf(dump_file, "\n{\n");

    FOR_EACH_LOCAL_DECL(DECL_STRUCT_FUNCTION(current_function_decl), i, var)
    {
        print_generic_decl(dump_file, var, 0);
        fprintf(dump_file, "\n");
    }
    for(i = 1; i < num_ssa_names; ++i)
        {
            var = ssa_name(i);
            if(var && !SSA_NAME_VAR(var))
                {
                    fprintf(dump_file, "\t");
                    print_generic_expr(dump_file, var, 0);
                    fprintf(dump_file, "\n");
                }
        }

    FOR_EACH_BB(bb)
    {
        fprintf(dump_file, "L%d: %s\n", bb->index,
            (single_succ_p(bb)) ? "single_succ" : "");
        gimple_stmt_iterator gsi;
        for(gsi = gsi_start_phis(bb); !gsi_end_p(gsi); gsi_next(&gsi))
            {
                gimple stmt = gsi_stmt(gsi);
                fprintf(dump_file, "\t#");
                print_gimple_stmt(dump_file, stmt, 0, 0);
            }
        for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
            {
                gimple stmt = gsi_stmt(gsi);
                fprintf(dump_file, "\t");
                print_gimple_stmt(dump_file, stmt, 0, 0);
            }
        edge e;
        gimple stmt;
        edge true_edge, false_edge;
        stmt = last_stmt (bb);

        if (stmt && gimple_code (stmt) == GIMPLE_COND)
            {

                extract_true_false_edges_from_block (bb, &true_edge,
                                            &false_edge);

                fprintf(dump_file, "\tgoto L%d", true_edge->dest->index);
                fprintf(dump_file, "\n");
                fprintf(dump_file, "else\n");
                fprintf(dump_file, "\tgoto L%d", false_edge->dest->index);
                fprintf(dump_file, "\n");
                continue;
            }
        e = find_fallthru_edge (bb->succs);
        if (e && e->dest != bb->next_bb)
            {
                fprintf(dump_file, "\tgoto L%d", e->dest->index);
                fprintf(dump_file, "\n");
            }
    }

    fprintf(dump_file, "}\n");
    fflush(dump_file);
}

static location_t
guess_loop_location(struct loop* l)
{
  location_t locus = UNKNOWN_LOCATION;
  basic_block header = l->header;
  gimple_stmt_iterator gsi = gsi_start_bb(header);
  if(!gsi_end_p(gsi))
  {
    gimple stmt = gsi_stmt(gsi);
    locus = gimple_location(stmt);
  }
  return locus;
}

static void
extract_kernels(struct loops* loops, tree child_fn,
                vec<acc_kernel>* kernels, gimple kernel_stmt)
{
  struct loop *ploop;
  acc_kernel kernel;
  unsigned nloops, i;
  struct loop **vloops;
  basic_block *body, bb_entry;
  struct function* child_cfun;

  if(gimple_code(kernel_stmt) == GIMPLE_ACC_PARALLEL 
    || loops->tree_root->inner == NULL 
    || loops->tree_root->inner->next == NULL)
    {
      kernel = new_acc_kernel(child_fn);

      if(loops->tree_root->inner != NULL)
        {
          bool par = loop_parallelizable_p(loops->tree_root->inner,
            &(kernel->niter_desc));
          if(!par)
          {
            warning_at(guess_loop_location(loops->tree_root->inner), 
              OPT_fopenacc, "loop cannot be parallelized");
          }
        }

      kernels->safe_push(kernel);
      mark_kernels_parallel (child_fn, (kernel->niter_desc.niter != NULL_TREE)
                                        ? 1 : 0);
      return;
    }

  if(dump_file)
  {
    basic_block *body;

    body = get_loop_body(loops->tree_root);
    fprintf(dump_file, "FAKE 0 LOOP: ");
    for(i = 0; i < loops->tree_root->num_nodes; ++i)
    {
      fprintf(dump_file, "%d%c", body[i]->index,
        (i < loops->tree_root->num_nodes-1) ? ' ' : '\n');
    }
    XDELETEVEC(body);
    for(ploop = loops->tree_root->inner; ploop != NULL; ploop = ploop->next)
    {
      fprintf(dump_file, "LOOP %d: ", ploop->num);
      body = get_loop_body(ploop);
      for(i = 0; i < ploop->num_nodes; ++i)
        fprintf(dump_file, "%d%c", body[i]->index,
        (i < ploop->num_nodes-1) ? ' ' : '\n');
      XDELETEVEC(body);
    }

    fflush(dump_file);
  }

  /* Loops connected to siblings in reverse order of 
    appearance so we reorder them
  */
  for(nloops = 0, ploop = loops->tree_root->inner;
      ploop != NULL;
      ++nloops, ploop = ploop->next)
      ;
  
  vloops = XALLOCAVEC(struct loop*, nloops);

  for(i = nloops, ploop = loops->tree_root->inner;
      i > 0;
      --i, ploop = ploop->next)
      vloops[i-1] = ploop;

  for(i = 0; i < nloops; ++i)
  {
    tree fn = child_fn;
    bool par;

    if(i > 0)
    {
      fn = clone_function(child_fn, kernel_stmt);
    }
    kernel = new_acc_kernel(fn);
    if(i > 0)
    {
      map_parameters(child_fn, kernel, kernel_stmt);
    }
    par = loop_parallelizable_p(vloops[i], &(kernel->niter_desc));
    if(!par)
    {
      warning_at(guess_loop_location(vloops[i]),
        OPT_fopenacc, "loop cannot be parallelized");
    }
    kernels->safe_push(kernel);
  }

  if(dump_file)
  {
    child_cfun = DECL_STRUCT_FUNCTION(child_fn);
    push_cfun(child_cfun);
    dump_fn_body(dump_file, "ORIGINAL");
    fflush(dump_file);
    pop_cfun();
  }

  for(i = 0; i < nloops - 1; ++i)
  {
    edge exit_loop = single_exit(vloops[i]);
    basic_block new_bb, before, after, imm_dom;
    gimple_stmt_iterator gsi;

    before = exit_loop->src;
    if(dump_file)
    {
      fprintf(dump_file, "before %d has %d successors\n",
        before->index, EDGE_COUNT(before->succs));
    }
    if(!single_succ_p(before))
    {
      edge p;
      edge_iterator ei;

      after = exit_loop->dest;
      if(dump_file)
      {
        fprintf(dump_file, "after %d has %d predecessors\n",
          after->index, EDGE_COUNT(after->preds));
      }
      imm_dom = get_immediate_dominator(CDI_DOMINATORS, after);

      new_bb = create_empty_bb(before);
      add_bb_to_loop(new_bb, loops->tree_root);
      redirect_edge_and_branch(exit_loop, new_bb);
      make_single_succ_edge(new_bb, after, EDGE_FALLTHRU);

      FOR_EACH_EDGE(p, ei, after->preds)
      {
        if(dump_file)
        {
          fprintf(dump_file, "edge %d -> %d\n", p->src->index, p->dest->index);
        }
        if(p->src->index != new_bb->index)
          redirect_edge_and_branch(p, new_bb);
      }

      set_immediate_dominator (CDI_DOMINATORS, new_bb, imm_dom);
      set_immediate_dominator (CDI_DOMINATORS, after, new_bb);
      if(i > 0)
      {
          gsi = gsi_last_bb(new_bb);
          gsi_insert_before(&gsi, gimple_build_return(NULL_TREE), GSI_SAME_STMT);
      }
    }
  }

  if(dump_file)
  {
    child_cfun = DECL_STRUCT_FUNCTION(child_fn);
    push_cfun(child_cfun);
    dump_fn_body(dump_file, "PADDING");
    fflush(dump_file);
    pop_cfun();
  }

  bb_entry = single_succ_edge(ENTRY_BLOCK_PTR)->dest;
  for(i = 0; i < nloops; ++i)
  {
    basic_block bb_exit;
    if(i == nloops - 1)
    {
      bb_exit = single_pred_edge(EXIT_BLOCK_PTR)->src;
    }
    else
    {
      bb_exit = single_exit(vloops[i])->dest;
    }
    if(dump_file)
    {
      fprintf(dump_file, "LOOP #%d, ENTRY %d, EXIT %d\n",
        vloops[i]->num, bb_entry->index, bb_exit->index);
    }
    
    (*kernels)[i]->bb_entry = bb_entry;
    (*kernels)[i]->bb_exit = bb_exit;


    if(i < nloops - 1)
    {
      bb_entry = single_succ(bb_exit);
    }

  }

  if(dump_file)
  {
    for(i = 0; i < nloops; ++i)
    {
      unsigned j;
      vec<basic_block> bbs;
      
      bbs.create(0);
      bbs.safe_push((*kernels)[i]->bb_entry);
      gather_blocks_in_sese_region((*kernels)[i]->bb_entry, (*kernels)[i]->bb_exit, &bbs);
      fprintf(dump_file, "LOOP #%d ", i);
      for(j = 0; j < bbs.length(); ++j)
        fprintf(dump_file, "%d ", bbs[j]->index);
      fprintf(dump_file, "\n");
    }
    dump_dominators(dump_file, ENTRY_BLOCK_PTR, 0);
  }

  for(i = 0; i < nloops; ++i)
  {
    tree fn = (*kernels)[i]->func;
    basic_block bb;

    if(i > 0)
    {
      int opt_level, k;
      tree block, t;
      gimple_stmt_iterator gsi;
      vec<basic_block> bbs;
      
      bbs.create(0);
      bbs.safe_push((*kernels)[i]->bb_entry);
      gather_blocks_in_sese_region((*kernels)[i]->bb_entry, (*kernels)[i]->bb_exit, &bbs);

      block = DECL_INITIAL(fn);
      child_cfun = DECL_STRUCT_FUNCTION (fn);
      init_tree_ssa (child_cfun);
	    init_ssa_operands (child_cfun);
	    child_cfun->gimple_df->in_ssa_p = true;
      bb = move_sese_region_to_fn (child_cfun, (*kernels)[i]->bb_entry,
        (*kernels)[i]->bb_exit, NULL_TREE);
      if(i == nloops - 1)
      {
        gsi = gsi_last_bb(bb);
        gsi_insert_before(&gsi, gimple_build_return(NULL_TREE), GSI_SAME_STMT);
      }

      for(k = 1; k < num_ssa_names; ++k)
      {
        tree var = ssa_name(k);
        if(var)
        {
          unsigned j;
          basic_block def_block = gimple_bb(SSA_NAME_DEF_STMT(var));

          for(j = 0; j < bbs.length(); ++j)
          {
            if(bbs[j] == def_block)
            {
              if(dump_file)
              {
                fprintf(dump_file, "Release ssa name %d ", k);
                print_generic_expr(dump_file, var, 0);
                fprintf(dump_file, " defined in block %d", def_block->index);
                fprintf(dump_file, "\n");
              }
              release_ssa_name(var);
              break;
            }
          }
        }
      }

      if(dump_file)
      {
        dump_fn_body(dump_file, "AFTER MOVE SESE");
        dump_ssa(dump_file);
        dump_dominators(dump_file, ENTRY_BLOCK_PTR, 0);
        fflush(dump_file);
      }

      child_cfun->curr_properties = cfun->curr_properties;
      cgraph_add_new_function (fn, true);
      push_cfun(child_cfun);

      if(dump_file)
      {
        dump_fn_body(dump_file, "NEW FUNCTION");
        fflush(dump_file);
      }

      FOR_EACH_BB(bb)
      {
        for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
            {
              struct walk_stmt_info wi;
              gimple stmt = gsi_stmt(gsi);

              memset(&wi, 0, sizeof(struct walk_stmt_info));
              wi.info = (void*)(*kernels)[i]->params_map;
              walk_gimple_op(stmt, map_params_cb, &wi);
            }
      }

      if(save_opt_level >= 0)
      {
        opt_level = optimize;
        optimize = save_opt_level;
      }
      calculate_dominance_info (CDI_DOMINATORS);
      FOR_EACH_BB(bb)
      {
        for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
            {
                gimple stmt = gsi_stmt(gsi);
                gimple_set_modified (stmt, true);
                update_stmt_operands(stmt);
            }
      }
      update_ssa(TODO_update_ssa);
      loop_optimizer_init (LOOPS_NORMAL | LOOPS_HAVE_RECORDED_EXITS);
      rewrite_into_loop_closed_ssa (NULL, TODO_update_ssa);
      pop_cfun();
      if(save_opt_level >= 0)
        optimize = opt_level;
    }
    mark_kernels_parallel (fn, 
      ((*kernels)[i]->niter_desc.niter != NULL_TREE) ? 1 : 0);
  }

}

static tree
get_gimple_def_var(gimple stmt)
{
    tree var = NULL_TREE;
    gcc_assert(gimple_code(stmt) == GIMPLE_ASSIGN
               || gimple_code(stmt) == GIMPLE_CALL 
               || gimple_code(stmt) == GIMPLE_PHI);

    if(gimple_code(stmt) == GIMPLE_PHI)
        {
            var = gimple_phi_result(stmt);
        }
    else if(is_gimple_assign(stmt))
        {
            var = gimple_assign_lhs(stmt);
        }
    else
        {
            var = gimple_call_lhs(stmt);
        }
    return var;
}

static void
set_gimple_def_var(gimple stmt, tree var)
{
    gcc_assert(gimple_code(stmt) == GIMPLE_ASSIGN
               || gimple_code(stmt) == GIMPLE_CALL);

    if(is_gimple_assign(stmt))
        {
            gimple_assign_set_lhs(stmt, var);
        }
    else
        {
            gimple_call_set_lhs(stmt, var);
        }
}

static tree check_for_ctrl_var(tree);

static bool
check_for_ctrl_var_cb(tree var, gimple stmt, void* data)
{
    tree* pvar = (tree*)data;
    unsigned i;

    for(i = 0; i < gimple_num_ops(stmt); ++i)
        {
            tree op_var = gimple_op(stmt, i);
            if(op_var == var)
                {
                    continue;
                }
            op_var = check_for_ctrl_var(op_var);
            if(op_var != NULL_TREE)
                {
                    *pvar = op_var;
                    return true;
                }
        }
    return false;
}

static tree
check_for_ctrl_var(tree var)
{
    if(dump_file)
        {
            fprintf(dump_file, "check var ");
            print_generic_expr(dump_file, var, 0);
            fprintf(dump_file, "\n");
        }
    if(is_gimple_constant(var))
        {
            return NULL_TREE;
        }

    if(is_gimple_variable(var))
        {
            if(SSA_NAME_VAR(var))
                {
                    return var;
                }
            else
                {
                    tree new_var = NULL_TREE;
                    walk_use_def_chains(var, check_for_ctrl_var_cb,
                                        (void*)&new_var, false);

                    if(new_var != NULL_TREE)
                        {
                            return new_var;
                        }
                }
        }

    return NULL_TREE;
}


// TODO
// check for those have cycle in SSA graph (?)
static tree
find_ctrl_var(basic_block header, struct loop* loop)
{
    gimple cond_stmt;
    tree var = NULL_TREE;

    cond_stmt = gsi_stmt(gsi_last_bb(header));

    gcc_assert(gimple_code(cond_stmt) == GIMPLE_COND);

    var = check_for_ctrl_var(gimple_cond_lhs(cond_stmt));
    if(var != NULL_TREE)
        {
            return var;
        }

    var = check_for_ctrl_var(gimple_cond_rhs(cond_stmt));
    gcc_assert(var != NULL_TREE);
    return var;
}

static bool
ud_chain_cb(tree var, gimple stmt, void* data)
{
    if(dump_file)
        {
            fprintf(dump_file, "walk ud chain ");
            print_generic_expr(dump_file, var, 0);
            fprintf(dump_file, " ");
            print_gimple_stmt(dump_file, stmt, 0, 0);
            fprintf(dump_file, "\n");
        }
    if(gimple_code(stmt) != GIMPLE_PHI)
        {
            gimple* pstmt = (gimple*)data;
            *pstmt = stmt;
            return true;
        }

    return false;
}

static void
find_ctrl_var_init(tree var, gimple_stmt_iterator* gsi)
{
    gimple def_stmt;
    walk_use_def_chains(var, ud_chain_cb, (void*)&def_stmt, false);
    *gsi = gsi_for_stmt(def_stmt);
    while(!gsi_end_p(*gsi))
        {
            if(gsi_stmt(*gsi) == def_stmt)
                {
                    return;
                }
            gsi_next(gsi);
        }
}

static bool
ctrl_var_cb(tree var, gimple stmt, void* data)
{
    vec<gimple_stmt_iterator>* piter = (vec<gimple_stmt_iterator>*)data;
    gimple_stmt_iterator gsi = gsi_for_stmt(stmt);
    while(!gsi_end_p(gsi))
        {
            if(gsi_stmt(gsi) == stmt)
                {
                    if(gimple_code (stmt) == GIMPLE_PHI)
                        {
                            unsigned i;
                            for(i = 0; i < piter->length(); ++i)
                                {
                                    if(gsi_stmt((*piter)[i]) == stmt)
                                        {
                                            break;
                                        }
                                }
                            if(i < piter->length())
                                {
                                    break;
                                }
                        }
                    piter->safe_push(gsi);
                    break;
                }
            gsi_next(&gsi);
        }

    return false;
}

static void
gather_control_var_defs(tree var, vec<gimple_stmt_iterator>* piter)
{
    piter->create(16);
    walk_use_def_chains(var, ctrl_var_cb, (void*)piter, false);
}

static void
parallelize_loop(struct loop* l, unsigned collapse)
{
    if(dump_file)
        {
            fprintf(dump_file, "parallelize loop %d\n", l->num);
        }
    unsigned i;

    basic_block* bb = get_loop_body(l);
    vec<basic_block> loop_blocks;

    loop_blocks.create(l->num_nodes);
    for(i = 0; i < l->num_nodes; ++i)
    {
      loop_blocks.safe_push(bb[i]);
    }
    XDELETEVEC(bb);

    if(dump_file)
        {
            fprintf(dump_file, "header: %d\n", l->header->index);
            fprintf(dump_file, "latch: %d\n", l->latch->index);
            fprintf(dump_file, "exit edge %p\n", (void*)single_exit(l));
            fflush(dump_file);
        }

    gcc_assert(single_dom_exit(l));
    if(dump_file)
        {
            dump_fn_body(dump_file, "BEFORE");
        }

    edge latch, exit;
    basic_block hdr_blk;

    latch = loop_latch_edge(l);
    exit = single_dom_exit(l);
    hdr_blk = exit->src;

    tree ctrl_var = find_ctrl_var(hdr_blk, l);

    if(dump_file)
        {
            fprintf(dump_file, "loop control var ");
            print_generic_expr(dump_file, ctrl_var, 0);
            fprintf(dump_file, "\n");
        }

    vec<gimple_stmt_iterator> ctrl_var_defs;
    gather_control_var_defs(ctrl_var, &ctrl_var_defs);
    if(dump_file)
        {
            unsigned i;
            for(i = 0; i < ctrl_var_defs.length(); ++i)
                {
                    print_gimple_stmt(dump_file, gsi_stmt(ctrl_var_defs[i]),
                                        0, 0);
                }
        }


    if(dump_file)
        {
            fprintf(dump_file, "latch edge %d -> %d\n",
                    latch->src->index, latch->dest->index);
            fprintf(dump_file, "exit edge %d -> %d\n",
                    exit->src->index, exit->dest->index);
            fprintf(dump_file, "redirecting %d -> %d\n",
                    latch->src->index, exit->dest->index);
        }

    vec<struct phi_arg_d*> phi_args;
    gimple_stmt_iterator phi_iter;

    phi_args.create(4);
    for(phi_iter = gsi_start_phis(latch->dest); !gsi_end_p(phi_iter);
            gsi_next(&phi_iter))
        {
            gimple phi_stmt = gsi_stmt(phi_iter);
            unsigned i;

            for(i = 0; i < gimple_phi_num_args(phi_stmt); ++i)
                {
                    edge e = gimple_phi_arg_edge(phi_stmt, i);
                    if(e->src->index == latch->src->index)
                        {
                            phi_args.safe_push(gimple_phi_arg(phi_stmt, i));
                            break;
                        }
                }
        }


    if(!redirect_edge_and_branch(latch, exit->dest))
        {
            redirect_edge_and_branch_force(latch, exit->dest);
        }


    for(phi_iter = gsi_start_phis(exit->dest); !gsi_end_p(phi_iter);
            gsi_next(&phi_iter))
        {
            gimple phi_stmt = gsi_stmt(phi_iter);
            unsigned i, j;

            for(i = 0; i < gimple_phi_num_args(phi_stmt); ++i)
              {
                edge e = gimple_phi_arg_edge(phi_stmt, i);
                if(e->src->index == latch->src->index
                        && gimple_phi_arg_def(phi_stmt, i) == NULL_TREE)
                  {
                    tree def_var = gimple_phi_result(phi_stmt);
                    for(j = 0; j < phi_args.length(); ++j)
                      {
                        struct phi_arg_d* pd = phi_args[j];
                        tree arg_var = get_use_from_ptr (&pd->imm_use);
                        if(SSA_NAME_VAR(def_var) != NULL_TREE
                             && SSA_NAME_VAR(def_var) == SSA_NAME_VAR(arg_var))
                          {
                              gimple_phi_set_arg(phi_stmt, i, pd);
                          }
                      }
                  }
              }
        }



    if(dump_file)
        {
            dump_fn_body(dump_file, "AFTER REDIRECT");
        }


    gcc_assert(can_remove_branch_p(exit));
    basic_block exit_bb = exit->dest;
    remove_branch(exit);
    vec<basic_block> v;
    v.create(1);
    v.quick_push(exit_bb);
    iterate_fix_dominators(CDI_DOMINATORS, v, true);

    if(dump_file)
        {
            dump_fn_body(dump_file, "AFTER REMOVE EXIT");
        }


    basic_block last_def = get_immediate_dominator(CDI_DOMINATORS, hdr_blk);
    int def_idx = -1;
    tree def_var = NULL_TREE;
    if(last_def != NULL)
        {
            for(i = 0; i < ctrl_var_defs.length(); ++i)
                {
                    if(ctrl_var_defs[i].bb == last_def)
                        {
                            break;
                        }
                }
            if(i < ctrl_var_defs.length())
                {
                    def_idx = i;
                }
        }

    if(def_idx >= 0)
        {
            if(dump_file)
                {
                    fprintf(dump_file, "last ctrl var def in block %d\n",
                            last_def->index);
                }
            gimple_stmt_iterator gsi = ctrl_var_defs[def_idx];
            gimple stmt = gsi_stmt(gsi);
            def_var = get_gimple_def_var(stmt);
        }

    for(i = 0; i < ctrl_var_defs.length(); ++i)
        {
            unsigned j;
            gimple_stmt_iterator gsi = ctrl_var_defs[i];
            for(j = 0; j < loop_blocks.length(); ++j)
                {
                    if(gsi.bb == loop_blocks[j])
                        {
                            break;
                        }
                }
            if(j < loop_blocks.length())
                {
                    gimple stmt = gsi_stmt(gsi);
                    tree lhs = get_gimple_def_var(stmt);
                    if(def_var != NULL_TREE)
                        {
                            replace_uses_by(lhs, def_var);
                            gsi_remove(&gsi, true);
                        }
                }
            else if(dominated_by_p(CDI_DOMINATORS, hdr_blk, gsi.bb))
                {
                    if(dump_file)
                        {
                            fprintf(dump_file,
                                    "use in block %d dominates header %d\n",
                                    gsi.bb->index, hdr_blk->index);
                        }
                    gimple stmt = gsi_stmt(gsi);
                    if(gimple_code(stmt) != GIMPLE_PHI)
                        {
                            location_t location = gimple_location(stmt);
                            tree lhs = get_gimple_def_var(stmt);
                            tree builtin_decl
                           = builtin_decl_explicit(BUILT_IN_OACC_GET_GLOBAL_ID);
                            tree builtin_return_type
                                = TREE_TYPE (TREE_TYPE (builtin_decl));
                            //FIXME: add more conversion magic???
                            gcc_assert(TREE_CODE(builtin_return_type)
                                       == TREE_CODE(TREE_TYPE(lhs)));

                            int builtin_unsigned 
                              = TYPE_UNSIGNED(builtin_return_type);
                            int lhs_unsigned = TYPE_UNSIGNED(TREE_TYPE(lhs));

                            /* _oacc_tmp = __builtin_get_global_id (0); */
                            gimple call_stmt = build_call(location,
                                        builtin_decl, 1,
                                        build_int_cst(builtin_return_type, 0));
                            tree tmp_var = create_tmp_reg(builtin_return_type,
                              "_acc_tmp");
                            tmp_var = make_ssa_name_fn(cfun, tmp_var, call_stmt);
                            set_gimple_def_var(call_stmt, tmp_var);
                            gen_add(&gsi, call_stmt);


                            if (builtin_unsigned != lhs_unsigned)
                              {
                                /* _ = (int) _oacc_tmp; */
                                gimple convert_stmt 
                                  = build_type_cast (TREE_TYPE(lhs), tmp_var);
                                tree convert_var 
                                  = create_tmp_reg(TREE_TYPE(lhs), "_acc_tmp");
                                convert_var 
                                  = make_ssa_name_fn(cfun, convert_var,
                                                  convert_stmt);
                                set_gimple_def_var(convert_stmt, convert_var);
                                gen_add (&gsi, convert_stmt);

                                /* i = _ + i; */
                                gimple add_stmt 
                                  = build_assign(PLUS_EXPR, convert_var, lhs);
                                tree new_var 
                                  = make_ssa_name_fn(cfun, SSA_NAME_VAR(lhs),
                                      add_stmt);
                                set_gimple_def_var(add_stmt, new_var);
                                gen_add(&gsi, add_stmt);
                              }
                          else
                              {
                                /* i = _oacc_tmp + i; */
                                gimple add_stmt 
                                  = build_assign(PLUS_EXPR, tmp_var, lhs);
                                tree new_var 
                                  = make_ssa_name_fn(cfun, SSA_NAME_VAR(lhs),
                                                      add_stmt);
                                set_gimple_def_var(add_stmt, new_var);
                                gen_add(&gsi, add_stmt);
                              }
                        }
                }
        }

    if(dump_file)
        {
            dump_fn_body(dump_file, "AFTER CTRL VAR");
        }

}

static void
parallelize_loops(struct loop* root, unsigned collapse)
{
    if(root->inner == NULL)
        {
            return;
        }

    calculate_dominance_info (CDI_DOMINATORS);
    fix_loop_structure(NULL);
    struct loop* ploop;
    for(ploop = root->inner; ploop != NULL; ploop = ploop->next)
        {
            parallelize_loop(ploop, collapse);
        }
}

static void
switch_to_child_func(struct function *child_cfun)
{
  basic_block bb;

  push_cfun(child_cfun);

  FOR_EACH_BB(bb)
  {
    gimple_stmt_iterator gsi;
    for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
      {
        gimple stmt = gsi_stmt(gsi);

        gimple_set_modified (stmt, true);
        update_stmt_operands(stmt);
      }
  }
  update_ssa(TODO_update_ssa);
  loop_optimizer_init (LOOPS_NORMAL | LOOPS_HAVE_RECORDED_EXITS);
  rewrite_into_loop_closed_ssa (NULL, TODO_update_ssa);
  scev_initialize ();
}

static void
switch_func_back(int save_opt_level)
{
  basic_block bb;

  scev_finalize();
  if(save_opt_level >= 0)
    {
      optimize = save_opt_level;
    }
  cleanup_tree_cfg();
  FOR_EACH_BB(bb)
  {
      gimple_stmt_iterator gsi;
      for(gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
          {
              gimple stmt = gsi_stmt(gsi);
              gimple_set_modified (stmt, true);
              update_stmt_operands(stmt);
          }
  }
  update_ssa(TODO_update_ssa);
  pop_cfun();
}

static void
schedule_kernel(gimple_stmt_iterator* gsi, acc_schedule sched,
                tree niter, tree clause)
{
  tree num_gangs = NULL_TREE,
    num_workers = NULL_TREE,
    vector_length = NULL_TREE;

  while(clause != NULL_TREE)
  {
    switch(ACC_CLAUSE_CODE(clause))
    {
    case ACC_CLAUSE_NUM_GANGS:
      num_gangs = ACC_CLAUSE_NUM_GANGS_EXPR(clause);
      break;
    case ACC_CLAUSE_NUM_WORKERS:
      num_workers = ACC_CLAUSE_NUM_WORKERS_EXPR(clause);
      break;
    case ACC_CLAUSE_VECTOR_LENGTH:
      vector_length = ACC_CLAUSE_VECTOR_LENGTH_EXPR(clause);
      break;
    default:
      break;
    }
    clause = ACC_CLAUSE_CHAIN(clause);
  }

  sched->items = integer_one_node;
  sched->tiling = NULL;
  sched->group_size = integer_minus_one_node;

  /*
    We currently do not use 'num_workers' clause hint.
    This clause has its origin from NVIDIA warps,
    OpenCL on the other hand doesn't support this concept.
  */

  if(num_gangs != NULL_TREE)
  {
    tree workitems = num_gangs;

    if(niter == NULL_TREE)
    {
      sched->items = workitems;
    }
    else
    {
      sched->items = niter;
      sched->tiling = workitems;
    }
  }
  else if(niter != NULL_TREE)
  {
    sched->items = niter;
  }

  if(vector_length != NULL_TREE)
  {
    sched->group_size = vector_length;
  }
}

static void
expand_oacc_kernels(gimple_stmt_iterator* gsi)
{
    unsigned i, j;
    gimple stmt = gsi_stmt(*gsi);
    tree sched_clauses = ((gimple_code(stmt) == GIMPLE_ACC_PARALLEL)
      ? gimple_acc_parallel_clauses(stmt) : NULL_TREE);

    tree child_fn = GIMPLE_ACC_CHILD_FN(stmt);

    struct function* child_cfun = DECL_STRUCT_FUNCTION(child_fn);
    bool is_paral = false;

    if(optimize < 1)
      {
          save_opt_level = optimize;
          ++optimize;
      }
    switch_to_child_func(child_cfun);

    struct loops* loops = current_loops;
    
    gcc_assert(loops != NULL && loops->tree_root != NULL);

    vec<acc_kernel> kernels;
    kernels.create(3);
    
    extract_kernels(loops, child_fn, &kernels, stmt);

    switch_func_back(save_opt_level);

    tree type, buffer_handle, queue_handle;

    type = build_pointer_type(void_type_node);
    for(i = 0; i < kernels.length(); ++i)
    {
      kernels[i]->kernel_handle = create_tmp_reg(type, "_oacc_tmp");
    }
    buffer_handle = create_tmp_reg(type, "_oacc_tmp");
    queue_handle = create_tmp_reg(type, "_oacc_tmp");

    const char* src_file = NULL;
    int src_line = 0;
    location_t locus = gimple_location(stmt);

    src_file = LOCATION_FILE(locus);
    src_line = LOCATION_LINE(locus);
    if(dump_file)
        {
            fprintf(dump_file, "file: '%s', line %d\n", src_file, src_line);
        }

    gimple call_stmt;

    if(flag_enable_openacc_profiling)
        {
            gen_replace(gsi, build_call(locus,
              builtin_decl_explicit(BUILT_IN_OACC_START_PROFILING), 0));

            /* OACC_check_cur_dev */
            gen_add(gsi, build_call(locus,
              builtin_decl_explicit(BUILT_IN_OACC_CHECK_CUR_DEV), 0));
        }
    else
        {
            gen_replace(gsi, build_call(locus,
              builtin_decl_explicit(BUILT_IN_OACC_CHECK_CUR_DEV), 0));
        }

    /* OACC_get_kernel */
    for(i = 0; i < kernels.length(); ++i) 
    {
      call_stmt = build_call(locus,
               builtin_decl_explicit(BUILT_IN_OACC_GET_KERNEL), 2,
               build_string_literal(strlen(ocl_module)+1, ocl_module),
               build_string_literal(
                   strlen(IDENTIFIER_POINTER(DECL_NAME(kernels[i]->func)))+1,
                   IDENTIFIER_POINTER(DECL_NAME(kernels[i]->func))));
      gimple_call_set_lhs(call_stmt, kernels[i]->kernel_handle);
      gen_add(gsi, call_stmt);
    }

    call_stmt = build_call(locus,
             builtin_decl_explicit(BUILT_IN_OACC_CREATE_EVENTS), 2,
             build_string_literal(strlen(src_file)+1, src_file),
             build_int_cst(uint32_type_node, src_line));
    gimple_call_set_lhs(call_stmt, queue_handle);
    gen_add(gsi, call_stmt);

    gen_add(gsi, build_call(locus,
              builtin_decl_explicit(BUILT_IN_OACC_ENQUEUE_EVENTS), 3,
              queue_handle,
              build_int_cst(uint32_type_node,
                            gimple_acc_nparams(stmt)),
              build_int_cst(uint32_type_node, OACC_PF_DATAIN)));

    for(i = 0; i < kernels.length(); ++i)
    {
      gen_add(gsi, build_call(locus,
                builtin_decl_explicit(BUILT_IN_OACC_ENQUEUE_EVENTS), 3,
                queue_handle, integer_one_node,
                build_int_cst(uint32_type_node, OACC_PF_EXEC)));
    }

    gen_add(gsi, build_call(locus,
              builtin_decl_explicit(BUILT_IN_OACC_ENQUEUE_EVENTS), 3,
              queue_handle,
              build_int_cst(uint32_type_node,
                            gimple_acc_nparams(stmt)),
              build_int_cst(uint32_type_node, OACC_PF_DATAOUT)));

    /* OACC_set_arg */
    tree bits_per_byte = build_int_cst(uint32_type_node, 8);
    tree chk_presence = integer_one_node;

    for(i = 0; i < gimple_acc_nparams(stmt); ++i)
        {
            tree arg = GIMPLE_ACC_PARAMS_PTR(stmt)[i];
            if(is_gimple_reg(arg)) continue;
            tree type = TREE_TYPE(arg);
            tree size = TYPE_SIZE(type);
            tree idx = build_int_cst(uint32_type_node, i);

            call_stmt = build_call(locus,
               builtin_decl_explicit(BUILT_IN_OACC_COPYIN), 5,
               build_fold_addr_expr(arg),
               fold_binary(TRUNC_DIV_EXPR,
                           uint32_type_node, size, bits_per_byte),
               chk_presence, queue_handle, idx);
            gimple_call_set_lhs(call_stmt, buffer_handle);
            gen_add(gsi, call_stmt);

            for(j = 0; j < kernels.length(); ++j)
            {
              gen_add(gsi, build_call(locus,
                  builtin_decl_explicit(BUILT_IN_OACC_SET_KERNEL_ARG), 3,
                  kernels[j]->kernel_handle, idx, buffer_handle));
            }
        }


    gen_add(gsi, build_call(locus,
                builtin_decl_explicit(BUILT_IN_OACC_ADVANCE_EVENTS), 1,
                queue_handle));

    /* OACC_start_kernel */
    for(i = 0; i < kernels.length(); ++i)
    {
      acc_schedule_t sched;
      tree offset = integer_zero_node;

      memset(&sched, sizeof(acc_schedule_t), 0);
      schedule_kernel(gsi, &sched, kernels[i]->niter_desc.niter,
                    sched_clauses);

      if(sched.tiling != NULL_TREE)
      {
        gimple stmt = gsi_stmt(*gsi), init_stmt;
        basic_block bb = gimple_bb(stmt);
        edge new_edge = split_block(bb, stmt), e;
        basic_block new_bb, header_bb, body_bb;
        struct loop* l;
        tree counter, counter_1, counter_2, counter_3;
        tree conv_var;

        new_bb = new_edge->dest;
        body_bb = create_empty_bb(bb);
        header_bb = create_empty_bb(body_bb);

        new_edge = redirect_edge_and_branch(new_edge, header_bb);
        e = make_edge(header_bb, body_bb, EDGE_DFS_BACK | EDGE_TRUE_VALUE);
        e = make_edge(header_bb, new_bb, EDGE_FALSE_VALUE);
        e = make_single_succ_edge(body_bb, header_bb, EDGE_FALLTHRU);

        set_immediate_dominator(CDI_DOMINATORS, header_bb, bb);
        set_immediate_dominator(CDI_DOMINATORS, new_bb, header_bb);
        set_immediate_dominator(CDI_DOMINATORS, body_bb, header_bb);

        l = alloc_loop();
        l->header = header_bb;
        header_bb->loop_father = l;
        l->latch = body_bb;
        body_bb->loop_father = l;


        place_new_loop(cfun, l);
        flow_loop_tree_node_add(bb->loop_father, l);
        
        counter = create_tmp_reg(intSI_type_node, "_oacc_counter");
        counter_1 = make_ssa_name_fn(cfun, counter, init_stmt);
        init_stmt = gimple_build_assign(counter_1, offset);
        gen_add(gsi, init_stmt);

        if(TYPE_UNSIGNED(TREE_TYPE(sched.items))
            != TYPE_UNSIGNED(TREE_TYPE(counter)))
        {
          gimple convert_stmt =
            build_type_cast(TREE_TYPE(counter), sched.items);
          conv_var = create_tmp_reg(TREE_TYPE(counter), "_acc_tmp");
          conv_var = make_ssa_name_fn(cfun, conv_var, convert_stmt);
          set_gimple_def_var(convert_stmt, conv_var);
          gen_add(gsi, convert_stmt);
        }
        else
        {
          conv_var = sched.items;
        }

        counter_2 = make_ssa_name_fn(cfun, counter, init_stmt);
        counter_3 = make_ssa_name_fn(cfun, counter, init_stmt);

        *gsi = gsi_start_bb(body_bb);
        gen_add(gsi, build_call(locus,
                      builtin_decl_explicit(BUILT_IN_OACC_START_KERNEL), 6,
                      kernels[i]->kernel_handle,
                      sched.tiling,       /* WORKITEMS */
                      counter_2,      /* OFFSET */
                      sched.group_size,  /* GROUPSIZE */
                      queue_handle,
                      integer_zero_node));
        stmt = build_assign(PLUS_EXPR, counter_2, sched.tiling);
        set_gimple_def_var(stmt, counter_3);
        gen_add(gsi, stmt);

        *gsi = gsi_start_bb(header_bb);
        stmt = create_phi_node(counter_2, header_bb);
        add_phi_arg(stmt, counter_1, new_edge, locus);
        add_phi_arg(stmt, counter_3, e, locus);

        gen_add(gsi, gimple_build_cond(LT_EXPR, counter_2, conv_var,
                          NULL, NULL));
        *gsi = gsi_start_bb(new_bb);
      }
      else 
      {
        gen_add(gsi, build_call(locus,
                      builtin_decl_explicit(BUILT_IN_OACC_START_KERNEL), 6,
                      kernels[i]->kernel_handle,
                      sched.items,       /* WORKITEMS */
                      offset,      /* OFFSET */
                      sched.group_size,  /* GROUPSIZE */
                      queue_handle,
                      integer_zero_node));
      }
      gen_add(gsi, build_call(locus,
                  builtin_decl_explicit(BUILT_IN_OACC_ADVANCE_EVENTS), 1,
                  queue_handle));
    }

    /* OACC_copyout */
    for(i = 0; i < gimple_acc_nparams(stmt); ++i)
        {
            tree arg = GIMPLE_ACC_PARAMS_PTR(stmt)[i];
            if(is_gimple_reg(arg)) continue;
            tree type = TREE_TYPE(arg);
            tree size = TYPE_SIZE(type);
            tree idx = build_int_cst(uint32_type_node, i);

            gen_add(gsi, build_call(locus,
                builtin_decl_explicit(BUILT_IN_OACC_COPYOUT), 5,
                build_fold_addr_expr(arg),
                fold_binary(TRUNC_DIV_EXPR, uint32_type_node, size,
                  bits_per_byte),
                chk_presence, queue_handle, idx));
        }

    gen_add(gsi, build_call(locus,
                builtin_decl_explicit(BUILT_IN_OACC_ADVANCE_EVENTS), 1,
                queue_handle));
    gen_add(gsi, build_call(locus,
                builtin_decl_explicit(BUILT_IN_OACC_WAIT_EVENTS), 1,
                queue_handle));

}

static void
generate_opencl(void)
{
    rewrite_out_of_ssa(&SA);
    cleanup_tree_cfg();
    generate_opencl_kernel(ocl_module, current_function_decl, &SA);
    finish_out_of_ssa(&SA);
}


/* if we generated OenCL code, function body isn't needed */
static void
finish_current_fn(void)
{
    if(dump_file)
        {
            fprintf(dump_file, "gimple_body=%p\n", (void*)cfun->gimple_body);
            fprintf(dump_file, "gimple_df=%p\n", (void*)cfun->gimple_df);
            fprintf(dump_file, "cfg=%p\n", (void*)cfun->cfg);
        }
    basic_block bb;
    unsigned i;

    for(i = 2; i < basic_block_info->length() - 2; ++i)
    {
      bb = (*basic_block_info)[i];
      unlink_block(bb);
    }

}

static void
expand_region (acc_region region)
{
  gimple stmt;
  gimple_stmt_iterator gsi;

  stmt = region->stmt;
  switch(gimple_code(stmt))
    {
    case GIMPLE_ACC_PARALLEL:
    case GIMPLE_ACC_KERNELS:
      gsi = gsi_for_stmt(stmt);
      expand_oacc_kernels(&gsi);
      break;
    default:
      gcc_unreachable();
    }
}

static void
traverse_regions (acc_region region)
{
  unsigned i;

  for(i = 0; i < region->children->length(); ++i)
  {
    traverse_regions ((*region->children)[i]);
  }
  if(region->stmt != NULL)
    expand_region(region);
}

static void
build_acc_region(basic_block bb, acc_region outer)
{
  gimple_stmt_iterator gsi;
  basic_block child;

  gsi = gsi_last_bb(bb);
  if(!gsi_end_p(gsi) && is_gimple_acc(gsi_stmt(gsi)))
    {
      gimple stmt;
      acc_region region = NULL;

      stmt = gsi_stmt(gsi);
      switch(gimple_code(stmt))
        {
        case GIMPLE_ACC_KERNELS:
        case GIMPLE_ACC_PARALLEL:
          region = new_acc_region(stmt, outer);
          outer = region;
          break;
        case GIMPLE_ACC_COMPUTE_REGION_END:
        case GIMPLE_ACC_DATA_REGION_END:
          gcc_assert(outer);
          region = outer;
          outer = outer->parent;
          gsi_replace( &gsi, gimple_build_nop (), false);
          break;
        default:
          break;
        }
    }
  for(child = first_dom_son(CDI_DOMINATORS, bb); child != NULL;
      child = next_dom_son(CDI_DOMINATORS, child))
    build_acc_region(child, outer);
}

/* Main entry point for expanding OpenACC.  */

static unsigned int
execute_expand_oacc (void)
{
    basic_block bb;
    splay_tree_node v;

    if(kernels &&
        (v = splay_tree_lookup(kernels, DECL_UID(current_function_decl)))
        != NULL)
    {
      if((unsigned)v->value > 0)
      {
        parallelize_loops(current_loops->tree_root, (unsigned)v->value);
      }
      generate_opencl();
      return 0;
    }

    root_region = new_acc_region(NULL, NULL);
    calculate_dominance_info (CDI_DOMINATORS);
    build_acc_region (ENTRY_BLOCK_PTR, root_region);

    if(root_region->children->length() > 0)
      {
        if(dump_file)
          {
            fprintf(dump_file, "ACC REGION TREE\n===============\n");
            dump_acc_region(dump_file, root_region, 0);
          }
        traverse_regions(root_region);
      }
    delete_acc_region(root_region);
    root_region = NULL;

    return 0;
}

/* OpenACC expansion */

static bool
gate_expand_oacc (void)
{
    return (flag_openacc != 0);
}


namespace
{
const pass_data pass_data_expand_oacc =
{
    GIMPLE_PASS,
    "oaccexp",				/* name */
    OPTGROUP_NONE,                        /* optinfo_flags */
    gate_expand_oacc,			/* gate */
    execute_expand_oacc,			/* execute */
    TV_NONE,				/* tv_id */
    PROP_cfg,			/* properties_required */
    0,					/* properties_provided */
    0,					/* properties_destroyed */
    0,					/* todo_flags_start */
    TODO_update_ssa                 		/* todo_flags_finish */
};

class pass_expand_oacc : public gimple_opt_pass
{
public:
    pass_expand_oacc(gcc::context *ctxt)
        :
        gimple_opt_pass(pass_data_expand_oacc,
                        ctxt)
    {}

    /* opt_pass methods: */
    bool gate ()
    {
        return gate_expand_oacc ();
    }
    unsigned int execute ()
    {
        return
            execute_expand_oacc ();
    }

}; // class pass_expand_oacc
}

gimple_opt_pass *
make_pass_expand_oacc (gcc::context *ctxt)
{
    return new pass_expand_oacc (ctxt);
}

/* Diagnose OpenACC structured block violations  */

/* Check for mismatched contexts and generate an error if needed.  Return
   true if an error is detected.  */

static bool
diagnose_cb(gimple_stmt_iterator *gsi_p, gimple branch_ctx, gimple label_ctx)
{
    if (label_ctx == branch_ctx)
        return false;
    /* If it's obvious we have an invalid entry, be specific about the error.*/
    if (branch_ctx == NULL)
        error ("invalid entry to OpenACC structured block");
    else
        /* Otherwise, be vague and lazy, but efficient.  */
        error ("invalid branch to/from an OpenACC structured block");

    gsi_replace (gsi_p, gimple_build_nop (), false);
    return true;
}

static void
get_recursive_seq (enum gimple_code code, gimple stmt, vec<gimple_seq*>* seq)
{
  switch (code)
  {
  case GIMPLE_ACC_KERNELS:
  case GIMPLE_ACC_PARALLEL:
  case GIMPLE_ACC_LOOP:
    seq->safe_push (gimple_acc_body_ptr (stmt));
    break;
  default:
    break;
  }
}

static unsigned int
diagnose_oacc_structured_block_errors (void)
{

    vec<enum gimple_code> oacc_codes;

    oacc_codes.create(3);
    oacc_codes.quick_push(GIMPLE_ACC_KERNELS);
    oacc_codes.quick_push(GIMPLE_ACC_PARALLEL);
    oacc_codes.quick_push(GIMPLE_ACC_LOOP);

    diagnose_gotos(&oacc_codes, get_recursive_seq, diagnose_cb);
    return 0;
}

static bool
gate_diagnose_oacc_blocks (void)
{
    return flag_openacc != 0;
}


namespace
{
const pass_data pass_data_diagnose_oacc_blocks =
{
    GIMPLE_PASS,
    "*diagnose_oacc_blocks",		/* name */
    OPTGROUP_NONE,                      /* optinfo_flags */
    gate_diagnose_oacc_blocks,		/* gate */
    diagnose_oacc_structured_block_errors,	/* execute */
    TV_NONE,				/* tv_id */
    PROP_gimple_any,			/* properties_required */
    0,					/* properties_provided */
    0,					/* properties_destroyed */
    0,					/* todo_flags_start */
    0,					/* todo_flags_finish */
};

class pass_diagnose_oacc_blocks : public gimple_opt_pass
{
public:
    pass_diagnose_oacc_blocks(gcc::context *ctxt)
        : gimple_opt_pass(pass_data_diagnose_oacc_blocks, ctxt)
    {}

    /* opt_pass methods: */
    bool gate ()
    {
        return gate_diagnose_oacc_blocks ();
    }
    unsigned int execute ()
    {
        return diagnose_oacc_structured_block_errors ();
    }

}; // class pass_diagnose_oacc_blocks
}

gimple_opt_pass *
make_pass_diagnose_oacc_blocks (gcc::context *ctxt)
{
    return new pass_diagnose_oacc_blocks (ctxt);
}

#include "gt-oacc-low.h"
