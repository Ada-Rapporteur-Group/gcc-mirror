GCOBOL = gcobol
COBOL1 = cobol1
DEBUG ?= -ggdb -O0

### This bit of boilerplate establishes the top-level directory of the
### repository.  It's useful in the GCOBOL environment that tests the binaries
### under development because not all Makefiles are the same distance away from
### the repository top-level folder.
###
### There are other ways of determining TOP_LEVEL, but the portability of this
### construction has its merits
###
### The GIT_ERROR test is a nod to the reality that all environments are not
### like my environment, and the user deserves at least a head's up about what's
### wrong and how to fix it.

GIT_ERROR=$(shell git rev-parse --show-toplevel >/dev/null 2>/dev/null; echo $$?)
ifneq ($(GIT_ERROR), 0)
SPACE := $(subst ,, )
$(info )
$(info This Makefile assumes that it is part of a GIT repository.)
$(info Because it is not, it can't determine the top level directory.)
$(info You will have to provide that information like this:)
$(info )
$(info $(SPACE)    make <rule> TOP_LEVEL=<top-level-directory>)
$(info )
$(error Aborting)
endif
TOP_LEVEL=$(shell git rev-parse --show-toplevel)

#
# BUILD_ROOT is the path to place where the build took place:
#
BUILD_ROOT ?= $(TOP_LEVEL)/build

# GCC_BIN is the relative path to the executables built by gcc-cobol/make
GCC_BIN = $(BUILD_ROOT)/gcc


LIBCOBOL_A=$(shell find $(BUILD_ROOT) -name "libgcobol.a")
LIBCOBOL_PATH = $(dir $(LIBCOBOL_A))
LIBROOT = $(subst /libgcobol/.libs/,,$(LIBCOBOL_PATH))
LIBSTDC_PATH = $(LIBROOT)/libstdc++-v3/src/.libs

comma = ,

RPATH = $(addprefix -Wl$(comma)-rpath=,$(LIBCOBOL_PATH) $(LIBSTDC_PATH))
COBOL_RUNTIME_LIBRARY = $(RPATH)

SEARCH_PATHS = \
 -B $(GCC_BIN) \
 -L $(LIBSTDC_PATH) \
 -L $(LIBCOBOL_PATH) \
 $(END)

TEST=./test
