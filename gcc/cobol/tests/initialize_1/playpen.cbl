        IDENTIFICATION DIVISION.
        PROGRAM-ID. PROG.
        DATA  DIVISION.
        WORKING-STORAGE SECTION.
        01 VAR1 PIC 999 DISPLAY.
        01 VAR2 PIC XXX.
        01 VAR3.
          02 V3N PIC 999 DISPLAY.
          02 V3A PIC XXX.

        01 VAR4.
          02 V4N PIC 999 DISPLAY VALUE 987.
          02 V4A PIC XXX.

        01 VAR5.
          02 V5N PIC 999 DISPLAY.
          02 V5A PIC XXX          VALUE "QRS".

        01 VAR6.
          02 V6N PIC 999 DISPLAY  VALUE  987 .
          02 V6A PIC XXX          VALUE "QRS".

        01 SHOULD_BE_N      PIC 999.
        01 SHOULD_BE_A      PIC XXX.
        01 SHOULD_BE_A6     PIC XXXXXX.

        PROCEDURE DIVISION.
            PERFORM TEST1.
            PERFORM TEST2.
            PERFORM TEST3.
            PERFORM TEST4.
            PERFORM TEST5.
            PERFORM TEST6.
            GOBACK.

        TEST6.
            DISPLAY "TEST6"
            MOVE 123456 TO VAR6
            MOVE 123456 TO SHOULD_BE_A6
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR6
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR6
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR6
            MOVE "000456 " TO SHOULD_BE_A6
            INITIALIZE V6N
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR6
            MOVE "123   " TO SHOULD_BE_A6
            INITIALIZE V6A
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR6
            MOVE "987QRS" TO SHOULD_BE_A6
            INITIALIZE VAR6 ALL VALUE
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR6
            MOVE "456abc" TO SHOULD_BE_A6
            INITIALIZE VAR6 REPLACING NUMERIC BY 456 ALPHANUMERIC BY "abc"
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR6
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR6 DEFAULT
            DISPLAY """" VAR6 """"  " should be " """" SHOULD_BE_A6 """".

        TEST5.
            DISPLAY "TEST5"
            MOVE 123456 TO VAR5
            MOVE 123456 TO SHOULD_BE_A6
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR5
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR5
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR5
            MOVE "000456 " TO SHOULD_BE_A6
            INITIALIZE V5N
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR5
            MOVE "123   " TO SHOULD_BE_A6
            INITIALIZE V5A
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR5
            MOVE "123QRS" TO SHOULD_BE_A6
            INITIALIZE VAR5 ALL VALUE
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR5
            MOVE "456abc" TO SHOULD_BE_A6
            INITIALIZE VAR5 REPLACING NUMERIC BY 456 ALPHANUMERIC BY "abc"
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR5
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR5 DEFAULT
            DISPLAY """" VAR5 """"  " should be " """" SHOULD_BE_A6 """".

        TEST4.
            DISPLAY "TEST4"
            MOVE 123456 TO VAR4
            MOVE 123456 TO SHOULD_BE_A6
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR4
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR4
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR4
            MOVE "000456 " TO SHOULD_BE_A6
            INITIALIZE V4N
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR4
            MOVE "123   " TO SHOULD_BE_A6
            INITIALIZE V4A
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR4
            MOVE 987456 TO SHOULD_BE_A6
            INITIALIZE VAR4 ALL VALUE
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR4
            MOVE "456abc" TO SHOULD_BE_A6
            INITIALIZE VAR4 REPLACING NUMERIC BY 456 ALPHANUMERIC BY "abc"
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR4
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR4 DEFAULT
            DISPLAY """" VAR4 """"  " should be " """" SHOULD_BE_A6 """".

        TEST3.
            DISPLAY "TEST3"
            MOVE 123456 TO VAR3
            MOVE 123456 TO SHOULD_BE_A6
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR3
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR3
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR3
            MOVE "123   " TO SHOULD_BE_A6
            INITIALIZE V3A
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR3
            MOVE "000456" TO SHOULD_BE_A6
            INITIALIZE V3N
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR3
            MOVE 123456 TO SHOULD_BE_A6
            INITIALIZE VAR3 ALL VALUE
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR3
            MOVE "456abc" TO SHOULD_BE_A6
            INITIALIZE VAR3 REPLACING NUMERIC BY 456 ALPHANUMERIC BY "abc"
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

            MOVE 123456 TO VAR3
            MOVE "000   " TO SHOULD_BE_A6
            INITIALIZE VAR3 DEFAULT
            DISPLAY """" VAR3 """"  " should be " """" SHOULD_BE_A6 """".

        TEST2.
            DISPLAY "TEST2"
            MOVE 123 TO VAR2
            MOVE 123 TO SHOULD_BE_A
            DISPLAY """" VAR2 """"  " should be " """" SHOULD_BE_A """"

            MOVE 123 TO VAR2
            MOVE SPACE TO SHOULD_BE_A
            INITIALIZE VAR2
            DISPLAY """" VAR2 """" " should be " """" SHOULD_BE_A """"

            MOVE 123 TO VAR2
            MOVE 123 TO SHOULD_BE_A
            INITIALIZE VAR2 ALL VALUE
            DISPLAY """" VAR2 """" " should be " """" SHOULD_BE_A """"

            MOVE 123 TO VAR2
            MOVE "abc" TO SHOULD_BE_A
            INITIALIZE VAR2 REPLACING NUMERIC BY 456 ALPHANUMERIC BY "abc"
            DISPLAY """" VAR2 """" " should be " """" SHOULD_BE_A """"

            MOVE 123 TO VAR2
            MOVE SPACE TO SHOULD_BE_A
            INITIALIZE VAR2 DEFAULT
            DISPLAY """" VAR2 """" " should be " """" SHOULD_BE_A """".

        TEST1.
            DISPLAY "TEST1"
            MOVE 123 TO VAR1
            MOVE 123 TO SHOULD_BE_N
            DISPLAY VAR1 " should be " SHOULD_BE_N

            MOVE 123 TO VAR1
            MOVE ZERO TO SHOULD_BE_N
            INITIALIZE VAR1
            DISPLAY VAR1 " should be " SHOULD_BE_N

            MOVE 123 TO VAR1
            MOVE 123 TO SHOULD_BE_N
            INITIALIZE VAR1 ALL VALUE
            DISPLAY VAR1 " should be " SHOULD_BE_N

            MOVE 123 TO VAR1
            MOVE 456 TO SHOULD_BE_N
            INITIALIZE VAR2 REPLACING NUMERIC BY 456 ALPHANUMERIC BY "abc"
            DISPLAY VAR1 " should be " SHOULD_BE_N

            MOVE 123 TO VAR1
            MOVE ZERO TO SHOULD_BE_N
            INITIALIZE VAR1 DEFAULT
            DISPLAY VAR1 " should be " SHOULD_BE_N.







      *>      MOVE "123456" TO VAR3
      *>      DISPLAY VAR3
      *>      INITIALIZE VAR3 ALL VALUE
      *>      DISPLAY VAR3
      *>      GOBACK.



      *>      DISPLAY VAR3.
      *>      INITIALIZE P1 ALL VALUE.
      *>      INITIALIZE P2 ALL VALUE.
      *>      INITIALIZE P3 ALL VALUE.
      *>      INITIALIZE P4 ALL VALUE.
      *>      INITIALIZE P5 ALL VALUE.
      *>      INITIALIZE P6 ALL VALUE.
      *>      DISPLAY VAR3.
      *>      GOBACK.


      *>      DISPLAY """" TABLE1 """"
      *>      INITIALIZE TABLE1
      *>      DISPLAY """" TABLE1 """"
      *>      INITIALIZE T1(4) ALL VALUE.
      *>      DISPLAY """" TABLE1 """"
      *>      GOBACK.

      *>      MOVE "THBBT!" TO TABLE2
      *>      DISPLAY """" TABLE2 """"
      *>      INITIALIZE TABLE2 ALL VALUE.
      *>      DISPLAY """" TABLE2 """"

      *>      DISPLAY """" TABLE2 """"
      *>      INITIALIZE TABLE2
      *>      DISPLAY """" TABLE2 """"
      *>      INITIALIZE T2(4) ALL VALUE.
      *>      DISPLAY """" TABLE2 """"
      *>      GOBACK.


      *>     MOVE 2015 TO WS-ASK-ID-DATE-YYYY
      *>     MOVE 08 TO WS-ASK-ID-DATE-MM
      *>     MOVE 21 TO WS-ASK-ID-DATE-DD
      *>     DISPLAY "THE DATE IS " WS-ASK-ID-DATE " COMPILED".
      *>
      *>     INITIALIZE WS-ASK-ID-DATE-R.
      *>     MOVE 08 TO WS-ASK-ID-DATE-MM
      *>     MOVE 21 TO WS-ASK-ID-DATE-DD
      *>     DISPLAY "THE DATE IS " WS-ASK-ID-DATE " INITIALIZE".
      *>
      *>     INITIALIZE WS-ASK-ID-DATE-R WITH FILLER.
      *>     MOVE 08 TO WS-ASK-ID-DATE-MM
      *>     MOVE 21 TO WS-ASK-ID-DATE-DD
      *>     DISPLAY "THE DATE IS " WS-ASK-ID-DATE " WITH FILLER".

      *>     INITIALIZE WS-ASK-ID-DATE-R WITH FILLER ALL TO VALUE.
      *>     MOVE 08 TO WS-ASK-ID-DATE-MM
      *>     MOVE 21 TO WS-ASK-ID-DATE-DD
      *>     DISPLAY "THE DATE IS " WS-ASK-ID-DATE " ALL TO VALUE".
           END PROGRAM PROG.
