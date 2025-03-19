        *> The PERFORM NO-MANS-LAND at line 29 should find the same section's
        *> paragraph at line 23.  The proper output should be

        *>   This is the first message.
        *>   This is the second message.
        *>   This is the third message.
        *>   The next message should be the fourth message
        *>   This is the fourth message.

        IDENTIFICATION DIVISION.
        PROGRAM-ID. ambiguous_label.

        PROCEDURE DIVISION.
           NO-MANS-LAND.
               DISPLAY "This is the first message.".

           NO-MANS-LAND.
               DISPLAY "This is the second message.".

           NO-MAN-IS-AN-ISLAND SECTION.
              GO TO KNOCK-KNOCK.

              NO-MANS-LAND.
                  DISPLAY "This is the fourth message.".

              KNOCK-KNOCK.
                 DISPLAY "This is the third message."
                 DISPLAY "The next message should be the fourth message"
                 PERFORM NO-MANS-LAND.

            STOP RUN.
