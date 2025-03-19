        IDENTIFICATION DIVISION.
        PROGRAM-ID.  moves.

        DATA DIVISION.
        WORKING-STORAGE SECTION.

          01  A_ALPHA     PIC X(10)           .
          01  A_6         PIC 999999          .
          01  A_S6        PIC S999999         .
          01  A_3V3       PIC 999V999         .
          01  A_S3V3      PIC S999V999        .
          01  A_3V3B      PIC 999V999  BINARY .
          01  A_S3V3B     PIC S999V999 BINARY .
          01  A_3V3B3     PIC 999V999  COMP-3 .
          01  A_S3V3B3    PIC S999V999 Comp-3 .
          01  A_3DOT3     PIC 999.999         .
          01  A_S3DOT3    PIC +999.999        .

          01  B_ALPHA     PIC X(10)           .
          01  B_6         PIC 999999          .
          01  B_S6        PIC S999999          .
          01  B_3V3       PIC 999V999         .
          01  B_S3V3      PIC S999V999        .
          01  B_3V3B      PIC 999V999  BINARY .
          01  B_S3V3B     PIC S999V999 BINARY .
          01  B_3V3B3     PIC 999V999  COMP-3 .
          01  B_S3V3B3    PIC S999V999 COMP-3 .
          01  B_3DOT3     PIC 999.999         .
          01  B_S3DOT3    PIC +999.999        .

          01  SOURCE-VARIABLE PIC X(8).
          01  NO_MOVE PIC X(9) VALUE "<no move>".

        01 Threes.
            05 Three1   PIC X(3).
            05 Three2   PIC X(3).
            05 Three3   PIC X(3).
            05 Three4   PIC X(3).

        01 Follow.
            05 Follow0                   PIC X(12).
            05 Follow1 REDEFINES Follow0 PIC X(3).
            05 Follow2 REDEFINES Follow0 PIC X(6).
            05 Follow3 REDEFINES Follow0 PIC X(9).
            05 Follow4 REDEFINES Follow0 PIC X(12).
            05 Addendum                  PIC X(3).

        PROCEDURE DIVISION.
            MOVE "12.34"  TO A_ALPHA
            MOVE  12.34   TO A_6
            MOVE -12.34   TO A_S6
            MOVE  12.34   TO A_3V3
            MOVE -12.34   TO A_S3V3
            MOVE  12.34   TO A_3V3B
            MOVE -12.34   TO A_S3V3B
            MOVE  12.34   TO A_3V3B3
            MOVE -12.34   TO A_S3V3B3
            MOVE  12.34   TO A_3DOT3
            MOVE -12.34   TO A_S3DOT3

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_ALPHA" TO SOURCE-VARIABLE
            MOVE A_ALPHA TO B_ALPHA
            MOVE A_ALPHA TO B_6
            MOVE A_ALPHA TO B_S6
            MOVE A_ALPHA TO B_3V3
            MOVE A_ALPHA TO B_S3V3
            MOVE A_ALPHA TO B_3V3B
            MOVE A_ALPHA TO B_S3V3B
            MOVE A_ALPHA TO B_3V3B3
            MOVE A_ALPHA TO B_S3V3B3
            MOVE A_ALPHA TO B_3DOT3
            MOVE A_ALPHA TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_6" TO SOURCE-VARIABLE
            MOVE A_6 TO B_ALPHA
            MOVE A_6 TO B_6
            MOVE A_6 TO B_S6
            MOVE A_6 TO B_3V3
            MOVE A_6 TO B_S3V3
            MOVE A_6 TO B_3V3B
            MOVE A_6 TO B_S3V3B
            MOVE A_6 TO B_3V3B3
            MOVE A_6 TO B_S3V3B3
            MOVE A_6 TO B_3DOT3
            MOVE A_6 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_S6" TO SOURCE-VARIABLE
            MOVE A_S6 TO B_ALPHA
            MOVE A_S6 TO B_6
            MOVE A_S6 TO B_S6
            MOVE A_S6 TO B_3V3
            MOVE A_S6 TO B_S3V3
            MOVE A_S6 TO B_3V3B
            MOVE A_S6 TO B_S3V3B
            MOVE A_S6 TO B_3V3B3
            MOVE A_S6 TO B_S3V3B3
            MOVE A_S6 TO B_3DOT3
            MOVE A_S6 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_3V3" TO SOURCE-VARIABLE
            *>MOVE A_3V3 TO B_ALPHA
            MOVE A_3V3 TO B_6
            MOVE A_3V3 TO B_S6
            MOVE A_3V3 TO B_3V3
            MOVE A_3V3 TO B_S3V3
            MOVE A_3V3 TO B_3V3B
            MOVE A_3V3 TO B_S3V3B
            MOVE A_3V3 TO B_3V3B3
            MOVE A_3V3 TO B_S3V3B3
            MOVE A_3V3 TO B_3DOT3
            MOVE A_3V3 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_S3V3" TO SOURCE-VARIABLE
            *>MOVE A_S3V3 TO B_ALPHA
            MOVE A_S3V3 TO B_6
            MOVE A_S3V3 TO B_S6
            MOVE A_S3V3 TO B_3V3
            MOVE A_S3V3 TO B_S3V3
            MOVE A_S3V3 TO B_3V3B
            MOVE A_S3V3 TO B_S3V3B
            MOVE A_S3V3 TO B_3V3B3
            MOVE A_S3V3 TO B_S3V3B3
            MOVE A_S3V3 TO B_3DOT3
            MOVE A_S3V3 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_3V3B" TO SOURCE-VARIABLE
            *>MOVE A_3V3B TO B_ALPHA
            MOVE A_3V3B TO B_6
            MOVE A_3V3B TO B_S6
            MOVE A_3V3B TO B_3V3
            MOVE A_3V3B TO B_S3V3
            MOVE A_3V3B TO B_3V3B
            MOVE A_3V3B TO B_S3V3B
            MOVE A_3V3B TO B_3V3B3
            MOVE A_3V3B TO B_S3V3B3
            MOVE A_3V3B TO B_3DOT3
            MOVE A_3V3B TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_S3V3B" TO SOURCE-VARIABLE
            *>MOVE A_S3V3B TO B_ALPHA
            MOVE A_S3V3B TO B_6
            MOVE A_S3V3B TO B_S6
            MOVE A_S3V3B TO B_3V3
            MOVE A_S3V3B TO B_S3V3
            MOVE A_S3V3B TO B_3V3B
            MOVE A_S3V3B TO B_S3V3B
            MOVE A_S3V3B TO B_3V3B3
            MOVE A_S3V3B TO B_S3V3B3
            MOVE A_S3V3B TO B_3DOT3
            MOVE A_S3V3B TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_3V3B3" TO SOURCE-VARIABLE
            *>MOVE A_3V3B3 TO B_ALPHA
            MOVE A_3V3B3 TO B_6
            MOVE A_3V3B3 TO B_S6
            MOVE A_3V3B3 TO B_3V3
            MOVE A_3V3B3 TO B_S3V3
            MOVE A_3V3B3 TO B_3V3B
            MOVE A_3V3B3 TO B_S3V3B
            MOVE A_3V3B3 TO B_3V3B3
            MOVE A_3V3B3 TO B_S3V3B3
            MOVE A_3V3B3 TO B_3DOT3
            MOVE A_3V3B3 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "B_S3V3B3" TO SOURCE-VARIABLE
            *>MOVE B_S3V3B3 TO B_ALPHA
            MOVE B_S3V3B3 TO B_6
            MOVE B_S3V3B3 TO B_S6
            MOVE B_S3V3B3 TO B_3V3
            MOVE B_S3V3B3 TO B_S3V3
            MOVE B_S3V3B3 TO B_3V3B
            MOVE B_S3V3B3 TO B_S3V3B
            MOVE B_S3V3B3 TO B_3V3B3
            MOVE B_S3V3B3 TO B_S3V3B3
            MOVE B_S3V3B3 TO B_3DOT3
            MOVE B_S3V3B3 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_3DOT3" TO SOURCE-VARIABLE
            MOVE A_3DOT3 TO B_ALPHA
            MOVE A_3DOT3 TO B_6
            MOVE A_3DOT3 TO B_S6
            MOVE A_3DOT3 TO B_3V3
            MOVE A_3DOT3 TO B_S3V3
            MOVE A_3DOT3 TO B_3V3B
            MOVE A_3DOT3 TO B_S3V3B
            MOVE A_3DOT3 TO B_3V3B3
            MOVE A_3DOT3 TO B_S3V3B3
            MOVE A_3DOT3 TO B_3DOT3
            MOVE A_3DOT3 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE NO_MOVE TO B_ALPHA
            MOVE "A_S3DOT3" TO SOURCE-VARIABLE
            MOVE A_S3DOT3 TO B_ALPHA
            MOVE A_S3DOT3 TO B_6
            MOVE A_S3DOT3 TO B_S6
            MOVE A_S3DOT3 TO B_3V3
            MOVE A_S3DOT3 TO B_S3V3
            MOVE A_S3DOT3 TO B_3V3B
            MOVE A_S3DOT3 TO B_S3V3B
            MOVE A_S3DOT3 TO B_3V3B3
            MOVE A_S3DOT3 TO B_S3V3B3
            MOVE A_S3DOT3 TO B_3DOT3
            MOVE A_S3DOT3 TO B_S3DOT3
            PERFORM DISPLAY_ALL

            MOVE "aaabbbcccddd" TO Follow4
            MOVE "111222333444" TO Threes
            DISPLAY "Follow4 should be 'aaabbbcccddd' but is " Follow4
            DISPLAY "Threes  should be '111222333444' but is " Threes
            DISPLAY SPACE

            MOVE "111222333444" TO Threes
            MOVE "aaabbbcccddd" TO Follow4
            DISPLAY "Threes  should be '111222333444' but is " Threes
            DISPLAY "Follow4 should be 'aaabbbcccddd' but is " Follow4

            STOP RUN.
        DISPLAY_ALL.
            DISPLAY "Source variable is " SOURCE-VARIABLE
            DISPLAY "B_ALPHA  is  " B_ALPHA
            DISPLAY "B_6      is  " B_6
            DISPLAY "B_S6     is "  B_S6
            DISPLAY "B_3V3    is  " B_3V3
            DISPLAY "B_S3V3   is "  B_S3V3
            DISPLAY "B_3V3B   is  " B_3V3B
            DISPLAY "B_S3V3B  is "  B_S3V3B
            DISPLAY "B_3V3B3  is  " B_3V3B3
            DISPLAY "B_S3V3B3 is "  B_S3V3B3
            DISPLAY "B_3DOT3  is  " B_3DOT3
            DISPLAY "B_S3DOT3 is "  B_S3DOT3
            DISPLAY " ".
        END PROGRAM moves.
