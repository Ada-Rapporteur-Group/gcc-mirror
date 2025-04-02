/* Test callback attribute error checking. */

/* { dg-do compile } */

void 
__attribute__((callback(1, 2)))
correct_1(void (*)(int*), int*);

void 
__attribute__((callback(1, 2, 3)))
correct_2(void (*)(int*, double*), int*, double*);

void 
__attribute__((callback(1, 0)))
unknown_1(void (*)(int*));

void 
__attribute__((callback(1, 2, 0)))
unknown_2(void (*)(int*, double*), int*, double*, char*);

void 
__attribute__((callback(1, 0, 3, 3)))
too_many(void (*)(int*, double*), int*, double*); /* { dg-error "argument number mismatch, 2 expected, got 3" }*/

void 
__attribute__((callback(1, 2)))
too_few_1(void (*)(int*, double*), int*, double*); /* { dg-error "argument number mismatch, 2 expected, got 1" }*/

void 
__attribute__((callback(1)))
too_few_2(void (*)(int*, double*), int*, double*); /* { dg-error "argument number mismatch, 2 expected, got 0" }*/

void 
__attribute__((callback(3, 1)))
promotion(char*, float, int (*)(int*));

void 
__attribute__((callback(2, 3)))
downcast(char*, void* (*)(float*), double*);

void 
__attribute__((callback(1, 2, 5)))
out_of_range_1(char (*)(float*, double*), float*, double*, int*); /* { dg-error "callback argument index 5 is out of range" } */

void 
__attribute__((callback(1, -2, 3)))
out_of_range_2(char (*)(float*, double*), float*, double*, int*); /* { dg-error "callback argument index -2 is out of range" } */

void 
__attribute__((callback(-1, 2, 3)))
out_of_range_3(char (*)(float*, double*), float*, double*, int*); /* { dg-error "callback function position out of range" } */

void 
__attribute__((callback(0, 2, 3)))
unknown_fn(char (*)(float*, double*), float*, double*, int*); /* { dg-error "callback function position cannot be marked as unknown" } */

void
__attribute__((callback(1, 2)))
not_a_fn(int, int); /* { dg-error "argument no. 1 is not an address of a function" } */

struct S{
  int x;
};

void
__attribute__((callback(1, 2)))
incompatible_types_1(void (*)(struct S*), struct S); /* { dg-error "argument type at index 2 is not compatible with callback argument type at index 1" } */

void
__attribute__((callback(1, 3, 2)))
incompatible_types_2(void (*)(struct S*, int*), int*, double); /* { dg-error "argument type at index 3 is not compatible with callback argument type at index 1" } */

void
__attribute__((callback(1, "2")))
wrong_arg_type_1(void (*)(void*), void*); /* { dg-error "argument no. 1 is not an integer constant" } */

void
__attribute__((callback("not a number", 2, 2)))
wrong_arg_type_2(void (*)(void*, void*), void*); /* { dg-error "argument specifying callback function position is not an integer constant" } */
