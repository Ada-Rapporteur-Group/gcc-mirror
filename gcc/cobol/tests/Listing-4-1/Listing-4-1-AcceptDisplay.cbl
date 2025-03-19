IDENTIFICATION DIVISION.
PROGRAM-ID.  Listing4-1.
AUTHOR.  Michael Coughlan.
DATA DIVISION.
WORKING-STORAGE SECTION.
01  UserName           PIC X(20).

*> Receiving data item for DATE system variable: Format is YYMMDD
01 CurrentDate.
   02  CurrentYear     PIC 99.
   02  CurrentMonth    PIC 99.
   02  CurrentDay      PIC 99.

*> Receiving data item for DAY system variable: Format is YYDDD
01 DayOfYear.
   02  YearYear        PIC 99.
   02  YearDay         PIC 9(3).

*> Receiving item for TIME: Format is HHMMSSss   s = S/100
01 CurrentTime.
   02  CurrentHour     PIC 99.
   02  CurrentMinute   PIC 99.
   02  CurrentSecond   PIC 99.
   02  CurrentCentisec PIC 99.

*> Receiving item for DATE YYYYMMDD system variable: Format is YYYYMMDD
01 Y2KDate.
   02 Y2KYear          PIC 9(4).
   02 Y2KMonth         PIC 99.
   02 Y2KDay           PIC 99.

*> Receiving item for DAY YYYYDDD system variable: Format is YYYYDDD
01 Y2KDayOfYear.
   02 Y2KDOY-Year      PIC 9(4).
   02 Y2KDOY-Day       PIC 999.

01 DOW PIC 9.

01 DateAndTimeNow.
    02 DateNow.
       03 YearNow              PIC 9999.
       03 MonthNow             PIC 99.
       03 DayNow               PIC 99.
    02 TimeC.
       03 HourNow              PIC 99.
       03 MinNow               PIC 99.
       03 SecNow               PIC 99.
       03 SecFrac              PIC 99.
    02 GMT.
       03 GMTDiff              PIC X.
       03 GMTHours             PIC 99.
       03 GMTMins              PIC 99.

01 DateAndTimeCompiled.
    02 DateNow.
       03 YearNow              PIC 9999.
       03 MonthNow             PIC 99.
       03 DayNow               PIC 99.
    02 TimeC.
       03 HourNow              PIC 99.
       03 MinNow               PIC 99.
       03 SecNow               PIC 99.
       03 SecFrac              PIC 99.
    02 GMT.
       03 GMTDiff              PIC X.
       03 GMTHours             PIC 99.
       03 GMTMins              PIC 99.

01 DateNowInt PIC 99999999.

        01 EnvName  PIC X(14) VALUE "USER".
        01 NewName  PIC X(14) VALUE 'McGillicuddy'.
        01 UserName2 PIC X(24).

        01 CommandLineCount PIC 999.
        01 CommandLine      PIC X(120).

PROCEDURE DIVISION.
Begin.
    DISPLAY "Please enter your name - " WITH NO ADVANCING
    ACCEPT  UserName
    DISPLAY "**********************"

    MOVE FUNCTION CURRENT-DATE TO DateAndTimeNow
    MOVE FUNCTION WHEN-COMPILED TO DateAndTimeCompiled
    ACCEPT CurrentDate  FROM DATE
    ACCEPT DayOfYear    FROM DAY
    ACCEPT CurrentTime  FROM TIME
    ACCEPT Y2KDate      FROM DATE YYYYMMDD
    ACCEPT Y2KDayOfYear FROM DAY YYYYDDD
    ACCEPT DOW          FROM DAY-OF-WEEK

    IF UserName NOT EQUAL TO "Oswald"
        *> For the sake of testing, we don't print out the volatile date and time
        *> when the UserName is "Oswald"
        DISPLAY "Name is " UserName
        DISPLAY "Date is " CurrentMonth "/" CurrentDay "/" CurrentYear
        DISPLAY "Today is day " YearDay " of the two-digit year " YearYear
        DISPLAY "The time is " CurrentHour ":" CurrentMinute ":" CurrentSecond "." CurrentCentisec
        DISPLAY "Y2KDate is " Y2KYear "-" Y2KMonth "-" Y2kDay
        DISPLAY "Y2K Day of Year is " Y2KDoy-Day " of " Y2KDOY-Year
        DISPLAY "Day-of-week (Monday is 1) is " DOW
        DISPLAY "Compile time was " DateAndTimeCompiled
        DISPLAY "Right now is     " DateAndTimeNow
        END-IF

    IF Y2KYear NOT EQUAL TO YearNow OF DateAndTimeNow
        DISPLAY "Years don't match " Y2KYear " " YearNow  OF DateAndTimeNow
        END-IF

    IF CurrentMonth NOT EQUAL TO MonthNow OF DateAndTimeNow
        DISPLAY "Months don't match " CurrentMonth " " MonthNow OF DateAndTimeNow
        END-IF


    MOVE "16010101" TO DateNowInt
    MOVE FUNCTION INTEGER-OF-DATE(DateNowInt) TO DateNowInt
    DISPLAY DateNowInt
    MOVE 1 TO DateNowInt
    MOVE FUNCTION DATE-OF-INTEGER(DateNowInt) TO DateNowInt
    DISPLAY DateNowInt

        MOVE "First" to NewName
        SET ENVIRONMENT EnvName TO NewName
        ACCEPT UserName2 FROM ENVIRONMENT EnvName.
        DISPLAY "getenv(""USER"") is " UserName2.

        MOVE "Second" to NewName
        SET ENVIRONMENT "USER" TO NewName
        ACCEPT UserName2 FROM ENVIRONMENT EnvName.
        DISPLAY "getenv(""USER"") is " UserName2.

        SET ENVIRONMENT EnvName TO "Third"
        ACCEPT UserName2 FROM ENVIRONMENT EnvName.
        DISPLAY "getenv(""USER"") is " UserName2.

        SET ENVIRONMENT "USER" TO "Fourth"
        ACCEPT UserName2 FROM ENVIRONMENT EnvName.
        DISPLAY "getenv(""USER"") is " UserName2.

        MOVE "Fifth" to NewName
        SET ENVIRONMENT EnvName TO NewName
        ACCEPT UserName2 FROM ENVIRONMENT "USER".
        DISPLAY "getenv(""USER"") is " UserName2.

        ACCEPT CommandLineCount FROM COMMAND-LINE-COUNT
        DISPLAY "Command Line Count is " CommandLineCount

        ACCEPT CommandLine FROM COMMAND-LINE
        DISPLAY "Entire command line is " CommandLine

        ACCEPT CommandLine FROM COMMAND-LINE(1)
        DISPLAY "First parameter is " CommandLine

        ACCEPT CommandLine FROM COMMAND-LINE(2)
        DISPLAY "Second parameter is " CommandLine

        ACCEPT CommandLine FROM COMMAND-LINE(3)
        DISPLAY "Third parameter is " CommandLine

        ACCEPT CommandLine FROM COMMAND-LINE(4)
        DISPLAY "Fourth parameter is " CommandLine

        ACCEPT CommandLine FROM COMMAND-LINE(5)
        DISPLAY "Fifth parameter is " CommandLine

        IF CommandLine EQUAL TO LOW-VALUE
            DISPLAY "Fourth parameter is LOW-VALUES".

    STOP RUN.
