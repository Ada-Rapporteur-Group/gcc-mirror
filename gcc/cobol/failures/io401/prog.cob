
       IDENTIFICATION DIVISION.
       PROGRAM-ID. prog.
       PROCEDURE DIVISION.
       CALL "prog2" ON EXCEPTION DISPLAY "Couldn't find 'prog2'".
       end program prog.
