      *> The error is on line 26, which should generate a syntax error.
      *> That redefines in  is reaching back into a-message.  That
      *> should not be possible.

        IDENTIFICATION DIVISION.
        PROGRAM-ID. test.

        DATA DIVISION.
        WORKING-STORAGE SECTION.

        01 for-numval.
            02 numval-list-values.
                03 FILLER pic X(24) value "  123.4      ".
                03 FILLER pic X(24) value "  +  123.4   ".
                03 FILLER pic X(24) value "+123.4".
                03 FILLER pic X(24) value "  123.4  +   ".
            02 FILLER redefines numval-list-values.
                03 numval-list pic X(24) OCCURS 4 times.

        01 for-numval-c.
            02 numval-c-list-values.
                03 FILLER pic X(24) value "$  123.4      ".
                03 FILLER pic X(24) value "$  +  123.4   ".
                03 FILLER pic X(24) value "$+123.4".
                03 FILLER pic X(24) value "$  123.4  +   ".
            02 FILLER redefines numval-list-values.
                03 numval-c-list pic X(24) OCCURS 4 times.

        PROCEDURE DIVISION.

        DISPLAY "The following line should be ""$+123.4"""
        DISPLAY numval-c-list(3) .

        END PROGRAM test.

