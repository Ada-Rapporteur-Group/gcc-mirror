/* Prints out a tree of generic/gimple nodes in human readable form, both in
   straight text and in HTML. The entry point is dump_generic_nodes().

   Copyright(C) 1990-2024 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or(at your option) any later
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
#include "tree.h"
#include "cgraph.h"
#include "diagnostic.h"
#include "varasm.h"
#include "print-rtl.h"
#include "stor-layout.h"
#include "langhooks.h"
#include "tree-iterator.h"
#include "gimple-pretty-print.h"
#include "tree-cfg.h"
#include "dumpfile.h"

#undef DEFTREESTRUCT
#define DEFTREESTRUCT(VAL, NAME) NAME,
static const char *ts_enum_names[] =
  {
  #include "treestruct.def"
  };
#undef DEFTREESTRUCT

#define ADD_FLAG(accessor,text)if(accessor(node)){strcat(ach," " text);}

static FILE *ftext = NULL;
static FILE *fhtml = NULL;
static FILE *fjson = NULL;

static int json_level = 0;
static const char *json_comma;
static const int spaces_per_indent = 2;

static void rjd_print_node(tree node);

static int phase = 1;

/* Define the hash table of nodes already seen.
   Such nodes are not repeated; brief cross-references are used.  */

struct TREE
  {
  tree this_node;
  int     seen;
  } ;

static struct TREE *nodes = NULL;
static int GV_size_of_tree = 0;
static int GV_number_of_nodes = 0;

static void
json_fprintf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));

static void
json_fprintf(const char *format, ...)
{
  char ach1[2048];
  if( phase == 2 && fjson )
    {
    va_list args;
    va_start(args, format);
    vsnprintf(ach1, sizeof(ach1), format, args);
    va_end(args);
    fprintf(fjson, "%s", ach1);
    }
}

static void
json_indent()
{
  for(int i=0; i<json_level*spaces_per_indent; i++)
    {
    json_fprintf(" ");
    }
}

static void
json_newline()
{
  json_fprintf("%s\n", json_comma);
  json_indent();
}

static int
find_node_in_nodes(tree node)
{
  // This is an O(n^2) abomination.  At a suitable time, replace it with a
  // hashed map!
  int retval = -1;
  gcc_assert(GV_number_of_nodes <= GV_size_of_tree);
  for(int i=0; i<GV_number_of_nodes; i++)
    {
    if( nodes[i].this_node == node )
      {
      retval = i;
      break;
      }
    }
  return retval;
}

static int
add_node_to_nodes(tree node)
{
  // Assume we know the node isn't there yet:
  gcc_assert(GV_number_of_nodes <= GV_size_of_tree);
  if( GV_number_of_nodes == GV_size_of_tree )
    {
    // We've run out of room.  Double the number of nodes:
    GV_size_of_tree *= 2;
    if( GV_size_of_tree == 0 )
      {
      GV_size_of_tree = 64;
      }
    struct TREE *newnodes =
               (struct TREE *)xmalloc( GV_size_of_tree * sizeof(struct TREE) );
    memcpy(newnodes,nodes, GV_number_of_nodes * sizeof(struct TREE));
    free(nodes);
    nodes = newnodes;
    }
  gcc_assert(GV_number_of_nodes <= GV_size_of_tree);
  nodes[GV_number_of_nodes].this_node = node;
  nodes[GV_number_of_nodes].seen = 0;
  GV_number_of_nodes += 1;
  return GV_number_of_nodes-1;
}

#pragma GCC diagnostic ignored "-Wsuggest-attribute=format"

static void
rjd_fprintf(const char *format, ...)
{
  // NOTE: I painfully learned that mixing fprintf() and vfprintf() calls
  // can result in hard-to-find memory allocation bugs.  Probably worth
  // tracking down, but the the problem shows up in the libc6 library
  // routines.
  char ach1[2048];
  char ach2[4196];
  char ach3[4196];
  if( phase == 2 )
    {
    va_list args;
    va_start(args, format);
    vsnprintf(ach1, sizeof(ach1), format, args);
    va_end(args);

    fprintf(ftext, "%s", ach1);

    // Copy ach1 to ach2, replacing '\n' with "<br>"
    char *p1 = ach1;
    char *p2 = ach2;

    while( *p1 )
        {
        if(*p1 == '\n')
          {
          p1 += 1;
          *p2 = '\0';
          strcat(p2, "<br>");
          p2 = ach2 + strlen(ach2);
          }
        else
          {
          *p2++ = *p1++;
          }
        }
    size_t ach1_length = strlen(ach1);

    // To make the HTML more-or-less readable, if ach1 ends with a newline,
    // make ach2 end with a newline as well.
    if( ach1_length && ach1[ach1_length-1] == '\n' )
      {
      *p2++ = '\n';
      }
    *p2++ = '\0';

    // We now look for NodeNumberNNN and replace it with
    // <a href="#NodeNumberNNN">NodeNumberNNN</a>

    char *pleft = strstr(ach2, "NodeNumber");
    if( pleft )
      {
      char *pright = pleft + strlen("NodeNumber");
      while( *pright >= '0' && *pright <= '9' )
        {
        pright += 1;
        }
      memset(ach3, 0, sizeof(ach3));
      memcpy(ach3, ach2, pleft - ach2);
      strcat(ach3, "<a href=\"#" );
      char *p = ach3 + strlen(ach3);
      memcpy(p, pleft, pright-pleft);
      strcat(ach3,"\">");
      p = ach3 + strlen(ach3);
      memcpy(p, pleft, pright-pleft);
      p = ach3 + strlen(ach3);
      strcat(ach3,"</a>");
      p = ach3 + strlen(ach3);
      strcpy(p, pright);
      strcpy(ach2, ach3);
      }

    fprintf(fhtml, "%s", ach2);
    }
}

#define NOT_QUOTED false
static void
json_namevalue(const char *name, const char *value, bool quoted = true)
{
  if( phase == 2 )
    {
    json_newline();
    if( quoted )
      {
      json_fprintf("\"%s\":\"%s\"", name, value);
      }
    else
      {
      json_fprintf("\"%s\":%s", name, value);
      }
    }
}

static void
html_boilerplate(char *title=NULL)
{
  if( fhtml )
    {
    if( title )
      {
      fprintf(fhtml,
              "<!DOCTYPE html>\n"
              "<html lang=\"en\">\n"
              "  <head>\n"
              "    <meta charset=\"utf-8\">\n"
              "    <title>%s</title>\n"
              "    <style>\n"
              "    body\n"
              "        {\n"
              "        font-family: courier, serif;\n"
              "        font-size: 13px;\n"
              "        }\n"
              "    </style>\n"
              "  </head>\n"
              "  <body>\n", title);
      }
    else
      {
      fprintf(fhtml, "%s",
              "  </body>\n"
              "</html>\n");
      }
    }
}

/* Print a node in brief fashion*/

static void
print_name(const char *prefix, tree node)
{
  if( node && TREE_CODE_CLASS(TREE_CODE(node)) == tcc_declaration )
    {
    tree name = DECL_NAME(node);
    if( name )
      {
      rjd_fprintf("%s\"%s\"", prefix, IDENTIFIER_POINTER(name));
      }
    }
}

