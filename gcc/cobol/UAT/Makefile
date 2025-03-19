.PHONY: all test

test:	testsuite
	@if [ "$(GCOBOL_BUILD_DIR)" ];				\
	then							\
	  echo Using libraries:; 				\
	  find $(GCOBOL_BUILD_DIR)/$(GCOBOL_ARCH) -name \*.so |	\
		grep -E 'libgcobol|libstdc[+]' | xargs file;	\
	fi
	./testsuite $(if $(KEYWORDS),-k $(KEYWORDS))

fail:	failsuite
	./failsuite $(if $(KEYWORDS),-k $(KEYWORDS))

skip:	skipsuite
	./skipsuite $(if $(KEYWORDS),-k $(KEYWORDS))

bugs:	bugsuite
	./bugsuite $(if $(KEYWORDS),-k $(KEYWORDS)) $(TFLAGS)

all:	test fail

TESTSUITE_AT_FILES=$(wildcard ./testsuite.src/*.at)
FAILSUITE_AT_FILES=$(wildcard ./failsuite.src/*.at)
SKIPSUITE_AT_FILES=$(wildcard ./skipsuite.src/*.at)
BUGSUITE_AT_FILES=$(wildcard ./bugsuite.src/*.at)
DECLARATIVE_AT_FILES=$(wildcard ./testsuite.src/declaratives.src/*.cob)

vis:
	echo FAILURE.bad: $(FAILURE.bad)
	echo FAILSUITE_OK_FILES: $(FAILSUITE_OK_FILES)

testsuite: atlocal $(TESTSUITE_AT_FILES) $(DECLARATIVE_AT_FILES) testsuite.at
	autom4te --language=autotest -I $@.src -o $@ $@.at

failsuite: atlocal $(FAILSUITE_OK_FILES) failsuite.at
	autom4te --language=autotest -I $@.src -o $@ \
		$@.at $(addprefix failsuite.src/,typedef.at)

skipsuite: atlocal $(SKIPSUITE_AT_FILES) skipsuite.at
	autom4te --language=autotest -I $@.src -o $@ $@.at

bugsuite: atlocal $(BUGSUITE_AT_FILES) bugsuite.at
	autom4te --language=autotest -I $@.src -o $@ $@.at

clean:
	@rm -fr *~ *.log testsuite  testsuite.dir \
                     failsuite  failsuite.dir \
                     skipsuite  skipsuite.dir \
                     bugsuite   bugsuite.dir
