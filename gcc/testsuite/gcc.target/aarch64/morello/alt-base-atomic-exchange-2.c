/* { dg-do assemble } */
/* { dg-additional-options "-foptimize-sibling-calls -save-temps" } */
/* { dg-final { check-function-bodies "**" ""  { {-O[123s]} } } } */
/* { dg-skip-if "" { *-*-* } { "-mabi=purecap" "-mfake-capability" } { "" } }  */

#include <stdint.h>

typedef __uint128_t uint128;
typedef __intcap intcap;

#define TEST_SIZE(TYPE, SIZE)						\
  TYPE									\
  test_##TYPE##_relaxed (TYPE *__capability ptr, TYPE val)		\
  {									\
    return __atomic_exchange_##SIZE ((TYPE *) ptr, val, __ATOMIC_RELAXED);	\
  }									\
									\
  TYPE									\
  test_##TYPE##_acquire (TYPE *__capability ptr, TYPE val)		\
  {									\
    return __atomic_exchange_##SIZE ((TYPE *) ptr, val, __ATOMIC_ACQUIRE);	\
  }									\
									\
  TYPE									\
  test_##TYPE##_release (TYPE *__capability ptr, TYPE val)		\
  {									\
    return __atomic_exchange_##SIZE ((TYPE *) ptr, val, __ATOMIC_RELEASE);	\
  }									\
									\
  TYPE									\
  test_##TYPE##_acq_rel (TYPE *__capability ptr, TYPE val)		\
  {									\
    return __atomic_exchange_##SIZE ((TYPE *) ptr, val, __ATOMIC_ACQ_REL);	\
  }									\
									\
  TYPE									\
  test_##TYPE##_seq_cst (TYPE *__capability ptr, TYPE val)		\
  {									\
    return __atomic_exchange_##SIZE ((TYPE *) ptr, val, __ATOMIC_SEQ_CST);	\
  }

/*
** test_uint8_t_relaxed:
**	swpb	w1, w0, \[x0\]
**	ret
*/

/*
** test_uint8_t_acquire:
**	swpab	w1, w0, \[x0\]
**	ret
*/

/*
** test_uint8_t_release:
**	swplb	w1, w0, \[x0\]
**	ret
*/

/*
** test_uint8_t_acq_rel:
**	swpalb	w1, w0, \[x0\]
**	ret
*/

/*
** test_uint8_t_seq_cst:
**	swpalb	w1, w0, \[x0\]
**	ret
*/
TEST_SIZE (uint8_t, 1)

/* Don't match the rest.  The matches above are mostly to make sure
   that there are no typos in the function names.  */
TEST_SIZE (uint16_t, 2)
TEST_SIZE (uint32_t, 4)
TEST_SIZE (uint64_t, 8)
TEST_SIZE (uint128, 16)
TEST_SIZE (intcap, capability)
