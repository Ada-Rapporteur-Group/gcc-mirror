       IDENTIFICATION DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.
       WORKING-STORAGE SECTION.                                         
       01  a     COMP-1 VALUE 1.E20.
       01  b     COMP-1 VALUE 1.E20.
       
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
           MULTIPLY a BY b GIVING b.
           END PROGRAM prog.
