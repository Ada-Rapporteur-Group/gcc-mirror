//
// 
//    Copyright (C) 2007-2008 Free Software Foundation, Inc.
//    Contributed by STMicroelectronics
// 
// This file is part of GCC.
// 
// GCC is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2, or (at your option) any later
// version.
// 
// GCC is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GCC; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.

using System;
using System.IO;
using System.Net.Sockets;
using System.Security;
using System.Security.Principal;
using System.Security.AccessControl;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Collections;

public class MSCorelibWrapper
{

    private static int my_errno;

    private static long initial_ticks;

    private static Stream[] streams_table;
    private static byte[] buffer;
    private const int buffer_size = 4 * 1024; // 4Kbytes


    // The following constant must be kept in sync with
    // definitions in stdio.h
    private const int FopenMax = 8;

    // The following constants must be kept in sync with
    // definitions in bits/libstd_fcntl.h
    private const int __LIBSTD_O_RDONLY  = 0x0001;
    private const int __LIBSTD_O_WRONLY  = 0x0002;
    private const int __LIBSTD_O_RDWR    = 0x0004;
    private const int __LIBSTD_O_APPEND  = 0x0008;
    private const int __LIBSTD_O_CREAT   = 0x0100;
    private const int __LIBSTD_O_TRUNC   = 0x0200;
    private const int __LIBSTD_O_EXCL    = 0x0400;
    private const int __LIBSTD_O_TEXT    = 0x4000;
    private const int __LIBSTD_O_BINARY  = 0x8000;

    // The following constants must be kept in sync with
    // definitions in bits/libstd_math.h
    private const int __LIBSTD_FP_INFINITE  = 0;
    private const int __LIBSTD_FP_NAN       = 1;
    private const int __LIBSTD_FP_NORMAL    = 2;
    private const int __LIBSTD_FP_SUBNORMAL = 3;
    private const int __LIBSTD_FP_ZERO      = 4;

    // The following constants must be kept in sync with
    // definitions in bits/libstd_stdio.h
    private const int __LIBSTD_SEEK_SET = 0;
    private const int __LIBSTD_SEEK_CUR = 1;
    private const int __LIBSTD_SEEK_END = 2;

    // The following constants must be kept in sync with
    // definitions in bits/libstd_errno.h
    private const int __LIBSTD_ENOENT       = 2;
    private const int __LIBSTD_EINTR        = 4;
    private const int __LIBSTD_EIO          = 5;
    private const int __LIBSTD_EBADF        = 9;
    private const int __LIBSTD_EAGAIN       = 11;
    private const int __LIBSTD_ENOMEM       = 12;
    private const int __LIBSTD_EACCES       = 13;
    private const int __LIBSTD_EFAULT       = 14;
    private const int __LIBSTD_EEXIST       = 17;
    private const int __LIBSTD_ENOTDIR      = 20;
    private const int __LIBSTD_EINVAL       = 22;
    private const int __LIBSTD_EMFILE       = 24;
    private const int __LIBSTD_ESPIPE       = 29;
    private const int __LIBSTD_EDOM         = 33;
    private const int __LIBSTD_ERANGE       = 34;
    private const int __LIBSTD_ENAMETOOLONG = 36;
    private const int __LIBSTD_EILSEQ       = 88;
    private const int __LIBSTD_ENOTSUP      = 134;
    private const int __LIBSTD_ENOSYS       = 333;

    /* file stat flags (st_mode) */
    /* in sync with sys/stat.h */
    private const int __LIBSTD_S_IFDIR      = 0x4000;
    private const int __LIBSTD_S_IFREG      = 0x8000;
    private const int __LIBSTD_S_IREAD      = 0x0100;
    private const int __LIBSTD_S_IWRITE     = 0x0080;
    private const int __LIBSTD_S_IEXEC      = 0x0040;

    /* sysconf variable names */
    /* in sync with bits/confname.h */
    private const int __LIBSTD_SC_CLK_TCK   = 2;
    
    /* Value of sysconf (SC_CLK_TCK), consistent with
     * usual values in POSIX. (used by gettimes) */
    private const int _SC_CLK_TCK_VALUE = 100;

    static MSCorelibWrapper()
    {
        streams_table = new Stream[FopenMax];
        // Init the standard streams
        streams_table[0] = Console.OpenStandardInput();
        streams_table[1] = Console.OpenStandardOutput();
        streams_table[2] = Console.OpenStandardError();
        // Init the clock support
        initial_ticks = DateTime.UtcNow.Ticks;
        // Init the internal buffer array
        buffer = new byte[buffer_size];

        /* Matching (pseudo)POSIX <--> .NET users */
        InitUsers ();
    }

