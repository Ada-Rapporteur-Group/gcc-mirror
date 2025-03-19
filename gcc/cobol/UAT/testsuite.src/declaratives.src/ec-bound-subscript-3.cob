       IDENTIFICATION DIVISION.

       PROGRAM-ID. prog.

       DATA DIVISION.

       WORKING-STORAGE SECTION.                                         
       01 OUR-RECORD.
           05 our-table  OCCURS 4 TIMES PIC X(5).
       01 our-index pic 99 value 6.
       
       PROCEDURE DIVISION.                                              

       DECLARATIVES.
       DECLARATIVE-1 SECTION.
           USE AFTER EXCEPTION CONDITION EC-ALL.
              DISPLAY "DECLARATIVE FOR EC-ALL".
           GOBACK.           
       END DECLARATIVES.

       MAIN-SECTION SECTION.    
       DISPLAY "TURN EC-ALL CHECKING ON".
       >>TURN EC-ALL CHECKING ON
       PERFORM TEST1.

       GOBACK.

       TEST1. 
           MOVE "12345" TO our-table(our-index).

           END PROGRAM prog.

