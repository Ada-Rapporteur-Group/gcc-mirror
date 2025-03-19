IDENTIFICATION DIVISION.
PROGRAM-ID.  Listing16-5.
AUTHOR.  Michael Coughlan.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 Parameters.
   02 StateNum      PIC 99.
   02 StateCode     PIC XX.
   02 StateName     PIC X(14).
   02 StateCapital  PIC X(14).
   02 StatePop      PIC 9(8).
   02 ErrorFlag     PIC 9.

01 idx  PIC 99.

*> Receiving item for TIME: Format is HHMMSSss   s = S/100
01 CurrentTime.
   02 FILLER        PIC 9(4).
   02 Seed          PIC 9(4).
01 RandState        PIC 99.
01 RandChoice       PIC 9.

01 Answer           PIC X(14).
01 PopAnswer        PIC 9(8).
01 MinPop           PIC 9(8).
01 MaxPop           PIC 9(8).
01 PrnStatePop      PIC ZZ,ZZZ,ZZ9.
01 StrLength        PIC 99.


PROCEDURE DIVISION.
Begin.
   ACCEPT CurrentTime FROM TIME
   COMPUTE RandState = 0
   PERFORM 4 TIMES
      ADD 1 TO RandChoice
      COMPUTE RandState  = RandChoice
      CALL "GetStateInfo"
           USING BY REFERENCE  RandState, StateCode, StateName,
                               StateCapital, StatePop, ErrorFlag
      EVALUATE RandChoice
        WHEN      1   PERFORM TestCapitalFromState
        WHEN      2   PERFORM TestCodeFromState
        WHEN      3   PERFORM TestPopFromState
        WHEN      4   PERFORM TestStateFromCapital
      END-EVALUATE
      DISPLAY SPACES
   END-PERFORM
   STOP RUN.


TestCapitalFromState.
   CALL "GetStringLength" USING BY CONTENT StateName
                                BY REFERENCE StrLength
   DISPLAY "What is the capital of " StateName(1:StrLength) "? "
           WITH NO ADVANCING
   ACCEPT Answer
   DISPLAY Answer
   IF FUNCTION UPPER-CASE(Answer) = FUNCTION UPPER-CASE(StateCapital)
      DISPLAY "That is correct"
    ELSE
      DISPLAY "That is incorrect.  The capital of " StateName(1:StrLength)
              " is " StateCapital
   END-IF.


TestCodeFromState.
   CALL "GetStringLength" USING BY CONTENT StateName
                                BY REFERENCE StrLength
   DISPLAY "What is the state code for " StateName(1:StrLength) "? "
           WITH NO ADVANCING
   ACCEPT Answer
   DISPLAY Answer
   IF FUNCTION UPPER-CASE(Answer) = FUNCTION UPPER-CASE(StateCode)
      DISPLAY "That is correct"
    ELSE
      DISPLAY "That is incorrect.  The code for " StateName(1:StrLength)
              " is " StateCode
   END-IF.


TestPopFromState.
   CALL "GetStringLength" USING BY CONTENT StateName
                                BY REFERENCE StrLength
   DISPLAY "What is the population of " StateName(1:StrLength) "? "
           WITH NO ADVANCING
   ACCEPT PopAnswer
   DISPLAY PopAnswer
   COMPUTE MinPop = PopAnswer - (PopAnswer * 0.25)
   COMPUTE MaxPop = PopAnswer + (PopAnswer * 0.25)
   MOVE StatePop TO PrnStatePop

   DISPLAY " Populations: " MinPop " < " StatePop " < " MaxPop

   IF StatePop > MinPop AND < MaxPop
      DISPLAY "That answer is close enough.  The actual population is "  PrnStatePop
    ELSE
      DISPLAY "That is incorrect.  The population of " StateName(1:StrLength)
              " is " PrnStatePop
   END-IF.


TestStateFromCapital.
   CALL "GetStringLength" USING BY CONTENT StateCapital
                                BY REFERENCE StrLength
   DISPLAY "Of what state is " StateCapital(1:StrLength) " the capital? "
           WITH NO ADVANCING
   ACCEPT Answer
   DISPLAY Answer
   IF FUNCTION UPPER-CASE(Answer) = FUNCTION UPPER-CASE(StateName)
      DISPLAY "That is correct"
    ELSE
      DISPLAY "That is incorrect.  The state for " StateCapital(1:StrLength)
              " is " StateName
   END-IF.



IDENTIFICATION DIVISION.
PROGRAM-ID.  GetStringLength IS INITIAL.
AUTHOR.  Michael Coughlan.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 CharCount       PIC 99 VALUE ZEROS.

LINKAGE SECTION.
01 StringParam     PIC X(14).
01 StringLength    PIC 99.

