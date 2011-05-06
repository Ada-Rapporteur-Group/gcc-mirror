2011-05-06  Gary Funck  <gary@intrepid.com>

	Merge trunk version 173471 into gupc branch.

2011-05-05  Gary Funck  <gary@intrepid.com>

	Make changes that bring the GUPC branch more closely in sync. 
	with the GCC trunk.  Revert any fixes that are not UPC-specific.
	Remove gratuitous re-formatting.

	* ../libstdc++-v3/config/os/bionic/ctype_noninline.h: Delete.
	  This file should have been removed in a previous merge
	  with the trunk.
	* ../configure.ac: Remove Cray Catamount/CNL support.
	* ../configure: Regenerate.
	* ../config.sub: Remove Cray Catamount/CNL support.
	* config.gcc: Remove Cray Catamount/CNL support.
	* ../maintainer-scripts/gcc_release: Revert to trunk.
        * c-family/c-common.h: Define parse_optimize_options.  Its definition
	  was missed in a previous merge with the trunk.
	* dwarf2out.c: Revert a fix which removed the 'type_main_variant'
	  procedure.
	* dwarf2out.c: Revert a fix that added a check for VECTOR_TYPE
	  in addition to ARRAY_TYPE.
	* c-typeck.c: Remove an extra newline character.
	* varasm.c: Revert a fix that improved an error message
	  when TLS common data is unimplemented.
	* varasm.c: Revert a gcc_assert that had been added which
	  checked for a null DECL_SIZE_UNIT field.
	* emultls.c: Revert to trunk. Remove possible fix.
	* Makefile.in: Revert extra blank line that is present
	  in the trunk version.
	* Makefile.in: Revert a fix that handled long shell
	  argument lists for plugin headers.
	* config/ia64/ia64.opt: Revert an option setting
	  that increased the default TLS address range.
	* config/ia64/crtbegin.asm: Revert to trunk.
	  Removes an extra newline character.
	* ChangeLog.upc: Spell check.

2011-05-03  Gary Funck  <gary@intrepid.com>

	* c-family/c-common.c: Remove extraneous FIXME/TODO comments.
	  (c_apply_type_quals_to_decl): Ditto.
	* c-family/c-common.h: Ditto.
	* dojump.c: Ditto.
	* c-delc.c (merge_decls): Ditto.
	* c-typeck.c (qualify_type, default_conversion,
	  build_component_ref, build_unary_op,
	  c_build_qualified_type): Ditto.
	* gimplify.c (create_tmp_var_raw): Remove UPC-specific dead code.

2011-04-29  Gary Funck  <gary@intrepid.com>

	* c-decl.c (finish_decl): Improve error diagnostics.
	  (grokdeclarator): Ditto.

	* c-typeck.c (build_c_cast): Improve error diagnostics.
	  (convert_for_assignment): Ditto.
	  (build_binary_op): Ditto.

	* c-parser.c (c_parser_upc_forall_statement):
	  Improve error diagnostics.

	* convert.c (convert_to_integer):  Improve error diagnostics.

2011-04-24  Gary Funck  <gary@intrepid.com>

	* c-parser.c (c_parser_upc_sync_statement): Fix ICE that
	  occurred if there is an error in the barrier id
	  expression.  Map error_mark_node into NULL.

2011-04-19  Gary Funck  <gary@intrepid.com>

	Merge trunk version 172359 into gupc branch.

2011-04-14  Gary Funck  <gary@intrepid.com>

	* c-family/c.opt: Add UPC as a valid language for various
	  switches where it is valid for "C", that were not updated
	  in previous merges with trunk.

2011-04-13  Gary Funck  <gary@intrepid.com>

	* c-family/c.opt (fupc-pre-include): New option definition.
	* gcc.c (upc_options): Do not add "-include gcc-upc.h" if
	  -fno-upc-pre-include is asserted.

2011-04-07  Gary Funck  <gary@intrepid.com>

	Merge trunk version 172158 into gupc branch.
	to bring in the following fix.

2011-04-05  Bernd Schmidt  <bernds@codesourcery.com>

	PR bootstrap/48403
	* haifa-sched.c (schedule_block): Increment cycle_issued_insns only
	if old and new states differ.

2011-04-06  Gary Funck  <gary@intrepid.com>

	Merge trunk version 171966 into gupc branch.

2011-04-01  Gary Funck  <gary@intrepid.com>

	* tree.h (tree_base): Move UPC flag bits into bit fields
	  located just before spare bits.  Decrement spare bits.
	  Rename 'shared_flag' -> 'upc_shared_flag',
	  'relaxed_flag' -> 'upc_relaxed_flag',
	  'strict_flag' -> 'upc_strict_flag, and adjust macros
	  that reference them accordingly.