    private static int allocateHandle(Stream stream)
    {
        int i;
        for(i=0;i<FopenMax;++i) {
            if (streams_table[i] == null) {
                streams_table[i] = stream;
                return i;
            }
        }
        return -1;
    }

    private static Stream getHandle(int fd)
    {
        Stream result = null;
        if (fd >= 0 && fd < FopenMax)
            result = streams_table[fd];
        if (result == null)
            my_errno = __LIBSTD_EBADF;
        return result;
    }

    private static void releaseHandle(int fd)
    {
        streams_table[fd] = null;
    }

    unsafe public static int open(sbyte* path, int oflag)
    {
        FileStream stream = null;
        FileMode mode;
        FileAccess access;
        IntPtr ptr_int_ptr = new IntPtr(path);
        String file_name = Marshal.PtrToStringAnsi(ptr_int_ptr);
        int handle = -1;
        bool seek_to_end = false;

        if (path == null) {
            my_errno = __LIBSTD_EFAULT;
            return -1;
        }

        if ((oflag & __LIBSTD_O_WRONLY) != 0) {
            access = FileAccess.Write;
        } else if ((oflag & __LIBSTD_O_RDWR) != 0) {
            access = FileAccess.ReadWrite;
        } else {
            access = FileAccess.Read;
        }

        // The order of these tests cannot be freely reordered.
        if ((oflag & __LIBSTD_O_APPEND) != 0) {
            mode = FileMode.Append;
            if (access == FileAccess.ReadWrite) {
                // This mode (a+) is not directly supported by .NET and we need to simulate it
                mode = FileMode.OpenOrCreate;
                seek_to_end = true;
            }
        } else if ((oflag & __LIBSTD_O_CREAT) != 0) {
            mode = FileMode.Create;
        } else if ((oflag & __LIBSTD_O_TRUNC) != 0) {
            mode = FileMode.Truncate;
        } else {
            mode = FileMode.Open;
        }

        try {
            stream = File.Open(file_name, mode, access);
            if (seek_to_end) {
                stream.Seek(0, SeekOrigin.End);
            }
        }
        catch(SecurityException) {
            my_errno = __LIBSTD_EACCES;
            return -1;
        }
        catch(FileNotFoundException) {
            my_errno = __LIBSTD_ENOENT;
            return -1;
        }
        catch(DirectoryNotFoundException) {
            my_errno = __LIBSTD_ENOTDIR;
            return -1;
        }
        catch(PathTooLongException) {
            my_errno = __LIBSTD_ENAMETOOLONG;
            return -1;
        }
        catch(UnauthorizedAccessException) {
            my_errno = __LIBSTD_EACCES;
            return -1;
        }
        catch(IOException) {
            // Could be anything, but EEXIST is most likely.
            my_errno = __LIBSTD_EEXIST;
            return -1;
        }

        handle = allocateHandle(stream);

        if (handle == -1)
            my_errno = __LIBSTD_EMFILE;

        return handle;
    }

    unsafe public static int write(int filedes, void* buf, int nbytes)
    {
        Stream stream = getHandle(filedes);
        int tot_written = 0;
        int j = 0;

        if(stream == null) {
            /* my_errno already set */
            return -1;
        }
        else if (nbytes == 0) {
            return 0;
        }
        else if (buf == null) {
            my_errno = __LIBSTD_EFAULT;
            return -1;
        }

        try {
            do {
                int size = nbytes < buffer_size ? nbytes : buffer_size;

                for(int i=0;i<size;++i, ++j) {
                    buffer[i] = ((byte*)buf)[j];
                }

                stream.Write(buffer, 0, size);

                tot_written += size;
                nbytes -= size;
            } while(nbytes > 0);
        }
        catch(IOException) {
            my_errno = __LIBSTD_EIO;
            return -1;
        }
        catch(ObjectDisposedException) {
            my_errno = __LIBSTD_EBADF;
            return -1;
        }
        catch(NotSupportedException) {
            my_errno = __LIBSTD_EINVAL;
            return -1;
        }
        catch(SocketException) {
            my_errno = __LIBSTD_EAGAIN;
            return -1;
        }

        return tot_written;
    }