PROCEDURE DIVISION USING StringParam, StringLength.
Begin.
   INSPECT FUNCTION REVERSE(StringParam) TALLYING CharCount
          FOR LEADING SPACES
   COMPUTE StringLength = 14 - CharCount
   EXIT PROGRAM.
END PROGRAM GetStringLength.
END PROGRAM Listing16-5.

IDENTIFICATION DIVISION.
PROGRAM-ID.  GetStateInfo IS INITIAL.
AUTHOR.  Michael Coughlan.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 StatesTable.
   02 StateValues.
      03 FILLER PIC X(38)  VALUE "ALAlabama       Montgomery    04822023".
      03 FILLER PIC X(38)  VALUE "AKAlaska        Juneau        00731449".
      03 FILLER PIC X(38)  VALUE "AZArizona       Phoenix       06553255".
      03 FILLER PIC X(38)  VALUE "ARArkansas      Little Rock   02949131".
      03 FILLER PIC X(38)  VALUE "CACalifornia    Sacramento    38041430".
      03 FILLER PIC X(38)  VALUE "COColorado      Denver        05187582".
      03 FILLER PIC X(38)  VALUE "CTConnecticut   Hartford      03590347".
      03 FILLER PIC X(38)  VALUE "DEDelaware      Dover         00917092".
      03 FILLER PIC X(38)  VALUE "FLFlorida       Tallahassee   19317568".
      03 FILLER PIC X(38)  VALUE "GAGeorgia       Atlanta       09919945".
      03 FILLER PIC X(38)  VALUE "HIHawaii        Honolulu      01392313".
      03 FILLER PIC X(38)  VALUE "IDIdaho         Boise         01595728".
      03 FILLER PIC X(38)  VALUE "ILIllinois      Springfield   12875255".
      03 FILLER PIC X(38)  VALUE "INIndiana       Indianapolis  06537334".
      03 FILLER PIC X(38)  VALUE "IAIowa          Des Moines    03074186".
      03 FILLER PIC X(38)  VALUE "KSKansas        Topeka        02885905".
      03 FILLER PIC X(38)  VALUE "KYKentucky      Frankfort     04380415".
      03 FILLER PIC X(38)  VALUE "LALouisiana     Baton Rouge   04601893".
      03 FILLER PIC X(38)  VALUE "MEMaine         Augusta       01329192".
      03 FILLER PIC X(38)  VALUE "MDMaryland      Annapolis     05884563".
      03 FILLER PIC X(38)  VALUE "MAMassachusetts Boston        06646144".
      03 FILLER PIC X(38)  VALUE "MIMichigan      Lansing       09883360".
      03 FILLER PIC X(38)  VALUE "MNMinnesota     Saint Paul    05379139".
      03 FILLER PIC X(38)  VALUE "MSMississippi   Jackson       02984926".
      03 FILLER PIC X(38)  VALUE "MOMissouri      Jefferson City06021988".
      03 FILLER PIC X(38)  VALUE "MTMontana       Helena        01005141".
      03 FILLER PIC X(38)  VALUE "NENebraska      Lincoln       01855525".
      03 FILLER PIC X(38)  VALUE "NVNevada        Carson City   02758931".
      03 FILLER PIC X(38)  VALUE "NHNew Hampshire Concord       01320718".
      03 FILLER PIC X(38)  VALUE "NJNew Jersey    Trenton       08864590".
      03 FILLER PIC X(38)  VALUE "NMNew Mexico    Santa Fe      02085538".
      03 FILLER PIC X(38)  VALUE "NYNew York      Albany        19570261".
      03 FILLER PIC X(38)  VALUE "NCNorth CarolinaRaleigh       09752073".
      03 FILLER PIC X(38)  VALUE "NDNorth Dakota  Bismarck      00699628".
      03 FILLER PIC X(38)  VALUE "OHOhio          Columbus      11544225".
      03 FILLER PIC X(38)  VALUE "OKOklahoma      Oklahoma City 03814820".
      03 FILLER PIC X(38)  VALUE "OROregon        Salem         03899353".
      03 FILLER PIC X(38)  VALUE "PAPennsylvania  Harrisburg    12763536".
      03 FILLER PIC X(38)  VALUE "RIRhode Island  Providence    01050292".
      03 FILLER PIC X(38)  VALUE "SCSouth CarolinaColumbia      04723723".
      03 FILLER PIC X(38)  VALUE "SDSouth Dakota  Pierre        00833354".
      03 FILLER PIC X(38)  VALUE "TNTennessee     Nashville     06456243".
      03 FILLER PIC X(38)  VALUE "TXTexas         Austin        26059203".
      03 FILLER PIC X(38)  VALUE "UTUtah          Salt Lake City02855287".
      03 FILLER PIC X(38)  VALUE "VTVermont       Montpelier    00626011".
      03 FILLER PIC X(38)  VALUE "VAVirginia      Richmond      08185867".
      03 FILLER PIC X(38)  VALUE "WAWashington    Olympia       06897012".
      03 FILLER PIC X(38)  VALUE "WVWest Virginia Charleston    01855413".
      03 FILLER PIC X(38)  VALUE "WIWisconsin     Madison       05726398".
      03 FILLER PIC X(38)  VALUE "WYWyoming       Cheyenne      00576412".
   02 FILLER REDEFINES StateValues.
      03 State OCCURS 50 TIMES
               INDEXED BY StateIdx.
         04 StateCode     PIC XX.
         04 StateName     PIC X(14).
         04 StateCapital  PIC X(14).
         04 StatePop      PIC 9(8).

