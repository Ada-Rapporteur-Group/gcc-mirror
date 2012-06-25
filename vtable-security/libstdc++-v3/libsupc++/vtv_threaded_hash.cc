// Copyright (C) 2012
// Free Software Foundation
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.

// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "vtv_threaded_hash.h"
#include "vtv_malloc.h"

#define my_malloc VTV_malloc
#define my_free VTV_free

#define INITIAL_SIZE 16
#define INITIAL_POWER 4
#define REHASH_LIMIT 0.8


/* Statistics/Profiling numbers (for debugging) 
   No need to protect these since they are only used for debugging */

static unsigned num_tables_allocated = 0;
static unsigned num_bucket_pointers_allocated = 0;
static unsigned num_buckets_created = 0;
static unsigned num_slots_filled = 0;
static unsigned num_rehashes = 0;
static unsigned num_rehashed_elements = 0;
static const unsigned size_of_bucket = sizeof (struct vlt_hash_bucket);
static const unsigned size_of_pointer = sizeof (void *);


static void
bucket_insert (struct vlt_hash_bucket **slot, void *value)
{
  struct vlt_hash_bucket *new_bucket =
      (struct vlt_hash_bucket *) my_malloc (sizeof (struct vlt_hash_bucket));

  new_bucket->data = value;
  new_bucket->next = *slot;
  num_buckets_created++;  /* Debug */
  if ((*slot) == NULL)    /* Debug */
    num_slots_filled++;   /* Debug */

  *slot = new_bucket;
}

static uint32_t
rehash_elements (struct vlt_hash_bucket **old_data,
                 struct vlt_hash_bucket **new_data,
                 uint32_t old_size, uint32_t new_size, uint32_t num_bits)
{
  uint32_t i;
  uint32_t mask = 0xffffffff >> (32 - num_bits);
  struct vlt_hash_bucket *cur_bucket;
  uint32_t num_elements = 0;

  num_rehashes++; /* Debug */
  num_rehashed_elements += old_size; /* Debug */

  for (i = 0; i < old_size; ++i)
    {
      if (old_data[i] != 0)
        {
          struct vlt_hash_bucket *bucket_list = old_data[i];
          for (cur_bucket = bucket_list; cur_bucket;
               cur_bucket = cur_bucket->next)
            {
              void *value = cur_bucket->data;
	      uint32_t hash = vlt_hash_pointer (value);
	      uint32_t new_index = hash & mask;
	      bucket_insert (&(new_data[new_index]), value);
	      num_elements++;
            }
        }
    }
  return num_elements;
}

static void
grow_table (struct vlt_hashtable *table)
{
  /*  IMPORTANT NOTE!! This function assumes that you have already acquired the
      lock on TABLE's pthread mutex before calling this function.  If you call
      this function without first acquiring the lock, something bad may happen
      to you.  YOU HAVE BEEN WARNED!  */

  struct vlt_hash_bucket **old_data = NULL;
  uint32_t old_size = table->data_size;
  uint32_t new_size = 2 * old_size;
  uint32_t new_power_size = table->power_of_2 + 1;

  struct vlt_hash_bucket **new_data =
      (struct vlt_hash_bucket **)
                      my_malloc (new_size * sizeof (struct vlt_hash_bucket *));
  old_data = table->data;

  num_bucket_pointers_allocated += new_size;

  table->num_elts = rehash_elements (old_data, new_data, old_size,
				     new_size, new_power_size);

  table->data = new_data;
  table->data_size = new_size;
  table->power_of_2 = new_power_size;
  table->hash_mask = 0xffffffff >> (32 - new_power_size);

  /* TODO:  Need to 'my_free' each allocated bucket in old_data... */
  my_free (old_data);
}

/* Externally Visible Functions */

struct vlt_hashtable*
vlt_hash_init_table (int initial_size_hint)
{
  struct vlt_hashtable *new_table =
      (struct vlt_hashtable *) my_malloc (sizeof (struct vlt_hashtable));
  int initial_size = INITIAL_SIZE;
  int initial_power = INITIAL_POWER;

  while (initial_size_hint > (REHASH_LIMIT * initial_size))
    {
      initial_size *= 2;
      initial_power++;
    }

  new_table->data_size = initial_size;
  new_table->power_of_2 = initial_power;
  new_table->hash_mask = 0xffffffff >> (32 - initial_power);
  new_table->num_elts = 0;
  pthread_mutex_init (&(new_table->mutex), NULL);

  num_tables_allocated++; /* Debug */
  num_bucket_pointers_allocated += initial_size; /* Debug */

  new_table->data =
      (struct vlt_hash_bucket **)
                  my_malloc (initial_size * sizeof (struct vlt_hash_bucket *));

  return new_table;
}

void
vlt_hash_insert (struct vlt_hashtable *table, void *value)
{
  uint32_t hash = vlt_hash_pointer (value);
  uint32_t mask = table->hash_mask;
  uint32_t index = hash & mask;
  vlt_hash_bucket * first_bucket = table->data[index];
  void * slot = vlt_bucket_find (first_bucket, value, NULL);

  /* Only do the insert if the value is not already in the table.  */
  if (!slot)
    {
      /* Grab the mutex before doing the comparison below to make sure
         nothing being compared changes in the middle of the comparison.  */
      pthread_mutex_lock (&(table->mutex));
      /* See if anybody else inserted the element since the last check and
	 before we grabbed the lock. */
      /* Re-calculate the index in case the table grew between the
         initial check above and when we grabbed the lock. */
      uint32_t new_mask = table->hash_mask;
      uint32_t new_index;
      bool should_insert;
      if (mask == new_mask)
      {
        new_index = index;
        should_insert = !vlt_bucket_find (table->data[new_index], value, first_bucket);
      }
      else 
      {
        new_index = hash & new_mask;
        should_insert = !vlt_bucket_find (table->data[new_index], value, NULL);
      }
      if (should_insert)
        {
	  if (table->num_elts >= (REHASH_LIMIT * table->data_size))
          {
	    grow_table (table);
            new_index = hash & table->hash_mask;
          }

          bucket_insert (&(table->data[new_index]), value);
          table->num_elts++;
        }
      pthread_mutex_unlock (&(table->mutex));
    }
}