    unsafe public static int read(int filedes, void* buf, int nbytes)
    {
        Stream stream = getHandle(filedes);
        int tot_read = 0;
        int j = 0;

        if(stream == null) {
            /* my_errno already set */
            return -1;
        }
        else if (nbytes == 0) {
            return 0;
        }
        else if (buf == null) {
            my_errno = __LIBSTD_EFAULT;
            return -1;
        }

        try {
            do {
                int size = nbytes < buffer_size ? nbytes : buffer_size;
                int actually_read;

                actually_read = stream.Read(buffer, 0, size);
                tot_read += actually_read;
                nbytes -= actually_read;
                for(int i=0;i<actually_read;++i, ++j) {
                    ((byte*)buf)[j] = buffer[i];
                }
                // Check if we reached the EOF
                if (actually_read < size)
                    return tot_read;
            } while(nbytes > 0);
        }
        catch(IOException) {
            my_errno = __LIBSTD_EIO;
            return -1;
        }
        catch(ObjectDisposedException) {
            my_errno = __LIBSTD_EBADF;
            return -1;
        }
        catch(NotSupportedException) {
            my_errno = __LIBSTD_EINVAL;
            return -1;
        }
        catch(SocketException) {
            my_errno = __LIBSTD_EAGAIN;
            return -1;
        }

        return tot_read;
    }

    public static int close(int filedes)
    {
        Stream stream = getHandle(filedes);

        if(stream != null) {
            stream.Close();
            releaseHandle(filedes);
            return 0;
        }
        my_errno = __LIBSTD_ENOSYS;
        return -1;
    }

    unsafe public static int filesize(sbyte* path)
    {
        int result;
        IntPtr ptr_int_ptr = new IntPtr(path);
        String file_name = Marshal.PtrToStringAnsi(ptr_int_ptr);
        try {
            FileInfo info = new FileInfo(file_name);
            result = (int)info.Length;
        }
        catch(Exception) {
            my_errno = __LIBSTD_ENOSYS;
            result = -1;
        }
        return result;
    }

    /* returns the number of elapsed secons since epoch in UTC
     * format until the last access */
    unsafe public static long file_lastaccess_sutc(sbyte* path)
    {
        DateTime epoch = new DateTime(1970, 1, 1);
        IntPtr ptr_int_ptr = new IntPtr(path);
        String file_name = Marshal.PtrToStringAnsi(ptr_int_ptr);        
        long result;

        try {
            FileInfo info = new FileInfo(file_name);
            result = (long) (info.LastAccessTimeUtc - epoch).TotalSeconds;
        }
        catch(Exception) {
            my_errno = __LIBSTD_ENOSYS;
            result = -1;
        }
        return result;
    }

    /* returns the number of elapsed secons since epoch in UTC
     * format until the last write */
    unsafe public static long file_lastwrite_sutc(sbyte* path)
    {
        DateTime epoch = new DateTime(1970, 1, 1);
        IntPtr ptr_int_ptr = new IntPtr(path);
        String file_name = Marshal.PtrToStringAnsi(ptr_int_ptr);        
        long result;

        try {
            FileInfo info = new FileInfo(file_name);
            result = (long) (info.LastWriteTimeUtc - epoch).TotalSeconds;
        }
        catch(Exception) {
            my_errno = __LIBSTD_ENOSYS;
            result = -1;
        }
        return result;
    }

    /* returns the number of elapsed secons since epoch in UTC
     * format until the file creation */
    unsafe public static long file_filecreation_sutc(sbyte* path)
    {
        DateTime epoch = new DateTime(1970, 1, 1);
        IntPtr ptr_int_ptr = new IntPtr(path);
        String file_name = Marshal.PtrToStringAnsi(ptr_int_ptr);        
        long result;

        try {
            FileInfo info = new FileInfo(file_name);
            result = (long) (info.CreationTimeUtc - epoch).TotalSeconds;
        }
        catch(Exception) {
            my_errno = __LIBSTD_ENOSYS;
            result = -1;
        }
        return result;
    }

