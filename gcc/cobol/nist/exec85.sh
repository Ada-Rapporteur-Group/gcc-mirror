#! /bin/sh

#002500*    SELECT  OPTIONAL POPULATION-FILE                             EXEC84.2
#002500     SELECT POPULATION-FILE                                       EXEC84.2
#002700*    XXXXX001.                                                    EXEC84.2
#002700     "newcob.val"                                                 EXEC84.2
#003000*    XXXXX002                                                     EXEC84.2
#003000     "XXXXX002"                                                   EXEC84.2
#003100*    ORGANIZATION SEQUENTIAL.                                     EXEC84.2
#003100     ORGANIZATION LINE SEQUENTIAL                                 EXEC84.2
#003400*    XXXXX003.                                                    EXEC84.2
#003400     "XXXXX003".                                                  EXEC84.2
#003700*    XXXXX055.                                                    EXEC84.2
#003700     "XXXXX055".                                                  EXEC84.2
#004000*    XXXXX058.                                                    EXEC84.2
#004000     "make_pop_linux.txt"                                         EXEC84.2

XXXXX001=../newcob.val
XXXXX002=SOURCE-COBOL-PROGRAMS
# ORGANIZATION SEQUENTIAL.
# ORGANIZATION LINE SEQUENTIAL
XXXXX003=XXXXX003
XXXXX055=PRINT-FILE
XXXXX058=$(dirname $0)/nc.conf

exec85=${1:-$(dirname $0)/obj/EXEC85}

export XXXXX001 XXXXX002 XXXXX003 XXXXX055 XXXXX058

# Limit output to 100 1K blocks. 
ulimit -f 100
echo running: $exec85 $XXXXX001 $XXXXX002 $XXXXX003 $XXXXX055 $XXXXX058

set -x
exec $exec85
