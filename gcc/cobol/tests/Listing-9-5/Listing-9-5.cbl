IDENTIFICATION DIVISION.
PROGRAM-ID. Listing9-5.
AUTHOR. Michael Coughlan.

*> Modified by Bob Dubner so I could see what's going on.

DATA DIVISION.
WORKING-STORAGE SECTION.
01 SmallScaledNumber  PIC SVP(5)999  VALUE .00000423.
01 LargeScaledNumber  PIC 999P(5)V   VALUE 45600000.
01 ScaledBillions     PIC 999P(9)    VALUE ZEROS.

01 SmallNumber        PIC 9V9(9)     VALUE 1.11111111.
01 LargeNumber        PIC 9(8)V9     VALUE 11111111.

01 PrnSmall           PIC 99.9(9).
01 PrnLarge           PIC ZZ,ZZZ,ZZ9.99.
01 PrnBillions        PIC ZZZ,ZZZ,ZZZ,ZZ9.

PROCEDURE DIVISION.
Begin.
    DISPLAY "SmallScaledNumber should be     +.00000423 and is      " SmallScaledNumber
    DISPLAY "LargeScaledNumber should be       45600000 and is        " LargeScaledNumber
    MOVE 123456789012  TO ScaledBillions
    DISPLAY "ScaledBillions    should be   123000000000 and is    " ScaledBillions
    DISPLAY " "

    DISPLAY "MOVING SmallScaledNumber TO PrnSmall"
    MOVE SmallScaledNumber TO PrnSmall
    DISPLAY "PrnSmall         should be    00.000004230 and is    " PrnSmall
    DISPLAY " "

    DISPLAY "MOVING LargeScaledNumber TO PrnLarge"
    MOVE LargeScaledNumber TO PrnLarge
    DISPLAY "PrnLarge         should be   45,600,000.00 and is   " PrnLarge
    DISPLAY " "

    DISPLAY "Adding SmallScaledNumber TO SmallNumber"
    ADD SmallScaledNumber TO SmallNumber
    MOVE SmallNumber TO PrnSmall
    DISPLAY "PrnSmall         should be    01.111115340 and is    " PrnSmall
    DISPLAY " "

    DISPLAY "Adding LargeScaledNumber TO LargeNumber"
    ADD LargeScaledNumber TO LargeNumber
    MOVE LargeNumber TO PrnLarge
    DISPLAY "LargeNumber      should be   56,711,111.00 and is   " PrnLarge
    DISPLAY " "

    DISPLAY "MOVE ScaledBillions TO PrnBillions"
    MOVE ScaledBillions  TO PrnBillions
    DISPLAY "PrnBillions      should be 123,000,000,000 and is " PrnBillions
    STOP RUN.
