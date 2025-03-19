Thu Oct 21 16:38:17 2021
For reasons unclear, with Make-lang.in:

    YACC = bison
    YFLAGS = -Werror --debug --token-table --defines=cobol/parse.h \
	    --report-file=cobol/parser.out --verbose

the gcc build insists on calling yacc for .y files:

	$ bison -y -o cobol/parse.c -Werrro --debug --token-table \
	  --defines=cobol/parse.h \
	  --report-file=cobol/parser.out --verbose ../../gcc/cobol/parse.y

"bison -y" comes from the yacc shell script that bison uses to emulate yacc.

Of course, it's not really yacc.  It's bison with yacc diagnostics and
yacc defaults.  No real yacc accepts that command line.

When you're modifing a compiler, the definition of "bug" is
ambiguous. The gcc docs don't say anywhere that you have to use yacc,
and in fact as of now none of the gcc compilers uses yacc or bison.

What to do?  If we're adding a new dependency to gcc, will anyone on
the project seriously argue in 2022 that anything other than GNU bison
is a reasonable choice?  The simplest assumption is No:

YACC = bison
YFLAGS = -Werror -Wno-yacc --debug --token-table --defines=cobol/parse.h \
	--report-file=cobol/parser.out --verbose

This turns off yacc warnings and still produces a parser.

Mon Oct 25 15:14:12 2021
gcobol adds two options to gcc.  They are defined in lang.opt:

       -f_flex_debug:  enable lex debugging
       -f_yacc_debug:  enable yacc debugging

# Tales of the CDF: the COPY statement
## Thu Nov 18 10:38:31 2021

The COPY statement is a brute.

    COPY src  REPLACING ==x== BY ==y==

means replacing any x with any y.  The arguments do not have to be
COBOL tokens or even complete character strings.  The arguments can
extend across lines and may (in IBM's compiler) be up to 322
characters. The arguments are just text, as long as that text is not "COPY"!

But they are not Just Text.  They are:

* Pseudo-text  (==x== and ==y==))
* An identifier
* A literal
* A COBOL word (except the word COPY)
* Function identifier

In other words, either pseudo-text, or a symbol (variable or
function), or a keyword that isn't COPY.

One of the challenges of a COBOL complier is a strange dynamicism in a
putatively static language. The COPY statement can change keywords,
but the compiler cannot simply self-modify as the input is read.  The
lexer is fixed when the compiler is compiled.

What to do?

The first attempt forked the compiler and rearranged inputs. That was
abandoned when we realized where COPY could appear: not just wherever
a statement occurs, but wherever a **string** appears. That is, at any
one moment, the next call to yylex() could return COPY.

The 2nd attempt is discussed later.

## Sun Nov 21 17:21:54 2021

This script produces a list of tokens reported as unused in the
grammar, and the programs they first appear in:

#! /bin/sh

if [ -z "$1" ]
then
    echo $0 parser.out >&2
fi

