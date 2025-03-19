        *> This should NOT compile because the reference to MSG-1 is ambiguous

        *> GnuCOBOL throws

        *>    bob@doobie:~/repos/gcc-cobol/gcc/cobol/failures/ambiguous-data-name$ make gc
        *>    cobc -x -free -o gc ambiguous-data-name.cbl
        *>    ambiguous-data-name.cbl:15: error: 'MSG-1' is ambiguous; needs qualification
        *>    ambiguous-data-name.cbl:9: note: 'MSG-1' defined here
        *>    ambiguous-data-name.cbl:12: note: 'MSG-1 IN MESSAGES' defined here
        *>    make: *** [../Makefile.inc:54: gc] Error 1

        IDENTIFICATION DIVISION.
        PROGRAM-ID. ambiguous-data-name.

        DATA DIVISION.
        WORKING-STORAGE SECTION.

        01 MSG-1 PIC X(40) VALUE "You should never see me".

        01 MESSAGES.
            02 MSG-1 PIC X(40) VALUE "You shouldn; see me, either".

        PROCEDURE DIVISION.
            DISPLAY MSG-1.
            STOP RUN.
