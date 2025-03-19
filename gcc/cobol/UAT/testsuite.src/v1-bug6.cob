       ID DIVISION.
       PROGRAM-ID. prog.
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       77 var-1 PIC X(10) VALUE SPACE.
       77 var-2 pic x(10) value " 1".
       77 var-3 pic x(20) value space.
       77 tf PIC X(4) VALUE SPACE.
       77 num-1 PIC 999.99 VALUE 122.3.
       PROCEDURE DIVISION.
       STRING-1.
          STRING "hello","world" INTO var-1.
          IF "helloworld" NOT = var-1
              DISPLAY "Expected ""helloworld"", Got """
                  var-1 """"
              MOVE 1 TO return-code
              END-IF.
       STRING-2.
          STRING "hello world" DELIMITED BY " " INTO var-1.
          IF "hello" NOT = var-1 THEN
              DISPLAY "Expected ""hello"", Got """
                  var-1 """"
              MOVE 1 TO return-code
              END-IF.
       STRING-3.
          STRING "hello world" INTO var-1.
          IF "hello world" NOT = var-1 THEN
              DISPLAY "Expected ""hello world"", Got """
                  var-1 """"
               MOVE 1 TO RETURN-CODE
               END-IF.
       STRING-3.
          STRING num-1 INTO var-1.
           IF var-1(1:1) = "+" THEN
             MOVE var-1(2:) TO var-1
             DISPLAY var-1
             END-IF.
           IF "122.3" NOT = var-1 THEN
               DISPLAY "Expected ""122.3"", Got """
                  var-1 """"
               MOVE 1 TO RETURN-CODE
               END-IF.
       STRING-4.
          MOVE "testing" TO var-1.
          STRING "testing",var-2 INTO var-3.
          IF "testing 1" not = var-3
               DISPLAY "Expected ""testing 1"", Got """
                  var-3 """"
               MOVE 1 TO RETURN-CODE
               END-IF.
       STRING-5.
          STRING var-1," 1" INTO var-3.
             IF "testing    1" NOT = var-3
               DISPLAY "Expected ""testing    1"", Got """
                  var-3 """"
               MOVE 1 TO RETURN-CODE
               END-IF.
       STRING-6.
          STRING SPACE, var-1 INTO var-2.
             IF " testing   " not = var-2
               DISPLAY "Expected "" testing   "", Got """
                  var-3 """"
               MOVE 1 TO RETURN-CODE
               END-IF.
       STRING-7.
          STRING "" INTO var-1.
          IF var-1 NOT = SPACE
             DISPLAY "Expected SPACE, Got """ var-3 """"
             MOVE 1 TO RETURN-CODE
             END-IF.
       STRING-8.
          STRING SPACE, var-1 DELIMITED by "i" INTO var-2.
          IF " test" not = var-3
             DISPLAY "Expected "" test"", Got """ var-3 """"
             MOVE 1 TO RETURN-CODE
             END-IF.
       STRING-9.
          STRING 'hello world & thanks for all the fishes' INTO var-3.
           IF var-3 NOT = "hello world & thanks" THEN
              DISPLAY "Expected "" test world & thanks"", Got """
                     var-3 """"
              MOVE 1 TO RETURN-CODE
              END-IF.
       STRING-10.
          STRING "hello world" delimited by "w" INTO var-3.
          IF var-3 NOT = "hello " THEN
              DISPLAY "Expected ""hello "", Got """
                     var-3 """"
              MOVE 1 TO RETURN-CODE
              END-IF.
       STRING-11.
          STRING "hello world" INTO var-1
              ON OVERFLOW MOVE "OVER" TO tf.
          IF "OVER" NOT = tf THEN
              DISPLAY "Expected tf = ""OVER"", Got """
                     tf  """"
              MOVE 1 TO RETURN-CODE
              END-IF.
       STRING-12.
          STRING "hello" INTO var-1
              NOT ON OVERFLOW MOVE "NOPE" TO tf.
          IF "NOPE" NOT = tf THEN
              DISPLAY "Expected tf = ""NOPE"", Got """
                     tf  """"
              MOVE 1 TO RETURN-CODE
              END-IF.
       GOBACK.
       END PROGRAM prog.

      *----------------------------
      * Notes for STRING-FAIL.cob
      *ID DIVISIOn.
      *PROGRAM-ID. prog.
      *DATA DIVISION.
      *WORKING-STORAGE SECTION.
      *   77 var-1 PIC X(20) VALUE SPACE.
      *PROCEDURE DIVISION.
      *> INVALID. Numberic literal not allowed in STRING statement
      *> SUCCEEDS with compiler error
      *> BUT "syntax error" no useful message -- TODO
      *STRING 10 INTO var-1.
      *    STRING "hello world" INTO "just kidding".

