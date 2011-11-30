/* Factored pre-parsed header (PPH) support for C++
   Copyright (C) 2010 Free Software Foundation, Inc.
   Contributed by Lawrence Crowl <crowl@google.com> and
   Diego Novillo <dnovillo@google.com>.

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

#ifndef GCC_CP_PPH_H
#define GCC_CP_PPH_H

#include "cp/cp-tree.h"


/* Types.  */

/* PPH streams.  */
typedef struct pph_stream pph_stream;

/* Actions associated with each symbol table entry.  These indicate
   what the reader should do when registering each entry with the
   middle-end.  */
enum pph_symtab_action {
  /* Declare this symbol with rest_of_decl_compilation.  */
  PPH_SYMTAB_DECLARE = 0x23,

  /* Expand this function with expand_or_defer_fn.  */
  PPH_SYMTAB_EXPAND
};

/* Record markers.  */
enum pph_record_marker {
  /* This record contains the physical representation of the memory data.  */
  PPH_RECORD_START = 0x23,

  /* Like PPH_RECORD_START, but the reconstructed data should not be
     added to the pickle cache (see pph_cache_should_handle).  */
  PPH_RECORD_START_NO_CACHE,

  /* Start a mutated reference.  This marker indicates that this data
     already existed in the cache for another PPH image, but it has
     mutated since it was inserted into the cache:

     - The writer will pickle the object again as if it had not
       been pickled before.

     - The reader uses this as an indication that it should not
       allocate a new object, it should simply unpickle the object on
       top of the already allocated object.  */
  PPH_RECORD_START_MUTATED,

  /* Start a merge key.  */
  PPH_RECORD_START_MERGE_KEY,

  /* Start a merge body.  */
  PPH_RECORD_START_MERGE_BODY,

  /* End of record marker.  If a record starts with PPH_RECORD_END, the
     reader should return a NULL pointer.  */
  PPH_RECORD_END,

  /* Internal reference.  This marker indicates that this data has
     been written before and it resides in the pickle cache for the
     current image.  Following this marker, the reader will find the
     cache slot where the data has been stored.  */
  PPH_RECORD_IREF,

  /* External reference.  This marker indicates that this data has
     been written before and it resides in the pickle cache for
     another image.  Following this marker, the reader will find two
     indices: (1) the index into the include table where the other
     image lives, and (2) the cache slot into that image's pickle
     cache where the data resides.  */
  PPH_RECORD_XREF,

  /* Preloaded reference. This marker indicates that this data is a preloaded
     node created by the front-end at the beginning of compilation, which we
     do not need to stream out as it will already exist on the way in.  */
  PPH_RECORD_PREF
};

/* Record type tags.  Every record saved on a PPH image contains a data
   tag to identify the data structure saved in that record.  */
enum pph_tag {
  PPH_null = 0,

  /* The tags below are named after the data types they represent.

     Note that to simplify tag management, we reserve enough
     values to fit all the tree codes.  This guarantees that for
     every tree code C and PPH tag T, (unsigned) C == (unsigned) T.

     The value PPH_any_tree is used when reading tree records.  Since
     the reader does not have enough context, it will generally not
     know what kind of tree is about to read, all it knows is that it
     should be a valid tree code.  */
  PPH_any_tree = MAX_TREE_CODES,

  /* Maintain the tags below in alphabetical order.  */
  PPH_binding_entry,
  PPH_binding_table,
  PPH_cgraph_node,
  PPH_cp_binding_level,
  PPH_cp_class_binding,
  PPH_cp_label_binding,
  PPH_cxx_binding,
  PPH_function,
  PPH_lang_decl,
  PPH_lang_type,
  PPH_language_function,
  PPH_sorted_fields_type,

  /* This tag must always be last.  */
  PPH_NUM_TAGS
};


/* Global state.  FIXME pph, get rid of these.  */

/* Log file where PPH analysis is written to.  Controlled by
   -fpph-logfile.  If this flag is not given, stdout is used.  */
extern FILE *pph_logfile;


/* Extern functions.  */

/* In pph-core.c  */
extern void pph_init (void);
extern void pph_finish (void);
extern void pph_dump_location (FILE *file, location_t loc);
extern void pph_dump_tree_name (FILE *file, tree t, int flags);
extern void pph_init_include_tree (void);

/* In pph-out.c.  */
extern void pph_out_uint (pph_stream *stream, unsigned int value);
extern void pph_out_location (pph_stream *stream, location_t loc);
extern void pph_out_tree (pph_stream *stream, tree t);
extern void pph_out_record_marker (pph_stream *stream,
			enum pph_record_marker marker, enum pph_tag tag);
void pph_add_decl_to_symtab (tree, enum pph_symtab_action, bool, bool);

/* In pph-in.c.  */
extern unsigned int pph_in_uint (pph_stream *stream);
extern location_t pph_in_location (pph_stream *stream);
extern tree pph_in_tree (pph_stream *stream);
extern enum pph_record_marker pph_in_record_marker (pph_stream *stream,
			enum pph_tag *tag_p);

/* In name-lookup.c.  */
struct binding_table_s;
void pph_out_binding_table (pph_stream *, struct binding_table_s *);
struct binding_table_s *pph_in_binding_table (pph_stream *);

/* In pt.c.  */
extern void pph_out_pending_templates_list (pph_stream *stream);
extern void pph_out_spec_entry_tables (pph_stream *stream);
extern void pph_in_pending_templates_list (pph_stream *stream);
extern void pph_in_spec_entry_tables (pph_stream *stream);


/* Inline functions.  */

/* Return true if we are generating a PPH image.  */
static inline bool
pph_writer_enabled_p (void)
{
  return pph_out_file != NULL;
}

/* Return true if PPH has been enabled.  */
static inline bool
pph_enabled_p (void)
{
  return pph_writer_enabled_p () || pph_reader_enabled_p ();
}


#endif  /* GCC_CP_PPH_H  */