/* Debugging Functions  */

/* Outputs the contents of a single SLOT in the hashtable.  A slot
   consists of a linked list of entries that all hashed to the same
   entry in the table.  IDX is the index of the SLOT in the hash table.
   MAX_SIZE is the length of the longest linked list seen in any slot so
   far (going through all the slots, from dump_table_to_file).  DUMP_FILE
   is where the output gets sent.  */

void
dump_bucket_info (struct vlt_hash_bucket *slot, uint32_t idx,
                  uint32_t *max_size, FILE *dump_file)
{
  struct vlt_hash_bucket *cur;
  uint32_t num_buckets = 0;

  if (slot == NULL)
    {
      fprintf (dump_file, "slot[%2d]: empty\n", idx);
      return;
    }

  for (cur = slot; cur; cur = cur->next)
    num_buckets++;

  if (num_buckets > *max_size)
    *max_size = num_buckets;

  fprintf (dump_file, "slot[%2d]: %u elements, ", idx, num_buckets);

  for (cur = slot; cur; cur = cur->next)
    fprintf (dump_file, " %p ", cur->data);

  fprintf (dump_file, "\n");
}

/* Outputs the main information about the hashtable TABLE.  DUMP_BUCKETS
   is a boolean indicating whether or not to output the contents of all the
   hashtable buckets.  DUMP_FILE is where the output gets sent.  */

void
dump_table_to_file (struct vlt_hashtable *table, uint32_t dump_buckets,
                    FILE *dump_file)
{
  uint32_t i;
  uint32_t max_bucket_size = 0;

  fprintf (dump_file, "Table Stats:\n");
  fprintf (dump_file, "     Max Array Size: %d (2^%d) \n", table->data_size,
           table->power_of_2);
  fprintf (dump_file, "     Hash Mask: 0x%x\n", table->hash_mask);
  fprintf (dump_file, "     Current Number of Elements: %d\n\n", table->num_elts);

  if (dump_buckets)
    {
      fprintf (dump_file, "Bucket Data:\n");
      for (i = 0; i < table->data_size; ++i)
        dump_bucket_info (table->data[i], i, &max_bucket_size, dump_file);

      fprintf (dump_file, "Max bucket size is: %d\n", max_bucket_size);
    }

  fprintf (dump_file, "\n");
}


/* Outputs the main information about the hashtable TABLE.  DUMP_BUCKETS
   is a boolean indicating whether or not to output the contents of all the
   hashtable buckets.  Output gets sent to stdout.  */

void
dump_table (struct vlt_hashtable *table, uint32_t dump_buckets)
{
  dump_table_to_file (table, dump_buckets, stdout);
}

/* Outputs the main information about the hashtable TABLE.  DUMP_BUCKETS
   is a boolean indicating whether or not to output the contents of all the
   hashtable buckets.  Very similar to dump_table, except output is
   send to a newly created file named FILENAME, if we can open it.  */

void
dump_table_to_filename (struct vlt_hashtable *table, uint32_t dump_buckets,
                        char *filename)
{
  FILE *fp;

  if (!filename)
    return;

  fp = fopen (filename, "w");
  if (fp)
    {
      dump_table_to_file (table, dump_buckets, fp);
      fclose (fp);
    }
}

void
dump_table_to_vtbl_map_file (struct vlt_hashtable *table,
                             uint32_t dump_buckets,
                             char *var_name, uint32_t name_len)
{
  char *filename = (char *) malloc ((name_len + 11) * sizeof (char));
  char *real_name = (char *) malloc ((name_len + 1) * sizeof (char));
  FILE *dump_file_fp = NULL;

  strncpy (real_name, var_name, name_len);
  real_name[name_len] = '\0';

  sprintf (filename, "/tmp/%s.log", real_name);

  dump_file_fp = fopen (filename, "w");
  if (dump_file_fp)
    {
      dump_table_to_file (table, dump_buckets, dump_file_fp);
      fclose (dump_file_fp);
    }

  free (real_name);
  free (filename);
}

void
dump_hashing_statistics (void)
{
  FILE *fp = fopen("/tmp/threaded-hash-statistics.log", "w");

  if (fp)
    {
      fprintf (fp, "Threaded Hash Table Statistics\n\n");
      fprintf (fp, "# Hash Tables Created:  %d\n", num_tables_allocated);
      fprintf (fp, "# Slots Created:  %d\n", num_bucket_pointers_allocated);
      fprintf (fp, "# Slots Filled:  %d\n", num_slots_filled);
      fprintf (fp, "# Unused Slots: %d\n",
               num_bucket_pointers_allocated - num_slots_filled);
      fprintf (fp, "Slot Size (in bytes): %d\n\n", size_of_pointer);

      fprintf (fp, "# Buckets Created: %d\n", num_buckets_created);
      fprintf (fp, "# Non-slot buckets (in collision chains): %d\n",
               num_buckets_created - num_slots_filled);
      fprintf (fp, "Bucket Size (in bytes):  %d\n\n", size_of_bucket);
      fprintf (fp, "# of re-hashes that occurred: %d\n", num_rehashes);
      fprintf (fp, "# of re-hashed elements: %d\n", num_rehashed_elements);

      fclose (fp);
    }
}