2011-04-01  Gary Funck  <gary@intrepid.com>

	* c-decl.c (grokdeclarator): Fix formatting of
	  code that sets UPC block size on scalars.

2011-04-01  Gary Funck  <gary@intrepid.com>

	* c-decl.c (grokdeclarator): Revert use of white space
	  to match the trunk (to rationalize diffs).
	* c-typeck.c (convert_for_assignment): Ditto.
	* tree-ssa.c (useless_type_conversion_p): Ditto.

2011-03-23  Gary Funck  <gary@intrepid.com>

	* DEV-PHASE: bump to 4.7.0-1 to reflect recent creation of
	  the GCC 4.6 release branch.

2011-03-21  Gary Funck  <gary@intrepid.com>

	Merge trunk version 171202 into gupc branch.

2011-03-20  Gary Funck  <gary@intrepid.com>

	* varasm.c: Call error() directly with a format specifier,
	  rather than using sprintf() to format the message.
	  This should make it easier to internationalize UPC's error messages.

2011-03-20  Gary Funck  <gary@intrepid.com>

	* configure.ac: Fix the check for gnu ld when enabling
	  UPC link script support.
	  configure: Regenerate (also picks up changes from previous
	  merge with trunk).

2011-03-20  Gary Funck  <gary@intrepid.com>

	Move UPC start files, end files, and linker specs.
	into libupc.  This reduces the impact on common GCC
	configuration files, and ensures that these UPC-specific
	components are only built when the UPC language dialect is selected.


gcc/
	* c-family/c.opt: Add -fupc-link switch, used to select UPC-specific
	  linker specs. Fix typo in -fupc-debug message.

	* config/upc-conf.h, config/darwin.h: Move defines for
	  UPC-related section begins/ends into libupc/config/default/
	  upc-crt-config.h.

	* config/darwin.h(LINK_COMMAND_SPEC_A): Add call outs to
	  UPC-related linker compiler specifications,
	  accessed via %:include().

        * configure.ac, configure: Remove logic related to building
	  upc-crtbegin/end. Remove config. tests for numa and cpu
	  affinity (previously used by the 'upc' driver); these
	  settings are now propagated by target-specific compiler
	  specs. built by libupc.  Regenerate autoconf.

	* gcc.c (LINK_COMMAND_SPEC): Add call outs to UPC-related
	  linker compiler specifications, accessed via %:include().
	  Define 'upc_crtbegin_spec', 'upc_crtend_spec', and
	  'link_upc_spec'.

	* Makefile.in: Remove definition of UPC_CRTSTUFF_CFLAGS.

	* config/linux.h, config/i386/darwin.h, config/i386/linux64.h,
	  config/i386/linux.h, config/i386/t-darwin, config/i386/t-darwin64,
	  config/ia64/linux.h, config/mips/t-iris,
	  config/mips/iris6.h: Revert to trunk version 167307.

libgcc/
	* configure, configure.ac, config.host, Makefile.in:
	  Revert to trunk version 167307.

2011-02-23  Gary Funck  <gary@intrepid.com>

	* c-decl.c (undeclared_variable): fix typo. Inadvertently
	removed negation on following 'if'.

2011-02-22  Gary Funck  <gary@intrepid.com>

	* c-decl.c (undeclared_variable): call upc_diagnose_deprecated_stmt
	to check for the usage of certain deprecated UPC keywords.
	* c-family/stub-upc.c (upc_diagnose_deprecated_stmt): New.
	* c-tree.h (undeclared_variable): Define prototype.

2011-02-12  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: (build_c_cast, convert_for_assignment)
	  Diagnose an attempt to convert from an integer to
	  a pointer-to-shared as an error.  Also, fix various
	  error messages so that they use the preferred term
	  pointer-to-shared instead of "shared pointer".

2011-02-07  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: (convert_for_assignment)
	  Fix typo. in error message.

2011-01-23  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: (c_build_qualified_type)
	  derive UPC block size by calling upc_get_block_size(),
	  to ensure that the element type of an array of an array
	  is derived correctly.

2010-12-29  Gary Funck  <gary@intrepid.com>

	Merge trunk version 168314 into gupc branch.

2010-12-15  Gary Funck  <gary@intrepid.com>

	Merge trunk version 167307 into gupc branch.

2010-10-19  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: Fix typo in previous fix
	  which led to a mis-compare for equal block sizes.

