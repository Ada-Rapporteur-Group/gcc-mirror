all:	test

test:	testsuite
	./testsuite -c
	./testsuite

testsuite:	atlocal package.m4 testsuite.at \
	./oddballs.at ./string.at ./unstring.at \
	./src/string_001.cob ./src/string_001a.cob \
	./src/string_001b.cob ./src/string_001c.cob \
	./src/string_002a.cob ./src/string_002b.cob \
	./src/string_002c.cob ./src/string_002d.cob \
	./src/string_003.cob ./src/string_004.cob \
	./src/string_005.cob ./src/string_005.cob \
	./src/string_006.cob ./src/string_007.cob \
	./src/string_008.cob ./src/string_009.cob \
	./src/string_020.cob ./src/string_021.cob \
	./src/unstring_001.cob ./src/unstring_002.cob \
	./src/unstring_003.cob ./src/unstring_004.cob \
        ./src/oddballs_001.cob ./src/oddballs_002.cob \
	./src/oddballs_003.cob
	autom4te --language=autotest -I. -o testsuite testsuite.at

gnusuite:	testsuite
	autom4te --language=autotest -I. -o gnusuite testsuite.at


clean:
	./testsuite -c
