        IDENTIFICATION DIVISION.
        PROGRAM-ID. entry-demo.
        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 AA PIC X VALUE 'A'.
        01 BB PIC X VALUE 'B'.
        01 CC PIC X VALUE 'C'.
        01 DD PIC X VALUE 'D'.
        01 EE PIC X VALUE 'E'.
        01 FF PIC X VALUE 'F'.
        PROCEDURE DIVISION.
        CALL "aaa"    USING AA BB CC.
        CALL "aaa-1"  USING DD EE FF.
        GOBACK.
        END PROGRAM entry-demo.

        IDENTIFICATION DIVISION.
        PROGRAM-ID. aaa.
        DATA DIVISION.
        WORKING-STORAGE SECTION.
        01 AA PIC X .
        01 BB PIC X .
        01 CC PIC X .

        LINKAGE SECTION.
        01 I PIC X .
        01 J PIC X .
        01 K PIC X .
        01 L PIC X .
        01 M PIC X .
        01 N PIC X .
        PROCEDURE DIVISION USING I J K.
            MOVE I TO AA
            MOVE J TO BB
            MOVE K TO CC
            DISPLAY "From above the ENTRY aaa-1:"
            PERFORM PRINT-A-B-C
            GOBACK.
        ENTRY "aaa-1" USING L M N
            MOVE L TO AA
            MOVE M TO BB
            MOVE N TO CC
            DISPLAY "From below the ENTRY aaa-1:"
            PERFORM PRINT-A-B-C
            GOBACK.
        PRINT-A-B-C.
            DISPLAY "A-B-C "
                    AA SPACE
                    BB SPACE
                    CC      .
        END PROGRAM aaa.
