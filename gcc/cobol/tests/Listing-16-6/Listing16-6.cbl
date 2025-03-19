IDENTIFICATION DIVISION.
PROGRAM-ID.  Listing16-6.
AUTHOR.  Michael Coughlan.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 Parameters.
   02 StateNum      PIC 99.
   02 StateCode     PIC XX.
   02 StateName     PIC X(14).
   02 StateCapital  PIC X(14).
   02 StatePop      PIC 9(8).
   02 ErrorFlag     PIC 9.
      88 NoError    VALUE ZERO.

*> Receiving item for TIME: Format is HHMMSSss   s = S/100
01 CurrentTime.
   02 FILLER        PIC 9(4).
   02 Seed          PIC 9(4).
01 RandChoice       PIC 9.
01 PrnStatePop      PIC ZZ,ZZZ,ZZ9.

PROCEDURE DIVISION.
Begin.
   ACCEPT CurrentTime FROM TIME
   COMPUTE RandChoice = 0
   PERFORM 4 TIMES
      DISPLAY SPACES
      INITIALIZE Parameters
      ADD 1 TO RandChoice
      EVALUATE RandChoice
        WHEN      1   DISPLAY "Enter a state number - " WITH NO ADVANCING
                      ACCEPT StateNum
                      DISPLAY StateNum
        WHEN      2   DISPLAY "Enter a two letter code - " WITH NO ADVANCING
                      ACCEPT StateCode
                      DISPLAY StateCode
        WHEN      3   DISPLAY "Enter a state name - " WITH NO ADVANCING
                      ACCEPT StateName
                      DISPLAY StateName
        WHEN      4   DISPLAY "Enter a state capital - " WITH NO ADVANCING
                      ACCEPT StateCapital
                      DISPLAY StateCapital
      END-EVALUATE
      CALL "GetStateInfo"
           USING BY REFERENCE  StateNum, StateCode, StateName,
                               StateCapital, StatePop, ErrorFlag
      IF NoError
         MOVE StatePop TO PrnStatePop
         DISPLAY StateNum ". " StateCode SPACE StateName
                 SPACE StateCapital SPACE PrnStatePop
        ELSE
         DISPLAY "There was an error.  Error Code = " ErrorFlag
      END-IF
   END-PERFORM
   STOP RUN.

