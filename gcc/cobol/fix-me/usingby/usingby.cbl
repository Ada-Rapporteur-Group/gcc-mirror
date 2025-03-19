        *> GCOBOL improperly rejects PROCEDURE DIVISION USING BY REFERENCE

        ID DIVISION.
        PROGRAM-ID. usingby.

        DATA DIVISION.
        WORKING-STORAGE SECTION.
            01 one pic x value "1".
            01 two pic x value "2".
            01 three pic x value "3".

        PROCEDURE DIVISION.
        CALL "params" using one two three.
        END PROGRAM usingby.

        ID DIVISION.
        PROGRAM-ID. params.
        DATA DIVISION.
        LINKAGE SECTION.
        01 one pic X.
        01 two pic X.
        01 three pic X.
        PROCEDURE DIVISION using by reference one two three.
        *> The following statement works
        *>PROCEDURE DIVISION using reference one two three.
        display one
        display two
        display three.
        GOBACK.
        END PROGRAM params.
