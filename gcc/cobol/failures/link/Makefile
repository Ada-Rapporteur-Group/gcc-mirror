.SUFFIXES: .cbl

D = $(realpath ../../)
GCOBOL = $(D)/built-gcobol
COBFLAGS = -ggdb -Og $F
#LDFLAGS = -L$(D)/lib -Wl,-rpath=$(D)/lib

all: main timedir libshowdir.so

main: main.cbl | libsub.so
	$(GCOBOL) $(COBFLAGS) $F -o$@ $(LDFLAGS) \
		-L$(PWD) -Wl,-rpath=$(PWD) $^ -lsub

libsub.so: sub.o sub2.o
	$(GCOBOL) $(COBFLAGS) -shared -o$@ $^

libshowdir.so: showdir.cbl
	$(GCOBOL) $(COBFLAGS) -shared -o$@ $^

timedir: timedir.c libshowdir.so
	$(CC)  $(COBFLAGS) -o$@ $(LDFLAGS) -lshowdir -L$(PWD) -Wl,-rpath=$(PWD) $^

test: main libsub.so
	./main
	xPARAMETERS_ON_ENTRY=1 ./timedir

.cbl.o:
	$(GCOBOL) $(COBFLAGS) -c -fPIC -o$@ $^
