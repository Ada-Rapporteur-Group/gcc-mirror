/* Declarations of the section header.

   Copyright (C) 2008 Free Software Foundation, Inc.
   Contributed by Kenneth Zadeck <zadeck@naturalbridge.com>

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2, or (at your option) any later
   version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.  */

#ifndef GCC_LTO_HEADER_H
#define GCC_LTO_HEADER_H

#include "target.h"
#include "cgraph.h"

/* The string that is the prefix on the section names we make for lto.
   For decls the DECL_ASSEMBLER_NAME is appended to make the section
   name for the functions and static_initializers.  For other types of
   sections a '.' and the section type are appended.  */
#define LTO_SECTION_NAME_PREFIX         ".gnu.lto_"

#define LTO_major_version 1
#define LTO_minor_version 0

/* These are all the LTO section types that are in an object file.  This
   list will grow as the number of IPA passes grows since each IPA
   pass will need its own section type to store its summary
   information.

   When adding a new section type, you must also extend the
   LTO_SECTION_NAME array in lto-section-in.c.  */
enum lto_section_type
{
  LTO_section_decls = 0,
  LTO_section_function_body,
  LTO_section_static_initializer,
  LTO_section_cgraph,
  LTO_section_ipa_pure_const,
  LTO_section_ipa_reference,
  LTO_section_symtab,
  LTO_section_wpa_fixup,
  LTO_section_opts,
  LTO_N_SECTION_TYPES		/* Must be last.  */
};

extern const char *lto_section_name[];

struct lto_header
{
  int16_t major_version;          /* LTO_major_version. */
  int16_t minor_version;          /* LTO_minor_version. */
  enum lto_section_type section_type;
};

/* The is the first part of the record in the .o file for many of the
   ipa passes.  */
struct lto_simple_header
{
  struct lto_header lto_header;   /* The header for all types of sections. */
  int32_t main_size;              /* Size of main gimple body of function.  */
  int32_t debug_main_size;        /* Size of main stream debugging information.  */
  int32_t compressed_size;
};

/* Indices to the various function, type and symbol streams. */
typedef enum {
  LTO_DECL_STREAM_TYPE = 0,		/* Must be first. */
  LTO_DECL_STREAM_FIELD_DECL,
  LTO_DECL_STREAM_FN_DECL,
  LTO_DECL_STREAM_VAR_DECL,
  LTO_DECL_STREAM_TYPE_DECL,
  LTO_DECL_STREAM_NAMESPACE_DECL,
  LTO_DECL_STREAM_LABEL_DECL,
  LTO_N_DECL_STREAMS
} lto_decl_stream_e_t;


/* Statistics gathered during LTO, WPA and LTRANS.  */
struct lto_stats_d
{
  unsigned HOST_WIDE_INT num_input_cgraph_nodes;
  unsigned HOST_WIDE_INT num_output_cgraph_nodes;
  unsigned HOST_WIDE_INT num_input_files;
  unsigned HOST_WIDE_INT num_output_files;
  unsigned HOST_WIDE_INT num_cgraph_partitions;
  unsigned HOST_WIDE_INT section_size[LTO_N_SECTION_TYPES];
  unsigned HOST_WIDE_INT num_function_bodies;
  unsigned HOST_WIDE_INT num_trees[NUM_TREE_CODES];
  unsigned HOST_WIDE_INT num_output_il_bytes;
  unsigned HOST_WIDE_INT num_compressed_il_bytes;
  unsigned HOST_WIDE_INT num_input_il_bytes;
  unsigned HOST_WIDE_INT num_uncompressed_il_bytes;
};

extern struct lto_stats_d lto_stats;

/* In lto-wpa-fixup.c  */
void lto_mark_nothrow_fndecl (tree);
void lto_fixup_nothrow_decls (void);

/* Define this symbol if you want to debug an lto stream.  This causes
   a set of redundant streams to be written into the .o files that can
   pinpoint problems where the reader is not in sync with the writers.
   The cost is a large amount of time and space, but this is the
   necessary to debug a stream protocol with little redundancy.  */
/* #define LTO_STREAM_DEBUGGING  */

#ifdef LTO_STREAM_DEBUGGING

struct lto_debug_context;

#define LTO_DEBUG_INDENT(tag) \
  lto_debug_indent (&lto_debug_context, tag)
#define LTO_DEBUG_INDENT_TOKEN(value) \
  lto_debug_indent_token (&lto_debug_context, value)
#define LTO_DEBUG_INTEGER(tag,high,low) \
  lto_debug_integer (&lto_debug_context, tag, high, low)
#define LTO_DEBUG_STRING(value,len) \
  lto_debug_string (&lto_debug_context, value, len)
#define LTO_DEBUG_TOKEN(value) \
  lto_debug_token (&lto_debug_context, value)
#define LTO_DEBUG_FN_NAME(value) \
  lto_debug_fn_name (&lto_debug_context, value)
#define LTO_DEBUG_TREE_FLAGS(code,value) \
  lto_debug_tree_flags (&lto_debug_context, code, flags)
#define LTO_DEBUG_UNDENT() \
  lto_debug_undent (&lto_debug_context)
#define LTO_DEBUG_WIDE(tag,value) \
  lto_debug_wide (&lto_debug_context, tag, value)

typedef void (*lto_debug_out) (struct lto_debug_context *context, char c);

struct lto_debug_context
{
  lto_debug_out out;
  int indent;
  void *current_data;
  void *decl_index_data;
  void *decl_data;
  void *label_data;
  void *ssa_names_data;
  void *cfg_data;
  void *main_data;
  const char *stream_name;
  const char **tag_names;
};

extern struct lto_debug_context lto_debug_context;

extern void lto_debug_indent (struct lto_debug_context *, int);
extern void lto_debug_indent_token (struct lto_debug_context *, const char *);
extern void lto_debug_integer (struct lto_debug_context *, const char *, HOST_WIDE_INT, HOST_WIDE_INT);
extern void lto_debug_string (struct lto_debug_context *, const char *, int);
extern void lto_debug_token (struct lto_debug_context *, const char *);
extern void lto_debug_fn_name (struct lto_debug_context *, const tree);
extern void lto_debug_undent (struct lto_debug_context *);
extern void lto_debug_wide (struct lto_debug_context *, const char *, HOST_WIDE_INT);

#else
#define LTO_DEBUG_INDENT(tag) (void)0
#define LTO_DEBUG_INDENT_TOKEN(value) (void)0
#define LTO_DEBUG_INTEGER(tag,high,low) (void)0
#define LTO_DEBUG_STRING(value,len) (void)0
#define LTO_DEBUG_TOKEN(value) (void)0
#define LTO_DEBUG_FN_NAME(value) (void)0
#define LTO_DEBUG_TREE_FLAGS(code, value) (void)0
#define LTO_DEBUG_UNDENT() (void)0
#define LTO_DEBUG_WIDE(tag,value) (void)0
#endif


/* Encoder data structure used to stream callgraph nodes.  */
struct lto_cgraph_encoder_d
{
  /* Map nodes to reference number. */
  struct pointer_map_t *map;

  /* Map reference number to node. */
  VEC(cgraph_node_ptr,heap) *nodes;
};

typedef struct lto_cgraph_encoder_d *lto_cgraph_encoder_t;

#endif /* lto-header.h */
