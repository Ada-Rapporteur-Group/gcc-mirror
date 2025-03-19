       id division.
       program-id. dbgtest2.
      *>environment division.
      *>    source-computer. linux with debugging mode.
       procedure division.
       declaratives.
          debug-declaratives section.
             use for debugging on all procedures.
                display "in declarative debug".
          end declaratives.

       the_program section.
       paragraph1.
           display "paragraph1".

          display 'regular message'.
          goback.
      *>*** This program tries DECLARATIVES "use for debugging"
      *>*** Failure output
      *> cobol1: syntax error, dbgtest2.cbl line 6 at '.'
      *> cobol1: max errors 1 reached, dbgtest2.cbl line 6 at '.'
      *> cobol1: error: failed compiling dbgtest2.cbl
      *>*** Failure output
      *> When this comment block is at the head of the program:
      *> ***
      *> kb-linode:~/repos/gclog$ gcobol -o dbgtest2 dbgtest2.cbl
      *> cobol1: start condition INITIAL: scanner default rule on line 1
      *> ***
