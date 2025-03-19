       IDENTIFICATION DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.
       WORKING-STORAGE SECTION.                                         
       01  a     COMP-1 VALUE 1.E20.
       01  b     COMP-1 VALUE 1.E20.
       
       PROCEDURE DIVISION.                                              
       DECLARATIVES.
       DECLARATIVE-1 SECTION.
           USE AFTER EXCEPTION CONDITION EC-SIZE.
              DISPLAY "DECLARATIVE FOR EC-SIZE".
           GOBACK.           
       END DECLARATIVES.

       MAIN-SECTION SECTION.    
       DISPLAY "TURN EC-SIZE CHECKING ON".
       >>TURN EC-SIZE CHECKING ON
       PERFORM TEST1.
       GOBACK.

       TEST1. 
           MULTIPLY a BY b GIVING b.
           END PROGRAM prog.
