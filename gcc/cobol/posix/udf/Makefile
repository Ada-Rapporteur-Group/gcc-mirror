LDFLAGS = -L $$(pwd) -Wl,-rpath -Wl,$$(pwd)

all: t/exit t/errno

t/exit: posix-exit.cbl t/exit.cbl
	../../built-gcobol $(FLAGS) -o $@ -I$$(pwd) $(lastword $^)

t/errno: t/errno.cbl posix-mkdir.cbl | libposix-errno.so
	../../built-gcobol $(FLAGS) -o $@ -I$$(pwd) \
	$(firstword $^) $(LDFLAGS) -lposix-errno

libposix-errno.so: ../c/posix_errno.c posix-errno.o
	gcc $(CFLAGS) -shared -o $@ $^

posix-errno.o: posix-errno.cbl
	../../built-gcobol $(FLAGS) -fPIC  -c -o $@ $^

posix-mkdir.cbl:
	man 2 mkdir | ../scrape.awk | \
	../udf-gen -D mode_t=unsigned\ long  > $@~
	@mv $@~ $@

test: $(basename $(wildcard t/*.cbl))
	t/errno

clean:
	rm -f *.o *.so $(basename $(wildcard t/*.cbl))
