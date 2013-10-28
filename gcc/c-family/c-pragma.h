/* Pragma related interfaces.
   Copyright (C) 1995-2013 Free Software Foundation, Inc.

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

#ifndef GCC_C_PRAGMA_H
#define GCC_C_PRAGMA_H

#include "cpplib.h" /* For enum cpp_ttype.  */

/* Pragma identifiers built in to the front end parsers.  Identifiers
   for ancillary handlers will follow these.  */
typedef enum pragma_kind {
  PRAGMA_NONE = 0,

  PRAGMA_OMP_ATOMIC,
  PRAGMA_OMP_BARRIER,
  PRAGMA_OMP_CRITICAL,
  PRAGMA_OMP_FLUSH,
  PRAGMA_OMP_FOR,
  PRAGMA_OMP_MASTER,
  PRAGMA_OMP_ORDERED,
  PRAGMA_OMP_PARALLEL,
  PRAGMA_OMP_PARALLEL_FOR,
  PRAGMA_OMP_PARALLEL_SECTIONS,
  PRAGMA_OMP_SECTION,
  PRAGMA_OMP_SECTIONS,
  PRAGMA_OMP_SINGLE,
  PRAGMA_OMP_TASK,
  PRAGMA_OMP_TASKWAIT,
  PRAGMA_OMP_TASKYIELD,
  PRAGMA_OMP_THREADPRIVATE,

  PRAGMA_ACC_PARALLEL,
  PRAGMA_ACC_PARALLEL_LOOP,
  PRAGMA_ACC_KERNELS,
  PRAGMA_ACC_KERNELS_LOOP,
  PRAGMA_ACC_DATA,
  PRAGMA_ACC_CACHE,
  PRAGMA_ACC_WAIT,
  PRAGMA_ACC_HOST_DATA,
  PRAGMA_ACC_LOOP,
  PRAGMA_ACC_DECLARE,
  PRAGMA_ACC_UPDATE,

  PRAGMA_GCC_PCH_PREPROCESS,

  PRAGMA_FIRST_EXTERNAL
} pragma_kind;


/* All clauses defined by OpenMP 2.5 and 3.0.
   Used internally by both C and C++ parsers.  */
typedef enum pragma_omp_clause {
  PRAGMA_OMP_CLAUSE_NONE = 0,

  PRAGMA_OMP_CLAUSE_COLLAPSE,
  PRAGMA_OMP_CLAUSE_COPYIN,
  PRAGMA_OMP_CLAUSE_COPYPRIVATE,
  PRAGMA_OMP_CLAUSE_DEFAULT,
  PRAGMA_OMP_CLAUSE_FIRSTPRIVATE,
  PRAGMA_OMP_CLAUSE_IF,
  PRAGMA_OMP_CLAUSE_LASTPRIVATE,
  PRAGMA_OMP_CLAUSE_NOWAIT,
  PRAGMA_OMP_CLAUSE_NUM_THREADS,
  PRAGMA_OMP_CLAUSE_ORDERED,
  PRAGMA_OMP_CLAUSE_PRIVATE,
  PRAGMA_OMP_CLAUSE_REDUCTION,
  PRAGMA_OMP_CLAUSE_SCHEDULE,
  PRAGMA_OMP_CLAUSE_SHARED,
  PRAGMA_OMP_CLAUSE_UNTIED,
  PRAGMA_OMP_CLAUSE_FINAL,
  PRAGMA_OMP_CLAUSE_MERGEABLE
} pragma_omp_clause;


/* All clauses defined by OpenACC 1.0.
   Used internally by both C and C++ parsers.  */
typedef enum pragma_acc_clause {
  PRAGMA_ACC_CLAUSE_NONE = 0,

  PRAGMA_ACC_CLAUSE_IF,
  PRAGMA_ACC_CLAUSE_ASYNC,
  PRAGMA_ACC_CLAUSE_COLLAPSE,
  PRAGMA_ACC_CLAUSE_SEQ,
  PRAGMA_ACC_CLAUSE_INDEPENDENT,
  PRAGMA_ACC_CLAUSE_GANG,
  PRAGMA_ACC_CLAUSE_WORKER,
  PRAGMA_ACC_CLAUSE_VECTOR,
  PRAGMA_ACC_CLAUSE_NUM_GANGS,
  PRAGMA_ACC_CLAUSE_NUM_WORKERS,
  PRAGMA_ACC_CLAUSE_VECTOR_LENGTH,
  PRAGMA_ACC_CLAUSE_REDUCTION,
  PRAGMA_ACC_CLAUSE_COPY,
  PRAGMA_ACC_CLAUSE_COPYIN,
  PRAGMA_ACC_CLAUSE_COPYOUT,
  PRAGMA_ACC_CLAUSE_CREATE,
  PRAGMA_ACC_CLAUSE_PRESENT,
  PRAGMA_ACC_CLAUSE_PRESENT_OR_COPY,
  PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYIN,
  PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYOUT,
  PRAGMA_ACC_CLAUSE_PRESENT_OR_CREATE,
  PRAGMA_ACC_CLAUSE_HOST,
  PRAGMA_ACC_CLAUSE_DEVICE,
  PRAGMA_ACC_CLAUSE_DEVICEPTR,
  PRAGMA_ACC_CLAUSE_DEVICE_RESIDENT,
  PRAGMA_ACC_CLAUSE_USE_DEVICE,
  PRAGMA_ACC_CLAUSE_PRIVATE,
  PRAGMA_ACC_CLAUSE_FIRSTPRIVATE
} pragma_acc_clause;

/* OpenACC 1.0:
 * Mask for parallel clauses
 */
