/* { dg-do run } */
/* { dg-options "-ldl -lcilkrts" } */

#include <cilk/cilk.h>
#include <cstdlib>

struct BruceWillis {
    BruceWillis (int i) : m(i) { }
    ~BruceWillis () { }
    operator int () { return m; }
    BruceWillis operator++ () { ++m; return *this; }
    int m;
};

int main () {
    cilk_for (BruceWillis bw(0);
              bw < (int)BruceWillis(16); // This is the problematic line.
              ++bw);
    exit (0);
    return 0;
}
