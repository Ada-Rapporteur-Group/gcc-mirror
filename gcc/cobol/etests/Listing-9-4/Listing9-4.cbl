IDENTIFICATION DIVISION.
PROGRAM-ID. Listing9-4.
AUTHOR. Michael Coughlan.

*> Extended by Bob Dubner to exercise INSPECT a little more deeply
*> Not much, but a little

DATA DIVISION.
WORKING-STORAGE SECTION.
01 Stars          PIC  *****.
01 NumOfStars     PIC 9.

01 twos     pic 99 VALUE 10.
01 threes   pic 99 VALUE 20.
01 fours    pic 99 VALUE 30.
01 bobs     pic 99 VALUE 40.

01 inspect_text PIC X(24) VALUE "two22three333four4444bob".

PROCEDURE DIVISION.
Begin.
   PERFORM VARYING NumOfStars FROM 0 BY 1 UNTIL NumOfStars > 5
      COMPUTE Stars = 10 ** (4 - NumOfStars)
      INSPECT Stars REPLACING ALL "1" BY SPACES
                              ALL "0" BY SPACES
      DISPLAY NumOfStars " = " Stars
   END-PERFORM

    DISPLAY "inspect_text " inspect_text
    INSPECT inspect_text
        TALLYING twos   for all "2"
                 bobs   for all "bob"
                 threes for all "3"
                 fours  for all "4"
        REPLACING ALL "bob" by "jim"
                  ALL "three" by "seven"

    DISPLAY "twos:   " twos
    DISPLAY "threes: " threes
    DISPLAY "fours:  " fours
    DISPLAY "bobs:   " bobs
    DISPLAY "inspect_text " inspect_text
    DISPLAY "(should be ) " "two22seven333four4444jim"

   STOP RUN.
