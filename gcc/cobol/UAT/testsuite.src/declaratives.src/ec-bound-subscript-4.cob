       IDENTIFICATION DIVISION.

       PROGRAM-ID. prog.

       DATA DIVISION.

       WORKING-STORAGE SECTION.                                         
       01 OUR-RECORD.
           05 our-table  OCCURS 4 TIMES PIC X(5).
       01 our-index pic 99 value 6.
       
       PROCEDURE DIVISION.                                              
       PERFORM TEST1.

       GOBACK.

       TEST1. 
           MOVE "12345" TO our-table(our-index).

           END PROGRAM prog.
