       IDENTIFICATION DIVISION.

       PROGRAM-ID. prog.

       DATA DIVISION.

       WORKING-STORAGE SECTION.                                         
       77 our-string PIC X(5) value "12345".
       77 ref-mod    PIC X(2).
       77 our-number PIC 99 VALUE 2.    
      *> ref-mod like our-string(1:2) giving "12".
       
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
           MOVE our-string(5:our-number) TO ref-mod.

           END PROGRAM prog.
