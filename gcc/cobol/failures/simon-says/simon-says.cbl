      *>From: simonsobisch@gnu.org
      *>Re: gcobol testing and reported bad results
      *>To: "James K. Lowden" <jklowden@symas.com>
      *>Date: Mon, 13 Mar 2023 02:11:59 -0500 (CDT)
      *>
      *>Let me give a list of the things we definitely need that I
      *>have in mind, allowing you to send "checkmarks" and links to
      *>issue tracker items for the missing parts back :-)
      *>
      *>* USAGE COMP-3 / PACKED DECIMAL up to 31/38 digits
      *>
      *>* USAGE COMP-1 + COMP-2 as floating types
      *>
      *>* USAGE INDEX and INDEXED BY (the internal representation doesn't
      *> matter, can be a machine "int" or other) along with SET INDEX TO /
      *> SET INDEX UP/DOWN BY
      *>
      *>* USAGE COMP-5 + COMP-X with matching binary storage to be passed /
      *> received from CALL c-function
      *>
      *>* support for CALLing into C functions, both static (directly
      *>linked in) and dynamic (resolved at runtime)
      *>
      *>* ideally: support for static CALLs (with CALL-CONVENTION and/or
      *>  with GnuCOBOL's extension CALL STATIC)
      *>
      *>* ideally: support for runtime checks:
      *> * divide by zero
      *> * SIZE OVERFLOW
      *> * index / reference modification out of bounds
      *>--> the first two need to be checked with ON SIZE ERROR, if
      *>that isn't given there should be a way to enable a check for
      *>that (resulting in an abort)
      *>
      *>* level 78 constants
      *>
      *>* ideally: OCCURS UNBOUNDED (IBM extension, used in LINKAGE),
      *> otherwise just recognize this in the parser and error (in which case
      *> we'd use the MF "unchecked OCCURS 1 DEPENDING ON var, with huge vars")
      *>
      *>* support for FUNCTION LENGTH, FUNCTION TRIM, FUNCTION COS, FUNCTION
      *> EXP, FUNCTION COS
      *>
      *>* ideally: support for GnuCOBOL's FUNCTION STORED-CHAR-LENGTH (otherwise
      *> we could use the MF code)
      *>
      *>* conditional compilation with values
      *> * set by defining level 78 values
      *> * set by command line option

        >>TURN EC-ALL CHECKING ON

       IDENTIFICATION DIVISION.
       PROGRAM-ID. simon-says.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
          77 C-3 USAGE COMP-3.                 *> up to 31/38 digits
          77 C-P USAGE PACKED-DECIMAL.         *> up to 31/38 digits
          77 C-1 USAGE COMP-1.                 *> as floating types
          77 C-2 USAGE COMP-2.                 *> as floating types
          77 C-5 USAGE COMP-5 PIC 9(8). *> passed/received from CALL c-function

          77 C-INDEXED USAGE INDEX.
          01 X.
             02 T PICTURE XXXX OCCURS 4 TIMES  INDEXED BY T-INDEXED.

       LINKAGE SECTION.

       PROCEDURE DIVISION.
          DECLARATIVES.

          BOUND-ERROR SECTION.
          USE AFTER EXCEPTION CONDITION EC-BOUND-SUBSCRIPT.
          DISPLAY "EC-BOUND-SUBSCRIPT: color inside the lines".

          DIVIDE-BY-ZERO SECTION.
          USE AFTER EXCEPTION CONDITION EC-SIZE-ZERO-DIVIDE.
          DISPLAY "EC-SIZE-ZERO-DIVIDE: caught".

          RANGE-PTR SECTION.
          USE AFTER EXCEPTION CONDITION EC-RANGE-PTR.
          DISPLAY "EC-RANGE-PTR: caught".

          END-DECLARATIVES.

        TESTING SECTION.
          MOVE 12345678012345678112345678312345678
          TO   C-3
          DISPLAY "C-3 IS " C-3
          MOVE 12345678012345678112345678312345678
          TO   C-P
          DISPLAY "C-P IS " C-P

      *>  MOVE 3.1425 TO C-1
          MOVE FUNCTION PI TO C-1
          DISPLAY "C-1 IS " C-1
      *>  MOVE 3.1425 TO C-2
          MOVE FUNCTION PI TO C-2
          DISPLAY "C-2 IS " C-2
          MOVE 42 TO C-5

          >>CALL-CONVENTION C
          CALL "printf" USING BY CONTENT
                        "C-5 IS %d\n", C-5 RETURNING C-5.
          DISPLAY "printf returned " C-5 " to C-5".
          SET C-INDEXED TO 2
      *>  SET C-INDEXED UP BY 1
      *>  MOVE 'ABCD' TO T(C-INDEXED)
      *>  DISPLAY "C-INDEXED IS " C-INDEXED " AND T IS " T(C-INDEXED)

          SET C-INDEXED TO 12
      *>  MOVE 'ABCD' TO T(C-INDEXED)
          DISPLAY "C-INDEXED IS " C-INDEXED " AND T IS UNCHANGED"

          MOVE 12 TO C-5.
          DISPLAY "C-5 IS " C-5 " AND T(" C-5 ") IS " T(C-5)

          MOVE "HI" TO T(1)
          DISPLAY "LENGTH: "
                  FUNCTION LENGTH( T(3) ),
                  " TRIM: "
                  "'"  FUNCTION TRIM( T(1) ) "'",
                  " COS: "
                  FUNCTION COS(2/3),
                  " EXP: "
                  FUNCTION  EXP(3).

          EXIT PROGRAM.
        EXTRA-SECTION SECTION.
      *>END PROGRAM simon-says.
