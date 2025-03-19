# README for the testsuite.src directory

## Organization

In the due course of time there will be many texts. They will be broken into groups of tests focusing on specific elements/features of COBOL. Those groups each have (at least) one autotest language file (.at).

This test suite separates the autotest statements (`m4` macros) from the source code used for the tests. A subdirectory exists for each autotest file that contains the data needed for the tests.

Where known-good output data is only a few lines long, it may be included in the autotest source. When it is longer, known-good data should also be stored in the subdirectory.

Rather than using `autom4te` "-I" to let it go find the materials, each reference uses `m4_include[(<subdir>/<filename>)]` format to explicitly point to the proper subdirectory. Names only need to be unique within an autotest file and its subdirectory.

## Why?

GnuCOBOL's autotest source files are **ENDLESS** because they contain all of the COBOL, COPYbooks, and known-good in line. That's fine but primitive.

By extracting test data, the actual autotest file is easier to edit and maintain. And the test data, in general, can be directly tested within the subdirectory for troubleshooting.
