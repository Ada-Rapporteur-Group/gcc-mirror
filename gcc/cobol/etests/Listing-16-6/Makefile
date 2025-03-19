# This makefile is for invoking the gcobol compiler to compile and run
# simple COBOL programs.  It was created mainly to showcase COBOL programs
# that either didn't compile, or compiled or ran improperly, for the purposes
# of development.

# This include file establishes the path to the compilation executables
include ../MakeVars.inc

SOURCE_FILE = $(wildcard *.cbl)
DONT_FAIL_DIFF ?= false
DEBUG = -ggdb
EBCDIC = -finternal-ebcdic

BEFORE := $(wildcard before.scr)
AFTER  := $(wildcard after.scr)

.PHONY: both
both:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test  Listing16-6.cbl Listing16-6sub.cbl $(COBOL_RUNTIME_LIBRARY)
	./test < input.txt

.PHONY: bothd
bothd:
	GCC_PRINT_TREE=1 gdb -q --args $(PREFIX)/$(COBOL1) \
		Listing16-6.cbl Listing16-6sub.cbl \
        -quiet \
		-dumpbase Listing16-6.cbl \
		-mtune=generic -march=x86-64 \
        -auxbase $(basename Listing16-6.cbl) \
		 $(DEBUG) $(EBCDIC) -O0 -version


#        -auxbase Listing16-6.cbl Listing16-6sub.cbl


.PHONY: testv
testv:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG)       -c -O0 -o      Listing16-6sub.o Listing16-6sub.cbl
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-6.cbl $(COBOL_RUNTIME_LIBRARY) Listing16-6sub.o
	./test < input.txt

.PHONY: test
test:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG)       -c -O0 -o      Listing16-6sub.o Listing16-6sub.cbl
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-6.cbl $(COBOL_RUNTIME_LIBRARY) Listing16-6sub.o
	./test <input.txt >under-test.txt 2>&1 || true
	diff -u known-good.txt under-test.txt || $(DONT_FAIL_DIFF)

.PHONY: known-good
known-good:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG)       -c -O0 -o      Listing16-6sub.o Listing16-6sub.cbl
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-6.cbl $(COBOL_RUNTIME_LIBRARY) Listing16-6sub.o
	./test <input.txt >under-test.txt 2>&1 || true
	cp under-test.txt known-good.txt

.PHONY: gc
gc:
	cobc -free -c    -o Listing16-6sub.o Listing16-6sub.cbl
	cobc -free    -x -o gc Listing16-6.cbl Listing16-6sub.o

.PHONY: clean
clean:
	rm -fr *.tags *.gimple *.s gc test* *.o

