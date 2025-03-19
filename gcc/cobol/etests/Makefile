# "make known-good" creates "known-good.txt" files in each subdirectory.
# "make test" checks the output of each compilation against the known-good file

include MakeVars.inc

P1:=$(COBOL_RUNTIME_LIBRARY)
P2:=$(SEARCH_PATHS)

# Get the list of subdirectories.
SUBDIRS = $(shell ls -d */)

# That list is the same for the various things we want to do, so tack on
# suffixes so that the rules below can tell them apart:
UNDER_TESTS = $(addsuffix under-test.txt , $(SUBDIRS))
KNOWN_GOODS = $(addsuffix known-good.txt , $(SUBDIRS))
TO_BE_CLEANED = $(addsuffix dummy , $(SUBDIRS))

# Note that the commands have "$(dir $@)" in them, which strips the
# suffixes off again.

.PHONY: all
all:
	$(error Choose from 'make test' and 'make known-good'.)

.PHONY: test $(UNDER_TESTS)
test: $(UNDER_TESTS)
$(UNDER_TESTS):
	@$(MAKE) -C $(dir $@) test COBOL_RUNTIME_LIBRARY="$(P1)" SEARCH_PATHS="$(P2)"

.PHONY: known-good $(KNOWN_GOODS)
known-good: $(KNOWN_GOODS)
$(KNOWN_GOODS):
	@$(MAKE) --no-print-directory -C $(dir $@) known-good COBOL_RUNTIME_LIBRARY="$(P1)" SEARCH_PATHS="$(P2)"

.PHONY: clean $(TO_BE_CLEANED)
clean: $(TO_BE_CLEANED)
$(TO_BE_CLEANED):
	@$(MAKE) -C $(dir $@) clean
