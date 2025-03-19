#WRITE

## When the file's ORGANIZATION IS LINE SEQUENTIAL

The main characteristic of the LINE SEQUENTIAL format is that trailing spaces in the record specified for output are trimmed away. Another characteristic is that unless told otherwise by an ADVANCING ZERO LINES clause, every write ends with a <newline> character.

When a WRITE ... AFTER ADVANCING N LINES follows a WRITE that ends with a <newline> or <formfeed>, the value of N is reduced by one.

Note: The contents of the record being written are not analyzed; any control characters contained in the record are sent to the file without any additional processing for end-of-line purposes.

Example:

WRITE xxx BEFORE ADVANCING ZERO LINES
or
WRITE xxx AFTER ADVANCING ZERO LINES

Result: xxx

Example:

WRITE xxx
or
WRITE xxx BEFORE ADVANCING 1 LINE

Result: xxx<newline>

Example:

WRITE xxx AFTER ADVANCING 1 LINE

Result: <newline>xxx<newline>

Example:

WRITE xxx AFTER ADVANCING 1 LINE
WRITE yyy AFTER ADVANCING 1 LINE
WRITE zzz AFTER ADVANCING 1 LINE

Result: <newline>xxx<newline>yyy<newline>zzz<newline>

Example:

WRITE xxx AFTER ADVANCING PAGE

Result: <formfeed>xxx<newline>

Note: In this case, there is no way to suppress the newline following the text

Example:

WRITE xxx BEFORE ADVANCING PAGE

Result: xxx<formfeed>

## When the file's ORGANIZATION IS SEQUENTIAL

Trailing spaces in the record being written are not trimmed away.

BEFORE and AFTER ADVANCING are treated more literally, without any effort made to end the file with a <newline>

Example:

WRITE xxx BEFORE ADVANCING ZERO LINES
or
WRITE xxx AFTER ADVANCING ZERO LINES
or
WRITE xxx

Result: xxx

Example:

WRITE xxx BEFORE ADVANCING 1 LINE

Result: xxx<newline>

Example:

WRITE xxx AFTER ADVANCING 1 LINE

Result: <newline>xxx

Example:

WRITE xxx AFTER ADVANCING 1 LINE
WRITE yyy AFTER ADVANCING 1 LINE
WRITE zzz AFTER ADVANCING 1 LINE

Result: <newline>xxx<newline>yyy<newline>zzz

Example:

WRITE xxx AFTER ADVANCING PAGE

Result: <formfeed>xxx

Example:

WRITE xxx BEFORE ADVANCING PAGE

Result: xxx<formfeed>