#define ACC_PARALLEL_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_IF)\
		| (1u << PRAGMA_ACC_CLAUSE_ASYNC)\
		| (1u << PRAGMA_ACC_CLAUSE_NUM_GANGS)\
		| (1u << PRAGMA_ACC_CLAUSE_NUM_WORKERS)\
		| (1u << PRAGMA_ACC_CLAUSE_VECTOR_LENGTH)\
		| (1u << PRAGMA_ACC_CLAUSE_REDUCTION)\
		| (1u << PRAGMA_ACC_CLAUSE_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_DEVICEPTR)\
		| (1u << PRAGMA_ACC_CLAUSE_PRIVATE)\
		| (1u << PRAGMA_ACC_CLAUSE_FIRSTPRIVATE))

/* OpenACC 1.0:
 * Mask for kernels clauses
 */
#define ACC_KERNELS_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_IF)\
		| (1u << PRAGMA_ACC_CLAUSE_ASYNC)\
		| (1u << PRAGMA_ACC_CLAUSE_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_DEVICEPTR))


/* OpenACC 1.0:
 * Mask for data clauses
 */
#define ACC_DATA_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_IF)\
		| (1u << PRAGMA_ACC_CLAUSE_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_DEVICEPTR))

/* OpenACC 1.0:
 * Mask for host_data clauses
 */
#define ACC_HOST_DATA_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_USE_DEVICE))


/* OpenACC 1.0:
 * Mask for loop clauses
 */
#define ACC_LOOP_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_COLLAPSE)\
		| (1u << PRAGMA_ACC_CLAUSE_GANG)\
		| (1u << PRAGMA_ACC_CLAUSE_WORKER)\
		| (1u << PRAGMA_ACC_CLAUSE_VECTOR)\
		| (1u << PRAGMA_ACC_CLAUSE_SEQ)\
		| (1u << PRAGMA_ACC_CLAUSE_INDEPENDENT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRIVATE)\
		| (1u << PRAGMA_ACC_CLAUSE_REDUCTION))

/* OpenACC 1.0:
 * Mask for declare clauses
 */
#define ACC_DECLARE_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPY)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYIN)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_COPYOUT)\
		| (1u << PRAGMA_ACC_CLAUSE_PRESENT_OR_CREATE)\
		| (1u << PRAGMA_ACC_CLAUSE_DEVICEPTR)\
		| (1u << PRAGMA_ACC_CLAUSE_DEVICE_RESIDENT))

/* OpenACC 1.0:
 * Mask for update clauses
 */
#define ACC_UPDATE_CLAUSE_MASK \
		( (1u << PRAGMA_ACC_CLAUSE_HOST)\
		| (1u << PRAGMA_ACC_CLAUSE_DEVICE)\
		| (1u << PRAGMA_ACC_CLAUSE_IF)\
		| (1u << PRAGMA_ACC_CLAUSE_ASYNC))

extern pragma_acc_clause
pragma_acc_clause_get_name(const char* p, pragma_acc_clause result);

extern struct cpp_reader* parse_in;

/* It's safe to always leave visibility pragma enabled as if
   visibility is not supported on the host OS platform the
   statements are ignored.  */
extern void push_visibility (const char *, int);
extern bool pop_visibility (int);

extern void init_pragma (void);

/* Front-end wrappers for pragma registration.  */
typedef void (*pragma_handler_1arg)(struct cpp_reader *);
/* A second pragma handler, which adds a void * argument allowing to pass extra
   data to the handler.  */
typedef void (*pragma_handler_2arg)(struct cpp_reader *, void *);

/* This union allows to abstract the different handlers.  */
union gen_pragma_handler {
  pragma_handler_1arg handler_1arg;
  pragma_handler_2arg handler_2arg;
};
/* Internally used to keep the data of the handler.  */
struct internal_pragma_handler_d {
  union gen_pragma_handler handler;
  /* Permits to know if handler is a pragma_handler_1arg (extra_data is false)
     or a pragma_handler_2arg (extra_data is true).  */
  bool extra_data;
  /* A data field which can be used when extra_data is true.  */
  void * data;
};
typedef struct internal_pragma_handler_d internal_pragma_handler;

extern void c_register_pragma (const char *space, const char *name,
                               pragma_handler_1arg handler);
extern void c_register_pragma_with_data (const char *space, const char *name,
                                         pragma_handler_2arg handler,
                                         void *data);

extern void c_register_pragma_with_expansion (const char *space,
                                              const char *name,
                                              pragma_handler_1arg handler);
extern void c_register_pragma_with_expansion_and_data (const char *space,
                                                       const char *name,
                                                   pragma_handler_2arg handler,
                                                       void *data);
extern void c_invoke_pragma_handler (unsigned int);

extern void maybe_apply_pragma_weak (tree);
extern void maybe_apply_pending_pragma_weaks (void);
extern tree maybe_apply_renaming_pragma (tree, tree);
extern void add_to_renaming_pragma_list (tree, tree);

extern enum cpp_ttype pragma_lex (tree *);

/* Flags for use with c_lex_with_flags.  The values here were picked
   so that 0 means to translate and join strings.  */
#define C_LEX_STRING_NO_TRANSLATE 1 /* Do not lex strings into
				       execution character set.  */
#define C_LEX_STRING_NO_JOIN	  2 /* Do not concatenate strings
				       nor translate them into execution
				       character set.  */

/* This is not actually available to pragma parsers.  It's merely a
   convenient location to declare this function for c-lex, after
   having enum cpp_ttype declared.  */
extern enum cpp_ttype c_lex_with_flags (tree *, location_t *, unsigned char *,
					int);

extern void c_pp_lookup_pragma (unsigned int, const char **, const char **);

extern GTY(()) tree pragma_extern_prefix;

#endif /* GCC_C_PRAGMA_H */
