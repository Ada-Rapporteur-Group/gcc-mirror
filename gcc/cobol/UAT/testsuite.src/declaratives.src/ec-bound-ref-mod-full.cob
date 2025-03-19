       IDENTIFICATION DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.
       WORKING-STORAGE SECTION.                                         
       77 our-string PIC X(5) value "12345".
       77 ref-mod    PIC X(2).
       77 our-number PIC 99 VALUE 2.    
       
       PROCEDURE DIVISION.                                              
       DECLARATIVES.
       DECLARATIVE-1 SECTION.
           USE AFTER EXCEPTION CONDITION EC-BOUND-REF-MOD.
              DISPLAY "DECLARATIVE FOR EC-BOUND-REF-MOD".
              RESUME NEXT STATEMENT.
       DECLARATIVE-2 SECTION.
           USE AFTER EXCEPTION CONDITION EC-BOUND.
              RESUME NEXT STATEMENT.
              DISPLAY "DECLARATIVE FOR EC-BOUND".
       DECLARATIVE-3 SECTION.
           USE AFTER EXCEPTION CONDITION EC-ALL.
              DISPLAY "DECLARATIVE FOR EC-ALL".
              RESUME NEXT STATEMENT.
           END DECLARATIVES.

       MAIN-SECTION SECTION.    
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-BOUND-REF-MOD CHECKING ON
       DISPLAY "TURN EC-BOUND-REF-MOD CHECKING ON".
           MOVE our-string(5:our-number) TO ref-mod.
           
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-BOUND CHECKING ON
       DISPLAY "TURN EC-BOUND CHECKING ON".    
           MOVE our-string(5:our-number) TO ref-mod.

       >>TURN EC-ALL CHECKING ON
       DISPLAY "TURN EC-ALL CHECKING ON".    
           MOVE our-string(5:our-number) TO ref-mod.

       GOBACK.

       TEST1. 
           MOVE our-string(5:our-number) TO ref-mod.