2010-10-18  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: Fix bug: Cast of (shared <type> * shared) not
	  diagnosed as an error

	  The conversion from any type (shared or not) to
	  a shared type is likely either meaningless or an error.  This update
	  makes any conversion to a shared type, an error.

2010-10-18  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: Fix bug: passing int to shared pointer arg.
	  generates spurious warning

	  Add a #define procedure that does the same thing as
	  WARN_FOR_ASSIGNMENT but issues an error diagnostic instead.  Use
	  this procedure to diagnose passing an integer value to a
	  pointer-to-shared as an error.

2010-10-18  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: Fix bug: shared [] in prototype silently ignored when
	  matching routine declaration.

	  When checking for type compatibility, shared qualified types must
	  have the same block factor.  This check was missing from
	  comptypes_internal().  This update adds the check for blocking
	  factor equality.

2010-10-17  Gary Funck  <gary@intrepid.com>

	* dwarf2out.c: Fix GCC Bug 45870 - note: non-delegitimized UNSPEC 5
	  found (-O1 -g)

	  See: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=45870#c6

2010-10-17  Gary Funck  <gary@intrepid.com>

	* tree-cfg.c: Implement the fix for GCC Bugzilla Bug
	  45869 - [4.5/4.6 Regression] type mismatch in shift expression
	  produces ice with -O3 and -m32.

	  See: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=45869

2010-10-17  Gary Funck  <gary@intrepid.com>

	* c-common.c: Diagnose the application of the various "*sizeof"
	  operations on generic pointer-to-shared as a compilation error.

2010-10-17  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Fix a segfault/ICE that occurred when printing an error
	  message regarding a function parameter being declared with a shared
	  qualifier.

	  The parameter's 'name' value is not defined at this point, and
	  cannot be used in the error message.  This update removes the
	  reference to 'name', and eliminates the segfault.

2010-10-16  Gary Funck  <gary@intrepid.com>

	* Makefile.in: Implement fixes for SGI/IRIX/MIPS port.

	  The gcc/Makefile.in rules for install-plugin had to be re-written to
	  break up a long list of header files that exceeded the command line
	  limitation imposed by Irix.

	  Access functions for TFmode types had to be implemented.
	  Apparently, this is the mode used for the SGI/MIPS port to represent
	  "long float".

2010-10-14  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Fix bug: Multiple equal blocking factors specified
	  via typedef chain should not be diagnosed as an error.

	  If the block size that is given by the typedef is equal to the block
	  size given explicitly in the variable declaration, then do not
	  complain.  The easiest way to make this check was to create a
	  temporary type that is a clone of the element type and then set its
	  block size using the given layout qualifier.  Then compare the block
	  size of the temporary (the declaration) to the block size specified
	  in the typedef.  This complexity is needed, because the '[*]' block
	  size needs to be calculated, and the '[]' needs to be mapped into a
	  zero block size.

2010-10-10  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Fix bug: ICE: two or more layout qualifiers
	  specified

	  The compiler properly detected the presence of two or more layout
	  qualifiers as an error, but then hit an assertion check, because the
	  code that followed the error expected to see a qualifier and not a
	  layout specifier.  The fix is simple: just return immediately after
	  detecting the error.

2010-10-10  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Improve error diagnostics for various cases of UPC
	  shared array type declarations.

	  Add the check for this error: "In the dynamic translation
	  environment, THREADS may not appear in declarations of shared arrays
	  with indefinite block size".  Also, fix up a few of the other
	  related error diagnostics.

2010-10-09  Gary Funck  <gary@intrepid.com>

	* c-common.c: Fix bug: segfault on incomplete array definition.

	  This turned out to be a bit complicated.   The logic in
	  upc_lang_layout_decl had to be re-arranged to avoid trying to lookup
	  the THREADS identifier in the case where the blocking factor has
	  been set to indefinite ([]).  This can happen when indefinite array
	  declarations are processed for shared arrays.  At that time, the
	  file scope has been closed and THREADS is no longer in scope.  Some
	  more work is needed on upc_lang_layout_decl().  It has some
	  duplication, and notably duplicates the two branches of the if
	  having to do with TYPE_SIZE and TYPE_SIZE_UNIT, that appear in the
	  caller of this routine (layout_decl()).

	  The method of forcing a layout qualifier of [] in the indefinite
	  declaration handler is odd a well.  The code that just does the
	  setting of the block factor, needs to moved into its own routine
	  that doesn't depend upon a declspec for '[]' to be passed in, just
	  in order to set the blocking factor to some value (in this case, 0).
	  Also, the logic for how that shared type is constructed is strange.
	  First the type with 0 blocking factor is set.  Then the shared
	  qualifier is removed from the type, and then added back later.  The
	  intermediate type has a blocking factor set, but it has no shared
	  qualifier.  Fixing this will require some thought.  It is tempting
	  just to make indefinite shared arrays an error, rather than forcing
	  the dimension to be '1'.

	  This likely fixes a serious error in the previous update to
	  upc_lang_layout_decl(), where it didn't have the logic to set
	  TYPE_SIZE_UNIT() in the main part of the 'if' statement.  This means
	  the previous update would fail on many tests.

