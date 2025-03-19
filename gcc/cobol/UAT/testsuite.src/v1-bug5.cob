       ID DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       77 var-1 PIC X(20) VALUE "hello world".
       77 var-2 PIC X(20) VALUE SPACE.
       77 var-3 PIC X(20) VALUE SPACE.
       PROCEDURE DIVISION.
          UNSTRING var-1 DELIMITED BY SPACE INTO var-2
             DELIMITED BY "l" var-3.
      *> Previous statement probably tripped up by second DELIMITED BY
          IF "hello" NOT = var-2 AND "world" NOT = var-3 THEN
             DISPLAY var-2 SPACE var-3
             MOVE 1 TO RETURN-CODE.
       END PROGRAM prog.

