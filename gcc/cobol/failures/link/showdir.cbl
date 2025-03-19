        PROGRAM-ID showdir.
        DATA DIVISION.
        WORKING-STORAGE SECTION.
          01 filler.
            05 P usage pointer.
            05 H redefines P usage binary-long-long.
          01 iso-date.
             05 iso_year pic 9999.
             05 value '-'.
             05 iso_mon pic 99.
             05 value '-'.
             05 iso_mday pic 99.
             05 value ' '.
             05 iso_hour pic 99.
             05 value ':'.
             05 iso_min pic 99.
             05 value ':'.
             05 iso_sec pic 99.
          
          77 entry-type pic 999.

        LINKAGE SECTION.
           01 tm.
             05 tm_sec binary-long.   *>  Seconds (0-60)
             05 tm_min binary-long.   *>  Minutes (0-59)
             05 tm_hour binary-long.  *>  Hours (0-23)
             05 tm_mday binary-long.  *>  Day of the month (1-31)
             05 tm_mon binary-long.   *>  Month (0-11)
             05 tm_year binary-long.  *>  Year - 1900
             05 tm_wday binary-long.  *>  Day of the week (Sunday=0)
             05 tm_yday binary-long.  *>  Day in the year
             05 tm_isdst binary-long. *>  Daylight saving time

           01 dirent.
             05 d_ino binary-long-long.  *> Inode number
             05 d_off binary-long-long.
             05 d_reclen binary-short.   *> Length of this record
             05 d_type binary-char unsigned. *> Type of file; not supported
                                         *> by all filesystem types
             05 d_name pic x(256).       *> Null-terminated filename

           
        PROCEDURE DIVISION using tm, dirent.
            display ' TM @ ', address of tm
            display 'ENT @ ', address of dirent.

          SHOW-TM.
            add 1900 to tm_year.
            add 1 to tm_mon.
            move tm_year to iso_year
            move tm_mon  to iso_mon
            move tm_mday to iso_mday
            
            move tm_hour to iso_hour
            move tm_min  to iso_min
            move tm_sec  to iso_sec.

            display iso-date.

          SHOW-ENT.
            display d_name ':'
            display x'09', 'inode: ' d_ino
            display x'09', 'd_off: ' d_off
            display x'09', 'len:   ' d_reclen
      *     display x'09', 'type:  ' d_type
            move d_type to entry-type
            display x'09', 'type:  ' entry-type.
