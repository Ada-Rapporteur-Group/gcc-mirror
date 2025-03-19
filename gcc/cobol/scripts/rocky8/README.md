# gcobol Configuration and Build Notes

This directory contains data and scripts to assist in building and
installing gcobol on Linux Rocky 8, which is a proxy for Red Hat 8.

- data: share/prerequisites
- scripts, in the order they should be run: 
  - bin/prepare-gcc-cobol
    - bin/build-bison
  - bin/configure-gcc-cobol

If you decide not to use the scripts directly, we hope you'll find
them useful as an indication of intention.

## share/prerequisites

The prerequisites file lists the packages needed to make a base Rocky
8 system ready to build gcobol.  Most of the prerequisites
are
[GCC requirements](https://gcc.gnu.org/install/prerequisites.html).
We don't require the full suite of gcc prerequisites because we're
building only two compilers:

- the C compiler, gcc
- the COBOL compiler, gcobol

## prepare-gcc-cobol

To update your system, run `bin/prepare-gcc-cobol`. You will need
superuser privileges because you're installing packages.  The script
reports what is installed, too.  If the system is ready, running it as
non-root will just report what it found.

`bin/prepare-gcc-cobol` read and processes `share/prerequisites`. You
can change what's installed by changing what's in that file. 

Bison is now a required package to build gcc.  The bison required to
build gcobol is newer than the bison provided by the Rocky 8 packages.
For that reason, `prepare-gcc-cobol` builds bison from source, see next. 

## build-bison

This stand-alone script is invoked by `prepare-gcc-cobol` if
needed. You can also run it yourself, or install bison however you
like. If you choose to run the script, you may wish first to set the
environment variable `srcdir`, which determines where the bison
sources are extracted and built. The default configure arguments are
used, meaning bison is installed in `/usr/local/bin`. 

## configure-gcc-cobol

Once the prerequisites are installed (`prepare-gcc-cobol` reports no
problems), it's time to run the gcc configure script. 

`configure-gcc-cobol` consults several environment variables whose
defaults you can override if you choose. If the variable is not set, a
sensible default is used. The most important might be `prefix`: if you
don't want to install in `/usr/local`, choose another.

Please note that gcc *cannot* be built "in tree"; the object files
cannot be produced in the same directory as their source files.  A
separate build directory is required. The default for
`configure-gcc-cobol` is to produce a `build` directory right off the
source root, which works fine.

### Warning

It is not possible to build any GCC compiler, including gcobol,
without also building the C compiler. Please keep that in mind when
deciding the PREFIX and installing the compiler, because you run the
risk of overwriting the system's base gcc.

## Build

The `configure` script produces a build tree.  In addition to the gcc
directory (which houses the gcobol source files in `gcc/cobol`) there
are many associated libraries that are used by various compilers in
the GNU Compiler Collection.  These all get built, and many installed,
because that's how the thing works.  Which ones are installed depends
on which compilers are built, which is controlled by the `--languages`
configure option.

The first build can take a while because you're building all the
libraries. It goes faster if you use `make -j12` or similar, depending
on your machine.  Subsequent builds, if you update the sources,
are much faster. 

To kick off the build, something like this will do fine: 

    $ cd build
    $ time make -s -j12 > log
    
That will finish by producing a little report of how long it
took. Depending on your compiler, many warning message may scroll by
as the build proceeds.  That is normal; the known way to prevent them
is to run the configure script with **CFLAGS=-w**.

Errors will of course terminate the build. Provided the above steps
are taken to prepare the machine, no error is expected.

## Install

The final step is `make install`.  Depending on your prefix you may
need superuser privileges. Remember nothing prevents you, as the
superuser, from overwriting the system's `gcc` by setting `prefix` to
`/usr`.  Please take care.

In all, just over 1000 files will be installed, including about 200
from the bison installation. You check specifically in your `prefix` for 

    bin/gcobol
    lib/libgcobol.so
    share/man/man1/gcobol.1
    
And of course **command -v gcobol** will confirm the installed
executable is on the `PATH`.

## Further steps

The installed gcobol manual (`man gcobol`) describes the compiler. 

In the source tree, along with file you're currently reading, you will
find `gcc/cobol/scripts/migration/migration-guide.1`. It describes
differences between GnuCOBOL and gcobol. To read it, **man**(1)
accepts a filename argument:

    $ man gcc/cobol/scripts/migration/migration-guide.1
    
The migration guide is currently not installed by `make install`
because it's not clear it *should* be.  It's usefulness will be assessed over time. 



