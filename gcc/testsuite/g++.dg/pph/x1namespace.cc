#include "x0namespace.h"

namespace A {
int x = 3;
} // namespace A

int y = 4;

int D::method()
{ return y; }

int main()
{ }