static void
rjd_subtree(const char *subtree_name, tree subtree)
{
  if( subtree )
    {
    if( phase == 1 )
      {
      // Make sure the subtree is in the list of nodes.  And, yes, this
      // is a potential headachy recursivy thingummy.  But computers are
      // good at that.
      rjd_print_node(subtree);

      int subtree_node_number = find_node_in_nodes(subtree);
      if( subtree_node_number == -1 )
        {
        printf("Run in circles, scream and shout!\n");
        exit(1);
        }

      }
    else if( phase == 2 )
      {
      char ach[512];
      int node_number = find_node_in_nodes(subtree);
      if( node_number >= 0 )
        {
        rjd_fprintf("%s: NodeNumber%d", subtree_name, node_number);

        // Handle a few subthings that are very common, and useful to see:
        gcc_assert(node_number < GV_number_of_nodes
                   && GV_number_of_nodes <= GV_size_of_tree);
        tree subnode = nodes[node_number].this_node;
        if( subnode )
          {
          enum tree_code subcode = TREE_CODE(subnode);

          // After the NodeNumber, print the code name.  Unless it is an
          // integer_cst, because we convert that to int32 or uint64 later.
          if( subcode != INTEGER_CST )
            {
            rjd_fprintf(" %s", get_tree_code_name(subcode));
            }

          if( subcode == IDENTIFIER_NODE && IDENTIFIER_POINTER(subnode) )
            {
            rjd_fprintf(" \"%s\"", IDENTIFIER_POINTER(subnode));
            }

          print_name(" ", subnode);

          if( subcode == INTEGER_CST )
            {
            tree int_cst_type = TREE_TYPE(subnode);
            tree_code int_cst_type_code = TREE_CODE(int_cst_type);

            if( int_cst_type_code == POINTER_TYPE )
              {
              rjd_fprintf(" pointer");
              }
            else if( int_cst_type_code == INTEGER_TYPE)
              {
              // The int_cst_type is an integer_type, so...
              tree min_value = TYPE_MIN_VALUE_RAW(int_cst_type);
              print_dec(wi::to_wide(min_value),
                        ach,
                        TYPE_SIGN(TREE_TYPE(min_value)));
              if( strcmp( ach, "0") )
                {
                rjd_fprintf(" int",ach);
                }
              else
                {
                rjd_fprintf(" uint",ach);
                }

              tree size_in_bits = TYPE_SIZE(int_cst_type);

              print_dec(wi::to_wide(size_in_bits),
                        ach,
                        TYPE_SIGN(TREE_TYPE(size_in_bits)));
              rjd_fprintf(ach);

              print_dec(wi::to_wide(subnode),
                        ach, TYPE_SIGN(TREE_TYPE(subnode)));
              }

            print_dec(wi::to_wide(subnode),
                      ach,
                      TYPE_SIGN(TREE_TYPE(subnode)));
            rjd_fprintf(" %s",ach);
            }

          if( subcode == DECL_EXPR )
            {
            int len = TREE_OPERAND_LENGTH(subnode);
            if( len )
              {
              print_name(" ", TREE_OPERAND(subnode, 0));
              }
            }

          if( subcode == CALL_EXPR )
            {
            int len = TREE_OPERAND_LENGTH(subnode);
            if( len > 1)
              {
              tree addr_expression = TREE_OPERAND(subnode, 1);
              int len2 = TREE_OPERAND_LENGTH(addr_expression);
              if( len2 )
                {
                print_name(" ", TREE_OPERAND(addr_expression, 0));
                }
              }
            }

          if( subcode == ADDR_EXPR  )
            {
            int len = TREE_OPERAND_LENGTH(subnode);
            if( len > 0)
              {
              print_name(" ", TREE_OPERAND(subnode, 0));
              }
            }

          if( subcode == MODIFY_EXPR )
            {
            int len = TREE_OPERAND_LENGTH(subnode);
            if( len > 0)
              {
              tree target = TREE_OPERAND(subnode, 0);
              tree_code target_code = TREE_CODE(target);
              tree_code_class target_code_class = TREE_CODE_CLASS(target_code);
              if( target_code_class == tcc_declaration )
                {
                print_name(" ", target);
                }
              else if( target_code == COMPONENT_REF
                                      && target_code_class == tcc_reference )
                {
                int len = TREE_OPERAND_LENGTH(target);
                tree structure = NULL_TREE;
                tree field     = NULL_TREE;
                if( len > 0 )
                  {
                  structure = TREE_OPERAND(target, 0);
                  }
                if( len > 1 )
                  {
                  field = TREE_OPERAND(target, 1);
                  }
                print_name(" ", structure);
                print_name("::", field);
                }
              }
            }

          rjd_fprintf("\n");
          }
        // In contrast, for the JSON output, we just want the node number:
        // But we need to intervene in the case where the subtree name starts
        // off with "operand[nnn]".  We are putting them in JSON arraysm, so we
        // need to eliminate that name
        if( strstr(subtree_name, "constructor_elt[") != subtree_name )
          {
          // constructors are handled separately because they have both index
          // and value members.  Search for "constructor_elt" to find that code.
          if(    strstr(subtree_name, "operand[") == subtree_name
              || strstr(subtree_name, "tree_vector_element[") == subtree_name
              || strstr(subtree_name, "statement_list[") == subtree_name
              || strstr(subtree_name, "nonlocalized_var[") == subtree_name
              )
            {
            // We are elminating the subtree name
            json_newline();
            }
          else
            {
            json_namevalue(subtree_name, "", NOT_QUOTED);
            }
          json_fprintf("{\"node\":%d}", node_number);
          }
        }
      else
        {
        // This can happen as a result of certain compilation
        // errors.   Just ignore them.
        }
      }
    }
  else
    {
    if( strstr(subtree_name, "operand[") == subtree_name )
      {
      json_newline();
      json_fprintf("{\"node\":null}");
      }

    }

}

static void
json_flags(const char *name, const char *ach)
{
  const char *p = ach+1;  // Skip past the initial space
  json_namevalue(name, "",  NOT_QUOTED);
  json_level += 1;
  json_comma = "";
  json_fprintf("\n");
  json_indent();
  json_fprintf("{");

  while( *p )
    {
    const char *pend = strchr(p, ' ');
    if( !pend )
      {
      pend = p + strlen(p);
      }
    char achName[256];
    char *d = achName;
    while(p < pend )
      {
      *d++ = *p++;
      }
    *d++= '\0';
    if( *p == ' ' )
      {
      p += 1;
      }
    json_namevalue(achName, "true", NOT_QUOTED);
    json_comma = ",";
    }
  json_fprintf("\n");
  json_indent();
  json_fprintf("}");

  json_level -= 1;
  json_comma = ",";
}

static void
json_start_array(const char *name)
{
  // We will set up a JSON array of operands
  json_namevalue(name,"", NOT_QUOTED);
  json_fprintf("\n");
  json_level += 1;
  json_indent();
  json_fprintf("[");
  json_comma = "";
}
static void
json_finish_array()
{
  json_fprintf("\n");
  json_indent();
  json_fprintf("]");
  json_level -= 1;
  json_comma = ",";
}

