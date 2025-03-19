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

.PHONY: test-nest
test-nest:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -main -O0 -o test-nested Listing16-2-nested.cbl $(COBOL_RUNTIME_LIBRARY)
	$(LIBRARY_PATH) ./test-nested < input.txt


.PHONY: test-side
test-side:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -main -O0 -o test-side-by-side Listing16-2-side-by-side.cbl $(COBOL_RUNTIME_LIBRARY)
	$(LIBRARY_PATH) ./test-side-by-side < input.txt

.PHONY: testv
testv:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG)         -c -O0 -o Listing16-2sub.o Listing16-2sub.cbl

	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-2.cbl Listing16-2sub.o $(COBOL_RUNTIME_LIBRARY)
	$(TEST) < input.txt

.PHONY: testt
testt:
	GCC_PRINT_TREE=1 $(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG)         -S -O0 -o Listing16-2sub.s Listing16-2sub.cbl -fdump-tree-gimple
	GCC_PRINT_TREE=1 $(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -main   -S -O0 -o Listing16-2.s Listing16-2.cbl -fdump-tree-gimple

.PHONY: test
test:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG)         -c -O0 -o Listing16-2sub.o Listing16-2sub.cbl
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-2.cbl  Listing16-2sub.o $(COBOL_RUNTIME_LIBRARY)
	$(TEST) <input.txt >under-test.txt 2>&1 || true
	diff -u known-good.txt under-test.txt || $(DONT_FAIL_DIFF)

.PHONY: known-good
known-good:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG)         -c -O0 -o Listing16-2sub.o Listing16-2sub.cbl
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -main    -O0 -o test Listing16-2.cbl  Listing16-2sub.o $(COBOL_RUNTIME_LIBRARY)
	$(TEST) <input.txt >under-test.txt 2>&1 || true
	cp under-test.txt known-good.txt

.PHONY: clean
clean:
	rm -fr *.tags *.gimple *.s gc test* *.o

