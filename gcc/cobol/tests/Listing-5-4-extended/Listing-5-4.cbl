        IDENTIFICATION DIVISION.
        PROGRAM-ID. Listing5-4.
        AUTHOR.  Michael Coughlan.

        *> Extended by Bob Dubner to exercise and test the compiler.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01  MakeOfCar        PIC X(10).
            88 VolksGroup  VALUE "skoda", "seat",
                                 "audi", "volkswagen"
                           FALSE "boat".
            88 GermanMade  VALUE "volkswagen", "audi",
                                 "mercedes", "bmw",
                                 "porsche".
        PROCEDURE DIVISION.
            MOVE "skoda" TO MakeOfCar. PERFORM Begin.
            MOVE "seat" TO MakeOfCar. PERFORM Begin.
            MOVE "audi" TO MakeOfCar. PERFORM Begin.
            MOVE "volkswagen" TO MakeOfCar. PERFORM Begin.
            MOVE "mercedes" TO MakeOfCar. PERFORM Begin.
            MOVE "bmw" TO MakeOfCar. PERFORM Begin.
            MOVE "porsche" TO MakeOfCar. PERFORM Begin.
            DISPLAY " "

            IF Volksgroup
                DISPLAY "Volksgroup is initially TRUE"
            ELSE
                DISPLAY "Volksgroup is initially FALSE"
                END-IF
            DISPLAY "After 'SET Volksgroup TO TRUE':"
            SET Volksgroup TO TRUE
            IF Volksgroup
                DISPLAY "Volksgroup is TRUE"
            ELSE
                DISPLAY "Volksgroup is FALSE"
                END-IF
            DISPLAY "After 'SET Volksgroup TO FALSE':"
            SET Volksgroup TO FALSE
            IF Volksgroup
                DISPLAY "Volksgroup is TRUE"
            ELSE
                DISPLAY "Volksgroup is FALSE"
                END-IF

            STOP RUN.

        Begin.
            DISPLAY MakeOfCar ": " WITH NO ADVANCING
            IF VolksGroup AND GermanMade
                DISPLAY "Made in Germany by the Volkswagen Group."
            ELSE
                IF VolksGroup
                    DISPLAY "Made by the Volkswagen Group."
            END-IF
                IF GermanMade
                    DISPLAY "Made in Germany."
                END-IF
            END-IF.

