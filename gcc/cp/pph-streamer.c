/* Routines for streaming PPH data.
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

/* Return true if the given tree T is streamable.  */

static bool
pph_is_streamable (tree t ATTRIBUTE_UNUSED)
{
  /* We accept most trees.  */
  return TREE_CODE (t) != SSA_NAME
	 && (TREE_CODE (t) < OMP_PARALLEL
	     || TREE_CODE (t) > OMP_CRITICAL);
}


/* Return true if T can be emitted in the decls table as a reference.
   This should only handle C++ specific declarations.  All others are
   handled by the LTO streamer directly.  */

static bool
pph_indexable_with_decls_p (tree t)
{
  return TREE_CODE (t) == TEMPLATE_DECL;
}


/* Pre-load common tree nodes into CACHE.  These nodes are always built by
   the front end, so there is no need to pickle them.  */

static void
pph_preload_common_nodes (struct lto_streamer_cache_d *cache)
{
  unsigned i;

  for (i = itk_char; i < itk_none; i++)
    lto_streamer_cache_append (cache, integer_types[i]);

  for (i = 0; i < TYPE_KIND_LAST; i++)
    lto_streamer_cache_append (cache, sizetype_tab[i]);

  /* global_trees[] can have NULL entries in it.  Skip them.  */
  for (i = 0; i < TI_MAX; i++)
    if (global_trees[i])
      lto_streamer_cache_append (cache, global_trees[i]);

  /* c_global_trees[] can have NULL entries in it.  Skip them.  */
  for (i = 0; i < CTI_MAX; i++)
    if (c_global_trees[i])
      lto_streamer_cache_append (cache, c_global_trees[i]);
}


/* Initialize all the streamer hooks used for streaming ASTs.  */

static void
pph_hooks_init (void)
{
  lto_streamer_hooks *h = streamer_hooks_init ();
  h->name = "C++ AST";
  h->preload_common_nodes = pph_preload_common_nodes;
  h->is_streamable = pph_is_streamable;
  h->write_tree = pph_write_tree;
  h->read_tree = pph_read_tree;
  h->pack_value_fields = pph_pack_value_fields;
  h->indexable_with_decls_p = pph_indexable_with_decls_p;
  h->unpack_value_fields = pph_unpack_value_fields;
  h->alloc_tree = pph_alloc_tree;
  h->output_tree_header = pph_output_tree_header;
  h->has_unique_integer_csts_p = true;
}


/* Create a new PPH stream to be stored on the file called NAME.
   MODE is passed to fopen directly.  */

pph_stream *
pph_stream_open (const char *name, const char *mode)
{
  pph_stream *stream;
  FILE *f;

  stream = NULL;
  f = fopen (name, mode);
  if (f)
    {
      pph_hooks_init ();
      stream = XCNEW (pph_stream);
      stream->file = f;
      stream->name = xstrdup (name);
      stream->write_p = (strchr (mode, 'w') != NULL);
      if (stream->write_p)
	pph_init_write (stream);
      else
	pph_init_read (stream);
      stream->cache.v = NULL;
      stream->cache.m = pointer_map_create ();
    }

  return stream;
}


/* Close PPH stream STREAM.  Write all the ASTs to disk and deallocate
   all memory used by it.  */

void
pph_stream_close (pph_stream *stream)
{
  if (stream->write_p)
    pph_flush_buffers (stream);
  fclose (stream->file);
  stream->file = NULL;
  VEC_free (void_p, heap, stream->cache.v);
  pointer_map_destroy (stream->cache.m);
  free (stream);
}


/* Data types supported by the PPH tracer.  */
enum pph_trace_type
{
    PPH_TRACE_TREE,
    PPH_TRACE_REF,
    PPH_TRACE_UINT,
    PPH_TRACE_BYTES,
    PPH_TRACE_STRING,
    PPH_TRACE_CHAIN,
    PPH_TRACE_BITPACK
};


/* Print tracing information for STREAM on pph_logfile.  DATA is the
   memory area to display, SIZE is the number of bytes to print, TYPE
   is the kind of data to print.  */

static void
pph_trace (pph_stream *stream, const void *data, unsigned int nbytes,
		  enum pph_trace_type type)
{
  const char *op = (stream->write_p) ? "<<" : ">>";
  const char *type_s[] = { "tree", "ref", "uint", "bytes", "string", "chain",
                           "bitpack" };

  if ((type == PPH_TRACE_TREE || type == PPH_TRACE_CHAIN)
      && !data
      && flag_pph_tracer <= 3)
    return;

  fprintf (pph_logfile, "*** %s: %s%s/%u, value=",
	   stream->name, op, type_s[type], (unsigned) nbytes);

