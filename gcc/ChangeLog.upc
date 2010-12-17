2010-12-15  Gary Funck  <gary@intrepid.com>

	Merge trunk version 167307 into gupc branch.

2010-10-19  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: Fix typo in previous fix
	  which led to a mis-compare for equal block sizess.

2010-10-18  Gary Funck  <gary@intrepid.com>

	* c-typeck.c: Fix bug: Cast of (shared <type> * shared) not
	  diagnosed as an error

	  The conversion from any type (shared or not) to
	  a shared type is likely either meanigless or an error.  This update
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
	  have the same block foactor.  This check was missing from
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
	  in the typedef.  This complexity is needed, becuase the '[*]' block
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
	  commpiler build or install problem, this variable may not be found.
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
	  pointer-to-shared nor an intger expression.  The update implements a
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

	  This declaration caused an internatl compiler error when compiled
	  with dynamic threads:
	      shared [*] int A[THREADS][16]; The bug was discovered when
	  compiling the RTED_UPC test suite.

	  The fix is to process layout qualifiiers after the entire array type
	  has been built.  Otherwise, we try to calculate the blocksize on a
	  shared array type that has not had its "size depends upon the value
	  of THREADS" flag set.

	  Also, added a test case.

	  See also: libupc/testsuite/libupc.upc/intrepid/test18.upc

2010-07-11  Gary Funck  <gary@intrepid.com>

	Fix a bug where a statement in c_build_qualified_type()
	in the trunk had been inadverntently deleted.
	This bug showed up in the IA64 port, because jmpbuf's
	on that arehitecture must be 16 byte aligned, and they were not.
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
