/* GCC MELT GENERATED C++ FILE warmelt-macro+07.cc - DO NOT EDIT - see http://gcc-melt.org/ */
/* secondary MELT generated C++ file of rank #7 */
#include "melt-run.h"


/* used hash from melt-run.h when compiling this file: */
MELT_EXTERN const char meltrun_used_md5_melt_f7[] = MELT_RUN_HASHMD5 /* from melt-run.h */;


/**** warmelt-macro+07.cc declarations ****/
/**** MELT GENERATED DECLARATIONS for warmelt-macro ** DO NOT EDIT ; see gcc-melt.org ****/

/****++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
***
    Copyright 2008 - 2014  Free Software Foundation, Inc.
    Contributed by Basile Starynkevitch <basile@starynkevitch.net>

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


/** ordinary MELT module meltbuild-sources/warmelt-macro**/
#define MELT_HAS_INITIAL_ENVIRONMENT 1 /*usualmodule*/



class Melt_InitialClassyFrame_WARMELTmiMACRO_h969421184; // forward declaration fromline 6588
typedef Melt_InitialClassyFrame_WARMELTmiMACRO_h969421184 Melt_InitialFrame;
/*** 6 MELT module variables declarations ****/
MELT_EXTERN void melt_forwarding_module_data (void);
MELT_EXTERN void melt_marking_module_data (void);

MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY melt_WARMELTmiMACRO_module_var_ptr_tab[16];
MELT_EXTERN bool MELT_MODULE_VISIBILITY melt_WARMELTmiMACRO_module_var_flags[1];

static inline melt_ptr_t
melt_module_var_fetch (int ix)
{
    return (ix > 0  &&  ix <= 6)?melt_WARMELTmiMACRO_module_var_ptr_tab[ix]:NULL;
}

static inline void
melt_module_var_put (int ix, melt_ptr_t val)
{
    if (ix > 0  &&  ix <= 6)
        {
            melt_WARMELTmiMACRO_module_var_ptr_tab[ix]= val;
            melt_WARMELTmiMACRO_module_var_flags[ix/16] = true;
        }
}

/* MELT module variables indexes */
enum
{
    meltmodatix_none,
    meltmodvarix_DIAGV_GIMPLE_symb = 1,
    meltmodvarix_DIAGV_GIMPLE_SEQ_symb = 2,
    meltmodvarix_DIAGV_TREE_symb = 3,
    meltmodvarix_DIAGV_BASIC_BLOCK_symb = 4,
    meltmodvarix_DIAGV_EDGE_symb = 5,
    meltmodvarix_MELT_TRANSRUNMACRO_CLOS_symb = 6,
    meltmodatix_last
}; /* end MELT module variables indexes */

/*** 7 MELT called hook declarations ***/

/*declare MELT called hook #0 HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER **/
MELT_EXTERN melt_ptr_t melthook_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_PREVENV, const char* meltinp1_MODULNAME);

/*declare MELT called hook #1 HOOK_MACRO_EXPORTER **/
MELT_EXTERN void melthook_HOOK_MACRO_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_VAL, melt_ptr_t meltinp2_CONTENV);

/*declare MELT called hook #2 HOOK_MELT_MAKE_LOCATION **/
MELT_EXTERN melt_ptr_t melthook_HOOK_MELT_MAKE_LOCATION (melt_ptr_t melthookdatap, const char* meltinp0_FILENAME, long meltinp1_LINENO);

/*declare MELT called hook #3 HOOK_MELT_MAKE_LOCATION **/
MELT_EXTERN melt_ptr_t melthook_HOOK_MELT_MAKE_LOCATION (melt_ptr_t melthookdatap, const char* meltinp0_FILENAME, long meltinp1_LINENO);

/*declare MELT called hook #4 HOOK_PATMACRO_EXPORTER **/
MELT_EXTERN void melthook_HOOK_PATMACRO_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_MACVAL, melt_ptr_t meltinp2_PATVAL, melt_ptr_t meltinp3_CONTENV);

/*declare MELT called hook #5 HOOK_SYMBOL_IMPORTER **/
MELT_EXTERN melt_ptr_t melthook_HOOK_SYMBOL_IMPORTER (melt_ptr_t melthookdatap, const char* meltinp0_SYMNAMESTR, const char* meltinp1_MODULENAMESTR, melt_ptr_t meltinp2_PARENV);

/*declare MELT called hook #6 HOOK_VALUE_EXPORTER **/
MELT_EXTERN void melthook_HOOK_VALUE_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_VAL, melt_ptr_t meltinp2_CONTENV);

/*** end of 7 MELT called hook declarations ***/

