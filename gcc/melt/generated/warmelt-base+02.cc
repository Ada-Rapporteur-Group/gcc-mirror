/* GCC MELT GENERATED C++ FILE warmelt-base+02.cc - DO NOT EDIT - see http://gcc-melt.org/ */
/* secondary MELT generated C++ file of rank #2 */
#include "melt-run.h"


/* used hash from melt-run.h when compiling this file: */
MELT_EXTERN const char meltrun_used_md5_melt_f2[] = MELT_RUN_HASHMD5 /* from melt-run.h */;


/**** warmelt-base+02.cc declarations ****/
/**** MELT GENERATED DECLARATIONS for warmelt-base ** DO NOT EDIT ; see gcc-melt.org ****/

/****++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
***
    Copyright 2008 - 2015  Free Software Foundation, Inc.
    Contributed by Basile Starynkevitch <basile@starynkevitch.net>
               and Pierre Vittet  <piervit@pvittet.com>

    This file is part of GCC.

    GCC is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3, or (at your option)
    any later version.

    GCC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GCC; see the file COPYING3.  If not see
    <http://www.gnu.org/licenses/>.
***
----------------------------------------------------------------****/


/** ordinary MELT module meltbuild-sources/warmelt-base**/
#define MELT_HAS_INITIAL_ENVIRONMENT 1 /*usualmodule*/



class Melt_InitialClassyFrame_WARMELTmiBASE_h579258933; // forward declaration fromline 6691
typedef Melt_InitialClassyFrame_WARMELTmiBASE_h579258933 Melt_InitialFrame;
/**** no MELT module variables ****/

/*** 3 MELT called hook declarations ***/

/*declare MELT called hook #0 HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER **/
MELT_EXTERN melt_ptr_t melthook_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_PREVENV, const char* meltinp1_MODULNAME);

/*declare MELT called hook #1 HOOK_SYMBOL_IMPORTER **/
MELT_EXTERN melt_ptr_t melthook_HOOK_SYMBOL_IMPORTER (melt_ptr_t melthookdatap, const char* meltinp0_SYMNAMESTR, const char* meltinp1_MODULENAMESTR, melt_ptr_t meltinp2_PARENV);

/*declare MELT called hook #2 HOOK_VALUE_EXPORTER **/
MELT_EXTERN void melthook_HOOK_VALUE_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_VAL, melt_ptr_t meltinp2_CONTENV);

/*** end of 3 MELT called hook declarations ***/

/*** 2 extra MELT c-headers ***/


/** MELT extra c-header 1 : h569977041 **/


/* C++ standard headers for multiple_sort */
#include <vector>
#include <algorithm>




/** MELT extra c-header 2 : h697307081 **/


/* A compare structure used in multiple_sort for std::stable_sort;
   it has to be a compilation-unit global type;
   it cannot be a struct inside multiple_sort;
   see http://stackoverflow.com/q/21201685/841108
   and ISO/IEC 14882 C++03 standard section 14.3.1
 */
class Melt_Sort_Compare_Index
{
    struct meltmultiple_st** melttup_ad;
    melt_ptr_t* meltcmp_ad;
public:
    Melt_Sort_Compare_Index (struct meltmultiple_st**tup_ad, melt_ptr_t* cmp_ad)
        : melttup_ad(tup_ad), meltcmp_ad(cmp_ad) {};
    ~Melt_Sort_Compare_Index()
    {
        meltcmp_ad=NULL;
        melttup_ad=NULL;
    };
    bool operator () (int meltleftix, int meltrightix)
    {
        return (bool)
               melthookproc_HOOK_SORT_COMPARE_LESS((*melttup_ad)->tabval[meltleftix],
                       (*melttup_ad)->tabval[meltrightix],
                       *meltcmp_ad);
    };
}; /* end class Melt_Sort_Compare_Index */


/*** end of 2 extra MELT c-headers ***/




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_1_WARMELTmiBASE_plIV(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_2_WARMELTmiBASE_miIV(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_3_WARMELTmiBASE_stIV(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_4_WARMELTmiBASE_diIV(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_5_WARMELTmiBASE_pcIV(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);

/** start of declaration for hook melthook_HOOK_MELT_MAKE_LOCATION**/

/** declaration of hook melthook_HOOK_MELT_MAKE_LOCATION */
MELT_EXTERN
melt_ptr_t melthook_HOOK_MELT_MAKE_LOCATION(melt_ptr_t melthookdatap,
        const char* meltinp0_FILENAME,
        long meltinp1_LINENO)
;



/** end of declaration for hook melthook_HOOK_MELT_MAKE_LOCATION**/






MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_7_WARMELTmiBASE_LIST_NTH_ELEMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_8_WARMELTmiBASE_LIST_CLONE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_9_WARMELTmiBASE_COMPARE_NAMED_ALPHA(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_10_WARMELTmiBASE_ADD2OUT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_11_WARMELTmiBASE_ADD2LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_12_WARMELTmiBASE_STRING4OUT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_13_WARMELTmiBASE_ADD2OUT4NULL(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_14_WARMELTmiBASE_ADD2OUT4INTEGER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_15_WARMELTmiBASE_ADD2OUT4STRING(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_16_WARMELTmiBASE_ADD2OUT4STRBUF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_17_WARMELTmiBASE_OUTPUT_JSON(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_18_WARMELTmiBASE_ADD2OUT4CLONEDSYMB(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_19_WARMELTmiBASE_ADD2OUT4NAMED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_20_WARMELTmiBASE_ADD2OUT4ROOTOBJECT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_21_WARMELTmiBASE_ADD2OUT4ANY(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_22_WARMELTmiBASE_MAPSTRING_EVERY(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_23_WARMELTmiBASE_MAPSTRING_ITERATE_TEST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_24_WARMELTmiBASE_MULTIPLE_EVERY(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_25_WARMELTmiBASE_MULTIPLE_BACKWARD_EVERY(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_26_WARMELTmiBASE_MULTIPLE_EVERY_BOTH(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_27_WARMELTmiBASE_SET_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_28_WARMELTmiBASE_INSTALL_VALUE_DESCRIPTOR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_34_WARMELTmiBASE_SYMBOL_CNAME(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);

/** start of declaration for hook melthook_HOOK_SORT_COMPARE_LESS**/

/** declaration of hook melthook_HOOK_SORT_COMPARE_LESS */
MELT_EXTERN
long melthook_HOOK_SORT_COMPARE_LESS(melt_ptr_t melthookdatap,
                                     melt_ptr_t meltinp0_LEFT,
                                     melt_ptr_t meltinp1_RIGHT,
                                     melt_ptr_t meltinp2_CMP)
;



/** end of declaration for hook melthook_HOOK_SORT_COMPARE_LESS**/






MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_37_WARMELTmiBASE_MULTIPLE_SORT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_39_WARMELTmiBASE_LAMBDA_cl1(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_40_WARMELTmiBASE_LAMBDA_cl2(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_41_WARMELTmiBASE_LAMBDA_cl3(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_42_WARMELTmiBASE_JSON_NAME_LESS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_46_WARMELTmiBASE_LAMBDA_cl4(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);


MELT_EXTERN void* melt_start_this_module (void*); /*mandatory start of module*/

MELT_EXTERN const char melt_module_is_gpl_compatible[];

/*declare opaque initial frame: */

typedef Melt_InitialClassyFrame_WARMELTmiBASE_h579258933 /*opaqueinitialclassy*/ meltinitial_frame_t;


/* define different names when debugging or not */
#if MELT_HAVE_DEBUG
MELT_EXTERN const char meltmodule_WARMELTmiBASE__melt_have_debug_enabled[];
#define melt_have_debug_string meltmodule_WARMELTmiBASE__melt_have_debug_enabled
#else /*!MELT_HAVE_DEBUG*/
MELT_EXTERN const char meltmodule_WARMELTmiBASE__melt_have_debug_disabled[];
#define melt_have_debug_string meltmodule_WARMELTmiBASE__melt_have_debug_disabled
#endif /*!MELT_HAVE_DEBUG*/



void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_0 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_1 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_2 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_3 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_4 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_5 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_6 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_7 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_8 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_9 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_10 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_11 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_12 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_13 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_14 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_15 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_16 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_17 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_18 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_19 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_20 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_21 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_22 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_23 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_24 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_25 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_26 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_27 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_28 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_29 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_30 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_31 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_32 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_33 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_34 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_35 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_36 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_37 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_38 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_39 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_40 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_41 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_42 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_43 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_44 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_45 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_46 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_47 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_48 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_49 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_50 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_51 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_52 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_53 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_54 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_55 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_56 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_57 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiBASE__initialmeltchunk_58 (meltinitial_frame_t*, char*); //declare



/**** warmelt-base+02.cc implementations ****/




melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST fromline 1752 */

    /** start of frame for meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST// fromline 1568
        : public Melt_CallFrameWithValues<2>
    {
    public: /* fromline 1572*/
// no classy longs
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<2> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST), clos) {};
        MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST() //the constructor fromline 1642
            : Melt_CallFrameWithValues<2> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<2> (fil,lin, sizeof(MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST)) {};
        MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<2> (fil,lin, sizeof(MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST


    /** end of frame for meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST fromline 1697**/

    /* end of frame for routine meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST fromline 1756 */

    /* classy proc frame meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST */
    MeltFrame_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("RETRIEVE_VALUE_DESCRIPTOR_LIST", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    MELT_LOCATION("warmelt-base.melt:1949:/ block");
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:1950:/ cond");
        /*cond*/
        if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)((/*!VALUE_DESCRIPTOR_LIST_REFERENCE*/ meltfrout->tabval[0])),
                                          (melt_ptr_t)((/*!CLASS_REFERENCE*/ meltfrout->tabval[1])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^getslot*/
                {
                    melt_ptr_t slot=NULL, obj=NULL;
                    obj = (melt_ptr_t)((/*!VALUE_DESCRIPTOR_LIST_REFERENCE*/ meltfrout->tabval[0])) /*=obj*/;
                    melt_object_get_field(slot,obj, 0, "REFERENCED_VALUE");
                    /*_.REFERENCED_VALUE__V2*/
                    meltfptr[1] = slot;
                };
                ;
            }
        else    /*^cond.else*/
            {

                /*_.REFERENCED_VALUE__V2*/ meltfptr[1] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:1949:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.REFERENCED_VALUE__V2*/ meltfptr[1];;

        {
            MELT_LOCATION("warmelt-base.melt:1949:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.REFERENCED_VALUE__V2*/
        meltfptr[1] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("RETRIEVE_VALUE_DESCRIPTOR_LIST", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_29_WARMELTmiBASE_RETRIEVE_VALUE_DESCRIPTOR_LIST*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT fromline 1752 */

    /** start of frame for meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT// fromline 1568
        : public Melt_CallFrameWithValues<20>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[6];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<20> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT), clos) {};
        MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT() //the constructor fromline 1642
            : Melt_CallFrameWithValues<20> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<20> (fil,lin, sizeof(MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT)) {};
        MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<20> (fil,lin, sizeof(MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT


    /** end of frame for meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT fromline 1697**/

    /* end of frame for routine meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT fromline 1756 */

    /* classy proc frame meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT */
    MeltFrame_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LIST_REMOVE_LAST_ELEMENT", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3382:/ getarg");
    /*_.LIS__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_LIST__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.LIS__V2*/ meltfptr[1])) == MELTOBMAG_LIST);;
        /*^compute*/
        /*_#NOT__L2*/
        meltfnum[1] =
            (!(/*_#IS_LIST__L1*/ meltfnum[0]));;
        MELT_LOCATION("warmelt-base.melt:3386:/ cond");
        /*cond*/
        if (/*_#NOT__L2*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3387:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3387:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IF___V3*/
                    meltfptr[2] = /*_.RETURN___V4*/ meltfptr[3];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3386:/ clear");
                    /*clear*/ /*_.RETURN___V4*/
                    meltfptr[3] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V3*/ meltfptr[2] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3388:/ quasiblock");


        /*_.LASTPAIR__V5*/
        meltfptr[3] =
            (melt_list_last((melt_ptr_t)(/*_.LIS__V2*/ meltfptr[1])));;
        /*^compute*/
        /*_.PREVPAIR__V6*/
        meltfptr[5] = (/*nil*/NULL);;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3391:/ cond");
        /*cond*/
        if (/*_.LASTPAIR__V5*/ meltfptr[3]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


#if MELT_HAVE_DEBUG
                    /*^cppif.then*/
                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*_#IS_PAIR__L3*/
                        meltfnum[2] =
                        (melt_magic_discr((melt_ptr_t)(/*_.LASTPAIR__V5*/ meltfptr[3])) == MELTOBMAG_PAIR);;
                        MELT_LOCATION("warmelt-base.melt:3391:/ cond");
                        /*cond*/
                        if (/*_#IS_PAIR__L3*/ meltfnum[2]) /*then*/
                            {
                                /*^cond.then*/
                                /*_._IFELSE___V9*/ meltfptr[8] = (/*nil*/NULL);;
                            }
                        else {
                                MELT_LOCATION("warmelt-base.melt:3391:/ cond.else");

                                /*^block*/
                                /*anyblock*/
                                {


                                    MELT_CHECK_SIGNAL();
                                    ;
                                    /*^apply*/
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[3];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_cstring =  "check lastpair";
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 3391;
                                        /*_.MELT_ASSERT_FAILURE_FUN__V10*/
                                        meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IFELSE___V9*/
                                    meltfptr[8] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-base.melt:3391:/ clear");
                                    /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/
                                    meltfptr[9] = 0 ;
                                }
                                ;
                            }
                        ;
                        /*_.IFCPP___V8*/
                        meltfptr[7] = /*_._IFELSE___V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:3391:/ clear");
                        /*clear*/ /*_#IS_PAIR__L3*/
                        meltfnum[2] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IFELSE___V9*/
                        meltfptr[8] = 0 ;
                    }

#else /*MELT_HAVE_DEBUG*/
                    /*^cppif.else*/
                    /*_.IFCPP___V8*/ meltfptr[7] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                    ;
                    /*^compute*/
                    /*_._IFELSE___V7*/
                    meltfptr[6] = /*_.IFCPP___V8*/ meltfptr[7];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3391:/ clear");
                    /*clear*/ /*_.IFCPP___V8*/
                    meltfptr[7] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IFELSE___V7*/ meltfptr[6] = /*_.LASTPAIR__V5*/ meltfptr[3];;
            }
        ;
        /*citerblock FOREACH_PAIR_COMPONENT_IN_LIST*/
        {
            /* start foreach_pair_component_in_list meltcit1__EACHLIST */
            for (/*_.CURPAIR__V11*/ meltfptr[9] = melt_list_first( (melt_ptr_t)/*_.LIS__V2*/ meltfptr[1]);
                                    melt_magic_discr((melt_ptr_t) /*_.CURPAIR__V11*/ meltfptr[9]) == MELTOBMAG_PAIR;
                                    /*_.CURPAIR__V11*/ meltfptr[9] = melt_pair_tail((melt_ptr_t) /*_.CURPAIR__V11*/ meltfptr[9]))
                {
                    /*_.CURELEM__V12*/ meltfptr[8] = melt_pair_head((melt_ptr_t) /*_.CURPAIR__V11*/ meltfptr[9]);



#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-base.melt:3395:/ cppif.then");
                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*_#IS_PAIR__L4*/
                        meltfnum[2] =
                            (melt_magic_discr((melt_ptr_t)(/*_.CURPAIR__V11*/ meltfptr[9])) == MELTOBMAG_PAIR);;
                        MELT_LOCATION("warmelt-base.melt:3395:/ cond");
                        /*cond*/
                        if (/*_#IS_PAIR__L4*/ meltfnum[2]) /*then*/
                            {
                                /*^cond.then*/
                                /*_._IFELSE___V14*/ meltfptr[13] = (/*nil*/NULL);;
                            }
                        else
                            {
                                MELT_LOCATION("warmelt-base.melt:3395:/ cond.else");

                                /*^block*/
                                /*anyblock*/
                                {


                                    MELT_CHECK_SIGNAL();
                                    ;
                                    /*^apply*/
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[4];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_cstring =  "check curpair";
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 3395;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.CURPAIR__V11*/ meltfptr[9];
                                        /*_.MELT_ASSERT_FAILURE_FUN__V15*/
                                        meltfptr[14] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IFELSE___V14*/
                                    meltfptr[13] = /*_.MELT_ASSERT_FAILURE_FUN__V15*/ meltfptr[14];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-base.melt:3395:/ clear");
                                    /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V15*/
                                    meltfptr[14] = 0 ;
                                }
                                ;
                            }
                        ;
                        /*_.IFCPP___V13*/
                        meltfptr[7] = /*_._IFELSE___V14*/ meltfptr[13];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:3395:/ clear");
                        /*clear*/ /*_#IS_PAIR__L4*/
                        meltfnum[2] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IFELSE___V14*/
                        meltfptr[13] = 0 ;
                    }

#else /*MELT_HAVE_DEBUG*/
                    /*^cppif.else*/
                    /*_.IFCPP___V13*/ meltfptr[7] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    /*^compute*/
                    /*_#eqeq__L5*/
                    meltfnum[2] =
                        ((/*_.CURPAIR__V11*/ meltfptr[9]) == (/*_.LASTPAIR__V5*/ meltfptr[3]));;
                    MELT_LOCATION("warmelt-base.melt:3396:/ cond");
                    /*cond*/
                    if (/*_#eqeq__L5*/ meltfnum[2]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3397:/ compute");
                                /*_.CURPAIR__V11*/
                                meltfptr[9] = /*_.SETQ___V17*/ meltfptr[13] = (/*nil*/NULL);;

                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_PAIR__L6*/
                                meltfnum[5] =
                                    (melt_magic_discr((melt_ptr_t)(/*_.PREVPAIR__V6*/ meltfptr[5])) == MELTOBMAG_PAIR);;
                                MELT_LOCATION("warmelt-base.melt:3398:/ cond");
                                /*cond*/
                                if (/*_#IS_PAIR__L6*/ meltfnum[5]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            {
                                                MELT_LOCATION("warmelt-base.melt:3399:/ locexp");
                                                /* list_remove_last_element UPDATEPAIR_CHK__1 */
                                                ((struct meltpair_st*)/*_.PREVPAIR__V6*/ meltfptr[5])->tl = NULL;
                                                ((struct meltlist_st*)/*_.LIS__V2*/ meltfptr[1])->last
                                                    = (struct meltpair_st*) /*_.PREVPAIR__V6*/ meltfptr[5];
                                                meltgc_touch_dest (/*_.LIS__V2*/ meltfptr[1], /*_.PREVPAIR__V6*/ meltfptr[5]);
                                                ;
                                            }
                                            ;
                                            /*epilog*/
                                        }
                                        ;
                                    }
                                else
                                    {
                                        MELT_LOCATION("warmelt-base.melt:3398:/ cond.else");

                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            {
                                                MELT_LOCATION("warmelt-base.melt:3406:/ locexp");
                                                /* list_remove_last_element EMPTYLIST_CHK__1 */
                                                ((struct meltlist_st*)/*_.LIS__V2*/ meltfptr[1])->first = NULL;
                                                ((struct meltlist_st*)/*_.LIS__V2*/ meltfptr[1])->last = NULL;
                                                meltgc_touch (/*_.LIS__V2*/ meltfptr[1]);
                                                ;
                                            }
                                            ;
                                            /*epilog*/
                                        }
                                        ;
                                    }
                                ;

                                MELT_CHECK_SIGNAL();
                                ;
                                MELT_LOCATION("warmelt-base.melt:3412:/ quasiblock");


                                /*_._RETVAL___V1*/
                                meltfptr[0] = /*_.CURELEM__V12*/ meltfptr[8];;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3412:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                MELT_LOCATION("warmelt-base.melt:3396:/ quasiblock");


                                /*_.PROGN___V19*/
                                meltfptr[18] = /*_.RETURN___V18*/ meltfptr[17];;
                                /*^compute*/
                                /*_._IF___V16*/
                                meltfptr[14] = /*_.PROGN___V19*/ meltfptr[18];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3396:/ clear");
                                /*clear*/ /*_.SETQ___V17*/
                                meltfptr[13] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_#IS_PAIR__L6*/
                                meltfnum[5] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.RETURN___V18*/
                                meltfptr[17] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V19*/
                                meltfptr[18] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V16*/ meltfptr[14] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    MELT_LOCATION("warmelt-base.melt:3413:/ compute");
                    /*_.PREVPAIR__V6*/
                    meltfptr[5] = /*_.SETQ___V20*/ meltfptr[13] = /*_.CURPAIR__V11*/ meltfptr[9];;
                } /* end foreach_pair_component_in_list meltcit1__EACHLIST */
            /*_.CURPAIR__V11*/ meltfptr[9] = NULL;
            /*_.CURELEM__V12*/
            meltfptr[8] = NULL;


            /*citerepilog*/

            MELT_LOCATION("warmelt-base.melt:3392:/ clear");
            /*clear*/ /*_.CURPAIR__V11*/
            meltfptr[9] = 0 ;
            /*^clear*/
            /*clear*/ /*_.CURELEM__V12*/
            meltfptr[8] = 0 ;
            /*^clear*/
            /*clear*/ /*_.IFCPP___V13*/
            meltfptr[7] = 0 ;
            /*^clear*/
            /*clear*/ /*_#eqeq__L5*/
            meltfnum[2] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V16*/
            meltfptr[14] = 0 ;
            /*^clear*/
            /*clear*/ /*_.SETQ___V20*/
            meltfptr[13] = 0 ;
        } /*endciterblock FOREACH_PAIR_COMPONENT_IN_LIST*/
        ;

        MELT_LOCATION("warmelt-base.melt:3388:/ clear");
        /*clear*/ /*_.LASTPAIR__V5*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PREVPAIR__V6*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V7*/
        meltfptr[6] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        /*epilog*/

        MELT_LOCATION("warmelt-base.melt:3382:/ clear");
        /*clear*/ /*_#IS_LIST__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L2*/
        meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LIST_REMOVE_LAST_ELEMENT", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_30_WARMELTmiBASE_LIST_REMOVE_LAST_ELEMENT*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    /*variadic*/ int variad_COMPLETE_SEQUENCE_AS_TUPLE_ix = 0, variad_COMPLETE_SEQUENCE_AS_TUPLE_len = melt_argdescr_length (meltxargdescr_);
#define melt_variadic_length  (0+variad_COMPLETE_SEQUENCE_AS_TUPLE_len)
#define melt_variadic_index variad_COMPLETE_SEQUENCE_AS_TUPLE_ix

    long current_blocklevel_signals_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE fromline 1752 */

    /** start of frame for meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE// fromline 1568
        : public Melt_CallFrameWithValues<19>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[3];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<19> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE), clos) {};
        MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE() //the constructor fromline 1642
            : Melt_CallFrameWithValues<19> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<19> (fil,lin, sizeof(MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE)) {};
        MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<19> (fil,lin, sizeof(MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE


    /** end of frame for meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE fromline 1697**/

    /* end of frame for routine meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE fromline 1756 */

    /* classy proc frame meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE */
    MeltFrame_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("COMPLETE_SEQUENCE_AS_TUPLE", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3417:/ getarg");
    /*_.SRC__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3421:/ quasiblock");


        /*_.NEWLIST__V4*/
        meltfptr[3] =
            (meltgc_new_list((meltobject_ptr_t)((/*!DISCR_LIST*/ meltfrout->tabval[0]))));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_MULTIPLE__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1])) == MELTOBMAG_MULTIPLE);;
        MELT_LOCATION("warmelt-base.melt:3423:/ cond");
        /*cond*/
        if (/*_#IS_MULTIPLE__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*citerblock FOREACH_IN_MULTIPLE*/
                    {
                        /* start foreach_in_multiple meltcit1__EACHTUP */
                        long  meltcit1__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.SRC__V2*/ meltfptr[1]);
                        for (/*_#IX__L2*/ meltfnum[1] = 0;
                                          (/*_#IX__L2*/ meltfnum[1] >= 0) && (/*_#IX__L2*/ meltfnum[1] <  meltcit1__EACHTUP_ln);
                                          /*_#IX__L2*/ meltfnum[1]++)
                            {
                                /*_.COMP__V5*/ meltfptr[4] = melt_multiple_nth((melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1]),  /*_#IX__L2*/ meltfnum[1]);




                                {
                                    MELT_LOCATION("warmelt-base.melt:3427:/ locexp");
                                    meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.COMP__V5*/ meltfptr[4]));
                                }
                                ;
                                if (/*_#IX__L2*/ meltfnum[1]<0) break;
                            } /* end  foreach_in_multiple meltcit1__EACHTUP */

                        /*citerepilog*/

                        MELT_LOCATION("warmelt-base.melt:3424:/ clear");
                        /*clear*/ /*_.COMP__V5*/
                        meltfptr[4] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_#IX__L2*/
                        meltfnum[1] = 0 ;
                    } /*endciterblock FOREACH_IN_MULTIPLE*/
                    ;
                    /*epilog*/
                }
                ;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3423:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_LIST__L3*/
                    meltfnum[2] =
                        (melt_magic_discr((melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1])) == MELTOBMAG_LIST);;
                    MELT_LOCATION("warmelt-base.melt:3429:/ cond");
                    /*cond*/
                    if (/*_#IS_LIST__L3*/ meltfnum[2]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                /*citerblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                {
                                    /* start foreach_pair_component_in_list meltcit2__EACHLIST */
                                    for (/*_.CURPAIR__V6*/ meltfptr[5] = melt_list_first( (melt_ptr_t)/*_.SRC__V2*/ meltfptr[1]);
                                                           melt_magic_discr((melt_ptr_t) /*_.CURPAIR__V6*/ meltfptr[5]) == MELTOBMAG_PAIR;
                                                           /*_.CURPAIR__V6*/ meltfptr[5] = melt_pair_tail((melt_ptr_t) /*_.CURPAIR__V6*/ meltfptr[5]))
                                        {
                                            /*_.CURCOMP__V7*/ meltfptr[6] = melt_pair_head((melt_ptr_t) /*_.CURPAIR__V6*/ meltfptr[5]);



                                            {
                                                MELT_LOCATION("warmelt-base.melt:3433:/ locexp");
                                                meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.CURCOMP__V7*/ meltfptr[6]));
                                            }
                                            ;
                                        } /* end foreach_pair_component_in_list meltcit2__EACHLIST */
                                    /*_.CURPAIR__V6*/ meltfptr[5] = NULL;
                                    /*_.CURCOMP__V7*/
                                    meltfptr[6] = NULL;


                                    /*citerepilog*/

                                    MELT_LOCATION("warmelt-base.melt:3430:/ clear");
                                    /*clear*/ /*_.CURPAIR__V6*/
                                    meltfptr[5] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.CURCOMP__V7*/
                                    meltfptr[6] = 0 ;
                                } /*endciterblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                ;
                                /*epilog*/
                            }
                            ;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-base.melt:3429:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-base.melt:3436:/ locexp");
                                    meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1]));
                                }
                                ;
                                MELT_LOCATION("warmelt-base.melt:3435:/ quasiblock");


                                /*epilog*/
                            }
                            ;
                        }
                    ;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3423:/ clear");
                    /*clear*/ /*_#IS_LIST__L3*/
                    meltfnum[2] = 0 ;
                }
                ;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3437:/ loop");
        /*loop*/
        {
meltlabloop_ARGLOOP_4:;/*^loopbody*/

            /*^block*/
            /*anyblock*/
            {


                MELT_CHECK_SIGNAL();
                ;
                MELT_LOCATION("warmelt-base.melt:3440:/ cond");
                /*cond*/
                if (/*ifvariadic nomore*/ variad_COMPLETE_SEQUENCE_AS_TUPLE_ix == variad_COMPLETE_SEQUENCE_AS_TUPLE_len) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            /*^compute*/

                            /*consume variadic  !*/ variad_COMPLETE_SEQUENCE_AS_TUPLE_ix += 0;;
                            MELT_LOCATION("warmelt-base.melt:3441:/ quasiblock");


                            /*^compute*/
                            /*_.ARGLOOP__V9*/
                            meltfptr[8] =  /*reallynil*/ NULL ;;

                            /*^exit*/
                            /*exit*/
                            {
                                goto meltlabexit_ARGLOOP_4;
                            }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                else
                    {
                        MELT_LOCATION("warmelt-base.melt:3440:/ cond.else");

                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:3442:/ cond");
                            /*cond*/
                            if (/*ifvariadic arg#1*/ variad_COMPLETE_SEQUENCE_AS_TUPLE_ix>=0 && variad_COMPLETE_SEQUENCE_AS_TUPLE_ix + 1 <= variad_COMPLETE_SEQUENCE_AS_TUPLE_len && meltxargdescr_[variad_COMPLETE_SEQUENCE_AS_TUPLE_ix]== MELTBPAR_PTR) /*then*/
                                {
                                    /*^cond.then*/
                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        /*^compute*/
                                        /*_.V__V10*/ meltfptr[9] =
                                            /*variadic argument value*/ ((meltxargtab_[variad_COMPLETE_SEQUENCE_AS_TUPLE_ix + 0].meltbp_aptr) ? (*(meltxargtab_[variad_COMPLETE_SEQUENCE_AS_TUPLE_ix + 0].meltbp_aptr)) : NULL);;
                                        /*^compute*/

                                        /*consume variadic Value !*/
                                        variad_COMPLETE_SEQUENCE_AS_TUPLE_ix += 1;;

                                        {
                                            MELT_LOCATION("warmelt-base.melt:3443:/ locexp");
                                            meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.V__V10*/ meltfptr[9]));
                                        }
                                        ;
                                        /*epilog*/

                                        MELT_LOCATION("warmelt-base.melt:3442:/ clear");
                                        /*clear*/ /*_.V__V10*/
                                        meltfptr[9] = 0 ;
                                    }
                                    ;
                                }
                            else    /*^cond.else*/
                                {

                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        MELT_LOCATION("warmelt-base.melt:3445:/ quasiblock");


                                        /*_.VCTY__V12*/
                                        meltfptr[11] =
                                            /*variadic_type_code*/
#ifdef melt_variadic_index
                                            (((melt_variadic_index + 0) >= 0
                                              && (melt_variadic_index + 0) < melt_variadic_length)
                                             ?  melt_code_to_ctype (meltxargdescr_[melt_variadic_index + 0]
                                                                    & MELT_ARGDESCR_MAX)
                                             : NULL)
#else
                                            NULL /* no variadic_ctype outside of variadic functions */
#endif /*melt_variadic_index*/
                                            ;;
                                        MELT_LOCATION("warmelt-base.melt:3448:/ cond");
                                        /*cond*/
                                        if (
                                            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.VCTY__V12*/ meltfptr[11]),
                                                                          (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])))
                                        ) /*then*/
                                            {
                                                /*^cond.then*/
                                                /*^getslot*/
                                                {
                                                    melt_ptr_t slot=NULL, obj=NULL;
                                                    obj = (melt_ptr_t)(/*_.VCTY__V12*/ meltfptr[11]) /*=obj*/;
                                                    melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                    /*_.NAMED_NAME__V13*/
                                                    meltfptr[12] = slot;
                                                };
                                                ;
                                            }
                                        else    /*^cond.else*/
                                            {

                                                /*_.NAMED_NAME__V13*/ meltfptr[12] =  /*reallynil*/ NULL ;;
                                            }
                                        ;

                                        {
                                            MELT_LOCATION("warmelt-base.melt:3447:/ locexp");
                                            error ("MELT ERROR MSG [#%ld]::: %s - %s", melt_dbgcounter, ( "COMPLETE_SEQUENCE_AS_TUPLE with unsupported ctype"),
                                                   melt_string_str((melt_ptr_t)(/*_.NAMED_NAME__V13*/ meltfptr[12])));
                                        }
                                        ;

#if MELT_HAVE_DEBUG
                                        MELT_LOCATION("warmelt-base.melt:3449:/ cppif.then");
                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*^cond*/
                                            /*cond*/
                                            if ((/*nil*/NULL)) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*_._IFELSE___V15*/ meltfptr[14] = (/*nil*/NULL);;
                                                }
                                            else
                                                {
                                                    MELT_LOCATION("warmelt-base.melt:3449:/ cond.else");

                                                    /*^block*/
                                                    /*anyblock*/
                                                    {


                                                        MELT_CHECK_SIGNAL();
                                                        ;
                                                        /*^apply*/
                                                        /*apply*/
                                                        {
                                                            union meltparam_un argtab[4];
                                                            memset(&argtab, 0, sizeof(argtab));
                                                            /*^apply.arg*/
                                                            argtab[0].meltbp_cstring =  "invalid variadic argument to COMPLETE_SEQUENCE_AS_TUPLE";
                                                            /*^apply.arg*/
                                                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                                            /*^apply.arg*/
                                                            argtab[2].meltbp_long = 3449;
                                                            /*^apply.arg*/
                                                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.VCTY__V12*/ meltfptr[11];
                                                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/
                                                            meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                        }
                                                        ;
                                                        /*_._IFELSE___V15*/
                                                        meltfptr[14] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-base.melt:3449:/ clear");
                                                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/
                                                        meltfptr[15] = 0 ;
                                                    }
                                                    ;
                                                }
                                            ;
                                            /*_.IFCPP___V14*/
                                            meltfptr[13] = /*_._IFELSE___V15*/ meltfptr[14];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3449:/ clear");
                                            /*clear*/ /*_._IFELSE___V15*/
                                            meltfptr[14] = 0 ;
                                        }

#else /*MELT_HAVE_DEBUG*/
                                        /*^cppif.else*/
                                        /*_.IFCPP___V14*/ meltfptr[13] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                                        ;
                                        /*^compute*/
                                        /*_.LET___V11*/
                                        meltfptr[9] = /*_.IFCPP___V14*/ meltfptr[13];;

                                        MELT_LOCATION("warmelt-base.melt:3445:/ clear");
                                        /*clear*/ /*_.VCTY__V12*/
                                        meltfptr[11] = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.NAMED_NAME__V13*/
                                        meltfptr[12] = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.IFCPP___V14*/
                                        meltfptr[13] = 0 ;
                                        /*epilog*/

                                        MELT_LOCATION("warmelt-base.melt:3442:/ clear");
                                        /*clear*/ /*_.LET___V11*/
                                        meltfptr[9] = 0 ;
                                    }
                                    ;
                                }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                ;
                /*epilog*/
            }
            ;
            ;
            goto meltlabloop_ARGLOOP_4;
meltlabexit_ARGLOOP_4:
            ;
            MELT_LOCATION("warmelt-base.melt:3437:/ loopepilog");
            /*loopepilog*/
            /*_.FOREVER___V8*/
            meltfptr[7] = /*_.ARGLOOP__V9*/ meltfptr[8];;
        }
        ;
        MELT_LOCATION("warmelt-base.melt:3451:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            /*_.RES__V18*/ meltfptr[14] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[3])), (melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3453:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.RES__V18*/ meltfptr[14];;

        {
            MELT_LOCATION("warmelt-base.melt:3453:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V17*/
        meltfptr[15] = /*_.RETURN___V19*/ meltfptr[11];;

        MELT_LOCATION("warmelt-base.melt:3451:/ clear");
        /*clear*/ /*_.RES__V18*/
        meltfptr[14] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V19*/
        meltfptr[11] = 0 ;
        /*_.LET___V3*/
        meltfptr[2] = /*_.LET___V17*/ meltfptr[15];;

        MELT_LOCATION("warmelt-base.melt:3421:/ clear");
        /*clear*/ /*_.NEWLIST__V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_MULTIPLE__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.FOREVER___V8*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V17*/
        meltfptr[15] = 0 ;
        MELT_LOCATION("warmelt-base.melt:3417:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3417:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("COMPLETE_SEQUENCE_AS_TUPLE", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef melt_variadic_length
#undef melt_variadic_index

#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_31_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_TUPLE*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    /*variadic*/ int variad_COMPLETE_SEQUENCE_AS_LIST_ix = 0, variad_COMPLETE_SEQUENCE_AS_LIST_len = melt_argdescr_length (meltxargdescr_);
#define melt_variadic_length  (0+variad_COMPLETE_SEQUENCE_AS_LIST_len)
#define melt_variadic_index variad_COMPLETE_SEQUENCE_AS_LIST_ix

    long current_blocklevel_signals_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST fromline 1752 */

    /** start of frame for meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST// fromline 1568
        : public Melt_CallFrameWithValues<17>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[3];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<17> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST), clos) {};
        MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST() //the constructor fromline 1642
            : Melt_CallFrameWithValues<17> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<17> (fil,lin, sizeof(MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST)) {};
        MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<17> (fil,lin, sizeof(MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST


    /** end of frame for meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST fromline 1697**/

    /* end of frame for routine meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST fromline 1756 */

    /* classy proc frame meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST */
    MeltFrame_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("COMPLETE_SEQUENCE_AS_LIST", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3457:/ getarg");
    /*_.SRC__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3461:/ quasiblock");


        /*_.NEWLIST__V4*/
        meltfptr[3] =
            (meltgc_new_list((meltobject_ptr_t)((/*!DISCR_LIST*/ meltfrout->tabval[0]))));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_MULTIPLE__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1])) == MELTOBMAG_MULTIPLE);;
        MELT_LOCATION("warmelt-base.melt:3463:/ cond");
        /*cond*/
        if (/*_#IS_MULTIPLE__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*citerblock FOREACH_IN_MULTIPLE*/
                    {
                        /* start foreach_in_multiple meltcit1__EACHTUP */
                        long  meltcit1__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.SRC__V2*/ meltfptr[1]);
                        for (/*_#IX__L2*/ meltfnum[1] = 0;
                                          (/*_#IX__L2*/ meltfnum[1] >= 0) && (/*_#IX__L2*/ meltfnum[1] <  meltcit1__EACHTUP_ln);
                                          /*_#IX__L2*/ meltfnum[1]++)
                            {
                                /*_.COMP__V5*/ meltfptr[4] = melt_multiple_nth((melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1]),  /*_#IX__L2*/ meltfnum[1]);




                                {
                                    MELT_LOCATION("warmelt-base.melt:3467:/ locexp");
                                    meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.COMP__V5*/ meltfptr[4]));
                                }
                                ;
                                if (/*_#IX__L2*/ meltfnum[1]<0) break;
                            } /* end  foreach_in_multiple meltcit1__EACHTUP */

                        /*citerepilog*/

                        MELT_LOCATION("warmelt-base.melt:3464:/ clear");
                        /*clear*/ /*_.COMP__V5*/
                        meltfptr[4] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_#IX__L2*/
                        meltfnum[1] = 0 ;
                    } /*endciterblock FOREACH_IN_MULTIPLE*/
                    ;
                    /*epilog*/
                }
                ;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3463:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_LIST__L3*/
                    meltfnum[2] =
                        (melt_magic_discr((melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1])) == MELTOBMAG_LIST);;
                    MELT_LOCATION("warmelt-base.melt:3469:/ cond");
                    /*cond*/
                    if (/*_#IS_LIST__L3*/ meltfnum[2]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                /*citerblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                {
                                    /* start foreach_pair_component_in_list meltcit2__EACHLIST */
                                    for (/*_.CURPAIR__V6*/ meltfptr[5] = melt_list_first( (melt_ptr_t)/*_.SRC__V2*/ meltfptr[1]);
                                                           melt_magic_discr((melt_ptr_t) /*_.CURPAIR__V6*/ meltfptr[5]) == MELTOBMAG_PAIR;
                                                           /*_.CURPAIR__V6*/ meltfptr[5] = melt_pair_tail((melt_ptr_t) /*_.CURPAIR__V6*/ meltfptr[5]))
                                        {
                                            /*_.CURCOMP__V7*/ meltfptr[6] = melt_pair_head((melt_ptr_t) /*_.CURPAIR__V6*/ meltfptr[5]);



                                            {
                                                MELT_LOCATION("warmelt-base.melt:3473:/ locexp");
                                                meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.CURCOMP__V7*/ meltfptr[6]));
                                            }
                                            ;
                                        } /* end foreach_pair_component_in_list meltcit2__EACHLIST */
                                    /*_.CURPAIR__V6*/ meltfptr[5] = NULL;
                                    /*_.CURCOMP__V7*/
                                    meltfptr[6] = NULL;


                                    /*citerepilog*/

                                    MELT_LOCATION("warmelt-base.melt:3470:/ clear");
                                    /*clear*/ /*_.CURPAIR__V6*/
                                    meltfptr[5] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.CURCOMP__V7*/
                                    meltfptr[6] = 0 ;
                                } /*endciterblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                ;
                                /*epilog*/
                            }
                            ;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-base.melt:3469:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-base.melt:3476:/ locexp");
                                    meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.SRC__V2*/ meltfptr[1]));
                                }
                                ;
                                MELT_LOCATION("warmelt-base.melt:3475:/ quasiblock");


                                /*epilog*/
                            }
                            ;
                        }
                    ;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3463:/ clear");
                    /*clear*/ /*_#IS_LIST__L3*/
                    meltfnum[2] = 0 ;
                }
                ;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3477:/ loop");
        /*loop*/
        {
meltlabloop_ARGLOOP_5:;/*^loopbody*/

            /*^block*/
            /*anyblock*/
            {


                MELT_CHECK_SIGNAL();
                ;
                MELT_LOCATION("warmelt-base.melt:3480:/ cond");
                /*cond*/
                if (/*ifvariadic nomore*/ variad_COMPLETE_SEQUENCE_AS_LIST_ix == variad_COMPLETE_SEQUENCE_AS_LIST_len) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            /*^compute*/

                            /*consume variadic  !*/ variad_COMPLETE_SEQUENCE_AS_LIST_ix += 0;;
                            MELT_LOCATION("warmelt-base.melt:3481:/ quasiblock");


                            /*^compute*/
                            /*_.ARGLOOP__V9*/
                            meltfptr[8] =  /*reallynil*/ NULL ;;

                            /*^exit*/
                            /*exit*/
                            {
                                goto meltlabexit_ARGLOOP_5;
                            }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                else
                    {
                        MELT_LOCATION("warmelt-base.melt:3480:/ cond.else");

                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:3482:/ cond");
                            /*cond*/
                            if (/*ifvariadic arg#1*/ variad_COMPLETE_SEQUENCE_AS_LIST_ix>=0 && variad_COMPLETE_SEQUENCE_AS_LIST_ix + 1 <= variad_COMPLETE_SEQUENCE_AS_LIST_len && meltxargdescr_[variad_COMPLETE_SEQUENCE_AS_LIST_ix]== MELTBPAR_PTR) /*then*/
                                {
                                    /*^cond.then*/
                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        /*^compute*/
                                        /*_.V__V10*/ meltfptr[9] =
                                            /*variadic argument value*/ ((meltxargtab_[variad_COMPLETE_SEQUENCE_AS_LIST_ix + 0].meltbp_aptr) ? (*(meltxargtab_[variad_COMPLETE_SEQUENCE_AS_LIST_ix + 0].meltbp_aptr)) : NULL);;
                                        /*^compute*/

                                        /*consume variadic Value !*/
                                        variad_COMPLETE_SEQUENCE_AS_LIST_ix += 1;;

                                        {
                                            MELT_LOCATION("warmelt-base.melt:3483:/ locexp");
                                            meltgc_append_list((melt_ptr_t)(/*_.NEWLIST__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.V__V10*/ meltfptr[9]));
                                        }
                                        ;
                                        /*epilog*/

                                        MELT_LOCATION("warmelt-base.melt:3482:/ clear");
                                        /*clear*/ /*_.V__V10*/
                                        meltfptr[9] = 0 ;
                                    }
                                    ;
                                }
                            else    /*^cond.else*/
                                {

                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        MELT_LOCATION("warmelt-base.melt:3485:/ quasiblock");


                                        /*_.VCTY__V12*/
                                        meltfptr[11] =
                                            /*variadic_type_code*/
#ifdef melt_variadic_index
                                            (((melt_variadic_index + 0) >= 0
                                              && (melt_variadic_index + 0) < melt_variadic_length)
                                             ?  melt_code_to_ctype (meltxargdescr_[melt_variadic_index + 0]
                                                                    & MELT_ARGDESCR_MAX)
                                             : NULL)
#else
                                            NULL /* no variadic_ctype outside of variadic functions */
#endif /*melt_variadic_index*/
                                            ;;
                                        MELT_LOCATION("warmelt-base.melt:3488:/ cond");
                                        /*cond*/
                                        if (
                                            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.VCTY__V12*/ meltfptr[11]),
                                                                          (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])))
                                        ) /*then*/
                                            {
                                                /*^cond.then*/
                                                /*^getslot*/
                                                {
                                                    melt_ptr_t slot=NULL, obj=NULL;
                                                    obj = (melt_ptr_t)(/*_.VCTY__V12*/ meltfptr[11]) /*=obj*/;
                                                    melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                    /*_.NAMED_NAME__V13*/
                                                    meltfptr[12] = slot;
                                                };
                                                ;
                                            }
                                        else    /*^cond.else*/
                                            {

                                                /*_.NAMED_NAME__V13*/ meltfptr[12] =  /*reallynil*/ NULL ;;
                                            }
                                        ;

                                        {
                                            MELT_LOCATION("warmelt-base.melt:3487:/ locexp");
                                            error ("MELT ERROR MSG [#%ld]::: %s - %s", melt_dbgcounter, ( "COMPLETE_SEQUENCE_AS_LIST with unsupported ctype"),
                                                   melt_string_str((melt_ptr_t)(/*_.NAMED_NAME__V13*/ meltfptr[12])));
                                        }
                                        ;

#if MELT_HAVE_DEBUG
                                        MELT_LOCATION("warmelt-base.melt:3489:/ cppif.then");
                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*^cond*/
                                            /*cond*/
                                            if ((/*nil*/NULL)) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*_._IFELSE___V15*/ meltfptr[14] = (/*nil*/NULL);;
                                                }
                                            else
                                                {
                                                    MELT_LOCATION("warmelt-base.melt:3489:/ cond.else");

                                                    /*^block*/
                                                    /*anyblock*/
                                                    {


                                                        MELT_CHECK_SIGNAL();
                                                        ;
                                                        /*^apply*/
                                                        /*apply*/
                                                        {
                                                            union meltparam_un argtab[4];
                                                            memset(&argtab, 0, sizeof(argtab));
                                                            /*^apply.arg*/
                                                            argtab[0].meltbp_cstring =  "invalid variadic argument to COMPLETE_SEQUENCE_AS_LIST";
                                                            /*^apply.arg*/
                                                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                                            /*^apply.arg*/
                                                            argtab[2].meltbp_long = 3489;
                                                            /*^apply.arg*/
                                                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.VCTY__V12*/ meltfptr[11];
                                                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/
                                                            meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                        }
                                                        ;
                                                        /*_._IFELSE___V15*/
                                                        meltfptr[14] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-base.melt:3489:/ clear");
                                                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/
                                                        meltfptr[15] = 0 ;
                                                    }
                                                    ;
                                                }
                                            ;
                                            /*_.IFCPP___V14*/
                                            meltfptr[13] = /*_._IFELSE___V15*/ meltfptr[14];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3489:/ clear");
                                            /*clear*/ /*_._IFELSE___V15*/
                                            meltfptr[14] = 0 ;
                                        }

#else /*MELT_HAVE_DEBUG*/
                                        /*^cppif.else*/
                                        /*_.IFCPP___V14*/ meltfptr[13] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                                        ;
                                        /*^compute*/
                                        /*_.LET___V11*/
                                        meltfptr[9] = /*_.IFCPP___V14*/ meltfptr[13];;

                                        MELT_LOCATION("warmelt-base.melt:3485:/ clear");
                                        /*clear*/ /*_.VCTY__V12*/
                                        meltfptr[11] = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.NAMED_NAME__V13*/
                                        meltfptr[12] = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.IFCPP___V14*/
                                        meltfptr[13] = 0 ;
                                        /*epilog*/

                                        MELT_LOCATION("warmelt-base.melt:3482:/ clear");
                                        /*clear*/ /*_.LET___V11*/
                                        meltfptr[9] = 0 ;
                                    }
                                    ;
                                }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                ;
                /*epilog*/
            }
            ;
            ;
            goto meltlabloop_ARGLOOP_5;
meltlabexit_ARGLOOP_5:
            ;
            MELT_LOCATION("warmelt-base.melt:3477:/ loopepilog");
            /*loopepilog*/
            /*_.FOREVER___V8*/
            meltfptr[7] = /*_.ARGLOOP__V9*/ meltfptr[8];;
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3491:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.NEWLIST__V4*/ meltfptr[3];;

        {
            MELT_LOCATION("warmelt-base.melt:3491:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V3*/
        meltfptr[2] = /*_.RETURN___V17*/ meltfptr[15];;

        MELT_LOCATION("warmelt-base.melt:3461:/ clear");
        /*clear*/ /*_.NEWLIST__V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_MULTIPLE__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.FOREVER___V8*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V17*/
        meltfptr[15] = 0 ;
        MELT_LOCATION("warmelt-base.melt:3457:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3457:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("COMPLETE_SEQUENCE_AS_LIST", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef melt_variadic_length
#undef melt_variadic_index

#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_32_WARMELTmiBASE_COMPLETE_SEQUENCE_AS_LIST*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET fromline 1752 */

    /** start of frame for meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET// fromline 1568
        : public Melt_CallFrameWithValues<12>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[4];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<12> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET), clos) {};
        MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET() //the constructor fromline 1642
            : Melt_CallFrameWithValues<12> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<12> (fil,lin, sizeof(MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET)) {};
        MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<12> (fil,lin, sizeof(MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET


    /** end of frame for meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET fromline 1697**/

    /* end of frame for routine meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET fromline 1756 */

    /* classy proc frame meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET */
    MeltFrame_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MELT_PREDEFINED_GET", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3518:/ getarg");
    /*_.NAMV__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_STRING__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-base.melt:3520:/ cond");
        /*cond*/
        if (/*_#IS_STRING__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.PREDEFSTR_CHK__V4*/ meltfptr[3] =
                        /*melt_predefined_get PREDEFSTR_CHK__1 */
                        melt_fetch_predefined (melt_predefined_index_by_name (melt_string_str ((melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1])))) ;;
                    /*^compute*/
                    /*_._IFELSE___V3*/
                    meltfptr[2] = /*_.PREDEFSTR_CHK__V4*/ meltfptr[3];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3520:/ clear");
                    /*clear*/ /*_.PREDEFSTR_CHK__V4*/
                    meltfptr[3] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L2*/
                    meltfnum[1] =
                        melt_is_instance_of((melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])));;
                    MELT_LOCATION("warmelt-base.melt:3523:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L2*/ meltfnum[1]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3524:/ quasiblock");


                                /*^cond*/
                                /*cond*/
                                if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1]),
                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                            /*_.NAMSTR__V7*/
                                            meltfptr[6] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.NAMSTR__V7*/ meltfptr[6] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                /*^compute*/
                                /*_.PREDEFNAM_CHK__V8*/
                                meltfptr[7] =
                                    /*melt_predefined_get PREDEFNAM_CHK__1 */
                                    melt_fetch_predefined (melt_predefined_index_by_name (melt_string_str ((melt_ptr_t)(/*_.NAMSTR__V7*/ meltfptr[6])))) ;;
                                /*^compute*/
                                /*_.LET___V6*/
                                meltfptr[5] = /*_.PREDEFNAM_CHK__V8*/ meltfptr[7];;

                                MELT_LOCATION("warmelt-base.melt:3524:/ clear");
                                /*clear*/ /*_.NAMSTR__V7*/
                                meltfptr[6] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PREDEFNAM_CHK__V8*/
                                meltfptr[7] = 0 ;
                                /*_._IFELSE___V5*/
                                meltfptr[3] = /*_.LET___V6*/ meltfptr[5];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3523:/ clear");
                                /*clear*/ /*_.LET___V6*/
                                meltfptr[5] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_INTEGERBOX__L3*/
                                meltfnum[2] =
                                    (melt_magic_discr((melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1])) == MELTOBMAG_INT);;
                                MELT_LOCATION("warmelt-base.melt:3529:/ cond");
                                /*cond*/
                                if (/*_#IS_INTEGERBOX__L3*/ meltfnum[2]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:3530:/ quasiblock");


                                            /*_#NUM__L4*/
                                            meltfnum[3] =
                                                (melt_get_int((melt_ptr_t)(/*_.NAMV__V2*/ meltfptr[1])));;
                                            /*^compute*/
                                            /*_.PREDEFNAM_CHK__V11*/
                                            meltfptr[5] =
                                                /*melt_predefined_get PREDEFNAM_CHK__2 */
                                                melt_fetch_predefined (/*_#NUM__L4*/ meltfnum[3]) ;;
                                            /*^compute*/
                                            /*_.LET___V10*/
                                            meltfptr[7] = /*_.PREDEFNAM_CHK__V11*/ meltfptr[5];;

                                            MELT_LOCATION("warmelt-base.melt:3530:/ clear");
                                            /*clear*/ /*_#NUM__L4*/
                                            meltfnum[3] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.PREDEFNAM_CHK__V11*/
                                            meltfptr[5] = 0 ;
                                            /*_._IFELSE___V9*/
                                            meltfptr[6] = /*_.LET___V10*/ meltfptr[7];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3529:/ clear");
                                            /*clear*/ /*_.LET___V10*/
                                            meltfptr[7] = 0 ;
                                        }
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:3534:/ quasiblock");


                                            /*_.PROGN___V12*/
                                            meltfptr[5] = (/*nil*/NULL);;
                                            /*^compute*/
                                            /*_._IFELSE___V9*/
                                            meltfptr[6] = /*_.PROGN___V12*/ meltfptr[5];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3529:/ clear");
                                            /*clear*/ /*_.PROGN___V12*/
                                            meltfptr[5] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V5*/
                                meltfptr[3] = /*_._IFELSE___V9*/ meltfptr[6];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3523:/ clear");
                                /*clear*/ /*_#IS_INTEGERBOX__L3*/
                                meltfnum[2] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V9*/
                                meltfptr[6] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_._IFELSE___V3*/
                    meltfptr[2] = /*_._IFELSE___V5*/ meltfptr[3];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3520:/ clear");
                    /*clear*/ /*_#IS_A__L2*/
                    meltfnum[1] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V5*/
                    meltfptr[3] = 0 ;
                }
                ;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3518:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_._IFELSE___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3518:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#IS_STRING__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MELT_PREDEFINED_GET", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_33_WARMELTmiBASE_MELT_PREDEFINED_GET*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_34_WARMELTmiBASE_SYMBOL_CNAME(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                       const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_34_WARMELTmiBASE_SYMBOL_CNAME fromline 1752 */

    /** start of frame for meltrout_34_WARMELTmiBASE_SYMBOL_CNAME of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME// fromline 1568
        : public Melt_CallFrameWithValues<20>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[3];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<20> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME), clos) {};
        MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME() //the constructor fromline 1642
            : Melt_CallFrameWithValues<20> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<20> (fil,lin, sizeof(MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME)) {};
        MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<20> (fil,lin, sizeof(MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME


    /** end of frame for meltrout_34_WARMELTmiBASE_SYMBOL_CNAME fromline 1697**/

    /* end of frame for routine meltrout_34_WARMELTmiBASE_SYMBOL_CNAME fromline 1756 */

    /* classy proc frame meltrout_34_WARMELTmiBASE_SYMBOL_CNAME */
    MeltFrame_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_34_WARMELTmiBASE_SYMBOL_CNAME fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("SYMBOL_CNAME", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3538:/ getarg");
    /*_.SY__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_A__L1*/
        meltfnum[0] =
            melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_CLONED_SYMBOL*/ meltfrout->tabval[0])));;
        MELT_LOCATION("warmelt-base.melt:3540:/ cond");
        /*cond*/
        if (/*_#IS_A__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    MELT_LOCATION("warmelt-base.melt:3541:/ quasiblock");


                    /*_.SBUF__V5*/
                    meltfptr[4] =
                        (melt_ptr_t) meltgc_new_strbuf((meltobject_ptr_t)((/*!DISCR_STRBUF*/ meltfrout->tabval[1])), (const char*)0);;
                    MELT_LOCATION("warmelt-base.melt:3542:/ cond");
                    /*cond*/
                    if (
                        /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]),
                                                      (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[2])))
                    ) /*then*/
                        {
                            /*^cond.then*/
                            /*^getslot*/
                            {
                                melt_ptr_t slot=NULL, obj=NULL;
                                obj = (melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]) /*=obj*/;
                                melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                /*_.NAMED_NAME__V6*/
                                meltfptr[5] = slot;
                            };
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_.NAMED_NAME__V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                        }
                    ;

                    {
                        MELT_LOCATION("warmelt-base.melt:3542:/ locexp");
                        meltgc_add_strbuf_cident((melt_ptr_t)(/*_.SBUF__V5*/ meltfptr[4]),
                                                 melt_string_str((melt_ptr_t)(/*_.NAMED_NAME__V6*/ meltfptr[5])));
                    }
                    ;
                    MELT_LOCATION("warmelt-base.melt:3543:/ cond");
                    /*cond*/
                    if (
                        /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]),
                                                      (melt_ptr_t)((/*!CLASS_CLONED_SYMBOL*/ meltfrout->tabval[0])))
                    ) /*then*/
                        {
                            /*^cond.then*/
                            /*^getslot*/
                            {
                                melt_ptr_t slot=NULL, obj=NULL;
                                obj = (melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]) /*=obj*/;
                                melt_object_get_field(slot,obj, 3, "CSYM_URANK");
                                /*_.CSYM_URANK__V7*/
                                meltfptr[6] = slot;
                            };
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_.CSYM_URANK__V7*/ meltfptr[6] =  /*reallynil*/ NULL ;;
                        }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3543:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[2];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_cstring =  "cl";
                        /*^apply.arg*/
                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.CSYM_URANK__V7*/ meltfptr[6];
                        /*_.ADD2OUT__V8*/
                        meltfptr[7] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[3])), (melt_ptr_t)(/*_.SBUF__V5*/ meltfptr[4]), (MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    /*_.STRBUF2STRING__V9*/
                    meltfptr[8] =
                        (meltgc_new_stringdup((meltobject_ptr_t)((/*!DISCR_VERBATIM_STRING*/ meltfrout->tabval[4])), melt_strbuf_str((melt_ptr_t)(/*_.SBUF__V5*/ meltfptr[4]))));;
                    /*^compute*/
                    /*_.LET___V4*/
                    meltfptr[3] = /*_.STRBUF2STRING__V9*/ meltfptr[8];;

                    MELT_LOCATION("warmelt-base.melt:3541:/ clear");
                    /*clear*/ /*_.SBUF__V5*/
                    meltfptr[4] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.NAMED_NAME__V6*/
                    meltfptr[5] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.CSYM_URANK__V7*/
                    meltfptr[6] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.ADD2OUT__V8*/
                    meltfptr[7] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.STRBUF2STRING__V9*/
                    meltfptr[8] = 0 ;
                    /*_._IFELSE___V3*/
                    meltfptr[2] = /*_.LET___V4*/ meltfptr[3];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3540:/ clear");
                    /*clear*/ /*_.LET___V4*/
                    meltfptr[3] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L2*/
                    meltfnum[1] =
                        melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_KEYWORD*/ meltfrout->tabval[5])));;
                    MELT_LOCATION("warmelt-base.melt:3546:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L2*/ meltfnum[1]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3547:/ quasiblock");


                                /*_.SBUF__V12*/
                                meltfptr[6] =
                                    (melt_ptr_t) meltgc_new_strbuf((meltobject_ptr_t)((/*!DISCR_STRBUF*/ meltfrout->tabval[1])), (const char*)0);;
                                MELT_LOCATION("warmelt-base.melt:3548:/ cond");
                                /*cond*/
                                if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]),
                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[2])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                            /*_.NAMED_NAME__V13*/
                                            meltfptr[7] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.NAMED_NAME__V13*/ meltfptr[7] =  /*reallynil*/ NULL ;;
                                    }
                                ;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3548:/ locexp");
                                    meltgc_add_strbuf_cident((melt_ptr_t)(/*_.SBUF__V12*/ meltfptr[6]),
                                                             melt_string_str((melt_ptr_t)(/*_.NAMED_NAME__V13*/ meltfptr[7])));
                                }
                                ;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3549:/ locexp");
                                    /*add2sbuf_strconst*/
                                    meltgc_add_strbuf((melt_ptr_t)(/*_.SBUF__V12*/ meltfptr[6]), ( "kw"));
                                }
                                ;
                                /*_.STRBUF2STRING__V14*/
                                meltfptr[8] =
                                    (meltgc_new_stringdup((meltobject_ptr_t)((/*!DISCR_VERBATIM_STRING*/ meltfrout->tabval[4])), melt_strbuf_str((melt_ptr_t)(/*_.SBUF__V12*/ meltfptr[6]))));;
                                /*^compute*/
                                /*_.LET___V11*/
                                meltfptr[5] = /*_.STRBUF2STRING__V14*/ meltfptr[8];;

                                MELT_LOCATION("warmelt-base.melt:3547:/ clear");
                                /*clear*/ /*_.SBUF__V12*/
                                meltfptr[6] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.NAMED_NAME__V13*/
                                meltfptr[7] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.STRBUF2STRING__V14*/
                                meltfptr[8] = 0 ;
                                /*_._IFELSE___V10*/
                                meltfptr[4] = /*_.LET___V11*/ meltfptr[5];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3546:/ clear");
                                /*clear*/ /*_.LET___V11*/
                                meltfptr[5] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_A__L3*/
                                meltfnum[2] =
                                    melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[6])));;
                                MELT_LOCATION("warmelt-base.melt:3552:/ cond");
                                /*cond*/
                                if (/*_#IS_A__L3*/ meltfnum[2]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:3553:/ quasiblock");


                                            /*_.SBUF__V17*/
                                            meltfptr[7] =
                                                (melt_ptr_t) meltgc_new_strbuf((meltobject_ptr_t)((/*!DISCR_STRBUF*/ meltfrout->tabval[1])), (const char*)0);;
                                            MELT_LOCATION("warmelt-base.melt:3554:/ cond");
                                            /*cond*/
                                            if (
                                                /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]),
                                                                              (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[2])))
                                            ) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^getslot*/
                                                    {
                                                        melt_ptr_t slot=NULL, obj=NULL;
                                                        obj = (melt_ptr_t)(/*_.SY__V2*/ meltfptr[1]) /*=obj*/;
                                                        melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                        /*_.NAMED_NAME__V18*/
                                                        meltfptr[8] = slot;
                                                    };
                                                    ;
                                                }
                                            else    /*^cond.else*/
                                                {

                                                    /*_.NAMED_NAME__V18*/ meltfptr[8] =  /*reallynil*/ NULL ;;
                                                }
                                            ;

                                            {
                                                MELT_LOCATION("warmelt-base.melt:3554:/ locexp");
                                                meltgc_add_strbuf_cident((melt_ptr_t)(/*_.SBUF__V17*/ meltfptr[7]),
                                                                         melt_string_str((melt_ptr_t)(/*_.NAMED_NAME__V18*/ meltfptr[8])));
                                            }
                                            ;
                                            /*_.STRBUF2STRING__V19*/
                                            meltfptr[5] =
                                                (meltgc_new_stringdup((meltobject_ptr_t)((/*!DISCR_VERBATIM_STRING*/ meltfrout->tabval[4])), melt_strbuf_str((melt_ptr_t)(/*_.SBUF__V17*/ meltfptr[7]))));;
                                            /*^compute*/
                                            /*_.LET___V16*/
                                            meltfptr[6] = /*_.STRBUF2STRING__V19*/ meltfptr[5];;

                                            MELT_LOCATION("warmelt-base.melt:3553:/ clear");
                                            /*clear*/ /*_.SBUF__V17*/
                                            meltfptr[7] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.NAMED_NAME__V18*/
                                            meltfptr[8] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.STRBUF2STRING__V19*/
                                            meltfptr[5] = 0 ;
                                            /*_._IFELSE___V15*/
                                            meltfptr[3] = /*_.LET___V16*/ meltfptr[6];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3552:/ clear");
                                            /*clear*/ /*_.LET___V16*/
                                            meltfptr[6] = 0 ;
                                        }
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:3557:/ quasiblock");


                                            /*_.PROGN___V20*/
                                            meltfptr[7] = (/*nil*/NULL);;
                                            /*^compute*/
                                            /*_._IFELSE___V15*/
                                            meltfptr[3] = /*_.PROGN___V20*/ meltfptr[7];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3552:/ clear");
                                            /*clear*/ /*_.PROGN___V20*/
                                            meltfptr[7] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V10*/
                                meltfptr[4] = /*_._IFELSE___V15*/ meltfptr[3];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3546:/ clear");
                                /*clear*/ /*_#IS_A__L3*/
                                meltfnum[2] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V15*/
                                meltfptr[3] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_._IFELSE___V3*/
                    meltfptr[2] = /*_._IFELSE___V10*/ meltfptr[4];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3540:/ clear");
                    /*clear*/ /*_#IS_A__L2*/
                    meltfnum[1] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V10*/
                    meltfptr[4] = 0 ;
                }
                ;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3538:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_._IFELSE___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3538:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#IS_A__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("SYMBOL_CNAME", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_34_WARMELTmiBASE_SYMBOL_CNAME_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_34_WARMELTmiBASE_SYMBOL_CNAME*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    /*variadic*/ int variad_MELT_MAKE_SEXPR_ix = 0, variad_MELT_MAKE_SEXPR_len = melt_argdescr_length (meltxargdescr_);
#define melt_variadic_length  (0+variad_MELT_MAKE_SEXPR_len)
#define melt_variadic_index variad_MELT_MAKE_SEXPR_ix

    long current_blocklevel_signals_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR fromline 1752 */

    /** start of frame for meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR// fromline 1568
        : public Melt_CallFrameWithValues<58>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[23];
        /*classy others*/
        const char* loc_CSTRING__o0;
        const char* loc_CSTRING__o1;
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<58> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR), clos) {};
        MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR() //the constructor fromline 1642
            : Melt_CallFrameWithValues<58> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<58> (fil,lin, sizeof(MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR)) {};
        MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<58> (fil,lin, sizeof(MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR


    /** end of frame for meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR fromline 1697**/

    /* end of frame for routine meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR fromline 1756 */

    /* classy proc frame meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR */
    MeltFrame_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MELT_MAKE_SEXPR", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3569:/ getarg");
    /*_.LOC__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3573:/ quasiblock");


        /*_.CONT__V4*/
        meltfptr[3] =
            (meltgc_new_list((meltobject_ptr_t)((/*!DISCR_LIST*/ meltfrout->tabval[0]))));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_MIXINT__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.LOC__V2*/ meltfptr[1])) == MELTOBMAG_MIXINT);;
        MELT_LOCATION("warmelt-base.melt:3574:/ cond");
        /*cond*/
        if (/*_#IS_MIXINT__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*_.VLOC__V5*/ meltfptr[4] = /*_.LOC__V2*/ meltfptr[1];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3574:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_MIXLOC__L2*/
                    meltfnum[1] =
                        (melt_magic_discr((melt_ptr_t)(/*_.LOC__V2*/ meltfptr[1])) == MELTOBMAG_MIXLOC);;
                    MELT_LOCATION("warmelt-base.melt:3577:/ cond");
                    /*cond*/
                    if (/*_#IS_MIXLOC__L2*/ meltfnum[1]) /*then*/
                        {
                            /*^cond.then*/
                            /*_._IFELSE___V6*/ meltfptr[5] = /*_.LOC__V2*/ meltfptr[1];;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-base.melt:3577:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_A__L3*/
                                meltfnum[2] =
                                    melt_is_instance_of((melt_ptr_t)(/*_.LOC__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_LOCATED*/ meltfrout->tabval[1])));;
                                MELT_LOCATION("warmelt-base.melt:3579:/ cond");
                                /*cond*/
                                if (/*_#IS_A__L3*/ meltfnum[2]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:3580:/ getslot");
                                            {
                                                melt_ptr_t slot=NULL, obj=NULL;
                                                obj = (melt_ptr_t)(/*_.LOC__V2*/ meltfptr[1]) /*=obj*/;
                                                melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
                                                /*_.LOCA_LOCATION__V8*/
                                                meltfptr[7] = slot;
                                            };
                                            ;
                                            /*_._IFELSE___V7*/
                                            meltfptr[6] = /*_.LOCA_LOCATION__V8*/ meltfptr[7];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3579:/ clear");
                                            /*clear*/ /*_.LOCA_LOCATION__V8*/
                                            meltfptr[7] = 0 ;
                                        }
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:3581:/ quasiblock");


                                            /*_.PROGN___V9*/
                                            meltfptr[7] = (/*nil*/NULL);;
                                            /*^compute*/
                                            /*_._IFELSE___V7*/
                                            meltfptr[6] = /*_.PROGN___V9*/ meltfptr[7];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3579:/ clear");
                                            /*clear*/ /*_.PROGN___V9*/
                                            meltfptr[7] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V6*/
                                meltfptr[5] = /*_._IFELSE___V7*/ meltfptr[6];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3577:/ clear");
                                /*clear*/ /*_#IS_A__L3*/
                                meltfnum[2] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V7*/
                                meltfptr[6] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_.VLOC__V5*/
                    meltfptr[4] = /*_._IFELSE___V6*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3574:/ clear");
                    /*clear*/ /*_#IS_MIXLOC__L2*/
                    meltfnum[1] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V6*/
                    meltfptr[5] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3582:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[2])), (3), "CLASS_SEXPR");
            /*_.INST__V11*/
            meltfptr[6] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V11*/ meltfptr[6])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V11*/ meltfptr[6]), (1), (/*_.VLOC__V5*/ meltfptr[4]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXP_CONTENTS", melt_magic_discr((melt_ptr_t)(/*_.INST__V11*/ meltfptr[6])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V11*/ meltfptr[6]), (2), (/*_.CONT__V4*/ meltfptr[3]), "SEXP_CONTENTS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V11*/ meltfptr[6], "newly made instance");
        ;
        /*_.SEXPR__V10*/
        meltfptr[7] = /*_.INST__V11*/ meltfptr[6];;
        MELT_LOCATION("warmelt-base.melt:3586:/ loop");
        /*loop*/
        {
meltlabloop_ARGLOOP_6:;/*^loopbody*/

            /*^block*/
            /*anyblock*/
            {


                MELT_CHECK_SIGNAL();
                ;
                MELT_LOCATION("warmelt-base.melt:3589:/ cond");
                /*cond*/
                if (/*ifvariadic nomore*/ variad_MELT_MAKE_SEXPR_ix == variad_MELT_MAKE_SEXPR_len) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            /*^compute*/

                            /*consume variadic  !*/ variad_MELT_MAKE_SEXPR_ix += 0;;
                            MELT_LOCATION("warmelt-base.melt:3590:/ quasiblock");


                            /*^compute*/
                            /*_.ARGLOOP__V13*/
                            meltfptr[12] =  /*reallynil*/ NULL ;;

                            /*^exit*/
                            /*exit*/
                            {
                                goto meltlabexit_ARGLOOP_6;
                            }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                else
                    {
                        MELT_LOCATION("warmelt-base.melt:3589:/ cond.else");

                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:3591:/ cond");
                            /*cond*/
                            if (/*ifvariadic arg#1*/ variad_MELT_MAKE_SEXPR_ix>=0 && variad_MELT_MAKE_SEXPR_ix + 1 <= variad_MELT_MAKE_SEXPR_len && meltxargdescr_[variad_MELT_MAKE_SEXPR_ix]== MELTBPAR_CSTRING) /*then*/
                                {
                                    /*^cond.then*/
                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        /*^compute*/
                                        /*_?*/ meltfram__.loc_CSTRING__o0 =
                                            /*variadic argument stuff*/ meltxargtab_[variad_MELT_MAKE_SEXPR_ix + 0].meltbp_cstring;;
                                        /*^compute*/

                                        /*consume variadic CSTRING !*/
                                        variad_MELT_MAKE_SEXPR_ix += 1;;
                                        MELT_LOCATION("warmelt-base.melt:3592:/ quasiblock");


                                        /*_.BS__V14*/
                                        meltfptr[13] =
                                            /*full constboxing*/ /*ctype_cstring boxing*/ meltgc_new_stringdup((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_STRING)))), (/*_?*/ meltfram__.loc_CSTRING__o0));;

                                        {
                                            MELT_LOCATION("warmelt-base.melt:3594:/ locexp");
                                            meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.BS__V14*/ meltfptr[13]));
                                        }
                                        ;

                                        MELT_LOCATION("warmelt-base.melt:3592:/ clear");
                                        /*clear*/ /*_.BS__V14*/
                                        meltfptr[13] = 0 ;
                                        /*epilog*/

                                        MELT_LOCATION("warmelt-base.melt:3591:/ clear");
                                        /*clear*/ /*_?*/
                                        meltfram__.loc_CSTRING__o0 = 0 ;
                                    }
                                    ;
                                }
                            else    /*^cond.else*/
                                {

                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        MELT_LOCATION("warmelt-base.melt:3595:/ cond");
                                        /*cond*/
                                        if (/*ifvariadic arg#1*/ variad_MELT_MAKE_SEXPR_ix>=0 && variad_MELT_MAKE_SEXPR_ix + 1 <= variad_MELT_MAKE_SEXPR_len && meltxargdescr_[variad_MELT_MAKE_SEXPR_ix]== MELTBPAR_LONG) /*then*/
                                            {
                                                /*^cond.then*/
                                                /*^block*/
                                                /*anyblock*/
                                                {

                                                    /*^compute*/
                                                    /*_#NUM__L4*/ meltfnum[2] =
                                                        /*variadic argument stuff*/ meltxargtab_[variad_MELT_MAKE_SEXPR_ix + 0].meltbp_long;;
                                                    /*^compute*/

                                                    /*consume variadic LONG !*/
                                                    variad_MELT_MAKE_SEXPR_ix += 1;;
                                                    MELT_LOCATION("warmelt-base.melt:3596:/ quasiblock");


                                                    /*_.BS__V15*/
                                                    meltfptr[13] =
                                                        /*full constboxing*/ /*boxing ctype_long*/ meltgc_new_int((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_CONSTANT_INTEGER)))), (/*_#NUM__L4*/ meltfnum[2]));;

                                                    {
                                                        MELT_LOCATION("warmelt-base.melt:3598:/ locexp");
                                                        meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.BS__V15*/ meltfptr[13]));
                                                    }
                                                    ;

                                                    MELT_LOCATION("warmelt-base.melt:3596:/ clear");
                                                    /*clear*/ /*_.BS__V15*/
                                                    meltfptr[13] = 0 ;
                                                    /*epilog*/

                                                    MELT_LOCATION("warmelt-base.melt:3595:/ clear");
                                                    /*clear*/ /*_#NUM__L4*/
                                                    meltfnum[2] = 0 ;
                                                }
                                                ;
                                            }
                                        else    /*^cond.else*/
                                            {

                                                /*^block*/
                                                /*anyblock*/
                                                {

                                                    MELT_LOCATION("warmelt-base.melt:3599:/ cond");
                                                    /*cond*/
                                                    if (/*ifvariadic arg#1*/ variad_MELT_MAKE_SEXPR_ix>=0 && variad_MELT_MAKE_SEXPR_ix + 1 <= variad_MELT_MAKE_SEXPR_len && meltxargdescr_[variad_MELT_MAKE_SEXPR_ix]== MELTBPAR_PTR) /*then*/
                                                        {
                                                            /*^cond.then*/
                                                            /*^block*/
                                                            /*anyblock*/
                                                            {

                                                                /*^compute*/
                                                                /*_.V__V16*/ meltfptr[13] =
                                                                    /*variadic argument value*/ ((meltxargtab_[variad_MELT_MAKE_SEXPR_ix + 0].meltbp_aptr) ? (*(meltxargtab_[variad_MELT_MAKE_SEXPR_ix + 0].meltbp_aptr)) : NULL);;
                                                                /*^compute*/

                                                                /*consume variadic Value !*/
                                                                variad_MELT_MAKE_SEXPR_ix += 1;;

                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                /*_#NULL__L5*/
                                                                meltfnum[1] =
                                                                    (/*null*/(/*_.V__V16*/ meltfptr[13]) == NULL);;
                                                                MELT_LOCATION("warmelt-base.melt:3600:/ cond");
                                                                /*cond*/
                                                                if (/*_#NULL__L5*/ meltfnum[1]) /*then*/
                                                                    {
                                                                        /*^cond.then*/
                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {




                                                                            {
                                                                                MELT_LOCATION("warmelt-base.melt:3601:/ locexp");
                                                                                meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.V__V16*/ meltfptr[13]));
                                                                            }
                                                                            ;
                                                                            /*clear*/ /*_._IFELSE___V17*/
                                                                            meltfptr[16] = 0 ;
                                                                            /*epilog*/
                                                                        }
                                                                        ;
                                                                    }
                                                                else
                                                                    {
                                                                        MELT_LOCATION("warmelt-base.melt:3600:/ cond.else");

                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {


                                                                            MELT_CHECK_SIGNAL();
                                                                            ;
                                                                            /*_#IS_OBJECT__L6*/
                                                                            meltfnum[2] =
                                                                                (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_OBJECT);;
                                                                            MELT_LOCATION("warmelt-base.melt:3602:/ cond");
                                                                            /*cond*/
                                                                            if (/*_#IS_OBJECT__L6*/ meltfnum[2]) /*then*/
                                                                                {
                                                                                    /*^cond.then*/
                                                                                    /*^block*/
                                                                                    /*anyblock*/
                                                                                    {




                                                                                        {
                                                                                            MELT_LOCATION("warmelt-base.melt:3603:/ locexp");
                                                                                            meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.V__V16*/ meltfptr[13]));
                                                                                        }
                                                                                        ;
                                                                                        /*clear*/ /*_._IFELSE___V18*/
                                                                                        meltfptr[17] = 0 ;
                                                                                        /*epilog*/
                                                                                    }
                                                                                    ;
                                                                                }
                                                                            else
                                                                                {
                                                                                    MELT_LOCATION("warmelt-base.melt:3602:/ cond.else");

                                                                                    /*^block*/
                                                                                    /*anyblock*/
                                                                                    {


                                                                                        MELT_CHECK_SIGNAL();
                                                                                        ;
                                                                                        /*_#IS_INTEGERBOX__L7*/
                                                                                        meltfnum[6] =
                                                                                            (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_INT);;
                                                                                        MELT_LOCATION("warmelt-base.melt:3604:/ cond");
                                                                                        /*cond*/
                                                                                        if (/*_#IS_INTEGERBOX__L7*/ meltfnum[6]) /*then*/
                                                                                            {
                                                                                                /*^cond.then*/
                                                                                                /*^block*/
                                                                                                /*anyblock*/
                                                                                                {




                                                                                                    {
                                                                                                        MELT_LOCATION("warmelt-base.melt:3605:/ locexp");
                                                                                                        meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.V__V16*/ meltfptr[13]));
                                                                                                    }
                                                                                                    ;
                                                                                                    /*clear*/ /*_._IFELSE___V19*/
                                                                                                    meltfptr[18] = 0 ;
                                                                                                    /*epilog*/
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                        else
                                                                                            {
                                                                                                MELT_LOCATION("warmelt-base.melt:3604:/ cond.else");

                                                                                                /*^block*/
                                                                                                /*anyblock*/
                                                                                                {


                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                    ;
                                                                                                    /*_#IS_STRING__L8*/
                                                                                                    meltfnum[7] =
                                                                                                        (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_STRING);;
                                                                                                    MELT_LOCATION("warmelt-base.melt:3606:/ cond");
                                                                                                    /*cond*/
                                                                                                    if (/*_#IS_STRING__L8*/ meltfnum[7]) /*then*/
                                                                                                        {
                                                                                                            /*^cond.then*/
                                                                                                            /*^block*/
                                                                                                            /*anyblock*/
                                                                                                            {




                                                                                                                {
                                                                                                                    MELT_LOCATION("warmelt-base.melt:3607:/ locexp");
                                                                                                                    meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.V__V16*/ meltfptr[13]));
                                                                                                                }
                                                                                                                ;
                                                                                                                /*clear*/ /*_._IFELSE___V20*/
                                                                                                                meltfptr[19] = 0 ;
                                                                                                                /*epilog*/
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                    else
                                                                                                        {
                                                                                                            MELT_LOCATION("warmelt-base.melt:3606:/ cond.else");

                                                                                                            /*^block*/
                                                                                                            /*anyblock*/
                                                                                                            {


                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                ;
                                                                                                                /*_#IS_MULTIPLE__L9*/
                                                                                                                meltfnum[8] =
                                                                                                                    (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_MULTIPLE);;
                                                                                                                MELT_LOCATION("warmelt-base.melt:3608:/ cond");
                                                                                                                /*cond*/
                                                                                                                if (/*_#IS_MULTIPLE__L9*/ meltfnum[8]) /*then*/
                                                                                                                    {
                                                                                                                        /*^cond.then*/
                                                                                                                        /*^block*/
                                                                                                                        /*anyblock*/
                                                                                                                        {

                                                                                                                            /*citerblock FOREACH_IN_MULTIPLE*/
                                                                                                                            {
                                                                                                                                /* start foreach_in_multiple meltcit1__EACHTUP */
                                                                                                                                long  meltcit1__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.V__V16*/ meltfptr[13]);
                                                                                                                                for (/*_#IX__L10*/ meltfnum[9] = 0;
                                                                                                                                                   (/*_#IX__L10*/ meltfnum[9] >= 0) && (/*_#IX__L10*/ meltfnum[9] <  meltcit1__EACHTUP_ln);
                                                                                                                                                   /*_#IX__L10*/ meltfnum[9]++)
                                                                                                                                    {
                                                                                                                                        /*_.COMP__V22*/ meltfptr[21] = melt_multiple_nth((melt_ptr_t)(/*_.V__V16*/ meltfptr[13]),  /*_#IX__L10*/ meltfnum[9]);




                                                                                                                                        {
                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3612:/ locexp");
                                                                                                                                            meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.COMP__V22*/ meltfptr[21]));
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                        if (/*_#IX__L10*/ meltfnum[9]<0) break;
                                                                                                                                    } /* end  foreach_in_multiple meltcit1__EACHTUP */

                                                                                                                                /*citerepilog*/

                                                                                                                                MELT_LOCATION("warmelt-base.melt:3609:/ clear");
                                                                                                                                /*clear*/ /*_.COMP__V22*/
                                                                                                                                meltfptr[21] = 0 ;
                                                                                                                                /*^clear*/
                                                                                                                                /*clear*/ /*_#IX__L10*/
                                                                                                                                meltfnum[9] = 0 ;
                                                                                                                            } /*endciterblock FOREACH_IN_MULTIPLE*/
                                                                                                                            ;
                                                                                                                            /*epilog*/
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                else
                                                                                                                    {
                                                                                                                        MELT_LOCATION("warmelt-base.melt:3608:/ cond.else");

                                                                                                                        /*^block*/
                                                                                                                        /*anyblock*/
                                                                                                                        {


                                                                                                                            MELT_CHECK_SIGNAL();
                                                                                                                            ;
                                                                                                                            /*_#IS_LIST__L11*/
                                                                                                                            meltfnum[10] =
                                                                                                                                (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_LIST);;
                                                                                                                            MELT_LOCATION("warmelt-base.melt:3613:/ cond");
                                                                                                                            /*cond*/
                                                                                                                            if (/*_#IS_LIST__L11*/ meltfnum[10]) /*then*/
                                                                                                                                {
                                                                                                                                    /*^cond.then*/
                                                                                                                                    /*^block*/
                                                                                                                                    /*anyblock*/
                                                                                                                                    {

                                                                                                                                        /*citerblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                                                                                                                        {
                                                                                                                                            /* start foreach_pair_component_in_list meltcit2__EACHLIST */
                                                                                                                                            for (/*_.CURPAIR__V24*/ meltfptr[23] = melt_list_first( (melt_ptr_t)/*_.V__V16*/ meltfptr[13]);
                                                                                                                                                                    melt_magic_discr((melt_ptr_t) /*_.CURPAIR__V24*/ meltfptr[23]) == MELTOBMAG_PAIR;
                                                                                                                                                                    /*_.CURPAIR__V24*/ meltfptr[23] = melt_pair_tail((melt_ptr_t) /*_.CURPAIR__V24*/ meltfptr[23]))
                                                                                                                                                {
                                                                                                                                                    /*_.CURCOMP__V25*/ meltfptr[24] = melt_pair_head((melt_ptr_t) /*_.CURPAIR__V24*/ meltfptr[23]);



                                                                                                                                                    {
                                                                                                                                                        MELT_LOCATION("warmelt-base.melt:3617:/ locexp");
                                                                                                                                                        meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.CURCOMP__V25*/ meltfptr[24]));
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                } /* end foreach_pair_component_in_list meltcit2__EACHLIST */
                                                                                                                                            /*_.CURPAIR__V24*/ meltfptr[23] = NULL;
                                                                                                                                            /*_.CURCOMP__V25*/
                                                                                                                                            meltfptr[24] = NULL;


                                                                                                                                            /*citerepilog*/

                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3614:/ clear");
                                                                                                                                            /*clear*/ /*_.CURPAIR__V24*/
                                                                                                                                            meltfptr[23] = 0 ;
                                                                                                                                            /*^clear*/
                                                                                                                                            /*clear*/ /*_.CURCOMP__V25*/
                                                                                                                                            meltfptr[24] = 0 ;
                                                                                                                                        } /*endciterblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                                                                                                                        ;
                                                                                                                                        /*epilog*/
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                            else
                                                                                                                                {
                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3613:/ cond.else");

                                                                                                                                    /*^block*/
                                                                                                                                    /*anyblock*/
                                                                                                                                    {


                                                                                                                                        MELT_CHECK_SIGNAL();
                                                                                                                                        ;
                                                                                                                                        /*_#IS_MIXLOC__L12*/
                                                                                                                                        meltfnum[11] =
                                                                                                                                            (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_MIXLOC);;
                                                                                                                                        MELT_LOCATION("warmelt-base.melt:3619:/ cond");
                                                                                                                                        /*cond*/
                                                                                                                                        if (/*_#IS_MIXLOC__L12*/ meltfnum[11]) /*then*/
                                                                                                                                            {
                                                                                                                                                /*^cond.then*/
                                                                                                                                                /*^block*/
                                                                                                                                                /*anyblock*/
                                                                                                                                                {

                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3620:/ quasiblock");


                                                                                                                                                    /*_#LOCLINE__L13*/
                                                                                                                                                    meltfnum[12] =
                                                                                                                                                        (LOCATION_LINE(melt_location_mixloc((melt_ptr_t)/*_.V__V16*/ meltfptr[13])));;
                                                                                                                                                    /*^compute*/
                                                                                                                                                    /*_?*/
                                                                                                                                                    meltfram__.loc_CSTRING__o1 =
                                                                                                                                                        (LOCATION_FILE(melt_location_mixloc((melt_ptr_t)/*_.V__V16*/ meltfptr[13])));;

                                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                                    ;

                                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                                    ;
                                                                                                                                                    /*^compute*/
                                                                                                                                                    /*_#gtI__L14*/
                                                                                                                                                    meltfnum[13] =
                                                                                                                                                        ((/*_#LOCLINE__L13*/ meltfnum[12]) > (0));;
                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3623:/ cond");
                                                                                                                                                    /*cond*/
                                                                                                                                                    if (/*_#gtI__L14*/ meltfnum[13]) /*then*/
                                                                                                                                                        {
                                                                                                                                                            /*^cond.then*/
                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {

                                                                                                                                                                /*_#CSTRING_NON_EMPTY__L16*/ meltfnum[15] =
                                                                                                                                                                    (((/*_?*/ meltfram__.loc_CSTRING__o1) != NULL) && ((const char*)(/*_?*/ meltfram__.loc_CSTRING__o1))[0] != (char)0);;
                                                                                                                                                                /*^compute*/
                                                                                                                                                                /*_#_IF___L15*/
                                                                                                                                                                meltfnum[14] = /*_#CSTRING_NON_EMPTY__L16*/ meltfnum[15];;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3623:/ clear");
                                                                                                                                                                /*clear*/ /*_#CSTRING_NON_EMPTY__L16*/
                                                                                                                                                                meltfnum[15] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    else    /*^cond.else*/
                                                                                                                                                        {

                                                                                                                                                            /*_#_IF___L15*/ meltfnum[14] = 0;;
                                                                                                                                                        }
                                                                                                                                                    ;
                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3623:/ cond");
                                                                                                                                                    /*cond*/
                                                                                                                                                    if (/*_#_IF___L15*/ meltfnum[14]) /*then*/
                                                                                                                                                        {
                                                                                                                                                            /*^cond.then*/
                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {


                                                                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                                                                ;
                                                                                                                                                                /*_.BOX__V27*/
                                                                                                                                                                meltfptr[26] =
                                                                                                                                                                    /*full constboxing*/ /*ctype_cstring boxing*/ meltgc_new_stringdup((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_STRING)))), (/*_?*/ meltfram__.loc_CSTRING__o1));;
                                                                                                                                                                /*^compute*/
                                                                                                                                                                /*_.BOX__V28*/
                                                                                                                                                                meltfptr[27] =
                                                                                                                                                                    /*full constboxing*/ /*boxing ctype_long*/ meltgc_new_int((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_CONSTANT_INTEGER)))), (/*_#LOCLINE__L13*/ meltfnum[12]));;
                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3627:/ blockmultialloc");
                                                                                                                                                                /*multiallocblock*/
                                                                                                                                                                {
                                                                                                                                                                    struct meltletrec_1_st
                                                                                                                                                                    {
                                                                                                                                                                        struct meltpair_st rpair_0___PAIROFLIST_x1;
                                                                                                                                                                        struct meltpair_st rpair_1___PAIROFLIST_x2;
                                                                                                                                                                        struct meltpair_st rpair_2___PAIROFLIST_x3;
                                                                                                                                                                        struct meltlist_st rlist_3__LIST_;
                                                                                                                                                                        long meltletrec_1_endgap;
                                                                                                                                                                    } *meltletrec_1_ptr = 0;
                                                                                                                                                                    meltletrec_1_ptr = (struct meltletrec_1_st *) meltgc_allocate (sizeof (struct meltletrec_1_st), 0);
                                                                                                                                                                    /*^blockmultialloc.initfill*/
                                                                                                                                                                    /*inipair rpair_0___PAIROFLIST_x1*/
                                                                                                                                                                    /*_._PAIROFLIST__V30*/
                                                                                                                                                                    meltfptr[29] = (melt_ptr_t) &meltletrec_1_ptr->rpair_0___PAIROFLIST_x1;
                                                                                                                                                                    meltletrec_1_ptr->rpair_0___PAIROFLIST_x1.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

                                                                                                                                                                    /*inipair rpair_1___PAIROFLIST_x2*/
                                                                                                                                                                    /*_._PAIROFLIST__V31*/
                                                                                                                                                                    meltfptr[30] = (melt_ptr_t) &meltletrec_1_ptr->rpair_1___PAIROFLIST_x2;
                                                                                                                                                                    meltletrec_1_ptr->rpair_1___PAIROFLIST_x2.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

                                                                                                                                                                    /*inipair rpair_2___PAIROFLIST_x3*/
                                                                                                                                                                    /*_._PAIROFLIST__V32*/
                                                                                                                                                                    meltfptr[31] = (melt_ptr_t) &meltletrec_1_ptr->rpair_2___PAIROFLIST_x3;
                                                                                                                                                                    meltletrec_1_ptr->rpair_2___PAIROFLIST_x3.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

                                                                                                                                                                    /*inilist rlist_3__LIST_*/
                                                                                                                                                                    /*_.LIST___V33*/
                                                                                                                                                                    meltfptr[32] = (melt_ptr_t) &meltletrec_1_ptr->rlist_3__LIST_;
                                                                                                                                                                    meltletrec_1_ptr->rlist_3__LIST_.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_LIST))));



                                                                                                                                                                    /*^putpairhead*/
                                                                                                                                                                    /*putpairhead*/
                                                                                                                                                                    melt_assertmsg("putpairhead /1 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V30*/ meltfptr[29]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V30*/ meltfptr[29]))->hd = (melt_ptr_t) ((/*!konst_3_HOOK_MELT_MAKE_LOCATION*/ meltfrout->tabval[3]));
                                                                                                                                                                    ;
                                                                                                                                                                    /*^putpairtail*/
                                                                                                                                                                    /*putpairtail*/
                                                                                                                                                                    melt_assertmsg("putpairtail /72ef7c5 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V30*/ meltfptr[29]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V30*/ meltfptr[29]))->tl = (meltpair_ptr_t) (/*_._PAIROFLIST__V31*/ meltfptr[30]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_._PAIROFLIST__V30*/ meltfptr[29]);
                                                                                                                                                                    ;
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3628:/ putpairhead");
                                                                                                                                                                    /*putpairhead*/
                                                                                                                                                                    melt_assertmsg("putpairhead /2 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V31*/ meltfptr[30]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V31*/ meltfptr[30]))->hd = (melt_ptr_t) (/*_.BOX__V27*/ meltfptr[26]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^putpairtail*/
                                                                                                                                                                    /*putpairtail*/
                                                                                                                                                                    melt_assertmsg("putpairtail /1a290fcf checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V31*/ meltfptr[30]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V31*/ meltfptr[30]))->tl = (meltpair_ptr_t) (/*_._PAIROFLIST__V32*/ meltfptr[31]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_._PAIROFLIST__V31*/ meltfptr[30]);
                                                                                                                                                                    ;
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3629:/ putpairhead");
                                                                                                                                                                    /*putpairhead*/
                                                                                                                                                                    melt_assertmsg("putpairhead /3 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V32*/ meltfptr[31]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V32*/ meltfptr[31]))->hd = (melt_ptr_t) (/*_.BOX__V28*/ meltfptr[27]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_._PAIROFLIST__V32*/ meltfptr[31]);
                                                                                                                                                                    ;
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3627:/ putlist");
                                                                                                                                                                    /*putlist*/
                                                                                                                                                                    melt_assertmsg("putlist checklist", melt_magic_discr((melt_ptr_t)(/*_.LIST___V33*/ meltfptr[32]))== MELTOBMAG_LIST);
                                                                                                                                                                    ((meltlist_ptr_t)(/*_.LIST___V33*/ meltfptr[32]))->first = (meltpair_ptr_t) (/*_._PAIROFLIST__V30*/ meltfptr[29]);
                                                                                                                                                                    ((meltlist_ptr_t)(/*_.LIST___V33*/ meltfptr[32]))->last = (meltpair_ptr_t) (/*_._PAIROFLIST__V32*/ meltfptr[31]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_.LIST___V33*/ meltfptr[32]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*_.LIST___V29*/
                                                                                                                                                                    meltfptr[28] = /*_.LIST___V33*/ meltfptr[32];;
                                                                                                                                                                    /*epilog*/

                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3627:/ clear");
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V30*/
                                                                                                                                                                    meltfptr[29] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V31*/
                                                                                                                                                                    meltfptr[30] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V32*/
                                                                                                                                                                    meltfptr[31] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_.LIST___V33*/
                                                                                                                                                                    meltfptr[32] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V30*/
                                                                                                                                                                    meltfptr[29] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V31*/
                                                                                                                                                                    meltfptr[30] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V32*/
                                                                                                                                                                    meltfptr[31] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_.LIST___V33*/
                                                                                                                                                                    meltfptr[32] = 0 ;
                                                                                                                                                                } /*end multiallocblock*/
                                                                                                                                                                ;
                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3625:/ quasiblock");


                                                                                                                                                                /*^rawallocobj*/
                                                                                                                                                                /*rawallocobj*/
                                                                                                                                                                {
                                                                                                                                                                    melt_ptr_t newobj = 0;
                                                                                                                                                                    melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[2])), (3), "CLASS_SEXPR");
                                                                                                                                                                    /*_.INST__V35*/
                                                                                                                                                                    meltfptr[30] =
                                                                                                                                                                        newobj;
                                                                                                                                                                };
                                                                                                                                                                ;
                                                                                                                                                                /*^putslot*/
                                                                                                                                                                /*putslot*/
                                                                                                                                                                melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V35*/ meltfptr[30])) == MELTOBMAG_OBJECT);
                                                                                                                                                                melt_putfield_object((/*_.INST__V35*/ meltfptr[30]), (1), (/*_.LOC__V2*/ meltfptr[1]), "LOCA_LOCATION");
                                                                                                                                                                ;
                                                                                                                                                                /*^putslot*/
                                                                                                                                                                /*putslot*/
                                                                                                                                                                melt_assertmsg("checkobj putslot  _ @SEXP_CONTENTS", melt_magic_discr((melt_ptr_t)(/*_.INST__V35*/ meltfptr[30])) == MELTOBMAG_OBJECT);
                                                                                                                                                                melt_putfield_object((/*_.INST__V35*/ meltfptr[30]), (2), (/*_.LIST___V29*/ meltfptr[28]), "SEXP_CONTENTS");
                                                                                                                                                                ;
                                                                                                                                                                /*^touchobj*/

                                                                                                                                                                melt_dbgtrace_written_object (/*_.INST__V35*/ meltfptr[30], "newly made instance");
                                                                                                                                                                ;
                                                                                                                                                                /*_.INST___V34*/
                                                                                                                                                                meltfptr[29] = /*_.INST__V35*/ meltfptr[30];;



                                                                                                                                                                {
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3625:/ locexp");
                                                                                                                                                                    meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.INST___V34*/ meltfptr[29]));
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                                /*clear*/ /*_._IFELSE___V26*/
                                                                                                                                                                meltfptr[25] = 0 ;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3623:/ clear");
                                                                                                                                                                /*clear*/ /*_.BOX__V27*/
                                                                                                                                                                meltfptr[26] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.BOX__V28*/
                                                                                                                                                                meltfptr[27] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.LIST___V29*/
                                                                                                                                                                meltfptr[28] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.INST___V34*/
                                                                                                                                                                meltfptr[29] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    else    /*^cond.else*/
                                                                                                                                                        {

                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {




                                                                                                                                                                {
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3630:/ locexp");
                                                                                                                                                                    meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)((/*nil*/NULL)));
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                                /*clear*/ /*_._IFELSE___V26*/
                                                                                                                                                                meltfptr[25] = 0 ;
                                                                                                                                                                /*epilog*/
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    ;

                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3620:/ clear");
                                                                                                                                                    /*clear*/ /*_#LOCLINE__L13*/
                                                                                                                                                    meltfnum[12] = 0 ;
                                                                                                                                                    /*^clear*/
                                                                                                                                                    /*clear*/ /*_?*/
                                                                                                                                                    meltfram__.loc_CSTRING__o1 = 0 ;
                                                                                                                                                    /*^clear*/
                                                                                                                                                    /*clear*/ /*_#gtI__L14*/
                                                                                                                                                    meltfnum[13] = 0 ;
                                                                                                                                                    /*^clear*/
                                                                                                                                                    /*clear*/ /*_#_IF___L15*/
                                                                                                                                                    meltfnum[14] = 0 ;
                                                                                                                                                    /*epilog*/
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                        else
                                                                                                                                            {
                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3619:/ cond.else");

                                                                                                                                                /*^block*/
                                                                                                                                                /*anyblock*/
                                                                                                                                                {


                                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                                    ;

                                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                                    ;
                                                                                                                                                    /*_#IS_MIXINT__L17*/
                                                                                                                                                    meltfnum[15] =
                                                                                                                                                        (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_MIXINT);;
                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3632:/ cond");
                                                                                                                                                    /*cond*/
                                                                                                                                                    if (/*_#IS_MIXINT__L17*/ meltfnum[15]) /*then*/
                                                                                                                                                        {
                                                                                                                                                            /*^cond.then*/
                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {

                                                                                                                                                                /*_.MIXINT_VAL__V36*/ meltfptr[31] =
                                                                                                                                                                    (melt_val_mixint((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])));;
                                                                                                                                                                /*^compute*/
                                                                                                                                                                /*_#IS_STRING__L19*/
                                                                                                                                                                meltfnum[13] =
                                                                                                                                                                    (melt_magic_discr((melt_ptr_t)(/*_.MIXINT_VAL__V36*/ meltfptr[31])) == MELTOBMAG_STRING);;
                                                                                                                                                                /*^compute*/
                                                                                                                                                                /*_#_IF___L18*/
                                                                                                                                                                meltfnum[12] = /*_#IS_STRING__L19*/ meltfnum[13];;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3632:/ clear");
                                                                                                                                                                /*clear*/ /*_.MIXINT_VAL__V36*/
                                                                                                                                                                meltfptr[31] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_#IS_STRING__L19*/
                                                                                                                                                                meltfnum[13] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    else    /*^cond.else*/
                                                                                                                                                        {

                                                                                                                                                            /*_#_IF___L18*/ meltfnum[12] = 0;;
                                                                                                                                                        }
                                                                                                                                                    ;
                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3632:/ cond");
                                                                                                                                                    /*cond*/
                                                                                                                                                    if (/*_#_IF___L18*/ meltfnum[12]) /*then*/
                                                                                                                                                        {
                                                                                                                                                            /*^cond.then*/
                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3635:/ quasiblock");


                                                                                                                                                                /*_#LOCLINE__L20*/
                                                                                                                                                                meltfnum[14] =
                                                                                                                                                                    (melt_get_int((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])));;

                                                                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                                                                ;
                                                                                                                                                                /*^compute*/
                                                                                                                                                                /*_.MIXINT_VAL__V38*/
                                                                                                                                                                meltfptr[26] =
                                                                                                                                                                    (melt_val_mixint((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])));;
                                                                                                                                                                /*^compute*/
                                                                                                                                                                /*_.BOX__V39*/
                                                                                                                                                                meltfptr[27] =
                                                                                                                                                                    /*full constboxing*/ /*boxing ctype_long*/ meltgc_new_int((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_CONSTANT_INTEGER)))), (/*_#LOCLINE__L20*/ meltfnum[14]));;
                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3639:/ blockmultialloc");
                                                                                                                                                                /*multiallocblock*/
                                                                                                                                                                {
                                                                                                                                                                    struct meltletrec_2_st
                                                                                                                                                                    {
                                                                                                                                                                        struct meltpair_st rpair_0___PAIROFLIST_x4;
                                                                                                                                                                        struct meltpair_st rpair_1___PAIROFLIST_x5;
                                                                                                                                                                        struct meltpair_st rpair_2___PAIROFLIST_x6;
                                                                                                                                                                        struct meltlist_st rlist_3__LIST_;
                                                                                                                                                                        long meltletrec_2_endgap;
                                                                                                                                                                    } *meltletrec_2_ptr = 0;
                                                                                                                                                                    meltletrec_2_ptr = (struct meltletrec_2_st *) meltgc_allocate (sizeof (struct meltletrec_2_st), 0);
                                                                                                                                                                    /*^blockmultialloc.initfill*/
                                                                                                                                                                    /*inipair rpair_0___PAIROFLIST_x4*/
                                                                                                                                                                    /*_._PAIROFLIST__V41*/
                                                                                                                                                                    meltfptr[29] = (melt_ptr_t) &meltletrec_2_ptr->rpair_0___PAIROFLIST_x4;
                                                                                                                                                                    meltletrec_2_ptr->rpair_0___PAIROFLIST_x4.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

                                                                                                                                                                    /*inipair rpair_1___PAIROFLIST_x5*/
                                                                                                                                                                    /*_._PAIROFLIST__V42*/
                                                                                                                                                                    meltfptr[31] = (melt_ptr_t) &meltletrec_2_ptr->rpair_1___PAIROFLIST_x5;
                                                                                                                                                                    meltletrec_2_ptr->rpair_1___PAIROFLIST_x5.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

                                                                                                                                                                    /*inipair rpair_2___PAIROFLIST_x6*/
                                                                                                                                                                    /*_._PAIROFLIST__V43*/
                                                                                                                                                                    meltfptr[42] = (melt_ptr_t) &meltletrec_2_ptr->rpair_2___PAIROFLIST_x6;
                                                                                                                                                                    meltletrec_2_ptr->rpair_2___PAIROFLIST_x6.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

                                                                                                                                                                    /*inilist rlist_3__LIST_*/
                                                                                                                                                                    /*_.LIST___V44*/
                                                                                                                                                                    meltfptr[43] = (melt_ptr_t) &meltletrec_2_ptr->rlist_3__LIST_;
                                                                                                                                                                    meltletrec_2_ptr->rlist_3__LIST_.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_LIST))));



                                                                                                                                                                    /*^putpairhead*/
                                                                                                                                                                    /*putpairhead*/
                                                                                                                                                                    melt_assertmsg("putpairhead /4 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V41*/ meltfptr[29]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V41*/ meltfptr[29]))->hd = (melt_ptr_t) ((/*!konst_3_HOOK_MELT_MAKE_LOCATION*/ meltfrout->tabval[3]));
                                                                                                                                                                    ;
                                                                                                                                                                    /*^putpairtail*/
                                                                                                                                                                    /*putpairtail*/
                                                                                                                                                                    melt_assertmsg("putpairtail /321f1323 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V41*/ meltfptr[29]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V41*/ meltfptr[29]))->tl = (meltpair_ptr_t) (/*_._PAIROFLIST__V42*/ meltfptr[31]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_._PAIROFLIST__V41*/ meltfptr[29]);
                                                                                                                                                                    ;
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3640:/ putpairhead");
                                                                                                                                                                    /*putpairhead*/
                                                                                                                                                                    melt_assertmsg("putpairhead /5 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V42*/ meltfptr[31]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V42*/ meltfptr[31]))->hd = (melt_ptr_t) (/*_.MIXINT_VAL__V38*/ meltfptr[26]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^putpairtail*/
                                                                                                                                                                    /*putpairtail*/
                                                                                                                                                                    melt_assertmsg("putpairtail /35bfcf9 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V42*/ meltfptr[31]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V42*/ meltfptr[31]))->tl = (meltpair_ptr_t) (/*_._PAIROFLIST__V43*/ meltfptr[42]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_._PAIROFLIST__V42*/ meltfptr[31]);
                                                                                                                                                                    ;
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3641:/ putpairhead");
                                                                                                                                                                    /*putpairhead*/
                                                                                                                                                                    melt_assertmsg("putpairhead /6 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V43*/ meltfptr[42]))== MELTOBMAG_PAIR);
                                                                                                                                                                    ((meltpair_ptr_t)(/*_._PAIROFLIST__V43*/ meltfptr[42]))->hd = (melt_ptr_t) (/*_.BOX__V39*/ meltfptr[27]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_._PAIROFLIST__V43*/ meltfptr[42]);
                                                                                                                                                                    ;
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3639:/ putlist");
                                                                                                                                                                    /*putlist*/
                                                                                                                                                                    melt_assertmsg("putlist checklist", melt_magic_discr((melt_ptr_t)(/*_.LIST___V44*/ meltfptr[43]))== MELTOBMAG_LIST);
                                                                                                                                                                    ((meltlist_ptr_t)(/*_.LIST___V44*/ meltfptr[43]))->first = (meltpair_ptr_t) (/*_._PAIROFLIST__V41*/ meltfptr[29]);
                                                                                                                                                                    ((meltlist_ptr_t)(/*_.LIST___V44*/ meltfptr[43]))->last = (meltpair_ptr_t) (/*_._PAIROFLIST__V43*/ meltfptr[42]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*^touch*/
                                                                                                                                                                    meltgc_touch(/*_.LIST___V44*/ meltfptr[43]);
                                                                                                                                                                    ;
                                                                                                                                                                    /*_.LIST___V40*/
                                                                                                                                                                    meltfptr[28] = /*_.LIST___V44*/ meltfptr[43];;
                                                                                                                                                                    /*epilog*/

                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3639:/ clear");
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V41*/
                                                                                                                                                                    meltfptr[29] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V42*/
                                                                                                                                                                    meltfptr[31] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V43*/
                                                                                                                                                                    meltfptr[42] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_.LIST___V44*/
                                                                                                                                                                    meltfptr[43] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V41*/
                                                                                                                                                                    meltfptr[29] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V42*/
                                                                                                                                                                    meltfptr[31] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_._PAIROFLIST__V43*/
                                                                                                                                                                    meltfptr[42] = 0 ;
                                                                                                                                                                    /*^clear*/
                                                                                                                                                                    /*clear*/ /*_.LIST___V44*/
                                                                                                                                                                    meltfptr[43] = 0 ;
                                                                                                                                                                } /*end multiallocblock*/
                                                                                                                                                                ;
                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3637:/ quasiblock");


                                                                                                                                                                /*^rawallocobj*/
                                                                                                                                                                /*rawallocobj*/
                                                                                                                                                                {
                                                                                                                                                                    melt_ptr_t newobj = 0;
                                                                                                                                                                    melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[2])), (3), "CLASS_SEXPR");
                                                                                                                                                                    /*_.INST__V46*/
                                                                                                                                                                    meltfptr[31] =
                                                                                                                                                                        newobj;
                                                                                                                                                                };
                                                                                                                                                                ;
                                                                                                                                                                /*^putslot*/
                                                                                                                                                                /*putslot*/
                                                                                                                                                                melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V46*/ meltfptr[31])) == MELTOBMAG_OBJECT);
                                                                                                                                                                melt_putfield_object((/*_.INST__V46*/ meltfptr[31]), (1), (/*_.LOC__V2*/ meltfptr[1]), "LOCA_LOCATION");
                                                                                                                                                                ;
                                                                                                                                                                /*^putslot*/
                                                                                                                                                                /*putslot*/
                                                                                                                                                                melt_assertmsg("checkobj putslot  _ @SEXP_CONTENTS", melt_magic_discr((melt_ptr_t)(/*_.INST__V46*/ meltfptr[31])) == MELTOBMAG_OBJECT);
                                                                                                                                                                melt_putfield_object((/*_.INST__V46*/ meltfptr[31]), (2), (/*_.LIST___V40*/ meltfptr[28]), "SEXP_CONTENTS");
                                                                                                                                                                ;
                                                                                                                                                                /*^touchobj*/

                                                                                                                                                                melt_dbgtrace_written_object (/*_.INST__V46*/ meltfptr[31], "newly made instance");
                                                                                                                                                                ;
                                                                                                                                                                /*_.INST___V45*/
                                                                                                                                                                meltfptr[29] = /*_.INST__V46*/ meltfptr[31];;

                                                                                                                                                                {
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3637:/ locexp");
                                                                                                                                                                    meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.INST___V45*/ meltfptr[29]));
                                                                                                                                                                }
                                                                                                                                                                ;



                                                                                                                                                                {
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3642:/ locexp");
                                                                                                                                                                    meltgc_append_list((melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (melt_ptr_t)((/*nil*/NULL)));
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                                /*clear*/ /*_._IFELSE___V37*/
                                                                                                                                                                meltfptr[32] = 0 ;

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3635:/ clear");
                                                                                                                                                                /*clear*/ /*_#LOCLINE__L20*/
                                                                                                                                                                meltfnum[14] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.MIXINT_VAL__V38*/
                                                                                                                                                                meltfptr[26] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.BOX__V39*/
                                                                                                                                                                meltfptr[27] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.LIST___V40*/
                                                                                                                                                                meltfptr[28] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_.INST___V45*/
                                                                                                                                                                meltfptr[29] = 0 ;
                                                                                                                                                                /*epilog*/
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    else
                                                                                                                                                        {
                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3632:/ cond.else");

                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {


                                                                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                                                                ;
                                                                                                                                                                /*_#IS_CLOSURE__L21*/
                                                                                                                                                                meltfnum[13] =
                                                                                                                                                                    (melt_magic_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13])) == MELTOBMAG_CLOSURE);;
                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3644:/ cond");
                                                                                                                                                                /*cond*/
                                                                                                                                                                if (/*_#IS_CLOSURE__L21*/ meltfnum[13]) /*then*/
                                                                                                                                                                    {
                                                                                                                                                                        /*^cond.then*/
                                                                                                                                                                        /*^block*/
                                                                                                                                                                        /*anyblock*/
                                                                                                                                                                        {


                                                                                                                                                                            MELT_CHECK_SIGNAL();
                                                                                                                                                                            ;
                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3645:/ apply");
                                                                                                                                                                            /*apply*/
                                                                                                                                                                            {
                                                                                                                                                                                /*_.V__V48*/ meltfptr[43] =  melt_apply ((meltclosure_ptr_t)(/*_.V__V16*/ meltfptr[13]), (melt_ptr_t)(/*_.CONT__V4*/ meltfptr[3]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                            /*_._IFELSE___V47*/
                                                                                                                                                                            meltfptr[42] = /*_.V__V48*/ meltfptr[43];;
                                                                                                                                                                            /*epilog*/

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3644:/ clear");
                                                                                                                                                                            /*clear*/ /*_.V__V48*/
                                                                                                                                                                            meltfptr[43] = 0 ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                else    /*^cond.else*/
                                                                                                                                                                    {

                                                                                                                                                                        /*^block*/
                                                                                                                                                                        /*anyblock*/
                                                                                                                                                                        {

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3647:/ quasiblock");


                                                                                                                                                                            /*_.DISCRIM__V50*/
                                                                                                                                                                            meltfptr[27] =
                                                                                                                                                                                ((melt_ptr_t) (melt_discr((melt_ptr_t)(/*_.V__V16*/ meltfptr[13]))));;
                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3647:/ cond");
                                                                                                                                                                            /*cond*/
                                                                                                                                                                            if (
                                                                                                                                                                                /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.DISCRIM__V50*/ meltfptr[27]),
                                                                                                                                                                                                              (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])))
                                                                                                                                                                            ) /*then*/
                                                                                                                                                                                {
                                                                                                                                                                                    /*^cond.then*/
                                                                                                                                                                                    /*^getslot*/
                                                                                                                                                                                    {
                                                                                                                                                                                        melt_ptr_t slot=NULL, obj=NULL;
                                                                                                                                                                                        obj = (melt_ptr_t)(/*_.DISCRIM__V50*/ meltfptr[27]) /*=obj*/;
                                                                                                                                                                                        melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                                                                                                                                                        /*_.DISCRNAME__V51*/
                                                                                                                                                                                        meltfptr[28] = slot;
                                                                                                                                                                                    };
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                            else    /*^cond.else*/
                                                                                                                                                                                {

                                                                                                                                                                                    /*_.DISCRNAME__V51*/ meltfptr[28] =  /*reallynil*/ NULL ;;
                                                                                                                                                                                }
                                                                                                                                                                            ;
                                                                                                                                                                            /*^compute*/
                                                                                                                                                                            /*_#VIX__L22*/
                                                                                                                                                                            meltfnum[14] =
                                                                                                                                                                                /*variadic_index*/
#ifdef melt_variadic_index
                                                                                                                                                                                (melt_variadic_index)
#else
                                                                                                                                                                                -1
#endif /*melt_variadic_index*/
                                                                                                                                                                                ;;

                                                                                                                                                                            {
                                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3651:/ locexp");
                                                                                                                                                                                melt_error_str((melt_ptr_t)(/*_.VLOC__V5*/ meltfptr[4]), ( "in MELT_MAKE_SEXPR unexpected value of discriminant"), (melt_ptr_t)(/*_.DISCRNAME__V51*/ meltfptr[28]));
                                                                                                                                                                            }
                                                                                                                                                                            ;

                                                                                                                                                                            {
                                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3652:/ locexp");
                                                                                                                                                                                /* melt_make_sexpr ERRBADVAL_CHK__1 */
                                                                                                                                                                                inform (UNKNOWN_LOCATION,
                                                                                                                                                                                        "unexpected value index in MELT_MAKE_SEXPR is %d", (int) /*_#VIX__L22*/ meltfnum[14]) ;
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;

                                                                                                                                                                            MELT_CHECK_SIGNAL();
                                                                                                                                                                            ;
                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3657:/ quasiblock");


                                                                                                                                                                            /*_._RETVAL___V1*/
                                                                                                                                                                            meltfptr[0] = (/*nil*/NULL);;

                                                                                                                                                                            {
                                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3657:/ locexp");
                                                                                                                                                                                /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                                                                                                                                                                if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                                                                                                                                                                    melt_warn_for_no_expected_secondary_results();
                                                                                                                                                                                /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                            /*^finalreturn*/
                                                                                                                                                                            ;
                                                                                                                                                                            /*finalret*/
                                                                                                                                                                            goto meltlabend_rout ;
                                                                                                                                                                            /*_.LET___V49*/
                                                                                                                                                                            meltfptr[26] = /*_.RETURN___V52*/ meltfptr[29];;

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3647:/ clear");
                                                                                                                                                                            /*clear*/ /*_.DISCRIM__V50*/
                                                                                                                                                                            meltfptr[27] = 0 ;
                                                                                                                                                                            /*^clear*/
                                                                                                                                                                            /*clear*/ /*_.DISCRNAME__V51*/
                                                                                                                                                                            meltfptr[28] = 0 ;
                                                                                                                                                                            /*^clear*/
                                                                                                                                                                            /*clear*/ /*_#VIX__L22*/
                                                                                                                                                                            meltfnum[14] = 0 ;
                                                                                                                                                                            /*^clear*/
                                                                                                                                                                            /*clear*/ /*_.RETURN___V52*/
                                                                                                                                                                            meltfptr[29] = 0 ;
                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3646:/ quasiblock");


                                                                                                                                                                            /*_.PROGN___V53*/
                                                                                                                                                                            meltfptr[43] = /*_.LET___V49*/ meltfptr[26];;
                                                                                                                                                                            /*^compute*/
                                                                                                                                                                            /*_._IFELSE___V47*/
                                                                                                                                                                            meltfptr[42] = /*_.PROGN___V53*/ meltfptr[43];;
                                                                                                                                                                            /*epilog*/

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:3644:/ clear");
                                                                                                                                                                            /*clear*/ /*_.LET___V49*/
                                                                                                                                                                            meltfptr[26] = 0 ;
                                                                                                                                                                            /*^clear*/
                                                                                                                                                                            /*clear*/ /*_.PROGN___V53*/
                                                                                                                                                                            meltfptr[43] = 0 ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                ;
                                                                                                                                                                /*_._IFELSE___V37*/
                                                                                                                                                                meltfptr[32] = /*_._IFELSE___V47*/ meltfptr[42];;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:3632:/ clear");
                                                                                                                                                                /*clear*/ /*_#IS_CLOSURE__L21*/
                                                                                                                                                                meltfnum[13] = 0 ;
                                                                                                                                                                /*^clear*/
                                                                                                                                                                /*clear*/ /*_._IFELSE___V47*/
                                                                                                                                                                meltfptr[42] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    ;
                                                                                                                                                    /*_._IFELSE___V26*/
                                                                                                                                                    meltfptr[25] = /*_._IFELSE___V37*/ meltfptr[32];;
                                                                                                                                                    /*epilog*/

                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:3619:/ clear");
                                                                                                                                                    /*clear*/ /*_#IS_MIXINT__L17*/
                                                                                                                                                    meltfnum[15] = 0 ;
                                                                                                                                                    /*^clear*/
                                                                                                                                                    /*clear*/ /*_#_IF___L18*/
                                                                                                                                                    meltfnum[12] = 0 ;
                                                                                                                                                    /*^clear*/
                                                                                                                                                    /*clear*/ /*_._IFELSE___V37*/
                                                                                                                                                    meltfptr[32] = 0 ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                        ;
                                                                                                                                        /*_._IFELSE___V23*/
                                                                                                                                        meltfptr[22] = /*_._IFELSE___V26*/ meltfptr[25];;
                                                                                                                                        /*epilog*/

                                                                                                                                        MELT_LOCATION("warmelt-base.melt:3613:/ clear");
                                                                                                                                        /*clear*/ /*_#IS_MIXLOC__L12*/
                                                                                                                                        meltfnum[11] = 0 ;
                                                                                                                                        /*^clear*/
                                                                                                                                        /*clear*/ /*_._IFELSE___V26*/
                                                                                                                                        meltfptr[25] = 0 ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                            ;
                                                                                                                            /*_._IFELSE___V21*/
                                                                                                                            meltfptr[20] = /*_._IFELSE___V23*/ meltfptr[22];;
                                                                                                                            /*epilog*/

                                                                                                                            MELT_LOCATION("warmelt-base.melt:3608:/ clear");
                                                                                                                            /*clear*/ /*_#IS_LIST__L11*/
                                                                                                                            meltfnum[10] = 0 ;
                                                                                                                            /*^clear*/
                                                                                                                            /*clear*/ /*_._IFELSE___V23*/
                                                                                                                            meltfptr[22] = 0 ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                ;
                                                                                                                /*_._IFELSE___V20*/
                                                                                                                meltfptr[19] = /*_._IFELSE___V21*/ meltfptr[20];;
                                                                                                                /*epilog*/

                                                                                                                MELT_LOCATION("warmelt-base.melt:3606:/ clear");
                                                                                                                /*clear*/ /*_#IS_MULTIPLE__L9*/
                                                                                                                meltfnum[8] = 0 ;
                                                                                                                /*^clear*/
                                                                                                                /*clear*/ /*_._IFELSE___V21*/
                                                                                                                meltfptr[20] = 0 ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                    ;
                                                                                                    /*_._IFELSE___V19*/
                                                                                                    meltfptr[18] = /*_._IFELSE___V20*/ meltfptr[19];;
                                                                                                    /*epilog*/

                                                                                                    MELT_LOCATION("warmelt-base.melt:3604:/ clear");
                                                                                                    /*clear*/ /*_#IS_STRING__L8*/
                                                                                                    meltfnum[7] = 0 ;
                                                                                                    /*^clear*/
                                                                                                    /*clear*/ /*_._IFELSE___V20*/
                                                                                                    meltfptr[19] = 0 ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                        ;
                                                                                        /*_._IFELSE___V18*/
                                                                                        meltfptr[17] = /*_._IFELSE___V19*/ meltfptr[18];;
                                                                                        /*epilog*/

                                                                                        MELT_LOCATION("warmelt-base.melt:3602:/ clear");
                                                                                        /*clear*/ /*_#IS_INTEGERBOX__L7*/
                                                                                        meltfnum[6] = 0 ;
                                                                                        /*^clear*/
                                                                                        /*clear*/ /*_._IFELSE___V19*/
                                                                                        meltfptr[18] = 0 ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                            ;
                                                                            /*_._IFELSE___V17*/
                                                                            meltfptr[16] = /*_._IFELSE___V18*/ meltfptr[17];;
                                                                            /*epilog*/

                                                                            MELT_LOCATION("warmelt-base.melt:3600:/ clear");
                                                                            /*clear*/ /*_#IS_OBJECT__L6*/
                                                                            meltfnum[2] = 0 ;
                                                                            /*^clear*/
                                                                            /*clear*/ /*_._IFELSE___V18*/
                                                                            meltfptr[17] = 0 ;
                                                                        }
                                                                        ;
                                                                    }
                                                                ;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:3599:/ clear");
                                                                /*clear*/ /*_.V__V16*/
                                                                meltfptr[13] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_#NULL__L5*/
                                                                meltfnum[1] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_._IFELSE___V17*/
                                                                meltfptr[16] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    else    /*^cond.else*/
                                                        {

                                                            /*^block*/
                                                            /*anyblock*/
                                                            {

                                                                MELT_LOCATION("warmelt-base.melt:3660:/ quasiblock");


                                                                /*_.VARIADIC_CTYPE__V55*/
                                                                meltfptr[28] =
                                                                    /*variadic_type_code*/
#ifdef melt_variadic_index
                                                                    (((melt_variadic_index + 0) >= 0
                                                                      && (melt_variadic_index + 0) < melt_variadic_length)
                                                                     ?  melt_code_to_ctype (meltxargdescr_[melt_variadic_index + 0]
                                                                                            & MELT_ARGDESCR_MAX)
                                                                     : NULL)
#else
                                                                    NULL /* no variadic_ctype outside of variadic functions */
#endif /*melt_variadic_index*/
                                                                    ;;
                                                                MELT_LOCATION("warmelt-base.melt:3660:/ cond");
                                                                /*cond*/
                                                                if (
                                                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.VARIADIC_CTYPE__V55*/ meltfptr[28]),
                                                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])))
                                                                ) /*then*/
                                                                    {
                                                                        /*^cond.then*/
                                                                        /*^getslot*/
                                                                        {
                                                                            melt_ptr_t slot=NULL, obj=NULL;
                                                                            obj = (melt_ptr_t)(/*_.VARIADIC_CTYPE__V55*/ meltfptr[28]) /*=obj*/;
                                                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                                            /*_.CTYNAME__V56*/
                                                                            meltfptr[29] = slot;
                                                                        };
                                                                        ;
                                                                    }
                                                                else    /*^cond.else*/
                                                                    {

                                                                        /*_.CTYNAME__V56*/ meltfptr[29] =  /*reallynil*/ NULL ;;
                                                                    }
                                                                ;
                                                                /*^compute*/
                                                                /*_#VIX__L23*/
                                                                meltfnum[14] =
                                                                    /*variadic_index*/
#ifdef melt_variadic_index
                                                                    (melt_variadic_index)
#else
                                                                    -1
#endif /*melt_variadic_index*/
                                                                    ;;

                                                                {
                                                                    MELT_LOCATION("warmelt-base.melt:3663:/ locexp");
                                                                    melt_error_str((melt_ptr_t)(/*_.VLOC__V5*/ meltfptr[4]), ( "in MELT_MAKE_SEXPR unexpected thing of ctype"), (melt_ptr_t)(/*_.CTYNAME__V56*/ meltfptr[29]));
                                                                }
                                                                ;

                                                                {
                                                                    MELT_LOCATION("warmelt-base.melt:3664:/ locexp");
                                                                    /* melt_make_sexpr ERRBADTHING_CHK__1 */
                                                                    inform (UNKNOWN_LOCATION,
                                                                            "unexpected thing index in MELT_MAKE_SEXPR is %d", (int) /*_#VIX__L23*/ meltfnum[14]) ;
                                                                    ;
                                                                }
                                                                ;

                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                MELT_LOCATION("warmelt-base.melt:3669:/ quasiblock");


                                                                /*_._RETVAL___V1*/
                                                                meltfptr[0] = (/*nil*/NULL);;

                                                                {
                                                                    MELT_LOCATION("warmelt-base.melt:3669:/ locexp");
                                                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                                                        melt_warn_for_no_expected_secondary_results();
                                                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                                                    ;
                                                                }
                                                                ;
                                                                /*^finalreturn*/
                                                                ;
                                                                /*finalret*/
                                                                goto meltlabend_rout ;
                                                                /*_.LET___V54*/
                                                                meltfptr[27] = /*_.RETURN___V57*/ meltfptr[26];;

                                                                MELT_LOCATION("warmelt-base.melt:3660:/ clear");
                                                                /*clear*/ /*_.VARIADIC_CTYPE__V55*/
                                                                meltfptr[28] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_.CTYNAME__V56*/
                                                                meltfptr[29] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_#VIX__L23*/
                                                                meltfnum[14] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_.RETURN___V57*/
                                                                meltfptr[26] = 0 ;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:3599:/ clear");
                                                                /*clear*/ /*_.LET___V54*/
                                                                meltfptr[27] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    ;
                                                    /*epilog*/
                                                }
                                                ;
                                            }
                                        ;
                                        /*epilog*/
                                    }
                                    ;
                                }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                ;
                /*epilog*/
            }
            ;
            ;
            goto meltlabloop_ARGLOOP_6;
meltlabexit_ARGLOOP_6:
            ;
            MELT_LOCATION("warmelt-base.melt:3586:/ loopepilog");
            /*loopepilog*/
            /*_.FOREVER___V12*/
            meltfptr[5] = /*_.ARGLOOP__V13*/ meltfptr[12];;
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3672:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.SEXPR__V10*/ meltfptr[7];;

        {
            MELT_LOCATION("warmelt-base.melt:3672:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V3*/
        meltfptr[2] = /*_.RETURN___V58*/ meltfptr[43];;

        MELT_LOCATION("warmelt-base.melt:3573:/ clear");
        /*clear*/ /*_.CONT__V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_MIXINT__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.VLOC__V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SEXPR__V10*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.FOREVER___V12*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V58*/
        meltfptr[43] = 0 ;
        MELT_LOCATION("warmelt-base.melt:3569:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3569:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MELT_MAKE_SEXPR", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef melt_variadic_length
#undef melt_variadic_index

#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_35_WARMELTmiBASE_MELT_MAKE_SEXPR*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_37_WARMELTmiBASE_MULTIPLE_SORT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_37_WARMELTmiBASE_MULTIPLE_SORT fromline 1752 */

    /** start of frame for meltrout_37_WARMELTmiBASE_MULTIPLE_SORT of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT// fromline 1568
        : public Melt_CallFrameWithValues<30>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[11];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<30> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT), clos) {};
        MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT() //the constructor fromline 1642
            : Melt_CallFrameWithValues<30> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<30> (fil,lin, sizeof(MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT)) {};
        MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<30> (fil,lin, sizeof(MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT


    /** end of frame for meltrout_37_WARMELTmiBASE_MULTIPLE_SORT fromline 1697**/

    /* end of frame for routine meltrout_37_WARMELTmiBASE_MULTIPLE_SORT fromline 1756 */

    /* classy proc frame meltrout_37_WARMELTmiBASE_MULTIPLE_SORT */
    MeltFrame_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_37_WARMELTmiBASE_MULTIPLE_SORT fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MULTIPLE_SORT", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3741:/ getarg");
    /*_.MUL__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.CMP__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.CMP__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.DIS__V4*/
    meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.DIS__V4*/ meltfptr[3])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_MULTIPLE__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.MUL__V2*/ meltfptr[1])) == MELTOBMAG_MULTIPLE);;
        MELT_LOCATION("warmelt-base.melt:3751:/ cond");
        /*cond*/
        if (/*_#IS_MULTIPLE__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {




                    {
                        MELT_LOCATION("warmelt-base.melt:3752:/ locexp");
                        /*void*/
                        (void)0;
                    }
                    ;
                    /*clear*/ /*_._IFELSE___V5*/
                    meltfptr[4] = 0 ;
                    /*epilog*/
                }
                ;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3751:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3753:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3753:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IFELSE___V5*/
                    meltfptr[4] = /*_.RETURN___V6*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3751:/ clear");
                    /*clear*/ /*_.RETURN___V6*/
                    meltfptr[5] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_HOOK__L2*/
        meltfnum[1] =
            (melt_magic_discr((melt_ptr_t)((/*!HOOK_SORT_COMPARE_LESS*/ meltfrout->tabval[0]))) == MELTOBMAG_HOOK);;
        MELT_LOCATION("warmelt-base.melt:3754:/ cond");
        /*cond*/
        if (/*_#IS_HOOK__L2*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*_._IFELSE___V7*/ meltfptr[5] = (/*nil*/NULL);;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3754:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-base.melt:3755:/ cppif.then");
                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*_#IS_HOOK__L3*/
                        meltfnum[2] =
                            (melt_magic_discr((melt_ptr_t)((/*!HOOK_SORT_COMPARE_LESS*/ meltfrout->tabval[0]))) == MELTOBMAG_HOOK);;
                        MELT_LOCATION("warmelt-base.melt:3755:/ cond");
                        /*cond*/
                        if (/*_#IS_HOOK__L3*/ meltfnum[2]) /*then*/
                            {
                                /*^cond.then*/
                                /*_._IFELSE___V9*/ meltfptr[8] = (/*nil*/NULL);;
                            }
                        else
                            {
                                MELT_LOCATION("warmelt-base.melt:3755:/ cond.else");

                                /*^block*/
                                /*anyblock*/
                                {


                                    MELT_CHECK_SIGNAL();
                                    ;
                                    /*^apply*/
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[6];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_cstring =  "multiple_sort check hook_sort_compare_less";
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 3755;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &(/*!HOOK_SORT_COMPARE_LESS*/ meltfrout->tabval[0]);
                                        /*^apply.arg*/
                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &(/*!MULTIPLE_SORT*/ meltfrout->tabval[2]);
                                        /*^apply.arg*/
                                        argtab[5].meltbp_aptr = (melt_ptr_t*) &/*_.MUL__V2*/ meltfptr[1];
                                        /*_.MELT_ASSERT_FAILURE_FUN__V10*/
                                        meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IFELSE___V9*/
                                    meltfptr[8] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-base.melt:3755:/ clear");
                                    /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/
                                    meltfptr[9] = 0 ;
                                }
                                ;
                            }
                        ;
                        /*_.IFCPP___V8*/
                        meltfptr[7] = /*_._IFELSE___V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:3755:/ clear");
                        /*clear*/ /*_#IS_HOOK__L3*/
                        meltfnum[2] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IFELSE___V9*/
                        meltfptr[8] = 0 ;
                    }

#else /*MELT_HAVE_DEBUG*/
                    /*^cppif.else*/
                    /*_.IFCPP___V8*/ meltfptr[7] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3758:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[1];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_cstring =  "multiple_sort with corrupted hook_sort_compare_less";
                        /*_.FATAL_ERROR_AT__V11*/
                        meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!FATAL_ERROR_AT*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    MELT_LOCATION("warmelt-base.melt:3754:/ quasiblock");


                    /*_.PROGN___V12*/
                    meltfptr[8] = /*_.FATAL_ERROR_AT__V11*/ meltfptr[9];;
                    /*^compute*/
                    /*_._IFELSE___V7*/
                    meltfptr[5] = /*_.PROGN___V12*/ meltfptr[8];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3754:/ clear");
                    /*clear*/ /*_.IFCPP___V8*/
                    meltfptr[7] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.FATAL_ERROR_AT__V11*/
                    meltfptr[9] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V12*/
                    meltfptr[8] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_CLOSURE__L4*/
        meltfnum[2] =
            (melt_magic_discr((melt_ptr_t)(/*_.CMP__V3*/ meltfptr[2])) == MELTOBMAG_CLOSURE);;
        MELT_LOCATION("warmelt-base.melt:3759:/ cond");
        /*cond*/
        if (/*_#IS_CLOSURE__L4*/ meltfnum[2]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {




                    {
                        MELT_LOCATION("warmelt-base.melt:3760:/ locexp");
                        /*void*/
                        (void)0;
                    }
                    ;
                    /*clear*/ /*_._IFELSE___V13*/
                    meltfptr[7] = 0 ;
                    /*epilog*/
                }
                ;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3759:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3761:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3761:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IFELSE___V13*/
                    meltfptr[7] = /*_.RETURN___V14*/ meltfptr[9];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3759:/ clear");
                    /*clear*/ /*_.RETURN___V14*/
                    meltfptr[9] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#NULL__L5*/
        meltfnum[4] =
            (/*null*/(/*_.DIS__V4*/ meltfptr[3]) == NULL);;
        MELT_LOCATION("warmelt-base.melt:3762:/ cond");
        /*cond*/
        if (/*_#NULL__L5*/ meltfnum[4]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    MELT_LOCATION("warmelt-base.melt:3763:/ compute");
                    /*_.DIS__V4*/
                    meltfptr[3] = /*_.SETQ___V16*/ meltfptr[9] = (/*!DISCR_MULTIPLE*/ meltfrout->tabval[4]);;
                    /*_._IF___V15*/
                    meltfptr[8] = /*_.SETQ___V16*/ meltfptr[9];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3762:/ clear");
                    /*clear*/ /*_.SETQ___V16*/
                    meltfptr[9] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V15*/ meltfptr[8] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_A__L6*/
        meltfnum[5] =
            melt_is_instance_of((melt_ptr_t)(/*_.DIS__V4*/ meltfptr[3]), (melt_ptr_t)((/*!CLASS_DISCRIMINANT*/ meltfrout->tabval[5])));;
        MELT_LOCATION("warmelt-base.melt:3764:/ cond");
        /*cond*/
        if (/*_#IS_A__L6*/ meltfnum[5]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {




                    {
                        MELT_LOCATION("warmelt-base.melt:3765:/ locexp");
                        /*void*/
                        (void)0;
                    }
                    ;
                    /*clear*/ /*_._IFELSE___V17*/
                    meltfptr[9] = 0 ;
                    /*epilog*/
                }
                ;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3764:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3766:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3766:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IFELSE___V17*/
                    meltfptr[9] = /*_.RETURN___V18*/ meltfptr[17];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3764:/ clear");
                    /*clear*/ /*_.RETURN___V18*/
                    meltfptr[17] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#CHECKMAGIC_CHK__L7*/
        meltfnum[6] =
            /* multiple_sort CHECKMAGIC_CHK__1 */
            (((meltobject_ptr_t)(/*_.DIS__V4*/ meltfptr[3]))->meltobj_magic == MELTOBMAG_MULTIPLE) ;;
        MELT_LOCATION("warmelt-base.melt:3767:/ cond");
        /*cond*/
        if (/*_#CHECKMAGIC_CHK__L7*/ meltfnum[6]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {




                    {
                        MELT_LOCATION("warmelt-base.melt:3770:/ locexp");
                        /*void*/
                        (void)0;
                    }
                    ;
                    /*clear*/ /*_._IFELSE___V19*/
                    meltfptr[17] = 0 ;
                    /*epilog*/
                }
                ;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3767:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3771:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3771:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IFELSE___V19*/
                    meltfptr[17] = /*_.RETURN___V20*/ meltfptr[19];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3767:/ clear");
                    /*clear*/ /*_.RETURN___V20*/
                    meltfptr[19] = 0 ;
                }
                ;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:3772:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_MULTIPLE__L8*/
            meltfnum[7] =
                (melt_magic_discr((melt_ptr_t)(/*_.MUL__V2*/ meltfptr[1])) == MELTOBMAG_MULTIPLE);;
            MELT_LOCATION("warmelt-base.melt:3772:/ cond");
            /*cond*/
            if (/*_#IS_MULTIPLE__L8*/ meltfnum[7]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V22*/ meltfptr[21] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:3772:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "multiple_sort check mul";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 3772;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MUL__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V23*/
                            meltfptr[22] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V22*/
                        meltfptr[21] = /*_.MELT_ASSERT_FAILURE_FUN__V23*/ meltfptr[22];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:3772:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V23*/
                        meltfptr[22] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V21*/
            meltfptr[19] = /*_._IFELSE___V22*/ meltfptr[21];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:3772:/ clear");
            /*clear*/ /*_#IS_MULTIPLE__L8*/
            meltfnum[7] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V22*/
            meltfptr[21] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V21*/ meltfptr[19] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-base.melt:3773:/ quasiblock");


        /*_#TUPLEN__L9*/
        meltfnum[7] =
            (melt_multiple_length((melt_ptr_t)(/*_.MUL__V2*/ meltfptr[1])));;
        MELT_LOCATION("warmelt-base.melt:3775:/ quasiblock");


        /*_.RES__V26*/
        meltfptr[25] =
            (meltgc_new_multiple((meltobject_ptr_t)(/*_.DIS__V4*/ meltfptr[3]), (/*_#TUPLEN__L9*/ meltfnum[7])));;
        /*^compute*/
        /*_#RESLEN__L10*/
        meltfnum[9] =
            (melt_multiple_length((melt_ptr_t)(/*_.RES__V26*/ meltfptr[25])));;

        {
            MELT_LOCATION("warmelt-base.melt:3779:/ locexp");
            /* multiple_sort SORTRES_CHK__1 start */
            if (/*_#RESLEN__L10*/ meltfnum[9] >= (long)INT_MAX/2)
                melt_fatal_error("too big sized %ld tuple to sort", /*_#RESLEN__L10*/ meltfnum[9]) ;
            melt_assertmsg ("check that RESLEN == TUPLEN in multiple_sort", /*_#RESLEN__L10*/ meltfnum[9] == /*_#TUPLEN__L9*/ meltfnum[7]) ;
            Melt_Sort_Compare_Index meltixsorter_SORTRES_CHK__1 ((meltmultiple_st**)(&(/*_.MUL__V2*/ meltfptr[1])), &(/*_.CMP__V3*/ meltfptr[2])) ;
            std::vector<int> meltixvect_SORTRES_CHK__1	;
            meltixvect_SORTRES_CHK__1.resize(/*_#RESLEN__L10*/ meltfnum[9])	;
            for (long meltix=0;
                    meltix</*_#RESLEN__L10*/ meltfnum[9];
                    meltix++)
                meltixvect_SORTRES_CHK__1[meltix] = meltix ;
            /* do the sort SORTRES_CHK__1 */
            std::stable_sort (meltixvect_SORTRES_CHK__1.begin(),
                              meltixvect_SORTRES_CHK__1.end(),
                              meltixsorter_SORTRES_CHK__1) ;
            melt_assertmsg ("check that RES is multiple in multiple_sort", melt_magic_discr (/*_.RES__V26*/ meltfptr[25]) == MELTOBMAG_MULTIPLE) ;
            melt_assertmsg ("check that MUL is multiple in multiple_sort", melt_magic_discr (/*_.MUL__V2*/ meltfptr[1]) == MELTOBMAG_MULTIPLE) ;
            for (long meltix=0;
                    meltix</*_#RESLEN__L10*/ meltfnum[9];
                    meltix++)
                {
                    int sortix_SORTRES_CHK__1 = meltixvect_SORTRES_CHK__1[meltix] ;
                    melt_assertmsg ("check index in multiple_sort", sortix_SORTRES_CHK__1>=0 && (long)sortix_SORTRES_CHK__1 < /*_#RESLEN__L10*/ meltfnum[9]) ;
                    ((meltmultiple_st*)(/*_.RES__V26*/ meltfptr[25]))->tabval[meltix]
                        = ((meltmultiple_st*)(/*_.MUL__V2*/ meltfptr[1]))->tabval[sortix_SORTRES_CHK__1] ;
                } ;
            meltgc_touch (/*_.RES__V26*/ meltfptr[25]) ;
            /* multiple_sort SORTRES_CHK__1 end */
            ;
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:3809:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_MULTIPLE__L11*/
            meltfnum[10] =
                (melt_magic_discr((melt_ptr_t)(/*_.RES__V26*/ meltfptr[25])) == MELTOBMAG_MULTIPLE);;
            MELT_LOCATION("warmelt-base.melt:3809:/ cond");
            /*cond*/
            if (/*_#IS_MULTIPLE__L11*/ meltfnum[10]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V28*/ meltfptr[27] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:3809:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check res";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 3809;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V26*/ meltfptr[25];
                            /*_.MELT_ASSERT_FAILURE_FUN__V29*/
                            meltfptr[28] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V28*/
                        meltfptr[27] = /*_.MELT_ASSERT_FAILURE_FUN__V29*/ meltfptr[28];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:3809:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V29*/
                        meltfptr[28] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V27*/
            meltfptr[26] = /*_._IFELSE___V28*/ meltfptr[27];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:3809:/ clear");
            /*clear*/ /*_#IS_MULTIPLE__L11*/
            meltfnum[10] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V28*/
            meltfptr[27] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V27*/ meltfptr[26] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3811:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.RES__V26*/ meltfptr[25];;

        {
            MELT_LOCATION("warmelt-base.melt:3811:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V25*/
        meltfptr[21] = /*_.RETURN___V30*/ meltfptr[28];;

        MELT_LOCATION("warmelt-base.melt:3775:/ clear");
        /*clear*/ /*_.RES__V26*/
        meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_#RESLEN__L10*/
        meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V27*/
        meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V30*/
        meltfptr[28] = 0 ;
        /*_.LET___V24*/
        meltfptr[22] = /*_.LET___V25*/ meltfptr[21];;

        MELT_LOCATION("warmelt-base.melt:3773:/ clear");
        /*clear*/ /*_#TUPLEN__L9*/
        meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V25*/
        meltfptr[21] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3741:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V24*/ meltfptr[22];;

        {
            MELT_LOCATION("warmelt-base.melt:3741:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#IS_MULTIPLE__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_HOOK__L2*/
        meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V7*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_CLOSURE__L4*/
        meltfnum[2] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V13*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L5*/
        meltfnum[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V15*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L6*/
        meltfnum[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V17*/
        meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#CHECKMAGIC_CHK__L7*/
        meltfnum[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V19*/
        meltfptr[17] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V21*/
        meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V24*/
        meltfptr[22] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MULTIPLE_SORT", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_37_WARMELTmiBASE_MULTIPLE_SORT_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_37_WARMELTmiBASE_MULTIPLE_SORT*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE fromline 1752 */

    /** start of frame for meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE// fromline 1568
        : public Melt_CallFrameWithValues<18>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[1];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<18> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE), clos) {};
        MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE() //the constructor fromline 1642
            : Melt_CallFrameWithValues<18> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<18> (fil,lin, sizeof(MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE)) {};
        MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<18> (fil,lin, sizeof(MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE


    /** end of frame for meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE fromline 1697**/

    /* end of frame for routine meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE fromline 1756 */

    /* classy proc frame meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE */
    MeltFrame_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MAPOBJECT_SORTED_ATTRIBUTE_TUPLE", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3816:/ getarg");
    /*_.MAPO__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3819:/ quasiblock");


        /*_#MAPCOUNT__L1*/
        meltfnum[0] =
            (melt_count_mapobjects((meltmapobjects_ptr_t)(/*_.MAPO__V2*/ meltfptr[1])));;
        /*^compute*/
        /*_.COUNTBOX__V4*/
        meltfptr[3] =
            (meltgc_new_int((meltobject_ptr_t)((/*!DISCR_INTEGER*/ meltfrout->tabval[0])), (0)));;
        /*^compute*/
        /*_.BOXEDONE__V5*/
        meltfptr[4] =
            (meltgc_new_int((meltobject_ptr_t)((/*!DISCR_INTEGER*/ meltfrout->tabval[0])), (1)));;
        /*^compute*/
        /*_.BOXEDZERO__V6*/
        meltfptr[5] =
            (meltgc_new_int((meltobject_ptr_t)((/*!DISCR_INTEGER*/ meltfrout->tabval[0])), (0)));;
        /*^compute*/
        /*_.BOXEDMINUSONE__V7*/
        meltfptr[6] =
            (meltgc_new_int((meltobject_ptr_t)((/*!DISCR_INTEGER*/ meltfrout->tabval[0])), (-1)));;
        /*^compute*/
        /*_.TUPL__V8*/
        meltfptr[7] =
            (meltgc_new_multiple((meltobject_ptr_t)((/*!DISCR_MULTIPLE*/ meltfrout->tabval[1])), (/*_#MAPCOUNT__L1*/ meltfnum[0])));;
        MELT_LOCATION("warmelt-base.melt:3830:/ quasiblock");


        /*^newclosure*/
        /*newclosure*/ /*_.LAMBDA___V10*/
        meltfptr[9] =
            (melt_ptr_t) meltgc_new_closure((meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE)))), (meltroutine_ptr_t)((/*!konst_4*/ meltfrout->tabval[4])), (2));
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V10*/ meltfptr[9])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 0>= 0 && 0< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V10*/ meltfptr[9])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V10*/ meltfptr[9])->tabval[0] = (melt_ptr_t)(/*_.COUNTBOX__V4*/ meltfptr[3]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V10*/ meltfptr[9])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 1>= 0 && 1< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V10*/ meltfptr[9])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V10*/ meltfptr[9])->tabval[1] = (melt_ptr_t)(/*_.TUPL__V8*/ meltfptr[7]);
        ;
        /*_.LAMBDA___V9*/
        meltfptr[8] = /*_.LAMBDA___V10*/ meltfptr[9];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3828:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.LAMBDA___V9*/ meltfptr[8];
            /*_.MAPOBJECT_EVERY__V11*/
            meltfptr[10] =  melt_apply ((meltclosure_ptr_t)((/*!MAPOBJECT_EVERY*/ meltfrout->tabval[2])), (melt_ptr_t)(/*_.MAPO__V2*/ meltfptr[1]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-base.melt:3839:/ quasiblock");


        MELT_LOCATION("warmelt-base.melt:3842:/ quasiblock");


        /*^newclosure*/
        /*newclosure*/ /*_.LAMBDA___V14*/
        meltfptr[13] =
            (melt_ptr_t) meltgc_new_closure((meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE)))), (meltroutine_ptr_t)((/*!konst_7*/ meltfrout->tabval[7])), (3));
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V14*/ meltfptr[13])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 0>= 0 && 0< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V14*/ meltfptr[13])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V14*/ meltfptr[13])->tabval[0] = (melt_ptr_t)(/*_.BOXEDMINUSONE__V7*/ meltfptr[6]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V14*/ meltfptr[13])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 1>= 0 && 1< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V14*/ meltfptr[13])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V14*/ meltfptr[13])->tabval[1] = (melt_ptr_t)(/*_.BOXEDZERO__V6*/ meltfptr[5]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V14*/ meltfptr[13])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 2>= 0 && 2< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V14*/ meltfptr[13])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V14*/ meltfptr[13])->tabval[2] = (melt_ptr_t)(/*_.BOXEDONE__V5*/ meltfptr[4]);
        ;
        /*_.LAMBDA___V13*/
        meltfptr[12] = /*_.LAMBDA___V14*/ meltfptr[13];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3840:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.LAMBDA___V13*/ meltfptr[12];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[1]);
            /*_.SORTUPL__V15*/
            meltfptr[14] =  melt_apply ((meltclosure_ptr_t)((/*!MULTIPLE_SORT*/ meltfrout->tabval[5])), (melt_ptr_t)(/*_.TUPL__V8*/ meltfptr[7]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-base.melt:3856:/ quasiblock");


        /*^newclosure*/
        /*newclosure*/ /*_.LAMBDA___V17*/
        meltfptr[16] =
            (melt_ptr_t) meltgc_new_closure((meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE)))), (meltroutine_ptr_t)((/*!konst_9*/ meltfrout->tabval[9])), (0));
        ;
        /*_.LAMBDA___V16*/
        meltfptr[15] = /*_.LAMBDA___V17*/ meltfptr[16];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3856:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.LAMBDA___V16*/ meltfptr[15];
            /*_.MULTIPLE_MAP__V18*/
            meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!MULTIPLE_MAP*/ meltfrout->tabval[8])), (melt_ptr_t)(/*_.SORTUPL__V15*/ meltfptr[14]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.LET___V12*/
        meltfptr[11] = /*_.MULTIPLE_MAP__V18*/ meltfptr[17];;

        MELT_LOCATION("warmelt-base.melt:3839:/ clear");
        /*clear*/ /*_.LAMBDA___V13*/
        meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SORTUPL__V15*/
        meltfptr[14] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LAMBDA___V16*/
        meltfptr[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MULTIPLE_MAP__V18*/
        meltfptr[17] = 0 ;
        /*_.LET___V3*/
        meltfptr[2] = /*_.LET___V12*/ meltfptr[11];;

        MELT_LOCATION("warmelt-base.melt:3819:/ clear");
        /*clear*/ /*_#MAPCOUNT__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.COUNTBOX__V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.BOXEDONE__V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_.BOXEDZERO__V6*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.BOXEDMINUSONE__V7*/
        meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPL__V8*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LAMBDA___V9*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MAPOBJECT_EVERY__V11*/
        meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V12*/
        meltfptr[11] = 0 ;
        MELT_LOCATION("warmelt-base.melt:3816:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3816:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MAPOBJECT_SORTED_ATTRIBUTE_TUPLE", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_38_WARMELTmiBASE_MAPOBJECT_SORTED_ATTRIBUTE_TUPLE*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_39_WARMELTmiBASE_LAMBDA_cl1(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                     const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_39_WARMELTmiBASE_LAMBDA_cl1_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_39_WARMELTmiBASE_LAMBDA_cl1 fromline 1752 */

    /** start of frame for meltrout_39_WARMELTmiBASE_LAMBDA_cl1 of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1// fromline 1568
        : public Melt_CallFrameWithValues<6>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[2];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<6> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1), clos) {};
        MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1() //the constructor fromline 1642
            : Melt_CallFrameWithValues<6> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<6> (fil,lin, sizeof(MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1)) {};
        MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<6> (fil,lin, sizeof(MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1


    /** end of frame for meltrout_39_WARMELTmiBASE_LAMBDA_cl1 fromline 1697**/

    /* end of frame for routine meltrout_39_WARMELTmiBASE_LAMBDA_cl1 fromline 1756 */

    /* classy proc frame meltrout_39_WARMELTmiBASE_LAMBDA_cl1 */
    MeltFrame_meltrout_39_WARMELTmiBASE_LAMBDA_cl1
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_39_WARMELTmiBASE_LAMBDA_cl1 fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LAMBDA_cl1", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3830:/ getarg");
    /*_.AT__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.VA__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.VA__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3831:/ quasiblock");


        /*_#CURCOUNT__L1*/
        meltfnum[0] =
            (melt_get_int((melt_ptr_t)((/*~COUNTBOX*/ meltfclos->tabval[0]))));;
        /*^compute*/
        /*_.MAKE_INTEGERBOX__V4*/
        meltfptr[3] =
            (meltgc_new_int((meltobject_ptr_t)((/*!DISCR_INTEGER*/ meltfrout->tabval[0])), (/*_#CURCOUNT__L1*/ meltfnum[0])));;
        MELT_LOCATION("warmelt-base.melt:3832:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_1_st
            {
                struct MELT_MULTIPLE_STRUCT(3) rtup_0__TUPLREC__x1;
                long meltletrec_1_endgap;
            } *meltletrec_1_ptr = 0;
            meltletrec_1_ptr = (struct meltletrec_1_st *) meltgc_allocate (sizeof (struct meltletrec_1_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x1*/
            /*_.TUPLREC___V6*/
            meltfptr[5] = (melt_ptr_t) &meltletrec_1_ptr->rtup_0__TUPLREC__x1;
            meltletrec_1_ptr->rtup_0__TUPLREC__x1.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_1_ptr->rtup_0__TUPLREC__x1.nbval = 3;


            /*^putuple*/
            /*putupl#1*/
            melt_assertmsg("putupl [:3832] #1 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:3832] #1 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))->tabval[0] = (melt_ptr_t)(/*_.AT__V2*/ meltfptr[1]);
            ;
            /*^putuple*/
            /*putupl#2*/
            melt_assertmsg("putupl [:3832] #2 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:3832] #2 checkoff", (1>=0 && 1< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))->tabval[1] = (melt_ptr_t)(/*_.VA__V3*/ meltfptr[2]);
            ;
            /*^putuple*/
            /*putupl#3*/
            melt_assertmsg("putupl [:3832] #3 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:3832] #3 checkoff", (2>=0 && 2< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V6*/ meltfptr[5]))->tabval[2] = (melt_ptr_t)(/*_.MAKE_INTEGERBOX__V4*/ meltfptr[3]);
            ;
            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V6*/ meltfptr[5]);
            ;
            /*_.ENT__V5*/
            meltfptr[4] = /*_.TUPLREC___V6*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:3832:/ clear");
            /*clear*/ /*_.TUPLREC___V6*/
            meltfptr[5] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V6*/
            meltfptr[5] = 0 ;
        } /*end multiallocblock*/
        ;

        {
            MELT_LOCATION("warmelt-base.melt:3835:/ locexp");
            meltgc_multiple_put_nth((melt_ptr_t)((/*~TUPL*/ meltfclos->tabval[1])), (/*_#CURCOUNT__L1*/ meltfnum[0]), (melt_ptr_t)(/*_.ENT__V5*/ meltfptr[4]));
        }
        ;
        /*_#plI__L2*/
        meltfnum[1] =
            ((/*_#CURCOUNT__L1*/ meltfnum[0]) + (1));;

        {
            MELT_LOCATION("warmelt-base.melt:3836:/ locexp");
            melt_put_int((melt_ptr_t)((/*~COUNTBOX*/ meltfclos->tabval[0])), (/*_#plI__L2*/ meltfnum[1]));
        }
        ;

        MELT_LOCATION("warmelt-base.melt:3831:/ clear");
        /*clear*/ /*_#CURCOUNT__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MAKE_INTEGERBOX__V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ENT__V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_#plI__L2*/
        meltfnum[1] = 0 ;
        /*epilog*/
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LAMBDA_cl1", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_39_WARMELTmiBASE_LAMBDA_cl1_melt;
    return (melt_ptr_t)(/*noretval*/ NULL);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_39_WARMELTmiBASE_LAMBDA_cl1*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_40_WARMELTmiBASE_LAMBDA_cl2(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                     const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_40_WARMELTmiBASE_LAMBDA_cl2_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_40_WARMELTmiBASE_LAMBDA_cl2 fromline 1752 */

    /** start of frame for meltrout_40_WARMELTmiBASE_LAMBDA_cl2 of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2// fromline 1568
        : public Melt_CallFrameWithValues<12>
    {
    public: /* fromline 1572*/
// no classy longs
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<12> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2), clos) {};
        MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2() //the constructor fromline 1642
            : Melt_CallFrameWithValues<12> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<12> (fil,lin, sizeof(MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2)) {};
        MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<12> (fil,lin, sizeof(MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2


    /** end of frame for meltrout_40_WARMELTmiBASE_LAMBDA_cl2 fromline 1697**/

    /* end of frame for routine meltrout_40_WARMELTmiBASE_LAMBDA_cl2 fromline 1756 */

    /* classy proc frame meltrout_40_WARMELTmiBASE_LAMBDA_cl2 */
    MeltFrame_meltrout_40_WARMELTmiBASE_LAMBDA_cl2
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_40_WARMELTmiBASE_LAMBDA_cl2 fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LAMBDA_cl2", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3842:/ getarg");
    /*_.E1__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.E2__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.E2__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3843:/ quasiblock");


        /*_.E1AT__V5*/
        meltfptr[4] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E1__V2*/ meltfptr[1]), (0)));;
        /*^compute*/
        /*_.E1VA__V6*/
        meltfptr[5] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E1__V2*/ meltfptr[1]), (1)));;
        /*^compute*/
        /*_.E1RK__V7*/
        meltfptr[6] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E1__V2*/ meltfptr[1]), (2)));;
        /*^compute*/
        /*_.E2AT__V8*/
        meltfptr[7] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E2__V3*/ meltfptr[2]), (0)));;
        /*^compute*/
        /*_.E2VA__V9*/
        meltfptr[8] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E2__V3*/ meltfptr[2]), (1)));;
        /*^compute*/
        /*_.E2RK__V10*/
        meltfptr[9] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E2__V3*/ meltfptr[2]), (2)));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3851:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[6];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.E1RK__V7*/ meltfptr[6];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.E2AT__V8*/ meltfptr[7];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.E2RK__V10*/ meltfptr[9];
            /*^apply.arg*/
            argtab[3].meltbp_aptr = (melt_ptr_t*) &(/*~BOXEDMINUSONE*/ meltfclos->tabval[0]);
            /*^apply.arg*/
            argtab[4].meltbp_aptr = (melt_ptr_t*) &(/*~BOXEDZERO*/ meltfclos->tabval[1]);
            /*^apply.arg*/
            argtab[5].meltbp_aptr = (melt_ptr_t*) &(/*~BOXEDONE*/ meltfclos->tabval[2]);
            /*_.COMPARE_OBJ_RANKED__V11*/
            meltfptr[10] =  melt_apply ((meltclosure_ptr_t)((/*!COMPARE_OBJ_RANKED*/ meltfrout->tabval[0])), (melt_ptr_t)(/*_.E1AT__V5*/ meltfptr[4]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3850:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.COMPARE_OBJ_RANKED__V11*/ meltfptr[10];;
        MELT_LOCATION("warmelt-base.melt:3850:/ putxtraresult");
        if (!meltxrestab_ || !meltxresdescr_) goto meltlabend_rout;
        if (meltxresdescr_[0] != MELTBPAR_PTR) goto meltlabend_rout;
        if (meltxrestab_[0].meltbp_aptr) *(meltxrestab_[0].meltbp_aptr) = (melt_ptr_t) ((/*nil*/NULL));
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V4*/
        meltfptr[3] = /*_.RETURN___V12*/ meltfptr[11];;

        MELT_LOCATION("warmelt-base.melt:3843:/ clear");
        /*clear*/ /*_.E1AT__V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_.E1VA__V6*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.E1RK__V7*/
        meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.E2AT__V8*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.E2VA__V9*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.E2RK__V10*/
        meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.COMPARE_OBJ_RANKED__V11*/
        meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V12*/
        meltfptr[11] = 0 ;
        MELT_LOCATION("warmelt-base.melt:3842:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V4*/ meltfptr[3];;

        {
            MELT_LOCATION("warmelt-base.melt:3842:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V4*/
        meltfptr[3] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LAMBDA_cl2", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_40_WARMELTmiBASE_LAMBDA_cl2_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_40_WARMELTmiBASE_LAMBDA_cl2*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_41_WARMELTmiBASE_LAMBDA_cl3(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                     const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_41_WARMELTmiBASE_LAMBDA_cl3_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_41_WARMELTmiBASE_LAMBDA_cl3 fromline 1752 */

    /** start of frame for meltrout_41_WARMELTmiBASE_LAMBDA_cl3 of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3// fromline 1568
        : public Melt_CallFrameWithValues<3>
    {
    public: /* fromline 1572*/
// no classy longs
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<3> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3), clos) {};
        MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3() //the constructor fromline 1642
            : Melt_CallFrameWithValues<3> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<3> (fil,lin, sizeof(MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3)) {};
        MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<3> (fil,lin, sizeof(MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3


    /** end of frame for meltrout_41_WARMELTmiBASE_LAMBDA_cl3 fromline 1697**/

    /* end of frame for routine meltrout_41_WARMELTmiBASE_LAMBDA_cl3 fromline 1756 */

    /* classy proc frame meltrout_41_WARMELTmiBASE_LAMBDA_cl3 */
    MeltFrame_meltrout_41_WARMELTmiBASE_LAMBDA_cl3
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_41_WARMELTmiBASE_LAMBDA_cl3 fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LAMBDA_cl3", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3856:/ getarg");
    /*_.EL__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        /*_.MULTIPLE_NTH__V3*/ meltfptr[2] =
            (melt_multiple_nth((melt_ptr_t)(/*_.EL__V2*/ meltfptr[1]), (0)));;
        MELT_LOCATION("warmelt-base.melt:3856:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.MULTIPLE_NTH__V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3856:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.MULTIPLE_NTH__V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LAMBDA_cl3", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_41_WARMELTmiBASE_LAMBDA_cl3_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_41_WARMELTmiBASE_LAMBDA_cl3*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_42_WARMELTmiBASE_JSON_NAME_LESS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_42_WARMELTmiBASE_JSON_NAME_LESS fromline 1752 */

    /** start of frame for meltrout_42_WARMELTmiBASE_JSON_NAME_LESS of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS// fromline 1568
        : public Melt_CallFrameWithValues<18>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[9];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<18> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS), clos) {};
        MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS() //the constructor fromline 1642
            : Melt_CallFrameWithValues<18> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<18> (fil,lin, sizeof(MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS)) {};
        MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<18> (fil,lin, sizeof(MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS


    /** end of frame for meltrout_42_WARMELTmiBASE_JSON_NAME_LESS fromline 1697**/

    /* end of frame for routine meltrout_42_WARMELTmiBASE_JSON_NAME_LESS fromline 1756 */

    /* classy proc frame meltrout_42_WARMELTmiBASE_JSON_NAME_LESS */
    MeltFrame_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_42_WARMELTmiBASE_JSON_NAME_LESS fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("JSON_NAME_LESS", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3863:/ getarg");
    /*_.LV__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.RV__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-base.melt:3865:/ quasiblock");


        /*_#NONSTRING__L1*/
        meltfnum[0] = 0;;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_STRING__L2*/
        meltfnum[1] =
            (melt_magic_discr((melt_ptr_t)(/*_.LV__V2*/ meltfptr[1])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-base.melt:3867:/ cond");
        /*cond*/
        if (/*_#IS_STRING__L2*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*_.LNAME__V5*/ meltfptr[4] = /*_.LV__V2*/ meltfptr[1];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3867:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L3*/
                    meltfnum[2] =
                        melt_is_instance_of((melt_ptr_t)(/*_.LV__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])));;
                    MELT_LOCATION("warmelt-base.melt:3868:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L3*/ meltfnum[2]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3869:/ compute");
                                /*_#NONSTRING__L1*/
                                meltfnum[0] = /*_#SETQ___L4*/ meltfnum[3] = 1;;
                                MELT_LOCATION("warmelt-base.melt:3870:/ cond");
                                /*cond*/
                                if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.LV__V2*/ meltfptr[1]),
                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.LV__V2*/ meltfptr[1]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                            /*_.NAMED_NAME__V7*/
                                            meltfptr[6] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.NAMED_NAME__V7*/ meltfptr[6] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                MELT_LOCATION("warmelt-base.melt:3868:/ quasiblock");


                                /*_.PROGN___V8*/
                                meltfptr[7] = /*_.NAMED_NAME__V7*/ meltfptr[6];;
                                /*^compute*/
                                /*_._IFELSE___V6*/
                                meltfptr[5] = /*_.PROGN___V8*/ meltfptr[7];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3868:/ clear");
                                /*clear*/ /*_#SETQ___L4*/
                                meltfnum[3] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.NAMED_NAME__V7*/
                                meltfptr[6] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V8*/
                                meltfptr[7] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.LNAME__V5*/
                    meltfptr[4] = /*_._IFELSE___V6*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3867:/ clear");
                    /*clear*/ /*_#IS_A__L3*/
                    meltfnum[2] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V6*/
                    meltfptr[5] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_STRING__L5*/
        meltfnum[3] =
            (melt_magic_discr((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-base.melt:3871:/ cond");
        /*cond*/
        if (/*_#IS_STRING__L5*/ meltfnum[3]) /*then*/
            {
                /*^cond.then*/
                /*_.RNAME__V9*/ meltfptr[6] = /*_.RV__V3*/ meltfptr[2];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3871:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L6*/
                    meltfnum[2] =
                        melt_is_instance_of((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])));;
                    MELT_LOCATION("warmelt-base.melt:3872:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L6*/ meltfnum[2]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3873:/ compute");
                                /*_#NONSTRING__L1*/
                                meltfnum[0] = /*_#SETQ___L7*/ meltfnum[6] = 1;;
                                MELT_LOCATION("warmelt-base.melt:3874:/ cond");
                                /*cond*/
                                if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2]),
                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.RV__V3*/ meltfptr[2]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                            /*_.NAMED_NAME__V11*/
                                            meltfptr[5] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.NAMED_NAME__V11*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                MELT_LOCATION("warmelt-base.melt:3872:/ quasiblock");


                                /*_.PROGN___V12*/
                                meltfptr[11] = /*_.NAMED_NAME__V11*/ meltfptr[5];;
                                /*^compute*/
                                /*_._IFELSE___V10*/
                                meltfptr[7] = /*_.PROGN___V12*/ meltfptr[11];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3872:/ clear");
                                /*clear*/ /*_#SETQ___L7*/
                                meltfnum[6] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.NAMED_NAME__V11*/
                                meltfptr[5] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V12*/
                                meltfptr[11] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V10*/ meltfptr[7] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.RNAME__V9*/
                    meltfptr[6] = /*_._IFELSE___V10*/ meltfptr[7];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3871:/ clear");
                    /*clear*/ /*_#IS_A__L6*/
                    meltfnum[2] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V10*/
                    meltfptr[7] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3876:/ cond");
        /*cond*/
        if (/*_#NONSTRING__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#STRINGltCASE__L8*/
                    meltfnum[6] =
                        melt_string_less((melt_ptr_t)(/*_.LNAME__V5*/ meltfptr[4]), (melt_ptr_t)(/*_.RNAME__V9*/ meltfptr[6]));;
                    MELT_LOCATION("warmelt-base.melt:3877:/ cond");
                    /*cond*/
                    if (/*_#STRINGltCASE__L8*/ meltfnum[6]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*^quasiblock*/


                                /*_._RETVAL___V1*/
                                meltfptr[0] = (/*!konst_1_TRUE*/ meltfrout->tabval[1]);;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3877:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                /*_._IF___V14*/
                                meltfptr[11] = /*_.RETURN___V15*/ meltfptr[7];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3877:/ clear");
                                /*clear*/ /*_.RETURN___V15*/
                                meltfptr[7] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V14*/ meltfptr[11] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_._IFELSE___V13*/
                    meltfptr[5] = /*_._IF___V14*/ meltfptr[11];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3876:/ clear");
                    /*clear*/ /*_#STRINGltCASE__L8*/
                    meltfnum[6] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IF___V14*/
                    meltfptr[11] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#STRINGlt__L9*/
                    meltfnum[2] =
                        melt_string_less((melt_ptr_t)(/*_.LNAME__V5*/ meltfptr[4]), (melt_ptr_t)(/*_.RNAME__V9*/ meltfptr[6]));;
                    MELT_LOCATION("warmelt-base.melt:3878:/ cond");
                    /*cond*/
                    if (/*_#STRINGlt__L9*/ meltfnum[2]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*^quasiblock*/


                                /*_._RETVAL___V1*/
                                meltfptr[0] = (/*!konst_1_TRUE*/ meltfrout->tabval[1]);;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3878:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                /*_._IF___V16*/
                                meltfptr[7] = /*_.RETURN___V17*/ meltfptr[11];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3878:/ clear");
                                /*clear*/ /*_.RETURN___V17*/
                                meltfptr[11] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V16*/ meltfptr[7] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_._IFELSE___V13*/
                    meltfptr[5] = /*_._IF___V16*/ meltfptr[7];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3876:/ clear");
                    /*clear*/ /*_#STRINGlt__L9*/
                    meltfnum[2] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IF___V16*/
                    meltfptr[7] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3879:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = (/*nil*/NULL);;

        {
            MELT_LOCATION("warmelt-base.melt:3879:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V4*/
        meltfptr[3] = /*_.RETURN___V18*/ meltfptr[11];;

        MELT_LOCATION("warmelt-base.melt:3865:/ clear");
        /*clear*/ /*_#NONSTRING__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L2*/
        meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LNAME__V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L5*/
        meltfnum[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RNAME__V9*/
        meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V13*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V18*/
        meltfptr[11] = 0 ;
        MELT_LOCATION("warmelt-base.melt:3863:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V4*/ meltfptr[3];;

        {
            MELT_LOCATION("warmelt-base.melt:3863:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V4*/
        meltfptr[3] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("JSON_NAME_LESS", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_42_WARMELTmiBASE_JSON_NAME_LESS_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_42_WARMELTmiBASE_JSON_NAME_LESS*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL fromline 1752 */

    /** start of frame for meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL// fromline 1568
        : public Melt_CallFrameWithValues<20>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[10];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<20> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL), clos) {};
        MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL() //the constructor fromline 1642
            : Melt_CallFrameWithValues<20> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<20> (fil,lin, sizeof(MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL)) {};
        MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<20> (fil,lin, sizeof(MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL


    /** end of frame for meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL fromline 1697**/

    /* end of frame for routine meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL fromline 1756 */

    /* classy proc frame meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL */
    MeltFrame_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("JSON_NAME_EQUAL", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3882:/ getarg");
    /*_.LV__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.RV__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#eqeq__L1*/
        meltfnum[0] =
            ((/*_.LV__V2*/ meltfptr[1]) == (/*_.RV__V3*/ meltfptr[2]));;
        MELT_LOCATION("warmelt-base.melt:3884:/ cond");
        /*cond*/
        if (/*_#eqeq__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*^quasiblock*/


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*!konst_0_TRUE*/ meltfrout->tabval[0]);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3884:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IF___V4*/
                    meltfptr[3] = /*_.RETURN___V5*/ meltfptr[4];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3884:/ clear");
                    /*clear*/ /*_.RETURN___V5*/
                    meltfptr[4] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V4*/ meltfptr[3] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3885:/ quasiblock");


        /*_#NONSTRING__L2*/
        meltfnum[1] = 0;;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_STRING__L3*/
        meltfnum[2] =
            (melt_magic_discr((melt_ptr_t)(/*_.LV__V2*/ meltfptr[1])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-base.melt:3887:/ cond");
        /*cond*/
        if (/*_#IS_STRING__L3*/ meltfnum[2]) /*then*/
            {
                /*^cond.then*/
                /*_.LNAME__V7*/ meltfptr[6] = /*_.LV__V2*/ meltfptr[1];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3887:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L4*/
                    meltfnum[3] =
                        melt_is_instance_of((melt_ptr_t)(/*_.LV__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])));;
                    MELT_LOCATION("warmelt-base.melt:3888:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L4*/ meltfnum[3]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3889:/ compute");
                                /*_#NONSTRING__L2*/
                                meltfnum[1] = /*_#SETQ___L5*/ meltfnum[4] = 1;;
                                MELT_LOCATION("warmelt-base.melt:3890:/ cond");
                                /*cond*/
                                if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.LV__V2*/ meltfptr[1]),
                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.LV__V2*/ meltfptr[1]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                            /*_.NAMED_NAME__V9*/
                                            meltfptr[8] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.NAMED_NAME__V9*/ meltfptr[8] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                MELT_LOCATION("warmelt-base.melt:3888:/ quasiblock");


                                /*_.PROGN___V10*/
                                meltfptr[9] = /*_.NAMED_NAME__V9*/ meltfptr[8];;
                                /*^compute*/
                                /*_._IFELSE___V8*/
                                meltfptr[7] = /*_.PROGN___V10*/ meltfptr[9];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3888:/ clear");
                                /*clear*/ /*_#SETQ___L5*/
                                meltfnum[4] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.NAMED_NAME__V9*/
                                meltfptr[8] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V10*/
                                meltfptr[9] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V8*/ meltfptr[7] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.LNAME__V7*/
                    meltfptr[6] = /*_._IFELSE___V8*/ meltfptr[7];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3887:/ clear");
                    /*clear*/ /*_#IS_A__L4*/
                    meltfnum[3] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V8*/
                    meltfptr[7] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_STRING__L6*/
        meltfnum[4] =
            (melt_magic_discr((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-base.melt:3891:/ cond");
        /*cond*/
        if (/*_#IS_STRING__L6*/ meltfnum[4]) /*then*/
            {
                /*^cond.then*/
                /*_.RNAME__V11*/ meltfptr[8] = /*_.RV__V3*/ meltfptr[2];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3891:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L7*/
                    meltfnum[3] =
                        melt_is_instance_of((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])));;
                    MELT_LOCATION("warmelt-base.melt:3892:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L7*/ meltfnum[3]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:3893:/ compute");
                                /*_#NONSTRING__L2*/
                                meltfnum[1] = /*_#SETQ___L8*/ meltfnum[7] = 1;;
                                MELT_LOCATION("warmelt-base.melt:3894:/ cond");
                                /*cond*/
                                if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.RV__V3*/ meltfptr[2]),
                                                                  (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.RV__V3*/ meltfptr[2]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                            /*_.NAMED_NAME__V13*/
                                            meltfptr[7] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.NAMED_NAME__V13*/ meltfptr[7] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                MELT_LOCATION("warmelt-base.melt:3892:/ quasiblock");


                                /*_.PROGN___V14*/
                                meltfptr[13] = /*_.NAMED_NAME__V13*/ meltfptr[7];;
                                /*^compute*/
                                /*_._IFELSE___V12*/
                                meltfptr[9] = /*_.PROGN___V14*/ meltfptr[13];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3892:/ clear");
                                /*clear*/ /*_#SETQ___L8*/
                                meltfnum[7] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.NAMED_NAME__V13*/
                                meltfptr[7] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V14*/
                                meltfptr[13] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V12*/ meltfptr[9] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.RNAME__V11*/
                    meltfptr[8] = /*_._IFELSE___V12*/ meltfptr[9];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3891:/ clear");
                    /*clear*/ /*_#IS_A__L7*/
                    meltfnum[3] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V12*/
                    meltfptr[9] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3896:/ cond");
        /*cond*/
        if (/*_#NONSTRING__L2*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#eqeqSmiCASE__L9*/
                    meltfnum[7] =
                        melt_string_same_case((melt_ptr_t)(/*_.LNAME__V7*/ meltfptr[6]), (melt_ptr_t)(/*_.RNAME__V11*/ meltfptr[8]));;
                    MELT_LOCATION("warmelt-base.melt:3897:/ cond");
                    /*cond*/
                    if (/*_#eqeqSmiCASE__L9*/ meltfnum[7]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*^quasiblock*/


                                /*_._RETVAL___V1*/
                                meltfptr[0] = (/*!konst_0_TRUE*/ meltfrout->tabval[0]);;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3897:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                /*_._IF___V16*/
                                meltfptr[13] = /*_.RETURN___V17*/ meltfptr[9];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3897:/ clear");
                                /*clear*/ /*_.RETURN___V17*/
                                meltfptr[9] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V16*/ meltfptr[13] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_._IFELSE___V15*/
                    meltfptr[7] = /*_._IF___V16*/ meltfptr[13];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3896:/ clear");
                    /*clear*/ /*_#eqeqSmiCASE__L9*/
                    meltfnum[7] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IF___V16*/
                    meltfptr[13] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#eqeqS__L10*/
                    meltfnum[3] =
                        melt_string_same((melt_ptr_t)(/*_.LNAME__V7*/ meltfptr[6]), (melt_ptr_t)(/*_.RNAME__V11*/ meltfptr[8]));;
                    MELT_LOCATION("warmelt-base.melt:3898:/ cond");
                    /*cond*/
                    if (/*_#eqeqS__L10*/ meltfnum[3]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*^quasiblock*/


                                /*_._RETVAL___V1*/
                                meltfptr[0] = (/*!konst_0_TRUE*/ meltfrout->tabval[0]);;

                                {
                                    MELT_LOCATION("warmelt-base.melt:3898:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                /*_._IF___V18*/
                                meltfptr[9] = /*_.RETURN___V19*/ meltfptr[13];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3898:/ clear");
                                /*clear*/ /*_.RETURN___V19*/
                                meltfptr[13] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V18*/ meltfptr[9] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_._IFELSE___V15*/
                    meltfptr[7] = /*_._IF___V18*/ meltfptr[9];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3896:/ clear");
                    /*clear*/ /*_#eqeqS__L10*/
                    meltfnum[3] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IF___V18*/
                    meltfptr[9] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3899:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = (/*nil*/NULL);;

        {
            MELT_LOCATION("warmelt-base.melt:3899:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V6*/
        meltfptr[4] = /*_.RETURN___V20*/ meltfptr[13];;

        MELT_LOCATION("warmelt-base.melt:3885:/ clear");
        /*clear*/ /*_#NONSTRING__L2*/
        meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L3*/
        meltfnum[2] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LNAME__V7*/
        meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L6*/
        meltfnum[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RNAME__V11*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V15*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V20*/
        meltfptr[13] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3882:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V6*/ meltfptr[4];;

        {
            MELT_LOCATION("warmelt-base.melt:3882:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#eqeq__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V6*/
        meltfptr[4] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("JSON_NAME_EQUAL", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_43_WARMELTmiBASE_JSON_NAME_EQUAL*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME fromline 1752 */

    /** start of frame for meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME// fromline 1568
        : public Melt_CallFrameWithValues<24>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[10];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<24> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME), clos) {};
        MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME() //the constructor fromline 1642
            : Melt_CallFrameWithValues<24> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<24> (fil,lin, sizeof(MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME)) {};
        MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<24> (fil,lin, sizeof(MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME


    /** end of frame for meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME fromline 1697**/

    /* end of frame for routine meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME fromline 1756 */

    /* classy proc frame meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME */
    MeltFrame_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("JSON_CANONICAL_NAME", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3903:/ getarg");
    /*_.N__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_STRINGCONST__L1*/
        meltfnum[0] =
            (melt_is_string_const((melt_ptr_t)(/*_.N__V2*/ meltfptr[1]), ( "json_false")));;
        MELT_LOCATION("warmelt-base.melt:3909:/ cond");
        /*cond*/
        if (/*_#IS_STRINGCONST__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*_._IFELSE___V3*/ meltfptr[2] = /*_.N__V2*/ meltfptr[1];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:3909:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_STRINGCONST__L2*/
                    meltfnum[1] =
                        (melt_is_string_const((melt_ptr_t)(/*_.N__V2*/ meltfptr[1]), ( "true")));;
                    MELT_LOCATION("warmelt-base.melt:3911:/ cond");
                    /*cond*/
                    if (/*_#IS_STRINGCONST__L2*/ meltfnum[1]) /*then*/
                        {
                            /*^cond.then*/
                            /*_._IFELSE___V4*/ meltfptr[3] = /*_.N__V2*/ meltfptr[1];;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-base.melt:3911:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_STRINGCONST__L3*/
                                meltfnum[2] =
                                    (melt_is_string_const((melt_ptr_t)(/*_.N__V2*/ meltfptr[1]), ( "null")));;
                                MELT_LOCATION("warmelt-base.melt:3913:/ cond");
                                /*cond*/
                                if (/*_#IS_STRINGCONST__L3*/ meltfnum[2]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*_._IFELSE___V5*/ meltfptr[4] = /*_.N__V2*/ meltfptr[1];;
                                    }
                                else
                                    {
                                        MELT_LOCATION("warmelt-base.melt:3913:/ cond.else");

                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*_#IS_STRING__L4*/
                                            meltfnum[3] =
                                                (melt_magic_discr((melt_ptr_t)(/*_.N__V2*/ meltfptr[1])) == MELTOBMAG_STRING);;
                                            MELT_LOCATION("warmelt-base.melt:3916:/ cond");
                                            /*cond*/
                                            if (/*_#IS_STRING__L4*/ meltfnum[3]) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^block*/
                                                    /*anyblock*/
                                                    {

                                                        MELT_LOCATION("warmelt-base.melt:3917:/ quasiblock");


                                                        /*_#NAMLEN__L5*/
                                                        meltfnum[4] =
                                                            melt_string_length((melt_ptr_t)(/*_.N__V2*/ meltfptr[1]));;
                                                        /*^compute*/
                                                        /*_.GET_SYMBOLSTR__V8*/
                                                        meltfptr[7] =
                                                            melthookproc_HOOK_NAMED_SYMBOL (melt_string_str((melt_ptr_t)(/*_.N__V2*/ meltfptr[1])), (long)MELT_GET);;
                                                        MELT_LOCATION("warmelt-base.melt:3918:/ cond");
                                                        /*cond*/
                                                        if (/*_.GET_SYMBOLSTR__V8*/ meltfptr[7]) /*then*/
                                                            {
                                                                /*^cond.then*/
                                                                /*_.NAMED__V9*/ meltfptr[8] = /*_.GET_SYMBOLSTR__V8*/ meltfptr[7];;
                                                            }
                                                        else
                                                            {
                                                                MELT_LOCATION("warmelt-base.melt:3918:/ cond.else");

                                                                /*^block*/
                                                                /*anyblock*/
                                                                {

                                                                    /*_.GET_KEYWORDSTR__V10*/ meltfptr[9] =
                                                                        melthookproc_HOOK_NAMED_KEYWORD (melt_string_str((melt_ptr_t)(/*_.N__V2*/ meltfptr[1])), (long) MELT_GET);;
                                                                    /*^compute*/
                                                                    /*_.NAMED__V9*/
                                                                    meltfptr[8] = /*_.GET_KEYWORDSTR__V10*/ meltfptr[9];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-base.melt:3918:/ clear");
                                                                    /*clear*/ /*_.GET_KEYWORDSTR__V10*/
                                                                    meltfptr[9] = 0 ;
                                                                }
                                                                ;
                                                            }
                                                        ;
                                                        /*_#BAD__L6*/
                                                        meltfnum[5] =
                                                            (/*null*/(/*_.NAMED__V9*/ meltfptr[8]) == NULL);;
                                                        MELT_LOCATION("warmelt-base.melt:3920:/ cond");
                                                        /*cond*/
                                                        if (
                                                            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.NAMED__V9*/ meltfptr[8]),
                                                                                          (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])))
                                                        ) /*then*/
                                                            {
                                                                /*^cond.then*/
                                                                /*^getslot*/
                                                                {
                                                                    melt_ptr_t slot=NULL, obj=NULL;
                                                                    obj = (melt_ptr_t)(/*_.NAMED__V9*/ meltfptr[8]) /*=obj*/;
                                                                    melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                                    /*_.NAMSTR__V11*/
                                                                    meltfptr[9] = slot;
                                                                };
                                                                ;
                                                            }
                                                        else    /*^cond.else*/
                                                            {

                                                                /*_.NAMSTR__V11*/ meltfptr[9] =  /*reallynil*/ NULL ;;
                                                            }
                                                        ;

                                                        MELT_CHECK_SIGNAL();
                                                        ;
                                                        /*^compute*/
                                                        /*_#IS_STRING__L7*/
                                                        meltfnum[6] =
                                                            (melt_magic_discr((melt_ptr_t)(/*_.NAMSTR__V11*/ meltfptr[9])) == MELTOBMAG_STRING);;
                                                        MELT_LOCATION("warmelt-base.melt:3923:/ cond");
                                                        /*cond*/
                                                        if (/*_#IS_STRING__L7*/ meltfnum[6]) /*then*/
                                                            {
                                                                /*^cond.then*/
                                                                /*^block*/
                                                                /*anyblock*/
                                                                {


#if MELT_HAVE_DEBUG
                                                                    MELT_LOCATION("warmelt-base.melt:3924:/ cppif.then");
                                                                    /*^block*/
                                                                    /*anyblock*/
                                                                    {


                                                                        MELT_CHECK_SIGNAL();
                                                                        ;
                                                                        /*_#STRING_LENGTH__L8*/
                                                                        meltfnum[7] =
                                                                            melt_string_length((melt_ptr_t)(/*_.NAMSTR__V11*/ meltfptr[9]));;
                                                                        /*^compute*/
                                                                        /*_#eqeqI__L9*/
                                                                        meltfnum[8] =
                                                                            ((/*_#STRING_LENGTH__L8*/ meltfnum[7]) == (/*_#NAMLEN__L5*/ meltfnum[4]));;
                                                                        MELT_LOCATION("warmelt-base.melt:3924:/ cond");
                                                                        /*cond*/
                                                                        if (/*_#eqeqI__L9*/ meltfnum[8]) /*then*/
                                                                            {
                                                                                /*^cond.then*/
                                                                                /*_._IFELSE___V14*/ meltfptr[13] = (/*nil*/NULL);;
                                                                            }
                                                                        else
                                                                            {
                                                                                MELT_LOCATION("warmelt-base.melt:3924:/ cond.else");

                                                                                /*^block*/
                                                                                /*anyblock*/
                                                                                {


                                                                                    MELT_CHECK_SIGNAL();
                                                                                    ;
                                                                                    /*^apply*/
                                                                                    /*apply*/
                                                                                    {
                                                                                        union meltparam_un argtab[5];
                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                        /*^apply.arg*/
                                                                                        argtab[0].meltbp_cstring =  "check namestrlen";
                                                                                        /*^apply.arg*/
                                                                                        argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                                                                        /*^apply.arg*/
                                                                                        argtab[2].meltbp_long = 3924;
                                                                                        /*^apply.arg*/
                                                                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.NAMSTR__V11*/ meltfptr[9];
                                                                                        /*^apply.arg*/
                                                                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.N__V2*/ meltfptr[1];
                                                                                        /*_.MELT_ASSERT_FAILURE_FUN__V15*/
                                                                                        meltfptr[14] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                    }
                                                                                    ;
                                                                                    /*_._IFELSE___V14*/
                                                                                    meltfptr[13] = /*_.MELT_ASSERT_FAILURE_FUN__V15*/ meltfptr[14];;
                                                                                    /*epilog*/

                                                                                    MELT_LOCATION("warmelt-base.melt:3924:/ clear");
                                                                                    /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V15*/
                                                                                    meltfptr[14] = 0 ;
                                                                                }
                                                                                ;
                                                                            }
                                                                        ;
                                                                        /*_.IFCPP___V13*/
                                                                        meltfptr[12] = /*_._IFELSE___V14*/ meltfptr[13];;
                                                                        /*epilog*/

                                                                        MELT_LOCATION("warmelt-base.melt:3924:/ clear");
                                                                        /*clear*/ /*_#STRING_LENGTH__L8*/
                                                                        meltfnum[7] = 0 ;
                                                                        /*^clear*/
                                                                        /*clear*/ /*_#eqeqI__L9*/
                                                                        meltfnum[8] = 0 ;
                                                                        /*^clear*/
                                                                        /*clear*/ /*_._IFELSE___V14*/
                                                                        meltfptr[13] = 0 ;
                                                                    }

#else /*MELT_HAVE_DEBUG*/
                                                                    /*^cppif.else*/
                                                                    /*_.IFCPP___V13*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                                                                    ;

                                                                    {
                                                                        MELT_LOCATION("warmelt-base.melt:3925:/ locexp");
                                                                        /* json_canonical_name COMPAREUPCASE_CHK__1 */
                                                                        const char* ncstr = melt_string_str(/*_.N__V2*/ meltfptr[1]);
                                                                        const char* namcstr = melt_string_str(/*_.NAMSTR__V11*/ meltfptr[9]);
                                                                        gcc_assert (ncstr != NULL);
                                                                        gcc_assert (namcstr != NULL);
                                                                        unsigned nlen = (unsigned)/*_#NAMLEN__L5*/ meltfnum[4];
                                                                        for (unsigned ix=0;
                                                                                ix<nlen && !/*_#BAD__L6*/ meltfnum[5];
                                                                                ix++)
                                                                            {
                                                                                char nc = ncstr[ix];
                                                                                char namc = namcstr[ix];
                                                                                if (ISUPPER(nc))
                                                                                    /*_#BAD__L6*/ meltfnum[5] = 1;
                                                                                else if (ISALPHA(nc) && ISALPHA(namc))
                                                                                    /*_#BAD__L6*/ meltfnum[5] = TOUPPER(nc) != namc;
                                                                                else
                                                                                    /*_#BAD__L6*/ meltfnum[5] = nc != namc;
                                                                            }; // end for ix
                                                                        /* end json_canonical_name COMPAREUPCASE_CHK__1 */;
                                                                    }
                                                                    ;

                                                                    MELT_CHECK_SIGNAL();
                                                                    ;
                                                                    MELT_LOCATION("warmelt-base.melt:3947:/ cond");
                                                                    /*cond*/
                                                                    if (/*_#BAD__L6*/ meltfnum[5]) /*then*/
                                                                        {
                                                                            /*^cond.then*/
                                                                            /*^block*/
                                                                            /*anyblock*/
                                                                            {


                                                                                MELT_CHECK_SIGNAL();
                                                                                ;
                                                                                /*^quasiblock*/


                                                                                /*_._RETVAL___V1*/
                                                                                meltfptr[0] = /*_.N__V2*/ meltfptr[1];;

                                                                                {
                                                                                    MELT_LOCATION("warmelt-base.melt:3947:/ locexp");
                                                                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                                                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                                                                        melt_warn_for_no_expected_secondary_results();
                                                                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                                                                    ;
                                                                                }
                                                                                ;
                                                                                /*^finalreturn*/
                                                                                ;
                                                                                /*finalret*/
                                                                                goto meltlabend_rout ;
                                                                                /*_._IFELSE___V16*/
                                                                                meltfptr[14] = /*_.RETURN___V17*/ meltfptr[13];;
                                                                                /*epilog*/

                                                                                MELT_LOCATION("warmelt-base.melt:3947:/ clear");
                                                                                /*clear*/ /*_.RETURN___V17*/
                                                                                meltfptr[13] = 0 ;
                                                                            }
                                                                            ;
                                                                        }
                                                                    else    /*^cond.else*/
                                                                        {

                                                                            /*^block*/
                                                                            /*anyblock*/
                                                                            {


                                                                                MELT_CHECK_SIGNAL();
                                                                                ;
                                                                                /*^quasiblock*/


                                                                                /*_._RETVAL___V1*/
                                                                                meltfptr[0] = /*_.NAMED__V9*/ meltfptr[8];;

                                                                                {
                                                                                    MELT_LOCATION("warmelt-base.melt:3947:/ locexp");
                                                                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                                                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                                                                        melt_warn_for_no_expected_secondary_results();
                                                                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                                                                    ;
                                                                                }
                                                                                ;
                                                                                /*^finalreturn*/
                                                                                ;
                                                                                /*finalret*/
                                                                                goto meltlabend_rout ;
                                                                                /*_._IFELSE___V16*/
                                                                                meltfptr[14] = /*_.RETURN___V18*/ meltfptr[13];;
                                                                                /*epilog*/

                                                                                MELT_LOCATION("warmelt-base.melt:3947:/ clear");
                                                                                /*clear*/ /*_.RETURN___V18*/
                                                                                meltfptr[13] = 0 ;
                                                                            }
                                                                            ;
                                                                        }
                                                                    ;
                                                                    MELT_LOCATION("warmelt-base.melt:3923:/ quasiblock");


                                                                    /*_.PROGN___V19*/
                                                                    meltfptr[13] = /*_._IFELSE___V16*/ meltfptr[14];;
                                                                    /*^compute*/
                                                                    /*_._IFELSE___V12*/
                                                                    meltfptr[11] = /*_.PROGN___V19*/ meltfptr[13];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-base.melt:3923:/ clear");
                                                                    /*clear*/ /*_.IFCPP___V13*/
                                                                    meltfptr[12] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_._IFELSE___V16*/
                                                                    meltfptr[14] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.PROGN___V19*/
                                                                    meltfptr[13] = 0 ;
                                                                }
                                                                ;
                                                            }
                                                        else    /*^cond.else*/
                                                            {

                                                                /*^block*/
                                                                /*anyblock*/
                                                                {


                                                                    MELT_CHECK_SIGNAL();
                                                                    ;
                                                                    MELT_LOCATION("warmelt-base.melt:3950:/ quasiblock");


                                                                    /*_._RETVAL___V1*/
                                                                    meltfptr[0] = /*_.N__V2*/ meltfptr[1];;

                                                                    {
                                                                        MELT_LOCATION("warmelt-base.melt:3950:/ locexp");
                                                                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                                                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                                                            melt_warn_for_no_expected_secondary_results();
                                                                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                                                        ;
                                                                    }
                                                                    ;
                                                                    /*^finalreturn*/
                                                                    ;
                                                                    /*finalret*/
                                                                    goto meltlabend_rout ;
                                                                    MELT_LOCATION("warmelt-base.melt:3949:/ quasiblock");


                                                                    /*_.PROGN___V21*/
                                                                    meltfptr[14] = /*_.RETURN___V20*/ meltfptr[12];;
                                                                    /*^compute*/
                                                                    /*_._IFELSE___V12*/
                                                                    meltfptr[11] = /*_.PROGN___V21*/ meltfptr[14];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-base.melt:3923:/ clear");
                                                                    /*clear*/ /*_.RETURN___V20*/
                                                                    meltfptr[12] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.PROGN___V21*/
                                                                    meltfptr[14] = 0 ;
                                                                }
                                                                ;
                                                            }
                                                        ;
                                                        /*_.LET___V7*/
                                                        meltfptr[6] = /*_._IFELSE___V12*/ meltfptr[11];;

                                                        MELT_LOCATION("warmelt-base.melt:3917:/ clear");
                                                        /*clear*/ /*_#NAMLEN__L5*/
                                                        meltfnum[4] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_.GET_SYMBOLSTR__V8*/
                                                        meltfptr[7] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_.NAMED__V9*/
                                                        meltfptr[8] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_#BAD__L6*/
                                                        meltfnum[5] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_.NAMSTR__V11*/
                                                        meltfptr[9] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_#IS_STRING__L7*/
                                                        meltfnum[6] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_._IFELSE___V12*/
                                                        meltfptr[11] = 0 ;
                                                        /*_._IFELSE___V6*/
                                                        meltfptr[5] = /*_.LET___V7*/ meltfptr[6];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-base.melt:3916:/ clear");
                                                        /*clear*/ /*_.LET___V7*/
                                                        meltfptr[6] = 0 ;
                                                    }
                                                    ;
                                                }
                                            else    /*^cond.else*/
                                                {

                                                    /*^block*/
                                                    /*anyblock*/
                                                    {


                                                        MELT_CHECK_SIGNAL();
                                                        ;
                                                        /*_#IS_A__L10*/
                                                        meltfnum[7] =
                                                            melt_is_instance_of((melt_ptr_t)(/*_.N__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])));;
                                                        MELT_LOCATION("warmelt-base.melt:3953:/ cond");
                                                        /*cond*/
                                                        if (/*_#IS_A__L10*/ meltfnum[7]) /*then*/
                                                            {
                                                                /*^cond.then*/
                                                                /*_._IFELSE___V22*/ meltfptr[13] = /*_.N__V2*/ meltfptr[1];;
                                                            }
                                                        else
                                                            {
                                                                MELT_LOCATION("warmelt-base.melt:3953:/ cond.else");

                                                                /*^block*/
                                                                /*anyblock*/
                                                                {


                                                                    MELT_CHECK_SIGNAL();
                                                                    ;
                                                                    MELT_LOCATION("warmelt-base.melt:3956:/ quasiblock");


                                                                    /*_._RETVAL___V1*/
                                                                    meltfptr[0] = (/*nil*/NULL);;

                                                                    {
                                                                        MELT_LOCATION("warmelt-base.melt:3956:/ locexp");
                                                                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                                                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                                                            melt_warn_for_no_expected_secondary_results();
                                                                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                                                        ;
                                                                    }
                                                                    ;
                                                                    /*^finalreturn*/
                                                                    ;
                                                                    /*finalret*/
                                                                    goto meltlabend_rout ;
                                                                    MELT_LOCATION("warmelt-base.melt:3955:/ quasiblock");


                                                                    /*_.PROGN___V24*/
                                                                    meltfptr[14] = /*_.RETURN___V23*/ meltfptr[12];;
                                                                    /*^compute*/
                                                                    /*_._IFELSE___V22*/
                                                                    meltfptr[13] = /*_.PROGN___V24*/ meltfptr[14];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-base.melt:3953:/ clear");
                                                                    /*clear*/ /*_.RETURN___V23*/
                                                                    meltfptr[12] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.PROGN___V24*/
                                                                    meltfptr[14] = 0 ;
                                                                }
                                                                ;
                                                            }
                                                        ;
                                                        /*_._IFELSE___V6*/
                                                        meltfptr[5] = /*_._IFELSE___V22*/ meltfptr[13];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-base.melt:3916:/ clear");
                                                        /*clear*/ /*_#IS_A__L10*/
                                                        meltfnum[7] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_._IFELSE___V22*/
                                                        meltfptr[13] = 0 ;
                                                    }
                                                    ;
                                                }
                                            ;
                                            /*_._IFELSE___V5*/
                                            meltfptr[4] = /*_._IFELSE___V6*/ meltfptr[5];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:3913:/ clear");
                                            /*clear*/ /*_#IS_STRING__L4*/
                                            meltfnum[3] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_._IFELSE___V6*/
                                            meltfptr[5] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V4*/
                                meltfptr[3] = /*_._IFELSE___V5*/ meltfptr[4];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:3911:/ clear");
                                /*clear*/ /*_#IS_STRINGCONST__L3*/
                                meltfnum[2] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V5*/
                                meltfptr[4] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_._IFELSE___V3*/
                    meltfptr[2] = /*_._IFELSE___V4*/ meltfptr[3];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3909:/ clear");
                    /*clear*/ /*_#IS_STRINGCONST__L2*/
                    meltfnum[1] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V4*/
                    meltfptr[3] = 0 ;
                }
                ;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3903:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_._IFELSE___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-base.melt:3903:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#IS_STRINGCONST__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V3*/
        meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("JSON_CANONICAL_NAME", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_44_WARMELTmiBASE_JSON_CANONICAL_NAME*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    /*variadic*/ int variad_MAKE_JSONOBJECT_ix = 0, variad_MAKE_JSONOBJECT_len = melt_argdescr_length (meltxargdescr_);
#define melt_variadic_length  (0+variad_MAKE_JSONOBJECT_len)
#define melt_variadic_index variad_MAKE_JSONOBJECT_ix

    long current_blocklevel_signals_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT fromline 1752 */

    /** start of frame for meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT// fromline 1568
        : public Melt_CallFrameWithValues<100>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[33];
        /*classy others*/
        const char* loc_CSTRING__o0;
        const char* loc_CSTRING__o1;
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<100> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT), clos) {};
        MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT() //the constructor fromline 1642
            : Melt_CallFrameWithValues<100> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<100> (fil,lin, sizeof(MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT)) {};
        MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<100> (fil,lin, sizeof(MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT


    /** end of frame for meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT fromline 1697**/

    /* end of frame for routine meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT fromline 1756 */

    /* classy proc frame meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT */
    MeltFrame_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MAKE_JSONOBJECT", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:3959:/ getarg");
    /*_.DIS__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#NULL__L1*/
        meltfnum[0] =
            (/*null*/(/*_.DIS__V2*/ meltfptr[1]) == NULL);;
        MELT_LOCATION("warmelt-base.melt:3965:/ cond");
        /*cond*/
        if (/*_#NULL__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^compute*/
                    /*_.DIS__V2*/ meltfptr[1] = /*_.SETQ___V4*/ meltfptr[3] = (/*!DISCR_JSONOBJECT*/ meltfrout->tabval[0]);;
                    /*_._IF___V3*/
                    meltfptr[2] = /*_.SETQ___V4*/ meltfptr[3];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3965:/ clear");
                    /*clear*/ /*_.SETQ___V4*/
                    meltfptr[3] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V3*/ meltfptr[2] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_NOT_A__L2*/
        meltfnum[1] =
            !melt_is_instance_of((melt_ptr_t)(/*_.DIS__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_DISCRIMINANT*/ meltfrout->tabval[1])));;
        MELT_LOCATION("warmelt-base.melt:3966:/ cond");
        /*cond*/
        if (/*_#IS_NOT_A__L2*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3967:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3967:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    MELT_LOCATION("warmelt-base.melt:3966:/ quasiblock");


                    /*_.PROGN___V7*/
                    meltfptr[6] = /*_.RETURN___V6*/ meltfptr[5];;
                    /*^compute*/
                    /*_._IF___V5*/
                    meltfptr[3] = /*_.PROGN___V7*/ meltfptr[6];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3966:/ clear");
                    /*clear*/ /*_.RETURN___V6*/
                    meltfptr[5] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V7*/
                    meltfptr[6] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V5*/ meltfptr[3] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#TESTDIS_CHK__L3*/
        meltfnum[2] =
            /*melt_make_jsonobject TESTDIS_CHK__1*/
            !/*_.DIS__V2*/ meltfptr[1] || ((meltobject_ptr_t)/*_.DIS__V2*/ meltfptr[1])->meltobj_magic != MELTOBMAG_JSONOBJECT;;
        MELT_LOCATION("warmelt-base.melt:3968:/ cond");
        /*cond*/
        if (/*_#TESTDIS_CHK__L3*/ meltfnum[2]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:3970:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:3970:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    MELT_LOCATION("warmelt-base.melt:3968:/ quasiblock");


                    /*_.PROGN___V10*/
                    meltfptr[9] = /*_.RETURN___V9*/ meltfptr[6];;
                    /*^compute*/
                    /*_._IF___V8*/
                    meltfptr[5] = /*_.PROGN___V10*/ meltfptr[9];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:3968:/ clear");
                    /*clear*/ /*_.RETURN___V9*/
                    meltfptr[6] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V10*/
                    meltfptr[9] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V8*/ meltfptr[5] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:3971:/ quasiblock");


        /*_.LISTENTRIES__V12*/
        meltfptr[9] =
            (meltgc_new_list((meltobject_ptr_t)((/*!DISCR_LIST*/ meltfrout->tabval[2]))));;
        MELT_LOCATION("warmelt-base.melt:3973:/ loop");
        /*loop*/
        {
meltlabloop_ARGLOOP_7:;/*^loopbody*/

            /*^block*/
            /*anyblock*/
            {


                MELT_CHECK_SIGNAL();
                ;
                MELT_LOCATION("warmelt-base.melt:3975:/ quasiblock");


                /*_.CURNAME__V16*/
                meltfptr[15] = (/*nil*/NULL);;
                /*^compute*/
                /*_.CURVAL__V17*/
                meltfptr[16] = (/*nil*/NULL);;
                /*^compute*/
                /*_.NAMETUP__V18*/
                meltfptr[17] = (/*nil*/NULL);;
                /*^compute*/
                /*_.VALTUP__V19*/
                meltfptr[18] = (/*nil*/NULL);;
                MELT_LOCATION("warmelt-base.melt:3981:/ cond");
                /*cond*/
                if (/*ifvariadic nomore*/ variad_MAKE_JSONOBJECT_ix == variad_MAKE_JSONOBJECT_len) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            /*^compute*/

                            /*consume variadic  !*/ variad_MAKE_JSONOBJECT_ix += 0;;
                            /*^quasiblock*/


                            /*^compute*/
                            /*_.ARGLOOP__V14*/
                            meltfptr[13] =  /*reallynil*/ NULL ;;

                            /*^exit*/
                            /*exit*/
                            {
                                goto meltlabexit_ARGLOOP_7;
                            }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                else    /*^cond.else*/
                    {

                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:3982:/ cond");
                            /*cond*/
                            if (/*ifvariadic arg#1*/ variad_MAKE_JSONOBJECT_ix>=0 && variad_MAKE_JSONOBJECT_ix + 1 <= variad_MAKE_JSONOBJECT_len && meltxargdescr_[variad_MAKE_JSONOBJECT_ix]== MELTBPAR_CSTRING) /*then*/
                                {
                                    /*^cond.then*/
                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        /*^compute*/
                                        /*_?*/ meltfram__.loc_CSTRING__o0 =
                                            /*variadic argument stuff*/ meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_cstring;;
                                        /*^compute*/

                                        /*consume variadic CSTRING !*/
                                        variad_MAKE_JSONOBJECT_ix += 1;;
                                        /*_.MAKE_STRINGCONST__V20*/
                                        meltfptr[19] =
                                            (meltgc_new_stringdup((meltobject_ptr_t)((/*!DISCR_STRING*/ meltfrout->tabval[3])), (/*_?*/ meltfram__.loc_CSTRING__o0)));;
                                        MELT_LOCATION("warmelt-base.melt:3982:/ compute");
                                        /*_.CURNAME__V16*/
                                        meltfptr[15] = /*_.SETQ___V21*/ meltfptr[20] = /*_.MAKE_STRINGCONST__V20*/ meltfptr[19];;

                                        {
                                            /*^locexp*/
                                            /*void*/(void)0;
                                        }
                                        ;

                                        MELT_CHECK_SIGNAL();
                                        ;
                                        /*epilog*/

                                        /*^clear*/
                                        /*clear*/ /*_?*/
                                        meltfram__.loc_CSTRING__o0 = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.MAKE_STRINGCONST__V20*/
                                        meltfptr[19] = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.SETQ___V21*/
                                        meltfptr[20] = 0 ;
                                    }
                                    ;
                                }
                            else    /*^cond.else*/
                                {

                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        MELT_LOCATION("warmelt-base.melt:3983:/ cond");
                                        /*cond*/
                                        if (/*ifvariadic arg#1*/ variad_MAKE_JSONOBJECT_ix>=0 && variad_MAKE_JSONOBJECT_ix + 1 <= variad_MAKE_JSONOBJECT_len && meltxargdescr_[variad_MAKE_JSONOBJECT_ix]== MELTBPAR_LONG) /*then*/
                                            {
                                                /*^cond.then*/
                                                /*^block*/
                                                /*anyblock*/
                                                {

                                                    /*^compute*/
                                                    /*_#LNAME__L4*/ meltfnum[3] =
                                                        /*variadic argument stuff*/ meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_long;;
                                                    /*^compute*/

                                                    /*consume variadic LONG !*/
                                                    variad_MAKE_JSONOBJECT_ix += 1;;

                                                    MELT_CHECK_SIGNAL();
                                                    ;
                                                    /*^apply*/
                                                    /*apply*/
                                                    {
                                                        union meltparam_un argtab[1];
                                                        memset(&argtab, 0, sizeof(argtab));
                                                        /*^apply.arg*/
                                                        argtab[0].meltbp_long = /*_#LNAME__L4*/ meltfnum[3];
                                                        /*_.STRING4OUT__V22*/
                                                        meltfptr[19] =  melt_apply ((meltclosure_ptr_t)((/*!STRING4OUT*/ meltfrout->tabval[4])), (melt_ptr_t)((/*!DISCR_STRING*/ meltfrout->tabval[3])), (MELTBPARSTR_LONG ""), argtab, "", (union meltparam_un*)0);
                                                    }
                                                    ;
                                                    /*^compute*/
                                                    /*_.CURNAME__V16*/
                                                    meltfptr[15] = /*_.SETQ___V23*/ meltfptr[20] = /*_.STRING4OUT__V22*/ meltfptr[19];;
                                                    /*epilog*/

                                                    /*^clear*/
                                                    /*clear*/ /*_#LNAME__L4*/
                                                    meltfnum[3] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_.STRING4OUT__V22*/
                                                    meltfptr[19] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_.SETQ___V23*/
                                                    meltfptr[20] = 0 ;
                                                }
                                                ;
                                            }
                                        else    /*^cond.else*/
                                            {

                                                /*^block*/
                                                /*anyblock*/
                                                {

                                                    MELT_LOCATION("warmelt-base.melt:3984:/ cond");
                                                    /*cond*/
                                                    if (/*ifvariadic arg#1*/ variad_MAKE_JSONOBJECT_ix>=0 && variad_MAKE_JSONOBJECT_ix + 1 <= variad_MAKE_JSONOBJECT_len && meltxargdescr_[variad_MAKE_JSONOBJECT_ix]== MELTBPAR_PTR) /*then*/
                                                        {
                                                            /*^cond.then*/
                                                            /*^block*/
                                                            /*anyblock*/
                                                            {

                                                                /*^compute*/
                                                                /*_.VNAME__V24*/ meltfptr[19] =
                                                                    /*variadic argument value*/ ((meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_aptr) ? (*(meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_aptr)) : NULL);;
                                                                /*^compute*/

                                                                /*consume variadic Value !*/
                                                                variad_MAKE_JSONOBJECT_ix += 1;;

                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                /*_#IS_A__L5*/
                                                                meltfnum[3] =
                                                                    melt_is_instance_of((melt_ptr_t)(/*_.VNAME__V24*/ meltfptr[19]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])));;
                                                                MELT_LOCATION("warmelt-base.melt:3985:/ cond");
                                                                /*cond*/
                                                                if (/*_#IS_A__L5*/ meltfnum[3]) /*then*/
                                                                    {
                                                                        /*^cond.then*/
                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {

                                                                            /*^compute*/
                                                                            /*_.CURNAME__V16*/ meltfptr[15] = /*_.SETQ___V26*/ meltfptr[25] = /*_.VNAME__V24*/ meltfptr[19];;
                                                                            /*_._IFELSE___V25*/
                                                                            meltfptr[20] = /*_.SETQ___V26*/ meltfptr[25];;
                                                                            /*epilog*/

                                                                            MELT_LOCATION("warmelt-base.melt:3985:/ clear");
                                                                            /*clear*/ /*_.SETQ___V26*/
                                                                            meltfptr[25] = 0 ;
                                                                        }
                                                                        ;
                                                                    }
                                                                else    /*^cond.else*/
                                                                    {

                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {


                                                                            MELT_CHECK_SIGNAL();
                                                                            ;
                                                                            /*_#IS_STRING__L6*/
                                                                            meltfnum[5] =
                                                                                (melt_magic_discr((melt_ptr_t)(/*_.VNAME__V24*/ meltfptr[19])) == MELTOBMAG_STRING);;
                                                                            MELT_LOCATION("warmelt-base.melt:3986:/ cond");
                                                                            /*cond*/
                                                                            if (/*_#IS_STRING__L6*/ meltfnum[5]) /*then*/
                                                                                {
                                                                                    /*^cond.then*/
                                                                                    /*^block*/
                                                                                    /*anyblock*/
                                                                                    {


                                                                                        MELT_CHECK_SIGNAL();
                                                                                        ;
                                                                                        /*^apply*/
                                                                                        /*apply*/
                                                                                        {
                                                                                            /*_.JSON_CANONICAL_NAME__V28*/ meltfptr[27] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_CANONICAL_NAME*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.VNAME__V24*/ meltfptr[19]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                                        }
                                                                                        ;
                                                                                        /*^compute*/
                                                                                        /*_.CURNAME__V16*/
                                                                                        meltfptr[15] = /*_.SETQ___V29*/ meltfptr[28] = /*_.JSON_CANONICAL_NAME__V28*/ meltfptr[27];;
                                                                                        /*_._IFELSE___V27*/
                                                                                        meltfptr[25] = /*_.SETQ___V29*/ meltfptr[28];;
                                                                                        /*epilog*/

                                                                                        MELT_LOCATION("warmelt-base.melt:3986:/ clear");
                                                                                        /*clear*/ /*_.JSON_CANONICAL_NAME__V28*/
                                                                                        meltfptr[27] = 0 ;
                                                                                        /*^clear*/
                                                                                        /*clear*/ /*_.SETQ___V29*/
                                                                                        meltfptr[28] = 0 ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                            else    /*^cond.else*/
                                                                                {

                                                                                    /*^block*/
                                                                                    /*anyblock*/
                                                                                    {


                                                                                        MELT_CHECK_SIGNAL();
                                                                                        ;
                                                                                        /*_#IS_MULTIPLE__L7*/
                                                                                        meltfnum[6] =
                                                                                            (melt_magic_discr((melt_ptr_t)(/*_.VNAME__V24*/ meltfptr[19])) == MELTOBMAG_MULTIPLE);;
                                                                                        MELT_LOCATION("warmelt-base.melt:3987:/ cond");
                                                                                        /*cond*/
                                                                                        if (/*_#IS_MULTIPLE__L7*/ meltfnum[6]) /*then*/
                                                                                            {
                                                                                                /*^cond.then*/
                                                                                                /*^block*/
                                                                                                /*anyblock*/
                                                                                                {

                                                                                                    /*^compute*/
                                                                                                    /*_.NAMETUP__V18*/ meltfptr[17] = /*_.SETQ___V31*/ meltfptr[28] = /*_.VNAME__V24*/ meltfptr[19];;
                                                                                                    /*_._IFELSE___V30*/
                                                                                                    meltfptr[27] = /*_.SETQ___V31*/ meltfptr[28];;
                                                                                                    /*epilog*/

                                                                                                    MELT_LOCATION("warmelt-base.melt:3987:/ clear");
                                                                                                    /*clear*/ /*_.SETQ___V31*/
                                                                                                    meltfptr[28] = 0 ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                        else    /*^cond.else*/
                                                                                            {

                                                                                                /*^block*/
                                                                                                /*anyblock*/
                                                                                                {


                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                    ;
                                                                                                    /*_#IS_LIST__L8*/
                                                                                                    meltfnum[7] =
                                                                                                        (melt_magic_discr((melt_ptr_t)(/*_.VNAME__V24*/ meltfptr[19])) == MELTOBMAG_LIST);;
                                                                                                    MELT_LOCATION("warmelt-base.melt:3988:/ cond");
                                                                                                    /*cond*/
                                                                                                    if (/*_#IS_LIST__L8*/ meltfnum[7]) /*then*/
                                                                                                        {
                                                                                                            /*^cond.then*/
                                                                                                            /*^block*/
                                                                                                            /*anyblock*/
                                                                                                            {


                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                ;
                                                                                                                /*^apply*/
                                                                                                                /*apply*/
                                                                                                                {
                                                                                                                    /*_.LIST_TO_MULTIPLE__V33*/ meltfptr[32] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[7])), (melt_ptr_t)(/*_.VNAME__V24*/ meltfptr[19]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                                                                }
                                                                                                                ;
                                                                                                                /*^compute*/
                                                                                                                /*_.NAMETUP__V18*/
                                                                                                                meltfptr[17] = /*_.SETQ___V34*/ meltfptr[33] = /*_.LIST_TO_MULTIPLE__V33*/ meltfptr[32];;
                                                                                                                /*_._IFELSE___V32*/
                                                                                                                meltfptr[28] = /*_.SETQ___V34*/ meltfptr[33];;
                                                                                                                /*epilog*/

                                                                                                                MELT_LOCATION("warmelt-base.melt:3988:/ clear");
                                                                                                                /*clear*/ /*_.LIST_TO_MULTIPLE__V33*/
                                                                                                                meltfptr[32] = 0 ;
                                                                                                                /*^clear*/
                                                                                                                /*clear*/ /*_.SETQ___V34*/
                                                                                                                meltfptr[33] = 0 ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                    else    /*^cond.else*/
                                                                                                        {

                                                                                                            /*^block*/
                                                                                                            /*anyblock*/
                                                                                                            {


                                                                                                                {
                                                                                                                    MELT_LOCATION("warmelt-base.melt:3989:/ locexp");
                                                                                                                    /*void*/
                                                                                                                    (void)0;
                                                                                                                }
                                                                                                                ;
                                                                                                                /*^quasiblock*/


                                                                                                                /*epilog*/
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                    ;
                                                                                                    /*_._IFELSE___V30*/
                                                                                                    meltfptr[27] = /*_._IFELSE___V32*/ meltfptr[28];;
                                                                                                    /*epilog*/

                                                                                                    MELT_LOCATION("warmelt-base.melt:3987:/ clear");
                                                                                                    /*clear*/ /*_#IS_LIST__L8*/
                                                                                                    meltfnum[7] = 0 ;
                                                                                                    /*^clear*/
                                                                                                    /*clear*/ /*_._IFELSE___V32*/
                                                                                                    meltfptr[28] = 0 ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                        ;
                                                                                        /*_._IFELSE___V27*/
                                                                                        meltfptr[25] = /*_._IFELSE___V30*/ meltfptr[27];;
                                                                                        /*epilog*/

                                                                                        MELT_LOCATION("warmelt-base.melt:3986:/ clear");
                                                                                        /*clear*/ /*_#IS_MULTIPLE__L7*/
                                                                                        meltfnum[6] = 0 ;
                                                                                        /*^clear*/
                                                                                        /*clear*/ /*_._IFELSE___V30*/
                                                                                        meltfptr[27] = 0 ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                            ;
                                                                            /*_._IFELSE___V25*/
                                                                            meltfptr[20] = /*_._IFELSE___V27*/ meltfptr[25];;
                                                                            /*epilog*/

                                                                            MELT_LOCATION("warmelt-base.melt:3985:/ clear");
                                                                            /*clear*/ /*_#IS_STRING__L6*/
                                                                            meltfnum[5] = 0 ;
                                                                            /*^clear*/
                                                                            /*clear*/ /*_._IFELSE___V27*/
                                                                            meltfptr[25] = 0 ;
                                                                        }
                                                                        ;
                                                                    }
                                                                ;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:3984:/ clear");
                                                                /*clear*/ /*_.VNAME__V24*/
                                                                meltfptr[19] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_#IS_A__L5*/
                                                                meltfnum[3] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_._IFELSE___V25*/
                                                                meltfptr[20] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    else    /*^cond.else*/
                                                        {

                                                            /*^block*/
                                                            /*anyblock*/
                                                            {


                                                                {
                                                                    MELT_LOCATION("warmelt-base.melt:3991:/ locexp");
                                                                    /*void*/
                                                                    (void)0;
                                                                }
                                                                ;
                                                                /*epilog*/
                                                            }
                                                            ;
                                                        }
                                                    ;
                                                    /*epilog*/
                                                }
                                                ;
                                            }
                                        ;
                                        /*epilog*/
                                    }
                                    ;
                                }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                ;
                MELT_LOCATION("warmelt-base.melt:3993:/ cond");
                /*cond*/
                if (/*ifvariadic nomore*/ variad_MAKE_JSONOBJECT_ix == variad_MAKE_JSONOBJECT_len) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            /*^compute*/

                            /*consume variadic  !*/ variad_MAKE_JSONOBJECT_ix += 0;;
                            /*^quasiblock*/


                            /*^compute*/
                            /*_.ARGLOOP__V14*/
                            meltfptr[13] =  /*reallynil*/ NULL ;;

                            /*^exit*/
                            /*exit*/
                            {
                                goto meltlabexit_ARGLOOP_7;
                            }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                else    /*^cond.else*/
                    {

                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:3995:/ cond");
                            /*cond*/
                            if (/*ifvariadic arg#1*/ variad_MAKE_JSONOBJECT_ix>=0 && variad_MAKE_JSONOBJECT_ix + 1 <= variad_MAKE_JSONOBJECT_len && meltxargdescr_[variad_MAKE_JSONOBJECT_ix]== MELTBPAR_CSTRING) /*then*/
                                {
                                    /*^cond.then*/
                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        /*^compute*/
                                        /*_?*/ meltfram__.loc_CSTRING__o1 =
                                            /*variadic argument stuff*/ meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_cstring;;
                                        /*^compute*/

                                        /*consume variadic CSTRING !*/
                                        variad_MAKE_JSONOBJECT_ix += 1;;
                                        /*_.BOX__V35*/
                                        meltfptr[32] =
                                            /*full constboxing*/ /*ctype_cstring boxing*/ meltgc_new_stringdup((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_STRING)))), (/*_?*/ meltfram__.loc_CSTRING__o1));;
                                        MELT_LOCATION("warmelt-base.melt:3995:/ compute");
                                        /*_.CURVAL__V17*/
                                        meltfptr[16] = /*_.SETQ___V36*/ meltfptr[33] = /*_.BOX__V35*/ meltfptr[32];;

                                        {
                                            /*^locexp*/
                                            /*void*/(void)0;
                                        }
                                        ;

                                        MELT_CHECK_SIGNAL();
                                        ;
                                        /*epilog*/

                                        /*^clear*/
                                        /*clear*/ /*_?*/
                                        meltfram__.loc_CSTRING__o1 = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.BOX__V35*/
                                        meltfptr[32] = 0 ;
                                        /*^clear*/
                                        /*clear*/ /*_.SETQ___V36*/
                                        meltfptr[33] = 0 ;
                                    }
                                    ;
                                }
                            else    /*^cond.else*/
                                {

                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        MELT_LOCATION("warmelt-base.melt:3996:/ cond");
                                        /*cond*/
                                        if (/*ifvariadic arg#1*/ variad_MAKE_JSONOBJECT_ix>=0 && variad_MAKE_JSONOBJECT_ix + 1 <= variad_MAKE_JSONOBJECT_len && meltxargdescr_[variad_MAKE_JSONOBJECT_ix]== MELTBPAR_LONG) /*then*/
                                            {
                                                /*^cond.then*/
                                                /*^block*/
                                                /*anyblock*/
                                                {

                                                    /*^compute*/
                                                    /*_#L__L9*/ meltfnum[7] =
                                                        /*variadic argument stuff*/ meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_long;;
                                                    /*^compute*/

                                                    /*consume variadic LONG !*/
                                                    variad_MAKE_JSONOBJECT_ix += 1;;
                                                    /*_.BOX__V37*/
                                                    meltfptr[28] =
                                                        /*full constboxing*/ /*boxing ctype_long*/ meltgc_new_int((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_CONSTANT_INTEGER)))), (/*_#L__L9*/ meltfnum[7]));;
                                                    MELT_LOCATION("warmelt-base.melt:3996:/ compute");
                                                    /*_.CURVAL__V17*/
                                                    meltfptr[16] = /*_.SETQ___V38*/ meltfptr[27] = /*_.BOX__V37*/ meltfptr[28];;
                                                    /*epilog*/

                                                    /*^clear*/
                                                    /*clear*/ /*_#L__L9*/
                                                    meltfnum[7] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_.BOX__V37*/
                                                    meltfptr[28] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_.SETQ___V38*/
                                                    meltfptr[27] = 0 ;
                                                }
                                                ;
                                            }
                                        else    /*^cond.else*/
                                            {

                                                /*^block*/
                                                /*anyblock*/
                                                {

                                                    MELT_LOCATION("warmelt-base.melt:3997:/ cond");
                                                    /*cond*/
                                                    if (/*ifvariadic arg#1*/ variad_MAKE_JSONOBJECT_ix>=0 && variad_MAKE_JSONOBJECT_ix + 1 <= variad_MAKE_JSONOBJECT_len && meltxargdescr_[variad_MAKE_JSONOBJECT_ix]== MELTBPAR_PTR) /*then*/
                                                        {
                                                            /*^cond.then*/
                                                            /*^block*/
                                                            /*anyblock*/
                                                            {

                                                                /*^compute*/
                                                                /*_.V__V39*/ meltfptr[25] =
                                                                    /*variadic argument value*/ ((meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_aptr) ? (*(meltxargtab_[variad_MAKE_JSONOBJECT_ix + 0].meltbp_aptr)) : NULL);;
                                                                /*^compute*/

                                                                /*consume variadic Value !*/
                                                                variad_MAKE_JSONOBJECT_ix += 1;;

                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                /*_#IS_A__L10*/
                                                                meltfnum[6] =
                                                                    melt_is_instance_of((melt_ptr_t)(/*_.V__V39*/ meltfptr[25]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])));;
                                                                MELT_LOCATION("warmelt-base.melt:3998:/ cond");
                                                                /*cond*/
                                                                if (/*_#IS_A__L10*/ meltfnum[6]) /*then*/
                                                                    {
                                                                        /*^cond.then*/
                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {

                                                                            /*^compute*/
                                                                            /*_.CURVAL__V17*/ meltfptr[16] = /*_.SETQ___V41*/ meltfptr[20] = /*_.V__V39*/ meltfptr[25];;
                                                                            /*_._IFELSE___V40*/
                                                                            meltfptr[19] = /*_.SETQ___V41*/ meltfptr[20];;
                                                                            /*epilog*/

                                                                            MELT_LOCATION("warmelt-base.melt:3998:/ clear");
                                                                            /*clear*/ /*_.SETQ___V41*/
                                                                            meltfptr[20] = 0 ;
                                                                        }
                                                                        ;
                                                                    }
                                                                else    /*^cond.else*/
                                                                    {

                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {


                                                                            MELT_CHECK_SIGNAL();
                                                                            ;
                                                                            /*_#IS_STRING__L11*/
                                                                            meltfnum[5] =
                                                                                (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_STRING);;
                                                                            MELT_LOCATION("warmelt-base.melt:3999:/ cond");
                                                                            /*cond*/
                                                                            if (/*_#IS_STRING__L11*/ meltfnum[5]) /*then*/
                                                                                {
                                                                                    /*^cond.then*/
                                                                                    /*^block*/
                                                                                    /*anyblock*/
                                                                                    {


                                                                                        MELT_CHECK_SIGNAL();
                                                                                        ;
                                                                                        /*^apply*/
                                                                                        /*apply*/
                                                                                        {
                                                                                            /*_.JSON_CANONICAL_NAME__V43*/ meltfptr[33] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_CANONICAL_NAME*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.V__V39*/ meltfptr[25]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                                        }
                                                                                        ;
                                                                                        /*^compute*/
                                                                                        /*_.CURVAL__V17*/
                                                                                        meltfptr[16] = /*_.SETQ___V44*/ meltfptr[28] = /*_.JSON_CANONICAL_NAME__V43*/ meltfptr[33];;
                                                                                        /*_._IFELSE___V42*/
                                                                                        meltfptr[32] = /*_.SETQ___V44*/ meltfptr[28];;
                                                                                        /*epilog*/

                                                                                        MELT_LOCATION("warmelt-base.melt:3999:/ clear");
                                                                                        /*clear*/ /*_.JSON_CANONICAL_NAME__V43*/
                                                                                        meltfptr[33] = 0 ;
                                                                                        /*^clear*/
                                                                                        /*clear*/ /*_.SETQ___V44*/
                                                                                        meltfptr[28] = 0 ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                            else    /*^cond.else*/
                                                                                {

                                                                                    /*^block*/
                                                                                    /*anyblock*/
                                                                                    {


                                                                                        MELT_CHECK_SIGNAL();
                                                                                        ;
                                                                                        /*_#IS_INTEGERBOX__L12*/
                                                                                        meltfnum[3] =
                                                                                            (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_INT);;
                                                                                        MELT_LOCATION("warmelt-base.melt:4000:/ cond");
                                                                                        /*cond*/
                                                                                        if (/*_#IS_INTEGERBOX__L12*/ meltfnum[3]) /*then*/
                                                                                            {
                                                                                                /*^cond.then*/
                                                                                                /*^block*/
                                                                                                /*anyblock*/
                                                                                                {

                                                                                                    /*^compute*/
                                                                                                    /*_.CURVAL__V17*/ meltfptr[16] = /*_.SETQ___V46*/ meltfptr[20] = /*_.V__V39*/ meltfptr[25];;
                                                                                                    /*_._IFELSE___V45*/
                                                                                                    meltfptr[27] = /*_.SETQ___V46*/ meltfptr[20];;
                                                                                                    /*epilog*/

                                                                                                    MELT_LOCATION("warmelt-base.melt:4000:/ clear");
                                                                                                    /*clear*/ /*_.SETQ___V46*/
                                                                                                    meltfptr[20] = 0 ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                        else    /*^cond.else*/
                                                                                            {

                                                                                                /*^block*/
                                                                                                /*anyblock*/
                                                                                                {


                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                    ;
                                                                                                    /*_#IS_MIXBIGINT__L13*/
                                                                                                    meltfnum[7] =
                                                                                                        (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_MIXBIGINT);;
                                                                                                    MELT_LOCATION("warmelt-base.melt:4001:/ cond");
                                                                                                    /*cond*/
                                                                                                    if (/*_#IS_MIXBIGINT__L13*/ meltfnum[7]) /*then*/
                                                                                                        {
                                                                                                            /*^cond.then*/
                                                                                                            /*^block*/
                                                                                                            /*anyblock*/
                                                                                                            {

                                                                                                                /*^compute*/
                                                                                                                /*_.CURVAL__V17*/ meltfptr[16] = /*_.SETQ___V48*/ meltfptr[28] = /*_.V__V39*/ meltfptr[25];;
                                                                                                                /*_._IFELSE___V47*/
                                                                                                                meltfptr[33] = /*_.SETQ___V48*/ meltfptr[28];;
                                                                                                                /*epilog*/

                                                                                                                MELT_LOCATION("warmelt-base.melt:4001:/ clear");
                                                                                                                /*clear*/ /*_.SETQ___V48*/
                                                                                                                meltfptr[28] = 0 ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                    else    /*^cond.else*/
                                                                                                        {

                                                                                                            /*^block*/
                                                                                                            /*anyblock*/
                                                                                                            {


                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                ;
                                                                                                                /*_#IS_MIXINT__L14*/
                                                                                                                meltfnum[13] =
                                                                                                                    (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_MIXINT);;
                                                                                                                MELT_LOCATION("warmelt-base.melt:4002:/ cond");
                                                                                                                /*cond*/
                                                                                                                if (/*_#IS_MIXINT__L14*/ meltfnum[13]) /*then*/
                                                                                                                    {
                                                                                                                        /*^cond.then*/
                                                                                                                        /*^block*/
                                                                                                                        /*anyblock*/
                                                                                                                        {

                                                                                                                            /*^compute*/
                                                                                                                            /*_.CURVAL__V17*/ meltfptr[16] = /*_.SETQ___V50*/ meltfptr[28] = /*_.V__V39*/ meltfptr[25];;
                                                                                                                            /*_._IFELSE___V49*/
                                                                                                                            meltfptr[20] = /*_.SETQ___V50*/ meltfptr[28];;
                                                                                                                            /*epilog*/

                                                                                                                            MELT_LOCATION("warmelt-base.melt:4002:/ clear");
                                                                                                                            /*clear*/ /*_.SETQ___V50*/
                                                                                                                            meltfptr[28] = 0 ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                else    /*^cond.else*/
                                                                                                                    {

                                                                                                                        /*^block*/
                                                                                                                        /*anyblock*/
                                                                                                                        {


                                                                                                                            MELT_CHECK_SIGNAL();
                                                                                                                            ;
                                                                                                                            /*_#IS_JSONOBJECT__L15*/
                                                                                                                            meltfnum[14] =
                                                                                                                                (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_JSONOBJECT);;
                                                                                                                            MELT_LOCATION("warmelt-base.melt:4003:/ cond");
                                                                                                                            /*cond*/
                                                                                                                            if (/*_#IS_JSONOBJECT__L15*/ meltfnum[14]) /*then*/
                                                                                                                                {
                                                                                                                                    /*^cond.then*/
                                                                                                                                    /*^block*/
                                                                                                                                    /*anyblock*/
                                                                                                                                    {

                                                                                                                                        /*^compute*/
                                                                                                                                        /*_.CURVAL__V17*/ meltfptr[16] = /*_.SETQ___V52*/ meltfptr[51] = /*_.V__V39*/ meltfptr[25];;
                                                                                                                                        /*_._IFELSE___V51*/
                                                                                                                                        meltfptr[28] = /*_.SETQ___V52*/ meltfptr[51];;
                                                                                                                                        /*epilog*/

                                                                                                                                        MELT_LOCATION("warmelt-base.melt:4003:/ clear");
                                                                                                                                        /*clear*/ /*_.SETQ___V52*/
                                                                                                                                        meltfptr[51] = 0 ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                            else    /*^cond.else*/
                                                                                                                                {

                                                                                                                                    /*^block*/
                                                                                                                                    /*anyblock*/
                                                                                                                                    {


                                                                                                                                        MELT_CHECK_SIGNAL();
                                                                                                                                        ;
                                                                                                                                        /*_#IS_MULTIPLE__L16*/
                                                                                                                                        meltfnum[15] =
                                                                                                                                            (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_MULTIPLE);;
                                                                                                                                        MELT_LOCATION("warmelt-base.melt:4004:/ cond");
                                                                                                                                        /*cond*/
                                                                                                                                        if (/*_#IS_MULTIPLE__L16*/ meltfnum[15]) /*then*/
                                                                                                                                            {
                                                                                                                                                /*^cond.then*/
                                                                                                                                                /*^block*/
                                                                                                                                                /*anyblock*/
                                                                                                                                                {


                                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                                    ;
                                                                                                                                                    /*^cond*/
                                                                                                                                                    /*cond*/
                                                                                                                                                    if (/*_.NAMETUP__V18*/ meltfptr[17]) /*then*/
                                                                                                                                                        {
                                                                                                                                                            /*^cond.then*/
                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:4005:/ compute");
                                                                                                                                                                /*_.VALTUP__V19*/
                                                                                                                                                                meltfptr[18] = /*_.SETQ___V55*/ meltfptr[54] = /*_.V__V39*/ meltfptr[25];;
                                                                                                                                                                /*_._IFELSE___V54*/
                                                                                                                                                                meltfptr[53] = /*_.SETQ___V55*/ meltfptr[54];;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:4004:/ clear");
                                                                                                                                                                /*clear*/ /*_.SETQ___V55*/
                                                                                                                                                                meltfptr[54] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    else    /*^cond.else*/
                                                                                                                                                        {

                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:4006:/ compute");
                                                                                                                                                                /*_.CURVAL__V17*/
                                                                                                                                                                meltfptr[16] = /*_.SETQ___V56*/ meltfptr[54] = /*_.V__V39*/ meltfptr[25];;
                                                                                                                                                                /*_._IFELSE___V54*/
                                                                                                                                                                meltfptr[53] = /*_.SETQ___V56*/ meltfptr[54];;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:4004:/ clear");
                                                                                                                                                                /*clear*/ /*_.SETQ___V56*/
                                                                                                                                                                meltfptr[54] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    ;
                                                                                                                                                    /*_._IFELSE___V53*/
                                                                                                                                                    meltfptr[51] = /*_._IFELSE___V54*/ meltfptr[53];;
                                                                                                                                                    /*epilog*/

                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:4004:/ clear");
                                                                                                                                                    /*clear*/ /*_._IFELSE___V54*/
                                                                                                                                                    meltfptr[53] = 0 ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                        else    /*^cond.else*/
                                                                                                                                            {

                                                                                                                                                /*^block*/
                                                                                                                                                /*anyblock*/
                                                                                                                                                {


                                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                                    ;
                                                                                                                                                    /*_#IS_LIST__L17*/
                                                                                                                                                    meltfnum[16] =
                                                                                                                                                        (melt_magic_discr((melt_ptr_t)(/*_.V__V39*/ meltfptr[25])) == MELTOBMAG_LIST);;
                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:4007:/ cond");
                                                                                                                                                    /*cond*/
                                                                                                                                                    if (/*_#IS_LIST__L17*/ meltfnum[16]) /*then*/
                                                                                                                                                        {
                                                                                                                                                            /*^cond.then*/
                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {


                                                                                                                                                                MELT_CHECK_SIGNAL();
                                                                                                                                                                ;
                                                                                                                                                                /*^cond*/
                                                                                                                                                                /*cond*/
                                                                                                                                                                if (/*_.NAMETUP__V18*/ meltfptr[17]) /*then*/
                                                                                                                                                                    {
                                                                                                                                                                        /*^cond.then*/
                                                                                                                                                                        /*^block*/
                                                                                                                                                                        /*anyblock*/
                                                                                                                                                                        {


                                                                                                                                                                            MELT_CHECK_SIGNAL();
                                                                                                                                                                            ;
                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:4008:/ apply");
                                                                                                                                                                            /*apply*/
                                                                                                                                                                            {
                                                                                                                                                                                /*_.LIST_TO_MULTIPLE__V59*/ meltfptr[58] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[7])), (melt_ptr_t)(/*_.V__V39*/ meltfptr[25]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                            /*^compute*/
                                                                                                                                                                            /*_.VALTUP__V19*/
                                                                                                                                                                            meltfptr[18] = /*_.SETQ___V60*/ meltfptr[59] = /*_.LIST_TO_MULTIPLE__V59*/ meltfptr[58];;
                                                                                                                                                                            /*_._IFELSE___V58*/
                                                                                                                                                                            meltfptr[53] = /*_.SETQ___V60*/ meltfptr[59];;
                                                                                                                                                                            /*epilog*/

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:4007:/ clear");
                                                                                                                                                                            /*clear*/ /*_.LIST_TO_MULTIPLE__V59*/
                                                                                                                                                                            meltfptr[58] = 0 ;
                                                                                                                                                                            /*^clear*/
                                                                                                                                                                            /*clear*/ /*_.SETQ___V60*/
                                                                                                                                                                            meltfptr[59] = 0 ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                else    /*^cond.else*/
                                                                                                                                                                    {

                                                                                                                                                                        /*^block*/
                                                                                                                                                                        /*anyblock*/
                                                                                                                                                                        {

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:4009:/ compute");
                                                                                                                                                                            /*_.CURVAL__V17*/
                                                                                                                                                                            meltfptr[16] = /*_.SETQ___V61*/ meltfptr[58] = /*_.V__V39*/ meltfptr[25];;
                                                                                                                                                                            /*_._IFELSE___V58*/
                                                                                                                                                                            meltfptr[53] = /*_.SETQ___V61*/ meltfptr[58];;
                                                                                                                                                                            /*epilog*/

                                                                                                                                                                            MELT_LOCATION("warmelt-base.melt:4007:/ clear");
                                                                                                                                                                            /*clear*/ /*_.SETQ___V61*/
                                                                                                                                                                            meltfptr[58] = 0 ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                ;
                                                                                                                                                                /*_._IFELSE___V57*/
                                                                                                                                                                meltfptr[54] = /*_._IFELSE___V58*/ meltfptr[53];;
                                                                                                                                                                /*epilog*/

                                                                                                                                                                MELT_LOCATION("warmelt-base.melt:4007:/ clear");
                                                                                                                                                                /*clear*/ /*_._IFELSE___V58*/
                                                                                                                                                                meltfptr[53] = 0 ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    else    /*^cond.else*/
                                                                                                                                                        {

                                                                                                                                                            /*^block*/
                                                                                                                                                            /*anyblock*/
                                                                                                                                                            {


                                                                                                                                                                {
                                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:4010:/ locexp");
                                                                                                                                                                    /*void*/
                                                                                                                                                                    (void)0;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                                /*^quasiblock*/


                                                                                                                                                                /*epilog*/
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                    ;
                                                                                                                                                    /*_._IFELSE___V53*/
                                                                                                                                                    meltfptr[51] = /*_._IFELSE___V57*/ meltfptr[54];;
                                                                                                                                                    /*epilog*/

                                                                                                                                                    MELT_LOCATION("warmelt-base.melt:4004:/ clear");
                                                                                                                                                    /*clear*/ /*_#IS_LIST__L17*/
                                                                                                                                                    meltfnum[16] = 0 ;
                                                                                                                                                    /*^clear*/
                                                                                                                                                    /*clear*/ /*_._IFELSE___V57*/
                                                                                                                                                    meltfptr[54] = 0 ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                        ;
                                                                                                                                        /*_._IFELSE___V51*/
                                                                                                                                        meltfptr[28] = /*_._IFELSE___V53*/ meltfptr[51];;
                                                                                                                                        /*epilog*/

                                                                                                                                        MELT_LOCATION("warmelt-base.melt:4003:/ clear");
                                                                                                                                        /*clear*/ /*_#IS_MULTIPLE__L16*/
                                                                                                                                        meltfnum[15] = 0 ;
                                                                                                                                        /*^clear*/
                                                                                                                                        /*clear*/ /*_._IFELSE___V53*/
                                                                                                                                        meltfptr[51] = 0 ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                            ;
                                                                                                                            /*_._IFELSE___V49*/
                                                                                                                            meltfptr[20] = /*_._IFELSE___V51*/ meltfptr[28];;
                                                                                                                            /*epilog*/

                                                                                                                            MELT_LOCATION("warmelt-base.melt:4002:/ clear");
                                                                                                                            /*clear*/ /*_#IS_JSONOBJECT__L15*/
                                                                                                                            meltfnum[14] = 0 ;
                                                                                                                            /*^clear*/
                                                                                                                            /*clear*/ /*_._IFELSE___V51*/
                                                                                                                            meltfptr[28] = 0 ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                ;
                                                                                                                /*_._IFELSE___V47*/
                                                                                                                meltfptr[33] = /*_._IFELSE___V49*/ meltfptr[20];;
                                                                                                                /*epilog*/

                                                                                                                MELT_LOCATION("warmelt-base.melt:4001:/ clear");
                                                                                                                /*clear*/ /*_#IS_MIXINT__L14*/
                                                                                                                meltfnum[13] = 0 ;
                                                                                                                /*^clear*/
                                                                                                                /*clear*/ /*_._IFELSE___V49*/
                                                                                                                meltfptr[20] = 0 ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                    ;
                                                                                                    /*_._IFELSE___V45*/
                                                                                                    meltfptr[27] = /*_._IFELSE___V47*/ meltfptr[33];;
                                                                                                    /*epilog*/

                                                                                                    MELT_LOCATION("warmelt-base.melt:4000:/ clear");
                                                                                                    /*clear*/ /*_#IS_MIXBIGINT__L13*/
                                                                                                    meltfnum[7] = 0 ;
                                                                                                    /*^clear*/
                                                                                                    /*clear*/ /*_._IFELSE___V47*/
                                                                                                    meltfptr[33] = 0 ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                        ;
                                                                                        /*_._IFELSE___V42*/
                                                                                        meltfptr[32] = /*_._IFELSE___V45*/ meltfptr[27];;
                                                                                        /*epilog*/

                                                                                        MELT_LOCATION("warmelt-base.melt:3999:/ clear");
                                                                                        /*clear*/ /*_#IS_INTEGERBOX__L12*/
                                                                                        meltfnum[3] = 0 ;
                                                                                        /*^clear*/
                                                                                        /*clear*/ /*_._IFELSE___V45*/
                                                                                        meltfptr[27] = 0 ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                            ;
                                                                            /*_._IFELSE___V40*/
                                                                            meltfptr[19] = /*_._IFELSE___V42*/ meltfptr[32];;
                                                                            /*epilog*/

                                                                            MELT_LOCATION("warmelt-base.melt:3998:/ clear");
                                                                            /*clear*/ /*_#IS_STRING__L11*/
                                                                            meltfnum[5] = 0 ;
                                                                            /*^clear*/
                                                                            /*clear*/ /*_._IFELSE___V42*/
                                                                            meltfptr[32] = 0 ;
                                                                        }
                                                                        ;
                                                                    }
                                                                ;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:3997:/ clear");
                                                                /*clear*/ /*_.V__V39*/
                                                                meltfptr[25] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_#IS_A__L10*/
                                                                meltfnum[6] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_._IFELSE___V40*/
                                                                meltfptr[19] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    else    /*^cond.else*/
                                                        {

                                                            /*^block*/
                                                            /*anyblock*/
                                                            {


                                                                {
                                                                    MELT_LOCATION("warmelt-base.melt:4011:/ locexp");
                                                                    /*void*/
                                                                    (void)0;
                                                                }
                                                                ;
                                                                /*epilog*/
                                                            }
                                                            ;
                                                        }
                                                    ;
                                                    /*epilog*/
                                                }
                                                ;
                                            }
                                        ;
                                        /*epilog*/
                                    }
                                    ;
                                }
                            ;
                            /*epilog*/
                        }
                        ;
                    }
                ;

                MELT_CHECK_SIGNAL();
                ;
                MELT_LOCATION("warmelt-base.melt:4013:/ cond");
                /*cond*/
                if (/*_.CURNAME__V16*/ meltfptr[15]) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:4014:/ blockmultialloc");
                            /*multiallocblock*/
                            {
                                struct meltletrec_1_st
                                {
                                    struct MELT_MULTIPLE_STRUCT(2) rtup_0__TUPLREC__x2;
                                    long meltletrec_1_endgap;
                                } *meltletrec_1_ptr = 0;
                                meltletrec_1_ptr = (struct meltletrec_1_st *) meltgc_allocate (sizeof (struct meltletrec_1_st), 0);
                                /*^blockmultialloc.initfill*/
                                /*inimult rtup_0__TUPLREC__x2*/
                                /*_.TUPLREC___V64*/
                                meltfptr[53] = (melt_ptr_t) &meltletrec_1_ptr->rtup_0__TUPLREC__x2;
                                meltletrec_1_ptr->rtup_0__TUPLREC__x2.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
                                meltletrec_1_ptr->rtup_0__TUPLREC__x2.nbval = 2;


                                /*^putuple*/
                                /*putupl#4*/
                                melt_assertmsg("putupl [:4014] #4 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[53]))== MELTOBMAG_MULTIPLE);
                                melt_assertmsg("putupl [:4014] #4 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[53]))));
                                ((meltmultiple_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[53]))->tabval[0] = (melt_ptr_t)(/*_.CURNAME__V16*/ meltfptr[15]);
                                ;
                                /*^putuple*/
                                /*putupl#5*/
                                melt_assertmsg("putupl [:4014] #5 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[53]))== MELTOBMAG_MULTIPLE);
                                melt_assertmsg("putupl [:4014] #5 checkoff", (1>=0 && 1< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[53]))));
                                ((meltmultiple_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[53]))->tabval[1] = (melt_ptr_t)(/*_.CURVAL__V17*/ meltfptr[16]);
                                ;
                                /*^touch*/
                                meltgc_touch(/*_.TUPLREC___V64*/ meltfptr[53]);
                                ;
                                /*_.TUPLE___V63*/
                                meltfptr[58] = /*_.TUPLREC___V64*/ meltfptr[53];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4014:/ clear");
                                /*clear*/ /*_.TUPLREC___V64*/
                                meltfptr[53] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.TUPLREC___V64*/
                                meltfptr[53] = 0 ;
                            } /*end multiallocblock*/
                            ;



                            {
                                /*^locexp*/
                                meltgc_append_list((melt_ptr_t)(/*_.LISTENTRIES__V12*/ meltfptr[9]), (melt_ptr_t)(/*_.TUPLE___V63*/ meltfptr[58]));
                            }
                            ;
                            /*clear*/ /*_._IFELSE___V62*/
                            meltfptr[59] = 0 ;
                            /*epilog*/

                            MELT_LOCATION("warmelt-base.melt:4013:/ clear");
                            /*clear*/ /*_.TUPLE___V63*/
                            meltfptr[58] = 0 ;
                        }
                        ;
                    }
                else    /*^cond.else*/
                    {

                        /*^block*/
                        /*anyblock*/
                        {


                            MELT_CHECK_SIGNAL();
                            ;
                            MELT_LOCATION("warmelt-base.melt:4015:/ cond");
                            /*cond*/
                            if (/*_.NAMETUP__V18*/ meltfptr[17]) /*then*/
                                {
                                    /*^cond.then*/
                                    /*^block*/
                                    /*anyblock*/
                                    {

                                        /*citerblock FOREACH_IN_MULTIPLE*/
                                        {
                                            /* start foreach_in_multiple meltcit1__EACHTUP */
                                            long  meltcit1__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.NAMETUP__V18*/ meltfptr[17]);
                                            for (/*_#NIX__L18*/ meltfnum[16] = 0;
                                                                (/*_#NIX__L18*/ meltfnum[16] >= 0) && (/*_#NIX__L18*/ meltfnum[16] <  meltcit1__EACHTUP_ln);
                                                                /*_#NIX__L18*/ meltfnum[16]++)
                                                {
                                                    /*_.CURNAMELEM__V66*/ meltfptr[51] = melt_multiple_nth((melt_ptr_t)(/*_.NAMETUP__V18*/ meltfptr[17]),  /*_#NIX__L18*/ meltfnum[16]);



                                                    MELT_LOCATION("warmelt-base.melt:4019:/ quasiblock");


                                                    /*_.CURVALELEM__V67*/
                                                    meltfptr[28] =
                                                        (melt_multiple_nth((melt_ptr_t)(/*_.VALTUP__V19*/ meltfptr[18]), (/*_#NIX__L18*/ meltfnum[16])));;

                                                    MELT_CHECK_SIGNAL();
                                                    ;
                                                    /*^compute*/
                                                    /*_#IS_STRING__L19*/
                                                    meltfnum[15] =
                                                        (melt_magic_discr((melt_ptr_t)(/*_.CURVALELEM__V67*/ meltfptr[28])) == MELTOBMAG_STRING);;
                                                    MELT_LOCATION("warmelt-base.melt:4020:/ cond");
                                                    /*cond*/
                                                    if (/*_#IS_STRING__L19*/ meltfnum[15]) /*then*/
                                                        {
                                                            /*^cond.then*/
                                                            /*^block*/
                                                            /*anyblock*/
                                                            {


                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                /*^apply*/
                                                                /*apply*/
                                                                {
                                                                    /*_.JSON_CANONICAL_NAME__V69*/ meltfptr[33] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_CANONICAL_NAME*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.CURVALELEM__V67*/ meltfptr[28]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                }
                                                                ;
                                                                /*^compute*/
                                                                /*_.CURVALELEM__V67*/
                                                                meltfptr[28] = /*_.SETQ___V70*/ meltfptr[27] = /*_.JSON_CANONICAL_NAME__V69*/ meltfptr[33];;
                                                                /*_._IF___V68*/
                                                                meltfptr[20] = /*_.SETQ___V70*/ meltfptr[27];;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:4020:/ clear");
                                                                /*clear*/ /*_.JSON_CANONICAL_NAME__V69*/
                                                                meltfptr[33] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_.SETQ___V70*/
                                                                meltfptr[27] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    else    /*^cond.else*/
                                                        {

                                                            /*_._IF___V68*/ meltfptr[20] =  /*reallynil*/ NULL ;;
                                                        }
                                                    ;

                                                    MELT_CHECK_SIGNAL();
                                                    ;
                                                    /*^compute*/
                                                    /*_#IS_STRING__L20*/
                                                    meltfnum[14] =
                                                        (melt_magic_discr((melt_ptr_t)(/*_.CURNAMELEM__V66*/ meltfptr[51])) == MELTOBMAG_STRING);;
                                                    MELT_LOCATION("warmelt-base.melt:4022:/ cond");
                                                    /*cond*/
                                                    if (/*_#IS_STRING__L20*/ meltfnum[14]) /*then*/
                                                        {
                                                            /*^cond.then*/
                                                            /*^block*/
                                                            /*anyblock*/
                                                            {


                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                MELT_LOCATION("warmelt-base.melt:4023:/ apply");
                                                                /*apply*/
                                                                {
                                                                    /*_.JSON_CANONICAL_NAME__V71*/ meltfptr[32] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_CANONICAL_NAME*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.CURNAMELEM__V66*/ meltfptr[51]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                                                }
                                                                ;
                                                                /*^blockmultialloc*/
                                                                /*multiallocblock*/
                                                                {
                                                                    struct meltletrec_2_st
                                                                    {
                                                                        struct MELT_MULTIPLE_STRUCT(2) rtup_0__TUPLREC__x3;
                                                                        long meltletrec_2_endgap;
                                                                    } *meltletrec_2_ptr = 0;
                                                                    meltletrec_2_ptr = (struct meltletrec_2_st *) meltgc_allocate (sizeof (struct meltletrec_2_st), 0);
                                                                    /*^blockmultialloc.initfill*/
                                                                    /*inimult rtup_0__TUPLREC__x3*/
                                                                    /*_.TUPLREC___V73*/
                                                                    meltfptr[19] = (melt_ptr_t) &meltletrec_2_ptr->rtup_0__TUPLREC__x3;
                                                                    meltletrec_2_ptr->rtup_0__TUPLREC__x3.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
                                                                    meltletrec_2_ptr->rtup_0__TUPLREC__x3.nbval = 2;


                                                                    /*^putuple*/
                                                                    /*putupl#6*/
                                                                    melt_assertmsg("putupl [:4023] #6 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V73*/ meltfptr[19]))== MELTOBMAG_MULTIPLE);
                                                                    melt_assertmsg("putupl [:4023] #6 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V73*/ meltfptr[19]))));
                                                                    ((meltmultiple_ptr_t)(/*_.TUPLREC___V73*/ meltfptr[19]))->tabval[0] = (melt_ptr_t)(/*_.JSON_CANONICAL_NAME__V71*/ meltfptr[32]);
                                                                    ;
                                                                    /*^putuple*/
                                                                    /*putupl#7*/
                                                                    melt_assertmsg("putupl [:4023] #7 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V73*/ meltfptr[19]))== MELTOBMAG_MULTIPLE);
                                                                    melt_assertmsg("putupl [:4023] #7 checkoff", (1>=0 && 1< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V73*/ meltfptr[19]))));
                                                                    ((meltmultiple_ptr_t)(/*_.TUPLREC___V73*/ meltfptr[19]))->tabval[1] = (melt_ptr_t)(/*_.CURVALELEM__V67*/ meltfptr[28]);
                                                                    ;
                                                                    /*^touch*/
                                                                    meltgc_touch(/*_.TUPLREC___V73*/ meltfptr[19]);
                                                                    ;
                                                                    /*_.TUPLE___V72*/
                                                                    meltfptr[25] = /*_.TUPLREC___V73*/ meltfptr[19];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-base.melt:4023:/ clear");
                                                                    /*clear*/ /*_.TUPLREC___V73*/
                                                                    meltfptr[19] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.TUPLREC___V73*/
                                                                    meltfptr[19] = 0 ;
                                                                } /*end multiallocblock*/
                                                                ;

                                                                {
                                                                    /*^locexp*/
                                                                    meltgc_append_list((melt_ptr_t)(/*_.LISTENTRIES__V12*/ meltfptr[9]), (melt_ptr_t)(/*_.TUPLE___V72*/ meltfptr[25]));
                                                                }
                                                                ;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:4022:/ clear");
                                                                /*clear*/ /*_.JSON_CANONICAL_NAME__V71*/
                                                                meltfptr[32] = 0 ;
                                                                /*^clear*/
                                                                /*clear*/ /*_.TUPLE___V72*/
                                                                meltfptr[25] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    else    /*^cond.else*/
                                                        {

                                                            /*^block*/
                                                            /*anyblock*/
                                                            {


                                                                MELT_CHECK_SIGNAL();
                                                                ;
                                                                /*_#IS_A__L21*/
                                                                meltfnum[13] =
                                                                    melt_is_instance_of((melt_ptr_t)(/*_.CURNAMELEM__V66*/ meltfptr[51]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])));;
                                                                MELT_LOCATION("warmelt-base.melt:4024:/ cond");
                                                                /*cond*/
                                                                if (/*_#IS_A__L21*/ meltfnum[13]) /*then*/
                                                                    {
                                                                        /*^cond.then*/
                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {

                                                                            MELT_LOCATION("warmelt-base.melt:4025:/ blockmultialloc");
                                                                            /*multiallocblock*/
                                                                            {
                                                                                struct meltletrec_3_st
                                                                                {
                                                                                    struct MELT_MULTIPLE_STRUCT(2) rtup_0__TUPLREC__x4;
                                                                                    long meltletrec_3_endgap;
                                                                                } *meltletrec_3_ptr = 0;
                                                                                meltletrec_3_ptr = (struct meltletrec_3_st *) meltgc_allocate (sizeof (struct meltletrec_3_st), 0);
                                                                                /*^blockmultialloc.initfill*/
                                                                                /*inimult rtup_0__TUPLREC__x4*/
                                                                                /*_.TUPLREC___V75*/
                                                                                meltfptr[58] = (melt_ptr_t) &meltletrec_3_ptr->rtup_0__TUPLREC__x4;
                                                                                meltletrec_3_ptr->rtup_0__TUPLREC__x4.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
                                                                                meltletrec_3_ptr->rtup_0__TUPLREC__x4.nbval = 2;


                                                                                /*^putuple*/
                                                                                /*putupl#8*/
                                                                                melt_assertmsg("putupl [:4025] #8 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V75*/ meltfptr[58]))== MELTOBMAG_MULTIPLE);
                                                                                melt_assertmsg("putupl [:4025] #8 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V75*/ meltfptr[58]))));
                                                                                ((meltmultiple_ptr_t)(/*_.TUPLREC___V75*/ meltfptr[58]))->tabval[0] = (melt_ptr_t)(/*_.CURNAMELEM__V66*/ meltfptr[51]);
                                                                                ;
                                                                                /*^putuple*/
                                                                                /*putupl#9*/
                                                                                melt_assertmsg("putupl [:4025] #9 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V75*/ meltfptr[58]))== MELTOBMAG_MULTIPLE);
                                                                                melt_assertmsg("putupl [:4025] #9 checkoff", (1>=0 && 1< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V75*/ meltfptr[58]))));
                                                                                ((meltmultiple_ptr_t)(/*_.TUPLREC___V75*/ meltfptr[58]))->tabval[1] = (melt_ptr_t)(/*_.CURVALELEM__V67*/ meltfptr[28]);
                                                                                ;
                                                                                /*^touch*/
                                                                                meltgc_touch(/*_.TUPLREC___V75*/ meltfptr[58]);
                                                                                ;
                                                                                /*_.TUPLE___V74*/
                                                                                meltfptr[53] = /*_.TUPLREC___V75*/ meltfptr[58];;
                                                                                /*epilog*/

                                                                                MELT_LOCATION("warmelt-base.melt:4025:/ clear");
                                                                                /*clear*/ /*_.TUPLREC___V75*/
                                                                                meltfptr[58] = 0 ;
                                                                                /*^clear*/
                                                                                /*clear*/ /*_.TUPLREC___V75*/
                                                                                meltfptr[58] = 0 ;
                                                                            } /*end multiallocblock*/
                                                                            ;

                                                                            {
                                                                                /*^locexp*/
                                                                                meltgc_append_list((melt_ptr_t)(/*_.LISTENTRIES__V12*/ meltfptr[9]), (melt_ptr_t)(/*_.TUPLE___V74*/ meltfptr[53]));
                                                                            }
                                                                            ;
                                                                            /*epilog*/

                                                                            MELT_LOCATION("warmelt-base.melt:4024:/ clear");
                                                                            /*clear*/ /*_.TUPLE___V74*/
                                                                            meltfptr[53] = 0 ;
                                                                        }
                                                                        ;
                                                                    }
                                                                else    /*^cond.else*/
                                                                    {

                                                                        /*^block*/
                                                                        /*anyblock*/
                                                                        {


                                                                            {
                                                                                MELT_LOCATION("warmelt-base.melt:4027:/ locexp");
                                                                                /*void*/
                                                                                (void)0;
                                                                            }
                                                                            ;
                                                                            MELT_LOCATION("warmelt-base.melt:4026:/ quasiblock");


                                                                            /*epilog*/
                                                                        }
                                                                        ;
                                                                    }
                                                                ;
                                                                /*epilog*/

                                                                MELT_LOCATION("warmelt-base.melt:4022:/ clear");
                                                                /*clear*/ /*_#IS_A__L21*/
                                                                meltfnum[13] = 0 ;
                                                            }
                                                            ;
                                                        }
                                                    ;

                                                    MELT_LOCATION("warmelt-base.melt:4019:/ clear");
                                                    /*clear*/ /*_.CURVALELEM__V67*/
                                                    meltfptr[28] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_#IS_STRING__L19*/
                                                    meltfnum[15] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_._IF___V68*/
                                                    meltfptr[20] = 0 ;
                                                    /*^clear*/
                                                    /*clear*/ /*_#IS_STRING__L20*/
                                                    meltfnum[14] = 0 ;
                                                    if (/*_#NIX__L18*/ meltfnum[16]<0) break;
                                                } /* end  foreach_in_multiple meltcit1__EACHTUP */

                                            /*citerepilog*/

                                            MELT_LOCATION("warmelt-base.melt:4016:/ clear");
                                            /*clear*/ /*_.CURNAMELEM__V66*/
                                            meltfptr[51] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_#NIX__L18*/
                                            meltfnum[16] = 0 ;
                                        } /*endciterblock FOREACH_IN_MULTIPLE*/
                                        ;
                                        /*epilog*/
                                    }
                                    ;
                                }
                            else
                                {
                                    MELT_LOCATION("warmelt-base.melt:4015:/ cond.else");

                                    /*_._IFELSE___V65*/
                                    meltfptr[54] =  /*reallynil*/ NULL ;;
                                }
                            ;
                            /*^compute*/
                            /*_._IFELSE___V62*/
                            meltfptr[59] = /*_._IFELSE___V65*/ meltfptr[54];;
                            /*epilog*/

                            MELT_LOCATION("warmelt-base.melt:4013:/ clear");
                            /*clear*/ /*_._IFELSE___V65*/
                            meltfptr[54] = 0 ;
                        }
                        ;
                    }
                ;
                /*_.LET___V15*/
                meltfptr[14] = /*_._IFELSE___V62*/ meltfptr[59];;

                MELT_LOCATION("warmelt-base.melt:3975:/ clear");
                /*clear*/ /*_.CURNAME__V16*/
                meltfptr[15] = 0 ;
                /*^clear*/
                /*clear*/ /*_.CURVAL__V17*/
                meltfptr[16] = 0 ;
                /*^clear*/
                /*clear*/ /*_.NAMETUP__V18*/
                meltfptr[17] = 0 ;
                /*^clear*/
                /*clear*/ /*_.VALTUP__V19*/
                meltfptr[18] = 0 ;
                /*^clear*/
                /*clear*/ /*_._IFELSE___V62*/
                meltfptr[59] = 0 ;
                /*epilog*/

                MELT_LOCATION("warmelt-base.melt:3973:/ clear");
                /*clear*/ /*_.LET___V15*/
                meltfptr[14] = 0 ;
            }
            ;
            ;
            goto meltlabloop_ARGLOOP_7;
meltlabexit_ARGLOOP_7:;/*^loopepilog*/
            /*loopepilog*/
            /*_.FOREVER___V13*/
            meltfptr[12] = /*_.ARGLOOP__V14*/ meltfptr[13];;
        }
        ;
        MELT_LOCATION("warmelt-base.melt:4030:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            /*_.TUPENTRIES__V77*/ meltfptr[27] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[7])), (melt_ptr_t)(/*_.LISTENTRIES__V12*/ meltfptr[9]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-base.melt:4033:/ quasiblock");


        /*^newclosure*/
        /*newclosure*/ /*_.LAMBDA___V79*/
        meltfptr[32] =
            (melt_ptr_t) meltgc_new_closure((meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE)))), (meltroutine_ptr_t)((/*!konst_10*/ meltfrout->tabval[10])), (0));
        ;
        /*_.LAMBDA___V78*/
        meltfptr[19] = /*_.LAMBDA___V79*/ meltfptr[32];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4032:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.LAMBDA___V78*/ meltfptr[19];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[11]);
            /*_.SORTEDTUPENTRIES__V80*/
            meltfptr[25] =  melt_apply ((meltclosure_ptr_t)((/*!MULTIPLE_SORT*/ meltfrout->tabval[8])), (melt_ptr_t)(/*_.TUPENTRIES__V77*/ meltfptr[27]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-base.melt:4036:/ quasiblock");


        /*_.UL__V82*/
        meltfptr[53] =
            (meltgc_new_list((meltobject_ptr_t)((/*!DISCR_LIST*/ meltfrout->tabval[2]))));;
        /*citerblock FOREACH_IN_MULTIPLE*/
        {
            /* start foreach_in_multiple meltcit2__EACHTUP */
            long  meltcit2__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.SORTEDTUPENTRIES__V80*/ meltfptr[25]);
            for (/*_#IX__L22*/ meltfnum[7] = 0;
                               (/*_#IX__L22*/ meltfnum[7] >= 0) && (/*_#IX__L22*/ meltfnum[7] <  meltcit2__EACHTUP_ln);
                               /*_#IX__L22*/ meltfnum[7]++)
                {
                    /*_.CURENT__V83*/ meltfptr[28] = melt_multiple_nth((melt_ptr_t)(/*_.SORTEDTUPENTRIES__V80*/ meltfptr[25]),  /*_#IX__L22*/ meltfnum[7]);



                    MELT_LOCATION("warmelt-base.melt:4041:/ quasiblock");


                    /*_#plI__L23*/
                    meltfnum[3] =
                        ((/*_#IX__L22*/ meltfnum[7]) + (1));;
                    /*^compute*/
                    /*_.NEXTENT__V84*/
                    meltfptr[20] =
                        (melt_multiple_nth((melt_ptr_t)(/*_.SORTEDTUPENTRIES__V80*/ meltfptr[25]), (/*_#plI__L23*/ meltfnum[3])));;

                    MELT_CHECK_SIGNAL();
                    ;
                    /*^compute*/
                    /*_#NULL__L24*/
                    meltfnum[5] =
                        (/*null*/(/*_.NEXTENT__V84*/ meltfptr[20]) == NULL);;
                    MELT_LOCATION("warmelt-base.melt:4043:/ cond");
                    /*cond*/
                    if (/*_#NULL__L24*/ meltfnum[5]) /*then*/
                        {
                            /*^cond.then*/
                            /*_#OR___L25*/ meltfnum[6] = /*_#NULL__L24*/ meltfnum[5];;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-base.melt:4043:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {

                                /*_.MULTIPLE_NTH__V85*/ meltfptr[54] =
                                    (melt_multiple_nth((melt_ptr_t)(/*_.CURENT__V83*/ meltfptr[28]), (0)));;
                                /*^compute*/
                                /*_.MULTIPLE_NTH__V86*/
                                meltfptr[15] =
                                    (melt_multiple_nth((melt_ptr_t)(/*_.NEXTENT__V84*/ meltfptr[20]), (0)));;

                                MELT_CHECK_SIGNAL();
                                ;
                                MELT_LOCATION("warmelt-base.melt:4043:/ apply");
                                /*apply*/
                                {
                                    union meltparam_un argtab[1];
                                    memset(&argtab, 0, sizeof(argtab));
                                    /*^apply.arg*/
                                    argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.MULTIPLE_NTH__V86*/ meltfptr[15];
                                    /*_.JSON_NAME_LESS__V87*/
                                    meltfptr[16] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_NAME_LESS*/ meltfrout->tabval[12])), (melt_ptr_t)(/*_.MULTIPLE_NTH__V85*/ meltfptr[54]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                }
                                ;
                                /*_#NOTNULL__L26*/
                                meltfnum[13] =
                                    ((/*_.JSON_NAME_LESS__V87*/ meltfptr[16]) != NULL);;
                                /*^compute*/
                                /*_#OR___L25*/
                                meltfnum[6] = /*_#NOTNULL__L26*/ meltfnum[13];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4043:/ clear");
                                /*clear*/ /*_.MULTIPLE_NTH__V85*/
                                meltfptr[54] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.MULTIPLE_NTH__V86*/
                                meltfptr[15] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.JSON_NAME_LESS__V87*/
                                meltfptr[16] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_#NOTNULL__L26*/
                                meltfnum[13] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*^cond*/
                    /*cond*/
                    if (/*_#OR___L25*/ meltfnum[6]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-base.melt:4044:/ locexp");
                                    meltgc_append_list((melt_ptr_t)(/*_.UL__V82*/ meltfptr[53]), (melt_ptr_t)(/*_.CURENT__V83*/ meltfptr[28]));
                                }
                                ;
                                /*epilog*/
                            }
                            ;
                        } /*noelse*/
                    ;

                    MELT_LOCATION("warmelt-base.melt:4041:/ clear");
                    /*clear*/ /*_#plI__L23*/
                    meltfnum[3] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.NEXTENT__V84*/
                    meltfptr[20] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_#NULL__L24*/
                    meltfnum[5] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_#OR___L25*/
                    meltfnum[6] = 0 ;
                    if (/*_#IX__L22*/ meltfnum[7]<0) break;
                } /* end  foreach_in_multiple meltcit2__EACHTUP */

            /*citerepilog*/

            MELT_LOCATION("warmelt-base.melt:4038:/ clear");
            /*clear*/ /*_.CURENT__V83*/
            meltfptr[28] = 0 ;
            /*^clear*/
            /*clear*/ /*_#IX__L22*/
            meltfnum[7] = 0 ;
        } /*endciterblock FOREACH_IN_MULTIPLE*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4045:/ apply");
        /*apply*/
        {
            /*_.LIST_TO_MULTIPLE__V88*/ meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[7])), (melt_ptr_t)(/*_.UL__V82*/ meltfptr[53]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
        }
        ;
        /*_.LET___V81*/
        meltfptr[58] = /*_.LIST_TO_MULTIPLE__V88*/ meltfptr[17];;

        MELT_LOCATION("warmelt-base.melt:4036:/ clear");
        /*clear*/ /*_.UL__V82*/
        meltfptr[53] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_TO_MULTIPLE__V88*/
        meltfptr[17] = 0 ;
        /*_.UNIQLISTENTRIES__V89*/
        meltfptr[18] = /*_.LET___V81*/ meltfptr[58];;
        /*^compute*/
        /*_#NBUNIQENTRIES__L27*/
        meltfnum[15] =
            (melt_multiple_length((melt_ptr_t)(/*_.UNIQLISTENTRIES__V89*/ meltfptr[18])));;
        /*^compute*/
        /*_.RESJ__V90*/
        meltfptr[59] = (/*nil*/NULL);;

        {
            MELT_LOCATION("warmelt-base.melt:4051:/ locexp");
            /* melt_make_jsonobject MAKEJSON_CHK__1 */
            // the only place where jsonobjects are allocated
            struct meltjsonobject_st* mj_MAKEJSON_CHK__1
            = (struct meltjsonobject_st*) meltgc_allocate (sizeof (struct meltjsonobject_st),
                        /*_#NBUNIQENTRIES__L27*/ meltfnum[15] * sizeof(struct melt_jsonobentry_st));
            mj_MAKEJSON_CHK__1->discr = (meltobject_ptr_t) /*_.DIS__V2*/ meltfptr[1];
            mj_MAKEJSON_CHK__1->jsob_aux = NULL;
            mj_MAKEJSON_CHK__1->jsob_size = /*_#NBUNIQENTRIES__L27*/ meltfnum[15];
            /*_.RESJ__V90*/
            meltfptr[59] = (melt_ptr_t) mj_MAKEJSON_CHK__1;
            mj_MAKEJSON_CHK__1 = NULL;
            ;
        }
        ;
        /*citerblock FOREACH_IN_MULTIPLE*/
        {
            /* start foreach_in_multiple meltcit3__EACHTUP */
            long  meltcit3__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.UNIQLISTENTRIES__V89*/ meltfptr[18]);
            for (/*_#IX__L28*/ meltfnum[14] = 0;
                               (/*_#IX__L28*/ meltfnum[14] >= 0) && (/*_#IX__L28*/ meltfnum[14] <  meltcit3__EACHTUP_ln);
                               /*_#IX__L28*/ meltfnum[14]++)
                {
                    /*_.CURENT__V91*/ meltfptr[14] = melt_multiple_nth((melt_ptr_t)(/*_.UNIQLISTENTRIES__V89*/ meltfptr[18]),  /*_#IX__L28*/ meltfnum[14]);




#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-base.melt:4066:/ cppif.then");
                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*_#MULTIPLE_LENGTH__L29*/
                        meltfnum[13] =
                            (melt_multiple_length((melt_ptr_t)(/*_.CURENT__V91*/ meltfptr[14])));;
                        /*^compute*/
                        /*_#eqeqI__L30*/
                        meltfnum[3] =
                            ((/*_#MULTIPLE_LENGTH__L29*/ meltfnum[13]) == (2));;
                        MELT_LOCATION("warmelt-base.melt:4066:/ cond");
                        /*cond*/
                        if (/*_#eqeqI__L30*/ meltfnum[3]) /*then*/
                            {
                                /*^cond.then*/
                                /*_._IFELSE___V93*/ meltfptr[15] = (/*nil*/NULL);;
                            }
                        else
                            {
                                MELT_LOCATION("warmelt-base.melt:4066:/ cond.else");

                                /*^block*/
                                /*anyblock*/
                                {


                                    MELT_CHECK_SIGNAL();
                                    ;
                                    /*^apply*/
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[3];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_cstring =  "check curent";
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 4066;
                                        /*_.MELT_ASSERT_FAILURE_FUN__V94*/
                                        meltfptr[16] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[13])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IFELSE___V93*/
                                    meltfptr[15] = /*_.MELT_ASSERT_FAILURE_FUN__V94*/ meltfptr[16];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-base.melt:4066:/ clear");
                                    /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V94*/
                                    meltfptr[16] = 0 ;
                                }
                                ;
                            }
                        ;
                        /*_.IFCPP___V92*/
                        meltfptr[54] = /*_._IFELSE___V93*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4066:/ clear");
                        /*clear*/ /*_#MULTIPLE_LENGTH__L29*/
                        meltfnum[13] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_#eqeqI__L30*/
                        meltfnum[3] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IFELSE___V93*/
                        meltfptr[15] = 0 ;
                    }

#else /*MELT_HAVE_DEBUG*/
                    /*^cppif.else*/
                    /*_.IFCPP___V92*/ meltfptr[54] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                    ;
                    MELT_LOCATION("warmelt-base.melt:4067:/ quasiblock");


                    /*_.CURNAM__V95*/
                    meltfptr[20] =
                        (melt_multiple_nth((melt_ptr_t)(/*_.CURENT__V91*/ meltfptr[14]), (0)));;
                    /*^compute*/
                    /*_.CURVAL__V96*/
                    meltfptr[53] =
                        (melt_multiple_nth((melt_ptr_t)(/*_.CURENT__V91*/ meltfptr[14]), (1)));;

#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-base.melt:4070:/ cppif.then");
                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*_#IS_STRING__L31*/
                        meltfnum[5] =
                            (melt_magic_discr((melt_ptr_t)(/*_.CURNAM__V95*/ meltfptr[20])) == MELTOBMAG_STRING);;
                        MELT_LOCATION("warmelt-base.melt:4070:/ cond");
                        /*cond*/
                        if (/*_#IS_STRING__L31*/ meltfnum[5]) /*then*/
                            {
                                /*^cond.then*/
                                /*_#OR___L32*/ meltfnum[6] = /*_#IS_STRING__L31*/ meltfnum[5];;
                            }
                        else
                            {
                                MELT_LOCATION("warmelt-base.melt:4070:/ cond.else");

                                /*^block*/
                                /*anyblock*/
                                {

                                    /*_#IS_A__L33*/ meltfnum[13] =
                                        melt_is_instance_of((melt_ptr_t)(/*_.CURNAM__V95*/ meltfptr[20]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])));;
                                    /*^compute*/
                                    /*_#OR___L32*/
                                    meltfnum[6] = /*_#IS_A__L33*/ meltfnum[13];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-base.melt:4070:/ clear");
                                    /*clear*/ /*_#IS_A__L33*/
                                    meltfnum[13] = 0 ;
                                }
                                ;
                            }
                        ;
                        /*^cond*/
                        /*cond*/
                        if (/*_#OR___L32*/ meltfnum[6]) /*then*/
                            {
                                /*^cond.then*/
                                /*_._IFELSE___V98*/ meltfptr[16] = (/*nil*/NULL);;
                            }
                        else
                            {
                                MELT_LOCATION("warmelt-base.melt:4070:/ cond.else");

                                /*^block*/
                                /*anyblock*/
                                {


                                    MELT_CHECK_SIGNAL();
                                    ;
                                    /*^apply*/
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[5];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_cstring =  "check curnam";
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 4070;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.CURNAM__V95*/ meltfptr[20];
                                        /*^apply.arg*/
                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CURENT__V91*/ meltfptr[14];
                                        /*_.MELT_ASSERT_FAILURE_FUN__V99*/
                                        meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[13])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IFELSE___V98*/
                                    meltfptr[16] = /*_.MELT_ASSERT_FAILURE_FUN__V99*/ meltfptr[15];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-base.melt:4070:/ clear");
                                    /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V99*/
                                    meltfptr[15] = 0 ;
                                }
                                ;
                            }
                        ;
                        /*_.IFCPP___V97*/
                        meltfptr[17] = /*_._IFELSE___V98*/ meltfptr[16];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4070:/ clear");
                        /*clear*/ /*_#IS_STRING__L31*/
                        meltfnum[5] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_#OR___L32*/
                        meltfnum[6] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IFELSE___V98*/
                        meltfptr[16] = 0 ;
                    }

#else /*MELT_HAVE_DEBUG*/
                    /*^cppif.else*/
                    /*_.IFCPP___V97*/ meltfptr[17] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                    ;

                    {
                        MELT_LOCATION("warmelt-base.melt:4071:/ locexp");
                        /* melt_make_jsonobject FILLJSON_CHK__1 */
                        // the only place where jsonobjects are filled
                        ((struct meltjsonobject_st*)/*_.RESJ__V90*/ meltfptr[59])->jsob_entab[/*_#IX__L28*/ meltfnum[14]].jsonob_name = /*_.CURNAM__V95*/ meltfptr[20];
                        meltgc_touch_dest (/*_.RESJ__V90*/ meltfptr[59], /*_.CURNAM__V95*/ meltfptr[20]);
                        ((struct meltjsonobject_st*)/*_.RESJ__V90*/ meltfptr[59])->jsob_entab[/*_#IX__L28*/ meltfnum[14]].jsonob_val = /*_.CURVAL__V96*/ meltfptr[53];
                        meltgc_touch_dest (/*_.RESJ__V90*/ meltfptr[59], /*_.CURVAL__V96*/ meltfptr[53]);
                        // done melt_make_jsonobject FILLJSON_CHK__1
                        ;
                    }
                    ;

                    MELT_LOCATION("warmelt-base.melt:4067:/ clear");
                    /*clear*/ /*_.CURNAM__V95*/
                    meltfptr[20] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.CURVAL__V96*/
                    meltfptr[53] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.IFCPP___V97*/
                    meltfptr[17] = 0 ;
                    if (/*_#IX__L28*/ meltfnum[14]<0) break;
                } /* end  foreach_in_multiple meltcit3__EACHTUP */

            /*citerepilog*/

            MELT_LOCATION("warmelt-base.melt:4063:/ clear");
            /*clear*/ /*_.CURENT__V91*/
            meltfptr[14] = 0 ;
            /*^clear*/
            /*clear*/ /*_#IX__L28*/
            meltfnum[14] = 0 ;
            /*^clear*/
            /*clear*/ /*_.IFCPP___V92*/
            meltfptr[54] = 0 ;
        } /*endciterblock FOREACH_IN_MULTIPLE*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4081:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.RESJ__V90*/ meltfptr[59];;

        {
            MELT_LOCATION("warmelt-base.melt:4081:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V76*/
        meltfptr[33] = /*_.RETURN___V100*/ meltfptr[15];;

        MELT_LOCATION("warmelt-base.melt:4030:/ clear");
        /*clear*/ /*_.TUPENTRIES__V77*/
        meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LAMBDA___V78*/
        meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SORTEDTUPENTRIES__V80*/
        meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V81*/
        meltfptr[58] = 0 ;
        /*^clear*/
        /*clear*/ /*_.UNIQLISTENTRIES__V89*/
        meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NBUNIQENTRIES__L27*/
        meltfnum[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RESJ__V90*/
        meltfptr[59] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V100*/
        meltfptr[15] = 0 ;
        /*_.LET___V11*/
        meltfptr[6] = /*_.LET___V76*/ meltfptr[33];;

        MELT_LOCATION("warmelt-base.melt:3971:/ clear");
        /*clear*/ /*_.LISTENTRIES__V12*/
        meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.FOREVER___V13*/
        meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V76*/
        meltfptr[33] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:3959:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V11*/ meltfptr[6];;

        {
            MELT_LOCATION("warmelt-base.melt:3959:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#NULL__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V3*/
        meltfptr[2] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L2*/
        meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V5*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#TESTDIS_CHK__L3*/
        meltfnum[2] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V8*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V11*/
        meltfptr[6] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MAKE_JSONOBJECT", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef melt_variadic_length
#undef melt_variadic_index

#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_45_WARMELTmiBASE_MAKE_JSONOBJECT*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_46_WARMELTmiBASE_LAMBDA_cl4(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                     const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_46_WARMELTmiBASE_LAMBDA_cl4_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_46_WARMELTmiBASE_LAMBDA_cl4 fromline 1752 */

    /** start of frame for meltrout_46_WARMELTmiBASE_LAMBDA_cl4 of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4// fromline 1568
        : public Melt_CallFrameWithValues<6>
    {
    public: /* fromline 1572*/
// no classy longs
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<6> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4), clos) {};
        MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4() //the constructor fromline 1642
            : Melt_CallFrameWithValues<6> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<6> (fil,lin, sizeof(MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4)) {};
        MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<6> (fil,lin, sizeof(MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4


    /** end of frame for meltrout_46_WARMELTmiBASE_LAMBDA_cl4 fromline 1697**/

    /* end of frame for routine meltrout_46_WARMELTmiBASE_LAMBDA_cl4 fromline 1756 */

    /* classy proc frame meltrout_46_WARMELTmiBASE_LAMBDA_cl4 */
    MeltFrame_meltrout_46_WARMELTmiBASE_LAMBDA_cl4
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_46_WARMELTmiBASE_LAMBDA_cl4 fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LAMBDA_cl4", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:4033:/ getarg");
    /*_.E1__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.E2__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.E2__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        /*_.MULTIPLE_NTH__V4*/ meltfptr[3] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E1__V2*/ meltfptr[1]), (0)));;
        /*^compute*/
        /*_.MULTIPLE_NTH__V5*/
        meltfptr[4] =
            (melt_multiple_nth((melt_ptr_t)(/*_.E2__V3*/ meltfptr[2]), (0)));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4033:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.MULTIPLE_NTH__V5*/ meltfptr[4];
            /*_.JSON_NAME_LESS__V6*/
            meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_NAME_LESS*/ meltfrout->tabval[0])), (melt_ptr_t)(/*_.MULTIPLE_NTH__V4*/ meltfptr[3]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*^quasiblock*/


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.JSON_NAME_LESS__V6*/ meltfptr[5];;

        {
            MELT_LOCATION("warmelt-base.melt:4033:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.MULTIPLE_NTH__V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MULTIPLE_NTH__V5*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_.JSON_NAME_LESS__V6*/
        meltfptr[5] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LAMBDA_cl4", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_46_WARMELTmiBASE_LAMBDA_cl4_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_46_WARMELTmiBASE_LAMBDA_cl4*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED fromline 1752 */

    /** start of frame for meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED// fromline 1568
        : public Melt_CallFrameWithValues<27>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[19];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<27> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED), clos) {};
        MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED() //the constructor fromline 1642
            : Melt_CallFrameWithValues<27> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<27> (fil,lin, sizeof(MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED)) {};
        MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<27> (fil,lin, sizeof(MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED


    /** end of frame for meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED fromline 1697**/

    /* end of frame for routine meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED fromline 1756 */

    /* classy proc frame meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED */
    MeltFrame_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("JSONOBJECT_GET_NAMED", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:4109:/ getarg");
    /*_.VJOB__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ATNAME__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ATNAME__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_JSONOBJECT__L1*/
        meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.VJOB__V2*/ meltfptr[1])) == MELTOBMAG_JSONOBJECT);;
        /*^compute*/
        /*_#NOT__L2*/
        meltfnum[1] =
            (!(/*_#IS_JSONOBJECT__L1*/ meltfnum[0]));;
        MELT_LOCATION("warmelt-base.melt:4112:/ cond");
        /*cond*/
        if (/*_#NOT__L2*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*^quasiblock*/


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:4112:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IF___V4*/
                    meltfptr[3] = /*_.RETURN___V5*/ meltfptr[4];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:4112:/ clear");
                    /*clear*/ /*_.RETURN___V5*/
                    meltfptr[4] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V4*/ meltfptr[3] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:4113:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_STRING__L3*/
        meltfnum[2] =
            (melt_magic_discr((melt_ptr_t)(/*_.ATNAME__V3*/ meltfptr[2])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-base.melt:4114:/ cond");
        /*cond*/
        if (/*_#IS_STRING__L3*/ meltfnum[2]) /*then*/
            {
                /*^cond.then*/
                /*_.VNAME__V7*/ meltfptr[6] = /*_.ATNAME__V3*/ meltfptr[2];;
            }
        else
            {
                MELT_LOCATION("warmelt-base.melt:4114:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_A__L4*/
                    meltfnum[3] =
                        melt_is_instance_of((melt_ptr_t)(/*_.ATNAME__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[0])));;
                    MELT_LOCATION("warmelt-base.melt:4116:/ cond");
                    /*cond*/
                    if (/*_#IS_A__L4*/ meltfnum[3]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:4117:/ getslot");
                                {
                                    melt_ptr_t slot=NULL, obj=NULL;
                                    obj = (melt_ptr_t)(/*_.ATNAME__V3*/ meltfptr[2]) /*=obj*/;
                                    melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                    /*_.NAMED_NAME__V9*/
                                    meltfptr[8] = slot;
                                };
                                ;
                                /*_._IFELSE___V8*/
                                meltfptr[7] = /*_.NAMED_NAME__V9*/ meltfptr[8];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4116:/ clear");
                                /*clear*/ /*_.NAMED_NAME__V9*/
                                meltfptr[8] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                MELT_LOCATION("warmelt-base.melt:4118:/ quasiblock");


                                /*_._RETVAL___V1*/
                                meltfptr[0] = (/*nil*/NULL);;

                                {
                                    MELT_LOCATION("warmelt-base.melt:4118:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                /*^quasiblock*/


                                /*_.PROGN___V11*/
                                meltfptr[10] = /*_.RETURN___V10*/ meltfptr[8];;
                                /*^compute*/
                                /*_._IFELSE___V8*/
                                meltfptr[7] = /*_.PROGN___V11*/ meltfptr[10];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4116:/ clear");
                                /*clear*/ /*_.RETURN___V10*/
                                meltfptr[8] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V11*/
                                meltfptr[10] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_.VNAME__V7*/
                    meltfptr[6] = /*_._IFELSE___V8*/ meltfptr[7];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:4114:/ clear");
                    /*clear*/ /*_#IS_A__L4*/
                    meltfnum[3] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V8*/
                    meltfptr[7] = 0 ;
                }
                ;
            }
        ;
        /*_#SZ__L5*/
        meltfnum[3] =
            /* jsonobject_size */ melt_jsonobject_size(/*_.VJOB__V2*/ meltfptr[1]) ;;
        /*^compute*/
        /*_#LO__L6*/
        meltfnum[5] = 0;;
        /*^compute*/
        /*_#HI__L7*/
        meltfnum[6] =
            ((/*_#SZ__L5*/ meltfnum[3]) - (1));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_STRING__L8*/
        meltfnum[7] =
            (melt_magic_discr((melt_ptr_t)(/*_.VNAME__V7*/ meltfptr[6])) == MELTOBMAG_STRING);;
        /*^compute*/
        /*_#NOT__L9*/
        meltfnum[8] =
            (!(/*_#IS_STRING__L8*/ meltfnum[7]));;
        MELT_LOCATION("warmelt-base.melt:4123:/ cond");
        /*cond*/
        if (/*_#NOT__L9*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4124:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:4124:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IF___V12*/
                    meltfptr[8] = /*_.RETURN___V13*/ meltfptr[10];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:4123:/ clear");
                    /*clear*/ /*_.RETURN___V13*/
                    meltfptr[10] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V12*/ meltfptr[8] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#eqeqI__L10*/
        meltfnum[9] =
            ((/*_#SZ__L5*/ meltfnum[3]) == (0));;
        MELT_LOCATION("warmelt-base.melt:4125:/ cond");
        /*cond*/
        if (/*_#eqeqI__L10*/ meltfnum[9]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4126:/ quasiblock");


                    /*_._RETVAL___V1*/
                    meltfptr[0] = (/*nil*/NULL);;

                    {
                        MELT_LOCATION("warmelt-base.melt:4126:/ locexp");
                        /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                        if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                            melt_warn_for_no_expected_secondary_results();
                        /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                        ;
                    }
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/
                    goto meltlabend_rout ;
                    /*_._IF___V14*/
                    meltfptr[7] = /*_.RETURN___V15*/ meltfptr[10];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-base.melt:4125:/ clear");
                    /*clear*/ /*_.RETURN___V15*/
                    meltfptr[10] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V14*/ meltfptr[7] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-base.melt:4127:/ loop");
        /*loop*/
        {
meltlabloop_GETLOOP_1:;/*^loopbody*/

            /*^block*/
            /*anyblock*/
            {


                MELT_CHECK_SIGNAL();
                ;

                MELT_CHECK_SIGNAL();
                ;
                /*_#plI__L11*/
                meltfnum[10] =
                    ((/*_#LO__L6*/ meltfnum[5]) + (3));;
                /*^compute*/
                /*_#gtI__L12*/
                meltfnum[11] =
                    ((/*_#plI__L11*/ meltfnum[10]) > (/*_#HI__L7*/ meltfnum[6]));;
                MELT_LOCATION("warmelt-base.melt:4129:/ cond");
                /*cond*/
                if (/*_#gtI__L12*/ meltfnum[11]) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:4130:/ quasiblock");


                            /*^compute*/
                            /*_.GETLOOP__V17*/
                            meltfptr[16] =  /*reallynil*/ NULL ;;

                            /*^exit*/
                            /*exit*/
                            {
                                goto meltlabexit_GETLOOP_1;
                            }
                            ;
                            /*epilog*/
                        }
                        ;
                    } /*noelse*/
                ;
                MELT_LOCATION("warmelt-base.melt:4131:/ quasiblock");


                /*_#plI__L14*/
                meltfnum[13] =
                    ((/*_#LO__L6*/ meltfnum[5]) + (/*_#HI__L7*/ meltfnum[6]));;
                /*^compute*/
                /*_#MI__L15*/
                meltfnum[14] =
                    ((/*_#plI__L14*/ meltfnum[13]) / (2));;
                /*^compute*/
                /*_.MIDNAME__V18*/
                meltfptr[17] =
                    /* jsonobject_nth_name */ melt_jsonobject_nth_name (/*_.VJOB__V2*/ meltfptr[1], (int)/*_#MI__L15*/ meltfnum[14]) ;;

                MELT_CHECK_SIGNAL();
                ;

                MELT_CHECK_SIGNAL();
                ;
                MELT_LOCATION("warmelt-base.melt:4134:/ apply");
                /*apply*/
                {
                    union meltparam_un argtab[1];
                    memset(&argtab, 0, sizeof(argtab));
                    /*^apply.arg*/
                    argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.MIDNAME__V18*/ meltfptr[17];
                    /*_.JSON_NAME_LESS__V19*/
                    meltfptr[18] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_NAME_LESS*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.VNAME__V7*/ meltfptr[6]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                }
                ;
                /*^cond*/
                /*cond*/
                if (/*_.JSON_NAME_LESS__V19*/ meltfptr[18]) /*then*/
                    {
                        /*^cond.then*/
                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:4135:/ compute");
                            /*_#HI__L7*/
                            meltfnum[6] = /*_#SETQ___L17*/ meltfnum[16] = /*_#MI__L15*/ meltfnum[14];;
                            /*_#_IFELSE___L16*/
                            meltfnum[15] = /*_#SETQ___L17*/ meltfnum[16];;
                            /*epilog*/

                            MELT_LOCATION("warmelt-base.melt:4134:/ clear");
                            /*clear*/ /*_#SETQ___L17*/
                            meltfnum[16] = 0 ;
                        }
                        ;
                    }
                else    /*^cond.else*/
                    {

                        /*^block*/
                        /*anyblock*/
                        {

                            MELT_LOCATION("warmelt-base.melt:4136:/ compute");
                            /*_#LO__L6*/
                            meltfnum[5] = /*_#SETQ___L18*/ meltfnum[16] = /*_#MI__L15*/ meltfnum[14];;
                            /*_#_IFELSE___L16*/
                            meltfnum[15] = /*_#SETQ___L18*/ meltfnum[16];;
                            /*epilog*/

                            MELT_LOCATION("warmelt-base.melt:4134:/ clear");
                            /*clear*/ /*_#SETQ___L18*/
                            meltfnum[16] = 0 ;
                        }
                        ;
                    }
                ;
                /*_#LET___L13*/
                meltfnum[12] = /*_#_IFELSE___L16*/ meltfnum[15];;

                MELT_LOCATION("warmelt-base.melt:4131:/ clear");
                /*clear*/ /*_#plI__L14*/
                meltfnum[13] = 0 ;
                /*^clear*/
                /*clear*/ /*_#MI__L15*/
                meltfnum[14] = 0 ;
                /*^clear*/
                /*clear*/ /*_.MIDNAME__V18*/
                meltfptr[17] = 0 ;
                /*^clear*/
                /*clear*/ /*_.JSON_NAME_LESS__V19*/
                meltfptr[18] = 0 ;
                /*^clear*/
                /*clear*/ /*_#_IFELSE___L16*/
                meltfnum[15] = 0 ;

                MELT_CHECK_SIGNAL();
                ;
                /*epilog*/

                MELT_LOCATION("warmelt-base.melt:4127:/ clear");
                /*clear*/ /*_#plI__L11*/
                meltfnum[10] = 0 ;
                /*^clear*/
                /*clear*/ /*_#gtI__L12*/
                meltfnum[11] = 0 ;
                /*^clear*/
                /*clear*/ /*_#LET___L13*/
                meltfnum[12] = 0 ;
            }
            ;
            ;
            goto meltlabloop_GETLOOP_1;
meltlabexit_GETLOOP_1:;/*^loopepilog*/
            /*loopepilog*/
            /*_.FOREVER___V16*/
            meltfptr[10] = /*_.GETLOOP__V17*/ meltfptr[16];;
        }
        ;
        /*citerblock FOREACH_LONG_UPTO*/
        {
            /* foreach_long_upto start meltcit1__EACHLONG */
            long meltcit1__EACHLONG_min =  /*_#LO__L6*/ meltfnum[5];
            long meltcit1__EACHLONG_max = /*_#HI__L7*/ meltfnum[6];
            long meltcit1__EACHLONG_cur = 0;
            for (meltcit1__EACHLONG_cur = meltcit1__EACHLONG_min;
                    meltcit1__EACHLONG_cur <= meltcit1__EACHLONG_max;
                    meltcit1__EACHLONG_cur ++)
                {
                    /*_#IX__L19*/ meltfnum[16] = meltcit1__EACHLONG_cur;



                    MELT_LOCATION("warmelt-base.melt:4140:/ quasiblock");


                    /*_.CURNAME__V21*/
                    meltfptr[18] =
                        /* jsonobject_nth_name */ melt_jsonobject_nth_name (/*_.VJOB__V2*/ meltfptr[1], (int)/*_#IX__L19*/ meltfnum[16]) ;;

                    MELT_CHECK_SIGNAL();
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4142:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[1];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.VNAME__V7*/ meltfptr[6];
                        /*_.JSON_NAME_EQUAL__V22*/
                        meltfptr[21] =  melt_apply ((meltclosure_ptr_t)((/*!JSON_NAME_EQUAL*/ meltfrout->tabval[2])), (melt_ptr_t)(/*_.CURNAME__V21*/ meltfptr[18]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    /*^cond*/
                    /*cond*/
                    if (/*_.JSON_NAME_EQUAL__V22*/ meltfptr[21]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-base.melt:4143:/ quasiblock");


                                /*_.CURVAL__V25*/
                                meltfptr[24] =
                                    /* jsonobject_nth_value */ melt_jsonobject_nth_value (/*_.VJOB__V2*/ meltfptr[1], (int)/*_#IX__L19*/ meltfnum[16]) ;;

                                MELT_CHECK_SIGNAL();
                                ;
                                MELT_LOCATION("warmelt-base.melt:4144:/ quasiblock");


                                /*_._RETVAL___V1*/
                                meltfptr[0] = /*_.CURVAL__V25*/ meltfptr[24];;

                                {
                                    MELT_LOCATION("warmelt-base.melt:4144:/ locexp");
                                    /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
                                    if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                                        melt_warn_for_no_expected_secondary_results();
                                    /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
                                    ;
                                }
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/
                                goto meltlabend_rout ;
                                /*_.LET___V24*/
                                meltfptr[23] = /*_.RETURN___V26*/ meltfptr[25];;

                                MELT_LOCATION("warmelt-base.melt:4143:/ clear");
                                /*clear*/ /*_.CURVAL__V25*/
                                meltfptr[24] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.RETURN___V26*/
                                meltfptr[25] = 0 ;
                                /*_._IF___V23*/
                                meltfptr[22] = /*_.LET___V24*/ meltfptr[23];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4142:/ clear");
                                /*clear*/ /*_.LET___V24*/
                                meltfptr[23] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V23*/ meltfptr[22] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.LET___V20*/
                    meltfptr[17] = /*_._IF___V23*/ meltfptr[22];;

                    MELT_LOCATION("warmelt-base.melt:4140:/ clear");
                    /*clear*/ /*_.CURNAME__V21*/
                    meltfptr[18] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.JSON_NAME_EQUAL__V22*/
                    meltfptr[21] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IF___V23*/
                    meltfptr[22] = 0 ;
                } /*end foreach_long_upto meltcit1__EACHLONG */

            /*citerepilog*/

            MELT_LOCATION("warmelt-base.melt:4137:/ clear");
            /*clear*/ /*_#IX__L19*/
            meltfnum[16] = 0 ;
            /*^clear*/
            /*clear*/ /*_.LET___V20*/
            meltfptr[17] = 0 ;
        } /*endciterblock FOREACH_LONG_UPTO*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4148:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = (/*nil*/NULL);;

        {
            MELT_LOCATION("warmelt-base.melt:4148:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*_.LET___V6*/
        meltfptr[4] = /*_.RETURN___V27*/ meltfptr[24];;

        MELT_LOCATION("warmelt-base.melt:4113:/ clear");
        /*clear*/ /*_#IS_STRING__L3*/
        meltfnum[2] = 0 ;
        /*^clear*/
        /*clear*/ /*_.VNAME__V7*/
        meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_#SZ__L5*/
        meltfnum[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#LO__L6*/
        meltfnum[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_#HI__L7*/
        meltfnum[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L8*/
        meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L9*/
        meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V12*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_#eqeqI__L10*/
        meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V14*/
        meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.FOREVER___V16*/
        meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V27*/
        meltfptr[24] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4109:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V6*/ meltfptr[4];;

        {
            MELT_LOCATION("warmelt-base.melt:4109:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_#IS_JSONOBJECT__L1*/
        meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L2*/
        meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V6*/
        meltfptr[4] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("JSONOBJECT_GET_NAMED", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_47_WARMELTmiBASE_JSONOBJECT_GET_NAMED*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD fromline 1752 */

    /** start of frame for meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD// fromline 1568
        : public Melt_CallFrameWithValues<31>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[6];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<31> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD), clos) {};
        MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD() //the constructor fromline 1642
            : Melt_CallFrameWithValues<31> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<31> (fil,lin, sizeof(MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD)) {};
        MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<31> (fil,lin, sizeof(MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD


    /** end of frame for meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD fromline 1697**/

    /* end of frame for routine meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD fromline 1756 */

    /* classy proc frame meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD */
    MeltFrame_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("OUTJSON_JSONOBJ_METHOD", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:4175:/ getarg");
    /*_.JSOB__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.OUT__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4176:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OUT__L1*/
            meltfnum[0] =
                (melt_is_out ((melt_ptr_t) /*_.OUT__V3*/ meltfptr[2])) ;;
            MELT_LOCATION("warmelt-base.melt:4176:/ cond");
            /*cond*/
            if (/*_#IS_OUT__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V5*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4176:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check out";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4176;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.OUT__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V6*/
                            meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V5*/
                        meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V6*/ meltfptr[5];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4176:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V6*/
                        meltfptr[5] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V4*/
            meltfptr[3] = /*_._IFELSE___V5*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4176:/ clear");
            /*clear*/ /*_#IS_OUT__L1*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V5*/
            meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V4*/ meltfptr[3] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4177:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_JSONOBJECT__L2*/
            meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.JSOB__V2*/ meltfptr[1])) == MELTOBMAG_JSONOBJECT);;
            MELT_LOCATION("warmelt-base.melt:4177:/ cond");
            /*cond*/
            if (/*_#IS_JSONOBJECT__L2*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V8*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4177:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check jsob";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4177;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.JSOB__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V9*/
                            meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V8*/
                        meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4177:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V9*/
                        meltfptr[8] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V7*/
            meltfptr[5] = /*_._IFELSE___V8*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4177:/ clear");
            /*clear*/ /*_#IS_JSONOBJECT__L2*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V8*/
            meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V7*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4178:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_cstring =  "{";
            /*_.ADD2OUT__V10*/
            meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*citerblock FOREACH_ENTRY_IN_JSONOBJECT*/
        {
            /* foreach_entry_in_jsonobject start meltcit1__EACHJSON */
            unsigned sz_meltcit1__EACHJSON =  melt_jsonobject_size(/*_.JSOB__V2*/ meltfptr[1]);
            for (/*_#IX__L3*/ meltfnum[0] = 0L;
                              /*_#IX__L3*/ meltfnum[0] < (long) sz_meltcit1__EACHJSON && /*_.JSOB__V2*/ meltfptr[1];
                              /*_#IX__L3*/ meltfnum[0]++)
                {
                    /*_.CURAT__V11*/ meltfptr[4] = melt_jsonobject_nth_name (/*_.JSOB__V2*/ meltfptr[1], /*_#IX__L3*/ meltfnum[0]);
                    if (!/*_.CURAT__V11*/ meltfptr[4]) continue;
                    /*_.CURVAL__V12*/
                    meltfptr[11] = melt_jsonobject_nth_value (/*_.JSOB__V2*/ meltfptr[1], /*_#IX__L3*/ meltfnum[0]);
                    /* begin inside foreach_entry_in_jsonobject meltcit1__EACHJSON */




                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4182:/ cond");
                    /*cond*/
                    if (/*_#IX__L3*/ meltfnum[0]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*^apply*/
                                /*apply*/
                                {
                                    union meltparam_un argtab[1];
                                    memset(&argtab, 0, sizeof(argtab));
                                    /*^apply.arg*/
                                    argtab[0].meltbp_cstring =  ",";
                                    /*_.ADD2OUT__V14*/
                                    meltfptr[13] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
                                }
                                ;
                                /*_._IF___V13*/
                                meltfptr[12] = /*_.ADD2OUT__V14*/ meltfptr[13];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4182:/ clear");
                                /*clear*/ /*_.ADD2OUT__V14*/
                                meltfptr[13] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V13*/ meltfptr[12] =  /*reallynil*/ NULL ;;
                        }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    /*^compute*/
                    /*_#IS_STRING__L4*/
                    meltfnum[3] =
                        (melt_magic_discr((melt_ptr_t)(/*_.CURAT__V11*/ meltfptr[4])) == MELTOBMAG_STRING);;
                    MELT_LOCATION("warmelt-base.melt:4183:/ cond");
                    /*cond*/
                    if (/*_#IS_STRING__L4*/ meltfnum[3]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {




                                {
                                    MELT_LOCATION("warmelt-base.melt:4184:/ locexp");
                                    meltgc_add_out_cstr((melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]),
                                                        melt_string_str((melt_ptr_t)(/*_.CURAT__V11*/ meltfptr[4])));
                                }
                                ;
                                /*clear*/ /*_._IFELSE___V15*/
                                meltfptr[13] = 0 ;
                                /*epilog*/
                            }
                            ;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-base.melt:4183:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_A__L5*/
                                meltfnum[4] =
                                    melt_is_instance_of((melt_ptr_t)(/*_.CURAT__V11*/ meltfptr[4]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[2])));;
                                MELT_LOCATION("warmelt-base.melt:4185:/ cond");
                                /*cond*/
                                if (/*_#IS_A__L5*/ meltfnum[4]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-base.melt:4186:/ quasiblock");


                                            /*^cond*/
                                            /*cond*/
                                            if (
                                                /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.CURAT__V11*/ meltfptr[4]),
                                                                              (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[2])))
                                            ) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^getslot*/
                                                    {
                                                        melt_ptr_t slot=NULL, obj=NULL;
                                                        obj = (melt_ptr_t)(/*_.CURAT__V11*/ meltfptr[4]) /*=obj*/;
                                                        melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                                                        /*_.ATNAM__V18*/
                                                        meltfptr[17] = slot;
                                                    };
                                                    ;
                                                }
                                            else    /*^cond.else*/
                                                {

                                                    /*_.ATNAM__V18*/ meltfptr[17] =  /*reallynil*/ NULL ;;
                                                }
                                            ;

#if MELT_HAVE_DEBUG
                                            MELT_LOCATION("warmelt-base.melt:4188:/ cppif.then");
                                            /*^block*/
                                            /*anyblock*/
                                            {


                                                MELT_CHECK_SIGNAL();
                                                ;
                                                /*_#IS_STRING__L6*/
                                                meltfnum[5] =
                                                    (melt_magic_discr((melt_ptr_t)(/*_.ATNAM__V18*/ meltfptr[17])) == MELTOBMAG_STRING);;
                                                MELT_LOCATION("warmelt-base.melt:4188:/ cond");
                                                /*cond*/
                                                if (/*_#IS_STRING__L6*/ meltfnum[5]) /*then*/
                                                    {
                                                        /*^cond.then*/
                                                        /*_._IFELSE___V20*/ meltfptr[19] = (/*nil*/NULL);;
                                                    }
                                                else
                                                    {
                                                        MELT_LOCATION("warmelt-base.melt:4188:/ cond.else");

                                                        /*^block*/
                                                        /*anyblock*/
                                                        {


                                                            MELT_CHECK_SIGNAL();
                                                            ;
                                                            /*^apply*/
                                                            /*apply*/
                                                            {
                                                                union meltparam_un argtab[4];
                                                                memset(&argtab, 0, sizeof(argtab));
                                                                /*^apply.arg*/
                                                                argtab[0].meltbp_cstring =  "check atnam";
                                                                /*^apply.arg*/
                                                                argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                                                /*^apply.arg*/
                                                                argtab[2].meltbp_long = 4188;
                                                                /*^apply.arg*/
                                                                argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ATNAM__V18*/ meltfptr[17];
                                                                /*_.MELT_ASSERT_FAILURE_FUN__V21*/
                                                                meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                            }
                                                            ;
                                                            /*_._IFELSE___V20*/
                                                            meltfptr[19] = /*_.MELT_ASSERT_FAILURE_FUN__V21*/ meltfptr[20];;
                                                            /*epilog*/

                                                            MELT_LOCATION("warmelt-base.melt:4188:/ clear");
                                                            /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V21*/
                                                            meltfptr[20] = 0 ;
                                                        }
                                                        ;
                                                    }
                                                ;
                                                /*_.IFCPP___V19*/
                                                meltfptr[18] = /*_._IFELSE___V20*/ meltfptr[19];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-base.melt:4188:/ clear");
                                                /*clear*/ /*_#IS_STRING__L6*/
                                                meltfnum[5] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_._IFELSE___V20*/
                                                meltfptr[19] = 0 ;
                                            }

#else /*MELT_HAVE_DEBUG*/
                                            /*^cppif.else*/
                                            /*_.IFCPP___V19*/ meltfptr[18] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                                            ;

                                            MELT_CHECK_SIGNAL();
                                            ;
                                            MELT_LOCATION("warmelt-base.melt:4189:/ apply");
                                            /*apply*/
                                            {
                                                union meltparam_un argtab[1];
                                                memset(&argtab, 0, sizeof(argtab));
                                                /*^apply.arg*/
                                                argtab[0].meltbp_cstring =  "\"";
                                                /*_.ADD2OUT__V22*/
                                                meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
                                            }
                                            ;

                                            {
                                                MELT_LOCATION("warmelt-base.melt:4190:/ locexp");
                                                /* output_jsonobj_method ADDNAME_CHK__1 */
                                                long namelen = strlen(melt_string_str(/*_.ATNAM__V18*/ meltfptr[17]));
                                                for (long ix=0;
                                                        ix<namelen;
                                                        ix++)
                                                    {
                                                        char curc = melt_string_str(/*_.ATNAM__V18*/ meltfptr[17])[ix];
                                                        char buf[4];
                                                        memset(buf, 0, sizeof(buf));
                                                        buf[0] = TOLOWER (curc);
                                                        buf[1] = (char)0;
                                                        meltgc_add_out_raw (/*_.OUT__V3*/ meltfptr[2], buf);
                                                    }
                                                ;
                                            }
                                            ;

                                            MELT_CHECK_SIGNAL();
                                            ;
                                            MELT_LOCATION("warmelt-base.melt:4204:/ apply");
                                            /*apply*/
                                            {
                                                union meltparam_un argtab[1];
                                                memset(&argtab, 0, sizeof(argtab));
                                                /*^apply.arg*/
                                                argtab[0].meltbp_cstring =  "\"";
                                                /*_.ADD2OUT__V23*/
                                                meltfptr[19] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
                                            }
                                            ;
                                            /*_.LET___V17*/
                                            meltfptr[16] = /*_.ADD2OUT__V23*/ meltfptr[19];;

                                            MELT_LOCATION("warmelt-base.melt:4186:/ clear");
                                            /*clear*/ /*_.ATNAM__V18*/
                                            meltfptr[17] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.IFCPP___V19*/
                                            meltfptr[18] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.ADD2OUT__V22*/
                                            meltfptr[20] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.ADD2OUT__V23*/
                                            meltfptr[19] = 0 ;
                                            /*_._IFELSE___V16*/
                                            meltfptr[15] = /*_.LET___V17*/ meltfptr[16];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:4185:/ clear");
                                            /*clear*/ /*_.LET___V17*/
                                            meltfptr[16] = 0 ;
                                        }
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*^block*/
                                        /*anyblock*/
                                        {


#if MELT_HAVE_DEBUG
                                            MELT_LOCATION("warmelt-base.melt:4207:/ cppif.then");
                                            /*^block*/
                                            /*anyblock*/
                                            {


                                                MELT_CHECK_SIGNAL();
                                                ;
                                                /*^cond*/
                                                /*cond*/
                                                if ((/*nil*/NULL)) /*then*/
                                                    {
                                                        /*^cond.then*/
                                                        /*_._IFELSE___V25*/ meltfptr[18] = (/*nil*/NULL);;
                                                    }
                                                else
                                                    {
                                                        MELT_LOCATION("warmelt-base.melt:4207:/ cond.else");

                                                        /*^block*/
                                                        /*anyblock*/
                                                        {


                                                            MELT_CHECK_SIGNAL();
                                                            ;
                                                            /*^apply*/
                                                            /*apply*/
                                                            {
                                                                union meltparam_un argtab[4];
                                                                memset(&argtab, 0, sizeof(argtab));
                                                                /*^apply.arg*/
                                                                argtab[0].meltbp_cstring =  "invalid JSON attr";
                                                                /*^apply.arg*/
                                                                argtab[1].meltbp_cstring =  "warmelt-base.melt";
                                                                /*^apply.arg*/
                                                                argtab[2].meltbp_long = 4207;
                                                                /*^apply.arg*/
                                                                argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.CURAT__V11*/ meltfptr[4];
                                                                /*_.MELT_ASSERT_FAILURE_FUN__V26*/
                                                                meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                            }
                                                            ;
                                                            /*_._IFELSE___V25*/
                                                            meltfptr[18] = /*_.MELT_ASSERT_FAILURE_FUN__V26*/ meltfptr[20];;
                                                            /*epilog*/

                                                            MELT_LOCATION("warmelt-base.melt:4207:/ clear");
                                                            /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V26*/
                                                            meltfptr[20] = 0 ;
                                                        }
                                                        ;
                                                    }
                                                ;
                                                /*_.IFCPP___V24*/
                                                meltfptr[17] = /*_._IFELSE___V25*/ meltfptr[18];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-base.melt:4207:/ clear");
                                                /*clear*/ /*_._IFELSE___V25*/
                                                meltfptr[18] = 0 ;
                                            }

#else /*MELT_HAVE_DEBUG*/
                                            /*^cppif.else*/
                                            /*_.IFCPP___V24*/ meltfptr[17] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
                                            ;
                                            MELT_LOCATION("warmelt-base.melt:4206:/ quasiblock");


                                            /*_.PROGN___V27*/
                                            meltfptr[19] = /*_.IFCPP___V24*/ meltfptr[17];;
                                            /*^compute*/
                                            /*_._IFELSE___V16*/
                                            meltfptr[15] = /*_.PROGN___V27*/ meltfptr[19];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-base.melt:4185:/ clear");
                                            /*clear*/ /*_.IFCPP___V24*/
                                            meltfptr[17] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.PROGN___V27*/
                                            meltfptr[19] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V15*/
                                meltfptr[13] = /*_._IFELSE___V16*/ meltfptr[15];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4183:/ clear");
                                /*clear*/ /*_#IS_A__L5*/
                                meltfnum[4] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V16*/
                                meltfptr[15] = 0 ;
                            }
                            ;
                        }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4208:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[1];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_cstring =  ":";
                        /*_.ADD2OUT__V28*/
                        meltfptr[16] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4209:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[1];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.CURVAL__V12*/ meltfptr[11];
                        /*_.OUTPUT_JSON__V29*/
                        meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!OUTPUT_JSON*/ meltfrout->tabval[3])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    /* foreach_entry_in_jsonobject end meltcit1__EACHJSON */
                    /*_.CURAT__V11*/
                    meltfptr[4] = NULL;
                    /*_.CURVAL__V12*/
                    meltfptr[11] = NULL;
                }

            /*citerepilog*/

            MELT_LOCATION("warmelt-base.melt:4179:/ clear");
            /*clear*/ /*_.CURAT__V11*/
            meltfptr[4] = 0 ;
            /*^clear*/
            /*clear*/ /*_.CURVAL__V12*/
            meltfptr[11] = 0 ;
            /*^clear*/
            /*clear*/ /*_#IX__L3*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V13*/
            meltfptr[12] = 0 ;
            /*^clear*/
            /*clear*/ /*_#IS_STRING__L4*/
            meltfnum[3] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/
            meltfptr[13] = 0 ;
            /*^clear*/
            /*clear*/ /*_.ADD2OUT__V28*/
            meltfptr[16] = 0 ;
            /*^clear*/
            /*clear*/ /*_.OUTPUT_JSON__V29*/
            meltfptr[20] = 0 ;
        } /*endciterblock FOREACH_ENTRY_IN_JSONOBJECT*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4211:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_cstring =  "}";
            /*_.ADD2OUT__V30*/
            meltfptr[18] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4212:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = (/*nil*/NULL);;

        {
            MELT_LOCATION("warmelt-base.melt:4212:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4175:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.RETURN___V31*/ meltfptr[17];;

        {
            MELT_LOCATION("warmelt-base.melt:4175:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V7*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ADD2OUT__V10*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ADD2OUT__V30*/
        meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V31*/
        meltfptr[17] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("OUTJSON_JSONOBJ_METHOD", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_48_WARMELTmiBASE_OUTJSON_JSONOBJ_METHOD*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD fromline 1752 */

    /** start of frame for meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD// fromline 1568
        : public Melt_CallFrameWithValues<15>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[3];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<15> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD), clos) {};
        MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD() //the constructor fromline 1642
            : Melt_CallFrameWithValues<15> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<15> (fil,lin, sizeof(MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD)) {};
        MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<15> (fil,lin, sizeof(MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD


    /** end of frame for meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD fromline 1697**/

    /* end of frame for routine meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD fromline 1756 */

    /* classy proc frame meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD */
    MeltFrame_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("OUTJSON_MULTIPLE_METHOD", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:4216:/ getarg");
    /*_.TUP__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.OUT__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4217:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OUT__L1*/
            meltfnum[0] =
                (melt_is_out ((melt_ptr_t) /*_.OUT__V3*/ meltfptr[2])) ;;
            MELT_LOCATION("warmelt-base.melt:4217:/ cond");
            /*cond*/
            if (/*_#IS_OUT__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V5*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4217:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check out";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4217;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.OUT__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V6*/
                            meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V5*/
                        meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V6*/ meltfptr[5];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4217:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V6*/
                        meltfptr[5] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V4*/
            meltfptr[3] = /*_._IFELSE___V5*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4217:/ clear");
            /*clear*/ /*_#IS_OUT__L1*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V5*/
            meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V4*/ meltfptr[3] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4218:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_MULTIPLE__L2*/
            meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.TUP__V2*/ meltfptr[1])) == MELTOBMAG_MULTIPLE);;
            MELT_LOCATION("warmelt-base.melt:4218:/ cond");
            /*cond*/
            if (/*_#IS_MULTIPLE__L2*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V8*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4218:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check tup";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4218;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.TUP__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V9*/
                            meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V8*/
                        meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4218:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V9*/
                        meltfptr[8] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V7*/
            meltfptr[5] = /*_._IFELSE___V8*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4218:/ clear");
            /*clear*/ /*_#IS_MULTIPLE__L2*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V8*/
            meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V7*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4219:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_cstring =  "[";
            /*_.ADD2OUT__V10*/
            meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*citerblock FOREACH_IN_MULTIPLE*/
        {
            /* start foreach_in_multiple meltcit1__EACHTUP */
            long  meltcit1__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.TUP__V2*/ meltfptr[1]);
            for (/*_#IX__L3*/ meltfnum[0] = 0;
                              (/*_#IX__L3*/ meltfnum[0] >= 0) && (/*_#IX__L3*/ meltfnum[0] <  meltcit1__EACHTUP_ln);
                              /*_#IX__L3*/ meltfnum[0]++)
                {
                    /*_.CURCOMP__V11*/ meltfptr[4] = melt_multiple_nth((melt_ptr_t)(/*_.TUP__V2*/ meltfptr[1]),  /*_#IX__L3*/ meltfnum[0]);




                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4223:/ cond");
                    /*cond*/
                    if (/*_#IX__L3*/ meltfnum[0]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*^apply*/
                                /*apply*/
                                {
                                    union meltparam_un argtab[1];
                                    memset(&argtab, 0, sizeof(argtab));
                                    /*^apply.arg*/
                                    argtab[0].meltbp_cstring =  ",";
                                    /*_.ADD2OUT__V13*/
                                    meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
                                }
                                ;
                                /*_._IF___V12*/
                                meltfptr[11] = /*_.ADD2OUT__V13*/ meltfptr[12];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-base.melt:4223:/ clear");
                                /*clear*/ /*_.ADD2OUT__V13*/
                                meltfptr[12] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V12*/ meltfptr[11] =  /*reallynil*/ NULL ;;
                        }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-base.melt:4224:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[1];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.CURCOMP__V11*/ meltfptr[4];
                        /*_.OUTPUT_JSON__V14*/
                        meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!OUTPUT_JSON*/ meltfrout->tabval[2])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    if (/*_#IX__L3*/ meltfnum[0]<0) break;
                } /* end  foreach_in_multiple meltcit1__EACHTUP */

            /*citerepilog*/

            MELT_LOCATION("warmelt-base.melt:4220:/ clear");
            /*clear*/ /*_.CURCOMP__V11*/
            meltfptr[4] = 0 ;
            /*^clear*/
            /*clear*/ /*_#IX__L3*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V12*/
            meltfptr[11] = 0 ;
            /*^clear*/
            /*clear*/ /*_.OUTPUT_JSON__V14*/
            meltfptr[12] = 0 ;
        } /*endciterblock FOREACH_IN_MULTIPLE*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4225:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_cstring =  "]";
            /*_.ADD2OUT__V15*/
            meltfptr[14] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[1])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4216:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.ADD2OUT__V15*/ meltfptr[14];;

        {
            MELT_LOCATION("warmelt-base.melt:4216:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V7*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ADD2OUT__V10*/
        meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ADD2OUT__V15*/
        meltfptr[14] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("OUTJSON_MULTIPLE_METHOD", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_49_WARMELTmiBASE_OUTJSON_MULTIPLE_METHOD*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1538

    /* start of frame for routine meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD fromline 1752 */

    /** start of frame for meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD// fromline 1568
        : public Melt_CallFrameWithValues<16>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[3];
        /*classy others*/
        long _meltsparel;
        void melt_mark_stuff (void)
        {
        } /*end melt_mark_stuff*/
        virtual void melt_mark_ggc_data (void)
        {
            melt_mark_values ();
            melt_mark_stuff ();
        }; /*end melt_mark_ggc_data*/
        MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<16> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD), clos) {};
        MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD() //the constructor fromline 1642
            : Melt_CallFrameWithValues<16> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<16> (fil,lin, sizeof(MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD)) {};
        MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<16> (fil,lin, sizeof(MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD


    /** end of frame for meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD fromline 1697**/

    /* end of frame for routine meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD fromline 1756 */

    /* classy proc frame meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD */
    MeltFrame_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("OUTJSON_NAMED_METHOD", meltcallcount);
    /*use arguments*/
    (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-base.melt:4231:/ getarg");
    /*_.NMD__V2*/
    meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.OUT__V3*/
    meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4232:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OUT__L1*/
            meltfnum[0] =
                (melt_is_out ((melt_ptr_t) /*_.OUT__V3*/ meltfptr[2])) ;;
            MELT_LOCATION("warmelt-base.melt:4232:/ cond");
            /*cond*/
            if (/*_#IS_OUT__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V5*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4232:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check out";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4232;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.OUT__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V6*/
                            meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V5*/
                        meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V6*/ meltfptr[5];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4232:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V6*/
                        meltfptr[5] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V4*/
            meltfptr[3] = /*_._IFELSE___V5*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4232:/ clear");
            /*clear*/ /*_#IS_OUT__L1*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V5*/
            meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V4*/ meltfptr[3] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4233:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L2*/
            meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.NMD__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-base.melt:4233:/ cond");
            /*cond*/
            if (/*_#IS_A__L2*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V8*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4233:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[4];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check nmd";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4233;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.NMD__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V9*/
                            meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V8*/
                        meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4233:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V9*/
                        meltfptr[8] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V7*/
            meltfptr[5] = /*_._IFELSE___V8*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4233:/ clear");
            /*clear*/ /*_#IS_A__L2*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V8*/
            meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V7*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-base.melt:4234:/ quasiblock");


        /*^getslot*/
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.NMD__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "NAMED_NAME");
            /*_.NAM__V11*/
            meltfptr[4] = slot;
        };
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-base.melt:4236:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_STRING__L3*/
            meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.NAM__V11*/ meltfptr[4])) == MELTOBMAG_STRING);;
            MELT_LOCATION("warmelt-base.melt:4236:/ cond");
            /*cond*/
            if (/*_#IS_STRING__L3*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V13*/ meltfptr[12] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-base.melt:4236:/ cond.else");

                    /*^block*/
                    /*anyblock*/
                    {


                        MELT_CHECK_SIGNAL();
                        ;
                        /*^apply*/
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_cstring =  "check nam";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-base.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 4236;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.NAM__V11*/ meltfptr[4];
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.NMD__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V14*/
                            meltfptr[13] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V13*/
                        meltfptr[12] = /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-base.melt:4236:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V14*/
                        meltfptr[13] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V12*/
            meltfptr[11] = /*_._IFELSE___V13*/ meltfptr[12];;
            /*epilog*/

            MELT_LOCATION("warmelt-base.melt:4236:/ clear");
            /*clear*/ /*_#IS_STRING__L3*/
            meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V13*/
            meltfptr[12] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V12*/ meltfptr[11] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4237:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_cstring =  "\"";
            /*_.ADD2OUT__V15*/
            meltfptr[13] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[2])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        {
            MELT_LOCATION("warmelt-base.melt:4238:/ locexp");
            /* outjson_named_method ADDNAME_CHK__2 */
            long namelen = strlen(melt_string_str(/*_.NAM__V11*/ meltfptr[4]));
            for (long ix=0;
                    ix<namelen;
                    ix++)
                {
                    char curc = melt_string_str(/*_.NAM__V11*/ meltfptr[4])[ix];
                    char buf[4];
                    memset(buf, 0, sizeof(buf));
                    buf[0] = TOLOWER (curc);
                    buf[1] = (char)0;
                    meltgc_add_out_raw (/*_.OUT__V3*/ meltfptr[2], buf);
                }
            ;
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4252:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_cstring =  "\"";
            /*_.ADD2OUT__V16*/
            meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!ADD2OUT*/ meltfrout->tabval[2])), (melt_ptr_t)(/*_.OUT__V3*/ meltfptr[2]), (MELTBPARSTR_CSTRING ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.LET___V10*/
        meltfptr[8] = /*_.ADD2OUT__V16*/ meltfptr[12];;

        MELT_LOCATION("warmelt-base.melt:4234:/ clear");
        /*clear*/ /*_.NAM__V11*/
        meltfptr[4] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V12*/
        meltfptr[11] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ADD2OUT__V15*/
        meltfptr[13] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ADD2OUT__V16*/
        meltfptr[12] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-base.melt:4231:/ quasiblock");


        /*_._RETVAL___V1*/
        meltfptr[0] = /*_.LET___V10*/ meltfptr[8];;

        {
            MELT_LOCATION("warmelt-base.melt:4231:/ locexp");
            /*ochecknores compilobj_nrep_return*/
#if MELT_HAVE_DEBUG
            if (meltxresdescr_ && meltxresdescr_[0] && meltxrestab_)
                melt_warn_for_no_expected_secondary_results();
            /* we warned when secondary results are expected but not returned. */
#endif /*MELT_HAVE_DEBUG*/
            ;
        }
        ;
        /*^finalreturn*/
        ;
        /*finalret*/
        goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V4*/
        meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V7*/
        meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V10*/
        meltfptr[8] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("OUTJSON_NAMED_METHOD", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_50_WARMELTmiBASE_OUTJSON_NAMED_METHOD*/




/**** end of warmelt-base+02.cc ****/