static void
rjd_print_node(tree node)
{
  char ach[4096];
  enum tree_code_class tclass;
  int len;
  int i;
  expanded_location xloc;
  enum tree_code code;

  if(node == 0)
    {
    // When handled a NULL, just return
    return;
    }

  int node_number = find_node_in_nodes(node);
  if( phase == 1 )
    {
    if( node_number != -1 )
      {
      // We're building the list of nodes, and we've already processed this
      // node:
      return;
      }

    // We are building the list of nodes, and this is a new one:
    node_number = add_node_to_nodes(node);
    }
  // From here on out, we know that node_number is valid, whether in
  // phase 1 or phase 2

  code = TREE_CODE(node);

  /* It is unsafe to look at any other fields of a node with ERROR_MARK or
     invalid code.  */
  if(code == ERROR_MARK || code >= MAX_TREE_CODES)
    {
    rjd_fprintf("This node is unsafe.  The reported TREE_CODE is %d\n",code);
    return;
    }

  tclass = TREE_CODE_CLASS(code);

  /* Announce the coming of a new node: */
  if( phase==2 && fhtml )
    {
    fprintf(fhtml, "<p id=\"NodeNumber%d\">\n", node_number);
    }
  rjd_fprintf("***********************************This is NodeNumber%d\n",
              node_number);

  /* Print the NodeNumber in a more canonical form: */
  rjd_fprintf("(%p) NodeNumber%d\n", node, node_number);

  // Print the tree_code for this node
  rjd_fprintf("tree_code: %s\n", get_tree_code_name(code));
  json_namevalue("tree_code", get_tree_code_name(code));

  // It might be useful to see the class
  const char *classtxt;
  switch(tclass)
    {
    case tcc_exceptional:
      classtxt = "tcc_exceptional";
      break;
    case tcc_constant:
      classtxt = "tcc_constant";
      break;
    case tcc_type:
      classtxt = "tcc_type";
      break;
    case tcc_declaration:
      classtxt = "tcc_declaration";
      break;
    case tcc_reference:
      classtxt = "tcc_reference";
      break;
    case tcc_comparison:
      classtxt = "tcc_comparison";
      break;
    case tcc_unary:
      classtxt = "tcc_unary";
      break;
    case tcc_binary:
      classtxt = "tcc_binary";
      break;
    case tcc_statement:
      classtxt = "tcc_statement";
      break;
    case tcc_vl_exp:
      classtxt = "tcc_vl_exp";
      break;
    case tcc_expression:
      classtxt = "tcc_expression";
      break;
    default:
      gcc_unreachable();
      break;
    }
  rjd_fprintf("tree_code_class: %s\n", classtxt);
  json_namevalue("tree_code_class", classtxt);

  int required[64];
  int processed[64];
  for(int i=0; i<64; i++)
    {
    required[i] = CODE_CONTAINS_STRUCT(code, i);
    processed[i] = 0;
    }

  if( CODE_CONTAINS_STRUCT(code, TS_BASE) )
    {
    processed[TS_BASE] = 1;
    // There are 16 bits in TS_BASE.  The trouble is, they have
    // different meanings for different codes; see the extensive
    // comment in tree-core.h
    strcpy(ach, "");
    if( tclass != tcc_type && TREE_SIDE_EFFECTS(node) )
      {
      strcat(ach," side_effects");
      }
    if( tclass != tcc_type && TREE_CONSTANT(node) )
      {
      strcat(ach," constant");
      }
    if( TREE_ADDRESSABLE(node) )
      {
      strcat(ach," addressable");
      }
    if( TREE_THIS_VOLATILE(node) )
      {
      strcat(ach," volatile");
      }
    if( tclass != tcc_type && TREE_READONLY(node) )
      {
      strcat(ach," readonly");
      }
    if( TREE_ASM_WRITTEN(node) )
      {
      strcat(ach," asm_written");
      }
    if( TREE_NO_WARNING(node) )
      {
      strcat(ach," nowarning");
      }
    if( TREE_VISITED(node) )
      {
      strcat(ach," visited");
      }

    if( TREE_USED(node) )
      {
      strcat(ach," used");
      }
    if( TREE_NOTHROW(node) )
      {
      strcat(ach," nothrow");
      }
    if( TREE_STATIC(node) )
      {
      strcat(ach," static");
      }
    if( TREE_PUBLIC(node) )
      {
      strcat(ach," public");
      }
    if( TREE_PRIVATE(node) )
      {
      strcat(ach," private");
      }
    if( TREE_PROTECTED(node) )
      {
      strcat(ach," protected");
      }
    if( TREE_DEPRECATED(node) )
      {
      strcat(ach," deprecated");
      }
    if( node->base.default_def_flag ) //There isn't a TREE_DEFAULT_DEF macro
      {
      strcat(ach," default_def");
      }
    if( tclass == tcc_constant )
      {
      if( TREE_OVERFLOW(node) )
        {
        strcat(ach," overflow");
        }
      }
    if( tclass == tcc_type )
      {
      ADD_FLAG(TYPE_UNSIGNED,   "unsigned");
      ADD_FLAG(TYPE_PACKED,     "packed");
      ADD_FLAG(TYPE_USER_ALIGN, "user_align");
      ADD_FLAG(TYPE_NAMELESS,   "nameless");
      ADD_FLAG(TYPE_ATOMIC,     "atomic");
      }
    if( strlen(ach) )
      {
      rjd_fprintf("base_flags:%s\n", ach);
      json_flags("base_flags", ach);
      }
    }

  if( tclass == tcc_type )
    {
    sprintf(ach, "%s(%u)",
            GET_MODE_NAME(TYPE_MODE(node)),(int)TYPE_MODE(node));
    rjd_fprintf("machine_mode: %s\n", ach);
    json_namevalue("machine_mode", ach);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_TYPED) )
    {
    processed[TS_TYPED] = 1;
    rjd_subtree("type", TREE_TYPE(node));
    if( tclass == tcc_type )
      {
      sprintf(ach, "%u", (int)TYPE_ADDR_SPACE(node));
      rjd_fprintf("address_space:%s\n", ach);
      json_namevalue("address_space", ach);
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_DECL_MINIMAL) )
    {
    processed[TS_DECL_MINIMAL] = 1;
    rjd_subtree("name", DECL_NAME(node));
    rjd_subtree("context", DECL_CONTEXT(node));
    xloc = expand_location(DECL_SOURCE_LOCATION(node));
    if( xloc.file )
      {
      sprintf(ach, "%s:%d:%d", xloc.file, xloc.line, xloc.column);
      rjd_fprintf("source_location: %s\n", ach);
      json_namevalue("source_location", ach);
      }
    sprintf(ach, "%d", DECL_PT_UID(node));
    rjd_fprintf("uid: %s\n", ach);
    json_namevalue("uid", ach, NOT_QUOTED);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_DECL_COMMON) )
    {
    processed[TS_DECL_COMMON] = 1;
    rjd_subtree("size(in bits)", DECL_SIZE(node));
    rjd_subtree("size_unit(in bytes)", DECL_SIZE_UNIT(node));

    const char *p;
    switch(code)
      {
      case FUNCTION_DECL:
        p = "initial(bindings)";
        break;
      case TRANSLATION_UNIT_DECL:
        p = "initial(block)";
        break;
      case VAR_DECL:
        p = "initial value";
        break;
      default:
        p = "initial";
        break;
      }
    rjd_subtree(p, DECL_INITIAL(node));
    rjd_subtree("attributes", DECL_ATTRIBUTES(node));
    rjd_subtree("abstract_origin", DECL_ABSTRACT_ORIGIN(node));

    sprintf(ach, "%s(%u)", GET_MODE_NAME(DECL_MODE(node)),(int)DECL_MODE(node));
    rjd_fprintf("machine_mode: %s\n", ach);
    json_namevalue("machine_mode", ach);

    strcpy(ach, "");
    if( DECL_NONLOCAL(node) )
      {
      strcat(ach," nonlocal");
      }
    if( DECL_VIRTUAL_P(node) )
      {
      strcat(ach," virtual");
      }
    if( DECL_IGNORED_P(node) )
      {
      strcat(ach," ignored");
      }
    if( DECL_ABSTRACT_P(node) )
      {
      strcat(ach," abstrac");
      }
    if( DECL_ARTIFICIAL(node) )
      {
      strcat(ach," artificial");
      }
    if( DECL_PRESERVE_P(node) )
      {
      strcat(ach," preserve");
      }
    if( code == VAR_DECL && DECL_DEBUG_EXPR(node) )
      {
      strcat(ach," debug_expr_is_from");
      }
    if( strlen(ach) )
      {
      rjd_fprintf("decl_flags:%s\n",ach);
      json_flags("decl_flags", ach);
      }

    if( code == FIELD_DECL )
      {
      sprintf(ach, "%u", (int)DECL_OFFSET_ALIGN(node));
      rjd_fprintf("offset_align: %s\n", ach);
      json_namevalue("offset_align", ach);
      }
    sprintf(ach, "%u", (int)DECL_ALIGN(node));
    rjd_fprintf("align: %u\n", ach);
    json_namevalue("align", ach, NOT_QUOTED);

    sprintf(ach, "%u", (int)DECL_WARN_IF_NOT_ALIGN(node));
    rjd_fprintf("warn_if_not_align: %s\n", ach);
    json_namevalue("warn_if_not_align", ach, NOT_QUOTED);

    sprintf(ach, "%u", (int)DECL_PT_UID(node));
    rjd_fprintf("pt_uid: %s\n", ach);
    json_namevalue("pt_uid", ach, NOT_QUOTED);

    if( DECL_LANG_SPECIFIC(node) )
      {
      rjd_fprintf("lang_specific(pointer): %p\n",DECL_LANG_SPECIFIC(node));
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_DECL_WRTL) )
    {
    processed[TS_DECL_WRTL] = 1;
    if( DECL_RTL_SET_P(node) )
      {
      rjd_fprintf("DECL_RTL for NODE has already been set\n");
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_DECL_WITH_VIS) )
    {
    processed[TS_DECL_WITH_VIS] = 1;
    rjd_subtree("raw_assembler_name", DECL_ASSEMBLER_NAME_RAW(node));
    if( DECL_LANG_SPECIFIC(node) )
      {
      rjd_fprintf("symtab_node(pointer): %p\n",DECL_LANG_SPECIFIC(node));
      }
    strcpy(ach, "");
    if( code == VAR_DECL )
      {
      if( DECL_DEFER_OUTPUT(node) )
        {
        strcat(ach, " defer_output");
        }
      if( DECL_HARD_REGISTER(node) )
        {
        strcat(ach, " hard_register");
        }
      if( DECL_COMMON(node) )
        {
        strcat(ach, " common");
        }
      if( DECL_IN_TEXT_SECTION(node) )
        {
        strcat(ach, " in_text_section");
        }
      if( DECL_IN_CONSTANT_POOL(node) )
        {
        strcat(ach, " in_constant_pool");
        }
      if( DECL_DLLIMPORT_P(node) )
        {
        strcat(ach, " dllimport_flag");
        }
      }
    if( DECL_WEAK(node) )
      {
      strcat(ach, " weak_flag");
      }
    if( DECL_SEEN_IN_BIND_EXPR_P(node) )
      {
      strcat(ach, " seen_in_bind_expr");
      }
    if( DECL_COMDAT(node) )
      {
      strcat(ach, " comdat_flag");
      }
    if( DECL_VISIBILITY_SPECIFIED(node) )
      {
      strcat(ach," visibility_specified");
      }
    if( code == VAR_DECL && DECL_HAS_INIT_PRIORITY_P(node) )
      {
      strcat(ach," init_priority_p");
      }
    if(  code == FUNCTION_DECL && DECL_FINAL_P(node) )
      {
      strcat(ach," final");
      }
    if(  code == FUNCTION_DECL && DECL_STATIC_CHAIN(node) )
      {
      strcat(ach," regdecl_flag");
      }
    if( strlen(ach) )
      {
      rjd_fprintf("decl_with_vis flags:%s\n",ach);
      json_flags("decl_with_vis", ach);
      }

    const char *p = "???";
    switch( DECL_VISIBILITY(node) )
      {
      case VISIBILITY_DEFAULT:
        p = "default";
        break;
      case VISIBILITY_PROTECTED:
        p = "protected";
        break;
      case VISIBILITY_HIDDEN:
        p = "hidden";
        break;
      case VISIBILITY_INTERNAL:
        p = "internal";
        break;
      }
    rjd_fprintf("visibility: %s\n", p);
    json_namevalue("visibility", p);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_DECL_NON_COMMON) )
    {
    processed[TS_DECL_NON_COMMON] = 1;
    rjd_subtree("result", DECL_RESULT_FLD(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_FUNCTION_DECL) )
    {
    processed[TS_FUNCTION_DECL] = 1;
    if( node->function_decl.f )
      {
      rjd_fprintf("function(pointer): %p\n",node->function_decl.f);
      }

    rjd_subtree("arguments", DECL_ARGUMENTS(node));
    rjd_subtree("personality", DECL_FUNCTION_PERSONALITY(node));
    rjd_subtree("function_specific_target",
                              DECL_FUNCTION_SPECIFIC_TARGET(node));
    rjd_subtree("function_specific_optimization",
                              DECL_FUNCTION_SPECIFIC_OPTIMIZATION(node));
    const char *p = "saved_tree";
    if( code == FUNCTION_DECL )
      {
      p = "saved_tree(function_body)";
      }
    rjd_subtree(p, DECL_SAVED_TREE(node));
    rjd_subtree("vindex", DECL_VINDEX(node));

    rjd_fprintf("function_code: %d\n",node->function_decl.function_code);

    switch(DECL_BUILT_IN_CLASS(node))
      {
      case NOT_BUILT_IN:
        break;
      case BUILT_IN_FRONTEND:
        rjd_fprintf("built_in: frontend\n");
        json_namevalue("built_in", "frontend");
        break;
      case BUILT_IN_MD:
        rjd_fprintf("built_in: md\n");
        json_namevalue("built_in", "md");
        break;
      case BUILT_IN_NORMAL:
        rjd_fprintf("built_in: normal\n");
        json_namevalue("built_in", "normal");
        break;
      }
    switch(FUNCTION_DECL_DECL_TYPE(node))
      {
      case NONE:
        break;
      case OPERATOR_NEW:
        rjd_fprintf("operator_new: 1\n");
        json_namevalue("operator_new", "1", NOT_QUOTED);
        break;
      case OPERATOR_DELETE:
        rjd_fprintf("operator_delete: 1\n");
        json_namevalue("operator_delete", "1", NOT_QUOTED);
        break;
      case LAMBDA_FUNCTION:
        rjd_fprintf("lambda_function: 1\n");
        json_namevalue("lambda_function", "1", NOT_QUOTED);
        break;
      }

    strcpy(ach, "");
    ADD_FLAG(TREE_PUBLIC, "public");
    ADD_FLAG(DECL_STATIC_CONSTRUCTOR, "static_ctor_flag");
    ADD_FLAG(DECL_STATIC_DESTRUCTOR, "static_dtor_flag");
    ADD_FLAG(DECL_UNINLINABLE, "uninlinable");
    ADD_FLAG(DECL_POSSIBLY_INLINED, "possibly_inlined");
    ADD_FLAG(DECL_IS_NOVOPS, "novops_flag");
    ADD_FLAG(DECL_IS_RETURNS_TWICE, "returns_twice_flag");
    ADD_FLAG(DECL_IS_MALLOC, "malloc_flag");
    ADD_FLAG(DECL_DECLARED_INLINE_P, "declared_inline_flag");
    ADD_FLAG(DECL_NO_INLINE_WARNING_P, "no_inline_warning_flag");
    ADD_FLAG(DECL_NO_INSTRUMENT_FUNCTION_ENTRY_EXIT,
             "no_instrument_function_entry_exit");
    ADD_FLAG(DECL_NO_LIMIT_STACK, "no_limit_stack");
    if( TREE_CODE(node) == FUNCTION_DECL )
      {
      ADD_FLAG(DECL_DISREGARD_INLINE_LIMITS, "disregard_inline_limits");
      }
    ADD_FLAG(DECL_PURE_P, "pure_flag");
    ADD_FLAG(DECL_LOOPING_CONST_OR_PURE_P, "looping_const_or_pure_flag");
    ADD_FLAG(DECL_HAS_DEBUG_ARGS_P, "has_debug_args_flag");
    ADD_FLAG(DECL_FUNCTION_VERSIONED, "versioned_function");
    ADD_FLAG(DECL_IS_REPLACEABLE_OPERATOR, "replaceable_operator");
    if( strlen(ach) )
      {
      rjd_fprintf("function_flags:%s\n", ach);
      json_flags("function_flags", ach);
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_TYPE_COMMON) )
    {
    processed[TS_TYPE_COMMON] = 1;

    rjd_subtree("size(in bits)", TYPE_SIZE(node));
    rjd_subtree("size_unit(in bytes)", TYPE_SIZE_UNIT(node));
    rjd_subtree("attributes", TYPE_ATTRIBUTES(node));

    sprintf(ach, "%d", TYPE_UID(node));
    rjd_fprintf("uid: %s\n", ach);
    json_namevalue("uid", ach, NOT_QUOTED);

    if( !VECTOR_TYPE_P(node) )
      {
      sprintf(ach, "%d", TYPE_PRECISION(node));
      rjd_fprintf("precision: %s\n", ach);
      json_namevalue("precision", ach, NOT_QUOTED);
      }

    sprintf(ach, "%d", TYPE_CONTAINS_PLACEHOLDER_INTERNAL(node));
    rjd_fprintf("contains_placeholder: %d\n", ach);
    json_namevalue("contains_placeholder", ach, NOT_QUOTED);

    strcpy(ach, "");
    ADD_FLAG(TYPE_NO_FORCE_BLK,"no_force_blk_flag");
    ADD_FLAG(TYPE_NEEDS_CONSTRUCTING,"needs_constructing_flag");
    if( code == RECORD_TYPE
        || code == UNION_TYPE
        || code == QUAL_UNION_TYPE )
      {
      ADD_FLAG(TYPE_TRANSPARENT_AGGR,"transparent_aggr_flag");
      }
    ADD_FLAG(TYPE_RESTRICT, "restrict_flag");
    if( code == RECORD_TYPE
        || code == UNION_TYPE
        || code == QUAL_UNION_TYPE
        || code == ARRAY_TYPE )
      {
      ADD_FLAG(TYPE_TYPELESS_STORAGE, "typeless_storage");
      }
    ADD_FLAG(TYPE_EMPTY_P, "empty_flag");
    ADD_FLAG(TYPE_INDIVISIBLE_P, "indivisible_p");
    if( strlen(ach) )
      {
      rjd_fprintf("type_common_flags:%s\n", ach);
      json_flags("type_common_flags", ach);
      }

    sprintf(ach, "%d",  TYPE_ALIGN(node));
    rjd_fprintf("align: %s\n", ach);
    json_namevalue("align", ach);

    sprintf(ach, "%d", TYPE_WARN_IF_NOT_ALIGN(node));
    rjd_fprintf("warn_if_not_align: %s\n", ach);
    json_namevalue("warn_if_not_align", ach);

    sprintf(ach, "%d", TYPE_ALIAS_SET(node));
    rjd_fprintf("alias_set_type: %s\n", ach);
    json_namevalue("alias_set_type", ach);

    rjd_subtree("pointer_to", TYPE_POINTER_TO(node));
    rjd_subtree("reference_to", TYPE_REFERENCE_TO(node));

    rjd_subtree("canonical", TYPE_CANONICAL(node));
    rjd_subtree("next_variant", TYPE_NEXT_VARIANT(node));
    rjd_subtree("main_variant", TYPE_MAIN_VARIANT(node));
    rjd_subtree("context", TYPE_CONTEXT(node));
    rjd_subtree("name", TYPE_REFERENCE_TO(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_TYPE_NON_COMMON) )
    {
    processed[TS_TYPE_NON_COMMON] = 1;
    rjd_subtree("values", TYPE_VALUES_RAW(node));
    rjd_subtree("minval", TYPE_MIN_VALUE_RAW(node));
    rjd_subtree("maxval", TYPE_MAX_VALUE_RAW(node));
    rjd_subtree("lang_1", TYPE_LANG_SLOT_1(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_TYPE_WITH_LANG_SPECIFIC) )
    {
    processed[TS_TYPE_WITH_LANG_SPECIFIC] = 1;
    if( TYPE_LANG_SPECIFIC(node) )
      {
      rjd_fprintf("lang_type(pointer): %p\n",TYPE_LANG_SPECIFIC(node));
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_INT_CST) )
    {
    processed[TS_INT_CST] = 1;
    if( phase == 2 )
    rjd_fprintf("value: ");
    print_dec(wi::to_wide(node), ach, TYPE_SIGN(TREE_TYPE(node)));
    rjd_fprintf("%s" , ach);
    rjd_fprintf("\n");
    json_namevalue("value", ach, NOT_QUOTED);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_REAL_CST) )
    {
    bool not_quoted = false;
    processed[TS_REAL_CST] = 1;

    if(TREE_OVERFLOW(node))
      {
      strcpy(ach, " overflow ");
      }
    else
      {
      REAL_VALUE_TYPE d = TREE_REAL_CST(node);
      if(REAL_VALUE_ISINF(d))
        {
        strcpy(ach, REAL_VALUE_NEGATIVE(d) ? " -Inf" : " Inf");
        }
      else if(REAL_VALUE_ISNAN(d))
        {
        /* Print a NaN in the format [-][Q]NaN[(significand[exponent])]
         where significand is a hexadecimal string that starts with
         the 0x prefix followed by 0 if the number is not canonical
         and a non-zero digit if it is, and exponent is decimal.  */
        sprintf(ach,
                "%s%sNaN",
                d.sign ? "-" : "",
                d.signalling ? "S" : "Q");
        }
      else
        {
        real_to_decimal(ach, &d, sizeof(ach), 0, 1);
        not_quoted = true;
        }
      }

    rjd_fprintf("value: %s\n", ach);
    json_namevalue("value", ach, not_quoted);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_VEC) )
    {
    processed[TS_VEC] = 1;

    len = TREE_VEC_LENGTH(node);
    if(len)
      {
      json_start_array("tree_vector_elements");
      }
    for(i = 0; i < len; i++)
      {
      if( TREE_VEC_ELT(node, i)  )
        {
        char temp[32];
        sprintf(temp, "tree_vector_element[%d]", i);

        rjd_subtree(temp, TREE_VEC_ELT(node, i));
        json_comma = ",";
        }
      }
    if(len)
      {
      json_finish_array();
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_EXP) )
    {
    processed[TS_EXP] = 1;
    xloc = expand_location( EXPR_LOCATION(node) );
    if( xloc.file )
      {
      sprintf(ach, "%s:%d:%d",
                  xloc.file,
                  xloc.line,
                  xloc.column);
      rjd_fprintf("expression_location %s\n", ach);
      json_namevalue("expression_location", ach);
      }
    len = TREE_OPERAND_LENGTH(node);

    tree node_vars = NULL_TREE;
    tree node_body = NULL_TREE;
    tree node_block = NULL_TREE;

    if( len )
      {
      json_start_array("operands");
      }
    for(i = 0; i < len; i++)
      {
      char temp[32];
      sprintf(temp, "operand[%d]", i);

      if( code == BIND_EXPR )
        {
        switch(i)
          {
          // vars/body/block is the order they appear.  I modify that to
          // vars/block/body because that's easier for me to deal with when I
          // manually graph the connections of the results
          case 0:
            node_vars = node;
            continue;
            break;
          case 1:
            node_body = node;
            continue;
            break;
          case 2:
            node_block = node;
            continue;
            break;
          }
        }
      if( code == COMPONENT_REF )
        {
        switch(i)
          {
          case 0:
            strcpy(temp,"struct/union");
            break;
          case 1:
            strcpy(temp,"field");
            break;
          case 2:
            strcpy(temp,"offset");
            break;
          }
        }
      rjd_subtree(temp, TREE_OPERAND(node, i));
      json_comma = ",";
      }
    if( len )
      {
      json_finish_array();
      }

    // Here's where I output the block/vars/body in my preferred order
    if(node_block)
      {
      rjd_subtree("block", TREE_OPERAND(node_block, 2));
      }
    if(node_vars)
      {
      rjd_subtree("vars", TREE_OPERAND(node_vars, 0));
      }
    if(node_body)
      {
      rjd_subtree("body", TREE_OPERAND(node_body, 1));
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_LIST) )
    {
    processed[TS_LIST] = 1;
    rjd_subtree("purpose", TREE_PURPOSE(node));
    rjd_subtree("value", TREE_VALUE(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_STATEMENT_LIST) )
    {
    processed[TS_STATEMENT_LIST] = 1;

    // We have a linked list to walk:

    int i = 0;
    tree_statement_list_node *next = STATEMENT_LIST_HEAD(node);
    if( next )
      {
      json_start_array("statement_list");
      }
    while( next )
      {
      sprintf(ach,"statement_list[%d]",i++);
      rjd_subtree(ach, next->stmt);

      // By rights, this next statement, while not illegal, should
      // be regarded as immoral.
      next = next->next;
      json_comma = ",";
      }
    if( STATEMENT_LIST_HEAD(node) )
      {
      json_finish_array();
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_RESULT_DECL) )
    {
    processed[TS_RESULT_DECL] = 1;

    strcpy(ach, "");
    ADD_FLAG(DECL_BY_REFERENCE, "by_reference");
    ADD_FLAG(DECL_NONSHAREABLE, "nonshareable");
    ADD_FLAG(DECL_HAS_VALUE_EXPR_P, "has_value_expr");
    ADD_FLAG(SSA_VAR_P, "ssa_name_is_possible");
    if( strlen(ach) )
      {
      rjd_fprintf("result_flags:%s\n",ach);
      json_flags("result_flags", ach);
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_STRING) )
    {
    // First, do the text/html string:
    strcpy(ach, "");
    char ach2[8];
    processed[TS_STRING] = 1;
    const char *p = TREE_STRING_POINTER(node);
    int i = TREE_STRING_LENGTH(node); // sizeof(), not strlen()
    while(--i >= 0)
      {
      char ch = *p++;
      if(ch >= ' ' && ch < 127)
        {
        sprintf(ach2, "%c", ch);
        }
      else
        {
        sprintf(ach2, "\\%03o", ch & 0xFF);
        }
      strcat(ach, ach2);
      }
    rjd_fprintf("string: \"");
    rjd_fprintf("%s\"\n", ach);

    // Second, do the JSON string:
    strcpy(ach, "");
    p = TREE_STRING_POINTER(node);
    i = TREE_STRING_LENGTH(node); // sizeof(), not strlen()
    while(--i >= 0)
      {
      char ch = *p++;
      strcpy(ach2, "");
      switch( ch )
        {
        case '\"' :
          strcpy(ach2, "\\\"");
          break;
        case '\\' :
          strcpy(ach2, "\\\\");
          break;
        case '/' :
          strcpy(ach2, "/");
          break;
        case '\b' :
          strcpy(ach2, "\\b");
          break;
        case '\f' :
          strcpy(ach2, "\\f");
          break;
        case '\n' :
          strcpy(ach2, "\\n");
          break;
        case '\r' :
          strcpy(ach2, "\\r");
          break;
        case '\t' :
          strcpy(ach2, "\\t");
          break;
        default:
        if(ch >= ' ' && ch < 127)
          {
          sprintf(ach2, "%c", ch);
          }
        else
          {
          sprintf(ach2, "\\u%4.4x", (unsigned int)(ch & 0xFF));
          }
        }
      strcat(ach, ach2);
      }
    json_namevalue("string", ach);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_IDENTIFIER) )
    {
    processed[TS_IDENTIFIER] = 1;
    rjd_fprintf("identifier: \"%s\"\n", IDENTIFIER_POINTER(node));
    json_namevalue("identifier", IDENTIFIER_POINTER(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_BLOCK) )
    {
    processed[TS_BLOCK] = 1;

    sprintf(ach, "%u", BLOCK_NUMBER(node));
    rjd_fprintf("block_num: %u\n", ach);
    json_namevalue("block_num", ach);

    xloc = expand_location(BLOCK_SOURCE_LOCATION(node));
    if( xloc.file )
      {
      rjd_fprintf(ach, "%s:%d:%d",
                  xloc.file,
                  xloc.line,
                  xloc.column);
      rjd_fprintf("block_location_start: %s\n", ach);
      json_namevalue("block_location_start", ach);
      }

    xloc = expand_location(BLOCK_SOURCE_END_LOCATION(node));
    if( xloc.file )
      {
      rjd_fprintf(ach, "%s:%d:%d",
                  xloc.file,
                  xloc.line,
                  xloc.column);
      rjd_fprintf("block_location_end: %s\n", ach);
      json_namevalue("block_location_end", ach);
      }

    if( BLOCK_DIE(node) )
      {
      rjd_fprintf("DWARF lexical block(pointer) %p\n", BLOCK_DIE(node));
      }

    rjd_subtree("vars", BLOCK_VARS(node));

    len = BLOCK_NUM_NONLOCALIZED_VARS(node);
    if( len )
      {
      json_start_array("nonlocalized_vars");
      }
    for(i = 0; i < len; i++)
      {
      char temp[32];
      sprintf(temp, "nonlocalized_var[%d]", i);
      rjd_subtree(temp, BLOCK_NONLOCALIZED_VAR(node, i));
      json_comma = ",";
      }
    if( len )
      {
      json_finish_array();
      }

    rjd_subtree("subblocks", BLOCK_SUBBLOCKS(node));
    rjd_subtree("supercontext", BLOCK_SUPERCONTEXT(node));
    rjd_subtree("abstract_origin", BLOCK_ABSTRACT_ORIGIN(node));
    rjd_subtree("fragment_origin", BLOCK_FRAGMENT_ORIGIN(node));
    rjd_subtree("fragment_chain", BLOCK_FRAGMENT_CHAIN(node));
    rjd_subtree("chain", BLOCK_CHAIN(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_PARM_DECL) )
    {
    processed[TS_PARM_DECL] = 1;
    // The only attribute unique to TS_PARM_DECL is rtx rtl.
    // I might process it, if I knew what it was.  RJD 2021-01-29
    }

  if( CODE_CONTAINS_STRUCT(code, TS_FIELD_DECL) )
    {
    processed[TS_FIELD_DECL] = 1;
    rjd_subtree("offset", DECL_FIELD_OFFSET(node));
    rjd_subtree("bit_field_type", DECL_BIT_FIELD_TYPE(node));
    rjd_subtree("qualifier", DECL_QUALIFIER(node));
    rjd_subtree("bit_offset", DECL_FIELD_BIT_OFFSET(node));
    rjd_subtree("fcontext", DECL_FCONTEXT(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_VAR_DECL) )
    {
    processed[TS_VAR_DECL] = 1;
    strcpy(ach, "");
    ADD_FLAG(TREE_PUBLIC,"public");
    ADD_FLAG(DECL_IN_TEXT_SECTION,"in_text_section");
    ADD_FLAG(DECL_IN_CONSTANT_POOL,"in_constant_pool");
    ADD_FLAG(DECL_HARD_REGISTER,"hard_register");
    ADD_FLAG(DECL_HAS_INIT_PRIORITY_P,"init_priority_p");
    ADD_FLAG(DECL_HAS_DEBUG_EXPR_P,"debug_expr_is_from");
    ADD_FLAG(VAR_DECL_IS_VIRTUAL_OPERAND,"is_virtual_operand");
    ADD_FLAG(DECL_NONLOCAL_FRAME,"non_local_frame_structure");
    ADD_FLAG(DECL_NONALIASED,"non_aliased");
    if( strlen(ach) )
      {
      rjd_fprintf("var_decl_flags:%s\n",ach);
      json_flags("var_decl_flags", ach);
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_TYPE_DECL) )
    {
    processed[TS_TYPE_DECL] = 1;
    strcpy(ach, "");
    ADD_FLAG(TREE_PUBLIC,"public");
    ADD_FLAG(TYPE_DECL_SUPPRESS_DEBUG,"suppress_debug");
    if( strlen(ach) )
      {
      rjd_fprintf("type_decl_flags:%s\n",ach);
      json_flags("type_decl_flags", ach);
      }
    rjd_subtree("original_type", DECL_ORIGINAL_TYPE(node));
    }

  if( CODE_CONTAINS_STRUCT(code, TS_CONST_DECL) )
    {
    processed[TS_CONST_DECL] = 1;
    }

  if( CODE_CONTAINS_STRUCT(code, TS_TRANSLATION_UNIT_DECL) )
    {
    processed[TS_TRANSLATION_UNIT_DECL] = 1;
    if( TRANSLATION_UNIT_LANGUAGE(node) )
      {
      rjd_fprintf("language: %s\n", TRANSLATION_UNIT_LANGUAGE(node));
      json_namevalue("language", TRANSLATION_UNIT_LANGUAGE(node));
      }
    }

  if( CODE_CONTAINS_STRUCT(code, TS_LABEL_DECL) )
    {
    processed[TS_LABEL_DECL] = 1;

    strcpy(ach, "");
    ADD_FLAG(TREE_ADDRESSABLE,"outside_stack_levels");
    ADD_FLAG(FORCED_LABEL,"forced_label");
    ADD_FLAG(FALLTHROUGH_LABEL_P,"fallthrough_allowed");
    ADD_FLAG(SWITCH_BREAK_LABEL_P,"switch_break");
    ADD_FLAG(DECL_NONLOCAL,"nonlocal_permitted");
    if( strlen(ach) )
      {
      rjd_fprintf("label_decl_flags:%s\n",ach);
      json_flags("label_decl_flags", ach);
      }

    rjd_subtree("label_context", DECL_CONTEXT(node));

    sprintf(ach, "%d", LABEL_DECL_UID(node));
    rjd_fprintf("label_uid: %s\n", ach);
    json_namevalue("label_uid", ach);

    sprintf(ach, "%d", EH_LANDING_PAD_NR(node));
    rjd_fprintf("eh_landing_pad: %s\n", ach);
    json_namevalue("eh_landing_pad", ach);
    }

  if( CODE_CONTAINS_STRUCT(code, TS_CONSTRUCTOR) )
    {
    processed[TS_CONSTRUCTOR] = 1;

    if( CONSTRUCTOR_NO_CLEARING(node) )
      {
      rjd_fprintf("no_clearing: ON\n");
      json_namevalue("no_clearing", "true", NOT_QUOTED);
      }
    else
      {
      rjd_fprintf("no_clearing: off\n");
      json_namevalue("no_clearing", "false", NOT_QUOTED);
      }

    char temp[32];

    if( CONSTRUCTOR_NELTS(node) )
      {
      json_start_array("constructor_elts");
      }
    for(size_t i=0; i<CONSTRUCTOR_NELTS(node); i++)
      {
      constructor_elt *c_elt = CONSTRUCTOR_ELT(node, i);

      sprintf(temp, "constructor_elt[%d].index",(int)i);
      rjd_subtree(temp, c_elt->index);

      sprintf(temp, "constructor_elt[%d].value",(int)i);
      rjd_subtree(temp, c_elt->value);

      int node_number_i = find_node_in_nodes(c_elt->index);
      sprintf(ach, "{\"constructor\":{\"index_node\":%d,", node_number_i);
      json_newline();
      json_fprintf("%s", ach);
      json_comma = ",";

      int node_number_v = find_node_in_nodes(c_elt->value);
      sprintf(ach, "\"value_node\":%d}}", node_number_v);
      json_fprintf("%s", ach);
      json_comma = ",";
      }
    if( CONSTRUCTOR_NELTS(node) )
      {
      json_finish_array();
      }
    }

  // We put this next statement at the end, because it's nice when CHAIN
  // is the last thing we see:
  if( CODE_CONTAINS_STRUCT(code, TS_COMMON) )
    {
    processed[TS_COMMON] = 1;
    rjd_subtree("chain", TREE_CHAIN(node));
    }

  for(int i=0; i<64; i++)
    {
    if( required[i] && !processed[i])
      {
      /*  Arriving here means that you have encountered a tree struct
          that you don't know how to handle.  This happened to me just
          now.  The error message I see is

              structure 'parm decl': NOT PROCESSED!!!!

          What to do?

          Well, the first thing I do is look in gcc/treestruct.def for
          "parm decl".  I find that text in this line:

              DEFTREESTRUCT(TS_PARM_DECL, "parm decl")

          This tells me that the tree struct's enum code is TS_PARM_DECL

          Next, I look in gcc/tree-core.h for the text "TS_PARM_DECL". I find
          it in this line:

              struct tree_parm_decl  GTY ((tag("TS_PARM_DECL"))) parm_decl;

          This tells me the structure I need to handle is "tree_parm_decl".
          The declaration of that structure is found earlier in gcc/tree-core.h

              struct GTY(()) tree_parm_decl {
              struct tree_decl_with_rtl common;
              rtx incoming_rtl; };

          That structure has a substructure "tree_decl_with_rtl", which will
          require  its one handler.  The structure has its own specific
          attribute "rtx incoming_rtl", which we might, or might not want to
          use as a source of display information.  But, in any case, we do need
          to add code up above for handling TS_PARM_DECL structures. You'll
          find that code in the block starting with

              if( CODE_CONTAINS_STRUCT(code, TS_PARM_DECL) )
                  {...}

          For each attribute in the TS_xxx that you are working with, there is
          an accessor macro in gcc/tree.h for getting at that data.  You need
          to be using those macros; there are a lot of hints and information
          about the attribute.  For example, by searching for ".incoming_rtl"
          -- note the leading dot -- you find this commented entry in
          gcc/tree.h:

              /_* For PARM_DECL, holds an RTL for the stack slot or register
                 where the data was actually passed.  *_/
              #define DECL_INCOMING_RTL(NODE) \
               (PARM_DECL_CHECK(NODE)->parm_decl.incoming_rtl)

          We are processing a PARM_DECL node, which means that the macro
          invocation:

              DECL_INCOMING_RTL(node)

          will safely return "incoming_rtl", because the PARM_DECL_CHECK macro
          won't throw an error.

          And that's how this error message is eliminated.
          */

      rjd_fprintf("structure \'%s\': ",ts_enum_names[i]);
      rjd_fprintf("NOT PROCESSED!!!!\n" );
      fprintf(stderr, "structure \'%s\': ",ts_enum_names[i]);
      fprintf(stderr, "NOT PROCESSED!!!!\n" );
      exit(1);
      }
    }

  if( phase==2 && fhtml )
    {
    fprintf(fhtml, "</p>\n");
    }
}

void
dump_generic_nodes(const char *filename, tree root)
{
  /*  This function is called at the beginning of gimplify_function_tree() in
   *  gimplify.cc.  The 'root' parameter is supposed to be a func_decl node.
   *
   *  When the flag_dump_generic_nodes flag is true, that means the compiler was
   *  invoked with -fdump-generic-nodes, and that means we jump into action.
   *
   *  We create two files based on filename.  When filename is NULL, it gets
   *  replaced with the name of the function as extracted from the func_decl
   *  node.
   *
   *  filename.nodes is a text file.  filename.nodes.html has the same
   *  information in a hypertext file with in-file links to referenced nodes.
   *
   *  The output is a listing of all of the function's nodes and their
   *  attributes.  Here is an example of the first two nodes of a typical file:

***********************************This is NodeNumber0
(0x7f12e13b0d00) NodeNumber0
tree_code: function_decl
tree_code_class: tcc_declaration
base_flags: static public
type: NodeNumber1 function_type
name: NodeNumber6410 identifier_node "main"
context: NodeNumber107 translation_unit_decl "bigger.c"
source_location: bigger.c:7:5
uid: 3663
initial(bindings): NodeNumber6411 block
machine_mode: QI(15)
align: 8
warn_if_not_align: 0
pt_uid: 3663
raw_assembler_name: NodeNumber6410 identifier_node "main"
visibility: default
result: NodeNumber6412 result_decl
function(pointer): 0x7f12e135d508
arguments: NodeNumber6413 parm_decl "argc"
saved_tree(function_body): NodeNumber6417 statement_list
function_code: 0
function_flags: public no_instrument_function_entry_exit
***********************************This is NodeNumber1
(0x7f12e13b3d20) NodeNumber1
tree_code: function_type
tree_code_class: tcc_type
machine_mode: QI(15)
type: NodeNumber2 integer_type
address_space:0
size(in bits): NodeNumber55 uint128 8
size_unit(in bytes): NodeNumber12 uint64 1
uid: 1515
precision: 0
contains_placeholder: 0
align: 8
warn_if_not_align: 0
alias_set_type: -1
canonical: NodeNumber1 function_type
main_variant: NodeNumber1 function_type
values: NodeNumber6408 tree_list
***********************************This is NodeNumber3

  */

  if( flag_dump_generic_nodes )
    {
    GV_number_of_nodes = 0;
    char achFilename[1024];
    if( !filename )
      {
      // If, perchance, the root is a decl, use its
      // name field as the root of the output file.  This means
      // that each function_decl will result in its output file:
      // main.tags, foo.tags, bar.tags, and so on.

      if( DECL_P(root) )
        {
        filename = IDENTIFIER_POINTER(DECL_NAME(root));
        }
      }

    if( filename )
      {
      // Find the root name:
      const char *p1 = strrchr(filename,'/');
      if( p1 )
        {
        p1 += 1;
        }
      else
        {
        p1 = filename;
        }
      strcpy(achFilename,filename);
      char *p2 = strrchr(achFilename,'.');
      if( p2 )
        {
        *p2 = '\0';
        }
      strcat(achFilename,".nodes");
      ftext = fopen(achFilename, "w");
      if( !ftext )
          {
          error("Unable to open %s", achFilename);
          }
      // For reasons I don't understand this setvbuf is necessary. Without
      // it the vfprintf calls here in this routine interfere with
      // printf calls elsewhere.
      setvbuf(ftext, NULL, _IONBF, 0);

      strcat(achFilename,".html");
      fhtml = fopen(achFilename, "w");
      if( !ftext )
          {
          error("Unable to open %s", achFilename);
          }
      setvbuf(fhtml, NULL, _IONBF, 0);

      char title[1024];
      strcpy(title, "GENERIC for ");
      strcat(title, filename);
      strcat(title, "()");

      html_boilerplate(title);

      strcpy(achFilename,filename);
      p2 = strrchr(achFilename,'.');
      if( p2 )
        {
        *p2 = '\0';
        }
//      strcat(achFilename,".json");
//      fjson = fopen(achFilename, "w");
//      if( !fjson )
//          {
//          error("Unable to open %s", achFilename);
//          }
//      // For reasons I don't understand this setvbuf is necessary. Without
//      // it the vfprintf calls here in this routine interfere with
//      // printf calls elsewhere.
//      setvbuf(fjson, NULL, _IONBF, 0);
      }
    else
      {
      fprintf(  stderr,
                "%s(): Needs either a filename or a DECL_NODE\n",
                __func__);
      gcc_assert(false);
      }

    if( ftext )
      {
      phase = 1;
      rjd_print_node(root);

      phase = 2;

      // Here is the JSON "header"
      json_level = 0;
      json_comma = ",";
      json_indent();
      json_fprintf("{\n");
      json_fprintf("\"version\":\"1.0\"");

      json_newline();
      json_fprintf("\"node_count\":%d", GV_number_of_nodes);

      json_comma = ",";
      json_newline();
      json_fprintf("\"nodes\":\n");
      json_fprintf("[");

      json_level += 1;
      json_comma = "";
      for(int i=0; i<GV_number_of_nodes; i++)
        {
        json_newline();
        json_comma = ",";
        json_fprintf("{\n");
        json_indent();
        json_fprintf("\"node\":%d", i);

        rjd_print_node(nodes[i].this_node);

        json_fprintf("\n");
        json_indent();
        json_fprintf("}");
        }
      json_level -= 1;

      // Here is the JSON "trailer, that ties off the header"
      json_fprintf("\n");
      json_fprintf("]\n");
      json_fprintf("}\n");
      json_level = 1;

      fclose(ftext);
      ftext = NULL;

      html_boilerplate();
      fclose(fhtml);
      ftext = NULL;

      if(fjson){fclose(fjson);}
      ftext = NULL;
      }
    }
}
