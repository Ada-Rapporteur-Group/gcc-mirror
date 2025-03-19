        identification          division.
        program-id.             prog.
        data                    division.
        working-storage         section.
        77 fib-a pic 9(32)      packed-decimal.
        77 fib-b pic 9(32)      packed-decimal.
        77 fib-c pic 9(32)      packed-decimal.
        77 fib-limit pic 9(32)  packed-decimal.
        77 loops                binary-long.
        77 time-start pic 99999v9(9) comp-5.
        77 time-end   pic 99999v9(9) comp-5.
        77 time-limit pic 99999v9(9) comp-5 value 10.
        77 time-elapsed pic 99999v9(9) comp-5.
        procedure               division.
            move 0 to loops
            move 1000000000000000000000000000000 to fib-limit
            move function seconds-past-midnight to time-start.
        outer-loop.
            add  1 to loops
            move loops to fib-a
            move 1 to fib-b.
        inner-loop.
            add  fib-a to fib-b giving fib-c
            move fib-b to fib-a
            move fib-c to fib-b
            if fib-c < fib-limit then 
                go to inner-loop
                end-if
            move function seconds-past-midnight to time-end
            subtract time-start from time-end giving time-elapsed
            if time-elapsed < time-limit then
                go to outer-loop
                end-if
            display "Loops ended up at " loops " in " time-elapsed " seconds".
        end program             prog.
