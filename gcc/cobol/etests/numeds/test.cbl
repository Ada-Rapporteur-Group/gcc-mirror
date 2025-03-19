        IDENTIFICATION DIVISION.
        PROGRAM-ID.  numeds.

        ENVIRONMENT DIVISION.
        CONFIGURATION SECTION.
        SPECIAL-NAMES.
            CURRENCY SIGN IS "$" WITH PICTURE SYMBOL "$"
            CURRENCY SIGN IS "USD" WITH PICTURE SYMBOL "u".

        DATA DIVISION.
        WORKING-STORAGE SECTION.

        01 N_9dot9      PICTURE  9999999999.99    .
        01 N_9dot9P     PICTURE  9999999999.99+   .
        01 N_P9dot9     PICTURE +9999999999.99   .
        01 N_9dot9M     PICTURE  9999999999.99-   .
        01 N_M9dot9     PICTURE -9999999999.99   .
        01 N_9sep9P     PICTURE  9,999,999,999.99+   .
        01 N_P9sep9     PICTURE +9,999,999,999.99   .
        01 N_9sep9M     PICTURE  9,999,999,999.99-   .
        01 N_M9sep9     PICTURE -9,999,999,999.99   .
        01 N_9dot9CR     PICTURE 9,999,999,999.99CR   .
        01 N_9dotDB      PICTURE 9,999,999,999.99DB   .

        01 N_9dot9C      PICTURE  9999999999.99$    .
        01 N_9dot9CP     PICTURE  9999999999.99$+   .
        01 N_P9dotC9     PICTURE +9999999999.99$   .
        01 N_9dot9CM     PICTURE  9999999999.99$-   .
        01 N_M9dotC9     PICTURE -9999999999.99$   .
        01 N_9sep9CP     PICTURE  9,999,999,999.99$+   .
        01 N_P9sepC9     PICTURE +9,999,999,999.99$   .
        01 N_9sep9CM     PICTURE  9,999,999,999.99$-   .
        01 N_M9sepC9     PICTURE -9,999,999,999.99$   .
        01 N_9dot9CCR    PICTURE  9,999,999,999.99$CR   .
        01 N_9dotCDB     PICTURE  9,999,999,999.99$DB   .

        01 N_C9dot9      PICTURE  $9999999999.99    .
        01 N_C9dot9P     PICTURE  $9999999999.99+   .
        01 N_PC9dot9     PICTURE +$9999999999.99   .
        01 N_C9dot9M     PICTURE  $9999999999.99-   .
        01 N_MC9dot9     PICTURE -$9999999999.99   .
        01 N_C9sep9P     PICTURE  $9,999,999,999.99+   .
        01 N_PC9sep9     PICTURE +$9,999,999,999.99   .
        01 N_C9sep9M     PICTURE  $9,999,999,999.99-   .
        01 N_MC9sep9     PICTURE -$9,999,999,999.99   .
        01 N_C9dot9CR    PICTURE  $9,999,999,999.99CR   .
        01 N_C9dotDB     PICTURE  $9,999,999,999.99DB   .

        01 N_Zdot9      PICTURE  ZZZZZZZZZZ9.99    .
        01 N_Zdot9P     PICTURE  ZZZZZZZZZZ9.99+   .
        01 N_PZdot9     PICTURE +ZZZZZZZZZZ9.99   .
        01 N_Zdot9M     PICTURE  ZZZZZZZZZZ9.99-   .
        01 N_MZdot9     PICTURE -ZZZZZZZZZZ9.99   .
        01 N_Zsep9P     PICTURE  Z,ZZZ,ZZZ,ZZ9.99+   .
        01 N_PZsep9     PICTURE +Z,ZZZ,ZZZ,ZZ9.99   .
        01 N_Zsep9M     PICTURE  Z,ZZZ,ZZZ,ZZ9.99-   .
        01 N_MZsep9     PICTURE -Z,ZZZ,ZZZ,ZZ9.99   .
        01 N_Zdot9CR    PICTURE  Z,ZZZ,ZZZ,ZZ9.99CR   .
        01 N_ZdotDB     PICTURE  Z,ZZZ,ZZZ,ZZZ.99DB   .

        01 N_xdot9      PICTURE  **********9.99    .
        01 N_xdot9P     PICTURE  **********9.99+   .
        01 N_Pxdot9     PICTURE +**********9.99   .
        01 N_xdot9M     PICTURE  **********9.99-   .
        01 N_Mxdot9     PICTURE -**********9.99   .
        01 N_xsep9P     PICTURE  *,***,***,**9.99+   .
        01 N_Pxsep9     PICTURE +*,***,***,**9.99   .
        01 N_xsep9M     PICTURE  *,***,***,**9.99-   .
        01 N_Mxsep9     PICTURE -*,***,***,**9.99   .
        01 N_xdot9CR    PICTURE  *,***,***,**9.99CR   .
        01 N_xdotDB     PICTURE  *,***,***,***.99DB   .

        01 N_cdot9      PICTURE  $$$$$$$$$$9.99    .
        01 N_cdot9P     PICTURE  $$$$$$$$$$9.99+   .
        01 N_Pcdot9     PICTURE +$$$$$$$$$$9.99   .
        01 N_cdot9M     PICTURE  $$$$$$$$$$9.99-   .
        01 N_Mcdot9     PICTURE -$$$$$$$$$$9.99   .
        01 N_csep9P     PICTURE  $,$$$,$$$,$$9.99+   .
        01 N_Pcsep9     PICTURE +$,$$$,$$$,$$9.99   .
        01 N_csep9M     PICTURE  $,$$$,$$$,$$9.99-   .
        01 N_Mcsep9     PICTURE -$,$$$,$$$,$$9.99   .
        01 N_cdot9CR    PICTURE  $,$$$,$$$,$$9.99CR   .
        01 N_cdotDB     PICTURE  $,$$$,$$$,$$$.99DB   .

        01 N_mmdot9      PICTURE   ----------9.99    .
        01 N_mmdot9P     PICTURE  $----------9.99    .
        01 N_mmsep9P     PICTURE   -,---,---,--9.99   .
        01 N_Pmmsep9     PICTURE  $-,---,---,--9.99   .

        01 N_ppdot9      PICTURE   ++++++++++9.99    .
        01 N_ppdot9P     PICTURE  $++++++++++9.99    .
        01 N_ppsep9P     PICTURE   +,+++,+++,++9.99   .
        01 N_Pppsep9     PICTURE  $+,+++,+++,++9.99   .

        01 N_csl9P     PICTURE  $/$$$/$$$/$$9.99+   .
        01 N_Pcsl9     PICTURE +$/$$$/$$$/$$9.99   .
        01 N_csl9M     PICTURE  $/$$$/$$$/$$9.99-   .
        01 N_Mcsl9     PICTURE -$/$$$/$$$/$$9.99   .
        01 N_csl9CR    PICTURE  $/$$$/$$$/$$9.99CR   .
        01 N_cslDB     PICTURE  $/$$$/$$$/$$$.99DB   .

        01 N_bl9P     PICTURE  $B$$$B$$$B$$9.99+   .
        01 N_Pbl9     PICTURE +$B$$$B$$$B$$9.99   .
        01 N_bl9M     PICTURE  $B$$$B$$$B$$9.99-   .
        01 N_Mbl9     PICTURE -$B$$$B$$$B$$9.99   .
        01 N_bl9CR    PICTURE  $B$$$B$$$B$$9.99CR   .
        01 N_blDB     PICTURE  $B$$$B$$$B$$$.99DB   .

        01 zdotz        PICTURE ZZZ.ZZZ   .
        01 stardotstar  PICTURE ***.***   .

        01 DATA-SOURCE PICTURE S9999V9.

        01  VAL  PIC    S999999V99.
        01  EN   PIC   +u,ZZZ,ZZZ.ZZ.
        01  EN2  PIC   +u,***,***.**.
        01  EN3  PIC   --/---/---.--.
        01  EN4  PIC   ++b+++B+++v++.
        01  EN5  PIC   uu,uuu,uuuVuu.

        01 PrnStateSales     PIC $$$,$$$,$$9.99.
        01 Edit6             PIC  $$,$$$,$$9.00.

        01 VARPP9 PIC PP9 VALUE 0.001.
        01 VARP9  PIC P9  VALUE 0.01.
        01 VARV9  PIC V9  VALUE 0.1.
        01 VAR9   PIC 9   VALUE 1.
        01 VAR9P  PIC 9P  VALUE 10.
        01 VAR9PP PIC 9PP VALUE 100.

        01 NE9P    PIC **P    VALUE 10.
        01 NE9PP   PIC **PP   VALUE 100.
        01 NE9PPP  PIC **PPP  VALUE 1000.
        01 NE9PPPP PIC **P(4) VALUE 10000.

        01 VALNE PIC 999999.

        PROCEDURE DIVISION.
            PERFORM ALL_VALUES.
            PERFORM EN_Tests.
            STOP RUN.

        ALL_VALUES.
            MOVE 1234.5 TO DATA-SOURCE
            PERFORM DISPLAY_ALL.
            MOVE -1234.5 TO DATA-SOURCE
            PERFORM DISPLAY_ALL.

        DISPLAY_ALL.

            DISPLAY "******** DATA-SOURCE is " DATA-SOURCE
            MOVE DATA-SOURCE To N_9dot9
            MOVE DATA-SOURCE To N_9dot9P
            MOVE DATA-SOURCE To N_P9dot9
            MOVE DATA-SOURCE To N_9dot9M
            MOVE DATA-SOURCE To N_M9dot9
            MOVE DATA-SOURCE To N_9sep9P
            MOVE DATA-SOURCE To N_P9sep9
            MOVE DATA-SOURCE To N_9sep9M
            MOVE DATA-SOURCE To N_M9sep9
            MOVE DATA-SOURCE To N_9dot9CR
            MOVE DATA-SOURCE To N_9dotDB

            MOVE DATA-SOURCE To N_9dot9C
            MOVE DATA-SOURCE To N_9dot9CP
            MOVE DATA-SOURCE To N_P9dotC9
            MOVE DATA-SOURCE To N_9dot9CM
            MOVE DATA-SOURCE To N_M9dotC9
            MOVE DATA-SOURCE To N_9sep9CP
            MOVE DATA-SOURCE To N_P9sepC9
            MOVE DATA-SOURCE To N_9sep9CM
            MOVE DATA-SOURCE To N_M9sepC9
            MOVE DATA-SOURCE To N_9dot9CCR
            MOVE DATA-SOURCE To N_9dotCDB

            MOVE DATA-SOURCE To N_C9dot9
            MOVE DATA-SOURCE To N_C9dot9P
            MOVE DATA-SOURCE To N_PC9dot9
            MOVE DATA-SOURCE To N_C9dot9M
            MOVE DATA-SOURCE To N_MC9dot9
            MOVE DATA-SOURCE To N_C9sep9P
            MOVE DATA-SOURCE To N_PC9sep9
            MOVE DATA-SOURCE To N_C9sep9M
            MOVE DATA-SOURCE To N_MC9sep9
            MOVE DATA-SOURCE To N_C9dot9CR
            MOVE DATA-SOURCE To N_C9dotDB

            MOVE DATA-SOURCE To N_Zdot9
            MOVE DATA-SOURCE To N_Zdot9P
            MOVE DATA-SOURCE To N_PZdot9
            MOVE DATA-SOURCE To N_Zdot9M
            MOVE DATA-SOURCE To N_MZdot9
            MOVE DATA-SOURCE To N_Zsep9P
            MOVE DATA-SOURCE To N_PZsep9
            MOVE DATA-SOURCE To N_Zsep9M
            MOVE DATA-SOURCE To N_MZsep9
            MOVE DATA-SOURCE To N_Zdot9CR
            MOVE DATA-SOURCE To N_ZdotDB

            MOVE DATA-SOURCE To N_xdot9
            MOVE DATA-SOURCE To N_xdot9P
            MOVE DATA-SOURCE To N_Pxdot9
            MOVE DATA-SOURCE To N_xdot9M
            MOVE DATA-SOURCE To N_Mxdot9
            MOVE DATA-SOURCE To N_xsep9P
            MOVE DATA-SOURCE To N_Pxsep9
            MOVE DATA-SOURCE To N_xsep9M
            MOVE DATA-SOURCE To N_Mxsep9
            MOVE DATA-SOURCE To N_xdot9CR
            MOVE DATA-SOURCE To N_xdotDB

            MOVE DATA-SOURCE To N_cdot9
            MOVE DATA-SOURCE To N_cdot9P
            MOVE DATA-SOURCE To N_Pcdot9
            MOVE DATA-SOURCE To N_cdot9M
            MOVE DATA-SOURCE To N_Mcdot9
            MOVE DATA-SOURCE To N_csep9P
            MOVE DATA-SOURCE To N_Pcsep9
            MOVE DATA-SOURCE To N_csep9M
            MOVE DATA-SOURCE To N_Mcsep9
            MOVE DATA-SOURCE To N_cdot9CR
            MOVE DATA-SOURCE To N_cdotDB

            MOVE DATA-SOURCE To N_mmdot9
            MOVE DATA-SOURCE To N_mmdot9P
            MOVE DATA-SOURCE To N_mmsep9P
            MOVE DATA-SOURCE To N_Pmmsep9

            MOVE DATA-SOURCE To N_ppdot9
            MOVE DATA-SOURCE To N_ppdot9P
            MOVE DATA-SOURCE To N_ppsep9P
            MOVE DATA-SOURCE To N_Pppsep9

            MOVE DATA-SOURCE To N_csl9P
            MOVE DATA-SOURCE To N_Pcsl9
            MOVE DATA-SOURCE To N_csl9M
            MOVE DATA-SOURCE To N_Mcsl9
            MOVE DATA-SOURCE To N_csl9CR
            MOVE DATA-SOURCE To N_cslDB

            MOVE DATA-SOURCE To N_bl9P
            MOVE DATA-SOURCE To N_Pbl9
            MOVE DATA-SOURCE To N_bl9M
            MOVE DATA-SOURCE To N_Mbl9
            MOVE DATA-SOURCE To N_bl9CR
            MOVE DATA-SOURCE To N_blDB

            DISPLAY " N_9dot9     " N_9dot9
            DISPLAY " N_9dot9P    " N_9dot9P
            DISPLAY " N_P9dot9   "  N_P9dot9
            DISPLAY " N_9dot9M    " N_9dot9M
            DISPLAY " N_M9dot9   "  N_M9dot9
            DISPLAY " N_9sep9P    " N_9sep9P
            DISPLAY " N_P9sep9   "  N_P9sep9
            DISPLAY " N_9sep9M    " N_9sep9M
            DISPLAY " N_M9sep9   "  N_M9sep9
            DISPLAY " N_9dot9CR   " N_9dot9CR
            DISPLAY " N_9dotDB    " N_9dotDB
            DISPLAY " "

            DISPLAY " N_9dot9C    " N_9dot9C
            DISPLAY " N_9dot9CP   " N_9dot9CP
            DISPLAY " N_P9dotC9  "  N_P9dotC9
            DISPLAY " N_9dot9CM   " N_9dot9CM
            DISPLAY " N_M9dotC9  "  N_M9dotC9
            DISPLAY " N_9sep9CP   " N_9sep9CP
            DISPLAY " N_P9sepC9  "  N_P9sepC9
            DISPLAY " N_9sep9CM   " N_9sep9CM
            DISPLAY " N_M9sepC9  "  N_M9sepC9
            DISPLAY " N_9dot9CCR  " N_9dot9CCR
            DISPLAY " N_9dotCDB   " N_9dotCDB
            DISPLAY " "

            DISPLAY " N_C9dot9    " N_C9dot9
            DISPLAY " N_C9dot9P   " N_C9dot9P
            DISPLAY " N_PC9dot9  "  N_PC9dot9
            DISPLAY " N_C9dot9M   " N_C9dot9M
            DISPLAY " N_MC9dot9  "  N_MC9dot9
            DISPLAY " N_C9sep9P   " N_C9sep9P
            DISPLAY " N_PC9sep9  "  N_PC9sep9
            DISPLAY " N_C9sep9M   " N_C9sep9M
            DISPLAY " N_MC9sep9  "  N_MC9sep9
            DISPLAY " N_C9dot9CR  " N_C9dot9CR
            DISPLAY " N_C9dotDB   " N_C9dotDB
            DISPLAY " "

            DISPLAY " N_Zdot9     " N_Zdot9
            DISPLAY " N_Zdot9P    " N_Zdot9P
            DISPLAY " N_PZdot9   "  N_PZdot9
            DISPLAY " N_Zdot9M    " N_Zdot9M
            DISPLAY " N_MZdot9   "  N_MZdot9
            DISPLAY " N_Zsep9P    " N_Zsep9P
            DISPLAY " N_PZsep9   "  N_PZsep9
            DISPLAY " N_Zsep9M    " N_Zsep9M
            DISPLAY " N_MZsep9   "  N_MZsep9
            DISPLAY " N_Zdot9CR   " N_Zdot9CR
            DISPLAY " N_ZdotDB    " N_ZdotDB
            DISPLAY " "

            DISPLAY " N_xdot9     " N_xdot9
            DISPLAY " N_xdot9P    " N_xdot9P
            DISPLAY " N_Pxdot9   "  N_Pxdot9
            DISPLAY " N_xdot9M    " N_xdot9M
            DISPLAY " N_Mxdot9   "  N_Mxdot9
            DISPLAY " N_xsep9P    " N_xsep9P
            DISPLAY " N_Pxsep9   "  N_Pxsep9
            DISPLAY " N_xsep9M    " N_xsep9M
            DISPLAY " N_Mxsep9   "  N_Mxsep9
            DISPLAY " N_xdot9CR   " N_xdot9CR
            DISPLAY " N_xdotDB    " N_xdotDB
            DISPLAY " "

            DISPLAY " N_cdot9     " N_cdot9
            DISPLAY " N_cdot9P    " N_cdot9P
            DISPLAY " N_Pcdot9   "  N_Pcdot9
            DISPLAY " N_cdot9M    " N_cdot9M
            DISPLAY " N_Mcdot9   "  N_Mcdot9
            DISPLAY " N_csep9P    " N_csep9P
            DISPLAY " N_Pcsep9   "  N_Pcsep9
            DISPLAY " N_csep9M    " N_csep9M
            DISPLAY " N_Mcsep9   "  N_Mcsep9
            DISPLAY " N_cdot9CR   " N_cdot9CR
            DISPLAY " N_cdotDB    " N_cdotDB
            DISPLAY " "

            DISPLAY " N_mmdot9    " N_mmdot9
            DISPLAY " N_mmdot9P  "  N_mmdot9P
            DISPLAY " N_mmsep9P   " N_mmsep9P
            DISPLAY " N_Pmmsep9  "  N_Pmmsep9
            DISPLAY " "

            DISPLAY " N_ppdot9    " N_ppdot9
            DISPLAY " N_ppdot9P  "  N_ppdot9P
            DISPLAY " N_ppsep9P   " N_ppsep9P
            DISPLAY " N_Pppsep9  "  N_Pppsep9
            DISPLAY " "

            DISPLAY " N_csl9P    " N_csl9P
            DISPLAY " N_Pcsl9   " N_Pcsl9
            DISPLAY " N_csl9M    " N_csl9M
            DISPLAY " N_Mcsl9   " N_Mcsl9
            DISPLAY " N_csl9CR   " N_csl9CR
            DISPLAY " N_cslDB    " N_cslDB
            DISPLAY " "

            DISPLAY " N_bl9P     " N_bl9P
            DISPLAY " N_Pbl9    " N_Pbl9
            DISPLAY " N_bl9M     " N_bl9M
            DISPLAY " N_Mbl9    " N_Mbl9
            DISPLAY " N_bl9CR    " N_bl9CR
            DISPLAY " N_blDB     " N_blDB
            DISPLAY " "
            DISPLAY " ".

            MOVE 0 to zdotz
            DISPLAY "zdotz is " zdotz.

            MOVE 0.009 to zdotz
            DISPLAY "zdotz is " zdotz.

            MOVE 0 to stardotstar
            DISPLAY "stardotstar is " stardotstar.

            MOVE 0.009 to stardotstar
            DISPLAY "stardotstar is " stardotstar.

            MOVE            0.09 to N_csep9P. DISPLAY N_csep9P.
            MOVE            0.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE            7.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE           67.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE          567.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE        -4567.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE       -34567.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE      -234567.89 to N_csep9P. DISPLAY N_csep9P.
            MOVE     -1234567.89 to N_csep9P. DISPLAY N_csep9P.

            MOVE            0.09 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE            0.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE            7.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE           67.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE          567.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE        -4567.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE       -34567.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE      -234567.89 to N_xdot9CR. DISPLAY N_xdot9CR.
            MOVE     -1234567.89 to N_xdot9CR. DISPLAY N_xdot9CR.

            MOVE            0.09 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE            0.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE            7.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE           67.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE          567.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE        -4567.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE       -34567.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE      -234567.89 to N_Zsep9P. DISPLAY N_Zsep9P.
            MOVE     -1234567.89 to N_Zsep9P. DISPLAY N_Zsep9P.

        EN_Tests.
        move 12628844.83 TO PrnStateSales
        DISPLay PrnStateSales

        MOVE 14584 to Edit6
        DISPLAY Edit6

        MOVE ZERO    TO VAL PERFORM DISP_EN
        MOVE  .01    TO VAL PERFORM DISP_EN
        MOVE -.1     TO VAL PERFORM DISP_EN
        MOVE  1      TO VAL PERFORM DISP_EN
        MOVE -10     TO VAL PERFORM DISP_EN
        MOVE  100    TO VAL PERFORM DISP_EN
        MOVE -1000   TO VAL PERFORM DISP_EN
        MOVE  10000  TO VAL PERFORM DISP_EN
        MOVE -100000 TO VAL PERFORM DISP_EN
        DISPLAY SPACE

        MOVE ZERO    TO VAL PERFORM DISP_EN2
        MOVE  .01    TO VAL PERFORM DISP_EN2
        MOVE -.1     TO VAL PERFORM DISP_EN2
        MOVE  1      TO VAL PERFORM DISP_EN2
        MOVE -10     TO VAL PERFORM DISP_EN2
        MOVE  100    TO VAL PERFORM DISP_EN2
        MOVE -1000   TO VAL PERFORM DISP_EN2
        MOVE  10000  TO VAL PERFORM DISP_EN2
        MOVE -100000 TO VAL PERFORM DISP_EN2
        DISPLAY SPACE

        MOVE ZERO    TO VAL PERFORM DISP_EN3
        MOVE  .01    TO VAL PERFORM DISP_EN3
        MOVE -.1     TO VAL PERFORM DISP_EN3
        MOVE  1      TO VAL PERFORM DISP_EN3
        MOVE -10     TO VAL PERFORM DISP_EN3
        MOVE  100    TO VAL PERFORM DISP_EN3
        MOVE -1000   TO VAL PERFORM DISP_EN3
        MOVE  10000  TO VAL PERFORM DISP_EN3
        MOVE -100000 TO VAL PERFORM DISP_EN3
        DISPLAY SPACE

        MOVE ZERO    TO VAL PERFORM DISP_EN4
        MOVE  .01    TO VAL PERFORM DISP_EN4
        MOVE -.1     TO VAL PERFORM DISP_EN4
        MOVE  1      TO VAL PERFORM DISP_EN4
        MOVE -10     TO VAL PERFORM DISP_EN4
        MOVE  100    TO VAL PERFORM DISP_EN4
        MOVE -1000   TO VAL PERFORM DISP_EN4
        MOVE  10000  TO VAL PERFORM DISP_EN4
        MOVE -100000 TO VAL PERFORM DISP_EN4
        DISPLAY SPACE

        MOVE ZERO    TO VAL PERFORM DISP_EN5
        MOVE  .01    TO VAL PERFORM DISP_EN5
        MOVE -.1     TO VAL PERFORM DISP_EN5
        MOVE  1      TO VAL PERFORM DISP_EN5
        MOVE -10     TO VAL PERFORM DISP_EN5
        MOVE  100    TO VAL PERFORM DISP_EN5
        MOVE -1000   TO VAL PERFORM DISP_EN5
        MOVE  10000  TO VAL PERFORM DISP_EN5
        MOVE -100000 TO VAL PERFORM DISP_EN5
        DISPLAY SPACE

        MOVE 10 TO NE9P
        MOVE 100 TO NE9PP
        MOVE 1000 TO NE9PPP
        MOVE 10000 TO NE9PPPP

        DISPLAY NE9P
        DISPLAY NE9PP
        DISPLAY NE9PPP
        DISPLAY NE9PPPP

        MOVE 300 TO NE9PP
        DISPLAY NE9PP

        MOVE NE9PP TO VAL
        DISPLAY VAL

        DISPLAY VARPP9
        DISPLAY VARP9
        DISPLAY VARV9
        DISPLAY VAR9
        DISPLAY VAR9P
        DISPLAY VAR9PP
        DISPLAY SPACE

        DISPLAY NE9P
        DISPLAY NE9PP
        DISPLAY NE9PPP
        DISPLAY NE9PPPP

        MOVE 300 TO NE9PP
        DISPLAY NE9PP

        MOVE NE9PP TO VALNE
        DISPLAY VALNE

       .

        DISP_EN.
            MOVE VAL TO EN
            DISPLAY VAL " results in >>" EN "<<".

        DISP_EN2.
            MOVE VAL TO EN2
            DISPLAY VAL " results in >>" EN2 "<<".

        DISP_EN3.
            MOVE VAL TO EN3
            DISPLAY VAL " results in >>" EN3 "<<".

        DISP_EN4.
            MOVE VAL TO EN4
            DISPLAY VAL " results in >>" EN4 "<<".

        DISP_EN5.
            MOVE VAL TO EN5
            DISPLAY VAL " results in >>" EN5 "<<".

        END PROGRAM numeds.