    unsafe public static int file_mode_flags(sbyte* path)
    {
        IntPtr ptr_int_ptr = new IntPtr(path);
        String file_name = Marshal.PtrToStringAnsi(ptr_int_ptr);        
        int flags = 0;

        Console.Error.Write("Warning: some features of stat() are not supported\n");

        /* File atributres */
        FileAttributes attr = File.GetAttributes (file_name);
        if ((attr & FileAttributes.Directory) == FileAttributes.Directory)
          flags |= __LIBSTD_S_IFDIR;
        if ((attr & FileAttributes.Normal) == FileAttributes.Normal)
          flags |= __LIBSTD_S_IFREG;

        /* Access control attributes */
        try {
          FileSecurity fSecurity = File.GetAccessControl(file_name);
          AuthorizationRuleCollection rules = fSecurity.GetAccessRules (true, true, typeof(NTAccount));
          for (int i = 0; i < rules.Count; i++)
            {
              FileSystemAccessRule rule = (FileSystemAccessRule)rules[i];
              if (rule.FileSystemRights == FileSystemRights.ReadData
                 || rule.FileSystemRights == FileSystemRights.FullControl
                 || rule.FileSystemRights == FileSystemRights.Read
                 || rule.FileSystemRights == FileSystemRights.ReadAndExecute
                 || rule.FileSystemRights == FileSystemRights.Modify)
                flags |= __LIBSTD_S_IREAD;
              if (rule.FileSystemRights == FileSystemRights.WriteData
                 || rule.FileSystemRights == FileSystemRights.CreateDirectories
                 || rule.FileSystemRights == FileSystemRights.CreateFiles
                 || rule.FileSystemRights == FileSystemRights.DeleteSubdirectoriesAndFiles
                 || rule.FileSystemRights == FileSystemRights.Delete
                 || rule.FileSystemRights == FileSystemRights.FullControl
                 || rule.FileSystemRights == FileSystemRights.Write
                 || rule.FileSystemRights == FileSystemRights.Modify)
                flags |= __LIBSTD_S_IWRITE;

              if (rule.FileSystemRights == FileSystemRights.ListDirectory
                 || rule.FileSystemRights == FileSystemRights.Traverse
                 || rule.FileSystemRights == FileSystemRights.ExecuteFile
                 || rule.FileSystemRights == FileSystemRights.FullControl
                 || rule.FileSystemRights == FileSystemRights.ReadAndExecute)
                flags |= __LIBSTD_S_IEXEC;
            }
        } catch (System.NotImplementedException e) {
          flags |= __LIBSTD_S_IREAD;
          if ((attr & FileAttributes.ReadOnly) != FileAttributes.ReadOnly)
            flags |= __LIBSTD_S_IWRITE;
          if ((flags & __LIBSTD_S_IFDIR) == __LIBSTD_S_IFDIR)
            flags |= __LIBSTD_S_IEXEC;

          Console.Error.Write("Warning: Unable to get file mode (default: S_IREAD and S_IWRITE if not ReadOnly)\n  Exception: ");
          Console.WriteLine(e.Message);
        }
        return flags;
    } 

    unsafe public static int file_uid(sbyte* path)
    {
      return 0;
    }

    unsafe public static int file_gid(sbyte* path)
    {
      return 0;
    }


    public static int lseek(int filedes, int offset, int whence)
    {
        Stream stream = getHandle(filedes);
        SeekOrigin origin;

        if(stream == null) {
            /* my_errno already set */
            return -1;
        }
        else if(!stream.CanSeek) {
            my_errno = __LIBSTD_ESPIPE;
            return -1;
        }

        if(whence < 0 || whence > 2) {
            my_errno = __LIBSTD_EINVAL;
            return -1;
        }

        if (whence == __LIBSTD_SEEK_SET)
            origin = SeekOrigin.Begin;
        else if (whence == __LIBSTD_SEEK_END)
            origin = SeekOrigin.End;
        else
            origin = SeekOrigin.Current;

        try {
            stream.Seek(offset, origin);
        }
        catch(NotSupportedException) {
            my_errno = __LIBSTD_ESPIPE;
            return -1;
        }
        catch(ObjectDisposedException) {
            my_errno = __LIBSTD_EBADF;
            return -1;
        }
        catch(EndOfStreamException) {
            my_errno = __LIBSTD_EINVAL;
            return -1;
        }

        return (int)stream.Position;
    }

    public static int fcntl(int filedes, int cmd, int arg)
    {
        my_errno = __LIBSTD_ENOSYS;
        return -1;
    }

    unsafe public static sbyte* getenv(sbyte* name)
    {
        String _name  = Marshal.PtrToStringAnsi(new System.IntPtr(name));
        String result = Environment.GetEnvironmentVariable(_name);
        if (result == null)
            return null;
        return (sbyte*)Marshal.StringToHGlobalAnsi(result);
    }

    unsafe public static void* malloc(uint size)
    {
        IntPtr res;

        if(size == 0)
            size = 1;

        try {
            res = Marshal.AllocHGlobal((int)size);
        } catch(OutOfMemoryException) {
            my_errno = __LIBSTD_ENOMEM;
            return null;
        }
        return (void*)res.ToInt32();
    }

    unsafe public static void free(void* ptr)
    {
        if(ptr != null) {
            IntPtr ptr_int_ptr = new IntPtr(ptr);
            Marshal.FreeHGlobal(ptr_int_ptr);
        }
    }

