      *> This should generate a syntax error, because the variable-length
      *> nums() table can't have anything following it.

        identification division.
        program-id. depends.

        data division.
        working-storage section.
        77 i pic 99.
        77 num-length   pic 99 value 10.
        77 init-string pic X(10) VALUE "ABCDEFGHIJ".

        01 tables.
            05 nums pic 9 occurs 1 to 10 times
                    depending on num-length.
            05 chr  pic x.

        procedure division.
        perform init-tables.

        display tables.
        move 5 to num-length
        display tables
        display nums(3)
        stop run.

        init-tables.
        perform varying i from 1 by 1 until i>10
            move i to nums(i)
            end-perform.