/*** no extra MELT c-headers ***/




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_1_WARMELTmiMACRO_REGISTER_DIAG_GIMPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_2_WARMELTmiMACRO_REGISTER_DIAG_GIMPLE_SEQ(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_3_WARMELTmiMACRO_REGISTER_DIAG_TREE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_4_WARMELTmiMACRO_REGISTER_DIAG_BASIC_BLOCK(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_5_WARMELTmiMACRO_REGISTER_DIAG_EDGE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_6_WARMELTmiMACRO_DIAGNOSTIC_ARGS_MACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_7_WARMELTmiMACRO_DIAGNOSTIC_EXPAND_MESSAGE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_8_WARMELTmiMACRO_ERROR_AT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_9_WARMELTmiMACRO_FATAL_ERROR_AT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_10_WARMELTmiMACRO_WARNING_AT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_11_WARMELTmiMACRO_INFORM_AT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_12_WARMELTmiMACRO_S_EXPR_WEIGHT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_13_WARMELTmiMACRO_LAMBDA_cl1(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_14_WARMELTmiMACRO_EXPAND_RESTLIST_AS_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_15_WARMELTmiMACRO_EXPAND_RESTLIST_AS_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_16_WARMELTmiMACRO_EXPAND_PAIRLIST_AS_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_17_WARMELTmiMACRO_EXPAND_PAIRLIST_AS_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_18_WARMELTmiMACRO_EXPAND_TUPLE_SLICE_AS_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_19_WARMELTmiMACRO_REGISTER_GENERATOR_DEVICE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_20_WARMELTmiMACRO_EXPAND_APPLY(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_21_WARMELTmiMACRO_EXPAND_MSEND(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_22_WARMELTmiMACRO_EXPAND_FIELDEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_23_WARMELTmiMACRO_EXPAND_CITERATION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_24_WARMELTmiMACRO_EXPAND_CMATCHEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_25_WARMELTmiMACRO_EXPAND_FUNMATCHEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_26_WARMELTmiMACRO_EXPAND_KEYWORDFUN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_27_WARMELTmiMACRO_MACROEXPAND_1(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_28_WARMELTmiMACRO_LAMBDA_cl2(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_29_WARMELTmiMACRO_EXPAND_PRIMITIVE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_30_WARMELTmiMACRO_EXPAND_HOOK(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_31_WARMELTmiMACRO_PATTERNEXPAND_PAIRLIST_AS_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_32_WARMELTmiMACRO_LAMBDA_cl3(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_33_WARMELTmiMACRO_PATMACEXPAND_FOR_MATCHER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_34_WARMELTmiMACRO_LAMBDA_cl4(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_35_WARMELTmiMACRO_LAMBDA_cl5(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_36_WARMELTmiMACRO_PATTERN_WEIGHT_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_37_WARMELTmiMACRO_LAMBDA_cl6(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_38_WARMELTmiMACRO_PATTERNEXPAND_EXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_39_WARMELTmiMACRO_PATTERNEXPAND_1(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_40_WARMELTmiMACRO_MACROEXPAND_TOPLEVEL_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_41_WARMELTmiMACRO_LAMBDA_ARG_BINDINGS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_42_WARMELTmiMACRO_INSTALL_INITIAL_MACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_43_WARMELTmiMACRO_INSTALL_INITIAL_PATMACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_44_WARMELTmiMACRO_WARN_IF_REDEFINED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_45_WARMELTmiMACRO_FLATTEN_FOR_C_CODE_EXPANSION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_46_WARMELTmiMACRO_PARSE_PAIRLIST_C_CODE_EXPANSION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_47_WARMELTmiMACRO_CHECK_C_EXPANSION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_48_WARMELTmiMACRO_MELT_REGISTER_TRANSLATOR_RUNNER_MACROEXPANSIONS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_49_WARMELTmiMACRO_MELT_INVOKE_TRANSLATOR_RUNNER_MACROEXPANSIONS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_50_WARMELTmiMACRO_MEXPAND_DEFPRIMITIVE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_51_WARMELTmiMACRO_MEXPAND_DEFCITERATOR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_52_WARMELTmiMACRO_MEXPAND_DEFCMATCHER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_53_WARMELTmiMACRO_MEXPAND_DEFUNMATCHER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_54_WARMELTmiMACRO_MEXPAND_DEFUN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_55_WARMELTmiMACRO_MELT_DELAYED_MACRO_EXPANDER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_56_WARMELTmiMACRO_MEXPAND_DEFMACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_57_WARMELTmiMACRO_LAMBDA_cl7(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);

/** start of declaration for hook melthook_HOOK_MACRO_INSTALLER**/

/** declaration of hook melthook_HOOK_MACRO_INSTALLER */
MELT_EXTERN
void melthook_HOOK_MACRO_INSTALLER(melt_ptr_t melthookdatap,
                                   melt_ptr_t meltinp0_MBIND,
                                   melt_ptr_t meltinp1_MEXPCLOS)
;



/** end of declaration for hook melthook_HOOK_MACRO_INSTALLER**/






MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_59_WARMELTmiMACRO_MEXPAND_AT_MACRO_EXPANSION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_60_WARMELTmiMACRO_MEXPAND_DEFVAR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_61_WARMELTmiMACRO_MEXPAND_DEFHOOK(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_62_WARMELTmiMACRO_MEXPAND_DEFINE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_63_WARMELTmiMACRO_SCAN_DEFCLASS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_64_WARMELTmiMACRO_MEXPAND_DEFCLASS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_65_WARMELTmiMACRO_PARSE_FIELD_ASSIGNMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_66_WARMELTmiMACRO_LAMBDA_cl8(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_67_WARMELTmiMACRO_MEXPAND_DEFINSTANCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_68_WARMELTmiMACRO_MEXPAND_DEFSELECTOR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_69_WARMELTmiMACRO_MEXPAND_INSTANCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_70_WARMELTmiMACRO_MEXPAND_LOAD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_71_WARMELTmiMACRO_PARSE_FIELD_PATTERN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_72_WARMELTmiMACRO_LAMBDA_cl9(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_73_WARMELTmiMACRO_PATEXPAND_INSTANCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_74_WARMELTmiMACRO_LAMBDA_cl10(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_75_WARMELTmiMACRO_PATEXPAND_OBJECT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_76_WARMELTmiMACRO_LAMBDA_cl11(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_77_WARMELTmiMACRO_MEXPAND_OBJECT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_78_WARMELTmiMACRO_EXPAND_MACROSTRING_PAIRS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_79_WARMELTmiMACRO_LAMBDA_cl12(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_80_WARMELTmiMACRO_MEXPAND_CODE_CHUNK(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_81_WARMELTmiMACRO_MEXPAND_EXPR_CHUNK(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_82_WARMELTmiMACRO_MEXPAND_UNSAFE_PUT_FIELDS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_83_WARMELTmiMACRO_MEXPAND_PUT_FIELDS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_84_WARMELTmiMACRO_MEXPAND_UNSAFE_GET_FIELD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_85_WARMELTmiMACRO_MEXPAND_GET_FIELD(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_86_WARMELTmiMACRO_PAIRLIST_TO_PROGN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_87_WARMELTmiMACRO_LAMBDA_cl13(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_88_WARMELTmiMACRO_MEXPAND_SETQ(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_89_WARMELTmiMACRO_MEXPAND_IF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_90_WARMELTmiMACRO_MEXPAND_WHEN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_91_WARMELTmiMACRO_MEXPAND_UNLESS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_92_WARMELTmiMACRO_MEXPAND_WITH_CLONED_SYMB(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_93_WARMELTmiMACRO_LAMBDA_cl14(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_94_WARMELTmiMACRO_MEXPAND_CPPIF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_95_WARMELTmiMACRO_MEXPAND_COND(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_96_WARMELTmiMACRO_LAMBDA_cl15(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_97_WARMELTmiMACRO_MEXPAND_AND(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_98_WARMELTmiMACRO_LAMBDA_cl16(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_99_WARMELTmiMACRO_PATEXPAND_AS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_100_WARMELTmiMACRO_MEXPAND_AS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_101_WARMELTmiMACRO_PATEXPAND_WHEN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_102_WARMELTmiMACRO_PATEXPAND_AND(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_103_WARMELTmiMACRO_MEXPAND_OR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_104_WARMELTmiMACRO_LAMBDA_cl17(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_105_WARMELTmiMACRO_PATEXPAND_OR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_106_WARMELTmiMACRO_MEXPAND_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_107_WARMELTmiMACRO_PATEXPAND_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_108_WARMELTmiMACRO_MEXPAND_DEREF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_109_WARMELTmiMACRO_MEXPANDOBSOLETE_CONTENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_110_WARMELTmiMACRO_MEXPAND_SET_REF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_111_WARMELTmiMACRO_MEXPAND_PLUS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_112_WARMELTmiMACRO_MEXPAND_MINUS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_113_WARMELTmiMACRO_MEXPAND_TIMES(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_114_WARMELTmiMACRO_MEXPAND_DIV(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_115_WARMELTmiMACRO_MEXPAND_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_116_WARMELTmiMACRO_PATEXPAND_TUPLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_117_WARMELTmiMACRO_MEXPAND_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_118_WARMELTmiMACRO_PATEXPAND_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_119_WARMELTmiMACRO_MEXPAND_MATCH(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_120_WARMELTmiMACRO_LAMBDA_cl18(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_121_WARMELTmiMACRO_MEXPAND_MATCHALT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_122_WARMELTmiMACRO_LAMBDA_cl19(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_123_WARMELTmiMACRO_MEXPAND_LETBINDING(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_124_WARMELTmiMACRO_MEXPAND_LET(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_125_WARMELTmiMACRO_LAMBDA_cl20(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_126_WARMELTmiMACRO_LAMBDA_cl21(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_127_WARMELTmiMACRO_LAMBDA_cl22(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_128_WARMELTmiMACRO_YES_RECURSIVELY_CONSTRUCTIBLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_129_WARMELTmiMACRO_MEXPAND_LETREC(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_130_WARMELTmiMACRO_LAMBDA_cl23(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_131_WARMELTmiMACRO_LAMBDA_cl24(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_132_WARMELTmiMACRO_MEXPAND_LAMBDA(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_133_WARMELTmiMACRO_LAMBDA_cl25(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_134_WARMELTmiMACRO_MEXPAND_VARIADIC(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_135_WARMELTmiMACRO_LAMBDA_cl26(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_136_WARMELTmiMACRO_LAMBDA_cl27(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_137_WARMELTmiMACRO_LAMBDA_cl28(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_138_WARMELTmiMACRO_LAMBDA_cl29(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_139_WARMELTmiMACRO_MEXPAND_MULTICALL(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_140_WARMELTmiMACRO_LAMBDA_cl30(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_141_WARMELTmiMACRO_LAMBDA_cl31(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_142_WARMELTmiMACRO_MEXPAND_BOX(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_143_WARMELTmiMACRO_MEXPAND_CONSTANT_BOX(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_144_WARMELTmiMACRO_MEXPAND_UNBOX(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_145_WARMELTmiMACRO_MEXPAND_COMMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_146_WARMELTmiMACRO_MEXPAND_CHEADER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_147_WARMELTmiMACRO_MEXPAND_CIMPLEMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_148_WARMELTmiMACRO_MEXPAND_MODULE_IS_GPL_COMPATIBLE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_149_WARMELTmiMACRO_MEXPAND_USE_PACKAGE_FROM_PKG_CONFIG(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_150_WARMELTmiMACRO_PAIRLIST_TO_RETURN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_151_WARMELTmiMACRO_LAMBDA_cl32(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_152_WARMELTmiMACRO_MEXPAND_PROGN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_153_WARMELTmiMACRO_MEXPAND_RETURN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_154_WARMELTmiMACRO_MEXPAND_FOREVER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_155_WARMELTmiMACRO_LAMBDA_cl33(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_156_WARMELTmiMACRO_MEXPAND_EXIT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_157_WARMELTmiMACRO_LAMBDA_cl34(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_158_WARMELTmiMACRO_MEXPAND_AGAIN(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_159_WARMELTmiMACRO_MEXPAND_COMPILE_WARNING(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_160_WARMELTmiMACRO_MEXPAND_COMPILE_ERROR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_161_WARMELTmiMACRO_MEXPAND_ASSERT_MSG(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_162_WARMELTmiMACRO_MEXPAND_THIS_LINE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_166_WARMELTmiMACRO_LAMBDA_cl35(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_170_WARMELTmiMACRO_LAMBDA_cl36(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);


MELT_EXTERN void* melt_start_this_module (void*); /*mandatory start of module*/

MELT_EXTERN const char melt_module_is_gpl_compatible[];

/*declare opaque initial frame: */

typedef Melt_InitialClassyFrame_WARMELTmiMACRO_h969421184 /*opaqueinitialclassy*/ meltinitial_frame_t;


/* define different names when debugging or not */
#if MELT_HAVE_DEBUG
MELT_EXTERN const char meltmodule_WARMELTmiMACRO__melt_have_debug_enabled[];
#define melt_have_debug_string meltmodule_WARMELTmiMACRO__melt_have_debug_enabled
#else /*!MELT_HAVE_DEBUG*/
MELT_EXTERN const char meltmodule_WARMELTmiMACRO__melt_have_debug_disabled[];
#define melt_have_debug_string meltmodule_WARMELTmiMACRO__melt_have_debug_disabled
#endif /*!MELT_HAVE_DEBUG*/



void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_0 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_1 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_2 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_3 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_4 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_5 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_6 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_7 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_8 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_9 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_10 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_11 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_12 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_13 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_14 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_15 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_16 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_17 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_18 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_19 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_20 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_21 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_22 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_23 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_24 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_25 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_26 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_27 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_28 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_29 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_30 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_31 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_32 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_33 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_34 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_35 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_36 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_37 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_38 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_39 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_40 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_41 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_42 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_43 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_44 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_45 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_46 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_47 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_48 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_49 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_50 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_51 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_52 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_53 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_54 (meltinitial_frame_t*, char*);
void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMACRO__initialmeltchunk_55 (meltinitial_frame_t*, char*);


/**** warmelt-macro+07.cc implementations ****/




melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE fromline 1715 */

    /** start of frame for meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE// fromline 1531
        : public Melt_CallFrameWithValues<26>
    {
    public: /* fromline 1535*/
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
        MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<26> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE), clos) {};
        MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE() //the constructor fromline 1605
            : Melt_CallFrameWithValues<26> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<26> (fil,lin, sizeof(MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE)) {};
        MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<26> (fil,lin, sizeof(MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE


    /** end of frame for meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE fromline 1660**/

    /* end of frame for routine meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE fromline 1719 */

    /* classy proc frame meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE */ MeltFrame_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_THIS_FILE", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8276:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8277:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8277:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8277:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8277;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_this_file sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8277:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8277:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8278:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8278:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8278:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8278;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8278:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8278:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8279:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8279:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8279:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8279;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8279:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8279:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8280:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8280:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8280:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8280;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8280:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8280:/ clear");
            /*clear*/ /*_#IS_OBJECT__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8281:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8282:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V18*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8283:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V19*/ meltfptr[18] = slot;
        };
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_MIXINT__L6*/ meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])) == MELTOBMAG_MIXINT);;
        MELT_LOCATION("warmelt-macro.melt:8285:/ cond");
        /*cond*/ if (/*_#IS_MIXINT__L6*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.MIXINT_VAL__V21*/ meltfptr[20] =
                        (melt_val_mixint((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])));;
                    /*^compute*/
                    /*_.DFILNAM__V20*/ meltfptr[19] = /*_.MIXINT_VAL__V21*/ meltfptr[20];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8285:/ clear");
                    /*clear*/ /*_.MIXINT_VAL__V21*/ meltfptr[20] = 0 ;
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
                    /*_#IS_MIXLOC__L7*/ meltfnum[1] =
                        (melt_magic_discr((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])) == MELTOBMAG_MIXLOC);;
                    MELT_LOCATION("warmelt-macro.melt:8286:/ cond");
                    /*cond*/ if (/*_#IS_MIXLOC__L7*/ meltfnum[1]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                /*_.MIXLOC_VAL__V23*/ meltfptr[22] =
                                    (melt_val_mixloc((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])));;
                                /*^compute*/
                                /*_._IFELSE___V22*/ meltfptr[20] = /*_.MIXLOC_VAL__V23*/ meltfptr[22];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8286:/ clear");
                                /*clear*/ /*_.MIXLOC_VAL__V23*/ meltfptr[22] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V22*/ meltfptr[20] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.DFILNAM__V20*/ meltfptr[19] = /*_._IFELSE___V22*/ meltfptr[20];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8285:/ clear");
                    /*clear*/ /*_#IS_MIXLOC__L7*/ meltfnum[1] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V22*/ meltfptr[20] = 0 ;
                }
                ;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8288:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L8*/ meltfnum[1] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8288:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L8*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8288:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L9*/ meltfnum[8];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8288;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_this_file dfilnam=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.DFILNAM__V20*/ meltfptr[19];
                            /*_.MELT_DEBUG_FUN__V25*/ meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V24*/ meltfptr[22] = /*_.MELT_DEBUG_FUN__V25*/ meltfptr[20];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8288:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V25*/ meltfptr[20] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V24*/ meltfptr[22] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8288:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L8*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V24*/ meltfptr[22] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8289:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.DFILNAM__V20*/ meltfptr[19];;

        {
            MELT_LOCATION("warmelt-macro.melt:8289:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V17*/ meltfptr[15] = /*_.RETURN___V26*/ meltfptr[20];;

        MELT_LOCATION("warmelt-macro.melt:8281:/ clear");
        /*clear*/ /*_.CONT__V18*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V19*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_MIXINT__L6*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DFILNAM__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V26*/ meltfptr[20] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8276:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V17*/ meltfptr[15];;

        {
            MELT_LOCATION("warmelt-macro.melt:8276:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V17*/ meltfptr[15] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_THIS_FILE", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_163_WARMELTmiMACRO_MEXPAND_THIS_FILE*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG fromline 1715 */

    /** start of frame for meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG// fromline 1531
        : public Melt_CallFrameWithValues<94>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[29];
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
        MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<94> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG), clos) {};
        MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG() //the constructor fromline 1605
            : Melt_CallFrameWithValues<94> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<94> (fil,lin, sizeof(MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG)) {};
        MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<94> (fil,lin, sizeof(MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG


    /** end of frame for meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG fromline 1660**/

    /* end of frame for routine meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG fromline 1719 */

    /* classy proc frame meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG */ MeltFrame_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_DEBUG", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8302:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8303:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8303:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8303:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8303;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_debug sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8303:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8303:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8304:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8304:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8304:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8304;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8304:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8304:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8305:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8305:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8305:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8305;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8305:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8305:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8306:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8306:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8306:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8306;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8306:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8306:/ clear");
            /*clear*/ /*_#IS_OBJECT__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8307:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8308:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V18*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8309:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V19*/ meltfptr[18] = slot;
        };
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_MIXINT__L6*/ meltfnum[0] =
            (melt_magic_discr((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])) == MELTOBMAG_MIXINT);;
        MELT_LOCATION("warmelt-macro.melt:8311:/ cond");
        /*cond*/ if (/*_#IS_MIXINT__L6*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.MIXINT_VAL__V21*/ meltfptr[20] =
                        (melt_val_mixint((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])));;
                    /*^compute*/
                    /*_.DFILNAM__V20*/ meltfptr[19] = /*_.MIXINT_VAL__V21*/ meltfptr[20];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8311:/ clear");
                    /*clear*/ /*_.MIXINT_VAL__V21*/ meltfptr[20] = 0 ;
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
                    /*_#IS_MIXLOC__L7*/ meltfnum[1] =
                        (melt_magic_discr((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])) == MELTOBMAG_MIXLOC);;
                    MELT_LOCATION("warmelt-macro.melt:8312:/ cond");
                    /*cond*/ if (/*_#IS_MIXLOC__L7*/ meltfnum[1]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                /*_.MIXLOC_VAL__V23*/ meltfptr[22] =
                                    (melt_val_mixloc((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])));;
                                /*^compute*/
                                /*_._IFELSE___V22*/ meltfptr[20] = /*_.MIXLOC_VAL__V23*/ meltfptr[22];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8312:/ clear");
                                /*clear*/ /*_.MIXLOC_VAL__V23*/ meltfptr[22] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V22*/ meltfptr[20] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.DFILNAM__V20*/ meltfptr[19] = /*_._IFELSE___V22*/ meltfptr[20];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8311:/ clear");
                    /*clear*/ /*_#IS_MIXLOC__L7*/ meltfnum[1] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V22*/ meltfptr[20] = 0 ;
                }
                ;
            }
        ;
        /*_#DLINE__L8*/ meltfnum[1] =
            (melt_get_int((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8314:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!konst_5_MELT_DEBUG_FUN*/ meltfrout->tabval[5]);
            /*_.DEBUGFUNBIND__V24*/ meltfptr[22] =  melt_apply ((meltclosure_ptr_t)((/*!FIND_ENV*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8315:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!konst_6_MELT_CALLCOUNT*/ meltfrout->tabval[6]);
            /*_.THECOUNTBIND__V25*/ meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!FIND_ENV*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8316:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!konst_7_MELT_NEED_DBG*/ meltfrout->tabval[7]);
            /*_.THENEEDDBGBIND__V26*/ meltfptr[25] =  melt_apply ((meltclosure_ptr_t)((/*!FIND_ENV*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8317:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!konst_8_MELT_INCREMENT_DBGCOUNTER*/ meltfrout->tabval[8]);
            /*_.THEINCRDBGBIND__V27*/ meltfptr[26] =  melt_apply ((meltclosure_ptr_t)((/*!FIND_ENV*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.LIST_FIRST__V28*/ meltfptr[27] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V18*/ meltfptr[5])));;
        /*^compute*/
        /*_.CURPAIR__V29*/ meltfptr[28] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V28*/ meltfptr[27])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8319:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.XARGLIST__V30*/ meltfptr[29] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_PAIRLIST_AS_LIST*/ meltfrout->tabval[9])), (melt_ptr_t)(/*_.CURPAIR__V29*/ meltfptr[28]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-macro.melt:8320:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_1_st
            {
                struct meltpair_st rpair_0___PAIROFLIST_x3;
                struct meltlist_st rlist_1__LIST_;
                long meltletrec_1_endgap;
            } *meltletrec_1_ptr = 0;
            meltletrec_1_ptr = (struct meltletrec_1_st *) meltgc_allocate (sizeof (struct meltletrec_1_st), 0);
            /*^blockmultialloc.initfill*/
            /*inipair rpair_0___PAIROFLIST_x3*/
            /*_._PAIROFLIST__V32*/ meltfptr[31] = (melt_ptr_t) &meltletrec_1_ptr->rpair_0___PAIROFLIST_x3;
            meltletrec_1_ptr->rpair_0___PAIROFLIST_x3.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_PAIR))));

            /*inilist rlist_1__LIST_*/
            /*_.LIST___V33*/ meltfptr[32] = (melt_ptr_t) &meltletrec_1_ptr->rlist_1__LIST_;
            meltletrec_1_ptr->rlist_1__LIST_.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_LIST))));



            /*^putpairhead*/
            /*putpairhead*/
            melt_assertmsg("putpairhead /5 checkpair", melt_magic_discr((melt_ptr_t)(/*_._PAIROFLIST__V32*/ meltfptr[31]))== MELTOBMAG_PAIR);
            ((meltpair_ptr_t)(/*_._PAIROFLIST__V32*/ meltfptr[31]))->hd = (melt_ptr_t) ((/*nil*/NULL));
            ;
            /*^touch*/
            meltgc_touch(/*_._PAIROFLIST__V32*/ meltfptr[31]);
            ;
            /*^putlist*/
            /*putlist*/
            melt_assertmsg("putlist checklist", melt_magic_discr((melt_ptr_t)(/*_.LIST___V33*/ meltfptr[32]))== MELTOBMAG_LIST);
            ((meltlist_ptr_t)(/*_.LIST___V33*/ meltfptr[32]))->first = (meltpair_ptr_t) (/*_._PAIROFLIST__V32*/ meltfptr[31]);
            ((meltlist_ptr_t)(/*_.LIST___V33*/ meltfptr[32]))->last = (meltpair_ptr_t) (/*_._PAIROFLIST__V32*/ meltfptr[31]);
            ;
            /*^touch*/
            meltgc_touch(/*_.LIST___V33*/ meltfptr[32]);
            ;
            /*_.DBGARGLIST__V31*/ meltfptr[30] = /*_.LIST___V33*/ meltfptr[32];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8320:/ clear");
            /*clear*/ /*_._PAIROFLIST__V32*/ meltfptr[31] = 0 ;
            /*^clear*/
            /*clear*/ /*_.LIST___V33*/ meltfptr[32] = 0 ;
            /*^clear*/
            /*clear*/ /*_._PAIROFLIST__V32*/ meltfptr[31] = 0 ;
            /*^clear*/
            /*clear*/ /*_.LIST___V33*/ meltfptr[32] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8323:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            /*_.SEXPW__V34*/ meltfptr[31] =  melt_apply ((meltclosure_ptr_t)((/*!S_EXPR_WEIGHT*/ meltfrout->tabval[10])), (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
        }
        ;
        /*_#NBSEPW__L9*/ meltfnum[8] =
            (melt_get_int((melt_ptr_t)(/*_.SEXPW__V34*/ meltfptr[31])));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#gtI__L10*/ meltfnum[9] =
            ((/*_#NBSEPW__L9*/ meltfnum[8]) > (26));;
        MELT_LOCATION("warmelt-macro.melt:8326:/ cond");
        /*cond*/ if (/*_#gtI__L10*/ meltfnum[9]) /*then*/
            {
                /*^cond.then*/
                /*_#OR___L11*/ meltfnum[10] = /*_#gtI__L10*/ meltfnum[9];;
            }
        else
            {
                MELT_LOCATION("warmelt-macro.melt:8326:/ cond.else");

                /*^block*/
                /*anyblock*/
                {

                    /*_#NULL__L12*/ meltfnum[11] =
                        (/*null*/(/*_.SEXPW__V34*/ meltfptr[31]) == NULL);;
                    /*^compute*/
                    /*_#OR___L11*/ meltfnum[10] = /*_#NULL__L12*/ meltfnum[11];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8326:/ clear");
                    /*clear*/ /*_#NULL__L12*/ meltfnum[11] = 0 ;
                }
                ;
            }
        ;
        /*^cond*/
        /*cond*/ if (/*_#OR___L11*/ meltfnum[10]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8331:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[2];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_cstring =  "weight:";
                        /*^apply.arg*/
                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPW__V34*/ meltfptr[31];
                        /*_.STRING4OUT__V35*/ meltfptr[32] =  melt_apply ((meltclosure_ptr_t)((/*!STRING4OUT*/ meltfrout->tabval[11])), (melt_ptr_t)((/*!DISCR_STRING*/ meltfrout->tabval[12])), (MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;

                    {
                        MELT_LOCATION("warmelt-macro.melt:8329:/ locexp");
                        melt_warning_str(0, (melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "suspicious very heavy (DEBUG ....)"), (melt_ptr_t)(/*_.STRING4OUT__V35*/ meltfptr[32]));
                    }
                    ;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8326:/ clear");
                    /*clear*/ /*_.STRING4OUT__V35*/ meltfptr[32] = 0 ;
                }
                ;
            } /*noelse*/
        ;

        MELT_LOCATION("warmelt-macro.melt:8323:/ clear");
        /*clear*/ /*_.SEXPW__V34*/ meltfptr[31] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NBSEPW__L9*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_#gtI__L10*/ meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#OR___L11*/ meltfnum[10] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_STRING__L13*/ meltfnum[11] =
            (melt_magic_discr((melt_ptr_t)(/*_.DFILNAM__V20*/ meltfptr[19])) == MELTOBMAG_STRING);;
        /*^compute*/
        /*_#NOT__L14*/ meltfnum[8] =
            (!(/*_#IS_STRING__L13*/ meltfnum[11]));;
        MELT_LOCATION("warmelt-macro.melt:8333:/ cond");
        /*cond*/ if (/*_#NOT__L14*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8335:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "(DEBUG ...) used without file location"), (melt_ptr_t)0);
                    }
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8336:/ quasiblock");


                    /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                    {
                        MELT_LOCATION("warmelt-macro.melt:8336:/ locexp");
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
                    /*finalret*/ goto meltlabend_rout ;
                    MELT_LOCATION("warmelt-macro.melt:8334:/ quasiblock");


                    /*_.PROGN___V38*/ meltfptr[37] = /*_.RETURN___V37*/ meltfptr[31];;
                    /*^compute*/
                    /*_._IF___V36*/ meltfptr[32] = /*_.PROGN___V38*/ meltfptr[37];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8333:/ clear");
                    /*clear*/ /*_.RETURN___V37*/ meltfptr[31] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V38*/ meltfptr[37] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V36*/ meltfptr[32] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_A__L15*/ meltfnum[9] =
            melt_is_instance_of((melt_ptr_t)(/*_.DEBUGFUNBIND__V24*/ meltfptr[22]), (melt_ptr_t)((/*!CLASS_FUNCTION_BINDING*/ meltfrout->tabval[14])));;
        MELT_LOCATION("warmelt-macro.melt:8337:/ cond");
        /*cond*/ if (/*_#IS_A__L15*/ meltfnum[9]) /*then*/
            {
                /*^cond.then*/
                /*_#OR___L16*/ meltfnum[10] = /*_#IS_A__L15*/ meltfnum[9];;
            }
        else
            {
                MELT_LOCATION("warmelt-macro.melt:8337:/ cond.else");

                /*^block*/
                /*anyblock*/
                {

                    /*_#IS_A__L17*/ meltfnum[16] =
                        melt_is_instance_of((melt_ptr_t)(/*_.DEBUGFUNBIND__V24*/ meltfptr[22]), (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])));;
                    /*^compute*/
                    /*_#OR___L16*/ meltfnum[10] = /*_#IS_A__L17*/ meltfnum[16];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8337:/ clear");
                    /*clear*/ /*_#IS_A__L17*/ meltfnum[16] = 0 ;
                }
                ;
            }
        ;
        /*_#NOT__L18*/ meltfnum[16] =
            (!(/*_#OR___L16*/ meltfnum[10]));;
        MELT_LOCATION("warmelt-macro.melt:8337:/ cond");
        /*cond*/ if (/*_#NOT__L18*/ meltfnum[16]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8340:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "(DEBUG ...) used in context with bad MELT_DEBUG_FUN"), (melt_ptr_t)0);
                    }
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8341:/ quasiblock");


                    /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                    {
                        MELT_LOCATION("warmelt-macro.melt:8341:/ locexp");
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
                    /*finalret*/ goto meltlabend_rout ;
                    MELT_LOCATION("warmelt-macro.melt:8339:/ quasiblock");


                    /*_.PROGN___V41*/ meltfptr[40] = /*_.RETURN___V40*/ meltfptr[37];;
                    /*^compute*/
                    /*_._IF___V39*/ meltfptr[31] = /*_.PROGN___V41*/ meltfptr[40];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8337:/ clear");
                    /*clear*/ /*_.RETURN___V40*/ meltfptr[37] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V41*/ meltfptr[40] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V39*/ meltfptr[31] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-macro.melt:8342:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_A__L19*/ meltfnum[18] =
            melt_is_instance_of((melt_ptr_t)(/*_.THECOUNTBIND__V25*/ meltfptr[20]), (melt_ptr_t)((/*!CLASS_PRIMITIVE_BINDING*/ meltfrout->tabval[15])));;
        MELT_LOCATION("warmelt-macro.melt:8345:/ cond");
        /*cond*/ if (/*_#IS_A__L19*/ meltfnum[18]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    MELT_LOCATION("warmelt-macro.melt:8346:/ cond");
                    /*cond*/ if (
                        /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.THECOUNTBIND__V25*/ meltfptr[20]),
                                                      (melt_ptr_t)((/*!CLASS_PRIMITIVE_BINDING*/ meltfrout->tabval[15])))
                    ) /*then*/
                        {
                            /*^cond.then*/
                            /*^getslot*/
                            {
                                melt_ptr_t slot=NULL, obj=NULL;
                                obj = (melt_ptr_t)(/*_.THECOUNTBIND__V25*/ meltfptr[20]) /*=obj*/;
                                melt_object_get_field(slot,obj, 3, "PBIND_PRIMITIVE");
                                /*_.PBIND_PRIMITIVE__V43*/ meltfptr[40] = slot;
                            };
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_.PBIND_PRIMITIVE__V43*/ meltfptr[40] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.THECOUNTPRIM__V42*/ meltfptr[37] = /*_.PBIND_PRIMITIVE__V43*/ meltfptr[40];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8345:/ clear");
                    /*clear*/ /*_.PBIND_PRIMITIVE__V43*/ meltfptr[40] = 0 ;
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
                    /*_#IS_A__L20*/ meltfnum[19] =
                        melt_is_instance_of((melt_ptr_t)(/*_.THECOUNTBIND__V25*/ meltfptr[20]), (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])));;
                    MELT_LOCATION("warmelt-macro.melt:8347:/ cond");
                    /*cond*/ if (/*_#IS_A__L20*/ meltfnum[19]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-macro.melt:8348:/ cond");
                                /*cond*/ if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.THECOUNTBIND__V25*/ meltfptr[20]),
                                                                  (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.THECOUNTBIND__V25*/ meltfptr[20]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "VBIND_VALUE");
                                            /*_.VBIND_VALUE__V45*/ meltfptr[44] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.VBIND_VALUE__V45*/ meltfptr[44] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                /*^compute*/
                                /*_._IFELSE___V44*/ meltfptr[40] = /*_.VBIND_VALUE__V45*/ meltfptr[44];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8347:/ clear");
                                /*clear*/ /*_.VBIND_VALUE__V45*/ meltfptr[44] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-macro.melt:8350:/ locexp");
                                    /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "(DEBUG ...) used in context with bad THE_MELTCALLCOUNT"), (melt_ptr_t)0);
                                }
                                ;
                                MELT_LOCATION("warmelt-macro.melt:8351:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                {
                                    MELT_LOCATION("warmelt-macro.melt:8351:/ locexp");
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
                                /*finalret*/ goto meltlabend_rout ;
                                MELT_LOCATION("warmelt-macro.melt:8349:/ quasiblock");


                                /*_.PROGN___V47*/ meltfptr[46] = /*_.RETURN___V46*/ meltfptr[44];;
                                /*^compute*/
                                /*_._IFELSE___V44*/ meltfptr[40] = /*_.PROGN___V47*/ meltfptr[46];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8347:/ clear");
                                /*clear*/ /*_.RETURN___V46*/ meltfptr[44] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V47*/ meltfptr[46] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_.THECOUNTPRIM__V42*/ meltfptr[37] = /*_._IFELSE___V44*/ meltfptr[40];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8345:/ clear");
                    /*clear*/ /*_#IS_A__L20*/ meltfnum[19] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V44*/ meltfptr[40] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8355:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_2_st
            {
                struct MELT_MULTIPLE_STRUCT(0) rtup_0__TUPLREC__x10;
                long meltletrec_2_endgap;
            } *meltletrec_2_ptr = 0;
            meltletrec_2_ptr = (struct meltletrec_2_st *) meltgc_allocate (sizeof (struct meltletrec_2_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x10*/
            /*_.TUPLREC___V49*/ meltfptr[46] = (melt_ptr_t) &meltletrec_2_ptr->rtup_0__TUPLREC__x10;
            meltletrec_2_ptr->rtup_0__TUPLREC__x10.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_2_ptr->rtup_0__TUPLREC__x10.nbval = 0;


            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V49*/ meltfptr[46]);
            ;
            /*_.TUPLE___V48*/ meltfptr[44] = /*_.TUPLREC___V49*/ meltfptr[46];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8355:/ clear");
            /*clear*/ /*_.TUPLREC___V49*/ meltfptr[46] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V49*/ meltfptr[46] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8352:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_PRIMITIVE*/ meltfrout->tabval[16])), (4), "CLASS_SOURCE_PRIMITIVE");
            /*_.INST__V51*/ meltfptr[46] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[46]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SPRIM_OPER", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[46]), (3), (/*_.THECOUNTPRIM__V42*/ meltfptr[37]), "SPRIM_OPER");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[46]), (2), (/*_.TUPLE___V48*/ meltfptr[44]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V51*/ meltfptr[46], "newly made instance");
        ;
        /*_.DCOUNT__V50*/ meltfptr[40] = /*_.INST__V51*/ meltfptr[46];;

        {
            MELT_LOCATION("warmelt-macro.melt:8357:/ locexp");
            meltgc_append_list((melt_ptr_t)(/*_.DBGARGLIST__V31*/ meltfptr[30]), (melt_ptr_t)(/*_.DCOUNT__V50*/ meltfptr[40]));
        }
        ;

        MELT_LOCATION("warmelt-macro.melt:8342:/ clear");
        /*clear*/ /*_#IS_A__L19*/ meltfnum[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.THECOUNTPRIM__V42*/ meltfptr[37] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPLE___V48*/ meltfptr[44] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DCOUNT__V50*/ meltfptr[40] = 0 ;

        {
            MELT_LOCATION("warmelt-macro.melt:8359:/ locexp");
            meltgc_append_list((melt_ptr_t)(/*_.DBGARGLIST__V31*/ meltfptr[30]), (melt_ptr_t)(/*_.DFILNAM__V20*/ meltfptr[19]));
        }
        ;
        /*_.MAKE_INTEGERBOX__V52*/ meltfptr[37] =
            (meltgc_new_int((meltobject_ptr_t)((/*!DISCR_CONSTANT_INTEGER*/ meltfrout->tabval[17])), (/*_#DLINE__L8*/ meltfnum[1])));;

        {
            MELT_LOCATION("warmelt-macro.melt:8360:/ locexp");
            meltgc_append_list((melt_ptr_t)(/*_.DBGARGLIST__V31*/ meltfptr[30]), (melt_ptr_t)(/*_.MAKE_INTEGERBOX__V52*/ meltfptr[37]));
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8361:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.XARGLIST__V30*/ meltfptr[29];
            /*_.LIST_APPEND2LIST__V53*/ meltfptr[44] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_APPEND2LIST*/ meltfrout->tabval[18])), (melt_ptr_t)(/*_.DBGARGLIST__V31*/ meltfptr[30]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8362:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L21*/ meltfnum[19] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8362:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L21*/ meltfnum[19]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L22*/ meltfnum[18] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8362:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L22*/ meltfnum[18];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8362;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_debug dbgarglist";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.DBGARGLIST__V31*/ meltfptr[30];
                            /*_.MELT_DEBUG_FUN__V55*/ meltfptr[54] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V54*/ meltfptr[40] = /*_.MELT_DEBUG_FUN__V55*/ meltfptr[54];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8362:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L22*/ meltfnum[18] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V55*/ meltfptr[54] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V54*/ meltfptr[40] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8362:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L21*/ meltfnum[19] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V54*/ meltfptr[40] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8363:/ quasiblock");


        /*_#NBDBGARG__L23*/ meltfnum[18] =
            (melt_list_length((melt_ptr_t)(/*_.DBGARGLIST__V31*/ meltfptr[30])));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_A__L24*/ meltfnum[19] =
            melt_is_instance_of((melt_ptr_t)(/*_.THENEEDDBGBIND__V26*/ meltfptr[25]), (melt_ptr_t)((/*!CLASS_PRIMITIVE_BINDING*/ meltfrout->tabval[15])));;
        MELT_LOCATION("warmelt-macro.melt:8367:/ cond");
        /*cond*/ if (/*_#IS_A__L24*/ meltfnum[19]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    MELT_LOCATION("warmelt-macro.melt:8368:/ cond");
                    /*cond*/ if (
                        /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.THENEEDDBGBIND__V26*/ meltfptr[25]),
                                                      (melt_ptr_t)((/*!CLASS_PRIMITIVE_BINDING*/ meltfrout->tabval[15])))
                    ) /*then*/
                        {
                            /*^cond.then*/
                            /*^getslot*/
                            {
                                melt_ptr_t slot=NULL, obj=NULL;
                                obj = (melt_ptr_t)(/*_.THENEEDDBGBIND__V26*/ meltfptr[25]) /*=obj*/;
                                melt_object_get_field(slot,obj, 3, "PBIND_PRIMITIVE");
                                /*_.PBIND_PRIMITIVE__V58*/ meltfptr[57] = slot;
                            };
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_.PBIND_PRIMITIVE__V58*/ meltfptr[57] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.THENEEDDBG__V57*/ meltfptr[40] = /*_.PBIND_PRIMITIVE__V58*/ meltfptr[57];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8367:/ clear");
                    /*clear*/ /*_.PBIND_PRIMITIVE__V58*/ meltfptr[57] = 0 ;
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
                    /*_#IS_A__L25*/ meltfnum[24] =
                        melt_is_instance_of((melt_ptr_t)(/*_.THENEEDDBGBIND__V26*/ meltfptr[25]), (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])));;
                    MELT_LOCATION("warmelt-macro.melt:8369:/ cond");
                    /*cond*/ if (/*_#IS_A__L25*/ meltfnum[24]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-macro.melt:8370:/ cond");
                                /*cond*/ if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.THENEEDDBGBIND__V26*/ meltfptr[25]),
                                                                  (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.THENEEDDBGBIND__V26*/ meltfptr[25]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "VBIND_VALUE");
                                            /*_.VBIND_VALUE__V60*/ meltfptr[59] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.VBIND_VALUE__V60*/ meltfptr[59] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                /*^compute*/
                                /*_._IFELSE___V59*/ meltfptr[57] = /*_.VBIND_VALUE__V60*/ meltfptr[59];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8369:/ clear");
                                /*clear*/ /*_.VBIND_VALUE__V60*/ meltfptr[59] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-macro.melt:8372:/ locexp");
                                    /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "(DEBUG ...) used in context with bad MELT_NEED_DBG"), (melt_ptr_t)0);
                                }
                                ;
                                MELT_LOCATION("warmelt-macro.melt:8373:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                {
                                    MELT_LOCATION("warmelt-macro.melt:8373:/ locexp");
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
                                /*finalret*/ goto meltlabend_rout ;
                                MELT_LOCATION("warmelt-macro.melt:8371:/ quasiblock");


                                /*_.PROGN___V62*/ meltfptr[61] = /*_.RETURN___V61*/ meltfptr[59];;
                                /*^compute*/
                                /*_._IFELSE___V59*/ meltfptr[57] = /*_.PROGN___V62*/ meltfptr[61];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8369:/ clear");
                                /*clear*/ /*_.RETURN___V61*/ meltfptr[59] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V62*/ meltfptr[61] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_.THENEEDDBG__V57*/ meltfptr[40] = /*_._IFELSE___V59*/ meltfptr[57];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8367:/ clear");
                    /*clear*/ /*_#IS_A__L25*/ meltfnum[24] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V59*/ meltfptr[57] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8377:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_3_st
            {
                struct MELT_MULTIPLE_STRUCT(1) rtup_0__TUPLREC__x11;
                long meltletrec_3_endgap;
            } *meltletrec_3_ptr = 0;
            meltletrec_3_ptr = (struct meltletrec_3_st *) meltgc_allocate (sizeof (struct meltletrec_3_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x11*/
            /*_.TUPLREC___V64*/ meltfptr[61] = (melt_ptr_t) &meltletrec_3_ptr->rtup_0__TUPLREC__x11;
            meltletrec_3_ptr->rtup_0__TUPLREC__x11.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_3_ptr->rtup_0__TUPLREC__x11.nbval = 1;


            /*^putuple*/
            /*putupl#13*/
            melt_assertmsg("putupl [:8377] #13 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[61]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:8377] #13 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[61]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V64*/ meltfptr[61]))->tabval[0] = (melt_ptr_t)((/*!konst_19*/ meltfrout->tabval[19]));
            ;
            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V64*/ meltfptr[61]);
            ;
            /*_.TUPLE___V63*/ meltfptr[59] = /*_.TUPLREC___V64*/ meltfptr[61];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8377:/ clear");
            /*clear*/ /*_.TUPLREC___V64*/ meltfptr[61] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V64*/ meltfptr[61] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8374:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_PRIMITIVE*/ meltfrout->tabval[16])), (4), "CLASS_SOURCE_PRIMITIVE");
            /*_.INST__V66*/ meltfptr[61] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[61])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V66*/ meltfptr[61]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SPRIM_OPER", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[61])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V66*/ meltfptr[61]), (3), (/*_.THENEEDDBG__V57*/ meltfptr[40]), "SPRIM_OPER");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[61])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V66*/ meltfptr[61]), (2), (/*_.TUPLE___V63*/ meltfptr[59]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V66*/ meltfptr[61], "newly made instance");
        ;
        /*_.DNEEDBG__V65*/ meltfptr[57] = /*_.INST__V66*/ meltfptr[61];;

        MELT_CHECK_SIGNAL();
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8382:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[23]);
            /*_.LIST_TO_MULTIPLE__V67*/ meltfptr[66] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[22])), (melt_ptr_t)(/*_.DBGARGLIST__V31*/ meltfptr[30]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-macro.melt:8378:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_APPLY*/ meltfrout->tabval[20])), (4), "CLASS_SOURCE_APPLY");
            /*_.INST__V69*/ meltfptr[68] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V69*/ meltfptr[68])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V69*/ meltfptr[68]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SAPP_FUN", melt_magic_discr((melt_ptr_t)(/*_.INST__V69*/ meltfptr[68])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V69*/ meltfptr[68]), (3), ((/*!konst_5_MELT_DEBUG_FUN*/ meltfrout->tabval[5])), "SAPP_FUN");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V69*/ meltfptr[68])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V69*/ meltfptr[68]), (2), (/*_.LIST_TO_MULTIPLE__V67*/ meltfptr[66]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V69*/ meltfptr[68], "newly made instance");
        ;
        /*_.DCALL__V68*/ meltfptr[67] = /*_.INST__V69*/ meltfptr[68];;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_A__L26*/ meltfnum[24] =
            melt_is_instance_of((melt_ptr_t)(/*_.THEINCRDBGBIND__V27*/ meltfptr[26]), (melt_ptr_t)((/*!CLASS_PRIMITIVE_BINDING*/ meltfrout->tabval[15])));;
        MELT_LOCATION("warmelt-macro.melt:8385:/ cond");
        /*cond*/ if (/*_#IS_A__L26*/ meltfnum[24]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    MELT_LOCATION("warmelt-macro.melt:8386:/ cond");
                    /*cond*/ if (
                        /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.THEINCRDBGBIND__V27*/ meltfptr[26]),
                                                      (melt_ptr_t)((/*!CLASS_PRIMITIVE_BINDING*/ meltfrout->tabval[15])))
                    ) /*then*/
                        {
                            /*^cond.then*/
                            /*^getslot*/
                            {
                                melt_ptr_t slot=NULL, obj=NULL;
                                obj = (melt_ptr_t)(/*_.THEINCRDBGBIND__V27*/ meltfptr[26]) /*=obj*/;
                                melt_object_get_field(slot,obj, 3, "PBIND_PRIMITIVE");
                                /*_.PBIND_PRIMITIVE__V71*/ meltfptr[70] = slot;
                            };
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_.PBIND_PRIMITIVE__V71*/ meltfptr[70] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.THEINCRDBG__V70*/ meltfptr[69] = /*_.PBIND_PRIMITIVE__V71*/ meltfptr[70];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8385:/ clear");
                    /*clear*/ /*_.PBIND_PRIMITIVE__V71*/ meltfptr[70] = 0 ;
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
                    /*_#IS_A__L27*/ meltfnum[26] =
                        melt_is_instance_of((melt_ptr_t)(/*_.THEINCRDBGBIND__V27*/ meltfptr[26]), (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])));;
                    MELT_LOCATION("warmelt-macro.melt:8387:/ cond");
                    /*cond*/ if (/*_#IS_A__L27*/ meltfnum[26]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                MELT_LOCATION("warmelt-macro.melt:8388:/ cond");
                                /*cond*/ if (
                                    /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.THEINCRDBGBIND__V27*/ meltfptr[26]),
                                                                  (melt_ptr_t)((/*!CLASS_VALUE_BINDING*/ meltfrout->tabval[13])))
                                ) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^getslot*/
                                        {
                                            melt_ptr_t slot=NULL, obj=NULL;
                                            obj = (melt_ptr_t)(/*_.THEINCRDBGBIND__V27*/ meltfptr[26]) /*=obj*/;
                                            melt_object_get_field(slot,obj, 1, "VBIND_VALUE");
                                            /*_.VBIND_VALUE__V73*/ meltfptr[72] = slot;
                                        };
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*_.VBIND_VALUE__V73*/ meltfptr[72] =  /*reallynil*/ NULL ;;
                                    }
                                ;
                                /*^compute*/
                                /*_._IFELSE___V72*/ meltfptr[70] = /*_.VBIND_VALUE__V73*/ meltfptr[72];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8387:/ clear");
                                /*clear*/ /*_.VBIND_VALUE__V73*/ meltfptr[72] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-macro.melt:8390:/ locexp");
                                    /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "(DEBUG ...) used in context with bad MELT_INCREMENT_DBGCOUNTER"), (melt_ptr_t)0);
                                }
                                ;
                                MELT_LOCATION("warmelt-macro.melt:8393:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                {
                                    MELT_LOCATION("warmelt-macro.melt:8393:/ locexp");
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
                                /*finalret*/ goto meltlabend_rout ;
                                MELT_LOCATION("warmelt-macro.melt:8389:/ quasiblock");


                                /*_.PROGN___V75*/ meltfptr[74] = /*_.RETURN___V74*/ meltfptr[72];;
                                /*^compute*/
                                /*_._IFELSE___V72*/ meltfptr[70] = /*_.PROGN___V75*/ meltfptr[74];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8387:/ clear");
                                /*clear*/ /*_.RETURN___V74*/ meltfptr[72] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V75*/ meltfptr[74] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_.THEINCRDBG__V70*/ meltfptr[69] = /*_._IFELSE___V72*/ meltfptr[70];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8385:/ clear");
                    /*clear*/ /*_#IS_A__L27*/ meltfnum[26] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V72*/ meltfptr[70] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8398:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_4_st
            {
                struct MELT_MULTIPLE_STRUCT(0) rtup_0__TUPLREC__x12;
                long meltletrec_4_endgap;
            } *meltletrec_4_ptr = 0;
            meltletrec_4_ptr = (struct meltletrec_4_st *) meltgc_allocate (sizeof (struct meltletrec_4_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x12*/
            /*_.TUPLREC___V77*/ meltfptr[74] = (melt_ptr_t) &meltletrec_4_ptr->rtup_0__TUPLREC__x12;
            meltletrec_4_ptr->rtup_0__TUPLREC__x12.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_4_ptr->rtup_0__TUPLREC__x12.nbval = 0;


            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V77*/ meltfptr[74]);
            ;
            /*_.TUPLE___V76*/ meltfptr[72] = /*_.TUPLREC___V77*/ meltfptr[74];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8398:/ clear");
            /*clear*/ /*_.TUPLREC___V77*/ meltfptr[74] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V77*/ meltfptr[74] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8394:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_PRIMITIVE*/ meltfrout->tabval[16])), (4), "CLASS_SOURCE_PRIMITIVE");
            /*_.INST__V79*/ meltfptr[74] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V79*/ meltfptr[74])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V79*/ meltfptr[74]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SPRIM_OPER", melt_magic_discr((melt_ptr_t)(/*_.INST__V79*/ meltfptr[74])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V79*/ meltfptr[74]), (3), (/*_.THEINCRDBG__V70*/ meltfptr[69]), "SPRIM_OPER");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V79*/ meltfptr[74])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V79*/ meltfptr[74]), (2), (/*_.TUPLE___V76*/ meltfptr[72]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V79*/ meltfptr[74], "newly made instance");
        ;
        /*_.DINCRDBG__V78*/ meltfptr[70] = /*_.INST__V79*/ meltfptr[74];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8399:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_IF*/ meltfrout->tabval[24])), (4), "CLASS_SOURCE_IF");
            /*_.INST__V81*/ meltfptr[80] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V81*/ meltfptr[80])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V81*/ meltfptr[80]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SIF_TEST", melt_magic_discr((melt_ptr_t)(/*_.INST__V81*/ meltfptr[80])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V81*/ meltfptr[80]), (2), (/*_.DNEEDBG__V65*/ meltfptr[57]), "SIF_TEST");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SIF_THEN", melt_magic_discr((melt_ptr_t)(/*_.INST__V81*/ meltfptr[80])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V81*/ meltfptr[80]), (3), (/*_.DCALL__V68*/ meltfptr[67]), "SIF_THEN");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V81*/ meltfptr[80], "newly made instance");
        ;
        /*_.DIFDBG__V80*/ meltfptr[79] = /*_.INST__V81*/ meltfptr[80];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8408:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_5_st
            {
                struct MELT_MULTIPLE_STRUCT(0) rtup_0__TUPLREC__x13;
                long meltletrec_5_endgap;
            } *meltletrec_5_ptr = 0;
            meltletrec_5_ptr = (struct meltletrec_5_st *) meltgc_allocate (sizeof (struct meltletrec_5_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x13*/
            /*_.TUPLREC___V83*/ meltfptr[82] = (melt_ptr_t) &meltletrec_5_ptr->rtup_0__TUPLREC__x13;
            meltletrec_5_ptr->rtup_0__TUPLREC__x13.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_5_ptr->rtup_0__TUPLREC__x13.nbval = 0;


            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V83*/ meltfptr[82]);
            ;
            /*_.TUPLE___V82*/ meltfptr[81] = /*_.TUPLREC___V83*/ meltfptr[82];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8408:/ clear");
            /*clear*/ /*_.TUPLREC___V83*/ meltfptr[82] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V83*/ meltfptr[82] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8404:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_PRIMITIVE*/ meltfrout->tabval[16])), (4), "CLASS_SOURCE_PRIMITIVE");
            /*_.INST__V85*/ meltfptr[84] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V85*/ meltfptr[84])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V85*/ meltfptr[84]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SPRIM_OPER", melt_magic_discr((melt_ptr_t)(/*_.INST__V85*/ meltfptr[84])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V85*/ meltfptr[84]), (3), ((/*!VOID*/ meltfrout->tabval[25])), "SPRIM_OPER");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V85*/ meltfptr[84])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V85*/ meltfptr[84]), (2), (/*_.TUPLE___V82*/ meltfptr[81]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V85*/ meltfptr[84], "newly made instance");
        ;
        /*_.DVOID__V84*/ meltfptr[82] = /*_.INST__V85*/ meltfptr[84];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8412:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_6_st
            {
                struct MELT_MULTIPLE_STRUCT(3) rtup_0__TUPLREC__x14;
                long meltletrec_6_endgap;
            } *meltletrec_6_ptr = 0;
            meltletrec_6_ptr = (struct meltletrec_6_st *) meltgc_allocate (sizeof (struct meltletrec_6_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x14*/
            /*_.TUPLREC___V87*/ meltfptr[86] = (melt_ptr_t) &meltletrec_6_ptr->rtup_0__TUPLREC__x14;
            meltletrec_6_ptr->rtup_0__TUPLREC__x14.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_6_ptr->rtup_0__TUPLREC__x14.nbval = 3;


            /*^putuple*/
            /*putupl#14*/
            melt_assertmsg("putupl [:8412] #14 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:8412] #14 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))->tabval[0] = (melt_ptr_t)(/*_.DINCRDBG__V78*/ meltfptr[70]);
            ;
            /*^putuple*/
            /*putupl#15*/
            melt_assertmsg("putupl [:8412] #15 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:8412] #15 checkoff", (1>=0 && 1< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))->tabval[1] = (melt_ptr_t)(/*_.DIFDBG__V80*/ meltfptr[79]);
            ;
            /*^putuple*/
            /*putupl#16*/
            melt_assertmsg("putupl [:8412] #16 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:8412] #16 checkoff", (2>=0 && 2< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V87*/ meltfptr[86]))->tabval[2] = (melt_ptr_t)(/*_.DVOID__V84*/ meltfptr[82]);
            ;
            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V87*/ meltfptr[86]);
            ;
            /*_.TUPLE___V86*/ meltfptr[85] = /*_.TUPLREC___V87*/ meltfptr[86];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8412:/ clear");
            /*clear*/ /*_.TUPLREC___V87*/ meltfptr[86] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V87*/ meltfptr[86] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8409:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_PROGN*/ meltfrout->tabval[26])), (3), "CLASS_SOURCE_PROGN");
            /*_.INST__V89*/ meltfptr[88] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V89*/ meltfptr[88])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V89*/ meltfptr[88]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SPROGN_BODY", melt_magic_discr((melt_ptr_t)(/*_.INST__V89*/ meltfptr[88])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V89*/ meltfptr[88]), (2), (/*_.TUPLE___V86*/ meltfptr[85]), "SPROGN_BODY");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V89*/ meltfptr[88], "newly made instance");
        ;
        /*_.DPROGN__V88*/ meltfptr[86] = /*_.INST__V89*/ meltfptr[88];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8414:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_CPPIF*/ meltfrout->tabval[27])), (5), "CLASS_SOURCE_CPPIF");
            /*_.INST__V91*/ meltfptr[90] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V91*/ meltfptr[90])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V91*/ meltfptr[90]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SIFP_COND", melt_magic_discr((melt_ptr_t)(/*_.INST__V91*/ meltfptr[90])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V91*/ meltfptr[90]), (2), ((/*!konst_28_MELT_HAVE_DEBUG*/ meltfrout->tabval[28])), "SIFP_COND");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SIFP_THEN", melt_magic_discr((melt_ptr_t)(/*_.INST__V91*/ meltfptr[90])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V91*/ meltfptr[90]), (3), (/*_.DPROGN__V88*/ meltfptr[86]), "SIFP_THEN");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SIFP_ELSE", melt_magic_discr((melt_ptr_t)(/*_.INST__V91*/ meltfptr[90])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V91*/ meltfptr[90]), (4), (/*_.DVOID__V84*/ meltfptr[82]), "SIFP_ELSE");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V91*/ meltfptr[90], "newly made instance");
        ;
        /*_.DCPPIF__V90*/ meltfptr[89] = /*_.INST__V91*/ meltfptr[90];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8423:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L28*/ meltfnum[26] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8423:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L28*/ meltfnum[26]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L29*/ meltfnum[28] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8423:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[7];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L29*/ meltfnum[28];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8423;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_debug dcall=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.DCALL__V68*/ meltfptr[67];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  " return dcppif=";
                            /*^apply.arg*/
                            argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.DCPPIF__V90*/ meltfptr[89];
                            /*_.MELT_DEBUG_FUN__V93*/ meltfptr[92] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V92*/ meltfptr[91] = /*_.MELT_DEBUG_FUN__V93*/ meltfptr[92];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8423:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L29*/ meltfnum[28] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V93*/ meltfptr[92] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V92*/ meltfptr[91] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8423:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L28*/ meltfnum[26] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V92*/ meltfptr[91] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8424:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.DCPPIF__V90*/ meltfptr[89];;

        {
            MELT_LOCATION("warmelt-macro.melt:8424:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V56*/ meltfptr[54] = /*_.RETURN___V94*/ meltfptr[92];;

        MELT_LOCATION("warmelt-macro.melt:8363:/ clear");
        /*clear*/ /*_#NBDBGARG__L23*/ meltfnum[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L24*/ meltfnum[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.THENEEDDBG__V57*/ meltfptr[40] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPLE___V63*/ meltfptr[59] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DNEEDBG__V65*/ meltfptr[57] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_TO_MULTIPLE__V67*/ meltfptr[66] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DCALL__V68*/ meltfptr[67] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L26*/ meltfnum[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.THEINCRDBG__V70*/ meltfptr[69] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPLE___V76*/ meltfptr[72] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DINCRDBG__V78*/ meltfptr[70] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DIFDBG__V80*/ meltfptr[79] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPLE___V82*/ meltfptr[81] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DVOID__V84*/ meltfptr[82] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPLE___V86*/ meltfptr[85] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DPROGN__V88*/ meltfptr[86] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DCPPIF__V90*/ meltfptr[89] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V94*/ meltfptr[92] = 0 ;
        /*_.LET___V17*/ meltfptr[15] = /*_.LET___V56*/ meltfptr[54];;

        MELT_LOCATION("warmelt-macro.melt:8307:/ clear");
        /*clear*/ /*_.CONT__V18*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V19*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_MIXINT__L6*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DFILNAM__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_#DLINE__L8*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DEBUGFUNBIND__V24*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.THECOUNTBIND__V25*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.THENEEDDBGBIND__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_.THEINCRDBGBIND__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V29*/ meltfptr[28] = 0 ;
        /*^clear*/
        /*clear*/ /*_.XARGLIST__V30*/ meltfptr[29] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DBGARGLIST__V31*/ meltfptr[30] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L13*/ meltfnum[11] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L14*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V36*/ meltfptr[32] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L15*/ meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#OR___L16*/ meltfnum[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L18*/ meltfnum[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V39*/ meltfptr[31] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MAKE_INTEGERBOX__V52*/ meltfptr[37] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_APPEND2LIST__V53*/ meltfptr[44] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V56*/ meltfptr[54] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8302:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V17*/ meltfptr[15];;

        {
            MELT_LOCATION("warmelt-macro.melt:8302:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V17*/ meltfptr[15] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_DEBUG", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_164_WARMELTmiMACRO_MEXPAND_DEBUG*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES fromline 1715 */

    /** start of frame for meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES// fromline 1531
        : public Melt_CallFrameWithValues<32>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[8];
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
        MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<32> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES), clos) {};
        MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES() //the constructor fromline 1605
            : Melt_CallFrameWithValues<32> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<32> (fil,lin, sizeof(MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES)) {};
        MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<32> (fil,lin, sizeof(MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES


    /** end of frame for meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES fromline 1660**/

    /* end of frame for routine meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES fromline 1719 */

    /* classy proc frame meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES */ MeltFrame_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_EXPORT_VALUES", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8442:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8443:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8443:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8443:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8443;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_values sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8443:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8443:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8444:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8444:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8444:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8444;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8444:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8444:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8445:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8445:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8445:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8445;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8445:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8445:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8446:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_CLOSURE__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) == MELTOBMAG_CLOSURE);;
            MELT_LOCATION("warmelt-macro.melt:8446:/ cond");
            /*cond*/ if (/*_#IS_CLOSURE__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8446:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check mexpander";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8446;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8446:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8446:/ clear");
            /*clear*/ /*_#IS_CLOSURE__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8447:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8447:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V18*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8447:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8447;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V18*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8447:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V17*/ meltfptr[15] = /*_._IFELSE___V18*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8447:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V18*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V17*/ meltfptr[15] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8448:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8449:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V21*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8450:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V22*/ meltfptr[21] = slot;
        };
        ;
        /*_.LIST_FIRST__V23*/ meltfptr[22] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V21*/ meltfptr[5])));;
        /*^compute*/
        /*_.CURPAIR__V24*/ meltfptr[23] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V23*/ meltfptr[22])));;
        MELT_LOCATION("warmelt-macro.melt:8454:/ quasiblock");


        /*^newclosure*/
        /*newclosure*/ /*_.LAMBDA___V26*/ meltfptr[25] =
            (melt_ptr_t) meltgc_new_closure((meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE)))), (meltroutine_ptr_t)((/*!konst_8*/ meltfrout->tabval[8])), (4));
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V26*/ meltfptr[25])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 0>= 0 && 0< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V26*/ meltfptr[25])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V26*/ meltfptr[25])->tabval[0] = (melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V26*/ meltfptr[25])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 1>= 0 && 1< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V26*/ meltfptr[25])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V26*/ meltfptr[25])->tabval[1] = (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V26*/ meltfptr[25])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 2>= 0 && 2< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V26*/ meltfptr[25])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V26*/ meltfptr[25])->tabval[2] = (melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V26*/ meltfptr[25])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 3>= 0 && 3< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V26*/ meltfptr[25])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V26*/ meltfptr[25])->tabval[3] = (melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]);
        ;
        /*_.LAMBDA___V25*/ meltfptr[24] = /*_.LAMBDA___V26*/ meltfptr[25];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8452:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[5]);
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.LAMBDA___V25*/ meltfptr[24];
            /*_.SYMBTUP__V27*/ meltfptr[26] =  melt_apply ((meltclosure_ptr_t)((/*!PAIRLIST_TO_MULTIPLE*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8462:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_EXPORT_VALUES*/ meltfrout->tabval[9])), (3), "CLASS_SOURCE_EXPORT_VALUES");
            /*_.INST__V29*/ meltfptr[28] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (1), (/*_.LOC__V22*/ meltfptr[21]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPORT_NAMES", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (2), (/*_.SYMBTUP__V27*/ meltfptr[26]), "SEXPORT_NAMES");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V29*/ meltfptr[28], "newly made instance");
        ;
        /*_.RES__V28*/ meltfptr[27] = /*_.INST__V29*/ meltfptr[28];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8466:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L7*/ meltfnum[1] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8466:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L7*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L8*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8466:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L8*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8466;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_values result res";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V28*/ meltfptr[27];
                            /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V30*/ meltfptr[29] = /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8466:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L8*/ meltfnum[0] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V30*/ meltfptr[29] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8466:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L7*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V30*/ meltfptr[29] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8467:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V28*/ meltfptr[27];;

        {
            MELT_LOCATION("warmelt-macro.melt:8467:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V20*/ meltfptr[18] = /*_.RETURN___V32*/ meltfptr[30];;

        MELT_LOCATION("warmelt-macro.melt:8448:/ clear");
        /*clear*/ /*_.CONT__V21*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LAMBDA___V25*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SYMBTUP__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V32*/ meltfptr[30] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8442:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V20*/ meltfptr[18];;

        {
            MELT_LOCATION("warmelt-macro.melt:8442:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V17*/ meltfptr[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V20*/ meltfptr[18] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_EXPORT_VALUES", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_165_WARMELTmiMACRO_MEXPAND_EXPORT_VALUES*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_166_WARMELTmiMACRO_LAMBDA_cl35(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_166_WARMELTmiMACRO_LAMBDA_cl35 fromline 1715 */

    /** start of frame for meltrout_166_WARMELTmiMACRO_LAMBDA_cl35 of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35// fromline 1531
        : public Melt_CallFrameWithValues<6>
    {
    public: /* fromline 1535*/
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
        MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<6> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35), clos) {};
        MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35() //the constructor fromline 1605
            : Melt_CallFrameWithValues<6> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<6> (fil,lin, sizeof(MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35)) {};
        MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<6> (fil,lin, sizeof(MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35


    /** end of frame for meltrout_166_WARMELTmiMACRO_LAMBDA_cl35 fromline 1660**/

    /* end of frame for routine meltrout_166_WARMELTmiMACRO_LAMBDA_cl35 fromline 1719 */

    /* classy proc frame meltrout_166_WARMELTmiMACRO_LAMBDA_cl35 */ MeltFrame_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_166_WARMELTmiMACRO_LAMBDA_cl35 fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LAMBDA_cl35", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8454:/ getarg");
    /*_.S__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-macro.melt:8455:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*~ENV*/ meltfclos->tabval[1]);
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &(/*~MEXPANDER*/ meltfclos->tabval[0]);
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &(/*~MODCTX*/ meltfclos->tabval[2]);
            /*_.SYM__V4*/ meltfptr[3] =  melt_apply ((meltclosure_ptr_t)((/*~MEXPANDER*/ meltfclos->tabval[0])), (melt_ptr_t)(/*_.S__V2*/ meltfptr[1]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_NOT_A__L1*/ meltfnum[0] =
            !melt_is_instance_of((melt_ptr_t)(/*_.SYM__V4*/ meltfptr[3]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[0])));;
        MELT_LOCATION("warmelt-macro.melt:8457:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-macro.melt:8458:/ cppif.then");
                    /*^block*/
                    /*anyblock*/
                    {


                        {
                            /*^locexp*/
                            /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                            melt_dbgcounter++;
#endif
                            ;
                        }
                        ;

                        MELT_CHECK_SIGNAL();
                        ;
                        /*_#MELT_NEED_DBG__L2*/ meltfnum[1] =
                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                            ;;
                        MELT_LOCATION("warmelt-macro.melt:8458:/ cond");
                        /*cond*/ if (/*_#MELT_NEED_DBG__L2*/ meltfnum[1]) /*then*/
                            {
                                /*^cond.then*/
                                /*^block*/
                                /*anyblock*/
                                {

                                    /*_#MELT_CALLCOUNT__L3*/ meltfnum[2] =
                                        /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                        meltcallcount  /* melt_callcount debugging */
#else
                                        0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                        ;;

                                    MELT_CHECK_SIGNAL();
                                    ;
                                    MELT_LOCATION("warmelt-macro.melt:8458:/ apply");
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[5];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L3*/ meltfnum[2];
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 8458;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_cstring =  "mexpand_export_values bad sym=";
                                        /*^apply.arg*/
                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SYM__V4*/ meltfptr[3];
                                        /*_.MELT_DEBUG_FUN__V6*/ meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IF___V5*/ meltfptr[4] = /*_.MELT_DEBUG_FUN__V6*/ meltfptr[5];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-macro.melt:8458:/ clear");
                                    /*clear*/ /*_#MELT_CALLCOUNT__L3*/ meltfnum[2] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.MELT_DEBUG_FUN__V6*/ meltfptr[5] = 0 ;
                                }
                                ;
                            }
                        else    /*^cond.else*/
                            {

                                /*_._IF___V5*/ meltfptr[4] =  /*reallynil*/ NULL ;;
                            }
                        ;

                        {
                            MELT_LOCATION("warmelt-macro.melt:8458:/ locexp");
                            /*void*/(void)0;
                        }
                        ;
                        /*^quasiblock*/


                        /*epilog*/

                        /*^clear*/
                        /*clear*/ /*_#MELT_NEED_DBG__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IF___V5*/ meltfptr[4] = 0 ;
                    }

#else /*MELT_HAVE_DEBUG*/
                    /*^cppif.else*/
                    /*^block*/
                    /*anyblock*/
                    {


                        {
                            /*^locexp*/
                            /*void*/(void)0;
                        }
                        ;
                        /*epilog*/
                    }

#endif /*MELT_HAVE_DEBUG*/
                    ;

                    {
                        MELT_LOCATION("warmelt-macro.melt:8459:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)((/*~LOC*/ meltfclos->tabval[3])), ( "(EXPORT_VALUES <sym>...) expecting symbol"), (melt_ptr_t)0);
                    }
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8457:/ quasiblock");


                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.LET___V3*/ meltfptr[2] = /*_.SYM__V4*/ meltfptr[3];;

        MELT_LOCATION("warmelt-macro.melt:8455:/ clear");
        /*clear*/ /*_.SYM__V4*/ meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L1*/ meltfnum[0] = 0 ;
        MELT_LOCATION("warmelt-macro.melt:8454:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-macro.melt:8454:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V3*/ meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LAMBDA_cl35", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_166_WARMELTmiMACRO_LAMBDA_cl35_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_166_WARMELTmiMACRO_LAMBDA_cl35*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO fromline 1715 */

    /** start of frame for meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO// fromline 1531
        : public Melt_CallFrameWithValues<69>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[20];
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
        MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<69> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO), clos) {};
        MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO() //the constructor fromline 1605
            : Melt_CallFrameWithValues<69> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<69> (fil,lin, sizeof(MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO)) {};
        MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<69> (fil,lin, sizeof(MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO


    /** end of frame for meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO fromline 1660**/

    /* end of frame for routine meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO fromline 1719 */

    /* classy proc frame meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO */ MeltFrame_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_EXPORT_MACRO", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8481:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8482:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8482:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8482:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8482;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_macro sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8482:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8482:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8483:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8483:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8483:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8483;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8483:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8483:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8484:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8484:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8484:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8484;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8484:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8484:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8485:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_CLOSURE__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) == MELTOBMAG_CLOSURE);;
            MELT_LOCATION("warmelt-macro.melt:8485:/ cond");
            /*cond*/ if (/*_#IS_CLOSURE__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8485:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check mexpander";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8485;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8485:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8485:/ clear");
            /*clear*/ /*_#IS_CLOSURE__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8486:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8486:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V18*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8486:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8486;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V18*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8486:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V17*/ meltfptr[15] = /*_._IFELSE___V18*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8486:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V18*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V17*/ meltfptr[15] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8487:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8488:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V21*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8489:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V22*/ meltfptr[21] = slot;
        };
        ;
        /*_.LIST_FIRST__V23*/ meltfptr[22] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V21*/ meltfptr[5])));;
        /*^compute*/
        /*_.CURPAIR__V24*/ meltfptr[23] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V23*/ meltfptr[22])));;
        /*^compute*/
        /*_.PAIR_HEAD__V25*/ meltfptr[24] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8491:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.SYMB__V26*/ meltfptr[25] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V25*/ meltfptr[24]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.DOC__V27*/ meltfptr[26] = (/*nil*/NULL);;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_NOT_A__L7*/ meltfnum[1] =
            !melt_is_instance_of((melt_ptr_t)(/*_.SYMB__V26*/ meltfptr[25]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[4])));;
        MELT_LOCATION("warmelt-macro.melt:8494:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L7*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8495:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]), ( "(EXPORT_MACRO <sym> [<expander>]) expecting symbol"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V28*/ meltfptr[27] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        MELT_LOCATION("warmelt-macro.melt:8496:/ compute");
        /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V29*/ meltfptr[28] = /*_.PAIR_TAIL__V28*/ meltfptr[27];;
        MELT_LOCATION("warmelt-macro.melt:8497:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8498:/ cond");
        /*cond*/ if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SYMB__V26*/ meltfptr[25]),
                                          (melt_ptr_t)((/*!CLASS_NAMED*/ meltfrout->tabval[5])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^getslot*/
                {
                    melt_ptr_t slot=NULL, obj=NULL;
                    obj = (melt_ptr_t)(/*_.SYMB__V26*/ meltfptr[25]) /*=obj*/;
                    melt_object_get_field(slot,obj, 1, "NAMED_NAME");
                    /*_.SYMBNAME__V31*/ meltfptr[30] = slot;
                };
                ;
            }
        else    /*^cond.else*/
            {

                /*_.SYMBNAME__V31*/ meltfptr[30] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-macro.melt:8499:/ quasiblock");


        /*_.SE__V33*/ meltfptr[32] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8501:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L8*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8501:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L8*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8501:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L9*/ meltfnum[8];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8501;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_macro sexpv=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SE__V33*/ meltfptr[32];
                            /*_.MELT_DEBUG_FUN__V35*/ meltfptr[34] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V34*/ meltfptr[33] = /*_.MELT_DEBUG_FUN__V35*/ meltfptr[34];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8501:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V35*/ meltfptr[34] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V34*/ meltfptr[33] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8501:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L8*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V34*/ meltfptr[33] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;
        /*_.LET___V32*/ meltfptr[31] = /*_.SE__V33*/ meltfptr[32];;

        MELT_LOCATION("warmelt-macro.melt:8499:/ clear");
        /*clear*/ /*_.SE__V33*/ meltfptr[32] = 0 ;
        /*_.SEXPV__V36*/ meltfptr[34] = /*_.LET___V32*/ meltfptr[31];;
        MELT_LOCATION("warmelt-macro.melt:8503:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.SYMB__V26*/ meltfptr[25];
            /*_.CB__V38*/ meltfptr[32] =  melt_apply ((meltclosure_ptr_t)((/*!FIND_ENV*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8505:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L10*/ meltfnum[8] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8505:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L10*/ meltfnum[8]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L11*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8505:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L11*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8505;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_macro cbind=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CB__V38*/ meltfptr[32];
                            /*_.MELT_DEBUG_FUN__V40*/ meltfptr[39] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V39*/ meltfptr[38] = /*_.MELT_DEBUG_FUN__V40*/ meltfptr[39];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8505:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L11*/ meltfnum[0] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V40*/ meltfptr[39] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V39*/ meltfptr[38] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8505:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L10*/ meltfnum[8] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V39*/ meltfptr[38] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;
        /*_.LET___V37*/ meltfptr[33] = /*_.CB__V38*/ meltfptr[32];;

        MELT_LOCATION("warmelt-macro.melt:8503:/ clear");
        /*clear*/ /*_.CB__V38*/ meltfptr[32] = 0 ;
        /*_.CBIND__V41*/ meltfptr[39] = /*_.LET___V37*/ meltfptr[33];;
        /*^compute*/
        /*_#ISDEFMACRO__L12*/ meltfnum[0] =
            melt_is_instance_of((melt_ptr_t)(/*_.CBIND__V41*/ meltfptr[39]), (melt_ptr_t)((/*!CLASS_DEFINED_MACRO_BINDING*/ meltfrout->tabval[7])));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L13*/ meltfnum[8] =
            (/*null*/(/*_.SEXPV__V36*/ meltfptr[34]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8508:/ cond");
        /*cond*/ if (/*_#NULL__L13*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#NOT__L14*/ meltfnum[13] =
                        (!(/*_#ISDEFMACRO__L12*/ meltfnum[0]));;
                    MELT_LOCATION("warmelt-macro.melt:8509:/ cond");
                    /*cond*/ if (/*_#NOT__L14*/ meltfnum[13]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                MELT_LOCATION("warmelt-macro.melt:8510:/ apply");
                                /*apply*/
                                {
                                    union meltparam_un argtab[2];
                                    memset(&argtab, 0, sizeof(argtab));
                                    /*^apply.arg*/
                                    argtab[0].meltbp_cstring =  "(EXPORT_MACRO $1 <expander>) needs an expander for non-defmacro symbol";
                                    /*^apply.arg*/
                                    argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.SYMBNAME__V31*/ meltfptr[30];
                                    /*_.ERROR_AT__V44*/ meltfptr[43] =  melt_apply ((meltclosure_ptr_t)((/*!ERROR_AT*/ meltfrout->tabval[8])), (melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]), (MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                }
                                ;
                                MELT_LOCATION("warmelt-macro.melt:8512:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                {
                                    MELT_LOCATION("warmelt-macro.melt:8512:/ locexp");
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
                                /*finalret*/ goto meltlabend_rout ;
                                MELT_LOCATION("warmelt-macro.melt:8509:/ quasiblock");


                                /*_.PROGN___V46*/ meltfptr[45] = /*_.RETURN___V45*/ meltfptr[44];;
                                /*^compute*/
                                /*_._IF___V43*/ meltfptr[32] = /*_.PROGN___V46*/ meltfptr[45];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-macro.melt:8509:/ clear");
                                /*clear*/ /*_.ERROR_AT__V44*/ meltfptr[43] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.RETURN___V45*/ meltfptr[44] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V46*/ meltfptr[45] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IF___V43*/ meltfptr[32] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8508:/ quasiblock");


                    /*_.PROGN___V47*/ meltfptr[43] = /*_.SYMB__V26*/ meltfptr[25];;
                    /*^compute*/
                    /*_.EXPV__V42*/ meltfptr[38] = /*_.PROGN___V47*/ meltfptr[43];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8508:/ clear");
                    /*clear*/ /*_#NOT__L14*/ meltfnum[13] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IF___V43*/ meltfptr[32] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V47*/ meltfptr[43] = 0 ;
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
                    MELT_LOCATION("warmelt-macro.melt:8516:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[3];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                        /*^apply.arg*/
                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
                        /*^apply.arg*/
                        argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                        /*_.MEXPANDER__V48*/ meltfptr[44] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.SEXPV__V36*/ meltfptr[34]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8515:/ quasiblock");


                    /*_.PROGN___V49*/ meltfptr[45] = /*_.MEXPANDER__V48*/ meltfptr[44];;
                    /*^compute*/
                    /*_.EXPV__V42*/ meltfptr[38] = /*_.PROGN___V49*/ meltfptr[45];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8508:/ clear");
                    /*clear*/ /*_.MEXPANDER__V48*/ meltfptr[44] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V49*/ meltfptr[45] = 0 ;
                }
                ;
            }
        ;
        /*_.PAIR_TAIL__V50*/ meltfptr[32] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        MELT_LOCATION("warmelt-macro.melt:8518:/ compute");
        /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V51*/ meltfptr[43] = /*_.PAIR_TAIL__V50*/ meltfptr[32];;

        MELT_CHECK_SIGNAL();
        ;
        /*_.PAIR_HEAD__V52*/ meltfptr[44] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        /*^compute*/
        /*_#eqeq__L15*/ meltfnum[13] =
            ((/*_.PAIR_HEAD__V52*/ meltfptr[44]) == ((/*!konst_9_DOC*/ meltfrout->tabval[9])));;
        MELT_LOCATION("warmelt-macro.melt:8519:/ cond");
        /*cond*/ if (/*_#eqeq__L15*/ meltfnum[13]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.PAIR_TAIL__V54*/ meltfptr[53] =
                        (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
                    MELT_LOCATION("warmelt-macro.melt:8521:/ compute");
                    /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V55*/ meltfptr[54] = /*_.PAIR_TAIL__V54*/ meltfptr[53];;
                    /*_.PAIR_HEAD__V56*/ meltfptr[55] =
                        (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
                    MELT_LOCATION("warmelt-macro.melt:8522:/ compute");
                    /*_.DOC__V27*/ meltfptr[26] = /*_.SETQ___V57*/ meltfptr[56] = /*_.PAIR_HEAD__V56*/ meltfptr[55];;
                    MELT_LOCATION("warmelt-macro.melt:8520:/ quasiblock");


                    /*_.PROGN___V58*/ meltfptr[57] = /*_.SETQ___V57*/ meltfptr[56];;
                    /*^compute*/
                    /*_._IF___V53*/ meltfptr[45] = /*_.PROGN___V58*/ meltfptr[57];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8519:/ clear");
                    /*clear*/ /*_.PAIR_TAIL__V54*/ meltfptr[53] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V55*/ meltfptr[54] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PAIR_HEAD__V56*/ meltfptr[55] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V57*/ meltfptr[56] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V58*/ meltfptr[57] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V53*/ meltfptr[45] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L16*/ meltfnum[15] =
            (/*null*/(/*_.EXPV__V42*/ meltfptr[38]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8523:/ cond");
        /*cond*/ if (/*_#NULL__L16*/ meltfnum[15]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8524:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[2];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_cstring =  "(EXPORT_MACRO $1 <expander> [:doc <docum>]) expecting expander";
                        /*^apply.arg*/
                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.SYMBNAME__V31*/ meltfptr[30];
                        /*_.ERROR_AT__V60*/ meltfptr[54] =  melt_apply ((meltclosure_ptr_t)((/*!ERROR_AT*/ meltfrout->tabval[8])), (melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]), (MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    /*_._IF___V59*/ meltfptr[53] = /*_.ERROR_AT__V60*/ meltfptr[54];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8523:/ clear");
                    /*clear*/ /*_.ERROR_AT__V60*/ meltfptr[54] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V59*/ meltfptr[53] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-macro.melt:8525:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^cond*/
        /*cond*/ if (/*_#ISDEFMACRO__L12*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_#NULL__L18*/ meltfnum[17] =
                        (/*null*/(/*_.SEXPV__V36*/ meltfptr[34]) == NULL);;
                    /*^compute*/
                    /*_#_IF___L17*/ meltfnum[16] = /*_#NULL__L18*/ meltfnum[17];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8525:/ clear");
                    /*clear*/ /*_#NULL__L18*/ meltfnum[17] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_#_IF___L17*/ meltfnum[16] = 0;;
            }
        ;
        MELT_LOCATION("warmelt-macro.melt:8525:/ cond");
        /*cond*/ if (/*_#_IF___L17*/ meltfnum[16]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-macro.melt:8526:/ quasiblock");


                    /*^rawallocobj*/
                    /*rawallocobj*/
                    {
                        melt_ptr_t newobj = 0;
                        melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_EXPORT_DEFMACRO*/ meltfrout->tabval[10])), (4), "CLASS_SOURCE_EXPORT_DEFMACRO");
                        /*_.INST__V64*/ meltfptr[54] =
                            newobj;
                    };
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V64*/ meltfptr[54])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V64*/ meltfptr[54]), (1), (/*_.LOC__V22*/ meltfptr[21]), "LOCA_LOCATION");
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @SEXPMAC_MNAME", melt_magic_discr((melt_ptr_t)(/*_.INST__V64*/ meltfptr[54])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V64*/ meltfptr[54]), (2), (/*_.SYMB__V26*/ meltfptr[25]), "SEXPMAC_MNAME");
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @SEXPMAC_DOC", melt_magic_discr((melt_ptr_t)(/*_.INST__V64*/ meltfptr[54])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V64*/ meltfptr[54]), (3), (/*_.DOC__V27*/ meltfptr[26]), "SEXPMAC_DOC");
                    ;
                    /*^touchobj*/

                    melt_dbgtrace_written_object (/*_.INST__V64*/ meltfptr[54], "newly made instance");
                    ;
                    /*_.INST___V63*/ meltfptr[57] = /*_.INST__V64*/ meltfptr[54];;
                    /*^compute*/
                    /*_.RES__V62*/ meltfptr[56] = /*_.INST___V63*/ meltfptr[57];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8525:/ clear");
                    /*clear*/ /*_.INST___V63*/ meltfptr[57] = 0 ;
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
                    MELT_LOCATION("warmelt-macro.melt:8530:/ quasiblock");


                    /*^rawallocobj*/
                    /*rawallocobj*/
                    {
                        melt_ptr_t newobj = 0;
                        melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_EXPORT_MACRO*/ meltfrout->tabval[11])), (5), "CLASS_SOURCE_EXPORT_MACRO");
                        /*_.INST__V66*/ meltfptr[65] =
                            newobj;
                    };
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[65])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V66*/ meltfptr[65]), (1), (/*_.LOC__V22*/ meltfptr[21]), "LOCA_LOCATION");
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @SEXPMAC_MNAME", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[65])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V66*/ meltfptr[65]), (2), (/*_.SYMB__V26*/ meltfptr[25]), "SEXPMAC_MNAME");
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @SEXPMAC_DOC", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[65])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V66*/ meltfptr[65]), (3), (/*_.DOC__V27*/ meltfptr[26]), "SEXPMAC_DOC");
                    ;
                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @SEXPMAC_MVAL", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[65])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.INST__V66*/ meltfptr[65]), (4), (/*_.EXPV__V42*/ meltfptr[38]), "SEXPMAC_MVAL");
                    ;
                    /*^touchobj*/

                    melt_dbgtrace_written_object (/*_.INST__V66*/ meltfptr[65], "newly made instance");
                    ;
                    /*_.INST___V65*/ meltfptr[57] = /*_.INST__V66*/ meltfptr[65];;
                    /*^compute*/
                    /*_.RES__V62*/ meltfptr[56] = /*_.INST___V65*/ meltfptr[57];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8525:/ clear");
                    /*clear*/ /*_.INST___V65*/ meltfptr[57] = 0 ;
                }
                ;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8537:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L19*/ meltfnum[17] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8537:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L19*/ meltfnum[17]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L20*/ meltfnum[19] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8537:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L20*/ meltfnum[19];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8537;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_macro result res=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V62*/ meltfptr[56];
                            /*_.MELT_DEBUG_FUN__V68*/ meltfptr[67] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V67*/ meltfptr[57] = /*_.MELT_DEBUG_FUN__V68*/ meltfptr[67];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8537:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L20*/ meltfnum[19] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V68*/ meltfptr[67] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V67*/ meltfptr[57] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8537:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L19*/ meltfnum[17] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V67*/ meltfptr[57] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8538:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V62*/ meltfptr[56];;

        {
            MELT_LOCATION("warmelt-macro.melt:8538:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V61*/ meltfptr[55] = /*_.RETURN___V69*/ meltfptr[67];;

        MELT_LOCATION("warmelt-macro.melt:8525:/ clear");
        /*clear*/ /*_#_IF___L17*/ meltfnum[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V62*/ meltfptr[56] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V69*/ meltfptr[67] = 0 ;
        /*_.LET___V30*/ meltfptr[29] = /*_.LET___V61*/ meltfptr[55];;

        MELT_LOCATION("warmelt-macro.melt:8497:/ clear");
        /*clear*/ /*_.SYMBNAME__V31*/ meltfptr[30] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V32*/ meltfptr[31] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SEXPV__V36*/ meltfptr[34] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V37*/ meltfptr[33] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CBIND__V41*/ meltfptr[39] = 0 ;
        /*^clear*/
        /*clear*/ /*_#ISDEFMACRO__L12*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L13*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.EXPV__V42*/ meltfptr[38] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V50*/ meltfptr[32] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V51*/ meltfptr[43] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V52*/ meltfptr[44] = 0 ;
        /*^clear*/
        /*clear*/ /*_#eqeq__L15*/ meltfnum[13] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V53*/ meltfptr[45] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L16*/ meltfnum[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V59*/ meltfptr[53] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V61*/ meltfptr[55] = 0 ;
        /*_.LET___V20*/ meltfptr[18] = /*_.LET___V30*/ meltfptr[29];;

        MELT_LOCATION("warmelt-macro.melt:8487:/ clear");
        /*clear*/ /*_.CONT__V21*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V25*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SYMB__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DOC__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L7*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V29*/ meltfptr[28] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V30*/ meltfptr[29] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8481:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V20*/ meltfptr[18];;

        {
            MELT_LOCATION("warmelt-macro.melt:8481:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V17*/ meltfptr[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V20*/ meltfptr[18] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_EXPORT_MACRO", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_167_WARMELTmiMACRO_MEXPAND_EXPORT_MACRO*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO fromline 1715 */

    /** start of frame for meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO// fromline 1531
        : public Melt_CallFrameWithValues<54>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[12];
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
        MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<54> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO), clos) {};
        MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO() //the constructor fromline 1605
            : Melt_CallFrameWithValues<54> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<54> (fil,lin, sizeof(MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO)) {};
        MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<54> (fil,lin, sizeof(MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO


    /** end of frame for meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO fromline 1660**/

    /* end of frame for routine meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO fromline 1719 */

    /* classy proc frame meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO */ MeltFrame_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_EXPORT_PATMACRO", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8549:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8550:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8550:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8550:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8550;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_patmacro sexpr";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8550:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8550:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8551:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8551:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8551:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8551;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8551:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8551:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8552:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8552:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8552:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8552;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8552:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8552:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8553:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_CLOSURE__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) == MELTOBMAG_CLOSURE);;
            MELT_LOCATION("warmelt-macro.melt:8553:/ cond");
            /*cond*/ if (/*_#IS_CLOSURE__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8553:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check mexpander";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8553;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8553:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8553:/ clear");
            /*clear*/ /*_#IS_CLOSURE__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8554:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8554:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V18*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8554:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8554;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V18*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8554:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V19*/ meltfptr[18] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V17*/ meltfptr[15] = /*_._IFELSE___V18*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8554:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V18*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V17*/ meltfptr[15] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8555:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8556:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V21*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8557:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V22*/ meltfptr[21] = slot;
        };
        ;
        /*_.LIST_FIRST__V23*/ meltfptr[22] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V21*/ meltfptr[5])));;
        /*^compute*/
        /*_.CURPAIR__V24*/ meltfptr[23] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V23*/ meltfptr[22])));;
        /*^compute*/
        /*_.PAIR_HEAD__V25*/ meltfptr[24] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8559:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.SYMB__V26*/ meltfptr[25] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V25*/ meltfptr[24]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.PATEXPV__V27*/ meltfptr[26] = (/*nil*/NULL);;
        /*^compute*/
        /*_.MACEXPV__V28*/ meltfptr[27] = (/*nil*/NULL);;
        /*^compute*/
        /*_.DOC__V29*/ meltfptr[28] = (/*nil*/NULL);;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_NOT_A__L7*/ meltfnum[1] =
            !melt_is_instance_of((melt_ptr_t)(/*_.SYMB__V26*/ meltfptr[25]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[4])));;
        MELT_LOCATION("warmelt-macro.melt:8564:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L7*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8565:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]), ( "(EXPORT_PATMACRO <sym> <patexpander> <macexpander> [:doc <docum>])\
 expecting symbol"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V30*/ meltfptr[29] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        MELT_LOCATION("warmelt-macro.melt:8566:/ compute");
        /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V31*/ meltfptr[30] = /*_.PAIR_TAIL__V30*/ meltfptr[29];;
        /*_.PAIR_HEAD__V32*/ meltfptr[31] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8567:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.MEXPANDER__V33*/ meltfptr[32] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V32*/ meltfptr[31]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*^compute*/
        /*_.PATEXPV__V27*/ meltfptr[26] = /*_.SETQ___V34*/ meltfptr[33] = /*_.MEXPANDER__V33*/ meltfptr[32];;

        MELT_CHECK_SIGNAL();
        ;
        /*_#NULL__L8*/ meltfnum[0] =
            (/*null*/(/*_.PATEXPV__V27*/ meltfptr[26]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8568:/ cond");
        /*cond*/ if (/*_#NULL__L8*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8569:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]), ( "(EXPORT_PATMACRO <sym> <patexpander> <macexpander> [:doc <docum>])\
 expecting patexpander"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V35*/ meltfptr[34] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        MELT_LOCATION("warmelt-macro.melt:8570:/ compute");
        /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V36*/ meltfptr[35] = /*_.PAIR_TAIL__V35*/ meltfptr[34];;
        /*_.PAIR_HEAD__V37*/ meltfptr[36] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8571:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.MEXPANDER__V38*/ meltfptr[37] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V37*/ meltfptr[36]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*^compute*/
        /*_.MACEXPV__V28*/ meltfptr[27] = /*_.SETQ___V39*/ meltfptr[38] = /*_.MEXPANDER__V38*/ meltfptr[37];;

        MELT_CHECK_SIGNAL();
        ;
        /*_#NULL__L9*/ meltfnum[8] =
            (/*null*/(/*_.MACEXPV__V28*/ meltfptr[27]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8572:/ cond");
        /*cond*/ if (/*_#NULL__L9*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8573:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V22*/ meltfptr[21]), ( "(EXPORT_PATMACRO <sym> <patexpander> <macexpander> [:doc <docum>])\
 expecting macexpander"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V40*/ meltfptr[39] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        MELT_LOCATION("warmelt-macro.melt:8574:/ compute");
        /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V41*/ meltfptr[40] = /*_.PAIR_TAIL__V40*/ meltfptr[39];;

        MELT_CHECK_SIGNAL();
        ;
        /*_.PAIR_HEAD__V42*/ meltfptr[41] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
        /*^compute*/
        /*_#eqeq__L10*/ meltfnum[9] =
            ((/*_.PAIR_HEAD__V42*/ meltfptr[41]) == ((/*!konst_5_DOC*/ meltfrout->tabval[5])));;
        MELT_LOCATION("warmelt-macro.melt:8575:/ cond");
        /*cond*/ if (/*_#eqeq__L10*/ meltfnum[9]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.PAIR_TAIL__V44*/ meltfptr[43] =
                        (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
                    MELT_LOCATION("warmelt-macro.melt:8577:/ compute");
                    /*_.CURPAIR__V24*/ meltfptr[23] = /*_.SETQ___V45*/ meltfptr[44] = /*_.PAIR_TAIL__V44*/ meltfptr[43];;
                    /*_.PAIR_HEAD__V46*/ meltfptr[45] =
                        (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V24*/ meltfptr[23])));;
                    MELT_LOCATION("warmelt-macro.melt:8578:/ compute");
                    /*_.DOC__V29*/ meltfptr[28] = /*_.SETQ___V47*/ meltfptr[46] = /*_.PAIR_HEAD__V46*/ meltfptr[45];;
                    MELT_LOCATION("warmelt-macro.melt:8576:/ quasiblock");


                    /*_.PROGN___V48*/ meltfptr[47] = /*_.SETQ___V47*/ meltfptr[46];;
                    /*^compute*/
                    /*_._IF___V43*/ meltfptr[42] = /*_.PROGN___V48*/ meltfptr[47];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8575:/ clear");
                    /*clear*/ /*_.PAIR_TAIL__V44*/ meltfptr[43] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V45*/ meltfptr[44] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PAIR_HEAD__V46*/ meltfptr[45] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V47*/ meltfptr[46] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V48*/ meltfptr[47] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V43*/ meltfptr[42] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-macro.melt:8581:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^quasiblock*/


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_EXPORT_PATMACRO*/ meltfrout->tabval[6])), (6), "CLASS_SOURCE_EXPORT_PATMACRO");
            /*_.INST__V51*/ meltfptr[45] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[45])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[45]), (1), (/*_.LOC__V22*/ meltfptr[21]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPMAC_MNAME", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[45])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[45]), (2), (/*_.SYMB__V26*/ meltfptr[25]), "SEXPMAC_MNAME");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPPAT_PVAL", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[45])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[45]), (5), (/*_.PATEXPV__V27*/ meltfptr[26]), "SEXPPAT_PVAL");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPMAC_MVAL", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[45])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[45]), (4), (/*_.MACEXPV__V28*/ meltfptr[27]), "SEXPMAC_MVAL");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPMAC_DOC", melt_magic_discr((melt_ptr_t)(/*_.INST__V51*/ meltfptr[45])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V51*/ meltfptr[45]), (3), (/*_.DOC__V29*/ meltfptr[28]), "SEXPMAC_DOC");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V51*/ meltfptr[45], "newly made instance");
        ;
        /*_.RES__V50*/ meltfptr[44] = /*_.INST__V51*/ meltfptr[45];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8589:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L11*/ meltfnum[10] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8589:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L11*/ meltfnum[10]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L12*/ meltfnum[11] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8589:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L12*/ meltfnum[11];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8589;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_patmacro result res";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V50*/ meltfptr[44];
                            /*_.MELT_DEBUG_FUN__V53*/ meltfptr[47] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V52*/ meltfptr[46] = /*_.MELT_DEBUG_FUN__V53*/ meltfptr[47];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8589:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L12*/ meltfnum[11] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V53*/ meltfptr[47] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V52*/ meltfptr[46] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8589:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L11*/ meltfnum[10] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V52*/ meltfptr[46] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8590:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V50*/ meltfptr[44];;

        {
            MELT_LOCATION("warmelt-macro.melt:8590:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V49*/ meltfptr[43] = /*_.RETURN___V54*/ meltfptr[47];;

        MELT_LOCATION("warmelt-macro.melt:8581:/ clear");
        /*clear*/ /*_.RES__V50*/ meltfptr[44] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V54*/ meltfptr[47] = 0 ;
        /*_.LET___V20*/ meltfptr[18] = /*_.LET___V49*/ meltfptr[43];;

        MELT_LOCATION("warmelt-macro.melt:8555:/ clear");
        /*clear*/ /*_.CONT__V21*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V25*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SYMB__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PATEXPV__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MACEXPV__V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DOC__V29*/ meltfptr[28] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L7*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V30*/ meltfptr[29] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V31*/ meltfptr[30] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V32*/ meltfptr[31] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MEXPANDER__V33*/ meltfptr[32] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V34*/ meltfptr[33] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L8*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V35*/ meltfptr[34] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V36*/ meltfptr[35] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V37*/ meltfptr[36] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MEXPANDER__V38*/ meltfptr[37] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V39*/ meltfptr[38] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L9*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V40*/ meltfptr[39] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V41*/ meltfptr[40] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V42*/ meltfptr[41] = 0 ;
        /*^clear*/
        /*clear*/ /*_#eqeq__L10*/ meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V43*/ meltfptr[42] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V49*/ meltfptr[43] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8549:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V20*/ meltfptr[18];;

        {
            MELT_LOCATION("warmelt-macro.melt:8549:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V17*/ meltfptr[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V20*/ meltfptr[18] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_EXPORT_PATMACRO", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_168_WARMELTmiMACRO_MEXPAND_EXPORT_PATMACRO*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS fromline 1715 */

    /** start of frame for meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS// fromline 1531
        : public Melt_CallFrameWithValues<31>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[8];
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
        MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<31> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS), clos) {};
        MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS() //the constructor fromline 1605
            : Melt_CallFrameWithValues<31> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<31> (fil,lin, sizeof(MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS)) {};
        MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<31> (fil,lin, sizeof(MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS


    /** end of frame for meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS fromline 1660**/

    /* end of frame for routine meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS fromline 1719 */

    /* classy proc frame meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS */ MeltFrame_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_EXPORT_CLASS", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8599:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8600:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8600:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8600:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8600;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_class sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8600:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8600:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8601:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8601:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8601:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8601;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8601:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8601:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8602:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8602:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8602:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8602;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8602:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8602:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L5*/ meltfnum[1] =
            (/*null*/(/*_.MEXPANDER__V4*/ meltfptr[3]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8603:/ cond");
        /*cond*/ if (/*_#NULL__L5*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^compute*/
                    /*_.MEXPANDER__V4*/ meltfptr[3] = /*_.SETQ___V15*/ meltfptr[5] = (/*!MACROEXPAND_1*/ meltfrout->tabval[4]);;
                    /*_._IF___V14*/ meltfptr[12] = /*_.SETQ___V15*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8603:/ clear");
                    /*clear*/ /*_.SETQ___V15*/ meltfptr[5] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V14*/ meltfptr[12] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8604:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8604:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V17*/ meltfptr[16] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8604:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8604;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V17*/ meltfptr[16] = /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8604:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V16*/ meltfptr[5] = /*_._IFELSE___V17*/ meltfptr[16];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8604:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V17*/ meltfptr[16] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V16*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8605:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8606:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V20*/ meltfptr[16] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8607:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V21*/ meltfptr[20] = slot;
        };
        ;
        /*_.LIST_FIRST__V22*/ meltfptr[21] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V20*/ meltfptr[16])));;
        /*^compute*/
        /*_.CURPAIR__V23*/ meltfptr[22] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V22*/ meltfptr[21])));;
        MELT_LOCATION("warmelt-macro.melt:8611:/ quasiblock");


        /*^newclosure*/
        /*newclosure*/ /*_.LAMBDA___V25*/ meltfptr[24] =
            (melt_ptr_t) meltgc_new_closure((meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE)))), (meltroutine_ptr_t)((/*!konst_8*/ meltfrout->tabval[8])), (4));
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V25*/ meltfptr[24])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 0>= 0 && 0< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V25*/ meltfptr[24])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V25*/ meltfptr[24])->tabval[0] = (melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V25*/ meltfptr[24])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 1>= 0 && 1< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V25*/ meltfptr[24])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V25*/ meltfptr[24])->tabval[1] = (melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V25*/ meltfptr[24])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 2>= 0 && 2< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V25*/ meltfptr[24])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V25*/ meltfptr[24])->tabval[2] = (melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4]);
        ;
        /*^putclosedv*/
        /*putclosv*/
        melt_assertmsg("putclosv checkclo", melt_magic_discr((melt_ptr_t)(/*_.LAMBDA___V25*/ meltfptr[24])) == MELTOBMAG_CLOSURE);
        melt_assertmsg("putclosv checkoff", 3>= 0 && 3< melt_closure_size((melt_ptr_t) (/*_.LAMBDA___V25*/ meltfptr[24])));
        ((meltclosure_ptr_t)/*_.LAMBDA___V25*/ meltfptr[24])->tabval[3] = (melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]);
        ;
        /*_.LAMBDA___V24*/ meltfptr[23] = /*_.LAMBDA___V25*/ meltfptr[24];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8609:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[6]);
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.LAMBDA___V24*/ meltfptr[23];
            /*_.SYMBTUP__V26*/ meltfptr[25] =  melt_apply ((meltclosure_ptr_t)((/*!PAIRLIST_TO_MULTIPLE*/ meltfrout->tabval[5])), (melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8617:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_EXPORT_CLASS*/ meltfrout->tabval[9])), (3), "CLASS_SOURCE_EXPORT_CLASS");
            /*_.INST__V28*/ meltfptr[27] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V28*/ meltfptr[27])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V28*/ meltfptr[27]), (1), (/*_.LOC__V21*/ meltfptr[20]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPORT_NAMES", melt_magic_discr((melt_ptr_t)(/*_.INST__V28*/ meltfptr[27])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V28*/ meltfptr[27]), (2), (/*_.SYMBTUP__V26*/ meltfptr[25]), "SEXPORT_NAMES");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V28*/ meltfptr[27], "newly made instance");
        ;
        /*_.RES__V27*/ meltfptr[26] = /*_.INST__V28*/ meltfptr[27];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8621:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L7*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8621:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L7*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8621:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L8*/ meltfnum[7];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8621;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_class result res";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V27*/ meltfptr[26];
                            /*_.MELT_DEBUG_FUN__V30*/ meltfptr[29] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V29*/ meltfptr[28] = /*_.MELT_DEBUG_FUN__V30*/ meltfptr[29];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8621:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V30*/ meltfptr[29] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V29*/ meltfptr[28] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8621:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L7*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V29*/ meltfptr[28] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8622:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V27*/ meltfptr[26];;

        {
            MELT_LOCATION("warmelt-macro.melt:8622:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V19*/ meltfptr[17] = /*_.RETURN___V31*/ meltfptr[29];;

        MELT_LOCATION("warmelt-macro.melt:8605:/ clear");
        /*clear*/ /*_.CONT__V20*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LAMBDA___V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SYMBTUP__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V31*/ meltfptr[29] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8599:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V19*/ meltfptr[17];;

        {
            MELT_LOCATION("warmelt-macro.melt:8599:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L5*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V16*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V19*/ meltfptr[17] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_EXPORT_CLASS", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_169_WARMELTmiMACRO_MEXPAND_EXPORT_CLASS*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_170_WARMELTmiMACRO_LAMBDA_cl36(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
                                        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_170_WARMELTmiMACRO_LAMBDA_cl36 fromline 1715 */

    /** start of frame for meltrout_170_WARMELTmiMACRO_LAMBDA_cl36 of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36// fromline 1531
        : public Melt_CallFrameWithValues<4>
    {
    public: /* fromline 1535*/
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
        MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<4> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36), clos) {};
        MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36() //the constructor fromline 1605
            : Melt_CallFrameWithValues<4> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<4> (fil,lin, sizeof(MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36)) {};
        MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<4> (fil,lin, sizeof(MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36


    /** end of frame for meltrout_170_WARMELTmiMACRO_LAMBDA_cl36 fromline 1660**/

    /* end of frame for routine meltrout_170_WARMELTmiMACRO_LAMBDA_cl36 fromline 1719 */

    /* classy proc frame meltrout_170_WARMELTmiMACRO_LAMBDA_cl36 */ MeltFrame_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_170_WARMELTmiMACRO_LAMBDA_cl36 fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("LAMBDA_cl36", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8611:/ getarg");
    /*_.S__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {

        MELT_LOCATION("warmelt-macro.melt:8612:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*~ENV*/ meltfclos->tabval[1]);
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &(/*~MEXPANDER*/ meltfclos->tabval[0]);
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &(/*~MODCTX*/ meltfclos->tabval[2]);
            /*_.SYM__V4*/ meltfptr[3] =  melt_apply ((meltclosure_ptr_t)((/*~MEXPANDER*/ meltfclos->tabval[0])), (melt_ptr_t)(/*_.S__V2*/ meltfptr[1]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_NOT_A__L1*/ meltfnum[0] =
            !melt_is_instance_of((melt_ptr_t)(/*_.SYM__V4*/ meltfptr[3]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[0])));;
        MELT_LOCATION("warmelt-macro.melt:8613:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L1*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8614:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)((/*~LOC*/ meltfclos->tabval[3])), ( "(EXPORT_CLASS <sym>...) expecting symbol"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.LET___V3*/ meltfptr[2] = /*_.SYM__V4*/ meltfptr[3];;

        MELT_LOCATION("warmelt-macro.melt:8612:/ clear");
        /*clear*/ /*_.SYM__V4*/ meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L1*/ meltfnum[0] = 0 ;
        MELT_LOCATION("warmelt-macro.melt:8611:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V3*/ meltfptr[2];;

        {
            MELT_LOCATION("warmelt-macro.melt:8611:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.LET___V3*/ meltfptr[2] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("LAMBDA_cl36", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_170_WARMELTmiMACRO_LAMBDA_cl36_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_170_WARMELTmiMACRO_LAMBDA_cl36*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM fromline 1715 */

    /** start of frame for meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM// fromline 1531
        : public Melt_CallFrameWithValues<55>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[17];
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
        MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<55> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM), clos) {};
        MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM() //the constructor fromline 1605
            : Melt_CallFrameWithValues<55> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<55> (fil,lin, sizeof(MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM)) {};
        MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<55> (fil,lin, sizeof(MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM


    /** end of frame for meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM fromline 1660**/

    /* end of frame for routine meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM fromline 1719 */

    /* classy proc frame meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM */ MeltFrame_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_EXPORT_SYNONYM", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8631:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8632:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8632:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8632:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8632;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_export_synonym sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8632:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8632:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8633:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8633:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8633:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8633;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8633:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8633:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8634:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8634:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8634:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8634;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8634:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8634:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L5*/ meltfnum[1] =
            (/*null*/(/*_.MEXPANDER__V4*/ meltfptr[3]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8635:/ cond");
        /*cond*/ if (/*_#NULL__L5*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^compute*/
                    /*_.MEXPANDER__V4*/ meltfptr[3] = /*_.SETQ___V15*/ meltfptr[5] = (/*!MACROEXPAND_1*/ meltfrout->tabval[4]);;
                    /*_._IF___V14*/ meltfptr[12] = /*_.SETQ___V15*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8635:/ clear");
                    /*clear*/ /*_.SETQ___V15*/ meltfptr[5] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V14*/ meltfptr[12] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8636:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8636:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V17*/ meltfptr[16] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8636:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8636;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V17*/ meltfptr[16] = /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8636:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V16*/ meltfptr[5] = /*_._IFELSE___V17*/ meltfptr[16];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8636:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V17*/ meltfptr[16] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V16*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8637:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8638:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V20*/ meltfptr[16] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8639:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V21*/ meltfptr[20] = slot;
        };
        ;
        /*_.LIST_FIRST__V22*/ meltfptr[21] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V20*/ meltfptr[16])));;
        /*^compute*/
        /*_.CURPAIR__V23*/ meltfptr[22] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V22*/ meltfptr[21])));;
        /*^compute*/
        /*_.NEWSYMB__V24*/ meltfptr[23] = (/*nil*/NULL);;
        /*^compute*/
        /*_.OLDSYMB__V25*/ meltfptr[24] = (/*nil*/NULL);;
        /*^compute*/
        /*_.DOC__V26*/ meltfptr[25] = (/*nil*/NULL);;
        /*^compute*/
        /*_.PAIR_HEAD__V27*/ meltfptr[26] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8646:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.MEXPANDER__V28*/ meltfptr[27] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V27*/ meltfptr[26]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*^compute*/
        /*_.NEWSYMB__V24*/ meltfptr[23] = /*_.SETQ___V29*/ meltfptr[28] = /*_.MEXPANDER__V28*/ meltfptr[27];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8647:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L7*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8647:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L7*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8647:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L8*/ meltfnum[7];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8647;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpander_export_synonym newsymb";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.NEWSYMB__V24*/ meltfptr[23];
                            /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V30*/ meltfptr[29] = /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8647:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V30*/ meltfptr[29] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8647:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L7*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V30*/ meltfptr[29] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_NOT_A__L9*/ meltfnum[7] =
            !melt_is_instance_of((melt_ptr_t)(/*_.NEWSYMB__V24*/ meltfptr[23]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[5])));;
        MELT_LOCATION("warmelt-macro.melt:8648:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L9*/ meltfnum[7]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8649:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "bad new name in (EXPORT_SYNONYM <newname> <oldname> [:doc <docum>])"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V32*/ meltfptr[30] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
        MELT_LOCATION("warmelt-macro.melt:8650:/ compute");
        /*_.CURPAIR__V23*/ meltfptr[22] = /*_.SETQ___V33*/ meltfptr[29] = /*_.PAIR_TAIL__V32*/ meltfptr[30];;
        /*_.PAIR_HEAD__V34*/ meltfptr[33] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8652:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.MEXPANDER__V35*/ meltfptr[34] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V34*/ meltfptr[33]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*^compute*/
        /*_.OLDSYMB__V25*/ meltfptr[24] = /*_.SETQ___V36*/ meltfptr[35] = /*_.MEXPANDER__V35*/ meltfptr[34];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8653:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L10*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8653:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L10*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L11*/ meltfnum[10] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8653:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L11*/ meltfnum[10];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8653;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpander_export_synonym oldsymb";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.OLDSYMB__V25*/ meltfptr[24];
                            /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V37*/ meltfptr[36] = /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8653:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L11*/ meltfnum[10] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V37*/ meltfptr[36] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8653:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L10*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V37*/ meltfptr[36] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_NOT_A__L12*/ meltfnum[10] =
            !melt_is_instance_of((melt_ptr_t)(/*_.OLDSYMB__V25*/ meltfptr[24]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[5])));;
        MELT_LOCATION("warmelt-macro.melt:8654:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L12*/ meltfnum[10]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8655:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "bad old name in (EXPORT_SYNONYM <newname> <oldname> [:doc <docum>])"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V39*/ meltfptr[37] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
        MELT_LOCATION("warmelt-macro.melt:8656:/ compute");
        /*_.CURPAIR__V23*/ meltfptr[22] = /*_.SETQ___V40*/ meltfptr[36] = /*_.PAIR_TAIL__V39*/ meltfptr[37];;

        MELT_CHECK_SIGNAL();
        ;
        /*_.PAIR_HEAD__V41*/ meltfptr[40] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
        /*^compute*/
        /*_#eqeq__L13*/ meltfnum[0] =
            ((/*_.PAIR_HEAD__V41*/ meltfptr[40]) == ((/*!konst_6_DOC*/ meltfrout->tabval[6])));;
        MELT_LOCATION("warmelt-macro.melt:8657:/ cond");
        /*cond*/ if (/*_#eqeq__L13*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.PAIR_TAIL__V43*/ meltfptr[42] =
                        (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
                    MELT_LOCATION("warmelt-macro.melt:8659:/ compute");
                    /*_.CURPAIR__V23*/ meltfptr[22] = /*_.SETQ___V44*/ meltfptr[43] = /*_.PAIR_TAIL__V43*/ meltfptr[42];;
                    /*_.PAIR_HEAD__V45*/ meltfptr[44] =
                        (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
                    MELT_LOCATION("warmelt-macro.melt:8660:/ compute");
                    /*_.DOC__V26*/ meltfptr[25] = /*_.SETQ___V46*/ meltfptr[45] = /*_.PAIR_HEAD__V45*/ meltfptr[44];;
                    MELT_LOCATION("warmelt-macro.melt:8658:/ quasiblock");


                    /*_.PROGN___V47*/ meltfptr[46] = /*_.SETQ___V46*/ meltfptr[45];;
                    /*^compute*/
                    /*_._IF___V42*/ meltfptr[41] = /*_.PROGN___V47*/ meltfptr[46];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8657:/ clear");
                    /*clear*/ /*_.PAIR_TAIL__V43*/ meltfptr[42] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V44*/ meltfptr[43] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PAIR_HEAD__V45*/ meltfptr[44] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V46*/ meltfptr[45] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V47*/ meltfptr[46] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V42*/ meltfptr[41] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8662:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L14*/ meltfnum[13] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8662:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L14*/ meltfnum[13]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L15*/ meltfnum[14] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8662:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L15*/ meltfnum[14];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8662;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpander_export_synonym doc";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.DOC__V26*/ meltfptr[25];
                            /*_.MELT_DEBUG_FUN__V49*/ meltfptr[43] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V48*/ meltfptr[42] = /*_.MELT_DEBUG_FUN__V49*/ meltfptr[43];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8662:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L15*/ meltfnum[14] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V49*/ meltfptr[43] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V48*/ meltfptr[42] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8662:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L14*/ meltfnum[13] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V48*/ meltfptr[42] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8663:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8664:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_EXPORT_SYNONYM*/ meltfrout->tabval[7])), (5), "CLASS_SOURCE_EXPORT_SYNONYM");
            /*_.INST__V52*/ meltfptr[46] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V52*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V52*/ meltfptr[46]), (1), (/*_.LOC__V21*/ meltfptr[20]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPSYN_NEWNAME", melt_magic_discr((melt_ptr_t)(/*_.INST__V52*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V52*/ meltfptr[46]), (2), (/*_.NEWSYMB__V24*/ meltfptr[23]), "SEXPSYN_NEWNAME");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPSYN_OLDNAME", melt_magic_discr((melt_ptr_t)(/*_.INST__V52*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V52*/ meltfptr[46]), (3), (/*_.OLDSYMB__V25*/ meltfptr[24]), "SEXPSYN_OLDNAME");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SEXPSYN_DOC", melt_magic_discr((melt_ptr_t)(/*_.INST__V52*/ meltfptr[46])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V52*/ meltfptr[46]), (4), (/*_.DOC__V26*/ meltfptr[25]), "SEXPSYN_DOC");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V52*/ meltfptr[46], "newly made instance");
        ;
        /*_.RES__V51*/ meltfptr[45] = /*_.INST__V52*/ meltfptr[46];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8670:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L16*/ meltfnum[14] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8670:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L16*/ meltfnum[14]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L17*/ meltfnum[13] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8670:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L17*/ meltfnum[13];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8670;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpander_export_synonym result";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V51*/ meltfptr[45];
                            /*_.MELT_DEBUG_FUN__V54*/ meltfptr[42] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V53*/ meltfptr[43] = /*_.MELT_DEBUG_FUN__V54*/ meltfptr[42];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8670:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L17*/ meltfnum[13] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V54*/ meltfptr[42] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V53*/ meltfptr[43] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8670:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L16*/ meltfnum[14] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V53*/ meltfptr[43] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8671:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V51*/ meltfptr[45];;

        {
            MELT_LOCATION("warmelt-macro.melt:8671:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V50*/ meltfptr[44] = /*_.RETURN___V55*/ meltfptr[42];;

        MELT_LOCATION("warmelt-macro.melt:8663:/ clear");
        /*clear*/ /*_.RES__V51*/ meltfptr[45] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V55*/ meltfptr[42] = 0 ;
        /*_.LET___V19*/ meltfptr[17] = /*_.LET___V50*/ meltfptr[44];;

        MELT_LOCATION("warmelt-macro.melt:8637:/ clear");
        /*clear*/ /*_.CONT__V20*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.NEWSYMB__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.OLDSYMB__V25*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DOC__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MEXPANDER__V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V29*/ meltfptr[28] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L9*/ meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V32*/ meltfptr[30] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V33*/ meltfptr[29] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V34*/ meltfptr[33] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MEXPANDER__V35*/ meltfptr[34] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V36*/ meltfptr[35] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L12*/ meltfnum[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V39*/ meltfptr[37] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V40*/ meltfptr[36] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V41*/ meltfptr[40] = 0 ;
        /*^clear*/
        /*clear*/ /*_#eqeq__L13*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V42*/ meltfptr[41] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V50*/ meltfptr[44] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8631:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V19*/ meltfptr[17];;

        {
            MELT_LOCATION("warmelt-macro.melt:8631:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L5*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V16*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V19*/ meltfptr[17] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_EXPORT_SYNONYM", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_171_WARMELTmiMACRO_MEXPAND_EXPORT_SYNONYM*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1715 */

    /** start of frame for meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE// fromline 1531
        : public Melt_CallFrameWithValues<26>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[8];
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
        MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<26> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE), clos) {};
        MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE() //the constructor fromline 1605
            : Melt_CallFrameWithValues<26> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<26> (fil,lin, sizeof(MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE)) {};
        MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<26> (fil,lin, sizeof(MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE


    /** end of frame for meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1660**/

    /* end of frame for routine meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1719 */

    /* classy proc frame meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE */ MeltFrame_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8683:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8684:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8684:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8684:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8684;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_current_module_environment_reference sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8684:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8684:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8685:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8685:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8685:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8685;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8685:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8685:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8686:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8686:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8686:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8686;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8686:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8686:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8687:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8687:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8687:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8687;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8687:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8687:/ clear");
            /*clear*/ /*_#IS_OBJECT__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8688:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8689:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V18*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8690:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V19*/ meltfptr[18] = slot;
        };
        ;
        /*_.LIST_FIRST__V20*/ meltfptr[19] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V18*/ meltfptr[5])));;
        /*^compute*/
        /*_.CURPAIR__V21*/ meltfptr[20] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V20*/ meltfptr[19])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8692:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_CURRENT_MODULE_ENVIRONMENT_REFERENCE*/ meltfrout->tabval[4])), (3), "CLASS_SOURCE_CURRENT_MODULE_ENVIRONMENT_REFERENCE");
            /*_.INST__V23*/ meltfptr[22] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V23*/ meltfptr[22])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V23*/ meltfptr[22]), (1), (/*_.LOC__V19*/ meltfptr[18]), "LOCA_LOCATION");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V23*/ meltfptr[22], "newly made instance");
        ;
        /*_.RES__V22*/ meltfptr[21] = /*_.INST__V23*/ meltfptr[22];;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NOTNULL__L6*/ meltfnum[0] =
            ((/*_.CURPAIR__V21*/ meltfptr[20]) != NULL);;
        MELT_LOCATION("warmelt-macro.melt:8695:/ cond");
        /*cond*/ if (/*_#NOTNULL__L6*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8696:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V19*/ meltfptr[18]), ( "(CURRENT_MODULE_ENVIRONMENT_REFERENCE) should not have any argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8697:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L7*/ meltfnum[1] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8697:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L7*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8697:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L8*/ meltfnum[7];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8697;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_current_module_environment_reference return res";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V22*/ meltfptr[21];
                            /*_.MELT_DEBUG_FUN__V25*/ meltfptr[24] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V24*/ meltfptr[23] = /*_.MELT_DEBUG_FUN__V25*/ meltfptr[24];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8697:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V25*/ meltfptr[24] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V24*/ meltfptr[23] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8697:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L7*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V24*/ meltfptr[23] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8698:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V22*/ meltfptr[21];;

        {
            MELT_LOCATION("warmelt-macro.melt:8698:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V17*/ meltfptr[15] = /*_.RETURN___V26*/ meltfptr[24];;

        MELT_LOCATION("warmelt-macro.melt:8688:/ clear");
        /*clear*/ /*_.CONT__V18*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V19*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOTNULL__L6*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V26*/ meltfptr[24] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8683:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V17*/ meltfptr[15];;

        {
            MELT_LOCATION("warmelt-macro.melt:8683:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V17*/ meltfptr[15] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_172_WARMELTmiMACRO_MEXPAND_CURRENT_MODULE_ENVIRONMENT_REFERENCE*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT fromline 1715 */

    /** start of frame for meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT// fromline 1531
        : public Melt_CallFrameWithValues<28>
    {
    public: /* fromline 1535*/
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
        MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<28> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT), clos) {};
        MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT() //the constructor fromline 1605
            : Melt_CallFrameWithValues<28> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<28> (fil,lin, sizeof(MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT)) {};
        MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<28> (fil,lin, sizeof(MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT


    /** end of frame for meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT fromline 1660**/

    /* end of frame for routine meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT fromline 1719 */

    /* classy proc frame meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT */ MeltFrame_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_PARENT_MODULE_ENVIRONMENT", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8717:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8718:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8718:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8718:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8718;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_parent_module_environment sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8718:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8718:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8719:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8719:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8719:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8719;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8719:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8719:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8720:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8720:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8720:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8720;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8720:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8720:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L5*/ meltfnum[1] =
            (/*null*/(/*_.MEXPANDER__V4*/ meltfptr[3]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8721:/ cond");
        /*cond*/ if (/*_#NULL__L5*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^compute*/
                    /*_.MEXPANDER__V4*/ meltfptr[3] = /*_.SETQ___V15*/ meltfptr[5] = (/*!MACROEXPAND_1*/ meltfrout->tabval[4]);;
                    /*_._IF___V14*/ meltfptr[12] = /*_.SETQ___V15*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8721:/ clear");
                    /*clear*/ /*_.SETQ___V15*/ meltfptr[5] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V14*/ meltfptr[12] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8722:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8722:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V17*/ meltfptr[16] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8722:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8722;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V17*/ meltfptr[16] = /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8722:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V16*/ meltfptr[5] = /*_._IFELSE___V17*/ meltfptr[16];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8722:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V17*/ meltfptr[16] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V16*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8723:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8724:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V20*/ meltfptr[16] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8725:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V21*/ meltfptr[20] = slot;
        };
        ;
        /*_.LIST_FIRST__V22*/ meltfptr[21] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V20*/ meltfptr[16])));;
        /*^compute*/
        /*_.CURPAIR__V23*/ meltfptr[22] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V22*/ meltfptr[21])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8727:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_PARENT_MODULE_ENVIRONMENT*/ meltfrout->tabval[5])), (2), "CLASS_SOURCE_PARENT_MODULE_ENVIRONMENT");
            /*_.INST__V25*/ meltfptr[24] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V25*/ meltfptr[24])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V25*/ meltfptr[24]), (1), (/*_.LOC__V21*/ meltfptr[20]), "LOCA_LOCATION");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V25*/ meltfptr[24], "newly made instance");
        ;
        /*_.RES__V24*/ meltfptr[23] = /*_.INST__V25*/ meltfptr[24];;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NOTNULL__L7*/ meltfnum[0] =
            ((/*_.CURPAIR__V23*/ meltfptr[22]) != NULL);;
        MELT_LOCATION("warmelt-macro.melt:8730:/ cond");
        /*cond*/ if (/*_#NOTNULL__L7*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8731:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(PARENT_MODULE_ENVIRONMENT) should not have any argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8732:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L8*/ meltfnum[7] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8732:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L8*/ meltfnum[7]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8732:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L9*/ meltfnum[8];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8732;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_parent_module_environment return res";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V24*/ meltfptr[23];
                            /*_.MELT_DEBUG_FUN__V27*/ meltfptr[26] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V26*/ meltfptr[25] = /*_.MELT_DEBUG_FUN__V27*/ meltfptr[26];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8732:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V27*/ meltfptr[26] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V26*/ meltfptr[25] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8732:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L8*/ meltfnum[7] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V26*/ meltfptr[25] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8733:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V24*/ meltfptr[23];;

        {
            MELT_LOCATION("warmelt-macro.melt:8733:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V19*/ meltfptr[17] = /*_.RETURN___V28*/ meltfptr[26];;

        MELT_LOCATION("warmelt-macro.melt:8723:/ clear");
        /*clear*/ /*_.CONT__V20*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOTNULL__L7*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V28*/ meltfptr[26] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8717:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V19*/ meltfptr[17];;

        {
            MELT_LOCATION("warmelt-macro.melt:8717:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L5*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V16*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V19*/ meltfptr[17] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_PARENT_MODULE_ENVIRONMENT", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_173_WARMELTmiMACRO_MEXPAND_PARENT_MODULE_ENVIRONMENT*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1715 */

    /** start of frame for meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE// fromline 1531
        : public Melt_CallFrameWithValues<26>
    {
    public: /* fromline 1535*/
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
        MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<26> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE), clos) {};
        MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE() //the constructor fromline 1605
            : Melt_CallFrameWithValues<26> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<26> (fil,lin, sizeof(MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE)) {};
        MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<26> (fil,lin, sizeof(MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE


    /** end of frame for meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1660**/

    /* end of frame for routine meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1719 */

    /* classy proc frame meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE */ MeltFrame_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8747:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8748:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8748:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8748:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8748;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_update_current_module_environment_reference sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8748:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8748:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8749:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8749:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8749:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8749;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8749:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8749:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8750:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8750:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8750:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8750;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8750:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8750:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8751:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8751:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V15*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8751:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8751;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V15*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8751:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V16*/ meltfptr[15] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V14*/ meltfptr[12] = /*_._IFELSE___V15*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8751:/ clear");
            /*clear*/ /*_#IS_OBJECT__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V15*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V14*/ meltfptr[12] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8752:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8753:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V18*/ meltfptr[5] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8754:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V19*/ meltfptr[18] = slot;
        };
        ;
        /*_.LIST_FIRST__V20*/ meltfptr[19] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V19*/ meltfptr[18])));;
        /*^compute*/
        /*_.CURPAIR__V21*/ meltfptr[20] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V20*/ meltfptr[19])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8756:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE*/ meltfrout->tabval[4])), (3), "CLASS_SOURCE_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE");
            /*_.INST__V23*/ meltfptr[22] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V23*/ meltfptr[22])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V23*/ meltfptr[22]), (1), (/*_.LOC__V18*/ meltfptr[5]), "LOCA_LOCATION");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V23*/ meltfptr[22], "newly made instance");
        ;
        /*_.RES__V22*/ meltfptr[21] = /*_.INST__V23*/ meltfptr[22];;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NOTNULL__L6*/ meltfnum[0] =
            ((/*_.CURPAIR__V21*/ meltfptr[20]) != NULL);;
        MELT_LOCATION("warmelt-macro.melt:8759:/ cond");
        /*cond*/ if (/*_#NOTNULL__L6*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8760:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V18*/ meltfptr[5]), ( "(UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE) should not have any argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#MELT_IS_BOOTSTRAPPING__L7*/ meltfnum[1] =
            (melt_flag_bootstrapping);;
        /*^compute*/
        /*_#NOT__L8*/ meltfnum[7] =
            (!(/*_#MELT_IS_BOOTSTRAPPING__L7*/ meltfnum[1]));;
        MELT_LOCATION("warmelt-macro.melt:8761:/ cond");
        /*cond*/ if (/*_#NOT__L8*/ meltfnum[7]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8762:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V18*/ meltfptr[5]), ( "(UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE) can only be used while\
 bootstrapping MELT."), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8763:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L9*/ meltfnum[8] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8763:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L9*/ meltfnum[8]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L10*/ meltfnum[9] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8763:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L10*/ meltfnum[9];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8763;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_update_current_module_environment_reference return res";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V22*/ meltfptr[21];
                            /*_.MELT_DEBUG_FUN__V25*/ meltfptr[24] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V24*/ meltfptr[23] = /*_.MELT_DEBUG_FUN__V25*/ meltfptr[24];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8763:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L10*/ meltfnum[9] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V25*/ meltfptr[24] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V24*/ meltfptr[23] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8763:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L9*/ meltfnum[8] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V24*/ meltfptr[23] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8764:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V22*/ meltfptr[21];;

        {
            MELT_LOCATION("warmelt-macro.melt:8764:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V17*/ meltfptr[15] = /*_.RETURN___V26*/ meltfptr[24];;

        MELT_LOCATION("warmelt-macro.melt:8752:/ clear");
        /*clear*/ /*_.LOC__V18*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CONT__V19*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOTNULL__L6*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_#MELT_IS_BOOTSTRAPPING__L7*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L8*/ meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V26*/ meltfptr[24] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8747:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V17*/ meltfptr[15];;

        {
            MELT_LOCATION("warmelt-macro.melt:8747:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V17*/ meltfptr[15] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_174_WARMELTmiMACRO_MEXPAND_UPDATE_CURRENT_MODULE_ENVIRONMENT_REFERENCE*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED fromline 1715 */

    /** start of frame for meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED// fromline 1531
        : public Melt_CallFrameWithValues<32>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[14];
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
        MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<32> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED), clos) {};
        MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED() //the constructor fromline 1605
            : Melt_CallFrameWithValues<32> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<32> (fil,lin, sizeof(MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED)) {};
        MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<32> (fil,lin, sizeof(MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED


    /** end of frame for meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED fromline 1660**/

    /* end of frame for routine meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED fromline 1719 */

    /* classy proc frame meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED */ MeltFrame_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_FETCH_PREDEFINED", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8782:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8783:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8783:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8783:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8783;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_fetch_predefined sexpr";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8783:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8783:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8784:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8784:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8784:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8784;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8784:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8784:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8785:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8785:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8785:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8785;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8785:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8785:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L5*/ meltfnum[1] =
            (/*null*/(/*_.MEXPANDER__V4*/ meltfptr[3]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8786:/ cond");
        /*cond*/ if (/*_#NULL__L5*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^compute*/
                    /*_.MEXPANDER__V4*/ meltfptr[3] = /*_.SETQ___V15*/ meltfptr[5] = (/*!MACROEXPAND_1*/ meltfrout->tabval[4]);;
                    /*_._IF___V14*/ meltfptr[12] = /*_.SETQ___V15*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8786:/ clear");
                    /*clear*/ /*_.SETQ___V15*/ meltfptr[5] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V14*/ meltfptr[12] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8787:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8787:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V17*/ meltfptr[16] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8787:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8787;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V17*/ meltfptr[16] = /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8787:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V16*/ meltfptr[5] = /*_._IFELSE___V17*/ meltfptr[16];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8787:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V17*/ meltfptr[16] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V16*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8788:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8789:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V20*/ meltfptr[16] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8790:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V21*/ meltfptr[20] = slot;
        };
        ;
        /*_.LIST_FIRST__V22*/ meltfptr[21] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V20*/ meltfptr[16])));;
        /*^compute*/
        /*_.CURPAIR__V23*/ meltfptr[22] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V22*/ meltfptr[21])));;
        /*^compute*/
        /*_.PAIR_HEAD__V24*/ meltfptr[23] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8792:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.SPREDEF__V25*/ meltfptr[24] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V24*/ meltfptr[23]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#NULL__L7*/ meltfnum[0] =
            (/*null*/(/*_.CURPAIR__V23*/ meltfptr[22]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8794:/ cond");
        /*cond*/ if (/*_#NULL__L7*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8795:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(FETCH_PREDEFINED <predef-name-or-rank>) missing argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_.PAIR_TAIL__V26*/ meltfptr[25] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
        /*^compute*/
        /*_#NOTNULL__L8*/ meltfnum[7] =
            ((/*_.PAIR_TAIL__V26*/ meltfptr[25]) != NULL);;
        MELT_LOCATION("warmelt-macro.melt:8796:/ cond");
        /*cond*/ if (/*_#NOTNULL__L8*/ meltfnum[7]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8797:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(FETCH_PREDEFINED <predef-name-or-rank>) extra argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_A__L9*/ meltfnum[8] =
            melt_is_instance_of((melt_ptr_t)(/*_.SPREDEF__V25*/ meltfptr[24]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[5])));;
        MELT_LOCATION("warmelt-macro.melt:8798:/ cond");
        /*cond*/ if (/*_#IS_A__L9*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*_#OR___L10*/ meltfnum[9] = /*_#IS_A__L9*/ meltfnum[8];;
            }
        else
            {
                MELT_LOCATION("warmelt-macro.melt:8798:/ cond.else");

                /*^block*/
                /*anyblock*/
                {

                    /*_#IS_INTEGERBOX__L11*/ meltfnum[10] =
                        (melt_magic_discr((melt_ptr_t)(/*_.SPREDEF__V25*/ meltfptr[24])) == MELTOBMAG_INT);;
                    /*^compute*/
                    /*_#OR___L10*/ meltfnum[9] = /*_#IS_INTEGERBOX__L11*/ meltfnum[10];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8798:/ clear");
                    /*clear*/ /*_#IS_INTEGERBOX__L11*/ meltfnum[10] = 0 ;
                }
                ;
            }
        ;
        /*_#NOT__L12*/ meltfnum[10] =
            (!(/*_#OR___L10*/ meltfnum[9]));;
        MELT_LOCATION("warmelt-macro.melt:8798:/ cond");
        /*cond*/ if (/*_#NOT__L12*/ meltfnum[10]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8799:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(FETCH_PREDEFINED <predef-name-or-rank>) invalid argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8800:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^quasiblock*/


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_FETCH_PREDEFINED*/ meltfrout->tabval[6])), (3), "CLASS_SOURCE_FETCH_PREDEFINED");
            /*_.INST__V29*/ meltfptr[28] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (1), (/*_.LOC__V21*/ meltfptr[20]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SFEPD_PREDEF", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (2), (/*_.SPREDEF__V25*/ meltfptr[24]), "SFEPD_PREDEF");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V29*/ meltfptr[28], "newly made instance");
        ;
        /*_.RES__V28*/ meltfptr[27] = /*_.INST__V29*/ meltfptr[28];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8803:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L13*/ meltfnum[12] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8803:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L13*/ meltfnum[12]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L14*/ meltfnum[13] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8803:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L14*/ meltfnum[13];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8803;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_fetch_predefined result";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V28*/ meltfptr[27];
                            /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V30*/ meltfptr[29] = /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8803:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L14*/ meltfnum[13] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V31*/ meltfptr[30] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V30*/ meltfptr[29] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8803:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L13*/ meltfnum[12] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V30*/ meltfptr[29] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8804:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V28*/ meltfptr[27];;

        {
            MELT_LOCATION("warmelt-macro.melt:8804:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V27*/ meltfptr[26] = /*_.RETURN___V32*/ meltfptr[30];;

        MELT_LOCATION("warmelt-macro.melt:8800:/ clear");
        /*clear*/ /*_.RES__V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V32*/ meltfptr[30] = 0 ;
        /*_.LET___V19*/ meltfptr[17] = /*_.LET___V27*/ meltfptr[26];;

        MELT_LOCATION("warmelt-macro.melt:8788:/ clear");
        /*clear*/ /*_.CONT__V20*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SPREDEF__V25*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L7*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOTNULL__L8*/ meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L9*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_#OR___L10*/ meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L12*/ meltfnum[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V27*/ meltfptr[26] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8782:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V19*/ meltfptr[17];;

        {
            MELT_LOCATION("warmelt-macro.melt:8782:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L5*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V16*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V19*/ meltfptr[17] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_FETCH_PREDEFINED", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_175_WARMELTmiMACRO_MEXPAND_FETCH_PREDEFINED*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED_melt =  melt_blocklevel_signals;

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using OUTPUT_CURFRAME_DECLSTRUCT @warmelt-outobj.melt:1501

    /* start of frame for routine meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED fromline 1715 */

    /** start of frame for meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED of CLASS_PROCROUTINEOBJ from 1518**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED// fromline 1531
        : public Melt_CallFrameWithValues<38>
    {
    public: /* fromline 1535*/
        long mcfr_varnum[15];
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
        MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED(meltclosure_ptr_t clos) //the closure constructor fromline 1593
            : Melt_CallFrameWithValues<38> (
#if ENABLE_CHECKING /*fromline 1597*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1601*/
                sizeof(MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED), clos) {};
        MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED() //the constructor fromline 1605
            : Melt_CallFrameWithValues<38> (
#if ENABLE_CHECKING /*fromline 1609*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1613*/
                sizeof(MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED)) {};
#if ENABLE_CHECKING /*fromline 1617*/
        MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED(const char*fil, int lin) //the constructor fromline 1619
            : Melt_CallFrameWithValues<38> (fil,lin, sizeof(MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED)) {};
        MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1624
            : Melt_CallFrameWithValues<38> (fil,lin, sizeof(MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED), clos) {};
#endif /* ENABLE_CHECKING fromline 1629*/

    }; // end  class MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED


    /** end of frame for meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED fromline 1660**/

    /* end of frame for routine meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED fromline 1719 */

    /* classy proc frame meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED */ MeltFrame_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED
    meltfram__ /*declfrastruct fromline 1743*/
    /*classyprocarg meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED fromline 1748*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1752*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1756*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_STORE_PREDEFINED", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-macro.melt:8811:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8812:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L1*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8812:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8812:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8812;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_store_predefined sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8812:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V6*/ meltfptr[5] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8812:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V6*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8813:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-macro.melt:8813:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8813:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexpr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8813;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8813:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8813:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8814:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-macro.melt:8814:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V12*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8814:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check env";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8814;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V12*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8814:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V13*/ meltfptr[12] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V11*/ meltfptr[9] = /*_._IFELSE___V12*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8814:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V12*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V11*/ meltfptr[9] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L5*/ meltfnum[1] =
            (/*null*/(/*_.MEXPANDER__V4*/ meltfptr[3]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8815:/ cond");
        /*cond*/ if (/*_#NULL__L5*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^compute*/
                    /*_.MEXPANDER__V4*/ meltfptr[3] = /*_.SETQ___V15*/ meltfptr[5] = (/*!MACROEXPAND_1*/ meltfrout->tabval[4]);;
                    /*_._IF___V14*/ meltfptr[12] = /*_.SETQ___V15*/ meltfptr[5];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8815:/ clear");
                    /*clear*/ /*_.SETQ___V15*/ meltfptr[5] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V14*/ meltfptr[12] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8816:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L6*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-macro.melt:8816:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L6*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V17*/ meltfptr[16] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-macro.melt:8816:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check modctx";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8816;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V17*/ meltfptr[16] = /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8816:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V18*/ meltfptr[17] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V16*/ meltfptr[5] = /*_._IFELSE___V17*/ meltfptr[16];;
            /*epilog*/

            MELT_LOCATION("warmelt-macro.melt:8816:/ clear");
            /*clear*/ /*_#IS_OBJECT__L6*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V17*/ meltfptr[16] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V16*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8817:/ quasiblock");


        MELT_LOCATION("warmelt-macro.melt:8818:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V20*/ meltfptr[16] = slot;
        };
        ;
        MELT_LOCATION("warmelt-macro.melt:8819:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V21*/ meltfptr[20] = slot;
        };
        ;
        /*_.LIST_FIRST__V22*/ meltfptr[21] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V20*/ meltfptr[16])));;
        /*^compute*/
        /*_.CURPAIR__V23*/ meltfptr[22] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V22*/ meltfptr[21])));;
        /*^compute*/
        /*_.PAIR_HEAD__V24*/ meltfptr[23] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8821:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.SPREDEF__V25*/ meltfptr[24] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V24*/ meltfptr[23]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.SVAL__V26*/ meltfptr[25] = (/*nil*/NULL);;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#NULL__L7*/ meltfnum[0] =
            (/*null*/(/*_.CURPAIR__V23*/ meltfptr[22]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8824:/ cond");
        /*cond*/ if (/*_#NULL__L7*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8825:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(STORE_PREDEFINED <predef-name-or-rank> <value>) missing predef"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_TAIL__V27*/ meltfptr[26] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
        MELT_LOCATION("warmelt-macro.melt:8826:/ compute");
        /*_.CURPAIR__V23*/ meltfptr[22] = /*_.SETQ___V28*/ meltfptr[27] = /*_.PAIR_TAIL__V27*/ meltfptr[26];;

        MELT_CHECK_SIGNAL();
        ;
        /*_#NULL__L8*/ meltfnum[7] =
            (/*null*/(/*_.CURPAIR__V23*/ meltfptr[22]) == NULL);;
        MELT_LOCATION("warmelt-macro.melt:8827:/ cond");
        /*cond*/ if (/*_#NULL__L8*/ meltfnum[7]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8828:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(STORE_PREDEFINED <predef-name-or-rank> <value>) missing predef"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        /*_.PAIR_HEAD__V29*/ meltfptr[28] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8829:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[3];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.MEXPANDER__V30*/ meltfptr[29] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.PAIR_HEAD__V29*/ meltfptr[28]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*^compute*/
        /*_.SVAL__V26*/ meltfptr[25] = /*_.SETQ___V31*/ meltfptr[30] = /*_.MEXPANDER__V30*/ meltfptr[29];;

        MELT_CHECK_SIGNAL();
        ;
        /*_.PAIR_TAIL__V32*/ meltfptr[31] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V23*/ meltfptr[22])));;
        /*^compute*/
        /*_#NOTNULL__L9*/ meltfnum[8] =
            ((/*_.PAIR_TAIL__V32*/ meltfptr[31]) != NULL);;
        MELT_LOCATION("warmelt-macro.melt:8830:/ cond");
        /*cond*/ if (/*_#NOTNULL__L9*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8831:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(STORE_PREDEFINED <predef-name-or-rank> <value>) extra argument"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_A__L10*/ meltfnum[9] =
            melt_is_instance_of((melt_ptr_t)(/*_.SPREDEF__V25*/ meltfptr[24]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[5])));;
        MELT_LOCATION("warmelt-macro.melt:8832:/ cond");
        /*cond*/ if (/*_#IS_A__L10*/ meltfnum[9]) /*then*/
            {
                /*^cond.then*/
                /*_#OR___L11*/ meltfnum[10] = /*_#IS_A__L10*/ meltfnum[9];;
            }
        else
            {
                MELT_LOCATION("warmelt-macro.melt:8832:/ cond.else");

                /*^block*/
                /*anyblock*/
                {

                    /*_#IS_INTEGERBOX__L12*/ meltfnum[11] =
                        (melt_magic_discr((melt_ptr_t)(/*_.SPREDEF__V25*/ meltfptr[24])) == MELTOBMAG_INT);;
                    /*^compute*/
                    /*_#OR___L11*/ meltfnum[10] = /*_#IS_INTEGERBOX__L12*/ meltfnum[11];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-macro.melt:8832:/ clear");
                    /*clear*/ /*_#IS_INTEGERBOX__L12*/ meltfnum[11] = 0 ;
                }
                ;
            }
        ;
        /*_#NOT__L13*/ meltfnum[11] =
            (!(/*_#OR___L11*/ meltfnum[10]));;
        MELT_LOCATION("warmelt-macro.melt:8832:/ cond");
        /*cond*/ if (/*_#NOT__L13*/ meltfnum[11]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-macro.melt:8833:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.LOC__V21*/ meltfptr[20]), ( "(STORE_PREDEFINED <predef-name-or-rank> <value>) invalid predef"), (melt_ptr_t)0);
                    }
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;
        MELT_LOCATION("warmelt-macro.melt:8834:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^quasiblock*/


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_STORE_PREDEFINED*/ meltfrout->tabval[6])), (4), "CLASS_SOURCE_STORE_PREDEFINED");
            /*_.INST__V35*/ meltfptr[34] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V35*/ meltfptr[34])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V35*/ meltfptr[34]), (1), (/*_.LOC__V21*/ meltfptr[20]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SSTPD_PREDEF", melt_magic_discr((melt_ptr_t)(/*_.INST__V35*/ meltfptr[34])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V35*/ meltfptr[34]), (2), (/*_.SPREDEF__V25*/ meltfptr[24]), "SSTPD_PREDEF");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SSTPD_VALUE", melt_magic_discr((melt_ptr_t)(/*_.INST__V35*/ meltfptr[34])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V35*/ meltfptr[34]), (3), (/*_.SVAL__V26*/ meltfptr[25]), "SSTPD_VALUE");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V35*/ meltfptr[34], "newly made instance");
        ;
        /*_.RES__V34*/ meltfptr[33] = /*_.INST__V35*/ meltfptr[34];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-macro.melt:8839:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*melt_increment_dbgcounter*/
