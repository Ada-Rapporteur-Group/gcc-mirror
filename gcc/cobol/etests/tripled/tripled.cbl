        IDENTIFICATION DIVISION.
        PROGRAM-ID. tripled.

        DATA DIVISION.
        WORKING-STORAGE SECTION.

        01 StateSalesTable.
          02 StateSalesTotal  PIC 9(8)V99  OCCURS 50 TIMES.

        01 OurTable.
          10 OuterTable OCCURS 10 TIMES.
             20 MiddleTable OCCURS 10 TIMES.
                30 InnerTable OCCURS 10 TIMES.
                   40 Payload PIC 9999.

        01 i PIC 99.
        01 j PIC 99.
        01 k PIC 99.
        01 val PIC 9999 VALUE 0.

        PROCEDURE DIVISION.

        PERFORM   varying i from 1 by 1 until i > 10
          PERFORM   varying   j from 1 by 1 until j > 10
            PERFORM   varying   k from 1 by 1 until k > 10
              move val to Payload(  i, j, k )
              add 1 to val
              END-PERFORM
            END-PERFORM
          END-PERFORM

        PERFORM   varying i from 1 by 1 until i > 10
          DISPLAY OuterTable(i)
          PERFORM   varying   j from 1 by 1 until j > 10
            DISPLAY MiddleTable(i,j)
            PERFORM   varying   k from 1 by 1 until k > 10
              DISPLAY Payload( i j k ) " " with no advancing
              END-PERFORM
              display " "
            END-PERFORM
          END-PERFORM

        DISPLAY payload( 1 1 3 )
        DISPLAY payload( 1 1 4 )
        COMPUTE val = payload(1, 1, 3) + payload( 1 1 4 )
        DISPLAY val
        .
        END PROGRAM tripled.





