IDENTIFICATION DIVISION.
PROGRAM-ID. Listing5-2.
AUTHOR.  Michael Coughlan.
*> Extended for more complete testing by Bob Dubner
DATA DIVISION.
WORKING-STORAGE SECTION.

01  Employees PIC X(12) VALUE SPACE.
    88 Coboler VALUE "Bob", "James", "Martin".

01  CityCode PIC 9 VALUE ZERO.
    88 CityIsDublin         VALUE 1.
    88 CityIsLimerick       VALUE 2.
    88 CityIsCork           VALUE 3.
    88 CityIsGalway         VALUE 4.
    88 CityIsSligo          VALUE 5.
    88 CityIsWaterford      VALUE 6.
    88 UniversityCity       VALUE 1 THRU 4.
    88 CityCodeNotValid     VALUE 0, 7, 8, 9.

PROCEDURE DIVISION.

    MOVE "James" to EMPLOYEES.
    IF Coboler
        DISPLAY EMPLOYEES " is a Coboler"
    ELSE
        DISPLAY EMPLOYEES " is not a Coboler"
        END-IF

    MOVE "Freddy" to EMPLOYEES.
    IF Coboler
        DISPLAY EMPLOYEES " is a Coboler"
    ELSE
        DISPLAY EMPLOYEES " is not a Coboler"
        END-IF

    MOVE 0 to CityCode.
    PERFORM Begin.
    MOVE 1 to CityCode
    PERFORM Begin.
    MOVE 2 to CityCode
    PERFORM Begin.
    MOVE 3 to CityCode
    PERFORM Begin.
    MOVE 4 to CityCode
    PERFORM Begin.
    MOVE 5 to CityCode
    PERFORM Begin.
    MOVE 6 to CityCode
    PERFORM Begin.
    MOVE 7 to CityCode
    PERFORM Begin.
    MOVE 8 to CityCode
    PERFORM Begin.
    MOVE 9 to CityCode
    PERFORM Begin.
    STOP RUN.

Begin.
*>   DISPLAY "Enter a city code (1-6) - " WITH NO ADVANCING
*>   ACCEPT CityCode
   DISPLAY "CityCode is " CityCode
   IF CityCodeNotValid
      DISPLAY "Invalid city code entered"
     ELSE
       IF CityIsLimerick
          DISPLAY "Hey, we're home."
       END-IF
       IF CityIsDublin
          DISPLAY "Hey, we're in the capital."
       END-IF
       IF UniversityCity
          DISPLAY "Apply the rent surcharge!"
       END-IF
   END-IF.
DummyParagraph.
   STOP RUN.


