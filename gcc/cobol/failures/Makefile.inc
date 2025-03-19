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

PROCESSOR=$(shell uname -p)

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
#ifeq ($(PROCESSOR), x86_64)
#	$(GCC_BIN)/$(COBOL1) $(GCOPTIONS) $(SOURCE_FILE) \
#        -quiet -dumpbase $(SOURCE_FILE) -mtune=generic -march=x86-64 \
#        $(DEBUG) -O0 -o $(basename $(SOURCE_FILE)).s
#endif
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY) -Wa,-a | sed -e '/^\f.*$$/d' -e '/^$$/d' > $(basename $(SOURCE_FILE)).lst
	./test < input.txt
ifneq ("$(AFTER)","")
	./$(AFTER)
endif

.PHONY: testvo2
testvo2:
ifneq ("$(BEFORE)","")
	./$(BEFORE)
endif
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O2 -o test $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY)
	./test < input.txt
ifneq ("$(AFTER)","")
	./$(AFTER)
endif


.PHONY: testvv
testvv:
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY)

.PHONY: tests
tests:
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -S -o test.s $(GCOPTIONS) $(SOURCE_FILE)
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0    -o test   $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY) \
        -Wa,-a | sed -e '/^\f.*$$/d' -e '/^$$/d' > $(basename $(SOURCE_FILE)).lst

.PHONY: gc
gc:
	cobc -x -free -o gc $(SOURCE_FILE)
	./gc

.PHONY: testd
testd:
ifeq ($(PROCESSOR), x86_64)
	gdb -q --args $(GCC_BIN)/$(COBOL1) $(GCOPTIONS) $(SOURCE_FILE) \
        -quiet -dumpbase $(SOURCE_FILE) -mtune=generic -march=x86-64 \
        $(DEBUG) -O0 -o $(basename $(SOURCE_FILE)).s
endif
ifeq ($(PROCESSOR), aarch64)
	gdb -q --args $(GCC_BIN)/$(COBOL1) $(SOURCE_FILE) -quiet \
    -dumpdir test- -dumpbase $(SOURCE_FILE) -dumpbase-ext .cbl \
    -mlittle-endian "-mabi=lp64" $(DEBUG) -O0 -o $(basename $(SOURCE_FILE)).s
endif

.PHONY: testdd
testdd:
ifeq ($(PROCESSOR), x86_64)
	gdb -q --args $(GCC_BIN)/$(COBOL1) $(GCOPTIONS) $(SOURCE_FILE) \
        -quiet -dumpbase $(SOURCE_FILE) -mtune=generic -march=x86-64 \
        $(DEBUG) -O2 -o $(basename $(SOURCE_FILE)).s
endif
ifeq ($(PROCESSOR), aarch64)
	gdb -q --args $(GCC_BIN)/$(COBOL1) $(SOURCE_FILE) -quiet \
    -dumpdir test- -dumpbase $(SOURCE_FILE) -dumpbase-ext .cbl \
    -mlittle-endian "-mabi=lp64" $(DEBUG) -O2 -o $(basename $(SOURCE_FILE)).s
endif

.PHONY: testt
testt:
	@rm -f test
	$(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test \
         $(GCOPTIONS) $(SOURCE_FILE) $(COBOL_RUNTIME_LIBRARY) -fdump-tree-gimple -fdump-generic-nodes

.PHONY: testg
testg:
	$(GCC_BIN)/$(COBOL1) -main $(SOURCE_FILE) \
        -quiet -dumpbase $(GCOPTIONS) $(SOURCE_FILE) -mtune=generic -march=x86-64 \
        $(DEBUG) -O0 -version -o $(basename $(SOURCE_FILE)).s

.PHONY: clean
clean:
	rm -fr *.tags *.gimple *.s *.lst gc test dump.txt *.nodes *.nodes.html REPORTT XXXXX*

.PHONY: testso
testso:
#	$(GCC_BIN)/$(GCOBOL) -fPIC -shared $(SEARCH_PATHS) $(DEBUG) -O0 -o test.so $(GCOPTIONS) $(SOURCE_FILE) $(COBOL_RUNTIME_LIBRARY)
	$(GCC_BIN)/$(GCOBOL) -shared $(SEARCH_PATHS) $(DEBUG) -O0 -o test.so $(GCOPTIONS) $(SOURCE_FILE)


.PHONY: testp
testp:
	perf stat $(GCC_BIN)/$(GCOBOL) -main $(SEARCH_PATHS) $(DEBUG) -O0 -o test $(GCOPTIONS) $(SOURCE_FILE) \
        $(COBOL_RUNTIME_LIBRARY)

.phony: io401
io401:
	/home/bob/repos/gcc-cobol/build/gcc/gcobol -c -B /home/bob/repos/gcc-cobol/build/gcc -L /home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libstdc++-v3/src/.libs -L /home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libgcobol/.libs/ -Wl,-rpath=/home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libgcobol/.libs/Wl,-rpath=/home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libstdc++-v3/src/.libs -o io401.o  -D C-OBS-ARCH=x86 -D C-OBS-COMPILER=2 -D C-OBS-OS=Linux -D C-OBS-PRECOMP=ocesql -copyext .lib -dialect mf -fno-static-call io401.cbl

.phony: io401d
io401d:
	gdb -q --args  /home/bob/repos/gcc-cobol/build/gcc/cobol1 io401.cbl -quiet -dialect mf -dumpdir io401- -dumpbase io401.cbl -dumpbase-ext .cbl "-mtune=generic" "-march=x86-64" -fno-static-call -D "C-OBS-ARCH=x86" -D "C-OBS-COMPILER=2" -D "C-OBS-OS=Linux" -D "C-OBS-PRECOMP=ocesql" -copyext .lib -dialect mf -o io401.s

.phony: io401s
io401s:
	/home/bob/repos/gcc-cobol/build/gcc/gcobol -S -B /home/bob/repos/gcc-cobol/build/gcc -L /home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libstdc++-v3/src/.libs -L /home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libgcobol/.libs/ -Wl,-rpath=/home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libgcobol/.libs/Wl,-rpath=/home/bob/repos/gcc-cobol/build/x86_64-linux-gnu/libstdc++-v3/src/.libs -o io401.s  -D C-OBS-ARCH=x86 -D C-OBS-COMPILER=2 -D C-OBS-OS=Linux -D C-OBS-PRECOMP=ocesql -copyext .lib -dialect mf -fno-static-call io401.cbl

