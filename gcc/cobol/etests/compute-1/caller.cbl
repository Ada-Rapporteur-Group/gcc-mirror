        IDENTIFICATION DIVISION.
        PROGRAM-ID.  caller.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 A PIC 99  VALUE 50.
        01 B PIC 999 VALUE 25.
        01 C PIC 99  VALUE 42.
        01 Z PIC 99  VALUE ZERO.


        PROCEDURE DIVISION.

        DISPLAY "Dividing something by ZERO..."
        DIVIDE B BY Z GIVING C
        DISPLAY "1 C ends up being " C.
        IF C NOT EQUAL TO 42 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DIVIDE B BY Z GIVING C
                ON SIZE ERROR DISPLAY "Proper Size Error".
        DISPLAY "2 C ends up being " C.
        IF C NOT EQUAL TO 42 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DIVIDE B BY Z GIVING C
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY "3 C ends up being " C.
        IF C NOT EQUAL TO 42 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DIVIDE B BY Z GIVING C
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY "4 C ends up being " C.
        IF C NOT EQUAL TO 42 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "Dividing 50 by 25..."
        DIVIDE A BY B GIVING C
        DISPLAY "5 C ends up being " C.
        IF C NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DIVIDE A BY B GIVING C
                ON SIZE ERROR DISPLAY "Improper Size Error".
        DISPLAY "6 C ends up being " C.
        IF C NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DIVIDE A BY B GIVING C
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY "7 C ends up being " C.
        IF C NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DIVIDE A BY B GIVING C
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY "8 C ends up being " C.
        IF C NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "DIVIDE ZERO into 50..."
        MOVE 50 TO A
        DIVIDE Z INTO A
        DISPLAY "9 A ends up being " A.
        IF A NOT EQUAL TO 50 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 50 TO A
        DIVIDE Z INTO A
                ON SIZE ERROR DISPLAY "Proper Size Error".
        DISPLAY "10 A ends up being " A.
        IF A NOT EQUAL TO 50 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 50 TO A
        DIVIDE Z INTO A
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY "11 A ends up being " A.
        IF A NOT EQUAL TO 50 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 50 TO A
        DIVIDE Z INTO A
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY "12 A ends up being " A.
        IF A NOT EQUAL TO 50 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "DIVIDE 25 into 50..."
        DIVIDE B INTO A
        DISPLAY "13 A ends up being " A.
        IF A NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        MOVE 50 TO A
        DISPLAY SPACE

        DIVIDE B INTO A
                ON SIZE ERROR DISPLAY "Improper Size Error".
        DISPLAY "14 A ends up being " A.
        IF A NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        MOVE 50 TO A
        DISPLAY SPACE

        DIVIDE B INTO A
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY "15 A ends up being " A.
        IF A NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        MOVE 50 TO A
        DISPLAY SPACE

        DIVIDE B INTO A
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY "16 A ends up being " A.
        IF A NOT EQUAL TO 2 DISPLAY "That was wrong" END-IF
        MOVE 50 TO A
        DISPLAY SPACE

        DISPLAY "Simple COMPUTE A=B, no ON ERROR clause"
        MOVE 5 TO B
        DISPLAY "17 COMPUTE A (PIC XX) = " B
        COMPUTE A = B
        DISPLAY A
        IF A NOT EQUAL TO 5 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 45 TO B
        DISPLAY "18 COMPUTE A (PIC XX) = " B
        COMPUTE A = B
        DISPLAY A
        IF A NOT EQUAL TO 45 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 345 TO B
        DISPLAY "19 COMPUTE A (PIC XX) = " B
        COMPUTE A = B
        DISPLAY A
        IF A NOT EQUAL TO 45 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "Simple COMPUTE A=B, with ON ERROR clause"
        MOVE 5 TO B
        DISPLAY "20 COMPUTE A (PIC XX) = " B
        COMPUTE A = B
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY A
        IF A NOT EQUAL TO 5 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 45 TO B
        DISPLAY "21 COMPUTE A (PIC XX) = " B
        COMPUTE A = B
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY A
        IF A NOT EQUAL TO 45 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        MOVE 345 TO B
        DISPLAY "22 COMPUTE A (PIC XX) = " B
        COMPUTE A = B
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY A
        IF A NOT EQUAL TO 45 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "23 COMPUTE 1 + 2 + 3 * 4 (should be 15, no error)"
        COMPUTE C = 1 + 2 + 3 * 4
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY C
        DISPLAY SPACE

        DISPLAY "24 COMPUTE 101 + 2 + 3 * 4 (should be 15, with error)"
        COMPUTE C = 101 + 2 + 3 * 4
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 15 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "25 COMPUTE 11 + 2 + 50/ZERO + 3 * 4 should be 99, with no error clause"
        MOVE 50 TO A
        MOVE 99 TO C
        COMPUTE C = 11 + 2 + A/Z + 3 * 4
        DISPLAY C
        IF C NOT EQUAL TO 99 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "26 COMPUTE 11 + 2 + 50/ZERO + 3 * 4 (should be 99, with error)"
        MOVE 50 TO A
        MOVE 99 TO C
        COMPUTE C = 11 + 2 + A/Z + 3 * 4
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 99 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "27 COMPUTE C = 2**3, should be 08"
        MOVE 99 TO C
        COMPUTE C = 2**3
        DISPLAY C
        IF C NOT EQUAL TO 8 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "28 COMPUTE C = 16**0.5, should be 04"
        MOVE 99 TO C
        COMPUTE C = 16**0.5
        DISPLAY C
        IF C NOT EQUAL TO 4 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "29 COMPUTE C = 0**0, should be 01"
        MOVE 99 TO C
        COMPUTE C = 0**0
        DISPLAY C
        IF C NOT EQUAL TO 1 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "30 COMPUTE C = 0**-1, should be 00"
        MOVE 99 TO C
        COMPUTE C = 0**-1
        DISPLAY C
        IF C NOT EQUAL TO 0 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "31 COMPUTE C = -16**0.5, should be 99"
        MOVE 99 TO C
        COMPUTE C = -16**0.5
        DISPLAY C
        IF C NOT EQUAL TO 99 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "32 COMPUTE C = 2**3, should be 08"
        MOVE 99 TO C
        COMPUTE C = 2**3
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 08 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "33 COMPUTE C = 16**0.5, should be 04"
        MOVE 99 TO C
        COMPUTE C = 16**0.5
                ON SIZE ERROR DISPLAY "Improper Size Error"
            NOT ON SIZE ERROR DISPLAY "Proper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 04 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "34 COMPUTE C = 0**0, should be 99"
        MOVE 99 TO C
        COMPUTE C = 0**0
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 99 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "35 COMPUTE C = 0**-1, should be 99"
        MOVE 99 TO C
        COMPUTE C = 0**-1
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 99 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        DISPLAY "36 COMPUTE C = -16**0.5, should be 99"
        MOVE 99 TO C
        COMPUTE C = -16**0.5
                ON SIZE ERROR DISPLAY "Proper Size Error"
            NOT ON SIZE ERROR DISPLAY "Improper NOT Size Error".
        DISPLAY C
        IF C NOT EQUAL TO 99 DISPLAY "That was wrong" END-IF
        DISPLAY SPACE

        STOP RUN.
        END PROGRAM caller.
