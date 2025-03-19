       IDENTIFICATION DIVISION.

       PROGRAM-ID. prog.

       DATA DIVISION.

       WORKING-STORAGE SECTION.                                         
       01 OUR-TABLE.
          05 our-entry  OCCURS 1 to 9 TIMES DEPENDING ON our-index pic 99.
       01 our-index pic 99.
       
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
       MOVE 5 TO our-index.
           MOVE 15 TO our-entry(6).

       END PROGRAM prog.    
