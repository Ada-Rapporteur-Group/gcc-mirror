        identification      division.
        program-id.         prog.
        data                division.
        working-storage     section.
        77 a                pic 9.
        77 b                pic 9.
        77 c                pic 9.
        procedure division.
        *> Fails when perform 2 times; works when perform 3 times
        perform 3 times
            display "One fish"
            end-perform
        *> Doesn't work if this section is first
        *> display "a b c"
        perform dumper varying a from 1 by 1 until a = 3
                  after b from 1 by 1 until b = 3
                  after c from 1 by 1 until c = 3
        display "3 times"
        perform 3 times
            display "One fish"
            end-perform
        display "3 times"
        goback.
        dumper.
        display a space b space c.
        end program         prog.