  switch (type)
    {
    case PPH_TRACE_TREE:
      {
	const_tree t = (const_tree) data;
	if (t)
	  {
	    print_generic_expr (pph_logfile, CONST_CAST (union tree_node *, t),
				0);
	    fprintf (pph_logfile, ", code=%s", tree_code_name[TREE_CODE (t)]);
	  }
	else
	  fprintf (pph_logfile, "NULL_TREE");
      }
      break;

    case PPH_TRACE_REF:
      {
	const_tree t = (const_tree) data;
	if (t)
	  {
	    print_generic_expr (pph_logfile, CONST_CAST (union tree_node *, t),
				0);
	    fprintf (pph_logfile, ", code=%s", tree_code_name[TREE_CODE (t)]);
	  }
	else
	  fprintf (pph_logfile, "NULL_TREE");
      }
      break;

    case PPH_TRACE_UINT:
      {
	unsigned int val = *((const unsigned int *) data);
	fprintf (pph_logfile, "%u (0x%x)", val, val);
      }
      break;

    case PPH_TRACE_BYTES:
      {
	size_t i;
	const char *buffer = (const char *) data;
	for (i = 0; i < MIN (nbytes, 100); i++)
	  {
	    if (ISPRINT (buffer[i]))
	      fprintf (pph_logfile, "%c", buffer[i]);
	    else
	      fprintf (pph_logfile, "[0x%02x]", (unsigned int) buffer[i]);
	  }
      }
      break;

    case PPH_TRACE_STRING:
      if (data)
	fprintf (pph_logfile, "%.*s", (int) nbytes, (const char *) data);
      else
	fprintf (pph_logfile, "<nil>");
      break;

    case PPH_TRACE_CHAIN:
      {
	const_tree t = (const_tree) data;
	print_generic_expr (pph_logfile, CONST_CAST (union tree_node *, t),
			    TDF_SLIM);
	fprintf (pph_logfile, " (%d nodes in chain)", list_length (t));
      }
      break;

    case PPH_TRACE_BITPACK:
      {
	const struct bitpack_d *bp = (const struct bitpack_d *) data;
	fprintf (pph_logfile, "0x%lx", bp->word);
      }
    break;

    default:
      gcc_unreachable ();
    }

  fputc ('\n', pph_logfile);
}


/* Show tracing information for T on STREAM.  */

void
pph_trace_tree (pph_stream *stream, tree t, bool ref_p)
{
  pph_trace (stream, t, t ? tree_code_size (TREE_CODE (t)) : 0,
		    ref_p ? PPH_TRACE_REF : PPH_TRACE_TREE);
}


/* Show tracing information for VAL on STREAM.  */

void
pph_trace_uint (pph_stream *stream, unsigned int val)
{
  pph_trace (stream, &val, sizeof (val), PPH_TRACE_UINT);
}


/* Show tracing information for NBYTES bytes of memory area DATA on
   STREAM.  */

void
pph_trace_bytes (pph_stream *stream, const void *data, size_t nbytes)
{
  pph_trace (stream, data, nbytes, PPH_TRACE_BYTES);
}


/* Show tracing information for S on STREAM.  */

void
pph_trace_string (pph_stream *stream, const char *s)
{
  pph_trace (stream, s, s ? strlen (s) : 0, PPH_TRACE_STRING);
}


/* Show tracing information for LEN bytes of S on STREAM.  */

void
pph_trace_string_with_length (pph_stream *stream, const char *s,
				     unsigned int len)
{
  pph_trace (stream, s, len, PPH_TRACE_STRING);
}


/* Show tracing information for a tree chain starting with T on STREAM.  */

void
pph_trace_chain (pph_stream *stream, tree t)
{
  pph_trace (stream, t, t ? tree_code_size (TREE_CODE (t)) : 0,
		    PPH_TRACE_CHAIN);
}


/* Show tracing information for a bitpack BP on STREAM.  */

void
pph_trace_bitpack (pph_stream *stream, struct bitpack_d *bp)
{
  pph_trace (stream, bp, sizeof (*bp), PPH_TRACE_BITPACK);
}


/* Insert DATA in STREAM's pickle cache at slot IX.  If DATA already
   existed in the cache, IX must be the same as the previous entry.  */

void
pph_cache_insert_at (pph_stream *stream, void *data, unsigned ix)
{
  void **map_slot;

  map_slot = pointer_map_insert (stream->cache.m, data);
  if (*map_slot)
    {
      /* DATA already existed in the cache.  Do nothing, but check
	 that we are trying to insert DATA in the same slot that we
	 had it in before.  */
      unsigned HOST_WIDE_INT prev_ix = (unsigned HOST_WIDE_INT) *map_slot;
      gcc_assert (prev_ix == ix);
    }
  else
    {
      *map_slot = (void *) (unsigned HOST_WIDE_INT) ix;
      if (ix + 1 > VEC_length (void_p, stream->cache.v))
	VEC_safe_grow_cleared (void_p, heap, stream->cache.v, ix + 1);
      VEC_replace (void_p, stream->cache.v, ix, data);
    }
}


/* Add pointer DATA to the pickle cache in STREAM.  On exit, *IX_P will
   contain the slot number where DATA is stored.  Return true if DATA
   already existed in the cache, false otherwise.  */

bool
pph_cache_add (pph_stream *stream, void *data, unsigned *ix_p)
{
  void **map_slot;
  unsigned ix;
  bool existed_p;

  map_slot = pointer_map_contains (stream->cache.m, data);
  if (map_slot == NULL)
    {
      existed_p = false;
      ix = VEC_length (void_p, stream->cache.v);
      pph_cache_insert_at (stream, data, ix);
    }
  else
    {
      unsigned HOST_WIDE_INT slot_ix = (unsigned HOST_WIDE_INT) *map_slot;
      gcc_assert (slot_ix == (unsigned) slot_ix);
      ix = (unsigned) slot_ix;
      existed_p = true;
    }

  *ix_p = ix;

  return existed_p;
}


/* Return the pointer at slot IX in STREAM's pickle cache.  */

void *
pph_cache_get (pph_stream *stream, unsigned ix)
{
  void *data = VEC_index (void_p, stream->cache.v, ix);
  gcc_assert (data);

  return data;
}
