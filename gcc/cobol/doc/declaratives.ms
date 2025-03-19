.TL
How Declaratives Work
.SH
Declaratives Section
.PP
Declaratives have compile-time and run-time components.  At compile
time, each DECLARATIVES section is parsed just like any other section.
Each USE STATEMENT serves to produce a descriptor of type
cbl_declarative_t that indicates which exceptions it covers, and for
which files (if any).
.PP
At END DECLARATIVES, two things happen.
.RS
.IP 1.
The declarative descriptors are installed as a "blob" in the symbol
table. Because the members of cbl_declarative_t are all either
enumerated types or symbol-table indexes, they can be treated as an
array of integers.
.IP 2.
A "secret section", _DECLARATIVES_EVAL is
produced. It is performed after every statement.
.RE
.PP
The generated code in the _DECLARATIVES_EVAL section calls the runtime
function __gg__match_exception, which returns an integer, representing
the entry in the symbol table of the declarative that handles the
raised exception.  The generated code compares the returned integer to
the simple index for each DECLARATIVE section.  If equal, it performs
that section.
.
.SH
Declaratives Activation
.PP
As each statement
.I foo
is parsed, the parser calls parser_\c
.I foo .
The generated code sets FILE-STATUS for I/O functions, else ec_status.type.
The parser then generates code to perform  _DECLARATIVES_EVAL.
.
.SH
Prepare Declaratives
.
.PS
boxwid = 2.0
lineht = 1/4
Declaratives: box "DECLARATIVES" "insert _DECLARATIVE_EVAL"
arrow down from Declaratives.s
Declarative: box "a declarative (SECTION)"
arrow down
box "USE"
arrow down
box "add 1 cbl_declarative_t"
arrow down 5/8
Statements: box "statements"
arc -> ccw from last box.ne to last box .n
line right from last box .e
line to (Here.x, Declarative.e.y) "\ next declarative" ljust
arrow left
arrow down from Statements.s
box "END DECLARATIVES"
arrow down
box "generate blob"
arrow down
box "generate call to" "__gg_match_exception"
arrow down 5/8 "first declarative\ " rjust
circle rad .75 "raised exception" "matches" "USE statement"
arrow down "\ Yes" ljust
box ht 3/4 "PERFORM declarative" "whose index was returned by" "__gg_match_exception"
arrow dashed right  1.0 "continue" above from last box .e
arrow right from last circle.e "No" above
box "next declarative"
arc -> from last box .n to last circle .ne
.PE
.SH
Invoke Declarative
.PS
Statement: box "statement"
arrow down from Statement.s
box "parser_\f[I]foo\f[]"
arrow down
box "PERFORM" "_DECLARATIVE_EVAL"
.PE
