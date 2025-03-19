IDENTIFICATION DIVISION.
PROGRAM-ID. "A".

DATA DIVISION.
WORKING-STORAGE SECTION.
01  CWD          PIC X(100).
01  RETURNED-CWD PIC X(100).
01  LEN_OF_CWD   PIC 999 VALUE 100.
01  USR-LOCAL-BIN  PIC X(15) VALUE "/usr/local/bin".
01  CHDIR_RETURN PIC S999 BINARY.

01  var1 pic x(24) VALUE "I shouldn't change".
01  var2 pic x(24) VALUE "I should change".

01  var128   pic 9(30) VALUE 987654321098765432109876543210.
01  var128-2 pic 9(30) .

PROCEDURE DIVISION.

    MOVE X'00' TO USR-LOCAL-BIN(15:1)
    CALL    "chdir"
            USING BY CONTENT USR-LOCAL-BIN
            RETURNING CHDIR_RETURN
    DISPLAY "Return from chdir is " CHDIR_RETURN

    DISPLAY "About to call the libc.so routine ""getcwd"" "
    CALL    "getcwd"
            USING BY REFERENCE CWD
                  BY VALUE   LEN_OF_CWD
    DISPLAY "CWD is '" CWD "'"
    DISPLAY SPACES

    MOVE SPACES TO CWD
    DISPLAY "About to call getcwd with RETURNING phrase"
    CALL    "getcwd"
            USING BY REFERENCE CWD
                  BY VALUE   LEN_OF_CWD
            RETURNING RETURNED-CWD
    DISPLAY "CWD is '" CWD "'"
    DISPLAY "RETURNED-CWD is '" RETURNED-CWD "'"
    DISPLAY SPACES

    DISPLAY "About to call ""imitationcwd"", which works like the libc.so routine ""cwd"" "
    CALL    "imitationcwd"
            USING BY REFERENCE CWD
                  BY VALUE   LEN_OF_CWD
    DISPLAY "CWD is '" CWD "'"
    DISPLAY SPACES

    MOVE SPACES TO CWD
    DISPLAY "About to call imitationcwd with RETURNING phrase"
    CALL    "imitationcwd"
            USING BY REFERENCE CWD
                  BY VALUE   LEN_OF_CWD
            RETURNING RETURNED-CWD
    DISPLAY "CWD is '" CWD "'"
    DISPLAY "RETURNED-CWD is '" RETURNED-CWD "'"
    DISPLAY SPACES

    MOVE SPACES TO CWD
    CALL "returner" RETURNING CWD
    DISPLAY "returner returned '" CWD "'"
    DISPLAY SPACES

    CALL "c-calls"
    DISPLAY SPACES

    >>CALL-CONVENTION C
    DISPLAY "COBOL will call C Routine_B, which will call COBOL routine_c"
    CALL "Routine_B"
    DISPLAY SPACES
    >>CALL-CONVENTION COBOL

    Display "simple check of cobol-to-cobol BY CONTENT and BY REFERENCE"
    DISPLAY "Before"
    DISPLAY var1
    display var2
    display space
    call "callee" using by content   var1
                        by reference var2
    DISPLAY "after"
    DISPLAY var1
    display var2

    DISPLAY "pass 128-bit value to a C routine"
    call "routine_128" USING BY VALUE var128

    *> DISPLAY "pass 128-bit value to a COBOL routine and get it back"
    *> MOVE ZERO to var128-2
    *> call "routine_128_cobol" USING BY VALUE var128 RETURNING var128-2
    *> DISPLAY "var128-2"

    MOVE ZERO TO RETURN-CODE
    GOBACK.
    END PROGRAM A.

IDENTIFICATION DIVISION.
PROGRAM-ID. returner.
DATA DIVISION.
LINKAGE SECTION.
01 retval PIC X(100).

PROCEDURE DIVISION RETURNING retval.
    DISPLAY "The COBOL ""returner"" routine will return ""Whassup?"" through RETURNING ".
    MOVE "Whassup?" TO retval.
    END PROGRAM returner.

IDENTIFICATION DIVISION.
PROGRAM-ID. c-calls.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 string-integer pic XXXXXX.
01 binary-integer  pic 999999 BINARY.

PROCEDURE DIVISION.
    MOVE "123456" to string-integer
    DISPLAY 'About to call string_to_long with "' string-integer '"'
    CALL "string_to_long"
            USING string-integer
            RETURNING binary-integer
    DISPLAY "string_to_long returned " binary-integer.
    DISPLAY SPACES

    MOVE 654321 to binary-integer
    DISPLAY 'About to call long_to_string with ' binary-integer
    CALL "long_to_string"
            USING BY VALUE binary-integer
            RETURNING string-integer
    DISPLAY 'long_to_string returned "' string-integer '"'
    DISPLAY SPACES.

    END PROGRAM  c-calls.

IDENTIFICATION DIVISION.
PROGRAM-ID. routine_c.
PROCEDURE DIVISION.
    DISPLAY "      I am COBOL routine_c".
    END PROGRAM routine_c.



IDENTIFICATION DIVISION.
PROGRAM-ID.  callee.

DATA DIVISION.
LINKAGE SECTION.
01 par1 pic x(24).
01 par2 pic x(24).

PROCEDURE DIVISION USING par1 par2.

move "Something is wrong" TO par1
move "Good: I changed!" TO par2

goback.
END PROGRAM callee.

*> IDENTIFICATION DIVISION.
*> PROGRAM-ID. routine_128_cobol.
*> DATA DIVISION.
*> LINKAGE SECTION.
*> 01  var1 pic 9(30) .
*> 01  var2 pic 9(30) .
*> PROCEDURE DIVISION USING var1 RETURNING var2.
    *> DISPLAY "      I am COBOL routine_128_cobol".
    *> DISPLAY var1
    *> MOVE var1 TO var2
    *> END PROGRAM routine_128_cobol.