LINKAGE SECTION.
01 StateNum-IO         PIC 99.
   88 ValidStateNum    VALUE 1 THRU 50.
01 StateCode-IO        PIC XX.
01 StateName-IO        PIC X(14).
01 StateCapital-IO     PIC X(14).
01 StatePop-IO         PIC 9(8).
01 ErrorFlag           PIC 9.
   88  NoErrorFound    VALUE ZERO.
   88  InvalidStateNum VALUE 1.
   88  NoSearchItems   VALUE 2.
   88  NoSuchStateCode VALUE 3.
   88  NoSuchStateName VALUE 4.
   88  NoSuchCapital   VALUE 5.

PROCEDURE DIVISION USING StateNum-IO, StateCode-IO, StateName-IO,
                         StateCapital-IO, StatePop-IO, ErrorFlag.
Begin.
   SET NoErrorFound TO TRUE
   SET StateIdx TO 1
   EVALUATE            TRUE
     WHEN StateNum-IO      NOT EQUAL ZEROS  PERFORM SearchUsingStateNum
     WHEN StateCode-IO     NOT EQUAL SPACES PERFORM SearchUsingStateCode
     WHEN StateName-IO     NOT EQUAL SPACES PERFORM SearchUsingStateName
     WHEN StateCapital-IO  NOT EQUAL SPACES PERFORM SearchUsingStateCapital
     WHEN OTHER SET NoSearchItems TO TRUE
   END-EVALUATE
   EXIT PROGRAM.

SearchUsingStateNum.
   IF NOT ValidStateNum SET InvalidStateNum TO TRUE
     DISPLAY "Not a ValidStateNum"
     ELSE
       MOVE StateCode(StateNum-IO)    TO StateCode-IO
       MOVE StateName(StateNum-IO)    TO StateName-IO
       MOVE StateCapital(StateNum-IO) TO StateCapital-IO
       MOVE StatePop(StateNum-IO)     TO StatePop-IO
   END-IF.


SearchUsingStateCode.
   SEARCH State
       AT END SET NoSuchStateCode TO TRUE
       WHEN FUNCTION UPPER-CASE(StateCode(StateIdx)) EQUAL TO
            FUNCTION UPPER-CASE(StateCode-IO)
            SET StateNum-IO  TO StateIdx
            MOVE StateCode(StateIdx)    TO StateCode-IO
            MOVE StateName(StateIdx)    TO StateName-IO
            MOVE StateCapital(StateIdx) TO StateCapital-IO
            MOVE StatePop(StateIdx)     TO StatePop-IO
    END-SEARCH.

SearchUsingStateName.
   SEARCH State
       AT END SET NoSuchStateName TO TRUE
       WHEN FUNCTION UPPER-CASE(StateName(StateIdx)) EQUAL TO
            FUNCTION UPPER-CASE(StateName-IO)
            SET StateNum-IO  TO StateIdx
            MOVE StateCode(StateIdx)    TO StateCode-IO
            MOVE StateName(StateIdx)    TO StateName-IO
            MOVE StateCapital(StateIdx) TO StateCapital-IO
            MOVE StatePop(StateIdx)     TO StatePop-IO
    END-SEARCH.

SearchUsingStateCapital.
   SEARCH State
       AT END SET NoSuchCapital TO TRUE
       WHEN FUNCTION UPPER-CASE(StateCapital(StateIdx)) EQUAL TO
            FUNCTION UPPER-CASE(StateCapital-IO)
            SET StateNum-IO  TO StateIdx
            MOVE StateCode(StateIdx)    TO StateCode-IO
            MOVE StateName(StateIdx)    TO StateName-IO
            MOVE StateCapital(StateIdx) TO StateCapital-IO
            MOVE StatePop(StateIdx)     TO StatePop-IO
    END-SEARCH.

END PROGRAM GetStateInfo.

