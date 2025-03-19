        ID DIVISION.
        PROGRAM-ID. playpen.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 dummy pic x.
        01 level pic 99 value 0.

        PROCEDURE DIVISION.
            display level "    About to start...".
            add 1 to level
            perform a through z.
            subtract 1 from level
            display level "        back from a through z".
            STOP RUN.

        a.
            display level " I am a"
            add 1 to level
            perform b through z
            subtract 1 from level
            display level
                        "    back from b through z; fall through to b".
        b.
            display level " I am b"
            add 1 to level
            perform c through z
            subtract 1 from level
            display level
                        "    back from c through z; fall through to c".
        c.
            display level " I am c"
            add 1 to level
            perform d through z.
            subtract 1 from level
            display level
                        "    back from d through z; fall through to d".
        d.
            display level " I am d"
            display level
                        "                           fall through to z".
        z.
            display level " I am z".
        zzz.
            display level " I am zzz".

        END PROGRAM playpen.