    unsafe public static void* realloc(void* ptr, uint size)
    {
        IntPtr ptr_int_ptr = new IntPtr(ptr);
        IntPtr size_int_ptr = new IntPtr(size);
        IntPtr res;

        try {
            if(ptr == null) {
                /* malloc */
                if(size == 0)
                    size = 1;
                res = Marshal.AllocHGlobal(size_int_ptr);
            }
            else if(size == 0) {
                /* free */
                Marshal.FreeHGlobal(ptr_int_ptr);
                return null;
            }
            else {
                res = Marshal.ReAllocHGlobal(ptr_int_ptr, size_int_ptr);
            }
        } catch (OutOfMemoryException) {
            my_errno = __LIBSTD_ENOMEM;
            return null;
        }

        return (void*)res.ToInt32();
    }

    public static int fpclassify(double d)
    {
        if (System.Double.IsInfinity(d))
            return __LIBSTD_FP_INFINITE;
        else if (System.Double.IsNaN(d))
            return __LIBSTD_FP_NAN;
        else
            return __LIBSTD_FP_NORMAL;
    }

    public static int clock()
    {
        long ticks = DateTime.UtcNow.Ticks;
        // The result is multiplied by CLOCKS_PER_SEC and divided by 10^7 as
        // ticks returns the number of 100th nanoseconds
        // (ticks - initial_ticks) / TICKS_PER_CLOCKS
        int res = (int)((ticks - initial_ticks) / 10);
        return res;
    }

    unsafe public static uint time(void* timer)
    {
        int* _timer = (int*)timer;
        long ticks = DateTime.UtcNow.Ticks;
        // result = ((ticks / TICKS_PER_SEC) - EPOCH_ADJUST);
        long result = ((ticks / 10000000) - 62135596800);
        if (_timer != null)
             *_timer = (int)result;
        return (uint)result;
    }

    unsafe public static void gmtime_(void* timer,
                                     int* tm_sec,  int* tm_min,  int* tm_hour,
                                     int* tm_mday, int* tm_mon,  int* tm_year,
                                     int* tm_wday, int* tm_yday, int* tm_isdst)
    {
        // TIME_TO_TICKS(t) ==  (((t) + EPOCH_ADJUST) * TICKS_PER_SEC)
        int* _timer = (int*)timer;
        long ticks = ((long)*_timer + 62135596800) * 10000000;
        DateTime dt = new DateTime(ticks);

        *tm_sec   = dt.Second;
        *tm_min   = dt.Minute;
        *tm_hour  = dt.Hour;
        *tm_mday  = dt.Day;
        *tm_mon   = dt.Month - 1;
        *tm_year  = dt.Year - 1900;
        *tm_wday  = (int)(dt.DayOfWeek);
        *tm_yday  = dt.DayOfYear;
        *tm_isdst = 0;  /* TODO - tm_isdst */
    }

    unsafe public static void gettimeofday (void *_tv_sec, void *_tv_usec)
    {
        int *tv_sec  = (int *)_tv_sec;
        int *tv_usec = (int *)_tv_usec;

        long t = DateTime.UtcNow.Ticks;

        //*tv_sec = (time_t)((t / TICKS_PER_SEC) - EPOCH_ADJUST);
        //*tv_usec = (suseconds_t)((t % TICKS_PER_SEC) / TICKS_PER_USEC);
        *tv_sec = (int)((t / 10000000) - 62135596800);
        *tv_usec = (int)((t % 10000000) / 10);
    }

  
    unsafe public static int gettimes (uint *clks, uint *tms_utime, uint *tms_stime, uint *tms_cutime, uint *tms_cstime)
    {
      Process tp = Process.GetCurrentProcess();

      try {
        /* This is valid as long as _SC_CLK_TCK_VALUE is 100  */
        *tms_utime = (uint)(tp.UserProcessorTime.TotalMilliseconds/(1000/_SC_CLK_TCK_VALUE));
        *tms_stime = (uint)(tp.PrivilegedProcessorTime.TotalMilliseconds/(1000/_SC_CLK_TCK_VALUE));
        /* Currently there is no way to get childs timings.
           In .NET it is possible to check parent ID by means of
           PeroformanceCounter : "Creating Process Id", but it
           is not implemented in Mono */
        *tms_cutime = 0;
        *tms_cstime = 0;
        Console.Error.Write("Warning: gettimes() - tms_cutime and tms_cstime defaults to 0\n");
      } catch (PlatformNotSupportedException) {
        my_errno = __LIBSTD_ENOTSUP;
        return -1;
      }

      /* clks (as return value of times function) is an arbitrary
         time reference. only useful when making more than one call
         to times. */
      *clks = (uint)((DateTime.UtcNow.Ticks - initial_ticks)/(10000000/_SC_CLK_TCK_VALUE));

      return 0;
      
    }

