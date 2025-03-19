       IDENTIFICATION DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.

       WORKING-STORAGE SECTION.                                         
       01  a     COMP-1 VALUE 1.E20.
       01  b     COMP-1 VALUE 1.E20.
       
       PROCEDURE DIVISION.                                              
       PERFORM TEST1.
       GOBACK.

       TEST1. 
           MULTIPLY a BY b GIVING b.
           END PROGRAM prog.
