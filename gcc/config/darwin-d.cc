/* Darwin support needed only by D front-end.
   Copyright (C) 2020-2025 Free Software Foundation, Inc.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tm_d.h"
#include "d/d-target.h"
#include "d/d-target-def.h"

/* Implement TARGET_D_OS_VERSIONS for Darwin targets.  */

static void
darwin_d_os_builtins (void)
{
  d_add_builtin_version ("Posix");
  d_add_builtin_version ("OSX");
  d_add_builtin_version ("darwin");
}

/* Handle a call to `__traits(getTargetInfo, "objectFormat")'.  */

static tree
darwin_d_handle_target_object_format (void)
{
  const char *objfmt = "macho";

  return build_string_literal (strlen (objfmt) + 1, objfmt);
}

/* Implement TARGET_D_REGISTER_OS_TARGET_INFO for Darwin targets.  */

static void
darwin_d_register_target_info (void)
{
  const struct d_target_info_spec handlers[] = {
    { "objectFormat", darwin_d_handle_target_object_format },
    { NULL, NULL },
  };

  d_add_target_info_handlers (handlers);
}

#undef TARGET_D_OS_VERSIONS
#define TARGET_D_OS_VERSIONS darwin_d_os_builtins

#undef TARGET_D_REGISTER_OS_TARGET_INFO
#define TARGET_D_REGISTER_OS_TARGET_INFO darwin_d_register_target_info

/* Define TARGET_D_MINFO_SECTION for Darwin targets.  */

#undef TARGET_D_MINFO_SECTION
#define TARGET_D_MINFO_SECTION "__DATA,__minfodata"

#undef TARGET_D_MINFO_SECTION_START
#define TARGET_D_MINFO_SECTION_START "*section$start$__DATA$__minfodata"

#undef TARGET_D_MINFO_SECTION_END
#define TARGET_D_MINFO_SECTION_END "*section$end$__DATA$__minfodata"

struct gcc_targetdm targetdm = TARGETDM_INITIALIZER;

/* Provide stubs for the hooks defined by darwin.h
     TARGET_EXTRA_PRE_INCLUDES, TARGET_EXTRA_INCLUDES

   As both, gcc and gdc link in incpath.o, we cannot conditionally undefine said
   hooks if D is build.  However, we can define do-nothing stubs of said hooks
   as we are not interested in objc include files in D.

   The hooks original purpose (see also darwin-c.cc):
    * darwin_register_objc_includes
      Register the GNU objective-C runtime include path if STDINC.

    * darwin_register_frameworks
      Register all the system framework paths if STDINC is true and setup
      the missing_header callback for subframework searching if any
      frameworks had been registered.  */

/* Prototypes for functions below to avoid a lengthy list of includes
   to achieve the same.  */
void darwin_register_objc_includes (const char *, const char *, int);
void darwin_register_frameworks (const char *, const char *, int);

void
darwin_register_objc_includes (const char *sysroot ATTRIBUTE_UNUSED,
                              const char *iprefix ATTRIBUTE_UNUSED,
                              int stdinc ATTRIBUTE_UNUSED)
{
}

void
darwin_register_frameworks (const char *sysroot ATTRIBUTE_UNUSED,
                           const char *iprefix ATTRIBUTE_UNUSED,
                           int stdinc ATTRIBUTE_UNUSED)
{
}
