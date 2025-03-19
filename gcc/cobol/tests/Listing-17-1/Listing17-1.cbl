IDENTIFICATION DIVISION.
PROGRAM-ID. Listing17-1.
AUTHOR.  MICHAEL COUGHLAN.
*> Reads a Relative file directly or in sequence

ENVIRONMENT DIVISION.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
    SELECT VehicleFile ASSIGN TO "Listing17-1.DAT"
        ORGANIZATION IS RELATIVE
        ACCESS MODE IS DYNAMIC
        RELATIVE KEY IS VehicleKey
        FILE STATUS  IS VehicleStatus.

DATA DIVISION.
FILE SECTION.
FD  VehicleFile.
01  VehicleRec.
    88  EndOfVehiclefile        VALUE HIGH-VALUES.
    02  VehicleNum              PIC 9(4).
    02  VehicleDesc             PIC X(25).
    02  ManfName                PIC X(20).

WORKING-STORAGE SECTION.
01  VehicleStatus               PIC X(2).
    88  RecordFound             VALUE "00".

01  VehicleKey                  PIC 9(4).

01  ReadType                    PIC 9 VALUE 1.
    88 Done                     VALUE 0.
    88 DirectRead               VALUE 1.
    88 SequentialRead           VALUE 2.

01  PrnVehicleRecord.
    02    PrnVehicleNum         PIC 9(4).
    02    PrnVehicleDesc        PIC BBX(25).
    02    PrnManfName           PIC BBX(20).

PROCEDURE DIVISION.
BEGIN.

    OPEN INPUT VehicleFile
    PERFORM ReadDemo UNTIL Done
    CLOSE VehicleFile.
    STOP RUN.

    ReadDemo.
        DISPLAY "Enter read type: 1 for RANDOM, 2 for SEQUENTIAL"
        ACCEPT ReadType
        IF DirectRead
           DISPLAY "RANDOM Read of one record:"
           DISPLAY "Enter vehicle key (4 digits) --> " WITH NO ADVANCING
           ACCEPT VehicleKey
           DISPLAY "Desired VehicleKey is " VehicleKey
           READ VehicleFile
             INVALID KEY DISPLAY "     Record not found, because vehicle file status = " VehicleStatus
           END-READ
           PERFORM DisplayRecord
        ELSE
            IF SequentialRead
                *> Read from current position; leaves with pointer
                *> at end-of-file
                DISPLAY "SEQUENTIAL read of entire file:"
                READ VehicleFile NEXT RECORD
                    AT END SET EndOfVehiclefile TO TRUE
                    END-READ
                PERFORM UNTIL EndOfVehiclefile
                    PERFORM DisplayRecord
                    READ VehicleFile NEXT RECORD
                        AT END SET EndOfVehiclefile TO TRUE
                        END-READ
                    END-PERFORM
                END-IF
            END-IF.

DisplayRecord.
    IF RecordFound
       MOVE VehicleNum  TO PrnVehicleNum
       MOVE VehicleDesc TO PrnVehicleDesc
       MOVE ManfName    TO PrnManfName
       DISPLAY "     " PrnVehicleRecord
    END-IF.
