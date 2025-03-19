        IDENTIFICATION DIVISION.
        PROGRAM-ID. Listing5-10.
        AUTHOR. Michael Coughlan.

        *> Extended by Bob Dubner to exercise the compiler

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 PlayerGuess-A    PIC 9  VALUE 1.
           88 Rock-A        VALUE 1.
           88 Paper-A       VALUE 2.
           88 Scissors-A    VALUE 3.

        01 PlayerGuess-B    PIC 9  VALUE 2.
           88 Rock-B        VALUE 1.
           88 Paper-B       VALUE 2.
           88 Scissors-B    VALUE 3.

        PROCEDURE DIVISION.
           DISPLAY "1=rock, 2=paper, 3=scissors"
           MOVE 1 TO PlayerGuess-A. MOVE 1 TO PlayerGuess-B. PERFORM BEGIN.
           MOVE 1 TO PlayerGuess-A. MOVE 2 TO PlayerGuess-B. PERFORM BEGIN.
           MOVE 1 TO PlayerGuess-A. MOVE 3 TO PlayerGuess-B. PERFORM BEGIN.
           DISPLAY " "
           MOVE 2 TO PlayerGuess-A. MOVE 1 TO PlayerGuess-B. PERFORM BEGIN.
           MOVE 2 TO PlayerGuess-A. MOVE 2 TO PlayerGuess-B. PERFORM BEGIN.
           MOVE 2 TO PlayerGuess-A. MOVE 3 TO PlayerGuess-B. PERFORM BEGIN.
           DISPLAY " "
           MOVE 3 TO PlayerGuess-A. MOVE 1 TO PlayerGuess-B. PERFORM BEGIN.
           MOVE 3 TO PlayerGuess-A. MOVE 2 TO PlayerGuess-B. PERFORM BEGIN.
           MOVE 3 TO PlayerGuess-A. MOVE 3 TO PlayerGuess-B. PERFORM BEGIN.
           STOP RUN.
        BEGIN.
        *>   DISPLAY "Guess for player A () : "
        *>           WITH NO ADVANCING
        *>   ACCEPT PlayerGuess-A
        *>   DISPLAY "Guess for player B (1=rock, 2=paper, 3=scissors) : "
        *>           WITH NO ADVANCING
        *>   ACCEPT PlayerGuess-B
           IF Rock-A     DISPLAY "Rock     " WITH NO ADVANCING END-IF
           IF Paper-A    DISPLAY "Paper    " WITH NO ADVANCING END-IF
           IF Scissors-A DISPLAY "Scissors " WITH NO ADVANCING END-IF
           DISPLAY " versus " WITH NO ADVANCING
           IF Rock-B     DISPLAY "Rock     " WITH NO ADVANCING END-IF
           IF Paper-B    DISPLAY "Paper    " WITH NO ADVANCING END-IF
           IF Scissors-B DISPLAY "Scissors " WITH NO ADVANCING END-IF
           DISPLAY ": " WITH NO ADVANCING

           EVALUATE  TRUE      ALSO    TRUE
              WHEN Rock-A      ALSO    Rock-B      DISPLAY "Draw"
              WHEN Rock-A      ALSO    Paper-B     DISPLAY "Player B wins"
              WHEN Rock-A      ALSO    Scissors-B  DISPLAY "Player A wins"
              WHEN Paper-A     ALSO    Rock-B      DISPLAY "Player A wins"
              WHEN Paper-A     ALSO    Paper-B     DISPLAY "Draw"
              WHEN Paper-A     ALSO    Scissors-B  DISPLAY "Player B wins"
              WHEN Scissors-A  ALSO    Rock-B      DISPLAY "Player B wins"
              WHEN Scissors-A  ALSO    Paper-B     DISPLAY "Player A wins"
              WHEN Scissors-A  ALSO    Scissors-B  DISPLAY "Draw"
              WHEN OTHER   DISPLAY "Evaluate problem"
           END-EVALUATE.
