/* C++ modules.  Experimental!
   Copyright (C) 2017-2019 Free Software Foundation, Inc.
   Written by Nathan Sidwell <nathan@acm.org> while at FaceBook

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

/* Comments in this file have a non-negligible chance of being wrong
   or at least inaccurate.  Due to (a) my misunderstanding, (b)
   ambiguities that I have interpretted differently to original intent
   (c) changes in the specification, (d) my poor wording, (e) source
   changes.  */

/* (Incomplete) Design Notes

   The merged modules proposal, p1103r1, allows me to drop support for
   two different schemes.
   
   Each namespace-scope fn/var/type/namespace decl has an originating
   module.  If it comes from the current TU, it is zero.  For any
   imported declaration it is non-zero.

   Each instantiation and class member fn/var/type has an
   instantiating module.  This may be different to the containing
   class's instantiating or originating module.  This is the same
   field as the originating module, DECL_MODULE_ORIGIN.

   The originating module determines ownership of everything within
   that context, and the permisibility of redefinitions from other
   TUs.

   For simplicitly template_decls propagate their result's module.

   These decls also have a DECL_MODULE_PURVIEW_P flag, indicating
   whether the declaration was in the global module fragment or in the
   module's purview.

   The decls for a particular module are held located in a sparse
   array hanging off the ns-level binding of the name.  This is
   partitioned into two: a set of Fixed slots at the start followed by
   the sparse slots afterwards.  By construction we only need to
   append new slots to the end -- there is never a need to insert in
   the middle.  The fixed slots are MODULE_SLOT_CURRENT for the
   current TU (regardless of whether it is a module or not),
   MODULE_SLOT_GLOBAL and MODULE_SLOT_PARTITION.  These latter two
   slots are used for merging entities across the global module and
   module partitions respectively.  MODULE_SLOT_PARTITION is only
   present in a module.  Neither slot is searched during name lookup
   -- they are internal use only.  This vector is created lazily once
   we require it, if there is only a declaration from the current TU, a
   regular binding is present.  It is converted on demand.

   OPTIMIZATION: Outside of the current TU, we only need ADL to work.
   We could optimize regular lookup for the current TU by glomming all
   the visible decls on its slot.  Perhaps wait until design is a
   little more settled though.

   There is only one instance of each extern-linkage namespace.  It
   appears in every module slot that makes it visible.  It also
   appears in MODULE_SLOT_GLOBAL. (it is an ODR violation if they
   collide with some other global module entity.)  We also have an
   optimization that shares the slot for adjacent modules that declare
   the same such namespace.

   A module interface compilation produces a Compiled Module Interface
   (CMI).  I use ELROND format, which allows a bunch of named sections
   containing arbitrary data.  Although I don't defend against
   actively hostile CMIs, there is some checksumming involved to
   verify data integrity.  When dumping out an interface, we generate
   a list of all the namespace-scope DECLS that are needed.  From that
   we determine the strongly connected components (SCC) within this
   TU.  Each SCC is dumped to a separate section of the CMI.  We
   generate a binding table section, mapping each namespace&name to a
   defining section.  This allows lazy loading.

   We do not separate declarations and definitions.  My guess is that
   if you refer to the declaration, you'll also need the definition
   (template body, inline function, class definition etc).  But this
   does mean we can get larger SCCs than if we separated them.  It is
   unclear whether this is a win or not.

   Notice this means we embed section indices into the contents of
   other sections.  Thus random manipulation of the CMI file by ELF
   tools may well break it.  The kosher way would probably be to
   introduce indirection via section symbols, but that would require
   defining a relocation type.

   References to decls not in the same SCC are by two different
   mechanisms.

   The simplest is for extern or module linkage entities, which are by
   context, name, module & overload index.  We look in exactly that
   scope, get the specified module binding and element from the
   overload set (or type).  Getting the module binding might cause
   lazy loading of that module's binding.

   There are some entities are unnameable -- a local type returned
   by a function (eg, a lambda).  These types must be referencable by
   importing modules.  We construct a per-module vector of such types
   and refer to them by index.

   Notice that lazy loading of one module's binding can cause lazy
   loading of other bindings of the same or other modules.  Clearly we
   want to avoid loops.  In a correct program there can be no loops in
   the module dependency graph, and the above-mentioned SCC algorithm
   places all intra-module circular dependencies in the same SCC.  It
   also orders the SCCs wrt each other, so dependent SCCs come first.
   As we load dependent modules first, we know there can be no
   reference to a higher-numbered module, and because we write out
   dependent SCCs first likewise for SCCs within the module.  This
   allows us to immediately detect broken references.

Classes used:

   dumper - logger

   data - buffer

   bytes - data streamer
   bytes_in : bytes - scalar reader
   bytes_out : bytes - scalar writer

   elf - ELROND format
   elf_in : elf - ELROND reader
   elf_out : elf - ELROND writer

   trees_in : bytes_in - tree reader
   trees_out : bytes_out - tree writer

   depset - dependency set
   depset::hash - hash table of depsets
   depset::tarjan - SCC determinator

   specset - specialization set
   specset::hash - hash table of specsets

   loc_spans - location map data

   module_state - module object

   slurping - data needed during loading

   macro_import - imported macro data
   macro_export - exported macro data

   module_mapper - mapper object

   The ELROND objects use mmap, for both reading and writing.  If mmap
   is unavailable, fileno IO is used to read and write blocks of data.

   The mapper object uses fileno IO to communicate with the server or
   program.   */

/* In expermental (trunk) sources, MODULE_VERSION is a #define passed
   in from the Makefile.  It records the modification date of the
   source directory -- that's the only way to stay sane.  In release
   sources, we (plan to) use the compiler's major.minor versioning.
   While the format might not change between at minor versions, it
   seems simplest to tie the two together.  There's no concept of
   inter-version compatibility.  */
#define IS_EXPERIMENTAL(V) ((V) >= (1U << 20))
#define MODULE_MAJOR(V) ((V) / 10000)
#define MODULE_MINOR(V) ((V) % 10000)
#define EXPERIMENT(A,B) (IS_EXPERIMENTAL (MODULE_VERSION) ? (A) : (B))
#ifndef MODULE_VERSION
#error "Shtopp! What are you doing? This is not ready yet."
#include "bversion.h"
#define MODULE_VERSION (BUILDING_GCC_MAJOR * 10000U + BUILDING_GCC_MINOR)
#elif !IS_EXPERIMENTAL (MODULE_VERSION)
#error "This is not the version I was looking for."
#endif

/* Mapper Protocol version.  Very new.  */
#define MAPPER_VERSION 0
#define _DEFAULT_SOURCE 1 /* To get TZ field of struct tm, if available.  */
#include "config.h"

/* Include network stuff first.  Excitingly OSX10.14 uses bcmp here, which
   we poison later!  */
#if defined (HAVE_AF_UNIX) || defined (HAVE_AF_INET6)
/* socket, connect, shutdown  */
# define NETWORKING 1
# include <sys/socket.h>
# ifdef HAVE_AF_UNIX
/* sockaddr_un  */
#  include <sys/un.h>
# endif
# include <netinet/in.h>
# ifdef HAVE_AF_INET6
/* sockaddr_in6, getaddrinfo, freeaddrinfo, gai_strerror, ntohs, htons.  */
#  include <netdb.h>
# endif
#endif
#ifndef HAVE_AF_INET6
# define gai_strerror(X) ""
#endif

#include "system.h"
#include "coretypes.h"
#include "cp-tree.h"
#include "timevar.h"
#include "stringpool.h"
#include "dumpfile.h"
#include "bitmap.h"
#include "cgraph.h"
#include "tree-iterator.h"
#include "cpplib.h"
#include "mkdeps.h"
#include "incpath.h"
#include "libiberty.h"
#include "stor-layout.h"
#include "version.h"
#include "tree-diagnostic.h"
#include "toplev.h"
#include "opts.h"
#include "attribs.h"
#include "intl.h"
#include "langhooks.h"

#if HAVE_MMAP_FILE && _POSIX_MAPPED_FILES > 0
/* mmap, munmap.  */
#define MAPPED_READING 1
#if HAVE_SYSCONF && defined (_SC_PAGE_SIZE)
/* msync, sysconf (_SC_PAGE_SIZE), ftruncate  */
/* posix_fallocate used if available.  */
#define MAPPED_WRITING 1
#else
#define MAPPED_WRITING 0
#endif
#else
#define MAPPED_READING 0
#define MAPPED_WRITING 0
#endif

#ifndef HAVE_MEMRCHR
/* Some unfortunate souls do not have memrchr.
   Everyone is fighting a struggle you know nothing about.  */
static void *
memrchr (void *s_, int c, size_t n)
{
  unsigned char *s = (unsigned char *)s_;
  while (n--)
    if (s[n] == c)
      return &s[n];
  return NULL;
}
#endif
#ifndef HAVE_SIGHANDLER_T
typedef void (*sighandler_t) (int);
#endif

static inline cpp_hashnode *cpp_node (tree id)
{
  return CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT (id));
}
static inline tree identifier (cpp_hashnode *node)
{
  return HT_IDENT_TO_GCC_IDENT (HT_NODE (node));
}
static inline const_tree identifier (const cpp_hashnode *node)
{
  return identifier (const_cast <cpp_hashnode *> (node));
}

/* Id for dumping module information.  */
int module_dump_id;

/* We have a special module owner.  */
#define MODULE_UNKNOWN (unsigned short)(~0U)    /* Not yet known.  */
#define MODULE_UNKNOWN_PARTITION (MODULE_UNKNOWN - 1)
#define MODULE_LIMIT (1 << MODULE_BITS < MODULE_UNKNOWN \
		      ? 1 << MODULE_BITS : MODULE_UNKNOWN_PARTITION)

/* Prefix for section names.  */
#define MOD_SNAME_PFX ".gnu.c++"

/* Format a version for user consumption.  */

typedef char verstr_t[32];
static void
version2string (unsigned version, verstr_t &out)
{
  unsigned major = MODULE_MAJOR (version);
  unsigned minor = MODULE_MINOR (version);

  if (IS_EXPERIMENTAL (version))
    sprintf (out, "%04u/%02u/%02u-%02u:%02u%s",
	     2000 + major / 10000, (major / 100) % 100, (major % 100),
	     minor / 100, minor % 100,
	     EXPERIMENT ("", " (experimental)"));
  else
    sprintf (out, "%u.%u", major, minor);
}

/* Include files to note translation for.  */
static vec<const char *, va_heap, vl_embed> *note_includes;

/* Traits to hash an arbitrary pointer.  Entries are not deletable,
   and removal is a noop (removal needed upon destruction).  */
template <typename T>
struct nodel_ptr_hash : pointer_hash<T>, typed_noop_remove <T *> {
  /* Nothing is deletable.  Everything is insertable.  */
  static bool is_deleted (T *) { return false; }
  static void mark_deleted (T *) { gcc_unreachable (); }
};

/* Map from pointer to signed integer.   */
typedef simple_hashmap_traits<nodel_ptr_hash<void>, int> ptr_int_traits;
typedef hash_map<void *,signed,ptr_int_traits> ptr_int_hash_map;

/********************************************************************/
/* Basic streaming & ELF.  Serialization is usually via mmap.  For
   writing we slide a buffer over the output file, syncing it
   approproiately.  For reading we simply map the whole file (as a
   file-backed read-only map -- it's just address space, leaving the
   OS pager to deal with getting the data to us).  Some buffers need
   to be more conventional malloc'd contents.   */

/* Variable length buffer.  */

class data {
public:
  class allocator {
  public:
    /* Tools tend to moan if the dtor's not virtual.  */
    virtual ~allocator () {}

    void grow (data &obj, unsigned needed, bool exact);
    void shrink (data &obj);
    virtual char *grow (char *ptr, unsigned needed);
    virtual void shrink (char *ptr);
  };

public:
  char *buffer;		/* Buffer being transferred.  */
  /* Although size_t would be the usual size, we know we never get
     more than 4GB of buffer -- because that's the limit of the
     encapsulation format.  And if you need bigger imports, you're
     doing it wrong.  */
  unsigned size;	/* Allocated size of buffer.  */
  unsigned pos;		/* Position in buffer.  */

public:
  data ()
    :buffer (NULL), size (0), pos (0)
  {
  }
  ~data ()
  {
    /* Make sure the derived and/or using class know what they're
       doing.  */
    gcc_checking_assert (!buffer);
  }

protected:
  char *use (unsigned count)
  {
    if (size < pos + count)
      return NULL;
    char *res = &buffer[pos];
    pos += count;
    return res;
  }

public:
  void unuse (unsigned count)
  {
    pos -= count;
  }

public:
  static allocator simple_memory;
};

/* The simple data allocator.  */
data::allocator data::simple_memory;

/* Grow buffer to at least size NEEDED.  */

void
data::allocator::grow (data &obj, unsigned needed, bool exact)
{
  gcc_checking_assert (needed ? needed > obj.size : !obj.size);
  if (!needed)
    /* Pick a default size.  */
    needed = EXPERIMENT (100, 1000);

  if (!exact)
    needed *= 2;
  obj.buffer = grow (obj.buffer, needed);
  if (obj.buffer)
    obj.size = needed;
  else
    obj.pos = obj.size = 0;
}

/* Free a buffer.  */

void
data::allocator::shrink (data &obj)
{
  shrink (obj.buffer);
  obj.buffer = NULL;
  obj.size = 0;
}

char *
data::allocator::grow (char *ptr, unsigned needed)
{
  return XRESIZEVAR (char, ptr, needed);
}

void
data::allocator::shrink (char *ptr)
{
  XDELETEVEC (ptr);
}

/* Byte streamer base.   Buffer with read/write position and smarts
   for single bits.  */

class bytes : public data {
public:
  typedef data parent;

protected:
  uint32_t bit_val;	/* Bit buffer.  */
  unsigned bit_pos;	/* Next bit in bit buffer.  */

public:
  bytes ()
    :parent (), bit_val (0), bit_pos (0)
  {}
  ~bytes () 
  {
  }

protected:
  unsigned calc_crc (unsigned) const;

protected:
  /* Finish bit packet.  Rewind the bytes not used.  */
  unsigned bit_flush ()
  {
    gcc_assert (bit_pos);
    unsigned bytes = (bit_pos + 7) / 8;
    unuse (4 - bytes);
    bit_pos = 0;
    bit_val = 0;
    return bytes;
  }
};

/* Calculate the crc32 of the buffer.  Note the CRC is stored in the
   first 4 bytes, so don't include them.  */

unsigned
bytes::calc_crc (unsigned l) const
{
  unsigned crc = 0;
  for (size_t ix = 4; ix < l; ix++)
    crc = crc32_byte (crc, buffer[ix]);
  return crc;
}

class elf_in;

/* Byte stream reader.  */

class bytes_in : public bytes {
  typedef bytes parent;

protected:
  bool overrun;  /* Sticky read-too-much flag.  */

public:
  bytes_in ()
    : parent (), overrun (false)
  {
  }
  ~bytes_in ()
  {
  }

public:
  /* Begin reading a named section.  */
  bool begin (location_t loc, elf_in *src, const char *name);
  /* Begin reading a numbered section with optional name.  */
  bool begin (location_t loc, elf_in *src, unsigned, const char * = NULL);
  /* Complete reading a buffer.  Propagate errors and return true on
     success.  */
  bool end (elf_in *src);
  /* Return true if there is unread data.  */
  bool more_p () const
  {
    return pos != size;
  }

public:
  /* Start reading at OFFSET.  */
  void random_access (unsigned offset)
  {
    if (offset > size)
      set_overrun ();
    pos = offset;
    bit_pos = bit_val = 0;
  }

public:
  void align (unsigned boundary)
  {
    if (unsigned pad = pos & (boundary - 1))
      read (boundary - pad);
  }

public:
  const char *read (unsigned count)
  {
    char *ptr = use (count);
    if (!ptr)
      set_overrun ();
    return ptr;
  }

public:
  bool check_crc () const;
  /* We store the CRC in the first 4 bytes, using host endianness.  */
  unsigned get_crc () const
  {
    return *(const unsigned *)&buffer[0];
  }

public:
  /* Manipulate the overrun flag.  */
  bool get_overrun () const
  {
    return overrun;
  }
  void set_overrun ()
  {
    overrun = true;
  }

public:
  unsigned u32 ();  	/* Read uncompressed integer.  */

public:
  bool b ();	    	/* Read a bool.  */
  void bflush ();	/* Completed a block of bools.  */

private:
  void bfill ();	/* Get the next block of bools.  */

public:
  int c ();		/* Read a char.  */
  int i ();		/* Read a signed int.  */
  unsigned u ();	/* Read an unsigned int.  */
  size_t z ();		/* Read a size_t.  */
  HOST_WIDE_INT wi ();  /* Read a HOST_WIDE_INT.  */
  unsigned HOST_WIDE_INT wu (); /* Read an unsigned HOST_WIDE_INT.  */
  const char *str (size_t * = NULL); /* Read a string.  */
  const void *buf (size_t); /* Read a fixed-length buffer.  */
  cpp_hashnode *cpp_node (); /* Read a cpp node.  */
};

/* Verify the buffer's CRC is correct.  */

bool
bytes_in::check_crc () const
{
  if (size < 4)
    return false;

  unsigned c_crc = calc_crc (size);
  if (c_crc != get_crc ())
    return false;

  return true;
}

class elf_out;

/* Byte stream writer.  */

class bytes_out : public bytes {
  typedef bytes parent;

public:
  allocator *memory;	/* Obtainer of memory.  */
  
public:
  bytes_out (allocator *memory)
    : parent (), memory (memory)
  {
  }
  ~bytes_out ()
  {
  }

public:
  bool streaming_p () const
  {
    return memory != NULL;
  }

public:
  void set_crc (unsigned *crc_ptr);

public:
  /* Begin writing, maybe reserve space for CRC.  */
  void begin (bool need_crc = true);
  /* Finish writing.  Spill to section by number.  */
  unsigned end (elf_out *, unsigned, unsigned *crc_ptr = NULL);

public:
  void align (unsigned boundary)
  {
    if (unsigned pad = pos & (boundary - 1))
      write (boundary - pad);
  }
  
public:
  char *write (unsigned count, bool exact = false)
  {
    if (size < pos + count)
      memory->grow (*this, pos + count, exact);
    return use (count);
  }

public:
  void u32 (unsigned);  /* Write uncompressed integer.  */

public:
  void b (bool);	/* Write bool.  */
  void bflush ();	/* Finish block of bools.  */

public:
  void c (unsigned char); /* Write unsigned char.  */
  void i (int);		/* Write signed int.  */
  void u (unsigned);	/* Write unsigned int.  */
  void z (size_t s);	/* Write size_t.  */
  void wi (HOST_WIDE_INT); /* Write HOST_WIDE_INT.  */
  void wu (unsigned HOST_WIDE_INT);  /* Write unsigned HOST_WIDE_INT.  */
  void str (const char *ptr)
  {
    str (ptr, strlen (ptr));
  }
  void cpp_node (const cpp_hashnode *node)
  {
    str ((const char *)NODE_NAME (node), NODE_LEN (node));
  }
  void str (const char *, size_t);  /* Write string of known length.  */
  void buf (const void *, size_t);  /* Write fixed length buffer.  */
  void *buf (size_t); /* Create a writable buffer */

public:
  /* Format a NUL-terminated raw string.  */
  void printf (const char *, ...) ATTRIBUTE_PRINTF_2;
  void print_time (const char *, const tm *, const char *);

public:
  /* Dump instrumentation.  */
  static void instrument ();

protected:
  /* Instrumentation.  */
  static unsigned spans[4];
  static unsigned lengths[4];
  static int is_set;
};

/* Instrumentation.  */
unsigned bytes_out::spans[4];
unsigned bytes_out::lengths[4];
int bytes_out::is_set = -1;

/* If CRC_PTR non-null, set the CRC of the buffer.  Mix the CRC into
   that pointed to by CRC_PTR.  */

void
bytes_out::set_crc (unsigned *crc_ptr)
{
  if (crc_ptr)
    {
      gcc_checking_assert (pos >= 4);

      unsigned crc = calc_crc (pos);
      unsigned accum = *crc_ptr;
      /* Only mix the existing *CRC_PTR if it is non-zero.  */
      accum = accum ? crc32_unsigned (accum, crc) : crc;
      *crc_ptr = accum;

      /* Buffer will be sufficiently aligned.  */
      *(unsigned *)buffer = crc;
    }
}

/* Finish a set of bools.  */

void
bytes_out::bflush ()
{
  if (bit_pos)
    {
      u32 (bit_val);
      lengths[2] += bit_flush ();
    }
  spans[2]++;
  is_set = -1;
}

void
bytes_in::bflush ()
{
  if (bit_pos)
    bit_flush ();
}

/* When reading, we don't know how many bools we'll read in.  So read
   4 bytes-worth, and then rewind when flushing if we didn't need them
   all.  You can't have a block of bools closer than 4 bytes to the
   end of the buffer.  */

void
bytes_in::bfill ()
{
  bit_val = u32 ();
}

/* Bools are packed into bytes.  You cannot mix bools and non-bools.
   You must call bflush before emitting another type.  So batch your
   bools.

   It may be worth optimizing for most bools being zero.  Some kind of
   run-length encoding?  */

void
bytes_out::b (bool x)
{
  if (is_set != x)
    {
      is_set = x;
      spans[x]++;
    }
  lengths[x]++;
  bit_val |= unsigned (x) << bit_pos++;
  if (bit_pos == 32)
    {
      u32 (bit_val);
      lengths[2] += bit_flush ();
    }
}

bool
bytes_in::b ()
{
  if (!bit_pos)
    bfill ();
  bool v = (bit_val >> bit_pos++) & 1;
  if (bit_pos == 32)
    bit_flush ();
  return v;
}

/* Exactly 4 bytes.  Used internally for bool packing and a few other
   places.  We can't simply use uint32_t because (a) alignment and
   (b) we need little-endian for the bool streaming rewinding to make
   sense.  */

void
bytes_out::u32 (unsigned val)
{
  if (char *ptr = write (4))
    {
      ptr[0] = val;
      ptr[1] = val >> 8;
      ptr[2] = val >> 16;
      ptr[3] = val >> 24;
    }
}

unsigned
bytes_in::u32 ()
{
  unsigned val = 0;
  if (const char *ptr = read (4))
    {
      val |= (unsigned char)ptr[0];
      val |= (unsigned char)ptr[1] << 8;
      val |= (unsigned char)ptr[2] << 16;
      val |= (unsigned char)ptr[3] << 24;
    }

  return val;
}

/* Chars are unsigned and written as single bytes. */

void
bytes_out::c (unsigned char v)
{
  if (char *ptr = write (1))
    *ptr = v;
}

int
bytes_in::c ()
{
  int v = 0;
  if (const char *ptr = read (1))
    v = (unsigned char)ptr[0];
  return v;
}

/* Ints 7-bit as a byte. Otherwise a 3bit count of following bytes in
   big-endian form.  4 bits are in the first byte.  */

void
bytes_out::i (int v)
{
  if (char *ptr = write (1))
    {
      if (v <= 0x3f && v >= -0x40)
	*ptr = v & 0x7f;
      else
	{
	  unsigned bytes = 0;
	  int probe;
	  if (v >= 0)
	    for (probe = v >> 8; probe > 0x7; probe >>= 8)
	      bytes++;
	  else
	    for (probe = v >> 8; probe < -0x8; probe >>= 8)
	      bytes++;
	  *ptr = 0x80 | bytes << 4 | (probe & 0xf);
	  if ((ptr = write (++bytes)))
	    for (; bytes--; v >>= 8)
	      ptr[bytes] = v & 0xff;
	}
    }
}

int
bytes_in::i ()
{
  int v = 0;
  if (const char *ptr = read (1))
    {
      v = *ptr & 0xff;
      if (v & 0x80)
	{
	  unsigned bytes = (v >> 4) & 0x7;
	  v &= 0xf;
	  if (v & 0x8)
	    v |= -1 ^ 0x7;
	  if ((ptr = read (++bytes)))
	    while (bytes--)
	      v = (v << 8) | (*ptr++ & 0xff);
	}
      else if (v & 0x40)
	v |= -1 ^ 0x3f;
    }

  return v;
}

void
bytes_out::u (unsigned v)
{
  if (char *ptr = write (1))
    {
      if (v <= 0x7f)
	*ptr = v;
      else
	{
	  unsigned bytes = 0;
	  unsigned probe;
	  for (probe = v >> 8; probe > 0xf; probe >>= 8)
	    bytes++;
	  *ptr = 0x80 | bytes << 4 | probe;
	  if ((ptr = write (++bytes)))
	    for (; bytes--; v >>= 8)
	      ptr[bytes] = v & 0xff;
	}
    }
}

unsigned
bytes_in::u ()
{
  unsigned v = 0;

  if (const char *ptr = read (1))
    {
      v = *ptr & 0xff;
      if (v & 0x80)
	{
	  unsigned bytes = (v >> 4) & 0x7;
	  v &= 0xf;
	  if ((ptr = read (++bytes)))
	    while (bytes--)
	      v = (v << 8) | (*ptr++ & 0xff);
	}
    }

  return v;
}

void
bytes_out::wi (HOST_WIDE_INT v)
{
  if (char *ptr = write (1))
    {
      if (v <= 0x3f && v >= -0x40)
	*ptr = v & 0x7f;
      else
	{
	  unsigned bytes = 0;
	  HOST_WIDE_INT probe;
	  if (v >= 0)
	    for (probe = v >> 8; probe > 0x7; probe >>= 8)
	      bytes++;
	  else
	    for (probe = v >> 8; probe < -0x8; probe >>= 8)
	      bytes++;
	  *ptr = 0x80 | bytes << 4 | (probe & 0xf);
	  if ((ptr = write (++bytes)))
	    for (; bytes--; v >>= 8)
	      ptr[bytes] = v & 0xff;
	}
    }
}

HOST_WIDE_INT
bytes_in::wi ()
{
  HOST_WIDE_INT v = 0;
  if (const char *ptr = read (1))
    {
      v = *ptr & 0xff;
      if (v & 0x80)
	{
	  unsigned bytes = (v >> 4) & 0x7;
	  v &= 0xf;
	  if (v & 0x8)
	    v |= -1 ^ 0x7;
	  if ((ptr = read (++bytes)))
	    while (bytes--)
	      v = (v << 8) | (*ptr++ & 0xff);
	}
      else if (v & 0x40)
	v |= -1 ^ 0x3f;
    }

  return v;
}

/* unsigned wide ints are just written as signed wide ints.  */

inline void
bytes_out::wu (unsigned HOST_WIDE_INT v)
{
  wi ((HOST_WIDE_INT) v);
}

inline unsigned HOST_WIDE_INT
bytes_in::wu ()
{
  return (unsigned HOST_WIDE_INT) wi ();
}

/* size_t written as unsigned or unsigned wide int.  */

inline void
bytes_out::z (size_t s)
{
  if (sizeof (s) == sizeof (unsigned))
    u (s);
  else
    wu (s);
}

inline size_t
bytes_in::z ()
{
  if (sizeof (size_t) == sizeof (unsigned))
    return u ();
  else
    return wu ();
}

/* Buffer simply memcpied.  */
void *
bytes_out::buf (size_t len)
{
  align (sizeof (void *) * 2);
  return write (len);
}

void
bytes_out::buf (const void *src, size_t len)
{
  if (void *ptr = buf (len))
    memcpy (ptr, src, len);
}

const void *
bytes_in::buf (size_t len)
{
  align (sizeof (void *) * 2);
  const char *ptr = read (len);

  return ptr;
}

/* strings as an size_t length, followed by the buffer.  Make sure
   there's a NUL terminator on read.  */

void
bytes_out::str (const char *string, size_t len)
{
  z (len);
  if (len)
    {
      gcc_checking_assert (!string[len]);
      buf (string, len + 1);
    }
}

const char *
bytes_in::str (size_t *len_p)
{
  size_t len = z ();

  /* We're about to trust some user data.  */
  if (overrun)
    len = 0;
  if (len_p)
    *len_p = len;
  const char *str = NULL;
  if (len)
    {
      str = reinterpret_cast<const char *> (buf (len + 1));
      if (!str || str[len])
	{
	  set_overrun ();
	  str = NULL;
	}
    }
  return str ? str : "";
}

cpp_hashnode *
bytes_in::cpp_node ()
{
  size_t len;
  const char *s = str (&len);
  if (!len)
    return NULL;
  return ::cpp_node (get_identifier_with_length (s, len));
}

/* Format a string directly to the buffer, including a terminating
   NUL.  Intended for human consumption.  */

void
bytes_out::printf (const char *format, ...)
{
  va_list args;
  /* Exercise buffer expansion.  */
  size_t len = EXPERIMENT (10, 500);

  while (char *ptr = write (len))
    {
      va_start (args, format);
      size_t actual = vsnprintf (ptr, len, format, args) + 1;
      va_end (args);
      if (actual <= len)
	{
	  unuse (len - actual);
	  break;
	}
      unuse (len);
      len = actual;
    }
}

void
bytes_out::print_time (const char *kind, const tm *time, const char *tz)
{
  printf ("%stime: %4u/%02u/%02u %02u:%02u:%02u %s",
	  kind, time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
	  time->tm_hour, time->tm_min, time->tm_sec, tz);
}

/* Encapsulated Lazy Records Of Named Declarations.
   Header: Stunningly Elf32_Ehdr-like
   Sections: Sectional data
     [1-N) : User data sections
     N .strtab  : strings, stunningly ELF STRTAB-like
   Index: Section table, stunningly ELF32_Shdr-like.   */

class elf {
protected:
  /* Constants used within the format.  */
  enum private_constants {
    /* File kind. */
    ET_NONE = 0,
    EM_NONE = 0,
    OSABI_NONE = 0,

    /* File format. */
    EV_CURRENT = 1,
    CLASS32 = 1,
    DATA2LSB = 1,
    DATA2MSB = 2,

    /* Section numbering.  */
    SHN_UNDEF = 0,
    SHN_LORESERVE = 0xff00,
    SHN_XINDEX = 0xffff,

    /* Section types.  */
    SHT_NONE = 0,	/* No contents.  */
    SHT_PROGBITS = 1, /* Random bytes.  */
    SHT_STRTAB = 3,	/* A string table.  */

    /* Section flags.  */
    SHF_NONE = 0x00,	/* Nothing.  */
    SHF_STRINGS = 0x20,  /* NUL-Terminated strings.  */

    /* I really hope we do not get CMI files larger than 4GB.  */
    MY_CLASS = CLASS32,
    /* It is host endianness that is relevant.  */
    MY_ENDIAN = DATA2LSB
#ifdef WORDS_BIGENDIAN
    ^ DATA2LSB ^ DATA2MSB
#endif
  };

public:
  /* Constants visible to users.  */
  enum public_constants {
    /* Special error codes.  Breaking layering a bit.  */
    E_BAD_DATA = -1,  /* Random unexpected data errors.  */
    E_BAD_LAZY = -2,  /* Badly ordered laziness.  */
    E_BAD_IMPORT = -3 /* A nested import failed.  */
  };

protected:
  /* File identification.  On-disk representation.  */
  struct ident {
    uint8_t magic[4];	/* 0x7f, 'E', 'L', 'F' */
    uint8_t klass;	/* 4:CLASS32 */
    uint8_t data;	/* 5:DATA2[LM]SB */
    uint8_t version;	/* 6:EV_CURRENT  */
    uint8_t osabi;	/* 7:OSABI_NONE */
    uint8_t abiver;	/* 8: 0 */
    uint8_t pad[7];	/* 9-15 */
  };
  /* File header.  On-disk representation.  */
  struct header {
    struct ident ident;
    uint16_t type;	/* ET_NONE */
    uint16_t machine;	/* EM_NONE */
    uint32_t version;	/* EV_CURRENT */
    uint32_t entry;	/* 0 */
    uint32_t phoff;	/* 0 */
    uint32_t shoff;	/* Section Header Offset in file */
    uint32_t flags; 
    uint16_t ehsize;	/* ELROND Header SIZE -- sizeof (header) */
    uint16_t phentsize; /* 0 */
    uint16_t phnum;	/* 0 */
    uint16_t shentsize; /* Section Header SIZE -- sizeof (section) */
    uint16_t shnum;	/* Section Header NUM */
    uint16_t shstrndx;	/* Section Header STRing iNDeX */
  };
  /* File section.  On-disk representation.  */
  struct section {
    uint32_t name;	/* String table offset.  */
    uint32_t type;	/* SHT_* */
    uint32_t flags;	/* SHF_* */
    uint32_t addr;	/* 0 */
    uint32_t offset;	/* OFFSET in file */
    uint32_t size;	/* SIZE of section */
    uint32_t link;	/* 0 */
    uint32_t info;	/* 0 */
    uint32_t addralign; /* 0 */
    uint32_t entsize;	/* ENTry SIZE, usually 0 */
  };

protected:
  data hdr;	/* The header.  */
  data sectab; 	/* The section table.  */
  data strtab;  /* String table.  */
  int fd;   	/* File descriptor we're reading or writing.  */
  int err; 	/* Sticky error code.  */

public:
  /* Construct from STREAM.  E is errno if STREAM NULL.  */
  elf (int fd, int e)
    :hdr (), sectab (), strtab (), fd (fd), err (fd >= 0 ? 0 : e)
  {}
  ~elf ()
  {
    gcc_checking_assert (fd < 0 && !hdr.buffer
			 && !sectab.buffer && !strtab.buffer);
  }

public:
  /* Return the error, if we have an error.  */
  int get_error () const
  {
    return err;
  }
  /* Set the error, unless it's already been set.  */
  void set_error (int e = E_BAD_DATA)
  {
    if (!err)
      err = e;
  }
  /* Get an error string.  */
  const char *get_error (const char *) const;

public:
  /* Begin reading/writing file.  Return false on error.  */
  bool begin () const
  {
    return !get_error ();
  }
  /* Finish reading/writing file.  Return false on error.  */
  bool end ();
};

/* Return error string.  */

const char *
elf::get_error (const char *name) const
{
  if (!name)
    return "Unknown CMI mapping";

  switch (err)
    {
    case 0:
      gcc_unreachable ();
    case E_BAD_DATA:
      return "Bad file data";
    case E_BAD_IMPORT:
      return "Bad import dependency";
    case E_BAD_LAZY:
      return "Bad lazy ordering";
    default:
      return xstrerror (err);
    }
}

/* Finish file, return true if there's an error.  */

bool
elf::end ()
{
  /* Close the stream and free the section table.  */
  if (fd >= 0 && close (fd))
    set_error (errno);
  fd = -1;

  return !get_error ();
}

/* ELROND reader.  */

class elf_in : public elf {
  typedef elf parent;

private:
  /* For freezing & defrosting.  */
#if !defined (HOST_LACKS_INODE_NUMBERS)
  dev_t device;
  ino_t inode;
#endif

public:
  elf_in (int fd, int e)
    :parent (fd, e)
  {
  }
  ~elf_in ()
  {
  }

public:
  bool is_frozen () const
  {
    return fd < 0 && hdr.pos;
  }
  bool is_freezable () const
  {
    return fd >= 0 && hdr.pos;
  }
  void freeze ();
  void defrost (const char *);

  /* If BYTES is in the mmapped area, allocate a new buffer for it.  */
  void preserve (bytes_in &bytes)
  {
#if MAPPED_READING
    if (hdr.buffer && bytes.buffer >= hdr.buffer
	&& bytes.buffer < hdr.buffer + hdr.pos)
      {
	char *buf = bytes.buffer;
	bytes.buffer = data::simple_memory.grow (NULL, bytes.size);
	memcpy (bytes.buffer, buf, bytes.size);
      }
#endif
  }
  /* If BYTES is not in SELF's mmapped area, free it.  SELF might be
     NULL. */
  static void release (elf_in *self, bytes_in &bytes)
  {
#if MAPPED_READING
    if (!(self && self->hdr.buffer && bytes.buffer >= self->hdr.buffer
	  && bytes.buffer < self->hdr.buffer + self->hdr.pos))
#endif
      data::simple_memory.shrink (bytes.buffer);
    bytes.buffer = NULL;
    bytes.size = 0;
  }

public:
  static void grow (data &data, unsigned needed)
  {
    gcc_checking_assert (!data.buffer);
#if !MAPPED_READING
    data.buffer = XNEWVEC (char, needed);
#endif
    data.size = needed;
  }
  static void shrink (data &data)
  {
#if !MAPPED_READING
    XDELETEVEC (data.buffer);
#endif
    data.buffer = NULL;
    data.size = 0;
  }

public:
  const section *get_section (unsigned s) const
  {
    if (s * sizeof (section) < sectab.size)
      return reinterpret_cast<const section *>
	(&sectab.buffer[s * sizeof (section)]);
    else
      return NULL;
  }
  unsigned get_section_limit () const
  {
    return sectab.size / sizeof (section);
  }

protected:
  const char *read (data *, unsigned, unsigned);

public:
  /* Read section by number.  */
  bool read (data *d, const section *s)
  {
    return s && read (d, s->offset, s->size);
  }

  /* Find section by name.  */
  unsigned find (const char *name);
  /* Find section by index.  */
  const section *find (unsigned snum, unsigned type = SHT_PROGBITS);

public:
  /* Release the string table, when we're done with it.  */
  void release ()
  {
    shrink (strtab);
  }

public:
  bool begin (location_t);
  bool end ()
  {
    release ();
#if MAPPED_READING
    if (hdr.buffer)
      munmap (hdr.buffer, hdr.pos);
    hdr.buffer = NULL;
#endif
    shrink (sectab);

    return parent::end ();
  }

public:
  /* Return string name at OFFSET.  Checks OFFSET range.  Always
     returns non-NULL.  We know offset 0 is an empty string.  */
  const char *name (unsigned offset)
  {
    return &strtab.buffer[offset < strtab.size ? offset : 0];
  }
};

/* ELROND writer.  */

class elf_out : public elf, public data::allocator {
  typedef elf parent;
  /* Desired section alignment on disk.  */
  static const int SECTION_ALIGN = 16;

private:
  ptr_int_hash_map identtab;	/* Map of IDENTIFIERS to strtab offsets. */
  unsigned pos;			/* Write position in file.  */
#if MAPPED_WRITING
  unsigned offset;		/* Offset of the mapping.  */
  unsigned extent;		/* Length of mapping.  */
  unsigned page_size;		/* System page size.  */
#endif

public:
  elf_out (int fd, int e)
    :parent (fd, e), identtab (500), pos (0)
  {
#if MAPPED_WRITING
    offset = extent = 0;
    page_size = sysconf (_SC_PAGE_SIZE);
    if (page_size < SECTION_ALIGN)
      /* Something really strange.  */
      set_error (EINVAL);
#endif
  }
  ~elf_out ()
  {
    data::simple_memory.shrink (hdr);
    data::simple_memory.shrink (sectab);
    data::simple_memory.shrink (strtab);
  }

#if MAPPED_WRITING
private:
  void create_mapping (unsigned ext, bool extending = true);
  void remove_mapping ();
#endif

protected:
  using allocator::grow;
  virtual char *grow (char *, unsigned needed);
#if MAPPED_WRITING
  using allocator::shrink;
  virtual void shrink (char *);
#endif

public:
  unsigned get_section_limit () const
  {
    return sectab.pos / sizeof (section);
  }

protected:
  unsigned add (unsigned type, unsigned name = 0,
		unsigned off = 0, unsigned size = 0, unsigned flags = SHF_NONE);
  unsigned write (const data &);
#if MAPPED_WRITING
  unsigned write (const bytes_out &);
#endif

public:
  /* IDENTIFIER to strtab offset.  */
  unsigned name (tree ident);
  /* String literal to strtab offset.  */
  unsigned name (const char *n);
  /* Qualified name of DECL to strtab offset.  */
  unsigned qualified_name (tree decl, bool is_defn);

private:
  unsigned strtab_write (const char *s, unsigned l);
  void strtab_write (tree decl, int);

public:
  /* Add a section with contents or strings.  */
  unsigned add (const bytes_out &, bool string_p, unsigned name);

public:
  /* Begin and end writing.  */
  bool begin ();
  bool end ();
};

/* Begin reading section NAME (of type PROGBITS) from SOURCE.
   Data always checked for CRC.  */

bool
bytes_in::begin (location_t loc, elf_in *source, const char *name)
{
  unsigned snum = source->find (name);

  return begin (loc, source, snum, name);
}

/* Begin reading section numbered SNUM with NAME (may be NULL).  */

bool
bytes_in::begin (location_t loc, elf_in *source, unsigned snum, const char *name)
{
  if (!source->read (this, source->find (snum))
      || !size || !check_crc ())
    {
      source->set_error (elf::E_BAD_DATA);
      source->shrink (*this);
      if (name)
	error_at (loc, "section %qs is missing or corrupted", name);
      else
	error_at (loc, "section #%u is missing or corrupted", snum);
      return false;
    }
  pos = 4;
  return true;
}

/* Finish reading a section.  */

bool
bytes_in::end (elf_in *src)
{
  if (more_p ())
    set_overrun ();
  if (overrun)
    src->set_error ();

  src->shrink (*this);

  return !overrun;
}

/* Begin writing buffer.  */

void
bytes_out::begin (bool need_crc)
{
  if (need_crc)
    pos = 4;
  memory->grow (*this, 0, false);
}

/* Finish writing buffer.  Stream out to SINK as named section NAME.
   Return section number or 0 on failure.  If CRC_PTR is true, crc
   the data.  Otherwise it is a string section.  */

unsigned
bytes_out::end (elf_out *sink, unsigned name, unsigned *crc_ptr)
{
  lengths[3] += pos;
  spans[3]++;

  set_crc (crc_ptr);
  unsigned sec_num = sink->add (*this, !crc_ptr, name);
  memory->shrink (*this);

  return sec_num;
}

/* Close and open the file, without destroying it.  */

void
elf_in::freeze ()
{
  gcc_checking_assert (!is_frozen ());
#if MAPPED_READING
  if (munmap (hdr.buffer, hdr.pos) < 0)
    set_error (errno);
#endif
  if (close (fd) < 0)
    set_error (errno);
  fd = -1;
}

void
elf_in::defrost (const char *name)
{
  gcc_checking_assert (is_frozen ());
  struct stat stat;

  fd = open (name, O_RDONLY | O_CLOEXEC);
  if (fd < 0 || fstat (fd, &stat) < 0)
    set_error (errno);
  else
    {
      bool ok = hdr.pos == unsigned (stat.st_size);
#ifndef HOST_LACKS_INODE_NUMBERS
      if (device != stat.st_dev
	  || inode != stat.st_ino)
	ok = false;
#endif
      if (!ok)
	set_error (EMFILE);
#if MAPPED_READING
      if (ok)
	{
	  char *mapping = reinterpret_cast<char *>
	    (mmap (NULL, hdr.pos, PROT_READ, MAP_SHARED, fd, 0));
	  if (mapping == MAP_FAILED)
	  fail:
	      set_error (errno);
	  else
	    {
	      if (madvise (mapping, hdr.pos, MADV_RANDOM))
		goto fail;

	      /* These buffers are never NULL in this case.  */
	      strtab.buffer = mapping + strtab.pos;
	      sectab.buffer = mapping + sectab.pos;
	      hdr.buffer = mapping;
	    }
	}
#endif
    }
}

/* Read at current position into BUFFER.  Return true on success.  */

const char *
elf_in::read (data *data, unsigned pos, unsigned length)
{
#if MAPPED_READING
  if (pos + length > hdr.pos)
    {
      set_error (EINVAL);
      return NULL;
    }
#else
  if (pos != ~0u && lseek (fd, pos, SEEK_SET) < 0)
    {
      set_error (errno);
      return NULL;
    }
#endif
  grow (*data, length);
#if MAPPED_READING  
  data->buffer = hdr.buffer + pos;
#else
  if (::read (fd, data->buffer, data->size) != length)
    {
      set_error (errno);
      shrink (*data);
      return NULL;
    }
#endif

  return data->buffer;
}

/* Read section SNUM of TYPE.  Return section pointer or NULL on error.  */

const elf::section *
elf_in::find (unsigned snum, unsigned type)
{
  const section *sec = get_section (snum);
  if (!snum || !sec || sec->type != type)
    return NULL;
  return sec;
}

/* Find a section NAME and TYPE.  Return section number, or zero on
   failure.  */

unsigned
elf_in::find (const char *sname)
{
  for (unsigned pos = sectab.size; pos -= sizeof (section); )
    {
      const section *sec
	= reinterpret_cast<const section *> (&sectab.buffer[pos]);

      if (0 == strcmp (sname, name (sec->name)))
	return pos / sizeof (section);
    }

  return 0;
}

/* Begin reading file.  Verify header.  Pull in section and string
   tables.  Return true on success.  */

bool
elf_in::begin (location_t loc)
{
  if (!parent::begin ())
    return false;

  struct stat stat;
  unsigned size = 0;
  if (!fstat (fd, &stat))
    {
#if !defined (HOST_LACKS_INODE_NUMBERS)
      device = stat.st_dev;
      inode = stat.st_ino;
#endif
      /* Never generate files > 4GB, check we've not been given one.  */
      if (stat.st_size == unsigned (stat.st_size))
	size = unsigned (stat.st_size);
    }

#if MAPPED_READING
  /* MAP_SHARED so that the file is backing store.  If someone else
     concurrently writes it, they're wrong.  */
  void *mapping = mmap (NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  if (mapping == MAP_FAILED)
    {
    fail:
      set_error (errno);
      return false;
    }
  /* We'll be hopping over this randomly.  */
  if (madvise (mapping, size, MADV_RANDOM))
    goto fail;

  hdr.buffer = (char *)mapping;
#else
  read (&hdr, 0, sizeof (header));
#endif
  hdr.pos = size; /* Record size of the file.  */

  const header *h = reinterpret_cast<const header *> (hdr.buffer);
  if (!h)
    return false;

  if (h->ident.magic[0] != 0x7f
      || h->ident.magic[1] != 'E'
      || h->ident.magic[2] != 'L'
      || h->ident.magic[3] != 'F')
    {
      error_at (loc, "not Encapsulated Lazy Records of Named Declarations");
    failed:
      shrink (hdr);
      return false;
    }

  /* We expect a particular format -- the ELF is not intended to be
     distributable.  */
  if (h->ident.klass != MY_CLASS
      || h->ident.data != MY_ENDIAN
      || h->ident.version != EV_CURRENT
      || h->type != ET_NONE
      || h->machine != EM_NONE
      || h->ident.osabi != OSABI_NONE)
    {
      error_at (loc, "unexpected encapsulation format or type");
      goto failed;
    }

  int e = -1;
  if (!h->shoff || h->shentsize != sizeof (section))
    {
    malformed:
      set_error (e);
      error_at (loc, "encapsulation is malformed");
      goto failed;
    }

  unsigned strndx = h->shstrndx;
  unsigned shnum = h->shnum;
  if (shnum == SHN_XINDEX)
    {
      if (!read (&sectab, h->shoff, sizeof (section)))
	{
	section_table_fail:
	  e = errno;
	  goto malformed;
	}
      shnum = get_section (0)->size;
      /* Freeing does mean we'll re-read it in the case we're not
	 mapping, but this is going to be rare.  */
      shrink (sectab);
    }

  if (!shnum)
    goto malformed;

  if (!read (&sectab, h->shoff, shnum * sizeof (section)))
    goto section_table_fail;

  if (strndx == SHN_XINDEX)
    strndx = get_section (0)->link;

  if (!read (&strtab, find (strndx, SHT_STRTAB)))
    goto malformed;

  /* The string table should be at least one byte, with NUL chars
     at either end.  */
  if (!(strtab.size && !strtab.buffer[0]
	&& !strtab.buffer[strtab.size - 1]))
    goto malformed;

#if MAPPED_READING
  /* Record the offsets of the section and string tables.  */
  sectab.pos = h->shoff;
  strtab.pos = shnum * sizeof (section);
#else
  shrink (hdr);
#endif

  return true;
}

/* Create a new mapping.  */

#if MAPPED_WRITING
void
elf_out::create_mapping (unsigned ext, bool extending)
{
#ifndef HAVE_POSIX_FALLOCATE
#define posix_fallocate(fd,off,len) ftruncate (fd, off + len)
#endif
  void *mapping = MAP_FAILED;
  if (extending && ext < 1024 * 1024)
    {
      if (!posix_fallocate (fd, offset, ext * 2))
	mapping = mmap (NULL, ext * 2, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, offset);
      if (mapping != MAP_FAILED)
	ext *= 2;
    }
  if (mapping == MAP_FAILED)
    {
      if (!extending || !posix_fallocate (fd, offset, ext))
	mapping = mmap (NULL, ext, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, offset);
      if (mapping == MAP_FAILED)
	{
	  set_error (errno);
	  mapping = NULL;
	  ext = 0;
	}
    }
#undef posix_fallocate
  hdr.buffer = (char *)mapping;
  extent = ext;
}
#endif

/* Flush out the current mapping.  */

#if MAPPED_WRITING
void
elf_out::remove_mapping ()
{
  if (hdr.buffer)
    {
      /* MS_ASYNC dtrt with the removed mapping, including a
	 subsequent overlapping remap.  */
      if (msync (hdr.buffer, extent, MS_ASYNC)
	  || munmap (hdr.buffer, extent))
	/* We're somewhat screwed at this point.  */
	set_error (errno);
    }

  hdr.buffer = NULL;
}
#endif

/* Grow a mapping of PTR to be NEEDED bytes long.  This gets
   interesting if the new size grows the EXTENT.  */

char *
elf_out::grow (char *data, unsigned needed)
{
  if (!hdr.buffer)
    return NULL;

  if (!data)
    {
      /* First allocation, align to SECTION_ALIGN now.  */
      if (unsigned padding = pos & (SECTION_ALIGN - 1))
	{
	  padding = SECTION_ALIGN - padding;
#if !MAPPED_WRITING
	  /* Align the section on disk, should help the necessary copies.
	     fseeking to extend is non-portable.  */
	  static char zero[SECTION_ALIGN];
	  if (::write (fd, &zero, padding) != padding)
	    set_error (errno);
#endif
	  pos += padding;
	}
#if MAPPED_WRITING
      data = hdr.buffer + (pos - offset);
#endif
    }

#if MAPPED_WRITING
  unsigned off = data - hdr.buffer;
  if (off + needed > extent)
    {
      /* We need to grow the mapping.  */
      unsigned lwm = off & ~(page_size - 1);
      unsigned hwm = (off + needed + page_size - 1) & ~(page_size - 1);

      gcc_checking_assert (hwm > extent);

      remove_mapping ();

      offset += lwm;
      create_mapping (extent < hwm - lwm ? hwm - lwm : extent);

      data = hdr.buffer + (off - lwm);
    }
#else
  data = allocator::grow (data, needed);
#endif

  return data;
}

#if MAPPED_WRITING
/* Shrinking is a NOP.  */
void
elf_out::shrink (char *)
{
}
#endif

/* Write S of length L to the strtab buffer.  L must include the ending
   NUL, if that's what you want.  */

unsigned
elf_out::strtab_write (const char *s, unsigned l)
{
  if (strtab.pos + l > strtab.size)
    data::simple_memory.grow (strtab, strtab.pos + l, false);
  memcpy (strtab.buffer + strtab.pos, s, l);
  unsigned res = strtab.pos;
  strtab.pos += l;
  return res;
}

/* Write qualified name of decl.  INNER >0 if this is a definition, <0
   if this is a qualifier of an outer name.  */

void
elf_out::strtab_write (tree decl, int inner)
{
  tree ctx = CP_DECL_CONTEXT (decl);
  if (TYPE_P (ctx))
    ctx = TYPE_NAME (ctx);
  if (ctx != global_namespace)
    strtab_write (ctx, -1);

  tree name = DECL_NAME (decl);
  if (!name)
    name = DECL_ASSEMBLER_NAME_RAW (decl);
  strtab_write (IDENTIFIER_POINTER (name), IDENTIFIER_LENGTH (name));

  if (inner)
    strtab_write (&"::{}"[inner+1], 2);
}

/* Map IDENTIFIER IDENT to strtab offset.  Inserts into strtab if not
   already there.  */

unsigned
elf_out::name (tree ident)
{
  unsigned res = 0;
  if (ident)
    {
      bool existed;
      int *slot = &identtab.get_or_insert (ident, &existed);
      if (!existed)
	*slot = strtab_write (IDENTIFIER_POINTER (ident),
			      IDENTIFIER_LENGTH (ident) + 1);
      res = *slot;
    }
  return res;
}

/* Map LITERAL to strtab offset.  Does not detect duplicates and
   expects LITERAL to remain live until strtab is written out.  */

unsigned
elf_out::name (const char *literal)
{
  return strtab_write (literal, strlen (literal) + 1);
}

/* Map a DECL's qualified name to strtab offset.  Does not detect
   duplicates.  */

unsigned
elf_out::qualified_name (tree decl, bool is_defn)
{
  gcc_checking_assert (DECL_P (decl) && decl != global_namespace);
  unsigned result = strtab.pos;

  strtab_write (decl, is_defn);
  strtab_write ("", 1);

  return result;
}

/* Add section to file.  Return section number.  TYPE & NAME identify
   the section.  OFF and SIZE identify the file location of its
   data.  FLAGS contains additional info.  */

unsigned
elf_out::add (unsigned type, unsigned name, unsigned off, unsigned size,
	      unsigned flags)
{
  gcc_checking_assert (!(off & (SECTION_ALIGN - 1)));
  if (sectab.pos + sizeof (section) > sectab.size)
    data::simple_memory.grow (sectab, sectab.pos + sizeof (section), false);
  section *sec = reinterpret_cast<section *> (sectab.buffer + sectab.pos);
  memset (sec, 0, sizeof (section));
  sec->type = type;
  sec->flags = flags;
  sec->name = name;
  sec->offset = off;
  sec->size = size;
  if (flags & SHF_STRINGS)
    sec->entsize = 1;

  unsigned res = sectab.pos;
  sectab.pos += sizeof (section);
  return res / sizeof (section);
}

/* Pad to the next alignment boundary, then write BUFFER to disk.
   Return the position of the start of the write, or zero on failure.   */

unsigned
elf_out::write (const data &buffer)
{
#if MAPPED_WRITING
  /* HDR is always mapped.  */
  if (&buffer != &hdr)
    {
      bytes_out out (this);
      grow (out, buffer.pos, true);
      if (out.buffer)
	memcpy (out.buffer, buffer.buffer, buffer.pos);
      shrink (out);
    }
  else
    /* We should have been aligned during the first allocation.  */
    gcc_checking_assert (!(pos & (SECTION_ALIGN - 1)));
#else
  if (::write (fd, buffer.buffer, buffer.pos) != buffer.pos)
    {
      set_error (errno);
      return 0;
    }
#endif
  unsigned res = pos;
  pos += buffer.pos;
  return res;
}

/* Write a streaming buffer.  It must be using us as an allocator.  */

#if MAPPED_WRITING
unsigned
elf_out::write (const bytes_out &buf)
{
  gcc_checking_assert (buf.memory == this);
  /* A directly mapped buffer.  */
  gcc_checking_assert (buf.buffer - hdr.buffer >= 0
		       && buf.buffer - hdr.buffer + buf.size <= extent);
  unsigned res = pos;
  pos += buf.pos;
  return res;
}
#endif

/* Write data and add section.  STRING_P is true for a string
   section, false for PROGBITS.  NAME identifies the section (0 is the
   empty name).  DATA is the contents.  Return section number or 0 on
   failure (0 is the undef section).  */

unsigned
elf_out::add (const bytes_out &data, bool string_p, unsigned name)
{
  unsigned off = write (data);

  return add (string_p ? SHT_STRTAB : SHT_PROGBITS, name,
	      off, data.pos, string_p ? SHF_STRINGS : SHF_NONE);
}

/* Begin writing the file.  Initialize the section table and write an
   empty header.  Return false on failure.  */

bool
elf_out::begin ()
{
  if (!parent::begin ())
    return false;

  /* Let the allocators pick a default.  */
  data::simple_memory.grow (strtab, 0, false);
  data::simple_memory.grow (sectab, 0, false);

  /* The string table starts with an empty string.  */
  name ("");

  /* Create the UNDEF section.  */
  add (SHT_NONE);

#if MAPPED_WRITING
  /* Start a mapping.  */
  create_mapping (EXPERIMENT (page_size,
			      (32767 + page_size) & ~(page_size - 1)));
  if (!hdr.buffer)
    return false;
#endif

  /* Write an empty header.  */
  grow (hdr, sizeof (header), true);
  header *h = reinterpret_cast<header *> (hdr.buffer);
  memset (h, 0, sizeof (header));
  hdr.pos = hdr.size;
  write (hdr);
  return !get_error ();
}

/* Finish writing the file.  Write out the string & section tables.
   Fill in the header.  Return true on error.  */

bool
elf_out::end ()
{
  if (fd >= 0)
    {
      /* Write the string table.  */
      unsigned strnam = name (".strtab");
      unsigned stroff = write (strtab);
      unsigned strndx = add (SHT_STRTAB, strnam, stroff, strtab.pos,
			     SHF_STRINGS);

      /* Store escape values in section[0].  */
      if (strndx >= SHN_LORESERVE)
	{
	  reinterpret_cast<section *> (sectab.buffer)->link = strndx;
	  strndx = SHN_XINDEX;
	}
      unsigned shnum = sectab.pos / sizeof (section);
      if (shnum >= SHN_LORESERVE)
	{
	  reinterpret_cast<section *> (sectab.buffer)->size = shnum;
	  shnum = SHN_XINDEX;
	}

      unsigned shoff = write (sectab);

#if MAPPED_WRITING
      if (offset)
	{
	  remove_mapping ();
	  offset = 0;
	  create_mapping ((sizeof (header) + page_size - 1) & ~(page_size - 1),
			  false);
	}
      unsigned length = pos;
#else
      if (lseek (fd, 0, SEEK_SET) < 0)
	set_error (errno);
#endif
      /* Write header.  */
      if (!get_error ())
	{
	  /* Write the correct header now.  */
	  header *h = reinterpret_cast<header *> (hdr.buffer);
	  h->ident.magic[0] = 0x7f;
	  h->ident.magic[1] = 'E';	/* Elrond */
	  h->ident.magic[2] = 'L';	/* is an */
	  h->ident.magic[3] = 'F';	/* elf.  */
	  h->ident.klass = MY_CLASS;
	  h->ident.data =  MY_ENDIAN;
	  h->ident.version = EV_CURRENT;
	  h->ident.osabi = OSABI_NONE;
	  h->type = ET_NONE;
	  h->machine = EM_NONE;
	  h->version = EV_CURRENT;
	  h->shoff = shoff;
	  h->ehsize = sizeof (header);
	  h->shentsize = sizeof (section);
	  h->shnum = shnum;
	  h->shstrndx = strndx;

	  pos = 0;
	  write (hdr);
	}

#if MAPPED_WRITING
      remove_mapping ();
      if (ftruncate (fd, length))
	set_error (errno);
#endif
    }

  data::simple_memory.shrink (sectab);
  data::simple_memory.shrink (strtab);

  return parent::end ();
}

/********************************************************************/

/* A dependency set.  This is used during stream out to determine the
   connectivity of the graph.  Every namespace-scope declaration that
   needs writing has a depset.  The depset is filled with the (depsets
   of) declarations within this module that it references.  For a
   declaration that'll generally be named types.  For definitions
   it'll also be declarations in the body.

   From that we can convert the graph to a DAG, via determining the
   Strongly Connected Clusters.  Each cluster is streamed
   independently, and thus we achieve lazy loading.

   Other decls that get a depset are namespaces themselves and
   unnameable declarations.   */

class depset {
private:
  tree entity;  /* Entity, or containing namespace.  */
  uintptr_t discriminator;  /* Flags or identifier.  */

public:
  /* The kinds of entity the depset could describe.  The ordering is
     significant, see cluster_cmp.  Also see entity_kind_name.  */
  enum entity_kind
  {
    EK_DECL,		/* A decl.  */
    EK_SPECIALIZATION,  /* A specialization.  */
    EK_UNNAMED,		/* An unnameable entity.  */
    EK_USING,		/* A using declaration.  */
    EK_NAMESPACE,	/* A namespace.  */
    EK_REDIRECT,	/* Redirect to a template_decl.  */
    EK_EXPLICIT_HWM,  
    EK_BINDING = EK_EXPLICIT_HWM, /* Implicitly encoded.  */
    EK_MAYBE_SPEC,	/* Potentially a specialization, else a DECL,
			   never a returned kind.  */

    EK_BITS = 3		/* Only need to encode below EK_EXPLICIT_HWM.  */
  };

private:
  /* Placement of bit fields in discriminator.  */
  enum disc_bits 
  {
    DB_ZERO_BIT, /* Set to disambiguate identifier from flags  */
    DB_SPECIAL_BIT, /* First dep slot is special.  */
    DB_KIND_BIT, /* Kind of the entity.  */
    DB_KIND_BITS = EK_BITS,
    DB_DEFN_BIT = DB_KIND_BIT + DB_KIND_BITS,
    DB_IS_INTERNAL_BIT,		/* It is an internal-linkage entity.  */
    DB_REFS_INTERNAL_BIT,	/* Refers to an internal-linkage
				   entity. */
    DB_GLOBAL_BIT,		/* Global module entity.  */
    DB_IMPORTED_BIT,		/* An imported entity.  */
    DB_PARTIAL_BIT,		/* A partial instantiation or
				   specialization.  */
    DB_UNREACHED_BIT,		/* A yet-to-be reached entity.  */
    DB_HIDDEN_BIT,		/* A hidden binding.  */
    DB_MERGEABLE_BIT,		/* An entity that needs merging.  */
    DB_PSEUDO_SPEC_BIT,		/* A non-specialization
				   specialization.  */
    DB_TYPE_SPEC_BIT,		/* Specialization from the type table.  */
    DB_BOTH_SPEC_BIT,		/* Specialization in both spec tables.  */
  };

public:
  /* The first slot is special for EK_SPECIALIZATIONS it is a
     spec_entry pointer.  It is not relevant for the SCC
     determination.  */
  vec<depset *> deps;  /* Depsets we reference.  */

public:
  unsigned cluster; /* Strongly connected cluster, later entity number  */
  unsigned section; /* Section written to.  */
  /* During SCC construction, section is lowlink, until the depset is
     removed from the stack.  See Tarjan algorithm for details.  */

private:
  /* Construction via factories.  Destruction via hash traits.  */
  depset (tree entity);
  ~depset ();

public:
  static depset *make_binding (tree, tree);
  static depset *make_entity (tree, entity_kind, bool = false);
  /* Late setting a binding name -- /then/ insert into hash!  */
  inline void set_binding_name (tree name)
  {
    gcc_checking_assert (!get_name ());
    discriminator = reinterpret_cast<uintptr_t> (name);
  }

private:
  template<unsigned I> void set_flag_bit ()
  {
    gcc_checking_assert (I < 2 || !is_binding ());
    discriminator |= 1u << I;
  }
  template<unsigned I> void clear_flag_bit ()
  {
    gcc_checking_assert (I < 2 || !is_binding ());
    discriminator &= ~(1u << I);
  }
  template<unsigned I> bool get_flag_bit () const
  {
    gcc_checking_assert (I < 2 || !is_binding ());
    return bool ((discriminator >> I) & 1);
  }
  
public:
  bool is_binding () const
  {
    return !get_flag_bit<DB_ZERO_BIT> ();
  }
  entity_kind get_entity_kind () const
  {
    if (is_binding ())
      return EK_BINDING;
    return entity_kind ((discriminator >> DB_KIND_BIT) & ((1u << EK_BITS) - 1));
  }
  const char *entity_kind_name () const;

public:
  bool has_defn () const
  {
    return get_flag_bit<DB_DEFN_BIT> ();
  }

public:
  bool is_internal () const
  {
    return get_flag_bit<DB_IS_INTERNAL_BIT> ();
  }
  bool refs_internal () const
  {
    return get_flag_bit<DB_REFS_INTERNAL_BIT> ();
  }
  bool is_global () const
  {
    return get_flag_bit<DB_GLOBAL_BIT> ();
  }
  bool is_import () const
  {
    return get_flag_bit<DB_IMPORTED_BIT> ();
  }
  bool is_unreached () const
  {
    return get_flag_bit<DB_UNREACHED_BIT> ();
  }
  bool is_partial () const
  {
    return get_flag_bit<DB_PARTIAL_BIT> ();
  }
  bool is_hidden () const
  {
    return get_flag_bit<DB_HIDDEN_BIT> ();
  }
  bool is_mergeable () const
  {
    return get_flag_bit<DB_MERGEABLE_BIT> ();
  }
  bool is_pseudo_spec () const
  {
    return get_flag_bit<DB_PSEUDO_SPEC_BIT> ();
  }
  bool is_type_spec () const
  {
    return get_flag_bit<DB_TYPE_SPEC_BIT> ();
  }

public:
  /* We set these bit outside of depset.  */
  void set_hidden_binding ()
  {
    set_flag_bit<DB_HIDDEN_BIT> ();
  }

public:
  bool is_special () const
  {
    return get_flag_bit<DB_SPECIAL_BIT> ();
  }
  void set_special ()
  {
    set_flag_bit<DB_SPECIAL_BIT> ();
  }

public:
  tree get_entity () const
  {
    return entity;
  }
  tree get_name () const
  {
    gcc_checking_assert (is_binding ());
    return reinterpret_cast <tree> (discriminator);
  }

public:
  /* Traits for a hash table of pointers to bindings.  */
  struct traits {
    /* Each entry is a pointer to a depset. */
    typedef depset *value_type;
    /* We lookup by container:maybe-identifier pair.  */
    typedef std::pair<tree,tree> compare_type;

    /* hash and equality for compare_type.  */
    inline static hashval_t hash (const compare_type &p)
    {
      hashval_t h = pointer_hash<tree_node>::hash (p.first);
      if (p.second)
	{
	  hashval_t nh = IDENTIFIER_HASH_VALUE (p.second);
	  h = iterative_hash_hashval_t (h, nh);
	}
      return h;
    }
    inline static bool equal (const value_type b, const compare_type &p)
    {
      if (b->entity != p.first)
	return false;

      if (p.second)
	return b->discriminator == reinterpret_cast<uintptr_t> (p.second);
      else
	return !b->is_binding ();
    }

    /* (re)hasher for a binding itself.  */
    inline static hashval_t hash (const value_type b)
    {
      hashval_t h = pointer_hash<tree_node>::hash (b->entity);
      if (b->is_binding ())
	{
	  hashval_t nh = IDENTIFIER_HASH_VALUE (b->get_name ());
	  h = iterative_hash_hashval_t (h, nh);
	}
      return h;
    }

    /* Empty via NULL.  */
    static inline void mark_empty (value_type &p) {p = NULL;}
    static inline bool is_empty (value_type p) {return !p;}

    /* Nothing is deletable.  Everything is insertable.  */
    static bool is_deleted (value_type) { return false; }
    static void mark_deleted (value_type) { gcc_unreachable (); }

    /* We own the entities in the hash table.  */
    static void remove (value_type p)
    {
      delete (p);
    }
  };

public:
  class hash : public hash_table<traits> {
    typedef traits::compare_type key_t;
    typedef hash_table<traits> parent;

  public:
    vec<depset *> worklist;  /* Worklist of decls to walk.  */
    depset *current;         /* Current depset being depended.  */
    bool sneakoscope;        /* Detecting dark magic (of a voldemort
				type).  */
    bool reached_unreached;  /* We reached an unreached entity.  */

  public:
    hash (size_t size)
      : parent (size), current (NULL),
	sneakoscope (false), reached_unreached (false)
    {
      worklist.create (size);
    }
    ~hash ()
    {
      worklist.release ();
    }

  private:
    depset **entity_slot (tree entity, bool = true);
    depset **binding_slot (tree ctx, tree name, bool = true);
    depset *maybe_add_declaration (tree decl);

  public:
    depset *find_entity (tree entity);
    depset *find_binding (tree ctx, tree name);

  public:
    depset *add_dependency (tree decl, entity_kind);

  private:
    depset *add_partial_redirect (depset *partial);
    bool add_binding (tree ns, tree value);

  public:  
    bool add_namespace_entities (tree ns, bitmap partitions);
    void add_specializations (bool decl_p);
    void add_class_entities (vec<tree, va_gc> *);

  public:    
    void find_dependencies ();
    bool finalize_dependencies ();
    vec<depset *> connect ();
  };

public:
  struct tarjan {
    vec<depset *> result;
    vec<depset *> stack;
    unsigned index;

    tarjan (unsigned size)
      : index (0)
    {
      result.create (size);
      stack.create (50);
    }
    ~tarjan () 
    {
      gcc_assert (!stack.length ());
      stack.release ();
    }

  public:
    void connect (depset *);
  };
};

inline
depset::depset (tree entity)
  :entity (entity), discriminator (0), cluster (0), section (0)
{
  deps.create (0);
}

inline
depset::~depset ()
{
  deps.release ();
}

const char *
depset::entity_kind_name () const
{
  /* Same order as entity_kind.  */
  static const char *const names[] = 
    {"decl", "specialization", "unnamed",
     "using", "namespace", "redirect",
     "binding"};
  entity_kind kind = get_entity_kind ();
  gcc_checking_assert (kind < sizeof (names) / sizeof(names[0]));
  return names[kind];
}

depset *depset::make_binding (tree ns, tree name)
{
  depset *r = new depset (ns);

  r->discriminator = reinterpret_cast <uintptr_t> (name);
  return r;
}

depset *depset::make_entity (tree entity, entity_kind ek, bool is_defn)
{
  depset *r = new depset (entity);

  r->discriminator = ((1 << DB_ZERO_BIT)
		      | (ek << DB_KIND_BIT)
		      | is_defn << DB_DEFN_BIT);

  return r;
}

/* Specializations that have yet to be loaded.  These are keyed to
   the name of the namespace-scope entity containing their
   most-general template.  */

class specset {
public:
  /* key  */
  tree ns;  /* Namespace containing the template.  */
  tree name;  /* Name of the entity.  */

  /* Payload.  */
  unsigned short allocp2;  /* Allocated pending  */
  unsigned num;    /* Number of pending.  */

  /* Trailing array of pending specializations.  These are indices
     into the entity array.  */
  unsigned pending[1];

public:
  /* Even with ctors, we're very pod-like.  */
  specset (tree ns, tree name)
    : ns (ns), name (name),
      allocp2 (0), num (0)
  {
  }
  specset (const specset *from)
  {
    size_t size = (offsetof (specset, pending)
		   + sizeof (specset::pending) * from->num);
    memmove (this, from, size);
    if (from->num)
      allocp2++;
  }

public:
  struct traits : delete_ptr_hash<specset> {
    /* hash and equality for compare_type.  */
    inline static hashval_t hash (const compare_type p)
    {
      hashval_t h = pointer_hash<tree_node>::hash (p->ns);
      hashval_t nh = pointer_hash<tree_node>::hash (p->name);
      h = iterative_hash_hashval_t (h, nh);

      return h;
    }
    inline static bool equal (const value_type b, const compare_type p)
    {
      if (b->ns != p->ns)
	return false;

      if (b->name != p->name)
	return false;

      return true;
    }
  };

public:
  class hash : public hash_table<traits> 
  {
    typedef traits::compare_type key_t;
    typedef hash_table<traits> parent;

  public:
    hash (size_t size)
      : parent (size)
    {
    }
    ~hash ()
    {
    }

  public:
    bool add (tree ns, tree name, unsigned index);
    specset *lookup (tree ns, tree name);
  };

  static hash *table;
};

specset::hash *specset::table;

/********************************************************************/
/* Tree streaming.   The tree streaming is very specific to the tree
   structures themselves.  A tag indicates the kind of tree being
   streamed.  -ve tags indicate backreferences to already-streamed
   trees.  Backreferences are auto-numbered.  */

/* Tree tags.  */
enum tree_tag {
  tt_null,		/* NULL_TREE.  */
  tt_fixed,		/* Fixed vector index.  */

  tt_node,		/* By-value node.  */
  tt_decl,		/* By-value mergeable decl.  */
  tt_tpl_parm,		/* Template parm.  */

  tt_id,  		/* Identifier node.  */
  tt_conv_id,		/* Conversion operator name.  */
  tt_anon_id,		/* Anonymous name.  */
  tt_lambda_id,		/* Lambda name.  */

  tt_typedef_type,	/* A (possibly implicit) typedefed type.  */
  tt_derived_type,	/* A type derived from another type.  */
  tt_variant_type,	/* A variant of another type.  */

  tt_tinfo_var,		/* Typeinfo object. */
  tt_tinfo_typedef,	/* Typeinfo typedef.  */
  tt_ptrmem_type,	/* Pointer to member type.  */

  tt_parm,		/* Function paramter or result.  */
  tt_enum_int,		/* An enum const.  */
  tt_data_member,	/* Data member or enum value.  */

  tt_namespace,		/* Namespace reference.  */
  tt_binfo,		/* A BINFO.  */
  tt_vtable,		/* A vtable.  */
  tt_thunk,		/* A thunk.  */
  tt_clone_ref,

  tt_entity,		/* A extra-cluster entity.  */

  tt_named, 	 	/* Named decl. */
  tt_implicit_template, /* An implicit member template.  */
  tt_template,		/* The TEMPLATE_RESULT of a template.  */
  tt_friend_template    /* A friend of a template class.  */
};

enum walk_kind {
  WK_none,	/* No walk to do (a back- or fixed-ref happened).  */
  WK_normal,	/* Normal walk (by-name if possible).  */

  WK_value,	/* By-value walk.  */
};

enum merge_kind
{
  MK_unique,		/* Known unique.  */
  MK_via_ctx = 0x1,	/* Found by CTX, NAME + maybe_arg types.  CTX
			   determines deduping.  */
  MK_named = 0x2,	/* Found by CTX, NAME + maybe_arg types.  */
  MK_implicit = 0x3,    /* Found by CTX, NAME + maybe_arg types.
			   Implicit member fn (cdtor/assop).  */

  MK_indirect_mask = 0x4,
  MK_local_friend = MK_indirect_mask |0x1, /* Found by container, name.  */
  MK_enum = MK_indirect_mask | 0x3,	/* Found by CTX, & 1stMemberNAME.  */

  /* Template specialization kinds below. These are all found via
     primary template and specialization args.  */
  MK_template_mask = 0x8,  /* A template specialization.  */
  MK_tmpl_decl_mask = 0x4, /* In the decl table (not the type table).  */
  MK_tmpl_both_mask = 0x2, /* ... but also in the type table.  */
  MK_tmpl_partial_mask = 0x2,  /* Partial type specialization.  */
  MK_tmpl_tmpl_mask = 0x1, /* We want TEMPLATE_DECL.  */

  MK_type_spec = MK_template_mask,
  MK_type_tmpl_spec = MK_type_spec | MK_tmpl_tmpl_mask,
  MK_type_partial_spec = MK_type_tmpl_spec | MK_tmpl_partial_mask,

  MK_decl_spec = MK_template_mask | MK_tmpl_decl_mask,
  MK_decl_tmpl_spec = MK_decl_spec | MK_tmpl_tmpl_mask,

  MK_hwm = 16
};
/* This is more than a debugging array.  NULLs are used to determine
   an invalid merge_kind number.  */
static char const *const merge_kind_name[MK_hwm] =
  {
    "unique", NULL, "named", "implicit",  /* 0...3  */
    NULL, NULL, NULL, "enum",   /* 4...7  */
    "type spec", "type tmpl spec", NULL, "type partial spec", /* 8...11  */
    "decl spec", "decl tmpl spec", "both spec", "both tmpl spec" /* 12...15  */
  };

struct nodel_decl_hash : nodel_ptr_hash<tree_node>
{
  inline static hashval_t hash (const value_type decl)
  {
    return hashval_t (DECL_UID (decl));
  }
};

typedef hash_map<tree,uintptr_t,
		 simple_hashmap_traits<nodel_decl_hash,uintptr_t> >
duplicate_hash_map;

/* Tree stream reader.  Note that reading a stream doesn't mark the
   read trees with TREE_VISITED.  Thus it's quite safe to have
   multiple concurrent readers.  Which is good, because lazy
   loading. */
class trees_in : public bytes_in {
  typedef bytes_in parent;

private:
  module_state *state;		/* Module being imported.  */
  vec<tree> back_refs;		/* Back references.  */
  duplicate_hash_map *duplicates;	/* Map from existings to duplicate.  */
  vec<tree> post_decls;		/* Decls to post process.  */

public:
  trees_in (module_state *);
  ~trees_in ();

public:
  int insert (tree);
  tree back_ref (int);

private:
  tree start (unsigned = 0);

public:
  /* Needed for binfo writing  */
  bool core_bools (tree);

private:
  /* Stream tree_core, lang_decl_specific and lang_type_specific
     bits.  */
  bool core_vals (tree);
  bool lang_type_bools (tree);
  bool lang_type_vals (tree);
  bool lang_decl_bools (tree);
  bool lang_decl_vals (tree);
  bool lang_vals (tree);
  tree tree_binfo ();
  bool tree_node_bools (tree);
  bool tree_node_vals (tree);
  tree tree_value ();
  tree decl_value ();
  tree tpl_parm_value ();

private:
  tree chained_decls ();  /* Follow DECL_CHAIN.  */
  vec<tree, va_gc> *tree_vec (); /* vec of tree.  */
  vec<tree_pair_s, va_gc> *tree_pair_vec (); /* vec of tree_pair.  */

public:
  /* Read a tree node.  */
  tree tree_node ();

private:
  tree tpl_parms (unsigned &tpl_levels);
  bool tpl_parms_fini (tree decl, unsigned tpl_levels);
  bool tpl_header (tree decl, unsigned *tpl_levels);
  tree fn_arg_types ();
  int fn_parms_init (tree);
  void fn_parms_fini (int tag, tree fn, tree existing, bool has_defn);
  unsigned add_indirect_tpl_parms (tree);
public:
  bool add_indirects (tree);

public:
  /* Serialize various definitions. */
  bool read_definition (tree decl);
  
private:
  bool is_matching_decl (tree existing, tree node);
  bool read_function_def (tree decl, tree maybe_template);
  bool read_var_def (tree decl, tree maybe_template);
  bool read_class_def (tree decl, tree maybe_template);
  bool read_enum_def (tree decl, tree maybe_template);

public:
  bool key_mergeable (merge_kind, tree, tree, tree,
		      tree *, tree *, tree *, tree *);

private:
  uintptr_t *find_duplicate (tree existing);

public:
  void register_duplicate (tree decl, tree existing);
  void unmatched_duplicate (tree existing)
  {
    *find_duplicate (existing) |= 1;
  }

  enum dupness
  {
    DUP_new,
    DUP_dup,
    DUP_bad
  };
  dupness get_dupness (tree decl);

  enum odrness
  {
    ODR_new,  /* A new entity, absorb it.  */
    ODR_check, /* A duplicate entity, check it.  */
    ODR_ignore /* A duplicate entity, ignore it. */
  };
  odrness get_odrness (tree decl, bool has_existing_defn);

public:
  /* Return the next decl to postprocess, or NULL.  */
  tree post_process ()
  {
    return post_decls.length () ? post_decls.pop () : NULL_TREE;
  }
private:
  /* Register DECL for postprocessing.  */
  void post_process (tree decl)
  {
    post_decls.safe_push (decl);
  }

private:
  void assert_definition (tree, odrness);
};

trees_in::trees_in (module_state *state)
  :parent (), state (state)
{
  duplicates = NULL;
  back_refs.create (500);
  post_decls.create (0);
}

trees_in::~trees_in ()
{
  delete (duplicates);
  back_refs.release ();
  post_decls.release ();
}

/* Tree stream writer.  */
class trees_out : public bytes_out {
  typedef bytes_out parent;

private:
  module_state *state;		/* The module we are writing.  */
  ptr_int_hash_map tree_map; 	/* Trees to references */
  depset::hash *dep_hash;    	/* Dependency table.  */
  int ref_num;			/* Back reference number.  */
  unsigned section;

public:
  trees_out (allocator *, module_state *, depset::hash &deps, unsigned sec = 0);
  ~trees_out ();

private:
  void mark_trees ();
  void unmark_trees ();

public:
  void begin ();
  unsigned end (elf_out *sink, unsigned name, unsigned *crc_ptr);
  void end ();

public:
  enum tags 
  {
    tag_backref = -1,	/* Upper bound on the backrefs.  */
    tag_value = 0,	/* Write by value.  */
    tag_fixed		/* Lower bound on the fixed trees.  */
  };

public:
  int insert (tree, walk_kind = WK_normal);

private:
  void start (tree, bool = false);

private:
  walk_kind ref_node (tree);

private:
  void core_bools (tree);
  void core_vals (tree);
  void lang_type_bools (tree);
  void lang_type_vals (tree);
  void lang_decl_bools (tree);
  void lang_decl_vals (tree);
  void lang_vals (tree);
  tree tree_binfo (tree, int, bool);
  void tree_node_bools (tree);
  void tree_node_vals (tree);

private:
  void chained_decls (tree);
  void tree_vec (vec<tree, va_gc> *);
  void tree_pair_vec (vec<tree_pair_s, va_gc> *);

public:
  /* Mark a node for by-value walking.  */
  void mark_by_value (tree);

public:
  void tree_node (tree);

private:
  void tpl_parms (tree parms, unsigned &tpl_levels);
  void tpl_parms_fini (tree decl, unsigned tpl_levels);
  void fn_arg_types (tree);
  void fn_parms_fini (tree) {}
  unsigned add_indirect_tpl_parms (tree);
public:
  void add_indirects (tree);
  void fn_parms_init (tree);
  void tpl_header (tree decl, unsigned *tpl_levels);

public:
  merge_kind get_merge_kind (depset *);
  tree get_container (tree decl);
  void key_mergeable (merge_kind, depset *, tree decl);

private:
  bool decl_node (tree, walk_kind ref);
  void type_node (tree);
  void tree_value (tree);
  void decl_value (tree, depset *);
  void tpl_parm_value (tree);

public:
  /* Serialize various definitions. */
  void write_definition (tree decl);
  void mark_declaration (tree decl, bool do_defn);

private:
  void mark_function_def (tree decl);
  void mark_var_def (tree decl);
  void mark_class_def (tree decl);
  void mark_enum_def (tree decl);
  void mark_class_member (tree decl, bool do_defn = true);
  void mark_binfos (tree type);

private:
  void write_var_def (tree decl);
  void write_function_def (tree decl);
  void write_class_def (tree decl);
  void write_enum_def (tree decl);

private:
  static void assert_definition (tree);

public:
  static void instrument ();

private:
  /* Tree instrumentation. */
  static unsigned tree_val_count;
  static unsigned decl_val_count;
  static unsigned back_ref_count;
  static unsigned null_count;
};

/* Instrumentation counters.  */
unsigned trees_out::tree_val_count;
unsigned trees_out::decl_val_count;
unsigned trees_out::back_ref_count;
unsigned trees_out::null_count;

trees_out::trees_out (allocator *mem, module_state *state, depset::hash &deps,
		      unsigned section)
  :parent (mem), state (state), tree_map (500),
   dep_hash (&deps), ref_num (0), section (section)
{
}

trees_out::~trees_out ()
{
}

/********************************************************************/
/* Location.  We're aware of the line-map concept and reproduce it
   here.  Each imported module allocates a contiguous span of ordinary
   maps, and of macro maps.  adhoc maps are serialized by contents,
   not pre-allocated.   The scattered linemaps of a module are
   coalesced when writing.  */


/* I use half-open [first,second) ranges.  */
typedef std::pair<unsigned,unsigned> range_t;

/* A range of locations.  */
typedef std::pair<location_t,location_t> loc_range_t;

/* Spans of the line maps that are occupied by this TU.  I.e. not
   within imports.  Only extended when in an interface unit.
   Interval zero corresponds to the forced header linemap(s).  This
   is a singleton object.  */

class loc_spans {
public:
  /* An interval of line maps.  The line maps here represent a contiguous
     non-imported range.  */
  struct span {
    loc_range_t ordinary;	/* Ordinary map location range. */
    loc_range_t macro;		/* Macro map location range.  */
    int ordinary_delta;	/* Add to ordinary loc to get serialized loc.  */
    int macro_delta;	/* Likewise for macro loc.  */
  };

private:
  vec<span> spans;

public:
  loc_spans ()
  {
    spans.create (20);
  }
  ~loc_spans ()
  {
    spans.release ();
  }

public:
  span &operator[] (unsigned ix)
  {
    return spans[ix];
  }
  unsigned length () const
  {
    return spans.length ();
  }

public:
  bool init_p () const
  {
    return spans.length () != 0;
  }
  /* Initializer.  */
  void init (const line_maps *lmaps, const line_map_ordinary *map);

public:
  enum {
    SPAN_RESERVED = 0,	/* Reserved (fixed) locations.  */
    SPAN_FIRST = 1,	/* LWM of locations to stream  */
    SPAN_MAIN = 2	/* Main file and onwards.  */
  };

public:
  location_t main_start () const
  {
    return spans[SPAN_MAIN].ordinary.first;
  }

public:
  void open (location_t);
  void close ();

public:
  const span *ordinary (location_t);
  const span *macro (location_t);
};

static loc_spans spans;

/********************************************************************/
/* Unnamed declarations.  (a) voldemort types, (b) instantiations.  */

struct GTY(()) unnamed_entity
{
  mc_slot slot;  /* The decl, or section number. */
  tree ns;	 /* If a specialization, the ns::id it specializes.  */
  tree id;

  unnamed_entity ()
    :ns (NULL), id (NULL)
  {
    slot.u.binding = NULL;
  }
};

/********************************************************************/

/********************************************************************/
/* Data needed by a module during the process of loading.  */
struct GTY(()) slurping {
  vec<unsigned, va_heap, vl_embed> *
    GTY((skip)) remap;			/* Module owner remapping.  */
  elf_in *GTY((skip)) from;     	/* The elf loader.  */

  /* This map is only for header imports themselves -- the global
     headers bitmap hold it for the current TU.  */
  bitmap headers;	/* Transitive direct header import graph. */

  /* These objects point into the mmapped area, unless we're not doing
     that, or we got frozen or closed.  In those cases they point to
     buffers we own.  */
  bytes_in macro_defs;	/* Macro definitions.  */
  bytes_in macro_tbl;	/* Macro table.  */

  /* Location remapping.  */
  range_t GTY((skip)) loc_deltas;

  unsigned current;	/* Section currently being loaded.  */
  unsigned remaining;	/* Number of lazy sections yet to read.  */
  unsigned lru;		/* An LRU counter.  */

 public:
  slurping (elf_in *);
  ~slurping ();

 public:
  /* Close the ELF file, if it's open.  */
  void close ()
  {
    if (from)
      {
	from->end ();
	delete from;
	from = NULL;
      }
  }

 public:
  void alloc_remap (unsigned size)
  {
    gcc_assert (!remap);
    vec_safe_reserve (remap, size);
    for (unsigned ix = size; ix--;)
      remap->quick_push (0);
  }
  int remap_module (unsigned owner)
  {
    return owner < remap->length () ? int((*remap)[owner]) : -1;
  }

 public:
  /* GC allocation.  But we must explicitly delete it.   */
  static void *operator new (size_t x)
  {
    return ggc_alloc_atomic (x);
  }
  static void operator delete (void *p)
  {
    ggc_free (p);
  }
};

slurping::slurping (elf_in *from)
  : remap (NULL), from (from),
    headers (BITMAP_GGC_ALLOC ()), macro_defs (), macro_tbl (),
    loc_deltas (0, 0),
    /* Start CURRENT with a non-terminator value, so we don't close
       the input during the initial import.  */
    current (~0u - 1), remaining (0), lru (0)
{
}

slurping::~slurping ()
{
  vec_free (remap);
  remap = NULL;
  if (macro_defs.size)
    elf_in::release (from, macro_defs);
  if (macro_tbl.size)
    elf_in::release (from, macro_tbl);
  close ();
}

#if CHECKING_P
/* We should stream each definition at most once.  */
static hash_set<tree> *note_defs;
#endif

void
trees_in::assert_definition (tree decl ATTRIBUTE_UNUSED,
			     odrness odr ATTRIBUTE_UNUSED)
{
#if CHECKING_P
  if (odr == ODR_new)
    {
      /* We must be inserting for the first time.  */
      bool existed = note_defs->add (decl);
      gcc_assert (!existed);
    }
  else
    /* If this is not the mergeable entity, it should not be in the
       table.  If it is a non-global-module mergeable entity, it
       should be in the table.  Global module entities could have been
       defined textually in the current TU and so might or might not
       be present.  */
    gcc_assert (get_dupness (decl) < DUP_dup
		? !note_defs->contains (decl)
		: (!DECL_LANG_SPECIFIC (decl)
		   || !DECL_MODULE_PURVIEW_P (decl)
		   || note_defs->contains (decl)));

  if (TREE_CODE (decl) == TEMPLATE_DECL)
    gcc_assert (!note_defs->contains (DECL_TEMPLATE_RESULT (decl)));
#endif
}

void
trees_out::assert_definition (tree decl ATTRIBUTE_UNUSED)
{
#if CHECKING_P
  bool existed = note_defs->add (decl);
  gcc_assert (!existed);
  if (TREE_CODE (decl) == TEMPLATE_DECL)
    gcc_assert (!note_defs->contains (DECL_TEMPLATE_RESULT (decl)));
#endif
}

/* Information about location maps used during writing.  */

struct location_map_info {
  range_t num_maps;

  unsigned max_range;
};

/* Flage for extensions that end up being streamed.  */

enum streamed_extensions {
  SE_OPENMP = 1 << 0,
  SE_BITS = 1
};

/********************************************************************/
/* State of a particular module. */

class GTY((chain_next ("%h.parent"), for_user)) module_state {
 public:
  /* We always import & export ourselves.  */
  bitmap imports;	/* Transitive modules we're importing.  */
  bitmap exports;	/* Subset of that, that we're exporting.  */

  module_state *parent;
  tree name;		/* Name of the module.  */

  slurping *slurp;	/* Data for loading.  */

  const char *flatname;	/* Flatname of module.  */
  char *filename;	/* CMI Filename */

  /* Indices into the entity_ary.  */
  unsigned entity_lwm;
  unsigned entity_num;

  /* Location ranges for this module.  adhoc-locs are decomposed, so
     don't have a range.  */
  loc_range_t GTY((skip)) ordinary_locs;
  loc_range_t GTY((skip)) macro_locs;

  /* The LOC is unset until we import the module.  */
  location_t loc; 	/* Location referring to module itself.  */
  /* The FROM_LOC is unset until we process a declaration.  */
  location_t from_loc;  /* Location module was imported at.  */

  unsigned short mod;		/* Module owner number.  */
  unsigned short subst;		/* Mangle subst if !0.  */
  unsigned crc;		/* CRC we saw reading it in. */

  unsigned short remap;		/* Remapping during writing.  */
  bool header_p : 1;	/* Is a header import.  */
  bool direct_p : 1;	/* A direct import of TU (includes interface
			   of implementation for which primary_p).  */
  bool primary_p : 1;   /* Is the primary interface of this
			   implementation unit.  */
  bool interface_p : 1; /* Is an interface (partition or primary).  */
  bool exported_p : 1;	/* Direct_p && exported.  */
  bool imported_p : 1;	/* Import has been done.  */
  bool partition_p : 1; /* A partition.  */
  bool from_partition_p : 1; /* Direct import of a partition.  */
  bool cmi_noted_p : 1;

  /* Record extensions emitted or permitted.  */
  unsigned char extensions : SE_BITS;

 public:
  module_state (tree name, module_state *, bool);
  ~module_state ();

 public:
  void release ()
  {
    imports = exports = NULL;
    slurped ();
  }
  void slurped ()
  {
    delete slurp;
    slurp = NULL;
  }
  elf_in *from () const
  {
    elf_in *from = slurp->from;
    gcc_checking_assert (from);
    return from;
  }

 public:
  /* Is this not a real module?  */
  bool is_detached () const
  {
    return from_loc == UNKNOWN_LOCATION;
  }
  bool is_direct () const
  {
    return direct_p;
  }
  bool is_imported () const
  {
    return imported_p;
  }
  bool is_primary () const
  {
    return primary_p;
  }
  bool is_interface () const
  {
    return interface_p;
  }
  bool is_header () const
  {
    return header_p;
  }
  bool is_partition () const
  {
    return partition_p;
  }

 public:
  bool check_not_purview (location_t loc);

 public:
  void mangle ();

 public:
  void set_import (module_state const *, bool is_export);
  void announce (const char *) const;

 public:
  /* Read and write module.  */
  void write (elf_out *to, cpp_reader *);
  void read (int fd, int e, cpp_reader *);

  /* Read a section.  */
  void load_section (unsigned snum);

  /* Juggle a limited number of file numbers.  */
  static void freeze_an_elf ();
  void maybe_defrost ();

  /* Lazily read a section.  */
  bool lazy_load (unsigned index, mc_slot *mslot, unsigned diags = 0);

 public:
  /* Check or complete a read.  */
  bool check_read (unsigned count, tree ns = NULL_TREE, tree id = NULL_TREE);

 private:
  /* The README, for human consumption.  */
  void write_readme (elf_out *to, const char *dialect, unsigned extensions);
  void write_env (elf_out *to);

 private:
  /* Import tables. */
  void write_imports (bytes_out &cfg, bool direct);
  unsigned read_imports (bytes_in &cfg, cpp_reader *, line_maps *maps);
  void write_imports (elf_out *to, unsigned *crc_ptr);
  bool read_imports (cpp_reader *, line_maps *);

 private:
  void write_partitions (elf_out *to, unsigned, unsigned *crc_ptr);
  bool read_partitions (unsigned);

 private:
  void write_config (elf_out *to, struct module_state_config &, unsigned crc);
  bool read_config (struct module_state_config &);

 public:
  void note_cmi_name ();

 private:
  static unsigned write_bindings (elf_out *to, vec<depset *> depsets,
				  depset::hash &table, unsigned *crc_ptr);
  bool read_bindings (vec<tree> spaces, unsigned, const range_t &range);

  void write_namespaces (elf_out *to, depset::hash &table,
			 vec<depset *> spaces, unsigned *crc_ptr);
  vec<tree> read_namespaces ();

  unsigned write_cluster (elf_out *to, depset *depsets[], unsigned size,
			  depset::hash &, unsigned &specializations,
			  unsigned &entities, unsigned *crc_ptr);
  bool read_cluster (unsigned snum);

 private:
  unsigned write_inits (elf_out *to, depset::hash &, unsigned *crc_ptr);
  bool read_inits (unsigned count);

 private:
  void write_specializations (elf_out *to, vec<depset *> depsets,
			      depset::hash &, unsigned count, unsigned *crc_ptr);
  bool read_specializations (unsigned count);

 private:
  void write_entities (elf_out *to, vec<depset *> depsets,
		       depset::hash &, unsigned count, unsigned *crc_ptr);
  bool read_entities (unsigned count, const range_t &range);

 private:
  location_map_info prepare_maps ();
  void write_ordinary_maps (elf_out *to, location_map_info &,
			    bool, unsigned *crc_ptr);
  bool read_ordinary_maps ();
  void write_macro_maps (elf_out *to, location_map_info &, unsigned *crc_ptr);
  bool read_macro_maps ();

 private:
  void write_define (bytes_out &, const cpp_macro *, bool located = true);
  cpp_macro *read_define (bytes_in &, cpp_reader *, bool located = true) const;
  unsigned write_macros (elf_out *to, cpp_reader *, unsigned *crc_ptr);
  bool read_macros ();
  void install_macros ();

 public:
  void import_macros ();

 public:
  static void undef_macro (cpp_reader *, location_t, cpp_hashnode *);
  static cpp_macro *deferred_macro (cpp_reader *, location_t, cpp_hashnode *);

 public:
  void write_location (bytes_out &, location_t);
  location_t read_location (bytes_in &) const;

 public:
  void set_flatname ();
  const char *get_flatname () const
  {
    return flatname;
  }

 public:
  /* Create a location for module.   */
  void maybe_create_loc ()
  {
    gcc_checking_assert (from_loc != UNKNOWN_LOCATION);
    if (loc == UNKNOWN_LOCATION)
      /* Error paths can cause this to be set and then repeated.  */
      loc = linemap_module_loc (line_table, from_loc, get_flatname ());
  }
  void attach (location_t from)
  {
    from_loc = from;

    if (!flatname)
      set_flatname ();
  }

 public:
  bool do_import (const char *filename, cpp_reader *);
  void direct_import (cpp_reader *, bool lazy);
};

/* Hash module state by name.  This cannot be a member of
   module_state, because of GTY restrictions.  We never delete from
   the hash table, but ggc_ptr_hash doesn't support that
   simplification.  */

struct module_state_hash : ggc_ptr_hash<module_state> {
  typedef std::pair<tree,uintptr_t> compare_type; /* {name,parent} */

  static inline hashval_t hash (const value_type m);
  static inline hashval_t hash (const compare_type &n);
  static inline bool equal (const value_type existing,
			    const compare_type &candidate);
};

module_state::module_state (tree name, module_state *parent, bool partition)
  : imports (BITMAP_GGC_ALLOC ()), exports (BITMAP_GGC_ALLOC ()),
    parent (parent), name (name), slurp (NULL),
    flatname (NULL), filename (NULL),
    entity_lwm (0), entity_num (0),
    ordinary_locs (0, 0), macro_locs (0, 0),
    loc (UNKNOWN_LOCATION), from_loc (UNKNOWN_LOCATION),
    mod (MODULE_UNKNOWN), subst (0), crc (0), remap (0),
    partition_p (partition)
{
  header_p = direct_p = primary_p = interface_p = exported_p
    = imported_p = from_partition_p = cmi_noted_p = false;
  extensions = 0;
  if (name && TREE_CODE (name) == STRING_CST)
    {
      header_p = true;
      const char *string = TREE_STRING_POINTER (name);
      gcc_checking_assert (string[0] == '.'
			   ? IS_DIR_SEPARATOR (string[1])
			   : IS_ABSOLUTE_PATH (string));
    }
  else
    gcc_checking_assert (!name || ISALPHA (IDENTIFIER_POINTER (name)[0]));
  gcc_checking_assert (!(parent && header_p));
}

module_state::~module_state ()
{
  release ();
}

/* Hash module state.  */
static hashval_t
module_name_hash (const_tree name)
{
  if (TREE_CODE (name) == STRING_CST)
    return htab_hash_string (TREE_STRING_POINTER (name));
  else
    return IDENTIFIER_HASH_VALUE (name);
}

hashval_t
module_state_hash::hash (const value_type m)
{
  hashval_t ph = pointer_hash<void>::hash
    (reinterpret_cast<void *> (reinterpret_cast<uintptr_t> (m->parent)
			       | m->is_partition ()));
  hashval_t nh = module_name_hash (m->name);
  return iterative_hash_hashval_t (ph, nh);
}

/* Hash a name.  */
hashval_t
module_state_hash::hash (const compare_type &c)
{
  hashval_t ph = pointer_hash<void>::hash (reinterpret_cast<void *> (c.second));
  hashval_t nh = module_name_hash (c.first);

  return iterative_hash_hashval_t (ph, nh);
}

bool
module_state_hash::equal (const value_type existing,
			  const compare_type &candidate)
{
  uintptr_t ep = (reinterpret_cast<uintptr_t> (existing->parent)
		  | existing->is_partition ());
  if (ep != candidate.second)
    return false;

  /* Identifier comparison is by pointer.  If the string_csts happen
     to be the same object, then they're equal too.  */
  if (existing->name == candidate.first)
    return true;

  /* If neither are string csts, they can't be equal.  */
  if (TREE_CODE (candidate.first) != STRING_CST
      || TREE_CODE (existing->name) != STRING_CST)
    return false;

  /* String equality.  */
  if (TREE_STRING_LENGTH (existing->name)
      == TREE_STRING_LENGTH (candidate.first)
      && !memcmp (TREE_STRING_POINTER (existing->name),
		  TREE_STRING_POINTER (candidate.first),
		  TREE_STRING_LENGTH (existing->name)))
    return true;

  return false;
}

/********************************************************************/
/* Global state */

/* Mapper name.  */
static const char *module_mapper_name;

/* Deferred imports.  */
static vec<module_state *, va_heap, vl_embed> *pending_imports;

/* CMI repository path and workspace.  */
static char *cmi_repo;
static size_t cmi_repo_length;
static char *cmi_path;
static size_t cmi_path_alloc;

/* Count of available and loaded clusters.  */
static unsigned available_clusters;
static unsigned loaded_clusters;

/* What the current TU is.  */
unsigned module_kind;

/* Global trees.  */
static const std::pair<tree *, unsigned> global_tree_arys[] =
  {
    std::pair<tree *, unsigned> (sizetype_tab, stk_type_kind_last),
    std::pair<tree *, unsigned> (integer_types, itk_none),
    std::pair<tree *, unsigned> (global_trees, TI_MODULE_HWM),
    std::pair<tree *, unsigned> (c_global_trees, CTI_MODULE_HWM),
    std::pair<tree *, unsigned> (cp_global_trees, CPTI_MODULE_HWM),
    std::pair<tree *, unsigned> (NULL, 0)
  };
static GTY(()) vec<tree, va_gc> *fixed_trees;
static unsigned global_crc;

/* Lazy loading can open many files concurrently, there are
   per-process limits on that.  We pay attention to the process limit,
   and attempt to increase it when we run out.  Otherwise we use an
   LRU scheme to figure out who to flush.  Note that if the import
   graph /depth/ exceeds lazy_limit, we'll exceed the limit.  */
static unsigned lazy_lru;  /* LRU counter.  */
static unsigned lazy_open; /* Number of open modules */
static unsigned lazy_limit; /* Current limit of open modules.  */
static unsigned lazy_hard_limit; /* Hard limit on open modules.  */
/* Account for source, assembler and dump files & directory searches.
   We don't keep the source file's open, so we don't have to account
   for #include depth.  I think dump files are opened and closed per
   pass, but ICBW.  */
#define LAZY_HEADROOM 15 /* File descriptor headroom.  */

/* Vector of module state.  Indexed by OWNER.  Has at least 2 slots.  */
static GTY(()) vec<module_state *, va_gc> *modules;

/* Hash of module state, findable by {name, parent}. */
static GTY(()) hash_table<module_state_hash> *modules_hash;

/* Map of imported entities.  We map DECL_UID to index of entity
   vector.  */
typedef hash_map<unsigned/*UID*/, unsigned/*index*/,
		 simple_hashmap_traits<int_hash<unsigned,0>, unsigned>
		 > entity_map_t;
static entity_map_t *entity_map;
/* Doesn't need GTYing, because any tree referenced here is also
   findable by, symbol table, specialization table, return type of
   reachable function.  */
static vec<mc_slot, va_heap, vl_embed> *entity_ary;

/* Members entities of imported classes that are defined in this TU.
   These are where the entity's context is not from the current TU.
   We need to emit the definition (but not the enclosing class).

   We could find these by walking ALL the imported classes that we
   could provide a member definition.  But that's expensive,
   especially when you consider lazy implicit member declarations,
   which could be ANY imported class.

   Template instantiations are in the template table, so we don't
   need to record those here.  */
static GTY(()) vec<tree, va_gc> *class_members;

/********************************************************************/
/* Mapper to query and inform of modular compilations.  This is a
   singleton.  It contains both FILE and fd entities.  The PEX
   interface provides the former, so we need to keep them around.
   the fd entities are used when networking is supported.  */

class module_mapper {
  const char *name;
  FILE *from;   /* Read from mapper.  */
  FILE *to;	/* Write to mapper.  */
  pex_obj *pex; /* If it's a subprocess.  */
  sighandler_t sigpipe; /* Original sigpipe disposition.  */

  char *buffer; /* Line buffer.  */
  size_t size;  /* Allocated size of buffer.  */
  char *pos;	/* Read/Write point in buffer.  */
  char *end;	/* Ending NUL byte.  */
  char *start;  /* Start of current response line.  */
  int fd_from;	/* Fileno from mapper. */
  int fd_to;	/* Fileno to mapper. */
  bool batching;/* Batching requests or responses.  */

private:
  /* Construction always succeeds, but may result in a dead mapper.  */
  module_mapper (location_t loc, const char *connection);
  ~module_mapper ()
  {
    gcc_assert (!from);
  }

private:
  void kill (location_t);
  static module_mapper *make (location_t loc);

public:
  static module_mapper *get (location_t loc)
  {
    if (!mapper)
      mapper = make (loc);
    return mapper;
  }
  static void fini (location_t loc)
  {
    if (mapper)
      {
	mapper->kill (loc);
	delete mapper;
	mapper = NULL;
      }
  }

public:
  bool is_live () const
  {
    return fd_from >= 0;
  }
  bool is_server () const
  {
    return is_live () && fd_to >= 0;
  }
  bool is_file () const
  {
    return is_live () && fd_to < 0;
  }

public:
  static char *import_export (const module_state *, bool export_p);
  static bool export_done (const module_state *);

public:
  bool cork ()
  {
    batching = true;
    return batching;
  }
  void uncork (location_t loc)
  {
    if (batching)
      {
	batching = false;
	/* Need to disable gnu-printf zero-length format warning.  */
	send_command (loc, "%s", "");
      }
  }
  bool is_corked () const
  {
    return batching;
  }
  bool eol_p () const
  {
    return pos == end;
  }

public:
  void imex_query (const module_state *, bool exporting);
  char *imex_response (const module_state *state)
  {
    return get_response (state->from_loc) > 0 ? cmi_response (state) : NULL;
  }
  bool translate_include (location_t, const char *path, size_t len);

public:
  /* After a response that may be corked, eat blank lines until it is
     uncorked.  */
  void maybe_uncork (location_t loc)
  {
    while (is_corked ())
      if (get_response (loc) > 0)
	response_unexpected (loc);
  }

private:
  bool handshake (location_t, const char *main_src);
  void send_command (location_t, const char * = NULL, ...) ATTRIBUTE_PRINTF_3;
  int get_response (location_t);
  char *response_token (location_t, bool all = false);
  int response_word (location_t, const char *, ...);
  const char *response_error ()
  {
    const char *result = pos != end ? pos : "unspecified error";
    pos = end;
    return result;
  }
  void response_unexpected (location_t);
  bool response_eol (location_t, bool ignore = false);
  char *cmi_response (const module_state *);

private:
  static module_mapper *mapper;
};

/* Our module mapper (created lazily).  */
module_mapper *module_mapper::mapper;

/********************************************************************/
static tree
get_clone_target (tree decl)
{
  tree target;

  if (TREE_CODE (decl) == TEMPLATE_DECL)
    {
      tree res_orig = DECL_CLONED_FUNCTION (DECL_TEMPLATE_RESULT (decl));
      
      target = DECL_TI_TEMPLATE (res_orig);
    }
  else
    target = DECL_CLONED_FUNCTION (decl);

  gcc_checking_assert (DECL_MAYBE_IN_CHARGE_CDTOR_P (target));

  return target;
}

/* Like FOR_EACH_CLONE, but will walk cloned templates.  */
#define FOR_EVERY_CLONE(CLONE, FN)			\
  if (!DECL_MAYBE_IN_CHARGE_CDTOR_P (FN));		\
  else							\
    for (CLONE = DECL_CHAIN (FN);			\
	 CLONE && DECL_CLONED_FUNCTION_P (CLONE);	\
	 CLONE = DECL_CHAIN (CLONE))

/* It'd be nice if USE_TEMPLATE was a field of template_info
   (a) it'd solve the enum case dealt with below,
   (b) both class templates and decl templates would store this in the
   same place
   (c) this function wouldn't need the by-ref arg, which is annoying.  */

static tree
node_template_info (tree decl, int &use)
{
  tree ti = NULL_TREE;
  int use_tpl = -1;
  if (DECL_IMPLICIT_TYPEDEF_P (decl))
    {
      tree type = TREE_TYPE (decl);

      ti = TYPE_TEMPLATE_INFO (type);
      if (ti)
	{
	  if (TYPE_LANG_SPECIFIC (type))
	    use_tpl = CLASSTYPE_USE_TEMPLATE (type);
	  else
	    {
	      /* An enum, where we don't explicitly encode use_tpl.
		 If the containing context (a type or a function), is
		 an ({im,ex}plicit) instantiation, then this is too.
		 If it's a partial or explicit specialization, then
		 this is not!.  */
	      tree ctx = CP_DECL_CONTEXT (decl);
	      if (TYPE_P (ctx))
		ctx = TYPE_NAME (ctx);
	      node_template_info (ctx, use);
	      use_tpl = use != 2 ? use : 0;
	    }
	}
    }
  else if (DECL_LANG_SPECIFIC (decl)
	   && (TREE_CODE (decl) == VAR_DECL
	       || TREE_CODE (decl) == TYPE_DECL
	       || TREE_CODE (decl) == FUNCTION_DECL
	       || TREE_CODE (decl) == FIELD_DECL
	       || TREE_CODE (decl) == TEMPLATE_DECL))
    {
      use_tpl = DECL_USE_TEMPLATE (decl);
      ti = DECL_TEMPLATE_INFO (decl);
    }

  use = use_tpl;
  return ti;
}

/* Find the index in entity_ary for an imported DECL.  It must be
   there.  */

static unsigned
import_entity_index (tree decl)
{
  unsigned index = *entity_map->get (DECL_UID (decl));

  return index;
}

/* Find the module for an imported entity at INDEX in the entity ary.
   There must be one.  */

static module_state *
import_entity_module (unsigned index)
{
  unsigned pos = 1;
  unsigned len = modules->length () - pos;
  while (len)
    {
      unsigned half = len / 2;
      module_state *probe = (*modules)[pos + half];
      if (index < probe->entity_lwm)
	len = half;
      else if (index < probe->entity_lwm + probe->entity_num)
	return probe;
      else
	{
	  pos += half + 1;
	  len = len - (half + 1);
	}
    }
  gcc_unreachable ();
}

/********************************************************************/
/* A dumping machinery.  */

class dumper {
public:
  enum {
    LOCATION = TDF_LINENO,  /* -lineno:Source location streaming.  */
    DEPEND = TDF_GRAPH,	/* -graph:Dependency graph construction.  */
    CLUSTER = TDF_BLOCKS,   /* -blocks:Clusters.  */
    TREE = TDF_UID, 	/* -uid:Tree streaming.  */
    MERGE = TDF_ALIAS,	/* -alias:Mergeable Entities.  */
    ELF = TDF_ASMNAME,	/* -asmname:Elf data.  */
    MAPPER = TDF_EH,	/* -eh:Mapper.  */
    MACRO = TDF_VOPS	/* -vops:Macros.  */
  };

private:
  struct impl {
    typedef vec<module_state *, va_heap, vl_embed> stack_t;

    FILE *stream;	/* Dump stream.  */
    unsigned indent; 	/* Local indentation.  */
    bool bol; 		/* Beginning of line.  */
    stack_t stack;	/* Trailing array of module_state.  */

    bool nested_name (tree);  /* Dump a name following DECL_CONTEXT.  */
  };

public:
  /* The dumper.  */
  impl *dumps;
  dump_flags_t flags;

public:
  /* Push/pop module state dumping.  */
  unsigned push (module_state *);
  void pop (unsigned);

public:
  /* Change local indentation.  */
  void indent ()
  {
    if (dumps)
      dumps->indent++;
  }
  void outdent ()
  {
    if (dumps)
      {
	gcc_checking_assert (dumps->indent);
	dumps->indent--;
      }
  }

public:
  /* Is dump enabled?.  */
  bool operator () (int mask = 0)
  {
    if (!dumps || !dumps->stream)
      return false;
    if (mask && !(mask & flags))
      return false;
    return true;
  }
  /* Dump some information.  */
  bool operator () (const char *, ...);
};

/* The dumper.  */
static dumper dump = {0, dump_flags_t (0)};

/* Push to dumping M.  Return previous indentation level.  */

unsigned
dumper::push (module_state *m)
{
  FILE *stream = NULL;
  if (!dumps || !dumps->stack.length ())
    {
      stream = dump_begin (module_dump_id, &flags);
      if (!stream)
	return 0;
    }

  if (!dumps || !dumps->stack.space (1))
    {
      /* Create or extend the dump implementor.  */
      unsigned current = dumps ? dumps->stack.length () : 0;
      unsigned count = current ? current * 2 : EXPERIMENT (1, 20);
      size_t alloc = (offsetof (impl, impl::stack)
		      + impl::stack_t::embedded_size (count));
      dumps = XRESIZEVAR (impl, dumps, alloc);
      dumps->stack.embedded_init (count, current);
    }
  if (stream)
    dumps->stream = stream;

  unsigned n = dumps->indent;
  dumps->indent = 0;
  dumps->bol = true;
  dumps->stack.quick_push (m);
  if (m)
    {
      module_state *from = NULL;

      if (dumps->stack.length () > 1)
	from = dumps->stack[dumps->stack.length () - 2];
      else
	dump ("");
      dump (from ? "Starting module %M (from %M)"
	    : "Starting module %M", m, from);
    }

  return n;
}

/* Pop from dumping.  Restore indentation to N.  */

void dumper::pop (unsigned n)
{
  if (!dumps)
    return;

  gcc_checking_assert (dump () && !dumps->indent);
  if (module_state *m = dumps->stack[dumps->stack.length () - 1])
    {
      module_state *from = (dumps->stack.length () > 1
			    ? dumps->stack[dumps->stack.length () - 2] : NULL);
      dump (from ? "Finishing module %M (returning to %M)"
	    : "Finishing module %M", m, from);
    }
  dumps->stack.pop ();
  dumps->indent = n;
  if (!dumps->stack.length ())
    {
      dump_end (module_dump_id, dumps->stream);
      dumps->stream = NULL;
    }
}

/* Dump a nested name for arbitrary tree T.  Sometimes it won't have a
   name.  */

bool
dumper::impl::nested_name (tree t)
{
  tree ti = NULL_TREE;
  int origin = -1;

  if (t && TREE_CODE (t) == TREE_BINFO)
    t = BINFO_TYPE (t);

  if (t && TYPE_P (t))
    t = TYPE_NAME (t);

  if (t && DECL_P (t))
    {
      if (t == global_namespace || DECL_TEMPLATE_PARM_P (t))
	;
      else if (tree ctx = DECL_CONTEXT (t))
	if (TREE_CODE (ctx) == TRANSLATION_UNIT_DECL
	    || nested_name (ctx))
	  fputs ("::", stream);

      if (!DECL_TEMPLATE_PARM_P (t)
	  && (TREE_CODE (t) == FUNCTION_DECL
	      || TREE_CODE (t) == VAR_DECL
	      || TREE_CODE (t) == TYPE_DECL
	      || (TREE_CODE (t) == TEMPLATE_DECL && DECL_TEMPLATE_RESULT (t))))
	{
	  tree o = get_instantiating_module_decl (t);
	  if (DECL_LANG_SPECIFIC (o))
	    origin = DECL_MODULE_ORIGIN (o);
	}

      int use_tpl;
      ti = node_template_info (t, use_tpl);

      t = DECL_NAME (t) ? DECL_NAME (t)
	: HAS_DECL_ASSEMBLER_NAME_P (t) ? DECL_ASSEMBLER_NAME_RAW (t)
	: NULL_TREE;
    }

  if (t)
    switch (TREE_CODE (t))
      {
      default:
	fputs ("#unnamed#", stream);
	break;

      case IDENTIFIER_NODE:
	fwrite (IDENTIFIER_POINTER (t), 1, IDENTIFIER_LENGTH (t), stream);
	break;

      case INTEGER_CST:
	print_hex (wi::to_wide (t), stream);
	break;

      case STRING_CST:
	/* If TREE_TYPE is NULL, this is a raw string.  */
	fwrite (TREE_STRING_POINTER (t), 1,
		TREE_STRING_LENGTH (t) - (TREE_TYPE (t) != NULL_TREE), stream);
	break;
      }
  else
    fputs ("#null#", stream);

  if (origin >= 0)
    {
      const module_state *module = (*modules)[origin];
      fprintf (stream, "@%s:%d", !module ? "" : !module->name ? "(unnamed)"
	       : module->get_flatname (), origin);
    }

  if (ti)
    {
      tree args = INNERMOST_TEMPLATE_ARGS (TI_ARGS (ti));
      fputs ("<", stream);
      if (args)
	for (int ix = 0; ix != TREE_VEC_LENGTH (args); ix++)
	  {
	    if (ix)
	      fputs (",", stream);
	    nested_name (TREE_VEC_ELT (args, ix));
	  }
      fputs (">", stream);
    }

  return true;
}

/* Formatted dumping.  FORMAT begins with '+' do not emit a trailing
   new line.  (Normally it is appended.)
   Escapes:
      %C - tree_code
      %I - identifier
      %M - module_state
      %N - name -- DECL_NAME
      %P - context:name pair
      %R - unsigned:unsigned ratio
      %S - symbol -- DECL_ASSEMBLER_NAME
      %U - long unsigned
      %V - version
      --- the following are printf-like, but without its flexibility
      %d - decimal int
      %p - pointer
      %s - string
      %u - unsigned int
      %x - hex int

  We do not implement the printf modifiers.  */

bool
dumper::operator () (const char *format, ...)
{
  if (!(*this) ())
    return false;

  bool no_nl = format[0] == '+';
  format += no_nl;

  if (dumps->bol)
    {
      /* Module import indent.  */
      if (unsigned depth = dumps->stack.length () - 1)
	{
	  const char *prefix = ">>>>";
	  fprintf (dumps->stream, (depth <= strlen (prefix)
				   ? &prefix[strlen (prefix) - depth]
				   : ">.%d.>"), depth);
	}

      /* Local indent.  */
      if (unsigned indent = dumps->indent)
	{
	  const char *prefix = "      ";
	  fprintf (dumps->stream, (indent <= strlen (prefix)
				   ? &prefix[strlen (prefix) - indent]
				   : "  .%d.  "), indent);
	}
      dumps->bol = false;
    }

  va_list args;
  va_start (args, format);
  while (const char *esc = strchr (format, '%'))
    {
      fwrite (format, 1, (size_t)(esc - format), dumps->stream);
      format = ++esc;
      switch (*format++)
	{
	default:
	  gcc_unreachable ();

	case '%':
	  fputc ('%', dumps->stream);
	  break;

	case 'C': /* Code */
	  {
	    tree_code code = (tree_code)va_arg (args, unsigned);
	    fputs (get_tree_code_name (code), dumps->stream);
	  }
	  break;

	case 'I': /* Identifier.  */
	  {
	    tree t = va_arg (args, tree);
	    dumps->nested_name (t);
	  }
	  break;

	case 'M': /* Module. */
	  {
	    const char *str = "(none)";
	    if (module_state *m = va_arg (args, module_state *))
	      {
		if (m->is_detached ())
		  str = "(detached)";
		else
		  str = m->get_flatname ();
	      }
	    fputs (str, dumps->stream);
	  }
	  break;

	case 'N': /* Name.  */
	  {
	    tree t = va_arg (args, tree);
	    if (t && TREE_CODE (t) == OVERLOAD)
	      t = OVL_FIRST (t);
	    fputc ('\'', dumps->stream);
	    dumps->nested_name (t);
	    fputc ('\'', dumps->stream);
	  }
	  break;

	case 'P': /* Pair.  */
	  {
	    tree ctx = va_arg (args, tree);
	    tree name = va_arg (args, tree);
	    fputc ('\'', dumps->stream);
	    dumps->nested_name (ctx);
	    if (ctx && ctx != global_namespace)
	      fputs ("::", dumps->stream);
	    dumps->nested_name (name);
	    fputc ('\'', dumps->stream);
	  }
	  break;

	case 'R': /* Ratio */
	  {
	    unsigned a = va_arg (args, unsigned);
	    unsigned b = va_arg (args, unsigned);
	    fprintf (dumps->stream, "%.1f", (float) a / (b + !b));
	  }
	  break;

	case 'S': /* Symbol name */
	  {
	    tree t = va_arg (args, tree);
	    if (t && TYPE_P (t))
	      t = TYPE_NAME (t);
	    if (t && HAS_DECL_ASSEMBLER_NAME_P (t)
		&& DECL_ASSEMBLER_NAME_SET_P (t))
	      {
		fputc ('(', dumps->stream);
		fputs (IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (t)),
		       dumps->stream);
		fputc (')', dumps->stream);
	      }
	  }
	  break;

	case 'U': /* long unsigned.  */
	  {
	    unsigned long u = va_arg (args, unsigned long);
	    fprintf (dumps->stream, "%lu", u);
	  }
	  break;

	case 'V': /* Verson.  */
	  {
	    unsigned v = va_arg (args, unsigned);
	    verstr_t string;

	    version2string (v, string);
	    fputs (string, dumps->stream);
	  }
	  break;

	case 'c': /* Character.  */
	  {
	    int c = va_arg (args, int);
	    fputc (c, dumps->stream);
	  }
	  break;

	case 'd': /* Decimal Int.  */
	  {
	    int d = va_arg (args, int);
	    fprintf (dumps->stream, "%d", d);
	  }
	  break;

	case 'p': /* Pointer. */
	  {
	    void *p = va_arg (args, void *);
	    fprintf (dumps->stream, "%p", p);
	  }
	  break;

	case 's': /* String. */
	  {
	    const char *s = va_arg (args, char *);
	    gcc_checking_assert (s);
	    fputs (s, dumps->stream);
	  }
	  break;

	case 'u': /* Unsigned.  */
	  {
	    unsigned u = va_arg (args, unsigned);
	    fprintf (dumps->stream, "%u", u);
	  }
	  break;

	case 'x': /* Hex. */
	  {
	    unsigned x = va_arg (args, unsigned);
	    fprintf (dumps->stream, "%x", x);
	  }
	  break;
	}
    }
  fputs (format, dumps->stream);
  va_end (args);
  if (!no_nl)
    {
      dumps->bol = true;
      fputc ('\n', dumps->stream);
    }
  return true;
}

/********************************************************************/
static bool
noisy_p ()
{
  if (quiet_flag)
    return false;

  pp_needs_newline (global_dc->printer) = true;
  diagnostic_set_last_function (global_dc, (diagnostic_info *) NULL);

  return true;
}

/* Set the cmi repo.  Strip trailing '/', '.' becomes NULL.  */

static void
set_cmi_repo (char *r)
{
  XDELETEVEC (cmi_repo);
  XDELETEVEC (cmi_path);
  cmi_path_alloc = 0;

  cmi_repo = NULL;
  cmi_repo_length = 0;

  if (!r)
    return;

  size_t len = strlen (r);
  if (len > 1 && IS_DIR_SEPARATOR (r[len-1]))
    r[--len] = 0;
  if (0 == strcmp (r, "."))
    return;

  cmi_repo = XNEWVEC (char, len + 1);
  memcpy (cmi_repo, r, len + 1);
  cmi_repo_length = len;
}

/* TO is a repo-relative name.  Provide one that we may use from where
   we are.  */

static const char *
maybe_add_cmi_prefix (const char *to, size_t *len_p = NULL)
{
  size_t len = len_p || cmi_repo_length ? strlen (to) : 0;

  if (cmi_repo_length && !IS_ABSOLUTE_PATH (to))
    {
      if (cmi_path_alloc < cmi_repo_length + len + 2)
	{
	  XDELETEVEC (cmi_path);
	  cmi_path_alloc = cmi_repo_length + len * 2 + 2;
	  cmi_path = XNEWVEC (char, cmi_path_alloc);

	  memcpy (cmi_path, cmi_repo, cmi_repo_length);
	  cmi_path[cmi_repo_length] = DIR_SEPARATOR;
	}

      memcpy (&cmi_path[cmi_repo_length + 1], to, len + 1);
      len += cmi_repo_length + 1;
      to = cmi_path;
    }

  if (len_p)
    *len_p = len;

  return to;
}

/* Try and create the directories of PATH.  */

static void
create_dirs (char *path)
{
  /* Try and create the missing directories.  */
  for (char *base = path; *base; base++)
    if (IS_DIR_SEPARATOR (*base))
      {
	char sep = *base;
	*base = 0;
	int failed = mkdir (path, S_IRWXU | S_IRWXG | S_IRWXO);
	*base = sep;
	if (failed
	    /* Maybe racing with another creator (of a *different*
	       module).  */
	    && errno != EEXIST)
	  break;
      }
}

/* If CMI path TO begins with the prefix, return a pointer to the
   trailing suffix.  Otherwise return TO.  */

static char *
maybe_strip_cmi_prefix (char *to)
{
  if (cmi_repo)
    {
      if (0 == strncmp (to, cmi_repo, cmi_repo_length))
	{
	  char *res = to;
	  for (size_t probe = cmi_repo_length;
	       IS_DIR_SEPARATOR (to[probe]);)
	    res = &to[++probe];
	  to = res;
	}
    }
  return to;
}

/* Given a CLASSTYPE_DECL_LIST VALUE get the the template friend decl,
   if that's what this is.  */

static tree
friend_from_decl_list (tree frnd)
{
  tree res = frnd;

  if (TREE_CODE (frnd) != TEMPLATE_DECL)
    {
      tree tmpl = NULL_TREE;
      if (TYPE_P (frnd))
	{
	  res = TYPE_NAME (frnd);
	  if (CLASSTYPE_TEMPLATE_INFO (frnd))
	    tmpl = CLASSTYPE_TI_TEMPLATE (frnd);
	}
      else if (DECL_TEMPLATE_INFO (frnd))
	{
	  tmpl = DECL_TI_TEMPLATE (frnd);
	  if (TREE_CODE (tmpl) != TEMPLATE_DECL)
	    tmpl = NULL_TREE;
	}

      if (tmpl && DECL_TEMPLATE_RESULT (tmpl) == res)
	res = tmpl;
    }

  return res;
}

/********************************************************************/
/* Instrumentation gathered writing bytes.  */

void
bytes_out::instrument ()
{
  dump ("Wrote %u bytes in %u blocks", lengths[3], spans[3]);
  dump ("Wrote %u bits in %u bytes", lengths[0] + lengths[1], lengths[2]);
  for (unsigned ix = 0; ix < 2; ix++)
    dump ("  %u %s spans of %R bits", spans[ix],
	  ix ? "one" : "zero", lengths[ix], spans[ix]);
  dump ("  %u blocks with %R bits padding", spans[2],
	lengths[2] * 8 - (lengths[0] + lengths[1]), spans[2]);
}

/* Instrumentation gathered writing trees.  */
void
trees_out::instrument ()
{
  if (dump (""))
    {
      bytes_out::instrument ();
      dump ("Wrote:");
      dump ("  %u decl trees", decl_val_count);
      dump ("  %u other trees", tree_val_count);
      dump ("  %u back references", back_ref_count);
      dump ("  %u null trees", null_count);
    }
}

/* Setup and teardown for a tree walk.  */

void
trees_out::begin ()
{
  gcc_assert (!streaming_p () || !tree_map.elements ());

  mark_trees ();
  if (streaming_p ())
    parent::begin ();
}

unsigned
trees_out::end (elf_out *sink, unsigned name, unsigned *crc_ptr)
{
  gcc_checking_assert (streaming_p ());

  unmark_trees ();
  return parent::end (sink, name, crc_ptr);
}

void
trees_out::end ()
{
  gcc_assert (!streaming_p ());

  unmark_trees ();
  /* Do not parent::end -- we weren't streaming.  */
}

void
trees_out::mark_trees ()
{
  if (size_t size = tree_map.elements ())
    {
      /* This isn't our first rodeo, destroy and recreate the
	 tree_map.  I'm a bad bad man.  Use the previous size as a
	 guess for the next one (so not all bad).  */
      tree_map.~ptr_int_hash_map ();
      new (&tree_map) ptr_int_hash_map (size);
    }

  /* Install the fixed trees, with +ve references.  */
  unsigned limit = fixed_trees->length ();
  for (unsigned ix = 0; ix != limit; ix++)
    {
      tree val = (*fixed_trees)[ix];
      bool existed = tree_map.put (val, ix + tag_fixed);
      gcc_checking_assert (!TREE_VISITED (val) && !existed);
      TREE_VISITED (val) = true;
    }

  ref_num = 0;
}

/* Unmark the trees we encountered  */

void
trees_out::unmark_trees ()
{
  ptr_int_hash_map::iterator end (tree_map.end ());
  for (ptr_int_hash_map::iterator iter (tree_map.begin ()); iter != end; ++iter)
    {
      tree node = reinterpret_cast<tree> ((*iter).first);
      int ref = (*iter).second;
      /* We should have visited the node, and converted its mergeable
	 reference to a regular reference.  */
      gcc_checking_assert (TREE_VISITED (node)
			   && (ref <= tag_backref || ref >= tag_fixed));
      TREE_VISITED (node) = false;
    }
}

/* Mark DECL for by-value walking.  We do this by inserting it into
   the tree map with a reference of zero.  May be called multiple
   times on the same node.  */

void
trees_out::mark_by_value (tree decl)
{
  gcc_checking_assert (DECL_P (decl)
		       /* Enum consts are INTEGER_CSTS.  */
		       || TREE_CODE (decl) == INTEGER_CST
		       || TREE_CODE (decl) == TREE_BINFO);

  if (TREE_VISITED (decl))
    /* Must already be forced or fixed.  */
    gcc_checking_assert (*tree_map.get (decl) >= tag_value);
  else
    {
      bool existed = tree_map.put (decl, tag_value);
      gcc_checking_assert (!existed);
      TREE_VISITED (decl) = true;
    }
}

/* Insert T into the map, return its tag number.    */

int
trees_out::insert (tree t, walk_kind walk)
{
  gcc_checking_assert (walk != WK_normal || !TREE_VISITED (t));
  int tag = --ref_num;
  bool existed;
  int &slot = tree_map.get_or_insert (t, &existed);
  gcc_checking_assert (TREE_VISITED (t) == existed
		       && (!existed
			   || (walk == WK_value && slot == tag_value)));
  TREE_VISITED (t) = true;
  slot = tag;

  return tag;
}

/* Insert T into the backreference array.  Return its back reference
   number.  */

int
trees_in::insert (tree t)
{
  gcc_checking_assert (t || get_overrun ());
  back_refs.safe_push (t);
  return -(int)back_refs.length ();
}

/* A chained set of decls.  */

void
trees_out::chained_decls (tree decls)
{
  for (; decls; decls = DECL_CHAIN (decls))
    tree_node (decls);
  tree_node (NULL_TREE);
}

tree
trees_in::chained_decls ()
{
  tree decls = NULL_TREE;
  for (tree *chain = &decls; chain && !get_overrun ();)
    if (tree decl = tree_node ())
      {
	if (!DECL_P (decl))
	  set_overrun ();
	else
	  {
	    if (*chain)
	      {
		// FIXME: suspicious, perhaps chain only when we know
		// not the definition?
		gcc_checking_assert (TREE_CODE (decl) == PARM_DECL
				     && TREE_CODE (*chain) == PARM_DECL);
	      }
	    *chain = decl;
	    chain = &DECL_CHAIN (decl);
	  }
      }
    else
      {
	gcc_checking_assert (!*chain);
	chain = NULL;
      }

  return decls;
}

/* A vector of trees.  */

void
trees_out::tree_vec (vec<tree, va_gc> *v)
{
  unsigned len = vec_safe_length (v);
  if (streaming_p ())
    u (len);
  if (len)
    for (unsigned ix = 0; ix != len; ix++)
      tree_node ((*v)[ix]);
}

vec<tree, va_gc> *
trees_in::tree_vec ()
{
  vec<tree, va_gc> *v = NULL;
  if (unsigned len = u ())
    {
      vec_alloc (v, len);
      for (unsigned ix = 0; ix != len; ix++)
	v->quick_push (tree_node ());
    }
  return v;
}

/* A vector of tree pairs.  */

void
trees_out::tree_pair_vec (vec<tree_pair_s, va_gc> *v)
{
  unsigned len = vec_safe_length (v);
  if (streaming_p ())
    u (len);
  if (len)
    for (unsigned ix = 0; ix != len; ix++)
      {
	tree_pair_s const &s = (*v)[ix];
	tree_node (s.purpose);
	tree_node (s.value);
      }
}

vec<tree_pair_s, va_gc> *
trees_in::tree_pair_vec ()
{
  vec<tree_pair_s, va_gc> *v = NULL;
  if (unsigned len = u ())
    {
      vec_alloc (v, len);
      for (unsigned ix = 0; ix != len; ix++)
	{
	  tree_pair_s s;
	  s.purpose = tree_node ();
	  s.value = tree_node ();
	  v->quick_push (s);
      }
    }
  return v;
}

/* Start tree write.  Write information to allocate the receiving
   node.  */

void
trees_out::start (tree t, bool code_streamed)
{
  if (TYPE_P (t))
    {
      enum tree_code code = TREE_CODE (t);
      gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t);
      /* All these types are TYPE_NON_COMMON.  */
      gcc_checking_assert (code == RECORD_TYPE
			   || code == UNION_TYPE
			   || code == ENUMERAL_TYPE
			   || code == TEMPLATE_TYPE_PARM
			   || code == TEMPLATE_TEMPLATE_PARM
			   || code == BOUND_TEMPLATE_TEMPLATE_PARM);
    }

  if (!code_streamed)
    u (TREE_CODE (t));

  switch (TREE_CODE (t))
    {
    default:
      if (TREE_CODE_CLASS (TREE_CODE (t)) == tcc_vl_exp)
	u (VL_EXP_OPERAND_LENGTH (t));
      break;

    case INTEGER_CST:
      u (TREE_INT_CST_NUNITS (t));
      u (TREE_INT_CST_EXT_NUNITS (t));
      u (TREE_INT_CST_OFFSET_NUNITS (t));
      break;

    case OMP_CLAUSE:
      state->extensions |= SE_OPENMP;
      u (OMP_CLAUSE_CODE (t));
      break;

    case STRING_CST:
      str (TREE_STRING_POINTER (t), TREE_STRING_LENGTH (t));
      break;

    case VECTOR_CST:
      u (VECTOR_CST_LOG2_NPATTERNS (t));
      u (VECTOR_CST_NELTS_PER_PATTERN (t));
      break;

    case TREE_BINFO:
      u (BINFO_N_BASE_BINFOS (t));
      break;

    case TREE_VEC:
      u (TREE_VEC_LENGTH (t));
      break;

    case FIXED_CST:
    case POLY_INT_CST:
      gcc_unreachable (); /* Not supported in C++.  */
      break;

    case IDENTIFIER_NODE:
    case MEM_REF:
    case SSA_NAME:
    case TARGET_MEM_REF:
    case TRANSLATION_UNIT_DECL:
      /* We shouldn't meet these.  */
      gcc_unreachable ();
      break;
    }
}

/* Start tree read.  Allocate the receiving node.  */

tree
trees_in::start (unsigned code)
{
  tree t = NULL_TREE;

  if (!code)
    code = u ();

  switch (code)
    {
    default:
      if (code >= MAX_TREE_CODES)
	{
	fail:
	  set_overrun ();
	  return NULL_TREE;
	}
      else if (TREE_CODE_CLASS (code) == tcc_vl_exp)
	{
	  unsigned ops = u ();
	  t = build_vl_exp (tree_code (code), ops);
	}
      else
	t = make_node (tree_code (code));
      break;

    case INTEGER_CST:
      {
	unsigned n = u ();
	unsigned e = u ();
	t = make_int_cst (n, e);
	TREE_INT_CST_OFFSET_NUNITS(t) = u ();
      }
      break;

    case OMP_CLAUSE:
      {
	if (!(state->extensions & SE_OPENMP))
	  goto fail;

	unsigned omp_code = u ();
	t = build_omp_clause (UNKNOWN_LOCATION, omp_clause_code (omp_code));
      }
      break;

    case STRING_CST:
      {
	size_t l;
	const char *chars = str (&l);
	t = build_string (l, chars);
      }
      break;

    case VECTOR_CST:
      {
	unsigned log2_npats = u ();
	unsigned elts_per = u ();
	t = make_vector (log2_npats, elts_per);
      }
      break;

    case TREE_BINFO:
      t = make_tree_binfo (u ());
      break;

    case TREE_VEC:
      t = make_tree_vec (u ());
      break;

    case FIXED_CST:
    case IDENTIFIER_NODE:
    case MEM_REF:
    case POLY_INT_CST:
    case SSA_NAME:
    case TARGET_MEM_REF:
    case TRANSLATION_UNIT_DECL:
      goto fail;
    }

  return t;
}

/* The structure streamers access the raw fields, because the
   alternative, of using the accessor macros can require using
   different accessors for the same underlying field, depending on the
   tree code.  That's both confusing and annoying.  */

/* Read & write the core boolean flags.  */

void
trees_out::core_bools (tree t)
{
#define WB(X) (b (X))
  tree_code code = TREE_CODE (t);

  WB (t->base.side_effects_flag);
  WB (t->base.constant_flag);
  WB (t->base.addressable_flag);
  WB (t->base.volatile_flag);
  WB (t->base.readonly_flag);

  bool asm_written = t->base.asm_written_flag;
  if (asm_written)
    {
      /* Some cases we do not want to propagate asm_written, as it is
	 TU-local.  */
      if (TYPE_P (t) || TREE_CODE (t) == TYPE_DECL)
	/* It's telling us about debug info.  */
	asm_written = false;
    }
  WB (asm_written);
  
  WB (t->base.nowarning_flag);
  // visited is zero
  WB (t->base.used_flag); // FIXME: should we be dumping this?
  WB (t->base.nothrow_flag);
  WB (t->base.static_flag);
  if (TREE_CODE_CLASS (code) != tcc_type)
    /* This is TYPE_CACHED_VALUES_P for types.  */
    WB (t->base.public_flag);
  WB (t->base.private_flag);
  WB (t->base.protected_flag);
  WB (t->base.deprecated_flag);
  WB (t->base.default_def_flag);

  switch (code)
    {
    case CALL_EXPR:
    case INTEGER_CST:
    case MEM_REF:
    case SSA_NAME:
    case TARGET_MEM_REF:
    case TREE_VEC:
      /* These use different base.u fields.  */
      break;

    default:
      WB (t->base.u.bits.lang_flag_0);
      bool flag_1 = t->base.u.bits.lang_flag_1;
      if (code == TEMPLATE_INFO)
	/* This is TI_PENDING_TEMPLATE_FLAG, not relevant to reader.  */
	flag_1 = false;
      WB (flag_1);
      WB (t->base.u.bits.lang_flag_2);
      WB (t->base.u.bits.lang_flag_3);
      WB (t->base.u.bits.lang_flag_4);
      WB (t->base.u.bits.lang_flag_5);
      WB (t->base.u.bits.lang_flag_6);
      WB (t->base.u.bits.saturating_flag);
      WB (t->base.u.bits.unsigned_flag);
      WB (t->base.u.bits.packed_flag);
      WB (t->base.u.bits.user_align);
      WB (t->base.u.bits.nameless_flag);
      WB (t->base.u.bits.atomic_flag);
      break;
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE_COMMON))
    {
      WB (t->type_common.no_force_blk_flag);
      WB (t->type_common.needs_constructing_flag);
      WB (t->type_common.transparent_aggr_flag);
      WB (t->type_common.restrict_flag);
      WB (t->type_common.string_flag);
      WB (t->type_common.lang_flag_0);
      WB (t->type_common.lang_flag_1);
      WB (t->type_common.lang_flag_2);
      WB (t->type_common.lang_flag_3);
      WB (t->type_common.lang_flag_4);
      WB (t->type_common.lang_flag_5);
      WB (t->type_common.lang_flag_6);
      WB (t->type_common.typeless_storage);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_COMMON))
    {
      WB (t->decl_common.nonlocal_flag);
      WB (t->decl_common.virtual_flag);
      WB (t->decl_common.ignored_flag);
      WB (t->decl_common.abstract_flag);
      WB (t->decl_common.artificial_flag);
      WB (t->decl_common.preserve_flag);
      WB (t->decl_common.debug_expr_is_from);
      WB (t->decl_common.lang_flag_0);
      WB (t->decl_common.lang_flag_1);
      WB (t->decl_common.lang_flag_2);
      WB (t->decl_common.lang_flag_3);
      WB (t->decl_common.lang_flag_4);
      WB (t->decl_common.lang_flag_5);
      WB (t->decl_common.lang_flag_6);
      WB (t->decl_common.lang_flag_7);
      WB (t->decl_common.lang_flag_8);
      WB (t->decl_common.decl_flag_0);

      // FIXME: This heuristic is not correct.  We should be fiddling
      // with this during the dependency walk
      /* static variables become external.  */
      WB (t->decl_common.decl_flag_1
	  || (code == VAR_DECL && TREE_STATIC (t)
	      && !header_module_p ()
	      && !DECL_WEAK (t) && !DECL_VTABLE_OR_VTT_P (t)));

      WB (t->decl_common.decl_flag_2);
      WB (t->decl_common.decl_flag_3);
      WB (t->decl_common.gimple_reg_flag);
      WB (t->decl_common.decl_by_reference_flag);
      WB (t->decl_common.decl_read_flag);
      WB (t->decl_common.decl_nonshareable_flag);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_WITH_VIS))
    {
      WB (t->decl_with_vis.defer_output);
      WB (t->decl_with_vis.hard_register);
      WB (t->decl_with_vis.common_flag);
      WB (t->decl_with_vis.in_text_section);
      WB (t->decl_with_vis.in_constant_pool);
      WB (t->decl_with_vis.dllimport_flag);
      WB (t->decl_with_vis.weak_flag);
      WB (t->decl_with_vis.seen_in_bind_expr);
      WB (t->decl_with_vis.comdat_flag);
      WB (t->decl_with_vis.visibility_specified);
      WB (t->decl_with_vis.comdat_flag);
      WB (t->decl_with_vis.init_priority_p);
      WB (t->decl_with_vis.shadowed_for_var_p);
      WB (t->decl_with_vis.cxx_constructor);
      WB (t->decl_with_vis.cxx_destructor);
      WB (t->decl_with_vis.final);
      WB (t->decl_with_vis.regdecl_flag);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_FUNCTION_DECL))
    {
      WB (t->function_decl.static_ctor_flag);
      WB (t->function_decl.static_dtor_flag);
      WB (t->function_decl.uninlinable);
      WB (t->function_decl.possibly_inlined);
      WB (t->function_decl.novops_flag);
      WB (t->function_decl.returns_twice_flag);
      WB (t->function_decl.malloc_flag);
      WB (t->function_decl.declared_inline_flag);
      WB (t->function_decl.no_inline_warning_flag);
      WB (t->function_decl.no_instrument_function_entry_exit);
      WB (t->function_decl.no_limit_stack);
      WB (t->function_decl.disregard_inline_limits);
      WB (t->function_decl.pure_flag);
      WB (t->function_decl.looping_const_or_pure_flag);

      WB (t->function_decl.has_debug_args_flag);
      WB (t->function_decl.versioned_function);

      /* decl_type is a (misnamed) 2 bit discriminator.	 */
      unsigned kind = t->function_decl.decl_type;
      WB ((kind >> 0) & 1);
      WB ((kind >> 1) & 1);
    }
#undef WB
}

bool
trees_in::core_bools (tree t)
{
#define RB(X) ((X) = b ())
  tree_code code = TREE_CODE (t);

  RB (t->base.side_effects_flag);
  RB (t->base.constant_flag);
  RB (t->base.addressable_flag);
  RB (t->base.volatile_flag);
  RB (t->base.readonly_flag);
  /* The writer will have written false when we don't need it.  */
  RB (t->base.asm_written_flag);
  RB (t->base.nowarning_flag);
  // visited is zero
  RB (t->base.used_flag);
  RB (t->base.nothrow_flag);
  RB (t->base.static_flag);
  if (TREE_CODE_CLASS (code) != tcc_type)
    RB (t->base.public_flag);
  RB (t->base.private_flag);
  RB (t->base.protected_flag);
  RB (t->base.deprecated_flag);
  RB (t->base.default_def_flag);

  switch (code)
    {
    case CALL_EXPR:
    case INTEGER_CST:
    case MEM_REF:
    case SSA_NAME:
    case TARGET_MEM_REF:
    case TREE_VEC:
      /* These use different base.u fields.  */
      break;

    default:
      RB (t->base.u.bits.lang_flag_0);
      RB (t->base.u.bits.lang_flag_1);
      RB (t->base.u.bits.lang_flag_2);
      RB (t->base.u.bits.lang_flag_3);
      RB (t->base.u.bits.lang_flag_4);
      RB (t->base.u.bits.lang_flag_5);
      RB (t->base.u.bits.lang_flag_6);
      RB (t->base.u.bits.saturating_flag);
      RB (t->base.u.bits.unsigned_flag);
      RB (t->base.u.bits.packed_flag);
      RB (t->base.u.bits.user_align);
      RB (t->base.u.bits.nameless_flag);
      RB (t->base.u.bits.atomic_flag);
      break;
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE_COMMON))
    {
      RB (t->type_common.no_force_blk_flag);
      RB (t->type_common.needs_constructing_flag);
      RB (t->type_common.transparent_aggr_flag);
      RB (t->type_common.restrict_flag);
      RB (t->type_common.string_flag);
      RB (t->type_common.lang_flag_0);
      RB (t->type_common.lang_flag_1);
      RB (t->type_common.lang_flag_2);
      RB (t->type_common.lang_flag_3);
      RB (t->type_common.lang_flag_4);
      RB (t->type_common.lang_flag_5);
      RB (t->type_common.lang_flag_6);
      RB (t->type_common.typeless_storage);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_COMMON))
    {
      RB (t->decl_common.nonlocal_flag);
      RB (t->decl_common.virtual_flag);
      RB (t->decl_common.ignored_flag);
      RB (t->decl_common.abstract_flag);
      RB (t->decl_common.artificial_flag);
      RB (t->decl_common.preserve_flag);
      RB (t->decl_common.debug_expr_is_from);
      RB (t->decl_common.lang_flag_0);
      RB (t->decl_common.lang_flag_1);
      RB (t->decl_common.lang_flag_2);
      RB (t->decl_common.lang_flag_3);
      RB (t->decl_common.lang_flag_4);
      RB (t->decl_common.lang_flag_5);
      RB (t->decl_common.lang_flag_6);
      RB (t->decl_common.lang_flag_7);
      RB (t->decl_common.lang_flag_8);
      RB (t->decl_common.decl_flag_0);
      RB (t->decl_common.decl_flag_1);
      RB (t->decl_common.decl_flag_2);
      RB (t->decl_common.decl_flag_3);
      RB (t->decl_common.gimple_reg_flag);
      RB (t->decl_common.decl_by_reference_flag);
      RB (t->decl_common.decl_read_flag);
      RB (t->decl_common.decl_nonshareable_flag);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_WITH_VIS))
    {
      RB (t->decl_with_vis.defer_output);
      RB (t->decl_with_vis.hard_register);
      RB (t->decl_with_vis.common_flag);
      RB (t->decl_with_vis.in_text_section);
      RB (t->decl_with_vis.in_constant_pool);
      RB (t->decl_with_vis.dllimport_flag);
      RB (t->decl_with_vis.weak_flag);
      RB (t->decl_with_vis.seen_in_bind_expr);
      RB (t->decl_with_vis.comdat_flag);
      RB (t->decl_with_vis.visibility_specified);
      RB (t->decl_with_vis.comdat_flag);
      RB (t->decl_with_vis.init_priority_p);
      RB (t->decl_with_vis.shadowed_for_var_p);
      RB (t->decl_with_vis.cxx_constructor);
      RB (t->decl_with_vis.cxx_destructor);
      RB (t->decl_with_vis.final);
      RB (t->decl_with_vis.regdecl_flag);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_FUNCTION_DECL))
    {
      RB (t->function_decl.static_ctor_flag);
      RB (t->function_decl.static_dtor_flag);
      RB (t->function_decl.uninlinable);
      RB (t->function_decl.possibly_inlined);
      RB (t->function_decl.novops_flag);
      RB (t->function_decl.returns_twice_flag);
      RB (t->function_decl.malloc_flag);
      RB (t->function_decl.declared_inline_flag);
      RB (t->function_decl.no_inline_warning_flag);
      RB (t->function_decl.no_instrument_function_entry_exit);
      RB (t->function_decl.no_limit_stack);
      RB (t->function_decl.disregard_inline_limits);
      RB (t->function_decl.pure_flag);
      RB (t->function_decl.looping_const_or_pure_flag);
      
      RB (t->function_decl.has_debug_args_flag);
      RB (t->function_decl.versioned_function);

      /* decl_type is a (misnamed) 2 bit discriminator.	 */
      unsigned kind = 0;
      kind |= unsigned (b ()) << 0;
      kind |= unsigned (b ()) << 1;
      t->function_decl.decl_type = function_decl_type (kind);
    }
#undef RB
  return !get_overrun ();
}

void
trees_out::lang_decl_bools (tree t)
{
#define WB(X) (b (X))
  const struct lang_decl *lang = DECL_LANG_SPECIFIC (t);

  WB (lang->u.base.language == lang_cplusplus);
  WB ((lang->u.base.use_template >> 0) & 1);
  WB ((lang->u.base.use_template >> 1) & 1);
  /* Vars stop being not really extern */
  WB (lang->u.base.not_really_extern
      && (TREE_CODE (t) != VAR_DECL
	  || DECL_VTABLE_OR_VTT_P (t) || DECL_WEAK (t)));
  WB (lang->u.base.initialized_in_class);
  WB (lang->u.base.threadprivate_or_deleted_p);
  WB (lang->u.base.anticipated_p);
  WB (lang->u.base.friend_or_tls);
  WB (lang->u.base.unknown_bound_p);
  WB (lang->u.base.odr_used); // FIXME: Should this be written?
  WB (lang->u.base.concept_p);
  WB (lang->u.base.var_declared_inline_p);
  WB (lang->u.base.dependent_init_p);
  gcc_checking_assert (!(*modules)[lang->u.base.module_origin]->remap);
  WB (lang->u.base.module_purview_p);
  switch (lang->u.base.selector)
    {
    default:
      gcc_unreachable ();

    case lds_fn:  /* lang_decl_fn.  */
      WB (lang->u.fn.global_ctor_p);
      WB (lang->u.fn.global_dtor_p);
      WB (lang->u.fn.static_function);
      WB (lang->u.fn.pure_virtual);
      WB (lang->u.fn.defaulted_p);
      WB (lang->u.fn.has_in_charge_parm_p);
      WB (lang->u.fn.has_vtt_parm_p);
      /* There shouldn't be a pending inline at this point.  */
      gcc_assert (!lang->u.fn.pending_inline_p);
      WB (lang->u.fn.nonconverting);
      WB (lang->u.fn.thunk_p);
      WB (lang->u.fn.this_thunk_p);
      WB (lang->u.fn.hidden_friend_p);
      WB (lang->u.fn.omp_declare_reduction_p);
      WB (lang->u.fn.has_dependent_explicit_spec_p);
      WB (lang->u.fn.immediate_fn_p);
      WB (lang->u.fn.maybe_deleted);
      /* FALLTHROUGH.  */

    case lds_min:  /* lang_decl_min.  */
      /* No bools.  */
      break;

    case lds_ns:  /* lang_decl_ns.  */
      /* No bools.  */
      break;

    case lds_parm:  /* lang_decl_parm.  */
      /* No bools.  */
      break;
    }
#undef WB
}

bool
trees_in::lang_decl_bools (tree t)
{
#define RB(X) ((X) = b ())
  struct lang_decl *lang = DECL_LANG_SPECIFIC (t);

  lang->u.base.language = b () ? lang_cplusplus : lang_c;
  unsigned v;
  v = b () << 0;
  v |= b () << 1;
  lang->u.base.use_template = v;
  RB (lang->u.base.not_really_extern);
  RB (lang->u.base.initialized_in_class);
  RB (lang->u.base.threadprivate_or_deleted_p);
  RB (lang->u.base.anticipated_p);
  RB (lang->u.base.friend_or_tls);
  RB (lang->u.base.unknown_bound_p);
  RB (lang->u.base.odr_used);
  RB (lang->u.base.concept_p);
  RB (lang->u.base.var_declared_inline_p);
  RB (lang->u.base.dependent_init_p);
  lang->u.base.module_origin = state->mod;
  RB (lang->u.base.module_purview_p);
  switch (lang->u.base.selector)
    {
    default:
      gcc_unreachable ();

    case lds_fn:  /* lang_decl_fn.  */
      RB (lang->u.fn.global_ctor_p);
      RB (lang->u.fn.global_dtor_p);
      RB (lang->u.fn.static_function);
      RB (lang->u.fn.pure_virtual);
      RB (lang->u.fn.defaulted_p);
      RB (lang->u.fn.has_in_charge_parm_p);
      RB (lang->u.fn.has_vtt_parm_p);
      RB (lang->u.fn.nonconverting);
      RB (lang->u.fn.thunk_p);
      RB (lang->u.fn.this_thunk_p);
      RB (lang->u.fn.hidden_friend_p);
      RB (lang->u.fn.omp_declare_reduction_p);
      RB (lang->u.fn.has_dependent_explicit_spec_p);
      RB (lang->u.fn.immediate_fn_p);
      RB (lang->u.fn.maybe_deleted);
      /* FALLTHROUGH.  */

    case lds_min:  /* lang_decl_min.  */
      /* No bools.  */
      break;

    case lds_ns:  /* lang_decl_ns.  */
      /* No bools.  */
      break;

    case lds_parm:  /* lang_decl_parm.  */
      /* No bools.  */
      break;
    }
#undef RB
  return !get_overrun ();
}

void
trees_out::lang_type_bools (tree t)
{
#define WB(X) (b (X))
  const struct lang_type *lang = TYPE_LANG_SPECIFIC (t);

  WB (lang->has_type_conversion);
  WB (lang->has_copy_ctor);
  WB (lang->has_default_ctor);
  WB (lang->const_needs_init);
  WB (lang->ref_needs_init);
  WB (lang->has_const_copy_assign);
  WB ((lang->use_template >> 0) & 1);
  WB ((lang->use_template >> 1) & 1);

  WB (lang->has_mutable);
  WB (lang->com_interface);
  WB (lang->non_pod_class);
  WB (lang->nearly_empty_p);
  WB (lang->user_align);
  WB (lang->has_copy_assign);
  WB (lang->has_new);
  WB (lang->has_array_new);
  WB ((lang->gets_delete >> 0) & 1);
  WB ((lang->gets_delete >> 1) & 1);
  // Interfaceness is recalculated upon reading.  May have to revisit?
  // lang->interface_only
  // lang->interface_unknown
  WB (lang->contains_empty_class_p);
  WB (lang->anon_aggr);
  WB (lang->non_zero_init);
  WB (lang->empty_p);
  WB (lang->vec_new_uses_cookie);
  WB (lang->declared_class);
  WB (lang->diamond_shaped);
  WB (lang->repeated_base);
  gcc_assert (!lang->being_defined);
  // lang->debug_requested
  WB (lang->fields_readonly);
  WB (lang->ptrmemfunc_flag);
  WB (lang->lazy_default_ctor);
  WB (lang->lazy_copy_ctor);
  WB (lang->lazy_copy_assign);
  WB (lang->lazy_destructor);
  WB (lang->has_const_copy_ctor);
  WB (lang->has_complex_copy_ctor);
  WB (lang->has_complex_copy_assign);
  WB (lang->non_aggregate);
  WB (lang->has_complex_dflt);
  WB (lang->has_list_ctor);
  WB (lang->non_std_layout);
  WB (lang->is_literal);
  WB (lang->lazy_move_ctor);
  WB (lang->lazy_move_assign);
  WB (lang->has_complex_move_ctor);
  WB (lang->has_complex_move_assign);
  WB (lang->has_constexpr_ctor);
  WB (lang->unique_obj_representations);
  WB (lang->unique_obj_representations_set);
#undef WB
}

bool
trees_in::lang_type_bools (tree t)
{
#define RB(X) ((X) = b ())
  struct lang_type *lang = TYPE_LANG_SPECIFIC (t);

  RB (lang->has_type_conversion);
  RB (lang->has_copy_ctor);
  RB (lang->has_default_ctor);
  RB (lang->const_needs_init);
  RB (lang->ref_needs_init);
  RB (lang->has_const_copy_assign);
  unsigned v;
  v = b () << 0;
  v |= b () << 1;
  lang->use_template = v;

  RB (lang->has_mutable);
  RB (lang->com_interface);
  RB (lang->non_pod_class);
  RB (lang->nearly_empty_p);
  RB (lang->user_align);
  RB (lang->has_copy_assign);
  RB (lang->has_new);
  RB (lang->has_array_new);
  v = b () << 0;
  v |= b () << 1;
  lang->gets_delete = v;
  // lang->interface_only
  // lang->interface_unknown
  lang->interface_unknown = true; // Redetermine interface
  RB (lang->contains_empty_class_p);
  RB (lang->anon_aggr);
  RB (lang->non_zero_init);
  RB (lang->empty_p);
  RB (lang->vec_new_uses_cookie);
  RB (lang->declared_class);
  RB (lang->diamond_shaped);
  RB (lang->repeated_base);
  gcc_assert (!lang->being_defined);
  gcc_assert (!lang->debug_requested);
  RB (lang->fields_readonly);
  RB (lang->ptrmemfunc_flag);
  RB (lang->lazy_default_ctor);
  RB (lang->lazy_copy_ctor);
  RB (lang->lazy_copy_assign);
  RB (lang->lazy_destructor);
  RB (lang->has_const_copy_ctor);
  RB (lang->has_complex_copy_ctor);
  RB (lang->has_complex_copy_assign);
  RB (lang->non_aggregate);
  RB (lang->has_complex_dflt);
  RB (lang->has_list_ctor);
  RB (lang->non_std_layout);
  RB (lang->is_literal);
  RB (lang->lazy_move_ctor);
  RB (lang->lazy_move_assign);
  RB (lang->has_complex_move_ctor);
  RB (lang->has_complex_move_assign);
  RB (lang->has_constexpr_ctor);
  RB (lang->unique_obj_representations);
  RB (lang->unique_obj_representations_set);
#undef RB
  return !get_overrun ();
}

/* Read & write the core values and pointers.  */

void
trees_out::core_vals (tree t)
{
#define WU(X) (u (X))
#define WT(X) (tree_node (X))
  tree_code code = TREE_CODE (t);

  /* First by shape of the tree.  */

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_MINIMAL))
    {
      /* Write this early, for better log information.  */
      WT (t->decl_minimal.name);
      if (!DECL_TEMPLATE_PARM_P (t))
	WT (t->decl_minimal.context);

      state->write_location (*this, t->decl_minimal.locus);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE_COMMON))
    {
      gcc_checking_assert (CODE_CONTAINS_STRUCT (code, TS_TYPE_NON_COMMON));

      /* We only stream the main variant.  */
      gcc_checking_assert (TYPE_MAIN_VARIANT (t) == t);

      /* Stream the name & context first, for better log information  */
      WT (t->type_common.name);
      WT (t->type_common.context);

      /* By construction we want to make sure we have the canonical
	 and main variants already in the type table, so emit them
	 now.  */
      WT (t->type_common.main_variant);

      tree canonical = t->type_common.canonical;
      if (canonical && DECL_TEMPLATE_PARM_P (TYPE_NAME (t)))
	/* We do not want to wander into different templates.
	   Reconstructed on stream in.  */
	canonical = t;
      WT (canonical);

      /* type_common.next_variant is internally manipulated.  */
      /* type_common.pointer_to, type_common.reference_to.  */

      if (streaming_p ())
	{
	  WU (t->type_common.precision);
	  WU (t->type_common.contains_placeholder_bits);
	  WU (t->type_common.mode);
	  WU (t->type_common.align);
	}

      if (!RECORD_OR_UNION_CODE_P (code))
	{
	  WT (t->type_common.size);
	  WT (t->type_common.size_unit);
	}
      WT (t->type_common.attributes);

      WT (t->type_common.common.chain); /* TYPE_STUB_DECL.  */
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPED))
    {
      tree type = t->typed.type;
      unsigned prec = 0;

      switch (code)
	{
	default:
	  break;

	case TEMPLATE_DECL:
	  /* We fill in the template's type separately.  */
	  type = NULL_TREE;
	  break;

	case TYPE_DECL:
	  if (DECL_ORIGINAL_TYPE (t)
	      && t != TYPE_NAME (TYPE_MAIN_VARIANT (type)))
	    /* This is a typedef.  We set its type separately.  */
	    type = NULL_TREE;
	  break;

	case ENUMERAL_TYPE:
	  if (type && !ENUM_FIXED_UNDERLYING_TYPE_P (t))
	    {
	      /* Type is a restricted range integer type derived from the
		 integer_types.  Find the right one.  */
	      prec = TYPE_PRECISION (type);
	      tree name = DECL_NAME (TYPE_NAME (type));

	      for (unsigned itk = itk_none; itk--;)
		if (integer_types[itk]
		    && DECL_NAME (TYPE_NAME (integer_types[itk])) == name)
		  {
		    type = integer_types[itk];
		    break;
		  }
	      gcc_assert (type != t->typed.type);
	    }
	  break;
	}

      WT (type);
      if (prec && streaming_p ())
	WU (prec);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_COMMON))
    {
      if (streaming_p ())
	{
	  WU (t->decl_common.mode);
	  WU (t->decl_common.off_align);
	  WU (t->decl_common.align);
	}

      /* For templates these hold instantiation (partial and/or
	 specialization) information.  */
      if (code != TEMPLATE_DECL)
	{
	  WT (t->decl_common.size);
	  WT (t->decl_common.size_unit);
	}

      WT (t->decl_common.attributes);
      WT (t->decl_common.abstract_origin);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_WITH_VIS))
    {
      WT (t->decl_with_vis.assembler_name);
      if (streaming_p ())
	WU (t->decl_with_vis.visibility);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE_NON_COMMON))
    {
      /* Records and unions hold FIELDS, VFIELD & BINFO on these
	 things.  */
      if (!RECORD_OR_UNION_CODE_P (code) && code != ENUMERAL_TYPE)
	{
	  /* Don't write the cached values vector.  */
	  WT (TYPE_CACHED_VALUES_P (t) ? NULL_TREE : t->type_non_common.values);
	  WT (t->type_non_common.maxval);
	  WT (t->type_non_common.minval);
	}

      WT (t->type_non_common.lang_1);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_EXP))
    {
      state->write_location (*this, t->exp.locus);

      bool vl = TREE_CODE_CLASS (code) == tcc_vl_exp;
      for (unsigned ix = (vl ? VL_EXP_OPERAND_LENGTH (t)
			  : TREE_OPERAND_LENGTH (t)); ix-- != vl;)
	WT (TREE_OPERAND (t, ix));
    }
  else
    /* The CODE_CONTAINS tables were inaccurate when I started.  */
    gcc_checking_assert (TREE_CODE_CLASS (code) != tcc_expression
			 && TREE_CODE_CLASS (code) != tcc_binary
			 && TREE_CODE_CLASS (code) != tcc_unary
			 && TREE_CODE_CLASS (code) != tcc_reference
			 && TREE_CODE_CLASS (code) != tcc_comparison
			 && TREE_CODE_CLASS (code) != tcc_statement
			 && TREE_CODE_CLASS (code) != tcc_vl_exp);

  /* Then by CODE.  Special cases and/or 1:1 tree shape
     correspondance. */
  switch (code)
    {
    default:
      break;

    case ARGUMENT_PACK_SELECT:  /* Transient during instantiation.  */
    case DEFERRED_PARSE:
    case IDENTIFIER_NODE:
    case MODULE_VECTOR:
    case SSA_NAME:
    case TRANSLATION_UNIT_DECL:
    case USERDEF_LITERAL:  /* Expanded during parsing.  */
      gcc_unreachable (); /* Should never meet.  */

      /* Constants.  */
    case COMPLEX_CST:
      WT (TREE_REALPART (t));
      WT (TREE_IMAGPART (t));
      break;

    case FIXED_CST:
      gcc_unreachable (); /* Not supported in C++.  */

    case INTEGER_CST:
      if (streaming_p ())
	{
	  unsigned num = TREE_INT_CST_EXT_NUNITS (t);
	  for (unsigned ix = 0; ix != num; ix++)
	    wu (TREE_INT_CST_ELT (t, ix));
	}
      break;

    case POLY_INT_CST:
      gcc_unreachable (); /* Not supported in C++.  */

    case REAL_CST:
      if (streaming_p ())
	buf (TREE_REAL_CST_PTR (t), sizeof (real_value));
      break;

    case STRING_CST:
      /* Streamed during start.  */
      break;

    case VECTOR_CST:
      for (unsigned ix = vector_cst_encoded_nelts (t); ix--;)
	WT (VECTOR_CST_ENCODED_ELT (t, ix));
      break;

      /* Decls.  */
    case RESULT_DECL:
      // FIXME?
      break;

    case VAR_DECL:
      if (DECL_CONTEXT (t)
	  && TREE_CODE (DECL_CONTEXT (t)) != FUNCTION_DECL)
	break;
      /* FALLTHROUGH  */

    case PARM_DECL:
      if (DECL_HAS_VALUE_EXPR_P (t))
	WT (DECL_VALUE_EXPR (t));
      /* FALLTHROUGH  */

    case CONST_DECL:
      WT (t->decl_common.initial);
      break;

    case FIELD_DECL:
      WT (t->field_decl.offset);
      WT (t->field_decl.bit_field_type);
      WT (t->field_decl.qualifier); /* bitfield unit.  */
      WT (t->field_decl.bit_offset);
      WT (t->field_decl.fcontext);
      break;

    case LABEL_DECL:
      if (streaming_p ())
	{
	  WU (t->label_decl.label_decl_uid);
	  WU (t->label_decl.eh_landing_pad_nr);
	}
      break;

    case FUNCTION_DECL:
      if (streaming_p ())
	{
	  /* Builtins can be streamed by value when a header declares
	     them.  */
	  // FIXME: Perhaps it's just BUILT_IN_NORMAL that's needed here?
	  WU (DECL_BUILT_IN_CLASS (t));
	  if (DECL_BUILT_IN_CLASS (t) != NOT_BUILT_IN)
	    WU (DECL_UNCHECKED_FUNCTION_CODE (t));
	}

      WT (t->function_decl.personality);
      WT (t->function_decl.function_specific_target);
      WT (t->function_decl.function_specific_optimization);
      WT (t->function_decl.vindex);
      break;

    case TYPE_DECL: /* DECL_ORIGINAL_TYPE */
    case USING_DECL: /* USING_DECL_SCOPE  */
      WT (t->decl_non_common.result);
      break;

      /* Miscellaneous common nodes.  */
    case BLOCK:
      state->write_location (*this, t->block.locus);
      state->write_location (*this, t->block.end_locus);
      chained_decls (t->block.vars);
      /* nonlocalized_vars is a middle-end thing.  */
      WT (t->block.subblocks);
      WT (t->block.supercontext);
      WT (t->block.abstract_origin);
      /* fragment_origin, fragment_chain are middle-end things.  */
      WT (t->block.chain);
      // FIXME: block_num, die?
      break;

    case CALL_EXPR:
      if (streaming_p ())
	WU (t->base.u.ifn);
      break;

    case CONSTRUCTOR:
      {
	unsigned len = vec_safe_length (t->constructor.elts);
	if (streaming_p ())
	  WU (len);
	if (len)
	  for (unsigned ix = 0; ix != len; ix++)
	    {
	      const constructor_elt &elt = (*t->constructor.elts)[ix];

	      WT (elt.index);
	      WT (elt.value);
	    }
      }
      break;

    case OMP_CLAUSE:
      {
	/* The ompcode is serialized in start.  */
	if (streaming_p ())
	  WU (t->omp_clause.subcode.dimension);
	state->write_location (*this, t->omp_clause.locus);

	unsigned len = omp_clause_num_ops[OMP_CLAUSE_CODE (t)];
	for (unsigned ix = 0; ix != len; ix++)
	  WT (t->omp_clause.ops[ix]);
      }
      break;

    case OPTIMIZATION_NODE:
      gcc_unreachable (); // FIXME
      break;

    case STATEMENT_LIST:
      for (tree_stmt_iterator iter = tsi_start (t);
	   !tsi_end_p (iter); tsi_next (&iter))
	if (tree stmt = tsi_stmt (iter))
	  WT (stmt);
      WT (NULL_TREE);
      break;

    case TARGET_OPTION_NODE:
      gcc_unreachable (); // FIXME
      break;

    case TREE_BINFO:
      {
	WT (t->binfo.common.chain);
	WT (t->binfo.offset);
	WT (t->binfo.inheritance);
	WT (t->binfo.vtable);
	WT (t->binfo.virtuals);
	WT (t->binfo.vptr_field);
	WT (t->binfo.vtt_subvtt);
	WT (t->binfo.vtt_vptr);

	tree_vec (BINFO_BASE_ACCESSES (t));
	unsigned num = vec_safe_length (BINFO_BASE_ACCESSES (t));
	for (unsigned ix = 0; ix != num; ix++)
	  WT (BINFO_BASE_BINFO (t, ix));
      }
      break;

    case TREE_LIST:
      WT (t->list.purpose);
      WT (t->list.value);
      WT (t->list.common.chain);
      break;

    case TREE_VEC:
      for (unsigned ix = TREE_VEC_LENGTH (t); ix--;)
	WT (TREE_VEC_ELT (t, ix));
      /* We stash NON_DEFAULT_TEMPLATE_ARGS_COUNT on TREE_CHAIN!  */
      gcc_checking_assert (!t->type_common.common.chain
			   || (TREE_CODE (t->type_common.common.chain)
			       == INTEGER_CST));
      WT (t->type_common.common.chain);
      break;

      /* C++-specific nodes ...  */
    case BASELINK:
      WT (((lang_tree_node *)t)->baselink.binfo);
      WT (((lang_tree_node *)t)->baselink.functions);
      WT (((lang_tree_node *)t)->baselink.access_binfo);
      break;

    case CONSTRAINT_INFO:
      WT (((lang_tree_node *)t)->constraint_info.template_reqs);
      WT (((lang_tree_node *)t)->constraint_info.declarator_reqs);
      WT (((lang_tree_node *)t)->constraint_info.associated_constr);
      break;

    case DEFERRED_NOEXCEPT:
      WT (((lang_tree_node *)t)->deferred_noexcept.pattern);
      WT (((lang_tree_node *)t)->deferred_noexcept.args);
      break;

    case LAMBDA_EXPR:
      WT (((lang_tree_node *)t)->lambda_expression.capture_list);
      WT (((lang_tree_node *)t)->lambda_expression.this_capture);
      WT (((lang_tree_node *)t)->lambda_expression.extra_scope);
      /* pending_proxies is a parse-time thing.  */
      gcc_assert (!((lang_tree_node *)t)->lambda_expression.pending_proxies);
      state->write_location
	(*this, ((lang_tree_node *)t)->lambda_expression.locus);
      if (streaming_p ())
	{
	  WU (((lang_tree_node *)t)->lambda_expression.default_capture_mode);
	  WU (((lang_tree_node *)t)->lambda_expression.discriminator);
	}
      break;

    case OVERLOAD:
      WT (((lang_tree_node *)t)->overload.function);
      WT (t->common.chain);
      break;
      
    case PTRMEM_CST:
      WT (((lang_tree_node *)t)->ptrmem.member);
      break;

    case STATIC_ASSERT:
      WT (((lang_tree_node *)t)->static_assertion.condition);
      WT (((lang_tree_node *)t)->static_assertion.message);
      state->write_location
	(*this, ((lang_tree_node *)t)->static_assertion.location);
      break;

    case TEMPLATE_DECL:
      /* Streamed with the template_decl node itself.  */
      gcc_checking_assert
      	(TREE_VISITED (((lang_tree_node *)t)->template_decl.arguments));
      gcc_checking_assert
	(TREE_VISITED (((lang_tree_node *)t)->template_decl.result));
      if (DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (t))
	WT (DECL_CHAIN (t));
      break;

    case TEMPLATE_INFO:
      {
	WT (((lang_tree_node *)t)->template_info.tmpl);
	WT (((lang_tree_node *)t)->template_info.args);

	const vec<qualified_typedef_usage_t, va_gc> *ac
	  = (((lang_tree_node *)t)
	     ->template_info.typedefs_needing_access_checking);
	unsigned len = vec_safe_length (ac);
	if (streaming_p ())
	  u (len);
	if (len)
	  {
	    for (unsigned ix = 0; ix != len; ix++)
	      {
		const qualified_typedef_usage_t &m = (*ac)[ix];
		WT (m.typedef_decl);
		WT (m.context);
		state->write_location (*this, m.locus);
	      }
	  }
      }
      break;

    case TEMPLATE_PARM_INDEX:
      if (streaming_p ())
	{
	  WU (((lang_tree_node *)t)->tpi.index);
	  WU (((lang_tree_node *)t)->tpi.level);
	  WU (((lang_tree_node *)t)->tpi.orig_level);
	}
      WT (((lang_tree_node *)t)->tpi.decl);
      /* TEMPLATE_PARM_DESCENDANTS (AKA TREE_CHAIN) is an internal
	 cache, do not stream.  */
      break;
      
    case TRAIT_EXPR:
      WT (((lang_tree_node *)t)->trait_expression.type1);
      WT (((lang_tree_node *)t)->trait_expression.type2);
      if (streaming_p ())
	WU (((lang_tree_node *)t)->trait_expression.kind);
      break;
    }

#undef WT
#undef WU
}

bool
trees_in::core_vals (tree t)
{
#define RU(X) ((X) = u ())
#define RUC(T,X) ((X) = T (u ()))
#define RT(X) ((X) = tree_node ())
  tree_code code = TREE_CODE (t);

  /* First by tree shape.  */
  if (CODE_CONTAINS_STRUCT (code, TS_DECL_MINIMAL))
    {
      RT (t->decl_minimal.name);
      if (!DECL_TEMPLATE_PARM_P (t))
	RT (t->decl_minimal.context);

      /* Don't zap the locus just yet, we don't record it correctly
	 and thus lose all location information.  */
      t->decl_minimal.locus = state->read_location (*this);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE_COMMON))
    {
      RT (t->type_common.name);
      RT (t->type_common.context);

      RT (t->type_common.main_variant);
      RT (t->type_common.canonical);

      /* type_common.next_variant is internally manipulated.  */
      /* type_common.pointer_to, type_common.reference_to.  */

      RU (t->type_common.precision);
      RU (t->type_common.contains_placeholder_bits);
      RUC (machine_mode, t->type_common.mode);
      RU (t->type_common.align);

      if (!RECORD_OR_UNION_CODE_P (code))
	{
	  RT (t->type_common.size);
	  RT (t->type_common.size_unit);
	}
      RT (t->type_common.attributes);

      RT (t->type_common.common.chain); /* TYPE_STUB_DECL.  */
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPED))
    {
      tree type = tree_node ();

      if (type && code == ENUMERAL_TYPE && !ENUM_FIXED_UNDERLYING_TYPE_P (t))
	{
	  unsigned precision = u ();

	  type = build_distinct_type_copy (type);
	  TYPE_PRECISION (type) = precision;
	  set_min_and_max_values_for_integral_type (type, precision,
						    TYPE_SIGN (type));
	}

      if (code != TEMPLATE_DECL)
	t->typed.type = type;
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_COMMON))
    {
      RUC (machine_mode, t->decl_common.mode);
      RU (t->decl_common.off_align);
      RU (t->decl_common.align);

      if (code != TEMPLATE_DECL)
	{
	  RT (t->decl_common.size);
	  RT (t->decl_common.size_unit);
	}

      RT (t->decl_common.attributes);
      RT (t->decl_common.abstract_origin);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_DECL_WITH_VIS))
    {
      RT (t->decl_with_vis.assembler_name);
      RUC (symbol_visibility, t->decl_with_vis.visibility);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_TYPE_NON_COMMON))
    {
      /* Records and unions hold FIELDS, VFIELD & BINFO on these
	 things.  */
      if (!RECORD_OR_UNION_CODE_P (code) && code != ENUMERAL_TYPE)
	{
	  /* This is not clobbering TYPE_CACHED_VALUES, because this
	     is a new type being read in, so there aren't any.  */
	  gcc_checking_assert (!TYPE_CACHED_VALUES_P (t));
	  RT (t->type_non_common.values);
	  RT (t->type_non_common.maxval);
	  RT (t->type_non_common.minval);
	}

      RT (t->type_non_common.lang_1);
    }

  if (CODE_CONTAINS_STRUCT (code, TS_EXP))
    {
      t->exp.locus = state->read_location (*this);

      bool vl = TREE_CODE_CLASS (code) == tcc_vl_exp;
      for (unsigned ix = (vl ? VL_EXP_OPERAND_LENGTH (t)
			  : TREE_OPERAND_LENGTH (t)); ix-- != vl;)
	RT (TREE_OPERAND (t, ix));
    }

  /* Then by CODE.  Special cases and/or 1:1 tree shape
     correspondance. */
  switch (code)
    {
    default:
      break;

    case ARGUMENT_PACK_SELECT:
    case DEFERRED_PARSE:
    case IDENTIFIER_NODE:
    case MODULE_VECTOR:
    case SSA_NAME:
    case TRANSLATION_UNIT_DECL:
    case USERDEF_LITERAL:
      return false; /* Should never meet.  */

      /* Constants.  */
    case COMPLEX_CST:
      RT (TREE_REALPART (t));
      RT (TREE_IMAGPART (t));
      break;

    case FIXED_CST:
      /* Not suported in C++.  */
      return false;

    case INTEGER_CST:
      {
	unsigned num = TREE_INT_CST_EXT_NUNITS (t);
	for (unsigned ix = 0; ix != num; ix++)
	  TREE_INT_CST_ELT (t, ix) = wu ();
      }
      break;

    case POLY_INT_CST:
      /* Not suported in C++.  */
      return false;

    case REAL_CST:
      if (const void *bytes = buf (sizeof (real_value)))
	TREE_REAL_CST_PTR (t)
	  = reinterpret_cast<real_value *> (memcpy (ggc_alloc<real_value> (),
						    bytes, sizeof (real_value)));
      break;

    case STRING_CST:
      /* Streamed during start.  */
      break;

    case VECTOR_CST:
      for (unsigned ix = vector_cst_encoded_nelts (t); ix--;)
	RT (VECTOR_CST_ENCODED_ELT (t, ix));
      break;

      /* Decls.  */
    case RESULT_DECL:
      // FIXME?
      break;

    case VAR_DECL:
      if (DECL_CONTEXT (t)
	  && TREE_CODE (DECL_CONTEXT (t)) != FUNCTION_DECL)
	break;
      /* FALLTHROUGH  */

    case PARM_DECL:
      if (DECL_HAS_VALUE_EXPR_P (t))
	{
	  tree val = tree_node ();
	  SET_DECL_VALUE_EXPR (t, val);
	}
      /* FALLTHROUGH  */

    case CONST_DECL:
      RT (t->decl_common.initial);
      break;

    case FIELD_DECL:
      RT (t->field_decl.offset);
      RT (t->field_decl.bit_field_type);
      RT (t->field_decl.qualifier);
      RT (t->field_decl.bit_offset);
      RT (t->field_decl.fcontext);
      break;

    case LABEL_DECL:
      RU (t->label_decl.label_decl_uid);
      RU (t->label_decl.eh_landing_pad_nr);
      break;
  
    case FUNCTION_DECL:
      {
	unsigned bltin = u ();
	t->function_decl.built_in_class = built_in_class (bltin);
	if (bltin != NOT_BUILT_IN)
	  {
	    bltin = u ();
	    DECL_UNCHECKED_FUNCTION_CODE (t) = built_in_function (bltin);
	  }

	RT (t->function_decl.personality);
	RT (t->function_decl.function_specific_target);
	RT (t->function_decl.function_specific_optimization);
	RT (t->function_decl.vindex);
      }
      break;

    case TYPE_DECL: /* DECL_ORIGINAL_TYPE */
    case USING_DECL: /* USING_DECL_SCOPE  */
      RT (t->decl_non_common.result);
      break;

      /* Miscellaneous common nodes.  */
    case BLOCK:
      t->block.locus = state->read_location (*this);
      t->block.end_locus = state->read_location (*this);
      t->block.vars = chained_decls ();
      /* nonlocalized_vars is middle-end.  */
      RT (t->block.subblocks);
      RT (t->block.supercontext);
      RT (t->block.abstract_origin);
      /* fragment_origin, fragment_chain are middle-end.  */
      RT (t->block.chain);
      // block_num, die?
      break;

    case CALL_EXPR:
      RUC (internal_fn, t->base.u.ifn);
      break;

    case CONSTRUCTOR:
      if (unsigned len = u ())
	{
	  vec_alloc (t->constructor.elts, len);
	  for (unsigned ix = 0; ix != len; ix++)
	    {
	      constructor_elt elt;

	      RT (elt.index);
	      RT (elt.value);
	      t->constructor.elts->quick_push (elt);
	    }
	}
      break;

    case OMP_CLAUSE:
      {
	RU (t->omp_clause.subcode.dimension);
	t->omp_clause.locus = state->read_location (*this);

	unsigned len = omp_clause_num_ops[OMP_CLAUSE_CODE (t)];
	for (unsigned ix = 0; ix != len; ix++)
	  RT (t->omp_clause.ops[ix]);
      }
      break;

    case OPTIMIZATION_NODE:
      gcc_unreachable (); // FIXME
      break;

    case STATEMENT_LIST:
      {
	tree_stmt_iterator iter = tsi_start (t);
	for (tree stmt; RT (stmt);)
	  tsi_link_after (&iter, stmt, TSI_CONTINUE_LINKING);
      }
      break;

    case TARGET_OPTION_NODE:
      gcc_unreachable (); // FIXME
      break;

    case TREE_BINFO:
      RT (t->binfo.common.chain);
      RT (t->binfo.offset);
      RT (t->binfo.inheritance);
      RT (t->binfo.vtable);
      RT (t->binfo.virtuals);
      RT (t->binfo.vptr_field);
      RT (t->binfo.vtt_subvtt);
      RT (t->binfo.vtt_vptr);

      BINFO_BASE_ACCESSES (t) = tree_vec ();
      if (!get_overrun ())
	{
	  unsigned num = vec_safe_length (BINFO_BASE_ACCESSES (t));
	  for (unsigned ix = 0; ix != num; ix++)
	    BINFO_BASE_APPEND (t, tree_node ());
	}
      break;

    case TREE_LIST:
      RT (t->list.purpose);
      RT (t->list.value);
      RT (t->list.common.chain);
      break;

    case TREE_VEC:
      for (unsigned ix = TREE_VEC_LENGTH (t); ix--;)
	RT (TREE_VEC_ELT (t, ix));
      RT (t->type_common.common.chain);
      break;

      /* C++-specific nodes ...  */
    case BASELINK:
      RT (((lang_tree_node *)t)->baselink.binfo);
      RT (((lang_tree_node *)t)->baselink.functions);
      RT (((lang_tree_node *)t)->baselink.access_binfo);
      break;

    case CONSTRAINT_INFO:
      RT (((lang_tree_node *)t)->constraint_info.template_reqs);
      RT (((lang_tree_node *)t)->constraint_info.declarator_reqs);
      RT (((lang_tree_node *)t)->constraint_info.associated_constr);
      break;

    case DEFERRED_NOEXCEPT:
      RT (((lang_tree_node *)t)->deferred_noexcept.pattern);
      RT (((lang_tree_node *)t)->deferred_noexcept.args);
      break;

    case LAMBDA_EXPR:
      RT (((lang_tree_node *)t)->lambda_expression.capture_list);
      RT (((lang_tree_node *)t)->lambda_expression.this_capture);
      RT (((lang_tree_node *)t)->lambda_expression.extra_scope);
      /* lambda_expression.pending_proxies is NULL  */
      ((lang_tree_node *)t)->lambda_expression.locus
	= state->read_location (*this);
      RUC (cp_lambda_default_capture_mode_type,
	   ((lang_tree_node *)t)->lambda_expression.default_capture_mode);
      RU (((lang_tree_node *)t)->lambda_expression.discriminator);
      break;

    case OVERLOAD:
      RT (((lang_tree_node *)t)->overload.function);
      RT (t->common.chain);
      break;

    case PTRMEM_CST:
      RT (((lang_tree_node *)t)->ptrmem.member);
      break;

    case STATIC_ASSERT:
      RT (((lang_tree_node *)t)->static_assertion.condition);
      RT (((lang_tree_node *)t)->static_assertion.message);
      ((lang_tree_node *)t)->static_assertion.location
	= state->read_location (*this);
      break;

    case TEMPLATE_DECL:
      /* Streamed when reading the raw template decl itself.  */
      gcc_assert (((lang_tree_node *)t)->template_decl.arguments);
      gcc_assert (((lang_tree_node *)t)->template_decl.result);
      if (DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (t))
	RT (DECL_CHAIN (t));
      break;

    case TEMPLATE_INFO:
      RT (((lang_tree_node *)t)->template_info.tmpl);
      RT (((lang_tree_node *)t)->template_info.args);
      if (unsigned len = u ())
	{
	  vec<qualified_typedef_usage_t, va_gc> *ac;
	  vec_alloc (ac, len);
	  ((lang_tree_node *)t)->template_info.typedefs_needing_access_checking
	    = ac;
	  for (unsigned ix = 0; ix != len; ix++)
	    {
	      qualified_typedef_usage_t m;
	      RT (m.typedef_decl);
	      RT (m.context);
	      m.locus = state->read_location (*this);
	      ac->quick_push (m);
	    }
	}
      break;

    case TEMPLATE_PARM_INDEX:
      RU (((lang_tree_node *)t)->tpi.index);
      RU (((lang_tree_node *)t)->tpi.level);
      RU (((lang_tree_node *)t)->tpi.orig_level);
      RT (((lang_tree_node *)t)->tpi.decl);
      break;

    case TRAIT_EXPR:
      RT (((lang_tree_node *)t)->trait_expression.type1);
      RT (((lang_tree_node *)t)->trait_expression.type2);
      RUC (cp_trait_kind, ((lang_tree_node *)t)->trait_expression.kind);
      break;
    }

#undef RT
#undef RM
#undef RU
  return !get_overrun ();
}

void
trees_out::lang_decl_vals (tree t)
{
  const struct lang_decl *lang = DECL_LANG_SPECIFIC (t);
#define WU(X) (u (X))
#define WT(X) (tree_node (X))
  /* Module index already written.  */
  switch (lang->u.base.selector)
    {
    default:
      gcc_unreachable ();

    case lds_fn:  /* lang_decl_fn.  */
      if (streaming_p ())
	{
	  if (DECL_NAME (t) && IDENTIFIER_OVL_OP_P (DECL_NAME (t)))
	    WU (lang->u.fn.ovl_op_code);
	}

      if (DECL_CLASS_SCOPE_P (t))
	WT (lang->u.fn.context);

      if (lang->u.fn.thunk_p)
	{
	  /* The thunked-to function.  */
	  WT (lang->u.fn.befriending_classes);
	  if (streaming_p ())
	    wi (lang->u.fn.u5.fixed_offset);
	}
      else
	WT (lang->u.fn.u5.cloned_function);

      if (FNDECL_USED_AUTO (t))
	WT (lang->u.fn.u.saved_auto_return_type);

      /* FALLTHROUGH.  */

    case lds_min:  /* lang_decl_min.  */
      WT (lang->u.min.template_info);
      WT (lang->u.min.access);
      break;

    case lds_ns:  /* lang_decl_ns.  */
      break;

    case lds_parm:  /* lang_decl_parm.  */
      if (streaming_p ())
	{
	  WU (lang->u.parm.level);
	  WU (lang->u.parm.index);
	}
      break;
    }
#undef WU
#undef WT
}

bool
trees_in::lang_decl_vals (tree t)
{
  struct lang_decl *lang = DECL_LANG_SPECIFIC (t);
#define RU(X) ((X) = u ())
#define RT(X) ((X) = tree_node ())

  /* Module index already read.  */
  switch (lang->u.base.selector)
    {
    default:
      gcc_unreachable ();

    case lds_fn:  /* lang_decl_fn.  */
      {
	if (DECL_NAME (t) && IDENTIFIER_OVL_OP_P (DECL_NAME (t)))
	  {
	    unsigned code = u ();

	    /* Check consistency.  */
	    if (code >= OVL_OP_MAX
		|| (ovl_op_info[IDENTIFIER_ASSIGN_OP_P (DECL_NAME (t))][code]
		    .ovl_op_code) == OVL_OP_ERROR_MARK)
	      set_overrun ();
	    else
	      lang->u.fn.ovl_op_code = code;
	  }

	if (DECL_CLASS_SCOPE_P (t))
	  RT (lang->u.fn.context);

	if (lang->u.fn.thunk_p)
	  {
	    RT (lang->u.fn.befriending_classes);
	    lang->u.fn.u5.fixed_offset = wi ();
	  }
	else
	  RT (lang->u.fn.u5.cloned_function);

	if (FNDECL_USED_AUTO (t))
	  RT (lang->u.fn.u.saved_auto_return_type);
      }
      /* FALLTHROUGH.  */

    case lds_min:  /* lang_decl_min.  */
      RT (lang->u.min.template_info);
      RT (lang->u.min.access);
      break;

    case lds_ns:  /* lang_decl_ns.  */
      break;

    case lds_parm:  /* lang_decl_parm.  */
      RU (lang->u.parm.level);
      RU (lang->u.parm.index);
      break;
    }
#undef RU
#undef RT
  return !get_overrun ();
}

/* Most of the value contents of lang_type is streamed in
   define_class.  */

void
trees_out::lang_type_vals (tree t)
{
  const struct lang_type *lang = TYPE_LANG_SPECIFIC (t);
#define WU(X) (u (X))
#define WT(X) (tree_node (X))
  if (streaming_p ())
    WU (lang->align);
#undef WU
#undef WT
}

bool
trees_in::lang_type_vals (tree t)
{
  struct lang_type *lang = TYPE_LANG_SPECIFIC (t);
#define RU(X) ((X) = u ())
#define RT(X) ((X) = tree_node ())
  RU (lang->align);
#undef RU
#undef RT
  return !get_overrun ();
}

tree
trees_out::tree_binfo (tree binfo, int depth, bool via_virt)
{
  tree dom;

  if (tree inh = BINFO_INHERITANCE_CHAIN (binfo))
    {
      bool is_virt = BINFO_VIRTUAL_P (binfo);
      dom = tree_binfo (inh, depth + !via_virt, is_virt || via_virt);
      if (!via_virt && streaming_p ())
	{
	  vec<tree, va_gc> *binfo_vec;
	  if (is_virt)
	    /* A virtual base.  Look on the CLASSTYPE_VIRTUALS.  */
	    binfo_vec = CLASSTYPE_VBASECLASSES (dom);
	  else
	    /* Look along BINFO_BASE_BINFOS (inh).  */
	    binfo_vec = BINFO_BASE_BINFOS (inh);
	  unsigned ix;
	  for (ix = 0; (*binfo_vec)[ix] != binfo; ix++)
	    ;
	  dump (dumper::TREE)
	    && dump ("Wrote derived %sBINFO %u %N of %N",
		     is_virt ? "virtual " : "", ix, binfo, inh);
	  u (ix);
	}
    }
  else
    {
      dom = BINFO_TYPE (binfo);
      tree_node (dom);

      if (streaming_p ())
	{
	  dump (dumper::TREE) && dump ("Wrote dominating BINFO %N", dom);
	  i (via_virt ? -depth : depth);
	}
    }
  return dom;
}

tree
trees_in::tree_binfo ()
{
  tree dom = tree_node ();
  dump (dumper::TREE) && dump ("Read dominating binfo %N", dom);
  int depth = i ();
  tree binfo = TYPE_BINFO (dom);
  if (depth)
    {
      vec<tree, va_gc> *binfo_vec = NULL;
      if (depth < 0)
	{
	  /* A virtual base.  Look on the CLASSTYPE_VIRTUALS.  */
	  binfo_vec = CLASSTYPE_VBASECLASSES (dom);
	  depth = -depth;
	}
      for (; depth--; binfo_vec = NULL)
	{
	  if (!binfo_vec)
	    binfo_vec = BINFO_BASE_BINFOS (binfo);
	  unsigned ix = u ();
	  if (vec_safe_length (binfo_vec) < ix)
	    {
	      set_overrun ();
	      binfo = NULL_TREE;
	      break;
	    }
	  else
	    binfo = (*binfo_vec)[ix];
	  dump (dumper::TREE) && dump ("Read derived BINFO %N", binfo);
	}
    }
  return binfo;
}

/* Write out the bools of T, including information about any
   LANG_SPECIFIC information.  Including allocation of any lang
   specific object.  */

void
trees_out::tree_node_bools (tree t)
{
  gcc_checking_assert (streaming_p ());

  /* We should never stream a namespace.  */
  gcc_checking_assert (TREE_CODE (t) != NAMESPACE_DECL);

  core_bools (t);

  switch (TREE_CODE_CLASS (TREE_CODE (t)))
    {
    case tcc_declaration:
      {
	/* The only nameable decls we should stream out are those from
	   this module, a partition or the global module.  All other
	   decls should be by name.  */
#if CHECKING_P
	if (TREE_CODE (t) == TEMPLATE_DECL
	    || TREE_CODE (t) == FUNCTION_DECL
	    || TREE_CODE (t) == VAR_DECL
	    || TREE_CODE (t) == TYPE_DECL
	    || (TREE_CODE (t) == CONST_DECL && DECL_CONTEXT (t)
		&& TREE_CODE (DECL_CONTEXT (t)) == ENUMERAL_TYPE))
	  gcc_checking_assert (!(*modules)[get_instantiating_module (t)]->remap);
#endif
	bool specific = DECL_LANG_SPECIFIC (t) != NULL;
	b (specific);
	if (specific && VAR_P (t))
	  b (DECL_DECOMPOSITION_P (t));
	if (specific)
	  lang_decl_bools (t);
      }
      break;

    case tcc_type:
      {
	bool specific = (TYPE_MAIN_VARIANT (t) == t
			 && TYPE_LANG_SPECIFIC (t) != NULL);
	gcc_assert (TYPE_LANG_SPECIFIC (t)
		    == TYPE_LANG_SPECIFIC (TYPE_MAIN_VARIANT (t)));

	b (specific);
	if (specific)
	  lang_type_bools (t);
      }
      break;

    default:
      break;
    }

  bflush ();
}

bool
trees_in::tree_node_bools (tree t)
{
  bool ok = core_bools (t);

  if (ok)
    switch (TREE_CODE_CLASS (TREE_CODE (t)))
      {
      case tcc_declaration:
	if (b ())
	  {
	    bool decomp = VAR_P (t) && b ();

	    ok = maybe_add_lang_decl_raw (t, decomp);
	    if (ok)
	      ok = lang_decl_bools (t);
	}
	break;

      case tcc_type:
	if (b ())
	  {
	    ok = maybe_add_lang_type_raw (t);
	    if (ok)
	      ok = lang_type_bools (t);
	  }
	break;

      default:
	break;
      }

  bflush ();
  if (!ok || get_overrun ())
    return false;

  return true;
}


/* Write out the lang-specifc vals of node T.  */

void
trees_out::lang_vals (tree t)
{
  switch (TREE_CODE_CLASS (TREE_CODE (t)))
    {
    case tcc_declaration:
      if (DECL_LANG_SPECIFIC (t))
	lang_decl_vals (t);
      break;

    case tcc_type:
      if (TYPE_MAIN_VARIANT (t) == t && TYPE_LANG_SPECIFIC (t))
	lang_type_vals (t);
      break;

    default:
      break;
    }
}

bool
trees_in::lang_vals (tree t)
{
  bool ok = true;

  switch (TREE_CODE_CLASS (TREE_CODE (t)))
    {
    case tcc_declaration:
      if (DECL_LANG_SPECIFIC (t))
	ok = lang_decl_vals (t);
      break;

    case tcc_type:
      if (TYPE_LANG_SPECIFIC (t))
	ok = lang_type_vals (t);
      else
	TYPE_LANG_SPECIFIC (t) = TYPE_LANG_SPECIFIC (TYPE_MAIN_VARIANT (t));
      break;

    default:
      break;
    }

  return ok;
}

/* Write out the value fields of node T.  */

void
trees_out::tree_node_vals (tree t)
{
  core_vals (t);
  lang_vals (t);
}

bool
trees_in::tree_node_vals (tree t)
{
  bool ok = core_vals (t);
  if (ok)
    ok = lang_vals (t);

  return ok;
}


/* If T is a back reference, fixed reference or NULL, write out it's
   code and return WK_none.  Otherwise return WK_value if we must write
   by value, or WK_normal otherwise.  */

walk_kind
trees_out::ref_node (tree t)
{
  if (!t)
    {
      if (streaming_p ())
	{
	  /* NULL_TREE -> tt_null.  */
	  null_count++;
	  i (tt_null);
	}
      return WK_none;
    }

  if (!TREE_VISITED (t))
    return WK_normal;

  /* An already-visited tree.  It must be in the map.  */
  int *val_ptr = tree_map.get (t);
  int val = *val_ptr;

  if (val == tag_value)
    /* An entry we should walk into.  */
    return WK_value;

  const char *kind;

  if (val <= tag_backref)
    {
      /* Back reference -> -ve number  */
      if (streaming_p ())
	i (val);
      kind = "backref";
    }
  else if (val >= tag_fixed)
    {
      /* Fixed reference -> tt_fixed */
      val -= tag_fixed;
      if (streaming_p ())
	i (tt_fixed), u (val);
      kind = "fixed";
    }

  if (streaming_p ())
    {
      back_ref_count++;
      dump (dumper::TREE)
	&& dump ("Wrote %s:%d %C:%N%S", kind, val, TREE_CODE (t), t, t);
    }
  return WK_none;
}

tree
trees_in::back_ref (int tag)
{
  tree res = NULL_TREE;

  if (tag < 0 && unsigned (~tag) < back_refs.length ())
    res = back_refs[~tag];

  if (!res
      /* Checking TREE_CODE is a dereference, so we know this is not a
	 wild pointer.  Checking the code provides evidence we've not
	 corrupted something.  */
      || TREE_CODE (res) >= MAX_TREE_CODES)
    set_overrun ();
  else
    dump (dumper::TREE) && dump ("Read backref:%d found %C:%N%S", tag,
				 TREE_CODE (res), res, res);
  return res;
}

unsigned
trees_out::add_indirect_tpl_parms (tree parms)
{
  unsigned len = 0;
  for (; parms; parms = TREE_CHAIN (parms), len++)
    {
      if (TREE_VISITED (parms))
	break;

      int tag = insert (parms);
      dump (dumper::TREE)
	&& dump ("Indirect:%d template's parameter %u %C:%N",
		 tag, len, TREE_CODE (parms), parms);
    }

  if (streaming_p ())
    u (len);

  return len;
}

unsigned
trees_in::add_indirect_tpl_parms (tree parms)
{
  unsigned len = u ();
  for (unsigned ix = 0; ix != len; parms = TREE_CHAIN (parms), ix++)
    {
      int tag = insert (parms);
      dump (dumper::TREE)
	&& dump ("Indirect:%d template's parameter %u %C:%N",
		 tag, ix, TREE_CODE (parms), parms);
    }

  return len;
}

/* We've just found DECL by name.  Insert nodes that come with it, but
   cannot be found by name, so we'll not accidentally walk into them.  */

void
trees_out::add_indirects (tree decl)
{
  unsigned count = 0;
  // FIXME: We'll eventually want default fn parms of templates and
  // perhaps default template parms too.  I think the former can be
  // referenced from instantiations (as they are lazily instantiated).
  // Also (deferred?) exception specifications of templates.
  tree inner = decl;
  if (TREE_CODE (decl) == TEMPLATE_DECL)
    {
      count += add_indirect_tpl_parms (DECL_TEMPLATE_PARMS (decl));

      inner = DECL_TEMPLATE_RESULT (decl);
      int tag = insert (inner);
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Indirect:%d template's result %C:%N",
		   tag, TREE_CODE (inner), inner);
      count++;
    }

  if (TREE_CODE (inner) == TYPE_DECL)
    {
      /* Make sure the type is in the map too.  Otherwise we get
	 different RECORD_TYPEs for the same type, and things go
	 south.  */
      tree type = TREE_TYPE (inner);
      int tag = insert (type);
      if (streaming_p ())
	dump (dumper::TREE) && dump ("Indirect:%d decl's type %C:%N", tag,
				     TREE_CODE (type), type);
      count++;
    }

  if (streaming_p ())
    {
      u (count);
      dump (dumper::TREE) && dump ("Inserted %u indirects", count);
    }
}

bool
trees_in::add_indirects (tree decl)
{
  unsigned count = 0;
	    
  tree inner = decl;
  if (TREE_CODE (inner) == TEMPLATE_DECL)
    {
      count += add_indirect_tpl_parms (DECL_TEMPLATE_PARMS (decl));

      inner = DECL_TEMPLATE_RESULT (decl);
      int tag = insert (inner);
      dump (dumper::TREE)
	&& dump ("Indirect:%d templates's result %C:%N", tag,
		 TREE_CODE (inner), inner);
      count++;
    }

  if (TREE_CODE (inner) == TYPE_DECL)
    {
      tree type = TREE_TYPE (inner);
      int tag = insert (type);
      dump (dumper::TREE)
	&& dump ("Indirect:%d decl's type %C:%N", tag, TREE_CODE (type), type);
      count++;
    }

  dump (dumper::TREE) && dump ("Inserted %u indirects", count);
  return count == u ();
}

/* Stream a template parameter.  There are 4.5 kinds of parameter:
   a) Template - TEMPLATE_DECL->TYPE_DECL->TEMPLATE_TEMPLATE_PARM
   	TEMPLATE_TYPE_PARM_INDEX TPI
   b) Type - TYPE_DECL->TEMPLATE_TYPE_PARM TEMPLATE_TYPE_PARM_INDEX TPI
   c.1) NonTYPE - PARM_DECL DECL_INITIAL TPI We meet this first
   c.2) NonTYPE - CONST_DECL DECL_INITIAL Same TPI
   d) BoundTemplate - TYPE_DECL->BOUND_TEMPLATE_TEMPLATE_PARM
       TEMPLATE_TYPE_PARM_INDEX->TPI
       TEMPLATE_TEMPLATE_PARM_INFO->TEMPLATE_INFO

   All of these point to a TEMPLATE_PARM_INDEX, and #B also has a TEMPLATE_INFO
*/

void
trees_out::tpl_parm_value (tree parm)
{
  gcc_checking_assert (DECL_P (parm) && DECL_TEMPLATE_PARM_P (parm));

  int parm_tag = insert (parm);
  if (streaming_p ())
    {
      i (tt_tpl_parm);
      dump (dumper::TREE) && dump ("Writing template parm:%d %C:%N",
				   parm_tag, TREE_CODE (parm), parm);
      start (parm);
      tree_node_bools (parm);
    }

  tree inner = parm;
  if (TREE_CODE (inner) == TEMPLATE_DECL)
    {
      inner = DECL_TEMPLATE_RESULT (inner);
      int inner_tag = insert (inner);
      if (streaming_p ())
	{
	  dump (dumper::TREE) && dump ("Writing inner template parm:%d %C:%N",
				       inner_tag, TREE_CODE (inner), inner);
	  start (inner);
	  tree_node_bools (inner);
	}
    }

  tree type = NULL_TREE;
  if (TREE_CODE (inner) == TYPE_DECL)
    {
      type = TREE_TYPE (inner);
      int type_tag = insert (type);
      if (streaming_p ())
	{
	  dump (dumper::TREE) && dump ("Writing template parm type:%d %C:%N",
				       type_tag, TREE_CODE (type), type);
	  start (type);
	  tree_node_bools (type);
	}
    }

  if (inner != parm)
    {
      /* This is a template-template parameter.  */
      unsigned tpl_levels = 0;
      tpl_header (parm, &tpl_levels);
      tpl_parms_fini (parm, tpl_levels);
    }

  tree_node_vals (parm);
  if (inner != parm)
    tree_node_vals (inner);
  if (type)
    tree_node_vals (type);

  if (streaming_p ())
    dump (dumper::TREE) && dump ("Wrote template parm:%d %C:%N",
				 parm_tag, TREE_CODE (parm), parm);
}

tree
trees_in::tpl_parm_value ()
{
  tree parm = start ();
  if (!parm || !tree_node_bools (parm))
    return NULL_TREE;

  int parm_tag = insert (parm);
  dump (dumper::TREE) && dump ("Reading template parm:%d %C:%N",
			       parm_tag, TREE_CODE (parm), parm);

  tree inner = parm;
  if (TREE_CODE (inner) == TEMPLATE_DECL)
    {
      inner = start ();
      if (!inner || !tree_node_bools (inner))
	return NULL_TREE;
      int inner_tag = insert (inner);
      dump (dumper::TREE) && dump ("Reading inner template parm:%d %C:%N",
				   inner_tag, TREE_CODE (inner), inner);
      DECL_TEMPLATE_RESULT (parm) = inner;
    }

  tree type = NULL_TREE;
  if (TREE_CODE (inner) == TYPE_DECL)
    {
      type = start ();
      if (!type || !tree_node_bools (type))
	return NULL_TREE;
      int type_tag = insert (type);
      dump (dumper::TREE) && dump ("Reading template parm type:%d %C:%N",
				   type_tag, TREE_CODE (type), type);

      TREE_TYPE (inner) = TREE_TYPE (parm) = type;
      TYPE_NAME (type) = parm;
    }

  if (inner != parm)
    {
      /* A template template parameter.  */
      unsigned tpl_levels = 0;
      tpl_header (parm, &tpl_levels);
      tpl_parms_fini (parm, tpl_levels);
    }

  tree_node_vals (parm);
  if (inner != parm)
    tree_node_vals (inner);
  if (type)
    {
      tree_node_vals (type);
      if (TYPE_CANONICAL (type))
	{
	  gcc_checking_assert (TYPE_CANONICAL (type) == type);
	  TYPE_CANONICAL (type) = canonical_type_parameter (type);
	}
    }

  dump (dumper::TREE) && dump ("Read template parm:%d %C:%N",
			       parm_tag, TREE_CODE (parm), parm);

  return parm;
}

/* DECL is a decl node that must be written by value.  DEP is the
   decl's depset.  */

void
trees_out::decl_value (tree decl, depset *dep)
{
  gcc_checking_assert (DECL_P (decl) && !DECL_CLONED_FUNCTION_P (decl)
		       && !DECL_TEMPLATE_PARM_P (decl));

  merge_kind mk = get_merge_kind (dep);

  if (CHECKING_P)
    {
      /* Never start in the middle of a template.  */
      int use_tpl = -1;
      if (tree ti = node_template_info (decl, use_tpl))
	gcc_checking_assert (TREE_CODE (TI_TEMPLATE (ti)) == OVERLOAD
			     || (DECL_TEMPLATE_RESULT (TI_TEMPLATE (ti))
				 != decl));
    }

  if (streaming_p ())
    {
      /* A new node -> tt_decl.  */
      decl_val_count++;
      i (tt_decl);
      u (mk);
      start (decl);

      if (mk != MK_unique)
	{
	  if (!state->is_header ())
	    {
	      /* Tell the importer whether this is a global module entity,
		 or a module entity.  This bool merges into the next block
		 of bools.  Sneaky.  */
	      tree o = get_originating_module_decl (decl);
	      bool is_mod = DECL_LANG_SPECIFIC (o) && DECL_MODULE_PURVIEW_P (o);
	      b (is_mod);
	    }
	  b (dep->has_defn ());
	}
      tree_node_bools (decl);
    }

  int tag = insert (decl, WK_value);
  if (streaming_p ())
    dump (dumper::TREE)
      && dump ("Writing %s:%d %C:%N%S", merge_kind_name[mk], tag,
	       TREE_CODE (decl), decl, decl);

  // FIXME: If mergeable, mark function parms etc as mergeable too

  tree inner = decl;
  int inner_tag = 0;
  if (TREE_CODE (decl) == TEMPLATE_DECL)
    {
      inner = DECL_TEMPLATE_RESULT (decl);

      inner_tag = insert (inner, WK_value);
      if (streaming_p ())
	{
	  start (inner);
	  tree_node_bools (inner);
	  dump (dumper::TREE)
	    && dump ("Writing %s:%d %C:%N%S", merge_kind_name[mk], inner_tag,
		     TREE_CODE (inner), inner, inner);
	}
    }

  tree type = NULL_TREE;
  int type_tag = 0;
  tree stub_decl = NULL_TREE;
  int stub_tag = 0;
  if (TREE_CODE (inner) == TYPE_DECL)
    {
      type = TREE_TYPE (inner);
      bool has_type = (type == TYPE_MAIN_VARIANT (type)
		       && TYPE_NAME (type) == inner);

      if (streaming_p ())
	u (has_type ? TREE_CODE (type) : 0);

      if (has_type)
	{
	  type_tag = insert (type, WK_value);
	  if (streaming_p ())
	    {
	      start (type, true);
	      tree_node_bools (type);
	      dump (dumper::TREE)
		&& dump ("Writing type:%d %C:%N", type_tag,
			 TREE_CODE (type), type);
	    }

	  stub_decl = TYPE_STUB_DECL (type);
	  bool has_stub = inner != stub_decl;
	  if (streaming_p ())
	    u (has_stub ? TREE_CODE (stub_decl) : 0);
	  if (has_stub)
	    {
	      stub_tag = insert (stub_decl);
	      if (streaming_p ())
		{
		  start (stub_decl, true);
		  tree_node_bools (stub_decl);
		  dump (dumper::TREE)
		    && dump ("Writing stub_decl:%d %C:%N", stub_tag,
			     TREE_CODE (stub_decl), stub_decl);
		}
	    }
	  else
	    stub_decl = NULL_TREE;
	}
      else
	/* Regular typedef.  */
	type = NULL_TREE;
    }

  tree container = get_container (decl);

  /* Stream the container, we want it correctly canonicalized before
     we start emitting keys for this decl.  */
  tree_node (container);

  unsigned tpl_levels = 0;
  if (decl != inner)
    tpl_header (decl, &tpl_levels);
  if (TREE_CODE (inner) == FUNCTION_DECL)
    fn_parms_init (inner);

  /* Now write out the merging information, and then really
     install the tag values.  */
  key_mergeable (mk, dep, decl);

  if (streaming_p ())
    dump (dumper::MERGE)
      && dump ("Wrote:%d's %s merge key %C:%N", tag,
	       merge_kind_name[mk], TREE_CODE (decl), decl);

  if (TREE_CODE (inner) == FUNCTION_DECL)
    // FIXME: Stream in the type here as that's where the default args are
    fn_parms_fini (inner);

  tree_node_vals (decl);

  if (inner_tag != 0)
    {
      tree_node_vals (inner);
      tpl_parms_fini (decl, tpl_levels);
    }

  if (type)
    {
      tree_node_vals (type);
      if (stub_decl)
	tree_node_vals (stub_decl);
    }

  // FIXME: It'd be nice if there was a flag to tell us to go look for
  // constraints.  Not a modules-specific problem though.
  if (flag_concepts)
    {
      tree constraints = get_constraints (decl);
      tree_node (constraints);
    }

  if (!type && TREE_CODE (inner) == TYPE_DECL)
    {
      /* A typedef type.  */
      int type_tag = insert (TREE_TYPE (inner));
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Cloned:%d typedef %C:%N", type_tag,
		   TREE_CODE (TREE_TYPE (inner)), TREE_TYPE (inner));
    }

  if (streaming_p () && DECL_MAYBE_IN_CHARGE_CDTOR_P (inner))
    {
      bool cloned_p
	= (DECL_CHAIN (inner) && DECL_CLONED_FUNCTION_P (DECL_CHAIN (inner)));
      bool needs_vtt_parm_p
	= (cloned_p && CLASSTYPE_VBASECLASSES (DECL_CONTEXT (inner)));
      bool omit_inherited_parms_p
	= (cloned_p && ctor_omit_inherited_parms (inner, false));
      unsigned flags = (int (cloned_p) << 0
			| int (needs_vtt_parm_p) << 1
			| int (omit_inherited_parms_p) << 2);
      u (flags);
      dump (dumper::TREE) && dump ("CDTOR %N is %scloned",
				   decl, cloned_p ? "" : "not ");
    }

  if (streaming_p ())
    dump (dumper::TREE) && dump ("Written decl:%d %C:%N", tag,
				 TREE_CODE (decl), decl);
}

tree
trees_in::decl_value ()
{
  int tag = 0;
  bool is_mod = false;
  bool has_defn = false;
  unsigned mk_u = u ();
  if (mk_u >= MK_hwm || !merge_kind_name[mk_u])
    {
      set_overrun ();
      return NULL_TREE;
    }
  merge_kind mk = merge_kind (mk_u);

  tree decl = start ();
  if (decl)
    {
      if (mk != MK_unique)
	{
	  if (!state->is_header ())
	    /* See note in trees_out about where this bool is sequenced.  */
	    is_mod = b ();

	  has_defn = b ();
	}

      if (!tree_node_bools (decl))
	decl = NULL_TREE;
    }
  
  /* Insert into map.  */
  tag = insert (decl);
  if (decl)
    dump (dumper::TREE)
      && dump ("Reading:%d %C", tag, TREE_CODE (decl));

  tree inner = decl;
  int inner_tag = 0;
  if (decl && TREE_CODE (decl) == TEMPLATE_DECL)
    {
      inner = start ();
      if (inner && tree_node_bools (inner))
	DECL_TEMPLATE_RESULT (decl) = inner;
      else
	decl = NULL_TREE;

      inner_tag = insert (inner);
      if (decl)
	dump (dumper::TREE)
	  && dump ("Reading%d %C", inner_tag, TREE_CODE (inner));
    }

  tree type = NULL_TREE;
  int type_tag = 0;
  tree stub_decl = NULL_TREE;
  int stub_tag = 0;
  if (decl && TREE_CODE (inner) == TYPE_DECL)
    {
      if (unsigned type_code = u ())
	{
	  type = start (type_code);
	  if (type && tree_node_bools (type))
	    {
	      TREE_TYPE (inner) = type;
	      TYPE_NAME (type) = inner;
	    }
	  else
	    decl = NULL_TREE;

	  type_tag = insert (type);
	  if (decl)
	    dump (dumper::TREE)
	      && dump ("Reading type:%d %C", type_tag, TREE_CODE (type));

	  if (unsigned stub_code = u ())
	    {
	      stub_decl = start (stub_code);
	      if (stub_decl && tree_node_bools (stub_decl))
		{
		  TREE_TYPE (stub_decl) = type;
		  TYPE_STUB_DECL (type) = stub_decl;
		}
	      else
		decl = NULL_TREE;

	      stub_tag = insert (stub_decl);
	      if (decl)
		dump (dumper::TREE)
		  && dump ("Reading stub_decl:%d %C", stub_tag,
			   TREE_CODE (stub_decl));
	    }
	}
    }

  if (!decl)
    {
    bail:
      if (inner_tag != 0)
	back_refs[~inner_tag] = NULL_TREE;
      if (type_tag != 0)
	back_refs[~type_tag] = NULL_TREE;
      if (stub_tag != 0)
	back_refs[~stub_tag] = NULL_TREE;
      if (tag != 0)
	back_refs[~tag] = NULL_TREE;
      set_overrun ();
      /* Bail.  */
      return NULL_TREE;
    }

  // FIXME: this needs a cleanup
  tree container_1 = tree_node ();
  unsigned tpl_levels = 0;
  if (true)
    {
      /* Figure out if this decl is already known about.  */
      tree key;
      tree fn_args = NULL_TREE;
      tree r_type = NULL_TREE;
      int parm_tag = 0;

      tree container = container_1;

      if (decl != inner)
	if (!tpl_header (decl, &tpl_levels))
	  goto bail;
      if (TREE_CODE (inner) == FUNCTION_DECL)
	parm_tag = fn_parms_init (inner);

      if (!key_mergeable (mk, decl, inner, type,
			  &container, &key, &fn_args, &r_type))
	goto bail;

      if (mk & MK_template_mask)
	{
	  /* A specialization of some kind.  */
	  DECL_NAME (decl) = DECL_NAME (container);
	  DECL_CONTEXT (decl) = DECL_CONTEXT (container);
	}
      else
	{
	  if (!(mk & MK_indirect_mask))
	    DECL_NAME (decl) = key;
	  DECL_CONTEXT (decl) = FROB_CONTEXT (container);
	}

      if (inner_tag != 0)
	{
	  DECL_NAME (inner) = DECL_NAME (decl);
	  DECL_CONTEXT (inner) = DECL_CONTEXT (decl);
	}

      const char *kind = "new";
      tree existing = NULL_TREE;

      if (mk & MK_template_mask)
	{
	  tree insert = decl;
	  if (mk & MK_tmpl_tmpl_mask)
	    {
	      if (!inner_tag)
		goto bail;
	      insert = inner;
	    }
	  bool is_decl = mk & MK_tmpl_decl_mask;
	  if (!is_decl)
	    {
	      if (mk == MK_type_spec && inner_tag)
		goto bail;
	      insert = type;
	    }

	  existing = match_mergeable_specialization (is_decl, container, key,
						     insert);

	  if (!existing)
	    {
	      if (mk & MK_tmpl_decl_mask && mk & MK_tmpl_both_mask)
		{} // FIXME: insert into type table
	    }
	  else if (mk & MK_tmpl_decl_mask)
	    {
	      /* A declaration specialization.  */
	      if (mk & MK_tmpl_tmpl_mask)
		if (tree ti = DECL_TEMPLATE_INFO (existing))
		  {
		    tree tmpl = TI_TEMPLATE (ti);
		    if (DECL_TEMPLATE_RESULT (tmpl) == existing)
		      existing = tmpl;
		  }

	      if (mk & MK_tmpl_both_mask)
		{} // FIXME: check it's in the type table too
	    }
	  else
	    {
	      /* A type specialization.  */
	      if (!(mk & MK_tmpl_tmpl_mask))
		existing = TYPE_NAME (existing);
	      else if (mk & MK_tmpl_partial_mask)
		{
		  /* A partial specialization.  */
		  for (tree partial = DECL_TEMPLATE_SPECIALIZATIONS (container);
		       partial; partial = TREE_CHAIN (partial))
		    if (TREE_TYPE (partial) == existing)
		      {
			existing = TREE_VALUE (partial);
			break;
		      }
		  gcc_assert (TREE_CODE (existing) == TEMPLATE_DECL);
		}
	      else
		if (tree ti = CLASSTYPE_TEMPLATE_INFO (existing))
		  {
		    tree tmpl = TI_TEMPLATE (ti);
		    if (DECL_TEMPLATE_RESULT (tmpl) == TYPE_NAME (existing))
		      existing = tmpl;
		  }
	    }
	}
      else if (mk == MK_unique)
	kind = "unique";
      else
	{
	  if (is_mod && !(state->is_primary () || state->is_partition ()))
	    /* This is a module-purview entity, and we're not loading part
	       of the current module, so it must be unique.  */
	    kind = "unique";
	  else
	    existing = match_mergeable_decl (decl, container, key, is_mod,
					     r_type, fn_args);
	}

      if (existing)
	{
	  /* Install the existing decl into the back ref array.  */
	  register_duplicate (decl, existing);
	  back_refs[~tag] = existing;
	  if (inner_tag != 0)
	    {
	      existing = DECL_TEMPLATE_RESULT (existing);
	      back_refs[~inner_tag] = existing;
	    }

	  if (type_tag != 0)
	    {
	      tree existing_type = TREE_TYPE (existing);
	      back_refs[~type_tag] = existing_type;
	      if (stub_tag != 0)
		back_refs[~stub_tag] = TYPE_STUB_DECL (existing_type);
	    }

	  kind = "matched";
	}

      if (parm_tag)
	/* EXISTING is the template result (or NULL).  */
	fn_parms_fini (parm_tag, inner, existing, has_defn);

      dump (dumper::MERGE)
	&& dump ("Read:%d's %s merge key (%s) %C:%N", tag,
		 merge_kind_name[mk], kind, TREE_CODE (decl), decl);
    }

  if (!tree_node_vals (decl))
    goto bail;

  if (inner_tag != 0)
    {
      gcc_checking_assert (DECL_TEMPLATE_RESULT (decl) == inner);

      if (!tree_node_vals (inner))
	goto bail;

      if (!tpl_parms_fini (decl, tpl_levels))
	goto bail;
    }

  if (type && (!tree_node_vals (type)
	       || (stub_decl && !tree_node_vals (stub_decl))))
    goto bail;

  tree constraints = NULL_TREE;
  if (flag_concepts && DECL_P (decl))
    constraints  = tree_node ();

  dump (dumper::TREE) && dump ("Read:%d %C:%N", tag, TREE_CODE (decl), decl);

  /* Regular typedefs will have a NULL TREE_TYPE at this point.  */
  bool is_typedef = TREE_CODE (inner) == TYPE_DECL && !type;
  if (is_typedef)
    {
      /* Frob it to be ready for cloning.  */
      TREE_TYPE (inner) = DECL_ORIGINAL_TYPE (inner);
      DECL_ORIGINAL_TYPE (inner) = NULL_TREE;
    }

  tree existing = back_refs[~tag];
  bool is_new = existing == decl;
  if (is_new)
    {
      /* A newly discovered node.  */
      if (TREE_CODE (decl) == FUNCTION_DECL && DECL_VIRTUAL_P (decl))
	/* Mark this identifier as naming a virtual function --
	   lookup_overrides relies on this optimization.  */
	IDENTIFIER_VIRTUAL_P (DECL_NAME (decl)) = true;

      if (constraints)
	set_constraints (decl, constraints);

      if (TREE_CODE (decl) == INTEGER_CST && !TREE_OVERFLOW (decl))
	{
	  decl = cache_integer_cst (decl, true);
	  back_refs[~tag] = decl;
	}

      if (is_typedef)
	set_underlying_type (inner);

      if (inner_tag)
	/* Set the TEMPLATE_DECL's type.  */
	TREE_TYPE (decl) = TREE_TYPE (inner);
    }
  else
    {
      /* DECL is the to-be-discarded decl.  Its internal pointers will
	 be to the EXISTING's structure.  Frob it to point to its
	 own other structures, so loading its definition will alter
	 it, and not the existing decl.  */
      dump (dumper::MERGE) && dump ("Deduping %N", existing);

      if (inner_tag != 0)
	DECL_TEMPLATE_RESULT (decl) = inner;

      if (type)
	{
	  /* Point at the to-be-discarded type & decl.  */
	  TYPE_NAME (type) = inner;
	  TREE_TYPE (inner) = type;

	  TYPE_STUB_DECL (type) = stub_decl ? stub_decl : inner;
	  if (stub_decl)
	    TREE_TYPE (stub_decl) = type;
	}

      if (inner_tag)
	/* Set the TEMPLATE_DECL's type.  */
	TREE_TYPE (decl) = TREE_TYPE (inner);

      if (!is_matching_decl (existing, decl))
	unmatched_duplicate (existing);

      // FIXME: Check default tmpl and fn parms here
      /* And our result is the existing node.  */
      decl = existing;
    }

  if (is_typedef)
    {
      /* Insert the type into the array now.  */
      tag = insert (TREE_TYPE (decl));
      dump (dumper::TREE)
	&& dump ("Cloned:%d typedef %C:%N",
		 tag, TREE_CODE (TREE_TYPE (decl)), TREE_TYPE (decl));
    }

  if (DECL_MAYBE_IN_CHARGE_CDTOR_P (decl))
    {
      unsigned flags = u ();

      if (is_new)
	{
	  gcc_checking_assert (!DECL_CHAIN (decl));
	  bool cloned_p = flags & 1;
	  dump (dumper::TREE) && dump ("CDTOR %N is %scloned",
				       decl, cloned_p ? "" : "not ");
	  if (cloned_p)
	    build_clones (decl, flags & 2, flags & 4);
	}
    }

  return decl;
}

/* Reference DECL.  REF indicates the walk kind we are performing.
   Return true if we should write this decl by value.  */

bool
trees_out::decl_node (tree decl, walk_kind ref)
{
  gcc_checking_assert (DECL_P (decl));

  if (TREE_CODE (decl) == NAMESPACE_DECL
      && !DECL_NAMESPACE_ALIAS (decl))
    {
      int origin = -1;
      if (!TREE_PUBLIC (decl))
	{
	  origin = DECL_MODULE_ORIGIN (decl);
	  if (origin)
	    origin = (*modules)[origin]->remap;
	}

      if (streaming_p ())
	{
	  i (tt_namespace);
	  i (origin);
	  tree_node (CP_DECL_CONTEXT (decl));
	  tree_node (DECL_NAME (decl));
	}
      else
	{
	  if (ref == WK_value)
	    tree_node (CP_DECL_CONTEXT (decl));
	  else
	    dep_hash->add_dependency (decl, depset::EK_NAMESPACE);
	}

      int tag = insert (decl, ref);
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Wrote%s namespace:%d %C:%N@%M",
		   origin < 0 ? " public" : "", tag, TREE_CODE (decl), decl,
		   origin < 0 ? NULL : (*modules)[origin]);

      return false;
    }

  if (ref == WK_value)
    {
      if (TREE_CODE (decl) != TEMPLATE_DECL
	  && TREE_CODE (decl) != FUNCTION_DECL
	  && TREE_CODE (decl) != VAR_DECL
	  && TREE_CODE (decl) != TYPE_DECL)
	return true;

      depset *dep = dep_hash->find_entity (decl);
      if (dep && !dep->is_mergeable ())
	dep = NULL;
      
      decl_value (decl, dep);
      return false;
    }

  if (!DECL_CONTEXT (decl))
    return true;

  if (DECL_TEMPLATE_PARM_P (decl))
    return true;

  switch (TREE_CODE (decl))
    {
    default:
      break;

    case RESULT_DECL:
      // FIXME: Like a parm?
      return true;

    case PARM_DECL:
      {
	if (streaming_p ())
	  i (tt_parm);
	tree_node (DECL_CONTEXT (decl));
	if (streaming_p ())
	  {
	    /* That must have put this in the map.  */
	    walk_kind ref = ref_node (decl);
	    if (ref != WK_none)
	      // FIXME: We can wander into bits of the template this
	      // was instantiated from.  For instance deferred
	      // noexcept and (probably?) default parms.  We need to
	      // refer to that specific node in some way.  For now
	      // just clone it.  We should preemptively puth those
	      // things in the map when we reference their template by
	      // name.  See add_indirects.
	      return true;
	    dump (dumper::TREE)
	      && dump ("Wrote %s reference %N",
		       TREE_CODE (decl) == PARM_DECL ? "parameter" : "result",
		       decl);
	  }
      }
      return false;

    case LABEL_DECL:
      return true;

    case TEMPLATE_DECL:
      if (DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (decl))
	{
	  /* A (local template) friend of a template.  */
	  if (streaming_p ())
	    {
	      i (tt_friend_template);
	      dump (dumper::TREE) && dump ("Writing friend template %C:%N",
					   TREE_CODE (decl), decl);
	    }

	  tree klass = DECL_CHAIN (decl);
	  tree_node (klass);

	  if (streaming_p ())
	    {
	      tree decls = CLASSTYPE_DECL_LIST (klass);
	      for (unsigned ix = 0;; decls = TREE_CHAIN (decls))
		if (!TREE_PURPOSE (decls))
		  {
		    tree frnd = friend_from_decl_list (TREE_VALUE (decls));
		    if (frnd == decl)
		      {
			u (ix);
			dump (dumper::TREE)
			  && dump ("Wrote friend %N[%u], %C:%N",
				   klass, ix, TREE_CODE (decl), decl);
			break;
		      }

		    /* Count every friend to make streaming in simpler.  */
		    ix++;
		  }

	      /* We must have found it.  */
	      gcc_checking_assert (decls);
	    }

	  return false;
	}
      break;

    case CONST_DECL:
    case FIELD_DECL:
      {
	if (streaming_p ())
	  i (tt_data_member);

	tree ctx = DECL_CONTEXT (decl);
	tree_node (ctx);
	tree name = DECL_NAME (decl);

	if (TREE_CODE (decl) == CONST_DECL)
	  gcc_checking_assert (TREE_CODE (ctx) == ENUMERAL_TYPE);

	if (name && IDENTIFIER_ANON_P (name))
	  name = NULL_TREE;

	tree_node (name);
	if (!name && streaming_p ())
	  {
	    /* Anonymous enum members are not a thing!  */
	    gcc_checking_assert (TREE_CODE (decl) == FIELD_DECL);

	    unsigned ix = get_field_ident (ctx, decl);
	    u (ix);
	  }

	int tag = insert (decl);
	if (streaming_p ())
	  dump (dumper::TREE)
	    && dump ("Wrote member:%d %C:%N", tag, TREE_CODE (decl), decl);
	return false;
      }
      break;

    case USING_DECL:
      gcc_checking_assert (TREE_CODE (CP_DECL_CONTEXT (decl)) == FUNCTION_DECL);
      return true;

    case VAR_DECL:
      if (DECL_VTABLE_OR_VTT_P (decl))
	{
	  /* VTT or VTABLE, they are all on the vtables list.  */
	  tree ctx = CP_DECL_CONTEXT (decl);
	  tree vtable = CLASSTYPE_VTABLES (ctx);
	  for (unsigned ix = 0; ; vtable = DECL_CHAIN (vtable), ix++)
	    if (vtable == decl)
	      {
		gcc_checking_assert (DECL_VIRTUAL_P (decl));
		if (streaming_p ())
		  {
		    u (tt_vtable);
		    u (ix);
		    dump (dumper::TREE)
		      && dump ("Writing vtable %N[%u]", ctx, ix);
		  }
		tree_node (ctx);
		return false;
	      }
	  gcc_unreachable ();
	}

      if (DECL_TINFO_P (decl))
	{
	tinfo:
	  /* A typeinfo, tt_tinfo_typedef or tt_tinfo_var.  */
	  bool is_var = TREE_CODE (decl) == VAR_DECL;
	  tree type = TREE_TYPE (decl);
	  unsigned ix = get_pseudo_tinfo_index (type);
	  if (streaming_p ())
	    {
	      i (is_var ? tt_tinfo_var : tt_tinfo_typedef);
	      u (ix);
	    }

	  if (is_var)
	    {
	      /* We also need the type it is for and mangled name, so
		 the reader doesn't need to complete the type (which
		 would break section ordering).  The type it is for is
		 stashed on the name's TREE_TYPE.  */
	      tree name = DECL_NAME (decl);
	      tree_node (name);
	      type = TREE_TYPE (name);
	      tree_node (type);
	    }

	  int tag = insert (decl);
	  if (streaming_p ())
	    dump (dumper::TREE)
	      && dump ("Wrote tinfo_%s:%d %u %N", is_var ? "var" : "type",
		       tag, ix, type);

	  if (!is_var)
	    {
	      tag = insert (type);
	      if (streaming_p ())
		dump (dumper::TREE)
		  && dump ("Wrote tinfo_type:%d %u %N", tag, ix, type);
	    }
	  return false;
	}
      break;

    case TYPE_DECL:
      if (DECL_TINFO_P (decl))
	goto tinfo;
      break;
    }

  if (DECL_THUNK_P (decl))
    {
      /* Thunks are similar to binfos -- write the thunked-to decl and
	 then thunk-specific key info.  */
      if (streaming_p ())
	{
	  i (tt_thunk);
	  i (THUNK_FIXED_OFFSET (decl));
	}

      tree target = decl;
      while (DECL_THUNK_P (target))
	target = THUNK_TARGET (target);
      tree_node (target);
      tree_node (THUNK_VIRTUAL_OFFSET (decl));
      int tag = insert (decl);
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Wrote:%d thunk %N to %N", tag, DECL_NAME (decl), target);
      return false;
    }

  if (DECL_CLONED_FUNCTION_P (decl))
    {
      tree target = get_clone_target (decl);
      if (streaming_p ())
	i (tt_clone_ref);

      tree_node (target);
      tree_node (DECL_NAME (decl));
      int tag = insert (decl);
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Wrote:%d clone %N of %N", tag, DECL_NAME (decl), target);
      return false;
    }

  tree inst = get_instantiating_module_decl (decl);

  /* Everything left should be a thing that is in the entity table.
     Things that can be defined outside of their (original
     declaration) context.  */
  // FIXME: *could* be in the entity table.  I don't get that right
  // yet.  What about using_decls etc?  They should be like
  // field_decls, but I moved that above, possibly unnecessarily
  
  gcc_checking_assert (TREE_CODE (STRIP_TEMPLATE (decl)) == VAR_DECL
		       || TREE_CODE (STRIP_TEMPLATE (decl)) == FUNCTION_DECL
		       || TREE_CODE (STRIP_TEMPLATE (decl)) == TYPE_DECL
		       || TREE_CODE (STRIP_TEMPLATE (decl)) == CONCEPT_DECL);

  int use_tpl = -1;
  tree ti = node_template_info (decl, use_tpl);
  tree tpl = NULL_TREE;

  /* TI_TEMPLATE is not a TEMPLATE_DECL for (some) friends, because
     we matched a non-template.  */
  if (ti && TREE_CODE (TI_TEMPLATE (ti)) == TEMPLATE_DECL
      && DECL_TEMPLATE_RESULT (TI_TEMPLATE (ti)) == decl)
    {
      tpl = TI_TEMPLATE (ti);
    partial_template:
      if (streaming_p ())
	{
	  i (tt_template);
	  dump (dumper::TREE)
	    && dump ("Writing implicit template %C:%N%S",
		     TREE_CODE (tpl), tpl, tpl);
	}
      tree_node (tpl);

      /* Streaming TPL caused us to visit DECL and maybe its type.  */
      gcc_checking_assert (TREE_VISITED (decl));
      if (DECL_IMPLICIT_TYPEDEF_P (decl))
	gcc_checking_assert (TREE_VISITED (TREE_TYPE (decl)));
      return false;
    }

  int origin = DECL_LANG_SPECIFIC (inst) ? DECL_MODULE_ORIGIN (inst) : 0;
  if (origin)
    origin = (*modules)[origin]->remap;
  bool is_import = origin != 0;
  const char *kind = NULL;
  depset *dep = NULL;
  tree name = DECL_NAME (decl);
  unsigned code = tt_named;
  int ident = -2;
  tree proxy = decl;
  tree ctx = NULL_TREE;

  if (use_tpl > 0)
    {
      /* Some kind of specialization.  Not all specializations are in
         the table, so we have to query it.  Those that are not there
         are findable by name, but a specializations in that their
         definitions can be generated anywhere -- we need to write
         them out if we did it.  */
      if (!streaming_p ())
	{
	  gcc_checking_assert (STRIP_TEMPLATE (decl)
			       == get_instantiating_module_decl (decl));
	  dep = dep_hash->add_dependency (decl, depset::EK_MAYBE_SPEC);
	  /* We should always insert or find something.  */
	  gcc_assert (dep && dep->is_import () == (origin != 0));
	}
      else
	dep = dep_hash->find_entity (decl);

      if (dep->get_entity_kind () == depset::EK_REDIRECT)
	{
	  /* The DECL_TEMPLATE_RESULT of a partial specialization.
	     Write the partial specialization's template.  */
	  depset *redirect = dep->deps[0];
	  gcc_checking_assert ((redirect->get_entity_kind ()
				== depset::EK_SPECIALIZATION)
			       && redirect->is_partial ());
	  tpl = redirect->get_entity ();
	  goto partial_template;
	}
      else if (dep->get_entity_kind () == depset::EK_SPECIALIZATION)
	{
	  if (streaming_p ())
	    goto direct_entity;
	  kind = "specialization";
	  goto insert;
	}
      else
	gcc_assert (dep->get_entity_kind () == depset::EK_DECL);
    }

  {
    ctx = CP_DECL_CONTEXT (decl);

    if (TREE_CODE (ctx) == FUNCTION_DECL)
      {
	/* We cannot lookup by name inside a function.  */
	if (!streaming_p ()
	    && (is_import
		|| (dep_hash->sneakoscope
		    && ctx == dep_hash->current->get_entity ())))
	  {
	    /* We've found a voldemort type.  Add it as a
	       dependency.  */
	    dep = dep_hash->add_dependency (decl, depset::EK_UNNAMED);
	    gcc_assert (dep->is_import () == is_import);
	    kind = "unnamed";
	    goto insert;
	  }

	if (streaming_p ())
	  {
	    dep = dep_hash->find_entity (decl);
	    if (dep && dep->get_entity_kind () == depset::EK_UNNAMED)
	      goto direct_entity;
	  }

	/* Some (non-mergeable?) internal entity of the function.  Do
	   by value.  */
	// FIXME: pass DEP to the value streamer?
	gcc_assert (!is_import);
	decl_value (decl, NULL);
	return false;
      }

    /* A named decl -> tt_named_decl.  */
    if (streaming_p ())
      {
	if (TREE_CODE (decl) == TEMPLATE_DECL
	    && (RECORD_OR_UNION_CODE_P (TREE_CODE (ctx))
		|| TREE_CODE (ctx) == ENUMERAL_TYPE)
	    && !DECL_MEMBER_TEMPLATE_P (decl))
	  {
	    /* An implicit member template.  Look for the templated
	       decl.  */
	    proxy = DECL_TEMPLATE_RESULT (decl);
	    code = tt_implicit_template;
	  }

	if (name && IDENTIFIER_ANON_P (name)
	    && TREE_CODE (ctx) != NAMESPACE_DECL)
	  name = NULL_TREE;

	if (TREE_CODE (ctx) == NAMESPACE_DECL)
	  {
	  direct_entity:
	    gcc_assert (code == tt_named);
	    code = tt_entity;
	    /* Locate the entity.  */
	    unsigned entity_num = import_entity_index (decl);
	    if (is_import)
	      {
		// FIXME: Not relying on origin, as we're gonna move
		// away from that
		/* An import.  */
		module_state *from = import_entity_module (entity_num);
		gcc_checking_assert (from->remap == origin);
		ident = entity_num - from->entity_lwm;
		kind = "import";
	      }
	    else
	      {
		/* It should be what we put there.  */
		gcc_checking_assert (dep_hash->find_entity (decl)->cluster
				     == -entity_num);
		ident = ~entity_num;

		tree o = get_originating_module_decl (decl);
		kind = (DECL_LANG_SPECIFIC (o) && DECL_MODULE_PURVIEW_P (o)
			? "purview" : "GMF");
	      }
	  }
	else
	  {
	    // FIXME: Fields should get here
	    ident = get_lookup_ident (ctx, name, origin, proxy);
	    /* Make sure we can find it by name.  */
	    gcc_checking_assert
	      (proxy == lookup_by_ident (ctx, name, origin, ident));
	    kind = is_import ? "import" : "member";
	  }

	i (code);
	if (code != tt_entity)
	  {
	    tree_node (ctx);
	    tree_node (name);
	  }
	u (origin);
	i (ident);
      }
    else
      {
	if (is_import)
	  ;
	else if (TREE_CODE (ctx) != NAMESPACE_DECL)
	  tree_node (ctx);
	else
	  dep_hash->add_dependency (decl, depset::EK_DECL);

	tree_node (name);
      }
  }

 insert:
  int tag = insert (decl);
  if (streaming_p ())
    dump (dumper::TREE)
      && dump ("Wrote %s:%d %C:%N@%M", kind, tag, TREE_CODE (decl), decl,
	       origin < 0 ? NULL : (*modules)[origin]);

  add_indirects (decl);

  return false;
}

void
trees_out::type_node (tree type)
{
  gcc_assert (TYPE_P (type));

  tree root = (TYPE_NAME (type)
	       ? TREE_TYPE (TYPE_NAME (type)) : TYPE_MAIN_VARIANT (type));

  if (type != root)
    {
      if (streaming_p ())
	i (tt_variant_type);
      tree_node (root);

      int flags = -1;
      
      if (TREE_CODE (type) == FUNCTION_TYPE
	  || TREE_CODE (type) == METHOD_TYPE)
	{
	  int quals = type_memfn_quals (type);
	  int rquals = type_memfn_rqual (type);
	  tree raises = TYPE_RAISES_EXCEPTIONS (type);
	  bool late = TYPE_HAS_LATE_RETURN_TYPE (type);

	  if (raises != TYPE_RAISES_EXCEPTIONS (root)
	      || rquals != type_memfn_rqual (root)
	      || quals != type_memfn_quals (root)
	      || late != TYPE_HAS_LATE_RETURN_TYPE (root))
	    flags = rquals | (int (late) << 2) | (quals << 3);
	}
      else
	{
	  // FIXME: Align
	}

      if (streaming_p ())
	i (flags);

      if (flags < 0)
	;
      else if (TREE_CODE (type) == FUNCTION_TYPE
	       || TREE_CODE (type) == METHOD_TYPE)
	{
	  tree raises = TYPE_RAISES_EXCEPTIONS (type);
	  if (raises == TYPE_RAISES_EXCEPTIONS (root))
	    raises = error_mark_node;
	  tree_node (raises);
	}

      tree_node (error_mark_node);  // FIXME: Attribs

      if (streaming_p ())
	{
	  /* Qualifiers.  */
	  int rquals = cp_type_quals (root);
	  int quals = cp_type_quals (type);
	  if (quals == rquals)
	    quals = -1;
	  i (quals);
	}

      if (ref_node (type) != WK_none)
	{
	  int tag = insert (type);
	  if (streaming_p ())
	    {
	      i (0);
	      dump (dumper::TREE)
		&& dump ("Wrote:%d variant type %C", tag, TREE_CODE (type));
	    }
	}
      return;
    }

  if (TYPE_PTRMEMFUNC_P (type))
    {
      /* This is a distinct type node, masquerading as a structure. */ 
      tree fn_type = TYPE_PTRMEMFUNC_FN_TYPE (type);
      if (streaming_p ())
	i (tt_ptrmem_type);
      tree_node (fn_type);
      int tag = insert (type);
      if (streaming_p ())
	dump (dumper::TREE) && dump ("Writen:%d ptrmem type", tag);
      return;
    }

  if (tree name = TYPE_NAME (type))
    if (DECL_TEMPLATE_PARM_P (name)
	|| (TREE_CODE (name) == TYPE_DECL && DECL_ORIGINAL_TYPE (name))
	|| TREE_CODE (type) == RECORD_TYPE
	|| TREE_CODE (type) == UNION_TYPE
	|| TREE_CODE (type) == ENUMERAL_TYPE)
      {
	/* We can meet template parms that we didn't meet in the
	   tpl_parms walk, because we're referring to a derived type
	   that was previously constructed from equivalent template
	   parms. */
	if (streaming_p ())
	  {
	    i (tt_typedef_type);
	    dump (dumper::TREE)
	      && dump ("Writing %stypedef %C:%N",
		       DECL_IMPLICIT_TYPEDEF_P (name) ? "implicit " : "",
		       TREE_CODE (name), name);
	  }
	tree_node (name);
	if (streaming_p ())
	  dump (dumper::TREE) && dump ("Wrote typedef %C:%N%S",
				       TREE_CODE (name), name, name);
	gcc_checking_assert (TREE_VISITED (type));
	return;
      }

  if (streaming_p ())
    {
      u (tt_derived_type);
      u (TREE_CODE (type));
    }

  tree_node (TREE_TYPE (type));
  switch (TREE_CODE (type))
    {
    default:
      /* We should never meet a type here that is indescribable in
	 terms of other types.  */
      gcc_unreachable ();

    case ARRAY_TYPE:
      tree_node (TYPE_DOMAIN (type));
      break;

    case COMPLEX_TYPE:
      /* No additional data.  */
      break;

    case DECLTYPE_TYPE:
    case TYPEOF_TYPE:
    case UNDERLYING_TYPE:
      tree_node (TYPE_VALUES_RAW (type));
      if (TREE_CODE (type) == DECLTYPE_TYPE)
	/* We stash a whole bunch of things into decltype's
	   flags.  */
	if (streaming_p ())
	  tree_node_bools (type);
      break;

    case FUNCTION_TYPE:
      tree_node (TYPE_ARG_TYPES (type));
      break;

    case INTEGER_TYPE:
      if (TREE_TYPE (type))
	{
	  /* A range type (representing an array domain).  */
	  tree_node (TYPE_MIN_VALUE (type));
	  tree_node (TYPE_MAX_VALUE (type));
	}
      else
	{
	  /* A new integral type (representing a bitfield).  */
	  if (streaming_p ())
	    {
	      unsigned prec = TYPE_PRECISION (type);
	      bool unsigned_p = TYPE_UNSIGNED (type);

	      u ((prec << 1) | unsigned_p);
	    }
	}
      break;

    case METHOD_TYPE:
      tree_node (TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (type))));
      tree_node (TREE_CHAIN (TYPE_ARG_TYPES (type)));
      break;

    case OFFSET_TYPE:
      tree_node (TYPE_OFFSET_BASETYPE (type));
      break;

    case POINTER_TYPE:
      /* No additional data.  */
      break;

    case REFERENCE_TYPE:
      if (streaming_p ())
	u (TYPE_REF_IS_RVALUE (type));
      break;

    case TYPE_ARGUMENT_PACK:
      /* No additional data.  */
      break;

    case TYPE_PACK_EXPANSION:
      if (streaming_p ())
	u (PACK_EXPANSION_LOCAL_P (type));
      tree_node (PACK_EXPANSION_PARAMETER_PACKS (type));
      break;

    case TYPENAME_TYPE:
      {
	tree_node (TYPE_CONTEXT (type));
	tree_node (DECL_NAME (TYPE_NAME (type)));
	tree_node (TYPENAME_TYPE_FULLNAME (type));
	if (streaming_p ())
	  {
	    enum tag_types tag_type = none_type;
	    if (TYPENAME_IS_ENUM_P (type))
	      tag_type = enum_type;
	    else if (TYPENAME_IS_CLASS_P (type))
	      tag_type = class_type;
	    u (int (tag_type));
	  }
	}
      break;

    case UNBOUND_CLASS_TEMPLATE:
      {
	tree decl = TYPE_NAME (type);
	tree_node (DECL_CONTEXT (decl));
	tree_node (DECL_NAME (decl));
	tree_node (DECL_TEMPLATE_PARMS (decl));
      }
      break;

    case VECTOR_TYPE:
      if (streaming_p ())
	{
	  gcc_checking_assert(NUM_POLY_INT_COEFFS == 1);
	  poly_uint64 nunits = TYPE_VECTOR_SUBPARTS (type);
	  wu (static_cast<unsigned HOST_WIDE_INT> (nunits.to_constant ()));
	}
      break;
    }

  /* We may have met the type during emitting the above.  */
  if (ref_node (type) != WK_none)
    {
      int tag = insert (type);
      if (streaming_p ())
	{
	  i (0);
	  dump (dumper::TREE)
	    && dump ("Wrote:%d derived type %C", tag, TREE_CODE (type));
	}
    }

  return;
}

/* T is a non-mergeable node that must be written by value.   */

void
trees_out::tree_value (tree t)
{
  /* We should never be writing a type by value.  tree_type should
     have streamed it, or we're going via its TYPE_DECL.  */
  gcc_checking_assert (!TYPE_P (t));

  if (DECL_P (t))
    /* No template, type, var or function, except anonymous
       non-context vars.  */
    gcc_checking_assert ((TREE_CODE (t) != TEMPLATE_DECL
			  && TREE_CODE (t) != TYPE_DECL
			  && (TREE_CODE (t) != VAR_DECL
			      || (!DECL_NAME (t) && !DECL_CONTEXT (t)))
			  && TREE_CODE (t) != FUNCTION_DECL));

  int tag = insert (t, WK_value);
  if (streaming_p ())
    {
      /* A new node -> tt_node.  */
      tree_val_count++;
      i (tt_node);
      dump (dumper::TREE)
	&& dump ("Writing tree:%d %C:%N", tag, TREE_CODE (t), t);
      start (t);
      tree_node_bools (t);
    }

  tree_node_vals (t);

  if (streaming_p ())
    dump (dumper::TREE) && dump ("Written tree:%d %C:%N", tag, TREE_CODE (t), t);
}

tree
trees_in::tree_value ()
{
  tree t = start ();
  if (!t || !tree_node_bools (t))
    return NULL_TREE;

  /* Insert into map.  */
  int tag = insert (t);
  dump (dumper::TREE)
    && dump ("Reading tree:%d %C", tag, TREE_CODE (t));

  if (!tree_node_vals (t))
    {
      back_refs[~tag] = NULL_TREE;
      set_overrun ();
      /* Bail.  */
      return NULL_TREE;
    }

  dump (dumper::TREE) && dump ("Read tree:%d %C:%N", tag, TREE_CODE (t), t);

  if (TREE_CODE (t) == INTEGER_CST && !TREE_OVERFLOW (t))
    {
      t = cache_integer_cst (t, true);
      back_refs[~tag] = t;
    }

  return t;
}

/* Stream out tree node T.  We automatically create local back
   references, which is essentially the lisp self-referential
   structure pretty-printer.  */

void
trees_out::tree_node (tree t)
{
  dump.indent ();
  walk_kind ref = ref_node (t);
  if (ref == WK_none)
    goto done;

  if (ref != WK_normal)
    goto skip_normal;

  if (TREE_CODE (t) == IDENTIFIER_NODE)
    {
      /* An identifier node -> tt_id, tt_conv_id, tt_anon_id, tt_lambda_id.  */
      int code = tt_id;
      if (IDENTIFIER_ANON_P (t))
	code = IDENTIFIER_LAMBDA_P (t) ? tt_lambda_id : tt_anon_id;
      else if (IDENTIFIER_CONV_OP_P (t))
	code = tt_conv_id;

      if (streaming_p ())
	i (code);

      if (code == tt_conv_id)
	tree_node (TREE_TYPE (t));
      else if (code == tt_id && streaming_p ())
	str (IDENTIFIER_POINTER (t), IDENTIFIER_LENGTH (t));

      int tag = insert (t);
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Written:%d %sidentifier:%N", tag,
		   code == tt_conv_id ? "conv_op "
		   : code == tt_anon_id ? "anon "
		   : code == tt_lambda_id ? "lambda "
		   : "",
		   code == tt_conv_id ? TREE_TYPE (t) : t);
      goto done;
    }

  if (TREE_CODE (t) == TREE_BINFO)
    {
      /* A BINFO -> tt_binfo.
	 We must do this by reference.  We stream the binfo tree
	 itself when streaming its owning RECORD_TYPE.  That we got
	 here means the dominating type is not in this SCC.  */
      if (streaming_p ())
	i (tt_binfo);
      tree_binfo (t, 0, false);

      gcc_checking_assert (!TREE_VISITED (t));
      int tag = insert (t);
      if (streaming_p ())
	dump (dumper::TREE) && dump ("Inserting binfo:%d %N", tag, t);
      goto done;
    }

  if (TREE_CODE (t) == INTEGER_CST
      && !TREE_OVERFLOW (t)
      && TREE_CODE (TREE_TYPE (t)) == ENUMERAL_TYPE)
    {
      /* An integral constant of enumeral type.  See if it matches one
	 of the enumeration values.  */
      for (tree values = TYPE_VALUES (TREE_TYPE (t));
	   values; values = TREE_CHAIN (values))
	{
	  tree decl = TREE_VALUE (values);
	  if (tree_int_cst_equal (DECL_INITIAL (decl), t))
	    {
	      if (streaming_p ())
		u (tt_enum_int);
	      tree_node (decl);
	      dump (dumper::TREE) && dump ("Written enum value %N", decl);
	      goto done;
	    }
	}
      /* It didn't match.  We'll write it a an explicit INTEGER_CST
	 node.  */
    }

  if (TYPE_P (t))
    {
      type_node (t);
      goto done;
    }

 skip_normal:
  if (DECL_P (t))
    {
      if (DECL_TEMPLATE_PARM_P (t))
	{
	  tpl_parm_value (t);
	  goto done;
	}

      if (!decl_node (t, ref))
	goto done;
    }

  /* Otherwise by value */
  tree_value (t);

 done:
  /* And, breath out.  */
  dump.outdent ();
}

/* Stream in a tree node.  */

tree
trees_in::tree_node ()
{
  if (get_overrun ())
    return NULL_TREE;

  dump.indent ();
  int tag = i ();
  tree res = NULL_TREE;
  switch (tag)
    {
    default:
      /* backref, pull it out of the map.  */
      res = back_ref (tag);
      break;

    case tt_null:
      /* NULL_TREE.  */
      break;

    case tt_fixed:
      /* A fixed ref, find it in the fixed_ref array.   */
      {
	unsigned fix = u ();
	if (fix < (*fixed_trees).length ())
	  {
	    res = (*fixed_trees)[fix];
	    dump (dumper::TREE) && dump ("Read fixed:%u %C:%N%S", fix,
					 TREE_CODE (res), res, res);
	  }

	if (!res)
	  set_overrun ();
      }
      break;

    case tt_parm:
      {
	tree fn = tree_node ();
	if (fn && TREE_CODE (fn) == FUNCTION_DECL)
	  res = tree_node ();
	if (res)
	  dump (dumper::TREE)
	    && dump ("Read %s reference %N",
		     TREE_CODE (res) == PARM_DECL ? "parameter" : "result",
		     res);
      }
      break;

    case tt_node:
      /* A new node.  Stream it in.  */
      res = tree_value ();
      break;

    case tt_decl:
      /* A new decl.  Stream it in.  */
      res = decl_value ();
      break;

    case tt_tpl_parm:
      /* A template parameter.  Stream it in.  */
      res = tpl_parm_value ();
      break;

    case tt_id:
      /* An identifier node.  */
      {
	size_t l;
	const char *chars = str (&l);
	res = get_identifier_with_length (chars, l);
	int tag = insert (res);
	dump (dumper::TREE)
	  && dump ("Read identifier:%d %N", tag, res);
      }
      break;

    case tt_conv_id:
      /* A conversion operator.  Get the type and recreate the
	 identifier.  */
      {
	tree type = tree_node ();
	if (!get_overrun ())
	  {
	    res = make_conv_op_name (type);
	    int tag = insert (res);
	    dump (dumper::TREE)
	      && dump ("Created conv_op:%d %S for %N", tag, res, type);
	  }
      }
      break;

    case tt_anon_id:
    case tt_lambda_id:
      /* An anonymous or lambda id.  */
      {
	res = make_anon_name ();
	if (tag == tt_lambda_id)
	  IDENTIFIER_LAMBDA_P (res) = true;
	int tag = insert (res);
	dump (dumper::TREE)
	  && dump ("Read %s identifier:%d %N",
		   IDENTIFIER_LAMBDA_P (res) ? "lambda" : "anon", tag, res);
      }
      break;

    case tt_typedef_type:
      res = tree_node ();
      if (res)
	{
	  dump (dumper::TREE)
	    && dump ("Read %stypedef %C:%N",
		     DECL_IMPLICIT_TYPEDEF_P (res) ? "implicit " : "",
		     TREE_CODE (res), res);
	  res = TREE_TYPE (res);
	}
      break;

    case tt_derived_type:
      /* A type derived from some other type.  */
      {
	enum tree_code code = tree_code (u ());
	res = tree_node ();

	switch (code)
	  {
	  default:
	    set_overrun ();
	    break;

	  case ARRAY_TYPE:
	    {
	      tree domain = tree_node ();
	      if (!get_overrun ())
		res = build_cplus_array_type (res, domain);
	    }
	    break;

	  case COMPLEX_TYPE:
	    if (!get_overrun ())
	      res = build_complex_type (res);
	    break;

	  case INTEGER_TYPE:
	    if (res)
	      {
		/* A range type (representing an array domain).  */
		tree min = tree_node ();
		tree max = tree_node ();

		if (!get_overrun ())
		  res = build_range_type (res, min, max);
	      }
	    else
	      {
		/* A new integral type (representing a bitfield).  */
		unsigned enc = u ();
		if (!get_overrun ())
		  res = build_nonstandard_integer_type (enc >> 1, enc & 1);
	      }
	    break;

	  case DECLTYPE_TYPE:
	  case TYPEOF_TYPE:
	  case UNDERLYING_TYPE:
	    {
	      tree expr = tree_node ();
	      if (!get_overrun ())
		{
		  res = cxx_make_type (code);
		  TYPE_VALUES_RAW (res) = expr;
		  if (code == DECLTYPE_TYPE)
		    tree_node_bools (res);
		  SET_TYPE_STRUCTURAL_EQUALITY (res);
		}
	    }
	    break;

	  case FUNCTION_TYPE:
	    {
	      tree args = tree_node ();
	      if (!get_overrun ())
		res = build_function_type (res, args);
	    }
	    break;

	  case METHOD_TYPE:
	    {
	      tree klass = tree_node ();
	      tree args = tree_node ();
	      
	      if (!get_overrun ())
		res = build_method_type_directly (klass, res, args);
	    }
	    break;
	    
	  case OFFSET_TYPE:
	    {
	      tree base = tree_node ();
	      if (!get_overrun ())
		res = build_offset_type (base, res);
	    }
	    break;

	  case POINTER_TYPE:
	    if (!get_overrun ())
	      res = build_pointer_type (res);
	    break;

	  case REFERENCE_TYPE:
	    {
	      bool rval = bool (u ());
	      if (!get_overrun ())
		res = cp_build_reference_type (res, rval);
	    }
	    break;

	  case TYPE_ARGUMENT_PACK:
	    if (!get_overrun ())
	      {
		tree pack = cxx_make_type (TYPE_ARGUMENT_PACK);
		SET_TYPE_STRUCTURAL_EQUALITY (pack);
		SET_ARGUMENT_PACK_ARGS (pack, res);
		res = pack;
	      }
	    break;

	  case TYPE_PACK_EXPANSION:
	    {
	      bool local = u ();
	      tree param_packs = tree_node ();
	      if (!get_overrun ())
		{
		  tree expn = cxx_make_type (TYPE_PACK_EXPANSION);
		  SET_TYPE_STRUCTURAL_EQUALITY (expn);
		  SET_PACK_EXPANSION_PATTERN (expn, res);
		  PACK_EXPANSION_PARAMETER_PACKS (expn) = param_packs;
		  PACK_EXPANSION_LOCAL_P (expn) = local;
		  res = expn;
		}
	    }
	    break;

	  case TYPENAME_TYPE:
	    {
	      tree ctx = tree_node ();
	      tree name = tree_node ();
	      tree fullname = tree_node ();
	      enum tag_types tag_type = tag_types (u ());

	      if (!get_overrun ())
		res = build_typename_type (ctx, name, fullname, tag_type);
	    }
	    break;

	  case UNBOUND_CLASS_TEMPLATE:
	    {
	      tree ctx = tree_node ();
	      tree name = tree_node ();
	      tree parms = tree_node ();

	      if (!get_overrun ())
		res = make_unbound_class_template_raw (ctx, name, parms);
	    }
	    break;

	  case VECTOR_TYPE:
	    {
	      unsigned HOST_WIDE_INT nunits = wu ();
	      if (!get_overrun ())
		res = build_vector_type (res, static_cast<poly_int64> (nunits));
	    }
	    break;
	  }

	int tag = i ();
	if (!tag)
	  {
	    tag = insert (res);
	    if (res)
	      dump (dumper::TREE)
		&& dump ("Created:%d derived type %C", tag, code);
	  }
	else
	  res = back_ref (tag);
      }
      break;

    case tt_variant_type:
      /* Variant of some type.  */
      {
	res = tree_node ();
	int flags = i ();
	if (get_overrun ())
	  ;
	else if (flags < 0)
	  /* No change.  */;
	else if (TREE_CODE (res) == FUNCTION_TYPE
		 || TREE_CODE (res) == METHOD_TYPE)
	  {
	    cp_ref_qualifier rqual = cp_ref_qualifier (flags & 3);
	    bool late = (flags >> 2) & 1;
	    cp_cv_quals quals = cp_cv_quals (flags >> 3);

	    tree raises = tree_node ();
	    if (raises == error_mark_node)
	      raises = TYPE_RAISES_EXCEPTIONS (res);

	    res = build_cp_fntype_variant (res, rqual, raises, late);
	    if (TREE_CODE (res) == FUNCTION_TYPE)
	      res = apply_memfn_quals (res, quals, rqual);
	  }
	else
	  {
	    res = build_aligned_type (res, flags);
	    TYPE_USER_ALIGN (res) = true;
	  }

	tree attribs = tree_node ();
	if (attribs != error_mark_node
	    && !get_overrun ())
	  res = cp_build_type_attribute_variant (res, attribs);

	int quals = i ();
	if (quals >= 0 && !get_overrun ())
	  res = cp_build_qualified_type (res, quals);

	int tag = i ();
	if (!tag)
	  {
	    tag = insert (res);
	    if (res)
	      dump (dumper::TREE)
		&& dump ("Created:%d variant type %C", tag, TREE_CODE (res));
	  }
	else
	  res = back_ref (tag);
      }
      break;

    case tt_tinfo_var:
    case tt_tinfo_typedef:
      /* A tinfo var or typedef.  */
      {
	bool is_var = tag == tt_tinfo_var;
	unsigned ix = u ();
	tree type = NULL_TREE;

	if (is_var)
	  {
	    tree name = tree_node ();
	    type = tree_node ();

	    if (!get_overrun ())
	      res = get_tinfo_decl_direct (type, name, int (ix));
	  }
	else
	  {
	    if (!get_overrun ())
	      {
		type = get_pseudo_tinfo_type (ix);
		res = TYPE_NAME (type);
	      }
	  }
	if (res)
	  {
	    int tag = insert (res);
	    dump (dumper::TREE)
	      && dump ("Created tinfo_%s:%d %S:%u for %N",
		       is_var ? "var" : "decl", tag, res, ix, type);
	    if (!is_var)
	      {
		tag = insert (type);
		dump (dumper::TREE)
		  && dump ("Created tinfo_type:%d %u %N", tag, ix, type);
	      }
	  }
      }
      break;

    case tt_ptrmem_type:
      /* A pointer to member function.  */
      {
	tree type = tree_node ();
	if (type && TREE_CODE (type) == POINTER_TYPE
	    && TREE_CODE (TREE_TYPE (type)) == METHOD_TYPE)
	  {
	    res = build_ptrmemfunc_type (type);
	    int tag = insert (res);
	    dump (dumper::TREE) && dump ("Created:%d ptrmem type", tag);
	  }
	else
	  set_overrun ();
      }
      break;

    case tt_enum_int:
      /* An enum const value.  */
      {
	if (tree decl = tree_node ())
	  {
	    dump (dumper::TREE) && dump ("Read enum value %N", decl);
	    res = DECL_INITIAL (decl);
	  }

	if (!res)
	  set_overrun ();
      }
      break;

    case tt_data_member:
      /* A data member or enumeration constant.  */
      {
	tree ctx = tree_node ();
	tree name = tree_node ();

	if (get_overrun ())
	  ;
	else if (TREE_CODE (ctx) == ENUMERAL_TYPE)
	  {
	    for (tree values = TYPE_VALUES (ctx);
		 values; values = TREE_CHAIN (values))
	      if (DECL_NAME (TREE_VALUE (values)) == name)
		{
		  res = TREE_VALUE (values);
		  break;
		}
	  }
	else if (RECORD_OR_UNION_TYPE_P (ctx))
	  {
	    unsigned ix = name ? 0 : u ();
	    res = lookup_field_ident (ctx, name, ix);
	  }

	if (!res)
	  set_overrun ();
	else
	  {
	    int tag = insert (res);
	    dump (dumper::TREE)
	      && dump ("Read member:%d %C:%N", tag, TREE_CODE (res), res);
	  }
      }
      break;

    case tt_namespace:
      /* Namespace reference.  */
      {
	int origin = i ();
	tree ctx = tree_node ();
	tree name = tree_node ();

	if (origin >= 0)
	  origin = state->slurp->remap_module (origin);

	res = get_imported_namespace (ctx, name, origin);
	if (!res || TREE_CODE (res) != NAMESPACE_DECL)
	  {
	    error_at (state->loc, "failed to find namespace %<%E%s%E%>",
		      ctx, &"::"[2 * (ctx == global_namespace)],
		      name);
	    set_overrun ();
	    res = NULL;
	  }

	if (res)
	  {
	    int tag = insert (res);
	    dump (dumper::TREE)
	      && dump ("Namespace:%d %C:%N@%M", tag, TREE_CODE (res),
		       res, origin < 0 ? NULL : (*modules)[origin]);
	  }
      }
      break;

    case tt_binfo:
      /* A BINFO.  Walk the tree of the dominating type.  */
      {
	res = tree_binfo ();
	if (get_overrun ())
	  break;

	/* Insert binfo into backreferences.  */
	tag = insert (res);
	dump (dumper::TREE) && dump ("Read binfo:%d %N", tag, res);
      }
      break;

    case tt_vtable:
      {
	unsigned ix = u ();
	tree ctx = tree_node ();
	dump (dumper::TREE) && dump ("Reading vtable %N[%u]", ctx, ix);
	if (TREE_CODE (ctx) == RECORD_TYPE && TYPE_LANG_SPECIFIC (ctx))
	  for (res = CLASSTYPE_VTABLES (ctx); res; res = DECL_CHAIN (res))
	    if (!ix--)
	      break;
	if (res)
	  mark_used (res, tf_none);
	else
	  set_overrun ();
      }
      break;

    case tt_thunk:
      {
	int fixed = i ();
	tree target = tree_node ();
	tree virt = tree_node ();

	for (tree thunk = DECL_THUNKS (target);
	     thunk; thunk = DECL_CHAIN (thunk))
	  if (THUNK_FIXED_OFFSET (thunk) == fixed
	      && !THUNK_VIRTUAL_OFFSET (thunk) == !virt
	      && (!virt
		  || tree_int_cst_equal (virt, THUNK_VIRTUAL_OFFSET (thunk))))
	    {
	      res = thunk;
	      break;
	    }

	int tag = insert (res);
	if (res)
	  dump (dumper::TREE)
	    && dump ("Read:%d thunk %N to %N", tag, DECL_NAME (res), target);
	else
	  set_overrun ();
      }
      break;

    case tt_clone_ref:
      {
	tree target = tree_node ();
	tree name = tree_node ();

	if (DECL_P (target) && DECL_MAYBE_IN_CHARGE_CDTOR_P (target))
	  {
	    tree clone;
	    FOR_EVERY_CLONE (clone, target)
	      if (DECL_NAME (clone) == name)
		{
		  res = clone;
		  break;
		}
	  }

	if (!res)
	  set_overrun ();
	int tag = insert (res);
	if (res)
	  dump (dumper::TREE)
	    && dump ("Read:%d clone %N of %N", tag, DECL_NAME (res), target);
	else
	  set_overrun ();
       }
      break;

    case tt_entity:
      /* Index into the entity table.  Perhaps not loaded yet!  */
      {
	unsigned origin = state->slurp->remap_module (u ());
	int ident = i (); // FIXME: unsigned when tt_named etc die
	module_state *from = (*modules)[origin];

	if (unsigned (ident) >= from->entity_num)
	  set_overrun ();
	if (!get_overrun ())
	  {
	    mc_slot *slot = &(*entity_ary)[from->entity_lwm + ident];
	    if (slot->is_lazy ())
	      from->lazy_load (ident, slot);
	    res = *slot;
	  }

	if (res)
	  {
	    const char *kind = (origin != state->mod ? "Imported" : "Named");
	    int tag = insert (res);
	    dump (dumper::TREE)
	      && dump ("%s:%d %C:%N@%M", kind, tag, TREE_CODE (res),
		       res, (*modules)[origin]);

	    if (!add_indirects (res))
	      {
		set_overrun ();
		res = NULL_TREE;
	      }
	  }
      }
      break;

    case tt_named:
    case tt_implicit_template:
      /* A named, anonymois or implicit decl.  */
      {
	tree ctx = tree_node ();
	tree name = tree_node ();

	// FIXME: I think owner is only needed for namespace-scope
	// CTX?  Yup.
	int origin = u ();
	origin = state->slurp->remap_module (origin);
	int ident = i ();
	if (!get_overrun ()
	    && (origin >= 0 || TREE_CODE (ctx) != NAMESPACE_DECL))
	  {
	    res = lookup_by_ident (ctx, name, origin, ident);
	    if (!res)
	      ;
	    else if (tag == tt_implicit_template)
	      {
		int use_tpl = -1;
		tree ti = node_template_info (res, use_tpl);
		res = TI_TEMPLATE (ti);
	      }
	  }

	if (!res)
	  {
	    error_at (state->loc, "failed to find %<%E%s%E%s%s%>",
		      ctx, &"::"[2 * (ctx == global_namespace)],
		      name ? name : get_identifier ("<anonymous>"),
		      origin >= 0 ? "@" : "",
		      origin >= 0 ? (*modules)[origin]->get_flatname () : "");
	    set_overrun ();
	  }
	else if (TREE_CODE (res) != TYPE_DECL && origin != state->mod)
	  mark_used (res, tf_none);

	if (res)
	  {
	    const char *kind = (origin != state->mod ? "Imported" : "Named");
	    int tag = insert (res);
	    dump (dumper::TREE)
	      && dump ("%s:%d %C:%N@%M", kind, tag, TREE_CODE (res),
		       res, (*modules)[origin]);

	    if (!add_indirects (res))
	      {
		set_overrun ();
		res = NULL_TREE;
	      }
	  }
      }
      break;

    case tt_template:
      /* A template.  */
      if (tree tpl = tree_node ())
	{
	  res = DECL_TEMPLATE_RESULT (tpl);
	  dump (dumper::TREE)
	    && dump ("Read template %C:%N", TREE_CODE (res), res);
	}
      break;

    case tt_friend_template:
      /* A (local template) friend of a template class.  */
      if (tree klass = tree_node ())
	{
	  unsigned ix = u ();
	  unsigned u = ix;
	  for (tree decls = CLASSTYPE_DECL_LIST (klass);
	       decls; decls = TREE_CHAIN (decls))
	    if (!TREE_PURPOSE (decls) && !u--)
	      {
		res = TREE_VALUE (decls);
		break;
	      }

	  if (res)
	    {
	      if (TREE_CODE (res) != TEMPLATE_DECL)
		res = DECL_TI_TEMPLATE (res);
	      dump (dumper::TREE)
		&& dump ("Read friend %N[%d] %C:%N",
			 klass, ix, TREE_CODE (res), res);
	    }
	}
      break;
    }

  dump.outdent ();
  return res;
}

void
trees_out::tpl_parms (tree parms, unsigned &tpl_levels)
{
  if (!parms)
    return;

  if (TREE_VISITED (parms))
    {
      ref_node (parms);
      return;
    }

  tpl_parms (TREE_CHAIN (parms), tpl_levels);

  tree vec = TREE_VALUE (parms);
  unsigned len = TREE_VEC_LENGTH (vec);
  /* Depth.  */
  int tag = insert (parms);
  if (streaming_p ())
    {
      i (len + 1);
      dump (dumper::TREE)
	&& dump ("Writing template parms:%d level:%N length:%d",
		 tag, TREE_PURPOSE (parms), len);
    }
  tree_node (TREE_PURPOSE (parms));

  for (unsigned ix = 0; ix != len; ix++)
    {
      tree parm = TREE_VEC_ELT (vec, ix);
      tree decl = TREE_VALUE (parm);

      gcc_checking_assert (DECL_TEMPLATE_PARM_P (decl));
      if (CHECKING_P)
	switch (TREE_CODE (decl))
	  {
	  default: gcc_unreachable ();

	  case TEMPLATE_DECL:
	    gcc_assert ((TREE_CODE (TREE_TYPE (decl)) == TEMPLATE_TEMPLATE_PARM)
			&& (TREE_CODE (DECL_TEMPLATE_RESULT (decl)) == TYPE_DECL)
			&& (TYPE_NAME (TREE_TYPE (decl)) == decl));
	    break;

	  case TYPE_DECL:
	    gcc_assert ((TREE_CODE (TREE_TYPE (decl)) == TEMPLATE_TYPE_PARM)
			&& (TYPE_NAME (TREE_TYPE (decl)) == decl));
	    break;

	  case PARM_DECL:
	    gcc_assert ((TREE_CODE (DECL_INITIAL (decl)) == TEMPLATE_PARM_INDEX)
			&& (TREE_CODE (TEMPLATE_PARM_DECL (DECL_INITIAL (decl)))
			    == CONST_DECL)
			&& (DECL_TEMPLATE_PARM_P
			    (TEMPLATE_PARM_DECL (DECL_INITIAL (decl)))));
	    break;
	  }

      tree_node (decl);
      tree_node (TEMPLATE_PARM_CONSTRAINTS (parm));
    }

  tpl_levels++;
}

tree
trees_in::tpl_parms (unsigned &tpl_levels)
{
  tree parms = NULL_TREE;

  while (int len = i ())
    {
      if (len < 0)
	{
	  parms = back_ref (len);
	  continue;
	}

      len -= 1;
      parms = tree_cons (NULL_TREE, NULL_TREE, parms);
      int tag = insert (parms);
      TREE_PURPOSE (parms) = tree_node ();

      dump (dumper::TREE)
	&& dump ("Reading template parms:%d level:%N length:%d",
		 tag, TREE_PURPOSE (parms), len);

      tree vec = make_tree_vec (len);
      for (int ix = 0; ix != len; ix++)
	{
	  tree decl = tree_node ();
	  if (!decl)
	    return NULL_TREE;

	  tree parm = build_tree_list (NULL, decl);
	  TEMPLATE_PARM_CONSTRAINTS (parm) = tree_node ();

	  TREE_VEC_ELT (vec, ix) = parm;
	}

      TREE_VALUE (parms) = vec;
      tpl_levels++;
    }

  return parms;
}

void
trees_out::tpl_parms_fini (tree tmpl, unsigned tpl_levels)
{
  for (tree parms = DECL_TEMPLATE_PARMS (tmpl);
       tpl_levels--; parms = TREE_CHAIN (parms))
    {
      tree vec = TREE_VALUE (parms);

      tree_node (TREE_TYPE (vec));
      tree dflt = error_mark_node;
      for (unsigned ix = TREE_VEC_LENGTH (vec); ix--;)
	{
	  tree parm = TREE_VEC_ELT (vec, ix);
	  if (dflt)
	    {
	      dflt = TREE_PURPOSE (parm);
	      tree_node (dflt);
	    }

	  tree decl = TREE_VALUE (parm);
	  if (TREE_CODE (decl) == TEMPLATE_DECL)
	    gcc_checking_assert (DECL_CONTEXT (decl) == tmpl);
	}
    }
}

bool
trees_in::tpl_parms_fini (tree tmpl, unsigned tpl_levels)
{
  for (tree parms = DECL_TEMPLATE_PARMS (tmpl);
       tpl_levels--; parms = TREE_CHAIN (parms))
    {
      tree vec = TREE_VALUE (parms);
      tree dflt = error_mark_node;

      TREE_TYPE (vec) = tree_node ();
      for (unsigned ix = TREE_VEC_LENGTH (vec); ix--;)
	{
	  tree parm = TREE_VEC_ELT (vec, ix);
	  if (dflt)
	    {
	      dflt = tree_node ();
	      if (get_overrun ())
		return false;
	      TREE_PURPOSE (parm) = dflt;
	    }

	  tree decl = TREE_VALUE (parm);
	  if (TREE_CODE (decl) == TEMPLATE_DECL)
	    DECL_CONTEXT (decl) = tmpl;
	}
    }
  return true;
}

/* PARMS is a LIST, one node per level.
   TREE_VALUE is a TREE_VEC of parm info for that level.
   each ELT is a TREE_LIST
   TREE_VALUE is PARM_DECL, TYPE_DECL or TEMPLATE_DECL
   TREE_PURPOSE is the default value.  */

void
trees_out::tpl_header (tree tpl, unsigned *tpl_levels)
{
  tree parms = DECL_TEMPLATE_PARMS (tpl);
  tpl_parms (parms, *tpl_levels);

  /* Mark end.  */
  if (streaming_p ())
    u (0);

  if (*tpl_levels)
    tree_node (TEMPLATE_PARM_CONSTRAINTS (parms));
}

bool
trees_in::tpl_header (tree tpl, unsigned *tpl_levels)
{
  tree parms = tpl_parms (*tpl_levels);
  if (!parms)
    return false;

  DECL_TEMPLATE_PARMS (tpl) = parms;

  if (*tpl_levels)
    TEMPLATE_PARM_CONSTRAINTS (parms) = tree_node ();

  return true;
}

/* PARMS is a LIST whose TREE_VALUE is the type of the parm.  */

void
trees_out::fn_arg_types (tree arg_types)
{
  for (; arg_types; arg_types = TREE_CHAIN (arg_types))
    tree_node (TREE_VALUE (arg_types));
  tree_node (NULL_TREE);
}

tree
trees_in::fn_arg_types ()
{
  tree arg_types = NULL_TREE;
  tree *arg_ptr = &arg_types;

  while (tree arg = tree_node ())
    {
      *arg_ptr = tree_cons (NULL_TREE, arg, NULL_TREE);
      arg_ptr = &TREE_CHAIN (*arg_ptr);
    }

  return arg_types;
}

/* Stream skeleton parm nodes, with their flags, type & parm indices.
   All the parms will have consecutive tags.  */

void
trees_out::fn_parms_init (tree fn)
{
  /* First init them.  */
  int base_tag = ref_num - 1;
  int ix = 0;
  for (tree parm = DECL_ARGUMENTS (fn);
       parm; parm = DECL_CHAIN (parm), ix++)
    {
      if (streaming_p ())
	{
	  start (parm);
	  tree_node_bools (parm);
	}
      int tag = insert (parm);
      gcc_checking_assert (base_tag - ix == tag);
    }
  /* Mark the end.  */
  if (streaming_p ())
    u (0);

  /* Now stream their contents.  */
  ix = 0;
  for (tree parm = DECL_ARGUMENTS (fn);
       parm; parm = DECL_CHAIN (parm), ix++)
    {
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Writing parm:%d %u (%N) of %N",
		   base_tag - ix, ix, parm, fn);
      tree_node_vals (parm);
    }
}

/* Build skeleton parm nodes, read their flags, type & parm indices.  */

int
trees_in::fn_parms_init (tree fn)
{
  int base_tag = ~(int)back_refs.length ();

  tree *parm_ptr = &DECL_ARGUMENTS (fn);
  int ix = 0;
  for (; int code = u (); ix++)
    {
      tree parm = start (code);
      if (!tree_node_bools (parm))
	return 0;

      int tag = insert (parm);
      gcc_checking_assert (base_tag - ix == tag);
      *parm_ptr = parm;
      parm_ptr = &DECL_CHAIN (parm);
    }

  ix = 0;
  for (tree parm = DECL_ARGUMENTS (fn);
       parm; parm = DECL_CHAIN (parm), ix++)
    {
      dump (dumper::TREE)
	&& dump ("Reading parm:%d %u (%N) of %N",
		 base_tag - ix, ix, parm, fn);
      if (!tree_node_vals (parm))
	return 0;
    }

  return base_tag;
}

/* Read the remaining parm node data.  Replace with existing (if
   non-null) in the map.  */

void
trees_in::fn_parms_fini (int tag, tree fn, tree existing, bool is_defn)
{
  tree existing_parm = existing ? DECL_ARGUMENTS (existing) : NULL_TREE;
  tree parms = DECL_ARGUMENTS (fn);
  unsigned ix = 0;
  for (tree parm = parms; parm; parm = DECL_CHAIN (parm), ix++)
    {
      if (existing_parm)
	{
	  if (is_defn && !DECL_SAVED_TREE (existing))
	    {
	      /* If we're about to become the definition, set the
		 names of the parms from us.  */
	      DECL_NAME (existing_parm) = DECL_NAME (parm);
	      DECL_SOURCE_LOCATION (existing_parm) = DECL_SOURCE_LOCATION (parm);
	    }

	  back_refs[~tag] = existing_parm;
	  existing_parm = DECL_CHAIN (existing_parm);
	}
      tag--;
    }
}

/* DEP is the depset of some decl we're streaming by value.  Determine
   the merging behaviour.  */

merge_kind
trees_out::get_merge_kind (depset *dep)
{
  if (!dep)
    return MK_unique;

  tree decl = dep->get_entity ();

  merge_kind mk = MK_named;
  switch (dep->get_entity_kind ())
    {
    default:
      if (TREE_CODE (decl) == TYPE_DECL)
	{
	  tree type = TREE_TYPE (decl);

	  gcc_checking_assert (decl == TYPE_NAME (type));
	  if (IDENTIFIER_ANON_P (DECL_NAME (decl)))
	    {
	      if (TREE_CODE (type) == ENUMERAL_TYPE && TYPE_VALUES (type))
		/* Keyed by first enum value.  */
		mk = MK_enum;
	      else
		/* No way to merge it.  */
		mk = MK_unique;
	    }
	}
      break;

    case depset::EK_SPECIALIZATION:
      {
	gcc_checking_assert (dep->is_special ());
	spec_entry *entry = reinterpret_cast <spec_entry *> (dep->deps[0]);

	if (!dep->is_type_spec ())
	  mk = MK_decl_spec;
	else if (dep->is_partial ())
	  mk = MK_type_partial_spec;
	else
	  mk = MK_type_spec;

	if (TREE_CODE (decl) == TEMPLATE_DECL)
	  {
	    tree res = DECL_TEMPLATE_RESULT (decl);
	    if (!(mk & MK_tmpl_decl_mask))
	      res = TREE_TYPE (res);
	    if (res == entry->spec)
	      mk = merge_kind (mk | MK_tmpl_tmpl_mask);
	  }

	// FIXME: check if BOTH_SPEC_BIT
	if (false)
	  mk = merge_kind (mk | MK_tmpl_both_mask);
      }
      break;
    }

  return mk;
}

tree
trees_out::get_container (tree decl)
{
  tree container = NULL_TREE;

  if (TREE_CODE (decl) == TEMPLATE_DECL)
    if (DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (decl))
      container = DECL_CHAIN (decl);
  if (!container)
    container = CP_DECL_CONTEXT (decl);
  if (TYPE_P (container))
    container = TYPE_NAME (container);

  int use_tpl;
  if (tree template_info = node_template_info (container, use_tpl))
    {
      if (use_tpl == 2)
	{
	  /* A partial or explicit specialization.  */
	  if (depset *dep = dep_hash->find_entity (decl))
	    if (dep->get_entity_kind () == depset::EK_REDIRECT)
	      container = dep->deps[0]->get_entity ();
	}
      else if (!use_tpl)
	container = TI_TEMPLATE (template_info);
    }

  return container;
}

/* Write out key information about a mergeable DEP.  Does not write
   the contents of DEP itself.  */
// FIXME: constraints probably need streaming too?

void
trees_out::key_mergeable (merge_kind mk, depset *dep, tree decl)
{
  if (streaming_p ())
    dump (dumper::MERGE)
      && dump ("Writing %s key for mergeable %s %C:%N", merge_kind_name[mk],
	       dep ? dep->entity_kind_name () : "unique",
	       TREE_CODE (decl), decl);

  tree inner = decl;
  if (TREE_CODE (decl) == TEMPLATE_DECL)
    /* A template needs its template parms for identification.  */
    inner = DECL_TEMPLATE_RESULT (decl);

  /* Now write the locating information. */
  if (mk & MK_template_mask)
    {
      /* Specializations are located via their originating template,
	 and the set of template args they specialize.  */
      gcc_checking_assert (dep && dep->is_special ());
      spec_entry *entry = reinterpret_cast <spec_entry *> (dep->deps[0]);
      tree_node (entry->tmpl);
      tree_node (entry->args);

      // FIXME:variable templates with concepts need constraints from
      // the specialization -- see spec_hasher::equal
      if (CHECKING_P)
	{
	  /* Make sure we can locate the decl.  */
	  tree existing = check_mergeable_specialization
	    (bool (mk & MK_tmpl_decl_mask), entry);

	  gcc_assert (existing);
	  if (mk & MK_tmpl_decl_mask)
	    {
	      if (mk & MK_tmpl_tmpl_mask)
		if (tree ti = DECL_TEMPLATE_INFO (existing))
		  existing = TI_TEMPLATE (ti);
	      if (mk & MK_tmpl_both_mask)
		{} // FIXME: check it's inthe type table too
	    }
	  else
	    {
	      if (!(mk & MK_tmpl_tmpl_mask))
		existing = TYPE_NAME (existing);
	      else if (mk & MK_tmpl_partial_mask)
		{
		  /* A partial specialization.  */
		  for (tree partial
			 = DECL_TEMPLATE_SPECIALIZATIONS (entry->tmpl);
		       partial; partial = TREE_CHAIN (partial))
		    if (TREE_TYPE (partial) == existing)
		      {
			existing = TREE_VALUE (partial);
			break;
		      }
		}
	      else
		if (tree ti = CLASSTYPE_TEMPLATE_INFO (existing))
		  existing = TI_TEMPLATE (ti);
	    }
	  /* The walkabout should have found ourselves.  */
	  gcc_assert (existing == decl);
	}
    }
 else if (mk & MK_indirect_mask)
   {
     tree name = decl;

     if (mk == MK_enum)
       {
	 /* Anonymous enums are located by their first identifier.  */
	 gcc_checking_assert (UNSCOPED_ENUM_P (TREE_TYPE (decl)));
	 if (tree values = TYPE_VALUES (TREE_TYPE (decl)))
	   name = DECL_NAME (TREE_VALUE (values));
       }
     else
       {
	 /* Anonymous types with a typedef name for linkage purposes
	    are located by that typedef.  */
	 name = TYPE_NAME (TREE_TYPE (decl));
	 gcc_checking_assert (!IDENTIFIER_ANON_P (DECL_NAME (name)));
       }

     tree_node (name);
   }
 else
   {
     /* Regular decls are located by their context, name, and
	additional disambiguating data.  */
     tree_node (DECL_NAME (decl));

     if (TREE_CODE (inner) == FUNCTION_DECL)
       {
	 /* Functions are distinguished by parameter types.  */
	 tree fn_type = TREE_TYPE (inner);
	 fn_arg_types (TYPE_ARG_TYPES (fn_type));

	 if (decl != inner)
	   /* And a function template needs the return type.  */
	   // FIXME: What if the return type is a voldemort?  We
	   // should be using the declared return type.
	   tree_node (TREE_TYPE (fn_type));
       }
   }
}

/* DECL, INNER & TYPE are a skeleton set of nodes for a decl.  Only
   the bools have been filled in.  Read its merging key.  Returns
   IS_SPECIALIZATION.  *CONTAINER will be NULL on error.  */

bool
trees_in::key_mergeable (merge_kind mk, tree decl, tree inner, tree,
			 tree *container, tree *key, tree *fn_args, tree *r_type)
{
  *key = NULL_TREE;
  *fn_args = *r_type = NULL_TREE;

  /* Now read the locating information. */
  if (mk & MK_template_mask)
    {
      *container = tree_node ();
      *key = tree_node ();
    }
  else
    {
      *container = STRIP_TEMPLATE (*container);
      *key = tree_node ();

      if (TREE_CODE (inner) == FUNCTION_DECL)
	{
	  *fn_args = fn_arg_types ();
	  if (decl != inner)
	    *r_type = tree_node ();
	}
    }

  return !get_overrun ();
}

/* DECL is a just streamed mergeable decl that should match EXISTING.  Check
   it does and issue an appropriate diagnostic if not.  Merge any
   bits from DECL to EXISTING.  */

bool
trees_in::is_matching_decl (tree existing, tree decl)
{
  // FIXME: We should probably do some duplicate decl-like stuff here
  // (beware, default parms should be the same?)
  // FIXME: Inhibit TYPENAME_TYPE resolution, all the way down!
  if (!comptypes (TREE_TYPE (existing), TREE_TYPE (decl),
		  COMPARE_STRUCTURAL))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"conflicting global module declaration %#qD", decl);
      inform (DECL_SOURCE_LOCATION (existing),
	      "existing declaration %#qD", existing);
      return false;
    }

  if ((TREE_CODE (decl) == VAR_DECL
       || TREE_CODE (decl) == FUNCTION_DECL)
      && DECL_TEMPLATE_INSTANTIATED (decl))
    /* Don't instantiate again!  */
    DECL_TEMPLATE_INSTANTIATED (existing) = true;

  return true;
}

/* Return non-zero if DECL has a definition that would be interesting to
   write out.  */

static bool
has_definition (tree decl)
{
  decl = STRIP_TEMPLATE (decl);

  switch (TREE_CODE (decl))
    {
    default:
      break;

    case FUNCTION_DECL:
      if (!DECL_SAVED_TREE (decl))
	/* Not defined.  */
	break;

      if (DECL_DECLARED_INLINE_P (decl))
	return true;

      if (DECL_TEMPLATE_INFO (decl))
	{
	  int use_tpl = DECL_USE_TEMPLATE (decl);

	  // FIXME: partial specializations have definitions too.
	  if (use_tpl < 2)
	    return true;
	}
      break;

    case TYPE_DECL:
      {
	tree type = TREE_TYPE (decl);

	if (type == TYPE_MAIN_VARIANT (type)
	    && decl == TYPE_NAME (type)
	    && (TREE_CODE (type) == ENUMERAL_TYPE
		? TYPE_VALUES (type) : TYPE_FIELDS (type)))
	  return true;
      }
      break;

    case VAR_DECL:
      if (!TREE_CONSTANT (decl))
	return false;
      /* Fallthrough.  */

    case CONCEPT_DECL:
      if (DECL_INITIAL (decl))
	return true;

      break;
    }

  return false;
}

uintptr_t *
trees_in::find_duplicate (tree existing)
{
  if (!duplicates)
    return NULL;

  return duplicates->get (STRIP_TEMPLATE (existing));
}

/* We're starting to read duplicate DECL.  EXISTING is the already
   known node.  */

void
trees_in::register_duplicate (tree decl, tree existing)
{
  if (!duplicates)
    duplicates = new duplicate_hash_map (40);

  bool existed;
  uintptr_t &slot =
    duplicates->get_or_insert (STRIP_TEMPLATE (existing), &existed);
  gcc_checking_assert (!existed);
  slot = reinterpret_cast<uintptr_t> (STRIP_TEMPLATE (decl));
}

/* DECL is the controlling mergeable decl of some graph.  Did we find
   an existing decl, or is it a new decl?  */

trees_in::dupness
trees_in::get_dupness (tree maybe_existing)
{
  if (!CHECKING_P && !duplicates)
    return DUP_new;

  if (uintptr_t *slot = find_duplicate (maybe_existing))
    return *slot & 1 ? DUP_bad : DUP_dup;

  return DUP_new;
}

/* DECL is an about-to-be defined decl.  Determine the ODR mergeness.
   HAVE_DEFN indicates whether we already have a definition for it.  */

trees_in::odrness
trees_in::get_odrness (tree decl, bool have_defn)
{
  if (get_overrun ())
    return ODR_ignore;

  /* If there's no deduping going on, we want this one.  */
  if (!duplicates)
    return ODR_new;

  tree owner = get_instantiating_module_decl (decl);
  dupness dup = get_dupness (owner);

  if (dup == DUP_bad)
    return ODR_ignore;

  if (!have_defn)
    if (dup < DUP_dup || STRIP_TEMPLATE (decl) == owner)
      return ODR_new;

  if (dup == DUP_dup)
    // FIXME: it'd be good to be able to locate the thing to check
    // against and allow checking in all cases
    return STRIP_TEMPLATE (decl) == owner ? ODR_check : ODR_ignore;

  gcc_unreachable ();
  return ODR_ignore;
}

/* The following writer functions rely on the current behaviour of
   depset::hash::add_dependency making the decl and defn depset nodes
   depend on eachother.  That way we don't have to worry about seeding
   the tree map with named decls that cannot be looked up by name (I.e
   template and function parms).  We know the decl and definition will
   be in the same cluster, which is what we want.  */

void
trees_out::write_function_def (tree decl)
{
  tree_node (DECL_RESULT (decl));
  tree_node (DECL_INITIAL (decl));
  tree_node (DECL_SAVED_TREE (decl));
  tree_node (DECL_FRIEND_CONTEXT (decl));

  constexpr_fundef *cexpr = retrieve_constexpr_fundef (decl);
  if (streaming_p ())
    u (cexpr != NULL);
  if (cexpr)
    {
      int tag = insert (cexpr->result);
      if (streaming_p ())
	dump (dumper::TREE)
	  && dump ("Constexpr:%d result %N", tag, cexpr->result);
      unsigned ix = 0;
      for (tree parm = cexpr->parms; parm; parm = DECL_CHAIN (parm), ix++)
	{
	  tag = insert (parm);
	  if (streaming_p ())
	    dump (dumper::TREE)
	      && dump ("Constexpr:%d parm:%u %N", tag, ix, parm);
	}
      tree_node (cexpr->body);
    }
}

void
trees_out::mark_function_def (tree)
{
}

bool
trees_in::read_function_def (tree decl, tree maybe_template)
{
  dump () && dump ("Reading function definition %N", decl);
  tree result = tree_node ();
  tree initial = tree_node ();
  tree saved = tree_node ();
  tree context = tree_node ();
  constexpr_fundef cexpr;

  if (u ())
    {
      cexpr.result = copy_decl (result);
      int tag = insert (cexpr.result);
      dump (dumper::TREE)
	  && dump ("Constexpr:%d result %N", tag, cexpr.result);
      cexpr.parms = NULL_TREE;
      tree *chain = &cexpr.parms;
      unsigned ix = 0;
      for (tree parm = DECL_ARGUMENTS (decl);
	   parm; parm = DECL_CHAIN (parm), ix++)
	{
	  tree p = copy_decl (parm);
	  tag = insert (p);
	  dump (dumper::TREE)
	    && dump ("Constexpr:%d parm:%u %N", tag, ix, p);
	  *chain = p;
	  chain = &DECL_CHAIN (p);
	}
      cexpr.body = tree_node ();
      cexpr.decl = decl;
    }
  else
    cexpr.decl = NULL_TREE;

  if (get_overrun ())
    return NULL_TREE;

  odrness odr = get_odrness (maybe_template,
			     DECL_SAVED_TREE (decl) != NULL_TREE);
  assert_definition (maybe_template, odr);

  if (odr == ODR_new)
    {
      DECL_RESULT (decl) = result;
      DECL_INITIAL (decl) = initial;
      DECL_SAVED_TREE (decl) = saved;
      if (context)
	SET_DECL_FRIEND_CONTEXT (decl, context);
      if (cexpr.decl)
	register_constexpr_fundef (cexpr);
      post_process (maybe_template);
    }
  else if (odr == ODR_check)
    {
      // FIXME: Check matching defn
    }
  
  return true;
}

void
trees_out::write_var_def (tree decl)
{
  tree_node (DECL_INITIAL (decl));
}

void
trees_out::mark_var_def (tree)
{
}

bool
trees_in::read_var_def (tree decl, tree maybe_template)
{
  tree init = tree_node ();

  if (get_overrun ())
    return false;

  odrness odr = get_odrness (maybe_template, DECL_INITIAL (decl) != NULL_TREE);
  assert_definition (maybe_template, odr);
  if (odr == ODR_new)
    {
      DECL_INITIAL (decl) = init;
    }
  else if (odr == ODR_check)
    {
      // FIXME: Check matching defn
    }

  return true;
}

/* If MEMBER doesn't have an independent life outside the class,
   return it (or it's TEMPLATE_DECL).  Otherwise NULL.  */

static tree
member_owned_by_class (tree member)
{
  gcc_assert (DECL_P (member));

  /* Clones are owned by their origin.  */
  if (DECL_CLONED_FUNCTION_P (member))
    return NULL;

  int use_tpl = -1;
  if (tree ti = node_template_info (member, use_tpl))
    {
      // FIXME: don't bail on things that CANNOT have their own
      // template header.  No, make sure they're in the same cluster.
      if (use_tpl > 0)
	return NULL_TREE;

      if (DECL_TEMPLATE_RESULT (TI_TEMPLATE (ti)) == member)
	member = TI_TEMPLATE (ti);
    }
  return member;
}

// FIXME: Handle DECL_ACCESS of members.  They will have USING_DECLS
// on the TYPE_FIELDS chain, from whence we can find the right
// DECL_ACCESS.  Also the used decls will be in the member_vector.
// Stream out and reconstruct on readin.

void
trees_out::write_class_def (tree defn)
{
  gcc_assert (DECL_P (defn));
  if (streaming_p ())
    dump () && dump ("Writing class definition %N", defn);

  tree type = TREE_TYPE (defn);
  tree_node (TYPE_SIZE (type));
  tree_node (TYPE_SIZE_UNIT (type));
  tree_node (TYPE_VFIELD (type));
  tree_node (TYPE_BINFO (type));

  /* Write the fields.  */
  for (tree field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    tree_node (field);
  tree_node (NULL_TREE);

  if (TYPE_LANG_SPECIFIC (type))
    {
      tree_vec (CLASSTYPE_MEMBER_VEC (type));
      tree_node (CLASSTYPE_LAMBDA_EXPR (type));

      /* TYPE_CONTAINS_VPTR_P looks at the vbase vector, which the
	 reader won't know at this point.  */
      int has_vptr = TYPE_CONTAINS_VPTR_P (type);

      if (streaming_p ())
	{
	  unsigned nvbases = vec_safe_length (CLASSTYPE_VBASECLASSES (type));
	  u (nvbases);
	  i (has_vptr);
	}

      if (has_vptr)
	{
	  tree_vec (CLASSTYPE_PURE_VIRTUALS (type));
	  tree_pair_vec (CLASSTYPE_VCALL_INDICES (type));
	  tree_node (CLASSTYPE_KEY_METHOD (type));
	}
    }

  if (TYPE_LANG_SPECIFIC (type))
    {
      tree_node (CLASSTYPE_PRIMARY_BINFO (type));

      tree as_base = CLASSTYPE_AS_BASE (type);
      if (as_base)
	as_base = TYPE_NAME (as_base);
      tree_node (as_base);
      if (as_base && as_base != defn)
	write_class_def (as_base);

      tree vtables = CLASSTYPE_VTABLES (type);
      chained_decls (vtables);
      /* Write the vtable initializers.  */
      for (; vtables; vtables = TREE_CHAIN (vtables))
	write_definition (vtables);

      /* Write the friend classes.  */
      for (tree friends = CLASSTYPE_FRIEND_CLASSES (type);
	   friends; friends = TREE_CHAIN (friends))
	/* TREE_VALUE is what we want.  */
	tree_node (TREE_VALUE (friends));
      /* End of friends.  */
      tree_node (NULL_TREE);

      /* Write the friend functions.  */
      for (tree friends = DECL_FRIENDLIST (defn);
	   friends; friends = TREE_CHAIN (friends))
	{
	  /* Name of these friends.  */
	  tree_node (TREE_PURPOSE (friends));
	  for (tree decls = TREE_VALUE (friends);
	       decls; decls = TREE_CHAIN (decls))
	    tree_node (TREE_VALUE (decls));
	  /* End of these friends called this.  */
	  tree_node (NULL_TREE);
	}
      /* End of friends.  */
      tree_node (NULL_TREE);

      /* Write the decl list.  */
      for (tree decls = CLASSTYPE_DECL_LIST (type); decls;
	   decls = TREE_CHAIN (decls))
	{
	  tree decl = TREE_VALUE (decls);
	  tree_node (decl);
	  tree_node (TREE_PURPOSE (decls));
	  if (!TREE_PURPOSE (decls))
	    if (tree frnd = friend_from_decl_list (decl))
	      if (TREE_CODE (frnd) == TEMPLATE_DECL
		  && DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (frnd))
		{
		  gcc_checking_assert (DECL_CHAIN (frnd) == type);

		  bool has_def = has_definition (frnd);

		  if (streaming_p ())
		    u (has_def);

		  if (has_def)
		    write_definition (frnd);
		}
	}
      /* End of decls.  */
      tree_node (NULL_TREE);

      if (TYPE_CONTAINS_VPTR_P (type))
	{
	  /* Write the thunks.  */
	  for (tree decls = TYPE_FIELDS (type);
	       decls; decls = DECL_CHAIN (decls))
	    if (TREE_CODE (decls) == FUNCTION_DECL
		&& DECL_VIRTUAL_P (decls))
	      {
		tree_node (decls);
		// FIXME: perhaps not chained here?
		chained_decls (DECL_THUNKS (decls));
	      }
	  tree_node (NULL_TREE);
	}
    }

  // FIXME: lang->nested_udts

  /* Now define all the members that do not have independent definitions.  */
  for (tree member = TYPE_FIELDS (type); member; member = TREE_CHAIN (member))
    if (has_definition (member))
      if (tree mine = member_owned_by_class (member))
	{
	  tree_node (mine);
	  write_definition (mine);
	}

  /* End of definitions.  */
  tree_node (NULL_TREE);
}

void
trees_out::mark_class_member (tree member, bool do_defn)
{
  gcc_assert (DECL_P (member));

  member = member_owned_by_class (member);
  if (member)
    mark_declaration (member, do_defn && has_definition (member));
}

void
trees_out::mark_class_def (tree defn)
{
  gcc_assert (DECL_P (defn));
  tree type = TREE_TYPE (defn);
  for (tree member = TYPE_FIELDS (type); member; member = DECL_CHAIN (member))
    /* Do not mark enum consts here.  */
    if (TREE_CODE (member) != CONST_DECL)
      {
	mark_class_member (member);
	if (TREE_CODE (member) == FIELD_DECL)
	  if (tree repr = DECL_BIT_FIELD_REPRESENTATIVE (member))
	    mark_declaration (repr, false);
      }

  /* Mark the binfo heirarchy.  */
  for (tree child = TYPE_BINFO (type); child; child = TREE_CHAIN (child))
    mark_by_value (child);

  if (TYPE_LANG_SPECIFIC (type))
    {
      if (tree as_base = CLASSTYPE_AS_BASE (type))
	if (as_base != type)
	  mark_declaration (TYPE_NAME (as_base), true);

      for (tree vtable = CLASSTYPE_VTABLES (type);
	   vtable; vtable = TREE_CHAIN (vtable))
	mark_declaration (vtable, true);

      if (TYPE_CONTAINS_VPTR_P (type))
	/* Mark the thunks, they belong to the class definition,
	   /not/ the thunked-to function.  */
	for (tree decls = TYPE_FIELDS (type);
	     decls; decls = DECL_CHAIN (decls))
	  if (TREE_CODE (decls) == FUNCTION_DECL)
	    for (tree thunks = DECL_THUNKS (decls);
		 thunks; thunks = DECL_CHAIN (thunks))
	      mark_declaration (thunks, false);

      for (tree decls = CLASSTYPE_DECL_LIST (type);
	   decls; decls = TREE_CHAIN (decls))
	{
	  tree decl = TREE_VALUE (decls);

	  if (TREE_PURPOSE (decls))
	    {
	      /* There may be decls here, that are not on the member vector.
		 for instance forward declarations of member tagged types.  */
	      if (TYPE_P (decl))
		/* In spite of its name, non-decls appear :(.  */
		decl = TYPE_NAME (decl);

	      /* Static asserts are on this chain too.  */
	      if (DECL_P (decl))
		{
		  gcc_assert (DECL_CONTEXT (decl) == type);
		  mark_class_member (decl, false);
		}
	    }
	  else if (tree frnd = friend_from_decl_list (decl))
	    {
	      if (TREE_CODE (frnd) == TEMPLATE_DECL
		   && DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (frnd))
		/* A templated friend declaration that we own.  */
		mark_declaration (frnd, has_definition (frnd));
	      else if (DECL_LANG_SPECIFIC (frnd)
		       && DECL_TEMPLATE_INFO (frnd)
		       && TREE_CODE (DECL_TI_TEMPLATE (frnd)) != TEMPLATE_DECL)
		/* A friend declared with a template-id.  */
		mark_declaration (frnd, false);
	    }
	}
    }
}

/* Nop sorting, needed for resorting the member vec.  */

static void
nop (void *, void *)
{
}

bool
trees_in::read_class_def (tree defn, tree maybe_template)
{
  gcc_assert (DECL_P (defn));
  dump () && dump ("Reading class definition %N", defn);
  tree type = TREE_TYPE (defn);
  tree size = tree_node ();
  tree size_unit = tree_node ();
  tree vfield = tree_node ();
  tree binfo = tree_node ();
  vec<tree, va_gc> *vbase_vec = NULL;
  vec<tree, va_gc> *member_vec = NULL;
  vec<tree, va_gc> *pure_virts = NULL;
  vec<tree_pair_s, va_gc> *vcall_indices = NULL;
  tree key_method = NULL_TREE;
  tree lambda = NULL_TREE;

  /* Read the fields.  */
  vec<tree> fields;
  fields.create (50);
  while (tree field = tree_node ())
    fields.safe_push (field);

  if (TYPE_LANG_SPECIFIC (type))
    {
      member_vec = tree_vec ();
      lambda = tree_node ();

      if (!get_overrun ())
	{
	  unsigned nvbases = u ();
	  if (nvbases)
	    {
	      vec_alloc (vbase_vec, nvbases);
	      for (tree child = binfo; child; child = TREE_CHAIN (child))
		if (BINFO_VIRTUAL_P (child))
		  vbase_vec->quick_push (child);
	    }
	}

      if (!get_overrun ())
	{
	  int has_vptr = i ();
	  if (has_vptr)
	    {
	      pure_virts = tree_vec ();
	      vcall_indices = tree_pair_vec ();
	      key_method = tree_node ();
	    }
	}
    }

  // FIXME: Read more stuff!
  // lang->nested_udts

  odrness odr = get_odrness (maybe_template, TYPE_SIZE (type) != NULL_TREE);
  assert_definition (maybe_template, odr);
  if (odr == ODR_new)
    {
      TYPE_SIZE (type) = size;
      TYPE_SIZE_UNIT (type) = size_unit;

      tree *chain = &TYPE_FIELDS (type);
      for (unsigned ix = 0; ix != fields.length (); ix++)
	{
	  tree field = fields[ix];

	  gcc_checking_assert (DECL_CHAIN (field)
			       == (ix + 1 < fields.length ()
				   && DECL_CLONED_FUNCTION_P (fields[ix+1])
				   ? fields[ix+1] : NULL_TREE));
	  *chain = field;
	  chain = &DECL_CHAIN (field);
	}

      TYPE_VFIELD (type) = vfield;
      TYPE_BINFO (type) = binfo;

      // FIXME: Do I need to rewire DECL_CHAIN on template clones?
      if (TYPE_LANG_SPECIFIC (type))
	{
	  CLASSTYPE_LAMBDA_EXPR (type) = lambda;

	  CLASSTYPE_MEMBER_VEC (type) = member_vec;
	  CLASSTYPE_PURE_VIRTUALS (type) = pure_virts;
	  CLASSTYPE_VCALL_INDICES (type) = vcall_indices;

	  CLASSTYPE_KEY_METHOD (type) = key_method;

	  CLASSTYPE_VBASECLASSES (type) = vbase_vec;

	  /* Resort the member vector.  */
	  resort_type_member_vec (member_vec, NULL, nop, NULL);
	}
    }
  else if (odr == ODR_check)
    {
      // FIXME: Check matching defn
    }

  if (TYPE_LANG_SPECIFIC (type))
    {
      tree primary = tree_node ();
      tree as_base = tree_node ();

      if (as_base)
	{
	  if (as_base != defn)
	    read_class_def (as_base, as_base);
	  as_base = TREE_TYPE (as_base);
	}

      /* Read the vtables.  */
      tree vtables = chained_decls ();
      for (tree vt = vtables; vt; vt = TREE_CHAIN (vt))
	read_var_def (vt, vt);

      // FIXME: We should be able to reverse the lists in the writer
      tree friend_classes = NULL_TREE;
      while (tree val = tree_node ())
	friend_classes = tree_cons (NULL_TREE, val, friend_classes);
      friend_classes = nreverse (friend_classes);

      tree friend_functions = NULL_TREE;
      while (tree name = tree_node ())
	{
	  tree val = NULL_TREE;
	  while (tree decl = tree_node ())
	    val = tree_cons (NULL_TREE, decl, val);
	  nreverse (val);
	  friend_functions = tree_cons (name, val, friend_functions);
	}
      friend_functions = nreverse (friend_functions);

      tree decl_list = NULL_TREE;
      while (tree decl = tree_node ())
	{
	  tree purpose = tree_node ();
	  decl_list = tree_cons (purpose, decl, decl_list);

	  if (!purpose)
	    if (tree frnd = friend_from_decl_list (decl))
	      if (TREE_CODE (frnd) == TEMPLATE_DECL
		  && DECL_UNINSTANTIATED_TEMPLATE_FRIEND_P (frnd))
		if (u () != 0)
		  if (!read_definition (frnd))
		    break;

	}
      decl_list = nreverse (decl_list);

      if (odr == ODR_new)
	{
	  CLASSTYPE_PRIMARY_BINFO (type) = primary;
	  CLASSTYPE_AS_BASE (type) = as_base;
	  if (!CLASSTYPE_KEY_METHOD (type) && vtables)
	    vec_safe_push (keyed_classes, type);
	  CLASSTYPE_VTABLES (type) = vtables;
	  CLASSTYPE_FRIEND_CLASSES (type) = friend_classes;
	  DECL_FRIENDLIST (defn) = friend_functions;
	  CLASSTYPE_DECL_LIST (type) = decl_list;

	  for (; friend_classes; friend_classes = TREE_CHAIN (friend_classes))
	    {
	      tree f = TREE_VALUE (friend_classes);

	      if (TYPE_P (f))
		{
		  CLASSTYPE_BEFRIENDING_CLASSES (f)
		    = tree_cons (NULL_TREE, type,
				 CLASSTYPE_BEFRIENDING_CLASSES (f));
		  dump () && dump ("Class %N befriending %C:%N",
				   type, TREE_CODE (f), f);
		}
	    }

	  for (; friend_functions;
	       friend_functions = TREE_CHAIN (friend_functions))
	    for (tree friend_decls = TREE_VALUE (friend_functions);
		 friend_decls; friend_decls = TREE_CHAIN (friend_decls))
	      {
		tree f = TREE_VALUE (friend_decls);
		
		DECL_BEFRIENDING_CLASSES (f)
		  = tree_cons (NULL_TREE, type, DECL_BEFRIENDING_CLASSES (f));
		dump () && dump ("Class %N befriending %C:%N",
				 type, TREE_CODE (f), f);
	      }
	}

      if (TYPE_CONTAINS_VPTR_P (type))
	/* Read and install the thunks.  */
	while (tree vfunc = tree_node ())
	  {
	    tree thunks = chained_decls ();
	    if (odr == ODR_new)
	      SET_DECL_THUNKS (vfunc, thunks);
	  }
    }

  /* Propagate to all variants.  */
  if (odr == ODR_new)
    fixup_type_variants (type);

  /* IS_FAKE_BASE_TYPE is inaccurate at this point, because if this is
     the fake base, we've not hooked it into the containing class's
     data structure yet.  Fortunately it has a unique name.  */
  if (DECL_NAME (defn) != as_base_identifier
      && (!CLASSTYPE_TEMPLATE_INFO (type)
	  || !uses_template_parms (TI_ARGS (CLASSTYPE_TEMPLATE_INFO (type)))))
    /* Emit debug info.  It'd be nice to know if the interface TU
       already emitted this.  */
    rest_of_type_compilation (type, !LOCAL_CLASS_P (type));

  /* Now define all the members.  */
  while (tree member = tree_node ())
    if (!read_definition (member))
      break;

  fields.release ();

  return !get_overrun ();
}

void
trees_out::write_enum_def (tree decl)
{
  tree type = TREE_TYPE (decl);

  tree_node (TYPE_VALUES (type));
  tree_node (TYPE_MIN_VALUE (type));
  tree_node (TYPE_MAX_VALUE (type));
}

void
trees_out::mark_enum_def (tree decl)
{
  tree type = TREE_TYPE (decl);

  for (tree values = TYPE_VALUES (type); values; values = TREE_CHAIN (values))
    {
      tree cst = TREE_VALUE (values);
      mark_by_value (cst);
      /* We must mark the init to avoid circularity in tt_enum_int.  */
      if (tree init = DECL_INITIAL (cst))
	if (TREE_CODE (init) == INTEGER_CST)
	  mark_by_value (init);
    }
}

bool
trees_in::read_enum_def (tree defn, tree maybe_template)
{
  tree type = TREE_TYPE (defn);
  tree values = tree_node ();
  tree min = tree_node ();
  tree max = tree_node ();

  if (get_overrun ())
    return false;

  // FIXME: ODR ?
  odrness odr = get_odrness (defn, TYPE_VALUES (type) != NULL_TREE);
  assert_definition (maybe_template, odr);

  if (odr == ODR_new)
    {
      TYPE_VALUES (type) = values;
      TYPE_MIN_VALUE (type) = min;
      TYPE_MAX_VALUE (type) = max;

      rest_of_type_compilation (type, DECL_NAMESPACE_SCOPE_P (defn));
    }
  else if (odr == ODR_check)
    {
      // FIXME: check odr
    }

  return true;
}

/* Write out the body of DECL.  See above circularity note.  */

void
trees_out::write_definition (tree decl)
{
  if (streaming_p ())
    {
      assert_definition (decl);
      dump ()
	&& dump ("Writing definition %C:%N", TREE_CODE (decl), decl);
    }
  else
    dump (dumper::DEPEND)
      && dump ("Depending definition %C:%N", TREE_CODE (decl), decl);

 again:
  switch (TREE_CODE (decl))
    {
    default:
      gcc_unreachable ();

    case TEMPLATE_DECL:
      decl = DECL_TEMPLATE_RESULT (decl);
      goto again;

    case FUNCTION_DECL:
      write_function_def (decl);
      break;

    case TYPE_DECL:
      {
	tree type = TREE_TYPE (decl);
	gcc_assert (TYPE_MAIN_VARIANT (type) == type
		    && TYPE_NAME (type) == decl);
	if (TREE_CODE (type) == ENUMERAL_TYPE)
	  write_enum_def (decl);
	else
	  write_class_def (decl);
      }
      break;

    case VAR_DECL:
    case CONCEPT_DECL:
      write_var_def (decl);
      break;
    }
}

/* Mark a declaration for by-value walking.  If DO_DEFN is true, mark
   its body too.  */

void
trees_out::mark_declaration (tree decl, bool do_defn)
{
  mark_by_value (decl);

  if (TREE_CODE (decl) == TEMPLATE_DECL)
    decl = DECL_TEMPLATE_RESULT (decl);

  if (!do_defn)
    return;

  switch (TREE_CODE (decl))
    {
    default:
      gcc_unreachable ();

    case FUNCTION_DECL:
      mark_function_def (decl);
      break;

    case TYPE_DECL:
      {
	tree type = TREE_TYPE (decl);
	gcc_assert (TYPE_MAIN_VARIANT (type) == type
		    && TYPE_NAME (type) == decl);
	if (TREE_CODE (type) == ENUMERAL_TYPE)
	  mark_enum_def (decl);
	else
	  mark_class_def (decl);
      }
      break;

    case VAR_DECL:
    case CONCEPT_DECL:
      mark_var_def (decl);
      break;
    }
}

/* Read in the body of DECL.  See above circularity note.  */

bool
trees_in::read_definition (tree decl)
{
  dump () && dump ("Reading definition %C %N", TREE_CODE (decl), decl);

  tree maybe_template = decl;

 again:
  switch (TREE_CODE (decl))
    {
    default:
      break;

    case TEMPLATE_DECL:
      decl = DECL_TEMPLATE_RESULT (decl);
      goto again;

    case FUNCTION_DECL:
      return read_function_def (decl, maybe_template);

    case TYPE_DECL:
      {
	tree type = TREE_TYPE (decl);
	gcc_assert (TYPE_MAIN_VARIANT (type) == type
		    && TYPE_NAME (type) == decl);
	if (TREE_CODE (type) == ENUMERAL_TYPE)
	  return read_enum_def (decl, maybe_template);
	else
	  return read_class_def (decl, maybe_template);
      }
      break;

    case VAR_DECL:
    case CONCEPT_DECL:
      return read_var_def (decl, maybe_template);
    }

  return false;
}

/* Lookup an maybe insert a slot for depset for KEY.  */

depset **
depset::hash::entity_slot (tree entity, bool insert)
{
  traits::compare_type key (entity, NULL);
  depset **slot = find_slot_with_hash (key, traits::hash (key),
				       insert ? INSERT : NO_INSERT);

  return slot;
}

depset **
depset::hash::binding_slot (tree ctx, tree name, bool insert)
{
  traits::compare_type key (ctx, name);
  depset **slot = find_slot_with_hash (key, traits::hash (key),
				       insert ? INSERT : NO_INSERT);

  return slot;
}

depset *
depset::hash::find_entity (tree entity)
{
  depset **slot = entity_slot (entity, false);

  return slot ? *slot : NULL;
}

depset *
depset::hash::find_binding (tree ctx, tree name)
{
  depset **slot = binding_slot (ctx, name, false);

  return slot ? *slot : NULL;
}

/* DECL is a newly discovered dependency of current.  Create the
   depset, if it doesn't already exist.  Add it to the worklist if so.
   Append it to current's depset.

   DECL will be an OVL_USING_P OVERLOAD, if it's from a binding that's
   a using decl.

   We do not have to worry about adding the same dependency more than
   once.  First it's harmless, but secondly the TREE_VISITED marking
   prevents us wanting to do it anyway.  */

depset *
depset::hash::add_dependency (tree decl, entity_kind ek)
{
  /* Make sure we're being told consistent information.  */
  gcc_checking_assert ((ek == EK_NAMESPACE)
		       == (TREE_CODE (decl) == NAMESPACE_DECL
			   && !DECL_NAMESPACE_ALIAS (decl)));
  gcc_checking_assert (ek != EK_BINDING && ek != EK_REDIRECT);
  if (ek == EK_USING)
    gcc_checking_assert (current->is_binding () && TREE_CODE (decl) == OVERLOAD);

  if (ek == EK_UNNAMED)
    /* Unnameable things are not namespace scope  */
    gcc_checking_assert (TREE_CODE (CP_DECL_CONTEXT (decl)) != NAMESPACE_DECL);

  if (TREE_CODE (decl) == TEMPLATE_DECL)
    {
      /* The template should have copied these from its result decl.  */
      tree res = DECL_TEMPLATE_RESULT (decl);

      gcc_checking_assert (DECL_MODULE_EXPORT_P (decl)
			   == DECL_MODULE_EXPORT_P (res));
      if (DECL_LANG_SPECIFIC (res))
	{
	  gcc_checking_assert (DECL_MODULE_PURVIEW_P (decl)
			       == DECL_MODULE_PURVIEW_P (res));
	  // FIXME: in template fns, vars are themselves templates.  But
	  // are local instantiations, I don't think they can end up in
	  // the instantiation table, and so we shouldn't depend on them
	  // here.  See the comment in trees_out::decl_node about having
	  // to look to see if we can find it there.
	  gcc_checking_assert ((DECL_MODULE_ORIGIN (decl)
				== DECL_MODULE_ORIGIN (res)));
	}
    }

  if (ek != EK_USING)
    /* We should only be given instantiating decls, except for
       voldemorts, where we should only get non-instantiating decls.  */
    gcc_checking_assert ((STRIP_TEMPLATE (decl)
			  == get_instantiating_module_decl (decl))
			 == (ek != EK_UNNAMED));

  depset **slot = entity_slot (decl, true);
  depset *dep = *slot;
  bool binding_p = current && current->is_binding ();

  if (!dep)
    {
      bool has_def = ek != EK_USING && has_definition (decl);
      bool maybe_spec = ek == EK_MAYBE_SPEC;
      if (maybe_spec)
	{
	  /* We were probing, and didn't find anything.  Therefore
	     this is a regular-ish decl, but mark it as a pseudo
	     spec so we know to write a definition.  */
	  ek = EK_DECL;
	  dump (dumper::DEPEND)
	    && dump ("Pseudo specialization %N discovered", decl);
	}

      /* The only OVERLOADS we should see are USING decls from
	 bindings.  */
      *slot = dep = make_entity (decl, ek, has_def);

      if (TREE_CODE (decl) == TEMPLATE_DECL)
	/* If we add a template, its result better not also be
	   present.  */
	gcc_checking_assert
	  (!entity_slot (DECL_TEMPLATE_RESULT (decl), false));

      if (ek != EK_USING)
	if (unsigned origin
	    = DECL_LANG_SPECIFIC (decl) ? DECL_MODULE_ORIGIN (decl) : 0)
	  if ((*modules)[origin]->remap)
	    {
	      dep->set_flag_bit<DB_IMPORTED_BIT> ();
	      gcc_checking_assert (ek ==EK_UNNAMED || ek == EK_SPECIALIZATION
				   || maybe_spec);
	    }

      if (binding_p)
	/* Dependency of a namespace binding.  */;
      else if (ek == EK_NAMESPACE)
	/* Dependency is a namespace.  */;
      else if (maybe_spec)
	/* Remember this has some specialization properties.  */
	dep->set_flag_bit<DB_PSEUDO_SPEC_BIT> ();
      else if (ek == EK_UNNAMED
	       || ek == EK_SPECIALIZATION)
	/* Dependency is unnameable.  We do not have to apply the
	   below checks to this entity, because we can only refer to
	   it by depending on its containing entity, and that entity
	   will have the below checks applied to it.  */;
      else
	{
	  tree ctx = CP_DECL_CONTEXT (decl);
	  gcc_checking_assert (TREE_CODE (ctx) == NAMESPACE_DECL);
	  tree not_tmpl = STRIP_TEMPLATE (decl);

	  if (!TREE_PUBLIC (ctx))
	    /* Member of internal namespace.  */
	    dep->set_flag_bit<DB_IS_INTERNAL_BIT> ();
	  else if (TREE_CODE (not_tmpl) != TYPE_DECL
		   && TREE_CODE (not_tmpl) != CONST_DECL
		   && DECL_THIS_STATIC (not_tmpl))
	    {
	      /* An internal decl.  In global module permit
		 extern "C" static inline functions
		 ... because.  */
	      if (!(header_module_p ()
		    || (TREE_CODE (not_tmpl) == FUNCTION_DECL
			&& DECL_DECLARED_INLINE_P (not_tmpl)
#if 0
			// FIXME: Disregard language linkage, because our
			// std lib is borked.  Templates cannot
			// have "C" linkage!
			&& DECL_EXTERN_C_P (not_tmpl)
#endif
			&& true)))
		dep->set_flag_bit<DB_IS_INTERNAL_BIT> ();
	    }
	  else if (DECL_IMPLICIT_TYPEDEF_P (decl)
		   && IDENTIFIER_ANON_P (DECL_NAME (decl)))
	    /* No linkage or linkage from typedef name (which
	       cannot be internal, because that's from the linkage
	       of the context.  */;
	  else
	    {
	      // FIXME: We have to walk the non-emitted entities
	      // in the module's purview too.  Discussing this in
	      // CWG, it is weird.
	      /* A reachable global module fragment entity.  Add
		 it to its scope's binding depset.  */
	      depset **bslot = binding_slot (ctx, DECL_NAME (decl), true);
	      depset *bdep = *bslot;
	      if (!bdep)
		*bslot = bdep = make_binding (ctx, DECL_NAME (decl));
	      bdep->deps.safe_push (dep);
	      dep->deps.safe_push (bdep);
	      dep->set_flag_bit<DB_GLOBAL_BIT> ();
	      dump (dumper::DEPEND)
		&& dump ("Reachable GMF %N added", decl);
	    }
	}

      if (ek == EK_SPECIALIZATION
	  || (ek == EK_DECL
	      && TREE_PUBLIC (CP_DECL_CONTEXT (decl))))
	/* Decl that could be declared in multiple CMIs (even
	   module-owned declarations could be defined in a
	   partition.  */
	dep->set_flag_bit<DB_MERGEABLE_BIT> ();

      if (!dep->is_import ())
	worklist.safe_push (dep);
    }
  else if (ek == EK_MAYBE_SPEC)
    /* It's whatever we already found.  */
    ek = dep->get_entity_kind ();
  else if (ek == EK_DECL && dep->get_entity_kind () == EK_SPECIALIZATION)
    /* decl is a friend of a template instantiation.  These
       have some of the properties of regular decls.  */
    dump (dumper::DEPEND) && dump ("Template friend %N discovered", decl);
  else
    /* Make sure we have consistent categorization.  */
    gcc_checking_assert (dep->get_entity_kind () == ek);

  if (ek == EK_REDIRECT)
    {
      dump (dumper::DEPEND)
	&& dump ("Redirect for %C:%N found", TREE_CODE (decl), decl);
      return dep;
    }

  dump (dumper::DEPEND)
    && dump ("%s on %s %C:%N added", binding_p ? "Binding" : "Dependency",
	     dep->entity_kind_name (), TREE_CODE (decl), decl);

  if (current && ek != EK_NAMESPACE)
    {
      current->deps.safe_push (dep);
      if (current->is_binding ())
	/* Binding and contents are mutually dependent.  */
	dep->deps.safe_push (current);
      else
	{
	  if (dep->is_internal ())
	    current->set_flag_bit<DB_REFS_INTERNAL_BIT> ();

	  if (current->get_entity_kind () == EK_USING
	      && !OVL_USING_P (current->get_entity ())
	      && DECL_IMPLICIT_TYPEDEF_P (decl)
	      && TREE_CODE (TREE_TYPE (decl)) == ENUMERAL_TYPE)
	    {
	      /* CURRENT is an unwrapped using-decl and DECL is an
		 enum's implicit typedef.  Is CURRENT a member of
		 the enum?  */
	      tree c_decl = OVL_FUNCTION (current->get_entity ());

	      if (TREE_CODE (c_decl) == CONST_DECL
		  && DECL_CONTEXT (c_decl) == TREE_TYPE (decl))
		/* Make DECL depend on CURRENT.  */
		dep->deps.safe_push (current);
	    }
	}

      if (dep->is_unreached ())
	{
	  /* The dependency is reachable now.  */
	  reached_unreached = true;
	  dep->clear_flag_bit<DB_UNREACHED_BIT> ();
	  dump (dumper::DEPEND)
	    && dump ("Reaching unreached %s %C:%N", dep->entity_kind_name (),
		     TREE_CODE (dep->get_entity ()), dep->get_entity ());
	}
    }

  return dep;
}

/* VALUE is an overload of decls that is bound in this module.  Create
   the relevant depsets for the binding and its contents.  MAYBE_TYPE
   is used for struct stat hack behaviour.  */

bool
depset::hash::add_binding (tree ns, tree value)
{
  current = make_binding (ns, NULL_TREE);

  tree name = NULL_TREE;
  gcc_checking_assert (TREE_PUBLIC (ns));
  for (ovl_iterator iter (value); iter; ++iter)
    {
      tree decl = *iter;
      name = DECL_NAME (decl);

      gcc_checking_assert (!IDENTIFIER_ANON_P (name));
      gcc_checking_assert (!(TREE_CODE (decl) == NAMESPACE_DECL
			     && !DECL_NAMESPACE_ALIAS (decl)));
      // FIXME:Distinguish GMF usings from purview usings.

      tree inner = decl;

      if (TREE_CODE (inner) == CONST_DECL
	  && TREE_CODE (DECL_CONTEXT (inner)) == ENUMERAL_TYPE)
	inner = TYPE_NAME (DECL_CONTEXT (inner));
      else if (TREE_CODE (inner) == TEMPLATE_DECL)
	inner = DECL_TEMPLATE_RESULT (inner);

      if (!DECL_LANG_SPECIFIC (inner) || !DECL_MODULE_PURVIEW_P (inner))
	/* Ignore global module fragment entities.  */
	continue;

      if ((TREE_CODE (inner) == VAR_DECL
	   || TREE_CODE (inner) == FUNCTION_DECL)
	  && DECL_THIS_STATIC (inner))
	{
	  if (!header_module_p ())
	    /* Ignore internal-linkage entitites.  */
	    continue;
	  // FIXME: Promote here?  Or should we have done that already?
	}

      if ((TREE_CODE (decl) == VAR_DECL
	   || TREE_CODE (decl) == TYPE_DECL)
	  && DECL_TINFO_P (decl))
	/* Ignore TINFO things.  */
	continue;

      bool using_p = iter.using_p ();
      depset::entity_kind ek = depset::EK_DECL;
      tree maybe_using = decl;
      if (using_p)
	{
	  maybe_using = iter.get_using ();
	  ek = depset::EK_USING;
	}
      else if (CP_DECL_CONTEXT (decl) != ns)
	{
	  /* A using that lost its wrapper or an unscoped enum
	     constant.  */
	  // FIXME: name-lookup should preserve this, but we tend to
	  // drop it for non-function decls :(
	  maybe_using = ovl_make (decl, NULL_TREE);
	  if (DECL_MODULE_EXPORT_P (TREE_CODE (decl) == CONST_DECL
				    ? TYPE_NAME (TREE_TYPE (decl))
				    : STRIP_TEMPLATE (decl)))
	    OVL_EXPORT_P (maybe_using) = true;
	  ek = depset::EK_USING;
	}

      depset *dep = add_dependency (maybe_using, ek);
      if (iter.hidden_p ())
	{
	  /* It is safe to mark the target decl with the hidden bit,
	     because we cannot have other bindings to this decl in
	     this TU.  The same is not true for export_p. */
	  // FIXME: check whether a partition can make the entity
	  // unhidden, perhaps the right things already happen?
	  dep->set_hidden_binding ();
	}
    }

  bool added = current->deps.length () != 0;
  if (added)
    {
      current->set_binding_name (name);
      depset **slot = binding_slot (ns, name, true);
      gcc_checking_assert (!*slot);
      *slot = current;
    }
  else
    delete current;
  current = NULL;

  return added;
}

/* Compare two writable bindings.  We don't particularly care on the
   ordering, just so long as it reproduces across builds.  */

static int
writable_cmp (const void *a_, const void *b_)
{
  tree a = *(const tree *)a_;
  tree b = *(const tree *)b_;

  tree first_a = OVL_FIRST (a);
  tree first_b = OVL_FIRST (b);

  gcc_checking_assert (first_a != first_b);
  return DECL_UID (first_a) < DECL_UID (first_b) ? -1 : +1;
}

/* Recursively find all the namespace bindings of NS.
   Add a depset for every binding that contains an export or
   module-linkage entity.  Add a defining depset for every such decl
   that we need to write a definition.  Such defining depsets depend
   on the binding depset.  Returns true if we contain something
   explicitly exported.  */

bool
depset::hash::add_namespace_entities (tree ns, bitmap partitions)
{
  dump () && dump ("Looking for writables in %N", ns);
  dump.indent ();

  unsigned count = 0;
  vec<tree> bindings;
  bindings.create (DECL_NAMESPACE_BINDINGS (ns)->size ());

  hash_table<named_decl_hash>::iterator end
    (DECL_NAMESPACE_BINDINGS (ns)->end ());
  for (hash_table<named_decl_hash>::iterator iter
	 (DECL_NAMESPACE_BINDINGS (ns)->begin ()); iter != end; ++iter)
    if (tree value = extract_module_binding (*iter, ns, partitions))
      bindings.quick_push (value);

  /* Sort for reproducibility.  */
  bindings.qsort (writable_cmp);
  while (bindings.length ())
    {
      tree value = bindings.pop ();
      if (TREE_CODE (value) != NAMESPACE_DECL)
	{
	  if (add_binding (ns, value))
	    count++;
	}
      else if (DECL_NAMESPACE_ALIAS (value))
	// FIXME: Not sure what to do with namespace aliases
	gcc_unreachable ();
      else if (DECL_NAME (value))
	{
	  gcc_checking_assert (TREE_PUBLIC (value));
	  bool not_empty = add_namespace_entities (value, partitions);
	  if (not_empty || DECL_MODULE_EXPORT_P (value))
	    {
	      add_dependency (value, depset::EK_NAMESPACE);
	      count++;
	    }
	}
    }

  bindings.release ();

  if (count)
    dump () && dump ("Found %u entries", count);
  dump.outdent ();

  return count != 0;
}

/* Add the members of imported classes that we defined in this TU.
   This will also include lazily created implicit member function
   declarations.  (All others will be definitions.)  */

void
depset::hash::add_class_entities (vec<tree, va_gc> *class_members)
{
  while (class_members->length ())
    {
      tree defn = class_members->pop ();
      (void)defn; // FIXME: do something
    }
}

/* We add the partial & explicit specializations, and the explicit
   instantiations.  */

static void
specialization_add (bool decl_p, spec_entry *entry, void *data_)
{
  vec<spec_entry *> *data = reinterpret_cast <vec<spec_entry *> *> (data_);

  if (!decl_p)
    {
      /* We exclusively use decls to locate things.  Make sure there's
	 no mismatch between the two specialization tables we keep.
	 pt.c optimizes instantiation lookup using a complicated
	 heuristic.  We don't attempt to replicate that algorithm, but
	 observe its behaviour and reproduce it upon read back.  */

       gcc_checking_assert (DECL_ALIAS_TEMPLATE_P (entry->tmpl)
			   || TREE_CODE (entry->spec) == ENUMERAL_TYPE
			   || DECL_CLASS_TEMPLATE_P (entry->tmpl));

       /* Only alias templates can appear in both tables (and
	  if they're in the type table they must also be in the decl table).  */
       gcc_checking_assert (!check_mergeable_specialization (true, entry)
			    == (decl_p || !DECL_ALIAS_TEMPLATE_P (entry->tmpl)));
    }

  data->safe_push (entry);
}

/* Arbitrary stable comparison.  */

static int
specialization_cmp (const void *a_, const void *b_)
{
  const spec_entry *ea = *reinterpret_cast<const spec_entry *const *> (a_);
  const spec_entry *eb = *reinterpret_cast<const spec_entry *const *> (b_);

  if (ea == eb)
    return 0;

  tree a = ea->spec;
  tree b = eb->spec;
  if (TYPE_P (a))
    {
      a = TYPE_NAME (a);
      b = TYPE_NAME (b);
    }

  if (a == b)
    /* This can happen with friend specializations.  Just order by
       entry address.  See note in depset_cmp.  */
    return ea < eb ? -1 : +1;

  return DECL_UID (a) < DECL_UID (b) ? -1 : +1;
}

/* Insert a redirect for the DECL_TEMPLATE_RESULT of a partial
   specialization, as we're unable to go from there to here (without
   repeating the DECL_TEMPLATE_SPECIALIZATIONS walk for *every*
   MAYBE_SPEC dependency add.  */

depset *
depset::hash::add_partial_redirect (depset *partial)
{
  partial->set_flag_bit<DB_PARTIAL_BIT> ();

  tree inner = DECL_TEMPLATE_RESULT (partial->get_entity ());
  depset *redirect = make_entity (inner, EK_REDIRECT);

  /* Redirects are never reached -- always snap to their target.  */
  redirect->set_flag_bit<DB_UNREACHED_BIT> ();

  depset **slot = entity_slot (inner, true);
  gcc_checking_assert (!*slot);
  *slot = redirect;
  redirect->deps.safe_push (partial);

  return redirect;
}

/* We add all kinds of specialializations.  Implicit specializations
   should only streamed and walked if they are reachable from
   elsewhere.  Hence the UNREACHED flag.  This is making the
   assumption that it is cheaper to reinstantiate them on demand
   elsewhere, rather than stream them in when we instantiate their
   general template.  Also, if we do stream them, we can only do that
   if they are not internal (which they can become if they themselves
   touch an internal entity?).  */

void
depset::hash::add_specializations (bool decl_p)
{
  vec<spec_entry *> data;
  data.create (100);
  walk_specializations (decl_p, specialization_add, &data);
  data.qsort (specialization_cmp);
  while (data.length ())
    {
      spec_entry *entry = data.pop ();
      tree spec = entry->spec;
      bool is_partial = false;
      int use_tpl = 0;
      bool is_alias = false;

      if (!decl_p && DECL_ALIAS_TEMPLATE_P (entry->tmpl))
	{
	  spec = TYPE_NAME (spec);
	  is_alias = true;
	}

      if (decl_p || is_alias)
	{
	  if (tree ti = DECL_TEMPLATE_INFO (spec))
	    {
	      tree tmpl = TI_TEMPLATE (ti);

	      use_tpl = DECL_USE_TEMPLATE (spec);
	      if (spec == DECL_TEMPLATE_RESULT (tmpl))
		{
		  spec = tmpl;
		  gcc_checking_assert (DECL_USE_TEMPLATE (spec) == use_tpl);
		}
	    }
	  else
	    /* This is some kind of friend.  */
	    gcc_assert (!DECL_USE_TEMPLATE (spec));
	}
      else
	{
	  if (TREE_CODE (spec) == ENUMERAL_TYPE)
	    {
	      tree ctx = DECL_CONTEXT (TYPE_NAME (spec));

	      if (TYPE_P (ctx))
		use_tpl = CLASSTYPE_USE_TEMPLATE (ctx);
	      else
		use_tpl = DECL_USE_TEMPLATE (ctx);
	    }
	  else
	    {
	      use_tpl = CLASSTYPE_USE_TEMPLATE (spec);

	      tree partial = DECL_TEMPLATE_SPECIALIZATIONS (entry->tmpl);
	      for (; partial; partial = TREE_CHAIN (partial))
		if (TREE_TYPE (partial) == spec)
		  break;

	      if (partial)
		{
		  gcc_checking_assert (entry->args == TREE_PURPOSE (partial));
		  is_partial = true;
		  /* Get the TEMPLATE_DECL for the partial
		     specialization.  */
		  spec = TREE_VALUE (partial);
		  gcc_assert (DECL_USE_TEMPLATE (spec) == use_tpl);
		}
	    }

	  if (!is_partial)
	    {
	      tree ti = TYPE_TEMPLATE_INFO (spec);
	      tree tmpl = TI_TEMPLATE (ti);

	      spec = TYPE_NAME (spec);
	      if (spec == DECL_TEMPLATE_RESULT (tmpl))
		{
		  spec = tmpl;
		  use_tpl = DECL_USE_TEMPLATE (spec);
		}
	    }
	}

      gcc_checking_assert (STRIP_TEMPLATE (spec)
			   == get_instantiating_module_decl (spec));

      bool needs_reaching = false;
      if (use_tpl == 1)
	/* Implicit instantiations only walked if we reach them.  */
	needs_reaching = true;
      else if (!DECL_LANG_SPECIFIC (spec)
	       || !DECL_MODULE_PURVIEW_P (spec))
	/* Likewise, GMF explicit or partial specializations.  */
	needs_reaching = true;

#if 0 && CHECKING_P
      /* The instantiation isn't always on
	 DECL_TEMPLATE_INSTANTIATIONS, */
      // FIXME: we probably need to remember this information?
      /* Verify the specialization is on the
	 DECL_TEMPLATE_INSTANTIATIONS of the template.  */
      for (tree cons = DECL_TEMPLATE_INSTANTIATIONS (entry->tmpl);
	   cons; cons = TREE_CHAIN (cons))
	if (TREE_VALUE (cons) == entry->spec)
	  {
	    gcc_assert (entry->args == TREE_PURPOSE (cons));
	    goto have_spec;
	  }
      gcc_unreachable ();
    have_spec:;
#endif

      depset *dep = add_dependency (spec, depset::EK_SPECIALIZATION);
      gcc_assert (dep->is_import ()
		  == ((*modules)[DECL_LANG_SPECIFIC (spec)
				 ? DECL_MODULE_ORIGIN (spec) : 0]->remap != 0));
      if (dep->is_special ())
	{
	  /* An already located specialization, this must be a friend
	     with a different entry->tmpl.  */
	  spec_entry *other = reinterpret_cast <spec_entry *> (dep->deps[0]);
	  if (other->tmpl != entry->tmpl)
	    gcc_checking_assert (!is_partial
				 && needs_reaching == dep->is_unreached ());
	  else
	    {
	      gcc_checking_assert (!decl_p && !dep->is_type_spec ());
	      // dep->set_flag_bit<DB_BOTH_SPEC_BIT> ();
	    }
	}
      else
	{
	  dep->set_special ();
	  dep->deps.safe_push (reinterpret_cast<depset *> (entry));
	  if (needs_reaching)
	    dep->set_flag_bit<DB_UNREACHED_BIT> ();
	  if (is_partial)
	    add_partial_redirect (dep);
	  if (!decl_p)
	    dep->set_flag_bit<DB_TYPE_SPEC_BIT> ();
	}
    }
  data.release ();
}

/* Iteratively find dependencies.  During the walk we may find more
   entries on the same binding that need walking.  */

void
depset::hash::find_dependencies ()
{
  trees_out walker (NULL, NULL, *this);
  vec<depset *> unreached;
  unreached.create (worklist.length ());

  for (;;)
    {
      reached_unreached = false;
      while (worklist.length ())
	{
	  depset *item = worklist.pop ();

	  gcc_checking_assert (!item->is_binding ());
	  if (item->is_unreached ())
	    unreached.quick_push (item);
	  else
	    {
	      current = item;
	      tree decl = current->get_entity ();
	      dump (dumper::DEPEND)
		&& dump ("Dependencies of %s %C:%N",
			 current->entity_kind_name (), TREE_CODE (decl), decl);
	      dump.indent ();
	      walker.begin ();
	      if (current->get_entity_kind () == EK_USING)
		walker.tree_node (OVL_FUNCTION (decl));
	      else if (TREE_VISITED (decl))
		/* A global tree.  */;
	      else
		{
		  walker.mark_declaration (decl, current->has_defn ());

		  /* Turn the Sneakoscope on when depending the decl.  */
		  sneakoscope = true;
		  walker.tree_node (decl);
		  sneakoscope = false;
		  if (current->has_defn ())
		    walker.write_definition (decl);
		}
	      walker.end ();

	      /* Mark all the explicit & partial specializations as
		 reachable.  */
	      if (TREE_CODE (decl) == TEMPLATE_DECL)
		for (tree cons = DECL_TEMPLATE_INSTANTIATIONS (decl);
		     cons; cons = TREE_CHAIN (cons))
		  {
		    tree spec = TREE_VALUE (cons);
		    if (TYPE_P (spec))
		      spec = TYPE_NAME (spec);
		    int use_tpl;
		    node_template_info (spec, use_tpl);
		    if (use_tpl & 2)
		      {
			depset *spec_dep = find_entity (spec);
			if (spec_dep->get_entity_kind () == EK_REDIRECT)
			  spec_dep = spec_dep->deps[0];
			gcc_checking_assert (spec_dep->get_entity_kind ()
					     == EK_SPECIALIZATION);
			if (spec_dep->is_unreached ())
			  {
			    reached_unreached = true;
			    spec_dep->clear_flag_bit<DB_UNREACHED_BIT> ();
			    dump (dumper::DEPEND)
			      && dump ("Reaching unreached specialization %C:%N",
				       TREE_CODE (spec), spec);
			  }
		      }
		  }

	      dump.outdent ();
	      current = NULL;
	    }
	}

      if (!reached_unreached)
	break;

      /* It's possible the we reached the unreached before we
	 processed it in the above loop, so we'll be doing this an
	 extra time.  However, to avoid that we have to do some
	 bit shuffling that also involves a scan of the list.
	 Swings & roundabouts I guess.  */
      std::swap (worklist, unreached);
    }

  unreached.release ();
}

/* Compare two binding entries.  TYPE_DECL before non-exported before
   exported.  */
// FIXME: Reachable globals are not findable by name

static int
binding_cmp (const void *a_, const void *b_)
{
  depset *a = *(depset *const *)a_;
  depset *b = *(depset *const *)b_;

  tree a_ent = a->get_entity ();
  tree b_ent = b->get_entity ();
  gcc_checking_assert (a_ent != b_ent
		       && !a->is_binding ()
		       && !b->is_binding ());

  /* Implicit typedefs come first.  */
  bool a_implicit = DECL_IMPLICIT_TYPEDEF_P (a_ent);
  bool b_implicit = DECL_IMPLICIT_TYPEDEF_P (b_ent);
  if (a_implicit || b_implicit)
    {
      /* A binding with two implicit type decls?  That's unpossible!  */
      gcc_checking_assert (!(a_implicit && b_implicit));
      return a_implicit ? -1 : +1;  /* Implicit first.  */
    }

  /* Hidden before non-hidden.  */
  bool a_hidden = a->is_hidden ();
  bool b_hidden = b->is_hidden ();
  if (a_hidden != b_hidden)
    return a_hidden ? -1 : +1;

  bool a_using = a->get_entity_kind () == depset::EK_USING;
  bool a_export;
  if (a_using)
    {
      a_export = OVL_EXPORT_P (a_ent);
      a_ent = OVL_FUNCTION (a_ent);
    }
  else
    a_export = DECL_MODULE_EXPORT_P (TREE_CODE (a_ent) == CONST_DECL
				     ? TYPE_NAME (TREE_TYPE (a_ent))
				     : STRIP_TEMPLATE (a_ent));
  
  bool b_using = b->get_entity_kind () == depset::EK_USING;
  bool b_export;
  if (b_using)
    {
      b_export = OVL_EXPORT_P (b_ent);
      b_ent = OVL_FUNCTION (b_ent);
    }
  else
    b_export = DECL_MODULE_EXPORT_P (TREE_CODE (b_ent) == CONST_DECL
				     ? TYPE_NAME (TREE_TYPE (b_ent))
				     : STRIP_TEMPLATE (b_ent));

  /* Non-exports before exports.  */
  if (a_export != b_export)
    return a_export ? +1 : -1;

  /* At this point we don't care, but want a stable sort.  */

  if (a_using != b_using)
    /* using first.  */
    return a_using? -1 : +1;

  return DECL_UID (a_ent) < DECL_UID (b_ent) ? -1 : +1;
}

/* Sort the bindings, issue errors about bad internal refs.  */

bool
depset::hash::finalize_dependencies ()
{
  bool ok = true;
  depset::hash::iterator end (this->end ());
  for (depset::hash::iterator iter (begin ()); iter != end; ++iter)
    {
      depset *dep = *iter;
      if (dep->is_binding ())
	dep->deps.qsort (binding_cmp);
      else if (dep->refs_internal ())
	{
	  ok = false;
	  tree decl = dep->get_entity ();
#if 1
	  // FIXME: __thread_active_p is borked, so allow it.
	  if (CP_DECL_CONTEXT (decl) == global_namespace
	      && DECL_NAME (decl)
	      && !strcmp (IDENTIFIER_POINTER (DECL_NAME (decl)),
			  "__gthread_active_p"))
	    ok = true;
#endif
	  if (!ok)
	    for (unsigned ix = dep->deps.length (); ix--;)
	      {
		depset *rdep = dep->deps[ix];
		if (rdep->is_internal ())
		  {
		    // FIXME: Better location information?  We're
		    // losing, so it doesn't matter about efficiency
		    error_at (DECL_SOURCE_LOCATION (decl),
			      "%q#D references internal linkage entity %q#D",
			      decl, rdep->get_entity ());
		    break;
		  }
	      }
	}
    }

  return ok;
}

/* Core of TARJAN's algorithm to find Strongly Connected Components
   within a graph.  See https://en.wikipedia.org/wiki/
   Tarjan%27s_strongly_connected_components_algorithm for details.

   We use depset::section as lowlink.  Completed nodes have
   depset::cluster containing the cluster number, with the top
   bit set.

   A useful property is that the output vector is a reverse
   topological sort of the resulting DAG.  In our case that means
   dependent SCCs are found before their dependers.  We make use of
   that property.  */

void
depset::tarjan::connect (depset *v)
{
  gcc_checking_assert (v->is_binding () || !v->is_unreached ());

  v->cluster = v->section = ++index;
  stack.safe_push (v);

  /* Walk all our dependencies, ignore a first marked slot  */
  for (unsigned ix = v->is_special (); ix != v->deps.length (); ix++)
    {
      depset *dep = v->deps[ix];
      unsigned lwm = dep->cluster;
      if (!dep->cluster)
	{
	  /* A new node.  Connect it.  */
	  connect (dep);
	  lwm = dep->section;
	}

      if (dep->section && v->section > lwm)
	v->section = lwm;
    }

  if (v->section == v->cluster)
    {
      /* Root of a new SCC.  Push all the members onto the result list. */
      unsigned num = v->cluster;
      depset *p;
      do
	{
	  p = stack.pop ();
	  p->cluster = num;
	  p->section = 0;
	  result.quick_push (p);
	}
      while (p != v);
    }
}

/* Compare two depsets.  The specific ordering is unimportant, we're
   just trying to get consistency.  */

static int
depset_cmp (const void *a_, const void *b_)
{
  depset *a = *(depset *const *)a_;
  depset *b = *(depset *const *)b_;

  depset::entity_kind a_kind = a->get_entity_kind ();
  depset::entity_kind b_kind = b->get_entity_kind ();

  if  (a_kind != b_kind)
    /* Different entity kinds, order by that.  */
    return a_kind < b_kind ? -1 : +1;
  
  tree a_decl = a->get_entity ();
  tree b_decl = b->get_entity ();
  if (a_kind == depset::EK_USING)
    {
      /* If one is a using, the other must be too.  */
      a_decl = OVL_FUNCTION (a_decl);
      b_decl = OVL_FUNCTION (b_decl);
    }

  if (a_decl != b_decl)
    /* Different entities, order by their UID.  */
    return DECL_UID (a_decl) < DECL_UID (b_decl) ? -1 : +1;

  if (a_kind == depset::EK_BINDING)
    {
      /* Both are bindings.  */
      /* Order by identifier hash (hey, it's a consistent number).  */
      // FIXME: strcmp for user-meaningful order?
      gcc_checking_assert (a->get_name () != b->get_name ());
      return (IDENTIFIER_HASH_VALUE (a->get_name ())
	      < IDENTIFIER_HASH_VALUE (b->get_name ())
	      ? -1 : +1);
    }

  /* They are the same decl.  This can happen with two using decls
     pointing to the same target.  The best we can aim for is
     consistently telling qsort how to order them.  Hopefully we'll
     never have to debug a case that depends on this.  Oh, who am I
     kidding?  Good luck.  */
  gcc_checking_assert (a_kind == depset::EK_USING);

  /* Order by depset address.  Not the best, but it is something.  */
  return a < b ? -1 : +1;
}

/* Compare members of a cluster.  Order by entity kind.  depsets
   of the same kind can be arbitrary, but we want something
   stable.  */

static int
cluster_cmp (const void *a_, const void *b_)
{
  depset *a = *(depset *const *)a_;
  depset *b = *(depset *const *)b_;

  unsigned a_kind = a->get_entity_kind ();
  unsigned b_kind = b->get_entity_kind ();
  if (a_kind != b_kind)
    return a_kind < b_kind ? -1 : +1;

  /* Now order for qsort stability.  */
  tree a_decl = a->get_entity ();
  tree b_decl = b->get_entity ();
  if (a_kind == depset::EK_USING)
    {
      a_decl = OVL_FUNCTION (a_decl);
      b_decl = OVL_FUNCTION (b_decl);
    }

  if (a_decl != b_decl)
    /* Different entities, order by their UID.  */
    return DECL_UID (a_decl) < DECL_UID (b_decl) ? -1 : +1;

  if (a == b)
    /* Can occur during testing.  */
    return 0;

  /* Same decl.  They must be bindings.  Order by strcmp for
     user-meaningful order.  */
  return strcmp (IDENTIFIER_POINTER (a->get_name ()),
		 IDENTIFIER_POINTER (b->get_name ()));
}

/* Reduce graph to SCCS clusters.  SCCS will be populated with the
   depsets in dependency order.  Each depset's CLUSTER field contains
   its cluster number.  Each SCC has a unique cluster number, and are
   contiguous in SCCS. Cluster numbers are otherwise arbitrary.  */

vec<depset *>
depset::hash::connect ()
{
  tarjan connector (size ());
  vec<depset *> deps;
  deps.create (size ());
  iterator end (this->end ());
  for (iterator iter (begin ()); iter != end; ++iter)
    {
      depset *item = *iter;

      if (item->is_binding () || !item->is_unreached ())
	deps.quick_push (item);
    }

  /* Iteration over the hash table is an unspecified ordering.  While
     that has advantages, it causes 2 problems.  Firstly repeatable
     builds are tricky.  Secondly creating testcases that check
     dependencies are correct by making sure a bad ordering would
     happen if that was wrong.  */
  deps.qsort (depset_cmp);

  while (deps.length ())
    {
      depset *v = deps.pop ();
      dump (dumper::CLUSTER) &&
	(v->is_binding ()
	 ? dump ("Connecting binding %P", v->get_entity (), v->get_name ())
	 : dump ("Connecting %s %s %C:%N",
		 !v->has_defn () ? "declaration" : "definition",
		 v->entity_kind_name (), TREE_CODE (v->get_entity ()),
		 v->get_entity ()));
      if (!v->cluster)
	connector.connect (v);
    }

  deps.release ();
  return connector.result;
}

bool
specset::hash::add (tree ns, tree name, unsigned index)
{
  specset key (ns, name);
  specset **slot = find_slot (&key, INSERT);
  specset *set = *slot;
  bool is_new = !set;

  if (is_new || set->num == (1u << set->allocp2))
    {
      unsigned n = set ? set->num * 2 : 1;
      size_t new_size = (offsetof (specset, pending)
			 + sizeof (specset::pending) * n);
      specset *new_set = (new (::operator new (new_size))
			  specset (set ? set : &key));
      delete set;
      set = new_set;
      *slot = set;
    }

  set->pending[set->num++] = index;

  return is_new;
}

specset *
specset::hash::lookup (tree ns, tree name)
{
  specset key (ns, name);
  specset *res = NULL;

  if (specset **slot = find_slot (&key, NO_INSERT))
    {
      res = *slot;
      /* We need to remove the specset without deleting it. */
      traits::mark_deleted (*slot);
    }

  return res;
}

/* Initialize location spans.  */

void
loc_spans::init (const line_maps *lmaps, const line_map_ordinary *map)
{
  gcc_checking_assert (!init_p ());
  spans.reserve (20);

  span interval;
  interval.ordinary.first = 0;
  interval.macro.second = MAX_LOCATION_T + 1;
  interval.ordinary_delta = interval.macro_delta = 0;

  /* A span for reserved fixed locs.  */
  interval.ordinary.second
    = MAP_START_LOCATION (LINEMAPS_ORDINARY_MAP_AT (line_table, 0));
  interval.macro.first = interval.macro.second;
  dump (dumper::LOCATION)
    && dump ("Fixed span %u ordinary:[%u,%u) macro:[%u,%u)", spans.length (),
	     interval.ordinary.first, interval.ordinary.second,
	     interval.macro.first, interval.macro.second);
  spans.quick_push (interval);

  /* A span for command line & forced headers.  */
  interval.ordinary.first = interval.ordinary.second;
  interval.macro.second = interval.macro.first;
  interval.ordinary.second = map->start_location;
  interval.macro.first = LINEMAPS_MACRO_LOWEST_LOCATION (lmaps);
  dump (dumper::LOCATION)
    && dump ("Pre span %u ordinary:[%u,%u) macro:[%u,%u)", spans.length (),
	     interval.ordinary.first, interval.ordinary.second,
	     interval.macro.first, interval.macro.second);
  spans.quick_push (interval);
  
  /* Start an interval for the main file.  */
  interval.ordinary.first = interval.ordinary.second;
  interval.macro.second = interval.macro.first;
  dump (dumper::LOCATION)
    && dump ("Main span %u ordinary:[%u,*) macro:[*,%u)", spans.length (),
	     interval.ordinary.first, interval.macro.second);
  spans.quick_push (interval);
}

/* Open a new linemap interval.  The just-created ordinary map is the
   first map of the interval.  */

void
loc_spans::open (location_t hwm = UNKNOWN_LOCATION)
{
  if (hwm == UNKNOWN_LOCATION)
    hwm = MAP_START_LOCATION (LINEMAPS_LAST_ORDINARY_MAP (line_table));

  span interval;
  interval.ordinary.first = interval.ordinary.second = hwm;
  interval.macro.first = interval.macro.second
    = LINEMAPS_MACRO_LOWEST_LOCATION (line_table);
  interval.ordinary_delta = interval.macro_delta = 0;
  dump (dumper::LOCATION)
    && dump ("Opening span %u ordinary:[%u,... macro:...,%u)",
	     spans.length (), interval.ordinary.first,
	     interval.macro.second);
  spans.safe_push (interval);
}

/* Close out the current linemap interval.  The last maps are within
   the interval.  */

void
loc_spans::close ()
{
  span &interval = spans.last ();

  interval.ordinary.second
    = ((line_table->highest_location + (1 << line_table->default_range_bits))
       & ~((1u << line_table->default_range_bits) - 1));
  interval.macro.first = LINEMAPS_MACRO_LOWEST_LOCATION (line_table);
  dump (dumper::LOCATION)
    && dump ("Closing span %u ordinary:[%u,%u) macro:[%u,%u)",
	     spans.length () - 1,
	     interval.ordinary.first,interval.ordinary.second,
	     interval.macro.first, interval.macro.second);
}

/* Given an ordinary location LOC, return the lmap_interval it resides
   in.  NULL if it is not in an interval.  */

const loc_spans::span *
loc_spans::ordinary (location_t loc)
{
  unsigned len = spans.length ();
  unsigned pos = 0;
  while (len)
    {
      unsigned half = len / 2;
      const span &probe = spans[pos + half];
      if (loc < probe.ordinary.first)
	len = half;
      else if (loc < probe.ordinary.second)
	return &probe;
      else
	{
	  pos += half + 1;
	  len = len - (half + 1);
	}
    }
  return NULL;
}

/* Likewise, given a macro location LOC, return the lmap interval it
   resides in.   */

const loc_spans::span *
loc_spans::macro (location_t loc)
{
  unsigned len = spans.length ();
  unsigned pos = 0;
  while (len)
    {
      unsigned half = len / 2;
      const span &probe = spans[pos + half];
      if (loc >= probe.macro.second)
	len = half;
      else if (loc >= probe.macro.first)
	return &probe;
      else
	{
	  pos += half + 1;
	  len = len - (half + 1);
	}
    }
  return NULL;
}

/* Return the ordinary location closest to FROM.  */

static location_t
ordinary_loc_of (line_maps *lmaps, location_t from)
{
  while (!IS_ORDINARY_LOC (from))
    {
      if (IS_ADHOC_LOC (from))
	from = get_location_from_adhoc_loc (lmaps, from);
      if (IS_MACRO_LOC (from))
	{
	  /* Find the ordinary location nearest FROM.  */
	  const line_map *map = linemap_lookup (lmaps, from);
	  const line_map_macro *mac_map = linemap_check_macro (map);
	  from = MACRO_MAP_EXPANSION_POINT_LOCATION (mac_map);
	}
    }
  return from;
}

static module_state **
get_module_slot (tree name, module_state *parent, bool partition, bool insert)
{
  module_state_hash::compare_type ct (name, uintptr_t (parent) | partition);
  hashval_t hv = module_state_hash::hash (ct);

  return modules_hash->find_slot_with_hash (ct, hv, insert ? INSERT : NO_INSERT);
}

static module_state *
get_primary (module_state *parent)
{
  while (parent->is_partition ())
    parent = parent->parent;
  return parent;
}

/* Find or create module NAME & PARENT in the hash table.  */

module_state *
get_module (tree name, module_state *parent, bool partition)
{
  if (partition)
    {
      if (!parent)
	parent = get_primary ((*modules)[0]);

      if (!parent->is_partition () && !parent->flatname)
	parent->set_flatname ();
    }

  module_state **slot = get_module_slot (name, parent, partition, true);
  module_state *state = *slot;
  if (!state)
    {
      state = (new (ggc_alloc<module_state> ())
	       module_state (name, parent, partition));
      *slot = state;
    }
  return state;
}

/* Process string name PTR into a module_state.  */

static module_state *
get_module (const char *ptr)
{
  if (ptr[0] == '.' ? IS_DIR_SEPARATOR (ptr[1]) : IS_ABSOLUTE_PATH (ptr))
    /* A header name.  */
    return get_module (build_string (strlen (ptr), ptr));

  bool partition = false;
  module_state *mod = NULL;

  for (const char *probe = ptr;; probe++)
    if (!*probe || *probe == '.' || *probe == ':')
      {
	if (probe == ptr)
	  return NULL;

	mod = get_module (get_identifier_with_length (ptr, probe - ptr),
			  mod, partition);
	ptr = probe;
	if (*ptr == ':')
	  {
	    if (partition)
	      return NULL;
	    partition = true;
	  }

	if (!*ptr++)
	  break;
      }
    else if (!(ISALPHA (*probe) || *probe == '_'
	       || (probe != ptr && ISDIGIT (*probe))))
      return NULL;

  return mod;
}

bool
module_normal_import_p (unsigned m)
{
  module_state *module = (*modules)[m];

  return !(module->is_header () || module->is_partition ()
	   || module->is_primary ());
}

/* Create a mapper.  The mapper may be dead.  Yes, I'm embedding some
   client-side socket handling in the compiler.  At least it's not
   ipv4.  */

module_mapper::module_mapper (location_t loc, const char *option)
  : name (NULL), from (NULL), to (NULL), pex (NULL), sigpipe (SIG_IGN),
    /* Exercise buffer expansion code.  */
    buffer (NULL), size (EXPERIMENT (3, 200)), pos (NULL), end (NULL),
    start (NULL), fd_from (-1), fd_to (-1), batching (false)
{
  const char *dflt = "|cxx-mapper";
  pex = NULL;

  /* We set name as soon as we know what kind of mapper this is.  */
  if (!option)
    option = dflt;

  timevar_start (TV_MODULE_MAPPER);
  dump () && dump ("Initializing mapper %s", option);

  /* String never modified in this case.  */
  set_cmi_repo (const_cast<char *> ("gcm.cache"));

  int err = 0;
  const char *errmsg = NULL;

  /* First copy.  */
  unsigned spaces = 0;
  unsigned len = 0;
  char *cookie = NULL;

  for (; option[len]; len++)
    {
      if (option[len] == ' ')
	spaces++;
      if (option[len] == '?' && !cookie)
	cookie = const_cast<char *> (&option[len]);
    }
  char *writable = XNEWVEC (char, len + 1);
  memcpy (writable, option, len + 1);
  if (cookie)
    {
      len = cookie - option;
      cookie = writable + len;
      *cookie = 0;
    }

  if (writable[0] == '|')
    {
      /* A program to spawn and talk to.  */
      /* Split writable at white-space.  No space-containing args
	 for you!  */
      char **argv = XALLOCAVEC (char *, spaces + 2);
      unsigned arg_no = 0;

      for (char *ptr = writable + 1; ; ptr++)
	{
	  argv[arg_no] = ptr;
	  for (;; ptr++)
	    {
	      if (*ptr == ' ')
		break;
	      else if (*ptr)
		continue;
	      else if (ptr != cookie)
		break;
	      else if (arg_no != 1)
		{
		  /* Not a cookie after all.  */
		  *cookie = '?';
		  cookie = NULL;
		}
	    }
	  if (!arg_no++)
	    len = ptr - (writable + 1);	  
	  if (!*ptr)
	    break;
	  *ptr = 0;
	}
      argv[arg_no] = NULL;

      pex = pex_init (PEX_USE_PIPES, progname, NULL);
      to = pex_input_pipe (pex, false);
      if (!to)
	{
	  err = errno;
	  errmsg = "connecting input";
	}
      else
	{
	  int flags = PEX_SEARCH;

	  /* Use strcmp to detect default, so we may explicitly name
	     it with additional args in tests etc.  */
	  if ((option == dflt || 0 == strcmp (argv[0], dflt + 1))
	      && save_decoded_options[0].opt_index == OPT_SPECIAL_program_name
	      && save_decoded_options[0].arg != progname)
	    {
	      /* Prepend the invoking path.  */
	      const char *fullname = save_decoded_options[0].arg;
	      size_t dir_len = progname - fullname;
	      char *argv0 = XNEWVEC (char, dir_len + len + 1);
	      memcpy (argv0, fullname, dir_len);
	      memcpy (argv0 + dir_len, argv[0], len + 1);
	      argv[0] = argv0;
	      flags = 0;
	    }
	  errmsg = pex_run (pex, flags, argv[0], argv, NULL, NULL, &err);
	  if (!flags)
	    XDELETEVEC (argv[0]);
	}

      if (!errmsg)
	{
	  from = pex_read_output (pex, false);
	  if (from)
	    {
	      fd_to = fileno (to);
	      fd_from = fileno (from);
	    }
	  else
	    {
	      err = errno;
	      errmsg = "connecting output";
	      fclose (to);
	      to = NULL;
	    }
	}
      name = writable;
    }
  else if (writable[0] == '<')
    {
      /* File descriptors, inc stdin/out.  */
      int from = -1, to = -1;
      char *ptr = writable + 1, *eptr;
      from = strtoul (ptr, &eptr, 0);
      if (*eptr == '>')
	{
	  ptr = eptr + 1;
	  to = strtoul (ptr, &eptr, 0);
	  if (eptr != ptr && from == -1)
	    from = to;
	}
      if (*eptr)
	errmsg = "parsing";
      else
	{
	  if (eptr == writable + 2)
	    {
	      from = fileno (stdin);
	      to = fileno (stdout);
	    }
	  fd_to = to;
	  fd_from = from;
	}
      name = writable;
    }

  if (!name)
    {
      int fd;

      /* Does it look like a socket?  */
#ifdef NETWORKING
#ifdef HAVE_AF_UNIX
      sockaddr_un un;
      size_t un_len = 0;
      un.sun_family = AF_UNSPEC;
#endif
      int port = 0;
#ifdef HAVE_AF_INET6
      struct addrinfo *addrs = NULL;
#endif
#endif
      if (writable[0] == '=')
	{
	  /* A local socket.  */
#ifdef HAVE_AF_UNIX
	  if (len < sizeof (un.sun_path))
	    {
	      memset (&un, 0, sizeof (un));
	      un.sun_family = AF_UNIX;
	      memcpy (un.sun_path, writable + 1, len);
	    }
	  un_len = offsetof (struct sockaddr_un, sun_path) + len + 1;
#else
	  errmsg = "unix protocol unsupported";
#endif
	  name = writable;
	}
      else if (char *colon = (char *)memrchr (writable, ':', len))
	{
	  /* Try a hostname:port address.  */
	  char *endp;
	  port = strtoul (colon + 1, &endp, 10);
	  if (port && endp != colon + 1 && !*endp)
	    {
	      /* Ends in ':number', treat as ipv6 domain socket.  */
#ifdef HAVE_AF_INET6
	      addrinfo hints;

	      hints.ai_flags = AI_NUMERICSERV;
	      hints.ai_family = AF_INET6;
	      hints.ai_socktype = SOCK_STREAM;
	      hints.ai_protocol = 0;
	      hints.ai_addrlen = 0;
	      hints.ai_addr = NULL;
	      hints.ai_canonname = NULL;
	      hints.ai_next = NULL;

	      *colon = 0;
	      /* getaddrinfo requires a port number, but is quite
		 happy to accept invalid ones.  So don't rely on it.  */
	      if (int e = getaddrinfo (colon == writable ? NULL : writable,
				       "0", &hints, &addrs))
		{
		  err = e;
		  errmsg = "resolving address";
		}
	      else
		un.sun_family = AF_INET6;
	      *colon = ':';
#else
	      errmsg = "ipv6 protocol unsupported";
#endif
	      name = writable;
	    }
	}
      
      if (un.sun_family != AF_UNSPEC)
	{
	  fd = socket (un.sun_family, SOCK_STREAM, 0);
	  if (fd < 0)
	    ;
#ifdef HAVE_AF_UNIX
	  else if (un.sun_family == AF_UNIX)
	    {
	      if (connect (fd, (sockaddr *)&un, un_len) < 0)
		{
		  close (fd);
		  fd = -1;
		}
	    }
#endif
#ifdef HAVE_AF_INET6
	  else if (un.sun_family == AF_INET6)
	    {
	      struct addrinfo *next;
	      for (next = addrs; next; next = next->ai_next)
		if (next->ai_family == AF_INET6
		    && next->ai_socktype == SOCK_STREAM)
		  {
		    sockaddr_in6 *in6 = (sockaddr_in6 *)next->ai_addr;
		    in6->sin6_port = htons (port);
		    if (ntohs (in6->sin6_port) != port)
		      errno = EINVAL;
		    else if (!connect (fd, next->ai_addr, next->ai_addrlen))
		      break;
		  }

	      if (!next)
		{
		  close (fd);
		  fd = -1;
		}
	    }
#endif
	  else
	    gcc_unreachable ();

#ifdef HAVE_AF_INET6
	  freeaddrinfo (addrs);
#endif
	  if (fd >= 0)
	    /* We have a socket.  */
	    fd_from = fd_to = fd;
	  else if (!errmsg)
	    {
	      err = errno;
	      errmsg = "connecting socket";
	    }
	}
    }

  if (!name)
    {
      /* Try a mapping file.  */
      from = fopen (writable, "r");
      if (from)
	fd_from = fileno (from);
      else
	{
	  err = errno;
	  errmsg = "opening";
	}
      name = writable;
    }

  if (errmsg)
    {
      errno = err;
      error_at (loc, err <= 0 ? G_("failed %s of mapper %qs: %s")
		: G_("failed %s of mapper %qs: %m"),
		errmsg, name ? name : option,
		err < 0 ? gai_strerror (err) : _("Facility not provided"));
      kill (loc);
      goto done;
    }

  if (noisy_p ())
    {
      fprintf (stderr, " mapper:%s", name);
      fflush (stderr);
    }
  dump () && dump ("Initialized mapper");

  pos = end = buffer = XNEWVEC (char, size);

  if (fd_to >= 0)
    {
#ifdef SIGPIPE
      /* We need to ignore sig pipe for a while.  */
      sigpipe = signal (SIGPIPE, SIG_IGN);
#endif
      if (!handshake (loc, cookie ? cookie + 1 : main_input_filename))
	kill (loc);
    }
  else
    {
      /* A mapping file.  Read it.  */
      dump () && dump ("Reading mapping file %s", name);

      bool starting = true;
      for (int r; (r = get_response (loc)) >= 0;)
	if (r)
	  {
	    char *mod = response_token (loc);
	    bool ignore = false;
	    char *file = NULL;

	    /* Ignore non-cookie lines.  */
	    if (cookie && 0 != strcmp (mod, cookie + 1))
	      ignore = true;
	    else
	      {
		if (cookie)
		  mod = response_token (loc);
		if (mod)
		  file = response_token (loc, true);
	      }

	    if (!response_eol (loc, ignore))
	      continue;

	    if (!file)
	      continue;

	    if (starting && 0 == strcmp (mod, "$root"))
	      {
		set_cmi_repo (file);
		continue;
	      }

	    starting = false;
	    file = maybe_strip_cmi_prefix (file);
	    module_state *state = get_module (mod);
	    if (!state)
	      response_unexpected (loc);
	    else if (!state->filename)
	      state->filename = xstrdup (file);
	    else if (strcmp (state->filename, file))
	      warning_at (loc, 0, "ignoring conflicting mapping of %qs to %qs",
			  state->get_flatname (), file);
	  }
      fclose (from);
      from = NULL;
      /* Leave fd_from alone to show liveness.  */
    }

 done:
  timevar_stop (TV_MODULE_MAPPER);
}

/* Close down the mapper.  Mark it as not restartable.  */

void
module_mapper::kill (location_t loc)
{
  if (!is_live ())
    return;

  timevar_start (TV_MODULE_MAPPER);
  dump () && dump ("Killing mapper %s", name);

  if (to)
    {
      fclose (to);
      to = NULL;
      fd_to = -1;
    }
#ifdef NETWORKING
  else if (fd_to >= 0)
    {
      shutdown (fd_to, SHUT_WR);
      fd_to = -1;
    }
#endif

  if (pex)
    {
      int status;

      pex_get_status (pex, 1, &status);
      pex_free (pex);
      pex = NULL;

      if (WIFSIGNALED (status))
	error_at (loc, "mapper %qs died by signal %s",
		  name, strsignal (WTERMSIG (status)));
      else if (WIFEXITED (status) && WEXITSTATUS (status) != 0)
	error_at (loc, "mapper %qs exit status %d",
		  name, WEXITSTATUS (status));
      from = NULL;
      fd_from = -1;
    }
  else if (fd_from >= 0)
    {
      if (!is_file ())
	close (fd_from);
      fd_from = -1;
    }

#ifdef SIGPIPE
  if (sigpipe != SIG_IGN)
    /* Restore sigpipe.  */
    signal (SIGPIPE, sigpipe);
#endif

  XDELETEVEC (buffer);
  buffer = NULL;

  timevar_stop (TV_MODULE_MAPPER);
}

/* Create a new mapper connecting to OPTION.  */

module_mapper *
module_mapper::make (location_t loc)
{
  const char *option = module_mapper_name;
  if (!option)
    option = getenv ("CXX_MODULE_MAPPER");
  return new module_mapper (loc, option);
}

/* Send a command to the mapper.  */

void
module_mapper::send_command (location_t loc, const char *format, ...)
{
  size_t actual = 0;
  if (pos != buffer)
    pos = end = buffer;
  if (batching)
    *end++ = '+';
  else if (end != buffer)
    *end++ = '-';

  for (;;)
    {
      va_list args;
      va_start (args, format);
      size_t available = (buffer + size) - end;
      actual = vsnprintf (end, available, format, args);
      va_end (args);
      if (actual < available)
	break;

      size = size * 2 + actual + 20;
      char *next = XRESIZEVEC (char, buffer, size);
      end = next + (end - buffer);
      buffer = pos = next;
    }

  if (batching)
    dump (dumper::MAPPER) && dump ("Mapper pending request:%s", end);
  else
    dump (dumper::MAPPER) && dump ("Mapper request:%s", buffer);
  end += actual;
  *end++ = '\n';
  if (!batching)
    {
      if (is_live () && end - buffer != write (fd_to, buffer, end - buffer))
	error_at (loc, "failed write to mapper %qs: %m", name);
      end = pos = buffer;
    }
}

/* Read a response from the mapper.  -ve -> end, 0 -> blank, +ve -> something*/

int
module_mapper::get_response (location_t loc)
{
  if (batching)
    pos = end + 1;
  else
    {
      gcc_assert (pos == end);
      size_t off = 0;
      bool bol = true;
      bool last = false;
      int stop = 0;

      if (is_live ())
	{
	  for (;;)
	    {
	      if (fd_to < 0)
		{
		  /* We're reading a file.  There can be no
		     continuations.  */
		  if (!fgets (buffer + off, size - off, from))
		    {
		      stop = feof (from) ? +1 : -1;
		      break;
		    }
		  off += strlen (buffer + off);
		  if (off && buffer[off - 1] == '\n')
		    break;
		}
	      else
		{
		  /* Reading a pipe or socket.  */
		  int bytes = read (fd_from, buffer + off, size - off - 1);
		  if (bytes <= 0)
		    {
		      stop = bytes ? -1 : +1;
		      break;
		    }
		  while (bytes)
		    {
		      if (bol)
			{
			  if (buffer[off] == '+')
			    batching = true;
			  else
			    last = true;
			}
		      bol = false;
		      if (char *eol
			  = (char *)memchr (buffer + off, '\n', size - off))
			{
			  bol = true;
			  unsigned nline = eol + 1 - buffer;
			  bytes -= nline - off;
			  off = nline;
			}
		      else
			{
			  off += bytes;
			  bytes = 0;
			  break;
			}
		    }
		  if (bol && last)
		    break;
		}
	      if (off + 1 == size)
		{
		  size *= 2;
		  buffer = XRESIZEVEC (char, buffer, size);
		}
	    }

	  if (stop)
	    {
	      if (stop < 0)
		error_at (loc, "failed read of mapper %qs: %m", name);
	      else if (is_server ())
		error_at (loc, "unexpected close from mapper %qs", name);
	      start = NULL;
	      return -1;
	    }

	  off--;
	}

      buffer[off] = 0;
      dump (dumper::MAPPER) && dump ("Mapper response:%s", buffer);
      end = buffer + off;
      pos = buffer;
    }

  for (;; pos = end + 1)
    {
      start = pos;
      end = NULL;
      if (*pos == '+')
	{
	  pos++;
	  end = strchr (pos, '\n');
	  if (end)
	    *end = 0;
	}

      if (!end)
	{
	  if (*pos == '-')
	    pos++;
	  end = pos + strlen (pos);
	  batching = false;
	}

      while (*pos && ISSPACE (*pos))
	pos++;

      if (*pos)
	return true;
      if (!batching)
	break;
    }

  return false;
}

void
module_mapper::response_unexpected (location_t loc)
{
  if (start)
    {
      /* Restore the whitespace we zapped tokenizing.  */
      for (char *ptr = start; ptr != pos; ptr++)
	if (!*ptr)
	  *ptr = ' ';
      error_at (loc, "mapper response malformed: %qs", start);
    }
  pos = end;
}

bool
module_mapper::response_eol (location_t loc, bool ignore)
{
  bool at_end = eol_p ();
  if (!at_end && !ignore)
    response_unexpected (loc);
  pos = end;
  return at_end;
}

char *
module_mapper::response_token (location_t loc, bool all)
{
  char *ptr = pos;

  if (ptr == end)
    {
      response_unexpected (loc);
      ptr = NULL;
    }
  else if (all)
    pos = end;
  else
    {
      char *eptr = ptr;
      while (eptr != end && !ISSPACE (*eptr))
	eptr++;

      if (eptr != end)
	{
	  *eptr++ = 0;
	  while (eptr != end && ISSPACE (*eptr))
	    eptr++;
	}
      pos = eptr;
    }

  return ptr;
}

int
module_mapper::response_word (location_t loc, const char *option, ...)
{
  if (const char *tok = response_token (loc))
    {
      va_list args;
      int count = 0;

      va_start (args, option);
      do
	{
	  if (!strcmp (option, tok))
	    {
	      va_end (args);
	      return count;
	    }
	  count++;
	  option = va_arg (args, const char *);
	}
      while (option);
      va_end (args);
      response_unexpected (loc);
    }
  return -1;
}

/*  Module mapper protocol non-canonical precis:

    HELLO version kind cookie
    	-> HELLO/ERROR response
    IMPORT module-name
    	-> OK bmipath
	-> ERROR
    EXPORT module-name
    	-> OK bmipath
    DONE module-name
    	No response
    RESET
        No response
 */

/* Start handshake.  */

bool
module_mapper::handshake (location_t loc, const char *cookie)
{
  send_command (loc, "HELLO %d GCC %s", MAPPER_VERSION, cookie);

  bool ok = get_response (loc) > 0;
  switch (response_word (loc, "HELLO", "ERROR", NULL))
    {
    default:
      ok = false;
      break;

    case 0: /* HELLO $ver $agent $repo */
      {
	const char *ver = response_token (loc);
	const char *agent = !eol_p () ? response_token (loc) : NULL;
	char *repo = !eol_p () ? response_token (loc, true) : NULL;

	if (ver)
	  dump () && dump ("Connected to mapper:%s version %s",
			   agent ? agent : "unknown", ver);
	if (response_eol (loc))
	  {
	    if (repo)
	      set_cmi_repo (repo);
	    ok = true;
	  }
      }
      break;

    case 1: /* ERROR $msg */
      error_at (loc, "mapper handshake failure: %s", response_error ());
      ok = false;
      break;
    }

  return ok;
}

/* IMPORT or EXPORT query.  */

void
module_mapper::imex_query (const module_state *state, bool exporting)
{
  send_command (state->from_loc, "%sPORT %s",
		exporting ? "EX" : "IM",
		state->get_flatname ());
}

/* Response to import/export query.  */

char *
module_mapper::cmi_response (const module_state *state)
{
  char *filename = NULL;

  switch (response_word (state->from_loc, "OK", "ERROR", NULL))
    {
    default:
      break;

    case 0: /* OK $bmifile  */
      filename = response_token (state->from_loc, true);
      filename = maybe_strip_cmi_prefix (filename);
      response_eol (state->from_loc);
      break;

    case 1: /* ERROR $msg */
      error_at (state->from_loc, "mapper cannot provide module %qs: %s",
		state->get_flatname (), response_error ());
      break;
    }

  return filename;
}

/* Import query.  */

char *
module_mapper::import_export (const module_state *state, bool export_p)
{
  module_mapper *mapper = get (state->from_loc);

  if (!mapper->is_server ())
    return NULL;

  timevar_start (TV_MODULE_MAPPER);
  mapper->imex_query (state, export_p);
  char *fname = mapper->imex_response (state);
  timevar_stop (TV_MODULE_MAPPER);

  return fname;
}

/* Export done.  */

bool
module_mapper::export_done (const module_state *state)
{
  bool ok = true;
  module_mapper *mapper = get (state->from_loc);

  if (mapper->is_server ())
    {
      timevar_start (TV_MODULE_MAPPER);
      dump (dumper::MAPPER) && dump ("Completed mapper");
      mapper->send_command (state->from_loc, "DONE %s",
			    state->get_flatname ());
      timevar_stop (TV_MODULE_MAPPER);
    }
  else
    ok = mapper->is_live ();

  return ok;
}

/* Include translation.  Query if PATH should be turned into a header
   import.  Return false if it should remain a #include, true
   otherwise.  */

bool
module_mapper::translate_include (location_t loc, const char *path, size_t len)
{
  bool xlate = false;

  timevar_start (TV_MODULE_MAPPER);
  if (mapper->is_server ())
    {
      send_command (loc, "INCLUDE %s", path);
      if (get_response (loc) <= 0)
	return false;

      switch (response_word (loc, "IMPORT", "TEXT", NULL))
	{
	default:
	  break;

	case 0:  /* Divert to import.  */
	  xlate = true;
	  break;

	case 1:  /* Treat as include.  */
	  break;
	}
      response_eol (loc);
    }
  else if (mapper->is_live ())
    {
      tree name = build_string (len, path);

      xlate = get_module_slot (name, NULL, false, false) != NULL;
    }
  timevar_stop (TV_MODULE_MAPPER);

  return xlate;
}

/* If THIS is the current purview, issue an import error and return false.  */

bool
module_state::check_not_purview (location_t loc)
{
  module_state *imp = (*modules)[0];
  if (imp && !imp->name)
    imp = imp->parent;
  if (imp == this)
    {
      /* Cannot import the current module.  */
      error_at (loc, "cannot import module %qs in its own purview",
		get_flatname ());
      inform (from_loc, "module %qs declared here", get_flatname ());
      return false;
    }
  return true;
}

/* Module name substitutions.  */
static vec<module_state *,va_heap> substs;

void
module_state::mangle ()
{
  if (subst)
    mangle_module_substitution (subst - 1);
  else
    {
      if (parent)
	parent->mangle ();
      if (!is_partition ())
	{
	  substs.safe_push (this);
	  subst = substs.length ();
	  mangle_identifier (name);
	}
    }
}

void
mangle_module (int mod)
{
  module_state *imp = (*modules)[mod];

  if (!imp->name)
    /* Set when importing the primary module interface.  */
    imp = imp->parent;

  imp->mangle ();
}

/* Clean up substitutions.  */
void
mangle_module_fini ()
{
  while (substs.length ())
    substs.pop ()->subst = 0;
}

/* Announce WHAT about the module.  */

void
module_state::announce (const char *what) const
{
  if (noisy_p ())
    {
      fprintf (stderr, mod < MODULE_LIMIT ? " %s:%s:%u" : " %s:%s",
	       what, get_flatname (), mod);
      fflush (stderr);
    }
}

/* A human-readable README section.  The contents of this section to
   not contribute to the CRC, so the contents can change per
   compilation.  That allows us to embed CWD, hostname, build time and
   what not.  It is a STRTAB that may be extracted with:
     readelf -pgnu.c++.README $(module).gcm */

void
module_state::write_readme (elf_out *to, const char *dialect,
			    unsigned extensions)
{
  bytes_out readme (to);

  readme.begin (false);

  readme.printf ("GNU C++ %smodule%s%s",
		 is_header () ? "header " : is_partition () ? "" : "primary ",
		 is_header () ? ""
		 : is_interface () ? " interface" : " implementation",
		 is_partition () ? " partition" : "");

  /* Compiler's version.  */
  readme.printf ("compiler: %s", version_string);

  /* Module format version.  */
  verstr_t string;
  version2string (MODULE_VERSION, string);
  readme.printf ("version: %s", string);

  /* Module information.  */
  readme.printf ("module: %s", get_flatname ());
  readme.printf ("source: %s", main_input_filename);
  readme.printf ("dialect: %s", dialect);
  if (extensions)
    readme.printf ("extensions: %s",
		   extensions & SE_OPENMP ? "-fopenmp" : "");

  /* The following fields could be expected to change between
     otherwise identical compilations.  Consider a distributed build
     system.  */
  if (char *cwd = getcwd (NULL, 0))
    {
      readme.printf ("cwd: %s", cwd);
      free (cwd);
    }
  readme.printf ("repository: %s", cmi_repo ? cmi_repo : ".");
#if NETWORKING
  {
    char hostname[64];
    if (!gethostname (hostname, sizeof (hostname)))
      readme.printf ("host: %s", hostname);
  }
#endif
  {
    /* This of course will change!  */
    time_t now = time (NULL);
    if (now != time_t (-1))
      {
	struct tm *time;

	time = gmtime (&now);
	readme.print_time ("build", time, "UTC");

#if defined (__USE_MISC) || defined (__USE_BSD) /* Is there a better way?  */
	time = localtime (&now);
	readme.print_time ("local", time, time->tm_zone);
#endif
      }
  }

  /* Its direct imports.  */
  for (unsigned ix = 1; ix < modules->length (); ix++)
    {
      module_state *state = (*modules)[ix];

      if (state->is_direct ())
	readme.printf ("%s: %s %s", state->exported_p ? "export" : "import",
		       state->get_flatname (), state->filename);
    }

  readme.end (to, to->name (MOD_SNAME_PFX ".README"), NULL);
}

/* Sort environment var names in reverse order.  */

static int
env_var_cmp (const void *a_, const void *b_)
{
  const unsigned char *a = *(const unsigned char *const *)a_;
  const unsigned char *b = *(const unsigned char *const *)b_;

  for (unsigned ix = 0; ; ix++)
    {
      bool a_end = !a[ix] || a[ix] == '=';
      if (a[ix] == b[ix])
	{
	  if (a_end)
	    break;
	}
      else
	{
	  bool b_end = !b[ix] || b[ix] == '=';

	  if (!a_end && !b_end)
	    return a[ix] < b[ix] ? +1 : -1;
	  if (a_end && b_end)
	    break;
	  return a_end ? +1 : -1;
	}
    }

  return 0;
}

/* Write the environment. It is a STRTAB that may be extracted with:
     readelf -pgnu.c++.ENV $(module).gcm */

void
module_state::write_env (elf_out *to)
{
  vec<const char *> vars;
  vars.create (20);

  extern char **environ;
  while (const char *var = environ[vars.length ()])
    vars.safe_push (var);
  vars.qsort (env_var_cmp);

  bytes_out env (to);
  env.begin (false);
  while (vars.length ())
    env.printf ("%s", vars.pop ());
  env.end (to, to->name (MOD_SNAME_PFX ".ENV"), NULL);

  vars.release ();
}

/* Write the direct or indirect imports.
   u:N
   {
     u:index
     s:name
     u32:crc
     s:filename (direct)
     u:exported (direct)
   } imports[N]
 */

void
module_state::write_imports (bytes_out &sec, bool direct)
{
  unsigned count = 0;

  for (unsigned ix = 1; ix < modules->length (); ix++)
    {
      module_state *imp = (*modules)[ix];

      if (imp->remap && imp->is_direct () == direct)
	count++;
    }

  gcc_assert (!direct || count);

  sec.u (count);
  for (unsigned ix = 1; ix < modules->length (); ix++)
    {
      module_state *imp = (*modules)[ix];

      if (imp->remap && imp->is_direct () == direct)
	{
	  dump () && dump ("Writing %simport:%u->%u %M (crc=%x)",
			   !direct ? "indirect "
			   : imp->exported_p ? "exported " : "",
			   ix, imp->remap, imp, imp->crc);
	  sec.u (imp->remap);
	  sec.str (imp->get_flatname ());
	  sec.u32 (imp->crc);
	  if (direct)
	    {
	      write_location (sec, imp->from_loc);
	      sec.str (imp->filename);
	      sec.u (imp->exported_p);
	    }
	}
    }
}

/* READER, LMAPS  != NULL == direct imports,
   == NUL == indirect imports.  */

unsigned
module_state::read_imports (bytes_in &sec, cpp_reader *reader, line_maps *lmaps)
{
  unsigned count = sec.u ();
  unsigned loaded = 0;

  while (count--)
    {
      unsigned ix = sec.u ();
      if (ix >= slurp->remap->length () || !ix || (*slurp->remap)[ix])
	{
	  sec.set_overrun ();
	  break;
	}

      const char *name = sec.str (NULL);
      module_state *imp = get_module (name);
      unsigned crc = sec.u32 ();
      bool exported = false;

      /* If the import is a partition, it must be the same primary
	 module as this TU.  */
      if (imp && imp->is_partition () &&
	  (!named_module_p ()
	   || (get_primary ((*modules)[0]) != get_primary (imp))))
	imp = NULL;

      if (!imp)
	sec.set_overrun ();
      if (sec.get_overrun ())
	break;

      if (lmaps)
	{
	  /* A direct import, maybe load it.  */
	  location_t floc = read_location (sec);
	  const char *fname = sec.str (NULL);
	  exported = sec.u ();

	  if (sec.get_overrun ())
	    break;

	  if (!imp->check_not_purview (loc))
	    continue;

	  if (imp->is_detached ())
	    imp->attach (floc);

	  if (!imp->is_imported ())
	    {
	      unsigned n = dump.push (imp);
	      imp->maybe_create_loc ();
	      imp->crc = crc;

	      if (imp->filename)
		fname = NULL;
	      else if (!fname[0])
		fname = module_mapper::import_export (imp, false);

	      if (imp->mod == MODULE_UNKNOWN_PARTITION)
		{
		  /* Must import the partition now, as inter-module
		     references from the partition we must be in
		     require it.  The deduping machinery better be
		     working ...  */
		  dump () && dump ("Importing elided partition %M", imp);
		  gcc_assert (imp->is_partition () && is_partition ());
		  imp->mod = MODULE_UNKNOWN;
		}

	      if (!imp->do_import (fname, reader))
		imp = NULL;
	      dump.pop (n);
	      if (!imp)
		continue;
	    }

	  if (is_partition () && !imp->is_partition ())
	    imp->from_partition_p = true;
	}
      else
	{
	  /* An indirect import, find it, it should already be here.  */
	  if (imp->is_detached ())
	    {
	      error_at (loc, "indirect import %qs is not already loaded", name);
	      continue;
	    }
	}

      if (imp->crc != crc)
	error_at (loc, "import %qs has CRC mismatch", imp->get_flatname ());

      (*slurp->remap)[ix] = imp->mod;
      if (lmaps)
	set_import (imp, exported);
      dump () && dump ("Found %simport:%u %M->%u", !lmaps ? "indirect "
		       : exported ? "exported " : "", ix, imp,
		       imp->mod);
      loaded++;
    }

  return loaded;
}

/* Write the import table to MOD_SNAME_PFX.imp.  */

void
module_state::write_imports (elf_out *to, unsigned *crc_ptr)
{
  dump () && dump ("Writing imports");
  dump.indent ();

  bytes_out sec (to);
  sec.begin ();

  write_imports (sec, true);
  write_imports (sec, false);

  sec.end (to, to->name (MOD_SNAME_PFX ".imp"), crc_ptr);
  dump.outdent ();
}

bool
module_state::read_imports (cpp_reader *reader, line_maps *lmaps)
{
  bytes_in sec;

  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".imp"))
    return false;

  dump () && dump ("Reading %u imports", slurp->remap->length () - 1);
  dump.indent ();

  /* Read the imports.  */
  unsigned direct = read_imports (sec, reader, lmaps);
  unsigned indirect = read_imports (sec, NULL, NULL);
  if (direct + indirect + 1 != slurp->remap->length ())
    from ()->set_error (elf::E_BAD_IMPORT);

  dump.outdent ();
  if (!sec.end (from ()))
    return false;
  return true;
}

/* We're the primary module interface, but have partitions.  Document
   them so that non-partition module implementation units know which
   have already been loaded.  */

void
module_state::write_partitions (elf_out *to, unsigned count, unsigned *crc_ptr)
{
  dump () && dump ("Writing %u elided partitions", count);
  dump.indent ();

  bytes_out sec (to);
  sec.begin ();

  for (unsigned ix = 1; ix != modules->length (); ix++)
    {
      module_state *imp = (*modules)[ix];
      if (imp->is_partition ())
	{
	  dump () && dump ("Writing elided partition %M (crc=%x)",
			   imp, imp->crc);
	  sec.str (imp->get_flatname ());
	  sec.u32 (imp->crc);
	  write_location (sec,
			  imp->is_direct () ? imp->from_loc : UNKNOWN_LOCATION);
	  sec.str (imp->filename);
	}
    }

  sec.end (to, to->name (MOD_SNAME_PFX ".prt"), crc_ptr);
  dump.outdent ();
}

bool
module_state::read_partitions (unsigned count)
{
  bytes_in sec;
  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".prt"))
    return false;

  dump () && dump ("Reading %u elided partitions", count);
  dump.indent ();

  while (count--)
    {
      const char *name = sec.str (NULL);
      unsigned crc = sec.u32 ();
      location_t floc = read_location (sec);
      const char *fname = sec.str (NULL);

      if (sec.get_overrun ())
	break;

      dump () && dump ("Reading elided partition %s (crc=%x)", name, crc);

      module_state *imp = get_module (name);
      if (!imp || !imp->is_partition () || !imp->is_detached ()
	  || get_primary (imp) != this)
	{
	  sec.set_overrun ();
	  break;
	}

      /* Attach the partition without loading it.  We'll have to load
	 for real if it's indirectly imported.  */
      imp->attach (floc);
      imp->crc = crc;
      // FIXME: Can't we use MODULE_UNKNOWN and imp->is_partition ()?
      imp->mod = MODULE_UNKNOWN_PARTITION; /* Mark as wierd.   */
      if (!imp->filename && fname[0])
	imp->filename = xstrdup (fname);
    }

  dump.outdent ();
  if (!sec.end (from ()))
    return false;
  return true;
}

/* Contents of a cluster.  */
enum cluster_tag {
  ct_decl,	/* A decl.  */
  ct_defn,	/* A definition.  */
  ct_bind,	/* A binding.  */
  ct_hwm
};

/* Declaration modifiers.  */
enum ct_decl_flags 
{
  cdf_is_defn = 0x1,		/* Has a definition.  */
  cdf_is_specialization = 0x2,  /* Some kind of specialization.  */
  cdf_is_partial = 0x4		/* A partial specialization.  */
};

/* Binding modifiers.  */
enum ct_bind_flags
{
  cbf_export = 0x1,	/* An exported decl.  */
  cbf_hidden = 0x2,	/* A hidden (friend) decl.  */
  cbf_using = 0x4,	/* A using decl.  */
  cbf_wrapped = 0x8,  	/* ... that is wrapped.  */
};

/* Write the cluster of depsets in SCC[0-SIZE).  */

unsigned
module_state::write_cluster (elf_out *to, depset *scc[], unsigned size,
			     depset::hash &table, unsigned &specializations,
			     unsigned &entities, unsigned *crc_ptr)
{
  dump () && dump ("Writing section:%u %u depsets", scc[0]->section, size);
  dump.indent ();

  trees_out sec (to, this, table, scc[0]->section);
  sec.begin ();

  /* Prepare, determine entity numbers   */
  dump (dumper::CLUSTER) && dump ("Cluster members:") && (dump.indent (), true);
  for (unsigned ix = 0; ix != size; ix++)
    {
      depset *b = scc[ix];

      switch (b->get_entity_kind ())
	{
	default:
	  gcc_unreachable ();

	case depset::EK_BINDING:
	  dump (dumper::CLUSTER)
	    && dump ("[%u]=%s %P", ix, b->entity_kind_name (),
		     b->get_entity (), b->get_name ());
	  for (unsigned jx = b->deps.length (); jx--;)
	    {
	      depset *dep = b->deps[jx];
	      gcc_checking_assert (dep->get_entity_kind () == depset::EK_USING
				   || TREE_VISITED (dep->get_entity ()));
	    }
	  break;

	case depset::EK_SPECIALIZATION:
	  ++specializations;
	  /* FALLTHROUGH  */

	case depset::EK_DECL:
	case depset::EK_UNNAMED:
	  b->cluster = ++entities;
	  sec.mark_declaration (b->get_entity (), b->has_defn ());
	  /* FALLTHROUGH  */

	case depset::EK_USING:
	  gcc_checking_assert (!b->is_unreached ());
	  dump (dumper::CLUSTER)
	    && dump ("[%u]=%s %s %N", ix, b->entity_kind_name (),
		     b->has_defn () ? "definition" : "declaration",
		     b->get_entity ());
	  break;
	}
    }
  dump (dumper::CLUSTER) && (dump.outdent (), true);

  depset *namer = NULL;

  /* Write things out.  The sorted order is DECK<SPEC<UNNAMED<BINDINGS
     -- see cluster_cmp.  I'm not totally sure this is robust, given
     the necessary merging of global module entities in the face of
     late return types of templates -- we must meet the containing
     function before something that uses its parms, so that the
     latter can be merged before the former.  It might be a more
     sophisticated sorting is needed along the lines of the earlier
     mergeable sort algorithm?  */
  for (unsigned ix = 0; ix != size; ix++)
    {
      depset *b = scc[ix];
      tree decl = b->get_entity ();
      int flags = 0;
      switch (b->get_entity_kind ())
	{
	default:
	  gcc_unreachable ();
	  break;

	case depset::EK_BINDING:
	  {
	    gcc_assert (TREE_CODE (decl) == NAMESPACE_DECL);
	    dump () && dump ("Depset:%u binding %C:%P", ix, TREE_CODE (decl),
			     decl, b->get_name ());
	    sec.u (ct_bind);
	    sec.tree_node (decl);
	    sec.tree_node (b->get_name ());

	    /* Write in reverse order, so reading will see the exports
	       first, thus building the overload chain will be
	       optimized.  */
	    for (unsigned jx = b->deps.length (); jx--;)
	      {
		depset *dep = b->deps[jx];
		tree decl = dep->get_entity ();
		unsigned flags = 0;
		if (dep->get_entity_kind () == depset::EK_USING)
		  {
		    flags |= cbf_using;
		    if (OVL_USING_P (decl))
		      flags |= cbf_wrapped;
		    if (OVL_EXPORT_P (decl))
		      flags |= cbf_export;
		    decl = OVL_FUNCTION (decl);
		  }
		else
		  {
		    /* An implicit typedef must be at zero.  */
		    gcc_assert (!DECL_IMPLICIT_TYPEDEF_P (decl) || !jx);
		    if (dep->is_hidden ())
		      flags |= cbf_hidden;
		    else if (DECL_MODULE_EXPORT_P (STRIP_TEMPLATE (decl)))
		      flags |= cbf_export;
		  }

		gcc_checking_assert (DECL_P (decl));

		sec.i (flags);
		sec.tree_node (decl);
	      }

	    /* Terminate the list.  */
	    sec.i (-1);
	  }
	  break;

	case depset::EK_USING:
	  dump () && dump ("Depset:%u %s %C:%N", ix, b->entity_kind_name (),
			   TREE_CODE (decl), decl);
	  break;

	case depset::EK_SPECIALIZATION:
	  flags |= cdf_is_specialization;
	  if (b->is_partial ())
	    flags |= cdf_is_partial;
	  /* FALLTHROUGH.  */

	case depset::EK_UNNAMED:
	case depset::EK_DECL:
	  dump () && dump ("Depset:%u %s entity:%u %C:%N", ix,
			   b->entity_kind_name (), b->cluster - 1,
			   TREE_CODE (decl), decl);

	  sec.u (ct_decl);
	  sec.tree_node (decl);
	  sec.u (flags);

	  gcc_checking_assert (b->cluster);
	  sec.u (b->cluster - 1);

	  /* Add it to the entity map, such that we can tell it is
	     part of us.  */
	  bool existed;
	  unsigned *slot = &entity_map->get_or_insert
	    (DECL_UID (decl), &existed);
	  if (existed)
	    /* If it existed, it should match.  */
	    gcc_checking_assert (decl == (*entity_ary)[*slot]);
	  *slot = -b->cluster;

	  dump () && dump ("Wrote declaration entity:%u %C:%N",
			   b->cluster - 1, TREE_CODE (decl), decl);

	  if (!namer)
	    namer = b;

	  if (b->has_defn ())
	    {
	      sec.u (ct_defn);
	      sec.tree_node (decl);
	      dump () && dump ("Writing definition %N", decl);
	      sec.write_definition (decl);

	      /* Is this a good enough human name?  */
	      if (!namer->has_defn ())
		namer = b;
	    }
	  break;
	}
    }

  /* We don't find the section by name.  Use depset's decl's name for
     human friendliness.  */
  unsigned name = 0;
  tree naming_decl = NULL_TREE;
  if (namer)
    {
      naming_decl = namer->get_entity ();
      if (namer->get_entity_kind () == depset::EK_USING)
	/* This unfortunately names the section from the target of the
	   using decl.  But the name is only a guide, so Do Not Care.  */
	naming_decl = OVL_FUNCTION (naming_decl);
      if (DECL_IMPLICIT_TYPEDEF_P (naming_decl))
	/* Lose any anonymousness.  */
	naming_decl = TYPE_NAME (TREE_TYPE (naming_decl));
      name = to->qualified_name (naming_decl, namer->has_defn ());
    }

  unsigned bytes = sec.pos;
  unsigned snum = sec.end (to, name, crc_ptr);

  for (unsigned ix = size; ix--;)
    gcc_checking_assert (scc[ix]->section == snum);

  dump.outdent ();
  dump () && dump ("Wrote section:%u named-by:%N", scc[0]->section, naming_decl);

  return bytes;
}

// FIXME: when DECL didn't go via match_mergeable_specialization we'll
// need to add it to the hash table too.  */

static void
install_specialization (tree decl, bool is_partial)
{
  // FIXME: see note about most_general_template.  Perhaps we should
  // be explicitly writing it?
  int use;
  tree args = NULL_TREE;
  tree tpl = decl;
  while (tree ti = node_template_info (tpl, use))
    {
      if (!args)
	args = TI_ARGS (ti);
      tpl = TI_TEMPLATE (ti);
    }

  if (is_partial)
    {
      /* Add onto DECL_TEMPLATE_SPECIALIZATIONS.  */
      tree specs = tree_cons (args, decl, DECL_TEMPLATE_SPECIALIZATIONS (tpl));
      TREE_TYPE (specs) = TREE_TYPE (DECL_TEMPLATE_RESULT (decl));
      DECL_TEMPLATE_SPECIALIZATIONS (tpl) = specs;
      dump (dumper::MERGE) &&
	dump ("Adding partial specialization %N to %N", decl,
	      TREE_TYPE (DECL_TEMPLATE_RESULT (tpl)));
    }

  /* Add onto DECL_TEMPLATE_INSTANTIATIONS.  */
  // FIXME:do it
}

/* Read a cluster from section SNUM.  */

bool
module_state::read_cluster (unsigned snum)
{
  trees_in sec (this);

  if (!sec.begin (loc, from (), snum))
    return false;

  dump () && dump ("Reading section:%u", snum);
  dump.indent ();

  while (!sec.get_overrun () && sec.more_p ())
    {
      unsigned ct = sec.u ();
      switch (ct)
	{
	default:
	  sec.set_overrun ();
	  break;

	case ct_bind:
	  /* A set of namespace bindings.  */
	  {
	    tree ns = sec.tree_node ();
	    tree name = sec.tree_node ();
	    tree decls = NULL_TREE;
	    tree visible = NULL_TREE;
	    tree type = NULL_TREE;
	    bool dedup = (TREE_PUBLIC (ns)
			  && (is_primary ()
			      || is_partition ()
			      || is_header ()));

	    /* We rely on the bindings being in the reverse order of
	       the resulting overload set.  */
	    for (;;)
	      {
		int flags = sec.i ();
		if (flags < 0)
		  break;

		if ((flags & cbf_hidden)
		    && (flags & (cbf_using | cbf_export)))
		  sec.set_overrun ();

		tree decl = sec.tree_node ();
		if (sec.get_overrun ())
		  break;

		if (decls && TREE_CODE (decl) == TYPE_DECL)
		  {
		    /* Stat hack.  */
		    if (type || !DECL_IMPLICIT_TYPEDEF_P (decl))
		      sec.set_overrun ();
		    type = decl;
		  }
		else
		  {
		    if (decls
			|| (flags & (cbf_hidden | cbf_wrapped))
			|| (dedup && TREE_CODE (decl) == FUNCTION_DECL)
			|| DECL_FUNCTION_TEMPLATE_P (decl))
		      {
			decls = ovl_make (decl, decls);
			if (flags & cbf_using)
			  {
			    dedup = true;
			    OVL_USING_P (decls) = true;
			    if (flags & cbf_export)
			      OVL_EXPORT_P (decls) = true;
			  }

			if (flags & cbf_hidden)
			  OVL_HIDDEN_P (decls) = true;
			else if (dedup)
			  OVL_DEDUP_P (decls) = true;
		      }
		    else
		      decls = decl;

		    if (flags & cbf_export)
		      visible = decls;
		  }
	      }

	    if (!decls)
	      sec.set_overrun ();

	    if (sec.get_overrun ())
	      break; /* Bail.  */

	    if (is_primary () || is_partition ())
	      visible = decls;

	    dump () && dump ("Binding of %P", ns, name);
	    if (!set_module_binding (ns, name, mod,
				     is_primary () || is_partition (),
				     decls, type, visible))
	      sec.set_overrun ();

	    if (type
		&& CP_DECL_CONTEXT (type) == ns
		&& sec.get_dupness (type) < trees_in::DUP_dup)
	      add_module_decl (ns, name, type);

	    for (ovl_iterator iter (decls); iter; ++iter)
	      if (!iter.using_p ())
		{
		  tree decl = *iter;
		  if (CP_DECL_CONTEXT (decl) == ns
		      && sec.get_dupness (decl) < trees_in::DUP_dup)
		    add_module_decl (ns, name, decl);
		}
	  }
	  break;

	case ct_decl:
	  /* A decl.  */
	  {
	    tree decl = sec.tree_node ();
	    dump () && dump ("Read declaration of %N", decl);

	    unsigned flags = sec.u ();
	    unsigned entity_index = sec.u ();

	    if (entity_index >= entity_num)
	      sec.set_overrun ();
	    if (sec.get_overrun ())
	      break;

	    {
	      /* Insert into the entity array.  */
	      mc_slot *slot = &(*entity_ary)[entity_lwm + entity_index];
	      if (!slot->is_lazy () || slot->get_lazy () != snum)
		{
		  sec.set_overrun ();
		  break;
		}
	      (*slot) = decl;
	    }

	    /* If we matched a decl from this TU, it might not be an
	       import!  */
	    if (DECL_LANG_SPECIFIC (decl) && DECL_MODULE_IMPORT_P (decl))
	      {
		/* Insert into the entity hash (it might already be
		   there.  */
		// FIXME: Until we get to write out the current
		// module, we only need namespace-scope decls here, as
		// those are the only things users need the
		// originating module for.  When writing out, we need
		// all imported entities so we can directly refer to
		// their index number.
		bool existed;
		unsigned *slot = &entity_map->get_or_insert
		  (DECL_UID (decl), &existed);
		if (!existed)
		  *slot = entity_lwm + entity_index;
		else
		  /* If it existed, it should match.  */
		  gcc_checking_assert (decl == (*entity_ary)[*slot]);
		}

	    if (flags & cdf_is_specialization)
	      install_specialization (decl, flags & cdf_is_partial);
	  }
	  break;

	case ct_defn:
	  {
	    tree decl = sec.tree_node ();
	    dump () && dump ("Reading definition of %N", decl);
	    sec.read_definition (decl);
	  }
	  break;
	}
    }

  /* When lazy loading is in effect, we can be in the middle of
     parsing or instantiating a function.  Save it away.
     push_function_context does too much work.   */
  tree old_cfd = current_function_decl;
  struct function *old_cfun = cfun;
  while (tree decl = sec.post_process ())
    {
      bool abstract = false;
      if (TREE_CODE (decl) == TEMPLATE_DECL)
	{
	  abstract = true;
	  decl = DECL_TEMPLATE_RESULT (decl);
	}

      current_function_decl = decl;
      allocate_struct_function (decl, abstract);
      cfun->language = ggc_cleared_alloc<language_function> ();
      cfun->language->base.x_stmt_tree.stmts_are_full_exprs_p = 1;

      if (abstract)
	;
      else if (DECL_ABSTRACT_P (decl))
	{
	  bool cloned = maybe_clone_body (decl);
	  if (!cloned)
	    from ()->set_error ();
	}
      else
	{
	  if (DECL_COMDAT (decl))
	    comdat_linkage (decl);
	  note_vague_linkage_fn (decl);
	  cgraph_node::finalize_function (decl, true);
	}

    }
  /* Look, function.c's interface to cfun does too much for us, we
     just need to restore the old value.  I do not want to go
     redesigning that if right now.  */
#undef cfun
  cfun = old_cfun;
  current_function_decl = old_cfd;

  dump.outdent ();
  dump () && dump ("Read section:%u", snum);

  loaded_clusters++;

  if (!sec.end (from ()))
    return false;

  return true;
}

/* SPACES is a sorted vector of namespaces.  Write out the namespaces
   to MOD_SNAME_PFX.nms section.

   Each namespace is:
     u:name,
     u:context, number of containing namespace (0 == ::)
     u:inline_p/export_p/public_p  */

void
module_state::write_namespaces (elf_out *to, depset::hash &table,
				vec<depset *> spaces,
				unsigned *crc_p)
{
  dump () && dump ("Writing namespaces");
  dump.indent ();

  bytes_out sec (to);
  sec.begin ();

  for (unsigned ix = 0; ix != spaces.length (); ix++)
    {
      depset *b = spaces[ix];
      tree ns = b->get_entity ();

      gcc_checking_assert (TREE_CODE (ns) == NAMESPACE_DECL);

      b->section = ix + 1;
      unsigned ctx_num = 0;
      tree ctx = CP_DECL_CONTEXT (ns);
      if (ctx != global_namespace)
	ctx_num = table.find_entity (ctx)->section;
      bool export_p = DECL_MODULE_EXPORT_P (ns);
      bool inline_p = DECL_NAMESPACE_INLINE_P (ns);
      bool public_p = TREE_PUBLIC (ns);

      /* We should only be naming public namespaces, or our own
	 private ones.  */
      gcc_checking_assert (public_p || !DECL_MODULE_ORIGIN (ns));
      unsigned flags = 0;
      if (export_p)
	flags |= 1;
      if (inline_p)
	flags |= 2;
      if (public_p)
	flags |= 4;
      dump () && dump ("Writing namespace %u %N%s%s%s, parent:%u",
		       b->section, ns, export_p ? ", export" : "",
		       public_p ? ", public" : "",
		       inline_p ? ", inline" : "", ctx_num);

      sec.u (to->name (DECL_NAME (ns)));
      if (!DECL_NAME (ns))
	{
	  gcc_checking_assert (DECL_ASSEMBLER_NAME_SET_P (ns));
	  sec.u (to->name (DECL_ASSEMBLER_NAME_RAW (ns)));
	}
      sec.u (ctx_num);
      /* Don't use bools, because this can be near the end of the
	 section, and it won't save anything anyway.  */
      sec.u (flags);
      write_location (sec, (TREE_PUBLIC (ns)
			    ? UNKNOWN_LOCATION : DECL_SOURCE_LOCATION (ns)));
    }

  sec.end (to, to->name (MOD_SNAME_PFX ".nms"), crc_p);
  dump.outdent ();
}

/* Read the namespace hierarchy from MOD_SNAME_PFX.namespace.  Fill in
   SPACES from that data.  */

vec<tree>
module_state::read_namespaces ()
{
  bytes_in sec;
  vec<tree> spaces;

  spaces.create (100);
  
  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".nms"))
    return spaces;

  dump () && dump ("Reading namespaces");
  dump.indent ();

  spaces.safe_push (global_namespace);
  while (sec.more_p ())
    {
      unsigned name = sec.u ();
      unsigned anon_name = name ? 0 : sec.u ();
      unsigned parent = sec.u ();
      /* See comment in write_namespace about why not bits.  */
      unsigned flags = sec.u ();
      location_t src_loc = read_location (sec);

      if (parent >= spaces.length ())
	sec.set_overrun ();
      if (sec.get_overrun ())
	break;

      tree id = name ? get_identifier (from ()->name (name)) : NULL_TREE;
      tree anon_id = anon_name
	? get_identifier (from ()->name (anon_name)) : NULL_TREE;
      bool public_p = flags & 4;
      bool inline_p = flags & 2;
      bool export_p = flags & 1;

      dump () && dump ("Read namespace %P%s%s%s, %u",
		       spaces[parent], id, export_p ? ", export" : "",
		       public_p ? ", public" : "",
		       inline_p ? ", inline" : "", spaces.length ());
      bool visible_p = (export_p
			|| (public_p && (is_partition () || is_primary ())));
      tree inner = add_imported_namespace (spaces[parent], id, mod,
					   src_loc, visible_p, inline_p,
					   anon_id);
      if (export_p && is_partition ())
	DECL_MODULE_EXPORT_P (inner) = true;

      spaces.safe_push (inner);
    }
  dump.outdent ();

  if (!sec.end (from ()))
    spaces.truncate (0);

  return spaces;
}

/* Write the binding TABLE to MOD_SNAME_PFX.bind

   Each binding is:
     u:name
     u:context - number of containing namespace
     u:section - section number of binding. */

unsigned
module_state::write_bindings (elf_out *to, vec<depset *> sccs,
			      depset::hash &table, unsigned *crc_p)
{
  dump () && dump ("Writing binding table");
  dump.indent ();

  unsigned num = 0;
  bytes_out sec (to);
  sec.begin ();

  for (unsigned ix = 0; ix != sccs.length (); ix++)
    {
      depset *b = sccs[ix];
      if (b->is_binding ())
	{
	  unsigned ns_num = 0;
	  tree ns = b->get_entity ();
	  if (ns != global_namespace)
	    ns_num = table.find_entity (ns)->section;
	  dump () && dump ("Bindings %P section:%u", ns, b->get_name (),
			   b->section);
	  sec.u (to->name (b->get_name ()));
	  sec.u (ns_num);
	  sec.u (b->section);
	  num++;
	}
    }

  sec.end (to, to->name (MOD_SNAME_PFX ".bnd"), crc_p);
  dump.outdent ();

  return num;
}

/* Read the binding table from MOD_SNAME_PFX.bind.  */

bool
module_state::read_bindings (vec<tree> spaces, unsigned num,
			     const range_t &range)
{
  bytes_in sec;

  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".bnd"))
    return false;

  dump () && dump ("Reading binding table");
  dump.indent ();
  for (; !sec.get_overrun () && num--;)
    {
      const char *name = from ()->name (sec.u ());
      unsigned nsnum = sec.u ();
      unsigned snum = sec.u ();

      if (nsnum >= spaces.length () || !name
	  || snum < range.first || snum >= range.second)
	sec.set_overrun ();
      if (!sec.get_overrun ())
	{
	  tree ctx = spaces[nsnum];
	  tree id = get_identifier (name);
	  dump () && dump ("Bindings %P section:%u", ctx, id, snum);
	  if (mod && !import_module_binding (ctx, id, mod, snum))
	    break;
	}
    }

  dump.outdent ();
  if (!sec.end (from ()))
    return false;
  return true;
}

/* Write the entity table to MOD_SNAME_PFX.ent

   Each entry is a section number.  */

void
module_state::write_entities (elf_out *to, vec<depset *> depsets,
			      depset::hash &table,
			      unsigned count, unsigned *crc_p)
{
  dump () && dump ("Writing entites");
  dump.indent ();

  trees_out sec (to, this, table);
  sec.begin ();

  unsigned current = 0;
  for (unsigned ix = 0; ix < depsets.length (); ix++)
    {
      depset *d = depsets[ix];

      if (d->cluster)
	{
	  current++;

	  gcc_checking_assert (!d->is_unreached ()
			       && d->cluster == current);
	  sec.u (d->section);
	}
      }
  gcc_assert (count == current);
  sec.end (to, to->name (MOD_SNAME_PFX ".ent"), crc_p);
  dump.outdent ();
}

bool
module_state::read_entities (unsigned count, const range_t &range)
{
  trees_in sec (this);

  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".ent"))
    return false;

  dump () && dump ("Reading entities");
  dump.indent ();

  vec_safe_reserve (entity_ary, count);
  unsigned ix;
  for (ix = 0; ix != count; ix++)
    {
      unsigned snum = sec.u ();
      if (snum < range.first || snum >= range.second)
	sec.set_overrun ();
      if (sec.get_overrun ())
	break;

      mc_slot slot;
      slot.u.binding = NULL_TREE;
      slot.set_lazy (snum);
      entity_ary->quick_push (slot);
    }
  entity_num = ix;

  dump.outdent ();
  if (!sec.end (from ()))
    return false;
  return true;
}

/* Write the unnamed table to MOD_SNAME_PFX.spc

   Each entry is a section number, key-locator tuple.
   Keys are so specialiazations can be loaded when instantiating the
   thing they're keyed to.  */
// FIXME: Should we coalesce according to key?
void
module_state::write_specializations (elf_out *to, vec<depset *> depsets,
				     depset::hash &table,
				     unsigned count, unsigned *crc_p)
{
  dump () && dump ("Writing specializations");
  dump.indent ();

  trees_out sec (to, this, table);
  sec.begin ();

  for (unsigned ix = 0; ix < depsets.length (); ix++)
    {
      depset *d = depsets[ix];
      if (d->get_entity_kind () == depset::EK_SPECIALIZATION)
	{
	  tree spec = d->get_entity ();
	  tree key = get_originating_module_decl (spec);
	  unsigned origin = (DECL_LANG_SPECIFIC (key)
			     ? DECL_MODULE_ORIGIN (key) : 0);
	  module_state *import = (*modules)[origin];

	  unsigned kind = 0;
	  if (!import->is_header ())
	    kind = import->is_partition () ? 1 : 2;

	  tree ctx = CP_DECL_CONTEXT (key);
	  gcc_checking_assert (TREE_CODE (ctx) == NAMESPACE_DECL);
	  sec.tree_node (ctx);
	  sec.tree_node (DECL_NAME (key));
	  sec.u (kind);
	  sec.u (d->cluster - 1);
	  dump () && dump ("Specialization %N entity:%u keyed to %N (%u)",
			   spec, d->cluster - 1, key, kind);
	  count--;
	}
      }
  gcc_assert (!count);
  sec.end (to, to->name (MOD_SNAME_PFX ".spc"), crc_p);
  dump.outdent ();
}

bool
module_state::read_specializations (unsigned count)
{
  trees_in sec (this);

  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".spc"))
    return false;

  dump () && dump ("Reading specializastions");
  dump.indent ();

  for (unsigned ix = 0; ix != count; ix++)
    {
      tree ns = sec.tree_node ();
      tree id = sec.tree_node ();
      unsigned kind = sec.u ();
      unsigned index = sec.u ();

      if (kind > 2 || index >= entity_num)
 	sec.set_overrun ();
       if (sec.get_overrun ())
 	break;

      /* It's now a regular import kind, if it's not part of the
	 same module.  */
      if (kind == 1
	  && !(is_primary () || is_partition ()))
	kind = 2;
      dump () && dump ("Specialization key %P (%u) entity:%u",
		       ns, id, kind, index);
      if (specset::table->add (ns, id, index + entity_lwm))
	if (!note_pending_specializations (ns, id, kind))
	  sec.set_overrun ();
    }

  dump.outdent ();
  if (!sec.end (from ()))
    return false;
  return true;
}

/* Read & write locations.  */
enum loc_kind {
  LK_ORDINARY,
  LK_MACRO,
  LK_ADHOC,
  LK_IMPORT_ORDINARY,
  LK_IMPORT_MACRO
};

static const module_state *
module_for_ordinary_loc (location_t loc)
{
  unsigned pos = 1;
  unsigned len = modules->length () - pos;

  while (len)
    {
      unsigned half = len / 2;
      module_state *probe = (*modules)[pos + half];
      if (loc < probe->ordinary_locs.first)
	len = half;
      else if (loc < probe->ordinary_locs.second)
	return probe;
      else
	{
	  pos += half + 1;
	  len = len - (half + 1);
	}
    }

  return NULL;
}

static const module_state *
module_for_macro_loc (location_t loc)
{
  unsigned pos = 1;
  unsigned len = modules->length () - pos;

  while (len)
    {
      unsigned half = len / 2;
      module_state *probe = (*modules)[pos + half];
      if (loc >= probe->macro_locs.second)
	len = half;
      else if (loc >= probe->macro_locs.first)
	return probe;
      else
	{
	  pos += half + 1;
	  len = len - (half + 1);
	}
    }

  return NULL;
}

/* If we're not streaming, record that we need location LOC.
   Otherwise stream it.  */

void
module_state::write_location (bytes_out &sec, location_t loc)
{
  if (!sec.streaming_p ())
    // FIXME: Implement optimization
    return;

  if (IS_ADHOC_LOC (loc))
    {
      dump (dumper::LOCATION) && dump ("Adhoc location");
      sec.u (LK_ADHOC);
      location_t locus = get_location_from_adhoc_loc (line_table, loc);
      write_location (sec, locus);
      source_range range = get_range_from_loc (line_table, loc);
      if (range.m_start == locus)
	/* Compress.  */
	range.m_start = UNKNOWN_LOCATION;
      write_location (sec, range.m_start);
      write_location (sec, range.m_finish);
    }
  else if (IS_MACRO_LOC (loc))
    {
      if (const loc_spans::span *span = spans.macro (loc))
	{
	  unsigned off = MAX_LOCATION_T - loc;

	  off -= span->macro_delta;

	  sec.u (LK_MACRO);
	  sec.u (off);
	  dump (dumper::LOCATION)
	    && dump ("Macro location %u output %u", loc, off);
	}
      else if (const module_state *import = module_for_macro_loc (loc))
	{
	  unsigned off = import->macro_locs.second - loc - 1;
	  sec.u (LK_IMPORT_MACRO);
	  sec.u (import->remap);
	  sec.u (off);
	  dump (dumper::LOCATION)
	    && dump ("Imported macro location %u output %u:%u",
		     loc, import->remap, off);
	}
      else
	gcc_unreachable ();
    }
  else if (IS_ORDINARY_LOC (loc))
    {
      if (const loc_spans::span *span = spans.ordinary (loc))
	{
	  unsigned off = loc;

	  off += span->ordinary_delta;
	  sec.u (LK_ORDINARY);
	  sec.u (off);

	  dump (dumper::LOCATION)
	    && dump ("Ordinary location %u output %u", loc, off);
	}
      else if (const module_state *import = module_for_ordinary_loc (loc))
	{
	  unsigned off = loc - import->ordinary_locs.first;
	  sec.u (LK_IMPORT_ORDINARY);
	  sec.u (import->remap);
	  sec.u (off);
	  dump (dumper::LOCATION)
	    && dump ("Imported ordinary location %u output %u:%u",
		     import->remap, import->remap, off);
	}
      else
	gcc_unreachable ();
    }
  else
    gcc_unreachable ();
}

location_t
module_state::read_location (bytes_in &sec) const
{
  location_t locus = UNKNOWN_LOCATION;
  unsigned kind = sec.u ();
  switch (kind)
     {
    default:
      sec.set_overrun ();
      break;

     case LK_ADHOC:
      {
	dump (dumper::LOCATION) && dump ("Adhoc location");
	locus = read_location (sec);
	source_range range;
	range.m_start = read_location (sec);
	if (range.m_start == UNKNOWN_LOCATION)
	  range.m_start = locus;
	range.m_finish = read_location (sec);
	if (locus != loc && range.m_start != loc && range.m_finish != loc)
	  locus = get_combined_adhoc_loc (line_table, locus, range, NULL);
      }
      break;

    case LK_MACRO:
      {
	unsigned off = sec.u ();
	location_t adjusted = MAX_LOCATION_T - off;

	adjusted -= slurp->loc_deltas.second;
	if (adjusted < macro_locs.first)
	  sec.set_overrun ();
	else if (adjusted < macro_locs.second)
	  locus = adjusted;
	else
	  sec.set_overrun ();
	dump (dumper::LOCATION)
	  && dump ("Macro %u becoming %u", off, locus);
      }
      break;

    case LK_ORDINARY:
      {
	unsigned off = sec.u ();
	location_t adjusted = off;

	adjusted += slurp->loc_deltas.first;
	if (adjusted >= ordinary_locs.second)
	  sec.set_overrun ();
	else if (adjusted >= ordinary_locs.first)
	  locus = adjusted;
	else if (adjusted < spans.main_start ())
	  locus = off;

	dump (dumper::LOCATION)
	  && dump ("Ordinary location %u becoming %u", off, locus);
      }
      break;

     case LK_IMPORT_MACRO:
     case LK_IMPORT_ORDINARY:
       {
	 unsigned mod = slurp->remap_module (sec.u ());
	 unsigned off = sec.u ();

	 if (!mod)
	   sec.set_overrun ();
	 else
	   {
	     const module_state *import = (*modules)[mod];
	     if (kind == LK_IMPORT_MACRO)
	       {
		 if (off < import->macro_locs.second - macro_locs.first)
		   locus = import->macro_locs.second - off - 1;
		 else
		   sec.set_overrun ();
	       }
	     else
	       {
		 if (off < (import->ordinary_locs.second
			    - import->ordinary_locs.first))
		   locus = import->ordinary_locs.first + off;
		 else
		   sec.set_overrun ();
	       }
	   }
       }
       break;
    }

  return locus;
}

/* Prepare the span adjustments.  */
// FIXME: The location streaming does not consider running out of
// locations in either the module interface, nor in the importers.
// At least we fail with a hard error though.

location_map_info
module_state::prepare_maps ()
{
  dump () && dump ("Preparing locations");
  dump.indent ();

  dump () && dump ("Reserved locations [%u,%u) macro [%u,%u)",
		   spans[loc_spans::SPAN_RESERVED].ordinary.first,
		   spans[loc_spans::SPAN_RESERVED].ordinary.second,
		   spans[loc_spans::SPAN_RESERVED].macro.first,
		   spans[loc_spans::SPAN_RESERVED].macro.second);

  location_map_info info;

  info.num_maps.first = info.num_maps.second = 0;

  /* Figure the alignment of ordinary location spans.  */
  unsigned max_range = 0;
  for (unsigned ix = loc_spans::SPAN_FIRST; ix != spans.length (); ix++)
    {
      loc_spans::span &span = spans[ix];
      line_map_ordinary const *omap
	= linemap_check_ordinary (linemap_lookup (line_table,
						  span.ordinary.first));

      /* We should exactly match up.  */
      gcc_checking_assert (MAP_START_LOCATION (omap) == span.ordinary.first);

      line_map_ordinary const *fmap = omap;
      for (; MAP_START_LOCATION (omap) < span.ordinary.second; omap++)
	{
	  /* We should never find a module linemap in an interval.  */
	  gcc_checking_assert (!MAP_MODULE_P (omap));

	  if (max_range < omap->m_range_bits)
	    max_range = omap->m_range_bits;
	}

      unsigned count = omap - fmap;
      info.num_maps.first += count;

      if (span.macro.first != span.macro.second)
	{
	  count = linemap_lookup_macro_index (line_table, span.macro.first) + 1;
	  count -= linemap_lookup_macro_index (line_table,
					       span.macro.second - 1);
	  dump (dumper::LOCATION) && dump ("Span:%u %u macro maps", ix, count);
	  info.num_maps.second += count;
	}
    }

  /* Adjust the maps.  Ordinary ones ascend, and we must maintain
     alignment.  Macro ones descend, but are unaligned.  */
  location_t ord_off = spans[loc_spans::SPAN_FIRST].ordinary.first;
  location_t mac_off = spans[loc_spans::SPAN_FIRST].macro.second;
  location_t range_mask = (1u << max_range) - 1;

  dump () && dump ("Ordinary maps range bits:%u, preserve:%x, zero:%u",
		   max_range, ord_off & range_mask, ord_off & ~range_mask);

  for (unsigned ix = loc_spans::SPAN_FIRST; ix != spans.length (); ix++)
    {
      loc_spans::span &span = spans[ix];

      span.macro_delta = mac_off - span.macro.second;
      mac_off -= span.macro.second - span.macro.first;
      dump () && dump ("Macro span:%u [%u,%u):%u->%d(%u)", ix,
		       span.macro.first, span.macro.second,
		       span.macro.second - span.macro.first,
		       span.macro_delta, span.macro.first + span.macro_delta);

      line_map_ordinary const *omap
	= linemap_check_ordinary (linemap_lookup (line_table,
						  span.ordinary.first));
      location_t base = MAP_START_LOCATION (omap);

      /* Preserve the low MAX_RANGE bits of base by incrementing ORD_OFF.  */
      unsigned low_bits = base & range_mask;
      if ((ord_off & range_mask) > low_bits)
	low_bits += range_mask + 1;
      ord_off = (ord_off & ~range_mask) + low_bits;
      span.ordinary_delta = ord_off - base;

      for (; MAP_START_LOCATION (omap) < span.ordinary.second; omap++)
	{
	  location_t start_loc = MAP_START_LOCATION (omap);
	  unsigned to = start_loc + span.ordinary_delta;
	  location_t end_loc = MAP_START_LOCATION (omap + 1);
	  
	  dump () && dump ("Ordinary span:%u [%u,%u):%u->%d(%u)", ix, start_loc,
			   end_loc, end_loc - start_loc,
			   span.ordinary_delta, to);

	  /* There should be no change in the low order bits.  */
	  gcc_checking_assert (((start_loc ^ to) & range_mask) == 0);
	}
      /* The ending serialized value.  */
      ord_off = span.ordinary.second + span.ordinary_delta;
    }

  dump () && dump ("Ordinary hwm:%u macro lwm:%u", ord_off, mac_off);

  dump.outdent ();

  info.max_range = max_range;

  return info;
}

/* Write the location maps.  This also determines the shifts for the
   location spans.  */
// FIXME: I do not prune the unreachable locations.  Modules with
// textually-large GMFs could well cause us to run out of locations.
// Regular single-file modules could also be affected.

void
module_state::write_ordinary_maps (elf_out *to, location_map_info &info,
				   bool has_partitions, unsigned *crc_p)
{
  dump () && dump ("Writing ordinary location maps");
  dump.indent ();

  vec<const char *> filenames;
  filenames.create (20);

  /* Determine the unique filenames.  */
  // FIXME: should be found by the prepare fn as part of the
  // unreachable pruning
  for (unsigned ix = loc_spans::SPAN_FIRST; ix != spans.length (); ix++)
    {
      loc_spans::span &span = spans[ix];
      line_map_ordinary const *omap
	= linemap_check_ordinary (linemap_lookup (line_table,
						  span.ordinary.first));

      /* We should exactly match up.  */
      gcc_checking_assert (MAP_START_LOCATION (omap) == span.ordinary.first);

      for (; MAP_START_LOCATION (omap) < span.ordinary.second; omap++)
	{
	  const char *fname = ORDINARY_MAP_FILE_NAME (omap);

	  /* We should never find a module linemap in an interval.  */
	  gcc_checking_assert (!MAP_MODULE_P (omap));

	  /* We expect very few filenames, so just an array.  */
	  for (unsigned jx = filenames.length (); jx--;)
	    {
	      const char *name = filenames[jx];
	      if (0 == strcmp (name, fname))
		{
		  /* Reset the linemap's name, because for things like
		     preprocessed input we could have multple
		     instances of the same name, and we'd rather not
		     percolate that.  */
		  const_cast<line_map_ordinary *> (omap)->to_file = name;
		  fname = NULL;
		  break;
		}
	    }
	  if (fname)
	    filenames.safe_push (fname);
	}
    }

  bytes_out sec (to);
  sec.begin ();

  /* Write the filenames.  */
  unsigned len = filenames.length ();
  sec.u (len);
  dump () && dump ("%u source file names", len);
  for (unsigned ix = 0; ix != len; ix++)
    {
      const char *fname = filenames[ix];
      dump (dumper::LOCATION) && dump ("Source file[%u]=%s", ix, fname);
      sec.str (fname);
    }

  location_t offset = spans[loc_spans::SPAN_FIRST].ordinary.first;
  location_t range_mask = (1u << info.max_range) - 1;

  dump () && dump ("Ordinary maps:%u, range bits:%u, preserve:%x, zero:%u",
		   info.num_maps.first, info.max_range, offset & range_mask,
		   offset & ~range_mask);
  sec.u (info.num_maps.first);	/* Num maps.  */
  sec.u (info.max_range);		/* Maximum range bits  */
  sec.u (offset & range_mask);	/* Bits to preserve.  */
  sec.u (offset & ~range_mask);

  for (unsigned ix = loc_spans::SPAN_FIRST; ix != spans.length (); ix++)
    {
      loc_spans::span &span = spans[ix];
      line_map_ordinary const *omap
	= linemap_check_ordinary (linemap_lookup (line_table,
						  span.ordinary.first));
      for (; MAP_START_LOCATION (omap) < span.ordinary.second; omap++)
	{
	  location_t start_loc = MAP_START_LOCATION (omap);
	  unsigned to = start_loc + span.ordinary_delta;

	  dump (dumper::LOCATION)
	    && dump ("Span:%u ordinary [%u,%u)->%u", ix, start_loc,
		     MAP_START_LOCATION (omap + 1), to);

	  /* There should be no change in the low order bits.  */
	  gcc_checking_assert (((start_loc ^ to) & range_mask) == 0);
	  sec.u (to);

	  /* Making accessors just for here, seems excessive.  */
	  sec.u (omap->reason);
	  sec.u (omap->sysp);
	  sec.u (omap->m_range_bits);
	  sec.u (omap->m_column_and_range_bits - omap->m_range_bits);

	  const char *fname = ORDINARY_MAP_FILE_NAME (omap);
	  for (unsigned ix = 0; ix != filenames.length (); ix++)
	    if (filenames[ix] == fname)
	      {
		sec.u (ix);
		break;
	      }
	  sec.u (ORDINARY_MAP_STARTING_LINE_NUMBER (omap));

	  /* Write the included from location, which means reading it
	     while reading in the ordinary maps.  So we'd better not
	     be getting ahead of ourselves.  */
	  location_t from = linemap_included_from (omap);
	  gcc_checking_assert (from < MAP_START_LOCATION (omap));
	  if (from != UNKNOWN_LOCATION && has_partitions)
	    {
	      /* A partition's span will have a from pointing at a
		 MODULE_INC.  Find that map's from.  */
		line_map_ordinary const *fmap
		  = linemap_check_ordinary (linemap_lookup (line_table, from));
		if (MAP_MODULE_P (fmap))
		  from = linemap_included_from (fmap);
	    }
	  write_location (sec, from);
	}
      /* The ending serialized value.  */
      offset = MAP_START_LOCATION (omap) + span.ordinary_delta;
    }
  dump () && dump ("Ordinary location hwm:%u", offset);
  sec.u (offset);

  filenames.release ();

  sec.end (to, to->name (MOD_SNAME_PFX ".om"), crc_p);
  dump.outdent ();
}

void
module_state::write_macro_maps (elf_out *to, location_map_info &info,
				unsigned *crc_p)
{
  dump () && dump ("Writing macro location maps");
  dump.indent ();

  bytes_out sec (to);
  sec.begin ();

  dump () && dump ("Macro maps:%u", info.num_maps.second);
  sec.u (info.num_maps.second);

  location_t offset = spans[loc_spans::SPAN_FIRST].macro.second;
  sec.u (offset);

  unsigned macro_num = 0;
  for (unsigned ix = loc_spans::SPAN_FIRST; ix != spans.length (); ix++)
    {
      loc_spans::span &span = spans[ix];
      if (span.macro.first == span.macro.second)
	continue;

      for (unsigned first
	     = linemap_lookup_macro_index (line_table, span.macro.second - 1);
	   first < LINEMAPS_MACRO_USED (line_table);
	   first++)
	{
	  line_map_macro const *mmap
	    = LINEMAPS_MACRO_MAP_AT (line_table, first);
	  location_t start_loc = MAP_START_LOCATION (mmap);
	  if (start_loc < span.macro.first)
	    break;
	  if (macro_num == info.num_maps.second)
	    {
	      /* We're ending on an empty macro expansion.  The
		 preprocessor doesn't prune such things.  */
	      // FIXME: This goes to show we should be eliding all
	      // macro expansions that are not covering any location
	      // we need to output (just like non-macro locations,
	      // mentioned above).  They also happen in #if
	      // conditionals, that we don't care about at all.
	      gcc_checking_assert (!mmap->n_tokens);
	      continue;
	    }

	  sec.u (offset);
	  sec.u (mmap->n_tokens);
	  sec.cpp_node (mmap->macro);
	  write_location (sec, mmap->expansion);
	  const location_t *locs = mmap->macro_locations;
	  /* There are lots of identical runs.  */
	  location_t prev = 0;
	  unsigned count = 0;
	  unsigned runs = 0;
	  for (unsigned jx = mmap->n_tokens * 2; jx--;)
	    {
	      location_t tok_loc = locs[jx];
	      if (tok_loc == prev)
		{
		  count++;
		  continue;
		}
	      runs++;
	      sec.u (count);
	      count = 1;
	      prev = tok_loc;
	      write_location (sec, tok_loc);
	    }
	  sec.u (count);
	  dump (dumper::LOCATION)
	    && dump ("Span:%u macro:%u %I %u/%u*2 locations [%u,%u)->%u",
		     ix, macro_num, identifier (mmap->macro),
		     runs, mmap->n_tokens,
		     start_loc, start_loc + mmap->n_tokens,
		     start_loc + span.macro_delta);
	  macro_num++;
	  offset -= mmap->n_tokens;
	  gcc_checking_assert (offset == start_loc + span.macro_delta);
	}
    }
  dump () && dump ("Macro location lwm:%u", offset);
  sec.u (offset);
  gcc_assert (macro_num == info.num_maps.second);

  sec.end (to, to->name (MOD_SNAME_PFX ".mm"), crc_p);
  dump.outdent ();
}

bool
module_state::read_ordinary_maps ()
{
  bytes_in sec;

  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".om"))
    return false;
  dump () && dump ("Reading ordinary location maps");
  dump.indent ();

  /* Read the filename table.  */
  unsigned len = sec.u ();
  dump () && dump ("%u source file names", len);
  vec<const char *> filenames;
  filenames.create (len);
  for (unsigned ix = 0; ix != len; ix++)
    {
      size_t l;
      const char *buf = sec.str (&l);
      char *fname = XNEWVEC (char, l + 1);
      memcpy (fname, buf, l + 1);
      dump (dumper::LOCATION) && dump ("Source file[%u]=%s", ix, fname);
      /* We leak these names into the line-map table.  But it
	 doesn't own them.  */
      filenames.quick_push (fname);
    }

  unsigned num_ordinary = sec.u (); 
  unsigned max_range = sec.u ();
  unsigned low_bits = sec.u ();
  location_t zero = sec.u ();
  location_t range_mask = (1u << max_range) - 1;

  dump () && dump ("Ordinary maps:%u, range bits:%u, preserve:%x, zero:%u",
		   num_ordinary, max_range, low_bits, zero);

  location_t offset = line_table->highest_location + 1;
  /* Ensure offset doesn't go backwards at the start.  */
  if ((offset & range_mask) > low_bits)
    offset += range_mask + 1;
  offset = (offset & ~range_mask);

  /* We need to insert our maps if we're a partition of the primary
     module interface.  */
  if (module_interface_p () && !module_partition_p () && is_partition ())
    spans.open (offset + low_bits);

  line_map_ordinary *maps = static_cast<line_map_ordinary *>
    (line_map_new_raw (line_table, false, num_ordinary));

  location_t lwm = offset;
  slurp->loc_deltas.first = offset - zero;
  ordinary_locs.first = zero + low_bits + slurp->loc_deltas.first;
  dump () && dump ("Ordinary loc delta %d", slurp->loc_deltas.first);

  for (unsigned ix = 0; ix != num_ordinary && !sec.get_overrun (); ix++)
    {
      line_map_ordinary *map = &maps[ix];
      unsigned hwm = sec.u ();

      /* Record the current HWM so that the below read_location is
	 ok.  */
      ordinary_locs.second = hwm + slurp->loc_deltas.first;
      map->start_location = hwm + (offset - zero);
      if (map->start_location < lwm)
	sec.set_overrun ();
      lwm = map->start_location;
      dump (dumper::LOCATION) && dump ("Map:%u %u->%u", ix, hwm, lwm);
      map->reason = lc_reason (sec.u ());
      map->sysp = sec.u ();
      map->m_range_bits = sec.u ();
      map->m_column_and_range_bits = map->m_range_bits + sec.u ();

      unsigned fnum = sec.u ();
      map->to_file = (fnum < filenames.length () ? filenames[fnum] : "");
      map->to_line = sec.u ();

      /* Root the outermost map at our location.  */
      location_t from = read_location (sec);
      map->included_from = from != UNKNOWN_LOCATION ? from : loc;
    }

  location_t hwm = sec.u ();
  ordinary_locs.second = hwm + slurp->loc_deltas.first;

  /* highest_location is the one handed out, not the next one to
     hand out.  */
  line_table->highest_location = ordinary_locs.second - 1;

  if (lwm > line_table->highest_location)
    /* We ran out of locations, fail.  */
    sec.set_overrun ();
  dump () && dump ("Ordinary location hwm:%u", ordinary_locs.second);

  filenames.release ();
  
  dump.outdent ();
  if (!sec.end (from ()))
    return false;

  return true;
}

bool
module_state::read_macro_maps ()
{
  bytes_in sec;

  if (!sec.begin (loc, from (), MOD_SNAME_PFX ".mm"))
    return false;
  dump () && dump ("Reading macro location maps");
  dump.indent ();

  unsigned num_macros = sec.u ();
  location_t zero = sec.u ();
  dump () && dump ("Macro maps:%u zero:%u", num_macros, zero);

  location_t offset = LINEMAPS_MACRO_LOWEST_LOCATION (line_table);
  slurp->loc_deltas.second = zero - offset;
  macro_locs.second = zero - slurp->loc_deltas.second;
  dump () && dump ("Macro loc delta %d", slurp->loc_deltas.second);

  for (unsigned ix = 0; ix != num_macros && !sec.get_overrun (); ix++)
    {
      unsigned lwm = sec.u ();
      /* Record the current LWM so that the below read_location is
	 ok.  */
      macro_locs.first = lwm - slurp->loc_deltas.second;

      unsigned n_tokens = sec.u ();
      cpp_hashnode *node = sec.cpp_node ();
      location_t exp_loc = read_location (sec);

      const line_map_macro *macro
	= linemap_enter_macro (line_table, node, exp_loc, n_tokens);
      if (!macro)
	/* We ran out of numbers, bail out (and that'll set overrun
	   due to unread data.  */
	break;

      location_t *locs = macro->macro_locations;
      location_t tok_loc = loc;
      unsigned count = sec.u ();
      unsigned runs = 0;
      for (unsigned jx = macro->n_tokens * 2; jx-- && !sec.get_overrun ();)
	{
	  while (!count-- && !sec.get_overrun ())
	    {
	      runs++;
	      tok_loc = read_location (sec);
	      count = sec.u ();
	    }
	  locs[jx] = tok_loc;
	}
      if (count)
	sec.set_overrun ();
      dump (dumper::LOCATION)
	&& dump ("Macro:%u %I %u/%u*2 locations [%u,%u)",
		 ix, identifier (node), runs, n_tokens,
		 MAP_START_LOCATION (macro),
		 MAP_START_LOCATION (macro) + n_tokens);
    }
  location_t lwm = sec.u ();
  macro_locs.first = lwm - slurp->loc_deltas.second;

  dump () && dump ("Macro location lwm:%u", macro_locs.first);

  if (module_interface_p () && !module_partition_p () && is_partition ())
    spans.close ();

  dump.outdent ();
  if (!sec.end (from ()))
    return false;

  return true;
}

/* Serialize the definition of MACRO.  */

void
module_state::write_define (bytes_out &sec, const cpp_macro *macro, bool located)
{
  sec.u (macro->count);

  sec.b (macro->fun_like);
  sec.b (macro->variadic);
  sec.b (macro->syshdr);
  sec.bflush ();

  if (located)
    write_location (sec, macro->line);
  if (macro->fun_like)
    {
      sec.u (macro->paramc);
      const cpp_hashnode *const *parms = macro->parm.params;
      for (unsigned ix = 0; ix != macro->paramc; ix++)
	sec.cpp_node (parms[ix]);
    }

  unsigned len = 0;
  for (unsigned ix = 0; ix != macro->count; ix++)
    {
      const cpp_token *token = &macro->exp.tokens[ix];
      if (located)
	write_location (sec, token->src_loc);
      sec.u (token->type);
      sec.u (token->flags);
      switch (cpp_token_val_index (token))
	{
	default:
	  gcc_unreachable ();

	case CPP_TOKEN_FLD_ARG_NO:
	  /* An argument reference.  */
	  sec.u (token->val.macro_arg.arg_no);
	  sec.cpp_node (token->val.macro_arg.spelling);
	  break;

	case CPP_TOKEN_FLD_NODE:
	  /* An identifier.  */
	  sec.cpp_node (token->val.node.node);
	  if (token->val.node.spelling == token->val.node.node)
	    /* The spelling will usually be the same.  so optimize
	       that.  */
	    sec.str (NULL, 0);
	  else
	    sec.cpp_node (token->val.node.spelling);
	  break;

	case CPP_TOKEN_FLD_NONE:
	  break;

	case CPP_TOKEN_FLD_STR:
	  /* A string, number or comment.  Not always NUL terminated,
	     we stream out in a single contatenation with embedded
	     NULs as that's a safe default.  */
	  len += token->val.str.len + 1;
	  sec.u (token->val.str.len);
	  break;

	case CPP_TOKEN_FLD_SOURCE:
	case CPP_TOKEN_FLD_TOKEN_NO:
	case CPP_TOKEN_FLD_PRAGMA:
	  /* These do not occur inside a macro itself.  */
	  gcc_unreachable ();
	}
    }

  if (len)
    {
      char *ptr = reinterpret_cast<char *> (sec.buf (len));
      len = 0;
      for (unsigned ix = 0; ix != macro->count; ix++)
	{
	  const cpp_token *token = &macro->exp.tokens[ix];
	  if (cpp_token_val_index (token) == CPP_TOKEN_FLD_STR)
	    {
	      memcpy (ptr + len, token->val.str.text,
		      token->val.str.len);
	      len += token->val.str.len;
	      ptr[len++] = 0;
	    }
	}
    }
}

/* Read a macro definition.  */

cpp_macro *
module_state::read_define (bytes_in &sec, cpp_reader *reader, bool located) const
{
  unsigned count = sec.u ();
  /* We rely on knowing cpp_reader's hash table is ident_hash, and
     it's subobject allocator is stringpool_ggc_alloc and that is just
     a wrapper for ggc_alloc_atomic.  */
  cpp_macro *macro
    = (cpp_macro *)ggc_alloc_atomic (sizeof (cpp_macro)
				     + sizeof (cpp_token) * (count - !!count));
  memset (macro, 0, sizeof (cpp_macro) + sizeof (cpp_token) * (count - !!count));

  macro->count = count;
  macro->kind = cmk_macro;
  macro->imported = true;

  macro->fun_like = sec.b ();
  macro->variadic = sec.b ();
  macro->syshdr = sec.b ();
  sec.bflush ();

  macro->line = located ? read_location (sec) : loc;

  if (macro->fun_like)
    {
      unsigned paramc = sec.u ();
      cpp_hashnode **params
	= (cpp_hashnode **)ggc_alloc_atomic (sizeof (cpp_hashnode *) * paramc);
      macro->paramc = paramc;
      macro->parm.params = params;
      for (unsigned ix = 0; ix != paramc; ix++)
	params[ix] = sec.cpp_node ();
    }

  unsigned len = 0;
  for (unsigned ix = 0; ix != count && !sec.get_overrun (); ix++)
    {
      cpp_token *token = &macro->exp.tokens[ix];
      token->src_loc = located ? read_location (sec) : loc;
      token->type = cpp_ttype (sec.u ());
      token->flags = sec.u ();
      switch (cpp_token_val_index (token))
	{
	default:
	  sec.set_overrun ();
	  break;

	case CPP_TOKEN_FLD_ARG_NO:
	  /* An argument reference.  */
	  {
	    unsigned arg_no = sec.u ();
	    if (arg_no - 1 >= macro->paramc)
	      sec.set_overrun ();
	    token->val.macro_arg.arg_no = arg_no;
	    token->val.macro_arg.spelling = sec.cpp_node ();
	  }
	  break;

	case CPP_TOKEN_FLD_NODE:
	  /* An identifier.  */
	  token->val.node.node = sec.cpp_node ();
	  token->val.node.spelling = sec.cpp_node ();
	  if (!token->val.node.spelling)
	    token->val.node.spelling = token->val.node.node;
	  break;

	case CPP_TOKEN_FLD_NONE:
	  break;

	case CPP_TOKEN_FLD_STR:
	  /* A string, number or comment.  */
	  token->val.str.len = sec.u ();
	  len += token->val.str.len + 1;
	  break;
	}
    }

  if (len)
    if (const char *ptr = reinterpret_cast<const char *> (sec.buf (len)))
      {
	/* There should be a final NUL.  */
	if (ptr[len-1])
	  sec.set_overrun ();
	/* cpp_alloc_token_string will add a final NUL.  */
	const unsigned char *buf
	  = cpp_alloc_token_string (reader, (const unsigned char *)ptr, len - 1);
	len = 0;
	for (unsigned ix = 0; ix != count && !sec.get_overrun (); ix++)
	  {
	    cpp_token *token = &macro->exp.tokens[ix];
	    if (cpp_token_val_index (token) == CPP_TOKEN_FLD_STR)
	      {
		token->val.str.text = buf + len;
		len += token->val.str.len;
		if (buf[len++])
		  sec.set_overrun ();
	      }
	  }
      }

  if (sec.get_overrun ())
    return NULL;
  return macro;
}

/* Exported macro data.  */
struct macro_export {
  cpp_macro *def;
  location_t undef_loc;

  macro_export ()
    :def (NULL), undef_loc (UNKNOWN_LOCATION)
  {
  }
};

/* Imported macro data.  */
class macro_import {
public:
  struct slot {
#if defined (WORDS_BIGENDIAN) && SIZEOF_VOID_P == 8
    int offset;
#endif
    /* We need to ensure we don't use the LSB for representation, as
       that's the union discriminator below.  */
    unsigned bits;

#if !(defined (WORDS_BIGENDIAN) && SIZEOF_VOID_P == 8)
    int offset;
#endif

  private:
    enum layout
      {
       L_MOD = 1,		/* Bit zero is always 1.  */
       L_UNDEF = MODULE_BITS + 1,	/* Has an undef.  */
       L_DEF = MODULE_BITS + 2,		/* Has a def.  */
       L_MOD_MASK = (1u << MODULE_BITS) - 1 /* Which module,  */
      };

  public:
    /* Not a regular ctor, because we put it in a union, and that's
       not allowed in C++ 98.  */
    static slot ctor (unsigned mod)
    {
      slot s;
      s.bits = 1 | (mod << L_MOD);
      s.offset = -1;
      return s;
    }

  public:
    bool get_undef () const 
    {
      return (bits >> L_UNDEF) & 1;
    }
    bool get_def () const 
    {
      return (bits >> L_DEF) & 1;
    }
    unsigned get_mod () const
    {
      return (bits >> L_MOD) & L_MOD_MASK;
    }
    void set_undef ()
    {
      bits |= 1u << L_UNDEF;
    }
    void set_def ()
    {
      bits |= 1u << L_DEF;
    }
    void clear_def ()
    {
      bits &= ~(1u << L_DEF);
    }
  };

private:
  typedef vec<slot, va_heap, vl_embed> ary_t;
  union either {
    /* Discriminated by bit 0.  The expected case is that there will
       be exactly one slot per macro, hence the effort of packing
       that.  */
    ary_t *ary;
    slot single;
  } u;

public:
  macro_import ()
  {
    u.ary = NULL;
  }

private:
  bool single_p () const
  {
    return u.single.bits & 1;
  }
  bool occupied_p () const
  {
    return u.ary != NULL;
  }

public:
  unsigned length () const
  {
    gcc_checking_assert (occupied_p ());
    return single_p () ? 1 : u.ary->length ();
  }
  slot &operator[] (unsigned ix)
  {
    gcc_checking_assert (occupied_p ());
    if (single_p ())
      {
	gcc_checking_assert (!ix);
	return u.single;
      }
    else
      return (*u.ary)[ix];
  }

public:
  slot &exported ();
  slot &append (unsigned);
};

/* O is a new import to append to the list for.  If we're an empty
   set, initialize us.  */

macro_import::slot &
macro_import::append (unsigned mod)
{
  if (!occupied_p ())
    {
      u.single = slot::ctor (mod);
      return u.single;
    }
  else
    {
      bool single = single_p ();
      ary_t *m = single ? NULL : u.ary;
      vec_safe_reserve (m, 1 + single);
      if (single)
	m->quick_push (u.single);
      u.ary = m;
      return *u.ary->quick_push (slot::ctor (mod));
    }
}

/* We're going to export something.  Make sure the first import slot
   is us.  */

macro_import::slot &
macro_import::exported ()
{
  if (occupied_p () && !(*this)[0].get_mod ())
    return (*this)[0];

  slot *a = &append (0);
  if (!single_p ())
    {
      slot &f = (*this)[0];
      std::swap (f, *a);
      a = &f;
    }
  return *a;
}

/* The import (&exported) macros.  cpp_hasnode's deferred field
   indexes this array (offset by 1, so zero means 'not present'.  */

static vec<macro_import, va_heap, vl_embed> *macro_imports;

/* The exported macros.  A macro_import slot's zeroth element's offset
   indexes this array.  If the zeroth slot is not for module zero,
   there is no export.  */

static vec<macro_export, va_heap, vl_embed> *macro_exports;

/* The reachable set of header imports from this TU.  */

static GTY(()) bitmap headers;

/* Get the (possibly empty) macro imports for NODE.  */

static macro_import &
get_macro_imports (cpp_hashnode *node)
{
  if (node->deferred)
    return (*macro_imports)[node->deferred - 1];

  vec_safe_reserve (macro_imports, 1);
  node->deferred = macro_imports->length () + 1;
  return *vec_safe_push (macro_imports, macro_import ());
}

/* Get the macro export for export EXP of NODE.  */

static macro_export &
get_macro_export (macro_import::slot &slot)
{
  if (slot.offset >= 0)
    return (*macro_exports)[slot.offset];

  vec_safe_reserve (macro_exports, 1);
  slot.offset = macro_exports->length ();
  return *macro_exports->quick_push (macro_export ());
}

/* If NODE is an exportable macro, add it to the export set.  */

static int
maybe_add_macro (cpp_reader *, cpp_hashnode *node, void *data_)
{
  bool exporting = false;

  if (cpp_user_macro_p (node))
    if (cpp_macro *macro = node->value.macro)
      /* Ignore imported, builtins, command line and forced header macros.  */
      if (!macro->imported && !macro->lazy && macro->line >= spans.main_start ())
	{
	  gcc_checking_assert (macro->kind == cmk_macro);
	  /* I don't want to deal with this corner case, that I suspect is
	     a devil's advocate reading of the standard.  */
	  gcc_checking_assert (!macro->extra_tokens);

	  macro_import::slot &slot = get_macro_imports (node).exported ();
	  macro_export &exp = get_macro_export (slot);
	  slot.set_def ();
	  exp.def = macro;
	  exporting = true;
	}

  if (!exporting && node->deferred)
    {
      macro_import &imports = (*macro_imports)[node->deferred - 1];
      macro_import::slot &slot = imports[0];
      if (!slot.get_mod ())
	{
	  gcc_checking_assert (slot.get_def () || slot.get_undef ());
	  exporting = true;
	}
    }

  if (exporting)
    static_cast<vec<cpp_hashnode *> *> (data_)->safe_push (node);

  return 1; /* Don't stop.  */
}

/* Order cpp_hashnodes A_ and B_ by their exported macro locations.  */

static int
macro_loc_cmp (const void *a_, const void *b_)
{
  const cpp_hashnode *node_a = *(const cpp_hashnode *const *)a_;
  macro_import &import_a = (*macro_imports)[node_a->deferred - 1];
  const macro_export &export_a = (*macro_exports)[import_a[0].offset];
  location_t loc_a = export_a.def ? export_a.def->line : export_a.undef_loc;

  const cpp_hashnode *node_b = *(const cpp_hashnode *const *)b_;
  macro_import &import_b = (*macro_imports)[node_b->deferred - 1];
  const macro_export &export_b = (*macro_exports)[import_b[0].offset];
  location_t loc_b = export_b.def ? export_b.def->line : export_b.undef_loc;

  if (loc_a < loc_b)
    return +1;
  else if (loc_a > loc_b)
    return -1;
  else
    return 0;
}

/* Write out the exported defines.  This is two sections, one
   containing the definitions, the other a table of node names.  */
// FIXME: macros from command line and forced headers are not to be
// exported.

unsigned
module_state::write_macros (elf_out *to, cpp_reader *reader, unsigned *crc_p)
{
  dump () && dump ("Writing macros");
  dump.indent ();

  vec<cpp_hashnode *> macros;
  macros.create (100);
  cpp_forall_identifiers (reader, maybe_add_macro, &macros);

  unsigned count = 0;
  if (macros.length ())
    {
      dump (dumper::MACRO) && dump ("No more than %u macros", macros.length ());

      macros.qsort (macro_loc_cmp);

      /* Write the defs */
      bytes_out sec (to);
      sec.begin ();

      for (unsigned ix = macros.length (); ix--;)
	{
	  cpp_hashnode *node = macros[ix];
	  macro_import::slot &slot = (*macro_imports)[node->deferred - 1][0];
	  gcc_assert (!slot.get_mod ()
		      && (slot.get_undef () || slot.get_def ()));

	  macro_export &mac = (*macro_exports)[slot.offset];
	  gcc_assert (slot.get_undef () == (mac.undef_loc != UNKNOWN_LOCATION)
		      && slot.get_def () == (mac.def != NULL));

	  if (IDENTIFIER_KEYWORD_P (identifier (node)))
	    {
	      warning_at (mac.def->line, 0,
			  "not exporting %<#define %E%> as it is a keyword",
			  identifier (node));
	      slot.offset = 0;
	      continue;
	    }

	  count++;
	  slot.offset = sec.pos;
	  dump (dumper::MACRO)
	    && dump ("Writing macro %s%s%s %I at %u",
		     slot.get_undef () ? "#undef" : "",
		     slot.get_undef () && slot.get_def () ? " & " : "",
		     slot.get_def () ? "#define" : "",
		     identifier (node), slot.offset);
	  if (mac.undef_loc != UNKNOWN_LOCATION)
	    write_location (sec, mac.undef_loc);
	  if (mac.def)
	    write_define (sec, mac.def);
	}
      sec.end (to, to->name (MOD_SNAME_PFX ".def"), crc_p);

      if (count)
	{
	  /* Write the table.  */
	  bytes_out sec (to);
	  sec.begin ();
	  sec.u (count);

	  for (unsigned ix = macros.length (); ix--;)
	    {
	      const cpp_hashnode *node = macros[ix];
	      macro_import::slot &slot = (*macro_imports)[node->deferred - 1][0];

	      if (slot.offset)
		{
		  sec.cpp_node (node);
		  sec.u ((slot.get_undef () << 0)
			 | ((slot.get_def ()) << 1));
		  sec.u (slot.offset);
		}
	    }
	  sec.end (to, to->name (MOD_SNAME_PFX ".mac"), crc_p);
	}
    }

  macros.release ();
  dump.outdent ();
  return count;
}

bool
module_state::read_macros ()
{
  /* Get the tbl section.  */
  if (!slurp->macro_tbl.begin (loc, from (), MOD_SNAME_PFX ".mac"))
    return false;

  /* Get the def section.  */
  if (!slurp->macro_defs.begin (loc, from (), MOD_SNAME_PFX ".def"))
    return false;

  return true;
}

/* Install the macro name table.  */

void
module_state::install_macros ()
{
  bytes_in &sec = slurp->macro_tbl;
  if (!sec.size)
    return;

  dump () && dump ("Reading macro table %M", this);
  dump.indent ();

  unsigned count = sec.u ();
  dump () && dump ("%u macros", count);
  while (count--)
    {
      cpp_hashnode *node = sec.cpp_node ();
      macro_import &imp = get_macro_imports (node);
      macro_import::slot &slot = imp.append (mod);
      unsigned flags = sec.u ();
      if ((flags >> 0) & 1)
	slot.set_undef ();
      if ((flags >> 1) & 1)
	slot.set_def ();
      slot.offset = sec.u ();

      dump (dumper::MACRO)
	&& dump ("Read %s macro %s%s%s %I at %u",
		 imp.length () > 1 ? "add" : "new",
		 slot.get_undef () ? "#undef" : "",
		 slot.get_undef () && slot.get_def () ? " & " : "",
		 slot.get_def () ? "#define" : "",
		 identifier (node), slot.offset);

      /* We'll leak an imported definition's TOKEN_FLD_STR's data
	 here.  But that only happens when we've had to resolve the
	 deferred macro before this import -- why are you doing
	 that?  */
      if (cpp_macro *cur = cpp_set_deferred_macro (node))
	if (!cur->imported)
	  {
	    macro_import::slot &slot = imp.exported ();
	    macro_export &exp = get_macro_export (slot);
	    exp.def = cur;
	    slot.set_def ();
	    dump (dumper::MACRO)
	      && dump ("Saving current #define %I", identifier (node));
	  }
    }

  /* We're now done with the table.  */
  elf_in::release (slurp->from, sec);

  dump.outdent ();
}

/* Import the transitive macros.  */

void
module_state::import_macros ()
{
  bitmap_ior_into (headers, slurp->headers);

  bitmap_iterator bititer;
  unsigned bitnum;
  EXECUTE_IF_SET_IN_BITMAP (slurp->headers, 0, bitnum, bititer)
    (*modules)[bitnum]->install_macros ();
}

/* NODE is being undefined at LOC.  Record it in the export table, if
   necessary.  */

void
module_state::undef_macro (cpp_reader *, location_t loc, cpp_hashnode *node)
{
  if (!node->deferred)
    /* The macro is not imported, so our undef is irrelevant.  */
    return;

  unsigned n = dump.push (NULL);

  macro_import::slot &slot = (*macro_imports)[node->deferred - 1].exported ();
  macro_export &exp = get_macro_export (slot);

  exp.undef_loc = loc;
  slot.set_undef ();
  exp.def = NULL;
  slot.clear_def ();

  dump (dumper::MACRO) && dump ("Recording macro #undef %I", identifier (node));

  dump.pop (n);
}

/* NODE is a deferred macro node.  Determine the definition and return
   it, with NULL if undefined.  May issue diagnostics.

   This can leak memory, when merging declarations -- the string
   contents (TOKEN_FLD_STR) of each definition are allocated in
   unreclaimable cpp objstack.  Only one will win.  However, I do not
   expect this to be common -- mostly macros have a single point of
   definition.  Perhaps we could restore the objstack to its position
   after the first imported definition (if that wins)?  The macros
   themselves are GC'd.  */

cpp_macro *
module_state::deferred_macro (cpp_reader *reader, location_t loc,
			      cpp_hashnode *node)
{
  macro_import &imports = (*macro_imports)[node->deferred - 1];

  unsigned n = dump.push (NULL);
  dump (dumper::MACRO) && dump ("Deferred macro %I", identifier (node));

  bitmap visible (BITMAP_GGC_ALLOC ());

  if (!(imports[0].get_undef () && !imports[0].get_mod ()))
    {
      /* Calculate the set of visible header imports.  */
      bitmap_copy (visible, headers);
      for (unsigned ix = imports.length (); ix--;)
	{
	  const macro_import::slot &slot = imports[ix];
	  unsigned mod = slot.get_mod ();
	  if (slot.get_undef () && bitmap_bit_p (visible, mod))
	    {
	      bitmap arg = mod ? (*modules)[mod]->slurp->headers : headers;
	      bitmap_and_compl_into (visible, arg);
	      bitmap_set_bit (visible, mod);
	    }
	}
    }
  bitmap_set_bit (visible, 0);

  /* Now find the macros that are still visible.  */
  bool failed = false;
  cpp_macro *def = NULL;
  vec<macro_export> defs;
  defs.create (imports.length ());
  for (unsigned ix = imports.length (); ix--;)
    {
      const macro_import::slot &slot = imports[ix];
      unsigned mod = slot.get_mod ();
      if (bitmap_bit_p (visible, mod))
	{
	  macro_export *pushed = NULL;
	  if (mod)
	    {
	      const module_state *imp = (*modules)[mod];
	      bytes_in &sec = imp->slurp->macro_defs;
	      if (!sec.get_overrun ())
		{
		  dump (dumper::MACRO)
		    && dump ("Reading macro %s%s%s %I module %M at %u",
			     slot.get_undef () ? "#undef" : "",
			     slot.get_undef () && slot.get_def ()
			     ? " & " : "",
			     slot.get_def () ? "#define" : "",
			     identifier (node), imp, slot.offset);
		  sec.random_access (slot.offset);

		  macro_export exp;
		  if (slot.get_undef ())
		    exp.undef_loc = imp->read_location (sec);
		  if (slot.get_def ())
		    exp.def = imp->read_define (sec, reader);
		  if (sec.get_overrun ())
		    error_at (loc, "macro definitions of %qE corrupted",
			      imp->name);
		  else
		    pushed = defs.quick_push (exp);
		}
	    }
	  else
	    pushed = defs.quick_push ((*macro_exports)[slot.offset]);
	  if (pushed && pushed->def)
	    {
	      if (!def)
		def = pushed->def;
	      else if (cpp_compare_macros (def, pushed->def))
		failed = true;
	    }
	}
    }

  if (failed)
    {
      /* If LOC is the first loc, this is the end of file check, which
	 is a warning.  */
      if (loc == MAP_START_LOCATION (LINEMAPS_ORDINARY_MAP_AT (line_table, 0)))
	warning_at (loc, OPT_Winvalid_imported_macros,
		    "inconsistent imported macro definition %qE",
		    identifier (node));
      else
	error_at (loc, "inconsistent imported macro definition %qE",
		  identifier (node));
      for (unsigned ix = defs.length (); ix--;)
	{
	  macro_export &exp = defs[ix];
	  if (exp.undef_loc)
	    inform (exp.undef_loc, "%<#undef %E%>", identifier (node));
	  if (exp.def)
	    inform (exp.def->line, "%<#define %s%>",
		    cpp_macro_definition (reader, node, exp.def));
	}
      def = NULL;
    }

  defs.release ();

  dump.pop (n);

  return def;
}

/* Stream the static aggregates.  Sadly some headers (ahem:
   iostream) contain static vars, and rely on them to run global
   ctors.  */
// FIXME: What about tls inits?
// FIXME: Do I need to walk to add to dependency table?
unsigned
module_state::write_inits (elf_out *to, depset::hash &table, unsigned *crc_ptr)
{
  if (!static_aggregates)
    return 0;

  dump () && dump ("Writing initializers");
  dump.indent ();

  static_aggregates = nreverse (static_aggregates);

  unsigned count = 0;
  trees_out sec (to, this, table, ~0u);
  sec.begin ();
  for (tree init = static_aggregates; init; init = TREE_CHAIN (init), count++)
    {
      tree decl = TREE_VALUE (init);

      dump ("Initializer:%u for %N", count, decl);
      sec.tree_node (decl);
      sec.tree_node (TREE_PURPOSE (init));
    }

  sec.end (to, to->name (MOD_SNAME_PFX ".ini"), crc_ptr);
  dump.outdent ();

  return count;
}

bool
module_state::read_inits (unsigned count)
{
  if (!count)
    return true;

  trees_in sec (this);
  if (!sec.begin (loc, from (), from ()->find (MOD_SNAME_PFX ".ini")))
    return false;
  dump () && dump ("Reading %u initializers", count);
  dump.indent ();
  for (unsigned ix = 0; ix != count; ix++)
    {
      tree decl = sec.tree_node ();
      tree init = sec.tree_node ();

      if (sec.get_overrun ())
	break;
      dump ("Initializer:%u for %N", count, decl);
      static_aggregates = tree_cons (init, decl, static_aggregates);
    }

  dump.outdent ();
  if (!sec.end (from ()))
    return false;  
  return true;
}

/* Compare bindings for two namespaces.  Those closer to :: are
   less.  */

static int
space_cmp (const void *a_, const void *b_)
{
  depset *a = *(depset *const *)a_;
  depset *b = *(depset *const *)b_;
  tree ns_a = a->get_entity ();
  tree ns_b = b->get_entity ();

  gcc_checking_assert (ns_a != ns_b);

  /* Deeper namespaces come after shallower ones.  */
  if (int delta = int (SCOPE_DEPTH (ns_a)) - int (SCOPE_DEPTH (ns_b)))
    return delta;

  /* Otherwise order by UID for consistent results.  */
  return DECL_UID (ns_a) < DECL_UID (ns_b) ? -1 : +1;
}

/* Tool configuration:  MOD_SNAME_PFX .config

   This is data that confirms current state (or fails).  */

/* Data for config reading and writing.  */
struct module_state_config {
  const char *dialect_str;
  range_t sec_range;
  unsigned num_specializations;
  unsigned num_entities;
  unsigned num_imports;
  unsigned num_partitions;
  unsigned num_bindings;
  unsigned num_macros;
  unsigned num_inits;

public:
  module_state_config ()
    :dialect_str (get_dialect ()),
     sec_range (0,0), num_specializations (0), num_entities (0),
     num_imports (0), num_partitions (0),
     num_bindings (0), num_macros (0), num_inits (0)
  {
  }

  static void release ()
  {
    XDELETEVEC (dialect);
    dialect = NULL;
  }

private:
  static const char *get_dialect ();
  static char *dialect;
};

char *module_state_config::dialect;

/* Generate a string of the significant compilation options.
   Generally assume the user knows what they're doing, in the same way
   that object files can be mixed.  */

const char *
module_state_config::get_dialect ()
{
  if (!dialect)
    dialect = concat (get_cxx_dialect_name (cxx_dialect),
		      flag_concepts ? "/concepts" : "",
		      flag_coroutines ? "/coroutines" : "",
		      NULL);

  return dialect;
}

void
module_state::write_config (elf_out *to, module_state_config &config,
			    unsigned inner_crc)
{
  bytes_out cfg (to);

  cfg.begin ();

  /* Write version and inner crc as u32 values, for easier
     debug inspection.  */
  dump () && dump ("Writing version=%V, inner_crc=%x",
		   MODULE_VERSION, inner_crc);
  cfg.u32 (unsigned (MODULE_VERSION));
  cfg.u32 (inner_crc);

  cfg.u (to->name (is_header () ? "" : get_flatname ()));

  /* Configuration. */
  dump () && dump ("Writing target='%s', host='%s'",
		   TARGET_MACHINE, HOST_MACHINE);
  unsigned target = to->name (TARGET_MACHINE);
  unsigned host = (!strcmp (TARGET_MACHINE, HOST_MACHINE)
		   ? target : to->name (HOST_MACHINE));
  cfg.u (target);
  cfg.u (host);

  cfg.str (config.dialect_str);
  cfg.u (extensions);

  /* Global tree information.  We write the globals crc separately,
     rather than mix it directly into the overall crc, as it is used
     to ensure data match between instances of the compiler, not
     integrity of the file.  */
  dump () && dump ("Writing globals=%u, crc=%x",
		   fixed_trees->length (), global_crc);
  cfg.u (fixed_trees->length ());
  cfg.u32 (global_crc);

  if (is_partition ())
    cfg.u (is_interface ());

  cfg.u (config.num_imports);
  cfg.u (config.num_partitions);

  cfg.u (config.sec_range.first);
  cfg.u (config.sec_range.second);
  dump () && dump ("Cluster sections are [%u,%u)",
		   config.sec_range.first, config.sec_range.second);

  cfg.u (config.num_bindings);
  dump () && dump ("Bindings %u", config.num_bindings);
  cfg.u (config.num_specializations);
  dump () && dump ("Specializations %u", config.num_specializations);
  cfg.u (config.num_entities);
  dump () && dump ("Entities %u", config.num_entities);
  cfg.u (config.num_macros);
  dump () && dump ("Macros %u", config.num_macros);
  cfg.u (config.num_inits);
  dump () && dump ("Initializers %u", config.num_inits);

  /* Now generate CRC, we'll have incorporated the inner CRC because
     of its serialization above.  */
  cfg.end (to, to->name (MOD_SNAME_PFX ".cfg"), &crc);
  dump () && dump ("Writing CRC=%x", crc);
}

void
module_state::note_cmi_name ()
{
  if (!cmi_noted_p && filename)
    {
      cmi_noted_p = true;
      inform (loc, "compiled module file is %qs",
	      maybe_add_cmi_prefix (filename));
    }
}

bool
module_state::read_config (module_state_config &config)
{
  bytes_in cfg;

  if (!cfg.begin (loc, from (), MOD_SNAME_PFX ".cfg"))
    return false;

  /* Check version.  */
  unsigned my_ver = MODULE_VERSION;
  unsigned their_ver = cfg.u32 ();
  dump () && dump  (my_ver == their_ver ? "Version %V"
		    : "Expecting %V found %V", my_ver, their_ver);
  if (their_ver != my_ver)
    {
      verstr_t my_string, their_string;

      version2string (my_ver, my_string);
      version2string (their_ver, their_string);

      if (!IS_EXPERIMENTAL (my_ver)
	  || !IS_EXPERIMENTAL (their_ver)
	  || MODULE_MAJOR (my_ver) != MODULE_MAJOR (their_ver))
	{
	  /* Non-experimental or majors differ, decline.  */
	  error_at (loc, "compiled module is %sversion %s",
		    IS_EXPERIMENTAL (their_ver) ? "experimental " : "",
		    their_string);
	  inform (loc, "compiler is %sversion %s",
		  IS_EXPERIMENTAL (my_ver) ? "experimental " : "",
		  my_string);
	  cfg.set_overrun ();
	  goto done;
	}
      else
	/* Minors differ, give it a go.  */
	if (warning_at (loc, 0, "compiled module is experimental version %s",
			their_string))
	  {
	    inform (loc, "compiler is experimental version %s,"
		    " close enough? %c%c\\%c(%c%c%c)%c/%c%c",
		    my_string, 0xc2, 0xaf, '_',
		    0xe3, 0x83, 0x84,
		    '_', 0xc2, 0xaf);
	    note_cmi_name ();
	  }
    }

  /*  We wrote the inner crc merely to merge it, so simply read it
      back and forget it.  */
  cfg.u32 ();

  /* Check module name.  */
  {
    const char *their_name = from ()->name (cfg.u ());
    const char *our_name = "";

    if (!is_header ())
      our_name = get_flatname ();

    /* Header units can be aliased, so name checking is
       inappropriate.  */
    if (0 != strcmp (their_name, our_name))
      {
	error_at (loc,
		  their_name[0] && our_name[0] ? G_("module %qs found")
		  : their_name[0]
		  ? G_("header module expected, module %qs found")
		  : G_("module %qs expected, header module found"),
		  their_name[0] ? their_name : our_name);
	cfg.set_overrun ();
	goto done;
      }
  }

  /* Check the CRC after the above sanity checks, so that the user is
     clued in.  */
  {
    unsigned e_crc = crc;
    crc = cfg.get_crc ();
    dump () && dump ("Reading CRC=%x", crc);
    if (!is_direct () && crc != e_crc)
      {
	error_at (loc, "module %qs CRC mismatch", get_flatname ());
	cfg.set_overrun ();
	goto done;
      }
  }

  /* Check target & host.  */
  {
    const char *their_target = from ()->name (cfg.u ());
    const char *their_host = from ()->name (cfg.u ());
    dump () && dump ("Read target='%s', host='%s'", their_target, their_host);
    if (strcmp (their_target, TARGET_MACHINE)
	|| strcmp (their_host, HOST_MACHINE))
      {
	error_at (loc, "target & host is %qs:%qs, expected %qs:%qs",
		  their_target, TARGET_MACHINE, their_host, HOST_MACHINE);
	cfg.set_overrun ();
	goto done;
      }
  }

  /* Check compilation dialect.  This must match.  */
  {
    const char *their_dialect = cfg.str ();
    if (strcmp (their_dialect, config.dialect_str))
      {
	error_at (loc, "language dialect differs %qs, expected %qs",
		  their_dialect, config.dialect_str);
	cfg.set_overrun ();
	goto done;
      }
  }

  /* Check for extensions.  If they set any, we must have them set
     too.  */
  {
    unsigned ext = cfg.u ();
    unsigned allowed = (flag_openmp ? SE_OPENMP : 0);

    if (unsigned bad = ext & ~allowed)
      {
	if (bad & SE_OPENMP)
	  error_at (loc, "module contains OpenMP, use %<-fopenmp%> to enable");
	cfg.set_overrun ();
	goto done;
      }
    extensions = ext;
  }

  /* Check global trees.  */
  {
    unsigned their_fixed_length = cfg.u ();
    unsigned their_fixed_crc = cfg.u32 ();
    dump () && dump ("Read globals=%u, crc=%x",
		     their_fixed_length, their_fixed_crc);
    if (!flag_preprocess_only
	&& (their_fixed_length != fixed_trees->length ()
	    || their_fixed_crc != global_crc))
      {
	error_at (loc, "fixed tree mismatch");
	cfg.set_overrun ();
	goto done;
      }
  }

  /* All non-partitions are interfaces.  */
  interface_p = !is_partition () || cfg.u ();

  config.num_imports = cfg.u ();
  config.num_partitions = cfg.u ();

  /* Allocate the REMAP vector.  */
  slurp->alloc_remap (config.num_imports);

  /* Random config data.  */
  config.sec_range.first = cfg.u ();
  config.sec_range.second = cfg.u ();
  dump () && dump ("Declaration sections are [%u,%u)",
		   config.sec_range.first, config.sec_range.second);

  config.num_bindings = cfg.u ();
  dump () && dump ("Bindings %u", config.num_bindings);

  config.num_specializations = cfg.u ();
  dump () && dump ("Specializations %u", config.num_specializations);

  config.num_entities = cfg.u ();
  dump () && dump ("Entities %u", config.num_entities);

  config.num_macros = cfg.u ();
  dump () && dump ("Macros %u", config.num_macros);

  config.num_inits = cfg.u ();
  dump () && dump ("Initializers %u", config.num_inits);

  if (config.sec_range.first > config.sec_range.second
      || config.sec_range.second > from ()->get_section_limit ())
    {
      error_at (loc, "paradoxical declaration section range");
      cfg.set_overrun ();
      goto done;
    }

 done:
  return cfg.end (from ());
}

/* Use ELROND format to record the following sections:
     qualified-names	    : binding value(s)
     MOD_SNAME_PFX.README   : human readable, strings
     MOD_SNAME_PFX.ENV      : environment strings, strings
     MOD_SNAME_PFX.nms 	    : namespace hierarchy
     MOD_SNAME_PFX.bnd      : binding table
     MOD_SNAME_PFX.spc      : specialization table
     MOD_SNAME_PFX.imp      : import table
     MOD_SNAME_PFX.ent      : entity table
     MOD_SNAME_PFX.prt      : partitions table
     MOD_SNAME_PFX.om       : ordinary locations
     MOD_SNAME_PFX.mm       : macro locations
     MOD_SNAME_PFX.def      : macro definitions
     MOD_SNAME_PFX.mac      : macro index
     MOD_SNAME_PFX.ini      : inits
     MOD_SNAME_PFX.cfg      : config data
*/

void
module_state::write (elf_out *to, cpp_reader *reader)
{
  /* Figure out remapped module numbers, which might elide
     partitions.  */
  bitmap partitions = NULL;
  if (!is_header () && !is_partition ())
    partitions = BITMAP_GGC_ALLOC ();

  unsigned mod_hwm = 1;
  for (unsigned ix = 1; ix != modules->length (); ix++)
    {
      module_state *imp = (*modules)[ix];

      /* Promote any non-partition import from a partition, unless
	 we're a partition.  */
      if (!is_partition () && !imp->is_partition () && imp->from_partition_p)
	imp->direct_p = true;

      /* Write any import that is not a partition, unless we're a
	 partition.  */
      if (!partitions || !imp->is_partition ())
	imp->remap = mod_hwm++;
      else
	{
	  dump () && dump ("Partition %M %u", imp, ix);
	  bitmap_set_bit (partitions, ix);
	  imp->remap = 0;
	  /* All interface partitions must be exported.  */
	  if (imp->is_interface () && !bitmap_bit_p (exports, imp->mod))
	    {
	      error_at (imp->loc, "interface partition is not exported");
	      bitmap_set_bit (exports, imp->mod);
	    }
	}
    }

  /* Find the set of decls we must write out.  */
  depset::hash table (DECL_NAMESPACE_BINDINGS (global_namespace)->size () * 8);
  /* Add the specializations before the writables, so that we can
     detect injected friend specializations.  */
  table.add_specializations (true);
  table.add_specializations (false);
  table.add_namespace_entities (global_namespace, partitions);
  if (class_members)
    {
      table.add_class_entities (class_members);
      class_members = NULL;
    }

  /* Now join everything up.  */
  table.find_dependencies ();
  // FIXME: Find reachable GMF entities from non-emitted pieces.  It'd
  // be nice to have a flag telling us this walk's necessary.  Even
  // better to not do it (why are we making visible implementation
  // details?) Fight the spec!

  if (!table.finalize_dependencies ())
    {
      to->set_error ();
      return;
    }

#if CHECKING_P
  // FIXME: Do we need to clear this? why would we write out a
  // definition we read in?
  /* We're done verifying at-most once reading, reset to verify
     at-most once writing.  */
  delete note_defs;
  note_defs = new hash_set<tree> (1000);
#endif

  /* Determine Strongy Connected Components.  */
  vec<depset *> sccs = table.connect ();

  unsigned crc = 0;
  location_map_info map_info = prepare_maps ();
  module_state_config config;

  config.num_imports = mod_hwm;
  config.num_partitions = modules->length () - mod_hwm;

  /* depset::cluster is the cluster number,
     depset::section is unspecified scratch value.

     The following loops make use of the tarjan property that
     dependencies will be earlier in the SCCS array.  */

  /* This first loop determines the number of depsets in each SCC, and
     also the number of namespaces we're dealing with.  During the
     loop, the meaning of a couple of depset fields now change:

     depset::cluster -> size_of cluster, if first of cluster & !namespace
     depset::section -> section number of cluster (if !namespace). */

  unsigned n_spaces = 0;
  config.sec_range.first = config.sec_range.second = to->get_section_limit ();
  for (unsigned size, ix = 0; ix < sccs.length (); ix += size)
    {
      depset **base = &sccs[ix];

      /* Count the members in this cluster.  */
      for (size = 1; ix + size < sccs.length (); size++)
	{
	  if (base[size]->cluster != base[0]->cluster)
	    break;
	  base[size]->cluster = base[size]->section = 0;

	  /* Namespaces and imported entities should be their own
	     clusters.  */
	  gcc_checking_assert (base[size]->get_entity_kind ()
			       != depset::EK_NAMESPACE);
	  gcc_checking_assert (base[size]->get_entity_kind ()
			       != depset::EK_REDIRECT);
	  gcc_checking_assert (base[size]->is_binding ()
			       || !base[size]->is_import ());
	}
      base[0]->cluster = base[0]->section = 0;

      /* Sort the cluster.  Later processing makes use of the ordering
	 of others < EK_USING < EK_BINDING. */
      qsort (base, size, sizeof (depset *), cluster_cmp);

      if (base[0]->get_entity_kind () == depset::EK_NAMESPACE)
	{
	  /* A namespace decl, these are handled specially.  */
	  gcc_checking_assert (size == 1);
	  n_spaces++;
	}
      else if (base[0]->get_entity_kind () == depset::EK_REDIRECT)
	gcc_checking_assert (size == 1);
      else if (!base[0]->is_binding () && base[0]->is_import ())
	gcc_checking_assert (size == 1);
      else
	{
	  /* Save the size in the first member's cluster slot.  */
	  base[0]->cluster = size;

	  for (unsigned jx = 0; jx != size; jx++)
	    /* Set the section number.  */
	    base[jx]->section = config.sec_range.second;

	  config.sec_range.second++;
	}
    }

  /* Write the clusters.  Namespace decls are put in the spaces array.
     The meaning of depset::cluster changes to provide the
     unnamed-decl count of the depset's decl (and remains zero for
     non-decls and non-unnamed).  */
  unsigned bytes = 0;
  vec<depset *> spaces;
  spaces.create (n_spaces);

  for (unsigned size, ix = 0; ix < sccs.length (); ix += size)
    {
      depset **base = &sccs[ix];
      size = base[0]->cluster;

      if (!size)
	{
	  /* A namespace, import or redirect.  */
	  tree decl = base[0]->get_entity ();
	  depset::entity_kind ek = base[0]->get_entity_kind ();
	  const char *kind = "";
	  if (ek == depset::EK_NAMESPACE)
	    {
	      spaces.quick_push (base[0]);
	      kind = "namespace";
	    }
	  else if (ek == depset::EK_REDIRECT)
	    kind = "redirect";
	  else
	    {
	      gcc_checking_assert (base[0]->is_import ());
	      kind = "import";
	    }

	  dump (dumper::CLUSTER) && dump ("Cluster %s %N", kind, decl);
	  size = 1;
	}
      else
	{
	  /* Cluster is now used to number unnamed decls.  */
	  base[0]->cluster = 0;

	  bytes
	    += write_cluster (to, base, size, table, config.num_specializations,
			      config.num_entities, &crc);
	}
    }

  /* We'd better have written as many sections and found as many
     namespaces as we predicted.  */
  gcc_assert (config.sec_range.second == to->get_section_limit ()
	      && spaces.length () == n_spaces);

  /* Write the namespaces.  */
  spaces.qsort (space_cmp);
  write_namespaces (to, table, spaces, &crc);

  /* Write the bindings themselves.  */
  config.num_bindings = write_bindings (to, sccs, table, &crc);

  /* Write the entitites.  None happens if we contain namespaces or
     nothing. */
  if (config.num_entities)
    write_entities (to, sccs, table, config.num_entities, &crc);

  /* Write the unnamed.  */
  if (config.num_specializations)
    write_specializations (to, sccs, table, config.num_specializations, &crc);

  /* Write the import table.  */
  if (config.num_imports > 1)
    write_imports (to, &crc);

  /* Write elided partition table.  */
  if (config.num_partitions)
    write_partitions (to, config.num_partitions, &crc);

  /* Write the line maps.  */
  write_ordinary_maps (to, map_info, config.num_partitions, &crc);
  write_macro_maps (to, map_info, &crc);

  config.num_macros = header_module_p () ? write_macros (to, reader, &crc) : 0;

  /* Write initializers that header units might contain.  */
  if (is_header ())
    config.num_inits = write_inits (to, table, &crc);

  unsigned clusters = config.sec_range.second - config.sec_range.first;
  dump () && dump ("Wrote %u clusters, average %u bytes/cluster",
		   clusters, (bytes + clusters / 2) / (clusters + !clusters));

  /* And finish up.  */
  write_config (to, config, crc);

  spaces.release ();
  sccs.release ();

  /* Human-readable info.  */
  write_readme (to, config.dialect_str, extensions);
  // FIXME: Write ths info to the 'reproducer' file yet to be implemented
  // write_env (to);

  trees_out::instrument ();
  dump () && dump ("Wrote %u sections", to->get_section_limit ());
}

/* Read a CMI from FD.  E is errno from its fopen.  Reading will
   be lazy, if this is an import and flag_module_lazy is in effect.  */

void
module_state::read (int fd, int e, cpp_reader *reader)
{
  gcc_checking_assert (!slurp);
  slurp = new slurping (new elf_in (fd, e));

  /* Stop GC during reading.  */
  function_depth++;

  {
    if (!from ()->begin (loc))
      goto bail;

    module_state_config config;

    if (!read_config (config))
      goto bail;

    if (!read_ordinary_maps ())
      goto bail;

    /* Read the import table.  */
    if (config.num_imports > 1 && !read_imports (reader, line_table))
      goto bail;

    /* Read the elided partition table, if we're the primary partition.  */
    if (config.num_partitions && is_primary ()
	&& !read_partitions (config.num_partitions))
      goto bail;

    /* Determine the module's number.  */
    gcc_checking_assert (mod == MODULE_UNKNOWN);
    gcc_checking_assert (this != (*modules)[0]);

    unsigned ix = modules->length ();
    if (ix == MODULE_LIMIT)
      {
	sorry ("too many modules loaded (limit is %u)", ix);
	from ()->set_error (elf::E_BAD_IMPORT);
	goto bail;
      }

    vec_safe_push (modules, this);
    /* We always import and export ourselves. */
    bitmap_set_bit (imports, ix);
    bitmap_set_bit (exports, ix);
    if (is_header ())
      bitmap_set_bit (slurp->headers, ix);
    mod = remap = ix;

    (*slurp->remap)[0] = mod;
    dump () && dump ("Assigning %M module number %u", this, mod);

    /* We should not have been frozen during the importing done by
       read_config.  */
    gcc_assert (!from ()->is_frozen ());

    if (!read_macro_maps ())
      goto bail;

    cpp_options *cpp_opts = cpp_get_options (reader);
    if (config.num_macros && !cpp_opts->preprocessed)
      if (!read_macros ())
	goto bail;

    if (!flag_preprocess_only)
      {
	available_clusters += config.sec_range.second - config.sec_range.first;

	/* Read the namespace hierarchy. */
	vec<tree> spaces = read_namespaces ();

	bool ok = spaces.length ()
	  && read_bindings (spaces, config.num_bindings, config.sec_range);

	spaces.release ();
	if (!ok)
	  goto bail;

	/* And entities.  */
	entity_lwm = vec_safe_length (entity_ary);
	if (config.num_entities
	    && !read_entities (config.num_entities, config.sec_range))
	  goto bail;

	/* And unnamed.  */
	if (config.num_specializations
	    && !read_specializations (config.num_specializations))
	  goto bail;

	if (!flag_module_lazy)
	  {
	    /* Read the sections in forward order, so that dependencies are read
	       first.  See note about tarjan_connect.  */
	    ggc_collect ();

	    unsigned hwm = config.sec_range.second;
	    for (unsigned ix = config.sec_range.first; ix != hwm; ix++)
	      {
		load_section (ix);
		if (from ()->get_error ())
		  goto bail;
		ggc_collect ();
	      }
	    if (CHECKING_P)
	      {
		// FIXME: check we loaded everything
	      }
	  }

	// FIXME: Belfast order-of-initialization means this may be inadequate.
	if (!read_inits (config.num_inits))
	  goto bail;
      }

    /* We're done with the string and non-decl sections now.  */
    from ()->release ();
    slurp->remaining = config.sec_range.second - config.sec_range.first;
    slurp->lru = ++lazy_lru;
  }
  
 bail:
  function_depth--;
  slurp->current++;
  gcc_assert (slurp->current == ~0u);
}

void
module_state::maybe_defrost ()
{
  if (from ()->is_frozen ())
    {
      if (lazy_open >= lazy_limit)
	freeze_an_elf ();
      dump () && dump ("Defrosting '%s'", filename);
      from ()->defrost (maybe_add_cmi_prefix (filename));
      lazy_open++;
    }
}

/* Load section SNUM, dealing with laziness.  It doesn't matter if we
   have multiple concurrent loads, because we do not use TREE_VISITED
   when reading back in.  */

void
module_state::load_section (unsigned snum)
{
  maybe_defrost ();

  unsigned old_current = slurp->current;
  slurp->current = snum;
  slurp->lru = 0;  /* Do not swap out.  */
  read_cluster (snum);
  slurp->lru = ++lazy_lru;
  slurp->current = old_current;
  slurp->remaining--;
}

/* After a reading operation, make sure things are still ok.  If not,
   emit an error and clean up.  In order to get some kind of context
   information, OUTERMOST is true, if this is the outermost cause of a
   read happening (eiher an import, or a lazy binding found during
   name-lookup).  In the latter case NS and ID provide the binding.  */

bool
module_state::check_read (unsigned diag_count, tree ns, tree id)
{
  bool done = (slurp->current == ~0u
	       && (from ()->get_error () || !slurp->remaining));
  if (done)
    {
      lazy_open--;
      if (slurp->macro_defs.size)
	from ()->preserve (slurp->macro_defs);
      if (slurp->macro_tbl.size)
	from ()->preserve (slurp->macro_tbl);
      from ()->end ();
    }

  bool ok = true;
  if (int e = from ()->get_error ())
    {
      const char *err = from ()->get_error (filename);
      /* Failure to read a module is going to cause big
	 problems, so bail out, if this is the top level.
	 Otherwise return NULL to let our importer know (and
	 fail).  */
      if (slurp->remaining && id)
	error_at (loc, "failed to load binding %<%E%s%E@%s%>: %s",
		  ns, &"::"[ns == global_namespace ? 2 : 0], id,
		  get_flatname (), err);
      else
	error_at (loc, "failed to read compiled module: %s", err);
      note_cmi_name ();

      if (e == EMFILE
	  || e == ENFILE
#if MAPPED_READING
	  || e == ENOMEM
#endif
	  || false)
	inform (loc, "consider using %<-fno-module-lazy%>,"
		" reducing %<--param %s%> value,"
		" or increasing the per-process file descriptor limit",
		"?");
      ok = false;
    }

  if (done)
    {
      slurp->close ();
      if (!is_header ())
	slurped ();
    }

  if (id && diag_count <= unsigned (errorcount) && flag_module_lazy)
    inform (input_location,
	    is_header () ? G_("during lazy loading of %<%E%s%E%>")
	    : G_("during lazy loading of %<%E%s%E@%s%>"),
	    ns, ns == global_namespace ? "" : "::", id, get_flatname ());

  if (!ok && diag_count)
    fatal_error (loc, "jumping off the crazy train to crashville");

  return ok;
}

/* Return the IDENTIFIER_NODE naming module IX.  This is the name
   including dots.  */

char const *
module_name (unsigned ix, bool header_ok)
{
  if (modules)
    {
      module_state *imp = (*modules)[ix];

      if (ix && !imp->name)
	imp = imp->parent;

      if (header_ok || !imp->is_header ())
	return imp->get_flatname ();
    }

  return NULL;
}

/* Return the bitmap describing what modules are imported.  Remember,
   we always import ourselves.  */

bitmap
get_import_bitmap ()
{
  return (*modules)[0]->imports;
}

/* Return the bitmap describing what modules are visible along the
   path of instantiation.  If we're not instantiation, this will be
   the visible imports of the TU.  *PATH_MAP_P is filled in with the
   modules owning the instantiation path -- wee see the
   module-linkage entities of those modules.  */
// FIXME: Should we cache this?  smoosh it into tinst_level?

bitmap
module_visible_instantiation_path (bitmap *path_map_p)
{
  if (!modules_p ())
    return NULL;

  bitmap visible = (*modules)[0]->imports;

  if (tinst_level *path = current_instantiation ())
    {
      bitmap path_map = BITMAP_GGC_ALLOC ();
      bitmap_set_bit (path_map, 0);

      bitmap tmp = BITMAP_GGC_ALLOC ();
      bitmap_copy (tmp, visible);
      visible = tmp;
      for (; path; path = path->next)
	{
	  tree decl = path->tldcl;
	  if (TREE_CODE (decl) == TREE_LIST)
	    decl = TREE_PURPOSE (decl);
	  if (TYPE_P (decl))
	    decl = TYPE_NAME (decl);
	  if (unsigned mod = get_originating_module (decl))
	    if (!bitmap_bit_p (path_map, mod))
	      {
		bitmap_set_bit (path_map, mod);
		bitmap imports = (*modules)[mod]->imports;
		bitmap_ior_into (visible, imports);
	      }
	}
      *path_map_p = path_map;
    }

  return visible;
}

/* We've just directly imported OTHER.  Update our import/export
   bitmaps.  IS_EXPORT is true if we're reexporting the OTHER.  */

void
module_state::set_import (module_state const *other, bool is_export)
{
  gcc_checking_assert (this != other);

  /* We see OTHER's exports (which include's OTHER).
     If OTHER is the primary interface or a partition we'll see its
     imports.  */
  bitmap_ior_into (imports, other->is_primary () || other->is_partition ()
		   ? other->imports : other->exports);

  if (is_export)
    /* We'll export OTHER's exports.  */
    bitmap_ior_into (exports, other->exports);

  if (is_header () && other->is_header () && mod)
    /* We only see OTHER's headers if it is header.  */
    bitmap_ior_into (slurp->headers, other->slurp->headers);
}

/* Return the declaring entity of DECL.  That is the decl determining
   how to decorate DECL with module information.  Returns NULL_TREE if
   it's the global module.  */

tree
get_originating_module_decl (tree decl)
{
  /* An enumeration constant.  */
  if (TREE_CODE (decl) == CONST_DECL
      && DECL_CONTEXT (decl)
      && (TREE_CODE (DECL_CONTEXT (decl)) == ENUMERAL_TYPE))
    decl = TYPE_NAME (DECL_CONTEXT (decl));

  gcc_checking_assert (TREE_CODE (decl) == TEMPLATE_DECL
		       || TREE_CODE (decl) == FUNCTION_DECL
		       || TREE_CODE (decl) == TYPE_DECL
		       || TREE_CODE (decl) == VAR_DECL
		       || TREE_CODE (decl) == CONCEPT_DECL
		       || TREE_CODE (decl) == NAMESPACE_DECL);

  for (tree ctx;; decl = ctx)
    {
      ctx = CP_DECL_CONTEXT (decl);
      if (TREE_CODE (ctx) == NAMESPACE_DECL)
	break;

      if (TYPE_P (ctx))
	{
	  ctx = TYPE_NAME (ctx);
	  if (!ctx)
	    {
	      /* Some kind of internal type.  */
	      gcc_checking_assert (DECL_ARTIFICIAL (decl));
	      return global_namespace;
	    }
	}
    }

  int use;
  if (tree ti = node_template_info (decl, use))
    {
      decl = TI_TEMPLATE (ti);
      /* It could be a partial specialization, so look again.  */
      ti = node_template_info (decl, use);
      if (use > 0)
	{
	  decl = TI_TEMPLATE (ti);
	  gcc_checking_assert ((node_template_info (decl, use), use <= 0));
	}
    }

  if (TREE_CODE (decl) == TEMPLATE_DECL)
    decl = DECL_TEMPLATE_RESULT (decl);

  return decl;
}

int
get_originating_module (tree decl, bool for_mangle)
{
  tree owner = get_originating_module_decl (decl);

  if (!DECL_LANG_SPECIFIC (owner))
    return for_mangle ? -1 : 0;

  if (for_mangle
      && (DECL_MODULE_EXPORT_P (owner) || !DECL_MODULE_PURVIEW_P (owner)))
    return -1;

  return DECL_MODULE_ORIGIN (owner);
}

tree
get_instantiating_module_decl (tree decl)
{
  if (TREE_CODE (decl) == CONST_DECL
      && DECL_CONTEXT (decl)
      && (TREE_CODE (DECL_CONTEXT (decl)) == ENUMERAL_TYPE))
    decl = TYPE_NAME (DECL_CONTEXT (decl));

  gcc_checking_assert (TREE_CODE (decl) == TEMPLATE_DECL
		       || TREE_CODE (decl) == FUNCTION_DECL
		       || TREE_CODE (decl) == TYPE_DECL
		       || TREE_CODE (decl) == VAR_DECL
		       || TREE_CODE (decl) == NAMESPACE_DECL);

  for (tree ctx;; decl = ctx)
    {
      ctx = CP_DECL_CONTEXT (decl);

      if (TREE_CODE (ctx) == NAMESPACE_DECL)
	break;

      int use;
      node_template_info (decl, use);
      if (use > 0)
	break;

      if (TYPE_P (ctx))
	{
	  ctx = TYPE_NAME (ctx);
	  if (!ctx)
	    /* Always return something, global_namespace is a useful
	       non-owning decl.  */
	    return global_namespace;
	}
    }

  decl = STRIP_TEMPLATE (decl);

  return decl;
}

unsigned
get_instantiating_module (tree decl)
{
  tree owner = get_instantiating_module_decl (decl);

  if (!DECL_LANG_SPECIFIC (owner))
    return 0;

  return DECL_MODULE_ORIGIN (owner);
}

/* Is it permissible to redeclare an entity instantiated by DECL.  */
// FIXME: This needs extending, see its use in duplicate_decls

bool
module_may_redeclare (tree inst)
{
  int origin = DECL_LANG_SPECIFIC (inst) ? DECL_MODULE_ORIGIN (inst) : 0;

  module_state *them = (*modules)[origin];
  module_state *me = (*modules)[0];

  if (them->is_header ())
    /* If it came from a header, it's in the global module.  */
    return (me->is_header ()
	    || !module_purview_p ());

  if (!origin)
    return ((DECL_LANG_SPECIFIC (inst) && DECL_MODULE_PURVIEW_P (inst))
	    == module_purview_p ());

  if (!me->name)
    me = me->parent;

  /* We can't have found a GMF entity from a named module.  */
  gcc_checking_assert (DECL_LANG_SPECIFIC (inst)
		       && DECL_MODULE_PURVIEW_P (inst));

  return me && get_primary (them) == get_primary (me);
}

/* DECL is being created by this TU.  Record it came from here.  We
   record module purview, so we can see if partial or explicit
   specialization needs to be written out, even though its purviewness
   comes from the most general template.  */

void
set_instantiating_module (tree decl)
{
  gcc_assert (TREE_CODE (decl) == FUNCTION_DECL
	      || TREE_CODE (decl) == VAR_DECL
	      || TREE_CODE (decl) == TYPE_DECL
	      || TREE_CODE (decl) == CONCEPT_DECL);

  if (!modules_p ())
    return;

  if (!DECL_LANG_SPECIFIC (decl) && module_purview_p ())
    retrofit_lang_decl (decl);
  if (DECL_LANG_SPECIFIC (decl))
    {
      DECL_MODULE_PURVIEW_P (decl) = module_purview_p ();
      DECL_MODULE_ORIGIN (decl) = 0;
    }

  int use_tpl = -1;
  tree ti = node_template_info (decl, use_tpl);
  if (use_tpl <= 0)
    {
      tree ctx = CP_DECL_CONTEXT (decl);
      if (TYPE_P (ctx))
	ctx = TYPE_NAME (ctx);

      if (TREE_CODE (ctx) != NAMESPACE_DECL
	  && DECL_LANG_SPECIFIC (ctx)
	  && DECL_MODULE_ORIGIN (ctx))
	{
	  if (ti)
	    {
	      gcc_checking_assert (!use_tpl);
	      /* Get to the TEMPLATE_DECL.  */
	      decl = TI_TEMPLATE (ti);
	    }

	  /* Record it on the innner_decls list.  */
	  vec_safe_push (class_members, decl);
	}
    }
}

void
set_originating_module (tree decl, bool friend_p ATTRIBUTE_UNUSED)
{
  set_instantiating_module (decl);

  if (TREE_CODE (CP_DECL_CONTEXT (decl)) != NAMESPACE_DECL)
    return;

  gcc_checking_assert (friend_p || decl == get_originating_module_decl (decl));

  if (!module_exporting_p ())
    return;

  // FIXME: Check ill-formed linkage
  DECL_MODULE_EXPORT_P (decl) = true;
}

/* Create the flat name string.  It is simplest to have it handy.  */

void
module_state::set_flatname ()
{
  gcc_checking_assert (!flatname);
  if (parent)
    {
      auto_vec<tree,5> ids;
      size_t len = 0;
      char const *primary = NULL;
      size_t pfx_len = 0;

      for (module_state *probe = this;
	   probe;
	   probe = probe->parent)
	if (is_partition () && !probe->is_partition ())
	  {
	    primary = probe->get_flatname ();
	    pfx_len = strlen (primary);
	    break;
	  }
	else
	  {
	    ids.safe_push (probe->name);
	    len += IDENTIFIER_LENGTH (probe->name) + 1;
	  }

      char *flat = XNEWVEC (char, pfx_len + len + is_partition ());
      flatname = flat;

      if (primary)
	{
	  memcpy (flat, primary, pfx_len);
	  flat += pfx_len;
	  *flat++ = ':';
	}

      for (unsigned len = 0; ids.length ();)
	{
	  if (len)
	    flat[len++] = '.';
	  tree elt = ids.pop ();
	  unsigned l = IDENTIFIER_LENGTH (elt);
	  memcpy (flat + len, IDENTIFIER_POINTER (elt), l + 1);
	  len += l;
	}
    }
  else if (is_header ())
    flatname = TREE_STRING_POINTER (name);
  else
    flatname = IDENTIFIER_POINTER (name);
}

/* Read the CMI file for a module.  FNAME, if not NULL, is the name we
   know it as.  */

bool
module_state::do_import (char const *fname, cpp_reader *reader)
{
  gcc_assert (global_namespace == current_scope ()
	      && !is_imported () && loc != UNKNOWN_LOCATION);
  unsigned diags = is_direct () ? errorcount + 1 : 0;

  if (lazy_open >= lazy_limit)
    freeze_an_elf ();

  if (fname)
    {
      gcc_assert (!filename);
      filename = xstrdup (fname);
    }

  if (mkdeps *deps = cpp_get_deps (reader))
    deps_add_module (deps, get_flatname ());

  int fd = -1;
  int e = ENOENT;
  if (filename)
    {
      const char *file = maybe_add_cmi_prefix (filename);
      dump () && dump ("CMI is %s", file);
      fd = open (file, O_RDONLY | O_CLOEXEC);
      e = errno;
    }

  announce ("importing");
  imported_p = true;
  lazy_open++;
  read (fd, e, reader);
  bool ok = check_read (diags);
  // FIXME: The below conditional looks odd.  I don't think we ever
  // now import MODULE_CURRENT, even in module implementation units?
  announce (flag_module_lazy && mod ? "lazy" : "imported");

  return ok;
}

/* Import this module now.  Fatal error on failure.  LAZY is true if
   we're a lazy pending imports (which will have preserved the line
   map already).  */

void
module_state::direct_import (cpp_reader *reader, bool lazy)
{
  timevar_start (TV_MODULE_IMPORT);
  unsigned n = dump.push (this);

  direct_p = true;
  if (!is_imported () && mod == MODULE_UNKNOWN)
    {
      char *fname = NULL;
      unsigned pre_hwm = 0;

      if (!lazy)
	{
	  /* Preserve the state of the line-map.  */
	  pre_hwm = LINEMAPS_ORDINARY_USED (line_table);
	  if (module_has_cmi_p ())
	    spans.close ();

	  maybe_create_loc ();
	  fname = module_mapper::import_export (this, false);
	}

      if (!do_import (fname, reader)
	  && !flag_preprocess_only)
	fatal_error (loc, "returning to gate for a mechanical issue");

      /* Restore the line-map state.  */
      if (!lazy)
	{
	  linemap_module_restore (line_table, pre_hwm);
	  if (module_has_cmi_p ())
	    spans.open ();
	}
    }

  if (is_imported ())
    {
      direct_p = true;
      if (exported_p)
	exported_p = true;

      (*modules)[0]->set_import (this, exported_p);
      if (is_header ())
	import_macros ();
    }

  dump.pop (n);
  timevar_stop (TV_MODULE_IMPORT);
}

/* Attempt to increase the file descriptor limit.  */

static bool
try_increase_lazy (unsigned want)
{
  gcc_checking_assert (lazy_open >= lazy_limit);

  /* If we're increasing, saturate at hard limit.  */
  if (want > lazy_hard_limit && lazy_limit < lazy_hard_limit)
    want = lazy_hard_limit;

#if HAVE_SETRLIMIT
  if ((!lazy_limit || !param_lazy_modules)
      && lazy_hard_limit
      && want <= lazy_hard_limit)
    {
      struct rlimit rlimit;
      rlimit.rlim_cur = want + LAZY_HEADROOM;
      rlimit.rlim_max = lazy_hard_limit + LAZY_HEADROOM;
      if (!setrlimit (RLIMIT_NOFILE, &rlimit))
	lazy_limit = want;
    }
#endif

  return lazy_open < lazy_limit;
}

/* Pick a victim module to freeze its reader.  */

void
module_state::freeze_an_elf ()
{
  if (try_increase_lazy (lazy_open * 2))
    return;

  module_state *victim = NULL;
  for (unsigned ix = modules->length (); ix--;)
    {
      module_state *candidate = (*modules)[ix];
      if (candidate && candidate->slurp && candidate->slurp->lru
	  && candidate->from ()->is_freezable ()
	  && (!victim || victim->slurp->lru > candidate->slurp->lru))
	victim = candidate;
    }

  if (victim)
    {
      dump () && dump ("Freezing '%s'", victim->filename);
      if (victim->slurp->macro_defs.size)
	/* Save the macro definitions to a buffer.  */
	victim->from ()->preserve (victim->slurp->macro_defs);
      if (victim->slurp->macro_tbl.size)
	/* Save the macro definitions to a buffer.  */
	victim->from ()->preserve (victim->slurp->macro_tbl);
      victim->from ()->freeze ();
      lazy_open--;
    }
  else
    dump () && dump ("No module available for freezing");
}

/* *SLOT is a lazy binding in namespace NS named ID.  Load it, or die
   trying.  */
// FIXME: Should we emit something when noisy ()?
// FIXME: Reconsider API when no longer indexing by name
bool
module_state::lazy_load (unsigned index, mc_slot *mslot, unsigned diags)
{
  unsigned n = dump.push (this);

  gcc_checking_assert (function_depth);

  unsigned snum = mslot->get_lazy ();
  dump () && dump ("Loading entity %M[%u] section:%u", this, index, snum);

  int e = elf::E_BAD_LAZY;
  if (snum < slurp->current)
    {
      load_section (snum);
      e = elf::E_BAD_DATA;
    }

  if (mslot->is_lazy ())
    {
      /* Oops, the section didn't set this slot.  */
      from ()->set_error (e);
      *mslot = NULL_TREE;
    }

  bool ok = check_read (diags);
 
  dump.pop (n);

  return ok;
}

/* Load MOD's binding for NS::ID into *MSLOT.  *MSLOT contains the
   lazy cookie.  OUTER is true if this is the outermost lazy, (used
   for diagnostics).  */

void
lazy_load_binding (unsigned mod, tree ns, tree id, mc_slot *mslot)
{
  timevar_start (TV_MODULE_IMPORT);

  gcc_checking_assert (mod);
  module_state *module = (*modules)[mod];
  unsigned n = dump.push (module);

  /* Stop GC happening, even in outermost loads (because our caller
     could well be building up a lookup set).  */
  function_depth++;

  unsigned snum = mslot->get_lazy ();
  dump () && dump ("Lazily binding %P@%N section:%u", ns, id,
		   module->name, snum);

  unsigned diags = errorcount + 1;
  module->load_section (snum);

  if (mslot->is_lazy ())
    {
      /* Oops, the section didn't set this slot.  */
      module->from ()->set_error (elf::E_BAD_DATA);
      *mslot = NULL_TREE;
    }

  function_depth--;

  module->check_read (diags, ns, id);

  dump.pop (n);
  timevar_stop (TV_MODULE_IMPORT);
}

/* Load any pending specializations of TMPL.  Called just before
   instantiating TMPL.  */

void
lazy_load_specializations (tree tmpl)
{
  gcc_checking_assert (DECL_TEMPLATE_LAZY_SPECIALIZATIONS_P (tmpl));

  tree owner = get_originating_module_decl (tmpl);

  timevar_start (TV_MODULE_IMPORT);
  if (specset *set
      = specset::table->lookup (CP_DECL_CONTEXT (owner), DECL_NAME (owner)))
    {
      unsigned n = dump.push (NULL);
      dump () && dump ("Reading %u pending specializations keyed to %N",
		       set->num, owner);
      function_depth++; /* Prevent GC */
      for (unsigned ix = 0; ix != set->num; ix++)
	{
	  unsigned index = set->pending[ix];
	  mc_slot *slot = &(*entity_ary)[index];
	  if (slot->is_lazy ())
	    {
	      module_state *module = import_entity_module (index);
	      module->lazy_load (index - module->entity_lwm, slot,
				 errorcount + 1);
	    }
	  else
	    dump () && dump ("Specialization %u already loaded", ix);
	}
      function_depth--;

      note_loaded_specializations (set->ns, set->name);

      /* We own set, so delete it now.  */
      delete set;
      dump.pop (n);
    }
  timevar_stop (TV_MODULE_IMPORT);
}

/* Import the module NAME into the current TU and maybe re-export it.
   Return true if the import affects macro state.  */

bool
import_module (module_state *imp, location_t from_loc, bool exporting,
	       tree, cpp_reader *reader, bool /*in_extern_c*/)
{
  if (module_exporting_p ())
    exporting = true;

  gcc_assert (global_namespace == current_scope ());
  from_loc = ordinary_loc_of (line_table, from_loc);

  if (!imp->check_not_purview (from_loc))
    return false;

  if (imp->is_detached ())
    imp->attach (from_loc);

  if (exporting)
    imp->exported_p = true;

  if (imp->is_header ())
    imp->direct_import (reader, false);
  else
    vec_safe_push (pending_imports, imp);

  return imp->is_header ();
}

/* Declare the name of the current module to be NAME.  EXPORTING_p is
   true if this TU is the exporting module unit.  */

bool
declare_module (module_state *state, location_t from_loc, bool exporting_p,
		tree, cpp_reader *)
{
  gcc_assert (global_namespace == current_scope ());
  from_loc = ordinary_loc_of (line_table, from_loc);

  module_state *current = (*modules)[0];
  if (module_purview_p () || !state->is_detached ())
    {
      if (module_purview_p ())
	state = current;

      error_at (from_loc, module_purview_p ()
		? G_("module already declared")
		: G_("module already imported"));
      inform (state->from_loc,
	      module_purview_p ()
	      ? G_("module %qs declared here")
	      : G_("module %qs imported here"),
	      state->get_flatname ());
      return false;
    }

  state->attach (from_loc);

  /* Yer a module, 'arry.  */
  module_kind &= ~MK_GLOBAL;
  module_kind |= MK_MODULE;

  if (state->is_partition () || exporting_p)
    {
      if (state->is_partition ())
	module_kind |= MK_PARTITION;

      if (exporting_p)
	{
	  state->interface_p = true;
	  module_kind |= MK_INTERFACE;
	}

      if (state->is_header ())
	module_kind |= MK_GLOBAL | MK_EXPORTING;

      /* Copy the importing information we may have already done.  */
      state->imports = current->imports;

      state->mod = 0;
      (*modules)[0] = state;
    }
  else
    {
      state->primary_p = state->interface_p = true;
      current->parent = state; /* So mangler knows module identity. */
    }

  vec_safe_push (pending_imports, state);

  return true;
}

/* Track if NODE undefs an imported macro.  */

void
module_cpp_undef (cpp_reader *reader, location_t loc, cpp_hashnode *node)
{
  if (!header_module_p ())
    {
      /* Turn us off.  */
      struct cpp_callbacks *cb = cpp_get_callbacks (reader);
      if (cb->undef == lang_hooks.preprocess_undef)
	{
	  cb->undef = NULL;
	  lang_hooks.preprocess_undef = NULL;
	}
    }
  if (lang_hooks.preprocess_undef)
    module_state::undef_macro (reader, loc, node);
}

cpp_macro *
module_cpp_deferred_macro (cpp_reader *reader, location_t loc,
			   cpp_hashnode *node)
{
  return module_state::deferred_macro (reader, loc, node);
}

/* NAME & LEN are a preprocessed header name, possibly including the
   surrounding "" or <> characters.  Return the raw string name of the
   module to which it refers.  This will be an absolute path, or begin
   with ./, so it is immediately distinguishable from a (non-header
   unit) module name.  If READER is non-null, ask the preprocessor to
   locate the header to which it refers using the appropriate include
   path.  Note that we do never do \ processing of the string, as that
   matches the preprocessor's behaviour.  */

static const char *
canonicalize_header_name (cpp_reader *reader, location_t loc, bool unquoted,
			  const char *str, size_t &len_r)
{
  size_t len = len_r;
  static char *buf = 0;
  static size_t alloc = 0;

  if (!unquoted)
    {
      gcc_checking_assert (len >= 2
			   && ((reader && str[0] == '<' && str[len-1] == '>')
			       || (str[0] == '"' && str[len-1] == '"')));
      str += 1;
      len -= 2;
    }

  if (reader)
    {
      gcc_assert (!unquoted);

      if (len >= alloc)
	{
	  alloc = len + 1;
	  buf = XRESIZEVEC (char, buf, alloc);
	}
      memcpy (buf, str, len);
      buf[len] = 0;

      if (const char *hdr
	  = cpp_find_header_unit (reader, buf, str[-1] == '<', loc))
	{
	  len = strlen (hdr);
	  str = hdr;
	}
      else
	str = buf;
    }

  if (!(str[0] == '.' ? IS_DIR_SEPARATOR (str[1]) : IS_ABSOLUTE_PATH (str)))
    {
      /* Prepend './'  */
      if (len + 3 > alloc)
	{
	  alloc = len + 3;
	  buf = XRESIZEVEC (char, buf, alloc);
	}

      buf[0] = '.';
      buf[1] = DIR_SEPARATOR;
      memmove (buf + 2, str, len);
      len += 2;
      buf[len] = 0;
      str = buf;
    }

  len_r = len;
  return str;
}

tree
module_map_header (cpp_reader *reader, location_t loc, bool search,
		   const char *str, size_t len)
{
  str = canonicalize_header_name (search ? reader : NULL, loc, false, str, len);
  return build_string (len, str);
}

/* Figure out whether to treat HEADER as an include or an import.  */

bool
module_translate_include (cpp_reader *reader, line_maps *lmaps, location_t loc,
			  const char *path)
{
  if (!modules_p ())
    {
      /* Turn off.  */
      cpp_get_callbacks (reader)->translate_include = NULL;
      return false;
    }

  if (!spans.init_p ())
    /* Before the main file, don't divert.  */
    return false;

  dump.push (NULL);

  dump (dumper::MAPPER) && dump ("Checking include translation '%s'", path);
  bool res = false;
  module_mapper *mapper = module_mapper::get (loc);
  if (mapper->is_live ())
    {
      size_t len = strlen (path);
      path = canonicalize_header_name (NULL, loc, true, path, len);
      res = mapper->translate_include (loc, path, len);

      bool note = false;

      if (note_include_translate < 0)
	note = true;
      else if (note_include_translate > 0 && res)
	note = true;
      else if (note_includes)
	{
	  /* We do not expect the note_includes vector to be large, so O(N)
	     iteration.  */
	  for (unsigned ix = note_includes->length (); !note && ix--;)
	    {
	      const char *hdr = (*note_includes)[ix];
	      if (!strcmp (hdr, path))
		note = true;
	    }
	}

      if (note)
	inform (loc, res
		? G_("include %qs translated to import")
		: G_("include %qs processed textually") , path);
    }

  dump (dumper::MAPPER) && dump (res ? "Translating include to import"
				 : "Keeping include as include");

  if (res)
    {
      /* Push the translation text.  */
      loc = ordinary_loc_of (lmaps, loc);
      const line_map_ordinary *map
	= linemap_check_ordinary (linemap_lookup (lmaps, loc));
      unsigned col = SOURCE_COLUMN (map, loc);
      col -= (col != 0); /* Columns are 1-based.  */

      size_t len = strlen (path);
      char *res = XNEWVEC (char, len + 60 + col);

      /* Internal keyword to permit use inside extern "C" {...}.
	 Bad glibc! No biscuit!  */
      strcpy (res, "__import");
      size_t actual = 8;
      if (col > actual)
	{
	  memset (res + actual, ' ', col - actual);
	  actual = col;
	}
      /* No need to encode characters, that's not how header names are
	 handled.  */
      res[actual++] = '"';
      memcpy (res + actual, path, len);
      actual += len;
      res[actual++] = '"';
      strcpy (res + actual, ";\n\n");
      actual += 3;
      /* cpplib will delete the buffer.  */
      cpp_push_buffer (reader, reinterpret_cast<unsigned char *> (res),
		       actual, false);
    }
  dump.pop (0);

  return res;
}

void
module_preprocess (mkdeps *deps, module_state *state, int is_module)
{
  if (is_module)
    /* Record the module, so that partition imports resolve
       correctly.  */
    (*modules)[0] = state;

  if (!state->flatname)
    state->set_flatname ();

  const char *path = NULL;
  if (is_module > 0
      /* Partitions always produce a CMI.  */
      || (is_module < 0 && state->is_partition ()))
    {
      path = state->filename;
      if (!path)
	path = module_mapper::import_export (state, true);
      path = path ? maybe_add_cmi_prefix (path) : "";
    }

  deps_add_module (deps, state->get_flatname (),
		   path, state->is_header ());
}

/* We've just properly entered the main source file.  I.e. after the
   command line, builtins and forced headers.  Record the line map and
   location of this map.  Note we may be called more than once.  The
   first call sticks.  */

void
module_begin_main_file (cpp_reader *reader, line_maps *lmaps,
		       const line_map_ordinary *map)
{
  gcc_checking_assert (lmaps == line_table);
  if (modules_p () && !spans.init_p ())
    {
      unsigned n = dump.push (NULL);
      spans.init (lmaps, map);
      dump.pop (n);
      if (flag_header_unit)
	{
	  /* Tell the preprocessor this is an include file.  */
	  cpp_retrofit_as_include (reader);
	  /* Set the module header name from the main_input_filename.  */
	  const char *main = main_input_filename;
	  size_t len = strlen (main);
	  main = canonicalize_header_name (NULL, 0, true, main, len);
	  module_state *state = get_module (build_string (len, main));
	  if (!flag_preprocess_only)
	    {
	      declare_module (state, spans.main_start (), true, NULL, reader);
	      process_deferred_imports (reader);
	    }
	  else if (mkdeps *deps = cpp_get_deps (reader))
	    module_preprocess (deps, state, 1);
	}
    }
}

/* Process any deferred imports.   */

void
process_deferred_imports (cpp_reader *reader)
{
  if (!vec_safe_length (pending_imports))
    return;

  dump.push (NULL);
  dump () && dump ("Processing %u deferred imports",
		   vec_safe_length (pending_imports));

  /* Preserve the state of the line-map.  */
  unsigned pre_hwm = LINEMAPS_ORDINARY_USED (line_table);
  if (module_has_cmi_p ())
    spans.close ();

  module_state *imp = (*pending_imports)[0];
  module_mapper *mapper = module_mapper::get (imp->from_loc);
  bool has_bmi = !imp->mod;
  bool any = false;

  timevar_start (TV_MODULE_MAPPER);
  if (mapper->is_server ())
    /* Send batched request to mapper.  */
    for (unsigned ix = 0; ix != pending_imports->length (); ix++)
      {
	imp = (*pending_imports)[ix];
	if (!imp->filename && !imp->imported_p)
	  {
	    /* The user may be directly importing the same module
	       twice in a single block (they do this kind of thing).
	       We only want one filename request, abuse the imported
	       flag to do that.  */
	    imp->imported_p = true;
	    if (!any)
	      mapper->cork ();
	    any = true;
	    mapper->imex_query (imp, !ix && has_bmi);
	  }
      }

  if (any)
    mapper->uncork (imp->from_loc);

  for (unsigned ix = 0; ix != pending_imports->length (); ix++)
    {
      imp = (*pending_imports)[ix];

      /* Read the mapper's responses.  */
      if (any && !imp->filename)
	{
	  imp->imported_p = false;
	  if (char *fname = mapper->imex_response (imp))
	    imp->filename = xstrdup (fname);
	}

      imp->maybe_create_loc ();
    }

  if (any)
    mapper->maybe_uncork (imp->loc);
  timevar_stop (TV_MODULE_MAPPER);

  /* Now do the importing, which might cause additional requests
     (although nested import filenames are usually in their
     importer's import table).  */
  for (unsigned ix = has_bmi ? 1 : 0;
       ix != pending_imports->length (); ix++)
    {
      module_state *imp = (*pending_imports)[ix];
      imp->direct_import (reader, true);
    }

  dump.pop (0);

  vec_free (pending_imports);

  linemap_module_restore (line_table, pre_hwm);
  if (module_has_cmi_p ())
    spans.open ();
}

/* VAL is a global tree, add it to the global vec if it is
   interesting.  Add some of its targets, if they too are
   interesting.  */

static int
maybe_add_global (tree val, unsigned &crc)
{
  int v = 0;

  if (val && !(identifier_p (val) || TREE_VISITED (val)))
    {
      TREE_VISITED (val) = true;
      crc = crc32_unsigned (crc, fixed_trees->length ());
      vec_safe_push (fixed_trees, val);
      v++;

      if (CODE_CONTAINS_STRUCT (TREE_CODE (val), TS_TYPED))
	v += maybe_add_global (TREE_TYPE (val), crc);
      if (CODE_CONTAINS_STRUCT (TREE_CODE (val), TS_TYPE_COMMON))
	v += maybe_add_global (TYPE_NAME (val), crc);
    }

  return v;
}

/* Initialize module state.  Create the hash table, determine the
   global trees.  Create the module for current TU.  */

void
init_module_processing (cpp_reader *reader)
{
  /* PCH should not be reachable because of lang-specs, but the
     user could have overriden that.  */
  if (pch_file)
    fatal_error (input_location,
		 "C++ modules are incompatible with precompiled headers");

  if (cpp_get_options (reader)->traditional)
    fatal_error (input_location,
		 "C++ modules are incompatible with traditional preprocessing");

  if (flag_preprocess_only)
    {
      cpp_options *cpp_opts = cpp_get_options (reader);
      if (flag_no_output
	  || (cpp_opts->deps.style != DEPS_NONE
	      && !cpp_opts->deps.need_preprocessor_output))
	{
	  warning (0, flag_dump_macros == 'M'
		   ? G_("macro debug output may be incomplete with modules")
		   : G_("module dependencies require full preprocessing"));
	  if (cpp_opts->deps.style != DEPS_NONE)
	    inform (input_location, "you should use the %<-%s%> option",
		    cpp_opts->deps.style == DEPS_SYSTEM ? "MD" : "MMD");
	}
    }

  /* :: is always exported.  */
  DECL_MODULE_EXPORT_P (global_namespace) = true;

  modules_hash = hash_table<module_state_hash>::create_ggc (31);
  vec_safe_reserve (modules, 20);

  /* Create module for current TU.  */
  module_state *current
    = new (ggc_alloc<module_state> ()) module_state (NULL_TREE, NULL, false);
  current->mod = 0;
  bitmap_set_bit (current->imports, 0);
  modules->quick_push (current);

  gcc_checking_assert (!fixed_trees);

  headers = BITMAP_GGC_ALLOC ();

  if (note_includes)
    for (unsigned ix = 0; ix != note_includes->length (); ix++)
      {
	const char *hdr = (*note_includes)[ix];
	size_t len = strlen (hdr);

	bool system = hdr[0] == '<';
	bool user = hdr[0] == '"';
	// FIXME: Check terminator matches

	hdr = canonicalize_header_name (system || user ? reader : NULL,
					0, !(system || user), hdr, len);
	char *path = XNEWVEC (char, len + 1);
	memcpy (path, hdr, len);
	path[len+1] = 0;

	(*note_includes)[ix] = path;
      }

  dump.push (NULL);

  /* Determine lazy handle bound.  */
  {
    unsigned limit = 1000;
#if HAVE_GETRLIMIT
    struct rlimit rlimit;
    if (!getrlimit (RLIMIT_NOFILE, &rlimit))
      {
	lazy_hard_limit = (rlimit.rlim_max < 1000000
			   ? unsigned (rlimit.rlim_max) : 1000000);
	lazy_hard_limit = (lazy_hard_limit > LAZY_HEADROOM
			   ? lazy_hard_limit - LAZY_HEADROOM : 0);
	if (rlimit.rlim_cur < limit)
	  limit = unsigned (rlimit.rlim_cur);
      }
#endif
    limit = limit > LAZY_HEADROOM ? limit - LAZY_HEADROOM : 1;

    if (unsigned parm = param_lazy_modules)
      {
	if (parm <= limit || !lazy_hard_limit || !try_increase_lazy (parm))
	  lazy_limit = parm;
      }
    else
      lazy_limit = limit;
  }

  if (dump ())
    {
      verstr_t ver;
      version2string (MODULE_VERSION, ver);
      dump ("Source: %s", main_input_filename);
      dump ("Compiler: %s", version_string);
      dump ("Modules: %s", ver);
      dump ("Checking: %s",
#if CHECKING_P
	    "checking"
#elif ENABLE_ASSERT_CHECKING
	    "asserting"
#else
	    "release"
#endif
	    );
      dump ("Compiled by: "
#ifdef __GNUC__
	    "GCC %d.%d, %s", __GNUC__, __GNUC_MINOR__,
#ifdef __OPTIMIZE__
	    "optimizing"
#else
	    "not optimizing"
#endif
#else
	    "not GCC"
#endif
	    );
      dump ("Reading: %s", MAPPED_READING ? "mmap" : "fileio");
      dump ("Writing: %s", MAPPED_WRITING ? "mmap" : "fileio");
      dump ("Lazy limit: %u", lazy_limit);
      dump ("Lazy hard limit: %u", lazy_hard_limit);
      dump ("");
    }

  /* Construct the global tree array.  This is an array of unique
     global trees (& types).  Do this now, rather than lazily, as
     some global trees are lazily created and we don't want that to
     mess with our syndrome of fixed trees.  */
  unsigned crc = 0;
  vec_alloc (fixed_trees, 200);

  dump () && dump ("+Creating globals");
  /* Insert the TRANSLATION_UNIT_DECL.  */
  TREE_VISITED (DECL_CONTEXT (global_namespace)) = true;
  fixed_trees->quick_push (DECL_CONTEXT (global_namespace));
  for (unsigned jx = 0; global_tree_arys[jx].first; jx++)
    {
      const tree *ptr = global_tree_arys[jx].first;
      unsigned limit = global_tree_arys[jx].second;

      for (unsigned ix = 0; ix != limit; ix++, ptr++)
	{
	  !(ix & 31) && dump ("") && dump ("+\t%u:%u:", jx, ix);
	  unsigned v = maybe_add_global (*ptr, crc);
	  dump () && dump ("+%u", v);
	}
    }
  global_crc = crc32_unsigned (crc, fixed_trees->length ());
  dump ("") && dump ("Created %u unique globals, crc=%x",
		     fixed_trees->length (), global_crc);
  for (unsigned ix = fixed_trees->length (); ix--;)
    TREE_VISITED ((*fixed_trees)[ix]) = false;

  dump.pop (0);

  if (!flag_module_lazy)
    /* Get the mapper now, if we're not being lazy.  */
    module_mapper::get (BUILTINS_LOCATION);

  if (!flag_preprocess_only)
    {
      specset::table = new specset::hash (EXPERIMENT (1, 400));

      entity_map = new entity_map_t (EXPERIMENT (1, 400));
      vec_safe_reserve (entity_ary, EXPERIMENT (1, 400));
    }

#if CHECKING_P
  note_defs = new hash_set<tree> (1000);
#endif

  /* Collect here to make sure things are tagged correctly (when
     aggressively GC'd).  */
  ggc_collect ();
}

/* If NODE is a deferred macro, load it.  */

static int
load_macros (cpp_reader *reader, cpp_hashnode *node, void *)
{
  location_t main_loc
    = MAP_START_LOCATION (LINEMAPS_ORDINARY_MAP_AT (line_table, 0));

  if (cpp_user_macro_p (node)
      && !node->value.macro)
    {
      cpp_macro *macro = cpp_get_deferred_macro (reader, node, main_loc);
      dump () && dump ("Loaded macro #%s %I",
		       macro ? "define" : "undef", identifier (node));
    }

  return 1;
}

/* Write the CMI, if we're a module interface.  */

void
finish_module_processing (cpp_reader *reader)
{
  if (header_module_p ())
    module_kind &= ~MK_EXPORTING;

  if (warn_imported_macros)
    {
      /* Force loading of any remaining deferred macros.  This will
	 produce diagnostics if they are ill-formed.  */
      unsigned n = dump.push (NULL);
      cpp_forall_identifiers (reader, load_macros, NULL);
      dump.pop (n);
    }

  if (!modules || !(*modules)[0]->name)
    {
      if (flag_module_only)
	warning (0, "%<-fmodule-only%> used for non-interface");
    }
  else if (!flag_syntax_only)
    {
      int fd = -1;
      int e = ENOENT;

      timevar_start (TV_MODULE_EXPORT);

      spans.close ();
      /* Force a valid but empty line map at the end.  This simplifies
	 the line table preparation and writing logic.  */
      linemap_add (line_table, LC_ENTER, false, "", 0);

      /* We write to a tmpname, and then atomically rename.  */
      const char *path = NULL;
      char *tmp_name = NULL;
      module_state *state = (*modules)[0];

      unsigned n = dump.push (state);
      state->announce ("creating");
      // FIXME: A default for the -fmodule-header case?
      if (state->filename)
	{
	  size_t len = 0;
	  path = maybe_add_cmi_prefix (state->filename, &len);
	  tmp_name = XNEWVEC (char, len + 3);
	  memcpy (tmp_name, path, len);
	  strcpy (&tmp_name[len], "~");

	  if (mkdeps *deps = cpp_get_deps (reader))
	    deps_add_module (deps, state->get_flatname (), path,
			     state->is_header ());

	  if (!errorcount)
	    for (unsigned again = 2; ; again--)
	      {
		fd = open (tmp_name, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC,
			   S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
		e = errno;
		if (fd >= 0 || !again || e != ENOENT)
		  break;
		create_dirs (tmp_name);
	      }
	  dump () && dump ("CMI is %s", path);
	}

      if (errorcount)
	warning_at (state->from_loc, 0,
		    "not writing module %qs due to errors",
		    state->get_flatname ());
      else
	{
	  elf_out to (fd, e);
	  if (to.begin ())
	    state->write (&to, reader);
	  if (to.end ())
	    if (rename (tmp_name, path))
	      to.set_error (errno);

	  if (to.get_error ())
	    {
	      error_at (state->from_loc,
			"failed to write compiled module: %s",
			to.get_error (state->filename));
	      state->note_cmi_name ();
	    }
	}

      if (!errorcount)
	module_mapper::export_done (state);
      else if (path)
	{
	  /* We failed, attempt to erase all evidence we even tried.  */
	  unlink (tmp_name);
	  unlink (path);
	  XDELETEVEC (tmp_name);
	}

      dump.pop (n);
      timevar_stop (TV_MODULE_EXPORT);

      ggc_collect ();
    }

  if (modules)
    {
      unsigned n = dump.push (NULL);
      dump () && dump ("Imported %u modules", modules->length () - 1);
      dump () && dump ("Containing %u clusters", available_clusters);
      dump () && dump ("Loaded %u clusters (%u%%)", loaded_clusters,
		       (loaded_clusters * 100 + 50) /
		       (available_clusters + !available_clusters));
      dump.pop (n);
    }

  /* We're done with the macro tables now.  */
  vec_free (macro_exports);
  vec_free (macro_imports);
  headers = NULL;

  /* We're now done with everything but the module names.  */
  set_cmi_repo (NULL);
  module_mapper::fini (input_location);
  module_state_config::release ();

#if CHECKING_P
  delete note_defs;
  note_defs = NULL;
#endif

  if (modules)
    for (unsigned ix = modules->length (); --ix;)
      if (module_state *state = (*modules)[ix])
	state->release ();

  /* No need to lookup modules anymore.  */
  modules_hash = NULL;

  /* Or entities.  */
  delete entity_map;
  entity_map = NULL;
  delete entity_ary;
  entity_ary = NULL;
  
  /* Or remember any pending specializations.  */
  delete specset::table;
  specset::table = NULL;

  /* Allow a GC, we've possibly made much data unreachable.  */
  ggc_collect ();
}

/* If CODE is a module option, handle it & return true.  Otherwise
   return false.  For unknown reasons I cannot get the option
   generation machinery to set fmodule-mapper or -fmodule-header to
   make a string type option variable.  */

bool
handle_module_option (unsigned code, const char *str, int)
{
  switch (opt_code (code))
    {
    case OPT_fmodule_mapper_:
      module_mapper_name = str;
      return true;

    case OPT_fmodule_header_:
      {
	/* Look away.  Look away now.  */
	extern cpp_options *cpp_opts;
	if (!strcmp (str, "user"))
	  cpp_opts->main_search = 1;
	else if (!strcmp (str, "system"))
	  cpp_opts->main_search = 2;
	else
	  error ("unknown header kind %qs", str);
      }
      /* Fallthrough.  */

    case OPT_fmodule_header:
      flag_header_unit = 1;
      flag_modules = 1;
      return true;

    case OPT_fnote_include_translate_query:
      note_include_translate = -1;
      return true;

    case OPT_fnote_include_translate_:
      vec_safe_push (note_includes, str);
      return true;

    default:
      return false;
    }
}

#include "gt-cp-module.h"
