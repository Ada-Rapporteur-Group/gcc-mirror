        identification          division.
        program-id.             prog.
        data                    division.
        working-storage         section.
        77 time-start pic 99999v9(9) comp-5.
        77 time-end   pic 99999v9(9) comp-5.
        77 time-limit pic 99999v9(9) comp-5 value 10.
        77 time-elapsed pic 99999v9(9) comp-5.
        77 loops                binary-double.
        77 counter              binary-double.
        77 aaa picture 9(32) packed-decimal value 123456789.
        77 bbb picture 9(32) display        value 123456789.
        77 ccc picture 9(32) packed-decimal.
        77 ddd picture 9(32) packed-decimal.
        77 loop-ne picture zzz,zzz,zzz,zz9.
        *> Loop overhead:
        *> Each of 1,000,000,000 loops required 00000.334703972 nanoseconds
        *>
        *> add aaa to bbb giving ccc:
        *> Each of 20,000,000 loops required 00194.751810150 nanoseconds
        *>
        *> With get_binary_value_local returning a fixed 123456789
        *> Each of 20,000,000 loops required 00099.708297350 nanoseconds
        *>
        *> With int128_to_field code for packed-decimal commented out:
        *> Each of 20,000,000 loops required 00031.181542750 nanoseconds
        procedure               division.
            move 0 to counter
            move 20000000 to loops
            move function seconds-past-midnight to time-start.
            perform loops times
                add aaa to bbb giving ccc
                add ccc to ddd
                end-perform
            move function seconds-past-midnight to time-end
            subtract time-start from time-end giving time-elapsed
            display ddd
            multiply 1000000000 by time-elapsed 
            divide time-elapsed by loops giving time-elapsed
            move loops to loop-ne
            display "Each of " function trim(loop-ne) " loops required " time-elapsed " nanoseconds".
        end program             prog.
