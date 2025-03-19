        IDENTIFICATION DIVISION.
        PROGRAM-ID. performs.

        *> This routine exercises inline and outofline
        *>
        *>  PERFORM
        *>  PERFORM UNTIL
        *>  PERFORM VARYING
        *>
        *> with both TEST BEFORE and TEST AFTER


        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01  counter  PIC 9.
        01  five     PIC 9 VALUE 5.

        01  DISPLAY_LINE PIC X(132).
        01  LOOPS    PIC 999999 VALUE 1.

        PROCEDURE DIVISION.
        BeginProgram.
        PERFORM LOOPS TIMES
            MOVE "Perform paragraph-AAA once" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA
            MOVE "Perform paragraph-AAA 3 times" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA 3 TIMES

            MOVE "Perform paragraph-BBB THROUGH paragraph-CCC once" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-BBB THROUGH PARAGRAPH-CCC

            MOVE "Perform paragraph-BBB THROUGH paragraph-CCC 3 TIMES" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-BBB THROUGH PARAGRAPH-CCC 3 TIMES

            MOVE "Trying (counter=0) PERFORM BUMP-COUNTER UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 to counter
            PERFORM BUMP-COUNTER UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=0) PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 to counter
            PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=0) PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 to counter
            PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=5) PERFORM BUMP-COUNTER UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 to counter
            PERFORM BUMP-COUNTER UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=5) PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 to counter
            PERFORM BUMP-COUNTER TEST BEFORE UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=5) PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 to counter
            PERFORM BUMP-COUNTER WITH TEST BEFORE UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "PERFORM proc (testing after, start at 0) UNTIL" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE "Trying (counter=0) PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 to counter
            PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=0) PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 to counter
            PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=5) PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 to counter
            PERFORM BUMP-COUNTER TEST AFTER UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (counter=5) PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 to counter
            PERFORM BUMP-COUNTER WITH TEST AFTER UNTIL counter >= 5
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM PARAGRAPH-AAA VARYING counter FROM 0 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA VARYING counter FROM 0 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM PARAGRAPH-AAA VARYING counter FROM 5 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA VARYING counter FROM 5 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3

            MOVE "Trying PERFORM paragraph-AAA WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM PARAGRAPH-AAA WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 3

            MOVE "Trying (count = 0) PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 TO counter
            PERFORM UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (count = 0) TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 TO counter
            PERFORM TEST BEFORE UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (count = 0) WITH TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 TO counter
            PERFORM WITH TEST BEFORE UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (count = 5) PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 TO counter
            PERFORM UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM

            MOVE "Trying (count = 5) TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 TO counter
            PERFORM TEST BEFORE UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM

            MOVE "Trying (count = 5) WITH TEST BEFORE PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 TO counter
            PERFORM WITH TEST BEFORE UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM


            MOVE "Trying (count = 0) TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 TO counter
            PERFORM TEST AFTER UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (count = 0) WITH TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 TO counter
            PERFORM WITH TEST AFTER UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (count = 5) TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 TO counter
            PERFORM TEST AFTER UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying (count = 5) WITH TEST AFTER PERFORM <counter += 1> UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 5 TO counter
            PERFORM WITH TEST AFTER UNTIL counter >= 5
                PERFORM DISP_COUNT
                ADD 1 TO COUNTER
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER VARYING counter FROM 0 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER VARYING counter FROM 5 BY 1 UNTIL counter >= five

            MOVE "Trying PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= five

            MOVE "Trying PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= five

            MOVE "Trying PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM BUMP-COUNTER WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= five
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM VARYING counter FROM 0 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM VARYING counter FROM 5 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM

            MOVE "Trying PERFORM TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM

            MOVE "Trying PERFORM WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM WITH TEST BEFORE VARYING counter FROM 5 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM

            MOVE "Trying PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM WITH TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM WITH TEST AFTER VARYING counter FROM 5 BY 1 UNTIL counter >= 5
                PERFORM DISP_COUNT
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Trying PERFORM 5 TIMES" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM 5 TIMES
                PERFORM DISP_COUNT
                ADD 1 to COUNTER
                END-PERFORM
            PERFORM DISPLAY_SPACE

            MOVE "PERFORM 10 TIMES; Skip 4, end at 7" TO DISPLAY_LINE PERFORM DISP_LINE
            MOVE 0 to COUNTER
            PERFORM 10 TIMES
                ADD 1 to COUNTER
                IF COUNTER EQUAL 4
                    EXIT PERFORM CYCLE
                    END-IF
                PERFORM DISP_COUNT
                IF COUNTER EQUAL 7
                    EXIT PERFORM
                    END-IF
                END-PERFORM
            PERFORM DISPLAY_SPACE

            MOVE "PERFORM TEST AFTER VARYING; skip 4, end at 7" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM TEST AFTER VARYING counter FROM 0 BY 1 UNTIL counter >= 10
                IF COUNTER EQUAL 4
                    EXIT PERFORM CYCLE
                    END-IF
                PERFORM DISP_COUNT
                IF COUNTER EQUAL 7
                    EXIT PERFORM
                    END-IF
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "PERFORM WITH TEST BEFORE VARYING; skip 4, end at 7" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM WITH TEST BEFORE VARYING counter FROM 0 BY 1 UNTIL counter >= 10
                IF COUNTER EQUAL 4
                    EXIT PERFORM CYCLE
                    END-IF
                PERFORM DISP_COUNT
                IF COUNTER EQUAL 7
                    EXIT PERFORM
                    END-IF
                END-PERFORM
            MOVE " " TO DISPLAY_LINE PERFORM DISP_LINE

            MOVE "Testing EXIT PARAGRAPH..." TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM TEST-EXIT-PARAGRAPH

            MOVE "Testing EXIT SECTION..." TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM ANOTHER-SECTION
            PERFORM DISPLAY_SPACE

            PERFORM AAA OF SEC2
            MOVE "Should have been 'AAA of SEC2'" TO DISPLAY_LINE PERFORM DISP_LINE
            PERFORM AAA OF SEC1
            MOVE "Should have been 'AAA of SEC1'" TO DISPLAY_LINE PERFORM DISP_LINE

        END-PERFORM

            MOVE "Duplicated pass-through 1" TO DISPLAY_LINE PERFORM DISP_LINE.
            DUPLICATED.
            MOVE "Duplicated pass-through 2" TO DISPLAY_LINE PERFORM DISP_LINE.
            DUPLICATED.
            MOVE "Duplicated pass-through 3" TO DISPLAY_LINE PERFORM DISP_LINE.

            STOP RUN.

        PARAGRAPH-AAA.
            MOVE "      I am paragraph_AAA" TO DISPLAY_LINE PERFORM DISP_LINE.

        PARAGRAPH-BBB.
            MOVE "      I am paragraph_BBB" TO DISPLAY_LINE PERFORM DISP_LINE.

        PARAGRAPH-CCC.
            MOVE "      I am paragraph_CCC" TO DISPLAY_LINE PERFORM DISP_LINE.

        PARAGRAPH-DDD.
            MOVE "      I am paragraph_DDD" TO DISPLAY_LINE PERFORM DISP_LINE.

        BUMP-COUNTER.
            PERFORM DISP_COUNT
            ADD 1 TO counter.

        NOBUMP-COUNTER.
            PERFORM DISP_COUNT.

        TEST-EXIT-PARAGRAPH.
            MOVE "Now you see me..." TO DISPLAY_LINE PERFORM DISP_LINE
            EXIT PARAGRAPH
            MOVE "And now you shouldn't" TO DISPLAY_LINE PERFORM DISP_LINE.

        ANOTHER-SECTION SECTION.
        PARAGRAPH-AAA2.
            MOVE "PARAGRAPH-AAA2" TO DISPLAY_LINE PERFORM DISP_LINE.
        PARAGRAPH-BBB2.
            MOVE "PARAGRAPH-BBB2" TO DISPLAY_LINE PERFORM DISP_LINE.
            EXIT PARAGRAPH
            MOVE "PARAGRAPH-BBB2, but this is an error" TO DISPLAY_LINE PERFORM DISP_LINE.
        PARAGRAPH-CCC2.
            MOVE "PARAGRAPH-CCC2" TO DISPLAY_LINE PERFORM DISP_LINE.
            EXIT SECTION.
            MOVE "PARAGRAPH-CCC2, but this is an error" TO DISPLAY_LINE PERFORM DISP_LINE.
        PARAGRAPH-DDD2.
            MOVE "PARAGRAPH-DDD2, but we should never get here." TO DISPLAY_LINE PERFORM DISP_LINE.

        SEC1 SECTION.
        AAA.
            MOVE "                  AAA OF SEC1" TO DISPLAY_LINE PERFORM DISP_LINE.
        SEC2 SECTION.
        AAA.
            MOVE "                  AAA OF SEC2" TO DISPLAY_LINE PERFORM DISP_LINE.

        DISP_LINE.
            IF LOOPS IS EQUAL TO 1
                DISPLAY DISPLAY_LINE
                END-IF.

        DISP_COUNT.
            IF LOOPS IS EQUAL TO 1
                DISPLAY COUNTER " " WITH NO ADVANCING
                END-IF.

        DISPLAY_SPACE.
            IF LOOPS IS EQUAL TO 1
                DISPLAY SPACE
                END-IF.

        END PROGRAM performs.
