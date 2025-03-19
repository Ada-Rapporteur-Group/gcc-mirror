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

.PHONY: all
all:
	@echo "These routines use the build executables at $(GCC_BIN)"

	@echo '"make testv"  compiles test.cbl'
	@echo '"make testd" is the same, but launches cobol1 using GDB'

	@echo '"make ccc"  will launch a C compilation'
	@echo '"make cccd" is the same, but launches cc1 using GDB'

.PHONY: testv
testv:
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG) -S -o test.s $(SOURCE_FILE)
	$(GCC_BIN)/$(GCOBOL) $(SEARCH_PATHS) $(DEBUG)    -o test   $(SOURCE_FILE) $(COBOL_RUNTIME_LIBRARY) -fdump-tree-gimple -fdump-generic-nodes

.PHONY: testd
testd:
	gdb --args \
	$(GCC_BIN)/$(COBOL1) $(SOURCE_FILE) -quiet -dumpbase test.cbl -dumpbase-ext .cbl -mtune=generic -march=x86-64 -ggdb -O0 -o test.s

.PHONY: clean
clean:
	@rm -f test ccc ccc.s test.s *.gimple *.nodes *.o *.html

.PHONY: ccc
ccc:
#	time -p $(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc  ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc.s ccc.c -S
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc   ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes

.PHONY: cccdd
cccdd:
#	time -p $(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc  ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O2 -o ccc.s ccc.c -S
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O2 -o ccc   ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes


.PHONY: ccc.o
ccc.o:
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc.s ccc.c -S
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc   ccc.c -c \
			-rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes

.PHONY: ccc2
ccc2:
#	time -p $(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc  ccc.c -rdynamic -ldl -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc1.s ccc1.c -S -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc2.s ccc2.c -S -fdump-tree-gimple -fdump-generic-nodes
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc1.o ccc1.c -c
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc2.o ccc2.c -c
	$(GCC_BIN)/$(GCC) -B $(GCC_BIN) -ggdb -O0 -o ccc ccc1.o ccc2.o

.PHONY: cccd
cccd:
#	gdb --args \
#	$(GCC_BIN)/cc1 -quiet -imultiarch x86_64-linux-gnu -iprefix $(GCC_BIN)/../lib/gcc/x86_64-linux-gnu/13/ -isystem $(GCC_BIN)/include -isystem $(GCC_BIN)/include-fixed $(CCC_SOURCE) -quiet -dumpbase ccc.c -dumpbase-ext .c -mtune=generic -march=x86-64 -ggdb -O0 -o test.s
	gdb --args \
	$(GCC_BIN)/cc1 -quiet -imultiarch x86_64-linux-gnu -iprefix $(GCC_BIN)/../lib/gcc/x86_64-linux-gnu/13/ -isystem $(GCC_BIN)/include -isystem $(GCC_BIN)/include-fixed $(CCC_SOURCE) -dumpbase ccc.c -mtune=generic -march=x86-64 -O0 -o ccc.s -fdump-generic-nodes

LINES = 3

.PHONY: many
many:
	./many.py $(LINES)
	$(MAKE) -f Makefile ccc
	$(MAKE) -f Makefile testv

.PHONY: cpp
cpp:
	g++ -o ccc ccc.cc
	./ccc