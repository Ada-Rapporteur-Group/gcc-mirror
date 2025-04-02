/* Test that we can handle multiple callback attributes and use them to
   propagate into callbacks. 'cb1' body borrowed from a ipa-cp test to get the
   pass to work. */

/* { dg-xfail-if "Linking will fail" { *-*-* } } */
/* { dg-do link } */
/* { dg-options "-O3 -flto -fdump-ipa-cp-details" } */
/* { dg-require-effective-target lto } */

struct S {
  int a, b, c;
};

extern void *blah(int, void *);

extern __attribute__((callback(1, 2), callback(3, 4, 5))) void
call(void (*fn1)(struct S *), struct S *a, void (*fn2)(struct S *, struct S *),
     struct S *b, struct S *c);

void cb1(struct S *p) {
  int i, c = p->c;
  int b = p->b;
  void *v = (void *)p;

  for (i = 0; i < c; i++)
    v = blah(b + i, v);
}

void cb2(struct S *a, struct S *b) {
  cb1(a);
  cb1(b);
}

void test(int a, int b, int c) {
  struct S s;
  s.a = a;
  s.b = b;
  s.c = c;
  struct S ss;
  ss.a = s.c;
  ss.b = s.b;
  ss.c = s.a;
  call(cb1, &s, cb2, &s, &ss);
}

int main() {
  test(1, 64, 32);
  return 0;
}

/* { dg-final { scan-wpa-ipa-dump "Creating a specialized node of cb1" "cp" } } */
/* { dg-final { scan-wpa-ipa-dump "Creating a specialized node of cb2" "cp" } } */
/* { dg-final { scan-wpa-ipa-dump-times "Aggregate replacements: " 2 "cp" } } */
