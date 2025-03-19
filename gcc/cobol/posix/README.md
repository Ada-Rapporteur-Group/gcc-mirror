# GCC COBOL Posix Functions and Adapter

## Purpose

ISO COBOL does not specify any relationship to any particular
operating system, and does not reference Posix. The raw capability is
there, of course, via the `CALL` statement.  But that's not very
convenient, and offers no parameter validation.

GCC COBOL as of this writing works *only* in a Posix environment. This
directory exists to make using OS-provided functions a bit more convenient.

## Contents

The machine-shop tools are in this directory.  Things directly usable
by a COBOL program are in the `udf/` and `c/` directories.

- `scrape.awk` extracts function prototypes from the SYNOPSIS of a man page.
- `udf-gen` reads function declarations and, for each one, produces a
  COBOL User Defined Function (UDF) that calls the function.
- `Makefile` produces a list of function prototypes from Section 2 of
  the manual.
- `c/` contains helper functions in C that cannot be expressed in
  COBOL. For example, the C `errno` "variable" may be a macro, and may
  not be declared except by `errno.h`, which is not accessible to
  COBOL.
- `udf/Makefile` builds some infrastructure and examples:
  - `udf/libposix-errno.so`, to get at the C `errno` variable and its
    string representation.
  - `udf/posix-mkdir.cbl` automatically from the manual, using `udf-gen`.
  - `udf/t/errno` and
  - `udf/t/exit` as examples of COBOL programs using these Posix UDFs.

## Prerequisites

`udf-gen` is a Python program that imports
the [PLY pycparser module](http://www.dabeaz.com/ply/) module, which must be installed.

`udf-gen` is lightly documented, use `udf-gen --help`. It can be a
little tedious to set up the first time, but if you want to use more a
few functions, it will be faster than doing the work by hand.

## Limitations

`udf-gen` does not

- generate a working UDF for function parameters of type `struct`,
  such as is used by **stat**(2).  This is because the information is
  not available in a standardized way in the SYNOPSIS of a man page.
- define helpful Level 88 values for "magic" numbers, such as
  permission bits in **chmod**(2).

None of this is particularly difficult; it's just a matter of time and
need. The `scrape.awk` script finds 560 functions in the Ubuntu LTS
22.04 manual.  Which of those is important is for users to decide.

## Other Options

IBM and Microfocus both supply intrinsic functions to interface with
the OS, each in their own way. GnuCOBOL implements some of those functions.

## Portability

The UDF produced by `udf-gen` is pure ISO COBOL.  The code should be
compilable by any ISO COBOL compiler.
