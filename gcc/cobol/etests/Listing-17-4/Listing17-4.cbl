IDENTIFICATION DIVISION.
PROGRAM-ID.  Listing17-4.
AUTHOR.  Michael Coughlan.
*Reads the file sequentially and then directly on any key

ENVIRONMENT DIVISION.
INPUT-OUTPUT SECTION.
    SELECT FilmFile ASSIGN TO "Listing17-4Film.DAT"
        ORGANIZATION IS INDEXED
        ACCESS MODE IS DYNAMIC
        RECORD KEY IS FilmId
        ALTERNATE RECORD KEY IS FilmTitle
                     WITH DUPLICATES
        ALTERNATE RECORD KEY IS DirectorId
                     WITH DUPLICATES
        FILE STATUS IS FilmStatus.

DATA DIVISION.
FILE SECTION.
FD FilmFile.
01 FilmRec.
   88 EndOfFilms            VALUE HIGH-VALUES.
   02 FilmId                PIC 9(7).
   02 FilmTitle             PIC X(40).
   02 DirectorId            PIC 999.


WORKING-STORAGE SECTION.
01 FilmStatus               PIC XX.
   88 FilmOK VALUE ZEROS.

01 RequiredSequence         PIC 9.
   88 FilmIdSequence        VALUE 1.
   88 FilmTitleSequence     VALUE 2.
   88 DirectorIdSequence    VALUE 3.

01 PrevDirectorId           PIC 999.

PROCEDURE DIVISION.
Begin.
    PERFORM CreateTheTestFile

    OPEN INPUT FilmFile
    PERFORM Sequentially.
    PERFORM Sequentially.
    PERFORM Sequentially.
    PERFORM Lookup.
    PERFORM Lookup.
    PERFORM Lookup.
    PERFORM Lookup.
    PERFORM Lookup.
    PERFORM Lookup.

    CLOSE FilmFile
    STOP RUN.

Sequentially.
    DISPLAY "*** Get Records Sequentially ***"
    DISPLAY "Enter key : 1 = FilmId, 2 = FilmTitle, 3 = DirectorId - "
            WITH NO ADVANCING.
    ACCEPT RequiredSequence.
    DISPLAY "Value entered: " RequiredSequence

    EVALUATE TRUE
       WHEN FilmIdSequence       PERFORM DisplayFilmData
       WHEN FilmTitleSequence    MOVE SPACES TO FilmTitle
                                 START FilmFile KEY IS GREATER THAN FilmTitle
                                      INVALID KEY DISPLAY "FilmStatus = " FilmStatus
                                 END-START
                                 PERFORM DisplayFilmData
       WHEN DirectorIdSequence   MOVE ZEROS TO DirectorId
                                 START FilmFile KEY IS GREATER THAN DirectorId
                                      INVALID KEY DISPLAY "FilmStatus = " FilmStatus
                                 END-START
                                 PERFORM DisplayFilmData
    END-EVALUATE.

Lookup.
    DISPLAY SPACES
    DISPLAY "*** Get Records Directly ***"
    DISPLAY "Enter key : 1 = FilmId, 2 = FilmTitle, 3 = DirectorId - "
            WITH NO ADVANCING.
    ACCEPT RequiredSequence.
    DISPLAY "Value entered: "  RequiredSequence
    EVALUATE TRUE
       WHEN FilmIdSequence       PERFORM GetFilmByFilmId
       WHEN FilmTitleSequence    PERFORM GetFilmByFilmTitle
       WHEN DirectorIdSequence   PERFORM GetFilmByDirectorId
    END-EVALUATE.

DisplayFilmData.
   READ FilmFile NEXT RECORD
      AT END SET EndOfFilms TO TRUE
   END-READ
   PERFORM UNTIL EndOfFilms
      DISPLAY FilmId SPACE FilmTitle SPACE DirectorId
      READ FilmFile NEXT RECORD
         AT END SET EndOfFilms TO TRUE
      END-READ
   END-PERFORM.

GetFilmByFilmId.
   DISPLAY "Enter the FilmId - " WITH NO ADVANCING
   ACCEPT FilmId
   DISPLAY "Value entered: "  FilmId
   READ FilmFile
      KEY IS FilmId
      INVALID KEY DISPLAY "Film not found - " FilmStatus
      NOT INVALID KEY DISPLAY FilmId SPACE FilmTitle SPACE DirectorId
   END-READ.


GetFilmByFilmTitle.
   DISPLAY "Enter the FilmTitle - " WITH NO ADVANCING
   ACCEPT FilmTitle
   DISPLAY "Value entered: "  FilmTitle
   READ FilmFile
      KEY IS FilmTitle
      INVALID KEY DISPLAY "Film not found - " FilmStatus
      NOT INVALID KEY DISPLAY FilmId SPACE FilmTitle SPACE DirectorId
   END-READ.


GetFilmByDirectorId.
   DISPLAY "Enter the Director Id - " WITH NO ADVANCING
   ACCEPT DirectorId
   DISPLAY "Value entered: "  DirectorId
   READ FilmFile
      KEY IS DirectorId
      INVALID KEY DISPLAY "Film not found - " FilmStatus
      NOT INVALID KEY DISPLAY FilmId SPACE FilmTitle SPACE DirectorId
   END-READ.

CreateTheTestFile.
    OPEN OUTPUT FilmFile
    MOVE "8805261Master and Commander                    012" TO FilmRec WRITE FilmRec
    MOVE "8805288Cape Fear                               033" TO FilmRec WRITE FilmRec
    MOVE "8805296Overboard                               004" TO FilmRec WRITE FilmRec
    MOVE "8805326The Color Purple                        005" TO FilmRec WRITE FilmRec
    MOVE "8805334Desperado                               002" TO FilmRec WRITE FilmRec
    MOVE "8805385First Knight                            003" TO FilmRec WRITE FilmRec
    MOVE "8805415Pulp Fiction                            002" TO FilmRec WRITE FilmRec
    MOVE "8805474Ghost                                   003" TO FilmRec WRITE FilmRec
    MOVE "8805504Jackie Brown                            002" TO FilmRec WRITE FilmRec
    MOVE "8805806Carlito's Way                           015" TO FilmRec WRITE FilmRec
    MOVE "8812438The Untouchables                        015" TO FilmRec WRITE FilmRec
    MOVE "8822334Blade Runner                            023" TO FilmRec WRITE FilmRec
    MOVE "8713669Alien                                   023" TO FilmRec WRITE FilmRec
    MOVE "8805075Lord of the Rings:Return of the King    009" TO FilmRec WRITE FilmRec
    MOVE "8805091Lord of the Rings:Fellowship of the Ring009" TO FilmRec WRITE FilmRec
    MOVE "8805105Mission Impossible                      015" TO FilmRec WRITE FilmRec
    MOVE "8805121Jaws                                    005" TO FilmRec WRITE FilmRec
    MOVE "8805156Carrie                                  015" TO FilmRec WRITE FilmRec
    MOVE "8805164Lord of the Rings:The Two Towers        009" TO FilmRec WRITE FilmRec
    MOVE "8805229Saving Private Ryan                     005" TO FilmRec WRITE FilmRec
    MOVE "8805245Catch Me If You Can                     005" TO FilmRec WRITE FilmRec
    MOVE "8805253Heavenly Creatures                      009" TO FilmRec WRITE FilmRec
    CLOSE FilmFile.
