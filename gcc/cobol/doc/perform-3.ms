.SH
PERFORM Format 3 (exception checking)
.LP
This flow chart expresses the flow of control within the PERFORM
statement.  Normal DECLARATIVES processing happens only if the EC was
enabled before the PERFORM statement and is not handled by the
PERFORM.
.
.PS
boxht = 3/4
boxwid = 1.0

define diamond {
        box invis $1 $2 $3 $4
        line from  last box .s to last box .w
        line to last box .n
        line to last box .e
        line to last box .s
}

Perform: box "PERFORM" "imperative-" "statement-1"
line -> down 1/4 from last box .s
Raised: [ diamond( "EC raised?" ) ]

line -> right from Raised.e "yes" above

Matched: [ diamond( "WHEN" "Matched?" ) ]
line -> right from Matched.e "yes" above
When: box "WHEN" "imperative-" "statement-2"

line -> down 1/4 from Matched.s "\0no" ljust
HaveOther: [ diamond( "OTHER" "clause?" ) ]
line -> right from HaveOther.e "yes" above
Other: box "OTHER" "imperative-" "statement-3"

line right from When.e;  line; line down Here.y - Other.e.y
line -> right from Other.e to last line .end
line -> down
HaveCommon: [ diamond( "\v'2p'COMMON" "clause?" ) ]
line -> left from HaveCommon.w "yes" above
Common: box "COMMON" "imperative-" "statement-4"
line    down 1/4 from Common.s
line    down 1/4 from HaveCommon.s "\0no" ljust 
line -> to 2nd last line .end
line -> down 1/4
Fatal: [ diamond( "EC is" "Fatal?" ) ]
box invis with .nw at Fatal.e + (3/8, 1/6) "or fatal with" "RESUME NEXT STATEMENT"

line -> down 1/4 from Fatal.s "\0yes" ljust
See: box wid 1.75 "See 14.6.13.1.3" "Fatal exception conditions"
line -> down from last box .s
Terminates: box "gcobol binary" "Terminates"

Continue: \
line right 2.0 from Fatal.e "no" above
line to (Here.x, Perform.c.y)
line -> to Perform.e "Continue" above 

line -> down 1/4 from Raised.s "\0no" ljust
Finally: [ diamond( "\v'2p'FINALLY" "clause?" ) ]
line -> down 1 from Finally.s "\0yes" ljust
S5: box  "FINALLY" "imperative-" "statement-5"
line -> down from S5.s
End: box wid 1.25 "END-PERFORM"
line -> down 1/4 from last box .s
Next: box "Next" "Statement"

line right 5/16 from Finally.e "no" above
line to (Here.x, End.c.y)
arrow to End.e

line down from HaveOther.s "\0no" ljust "\0(EC disabled)" ljust
line to (Here.x, Terminates.s.y)
line 1/6
line -> to (Continue.end.x, Here.y) then to Continue.end


                                   
.PE
