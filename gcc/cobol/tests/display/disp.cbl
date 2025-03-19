        IDENTIFICATION DIVISION.
        PROGRAM-ID.  disp.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 VAR PIC X(30) VALUE "    Marty    ".

        PROCEDURE DIVISION.
            DISPLAY SPACE
            DISPLAY """" VAR """"
            DISPLAY """" FUNCTION TRIM(VAR) """"
            STOP RUN.