    public static int getsysconf (int name)
    {
      switch (name) {
        case __LIBSTD_SC_CLK_TCK:
          /* this value is must be coherent with the clocks returned by 'gettimes'
             In this implementation we use 100 ticks -> 1 s */
          return _SC_CLK_TCK_VALUE;

        default:
          Console.Error.Write("Warning: getsysconf({0}) - Not implemented\n", name);
          my_errno = __LIBSTD_ENOTSUP;
          return -1;
      }
    }


    public static void exit(int status)
    {
        Environment.Exit(status);
    }

    unsafe public static int rename(sbyte* oldname, sbyte* newname)
    {
        String _oldname  = Marshal.PtrToStringAnsi(new System.IntPtr(oldname));
        String _newname  = Marshal.PtrToStringAnsi(new System.IntPtr(newname));
        try {
            File.Move(_newname, _oldname);
        } catch(Exception) {
            my_errno = __LIBSTD_ENOSYS;
            return -1;
        }
        return 0;
    }

    unsafe public static int remove(sbyte* filename)
    {
        String _filename  = Marshal.PtrToStringAnsi(new System.IntPtr(filename));
        try {
            File.Delete(_filename);
        } catch(Exception) {
            my_errno = __LIBSTD_ENOSYS;
            return -1;
        }
        return 0;
    }

    unsafe public static int link(sbyte* oldname, sbyte* newname)
    {
        my_errno = __LIBSTD_ENOSYS;
        return -1;
    }

    unsafe public static int unlink(sbyte* name)
    {
        String _name = Marshal.PtrToStringAnsi(new System.IntPtr(name));

        try {
            File.Delete (_name);
        } catch (Exception) {
            /* FIXME: set the actual error code */
            my_errno = __LIBSTD_EIO;
            return -1;
        }

        return 0;
    }

    unsafe public static int* errno()
    {
        fixed (int* my_perrno = &my_errno) {
           return my_perrno;
        }
    }

    /*****************        User information         *******************/
    /* This provides an abstraction of POSIX users. Values for uid are
       coherent ONLY inside this library, and don't match the underlying
       system ones -in case the that there is a POSIX system-. 
       
       UID are generated (in a random way) from user strings. Thus,
       a call recieving an UID as argument will only accept the
       user if it has been generated inside the library; via:
        - getuid(), geteuid()
        - getpwnam()
        - stat() -users not yet implemented here-
    */

    class UserPair {
      public UserPair (String name, uint uid) {
        this.name = name;
        this.uid  = uid;
      }

      public String  name;
      public uint    uid;
    };

    private static ArrayList users_set;
    private static uint      users_count;

    private static void InitUsers ()
    {
      users_set = new ArrayList(8);
      users_count = 0;
    }

    private static uint GetUidFromName (String name)
    {
      uint uid = 0;

      foreach (UserPair user in users_set)
        {
          if (user.name == name)
            uid = user.uid;
        }

      if (uid != 0)
        return uid;

      /* here is where users join users_set */
      uid = ++users_count;
      users_set.Add (new UserPair (name, uid));
      return uid;
    }

    private static String GetNameFromUid (uint uid)
    {
      foreach (UserPair user in users_set)
        {
          if (user.uid == uid)
            return user.name;
        }

      /* may be an UID external to this implementation, not supported */
      throw new Exception("the specified UID does not exist");
    }

    /* POSIX user-related functions */
    public static uint getuid ()
    {
      String name = WindowsIdentity.GetCurrent().Name;

      return GetUidFromName (name);
    }
    
    public static uint geteuid ()
    {
      /* Are there "effective users" in .NET? Is that impersonation? */
      return getuid ();
    }

    unsafe public static int getpwuid_ (uint uid, sbyte** name, sbyte** passwd,
                                        uint* gid, sbyte** gecos, sbyte** dir, sbyte** shell)
    {
      String str_name;

      try {
        str_name = GetNameFromUid (uid);
      } catch (Exception) {
        my_errno = __LIBSTD_ENOENT;
        return -1;
      }

      *name = (sbyte*) Marshal.StringToHGlobalAnsi(str_name).ToPointer();

      return getpw_base (str_name, passwd, gid, gecos, dir, shell);
    }

    unsafe public static int getpwnam_ (sbyte* name, sbyte** passwd, uint* uid,
                                        uint* gid, sbyte** gecos, sbyte** dir, sbyte** shell)
    {
      String str_name = Marshal.PtrToStringAnsi(new IntPtr(name));

      *uid = GetUidFromName (str_name);

      return getpw_base (str_name, passwd, gid, gecos, dir, shell);
    }

