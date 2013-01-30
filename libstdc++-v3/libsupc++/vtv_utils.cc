/* Copyright (C) 2012
   Free Software Foundation

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* This file is part of the vtable verication runtime library (see
   comments in vtv_rts.cc for more information about vtable
   verification).  This file contains log file utilities.  */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "vtv_utils.h"

/* This is the directory into which all vtable verication log files
   get written.  */
static const char * const logs_dir = "/tmp/vtv_logs";


/* This function takes the NAME of a log file to open, attempts to
   open it in the logs_dir directory, and returns the resulting file
   decriptor.  */

int
vtv_open_log (const char *name)
{
  char log_name[256];
  snprintf (log_name, sizeof (log_name), "%s/%s", logs_dir, name);
  mkdir (logs_dir, S_IRWXU);
  int fd = open (log_name, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
  if (fd == -1)
    vtv_add_to_log (2, "Cannot open log file %s %s\n", name,
		    strerror (errno));
  return fd;
}

/* This function takes a file descriptor (FD) and a string (STR) and
   tries to write the string to the file.  */

static int
vtv_log_write (int fd, const char *str)
{
  if (write (fd, str, strlen (str)) != -1)
    return 0;

  if (fd != 2) /* Make sure we dont get in a loop.  */
    vtv_add_to_log (2, "Error writing to log: %s\n", strerror (errno));
  return -1;
}


/* This function takes a file decriptor (LOG_FILE) and an output
 format string (FORMAT), followed by zero or more print format
 arguments (the same as fprintf, for example).  It gets the current
 process ID and PPID, pre-pends them to the formatted message, and
 writes write it out to the log file referenced by LOG_FILE via calles
 to vtv_log_write.  */

int
vtv_add_to_log (int log_file, const char * format, ...)
{
  /* We dont want to dynamically allocate this buffer. This should be
     more than enough in most cases. It if isn't we are careful not to
     do a buffer overflow.  */
  char output[1024];

  va_list ap;
  va_start (ap, format);

  snprintf (output, sizeof (output), "VTV: PID=%d PPID=%d ", getpid (),
	    getppid ());
  vtv_log_write (log_file, output);
  vsnprintf (output, sizeof (output), format, ap);
  vtv_log_write (log_file, output);

  /* fdatasync is quite expensive. Only enable if you suspect you are
     loosing log data in in a program crash?  */
  /*  fdatasync(log_file);  */

  return 0;
}
