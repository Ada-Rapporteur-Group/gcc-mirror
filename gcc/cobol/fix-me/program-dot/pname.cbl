        *> According to IBM page 82, the dots after PROGRAM-ID
        *> and pname are optional

        ID DIVISION.
        PROGRAM-ID pname
        DATA DIVISION.
        WORKING-STORAGE SECTION.
        77 PRINT-REC PIC X(8).
        PROCEDURE DIVISION.
        MOVE "" TO PRINT-REC
        STOP RUN.
        END PROGRAM pname.
