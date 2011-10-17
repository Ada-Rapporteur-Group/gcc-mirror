// { dg-xfail-if "ICE CGRAPH" { "*-*-*" } { "-fpph-map=pph.map" } }
// { dg-bogus "x4keyex.cc:29:1: internal compiler error: in cgraph_analyze_functions, at cgraphunit.c:1193" "" { xfail *-*-* } 0 }

// Previously.
// xfail BOGUS MERGE LABELS
//
// This test case fails to compare because LFB/LFE labels are different.
//
// 1- Both x0keyno1.h and x0keyno2.h declare exactly the same, as
//    they both textually include a0keyed.h.
// 2- When we read x0keyno1.pph, we instantiate all the decls and cgraph
//    nodes for struct keyed.
// 3- When we read x0keyno2.pph, we re-instantiate the same decls and
//    cgraph nodes, which are used instead of the ones in x0keyno1.pph.
// 4- Since the new decls and nodes have been created later, the functions
//    have different function numbers (function::funcdef_no field), which
//    is used to emit the LFB/LFE labels.
//
// The future merging process will fix this by choosing the decls and nodes
// created first by x0keyno1.pph.

#include "x0keyed1.h"
#include "x0keyed2.h"

int main()
{
    keyed variable;
    return variable.mix( 3 );
}