    unsafe private static int getpw_base (String name, sbyte** passwd, uint* gid,
                                          sbyte** gecos, sbyte** dir, sbyte** shell)
    {
      /*home_path = (Environment.OSVersion.Platform == PlatformID.Unix || 
                   Environment.OSVersion.Platform == PlatformID.MacOSX)
          ? Environment.GetEnvironmentVariable("HOME")
          : Environment.ExpandEnvironmentVariables("%HOMEDRIVE%%HOMEPATH%");*/
 
      *passwd = (sbyte*) new IntPtr(0);
      *gid = 0;
      /* TODO: may be we can find the actual name */
      *gecos = (sbyte*)  Marshal.StringToHGlobalAnsi(name).ToPointer();
      if (name == WindowsIdentity.GetCurrent().Name)
        {
          String home_path = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
          *dir = (sbyte*) Marshal.StringToHGlobalAnsi(home_path).ToPointer();
        }
      else
        *dir = (sbyte*) new IntPtr(0);
      *shell = (sbyte*) new IntPtr(0);

      return 0;
    }

    unsafe public static long getcwd(sbyte* name, ulong size )
    {
        String cwd = Environment.CurrentDirectory;
        int i = 0;

        if ((int)size < cwd.Length)
          return -1;

        for (i = 0; i < cwd.Length; i++)
          name[i] = Convert.ToSByte(cwd[i]);

        name[i] = 0;

        return 0;
    }

    unsafe public static void * signal (int signal, void * handler)
    {
        Console.Error.Write("Warning: signal() not implemented\n");
        return (void *)-1;
    }

    unsafe public static int raise (int signal)
    {
        Console.Error.Write("Warning: raise() not implemented\n");
        return -1;
    }


    unsafe public static int kill (int pid, int signal)
    {
        Console.Error.Write("Warning: kill() not implemented\n");
        return -1;
    }


    public static double dbl_epsilon()
    {
        return System.Double.Epsilon;
    }

    public static double dbl_minval()
    {
        return System.Double.MinValue;
    }

    public static double dbl_maxval()
    {
        return System.Double.MaxValue;
    }

    public static double dbl_hugeval()
    {
        return System.Double.PositiveInfinity;
    }

    public static float flt_epsilon()
    {
        return System.Single.Epsilon;
    }

    public static float flt_minval()
    {
        return System.Single.MinValue;
    }

    public static float flt_maxval()
    {
        return System.Single.MaxValue;
    }

    public static float flt_hugeval()
    {
        return System.Single.PositiveInfinity;
    }

    public static float flt_nan()
    {
        return System.Single.NaN;
    }

