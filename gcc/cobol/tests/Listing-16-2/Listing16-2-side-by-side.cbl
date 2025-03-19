IDENTIFICATION DIVISION.
PROGRAM-ID. Listing16-2.
AUTHOR.  Michael Coughlan.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 StudentId              PIC 9(7).

01 ValidationResult       PIC 9.
   88 ValidStudentId      VALUE ZERO.
   88 InvalidStudentId    VALUE 1.

PROCEDURE DIVISION.
Begin.
    PERFORM 3 TIMES
       DISPLAY "Enter a Student Id : " WITH NO ADVANCING
       ACCEPT StudentId
       CALL "ValidateCheckDigit" USING BY CONTENT StudentID
                                       BY REFERENCE ValidationResult
       IF ValidStudentId
          DISPLAY "The Student id - " StudentId " - is valid"
        ELSE
          DISPLAY "The Student id - " StudentId " - is not valid"
       END-IF
       DISPLAY SPACES
    END-PERFORM
    STOP RUN.
    END PROGRAM Listing16-2.

IDENTIFICATION DIVISION.
PROGRAM-ID. ValidateCheckDigit IS INITIAL.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 SumOfNums            PIC 9(5).
01 Quotient             PIC 9(5).
01 CalcResult           PIC 99.

LINKAGE SECTION.
01 NumToValidate.
   02  D1               PIC 9.
   02  D2               PIC 9.
   02  D3               PIC 9.
   02  D4               PIC 9.
   02  D5               PIC 9.
   02  D6               PIC 9.
   02  D7               PIC 9.

01 Result               PIC 9.
   88 InvalidCheckDigit VALUE 1.
   88 ValidCheckDigit   VALUE 0.

PROCEDURE DIVISION USING NumToValidate, Result.
*> Returns a Result of 1 (invalid check digit) or 0 (valid check digit)
Begin.
   COMPUTE SumOfNums = (D1 * 7) + (D2 * 6) + (D3 * 5) + (D4 * 4) + (D5 * 3) + (D6 * 2) + (D7).
   DIVIDE SumOfNums BY 11 GIVING Quotient REMAINDER CalcResult
   IF CalcResult EQUAL TO ZERO
      SET ValidCheckDigit TO TRUE
    ELSE
      SET InvalidCheckDigit TO TRUE
   END-IF
   EXIT PROGRAM.
   END PROGRAM ValidateCheckDigit.

