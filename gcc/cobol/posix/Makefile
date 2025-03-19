prototypes.c:  headers prototypes.cpp
	cat $^ > $@~
	@mv $@~ $@

prototypes.cpp: posix.txt
	awk -F'[/.]' '{ print $$6 }' $^ | \
	while read F; do echo "/* $$F */" && man 2 $$F | \
			./scrape.awk -v funcname=$$6; done > $@~
	@mv $@~ $@

posix.txt:
	zgrep -l 'POSIX[.]' /usr/share/man/man2/*z > $@~
	@mv $@~ $@
