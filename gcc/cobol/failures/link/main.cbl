        PROGRAM-ID caller.
        DATA DIVISION.
        WORKING-STORAGE SECTION.
            77 CALLED PIC X(30) VALUE 'SUB'.
        PROCEDURE DIVISION.
            DISPLAY 'calling ...'
            CALL CALLED.
            DISPLAY 'done.'
