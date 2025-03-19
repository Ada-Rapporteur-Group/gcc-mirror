       IDENTIFICATION DIVISION.
       PROGRAM-ID. phase0.
      *>-----------------------------------------
      *> Replaces contents of positions 1 through 6 with blanks.
      *> Truncates contents after 72
      *> TRIMs the line: TRAILING getting rid of white-space at the end
      *>-----------------------------------------

       ENVIRONMENT DIVISION.
       CONFIGURATION SECTION.
       REPOSITORY.
           FUNCTION ALL INTRINSIC.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
          SELECT nist-file
             ASSIGN TO nist-file-name
             FILE STATUS IS nist-file-status
             ORGANIZATION IS LINE SEQUENTIAL.

       DATA DIVISION.
       FILE SECTION.
          FD nist-file.
             01 nist-record PIC  X(100).
       WORKING-STORAGE SECTION.
       77 nist-file-name PIC x(40) VALUE "NC101A.cob".
       77 nist-file-status PIC 99.
       77 work-string PIC X(80).

       PROCEDURE DIVISION.
           OPEN INPUT nist-file.
       main-loop.
           READ nist-file AT END perform all-done.
           PERFORM UNTIL nist-file-status EQUALS 10
               PERFORM process-a-record
               READ nist-file at end PERFORM all-done
               END-PERFORM.
       GOBACK.

       PROCESS-A-RECORD.
           MOVE nist-record TO work-string.
           IF work-string(73:) NOT EQUAL SPACE
           THEN
               MOVE SPACE to work-string(73:)
               END-IF.
           MOVE SPACE TO work-string(1:6).
           DISPLAY  TRIM(work-string TRAILING) .

       all-done.
           close nist-file.
       goback.
