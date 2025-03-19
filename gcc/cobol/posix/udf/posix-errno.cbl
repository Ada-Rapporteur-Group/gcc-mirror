       Identification Division.
       Function-ID. posix-errno.

       Data Division.
       Linkage Section.
       77 Return-Value Binary-Long.
       01 Error-Msg PIC X ANY LENGTH.

       Procedure Division
           using Error-Msg
           Returning Return-Value.
       CALL "posix_errno"
           returning Return-Value.
       CALL "strerror"
           using by value Return-Value
           returning error-msg.
       Goback.
       END FUNCTION posix-errno.