2010-10-09  Gary Funck  <gary@intrepid.com>

	* varasm.c: Add an assertion check for the case that DECL_SIZE_UNIT
	  (decl) is null, which can happen if some layout error occurred
	  upstream.

2010-10-09  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Fix bug: file scope shared arrays mis-diagnosed as
	  "variable-sized" when compiled in dynamic threads.

	  This long-standing bug is easily fixed.  Just check
	  for the situation that the non-constant sized type is shared and
	  that it does not have a dimension that references a multiple of
	  threads.  If this criteria is met, then issue a meaningful
	  diagnostic.

2010-10-01  Gary Funck  <gary@intrepid.com>

	* configure, configure.ac: Update manual page, and bug reporting
	  URL.

	  Update "man" page to reflect debugging switches.  Also, some general
	  clean up.  Change the bug reporting URL to point to gccupc.org.

2010-09-27  Gary Funck  <gary@intrepid.com>

	* c-parser.c, config/upc-conf.h: Issue a descriptive message when
	  the UPC forall depth count variable is not found.

	  The __upc_forall_depth variable should be defined in gcc-upc-lib.h.
	  The compiler will generate code that references this variable in
	  order to implement nested upc_forall semantics.  If there is a
	  compiler build or install problem, this variable may not be found.
	  In this case, terminate with an internal_error().

2010-09-26  Gary Funck  <gary@intrepid.com>

	* c-parser.c: Fix Bug 240: upc_forall with empty clauses
	  mis-diagnosed as syntax error.

	  Fix a failure exhibited by the Berkeley test case,
	  bug873a.upc, which has the code:
	       double d;
	       upc_forall (;;;d) {...} The compiler did not properly handle
	  the empty "condition" clause, and did not recover well when it was
	  determined that the use of a double value, "d" above, was neither a
	  pointer-to-shared nor an integer expression.  The update implements a
	  fix for both issues.

	  See also: gcc/c-parser.c gcc/upc/upc-act.c

2010-09-23  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Fix Bug 29: Layout qualifier within a typedef is not
	  incorporated into the referencing type.

	  This was semi-fixed a few times before.  This update fixes a few
	  more places where the layout qualifier wasn't being propagated
	  through typedef's properly.  What made this a bit tricky is shown in
	  the example cited in the bug report:

	  typedef shared [5] int A_t; A_t A[5*THREADS];

	  In the typedef, the blocksize is being applied to a shared *scalar*,
	  and the code was applying the blocksize only to arrays.  This update
	  handles shared scalars correctly.

2010-09-22  Gary Funck  <gary@intrepid.com>

	* c-parser.c, c-tree.h, stub-upc.c: Fix Bug 403: Nested
	  upc_forall() semantics are not implemented

	  The checkforall test in the Berkeley harness test suite indicated
	  that GCC/UPC was not properly implementing nested upc_forall
	  semantics.  Nested upc_forall statements (both statically or
	  dynamically nested) must implement their affinity clause as if it
	  were "continue"; thus all steps in the loop must execute without
	  regard for affinity.  To implement these semantics a global depth
	  counter, __upc_forall_depth, is maintained by the generated code
	  that implements upc_forall.

	  See also: gcc/c-parser.c gcc/c-tree.h gcc/stub-upc.c
	  gcc/upc/upc-act.c gcc/upc/upc-act.h libupc/include/gcc-upc-lib.in
	  libupc/include/upc.h libupc/smp/upc_main.c

2010-09-19  Gary Funck  <gary@intrepid.com>

	* c-decl.c: c-decl.c: zero out the layout specifier, after
	  processing an array type.

	  Fix the previous fix, that moved the setting of the type's layout
	  qualifier to the outside of the array type processing loop.  What is
	  missing from the fix is that the layout_qualifier variable needs to
	  be cleared after setting the type's blocksize.

