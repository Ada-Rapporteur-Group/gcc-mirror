# Linking and Loading COBOL Programs
## Tue Feb  7 12:02:54 2023

If you have a fox, a bag of grain, a chicken, and two COBOL files, how
do you get them all across the river?

More simply: Given 2 COBOL modules, how to we link them together?  Answers:

1.  Statically
2.  Dynamically

## Statically

With static linking, all symbols are resolved by the static
linker, **ld**(1).

    gcobol -o X A.cbl B.cbl

compiles both COBOL programs and links them to produce an executable, `X`.

    gcobol -o libX.so -shared A.cbl B.cbl

compiles both COBOL programs and links them to produce a shared
object, or dynamic library (same thing).

The *lib* prefix is a Unix convention.  It doesn't signify anything to
the operating system; a file with that prefix need not be a shared
object, and shared objects need not have that prefix. But some *tools*
rely on the *lib* prefix (and *.so* extension) as defaults.

    gcobol -c A.cbl B.cbl

compiles both COBOL programs and produces object files from each
one, namely `A.o` and `B.o`.

    gcobol -o X A.cbl B.o

compiles `A.cbl` to produce `A.o`, and links `A.o` and `B.o` to
produce `X`.

## Dynamically

With dynamic linking, all symbols are *checked* by the static linker,
but aren't resolved until the executable is loaded, when the run-time
linker runs.  The static linker ensures that the libraries available
when the executable is produced supply all the symbols the executable
uses. One *hopes* that when the executable runs, those same libraries
-- i.e., the versions of those libraries -- will be installed on the
host machine. If that hope is dashed, the runtime linker will report
an error, and the executable will not run.

    gcobol -o libB.so -shared B.cbl
    gcobol -o A  A.cbl -L. -lB

compiles and links `B.cbl` to `libB.so`, then compiles `A.cbl` and
links it to `libB.so`. But "link" here does not mean any real linking
is done. When the static linker sees a shared object as input, it only
uses the shared object's list of exported names, to confirm that the
program could use the library to resolve its symbols.

If at this stage you try to run `A`, it will probably fail, with
**ld.so**(8) saying it can't find `libB.so`. Normally, the runtime
linker does not look in the current working directory for
libraries. Its default search locations are controlled by its
configuration and environment variables, but by default it usually
looks in `/lib` and `/usr/lib`.  That is why libraries are normally
installed prior to use.

If the library is not going to be used from a standard location, the
linker has to be told where else to look for it. One way that's done
is through the environment:

    LD_LIBRARY_PATH=$PWD ./A

adds the current working directory to its search list, where indeed it
will find `libB.so`.

A better way it to add the search directory to the executable, using
linker flags:

    gcobol -o A  A.cbl -L. -Wl,-rpath=$PWD -lB

Here,

    -Wl,

(note the comma) is a **gcc**(1) option whose argument is passed to
the linker. That argument is

    -rpath=$PWD

To quote the **ld**(1) man page:

 *Add a directory to the runtime library search path.  This is used
  when linking an ELF executable with shared objects.  All -rpath
  arguments are concatenated and passed to the runtime linker, which
  uses them to locate shared objects at runtime.*

When the linker produces the `A` executable, it adds the **-rpath**
directory to it, in the *RPATH* or *RUNPATH* tag. When the executable
is loaded and run, the runtime linker consults those tags for
information on where to search for libraries.

## Example: showing is knowing

Above, we ignored *position-independent code* because it's a detail.
In working examples, we have to include it. Let's show the parts:

Program A:

        ID DIVISION.
          PROGRAM-ID A.

        PROCEDURE DIVISION.
          SAY-AHH.
            DISPLAY "Ahh".

Program B:

        ID DIVISION.
          PROGRAM-ID B.

        PROCEDURE DIVISION.
          SAY-BEE.
            DISPLAY "Bee".

Compile:

    gcobol -c -fPIC A.cbl B.cbl
    gcobol -o libB.so  -shared B.o

Output:

    $ file *
    A.cbl:   ASCII text
    A.o:     ELF 64-bit LSB relocatable, [...]
    B.cbl:   ASCII text
    B.o:     ELF 64-bit LSB relocatable, [...]
    libB.so: ELF 64-bit LSB shared object, [...]

## Statically linked example

    $ gcobol  -o A A.cbl B.cbl && ./A
	Ahh

A **main**() function is generated for `A.cbl` by default because it
is the first program on the command line. Because `A` doesn't call
`B`, we have only one line of output.

Let's change `A` to call `B`:

        ID DIVISION.
          PROGRAM-ID A.

        PROCEDURE DIVISION.
          SAY-AHH.
            DISPLAY "Ahh".
            CALL "B".

	$ gcobol  -o A A.cbl B.cbl && ./A
	Ahh
	Bee

We know the programs are statically linked, because both symbols are
supplied by the program itself:

    $ nm A | grep -w T
    0000000000401e00 T _start
    0000000000401f74 T a
    0000000000403454 T b
    0000000000401f04 T main

## Dynamically linked example

	$ gcobol-bin  -o A A.cbl -L. -lB -Wl,-rpath=$PWD && ./A
	Ahh
	Bee

  * The compiler produces `A.o` from `A.cbl`, leaving open how `CALL
    "B"` will be resolved.
  * The static linker finds libB.so in the current working directory.
    It finds the `b` symbol in it, thus satisfying the needs of `A.o`.
    It adds the current working directory to the *RUNPATH* of `A`, per
    the invocation.

We know `A` does not supply `b`:

	$ nm A | grep -w T
	0000000000401e40 T _start
	0000000000401fb4 T a
	0000000000401f44 T main

We know `A` is dynamically linked to B:

    $ readelf -d A

    Dynamic section at offset 0x3d98 contains 30 entries:
      Tag        Type                         Name/Value
     0x0000000000000001 (NEEDED)             Shared library: [libB.so]
     0x0000000000000001 (NEEDED)             Shared library: [libgcobol.so.4]
     0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
     0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
     0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
     0x000000000000001d (RUNPATH)            Library runpath: [/home/[...]]
     0x000000000000000c (INIT)               0x401c88
     0x000000000000000d (FINI)               0x403494

and we see the *RUNPATH* entry showing the directories that the
runtime linker will peruse in search of `libB.so`.
