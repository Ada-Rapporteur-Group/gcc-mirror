        IDENTIFICATION DIVISION.
        PROGRAM-ID. Listing5-5.
        AUTHOR.  Michael Coughlan.

        *> Extended by Bob Dubner to exercise the compiler

        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 CountryCode       PIC 999 VALUE ZEROS.
           88 BritishCountry VALUES 3, 7, 10, 15.

        01 CurrencyCode        PIC 99 VALUE ZEROS.
           88 CurrencyIsPound  VALUE 14.
           88 CurrencyIsEuro   VALUE 03.
           88 CurrencyIsDollar VALUE 28.

        PROCEDURE DIVISION.
            MOVE  2 TO CountryCode. PERFORM Begin.
            MOVE  3 TO CountryCode. PERFORM Begin.
            MOVE  6 TO CountryCode. PERFORM Begin.
            MOVE  7 TO CountryCode. PERFORM Begin.
            MOVE  9 TO CountryCode. PERFORM Begin.
            MOVE 10 TO CountryCode. PERFORM Begin.
            MOVE 14 TO CountryCode. PERFORM Begin.
            MOVE 15 TO CountryCode. PERFORM Begin.
            STOP RUN.

        Begin.
           DISPLAY "Country Code is " CountryCode ": " WITH NO ADVANCING
           IF BritishCountry THEN
              SET CurrencyIsPound TO TRUE
           END-IF
           IF CurrencyIsPound THEN
              DISPLAY "Uses pound sterling"
            ELSE
              DISPLAY "Does not use pound sterling"
           END-IF
           *> These redundant instructions are to test the parser.
           MOVE 0 TO CurrencyCode.
           MOVE ZERO TO CurrencyCode.
           MOVE ZEROS TO CurrencyCode.
           MOVE ZEROES TO CurrencyCode.
