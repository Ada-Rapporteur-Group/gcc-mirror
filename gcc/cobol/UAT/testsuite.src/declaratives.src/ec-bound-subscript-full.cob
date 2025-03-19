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
           USE AFTER EXCEPTION CONDITION EC-BOUND-SUBSCRIPT.
              DISPLAY "DECLARATIVE FOR EC-BOUND-SUBSCRIPT".
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
       >>TURN EC-BOUND-SUBSCRIPT CHECKING ON
       DISPLAY "TURN EC-BOUND-SUBSCRIPT CHECKING ON".
           MOVE "12345" TO our-table(our-index).
                                                                        
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-BOUND CHECKING ON
       DISPLAY "TURN EC-BOUND CHECKING ON".    
           MOVE "12345" TO our-table(our-index).

       >>TURN EC-ALL CHECKING ON
       DISPLAY "TURN EC-ALL CHECKING ON".
           MOVE "12345" TO our-table(our-index).

       GOBACK.

