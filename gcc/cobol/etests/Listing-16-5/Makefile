# This makefile is for invoking the gcobol compiler to compile and run
# simple COBOL programs.  It was created mainly to showcase COBOL programs
# that either didn't compile, or compiled or ran improperly, for the purposes
# of development.

# This include file establishes the path to the compilation executables
include ../MakeVars.inc

SOURCE_FILE = $(wildcard *.cbl)
DONT_FAIL_DIFF ?= false
DEBUG = -ggdb

BEFORE := $(wildcard before.scr)
AFTER  := $(wildcard after.scr)

.PHONY: testv
testv:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG)       -c -O0 -o      Listing16-5sub.o Listing16-5sub.cbl
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-5.cbl $(COBOL_RUNTIME_LIBRARY) Listing16-5sub.o
	./test < input.txt

.PHONY: test
test:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG)       -c -O0 -o      Listing16-5sub.o Listing16-5sub.cbl
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-5.cbl $(COBOL_RUNTIME_LIBRARY) Listing16-5sub.o
	./test <input.txt >under-test.txt 2>&1 || true
	diff -u known-good.txt under-test.txt || $(DONT_FAIL_DIFF)

.PHONY: known-good
known-good:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG)       -c -O0 -o      Listing16-5sub.o Listing16-5sub.cbl
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-5.cbl $(COBOL_RUNTIME_LIBRARY) Listing16-5sub.o
	./test <input.txt >under-test.txt 2>&1 || true
	cp under-test.txt known-good.txt

.PHONY: comb
comb:
	$(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test combined.cbl $(COBOL_RUNTIME_LIBRARY)
	./test < input.txt

.PHONY: combd
combd:
	gdb --args $(PREFIX)/$(COBOL1) -main combined.cbl \
		-quiet -dumpbase \
		combined.cbl -mtune=generic -march=x86-64 \
		-auxbase $(basename combined.cbl) $(DEBUG) -O0 -version \
		-o $(basename combined.cbl).s

.PHONY: testd1
combd1:
	gdb --args $(PREFIX)/$(COBOL1) -main Listing16-5sub.cbl \
		-quiet -dumpbase \
		combined.cbl -mtune=generic -march=x86-64 \
		-auxbase $(basename Listing16-5sub.cbl) $(DEBUG) -O0 -version \
		-o $(basename Listing16-5sub.cbl).s

.PHONY: combt
combt:
	@rm -f test
	GCC_PRINT_TREE=1 $(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -O0 -S -o test.s combined.cbl                          -fdump-tree-gimple
	GCC_PRINT_TREE=1 $(GCC_BIN)/$(GCOBOL) -finternal-ebcdic $(SEARCH_PATHS) $(DEBUG) -O0    -o test   combined.cbl $(COBOL_RUNTIME_LIBRARY) -fdump-tree-gimple

.PHONY: gc
gc:
	cobc -free -c    -o Listing16-5sub.o Listing16-5sub.cbl
	cobc -free    -x -o gc Listing16-5.cbl Listing16-5sub.o

.PHONY: clean
clean:
	rm -fr *.tags *.gimple *.s gc test* *.o

