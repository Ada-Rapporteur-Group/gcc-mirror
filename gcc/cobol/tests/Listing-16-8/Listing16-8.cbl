IDENTIFICATION DIVISION.
PROGRAM-ID. Listing16-8.
AUTHOR.  Michael Coughlan.

DATA DIVISION.
WORKING-STORAGE SECTION.
01 CopyData.

COPY Copybook1
     REPLACING S BY 15.
*> Changes the size of a data item
*> After replacement:
*>      02 CustomerName    PIC X(15).

COPY Copybook2 REPLACING ==V99== BY ====.
*> Changes the type of a data item to an integer
*> After replacement:
*>      02 CustomerOrder           PIC 9(6).

COPY Copybook3 REPLACING "CustKey" BY "MyValue".
COPY Copybook3 REPLACING CustKey BY NewKey.
*> demonstrates the difference between a literal and a COBOL-Word
*> First replacement:
*>       02 CustKey              PIC X(7) VALUE "MyValue".
*> Second replacment
*>       02 NewKey              PIC X(7) VALUE "CustKey".

COPY Copybook3 REPLACING CustKey BY
==CustAddress.
     03 Adr1         PIC X(10).
     03 Adr2         PIC X(10).
     03 Adr3         PIC X(10).
  02 CustId==.

*>Changes the CustKey declaration to add some new data items.
*>After REPLACEMENT the included text will be -
*>   02 CustAddress.
*>     03 Adr1         PIC X(10).
*>     03 Adr2         PIC X(10).
*>     03 Adr3         PIC X(10).
*>   02 CustId         PIC X(7) VALUE "CustKey".

PROCEDURE DIVISION.
BeginProg.
  MOVE "123456789012345678901234567890" TO CustomerName
  DISPLAY "CustomerName - " CustomerName
  DISPLAY "(should be     123456789012345)"
  DISPLAY SPACE

  MOVE 1234.56 TO CustomerOrder
  DISPLAY "CustomerOrder - " CustomerOrder
  DISPLAY "(should be      001234)"
  DISPLAY SPACE

  DISPLAY "CustKey value changed to - " CustKey
  DISPLAY "(should be                 MyValue)"
  DISPLAY SPACE

  DISPLAY "NewKey value - " NewKey
  DISPLAY "(should be     CustKey)"
  DISPLAY SPACE

  MOVE "Dublin"  TO Adr3

  DISPLAY "CustId value - "CustId
  DISPLAY "(should be     CustKey)"
  DISPLAY SPACE

STOP RUN.
