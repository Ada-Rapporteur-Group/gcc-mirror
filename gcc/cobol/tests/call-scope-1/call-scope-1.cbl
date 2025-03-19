        IDENTIFICATION DIVISION.
        PROGRAM-ID.  program-aaa.
        PROCEDURE DIVISION.
        DISPLAY "program-aaa calls nested program program-b1"
        CALL "program-b1"
        DISPLAY "program-aaa calls nested program program-b2"
        CALL "program-b2"
        DISPLAY "program-aaa calls nested program program-b3"
        CALL "program-b3"
        CALL "common-test"
        GOBACK.
            IDENTIFICATION DIVISION.
            PROGRAM-ID.  program-b1.
            PROCEDURE DIVISION.
            DISPLAY "   program-b1 calls its nested program-c"
            CALL "program-c"
            GOBACK.
                IDENTIFICATION DIVISION.
                PROGRAM-ID.  program-c.
                PROCEDURE DIVISION.
                DISPLAY "      Hello from b1's program-c"
                GOBACK.
                END PROGRAM program-c.
            END PROGRAM program-b1.

            IDENTIFICATION DIVISION.
            PROGRAM-ID.  program-b2.
            PROCEDURE DIVISION.
            DISPLAY "   program-b2 calls its nested program-c"
            CALL "program-c"
            GOBACK.
                IDENTIFICATION DIVISION.
                PROGRAM-ID.  program-c.
                PROCEDURE DIVISION.
                DISPLAY "      Hello from b2's program-c"
                GOBACK.
                END PROGRAM program-c.
            END PROGRAM program-b2.

            IDENTIFICATION DIVISION.
            PROGRAM-ID.  program-b3.
            PROCEDURE DIVISION.
            DISPLAY "   program-b2 calls its nested program-c"
            CALL "program-c"
            GOBACK.
                IDENTIFICATION DIVISION.
                PROGRAM-ID.  program-c.
                PROCEDURE DIVISION.
                DISPLAY "      Hello from b3's program-c"
                GOBACK.
                END PROGRAM program-c.
            END PROGRAM program-b3.

        IDENTIFICATION DIVISION.
        PROGRAM-ID.  common-test.
        PROCEDURE DIVISION.
        DISPLAY "This is common-test"
        CALL "common-level-1B"
        GOBACK.

        IDENTIFICATION DIVISION.
        PROGRAM-ID.  common-level-1A.
        PROCEDURE DIVISION.
        DISPLAY "This is common-level-1A"
        GOBACK.
        END PROGRAM common-level-1A.

        IDENTIFICATION DIVISION.
        PROGRAM-ID.  common-level-1B IS COMMON.
        PROCEDURE DIVISION.
        DISPLAY "This is common-level-1B"
        CALL "common-level-2B"
        GOBACK.

            IDENTIFICATION DIVISION.
            PROGRAM-ID.  common-level-2A IS COMMON.
            PROCEDURE DIVISION.
            DISPLAY "This is common-level-2A"
            GOBACK.
            END PROGRAM common-level-2A.

            IDENTIFICATION DIVISION.
            PROGRAM-ID.  common-level-2B.
            PROCEDURE DIVISION.
            DISPLAY "This is common-level-2B"
            CALL "common-level-3B"
            GOBACK.
                IDENTIFICATION DIVISION.
                PROGRAM-ID.  common-level-3A.
                PROCEDURE DIVISION.
                DISPLAY "This is common-level-3A"
                GOBACK.
                END PROGRAM common-level-3A.

                IDENTIFICATION DIVISION.
                PROGRAM-ID.  common-level-3B.
                PROCEDURE DIVISION.
                DISPLAY "This is common-level-3B"

        >>IF OLD-WAY IS DEFINED
                CALL "common-level-1A"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-1A".
                CALL "common-level-1B"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-1B".
                CALL "common-level-1C"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-1C".

                CALL "common-level-2A"
                ON EXCEPTION DISPLAY "Improperly couldn't call common-level-2A".
                CALL "common-level-2B"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-2B".
                CALL "common-level-2C"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-2C".

                CALL "common-level-3A"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-3A".
                CALL "common-level-3B"
                ON EXCEPTION DISPLAY "  Properly couldn't call common-level-3B".
                CALL "common-level-3C"
                ON EXCEPTION DISPLAY "Improperly couldn't call common-level-3C".
        >>ELSE
                CALL "common-level-2A"
                ON EXCEPTION DISPLAY "3B Improperly couldn't call common-level-2A".
                CALL "common-level-3C"
                ON EXCEPTION DISPLAY "3B Improperly couldn't call common-level-3C".
        >>END-IF
                GOBACK.
                END PROGRAM common-level-3B.

                IDENTIFICATION DIVISION.
                PROGRAM-ID.  common-level-3C IS COMMON.
                PROCEDURE DIVISION.
                DISPLAY "This is common-level-3C"
                GOBACK.
                END PROGRAM common-level-3C.

            END PROGRAM common-level-2B.

            IDENTIFICATION DIVISION.
            PROGRAM-ID.  common-level-2C.
            PROCEDURE DIVISION.
            DISPLAY "This is common-level-2C"
            GOBACK.
            END PROGRAM common-level-2C.
        END PROGRAM common-level-1B.

        IDENTIFICATION DIVISION.
        PROGRAM-ID.  common-level-1C.
        PROCEDURE DIVISION.
        DISPLAY "This is common-level-1C"
        GOBACK.
        END PROGRAM common-level-1C.

        END PROGRAM common-test.

        END PROGRAM program-aaa.