2010-09-19  Gary Funck  <gary@intrepid.com>

	* config/upc-conf.h: Fix Bug 375: error message is off-by-one when
	  given blocksize is greater than UPC_MAX_BLOCKSIZE.

	  The value we were using for UPC_MAX_BLOCK_SIZE was one bigger than
	  the actual maximum block size.  Therefore, the message was correct,
	  but the underlying value that was being checked was wrong.  Change
	  the values so that they agree with the actual implementation-defined
	  limit.

2010-09-11  Gary Funck  <gary@intrepid.com>

	* c-decl.c: Fix Bug 402: ICE: '[*]' layout factor on
	  multi-dimensional shared array with dynamic threads.

	  This declaration caused an internal compiler error when compiled
	  with dynamic threads:
	      shared [*] int A[THREADS][16]; The bug was discovered when
	  compiling the RTED_UPC test suite.

	  The fix is to process layout qualifiers after the entire array type
	  has been built.  Otherwise, we try to calculate the blocksize on a
	  shared array type that has not had its "size depends upon the value
	  of THREADS" flag set.

	  Also, added a test case.

	  See also: libupc/testsuite/libupc.upc/intrepid/test18.upc

2010-07-11  Gary Funck  <gary@intrepid.com>

	Fix a bug where a statement in c_build_qualified_type()
	in the trunk had been inadvertently deleted.
	This bug showed up in the IA64 port, because jmpbuf's
	on that architecture must be 16 byte aligned, and they were not.
	c-typeck.c (c_build_qualified_type): Revive the deleted line.

2010-07-08  Gary Funck  <gary@intrepid.com>

	Make changes so that other language compilers
	will build and bootstrap.
	* c-family/c-common.c (compiling_upc, flag_upc,
	flag_upc_instrument, flag_upc_instrument_functions,
	use_upc_dwarf2_extensions): Move to stub-upc.c and
	upc-lang.c.
	* c-family/c-common.h (use_upc_dwarf2_extensions,
	compiling_upc): Add extern definitions - needed
	to compile/build other language front ends.
	* c-family/c.opt: Fix the spelling of ObjC.
	It had been incorrectly spelled as Objc.
	* c-family/c.opt: Add UPC for the various switches
	that are valid for both C and ObjC.
	* c-fmaily/c-opts.c: Add CL_UPC to the list of
	supported options switches when compiling assembly
	language.
	* lto/lto-lang.c (use_upc_dwarf2_extensions,
	flag_upc_instrument, flag_upc_instrument_functions):
	Remove these definitions.  They have been moved
	to c-family/stub-upc.c.
	* upc/ChangeLog: Move relevant entries
	to ChangeLog.upc.
	* c-family/stub-upc.c (compiling_upc, flag_upc,
	flag_upc_instrument, flag_upc_instrument_functions,
	use_upc_dwarf2_extensions): Moved from c-common.c
	* upc/upc-lang.c (compiling_upc, flag_upc,
	flag_upc_instrument, flag_upc_instrument_functions,
	use_upc_dwarf2_extensions): Moved from c-common.c
	* objc/objc-act.c (objc_gimplify_expr): Add additional
	parameters to c_gimplify_expr() call, that are used
	by upc's tree rewrites.
	* cp/cp-gimplify.c (cp_gimplify_expr): Likewise.
	* gcc/cp/lex.c (init_reswords): If not compiling
	UPC, then mask off the UPC keywords.
	* cp/Make-lang.in (C_STUB_OBJS): Use this
	make macro to link with c-family/stub-objc.o
	and c-family/stub-upc.o.
	* fortran/Make-lang.in (C_STUB_OBJS): Likewise.
	* java/Make-lang.in (C_STUB_OBJS): Likewise.
	* objc/Make-lang.in: Link with c-family/stub-upc.o
	to avoid undefined references.
	c-parser.c: Fix line indentation.
	* libcpp/include/cpplib.h: Remove CL_UPC from
	the list of language kinds accepted by the
	C preprocessor.  This is not necessary because
	UPC is a derivative of C99, and does not need
	a different language kind.
	* c-fmaily/c-opts.c (c_common_handle_option):
	Call set_std_c99() when processing the
	"--lang upc" switch, instead of setting the
	language kind to CL_UPC.
	* libupc/testsuite/libupc.upc/intrepid/ChangeLog: New.

2010-07-03  Gary Funck  <gary@intrepid.com>

	Merge trunk version 161517 into gupc branch.
	* gcc/stub-upc.c: Move to gcc/c-family/.
	* libupc/testsuite/libupc.upc/intrepid/test19.upc:
	Add 'unused' attributes to avoid "set, but
	not referenced" warnings.
	* libupc/testsuite/libupc.upc/intrepid/test18.upc:
	Likewise.
