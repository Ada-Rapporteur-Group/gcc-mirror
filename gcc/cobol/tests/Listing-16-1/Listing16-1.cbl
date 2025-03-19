IDENTIFICATION DIVISION.
PROGRAM-ID. Listing16-1.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 Increment      PIC 99 VALUE ZERO.
   88 EndOfData   VALUE ZERO.

PROCEDURE DIVISION.
Begin.
*> Demonstrates the difference between Steady
*> and Dynamic.  Entering a zero ends the iteration
   DISPLAY "Enter an increment value (0-99) - " WITH NO ADVANCING
   ACCEPT Increment
   PERFORM UNTIL EndOfData
      DISPLAY INCREMENT
      CALL "Ste-ady"  USING BY CONTENT Increment
      CALL "Dynamic" USING BY CONTENT Increment
      DISPLAY SPACES
      DISPLAY "Enter an increment value (0-99) - " WITH NO ADVANCING
      ACCEPT Increment
   END-PERFORM
   STOP RUN.

  IDENTIFICATION DIVISION.
  PROGRAM-ID. Dynamic.
  DATA DIVISION.
  WORKING-STORAGE SECTION.
  01 RunningTotal   PIC 9(5) VALUE ZERO.
  01 PrnTotal       PIC ZZ,ZZ9.

  LINKAGE SECTION.
  01 ValueToAdd     PIC 99.
  PROCEDURE DIVISION USING ValueToAdd.
  Begin.
     ADD ValueToAdd TO RunningTotal
     MOVE RunningTotal TO PrnTotal
     DISPLAY "Dynamic total = " PrnTotal
     EXIT PROGRAM.
  END PROGRAM Dynamic.


  IDENTIFICATION DIVISION.
  PROGRAM-ID. Ste-ady IS INITIAL.
  DATA DIVISION.
  WORKING-STORAGE SECTION.
  01 RunningTotal_2   PIC 9(5) VALUE ZERO.
  01 PrnTotal_2       PIC ZZ,ZZ9.

  LINKAGE SECTION.
  01 ValueToAdd_2  PIC 99.
  PROCEDURE DIVISION USING ValueToAdd_2 .
  Begin.
     ADD ValueToAdd_2  TO RunningTotal_2
     MOVE RunningTotal_2 TO PrnTotal_2
     DISPLAY "Steady  total = " PrnTotal_2
     EXIT PROGRAM.
  END PROGRAM Ste-ady.
END PROGRAM Listing16-1.
