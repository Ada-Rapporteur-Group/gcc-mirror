#ifndef X1STRUCT_H
#define X1STRUCT_H
#include "c0struct2.h"
struct D : thing {
    type method();
    type another()
    { return fld + mbr + gbl; }
    type fld;
    static type mbr;
};
#endif
