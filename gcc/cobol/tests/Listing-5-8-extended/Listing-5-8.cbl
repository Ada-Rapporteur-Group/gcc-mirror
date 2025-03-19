        IDENTIFICATION DIVISION.
        PROGRAM-ID. Listing5-8.
        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 Age            PIC 99 VALUE ZERO.
           88 Infant      VALUE 0 THRU 3.
           88 YoungChild  VALUE 4 THRU 7.
           88 Child       VALUE 8 THRU 12.
           88 Visitor     VALUE 13 THRU 64.
           88 Pensioner   VALUE 65 THRU 99.

        01 Height         PIC 999 VALUE ZERO.

        01 Admission      PIC $99.99.


        PROCEDURE DIVISION.
            MOVE 40 to Height. MOVE  2 to AGE. Perform Begin.
            MOVE 50 to Height. MOVE  2 to AGE. Perform Begin.
            MOVE 40 to Height. MOVE  6 to AGE. Perform Begin.
            MOVE 50 to Height. MOVE  6 to AGE. Perform Begin.
            MOVE 40 to Height. MOVE 10 to AGE. Perform Begin.
            MOVE 50 to Height. MOVE 10 to AGE. Perform Begin.
            MOVE 40 to Height. MOVE 20 to AGE. Perform Begin.
            MOVE 50 to Height. MOVE 20 to AGE. Perform Begin.
            MOVE 40 to Height. MOVE 80 to AGE. Perform Begin.
            MOVE 50 to Height. MOVE 80 to AGE. Perform Begin.
            STOP RUN.

        Begin.
           EVALUATE TRUE        ALSO       TRUE
             WHEN   Infant      ALSO       ANY           MOVE 0  TO Admission
             WHEN   YoungChild  ALSO       ANY           MOVE 10 TO Admission
             WHEN   Child       ALSO   Height >= 48      MOVE 15 TO Admission
             WHEN   Child       ALSO   Height < 48       MOVE 10 TO Admission
             WHEN   Visitor     ALSO   Height >= 48      MOVE 25 TO Admission
             WHEN   Visitor     ALSO   Height < 48       MOVE 18 TO Admission
             WHEN   Pensioner   ALSO       ANY           MOVE 10 TO Admission
           END-EVALUATE

           DISPLAY "Age is " Age " and Height is " Height WITH NO ADVANCING
           DISPLAY ", so Admission charged is " Admission.

