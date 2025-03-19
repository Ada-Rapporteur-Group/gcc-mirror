IDENTIFICATION DIVISION.
PROGRAM-ID. Listing9-3.
AUTHOR. Michael Coughlan.

*> Modified by Bob Dubner to demonstrate multi-character currency sign.

ENVIRONMENT DIVISION.
CONFIGURATION SECTION.
SPECIAL-NAMES.
    CURRENCY SIGN IS "£"
    CURRENCY SIGN IS "$"
    CURRENCY SIGN IS "¥"
    CURRENCY SIGN IS "GoldPressedLatinum " WITH PICTURE SYMBOL "L".

DATA DIVISION.
WORKING-STORAGE SECTION.
01  DollarValue      PIC 9999V99.

01  PrnDollarValue   PIC $$$,$$9.99.
01  PrnYenValue      PIC ¥¥¥,¥¥9.99.
01  PrnPoundValue    PIC £££,££9.99.
01  PrnFerengiValue  PIC LLL,LL9.99.

01  Dollar2PoundRate PIC 99V9(6) VALUE 0.640138.
01  Dollar2YenRate   PIC 99V9(6) VALUE 98.6600.

PROCEDURE DIVISION.
Begin.
   DISPLAY "Enter a dollar value to convert :- " WITH NO ADVANCING
   ACCEPT DollarValue
   DISPLAY "The DollarValue entered: " DollarValue

   COMPUTE PrnYenValue ROUNDED = DollarValue * Dollar2YenRate

   MOVE DollarValue TO PrnDollarValue
   COMPUTE PrnPoundValue ROUNDED = DollarValue * Dollar2PoundRate

   MOVE DollarValue TO PrnFerengiValue

   DISPLAY "Dollar value    = " PrnDollarValue
   DISPLAY "Ferengi value   = " PrnFerengiValue
   DISPLAY "Yen value       = " PrnYenValue
   DISPLAY "Pound value     = " PrnPoundValue

   STOP RUN.

