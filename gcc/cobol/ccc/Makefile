user=$(shell echo $$USER)

include MakeVars.inc

GCC-COBOL-REPO = $(realpath ../../..)
GCC_BIN = $(GCC-COBOL-REPO)/build/gcc

GCC    = xgcc
GPP    = xg++
GCOBOL = gcobol
COBOL1 = cobol1

SOURCE_FILE=test.cbl
CCC_SOURCE=ccc.c

DEBUG=-ggdb -O0

.PHONY: all
all:
	@echo "These routines use the build executables at $(GCC_BIN)"

	@echo '"make testv"  compiles test.cbl'
	@echo '"make testd" is the same, but launches cobol1 using GDB'

	@echo '"make ccc"  will launch a C compilation'
	@echo '"make cccd" is the same, but launches cc1 using GDB'

.PHONY: testv
testv:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -S -o test.s $(SOURCE_FILE) $(GCOPTIONS)
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG)    -o test   $(SOURCE_FILE) $(COBOL_RUNTIME_LIBRARY) $(GCOPTIONS) -fdump-tree-gimple -fdump-generic-nodes

.PHONY: testp
testp:
	perf stat $(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -o test   $(SOURCE_FILE) $(GCOPTIONS) $(COBOL_RUNTIME_LIBRARY)

.PHONY: testd
testd:
	gdb --args \
	$(GCC_BIN)/$(COBOL1) $(SOURCE_FILE) -quiet -dumpbase $(SOURCE_FILE) -dumpbase-ext .cbl -mtune=generic -march=x86-64 $(DEBUG) $(GCOPTIONS) -o test.s

.PHONY: clean
clean:
	@rm -f test ccc ccc.s test.s *.gimple *.nodes *.o *.html

.PHONY: ccc
ccc:
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc.s ccc.c -S
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc   ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes

.PHONY: cccp
cccp:
	perf stat $(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc   ccc.c -rdynamic -ldl $(GCOPTIONS) # -fdump-tree-gimple -fdump-generic-nodes

.PHONY: cccdd
cccdd:
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc.s ccc.c -S
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc   ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes


.PHONY: ccc.o
ccc.o:
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc.s ccc.c -S
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc   ccc.c -c \
			-rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes

.PHONY: ccc2
ccc2:
#	time -p $(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc  ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc1.s ccc1.c -S -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc2.s ccc2.c -S -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc1.o ccc1.c -c
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc2.o ccc2.c -c
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) $(DEBUG) -o ccc ccc1.o ccc2.o

.PHONY: cccd
cccd:
#	gdb --args \
#	$(GCC_BIN)/cc1 -quiet -imultiarch x86_64-linux-gnu -iprefix $(GCC_BIN)/../lib/gcc/x86_64-linux-gnu/13/ -isystem $(GCC_BIN)/include -isystem $(GCC_BIN)/include-fixed $(CCC_SOURCE) -quiet -dumpbase ccc.c -dumpbase-ext .c -mtune=generic -march=x86-64 $(DEBUG) -o test.s
	gdb --args \
	$(GCC_BIN)/cc1 -quiet -imultiarch x86_64-linux-gnu -iprefix $(GCC_BIN)/../lib/gcc/x86_64-linux-gnu/13/ -isystem $(GCC_BIN)/include -isystem $(GCC_BIN)/include-fixed $(CCC_SOURCE) -dumpbase ccc.c -mtune=generic -march=x86-64 $(DEBUG) -o ccc.s -fdump-generic-nodes

LINES = 3

.PHONY: many
many:
	./many.py $(LINES)
	$(MAKE) -f Makefile ccc
	$(MAKE) -f Makefile testv

.PHONY: cpp
cpp:
	g++ -Wa,-adhln -ggdb -O0 -S -o ccc.s ccc.cc
#	g++ -Wa,-adhln -ggdb -O0 ccc.cc > ccc.s
	g++ -ggdb -O0 -o ccc ccc.cc
	./ccc

.PHONY: gcp
gcp:
	perf stat cobc -O0 -o gc -x $(SOURCE_FILE)

.PHONY: gcp2
gcp2:
	perf stat cobc -O2 -o gc -x $(SOURCE_FILE)
