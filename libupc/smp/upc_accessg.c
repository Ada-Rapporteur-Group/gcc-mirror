/* Copyright (C) 2005-2009 Free Software Foundation, Inc.
   This file is part of the UPC runtime Library.
   Written by Gary Funck <gary@intrepid.com>
   and Nenad Vukicevic <nenad@intrepid.com>
   Original Implementation by Adam Leko <adam@leko.org>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.

   As a special exception, if you link this library with files
   compiled with a GNU compiler to produce an executable, this does
   not cause the resulting executable to be covered by the GNU General
   Public License.  This exception does not however invalidate any
   other reasons why the executable file might be covered by the GNU
   General Public License.  */

#include "upc_config.h"
#include "upc_sysdep.h"
#include "upc_defs.h"
#include "upc_access.h"
#include "upc_lib.h"
#include "gasp_upc.h"
#include "upc_pupc.h"

/* relaxed accesses (profiled) */

u_intQI_t
__getgqi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intQI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getqi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

u_intHI_t
__getghi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intHI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __gethi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

u_intSI_t
__getgsi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intSI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getsi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

u_intDI_t
__getgdi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intDI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getdi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

#if GUPCR_TARGET64
u_intTI_t
__getgti3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intTI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getti2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}
#endif

float
__getgsf3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  float val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getsf2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

double
__getgdf3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  double val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getdf2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

void
__getgblk5 (void *dest, upc_shared_ptr_t src, size_t n, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_GET, 1, dest, &src, n);
  __getblk3 (dest, src, n);
  p_end (GASP_UPC_GET, 1, dest, &src, n);
}

void
__putgqi4 (upc_shared_ptr_t p, u_intQI_t v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putqi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putghi4 (upc_shared_ptr_t p, u_intHI_t v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __puthi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putgsi4 (upc_shared_ptr_t p, u_intSI_t v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putsi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putgdi4 (upc_shared_ptr_t p, u_intDI_t v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putdi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

#if GUPCR_TARGET64
void
__putgti4 (upc_shared_ptr_t p, u_intTI_t v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putti2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}
#endif

void
__putgsf4 (upc_shared_ptr_t p, float v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putsf2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putgdf4 (upc_shared_ptr_t p, double v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putdf2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putgblk5 (upc_shared_ptr_t dest, void *src, size_t n, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_PUT, 1, &dest, src, n);
  __putblk3 (dest, src, n);
  p_end (GASP_UPC_PUT, 1, &dest, src, n);
}

void
__copygblk5 (upc_shared_ptr_t dest, upc_shared_ptr_t src, size_t n,
	     const char *filename, int linenum)
{
  p_start (GASP_UPC_MEMCPY, &dest, &src, n);
  __copyblk3 (dest, src, n);
  p_end (GASP_UPC_MEMCPY, &dest, &src, n);
}

/* strict accesses (profiled) */

u_intQI_t
__getsgqi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intQI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getsqi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

u_intHI_t
__getsghi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intHI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getshi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

u_intSI_t
__getsgsi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intSI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getssi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

u_intDI_t
__getsgdi3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intDI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getsdi2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

#if GUPCR_TARGET64
u_intTI_t
__getsgti3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  u_intTI_t val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getsti2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}
#endif

float
__getsgsf3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  float val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getssf2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

double
__getsgdf3 (upc_shared_ptr_t p, const char *filename, int linenum)
{
  double val;
  p_start (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  val = __getsdf2 (p);
  p_end (GASP_UPC_GET, 1, &val, &p, sizeof (val));
  return val;
}

void
__getsgblk5 (void *dest, upc_shared_ptr_t src, size_t n, const char *filename,
	     int linenum)
{
  p_start (GASP_UPC_GET, 1, dest, &src, n);
  __getblk3 (dest, src, n);
  p_end (GASP_UPC_GET, 1, dest, &src, n);
}

void
__putsgqi4 (upc_shared_ptr_t p, u_intQI_t v, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putsqi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putsghi4 (upc_shared_ptr_t p, u_intHI_t v, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putshi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putsgsi4 (upc_shared_ptr_t p, u_intSI_t v, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putssi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putsgdi4 (upc_shared_ptr_t p, u_intDI_t v, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putsdi2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

#if GUPCR_TARGET64
void
__putsgti4 (upc_shared_ptr_t p, u_intTI_t v, const char *filename,
	    int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putsti2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}
#endif

void
__putsgsf4 (upc_shared_ptr_t p, float v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putssf2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putsgdf4 (upc_shared_ptr_t p, double v, const char *filename, int linenum)
{
  p_start (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
  __putsdf2 (p, v);
  p_end (GASP_UPC_PUT, 1, &p, &v, sizeof (v));
}

void
__putsgblk5 (upc_shared_ptr_t dest, void *src, size_t n, const char *filename,
	     int linenum)
{
  p_start (GASP_UPC_PUT, 0, &dest, src, n);
  __putsblk3 (dest, src, n);
  p_end (GASP_UPC_PUT, 0, &dest, src, n);
}

void
__copysgblk5 (upc_shared_ptr_t dest, upc_shared_ptr_t src, size_t n,
	      const char *filename, int linenum)
{
  p_start (GASP_UPC_MEMCPY, &dest, &src, n);
  __copysblk3 (dest, src, n);
  p_end (GASP_UPC_MEMCPY, &dest, &src, n);
}

void
upc_memcpyg (upc_shared_ptr_t dest, upc_shared_ptr_t src, size_t n,
	     const char *filename, int linenum)
{
  p_start (GASP_UPC_MEMCPY, &dest, &src, n);
  upc_memcpy (dest, src, n);
  p_end (GASP_UPC_MEMCPY, &dest, &src, n);
}

void
upc_memgetg (void *dest, upc_shared_ptr_t src, size_t n, const char *filename,
	     int linenum)
{
  p_start (GASP_UPC_MEMGET, &dest, &src, n);
  upc_memget (dest, src, n);
  p_end (GASP_UPC_MEMGET, &dest, &src, n);
}

void
upc_memputg (upc_shared_ptr_t dest, const void *src, size_t n,
	     const char *filename, int linenum)
{
  p_start (GASP_UPC_MEMPUT, &dest, src, n);
  upc_memput (dest, src, n);
  p_end (GASP_UPC_MEMPUT, &dest, src, n);
}

void
upc_memsetg (upc_shared_ptr_t dest, int c, size_t n, const char *filename,
	     int linenum)
{
  p_start (GASP_UPC_MEMSET, &dest, c, n);
  upc_memset (dest, c, n);
  p_end (GASP_UPC_MEMSET, &dest, c, n);
}