    public static float flt_infinity()
    {
        return System.Single.PositiveInfinity;
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    ///  MATH SECTION /////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    public static double acos(double d)
    {
        return System.Math.Acos(d);
    }

    public static float acosf(float f)
    {
        return (float)System.Math.Acos(f);
    }

    public static double asin(double d)
    {
        return System.Math.Asin(d);
    }

    public static float asinf(float f)
    {
        return (float)System.Math.Asin(f);
    }

    public static double atan(double d)
    {
        return System.Math.Atan(d);
    }

    public static float atanf(float f)
    {
        return (float)System.Math.Atan(f);
    }

    public static double atan2(double p0, double p1)
    {
        return System.Math.Atan2(p0, p1);
    }

    public static float atan2f(float p0, float p1)
    {
        return (float)System.Math.Atan2(p0, p1);
    }

    public static double cos(double d)
    {
        return System.Math.Cos(d);
    }

    public static float cosf(float f)
    {
        return (float)System.Math.Cos(f);
    }

    public static double sin(double d)
    {
        return System.Math.Sin(d);
    }

    public static float sinf(float f)
    {
        return (float)System.Math.Sin(f);
    }

    public static double tan(double d)
    {
        return System.Math.Tan(d);
    }

    public static float tanf(float f)
    {
        return (float)System.Math.Tan(f);
    }

    public static double cosh(double d)
    {
        return System.Math.Cosh(d);
    }

    public static float coshf(float f)
    {
        return (float)System.Math.Cosh(f);
    }

    public static double sinh(double d)
    {
        return System.Math.Sinh(d);
    }

    public static float sinhf(float f)
    {
        return (float)System.Math.Sinh(f);
    }

    public static double tanh(double d)
    {
        return System.Math.Tanh(d);
    }

    public static float tanhf(float f)
    {
        return (float)System.Math.Tanh(f);
    }

    public static double exp(double d)
    {
        return System.Math.Exp(d);
    }

    public static float expf(float f)
    {
        return (float)System.Math.Exp(f);
    }

    public static double exp2(double d)
    {
        return System.Math.Pow((double)2.0, d);
    }

    public static float exp2f(float f)
    {
        return (float)System.Math.Pow((double)2.0, f);
    }

    public static double expm1(double d)
    {
        return System.Math.Exp(d) - (double)1.0;
    }

    public static float expm1f(float f)
    {
        return (float)System.Math.Exp(f) - (float)1.0;
    }

    public static double log(double d)
    {
        return System.Math.Log(d);
    }

    public static float logf(float f)
    {
        return (float)System.Math.Log(f);
    }

    public static double log10(double d)
    {
        return System.Math.Log10(d);
    }

    public static float log10f(float f)
    {
        return (float)System.Math.Log10(f);
    }

    public static double log1p(double d)
    {
        return System.Math.Log(d + (double)1.0);
    }

    public static float log1pf(float f)
    {
        return (float)System.Math.Log(f + (float)1.0);
    }

    public static double log2(double d)
    {
        return System.Math.Log(d) / System.Math.Log((double)2.0);
    }

    public static float log2f(float f)
    {
        return (float)System.Math.Log(f) / (float)System.Math.Log((float)2.0);
    }

    public static double fabs(double d)
    {
        return System.Math.Abs(d);
    }

    public static float fabsf(float f)
    {
        return (float)System.Math.Abs(f);
    }

    public static double pow(double p0, double p1)
    {
        return System.Math.Pow(p0, p1);
    }

    public static float powf(float f0, float f1)
    {
        return (float)System.Math.Pow(f0, f1);
    }

    public static double ceil(double d)
    {
        return System.Math.Ceiling(d);
    }

    public static float ceilf(float f)
    {
        return (float)System.Math.Ceiling(f);
    }

    public static double cbrt(double d)
    {
        return System.Math.Pow(d, (double)1/(double)3);
    }

    public static float cbrtf(float f)
    {
        return (float)System.Math.Pow(f, (float)1/(float)3);
    }

    public static double sqrt(double d)
    {
        return System.Math.Sqrt(d);
    }

    public static float sqrtf(float f)
    {
        return (float)System.Math.Sqrt(f);
    }

    public static double floor(double d)
    {
        return System.Math.Floor(d);
    }

    public static float floorf(float f)
    {
        return (float)System.Math.Floor(f);
    }

    public static double round(double d)
    {
      return System.Math.Round(d, 0);
    }

    public static float roundf(float f)
    {
      return (float)System.Math.Round(f, 0);
    }

    public static int lround(double d)
    {
        return Convert.ToInt32(d);
    }

    public static int lroundf(float f)
    {
        return Convert.ToInt32(f);
    }

    public static double ldexp(double p0, int p1)
    {
        if (   p1 == 0
            || p0 == 0.0
            || System.Double.IsInfinity(p0)
            || System.Double.IsNaN(p0))
            return p0;

        double result;

        if (p1 > 0)
            result = (p0 * (double)(2 << p1));
        else
            result = (p0 / (double)(2 << (-p1)));

        if (   result == 0.0
            || System.Double.IsInfinity(result)
            || System.Double.IsNaN(result))
            my_errno = __LIBSTD_ERANGE;

        return result;
    }

    public static float ldexpf(float p0, int p1)
    {
        if (   p1 == 0
            || p0 == 0.0
            || System.Single.IsInfinity(p0)
            || System.Single.IsNaN(p0))
            return p0;

        float result;

        if (p1 > 0)
            result = (p0 * (float)(2 << p1));
        else
            result = (p0 / (float)(2 << (-p1)));

        if (   result == 0.0
            || System.Single.IsInfinity(result)
            || System.Single.IsNaN(result))
            my_errno = __LIBSTD_ERANGE;

        return result;
    }

    // FLT_RADIX is 2 in this implementation. Keep this in sync with float.h
    public static double scalbn(double p0, int p1)
    {
        return ldexp(p0, p1);
    }
    // FLT_RADIX is 2 in this implementation. Keep this in sync with float.h
    public static float scalbnf(float p0, int p1)
    {
        return ldexpf(p0, p1);
    }
    // FLT_RADIX is 2 in this implementation. Keep this in sync with float.h
    public static double scalbln(double p0, int p1)
    {
        return ldexp(p0, p1);
    }
    // FLT_RADIX is 2 in this implementation. Keep this in sync with float.h
    public static float scalblnf(float p0, int p1)
    {
        return ldexpf(p0, p1);
    }

    public static double hypot(double p0, double p1)
    {
        return System.Math.Sqrt(p0*p0 + p1*p1);
    }

    public static float hypotf(float p0, float p1)
    {
        return (float)System.Math.Sqrt(p0*p0 + p1*p1);
    }

};

