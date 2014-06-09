/* Map __<func>tf<n> used by the standard IEEE 128-bit floating point routines
   to the name used for __float128 when used on a VSX system (KFmode).  */

#define __addtf3	__addkf3
#define __subtf3	__subkf3
#define __multf3	__mulkf3
#define __divtf3	__divkf3
#define __eqtf2		__eqkf2
#define __netf2		__nekf2
#define __getf2		__gekf2
#define __gttf2		__gtkf2
#define __letf2		__lekf2
#define __lttf2		__ltkf2
#define __unordtf2	__unordkf2
#define __negtf2	__negkf2
#define __extenddftf2	__extenddfkf2
#define __extendsftf2	__extendsfkf2
#define __trunctfdf2	__trunckfdf2
#define __trunctfsf2	__trunckfsf2
#define __fixtfsi	__fixkfsi
#define __fixtfdi	__fixkfdi
#define __fixtfti	__fixkfti
#define __fixunstfsi	__fixunskfsi
#define __fixunstfdi	__fixunskfdi
#define __fixunstfti	__fixunskfti
#define __floatsitf	__floatsikf
#define __floatditf	__floatdikf
#define __floattitf	__floattikf
#define __floatunsitf	__floatunsikf
#define __floatunditf	__floatundikf
#define __floatuntitf	__floatuntikf
