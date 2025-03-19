IDENTIFICATION DIVISION.
PROGRAM-ID. Listing5-1.

*> Expanded version of Coughlan's 5-1

ENVIRONMENT DIVISION.
CONFIGURATION SECTION.
SPECIAL-NAMES.
    CLASS HexNumber IS "0" THRU "9", "A" THRU "F"
    CLASS RealName  IS "A" THRU "Z", "a" THRU "z", "'", SPACE.

DATA DIVISION.
WORKING-STORAGE SECTION.
01 NumIn       PIC X(4).

PROCEDURE DIVISION.
    MOVE "0000" to NumIN
    PERFORM Begin.

    MOVE "FFFF" to NumIN
    PERFORM Begin.

    MOVE "AA11" to NumIN
    PERFORM Begin.

    MOVE "FFFG" to NumIN
    PERFORM Begin.

    STOP RUN.

Begin.
   IF NumIn IS HexNumber THEN
      DISPLAY NumIn " is a Hex number"
    ELSE
      DISPLAY NumIn " is not a Hex number"
   END-IF

   IF NumIN IS ALPHABETIC
      DISPLAY NumIN " is alphabetic"
    ELSE
      DISPLAY NumIN " is not alphabetic"
   END-IF

   IF NumIN IS RealName THEN
      DISPLAY NumIN " is a real name"
    ELSE
      DISPLAY NumIN " is not a real name"
   END-IF
   DISPLAY " ".