#if MELT_HAVE_DEBUG
                melt_dbgcounter++;
#endif
                ;
            }
            ;

            MELT_CHECK_SIGNAL();
            ;
            /*_#MELT_NEED_DBG__L14*/ meltfnum[13] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-macro.melt:8839:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L14*/ meltfnum[13]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L15*/ meltfnum[14] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-macro.melt:8839:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L15*/ meltfnum[14];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-macro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 8839;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_store_predefined result";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V34*/ meltfptr[33];
                            /*_.MELT_DEBUG_FUN__V37*/ meltfptr[36] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V36*/ meltfptr[35] = /*_.MELT_DEBUG_FUN__V37*/ meltfptr[36];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-macro.melt:8839:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L15*/ meltfnum[14] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V37*/ meltfptr[36] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V36*/ meltfptr[35] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-macro.melt:8839:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L14*/ meltfnum[13] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V36*/ meltfptr[35] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*^block*/
        /*anyblock*/
        {


            {
                /*^locexp*/
                /*void*/(void)0;
            }
            ;
            /*epilog*/
        }

#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8840:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V34*/ meltfptr[33];;

        {
            MELT_LOCATION("warmelt-macro.melt:8840:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*_.LET___V33*/ meltfptr[32] = /*_.RETURN___V38*/ meltfptr[36];;

        MELT_LOCATION("warmelt-macro.melt:8834:/ clear");
        /*clear*/ /*_.RES__V34*/ meltfptr[33] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V38*/ meltfptr[36] = 0 ;
        /*_.LET___V19*/ meltfptr[17] = /*_.LET___V33*/ meltfptr[32];;

        MELT_LOCATION("warmelt-macro.melt:8817:/ clear");
        /*clear*/ /*_.CONT__V20*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V23*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V24*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SPREDEF__V25*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SVAL__V26*/ meltfptr[25] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L7*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V27*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V28*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L8*/ meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_HEAD__V29*/ meltfptr[28] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MEXPANDER__V30*/ meltfptr[29] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SETQ___V31*/ meltfptr[30] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V32*/ meltfptr[31] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOTNULL__L9*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L10*/ meltfnum[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#OR___L11*/ meltfnum[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NOT__L13*/ meltfnum[11] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V33*/ meltfptr[32] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-macro.melt:8811:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V19*/ meltfptr[17];;

        {
            MELT_LOCATION("warmelt-macro.melt:8811:/ locexp");
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
        /*finalret*/ goto meltlabend_rout ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.IFCPP___V8*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_#NULL__L5*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V14*/ meltfptr[12] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V16*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V19*/ meltfptr[17] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_STORE_PREDEFINED", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_176_WARMELTmiMACRO_MEXPAND_STORE_PREDEFINED*/




/**** end of warmelt-macro+07.cc ****/