awk -e '/^Terminals unused in grammar/,/^Grammar/ {
    if( $1 ) { print $1 }
}' $1 | while read token
do
    grep -lw $token Ch??/*.cbl | head -1 |
	sed "s/^/$token\	/"
done

Organized by chapter, alphabetically:

$ ./build/token_uses build/parser.out |
	awk -F '[\t/]' \
		'{ chap[$2] = chap[$2]? chap[$2] ", " $1 : $1 }
		 END { for( c in chap) { print c, chap[c] } }' | sort

Ch02 COBOL, DIVISION, ID, PROCEDURE, ZEROS
Ch04 FILLER
Ch05 CONTROL
Ch07 WRITE
Ch08 LINES, PAGE
Ch09 ALL, REPLACING
Ch11 OCCURS, REDEFINES, THAN
Ch12 RETURN
Ch13 ASCENDING, INDEXED, KEY, SEARCH
Ch14 DESCENDING, RELEASE, SD, SORT, USING
Ch15 FOR, LEADING, TALLYING
Ch16 CALL, IO, LINKAGE, RANDOM
Ch17 ACCESS, ALTERNATE, COLUMN, DETAIL, FIRST, FOOTING, GENERATE, HEADING,
	 INITIATE, INVALID, LAST, LIMIT, MODE, NEXT, PLUS, RD, RELATIVE, REPORT,
	 REWRITE, TERMINATE, TYPE
Ch18 ARE, CONTROLS, DECLARATIVES, FINAL, GROUP, INDICATE, PF, REPORTING, SUM

## Wed Nov 24 16:41:26 2021

# EVALUATE

EVALUATE cond [ ALSO conds 0-N ]
         [ WHEN  cond [ ALSO conds 0-N ] statements 1-N ]
		 [ WHEN OTHER statements 0-1 ]

## EVALUATE interpretation

    EVALUATE truth ALSO truth [ALSO truth ...]
	    WHEN cond  ALSO cond  [ALSO cond ...]  statements
	END-EVALUATE

On the EVALUATE line, each `truth` is some expression that resolves to a
Boolean value. It could be:

* an arithmetic expression
* some combination of relop, logop, and setop
* TRUE, FALSE, or ANY
*     x THRU y
* NOT x THRU y

where x and y are fields, literals, or expressions.

In any case, the truth expressions are evaluated every time every time
EVALUATE is executed.  Each one resolves to true/false somehow.

In the WHEN clauses, `cond` likewise resolves to a  Boolean value.

# COPY redux
## Sun Feb 20 15:20:24 2022

The Cobol Compiler Directing Facility (CDF) is somewhat analogous to
the C preprocessor, and traditionally was implemented as a
preprocessor. We didn't want to go that route, though. If at all
possible, we wanted a 1-pass compiler.

flex provides features to manage multiple input buffers but, to
support the CDF, you have to parse its grammar, which is complex
enough that you want to use yacc.  Problem is, the CDF grammar
"interrupts" the Cobol grammar arbitrarily: every token returned by
yylex() could start a CDF expression.

CDF is not the end of the road, either. Cobol programs are frequently
an amalgam of many languages implemented with preprocessors. In
addition to the CDF, a program might require CICS and SQL processing.

The solution is to use one lexer and *N* parsers, as a pipeline. The
main parser, `parse.y`, deals with Cobol. When it calls **yylex**(),
though, that's not the function provided by lexer. Instead, it's the
head of the "pre-parser" framework that massages the input and filters
the tokens returned to the parser.

Similar to **atexit**(3), parsers are installed as a stack, each one
at the "head", where the lexer is invoked. Each parser *P* in the
pipeline provides a **yylex**() function and invokes one.  When it
calls yylex(), the token returned is either part of the *P*
grammar, or it is not. If it is, it's handled by parser *P*. If it is
not, it's returned to *its* caller, the next parser in the pipeline.

The analogy to **atexit** is imperfect.  For one thing, **atexit**
functions are all different.  For another, they don't call each
other. And, finally, each function *name* in the **atexit** stack is
unique.

We now enter a maze of twisty little parsers.

Much computer programming is obvious or near-obvious. Most of it boils
down to *input X and output Y*. There are pages and pages of
documentation for functions and programs and utilities that describe
their Xs and Ys. For common large problems, there are books, both for
industrial problems like *Learn SQL Server in 24 Hours* to computer
science tomes on parsers or polygons or signal processing.

The problem of setting up a dynamic chain of programs *must* have been
solved many times before. But there's no support for it in the C
standard library, it's not a textbook problem.

## A dynamic parser chain

We could have each parser in the chain work like this:

    while( token in valid_tokens ) {
        parse(token)
    }
    return token

No yacc output works that way. A *token* either is or is not part of
the language implemented by a yacc parser. Any input token that is not
part of the grammar constitutes an error. That's actually a clue that
the above is wrong: once we've entered a parser, we should exit
(successfully) only when the parser accepts the input stream.  It
doesn't just fling unrecognized tokens up the chain in case it's
useful to someone else!

Each parser has a set of *start* tokens: those that can be the first
token in the language it accepts. If the set of start tokens is
disjoint -- no two parsers share a start token -- then encountering
any start token tells us which parser to engage. It stays engaged
until it succeeds, meaning the token stream is redirected to the
previously-engaged parser, or fails, in which case it's game over for
the whole house of cards, er, parsers.

The parsers also have a priority. In the Cobol case, the priority
looks like this:

1.  CDF
2.  SQL, CICS, IMS, etc.
3.  COBOL

So far, we have only CDF and COBOL.  Later others might be inserted.

The lexer recognizes the union of all tokens for all grammars. (If a
new parser is added later, the lexer might have to be modified to
recognize, at least, the new parser's start tokens.)

That suggests a different model:

    int yylex
    token = yylex();
    if( token in start_tokens and
        parser_of(token) != current_parser )
    {
      start new parser # calls this function recursively for its tokens
    }
    return token

That works.  We rename the scanner's yylex function to **lexer**(),
and define a yylex along the lines of the above.  The CDF parser does
its job, and the Cobol parser resumes where it left off.  For now,
there's no dynamic list and no set of start tokens; if the token is
COPY, we start the CDF parser, else not. It's, er, a start.

But we are not done, because copybook processing can modify the input.

We can use flex's support for multiple input buffers to redirect its
attention to the copybook file. But it cannot read that file directly;
it must apply the substitutions indicated in the COPY directive. Not
just that, but copybooks can be nested: a file referenced by COPY may
itself contain a COPY directive with *different substitutions* (or
none). Substitutions are applied to the input in succession, until the
fully munged text reaches the Cobol parser.

It's possible to do this in a single process; anything is.  But a
problem of successive independent edits to stream of text suggests a
pipeline similar to what the shell does:

    copy copybook | lexer | parser

except that the lexer process is interrupting itself to start the
"copy" process, and read its output, before continuing with its
regularly scheduled programming.

It looks something like this:

    lexing A.cbl
        # hit COPY
        parse COPY
        change lexer input to pipe
        # start child "copy" process
            while read B.cpy
                modify input
                write to pipe
            exit
        read EOF
        reap status of "copy" process
        restore prior input state
        # resume lexing

or like this:

    awk -f

    /COPY foo/ {
        # process COPY parameters
        ...
        while( getline < "foo.cpy" ) {
            # process copybook file
            ...
        }
    }

Sat Apr 30 13:05:44 EDT 2022

# Name Resolution

In Cobol, a variable's name is unique within its hierarchy.  If it's
not unique globally, any partial qualification is sufficient that
identifies it uniquely.  Given the structure

    01  A
        02  B
            03  A
            03  B
            03  C

a program can refer to `C` alone, because it's unique.  Although
unnecessary, it can also over-qualify it:

    `C of B of A`
or  `C of B`
or  `C of A`

The problem for the parser is to recognize when a referenced name is
unique and when it's not.  And to reject incorrect references, such as

    C of A of B

A reference to `A` alone means the 01 group.  There is no syntax to
say *A of program P* or *01 A*.  In fact, level numbers are never
referenced in a Cobol program.  Level numbers serve only to describe
the hierarchy, and levels may be renumbered by the compiler (while
retaining the same relative structure).  To avoid confusion, Some
compilers require 01 names to be unique (forbid non-01 by the same
name).

## Example Problem

In gcobol, symbols are kept in a linear symbol table.  Hierarchy is
represented by a field's `parent`, which is an index into the symbol
table.  Naturally, data elements (usually) have names, too. To illustrate:

    17        01  A
    18            02  B
    19                03  A
    20                03  B
    21                03  C

The fields 19, 20, and 21 have a parent of 18, and 18 has parent 17.

One may think of the structure as an array of parents:

    Field#  Name  Parents
    21      C     18, 17
    20      B     18, 17
    19      A     18, 17
    18      B     17
    17      A      0

In this example `A` alone is not ambiguous under the rule "01
reigns". `C` is unique, and `B` always needs qualification.

## Resolution Algorithm

For any name, generate a *structure sequence* for each qualifying component.

If there is no qualification (just the bare name), accept if:

-  There is an 00, 01 or 77 by that name, or
-  There is only one field with that name

Else it's an error. (00 level is reserved for register names, e.g. `FILE-STATUS`.)

Here's an example from NIST program NC202A:

    MOVE   11  TO  ADD-CORR-1 OF GRP-FOR-ADD-CORR-1.

Several fields are called `ADD-CORR-1`:

    117: 01 GRP-FOR-ADD-CORR-1   P   0
    121: 03 ADD-CORR-1           P 118
    132: 05 ADD-CORR-1           P 131
    145: 04 ADD-CORR-1           P 144
    162: 05 ADD-CORR-1           P 158

Their structure:

    Field#  Name                 Parents
    117     GRP-FOR-ADD-CORR-1
    121     ADD-CORR-1           118 117
    132     ADD-CORR-1           131 130
    145     ADD-CORR-1           144 143
    162     ADD-CORR-1           158 157 156

The Cobol `MOVE` statement refers a field named `ADD-CORR-1` that is
part of `GRP-FOR-ADD-CORR-1`.  We have 4 candidates: fields 121, 132,
145, and 162, and 1 candidate group, field 117. Only field 121 has 117
among its parents, and that is unique because it's at the root (has
no ancestor). Therefore, field 121 unique meets the selection criteria.

## Implementation

When all data fields have been added to the symbol table (at the
beginning of `PROCEDURE DIVISION`) compose a map --
`std::multimap<string, vector<size_t>>` -- to represent each name and
its *structure sequence*.

The function

    cbl_field_t * symbol_field_find( std::list<string> names );

uses the symbol map to resolve the name, or return `NULL` on error.

For each name in `names`, it builds a `std::set<vector<size_t>>` of
the `mapped_type` for the first name from the symbol map. (The 1st
element of the vector is the field's number.) Call this the *items*
set.  It then builds the same kind of set, a *groups* set, for the
next name, and eliminates from *items* set any entries whose structure
is not a superset an entry in *groups*.

The process is repeated for each successive name in `names`. When the
`names` vector is exhausted, *items* has 0, 1, or more entries
remaining.

Success is defined when exactly 1 item remains.  Zero *items*
indicates no such name exists, and 2 or more indicates an ambiguous
name.

# Location, Location, Location
## Wed Jul  6 14:33:40 2022

Relying solely on `yylineno` for error messages is somewhat
misleading.  Relying on it for debugging would be infuriating.

`yylineno` is set by the lexer.  In an LALR(1) parser like the one
generated by Bison, very often that's the line of the *lookahead*
token.  In Cobol, often the lookahead token is the verb for the next
statement, which is seldom on the same line as the current statement.

This manifested in gcobol as *sometimes*.  Sometimes the line number
in the syntax error was off by one.  We shrugged that off until it
became a real problem.  Alas, that day has arrived.

In Bison, every token -- terminal and nonterminal -- has a location.
Technically, it's a user-defined type, but the default `YYLTYPE` is
fine. It's the lexer's job to set `yylloc`; the generated parser
associates the values in that variable with each token.

A small bit of apprentice wizardry exposes `YYLTYPE` in `symbols.h`,
and a new function `cobol_location` to return it. In the parser
actions, we set the global location to be that of the statement's
verb, e.g. `DISPLAY`.  Now the **gdb** user knows he can set a
breakpoint by line number, wherever a statement begins.

## Tue Jul 12 17:08:40 2022

It seems gcc does not like it if we assign to `yylineno`.

    cobol1: internal compiler error: in linemap_line_start, at libcpp/line-map.cc:867

That error is provoked if `yylineno` is restored to its prior value
when the lexer pops its input stack of filenames.  That is, when we
reach EOF for a copybook file, we want to set the line number back to
what it was before we opened the copybook file.  If we do, the apple cart
upset becomes.

This might not matter. Soon to come is reworked input-preprocessing to
deal with line-continuation shenanigans permissible in Cobol.  (For
example, it's valid to split keywords across lines.)

# PERFORM acrobatics
## Thu Jul 21 12:36:28 2022

Consider the following program:

    PROCEDURE DIVISION.
       GREETING.
            DISPLAY 'HI'.

    S2 SECTION.
       PERFORM GREETING.
       GREETING.
            DISPLAY 'BYE'.

    LAST SECTION.
       STOP RUN.

What does it print?

 - `HI`  because execution starts at the beginning.
 - `BYE` because `PERFORM GREETING` finds `GREETING OF S2`.
 - `BYE` because execution continues after the PERFORM, through the paragraph

Now consider this: when the parser sees `PERFORM GREETING`, a
perfectly good definition for GREETING exists, above the
section. Naively, it might say, "This is no forward reference.
There's a `GREETING`, so let's perform it."  Generate the code and
move onto the next statement. What to do, then, when `GREETING of S2`
makes its appearance?

The naive approach as our first one, so the compiled code produced:

 - `HI`  because execution starts at the beginning.
 - `HI`  because `PERFORM GREETING` found the `GREETING` on line 2.
 - `BYE` because execution continues after the PERFORM.

What to do?

A solution presented itself:

  - *Assume* every `PERFORM` refers to a paragraph in the current section
  - If no such paragraph is defined, generate one at the end of the section

That leads to inefficient code, in some cases to 3 levels of
indirection. While it might work, we opted for what we think is a
better solution:

  - Detect the incorrectly resolved targets
  - Update the Gimple tree with corrected targets

This takes advantage of the GCC design. The front end parses the Cobol
text and constructs an in-memory version of the program, a Gimple
tree.  Code generation doesn't begin until parsing is done, at which
point the tree is submitted to the back end.  Until that point, the
tree can be modified as needed.  This is one of those needs.

# Linking and Loading
## Tue Feb  7 12:02:54 2023

If you have a fox, a bag of grain, a chicken, and two COBOL files, how
do you get them all across the river?

More simply: Given 2 COBOL modules, how to we link them together?  Answers:

1.  Statically
2.  Dynamically

## Statically

With static linking, all symbols are resolved by the static
linker, **ld**(1).

    gcobol -o X A.cbl B.cbl

compiles both COBOL programs and links them to produce an executable, `X`.

    gcobol -o libX.so -shared A.cbl B.cbl

compiles both COBOL programs and links them to produce a shared
object, or dynamic library (same thing).

The *lib* prefix is a Unix convention.  It doesn't signify anything to
the operating system; a file with that prefix need not be a shared
object, and shared objects need not have that prefix. But some *tools*
rely on the *lib* prefix (and *.so* extension) as defaults.

    gcobol -c A.cbl B.cbl

compiles both COBOL programs and produces object files from each
one, namely `A.o` and `B.o`.

    gcobol -o X A.cbl B.o

compiles `A.cbl` to produce `A.o`, and links `A.o` and `B.o` to
produce `X`.

## Dynamically

With dynamic linking, all symbols are *checked* by the static linker,
but aren't resolved until the executable is loaded, when the run-time
linker runs.  The static linker ensures that the libraries available
when the executable is produced supply all the symbols the executable
uses. One *hopes* that when the executable runs, those same libraries
-- i.e., the versions of those libraries -- will be installed on the
host machine. If that hope is dashed, the runtime linker will report
an error, and the executable will not run.

    gcobol -o libB.so -shared B.cbl
    gcobol -o A  A.cbl -L. -lB

compiles and links `B.cbl` to `libB.so`, then compiles `A.cbl` and
links it to `libB.so`. But "link" here does not mean any real linking
is done. When the static linker sees a shared object as input, it only
uses the shared object's list of exported names, to confirm that the
program could use the library to resolve its symbols.

If at this stage you try to run `A`, it will probably fail, with
**ld.so**(8) saying it can't find `libB.so`. Normally, the runtime
linker does not look in the current working directory for
libraries. Its default search locations are controlled by its
configuration and environment variables, but by default it usually
looks in `/lib` and `/usr/lib`.  That is why libraries are normally
installed prior to use.

If the library is not going to be used from a standard location, the
linker has to be told where else to look for it. One way that's done
is through the environment:

    LD_LIBRARY_PATH=$PWD ./A

adds the current working directory to its search list, where indeed it
will find `libB.so`.

A better way it to add the search directory to the executable, using
linker flags:

    gcobol -o A  A.cbl -L. -Wl,-rpath=$PWD -lB

Here,

    -Wl,

(note the comma) is a **gcc**(1) option whose argument is passed to
the linker. That argument is

    -rpath=$PWD

To quote the **ld**(1) man page:

 *Add a directory to the runtime library search path.  This is used
  when linking an ELF executable with shared objects.  All -rpath
  arguments are concatenated and passed to the runtime linker, which
  uses them to locate shared objects at runtime.*

When the linker produces the `A` executable, it adds the **-rpath**
directory to it, in the *RPATH* or *RUNPATH* tag. When the executable
is loaded and run, the runtime linker consults those tags for
information on where to search for libraries.

## Example: showing is knowing

Above, we ignored *position-independent code* because it's a detail.
In working examples, we have to include it. Let's show the parts:

Program A:

        ID DIVISION.
          PROGRAM-ID A.

        PROCEDURE DIVISION.
          SAY-AHH.
            DISPLAY "Ahh".

Program B:

        ID DIVISION.
          PROGRAM-ID B.

        PROCEDURE DIVISION.
          SAY-BEE.
            DISPLAY "Bee".

Compile:

    gcobol -c -fPIC A.cbl B.cbl
    gcobol -o libB.so  -shared B.o

Output:

    $ file *
    A.cbl:   ASCII text
    A.o:     ELF 64-bit LSB relocatable, [...]
    B.cbl:   ASCII text
    B.o:     ELF 64-bit LSB relocatable, [...]
    libB.so: ELF 64-bit LSB shared object, [...]

## Statically linked example

    $ gcobol  -o A A.cbl B.cbl && ./A
	Ahh

A **main**() function is generated for `A.cbl` by default because it
is the first program on the command line. Because `A` doesn't call
`B`, we have only one line of output.

Let's change `A` to call `B`:

        ID DIVISION.
          PROGRAM-ID A.

        PROCEDURE DIVISION.
          SAY-AHH.
            DISPLAY "Ahh".
            CALL "B".

	$ gcobol  -o A A.cbl B.cbl && ./A
	Ahh
	Bee

We know the programs are statically linked, because both symbols are
supplied by the program itself:

    $ nm A | grep -w T
    0000000000401e00 T _start
    0000000000401f74 T a
    0000000000403454 T b
    0000000000401f04 T main

## Dynamically linked example

	$ gcobol-bin  -o A A.cbl -L. -lB -Wl,-rpath=$PWD && ./A
	Ahh
	Bee

  * The compiler produces `A.o` from `A.cbl`, leaving open how `CALL
    "B"` will be resolved.
  * The static linker finds `libB.so` in the current working directory.
    It finds the `b` symbol in it, thus satisfying the needs of `A.o`.
    It adds the current working directory to the *RUNPATH* of `A`, per
    the invocation.

We know `A` does not supply `b`:

	$ nm A | grep -w T
	0000000000401e40 T _start
	0000000000401fb4 T a
	0000000000401f44 T main

We know `A` is dynamically linked to B:

    $ readelf -d A

    Dynamic section at offset 0x3d98 contains 30 entries:
      Tag        Type                         Name/Value
     0x0000000000000001 (NEEDED)             Shared library: [libB.so]
     0x0000000000000001 (NEEDED)             Shared library: [libgcobol.so.4]
     0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
     0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
     0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
     0x000000000000001d (RUNPATH)            Library runpath: [/home/[...]]
     0x000000000000000c (INIT)               0x401c88
     0x000000000000000d (FINI)               0x403494

and we see the *RUNPATH* entry showing the directories that the
runtime linker will peruse in search of `libB.so`.

# Literally Booleans of Choices
## Wed Feb 15 18:39:24 2023

gcobol is deferring the implementation of Booleans pending better
information.

Boolean literals and data elements appear to have received different
treatment in every specification we find.  They do not appear in the
NIST CCVS-85 Nucleus module.

  * IBM limits Boolean literals and data elements to 1 Boolean value,
    represented by `B'0'` or `B'1'`. No Boolean operations are named
    apart from the logical `AND`, `OR`, and `NOT`.
  * ISO 2014 classifies Boolean as a separate class and category,
    effectively as bit-strings. Boolean values support up to 1000
    "digits". It defines `B-OR`, `B-AND`, and `B-XOR` operations. For
    this class and category, however, `MOVE` and `DISPLAY` semantics
    are unspecified.
  * GnuCOBOL defines Boolean literals as a Numeric literal. No upper
    limit is mentioned, although one might infer that, like
    hexadecimal numeric literals, they're limited to 64 bits.

As of now, we lack a good test case, which is to say any test case.
The NIST tests are silent, and the GnuCOBOL tests are inconsistent
with ISO, which is our benchmark.

# HOWTO Declaratives
## Wed Feb 22 10:51:44 2023

At a glance, DECLARATIVES look like try/catch in C++.  But they're not
because, among other things, there's no stack. Declaratives are
actually default stand-in paragraphs for the ON ERROR (etc.) clauses
of conditional statements.  And *paragraphs* is the key concept. When
an exception is raised, and not handled by the statement that raised
it, we can PERFORM DECLARATIVES, and let each USE statement determine
whether or not it handles the raised exception.

The decision over whether or not a raised condition meets the criteria
described by a USE statement involves no Cobol data.  In fact,
everything is expressed as an integer: the raised exception, the
declarative's criteria: the handled exception, and file mode or list
of files (which are denoted in the compiler by their index into the
symbol table). The criteria-matching code thus is easily expressed in C.

The plan is to *generate* that "C" function as part of any Cobol
module that includes a DECLARATIVES section, and make it a static
(private per-module) function that is called by each declarative to
determine if it covers the raised exception. That function returns a
Boolean result (as a Cobol FldConditional) which the declarative uses
to branch into or over its code.

As each individual statement is parsed, the parser recognizes whether
or not it includes conditional exception handling. If not, or if the
raised exception is not the handled one, the parser uses
parser_perform to emit code to PERFORM the DECLARATIVES section. When
(if) that PERFORM returns, control proceeds to the next statement.

# Macro processor: note to future self
## Thu Mar 30 15:32:27 2023

    >>MACRO [qualifiers...] name ( parameter, ...  )
    cobol-text ${name1} cobol-text ${name2}...
    >>END-MACRO

The scope of the macro is limited to the division or section it
appears in; "global" macros appear before the IDENTIFIER DIVISION.

Use ${...} as parameter names to make them visually obvious, and to
allow the user to use the same name for the parameter as for some
associated normal Cobol identifier.

The CDF constructs a macro dictionary and installs the names in the
symbol table.  As the macros are encountered in the program, they
appear in the form

	name param1 ...

with no parentheses and no optional parameters, so that the parser
knows which tokens are macro parameters. Parameters are parsed per
usual before the macro is expanded; this rule allows constant
arithmetic expressions to be passed as a single parameter.

Unqualified, such a macro could stand for any identifier.  Qualifiers
would identify the macro as a type of statement, or paragraph, or data
item, etc.

### Macro Engineering
#### Parsing the macro

The lexer recognized >>MACRO, and enters the `macro_state` start condition. Until it sees `')'`, which indicates the end of the parameter list, it returns NAME tokens. After returning `')'`, it enters `macro_body_state`, which ends with `>>END-MACRO`.

In `macro_body_state`, the lexer returns only two kinds of tokens:

 - NAME of a macro parameter reference, and
 - STRING of Cobol text (irrespective of quotes)

The CDF can parse the macro with no particular difficulty. In the
symbol table, we have `SymMacro` whose definition is:

    struct macro_body_t {
        name_t name;
        enum {...} type;  // where the macro may appear, syntactically
        size_t npart;
        struct macro_body_part_t {
            name_t parameter_name;
            char *cobol_text;
        } *parts;
    };

`parameter_name` may be empty, meaning no parameter precedes the Cobol
text.  The `cobol_text` may be NULL, indicating no text follows the parameter.

Macros are limited to 15 parameters, although parameters may
themselves be macro references, recursively.  Macro names may not
appear in the macro body because cobol_text is not parsed.

Like other symbols, macro names may not be unique.  Two *macros*
cannot have the same name; that's an error.  But a macro may have the
same name as a symbol.  If it does, though, and has the same *type* as
the symbol, then it is removed (with a diagnostic) because the symbol
supersedes a macro of the same name.

#### Expanding the macro

When the *lexer* is about to return a name, it checks the macro
dictionary (the symbol table) for an eligible macro.  If found, it
returns a `MACRO_n` token, where 0 <= n < 16.

When the lexer encounters a `MACRO` token, expansion commences:

 - Open a pipe to hold the macro expansion
 - `fork`,
   - child
     - parsing continues in `parse.y`
     - write the expanded macro to the pipe, substituting parameters
     - when the parser sees `>>END-MACRO`, it calls `_exit(0)`.
   - parent
     - calls itself until it encounters `>>END-MACRO`
     - `yypush_buffer_state(pipe)`
     - returns first token from expanded macro (first token in the macro body)
     - at `<<EOF>>`, pop buffer state
     - continue per usual unless the child exited abnormally

yacc grammar for parsing a macro:

    macro: macro_args macro_body
        ;
    macro_args:
        ...
        |    MACRO_3 marg marg marg
        ...
        ;
    marg:    cce_expr // constant expression
        |    STRING
        |    NAME
        ;
    macro_body: macro_part
        |       macro_body macro_part
        ;
    macro_part:
             NAME STRING
        |    NAME
        |         STRING
        ;

# Link early and often
## Mon May 15 16:44:04 2023

Never do yourself what the computer can do for you. Let's exploit the
linker to avoid errors and improve performance.

To be clear on terminology, we have 3 kinds of linking:

 - static linking, where the symbol definition is supplied when the executable is produced.
 - runtime linking, where the symbol is rendered as undefined in the
   executable, and resolved by the runtime linker, ld.so(8).
 - dynamic linking, where the program uses dlopen(3) to resolve the
   symbol under program control.

### Dynamic linking

As of today, every CALL is resolved by dynamic linking. In *general*,
that's how Cobol works, because it uses "call by name". For

    CALL NAME

`NAME` is an alphanumeric variable whose value is determined at
runtime. (For example, the value could come from a file, or from the
environment.) Because the symbol isn't known until time, it can't be
resolved until runtime.

### Static and Runtime linking

Sometimes the name is known at compile time.  For

    CALL "name"

or

    CALL NAME *> where NAME is an 01 or 77 CONSTANT

the compiler knows the name.  It can simply reference the name
("invoke the function").  The object code will include that name as
undefined, and the linker does the rest. Whether the static linker
resolves the symbol, or the runtime linker does, is determined by the
libraries supplied at link time.

Static and runtime linking have three advantages.

 1. They are faster, running in about 10% of the time.
 2. If the symbol is not supplied, the linker will produce an
    error. Better to discover the error at build time than at run
    time.
 3. The executable can be built with information about what libraries
    are needed, and where they are to be found.

### What's in a name?

In Cobol, the `"name"` in

    CALL "name"

may be one of three things:

 1. the name of a `COMMON` program
 2. the name of a contained program
 3. an external COBOL program name
 4. an external name, not COBOL

The first two cases we call "local" names, because they're supplied by
the file we're compiling. A local name, by the rules of Cobol, is
case-insensitive. Furthermore, a given source file might have more
than one program with the same name. A `CALL` to a name with more than
one definition is an error.

If there is exactly one local name (no matter the case) in scope at
point of call, the compiler can produce the `CALL`. Because the target
must be a contained program, and contained programs have internal
linkage, it's up to the assembler to match the reference with its
definition.

To enforce unique, case-insensitive names, we can make sure all
local names (when defined and when referenced) are lower-case.

If no local name is defined, then `"name"` must reference an external
program or function.  The name might be case-sensitive: if it refers
to a COBOL program, the COBOL standard requires a case-insensitive
match.  On the other hand, if `"name"` refers to C function, only a
case-sensitive match is correct.  Because we want to the linker to do
the work, and because it uses case-sensitive matching, the supplied
symbol must match the called target exactly.

When a COBOL program is compiled by gcobol, its public symbol is
produced in lowercase form. When a COBOL program calls a COBOL program
(using a literal) the unresolved external symbol, i.e. the CALL
target, is likewise produced in lowercase form. The linker can resolve
the name because caller and called use the same lowercase convention.

When `"name"` refers to a non-COBOL function, the programmer has two
choices.

 1. If the name of the called function is defined in all lowercase
    then no special step need be taken. gcobol will render the calling
    symbol in lowercase (regardless of how it appears in the program)
    and the linker will match correctly.
 2. If the name of the called function is not defined in all
    lowercase, the programmer must do two things:
   - Use `>>CALL-CONVENTION VERBATIM`
   - Ensure `"name"` matches the called symbol exactly.  In this case,
    gcobol does not alter `"name"` in any way. It produces a symbol by
    that exact name for the linker to resolve.

### CALL linkage recap

    CALL NAME

Unless `NAME` is `CONSTANT`, this results in dynamic linking. The
value of `NAME` does not appear as a symbol in the executable because
it's not defined to the compiler.

    CALL NAME, CALL "name"

If the `CALL` target is a level 01 or 77 `CONSTANT` or an alphanumeric
literal, it does appear as a symbol in the executable because it is
defined to the compiler. If the target is locally defined (a contained
program), it is defined with internal linkage, converted to
lowercase. If the target is an externally defined, the symbol produced
in the executable is a lowercase version of that supplied by the Cobol
text unless `>>CALL-CONVENTION VERBATIM` is used.

# Efficient exceptions
## Mon Aug 28 15:38:34 2023

On August 8 5:25 PM, we agreed the declarative-matching code would not
engage unless

	1.  an exception is raised, and
	2.  the exception is not handled by a conditional clause in the
        statement (e.g. ON SIZE ERROR), and
	3.  the exception raised is enabled.

Conditional clauses execute regardless of TURN directives.  We need to
check if declaratives for I/O match regardless of TURN directives,
too.  If so, the default mask is not ec_none_e, but ec_io_e.


# Floating Point Precision
## Tue September  5 10:16:23 2023

ISO COBOL demands 34 digits of precision for floating point
computation. IEEE 754 double precision floating point (64 bits)
provides only about 13. More digits means more bits: we need 128-bit
floating point support.

This is the story of how we arrived at `_Float128`.

At first, we thought we'd need a specialized math library.  GCC
helpfully includes **libquadmath** and, after a few stabs in the dark,
that seemed to be a good candidate. But, as it turns out, GCC
anticipated our needs: it now supports the ISO C `_Float128` type
directly.

One helpful discussion of the topic can be found at

    https://cpufun.substack.com/p/portable-support-for-128b-floats

wherein we discover that in the Intel world, these definitions generally hold:

    - float       32 bits
    - double      64 bits
    - long double 80 bits

because Intel processors had an 80-bit floating point type that is
sometimes exposed in C as a `long double` type.

For us on the GCC COBOL project, the ARM architecture is also
interesting, because Apple makes the best laptops, and we like the
best laptops.  (Some of us, anyway.) Because ARM never had an 80-bit
floating point type, `long double` is defined as perhaps one might
expect:

    - float        32 bits
    - double       64 bits
    - long double 128 bits

There's nothing new here, in the sense that C makes few guarantees
about machine representation of native types.  How many bits is your
`int`?

ISO/IEC TS 18661-3 defines `_Float128` as a 128-bit floating point
format.  GCC defines it for both architectures.  So far, so good.

The GNU C standard library defines math functions (e.g. **acos**(3))
for _Float128. That's crucial support, and works on both
architectures. Yay!

The I/O story is a little disappointing, but not too bad.

Recall that **printf**(3) and **scanf**(3) support `long double`. For
ARM, that's job done: nothing special needed.

ISO C defines **strfromf28**(3) and **strtof128**(3) to
convert from `char *` to `_Float128`. The GNU C standard library
provides those functions, but only on platforms that 1) support
`_Float128`, and 2) do not define it as `long double`.  In other
words, it's implemented only if **printf**(3) won't do the
trick. Which, as we know, is the case on Intel.

What is our most portable answer?

With a few hours work, we might be able to extend `printf` using the
GNU **register_printf_function**(3), such that on x64 machines,
`"%Lf"` means `_Float128`, not `long double`. But that works only with
the GNU C standard library, and solves only one side of the equation:
output. There's no similar functionality for **scanf**(3).

In the context of COBOL, the need for C formatted I/O is quite
narrow. We need to interpret string constants in the parser, and
support conversion for things like `DISPLAY`, `ACCEPT`, `READ`, and
`WRITE`. For our purposes, the portable answer is to provide the
missing ISO C functions on ARM.

# Once more unto COPY
## Mon Sep 18 20:47:14 2023

All programming is iteration, and none more so than understanding and
writing the CDF. The first version of COPY support is now almost 2
years old, and we're not done.

Initially, we had an "ordinary" compiler, all lex & yacc. Continuation
lines and the like were handled in the lexer, where we had nice regex
support. The CDF made that model unworkable because CDF
text-manipulation changes the lexer's input.

Gradually, more and more of Cobol's source-format rules were handled
before the lexer: not just continuation and debug lines, but COPY and
SOURCE-FORMAT.  And, Real Soon Now, REPLACE.

Problem is, the current state of affairs is internally
inconsistent. The lexer's file-reading function maps the input, deals
with formatting issues, and copies chunks of good Cobol text to the
lexer's input buffer. This is very efficient insofar as the input text
is never altered; the reader just skips over any non-Cobol text, and
copies the good bits to the lexer's input.  But it's very closely tied
to the idea of filling that buffer.

The COPY reader, on the other hand, reads the file into a buffer,
modifies it in place, and writes the modified buffer to a pipe.  That
pipe is then read by the lexer's file-reading function, where its
effort to deal with input-format issues is at best redundant, and
sometimes creates problems because the modified input no longer
conforms. For example, COPY ... REPLACING could create extra-long
lines. It's also incomplete as of now; it lacks some of the
functionality in the lexer's regular file-reader.

The COBOL ISO 2023 standard describes a way out in Section 6.5,
Logical Conversion. So that's what we're going to do.

  1. "Source text and library text in fixed-form reference format
      logically converted to *Free-Form Reference Format* before the
      application of replacing and conditional compilation
      actions. Continued and continuation lines in fixed format and in
      free format are concatenated to remove continuation indicators,
      and comments and blank lines are removed from both
      formats. There is no restriction on the maximum line length of
      the free-format text resulting from logical conversion."
     The result is said to be a *Logically-converted Compilation Group*.
  2. CDF text-manipulation `COPY` and `REPLACE` operations read
     *Free-Form Reference Format* and produce a *Structured
     Compilation Group*. This is what is fed to the lexer.

The solution is Just Work: combine and simplify.

  1. For any file, map it so that the buffer can be modified, but not
     written back to the file. No further allocation is needed.
  2. Transform the mapped buffer to Free-Form Reference Format using
     **memmove**(3) and **memset**(3). Because the process only
     eliminates comments and shortens continued lines, the result is
     the same size, but with more blanks. This is one function that
     operates on any buffer.
  3. For a CDF input, continue with `COPY` and `REPLACE`. Then write
     the result to a pipe.
  4. For lexer input, fill the lexer's buffer of course.

The lexer input function, unceremoniously called `lexer_input`, is
vastly simplified. If its input is a file, it maps it, immediately
converts it to Free-Form Reference Format, and proceeds to feed it to
the lexer. If the input is a pipe, that means it came from the CDF,
and needs no conversion. So, write it to file (as now) skip
conversion, and feed that mapped file to the lexer.

# The Joy of Exception Conditions
## Tue Sep 26 18:42:31 2023

We were doing it wrong.

A Cobol program cannot, under program control, enable and disable
exception conditions. That is, `>>TURN` is a CDF directive: an
instruction to the compiler on what code to generate. The set of
enabled ECs is updated as the code is compiled, from `>>TURN` to
`>>TURN`. It is **not** updated during execution: If you `PERFORM` a
procedure that includes a `>>TURN` that enables some EC, nothing will
have changed (about enabled ECs) when the procedure returns.

In fact, `>>TURN` is not even in the Cobol when it's being compiled.
The CDF parses the `>>TURN` directive, updates its list of enabled
ECs, and removes the line from the input before the parser sees it.

At least, that's how it should be.  We were keeping the list of
enabled ECs in the runtime library. We're now changing that to keep
the list in the compiler. And, when at a raised EC is being evaluated,
each time a call to the runtime function is produced, the call
includes the compiler's current set of enabled ECs. If you heard the
apple cart groaning, that's why.

On the parser side, we maintain a `std::set` of tuples

    {enabled, location, ec, file}

The type of the set is known as `cbl_enabled_exceptions_t`, and the
compile-time variable is `enabled_exceptions`. The class includes
methods to add/remove ECs, and to match a (potentially) raised EC, and
perhaps file against that set. The matching function can be used
during code generation to decide if **any** matching logic need be
emitted: if all ECs are disabled, no raised EC can invoke any
declarative, or even the default handler.

Before each statement, a runtime function is called to check for a
raised EC.  If one was raised, it verifies that it's enabled for the
current file (if applicable).  If it is, it matches the EC against the
list of declaratives.  If one matched, it returns that declarative's
identifier, which the generated code uses to `PERFORM` the
declarative. If it's enabled and matches no declarative, the runtime
function invokes the default handler, which may exit.  If it does not,
the function returns 0 to the program, meaning no match.

But how, you surely ask, does the compile-time table find its way to
the runtime function?  Why, as a parameter, of course.

Each time the function is called, the code generator first transforms
our fancy `std::set` into POD, plain old data: an array of
structures. It turns that array into runtime data, putting hundreds of
bytes on the stack.

That might not be the most efficient arrangement. We might want to
keep the runtime table cached, and update it only when the
compile-time table changes.  Perhaps. But first, we have to make it
work.

# REPLACE Replaces COPY
## Tue Oct 10 10:06:18 2023

The work of the CDF Text Manipulation "elements" (as they're known in
the ISO spec) is less about parsing than about, well, text
manipulation. It's a bit like a simple form of **sed**(1), specialized
for COBOL, and without regular expressions.

Having implemented `REPLACE`, it's now time to redo `COPY` one last time.
The NIST SM module, which tests these operations, includes this gem:

    REPLACE =="FAIL"== BY =="PASS"==.
        COPY    KK208A.
    REPLACE OFF.

That `REPLACE` affects the included file. Each file cannot be
processed in isolation.

The reader will recall that `COPY` has a REPLACING form that is nearly
identical to `REPLACE`.  (In fact, it is identical in the 2023
specification, but old code uses older, now obsolete forms.

One way to do this -- and it's been done, by others -- is to implement
the CDF as a true preprocessor with its own lex/yacc.  In theory that
should be faster, because the CDF can run in parallel with the
compiler, which can start parsing as soon as the CDF produces its
first line. And anyone writing a compiler knows those tools well.

The thing is, though, that because the CDF is tied to Free-Form
Reference Format, some of the work is governed by how the input file
is formatted (and what formatting directives it includes).
Furthermore, because the output of the CDF is still still in Free-Form
Reference Format, we want to retain the whitespace and line endings
that tokenization and parsing would ignore. And the grammar is pretty simple.

On the evidence, lex/yacc isn't much help, either. The gcobol
`REPLACE` implementation is built into the file-reader, and uses only
regular expressions.  It's probably as many lines of C++ as the `COPY`
implementation, excluding the lex/yacc support for `COPY`. And the
`COPY` implementation includes some heavy cart-before-horse machinery
to invoke the parser ahead of the lexer.

The new design is sequential and recursive. At the bottom, we imagine
a simple file reader that applies any active REPLACE directive:

    File Read( in, out ):
            for each line:
                if active REPLACE
                    write prefix
                    write substitute
                else
                    write line

It would be nice if `COPY` could operate in isolation, but that's not
COBOL.  `COPY` output is filtered through any active `REPLACE`
directives that are in force when `COPY` is encountered. Technically,
there's a global stack of active `REPLACE` directives.  That's a
little more complex:

    File Read( input, output ):
        for each line:
            if COPY
                parse COPY, remove
                push copy-replacing onto active REPLACE stack
                copy-in = File Open( copybook-name )
                copy-out = File Prepare( copy-in )
                File Read( copy-in, copy-out )
                pop active REPLACE stack
                File Read( copy-out, output )
            if REPLACE
                parse REPLACE, remove
                update/push/pop active REPLACE stack
            if active REPLACE
                write prefix
                write substitute
            else
                write line

What does File Open look like?

    File Open( filename ):
        input = open filename
        return input

What does File Prepare look like?

    File Prepare( input ):
        mmap input
        Free-Form Reference Format
        open output
        return output

Finally, we need a lexer function to set `yyin` (a C `FILE*`):

    FILE* lex_open( filename ):
        input = File Open( filename )
        output = File Prepare( input )
        File Read( input, output )
        return fdopen( output )

This function is called only once, using the filename supplied on the
command line. The returned output is not the input file, but the
output of the top-level File Prepare.

That gives a call stack:

    lex_open( filename )
        File Open( filename )
        File Prepare( fd )
        File Read( input, output )
            File Open( copybook )
            File Prepare( copy-in )
            File Read( copy-in, copy-out )
            File Read( copy-out, output )

The 2nd File Read takes care of the situation we began with:

    REPLACE =="FAIL"== BY =="PASS"==.
        COPY    KK208A.
    REPLACE OFF.

If `KK208A` has only this:

    REPLACE ==ABC== BY =="FAIL"==
    DISPLAY ABC
    REPLACE LAST OFF

its output (from File Open) is

    DISPLAY "FAIL"

which the encompassing program's `REPLACE` renders as

    DISPLAY "PASS"

Nice properties of this design:

  - One flex input, no push/pop of flex state
  - One process, no fork
  - Intermediate files (normally anonymous) can be inspected

# Preserving line numbers in continuous input
## Wed Nov  1 13:00:55 2023

The input to the lexer consists of one stream of interpolated files:

    main file
    ...
    copybook
    ...
    main file (resume)

We insert markers in the input stream to notify the lexer that a new
file has begun, or an old one resumed.  In C, that's done with the
`#FILE` directive, which we can appropriate, sort of:

    #FILE PUSH main_file
    main_file
    ...
    #FILE PUSH copybook
    copybook
    ...
    #FILE POP
    main file (resume)

The lexer maintains the current filename and line number on the top of
an input stack. Before pushing a name, it records yylineno in the
top-of-stack element.  On popping, it sets yylineno to the saved
value.

# Abbreviated Complex Relation Conditions
## Tue May 28 13:34:21 2024

ACRCs present a parsing challenge, both standard and nonstandard. 

In COBOL we can say

    IF A < B OR C AND D THEN
    
meaning

    IF A < B OR A < C AND A < D THEN

meaning

    IF A < B OR (A < C AND A < D) THEN
    
Although ISO says parenthesis are not allowed in ACRCs

  "and no parentheses are used within such a consecutive sequence"
  
many compilers appear to accept them anyway. 

The standard problem arises as the parser proceeds along the input.
It reduces

    A < B
    
to a Boolean, let's call it `bool_1`.  It stashes `A <` into an
antecedent structure for future reference.  It then shifts `OR` and
`C` onto the stack.

At this point, it would seem `OR` can be reduced.  We have

    bool_1 OR C

and `bool_1` captured the omitted antecedents `A` and `<`, So it would
seem we can evaluate

    A < C
    
to `bool_2` and reduce, in effect

    bool_1 = (bool_1 OR bool_2)
    
But we cannot.  The upcoming `AND` upsets the apple cart.  We cannot
reduce `OR` before `AND`. 

That's OK. Operator precedence in the parser says `AND` is resolved
before `OR`.  Instead of triggering a reduction, the appearance of
`AND` causes more tokens to be shifted onto the stack:

    bool_1 OR C AND D

Upon striking `THEN` (or other syntax that is not part of a relation
condition), we can reduce the `AND`, then `OR`, and finally the whole
thing.

The trick is in the antecedent. Each abbreviated relation must copy
its antecedent from the left-hand side.  Problem is to find a *parser
action* that can do that. `OR C` has not been reduced when `AND D` is
reduced; there was no opportunity to copy the antecedent to the `C`
token. 

In the parser, we distinguish *relation conditions* -- those
containing a relation operator -- from others as a distinct
nonterminal. A Boolean function or Level 88 need not apply.
Abbreviated relation conditions can appear to the right of a complete
relation condition, only.  Logically:

    acrc: rel_term
        | acrc AND abbr_term
        | acrc OR  abbr_term
        ;
        
where `rel_term` has all three components (LHS, operator, RHS), and
`abbr_term` has an RHS value and possibly an operator, but no LHS.
        
# Abbreviated Complex Relation Conditions: Solution
## Wed Jun  5 11:25:33 2024

The AND/OR grammar in the gcobol parser is now much simpler and, in at
least one case, recognizes correctly a construct it used to
reject. But from this author's perspective, there are aspects of it
that work mysteriously, and some workarounds were required.

Like all declarative languages, LALR grammars are both completely
deterministic and very difficult to debug. I suspect nearly all Bison
users sooner or later arrive at a solution that works still wondering
why others don't.

The basic answer to devising a grammar to parse COBOL conditional
expressions followed several principles that are more or less obvious
in retrospect:

 - Distinguish arithmetic expressions from strings. 
 - Distinguish relation expressions from *simple conditions*,
   i.e. tests of class, condition variables (Level 88), and
   switches. These don't compare two values, and thus can't have
   abbreviated components.
 - Treat all operands to `AND` and `OR` uniformly. 
 - Use operator precedence to prioritize `OR`.
 - When precedence fails, defer `OR` evaluation. 
 
Arithmetic expressions can be compared to alphanumeric values in
COBOL, but only numeric values participate in arithmetic
expressions. The abbreviated part of an Abbreviated Complex Relation
Expression can follow only a *relation condition*, one that compares
two things (for equality or inequality).

The parser must distinguish between these two: 
 
     A = B OR C < D
     A = B OR C
     
When it gets to C, how does it decide to reduce the (implied) `A = C`,
or not?  By examining the *lookahead token*.  Remember that `C` could
be any arbitrary expression. The possibilities are limited, though:
once `C` is reduced, it will be followed *either* by a relational
operator (say `=`) *or* a logical operator (`AND` or `OR`), or something
else, signaling the end of the expression.  That's how it decides.
 
The parser must prioritize `AND` over `OR`. These are the same: 
 
     A = B OR C AND D
     A = B OR A = C AND A = D

The difficulty is that `A = B OR A = C` should not be reduced because
it's followed by `AND`, meaning that, as far as `OR` is concerned, the
right-hand side `A = C` is not complete. As far as I'm concerned, the
grammar is very clear on the point: `AND ` has higher precedence, and
each reduction rule is explicitly marked with AND/OR precedence.
Nevertheless, Bison forces a reduction of the `OR`.  Explanations
welcome. (Speculation we already have aplenty.)

The working answer treats every `OR` RHS as "maybe AND".  Whenever
`OR` is first encountered, the operands are merely recorded, and the
OR operation deferred. Successive `AND`s, if any, are applied to the
unresolved RHS. Each successive `OR` produces an evaluation of the
outstanding operands, and slots in a new, deferred RHS. Only when we
reach the end of the whole conditional expression is the last `OR`, if
any, evaluated.

### And NOT

`NOT` is interesting in COBOL, Like SQL, a COBOL `NOT` has higher
precedence than `AND` and `OR`.  These two are equivalent:

    NOT A = B
    A NOT = B

Most languages disallow the former; `NOT A` would be invalid unless
it's a truth value.  The **gcobol** parser captures the leading `NOT` as
an attribute of the operand, and uses it to invert the sense of the
relational operator.

### Rumination

Logical inferences are hard to debug in general. Koenig lookup in C++,
for example, follows a public algorithm to determine which overloaded
function is used, and yet can requires painstaking, step-by-step
analysis to explain.  (STL errors are hard enough; "mistaken"
successes produce no diagnostic.)  SQL queries that produce the
"wrong" result likewise require the user to reason externally; they
can't be debugged by stepping through the query's execution.

The Bison user faces the same kind of challenge. When the grammar is
not LALR, Bison says what is wrong, but not why it is wrong.  It
reports the conflicting states.  It will produce a counterexample
illustrating how those two states might be arrived at while parsing
the same input. But nothing reverse-engineers the grammar to point out
the thing -- or at least *a* thing -- that engendered the conflict to
start with. 

The user is forced to do something the computer could do much faster:
try permutations of the grammar, guessing at where the ambiguity could
be introduced.  An "unbison" tool could highlight parts of the grammar
that, if removed, would result in a consistent LALR grammar. Better, a
deterministic tool could trace backwards from the conflicting states,
exposing the sets that were used to produce them, and find the
redundant components (if that's what they are)

This is where, in 2024, someone will say "AI".  Indeed, perhaps an AI
tool could, on the million-monkeys model, try multitudinous variations
for the user to consider. But IMO the problem was arrived at
deterministically, and could be solved the same way.

# Thu Jan  2 11:02:54 2025
## Locations

  "[Lex] does nothing you want done."
  -- Ken Thompson, "Coders At Work", page 476. 
  
The Flex manual spends quite a few words describing `%bison-locations`
without mentioning that the generated scanner does *nothing* to track
location.  It obviously *could*; the user-defined rules don't change
what the scanner matched. But it doesn't.

What "Bison support" Flex offers is a red herring.  The description is
misleading and inaccurate, and unnecessary for the stated purpose.
Proof: we don't use it.

Problems with the Flex manual start (in this regard) with `YY_DECL`,
which doesn't appear in the index. It's described in Section 9, "The
Generated Scanner".  As happens often in this manual, the central
description is diluted by an aside, in this case about how to define
`YY_DECL` using pre-ANSI syntax, and paragraph about bootstrapping old systems. 

`YY_DECL`, for the record, is how the Flex user defines the name of
the generated scanner.  If that scanner takes parameters (something
affected by Flex options) then `YY_DECL` must be updated to match.

Appendix A.2 describes the effect of the `%bison-bridge` and
`%bison-locations` options, which *sound* promising.  It says, 

  If '%option bison-locations' is specified, then the declaration becomes,

    int yylex ( YYSTYPE * lvalp, YYLTYPE * llocp, yyscan_t scanner );

which is just *not true*. A `yyscan_t` parameter will be present only
if the scanner is reentrant. 

These options are misnamed. Bison doesn't need the generated scanner
to do anything special. It doesn't need the `YYSTYPE` and `YYLTYPE` to
be parameters. By parameterizing them, the generated scanner avoids
writing to global variables, which *might* be helpful, if that's what
the parser wants.  But that depends on the parser, not Bison.

## What actually happens with the semantic types and locations

The generated scanner matches patterns and executes the user-provided
action, if any, for each one.  Flex of itself never writes to `yylval`
or `yylloc`. One of the ugly parts of lex/yacc programming is that it
is incumbent on the user to assign the value of `yylval` consistent
with its defined `%type` in the parser.

Similarly, it is up to the user to keep track of the location. Flex
provides a modicum of help with `%option yylineno`, but there is no
support for columns.

In our system, the generated scanner function takes no parameters, and
the generated parser defines two global variables,

    YYSTYPE yylval;
    YYLTYPE yylloc;
    
After each call to `yylex()`, the parser examines the returned value
to determine what token was matched.  It relies on the scanner to have
updated those two variables with the semantic value and location of
the token.

The value of `yylval` depends on the matched rule, of course.  The
value of `yylloc` does not; it is updated via the `YY_USER_ACTION`
macro, which calls our `update_location()` function.

After each call to the lexer, and before execution of any action
associated with the current rule, the parser invokes the code defined
by the macro `YYLLOC_DEFAULT`. This allows it to update the location
each component of the rule, including nonterminals.  For example,

    picture_sym:    PICTURE SYMBOL LITERAL

the parser calls `yylex` 3 times, getting the tokens `PICTURE`
`SYMBOL`, and `LITERAL`. For each one, the scanner set the location,
and the parser captures the value of `yylloc` to associate it with the
right-hand side of the rule, so that `@1`, `@2` and `@3` have correct
locations.  And it extends the putative location of `picture_sym`
(which is not a token and doesn't appear in the COBOL text). Before
any action associated with this rule is executed, `picture_sym` has
its "location" (accessed via `@$`) set to be the first line & column
of `PICTURE` through the last line and column of `LITERAL`.

## Why location matters

Location -- in particular, the column -- matters because it's used by
the gcc diagnostic framework. The internal gcc function `warning_at`
takes a location that allows it to produce a message such as

    check_88.cbl:13:37: warning: 'X"000102"' has embedded NUL
       13 |            88  CheckBinary VALUE X"000102".
          |                                     ^

Without a column, the message could not position the caret correctly. 

As it happens, gcobol does not produce exactly that message. But we're
getting there; now the caret is usually helpful.
