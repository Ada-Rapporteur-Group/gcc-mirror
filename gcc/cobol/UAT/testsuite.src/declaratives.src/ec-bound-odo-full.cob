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
           USE AFTER EXCEPTION CONDITION EC-BOUND-ODO.
              DISPLAY "DECLARATIVE FOR EC-BOUND-ODO".
              RESUME NEXT STATEMENT.
       DECLARATIVE-2 SECTION.
           USE AFTER EXCEPTION CONDITION EC-BOUND.
              DISPLAY "DECLARATIVE FOR EC-BOUND".
              RESUME NEXT STATEMENT.
       DECLARATIVE-3 SECTION.
           USE AFTER EXCEPTION CONDITION EC-ALL.
              DISPLAY "DECLARATIVE FOR EC-ALL".
              RESUME NEXT STATEMENT.
           END DECLARATIVES.
       MAIN-SECTION SECTION.    
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-BOUND-ODO CHECKING ON
       DISPLAY "TURN EC-BOUND-ODO CHECKING ON".
       MOVE 5 TO our-index.
           MOVE 15 TO our-entry(6).
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-BOUND CHECKING ON
       DISPLAY "TURN EC-BOUND CHECKING ON".    
       MOVE 5 TO our-index.
           MOVE 15 TO our-entry(6).
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-ALL CHECKING ON
       DISPLAY "TURN EC-ALL CHECKING ON".    
       MOVE 5 TO our-index.
           MOVE 15 TO our-entry(6).
       goback.
