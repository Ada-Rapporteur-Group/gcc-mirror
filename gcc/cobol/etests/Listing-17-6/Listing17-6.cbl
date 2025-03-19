IDENTIFICATION DIVISION.
PROGRAM-ID.  Listing17-6.
AUTHOR. Michael Coughlan.

ENVIRONMENT DIVISION.
INPUT-OUTPUT SECTION.
    SELECT FilmFile ASSIGN TO "Listing17-6Film.DAT"
        ORGANIZATION IS INDEXED
        ACCESS MODE IS DYNAMIC
        RECORD KEY IS FilmId-FF
        ALTERNATE RECORD KEY IS FilmTitle-FF
                     WITH DUPLICATES
        ALTERNATE RECORD KEY IS DirectorId-FF
                     WITH DUPLICATES
        FILE STATUS IS FilmStatus.

   SELECT DirectorFile ASSIGN TO "Listing17-6Dir.DAT"
        ORGANIZATION IS INDEXED
        ACCESS MODE IS DYNAMIC
        RECORD KEY IS DirectorId-DF
        ALTERNATE RECORD KEY IS DirectorSurname-DF
        FILE STATUS IS DirectorStatus.

DATA DIVISION.
FILE SECTION.
FD FilmFile.
01 FilmRec-FF.
   88 EndOfFilms     VALUE HIGH-VALUES.
   02 FilmId-FF            PIC 9(7).
   02 FilmTitle-FF         PIC X(40).
   02 DirectorId-FF        PIC 999.

FD DirectorFile.
01 DirectorRec-DF.
   88 EndOfDirectors  VALUE HIGH-VALUES.
   02 DirectorId-DF         PIC 999.
   02 DirectorSurname-DF    PIC X(20).


WORKING-STORAGE SECTION.
01 AllStatusFlags  VALUE ZEROS.
   02 FilmStatus            PIC XX.
      88 FilmOk    VALUE "02", "00".

   02 DirectorStatus        PIC XX.

01 DirectorName             PIC X(20).


PROCEDURE DIVISION.
Begin.
    PERFORM BuildFilmFile
    PERFORM BuildDirectorFile

    OPEN INPUT FilmFile
    OPEN INPUT DirectorFile

    PERFORM CheckDirector
    PERFORM CheckDirector
    PERFORM CheckDirector
    PERFORM CheckDirector

    CLOSE FilmFile
    CLOSE DirectorFile
    STOP RUN.

CheckDirector.
    DISPLAY "Please enter the director surname :- "
            WITH NO ADVANCING
    ACCEPT DirectorSurname-DF
    DISPLAY "Entered " DirectorSurname-DF
    READ DirectorFile
        KEY IS DirectorSurname-DF
        INVALID KEY DISPLAY "-DF ERROR Status = " DirectorStatus
        NOT INVALID KEY PERFORM GetFilmsForDirector
    END-READ.

GetFilmsForDirector.
    MOVE DirectorId-DF TO DirectorId-FF
    READ FilmFile
        KEY IS DirectorId-FF
        INVALID KEY DISPLAY "-FF ERROR Status = " FilmStatus
    END-READ
    IF FilmOk
       PERFORM UNTIL DirectorId-DF NOT Equal TO DirectorId-FF OR EndOfFilms
          DISPLAY DirectorId-DF SPACE DirectorSurname-DF SPACE FilmId-FF SPACE FilmTitle-FF
          READ FilmFile NEXT RECORD
             AT END SET EndOfFilms TO TRUE
          END-READ
       END-PERFORM
    END-IF.

BuildFilmFile.
    OPEN OUTPUT FilmFile
    MOVE "8805261Master and Commander                    012" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805288Cape Fear                               033" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805296Overboard                               004" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805326The Color Purple                        005" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805334Desperado                               002" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805385First Knight                            003" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805415Pulp Fiction                            002" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805474Ghost                                   003" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805504Jackie Brown                            002" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805806Carlito's Way                           015" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8812438The Untouchables                        015" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8822334Blade Runner                            023" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8713669Alien                                   023" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805075Lord of the Rings:Return of the King    009" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805091Lord of the Rings:Fellowship of the Ring009" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805105Mission Impossible                      015" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805121Jaws                                    005" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805156Carrie                                  015" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805164Lord of the Rings:The Two Towers        009" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805229Saving Private Ryan                     005" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805245Catch Me If You Can                     005" TO FilmRec-FF WRITE FILE FilmFile
    MOVE "8805253Heavenly Creatures                      009" TO FilmRec-FF WRITE FILE FilmFile
    CLOSE FilmFile.

BuildDirectorFile.
    OPEN OUTPUT DirectorFile
    MOVE "002Tarantino           " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "003Zucker              " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "004Marshall            " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "005Spielberg           " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "009Jackson             " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "012Weir                " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "015De Palma            " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "023Scott               " TO DirectorRec-DF WRITE FILE DirectorFile
    MOVE "033Scorsese            " TO DirectorRec-DF WRITE FILE DirectorFile
    CLOSE DirectorFile.
