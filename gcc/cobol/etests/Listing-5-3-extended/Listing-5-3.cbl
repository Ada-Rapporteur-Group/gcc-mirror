        IDENTIFICATION DIVISION.
        PROGRAM-ID. Listing5-3.
        AUTHOR.  Michael Coughlan.

        *> This extended version, by Bob Dubner, is a more exhaustive demonstration
        *> than the one from the book.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 InputChar     PIC X.
           88 Vowel      VALUE  "A","E","I","O","U".
           88 Consonant  VALUE  "B" THRU "D", "F","G","H"
                                "J" THRU "N", "P" THRU "T"
                                "V" THRU "Z".
           88 Digit      VALUE  "0" THRU "9".
           88 ValidChar  VALUE  "A" THRU "Z", "0" THRU "9".

        PROCEDURE DIVISION.
        MOVE "A" to InputChar. PERFORM Begin.
        MOVE "B" to InputChar. PERFORM Begin.
        MOVE "C" to InputChar. PERFORM Begin.
        MOVE "D" to InputChar. PERFORM Begin.
        MOVE "E" to InputChar. PERFORM Begin.
        MOVE "F" to InputChar. PERFORM Begin.
        MOVE "G" to InputChar. PERFORM Begin.
        MOVE "H" to InputChar. PERFORM Begin.
        MOVE "I" to InputChar. PERFORM Begin.
        MOVE "J" to InputChar. PERFORM Begin.
        MOVE "K" to InputChar. PERFORM Begin.
        MOVE "L" to InputChar. PERFORM Begin.
        MOVE "M" to InputChar. PERFORM Begin.
        MOVE "N" to InputChar. PERFORM Begin.
        MOVE "O" to InputChar. PERFORM Begin.
        MOVE "P" to InputChar. PERFORM Begin.
        MOVE "Q" to InputChar. PERFORM Begin.
        MOVE "R" to InputChar. PERFORM Begin.
        MOVE "S" to InputChar. PERFORM Begin.
        MOVE "T" to InputChar. PERFORM Begin.
        MOVE "U" to InputChar. PERFORM Begin.
        MOVE "V" to InputChar. PERFORM Begin.
        MOVE "W" to InputChar. PERFORM Begin.
        MOVE "X" to InputChar. PERFORM Begin.
        MOVE "Y" to InputChar. PERFORM Begin.
        MOVE "Z" to InputChar. PERFORM Begin.
        MOVE "x" to InputChar. PERFORM Begin.
        MOVE "0" to InputChar. PERFORM Begin.
        MOVE "1" to InputChar. PERFORM Begin.
        MOVE "2" to InputChar. PERFORM Begin.
        MOVE "3" to InputChar. PERFORM Begin.
        MOVE "4" to InputChar. PERFORM Begin.
        MOVE "5" to InputChar. PERFORM Begin.
        MOVE "6" to InputChar. PERFORM Begin.
        MOVE "7" to InputChar. PERFORM Begin.
        MOVE "8" to InputChar. PERFORM Begin.
        MOVE "9" to InputChar. PERFORM Begin.
        STOP RUN.

        Begin.
           DISPLAY InputChar ": " WITH NO ADVANCING
           IF ValidChar
              DISPLAY "Input OK " WITH NO ADVANCING
            ELSE
              DISPLAY "Invalid character entered "
           END-IF
           IF Vowel
              DISPLAY "Vowel"
           END-IF
           IF Consonant
              DISPLAY "Consonent"
           END-IF
           IF Digit
              DISPLAY "Digit"
           END-IF.
