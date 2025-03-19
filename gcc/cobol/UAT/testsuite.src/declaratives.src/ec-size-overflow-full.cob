       IDENTIFICATION DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.
       WORKING-STORAGE SECTION.                                         
       01  a     COMP-1 VALUE 1.E20.
       01  b     COMP-1 VALUE 1.E20.
       PROCEDURE DIVISION.                                              
       DECLARATIVES.
       DECLARATIVE-1 SECTION.
           USE AFTER EXCEPTION CONDITION EC-SIZE-OVERFLOW.
              DISPLAY "DECLARATIVE FOR EC-SIZE-OVERFLOW".
              RESUME NEXT STATEMENT.
       DECLARATIVE-2 SECTION.
           USE AFTER EXCEPTION CONDITION EC-SIZE.
              DISPLAY "DECLARATIVE FOR EC-SIZE".
              RESUME NEXT STATEMENT.
       DECLARATIVE-3 SECTION.
           USE AFTER EXCEPTION CONDITION EC-ALL.
              DISPLAY "DECLARATIVE FOR EC-ALL".
              RESUME NEXT STATEMENT.
           END DECLARATIVES.

       MAIN-SECTION SECTION.    
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-SIZE-OVERFLOW CHECKING ON
       DISPLAY "TURN EC-SIZE-OVERFLOW CHECKING ON".
            move 1.e20 to a b
            MULTIPLY a BY b GIVING b
                                                                        
       >>TURN EC-ALL CHECKING OFF    
       >>TURN EC-SIZE CHECKING ON
       DISPLAY "TURN EC-SIZE CHECKING ON".    
            move 1.e20 to a b
            MULTIPLY a BY b GIVING b

       >>TURN EC-ALL CHECKING ON
       DISPLAY "TURN EC-ALL CHECKING ON".
            move 1.e20 to a b
            MULTIPLY a BY b GIVING b.

       GOBACK.

