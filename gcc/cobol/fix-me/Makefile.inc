# This makefile is for regression testing.  It assumes there is a
# single .cbl file to be compiled and run, The combined output of the
# compilation and the run is placed in an under-test.txt file, and then
# compared with a known-good.txt file.

# This include file establishes the path to the compilation executables
include ../MakeVars.inc

SOURCE_FILE = $(wildcard *.cbl)
DONT_FAIL_DIFF ?= false
DEBUG = -ggdb

BEFORE := $(wildcard before.scr)
AFTER  := $(wildcard after.scr)

.PHONY: all
all:
	@echo "Choices:"
	@echo "'make testv'   -- GCOBOL compile and run $(SOURCE_FILE)"
	@echo "'make testvv'  -- compiles with -f-flex-debug -f-yacc-debug"
	@echo "'make testd'   -- uses gdb to launch cobol1"
	@echo "'make testt'   -- does a gimple + tags build"
	@echo "'make gc'      -- uses cobc to compile and run $(SOURCE_FILE)"

.PHONY: test
test: testv

.PHONY: testv
testv:
ifneq ("$(BEFORE)","")
	./$(BEFORE)
endif
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY)
	./test < input.txt
ifneq ("$(AFTER)","")
	./$(AFTER)
endif

.PHONY: testvv
testvv:
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY) -f-flex-debug -f-yacc-debug

.PHONY: tests
tests:
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -S -o test.s $(GCOPTIONS) $(SOURCE_FILE)
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0    -o test   $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY) \
        -Wa,-aln > $(basename $(SOURCE_FILE)).lst

.PHONY: gc
gc:
	cobc -x -free -o gc $(SOURCE_FILE)
	./gc

.PHONY: testd
testd:
	GCC_PRINT_TREE=1 gdb -q --args $(GCC_BIN)/$(COBOL1) $(GCOPTIONS) $(SOURCE_FILE) \
        -quiet -dumpbase $(SOURCE_FILE) -mtune=generic -march=x86-64 \
        $(DEBUG) -O0 -version -o $(basename $(SOURCE_FILE)).s

.PHONY: testt
testt:
	@rm -f test
	GCC_PRINT_TREE=1 $(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test \
         $(GCOPTIONS) $(SOURCE_FILE) $(COBOL_RUNTIME_LIBRARY) -fdump-tree-gimple

.PHONY: testg
testg:
	$(GCC_BIN)/$(COBOL1) -main $(SOURCE_FILE) \
        -quiet -dumpbase $(GCOPTIONS) $(SOURCE_FILE) -mtune=generic -march=x86-64 \
        $(DEBUG) -O0 -version -o $(basename $(SOURCE_FILE)).s

.PHONY: clean
clean:
	rm -fr *.tags *.gimple *.s *.lst gc test dump.txt *.nodes *.nodes.html

