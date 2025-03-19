        identification division.
        program-id. dubner.
        data division.
        working-storage section.

        procedure division.
        display "The hijacked code has ended"

        call "aaa"
        call "bbb"
        call "ccc"

        stop run.
        end program dubner.

      *>
        identification division.
        program-id. aaa.
        data division.
        working-storage section.
        procedure division.
        display "This is program aaa"
        call "aaa_1"
        goback.
            identification division.
            program-id. aaa_1.
            data division.
            working-storage section.
            procedure division.
            display "This is program aaa_1"
            goback.
            end program aaa_1.
        end program aaa.

        identification division.
        program-id. bbb.
        data division.
        working-storage section.
        procedure division.
        display "This is program bbb"
        call "bbb_1"
        goback.
            identification division.
            program-id. bbb_1.
            data division.
            working-storage section.
            procedure division.
            display "This is program bbb_1"
            goback.
            end program bbb_1.
        end program bbb.

        identification division.
        program-id. ccc.
        data division.
        working-storage section.
        procedure division.
        display "This is program ccc"
        call "ccc_1"
        goback.
            identification division.
            program-id. ccc_1.
            data division.
            working-storage section.
            procedure division.
            display "This is program ccc_1"
            goback.
            end program ccc_1.
        end program ccc.

        identification division.
        program-id. ddd.
        data division.
        working-storage section.

        procedure division.
        display "This is program ddd"
        call "dddddd_1"
        goback.
            identification division.
            program-id. dddddd_1.
            data division.
            working-storage section.
            procedure division.
            display "This is program dddddd_1"
            goback.
            end program dddddd_1.
        end program ddd.

