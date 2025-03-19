# Tests For COBOL for GCC

This directory contains several autotest suites that can be run against
an installed copy of `gcobol`. It is designed to be entirely independent
of the process of building from source. It expects that `make install`
from a built source tree will behave the same as COBOLworx's binary
packages.

By default, the cobol compiler is invoked simply with "gcobol", so in
general it will be looking for an installed version. This can be
changed by setting the `GCOBOL`, `GCOBOL_FLAGS`, `GCOBOL_LDFLAGS`
environment variables.

Users who are developing the compiler might want to use the build of
the compiler that is under development.  This can be accomplished on
an x64 machine with the `GCOBOL_BUILD_DIR` environment variable, e.g.:

    GCOBOL_BUILD_DIR=/home/bob/repos/gcc-cobol/build

# The make commands

- `make` or `make test` Builds the "should work" tests
- `make fail` Builds the tests that currently are failing
- `make skip` Builds the tests that are intentionally skipped.
- `make bugs` Builds the tests currently flagged for attention
- `make -i all` Builds all of the above

It should be noted that `make skip` is in place mainly as a bookkeeping
tool to keep track of source code that might be moved to `test` or
`fail` at some later time.

# The four test suites

## test

These tests are driven by `testsuite.at` and `testsuite.src`. The are
"Source code that should work, and does".  These are tests that should
have an "ok" result.

## fail

These tests driven by `failsuite.at` and `failsuite.src` are "Source
code that should work, and doesn't".  Tests in this suite tests that
should have a "FAILED" result.  When the compiler is finally able to
handle one of these tests, it should be moved into the `test` suite of
known-good tests.  If a decision is made that a test can't be made to
work, it should be moved into the `skip` suite.

## skip

These tests are driving by `skipsuite.at` and `skipsuite.src`.  This
suite is intended for source code that simply can't be cajoled into an
ISO-compliant form.  When appropriate, tests should be updated and moved
into the `test` or `skip` suites.

## bugs

These are high-impact failures placed here for for high priority
attention.

# For Developers Addressing Failures/Skips

The philosophy being espoused here is that `make test` is for regression
testing.  The development goal is to improve the compiler to move tests
from `failsuite` and `skipsuite` to `testsuite`.

Doing so will generally mean editing the various source files in the
`testsuite.src`, `failsuite.src`, `skipsuite.src`, and `bugsuite.src`
directories.

This is dangerous, but necessary.

In general, when a test fails, the information about the failure is in
xxxxsuite.log, and in individual subdirectories of xxxxsuite.dir/


## Ongoing use

When you `make test`, the Makefile compares ./testsuite to the source
code in testsuite.src.  ./testsuite is rebuilt, when necessary.
./testsuite is a script that runs the tests.

There are some options.

`testsuite 47` will run test #47.

`testsuite -k copy` runs all the tests that have `copy` as a keyword.

The keyword situation is currently pretty sloppy.  Watch this space.

## To find out what happened in failed/skipped tests

`testsuite` creates testsuite.log (in the root directory) and, if any
tests fail (expectedly or not), ore are skipped, testsuite.dir.
testsuite.dir has a marker line that starts: "## Detailed".  The logs
of each failure are listed after that marker.

An example of a test's testsuite.log:
```
#                             -*- compilation -*-
8. run_initialize.at:27: testing INITIALIZE group entry with OCCURS ...
/run_initialize.at:52: $COMPILE prog.cob
/run_initialize.at:53: ./a.out
--- /dev/null	2022-12-05 15:38:03.744000000 +0000
+++ /home/mheyman/repos/gcobol-tests/testsuite.dir/at-groups/8/stdout	2022-12-28 18:39:16.029199183 +0000
@@ -0,0 +1 @@
+ 0
8. run_initialize.at:27: 8. INITIALIZE group entry with OCCURS (run_initialize.at:27): FAILED (run_initialize.at:53)
```

Explanation by line number:

1. comment, more useful in the global testsuite.log
2. Test number, <autotest source filename>:<line number>, test name
3. location in autotest file of AT_CHECK running a command, the command run
4. indicator of what output source, date, time, $0
5. confusing gorp that always shows up and I have no info on what it might
   mean
6. '+' indicates an unexpected output on STDOUT followed, without a blank,
   by the output.  '-' would mean an expected output that was not received.
7. test number, autotest source file and line number, and the result line

To find the test's failure directory, for this test-number:

     cd testsuite.dir/008

The log is testsuite.log. Any programs and files created for the test are
in that directory and any subdirectories created by the test. There is a
shell script `run` that reruns the test within the directory.

# Thoughts

## Roadmap

Obviously, the suite will eventually need to be made part of the gcc-cobol repository.
To do that, it needs to be parameterized to provide options for testing within the
repo against the (newly) built binaries. For the present, it is not obvious that
that effort should be done soon.

## V2

There is a v2/ subdirectory with entirely new tests being developed using the ISO
standard as the reference. It is still tiny. Work on that is ongoing at a lower
priority than on the main testsuite.

# TODO

## Short Term

1. Replace "EXIT PROGRAM" with "GOBACK" to allow cobc test comparisons.
   NOT OPTIMAL but a global replace (`sed`) project later is not a big
   deal.
2. Tests for arithmetic on edited-numeric (DISPLAY) data items. gcobol
   currently happily performs arithmetic on them.
3. New template with perform-failure and report-failures.
4. Remove all SKIPped tests that are now and forever Gnu dependent
5. Test for STOP RUN in a called routine.

## Longer Term

1. Syntax messages that aren't pointing at something and it's up to
   the user to figure out WTF just happened.
2. Agreements on control of error and warning messages
3. Dialects
