/* GCC MELT GENERATED C++ FILE warmelt-moremacro.cc - DO NOT EDIT - see http://gcc-melt.org/ */

/***+ warmelt-moremacro without options +***/
#include "melt-run.h"


/* used hash from melt-run.h when compiling this file: */
MELT_EXTERN const char meltrun_used_md5_melt[] = MELT_RUN_HASHMD5 /* from melt-run.h */;


/**** warmelt-moremacro declarations ****/
/**** MELT GENERATED DECLARATIONS for warmelt-moremacro ** DO NOT EDIT ; see gcc-melt.org ****/

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


/** ordinary MELT module meltbuild-sources/warmelt-moremacro**/
#define MELT_HAS_INITIAL_ENVIRONMENT 1 /*usualmodule*/



class Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074; // forward declaration fromline 6691
typedef Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074 Melt_InitialFrame;
/**** no MELT module variables ****/

/*** 6 MELT called hook declarations ***/

/*declare MELT called hook #0 HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER **/
MELT_EXTERN melt_ptr_t melthook_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_PREVENV, const char* meltinp1_MODULNAME);

/*declare MELT called hook #1 HOOK_MACRO_EXPORTER **/
MELT_EXTERN void melthook_HOOK_MACRO_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_VAL, melt_ptr_t meltinp2_CONTENV);

/*declare MELT called hook #2 HOOK_MELT_MAKE_LOCATION **/
MELT_EXTERN melt_ptr_t melthook_HOOK_MELT_MAKE_LOCATION (melt_ptr_t melthookdatap, const char* meltinp0_FILENAME, long meltinp1_LINENO);

/*declare MELT called hook #3 HOOK_PATMACRO_EXPORTER **/
MELT_EXTERN void melthook_HOOK_PATMACRO_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_MACVAL, melt_ptr_t meltinp2_PATVAL, melt_ptr_t meltinp3_CONTENV);

/*declare MELT called hook #4 HOOK_SYMBOL_IMPORTER **/
MELT_EXTERN melt_ptr_t melthook_HOOK_SYMBOL_IMPORTER (melt_ptr_t melthookdatap, const char* meltinp0_SYMNAMESTR, const char* meltinp1_MODULENAMESTR, melt_ptr_t meltinp2_PARENV);

/*declare MELT called hook #5 HOOK_VALUE_EXPORTER **/
MELT_EXTERN void melthook_HOOK_VALUE_EXPORTER (melt_ptr_t melthookdatap, melt_ptr_t meltinp0_SYM, melt_ptr_t meltinp1_VAL, melt_ptr_t meltinp2_CONTENV);

/*** end of 6 MELT called hook declarations ***/

/*** no extra MELT c-headers ***/




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_8_WARMELTmiMOREMACRO_ANTIQUOTER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_9_WARMELTmiMOREMACRO_MEXPAND_BACKQUOTE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_10_WARMELTmiMOREMACRO_MEXPAND_COMMA(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);




MELT_EXTERN melt_ptr_t MELT_MODULE_VISIBILITY meltrout_11_WARMELTmiMOREMACRO_SUBSTITUTE_SEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_, const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_);


MELT_EXTERN void* melt_start_this_module (void*); /*mandatory start of module*/

MELT_EXTERN const char melt_module_is_gpl_compatible[];

/*declare opaque initial frame: */

typedef Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074 /*opaqueinitialclassy*/ meltinitial_frame_t;


/* define different names when debugging or not */
#if MELT_HAVE_DEBUG
MELT_EXTERN const char meltmodule_WARMELTmiMOREMACRO__melt_have_debug_enabled[];
#define melt_have_debug_string meltmodule_WARMELTmiMOREMACRO__melt_have_debug_enabled
#else /*!MELT_HAVE_DEBUG*/
MELT_EXTERN const char meltmodule_WARMELTmiMOREMACRO__melt_have_debug_disabled[];
#define melt_have_debug_string meltmodule_WARMELTmiMOREMACRO__melt_have_debug_disabled
#endif /*!MELT_HAVE_DEBUG*/



void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMOREMACRO__initialmeltchunk_0 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMOREMACRO__initialmeltchunk_1 (meltinitial_frame_t*, char*); //declare

void MELT_MODULE_VISIBILITY meltmod__WARMELTmiMOREMACRO__initialmeltchunk_2 (meltinitial_frame_t*, char*); //declare



/**** warmelt-moremacro implementations ****/
/**** MELT GENERATED IMPLEMENTATIONS for warmelt-moremacro ** DO NOT EDIT ; see gcc-melt.org ****/
/*** no extra MELT implementations ***/




melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST fromline 1752 */

    /** start of frame for meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST// fromline 1568
        : public Melt_CallFrameWithValues<75>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[28];
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
        MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<75> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST), clos) {};
        MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST() //the constructor fromline 1642
            : Melt_CallFrameWithValues<75> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<75> (fil,lin, sizeof(MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST)) {};
        MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<75> (fil,lin, sizeof(MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST


    /** end of frame for meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST fromline 1697**/

    /* end of frame for routine meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST fromline 1756 */

    /* classy proc frame meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST */ MeltFrame_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("EACH_COMPONENT_IN_LIST", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:44:/ getarg");
    /*_.SEXP__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

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
        MELT_LOCATION("warmelt-moremacro.melt:50:/ cppif.then");
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
            MELT_LOCATION("warmelt-moremacro.melt:50:/ cond");
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
                        MELT_LOCATION("warmelt-moremacro.melt:50:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[8];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 50;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list macro sexp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXP__V2*/ meltfptr[1];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  "\n env=";
                            /*^apply.arg*/
                            argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[1]);
                            /*^apply.arg*/
                            argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:50:/ clear");
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
                MELT_LOCATION("warmelt-moremacro.melt:50:/ locexp");
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
        MELT_LOCATION("warmelt-moremacro.melt:51:/ quasiblock");


        MELT_LOCATION("warmelt-moremacro.melt:52:/ cond");
        /*cond*/ if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SEXP__V2*/ meltfptr[1]),
                                          (melt_ptr_t)((/*!CLASS_LOCATED*/ meltfrout->tabval[2])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^getslot*/
                {
                    melt_ptr_t slot=NULL, obj=NULL;
                    obj = (melt_ptr_t)(/*_.SEXP__V2*/ meltfptr[1]) /*=obj*/;
                    melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
                    /*_.SLOC__V9*/ meltfptr[5] = slot;
                };
                ;
            }
        else    /*^cond.else*/
            {

                /*_.SLOC__V9*/ meltfptr[5] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-moremacro.melt:53:/ cond");
        /*cond*/ if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SEXP__V2*/ meltfptr[1]),
                                          (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[3])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^getslot*/
                {
                    melt_ptr_t slot=NULL, obj=NULL;
                    obj = (melt_ptr_t)(/*_.SEXP__V2*/ meltfptr[1]) /*=obj*/;
                    melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
                    /*_.SEXCONT__V10*/ meltfptr[9] = slot;
                };
                ;
            }
        else    /*^cond.else*/
            {

                /*_.SEXCONT__V10*/ meltfptr[9] =  /*reallynil*/ NULL ;;
            }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:55:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L3*/ meltfnum[1] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:55:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L4*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:55:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[8];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L4*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 55;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list sloc=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[1]);
                            /*^apply.arg*/
                            argtab[5].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V9*/ meltfptr[5];
                            /*^apply.arg*/
                            argtab[6].meltbp_cstring =  " sexcont=";
                            /*^apply.arg*/
                            argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SEXCONT__V10*/ meltfptr[9];
                            /*_.MELT_DEBUG_FUN__V12*/ meltfptr[11] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V11*/ meltfptr[10] = /*_.MELT_DEBUG_FUN__V12*/ meltfptr[11];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:55:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L4*/ meltfnum[0] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V12*/ meltfptr[11] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V11*/ meltfptr[10] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:55:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V11*/ meltfptr[10] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:56:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_LIST__L5*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.SEXCONT__V10*/ meltfptr[9])) == MELTOBMAG_LIST);;
            MELT_LOCATION("warmelt-moremacro.melt:56:/ cond");
            /*cond*/ if (/*_#IS_LIST__L5*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V14*/ meltfptr[10] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:56:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check sexcont";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 56;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXCONT__V10*/ meltfptr[9];
                            /*_.MELT_ASSERT_FAILURE_FUN__V15*/ meltfptr[14] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[4])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V14*/ meltfptr[10] = /*_.MELT_ASSERT_FAILURE_FUN__V15*/ meltfptr[14];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:56:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V15*/ meltfptr[14] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V13*/ meltfptr[11] = /*_._IFELSE___V14*/ meltfptr[10];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:56:/ clear");
            /*clear*/ /*_#IS_LIST__L5*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V14*/ meltfptr[10] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V13*/ meltfptr[11] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:57:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:58:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[6]);
            /*_.TCONT__V17*/ meltfptr[10] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[5])), (melt_ptr_t)(/*_.SEXCONT__V10*/ meltfptr[9]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_#TCONTLEN__L6*/ meltfnum[1] =
            (melt_multiple_length((melt_ptr_t)(/*_.TCONT__V17*/ meltfptr[10])));;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:61:/ cppif.then");
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
            MELT_LOCATION("warmelt-moremacro.melt:61:/ cond");
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
                        MELT_LOCATION("warmelt-moremacro.melt:61:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[7];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L8*/ meltfnum[7];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 61;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list tcont=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.TCONT__V17*/ meltfptr[10];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  "; tcontlen=";
                            /*^apply.arg*/
                            argtab[6].meltbp_long = /*_#TCONTLEN__L6*/ meltfnum[1];
                            /*_.MELT_DEBUG_FUN__V19*/ meltfptr[18] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_LONG ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V18*/ meltfptr[17] = /*_.MELT_DEBUG_FUN__V19*/ meltfptr[18];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:61:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L8*/ meltfnum[7] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V19*/ meltfptr[18] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V18*/ meltfptr[17] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:61:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L7*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V18*/ meltfptr[17] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:62:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_MULTIPLE__L9*/ meltfnum[7] =
                (melt_magic_discr((melt_ptr_t)(/*_.TCONT__V17*/ meltfptr[10])) == MELTOBMAG_MULTIPLE);;
            MELT_LOCATION("warmelt-moremacro.melt:62:/ cond");
            /*cond*/ if (/*_#IS_MULTIPLE__L9*/ meltfnum[7]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V21*/ meltfptr[17] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:62:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check tcont";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 62;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.TCONT__V17*/ meltfptr[10];
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXCONT__V10*/ meltfptr[9];
                            /*_.MELT_ASSERT_FAILURE_FUN__V22*/ meltfptr[21] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[4])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V21*/ meltfptr[17] = /*_.MELT_ASSERT_FAILURE_FUN__V22*/ meltfptr[21];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:62:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V22*/ meltfptr[21] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V20*/ meltfptr[18] = /*_._IFELSE___V21*/ meltfptr[17];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:62:/ clear");
            /*clear*/ /*_#IS_MULTIPLE__L9*/ meltfnum[7] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V21*/ meltfptr[17] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V20*/ meltfptr[18] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:63:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#gtI__L10*/ meltfnum[0] =
                ((/*_#TCONTLEN__L6*/ meltfnum[1]) > (0));;
            MELT_LOCATION("warmelt-moremacro.melt:63:/ cond");
            /*cond*/ if (/*_#gtI__L10*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V24*/ meltfptr[17] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:63:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check tcontlen";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 63;
                            /*^apply.arg*/
                            argtab[3].meltbp_long = /*_#TCONTLEN__L6*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.TCONT__V17*/ meltfptr[10];
                            /*_.MELT_ASSERT_FAILURE_FUN__V25*/ meltfptr[24] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[4])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V24*/ meltfptr[17] = /*_.MELT_ASSERT_FAILURE_FUN__V25*/ meltfptr[24];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:63:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V25*/ meltfptr[24] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V23*/ meltfptr[21] = /*_._IFELSE___V24*/ meltfptr[17];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:63:/ clear");
            /*clear*/ /*_#gtI__L10*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V24*/ meltfptr[17] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V23*/ meltfptr[21] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#ltI__L11*/ meltfnum[7] =
            ((/*_#TCONTLEN__L6*/ meltfnum[1]) < (4));;
        MELT_LOCATION("warmelt-moremacro.melt:64:/ cond");
        /*cond*/ if (/*_#ltI__L11*/ meltfnum[7]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-moremacro.melt:65:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.SLOC__V9*/ meltfptr[5]), ( "EACH_COMPONENT_IN_LIST <expr-list> <var-comp> too short"), (melt_ptr_t)0);
                    }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-moremacro.melt:66:/ quasiblock");


                    /*_._RETVAL___V1*/ meltfptr[0] = (/*nil*/NULL);;
                    MELT_LOCATION("warmelt-moremacro.melt:66:/ putxtraresult");
                    if (!meltxrestab_ || !meltxresdescr_) goto meltlabend_rout;
                    if (meltxresdescr_[0] != MELTBPAR_PTR) goto meltlabend_rout;
                    if (meltxrestab_[0].meltbp_aptr) *(meltxrestab_[0].meltbp_aptr) = (melt_ptr_t) ((/*nil*/NULL));
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/ goto meltlabend_rout ;
                    MELT_LOCATION("warmelt-moremacro.melt:64:/ quasiblock");


                    /*_.PROGN___V28*/ meltfptr[27] = /*_.RETURN___V27*/ meltfptr[17];;
                    /*^compute*/
                    /*_._IF___V26*/ meltfptr[24] = /*_.PROGN___V28*/ meltfptr[27];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:64:/ clear");
                    /*clear*/ /*_.RETURN___V27*/ meltfptr[17] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V28*/ meltfptr[27] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V26*/ meltfptr[24] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-moremacro.melt:67:/ quasiblock");


        MELT_LOCATION("warmelt-moremacro.melt:68:/ quasiblock");


        /*_.SE__V31*/ meltfptr[30] =
            (melt_multiple_nth((melt_ptr_t)(/*_.TCONT__V17*/ meltfptr[10]), (1)));;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:70:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L12*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:70:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L12*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L13*/ meltfnum[12] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:70:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L13*/ meltfnum[12];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 70;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list sexplist=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SE__V31*/ meltfptr[30];
                            /*_.MELT_DEBUG_FUN__V33*/ meltfptr[32] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V32*/ meltfptr[31] = /*_.MELT_DEBUG_FUN__V33*/ meltfptr[32];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:70:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L13*/ meltfnum[12] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V33*/ meltfptr[32] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V32*/ meltfptr[31] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:70:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L12*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V32*/ meltfptr[31] = 0 ;
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
        /*_.LET___V30*/ meltfptr[27] = /*_.SE__V31*/ meltfptr[30];;

        MELT_LOCATION("warmelt-moremacro.melt:68:/ clear");
        /*clear*/ /*_.SE__V31*/ meltfptr[30] = 0 ;
        /*_.SEXPLIST__V34*/ meltfptr[32] = /*_.LET___V30*/ meltfptr[27];;
        MELT_LOCATION("warmelt-moremacro.melt:72:/ quasiblock");


        /*_.SV__V36*/ meltfptr[30] =
            (melt_multiple_nth((melt_ptr_t)(/*_.TCONT__V17*/ meltfptr[10]), (2)));;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:74:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L14*/ meltfnum[12] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:74:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L14*/ meltfnum[12]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L15*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:74:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L15*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 74;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list svarcomp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SV__V36*/ meltfptr[30];
                            /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V37*/ meltfptr[36] = /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:74:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L15*/ meltfnum[0] = 0 ;
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
                MELT_LOCATION("warmelt-moremacro.melt:74:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L14*/ meltfnum[12] = 0 ;
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
        /*_.LET___V35*/ meltfptr[31] = /*_.SV__V36*/ meltfptr[30];;

        MELT_LOCATION("warmelt-moremacro.melt:72:/ clear");
        /*clear*/ /*_.SV__V36*/ meltfptr[30] = 0 ;
        /*_.SVARCOMP__V39*/ meltfptr[37] = /*_.LET___V35*/ meltfptr[31];;
        MELT_LOCATION("warmelt-moremacro.melt:76:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
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
            /*_.ME__V41*/ meltfptr[30] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.SEXPLIST__V34*/ meltfptr[32]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:78:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L16*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:78:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L16*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L17*/ meltfnum[12] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:78:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L17*/ meltfnum[12];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 78;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list mlistexp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.ME__V41*/ meltfptr[30];
                            /*_.MELT_DEBUG_FUN__V43*/ meltfptr[42] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V42*/ meltfptr[41] = /*_.MELT_DEBUG_FUN__V43*/ meltfptr[42];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:78:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L17*/ meltfnum[12] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V43*/ meltfptr[42] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V42*/ meltfptr[41] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:78:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L16*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V42*/ meltfptr[41] = 0 ;
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
        /*_.LET___V40*/ meltfptr[36] = /*_.ME__V41*/ meltfptr[30];;

        MELT_LOCATION("warmelt-moremacro.melt:76:/ clear");
        /*clear*/ /*_.ME__V41*/ meltfptr[30] = 0 ;
        /*_.MLISTEXP__V44*/ meltfptr[42] = /*_.LET___V40*/ meltfptr[36];;
        MELT_LOCATION("warmelt-moremacro.melt:80:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
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
            /*_.MV__V46*/ meltfptr[30] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.SVARCOMP__V39*/ meltfptr[37]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:82:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L18*/ meltfnum[12] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:82:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L18*/ meltfnum[12]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L19*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:82:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L19*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 82;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list mvarcomp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.MV__V46*/ meltfptr[30];
                            /*_.MELT_DEBUG_FUN__V48*/ meltfptr[47] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V47*/ meltfptr[46] = /*_.MELT_DEBUG_FUN__V48*/ meltfptr[47];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:82:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L19*/ meltfnum[0] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V48*/ meltfptr[47] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V47*/ meltfptr[46] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:82:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L18*/ meltfnum[12] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V47*/ meltfptr[46] = 0 ;
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
        /*_.LET___V45*/ meltfptr[41] = /*_.MV__V46*/ meltfptr[30];;

        MELT_LOCATION("warmelt-moremacro.melt:80:/ clear");
        /*clear*/ /*_.MV__V46*/ meltfptr[30] = 0 ;
        /*_.MVARCOMP__V49*/ meltfptr[47] = /*_.LET___V45*/ meltfptr[41];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:85:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L20*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:85:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L20*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L21*/ meltfnum[12] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:85:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[7];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L21*/ meltfnum[12];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 85;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list tcont=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.TCONT__V17*/ meltfptr[10];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  "\n.. before expand_tuple_slice_as_tuple=";
                            /*^apply.arg*/
                            argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!EXPAND_TUPLE_SLICE_AS_TUPLE*/ meltfrout->tabval[7]);
                            /*_.MELT_DEBUG_FUN__V51*/ meltfptr[30] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V50*/ meltfptr[46] = /*_.MELT_DEBUG_FUN__V51*/ meltfptr[30];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:85:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L21*/ meltfnum[12] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V51*/ meltfptr[30] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V50*/ meltfptr[46] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:85:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L20*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V50*/ meltfptr[46] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:87:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            union meltparam_un argtab[5];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_long = 3;
            /*^apply.arg*/
            argtab[1].meltbp_long = -1;
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
            /*^apply.arg*/
            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
            /*_.BE__V53*/ meltfptr[46] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_TUPLE_SLICE_AS_TUPLE*/ meltfrout->tabval[7])), (melt_ptr_t)(/*_.TCONT__V17*/ meltfptr[10]), (MELTBPARSTR_LONG MELTBPARSTR_LONG MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:89:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L22*/ meltfnum[12] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:89:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L22*/ meltfnum[12]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L23*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:89:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L23*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 89;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list bodyexp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.BE__V53*/ meltfptr[46];
                            /*_.MELT_DEBUG_FUN__V55*/ meltfptr[54] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V54*/ meltfptr[53] = /*_.MELT_DEBUG_FUN__V55*/ meltfptr[54];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:89:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L23*/ meltfnum[0] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V55*/ meltfptr[54] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V54*/ meltfptr[53] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:89:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L22*/ meltfnum[12] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V54*/ meltfptr[53] = 0 ;
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
        /*_.LET___V52*/ meltfptr[30] = /*_.BE__V53*/ meltfptr[46];;

        MELT_LOCATION("warmelt-moremacro.melt:87:/ clear");
        /*clear*/ /*_.BE__V53*/ meltfptr[46] = 0 ;
        MELT_LOCATION("warmelt-moremacro.melt:84:/ quasiblock");


        /*_.BODYEXP__V56*/ meltfptr[54] = /*_.LET___V52*/ meltfptr[30];;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_NOT_A__L24*/ meltfnum[0] =
            !melt_is_instance_of((melt_ptr_t)(/*_.MVARCOMP__V49*/ meltfptr[47]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[8])));;
        MELT_LOCATION("warmelt-moremacro.melt:92:/ cond");
        /*cond*/ if (/*_#IS_NOT_A__L24*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    {
                        MELT_LOCATION("warmelt-moremacro.melt:93:/ locexp");
                        /* error_plain */ melt_error_str((melt_ptr_t)(/*_.SLOC__V9*/ meltfptr[5]), ( "EACH_COMPONENT_IN_LIST <expr-list> <var-comp> bad second argument for\
 component variable"), (melt_ptr_t)0);
                    }
                    ;

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-moremacro.melt:94:/ quasiblock");


                    /*_._RETVAL___V1*/ meltfptr[0] = (/*nil*/NULL);;
                    MELT_LOCATION("warmelt-moremacro.melt:94:/ putxtraresult");
                    if (!meltxrestab_ || !meltxresdescr_) goto meltlabend_rout;
                    if (meltxresdescr_[0] != MELTBPAR_PTR) goto meltlabend_rout;
                    if (meltxrestab_[0].meltbp_aptr) *(meltxrestab_[0].meltbp_aptr) = (melt_ptr_t) ((/*nil*/NULL));
                    ;
                    /*^finalreturn*/
                    ;
                    /*finalret*/ goto meltlabend_rout ;
                    MELT_LOCATION("warmelt-moremacro.melt:92:/ quasiblock");


                    /*_.PROGN___V59*/ meltfptr[58] = /*_.RETURN___V58*/ meltfptr[46];;
                    /*^compute*/
                    /*_._IF___V57*/ meltfptr[53] = /*_.PROGN___V59*/ meltfptr[58];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:92:/ clear");
                    /*clear*/ /*_.RETURN___V58*/ meltfptr[46] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V59*/ meltfptr[58] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V57*/ meltfptr[53] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-moremacro.melt:95:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:96:/ apply");
        /*apply*/
        {
            /*_.CURPAIRINLISTSYMB__V61*/ meltfptr[58] =  melt_apply ((meltclosure_ptr_t)((/*!CLONE_SYMBOL*/ meltfrout->tabval[9])), (melt_ptr_t)((/*!konst_10_CURPAIRINLISTSYMB*/ meltfrout->tabval[10])), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-moremacro.melt:97:/ quasiblock");


        /*_.HOOK_MELT_MAKE_LOCATION__V63*/ meltfptr[62] =
            /*hookcall*/ melthook_HOOK_MELT_MAKE_LOCATION ((melt_ptr_t) (/*!HOOK_MELT_MAKE_LOCATION*/ meltfrout->tabval[12]),  "warmelt-moremacro.melt", 98) ;;
        /*^compute*/
        /*_.HOOK_MELT_MAKE_LOCATION__V64*/ meltfptr[63] =
            /*hookcall*/ melthook_HOOK_MELT_MAKE_LOCATION ((melt_ptr_t) (/*!HOOK_MELT_MAKE_LOCATION*/ meltfrout->tabval[12]),  "warmelt-moremacro.melt", 99) ;;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:99:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.MLISTEXP__V44*/ meltfptr[42];
            /*_.MELT_MAKE_SEXPR__V65*/ meltfptr[64] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_MAKE_SEXPR*/ meltfrout->tabval[11])), (melt_ptr_t)(/*_.HOOK_MELT_MAKE_LOCATION__V64*/ meltfptr[63]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*_.HOOK_MELT_MAKE_LOCATION__V66*/ meltfptr[65] =
            /*hookcall*/ melthook_HOOK_MELT_MAKE_LOCATION ((melt_ptr_t) (/*!HOOK_MELT_MAKE_LOCATION*/ meltfrout->tabval[12]),  "warmelt-moremacro.melt", 100) ;;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:100:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.CURPAIRINLISTSYMB__V61*/ meltfptr[58];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MVARCOMP__V49*/ meltfptr[47];
            /*_.MELT_MAKE_SEXPR__V67*/ meltfptr[66] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_MAKE_SEXPR*/ meltfrout->tabval[11])), (melt_ptr_t)(/*_.HOOK_MELT_MAKE_LOCATION__V66*/ meltfptr[65]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:98:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[4];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!konst_13_FOREACH_PAIR_COMPONENT_IN_LIST*/ meltfrout->tabval[13]);
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.MELT_MAKE_SEXPR__V65*/ meltfptr[64];
            /*^apply.arg*/
            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MELT_MAKE_SEXPR__V67*/ meltfptr[66];
            /*^apply.arg*/
            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.BODYEXP__V56*/ meltfptr[54];
            /*_.RESEXP__V68*/ meltfptr[67] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_MAKE_SEXPR*/ meltfrout->tabval[11])), (melt_ptr_t)(/*_.HOOK_MELT_MAKE_LOCATION__V63*/ meltfptr[62]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:103:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L25*/ meltfnum[12] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:103:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L25*/ meltfnum[12]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L26*/ meltfnum[25] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:103:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L26*/ meltfnum[25];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 103;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list resexp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RESEXP__V68*/ meltfptr[67];
                            /*_.MELT_DEBUG_FUN__V70*/ meltfptr[69] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V69*/ meltfptr[68] = /*_.MELT_DEBUG_FUN__V70*/ meltfptr[69];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:103:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L26*/ meltfnum[25] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V70*/ meltfptr[69] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V69*/ meltfptr[68] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:103:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L25*/ meltfnum[12] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V69*/ meltfptr[68] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:104:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
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
            /*_.MEXP__V72*/ meltfptr[68] =  melt_apply ((meltclosure_ptr_t)(/*_.MEXPANDER__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.RESEXP__V68*/ meltfptr[67]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:106:/ cond");
        /*cond*/ if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.MEXP__V72*/ meltfptr[68]),
                                          (melt_ptr_t)((/*!CLASS_LOCATED*/ meltfrout->tabval[2])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*^putslot*/
                    /*putslot*/
                    melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.MEXP__V72*/ meltfptr[68])) == MELTOBMAG_OBJECT);
                    melt_putfield_object((/*_.MEXP__V72*/ meltfptr[68]), (1), (/*_.SLOC__V9*/ meltfptr[5]), "LOCA_LOCATION");
                    ;
                    /*^touch*/
                    meltgc_touch(/*_.MEXP__V72*/ meltfptr[68]);
                    ;
                    /*^touchobj*/

                    melt_dbgtrace_written_object (/*_.MEXP__V72*/ meltfptr[68], "put-fields");
                    ;
                    /*epilog*/
                }
                ;
            } /*noelse*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:107:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L27*/ meltfnum[25] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:107:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L27*/ meltfnum[25]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L28*/ meltfnum[12] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:107:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L28*/ meltfnum[12];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 107;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "each_component_in_list final mexp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.MEXP__V72*/ meltfptr[68];
                            /*_.MELT_DEBUG_FUN__V74*/ meltfptr[73] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V73*/ meltfptr[72] = /*_.MELT_DEBUG_FUN__V74*/ meltfptr[73];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:107:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L28*/ meltfnum[12] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V74*/ meltfptr[73] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V73*/ meltfptr[72] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:107:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L27*/ meltfnum[25] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V73*/ meltfptr[72] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:108:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.MEXP__V72*/ meltfptr[68];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:108:/ locexp");
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
        /*_.LET___V71*/ meltfptr[69] = /*_.RETURN___V75*/ meltfptr[73];;

        MELT_LOCATION("warmelt-moremacro.melt:104:/ clear");
        /*clear*/ /*_.MEXP__V72*/ meltfptr[68] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V75*/ meltfptr[73] = 0 ;
        /*_.LET___V62*/ meltfptr[61] = /*_.LET___V71*/ meltfptr[69];;

        MELT_LOCATION("warmelt-moremacro.melt:97:/ clear");
        /*clear*/ /*_.HOOK_MELT_MAKE_LOCATION__V63*/ meltfptr[62] = 0 ;
        /*^clear*/
        /*clear*/ /*_.HOOK_MELT_MAKE_LOCATION__V64*/ meltfptr[63] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MELT_MAKE_SEXPR__V65*/ meltfptr[64] = 0 ;
        /*^clear*/
        /*clear*/ /*_.HOOK_MELT_MAKE_LOCATION__V66*/ meltfptr[65] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MELT_MAKE_SEXPR__V67*/ meltfptr[66] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RESEXP__V68*/ meltfptr[67] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V71*/ meltfptr[69] = 0 ;
        /*_.LET___V60*/ meltfptr[46] = /*_.LET___V62*/ meltfptr[61];;

        MELT_LOCATION("warmelt-moremacro.melt:95:/ clear");
        /*clear*/ /*_.CURPAIRINLISTSYMB__V61*/ meltfptr[58] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V62*/ meltfptr[61] = 0 ;
        /*_.LET___V29*/ meltfptr[17] = /*_.LET___V60*/ meltfptr[46];;

        MELT_LOCATION("warmelt-moremacro.melt:67:/ clear");
        /*clear*/ /*_.LET___V30*/ meltfptr[27] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SEXPLIST__V34*/ meltfptr[32] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V35*/ meltfptr[31] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SVARCOMP__V39*/ meltfptr[37] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V40*/ meltfptr[36] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MLISTEXP__V44*/ meltfptr[42] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V45*/ meltfptr[41] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MVARCOMP__V49*/ meltfptr[47] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V52*/ meltfptr[30] = 0 ;
        /*^clear*/
        /*clear*/ /*_.BODYEXP__V56*/ meltfptr[54] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_NOT_A__L24*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V57*/ meltfptr[53] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V60*/ meltfptr[46] = 0 ;
        /*_.LET___V16*/ meltfptr[14] = /*_.LET___V29*/ meltfptr[17];;

        MELT_LOCATION("warmelt-moremacro.melt:57:/ clear");
        /*clear*/ /*_.TCONT__V17*/ meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_#TCONTLEN__L6*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V20*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V23*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_#ltI__L11*/ meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V26*/ meltfptr[24] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V29*/ meltfptr[17] = 0 ;
        /*_.LET___V8*/ meltfptr[6] = /*_.LET___V16*/ meltfptr[14];;

        MELT_LOCATION("warmelt-moremacro.melt:51:/ clear");
        /*clear*/ /*_.SLOC__V9*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SEXCONT__V10*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V13*/ meltfptr[11] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V16*/ meltfptr[14] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:44:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V8*/ meltfptr[6];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:44:/ locexp");
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
        /*clear*/ /*_.LET___V8*/ meltfptr[6] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("EACH_COMPONENT_IN_LIST", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION fromline 1752 */

    /** start of frame for meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION// fromline 1568
        : public Melt_CallFrameWithValues<10>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[4];
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
        MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<10> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION), clos) {};
        MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION() //the constructor fromline 1642
            : Melt_CallFrameWithValues<10> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<10> (fil,lin, sizeof(MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION)) {};
        MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<10> (fil,lin, sizeof(MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION


    /** end of frame for meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION fromline 1697**/

    /* end of frame for routine meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION fromline 1756 */

    /* classy proc frame meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION */ MeltFrame_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("FILTERGCCVERSION", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:116:/ getarg");
    /*_.VERSIONSTR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;
    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:117:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_STRING__L1*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.VERSIONSTR__V2*/ meltfptr[1])) == MELTOBMAG_STRING);;
            MELT_LOCATION("warmelt-moremacro.melt:117:/ cond");
            /*cond*/ if (/*_#IS_STRING__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V4*/ meltfptr[3] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:117:/ cond.else");

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
                            argtab[0].meltbp_cstring =  "check versionstr";
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 117;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.VERSIONSTR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V5*/ meltfptr[4] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V4*/ meltfptr[3] = /*_.MELT_ASSERT_FAILURE_FUN__V5*/ meltfptr[4];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:117:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V5*/ meltfptr[4] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V3*/ meltfptr[2] = /*_._IFELSE___V4*/ meltfptr[3];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:117:/ clear");
            /*clear*/ /*_#IS_STRING__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V4*/ meltfptr[3] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V3*/ meltfptr[2] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:118:/ quasiblock");


        /*_#VERSIONLEN__L2*/ meltfnum[0] =
            melt_string_length((melt_ptr_t)(/*_.VERSIONSTR__V2*/ meltfptr[1]));;
        /*^compute*/
        /*_.RES__V7*/ meltfptr[3] = (/*nil*/NULL);;
        /*^compute*/
        /*_?*/ meltfram__.loc_CSTRING__o0 =  "?";;
        /*^compute*/
        /*_?*/ meltfram__.loc_CSTRING__o1 =  "-?-";;

        {
            MELT_LOCATION("warmelt-moremacro.melt:126:/ locexp");
            /* filtergccversion FILTERGCC__1*/
            /*_?*/ meltfram__.loc_CSTRING__o0 = melt_gccversionstr;
            /*_?*/ meltfram__.loc_CSTRING__o1 = melt_gccversionstr+/*_#VERSIONLEN__L2*/ meltfnum[0];
            if (/*_#VERSIONLEN__L2*/ meltfnum[0]>0
                                     && !strncmp (melt_string_str((melt_ptr_t)/*_.VERSIONSTR__V2*/ meltfptr[1]),
                                                  melt_gccversionstr,
                                                  /*_#VERSIONLEN__L2*/ meltfnum[0])
                                     && !ISDIGIT (melt_gccversionstr[/*_#VERSIONLEN__L2*/ meltfnum[0]]))
                /*_.RES__V7*/ meltfptr[3] = /*_.VERSIONSTR__V2*/ meltfptr[1];
            ;
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:138:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L3*/ meltfnum[2] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:138:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L3*/ meltfnum[2]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L4*/ meltfnum[3] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:138:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[13];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L4*/ meltfnum[3];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 138;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "filtergccversion versionlen=";
                            /*^apply.arg*/
                            argtab[4].meltbp_long = /*_#VERSIONLEN__L2*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  " versionstr=";
                            /*^apply.arg*/
                            argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.VERSIONSTR__V2*/ meltfptr[1];
                            /*^apply.arg*/
                            argtab[7].meltbp_cstring =  " gccverstr=\'";
                            /*^apply.arg*/
                            argtab[8].meltbp_cstring = /*_?*/ meltfram__.loc_CSTRING__o0;
                            /*^apply.arg*/
                            argtab[9].meltbp_cstring =  "\'; gccverest=\'";
                            /*^apply.arg*/
                            argtab[10].meltbp_cstring = /*_?*/ meltfram__.loc_CSTRING__o1;
                            /*^apply.arg*/
                            argtab[11].meltbp_cstring =  "\'\n.. res=";
                            /*^apply.arg*/
                            argtab[12].meltbp_aptr = (melt_ptr_t*) &/*_.RES__V7*/ meltfptr[3];
                            /*_.MELT_DEBUG_FUN__V9*/ meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V8*/ meltfptr[7] = /*_.MELT_DEBUG_FUN__V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:138:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L4*/ meltfnum[3] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V9*/ meltfptr[8] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V8*/ meltfptr[7] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:138:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L3*/ meltfnum[2] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V8*/ meltfptr[7] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:140:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.RES__V7*/ meltfptr[3];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:140:/ locexp");
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
        /*_.LET___V6*/ meltfptr[4] = /*_.RETURN___V10*/ meltfptr[8];;

        MELT_LOCATION("warmelt-moremacro.melt:118:/ clear");
        /*clear*/ /*_#VERSIONLEN__L2*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RES__V7*/ meltfptr[3] = 0 ;
        /*^clear*/
        /*clear*/ /*_?*/ meltfram__.loc_CSTRING__o0 = 0 ;
        /*^clear*/
        /*clear*/ /*_?*/ meltfram__.loc_CSTRING__o1 = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V10*/ meltfptr[8] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:116:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V6*/ meltfptr[4];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:116:/ locexp");
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
        /*clear*/ /*_.IFCPP___V3*/ meltfptr[2] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V6*/ meltfptr[4] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("FILTERGCCVERSION", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF fromline 1752 */

    /** start of frame for meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF// fromline 1568
        : public Melt_CallFrameWithValues<83>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[33];
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
        MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<83> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF), clos) {};
        MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF() //the constructor fromline 1642
            : Melt_CallFrameWithValues<83> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<83> (fil,lin, sizeof(MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF)) {};
        MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<83> (fil,lin, sizeof(MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF


    /** end of frame for meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF fromline 1697**/

    /* end of frame for routine meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF fromline 1756 */

    /* classy proc frame meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF */ MeltFrame_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_GCCIF", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:143:/ getarg");
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
        MELT_LOCATION("warmelt-moremacro.melt:144:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L1*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[0])));;
            MELT_LOCATION("warmelt-moremacro.melt:144:/ cond");
            /*cond*/ if (/*_#IS_A__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V7*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:144:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 144;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V8*/ meltfptr[7] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V7*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V8*/ meltfptr[7];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:144:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V8*/ meltfptr[7] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V6*/ meltfptr[5] = /*_._IFELSE___V7*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:144:/ clear");
            /*clear*/ /*_#IS_A__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V7*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V6*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:145:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L2*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[2])));;
            MELT_LOCATION("warmelt-moremacro.melt:145:/ cond");
            /*cond*/ if (/*_#IS_A__L2*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V10*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:145:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 145;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V10*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:145:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V9*/ meltfptr[7] = /*_._IFELSE___V10*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:145:/ clear");
            /*clear*/ /*_#IS_A__L2*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V10*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V9*/ meltfptr[7] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:146:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L3*/ meltfnum[0] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:146:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L3*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L4*/ meltfnum[3] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:146:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L4*/ meltfnum[3];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 146;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_gccif sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V13*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V12*/ meltfptr[10] = /*_.MELT_DEBUG_FUN__V13*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:146:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L4*/ meltfnum[3] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V13*/ meltfptr[6] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V12*/ meltfptr[10] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:146:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L3*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V12*/ meltfptr[10] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:147:/ quasiblock");


        MELT_LOCATION("warmelt-moremacro.melt:148:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V15*/ meltfptr[10] = slot;
        };
        ;
        MELT_LOCATION("warmelt-moremacro.melt:149:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.SLOC__V16*/ meltfptr[15] = slot;
        };
        ;
        /*_.LIST_FIRST__V17*/ meltfptr[16] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V15*/ meltfptr[10])));;
        /*^compute*/
        /*_.CURPAIR__V18*/ meltfptr[17] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V17*/ meltfptr[16])));;
        /*^compute*/
        /*_.CURIF__V19*/ meltfptr[18] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V18*/ meltfptr[17])));;
        /*^compute*/
        /*_.RESTPAIR__V20*/ meltfptr[19] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V18*/ meltfptr[17])));;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:154:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L5*/ meltfnum[3] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:154:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L5*/ meltfnum[3]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L6*/ meltfnum[0] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:154:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[7];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L6*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 154;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpand_gccif restpair=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.RESTPAIR__V20*/ meltfptr[19];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  "\n.. first curif=";
                            /*^apply.arg*/
                            argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.CURIF__V19*/ meltfptr[18];
                            /*_.MELT_DEBUG_FUN__V22*/ meltfptr[21] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V21*/ meltfptr[20] = /*_.MELT_DEBUG_FUN__V22*/ meltfptr[21];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:154:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L6*/ meltfnum[0] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V22*/ meltfptr[21] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V21*/ meltfptr[20] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:154:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L5*/ meltfnum[3] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V21*/ meltfptr[20] = 0 ;
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
        /*_#IS_A__L7*/ meltfnum[0] =
            melt_is_instance_of((melt_ptr_t)(/*_.CURIF__V19*/ meltfptr[18]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[0])));;
        MELT_LOCATION("warmelt-moremacro.melt:155:/ cond");
        /*cond*/ if (/*_#IS_A__L7*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    MELT_LOCATION("warmelt-moremacro.melt:156:/ quasiblock");


                    /*^cond*/
                    /*cond*/ if (
                        /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.CURIF__V19*/ meltfptr[18]),
                                                      (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[0])))
                    ) /*then*/
                        {
                            /*^cond.then*/
                            /*^getslot*/
                            {
                                melt_ptr_t slot=NULL, obj=NULL;
                                obj = (melt_ptr_t)(/*_.CURIF__V19*/ meltfptr[18]) /*=obj*/;
                                melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
                                /*_.XCURIF__V25*/ meltfptr[24] = slot;
                            };
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_.XCURIF__V25*/ meltfptr[24] =  /*reallynil*/ NULL ;;
                        }
                    ;

#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-moremacro.melt:158:/ cppif.then");
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
                        /*_#MELT_NEED_DBG__L8*/ meltfnum[3] =
                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                            ;;
                        MELT_LOCATION("warmelt-moremacro.melt:158:/ cond");
                        /*cond*/ if (/*_#MELT_NEED_DBG__L8*/ meltfnum[3]) /*then*/
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
                                    MELT_LOCATION("warmelt-moremacro.melt:158:/ apply");
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[8];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L9*/ meltfnum[8];
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 158;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_cstring =  "mexpand_gccif xcurif=";
                                        /*^apply.arg*/
                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.XCURIF__V25*/ meltfptr[24];
                                        /*^apply.arg*/
                                        argtab[5].meltbp_cstring =  " sloc=";
                                        /*^apply.arg*/
                                        argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[4]);
                                        /*^apply.arg*/
                                        argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V16*/ meltfptr[15];
                                        /*_.MELT_DEBUG_FUN__V27*/ meltfptr[26] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IF___V26*/ meltfptr[25] = /*_.MELT_DEBUG_FUN__V27*/ meltfptr[26];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-moremacro.melt:158:/ clear");
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
                            MELT_LOCATION("warmelt-moremacro.melt:158:/ locexp");
                            /*void*/(void)0;
                        }
                        ;
                        /*^quasiblock*/


                        /*epilog*/

                        /*^clear*/
                        /*clear*/ /*_#MELT_NEED_DBG__L8*/ meltfnum[3] = 0 ;
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
                    MELT_LOCATION("warmelt-moremacro.melt:159:/ compute");
                    /*_.CURIF__V19*/ meltfptr[18] = /*_.SETQ___V28*/ meltfptr[26] = /*_.XCURIF__V25*/ meltfptr[24];;
                    /*_.LET___V24*/ meltfptr[20] = /*_.SETQ___V28*/ meltfptr[26];;

                    MELT_LOCATION("warmelt-moremacro.melt:156:/ clear");
                    /*clear*/ /*_.XCURIF__V25*/ meltfptr[24] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.SETQ___V28*/ meltfptr[26] = 0 ;
                    /*_._IF___V23*/ meltfptr[21] = /*_.LET___V24*/ meltfptr[20];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:155:/ clear");
                    /*clear*/ /*_.LET___V24*/ meltfptr[20] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V23*/ meltfptr[21] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_STRING__L10*/ meltfnum[8] =
            (melt_magic_discr((melt_ptr_t)(/*_.CURIF__V19*/ meltfptr[18])) == MELTOBMAG_STRING);;
        MELT_LOCATION("warmelt-moremacro.melt:162:/ cond");
        /*cond*/ if (/*_#IS_STRING__L10*/ meltfnum[8]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-moremacro.melt:163:/ cppif.then");
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
                        /*_#MELT_NEED_DBG__L11*/ meltfnum[3] =
                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                            ;;
                        MELT_LOCATION("warmelt-moremacro.melt:163:/ cond");
                        /*cond*/ if (/*_#MELT_NEED_DBG__L11*/ meltfnum[3]) /*then*/
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
                                    MELT_LOCATION("warmelt-moremacro.melt:163:/ apply");
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[8];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L12*/ meltfnum[11];
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 163;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_cstring =  "mexpand_gccif string curif=";
                                        /*^apply.arg*/
                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CURIF__V19*/ meltfptr[18];
                                        /*^apply.arg*/
                                        argtab[5].meltbp_cstring =  " sloc=";
                                        /*^apply.arg*/
                                        argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[4]);
                                        /*^apply.arg*/
                                        argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V16*/ meltfptr[15];
                                        /*_.MELT_DEBUG_FUN__V31*/ meltfptr[26] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IF___V30*/ meltfptr[24] = /*_.MELT_DEBUG_FUN__V31*/ meltfptr[26];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-moremacro.melt:163:/ clear");
                                    /*clear*/ /*_#MELT_CALLCOUNT__L12*/ meltfnum[11] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.MELT_DEBUG_FUN__V31*/ meltfptr[26] = 0 ;
                                }
                                ;
                            }
                        else    /*^cond.else*/
                            {

                                /*_._IF___V30*/ meltfptr[24] =  /*reallynil*/ NULL ;;
                            }
                        ;

                        {
                            MELT_LOCATION("warmelt-moremacro.melt:163:/ locexp");
                            /*void*/(void)0;
                        }
                        ;
                        /*^quasiblock*/


                        /*epilog*/

                        /*^clear*/
                        /*clear*/ /*_#MELT_NEED_DBG__L11*/ meltfnum[3] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IF___V30*/ meltfptr[24] = 0 ;
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

                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-moremacro.melt:164:/ apply");
                    /*apply*/
                    {
                        /*_.FILTERGCCVERSION__V32*/ meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!FILTERGCCVERSION*/ meltfrout->tabval[5])), (melt_ptr_t)(/*_.CURIF__V19*/ meltfptr[18]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                    }
                    ;
                    /*^cond*/
                    /*cond*/ if (/*_.FILTERGCCVERSION__V32*/ meltfptr[20]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


#if MELT_HAVE_DEBUG
                                MELT_LOCATION("warmelt-moremacro.melt:165:/ cppif.then");
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
                                    /*_#MELT_NEED_DBG__L13*/ meltfnum[11] =
                                        /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                        (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                        0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                        ;;
                                    MELT_LOCATION("warmelt-moremacro.melt:165:/ cond");
                                    /*cond*/ if (/*_#MELT_NEED_DBG__L13*/ meltfnum[11]) /*then*/
                                        {
                                            /*^cond.then*/
                                            /*^block*/
                                            /*anyblock*/
                                            {

                                                /*_#MELT_CALLCOUNT__L14*/ meltfnum[3] =
                                                    /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                    meltcallcount  /* melt_callcount debugging */
#else
                                                    0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                    ;;

                                                MELT_CHECK_SIGNAL();
                                                ;
                                                MELT_LOCATION("warmelt-moremacro.melt:165:/ apply");
                                                /*apply*/
                                                {
                                                    union meltparam_un argtab[5];
                                                    memset(&argtab, 0, sizeof(argtab));
                                                    /*^apply.arg*/
                                                    argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L14*/ meltfnum[3];
                                                    /*^apply.arg*/
                                                    argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                    /*^apply.arg*/
                                                    argtab[2].meltbp_long = 165;
                                                    /*^apply.arg*/
                                                    argtab[3].meltbp_cstring =  "mexpand_gccif filtered curif=";
                                                    /*^apply.arg*/
                                                    argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CURIF__V19*/ meltfptr[18];
                                                    /*_.MELT_DEBUG_FUN__V35*/ meltfptr[34] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                }
                                                ;
                                                /*_._IF___V34*/ meltfptr[24] = /*_.MELT_DEBUG_FUN__V35*/ meltfptr[34];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-moremacro.melt:165:/ clear");
                                                /*clear*/ /*_#MELT_CALLCOUNT__L14*/ meltfnum[3] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_.MELT_DEBUG_FUN__V35*/ meltfptr[34] = 0 ;
                                            }
                                            ;
                                        }
                                    else    /*^cond.else*/
                                        {

                                            /*_._IF___V34*/ meltfptr[24] =  /*reallynil*/ NULL ;;
                                        }
                                    ;

                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:165:/ locexp");
                                        /*void*/(void)0;
                                    }
                                    ;
                                    /*^quasiblock*/


                                    /*epilog*/

                                    /*^clear*/
                                    /*clear*/ /*_#MELT_NEED_DBG__L13*/ meltfnum[11] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V34*/ meltfptr[24] = 0 ;
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
                                MELT_LOCATION("warmelt-moremacro.melt:166:/ quasiblock");



                                MELT_CHECK_SIGNAL();
                                ;
                                /*^apply*/
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
                                    /*_.EXPRESTLIST__V37*/ meltfptr[24] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_PAIRLIST_AS_LIST*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.RESTPAIR__V20*/ meltfptr[19]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                }
                                ;

#if MELT_HAVE_DEBUG
                                MELT_LOCATION("warmelt-moremacro.melt:168:/ cppif.then");
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
                                    /*_#MELT_NEED_DBG__L15*/ meltfnum[3] =
                                        /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                        (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                        0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                        ;;
                                    MELT_LOCATION("warmelt-moremacro.melt:168:/ cond");
                                    /*cond*/ if (/*_#MELT_NEED_DBG__L15*/ meltfnum[3]) /*then*/
                                        {
                                            /*^cond.then*/
                                            /*^block*/
                                            /*anyblock*/
                                            {

                                                /*_#MELT_CALLCOUNT__L16*/ meltfnum[11] =
                                                    /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                    meltcallcount  /* melt_callcount debugging */
#else
                                                    0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                    ;;

                                                MELT_CHECK_SIGNAL();
                                                ;
                                                MELT_LOCATION("warmelt-moremacro.melt:168:/ apply");
                                                /*apply*/
                                                {
                                                    union meltparam_un argtab[5];
                                                    memset(&argtab, 0, sizeof(argtab));
                                                    /*^apply.arg*/
                                                    argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L16*/ meltfnum[11];
                                                    /*^apply.arg*/
                                                    argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                    /*^apply.arg*/
                                                    argtab[2].meltbp_long = 168;
                                                    /*^apply.arg*/
                                                    argtab[3].meltbp_cstring =  "mexpand_gccif stringy exprestlist=";
                                                    /*^apply.arg*/
                                                    argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.EXPRESTLIST__V37*/ meltfptr[24];
                                                    /*_.MELT_DEBUG_FUN__V39*/ meltfptr[38] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                }
                                                ;
                                                /*_._IF___V38*/ meltfptr[37] = /*_.MELT_DEBUG_FUN__V39*/ meltfptr[38];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-moremacro.melt:168:/ clear");
                                                /*clear*/ /*_#MELT_CALLCOUNT__L16*/ meltfnum[11] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_.MELT_DEBUG_FUN__V39*/ meltfptr[38] = 0 ;
                                            }
                                            ;
                                        }
                                    else    /*^cond.else*/
                                        {

                                            /*_._IF___V38*/ meltfptr[37] =  /*reallynil*/ NULL ;;
                                        }
                                    ;

                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:168:/ locexp");
                                        /*void*/(void)0;
                                    }
                                    ;
                                    /*^quasiblock*/


                                    /*epilog*/

                                    /*^clear*/
                                    /*clear*/ /*_#MELT_NEED_DBG__L15*/ meltfnum[3] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V38*/ meltfptr[37] = 0 ;
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
                                MELT_LOCATION("warmelt-moremacro.melt:169:/ quasiblock");


                                /*_.EXPFIRST__V41*/ meltfptr[37] =
                                    (melt_pair_head (melt_list_first((melt_ptr_t)(/*_.EXPRESTLIST__V37*/ meltfptr[24]))));;
                                /*^compute*/
                                /*_.LIST_POP_FIRST__V42*/ meltfptr[41] =
                                    (meltgc_popfirst_list((melt_ptr_t)(/*_.EXPRESTLIST__V37*/ meltfptr[24])));;
                                MELT_LOCATION("warmelt-moremacro.melt:170:/ quasiblock");


                                /*_.EXPTAIL__V43*/ meltfptr[42] = /*_.EXPRESTLIST__V37*/ meltfptr[24];;

#if MELT_HAVE_DEBUG
                                MELT_LOCATION("warmelt-moremacro.melt:172:/ cppif.then");
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
                                    /*_#MELT_NEED_DBG__L17*/ meltfnum[11] =
                                        /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                        (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                        0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                        ;;
                                    MELT_LOCATION("warmelt-moremacro.melt:172:/ cond");
                                    /*cond*/ if (/*_#MELT_NEED_DBG__L17*/ meltfnum[11]) /*then*/
                                        {
                                            /*^cond.then*/
                                            /*^block*/
                                            /*anyblock*/
                                            {

                                                /*_#MELT_CALLCOUNT__L18*/ meltfnum[3] =
                                                    /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                    meltcallcount  /* melt_callcount debugging */
#else
                                                    0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                    ;;

                                                MELT_CHECK_SIGNAL();
                                                ;
                                                MELT_LOCATION("warmelt-moremacro.melt:172:/ apply");
                                                /*apply*/
                                                {
                                                    union meltparam_un argtab[7];
                                                    memset(&argtab, 0, sizeof(argtab));
                                                    /*^apply.arg*/
                                                    argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L18*/ meltfnum[3];
                                                    /*^apply.arg*/
                                                    argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                    /*^apply.arg*/
                                                    argtab[2].meltbp_long = 172;
                                                    /*^apply.arg*/
                                                    argtab[3].meltbp_cstring =  "mexpand_gccif stringy return expfirst=";
                                                    /*^apply.arg*/
                                                    argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.EXPFIRST__V41*/ meltfptr[37];
                                                    /*^apply.arg*/
                                                    argtab[5].meltbp_cstring =  " exptail=";
                                                    /*^apply.arg*/
                                                    argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.EXPTAIL__V43*/ meltfptr[42];
                                                    /*_.MELT_DEBUG_FUN__V45*/ meltfptr[44] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                }
                                                ;
                                                /*_._IF___V44*/ meltfptr[43] = /*_.MELT_DEBUG_FUN__V45*/ meltfptr[44];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-moremacro.melt:172:/ clear");
                                                /*clear*/ /*_#MELT_CALLCOUNT__L18*/ meltfnum[3] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_.MELT_DEBUG_FUN__V45*/ meltfptr[44] = 0 ;
                                            }
                                            ;
                                        }
                                    else    /*^cond.else*/
                                        {

                                            /*_._IF___V44*/ meltfptr[43] =  /*reallynil*/ NULL ;;
                                        }
                                    ;

                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:172:/ locexp");
                                        /*void*/(void)0;
                                    }
                                    ;
                                    /*^quasiblock*/


                                    /*epilog*/

                                    /*^clear*/
                                    /*clear*/ /*_#MELT_NEED_DBG__L17*/ meltfnum[11] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V44*/ meltfptr[43] = 0 ;
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
                                MELT_LOCATION("warmelt-moremacro.melt:173:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] = /*_.EXPFIRST__V41*/ meltfptr[37];;
                                MELT_LOCATION("warmelt-moremacro.melt:173:/ putxtraresult");
                                if (!meltxrestab_ || !meltxresdescr_) goto meltlabend_rout;
                                if (meltxresdescr_[0] != MELTBPAR_PTR) goto meltlabend_rout;
                                if (meltxrestab_[0].meltbp_aptr) *(meltxrestab_[0].meltbp_aptr) = (melt_ptr_t) (/*_.EXPTAIL__V43*/ meltfptr[42]);
                                ;
                                /*^finalreturn*/
                                ;
                                /*finalret*/ goto meltlabend_rout ;
                                /*_.LET___V40*/ meltfptr[38] = /*_.RETURN___V46*/ meltfptr[44];;

                                MELT_LOCATION("warmelt-moremacro.melt:169:/ clear");
                                /*clear*/ /*_.EXPFIRST__V41*/ meltfptr[37] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.LIST_POP_FIRST__V42*/ meltfptr[41] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.EXPTAIL__V43*/ meltfptr[42] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.RETURN___V46*/ meltfptr[44] = 0 ;
                                /*_.LET___V36*/ meltfptr[34] = /*_.LET___V40*/ meltfptr[38];;

                                MELT_LOCATION("warmelt-moremacro.melt:166:/ clear");
                                /*clear*/ /*_.EXPRESTLIST__V37*/ meltfptr[24] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.LET___V40*/ meltfptr[38] = 0 ;
                                MELT_LOCATION("warmelt-moremacro.melt:164:/ quasiblock");


                                /*_.PROGN___V47*/ meltfptr[43] = /*_.LET___V36*/ meltfptr[34];;
                                /*^compute*/
                                /*_._IFELSE___V33*/ meltfptr[26] = /*_.PROGN___V47*/ meltfptr[43];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:164:/ clear");
                                /*clear*/ /*_.LET___V36*/ meltfptr[34] = 0 ;
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


#if MELT_HAVE_DEBUG
                                MELT_LOCATION("warmelt-moremacro.melt:176:/ cppif.then");
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
                                    /*_#MELT_NEED_DBG__L19*/ meltfnum[3] =
                                        /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                        (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                        0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                        ;;
                                    MELT_LOCATION("warmelt-moremacro.melt:176:/ cond");
                                    /*cond*/ if (/*_#MELT_NEED_DBG__L19*/ meltfnum[3]) /*then*/
                                        {
                                            /*^cond.then*/
                                            /*^block*/
                                            /*anyblock*/
                                            {

                                                /*_#MELT_CALLCOUNT__L20*/ meltfnum[11] =
                                                    /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                    meltcallcount  /* melt_callcount debugging */
#else
                                                    0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                    ;;

                                                MELT_CHECK_SIGNAL();
                                                ;
                                                MELT_LOCATION("warmelt-moremacro.melt:176:/ apply");
                                                /*apply*/
                                                {
                                                    union meltparam_un argtab[8];
                                                    memset(&argtab, 0, sizeof(argtab));
                                                    /*^apply.arg*/
                                                    argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L20*/ meltfnum[11];
                                                    /*^apply.arg*/
                                                    argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                    /*^apply.arg*/
                                                    argtab[2].meltbp_long = 176;
                                                    /*^apply.arg*/
                                                    argtab[3].meltbp_cstring =  "mexpand_gccif gcc version mismatched curif=";
                                                    /*^apply.arg*/
                                                    argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CURIF__V19*/ meltfptr[18];
                                                    /*^apply.arg*/
                                                    argtab[5].meltbp_cstring =  " sloc=";
                                                    /*^apply.arg*/
                                                    argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[4]);
                                                    /*^apply.arg*/
                                                    argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V16*/ meltfptr[15];
                                                    /*_.MELT_DEBUG_FUN__V49*/ meltfptr[41] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                }
                                                ;
                                                /*_._IF___V48*/ meltfptr[37] = /*_.MELT_DEBUG_FUN__V49*/ meltfptr[41];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-moremacro.melt:176:/ clear");
                                                /*clear*/ /*_#MELT_CALLCOUNT__L20*/ meltfnum[11] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_.MELT_DEBUG_FUN__V49*/ meltfptr[41] = 0 ;
                                            }
                                            ;
                                        }
                                    else    /*^cond.else*/
                                        {

                                            /*_._IF___V48*/ meltfptr[37] =  /*reallynil*/ NULL ;;
                                        }
                                    ;

                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:176:/ locexp");
                                        /*void*/(void)0;
                                    }
                                    ;
                                    /*^quasiblock*/


                                    /*epilog*/

                                    /*^clear*/
                                    /*clear*/ /*_#MELT_NEED_DBG__L19*/ meltfnum[3] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V48*/ meltfptr[37] = 0 ;
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
                                MELT_LOCATION("warmelt-moremacro.melt:177:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                {
                                    MELT_LOCATION("warmelt-moremacro.melt:177:/ locexp");
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
                                MELT_LOCATION("warmelt-moremacro.melt:175:/ quasiblock");


                                /*_.PROGN___V51*/ meltfptr[44] = /*_.RETURN___V50*/ meltfptr[42];;
                                /*^compute*/
                                /*_._IFELSE___V33*/ meltfptr[26] = /*_.PROGN___V51*/ meltfptr[44];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:164:/ clear");
                                /*clear*/ /*_.RETURN___V50*/ meltfptr[42] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V51*/ meltfptr[44] = 0 ;
                            }
                            ;
                        }
                    ;
                    MELT_LOCATION("warmelt-moremacro.melt:162:/ quasiblock");


                    /*_.PROGN___V52*/ meltfptr[24] = /*_._IFELSE___V33*/ meltfptr[26];;
                    /*^compute*/
                    /*_._IFELSE___V29*/ meltfptr[25] = /*_.PROGN___V52*/ meltfptr[24];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:162:/ clear");
                    /*clear*/ /*_.FILTERGCCVERSION__V32*/ meltfptr[20] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V33*/ meltfptr[26] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_.PROGN___V52*/ meltfptr[24] = 0 ;
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
                    /*_#IS_LIST__L21*/ meltfnum[11] =
                        (melt_magic_discr((melt_ptr_t)(/*_.CURIF__V19*/ meltfptr[18])) == MELTOBMAG_LIST);;
                    MELT_LOCATION("warmelt-moremacro.melt:178:/ cond");
                    /*cond*/ if (/*_#IS_LIST__L21*/ meltfnum[11]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {


#if MELT_HAVE_DEBUG
                                MELT_LOCATION("warmelt-moremacro.melt:179:/ cppif.then");
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
                                    /*_#MELT_NEED_DBG__L22*/ meltfnum[3] =
                                        /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                        (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                        0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                        ;;
                                    MELT_LOCATION("warmelt-moremacro.melt:179:/ cond");
                                    /*cond*/ if (/*_#MELT_NEED_DBG__L22*/ meltfnum[3]) /*then*/
                                        {
                                            /*^cond.then*/
                                            /*^block*/
                                            /*anyblock*/
                                            {

                                                /*_#MELT_CALLCOUNT__L23*/ meltfnum[22] =
                                                    /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                    meltcallcount  /* melt_callcount debugging */
#else
                                                    0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                    ;;

                                                MELT_CHECK_SIGNAL();
                                                ;
                                                MELT_LOCATION("warmelt-moremacro.melt:179:/ apply");
                                                /*apply*/
                                                {
                                                    union meltparam_un argtab[8];
                                                    memset(&argtab, 0, sizeof(argtab));
                                                    /*^apply.arg*/
                                                    argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L23*/ meltfnum[22];
                                                    /*^apply.arg*/
                                                    argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                    /*^apply.arg*/
                                                    argtab[2].meltbp_long = 179;
                                                    /*^apply.arg*/
                                                    argtab[3].meltbp_cstring =  "mexpand_gccif list curif=";
                                                    /*^apply.arg*/
                                                    argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CURIF__V19*/ meltfptr[18];
                                                    /*^apply.arg*/
                                                    argtab[5].meltbp_cstring =  " sloc=";
                                                    /*^apply.arg*/
                                                    argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[4]);
                                                    /*^apply.arg*/
                                                    argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V16*/ meltfptr[15];
                                                    /*_.MELT_DEBUG_FUN__V55*/ meltfptr[43] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                }
                                                ;
                                                /*_._IF___V54*/ meltfptr[34] = /*_.MELT_DEBUG_FUN__V55*/ meltfptr[43];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-moremacro.melt:179:/ clear");
                                                /*clear*/ /*_#MELT_CALLCOUNT__L23*/ meltfnum[22] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_.MELT_DEBUG_FUN__V55*/ meltfptr[43] = 0 ;
                                            }
                                            ;
                                        }
                                    else    /*^cond.else*/
                                        {

                                            /*_._IF___V54*/ meltfptr[34] =  /*reallynil*/ NULL ;;
                                        }
                                    ;

                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:179:/ locexp");
                                        /*void*/(void)0;
                                    }
                                    ;
                                    /*^quasiblock*/


                                    /*epilog*/

                                    /*^clear*/
                                    /*clear*/ /*_#MELT_NEED_DBG__L22*/ meltfnum[3] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V54*/ meltfptr[34] = 0 ;
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
                                MELT_LOCATION("warmelt-moremacro.melt:180:/ quasiblock");


                                /*_.OK__V57*/ meltfptr[37] = (/*nil*/NULL);;
                                /*citerblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                {
                                    /* start foreach_pair_component_in_list meltcit1__EACHLIST */
                                    for (/*_.CURPAIR__V58*/ meltfptr[42] = melt_list_first( (melt_ptr_t)/*_.CURIF__V19*/ meltfptr[18]);
                                                            melt_magic_discr((melt_ptr_t) /*_.CURPAIR__V58*/ meltfptr[42]) == MELTOBMAG_PAIR;
                                                            /*_.CURPAIR__V58*/ meltfptr[42] = melt_pair_tail((melt_ptr_t) /*_.CURPAIR__V58*/ meltfptr[42]))
                                        {
                                            /*_.CURSTR__V59*/ meltfptr[44] = melt_pair_head((melt_ptr_t) /*_.CURPAIR__V58*/ meltfptr[42]);



                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*_#IS_STRING__L24*/ meltfnum[22] =
                                                (melt_magic_discr((melt_ptr_t)(/*_.CURSTR__V59*/ meltfptr[44])) == MELTOBMAG_STRING);;
                                            /*^compute*/
                                            /*_#NOT__L25*/ meltfnum[3] =
                                                (!(/*_#IS_STRING__L24*/ meltfnum[22]));;
                                            MELT_LOCATION("warmelt-moremacro.melt:185:/ cond");
                                            /*cond*/ if (/*_#NOT__L25*/ meltfnum[3]) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^block*/
                                                    /*anyblock*/
                                                    {


                                                        {
                                                            MELT_LOCATION("warmelt-moremacro.melt:186:/ locexp");
                                                            /* error_plain */ melt_error_str((melt_ptr_t)(/*_.SLOC__V16*/ meltfptr[15]), ( "GCCIF condition not a list of strings"), (melt_ptr_t)0);
                                                        }
                                                        ;
                                                        /*epilog*/
                                                    }
                                                    ;
                                                } /*noelse*/
                                            ;

                                            MELT_CHECK_SIGNAL();
                                            ;

                                            MELT_CHECK_SIGNAL();
                                            ;
                                            MELT_LOCATION("warmelt-moremacro.melt:187:/ apply");
                                            /*apply*/
                                            {
                                                /*_.FILTERGCCVERSION__V60*/ meltfptr[20] =  melt_apply ((meltclosure_ptr_t)((/*!FILTERGCCVERSION*/ meltfrout->tabval[5])), (melt_ptr_t)(/*_.CURSTR__V59*/ meltfptr[44]), (""), (union meltparam_un*)0, "", (union meltparam_un*)0);
                                            }
                                            ;
                                            /*^cond*/
                                            /*cond*/ if (/*_.FILTERGCCVERSION__V60*/ meltfptr[20]) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^block*/
                                                    /*anyblock*/
                                                    {

                                                        MELT_LOCATION("warmelt-moremacro.melt:188:/ compute");
                                                        /*_.OK__V57*/ meltfptr[37] = /*_.SETQ___V62*/ meltfptr[24] = (/*!konst_7_TRUE*/ meltfrout->tabval[7]);;
                                                        /*_._IF___V61*/ meltfptr[26] = /*_.SETQ___V62*/ meltfptr[24];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-moremacro.melt:187:/ clear");
                                                        /*clear*/ /*_.SETQ___V62*/ meltfptr[24] = 0 ;
                                                    }
                                                    ;
                                                }
                                            else    /*^cond.else*/
                                                {

                                                    /*_._IF___V61*/ meltfptr[26] =  /*reallynil*/ NULL ;;
                                                }
                                            ;
                                        } /* end foreach_pair_component_in_list meltcit1__EACHLIST */
                                    /*_.CURPAIR__V58*/ meltfptr[42] = NULL;
                                    /*_.CURSTR__V59*/ meltfptr[44] = NULL;


                                    /*citerepilog*/

                                    MELT_LOCATION("warmelt-moremacro.melt:182:/ clear");
                                    /*clear*/ /*_.CURPAIR__V58*/ meltfptr[42] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.CURSTR__V59*/ meltfptr[44] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_#IS_STRING__L24*/ meltfnum[22] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_#NOT__L25*/ meltfnum[3] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.FILTERGCCVERSION__V60*/ meltfptr[20] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V61*/ meltfptr[26] = 0 ;
                                } /*endciterblock FOREACH_PAIR_COMPONENT_IN_LIST*/
                                ;

#if MELT_HAVE_DEBUG
                                MELT_LOCATION("warmelt-moremacro.melt:190:/ cppif.then");
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
                                    /*_#MELT_NEED_DBG__L26*/ meltfnum[25] =
                                        /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                        (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                        0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                        ;;
                                    MELT_LOCATION("warmelt-moremacro.melt:190:/ cond");
                                    /*cond*/ if (/*_#MELT_NEED_DBG__L26*/ meltfnum[25]) /*then*/
                                        {
                                            /*^cond.then*/
                                            /*^block*/
                                            /*anyblock*/
                                            {

                                                /*_#MELT_CALLCOUNT__L27*/ meltfnum[26] =
                                                    /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                    meltcallcount  /* melt_callcount debugging */
#else
                                                    0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                    ;;

                                                MELT_CHECK_SIGNAL();
                                                ;
                                                MELT_LOCATION("warmelt-moremacro.melt:190:/ apply");
                                                /*apply*/
                                                {
                                                    union meltparam_un argtab[8];
                                                    memset(&argtab, 0, sizeof(argtab));
                                                    /*^apply.arg*/
                                                    argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L27*/ meltfnum[26];
                                                    /*^apply.arg*/
                                                    argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                    /*^apply.arg*/
                                                    argtab[2].meltbp_long = 190;
                                                    /*^apply.arg*/
                                                    argtab[3].meltbp_cstring =  "mexpand_gccif ok=";
                                                    /*^apply.arg*/
                                                    argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.OK__V57*/ meltfptr[37];
                                                    /*^apply.arg*/
                                                    argtab[5].meltbp_cstring =  " sloc=";
                                                    /*^apply.arg*/
                                                    argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[4]);
                                                    /*^apply.arg*/
                                                    argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V16*/ meltfptr[15];
                                                    /*_.MELT_DEBUG_FUN__V64*/ meltfptr[34] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                }
                                                ;
                                                /*_._IF___V63*/ meltfptr[43] = /*_.MELT_DEBUG_FUN__V64*/ meltfptr[34];;
                                                /*epilog*/

                                                MELT_LOCATION("warmelt-moremacro.melt:190:/ clear");
                                                /*clear*/ /*_#MELT_CALLCOUNT__L27*/ meltfnum[26] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_.MELT_DEBUG_FUN__V64*/ meltfptr[34] = 0 ;
                                            }
                                            ;
                                        }
                                    else    /*^cond.else*/
                                        {

                                            /*_._IF___V63*/ meltfptr[43] =  /*reallynil*/ NULL ;;
                                        }
                                    ;

                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:190:/ locexp");
                                        /*void*/(void)0;
                                    }
                                    ;
                                    /*^quasiblock*/


                                    /*epilog*/

                                    /*^clear*/
                                    /*clear*/ /*_#MELT_NEED_DBG__L26*/ meltfnum[25] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_._IF___V63*/ meltfptr[43] = 0 ;
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
                                MELT_LOCATION("warmelt-moremacro.melt:191:/ cond");
                                /*cond*/ if (/*_.OK__V57*/ meltfptr[37]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {

                                            MELT_LOCATION("warmelt-moremacro.melt:192:/ quasiblock");



                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*^apply*/
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
                                                /*_.EXPRESTLIST__V67*/ meltfptr[43] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_PAIRLIST_AS_LIST*/ meltfrout->tabval[6])), (melt_ptr_t)(/*_.RESTPAIR__V20*/ meltfptr[19]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                            }
                                            ;

#if MELT_HAVE_DEBUG
                                            MELT_LOCATION("warmelt-moremacro.melt:194:/ cppif.then");
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
                                                MELT_LOCATION("warmelt-moremacro.melt:194:/ cond");
                                                /*cond*/ if (/*_#MELT_NEED_DBG__L28*/ meltfnum[26]) /*then*/
                                                    {
                                                        /*^cond.then*/
                                                        /*^block*/
                                                        /*anyblock*/
                                                        {

                                                            /*_#MELT_CALLCOUNT__L29*/ meltfnum[25] =
                                                                /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                                meltcallcount  /* melt_callcount debugging */
#else
                                                                0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                                ;;

                                                            MELT_CHECK_SIGNAL();
                                                            ;
                                                            MELT_LOCATION("warmelt-moremacro.melt:194:/ apply");
                                                            /*apply*/
                                                            {
                                                                union meltparam_un argtab[8];
                                                                memset(&argtab, 0, sizeof(argtab));
                                                                /*^apply.arg*/
                                                                argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L29*/ meltfnum[25];
                                                                /*^apply.arg*/
                                                                argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                /*^apply.arg*/
                                                                argtab[2].meltbp_long = 194;
                                                                /*^apply.arg*/
                                                                argtab[3].meltbp_cstring =  "mexpand_gccif multicond exprestlist=";
                                                                /*^apply.arg*/
                                                                argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.EXPRESTLIST__V67*/ meltfptr[43];
                                                                /*^apply.arg*/
                                                                argtab[5].meltbp_cstring =  " sloc=";
                                                                /*^apply.arg*/
                                                                argtab[6].meltbp_aptr = (melt_ptr_t*) &(/*!DEBUG_LESS*/ meltfrout->tabval[4]);
                                                                /*^apply.arg*/
                                                                argtab[7].meltbp_aptr = (melt_ptr_t*) &/*_.SLOC__V16*/ meltfptr[15];
                                                                /*_.MELT_DEBUG_FUN__V69*/ meltfptr[68] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                            }
                                                            ;
                                                            /*_._IF___V68*/ meltfptr[67] = /*_.MELT_DEBUG_FUN__V69*/ meltfptr[68];;
                                                            /*epilog*/

                                                            MELT_LOCATION("warmelt-moremacro.melt:194:/ clear");
                                                            /*clear*/ /*_#MELT_CALLCOUNT__L29*/ meltfnum[25] = 0 ;
                                                            /*^clear*/
                                                            /*clear*/ /*_.MELT_DEBUG_FUN__V69*/ meltfptr[68] = 0 ;
                                                        }
                                                        ;
                                                    }
                                                else    /*^cond.else*/
                                                    {

                                                        /*_._IF___V68*/ meltfptr[67] =  /*reallynil*/ NULL ;;
                                                    }
                                                ;

                                                {
                                                    MELT_LOCATION("warmelt-moremacro.melt:194:/ locexp");
                                                    /*void*/(void)0;
                                                }
                                                ;
                                                /*^quasiblock*/


                                                /*epilog*/

                                                /*^clear*/
                                                /*clear*/ /*_#MELT_NEED_DBG__L28*/ meltfnum[26] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_._IF___V68*/ meltfptr[67] = 0 ;
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
                                            MELT_LOCATION("warmelt-moremacro.melt:196:/ quasiblock");


                                            /*_.EXPFIRST__V71*/ meltfptr[67] =
                                                (melt_pair_head (melt_list_first((melt_ptr_t)(/*_.EXPRESTLIST__V67*/ meltfptr[43]))));;
                                            /*^compute*/
                                            /*_.LIST_POP_FIRST__V72*/ meltfptr[71] =
                                                (meltgc_popfirst_list((melt_ptr_t)(/*_.EXPRESTLIST__V67*/ meltfptr[43])));;
                                            MELT_LOCATION("warmelt-moremacro.melt:197:/ quasiblock");


                                            /*_.EXPTAIL__V73*/ meltfptr[72] = /*_.EXPRESTLIST__V67*/ meltfptr[43];;

#if MELT_HAVE_DEBUG
                                            MELT_LOCATION("warmelt-moremacro.melt:200:/ cppif.then");
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
                                                /*_#MELT_NEED_DBG__L30*/ meltfnum[25] =
                                                    /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                                    (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                                    0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                                    ;;
                                                MELT_LOCATION("warmelt-moremacro.melt:200:/ cond");
                                                /*cond*/ if (/*_#MELT_NEED_DBG__L30*/ meltfnum[25]) /*then*/
                                                    {
                                                        /*^cond.then*/
                                                        /*^block*/
                                                        /*anyblock*/
                                                        {

                                                            /*_#MELT_CALLCOUNT__L31*/ meltfnum[26] =
                                                                /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                                meltcallcount  /* melt_callcount debugging */
#else
                                                                0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                                ;;

                                                            MELT_CHECK_SIGNAL();
                                                            ;
                                                            MELT_LOCATION("warmelt-moremacro.melt:200:/ apply");
                                                            /*apply*/
                                                            {
                                                                union meltparam_un argtab[7];
                                                                memset(&argtab, 0, sizeof(argtab));
                                                                /*^apply.arg*/
                                                                argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L31*/ meltfnum[26];
                                                                /*^apply.arg*/
                                                                argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                /*^apply.arg*/
                                                                argtab[2].meltbp_long = 200;
                                                                /*^apply.arg*/
                                                                argtab[3].meltbp_cstring =  "mexpand_gccif multicond  return expfirst=";
                                                                /*^apply.arg*/
                                                                argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.EXPFIRST__V71*/ meltfptr[67];
                                                                /*^apply.arg*/
                                                                argtab[5].meltbp_cstring =  "\n.. exptail=";
                                                                /*^apply.arg*/
                                                                argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.EXPTAIL__V73*/ meltfptr[72];
                                                                /*_.MELT_DEBUG_FUN__V75*/ meltfptr[74] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                            }
                                                            ;
                                                            /*_._IF___V74*/ meltfptr[73] = /*_.MELT_DEBUG_FUN__V75*/ meltfptr[74];;
                                                            /*epilog*/

                                                            MELT_LOCATION("warmelt-moremacro.melt:200:/ clear");
                                                            /*clear*/ /*_#MELT_CALLCOUNT__L31*/ meltfnum[26] = 0 ;
                                                            /*^clear*/
                                                            /*clear*/ /*_.MELT_DEBUG_FUN__V75*/ meltfptr[74] = 0 ;
                                                        }
                                                        ;
                                                    }
                                                else    /*^cond.else*/
                                                    {

                                                        /*_._IF___V74*/ meltfptr[73] =  /*reallynil*/ NULL ;;
                                                    }
                                                ;

                                                {
                                                    MELT_LOCATION("warmelt-moremacro.melt:200:/ locexp");
                                                    /*void*/(void)0;
                                                }
                                                ;
                                                /*^quasiblock*/


                                                /*epilog*/

                                                /*^clear*/
                                                /*clear*/ /*_#MELT_NEED_DBG__L30*/ meltfnum[25] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_._IF___V74*/ meltfptr[73] = 0 ;
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
                                                MELT_LOCATION("warmelt-moremacro.melt:202:/ locexp");

#if MELT_HAVE_DEBUG
                                                if (melt_need_debug (0))
                                                    melt_dbgshortbacktrace(( "mexpand_gccif multicond"), (8));
#endif
                                                ;
                                            }
                                            ;

                                            MELT_CHECK_SIGNAL();
                                            ;
                                            MELT_LOCATION("warmelt-moremacro.melt:203:/ quasiblock");


                                            /*_._RETVAL___V1*/ meltfptr[0] = /*_.EXPFIRST__V71*/ meltfptr[67];;
                                            MELT_LOCATION("warmelt-moremacro.melt:203:/ putxtraresult");
                                            if (!meltxrestab_ || !meltxresdescr_) goto meltlabend_rout;
                                            if (meltxresdescr_[0] != MELTBPAR_PTR) goto meltlabend_rout;
                                            if (meltxrestab_[0].meltbp_aptr) *(meltxrestab_[0].meltbp_aptr) = (melt_ptr_t) (/*_.EXPTAIL__V73*/ meltfptr[72]);
                                            ;
                                            /*^finalreturn*/
                                            ;
                                            /*finalret*/ goto meltlabend_rout ;
                                            /*_.LET___V70*/ meltfptr[68] = /*_.RETURN___V76*/ meltfptr[74];;

                                            MELT_LOCATION("warmelt-moremacro.melt:196:/ clear");
                                            /*clear*/ /*_.EXPFIRST__V71*/ meltfptr[67] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.LIST_POP_FIRST__V72*/ meltfptr[71] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.EXPTAIL__V73*/ meltfptr[72] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.RETURN___V76*/ meltfptr[74] = 0 ;
                                            /*_.LET___V66*/ meltfptr[34] = /*_.LET___V70*/ meltfptr[68];;

                                            MELT_LOCATION("warmelt-moremacro.melt:192:/ clear");
                                            /*clear*/ /*_.EXPRESTLIST__V67*/ meltfptr[43] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.LET___V70*/ meltfptr[68] = 0 ;
                                            /*_._IFELSE___V65*/ meltfptr[24] = /*_.LET___V66*/ meltfptr[34];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-moremacro.melt:191:/ clear");
                                            /*clear*/ /*_.LET___V66*/ meltfptr[34] = 0 ;
                                        }
                                        ;
                                    }
                                else    /*^cond.else*/
                                    {

                                        /*^block*/
                                        /*anyblock*/
                                        {


#if MELT_HAVE_DEBUG
                                            MELT_LOCATION("warmelt-moremacro.melt:206:/ cppif.then");
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
                                                /*_#MELT_NEED_DBG__L32*/ meltfnum[26] =
                                                    /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                                    (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                                    0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                                    ;;
                                                MELT_LOCATION("warmelt-moremacro.melt:206:/ cond");
                                                /*cond*/ if (/*_#MELT_NEED_DBG__L32*/ meltfnum[26]) /*then*/
                                                    {
                                                        /*^cond.then*/
                                                        /*^block*/
                                                        /*anyblock*/
                                                        {

                                                            /*_#MELT_CALLCOUNT__L33*/ meltfnum[25] =
                                                                /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                                meltcallcount  /* melt_callcount debugging */
#else
                                                                0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                                ;;

                                                            MELT_CHECK_SIGNAL();
                                                            ;
                                                            MELT_LOCATION("warmelt-moremacro.melt:206:/ apply");
                                                            /*apply*/
                                                            {
                                                                union meltparam_un argtab[5];
                                                                memset(&argtab, 0, sizeof(argtab));
                                                                /*^apply.arg*/
                                                                argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L33*/ meltfnum[25];
                                                                /*^apply.arg*/
                                                                argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                /*^apply.arg*/
                                                                argtab[2].meltbp_long = 206;
                                                                /*^apply.arg*/
                                                                argtab[3].meltbp_cstring =  "mexpand_gccif sexpr gcc version multicond mismatched";
                                                                /*^apply.arg*/
                                                                argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                                                                /*_.MELT_DEBUG_FUN__V78*/ meltfptr[67] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[3])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                            }
                                                            ;
                                                            /*_._IF___V77*/ meltfptr[73] = /*_.MELT_DEBUG_FUN__V78*/ meltfptr[67];;
                                                            /*epilog*/

                                                            MELT_LOCATION("warmelt-moremacro.melt:206:/ clear");
                                                            /*clear*/ /*_#MELT_CALLCOUNT__L33*/ meltfnum[25] = 0 ;
                                                            /*^clear*/
                                                            /*clear*/ /*_.MELT_DEBUG_FUN__V78*/ meltfptr[67] = 0 ;
                                                        }
                                                        ;
                                                    }
                                                else    /*^cond.else*/
                                                    {

                                                        /*_._IF___V77*/ meltfptr[73] =  /*reallynil*/ NULL ;;
                                                    }
                                                ;

                                                {
                                                    MELT_LOCATION("warmelt-moremacro.melt:206:/ locexp");
                                                    /*void*/(void)0;
                                                }
                                                ;
                                                /*^quasiblock*/


                                                /*epilog*/

                                                /*^clear*/
                                                /*clear*/ /*_#MELT_NEED_DBG__L32*/ meltfnum[26] = 0 ;
                                                /*^clear*/
                                                /*clear*/ /*_._IF___V77*/ meltfptr[73] = 0 ;
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
                                            MELT_LOCATION("warmelt-moremacro.melt:207:/ quasiblock");


                                            /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                            {
                                                MELT_LOCATION("warmelt-moremacro.melt:207:/ locexp");
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
                                            MELT_LOCATION("warmelt-moremacro.melt:205:/ quasiblock");


                                            /*_.PROGN___V80*/ meltfptr[72] = /*_.RETURN___V79*/ meltfptr[71];;
                                            /*^compute*/
                                            /*_._IFELSE___V65*/ meltfptr[24] = /*_.PROGN___V80*/ meltfptr[72];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-moremacro.melt:191:/ clear");
                                            /*clear*/ /*_.RETURN___V79*/ meltfptr[71] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_.PROGN___V80*/ meltfptr[72] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_.LET___V56*/ meltfptr[41] = /*_._IFELSE___V65*/ meltfptr[24];;

                                MELT_LOCATION("warmelt-moremacro.melt:180:/ clear");
                                /*clear*/ /*_.OK__V57*/ meltfptr[37] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V65*/ meltfptr[24] = 0 ;
                                MELT_LOCATION("warmelt-moremacro.melt:178:/ quasiblock");


                                /*_.PROGN___V81*/ meltfptr[74] = /*_.LET___V56*/ meltfptr[41];;
                                /*^compute*/
                                /*_._IFELSE___V53*/ meltfptr[38] = /*_.PROGN___V81*/ meltfptr[74];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:178:/ clear");
                                /*clear*/ /*_.LET___V56*/ meltfptr[41] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V81*/ meltfptr[74] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*^block*/
                            /*anyblock*/
                            {


                                {
                                    MELT_LOCATION("warmelt-moremacro.melt:210:/ locexp");
                                    /* error_plain */ melt_error_str((melt_ptr_t)(/*_.SLOC__V16*/ meltfptr[15]), ( "GCCIF bad condition, should be a string or a list of strings"), (melt_ptr_t)0);
                                }
                                ;
                                MELT_LOCATION("warmelt-moremacro.melt:211:/ quasiblock");


                                /*_._RETVAL___V1*/ meltfptr[0] =  /*reallynil*/ NULL ;;

                                {
                                    MELT_LOCATION("warmelt-moremacro.melt:211:/ locexp");
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
                                MELT_LOCATION("warmelt-moremacro.melt:209:/ quasiblock");


                                /*_.PROGN___V83*/ meltfptr[68] = /*_.RETURN___V82*/ meltfptr[43];;
                                /*^compute*/
                                /*_._IFELSE___V53*/ meltfptr[38] = /*_.PROGN___V83*/ meltfptr[68];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:178:/ clear");
                                /*clear*/ /*_.RETURN___V82*/ meltfptr[43] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_.PROGN___V83*/ meltfptr[68] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_._IFELSE___V29*/ meltfptr[25] = /*_._IFELSE___V53*/ meltfptr[38];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:162:/ clear");
                    /*clear*/ /*_#IS_LIST__L21*/ meltfnum[11] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V53*/ meltfptr[38] = 0 ;
                }
                ;
            }
        ;
        /*_.LET___V14*/ meltfptr[6] = /*_._IFELSE___V29*/ meltfptr[25];;

        MELT_LOCATION("warmelt-moremacro.melt:147:/ clear");
        /*clear*/ /*_.CONT__V15*/ meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.SLOC__V16*/ meltfptr[15] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V17*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V18*/ meltfptr[17] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURIF__V19*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RESTPAIR__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L7*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V23*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_STRING__L10*/ meltfnum[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V29*/ meltfptr[25] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:143:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V14*/ meltfptr[6];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:143:/ locexp");
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
        /*clear*/ /*_.IFCPP___V6*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V9*/ meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V14*/ meltfptr[6] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_GCCIF", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER fromline 1752 */

    /** start of frame for meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER// fromline 1568
        : public Melt_CallFrameWithValues<12>
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
        MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<12> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER), clos) {};
        MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER() //the constructor fromline 1642
            : Melt_CallFrameWithValues<12> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<12> (fil,lin, sizeof(MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER)) {};
        MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<12> (fil,lin, sizeof(MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER


    /** end of frame for meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER fromline 1697**/

    /* end of frame for routine meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER fromline 1756 */

    /* classy proc frame meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER */ MeltFrame_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPANDOBSOLETE_CONTAINER", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:225:/ getarg");
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
        MELT_LOCATION("warmelt-moremacro.melt:226:/ cppif.then");
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
            MELT_LOCATION("warmelt-moremacro.melt:226:/ cond");
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
                        MELT_LOCATION("warmelt-moremacro.melt:226:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 226;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "mexpandobsolete_container sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V6*/ meltfptr[5] = /*_.MELT_DEBUG_FUN__V7*/ meltfptr[6];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:226:/ clear");
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
                MELT_LOCATION("warmelt-moremacro.melt:226:/ locexp");
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
        MELT_LOCATION("warmelt-moremacro.melt:227:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-moremacro.melt:227:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V9*/ meltfptr[5] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:227:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 227;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V9*/ meltfptr[5] = /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:227:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V8*/ meltfptr[6] = /*_._IFELSE___V9*/ meltfptr[5];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:227:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V9*/ meltfptr[5] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V8*/ meltfptr[6] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:228:/ cond");
        /*cond*/ if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]),
                                          (melt_ptr_t)((/*!CLASS_LOCATED*/ meltfrout->tabval[3])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^getslot*/
                {
                    melt_ptr_t slot=NULL, obj=NULL;
                    obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
                    melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
                    /*_.LOCA_LOCATION__V11*/ meltfptr[9] = slot;
                };
                ;
            }
        else    /*^cond.else*/
            {

                /*_.LOCA_LOCATION__V11*/ meltfptr[9] =  /*reallynil*/ NULL ;;
            }
        ;

        {
            MELT_LOCATION("warmelt-moremacro.melt:228:/ locexp");
            melt_warning_str(0, (melt_ptr_t)(/*_.LOCA_LOCATION__V11*/ meltfptr[9]), ( "obsolete use of CONTAINER in expression; use REFERENCE instead"), (melt_ptr_t)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:230:/ apply");
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
            /*_.MEXPAND_REFERENCE__V12*/ meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!MEXPAND_REFERENCE*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:225:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.MEXPAND_REFERENCE__V12*/ meltfptr[5];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:225:/ locexp");
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
        /*clear*/ /*_.LOCA_LOCATION__V11*/ meltfptr[9] = 0 ;
        /*^clear*/
        /*clear*/ /*_.MEXPAND_REFERENCE__V12*/ meltfptr[5] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPANDOBSOLETE_CONTAINER", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER fromline 1752 */

    /** start of frame for meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER// fromline 1568
        : public Melt_CallFrameWithValues<11>
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
        MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<11> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER), clos) {};
        MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER() //the constructor fromline 1642
            : Melt_CallFrameWithValues<11> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<11> (fil,lin, sizeof(MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER)) {};
        MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<11> (fil,lin, sizeof(MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER


    /** end of frame for meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER fromline 1697**/

    /* end of frame for routine meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER fromline 1756 */

    /* classy proc frame meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER */ MeltFrame_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("PATEXPANDOBSOLETE_CONTAINER", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:232:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.PCTX__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.PCTX__V4*/ meltfptr[3])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:233:/ cppif.then");
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
            MELT_LOCATION("warmelt-moremacro.melt:233:/ cond");
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
                        MELT_LOCATION("warmelt-moremacro.melt:233:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 233;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "patexpandobsolete_container sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V6*/ meltfptr[5] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V5*/ meltfptr[4] = /*_.MELT_DEBUG_FUN__V6*/ meltfptr[5];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:233:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
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
                MELT_LOCATION("warmelt-moremacro.melt:233:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
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

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:234:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-moremacro.melt:234:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V8*/ meltfptr[4] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:234:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 234;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V9*/ meltfptr[8] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V8*/ meltfptr[4] = /*_.MELT_ASSERT_FAILURE_FUN__V9*/ meltfptr[8];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:234:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V9*/ meltfptr[8] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V7*/ meltfptr[5] = /*_._IFELSE___V8*/ meltfptr[4];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:234:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V8*/ meltfptr[4] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V7*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:235:/ cond");
        /*cond*/ if (
            /*ifisa*/ melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]),
                                          (melt_ptr_t)((/*!CLASS_LOCATED*/ meltfrout->tabval[3])))
        ) /*then*/
            {
                /*^cond.then*/
                /*^getslot*/
                {
                    melt_ptr_t slot=NULL, obj=NULL;
                    obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
                    melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
                    /*_.LOCA_LOCATION__V10*/ meltfptr[8] = slot;
                };
                ;
            }
        else    /*^cond.else*/
            {

                /*_.LOCA_LOCATION__V10*/ meltfptr[8] =  /*reallynil*/ NULL ;;
            }
        ;

        {
            MELT_LOCATION("warmelt-moremacro.melt:235:/ locexp");
            melt_warning_str(0, (melt_ptr_t)(/*_.LOCA_LOCATION__V10*/ meltfptr[8]), ( "obsolete use of CONTAINER in pattern; use REFERENCE instead"), (melt_ptr_t)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:237:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.PCTX__V4*/ meltfptr[3];
            /*_.PATEXPAND_REFERENCE__V11*/ meltfptr[4] =  melt_apply ((meltclosure_ptr_t)((/*!PATEXPAND_REFERENCE*/ meltfrout->tabval[4])), (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:232:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.PATEXPAND_REFERENCE__V11*/ meltfptr[4];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:232:/ locexp");
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
        /*clear*/ /*_.IFCPP___V7*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOCA_LOCATION__V10*/ meltfptr[8] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PATEXPAND_REFERENCE__V11*/ meltfptr[4] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("PATEXPANDOBSOLETE_CONTAINER", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR fromline 1752 */

    /** start of frame for meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR// fromline 1568
        : public Melt_CallFrameWithValues<69>
    {
    public: /* fromline 1572*/
        long mcfr_varnum[36];
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
        MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<69> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR), clos) {};
        MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR() //the constructor fromline 1642
            : Melt_CallFrameWithValues<69> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<69> (fil,lin, sizeof(MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR)) {};
        MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<69> (fil,lin, sizeof(MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR


    /** end of frame for meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR fromline 1697**/

    /* end of frame for routine meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR fromline 1756 */

    /* classy proc frame meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR */ MeltFrame_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("EXPAND_QUOTED_SEXPR", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:246:/ getarg");
    /*_.SEXPR__V2*/ meltfptr[1] = (melt_ptr_t) meltfirstargp_;

    /*getarg#1*/
    /*^getarg*/
    if (meltxargdescr_[0] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ENV__V3*/ meltfptr[2] = (meltxargtab_[0].meltbp_aptr) ? (*(meltxargtab_[0].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2])) != NULL);


    /*getarg#2*/
    /*^getarg*/
    if (meltxargdescr_[1] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.ANTIQUOTEFUN__V4*/ meltfptr[3] = (meltxargtab_[1].meltbp_aptr) ? (*(meltxargtab_[1].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.ANTIQUOTEFUN__V4*/ meltfptr[3])) != NULL);


    /*getarg#3*/
    /*^getarg*/
    if (meltxargdescr_[2] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MEXPANDER__V5*/ meltfptr[4] = (meltxargtab_[2].meltbp_aptr) ? (*(meltxargtab_[2].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MEXPANDER__V5*/ meltfptr[4])) != NULL);


    /*getarg#4*/
    /*^getarg*/
    if (meltxargdescr_[3] != MELTBPAR_PTR) goto meltlab_endgetargs;
    /*_.MODCTX__V6*/ meltfptr[5] = (meltxargtab_[3].meltbp_aptr) ? (*(meltxargtab_[3].meltbp_aptr)) : NULL;
    gcc_assert(melt_discr((melt_ptr_t)(/*_.MODCTX__V6*/ meltfptr[5])) != NULL);

    ;
    goto meltlab_endgetargs;
meltlab_endgetargs:
    ;
    /*body*/
    /*^block*/
    /*anyblock*/
    {


#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:247:/ cppif.then");
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
            MELT_LOCATION("warmelt-moremacro.melt:247:/ cond");
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
                        MELT_LOCATION("warmelt-moremacro.melt:247:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L2*/ meltfnum[1];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 247;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "expand_quoted_sexpr sexpr=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_DEBUG_FUN__V8*/ meltfptr[7] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V7*/ meltfptr[6] = /*_.MELT_DEBUG_FUN__V8*/ meltfptr[7];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:247:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L2*/ meltfnum[1] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V8*/ meltfptr[7] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V7*/ meltfptr[6] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:247:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V7*/ meltfptr[6] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:248:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L3*/ meltfnum[1] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
            MELT_LOCATION("warmelt-moremacro.melt:248:/ cond");
            /*cond*/ if (/*_#IS_A__L3*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V10*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:248:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 248;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V10*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:248:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V9*/ meltfptr[7] = /*_._IFELSE___V10*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:248:/ clear");
            /*clear*/ /*_#IS_A__L3*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V10*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V9*/ meltfptr[7] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:249:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L4*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[3])));;
            MELT_LOCATION("warmelt-moremacro.melt:249:/ cond");
            /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V13*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:249:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 249;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V13*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:249:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V12*/ meltfptr[10] = /*_._IFELSE___V13*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:249:/ clear");
            /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V13*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V12*/ meltfptr[10] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:250:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L5*/ meltfnum[1] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V6*/ meltfptr[5])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-moremacro.melt:250:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L5*/ meltfnum[1]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V16*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:250:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 250;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V6*/ meltfptr[5];
                            /*_.MELT_ASSERT_FAILURE_FUN__V17*/ meltfptr[16] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[2])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V16*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V17*/ meltfptr[16];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:250:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V17*/ meltfptr[16] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V15*/ meltfptr[13] = /*_._IFELSE___V16*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:250:/ clear");
            /*clear*/ /*_#IS_OBJECT__L5*/ meltfnum[1] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V16*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V15*/ meltfptr[13] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:251:/ quasiblock");


        /*^getslot*/
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V19*/ meltfptr[6] = slot;
        };
        ;
        MELT_LOCATION("warmelt-moremacro.melt:252:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V20*/ meltfptr[19] = slot;
        };
        ;
        /*_#DLINE__L6*/ meltfnum[0] =
            (melt_get_int((melt_ptr_t)(/*_.LOC__V20*/ meltfptr[19])));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_MIXINT__L7*/ meltfnum[1] =
            (melt_magic_discr((melt_ptr_t)(/*_.LOC__V20*/ meltfptr[19])) == MELTOBMAG_MIXINT);;
        MELT_LOCATION("warmelt-moremacro.melt:255:/ cond");
        /*cond*/ if (/*_#IS_MIXINT__L7*/ meltfnum[1]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {

                    /*_.MIXINT_VAL__V22*/ meltfptr[21] =
                        (melt_val_mixint((melt_ptr_t)(/*_.LOC__V20*/ meltfptr[19])));;
                    /*^compute*/
                    /*_.DFILNAM__V21*/ meltfptr[20] = /*_.MIXINT_VAL__V22*/ meltfptr[21];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:255:/ clear");
                    /*clear*/ /*_.MIXINT_VAL__V22*/ meltfptr[21] = 0 ;
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
                    /*_#IS_MIXLOC__L8*/ meltfnum[7] =
                        (melt_magic_discr((melt_ptr_t)(/*_.LOC__V20*/ meltfptr[19])) == MELTOBMAG_MIXLOC);;
                    MELT_LOCATION("warmelt-moremacro.melt:256:/ cond");
                    /*cond*/ if (/*_#IS_MIXLOC__L8*/ meltfnum[7]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {

                                /*_.MIXLOC_VAL__V24*/ meltfptr[23] =
                                    (melt_val_mixloc((melt_ptr_t)(/*_.LOC__V20*/ meltfptr[19])));;
                                /*^compute*/
                                /*_._IFELSE___V23*/ meltfptr[21] = /*_.MIXLOC_VAL__V24*/ meltfptr[23];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:256:/ clear");
                                /*clear*/ /*_.MIXLOC_VAL__V24*/ meltfptr[23] = 0 ;
                            }
                            ;
                        }
                    else    /*^cond.else*/
                        {

                            /*_._IFELSE___V23*/ meltfptr[21] =  /*reallynil*/ NULL ;;
                        }
                    ;
                    /*^compute*/
                    /*_.DFILNAM__V21*/ meltfptr[20] = /*_._IFELSE___V23*/ meltfptr[21];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:255:/ clear");
                    /*clear*/ /*_#IS_MIXLOC__L8*/ meltfnum[7] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V23*/ meltfptr[21] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_.BOX__V25*/ meltfptr[23] =
            /*full constboxing*/ /*boxing ctype_long*/ meltgc_new_int((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(DISCR_CONSTANT_INTEGER)))), (/*_#DLINE__L6*/ meltfnum[0]));;
        MELT_LOCATION("warmelt-moremacro.melt:260:/ blockmultialloc");
        /*multiallocblock*/
        {
            struct meltletrec_1_st
            {
                struct MELT_MULTIPLE_STRUCT(2) rtup_0__TUPLREC__x1;
                long meltletrec_1_endgap;
            } *meltletrec_1_ptr = 0;
            meltletrec_1_ptr = (struct meltletrec_1_st *) meltgc_allocate (sizeof (struct meltletrec_1_st), 0);
            /*^blockmultialloc.initfill*/
            /*inimult rtup_0__TUPLREC__x1*/
            /*_.TUPLREC___V27*/ meltfptr[26] = (melt_ptr_t) &meltletrec_1_ptr->rtup_0__TUPLREC__x1;
            meltletrec_1_ptr->rtup_0__TUPLREC__x1.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MULTIPLE))));
            meltletrec_1_ptr->rtup_0__TUPLREC__x1.nbval = 2;


            /*^putuple*/
            /*putupl#1*/
            melt_assertmsg("putupl [:260] #1 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V27*/ meltfptr[26]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:260] #1 checkoff", (0>=0 && 0< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V27*/ meltfptr[26]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V27*/ meltfptr[26]))->tabval[0] = (melt_ptr_t)(/*_.DFILNAM__V21*/ meltfptr[20]);
            ;
            /*^putuple*/
            /*putupl#2*/
            melt_assertmsg("putupl [:260] #2 checktup", melt_magic_discr((melt_ptr_t)(/*_.TUPLREC___V27*/ meltfptr[26]))== MELTOBMAG_MULTIPLE);
            melt_assertmsg("putupl [:260] #2 checkoff", (1>=0 && 1< melt_multiple_length((melt_ptr_t)(/*_.TUPLREC___V27*/ meltfptr[26]))));
            ((meltmultiple_ptr_t)(/*_.TUPLREC___V27*/ meltfptr[26]))->tabval[1] = (melt_ptr_t)(/*_.BOX__V25*/ meltfptr[23]);
            ;
            /*^touch*/
            meltgc_touch(/*_.TUPLREC___V27*/ meltfptr[26]);
            ;
            /*_.TUPLE___V26*/ meltfptr[21] = /*_.TUPLREC___V27*/ meltfptr[26];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:260:/ clear");
            /*clear*/ /*_.TUPLREC___V27*/ meltfptr[26] = 0 ;
            /*^clear*/
            /*clear*/ /*_.TUPLREC___V27*/ meltfptr[26] = 0 ;
        } /*end multiallocblock*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:257:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_HOOK_CALL*/ meltfrout->tabval[4])), (4), "CLASS_SOURCE_HOOK_CALL");
            /*_.INST__V29*/ meltfptr[28] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (1), (/*_.LOC__V20*/ meltfptr[19]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SHOOK_CALLED", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (3), ((/*!HOOK_MELT_MAKE_LOCATION*/ meltfrout->tabval[5])), "SHOOK_CALLED");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V29*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V29*/ meltfptr[28]), (2), (/*_.TUPLE___V26*/ meltfptr[21]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V29*/ meltfptr[28], "newly made instance");
        ;
        /*_.LOCEXP__V28*/ meltfptr[26] = /*_.INST__V29*/ meltfptr[28];;
        /*^compute*/
        /*_.ARGLIST__V30*/ meltfptr[29] =
            (meltgc_new_list((meltobject_ptr_t)((/*!DISCR_LIST*/ meltfrout->tabval[6]))));;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:263:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L9*/ meltfnum[7] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:263:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L9*/ meltfnum[7]) /*then*/
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
                        MELT_LOCATION("warmelt-moremacro.melt:263:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[7];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L10*/ meltfnum[9];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 263;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "expand_quoted_sexpr dline=";
                            /*^apply.arg*/
                            argtab[4].meltbp_long = /*_#DLINE__L6*/ meltfnum[0];
                            /*^apply.arg*/
                            argtab[5].meltbp_cstring =  " dfilnam=";
                            /*^apply.arg*/
                            argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.DFILNAM__V21*/ meltfptr[20];
                            /*_.MELT_DEBUG_FUN__V32*/ meltfptr[31] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V31*/ meltfptr[30] = /*_.MELT_DEBUG_FUN__V32*/ meltfptr[31];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:263:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L10*/ meltfnum[9] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V32*/ meltfptr[31] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V31*/ meltfptr[30] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:263:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L9*/ meltfnum[7] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V31*/ meltfptr[30] = 0 ;
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
        /*citerblock FOREACH_PAIR_COMPONENT_IN_LIST*/
        {
            /* start foreach_pair_component_in_list meltcit1__EACHLIST */
            for (/*_.CURPAIR__V33*/ meltfptr[31] = melt_list_first( (melt_ptr_t)/*_.CONT__V19*/ meltfptr[6]);
                                    melt_magic_discr((melt_ptr_t) /*_.CURPAIR__V33*/ meltfptr[31]) == MELTOBMAG_PAIR;
                                    /*_.CURPAIR__V33*/ meltfptr[31] = melt_pair_tail((melt_ptr_t) /*_.CURPAIR__V33*/ meltfptr[31]))
                {
                    /*_.CURCOMP__V34*/ meltfptr[30] = melt_pair_head((melt_ptr_t) /*_.CURPAIR__V33*/ meltfptr[31]);



#if MELT_HAVE_DEBUG
                    MELT_LOCATION("warmelt-moremacro.melt:267:/ cppif.then");
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
                        /*_#MELT_NEED_DBG__L11*/ meltfnum[9] =
                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                            ;;
                        MELT_LOCATION("warmelt-moremacro.melt:267:/ cond");
                        /*cond*/ if (/*_#MELT_NEED_DBG__L11*/ meltfnum[9]) /*then*/
                            {
                                /*^cond.then*/
                                /*^block*/
                                /*anyblock*/
                                {

                                    /*_#MELT_CALLCOUNT__L12*/ meltfnum[7] =
                                        /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                        meltcallcount  /* melt_callcount debugging */
#else
                                        0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                        ;;

                                    MELT_CHECK_SIGNAL();
                                    ;
                                    MELT_LOCATION("warmelt-moremacro.melt:267:/ apply");
                                    /*apply*/
                                    {
                                        union meltparam_un argtab[7];
                                        memset(&argtab, 0, sizeof(argtab));
                                        /*^apply.arg*/
                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L12*/ meltfnum[7];
                                        /*^apply.arg*/
                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                        /*^apply.arg*/
                                        argtab[2].meltbp_long = 267;
                                        /*^apply.arg*/
                                        argtab[3].meltbp_cstring =  "expand_quoted_sexpr curcomp=";
                                        /*^apply.arg*/
                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.CURCOMP__V34*/ meltfptr[30];
                                        /*^apply.arg*/
                                        argtab[5].meltbp_cstring =  "\n.. arglist=";
                                        /*^apply.arg*/
                                        argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.ARGLIST__V30*/ meltfptr[29];
                                        /*_.MELT_DEBUG_FUN__V36*/ meltfptr[35] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                    }
                                    ;
                                    /*_._IF___V35*/ meltfptr[34] = /*_.MELT_DEBUG_FUN__V36*/ meltfptr[35];;
                                    /*epilog*/

                                    MELT_LOCATION("warmelt-moremacro.melt:267:/ clear");
                                    /*clear*/ /*_#MELT_CALLCOUNT__L12*/ meltfnum[7] = 0 ;
                                    /*^clear*/
                                    /*clear*/ /*_.MELT_DEBUG_FUN__V36*/ meltfptr[35] = 0 ;
                                }
                                ;
                            }
                        else    /*^cond.else*/
                            {

                                /*_._IF___V35*/ meltfptr[34] =  /*reallynil*/ NULL ;;
                            }
                        ;

                        {
                            MELT_LOCATION("warmelt-moremacro.melt:267:/ locexp");
                            /*void*/(void)0;
                        }
                        ;
                        /*^quasiblock*/


                        /*epilog*/

                        /*^clear*/
                        /*clear*/ /*_#MELT_NEED_DBG__L11*/ meltfnum[9] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_._IF___V35*/ meltfptr[34] = 0 ;
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
                    /*_#NULL__L13*/ meltfnum[7] =
                        (/*null*/(/*_.CURCOMP__V34*/ meltfptr[30]) == NULL);;
                    MELT_LOCATION("warmelt-moremacro.melt:268:/ cond");
                    /*cond*/ if (/*_#NULL__L13*/ meltfnum[7]) /*then*/
                        {
                            /*^cond.then*/
                            /*^block*/
                            /*anyblock*/
                            {




                                {
                                    MELT_LOCATION("warmelt-moremacro.melt:269:/ locexp");
                                    meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)((/*nil*/NULL)));
                                }
                                ;
                                /*clear*/ /*_._IFELSE___V37*/ meltfptr[35] = 0 ;
                                /*epilog*/
                            }
                            ;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-moremacro.melt:268:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_INTEGERBOX__L14*/ meltfnum[9] =
                                    (melt_magic_discr((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30])) == MELTOBMAG_INT);;
                                MELT_LOCATION("warmelt-moremacro.melt:271:/ cond");
                                /*cond*/ if (/*_#IS_INTEGERBOX__L14*/ meltfnum[9]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*^block*/
                                        /*anyblock*/
                                        {




                                            {
                                                MELT_LOCATION("warmelt-moremacro.melt:272:/ locexp");
                                                meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]));
                                            }
                                            ;
                                            /*clear*/ /*_._IFELSE___V38*/ meltfptr[34] = 0 ;
                                            /*epilog*/
                                        }
                                        ;
                                    }
                                else
                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:271:/ cond.else");

                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*_#IS_STRING__L15*/ meltfnum[14] =
                                                (melt_magic_discr((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30])) == MELTOBMAG_STRING);;
                                            MELT_LOCATION("warmelt-moremacro.melt:273:/ cond");
                                            /*cond*/ if (/*_#IS_STRING__L15*/ meltfnum[14]) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^block*/
                                                    /*anyblock*/
                                                    {




                                                        {
                                                            MELT_LOCATION("warmelt-moremacro.melt:274:/ locexp");
                                                            meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]));
                                                        }
                                                        ;
                                                        /*clear*/ /*_._IFELSE___V39*/ meltfptr[38] = 0 ;
                                                        /*epilog*/
                                                    }
                                                    ;
                                                }
                                            else
                                                {
                                                    MELT_LOCATION("warmelt-moremacro.melt:273:/ cond.else");

                                                    /*^block*/
                                                    /*anyblock*/
                                                    {


                                                        MELT_CHECK_SIGNAL();
                                                        ;
                                                        /*_#IS_A__L16*/ meltfnum[15] =
                                                            melt_is_instance_of((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]), (melt_ptr_t)((/*!CLASS_KEYWORD*/ meltfrout->tabval[7])));;
                                                        MELT_LOCATION("warmelt-moremacro.melt:275:/ cond");
                                                        /*cond*/ if (/*_#IS_A__L16*/ meltfnum[15]) /*then*/
                                                            {
                                                                /*^cond.then*/
                                                                /*^block*/
                                                                /*anyblock*/
                                                                {




                                                                    {
                                                                        MELT_LOCATION("warmelt-moremacro.melt:276:/ locexp");
                                                                        meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]));
                                                                    }
                                                                    ;
                                                                    /*clear*/ /*_._IFELSE___V40*/ meltfptr[39] = 0 ;
                                                                    /*epilog*/
                                                                }
                                                                ;
                                                            }
                                                        else
                                                            {
                                                                MELT_LOCATION("warmelt-moremacro.melt:275:/ cond.else");

                                                                /*^block*/
                                                                /*anyblock*/
                                                                {


                                                                    MELT_CHECK_SIGNAL();
                                                                    ;
                                                                    /*_#IS_A__L17*/ meltfnum[16] =
                                                                        melt_is_instance_of((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[8])));;
                                                                    MELT_LOCATION("warmelt-moremacro.melt:277:/ cond");
                                                                    /*cond*/ if (/*_#IS_A__L17*/ meltfnum[16]) /*then*/
                                                                        {
                                                                            /*^cond.then*/
                                                                            /*^block*/
                                                                            /*anyblock*/
                                                                            {

                                                                                MELT_LOCATION("warmelt-moremacro.melt:278:/ quasiblock");



                                                                                MELT_CHECK_SIGNAL();
                                                                                ;
                                                                                /*^quasiblock*/


                                                                                /*^rawallocobj*/
                                                                                /*rawallocobj*/
                                                                                {
                                                                                    melt_ptr_t newobj = 0;
                                                                                    melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_QUOTE*/ meltfrout->tabval[9])), (3), "CLASS_SOURCE_QUOTE");
                                                                                    /*_.INST__V43*/ meltfptr[42] =
                                                                                        newobj;
                                                                                };
                                                                                ;
                                                                                /*^putslot*/
                                                                                /*putslot*/
                                                                                melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V43*/ meltfptr[42])) == MELTOBMAG_OBJECT);
                                                                                melt_putfield_object((/*_.INST__V43*/ meltfptr[42]), (1), (/*_.LOC__V20*/ meltfptr[19]), "LOCA_LOCATION");
                                                                                ;
                                                                                /*^putslot*/
                                                                                /*putslot*/
                                                                                melt_assertmsg("checkobj putslot  _ @SQUOTED", melt_magic_discr((melt_ptr_t)(/*_.INST__V43*/ meltfptr[42])) == MELTOBMAG_OBJECT);
                                                                                melt_putfield_object((/*_.INST__V43*/ meltfptr[42]), (2), (/*_.CURCOMP__V34*/ meltfptr[30]), "SQUOTED");
                                                                                ;
                                                                                /*^touchobj*/

                                                                                melt_dbgtrace_written_object (/*_.INST__V43*/ meltfptr[42], "newly made instance");
                                                                                ;
                                                                                /*_.QSYMB__V42*/ meltfptr[41] = /*_.INST__V43*/ meltfptr[42];;



                                                                                {
                                                                                    MELT_LOCATION("warmelt-moremacro.melt:282:/ locexp");
                                                                                    meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.QSYMB__V42*/ meltfptr[41]));
                                                                                }
                                                                                ;
                                                                                /*clear*/ /*_._IFELSE___V41*/ meltfptr[40] = 0 ;

                                                                                MELT_LOCATION("warmelt-moremacro.melt:278:/ clear");
                                                                                /*clear*/ /*_.QSYMB__V42*/ meltfptr[41] = 0 ;
                                                                                /*epilog*/
                                                                            }
                                                                            ;
                                                                        }
                                                                    else
                                                                        {
                                                                            MELT_LOCATION("warmelt-moremacro.melt:277:/ cond.else");

                                                                            /*^block*/
                                                                            /*anyblock*/
                                                                            {


                                                                                MELT_CHECK_SIGNAL();
                                                                                ;
                                                                                /*_#IS_A__L18*/ meltfnum[17] =
                                                                                    melt_is_instance_of((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[1])));;
                                                                                MELT_LOCATION("warmelt-moremacro.melt:283:/ cond");
                                                                                /*cond*/ if (/*_#IS_A__L18*/ meltfnum[17]) /*then*/
                                                                                    {
                                                                                        /*^cond.then*/
                                                                                        /*^block*/
                                                                                        /*anyblock*/
                                                                                        {


                                                                                            MELT_CHECK_SIGNAL();
                                                                                            ;
                                                                                            /*_#IS_CLOSURE__L19*/ meltfnum[18] =
                                                                                                (melt_magic_discr((melt_ptr_t)(/*_.ANTIQUOTEFUN__V4*/ meltfptr[3])) == MELTOBMAG_CLOSURE);;
                                                                                            MELT_LOCATION("warmelt-moremacro.melt:284:/ cond");
                                                                                            /*cond*/ if (/*_#IS_CLOSURE__L19*/ meltfnum[18]) /*then*/
                                                                                                {
                                                                                                    /*^cond.then*/
                                                                                                    /*^block*/
                                                                                                    /*anyblock*/
                                                                                                    {

                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:285:/ quasiblock");


                                                                                                        /*^getslot*/
                                                                                                        {
                                                                                                            melt_ptr_t slot=NULL, obj=NULL;
                                                                                                            obj = (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]) /*=obj*/;
                                                                                                            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
                                                                                                            /*_.CURLOC__V45*/ meltfptr[44] = slot;
                                                                                                        };
                                                                                                        ;
                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:286:/ getslot");
                                                                                                        {
                                                                                                            melt_ptr_t slot=NULL, obj=NULL;
                                                                                                            obj = (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]) /*=obj*/;
                                                                                                            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
                                                                                                            /*_.CURCONT__V46*/ meltfptr[45] = slot;
                                                                                                        };
                                                                                                        ;

                                                                                                        MELT_CHECK_SIGNAL();
                                                                                                        ;

                                                                                                        MELT_CHECK_SIGNAL();
                                                                                                        ;
                                                                                                        /*_#LIST_LENGTH__L20*/ meltfnum[19] =
                                                                                                            (melt_list_length((melt_ptr_t)(/*_.CURCONT__V46*/ meltfptr[45])));;
                                                                                                        /*^compute*/
                                                                                                        /*_#eqeqI__L21*/ meltfnum[20] =
                                                                                                            ((/*_#LIST_LENGTH__L20*/ meltfnum[19]) == (2));;
                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:288:/ cond");
                                                                                                        /*cond*/ if (/*_#eqeqI__L21*/ meltfnum[20]) /*then*/
                                                                                                            {
                                                                                                                /*^cond.then*/
                                                                                                                /*^block*/
                                                                                                                /*anyblock*/
                                                                                                                {

                                                                                                                    /*_.LIST_FIRST_ELEMENT__V47*/ meltfptr[46] =
                                                                                                                        (melt_pair_head (melt_list_first((melt_ptr_t)(/*_.CURCONT__V46*/ meltfptr[45]))));;
                                                                                                                    /*^compute*/
                                                                                                                    /*_#eqeq__L23*/ meltfnum[22] =
                                                                                                                        ((/*_.LIST_FIRST_ELEMENT__V47*/ meltfptr[46]) == ((/*!konst_10_COMMA*/ meltfrout->tabval[10])));;
                                                                                                                    /*^compute*/
                                                                                                                    /*_#_IF___L22*/ meltfnum[21] = /*_#eqeq__L23*/ meltfnum[22];;
                                                                                                                    /*epilog*/

                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:288:/ clear");
                                                                                                                    /*clear*/ /*_.LIST_FIRST_ELEMENT__V47*/ meltfptr[46] = 0 ;
                                                                                                                    /*^clear*/
                                                                                                                    /*clear*/ /*_#eqeq__L23*/ meltfnum[22] = 0 ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                        else    /*^cond.else*/
                                                                                                            {

                                                                                                                /*_#_IF___L22*/ meltfnum[21] = 0;;
                                                                                                            }
                                                                                                        ;
                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:288:/ cond");
                                                                                                        /*cond*/ if (/*_#_IF___L22*/ meltfnum[21]) /*then*/
                                                                                                            {
                                                                                                                /*^cond.then*/
                                                                                                                /*^block*/
                                                                                                                /*anyblock*/
                                                                                                                {

                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:291:/ quasiblock");



                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                    ;
                                                                                                                    /*^apply*/
                                                                                                                    /*apply*/
                                                                                                                    {
                                                                                                                        union meltparam_un argtab[1];
                                                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[0].meltbp_long = 1;
                                                                                                                        /*_.COMMAEXP__V48*/ meltfptr[46] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_NTH_ELEMENT*/ meltfrout->tabval[11])), (melt_ptr_t)(/*_.CURCONT__V46*/ meltfptr[45]), (MELTBPARSTR_LONG ""), argtab, "", (union meltparam_un*)0);
                                                                                                                    }
                                                                                                                    ;

#if MELT_HAVE_DEBUG
                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:293:/ cppif.then");
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
                                                                                                                        /*_#MELT_NEED_DBG__L24*/ meltfnum[22] =
                                                                                                                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                                                                                                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                                                                                                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                                                                                                            ;;
                                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:293:/ cond");
                                                                                                                        /*cond*/ if (/*_#MELT_NEED_DBG__L24*/ meltfnum[22]) /*then*/
                                                                                                                            {
                                                                                                                                /*^cond.then*/
                                                                                                                                /*^block*/
                                                                                                                                /*anyblock*/
                                                                                                                                {

                                                                                                                                    /*_#MELT_CALLCOUNT__L25*/ meltfnum[24] =
                                                                                                                                        /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                                                                                                        meltcallcount  /* melt_callcount debugging */
#else
                                                                                                                                        0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                                                                                                        ;;

                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                    ;
                                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:293:/ apply");
                                                                                                                                    /*apply*/
                                                                                                                                    {
                                                                                                                                        union meltparam_un argtab[7];
                                                                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L25*/ meltfnum[24];
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[2].meltbp_long = 293;
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[3].meltbp_cstring =  "expand_quoted_sexpr commaexp=";
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.COMMAEXP__V48*/ meltfptr[46];
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[5].meltbp_cstring =  " curloc=";
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[6].meltbp_aptr = (melt_ptr_t*) &/*_.CURLOC__V45*/ meltfptr[44];
                                                                                                                                        /*_.MELT_DEBUG_FUN__V50*/ meltfptr[49] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                    /*_._IF___V49*/ meltfptr[48] = /*_.MELT_DEBUG_FUN__V50*/ meltfptr[49];;
                                                                                                                                    /*epilog*/

                                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:293:/ clear");
                                                                                                                                    /*clear*/ /*_#MELT_CALLCOUNT__L25*/ meltfnum[24] = 0 ;
                                                                                                                                    /*^clear*/
                                                                                                                                    /*clear*/ /*_.MELT_DEBUG_FUN__V50*/ meltfptr[49] = 0 ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                        else    /*^cond.else*/
                                                                                                                            {

                                                                                                                                /*_._IF___V49*/ meltfptr[48] =  /*reallynil*/ NULL ;;
                                                                                                                            }
                                                                                                                        ;

                                                                                                                        {
                                                                                                                            MELT_LOCATION("warmelt-moremacro.melt:293:/ locexp");
                                                                                                                            /*void*/(void)0;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                        /*^quasiblock*/


                                                                                                                        /*epilog*/

                                                                                                                        /*^clear*/
                                                                                                                        /*clear*/ /*_#MELT_NEED_DBG__L24*/ meltfnum[22] = 0 ;
                                                                                                                        /*^clear*/
                                                                                                                        /*clear*/ /*_._IF___V49*/ meltfptr[48] = 0 ;
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
                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:294:/ apply");
                                                                                                                    /*apply*/
                                                                                                                    {
                                                                                                                        union meltparam_un argtab[5];
                                                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ARGLIST__V30*/ meltfptr[29];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.CURLOC__V45*/ meltfptr[44];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V5*/ meltfptr[4];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V6*/ meltfptr[5];
                                                                                                                        /*_.ANTIQUOTEFUN__V51*/ meltfptr[49] =  melt_apply ((meltclosure_ptr_t)(/*_.ANTIQUOTEFUN__V4*/ meltfptr[3]), (melt_ptr_t)(/*_.COMMAEXP__V48*/ meltfptr[46]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                                                    }
                                                                                                                    ;

#if MELT_HAVE_DEBUG
                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:295:/ cppif.then");
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
                                                                                                                        /*_#MELT_NEED_DBG__L26*/ meltfnum[24] =
                                                                                                                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                                                                                                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                                                                                                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                                                                                                            ;;
                                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:295:/ cond");
                                                                                                                        /*cond*/ if (/*_#MELT_NEED_DBG__L26*/ meltfnum[24]) /*then*/
                                                                                                                            {
                                                                                                                                /*^cond.then*/
                                                                                                                                /*^block*/
                                                                                                                                /*anyblock*/
                                                                                                                                {

                                                                                                                                    /*_#MELT_CALLCOUNT__L27*/ meltfnum[22] =
                                                                                                                                        /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                                                                                                        meltcallcount  /* melt_callcount debugging */
#else
                                                                                                                                        0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                                                                                                        ;;

                                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                                    ;
                                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:295:/ apply");
                                                                                                                                    /*apply*/
                                                                                                                                    {
                                                                                                                                        union meltparam_un argtab[5];
                                                                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L27*/ meltfnum[22];
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[2].meltbp_long = 295;
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[3].meltbp_cstring =  "expand_quoted_sexpr after antiquotefun arglist=";
                                                                                                                                        /*^apply.arg*/
                                                                                                                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.ARGLIST__V30*/ meltfptr[29];
                                                                                                                                        /*_.MELT_DEBUG_FUN__V53*/ meltfptr[52] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                    /*_._IF___V52*/ meltfptr[48] = /*_.MELT_DEBUG_FUN__V53*/ meltfptr[52];;
                                                                                                                                    /*epilog*/

                                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:295:/ clear");
                                                                                                                                    /*clear*/ /*_#MELT_CALLCOUNT__L27*/ meltfnum[22] = 0 ;
                                                                                                                                    /*^clear*/
                                                                                                                                    /*clear*/ /*_.MELT_DEBUG_FUN__V53*/ meltfptr[52] = 0 ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                        else    /*^cond.else*/
                                                                                                                            {

                                                                                                                                /*_._IF___V52*/ meltfptr[48] =  /*reallynil*/ NULL ;;
                                                                                                                            }
                                                                                                                        ;

                                                                                                                        {
                                                                                                                            MELT_LOCATION("warmelt-moremacro.melt:295:/ locexp");
                                                                                                                            /*void*/(void)0;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                        /*^quasiblock*/


                                                                                                                        /*epilog*/

                                                                                                                        /*^clear*/
                                                                                                                        /*clear*/ /*_#MELT_NEED_DBG__L26*/ meltfnum[24] = 0 ;
                                                                                                                        /*^clear*/
                                                                                                                        /*clear*/ /*_._IF___V52*/ meltfptr[48] = 0 ;
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
                                                                                                                    /*_._IFELSE___V44*/ meltfptr[41] = /*_.ANTIQUOTEFUN__V51*/ meltfptr[49];;

                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:291:/ clear");
                                                                                                                    /*clear*/ /*_.COMMAEXP__V48*/ meltfptr[46] = 0 ;
                                                                                                                    /*^clear*/
                                                                                                                    /*clear*/ /*_.ANTIQUOTEFUN__V51*/ meltfptr[49] = 0 ;
                                                                                                                    /*epilog*/
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                        else
                                                                                                            {
                                                                                                                MELT_LOCATION("warmelt-moremacro.melt:288:/ cond.else");

                                                                                                                /*^block*/
                                                                                                                /*anyblock*/
                                                                                                                {


                                                                                                                    MELT_CHECK_SIGNAL();
                                                                                                                    ;
                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:297:/ apply");
                                                                                                                    /*apply*/
                                                                                                                    {
                                                                                                                        union meltparam_un argtab[4];
                                                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.ANTIQUOTEFUN__V4*/ meltfptr[3];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V5*/ meltfptr[4];
                                                                                                                        /*^apply.arg*/
                                                                                                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V6*/ meltfptr[5];
                                                                                                                        /*_.EXPAND_QUOTED_SEXPR__V54*/ meltfptr[52] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_QUOTED_SEXPR*/ meltfrout->tabval[12])), (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                                                    }
                                                                                                                    ;



                                                                                                                    {
                                                                                                                        /*^locexp*/
                                                                                                                        meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.EXPAND_QUOTED_SEXPR__V54*/ meltfptr[52]));
                                                                                                                    }
                                                                                                                    ;
                                                                                                                    /*clear*/ /*_._IFELSE___V44*/ meltfptr[41] = 0 ;
                                                                                                                    /*epilog*/

                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:288:/ clear");
                                                                                                                    /*clear*/ /*_.EXPAND_QUOTED_SEXPR__V54*/ meltfptr[52] = 0 ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                        ;

                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:285:/ clear");
                                                                                                        /*clear*/ /*_.CURLOC__V45*/ meltfptr[44] = 0 ;
                                                                                                        /*^clear*/
                                                                                                        /*clear*/ /*_.CURCONT__V46*/ meltfptr[45] = 0 ;
                                                                                                        /*^clear*/
                                                                                                        /*clear*/ /*_#LIST_LENGTH__L20*/ meltfnum[19] = 0 ;
                                                                                                        /*^clear*/
                                                                                                        /*clear*/ /*_#eqeqI__L21*/ meltfnum[20] = 0 ;
                                                                                                        /*^clear*/
                                                                                                        /*clear*/ /*_#_IF___L22*/ meltfnum[21] = 0 ;
                                                                                                        /*epilog*/
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                            else
                                                                                                {
                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:284:/ cond.else");

                                                                                                    /*^block*/
                                                                                                    /*anyblock*/
                                                                                                    {


                                                                                                        MELT_CHECK_SIGNAL();
                                                                                                        ;
                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:298:/ apply");
                                                                                                        /*apply*/
                                                                                                        {
                                                                                                            union meltparam_un argtab[4];
                                                                                                            memset(&argtab, 0, sizeof(argtab));
                                                                                                            /*^apply.arg*/
                                                                                                            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                                                                                                            /*^apply.arg*/
                                                                                                            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.ANTIQUOTEFUN__V4*/ meltfptr[3];
                                                                                                            /*^apply.arg*/
                                                                                                            argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V5*/ meltfptr[4];
                                                                                                            /*^apply.arg*/
                                                                                                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V6*/ meltfptr[5];
                                                                                                            /*_.EXPAND_QUOTED_SEXPR__V55*/ meltfptr[48] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_QUOTED_SEXPR*/ meltfrout->tabval[12])), (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                                        }
                                                                                                        ;



                                                                                                        {
                                                                                                            /*^locexp*/
                                                                                                            meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.EXPAND_QUOTED_SEXPR__V55*/ meltfptr[48]));
                                                                                                        }
                                                                                                        ;
                                                                                                        /*clear*/ /*_._IFELSE___V44*/ meltfptr[41] = 0 ;
                                                                                                        /*epilog*/

                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:284:/ clear");
                                                                                                        /*clear*/ /*_.EXPAND_QUOTED_SEXPR__V55*/ meltfptr[48] = 0 ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                            ;
                                                                                            /*epilog*/

                                                                                            MELT_LOCATION("warmelt-moremacro.melt:283:/ clear");
                                                                                            /*clear*/ /*_#IS_CLOSURE__L19*/ meltfnum[18] = 0 ;
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
                                                                                            /*_#IS_LIST__L28*/ meltfnum[22] =
                                                                                                (melt_magic_discr((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30])) == MELTOBMAG_LIST);;
                                                                                            MELT_LOCATION("warmelt-moremacro.melt:302:/ cond");
                                                                                            /*cond*/ if (/*_#IS_LIST__L28*/ meltfnum[22]) /*then*/
                                                                                                {
                                                                                                    /*^cond.then*/
                                                                                                    /*^block*/
                                                                                                    /*anyblock*/
                                                                                                    {


                                                                                                        MELT_CHECK_SIGNAL();
                                                                                                        ;
                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:303:/ apply");
                                                                                                        /*apply*/
                                                                                                        {
                                                                                                            union meltparam_un argtab[1];
                                                                                                            memset(&argtab, 0, sizeof(argtab));
                                                                                                            /*^apply.arg*/
                                                                                                            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.CURCOMP__V34*/ meltfptr[30];
                                                                                                            /*_.LIST_APPEND2LIST__V57*/ meltfptr[49] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_APPEND2LIST*/ meltfrout->tabval[13])), (melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                                        }
                                                                                                        ;
                                                                                                        /*_._IFELSE___V56*/ meltfptr[46] = /*_.LIST_APPEND2LIST__V57*/ meltfptr[49];;
                                                                                                        /*epilog*/

                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:302:/ clear");
                                                                                                        /*clear*/ /*_.LIST_APPEND2LIST__V57*/ meltfptr[49] = 0 ;
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
                                                                                                        /*_#IS_MULTIPLE__L29*/ meltfnum[24] =
                                                                                                            (melt_magic_discr((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30])) == MELTOBMAG_MULTIPLE);;
                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:304:/ cond");
                                                                                                        /*cond*/ if (/*_#IS_MULTIPLE__L29*/ meltfnum[24]) /*then*/
                                                                                                            {
                                                                                                                /*^cond.then*/
                                                                                                                /*^block*/
                                                                                                                /*anyblock*/
                                                                                                                {

                                                                                                                    /*citerblock FOREACH_IN_MULTIPLE*/
                                                                                                                    {
                                                                                                                        /* start foreach_in_multiple meltcit2__EACHTUP */
                                                                                                                        long  meltcit2__EACHTUP_ln = melt_multiple_length((melt_ptr_t)/*_.CURCOMP__V34*/ meltfptr[30]);
                                                                                                                        for (/*_#IX__L30*/ meltfnum[19] = 0;
                                                                                                                                           (/*_#IX__L30*/ meltfnum[19] >= 0) && (/*_#IX__L30*/ meltfnum[19] <  meltcit2__EACHTUP_ln);
                                                                                                                                           /*_#IX__L30*/ meltfnum[19]++)
                                                                                                                            {
                                                                                                                                /*_.SUBCOMP__V58*/ meltfptr[52] = melt_multiple_nth((melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]),  /*_#IX__L30*/ meltfnum[19]);




                                                                                                                                {
                                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:308:/ locexp");
                                                                                                                                    meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.SUBCOMP__V58*/ meltfptr[52]));
                                                                                                                                }
                                                                                                                                ;
                                                                                                                                if (/*_#IX__L30*/ meltfnum[19]<0) break;
                                                                                                                            } /* end  foreach_in_multiple meltcit2__EACHTUP */

                                                                                                                        /*citerepilog*/

                                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:305:/ clear");
                                                                                                                        /*clear*/ /*_.SUBCOMP__V58*/ meltfptr[52] = 0 ;
                                                                                                                        /*^clear*/
                                                                                                                        /*clear*/ /*_#IX__L30*/ meltfnum[19] = 0 ;
                                                                                                                    } /*endciterblock FOREACH_IN_MULTIPLE*/
                                                                                                                    ;
                                                                                                                    /*epilog*/
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                        else
                                                                                                            {
                                                                                                                MELT_LOCATION("warmelt-moremacro.melt:304:/ cond.else");

                                                                                                                /*^block*/
                                                                                                                /*anyblock*/
                                                                                                                {


                                                                                                                    {
                                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:310:/ locexp");
                                                                                                                        meltgc_append_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.CURCOMP__V34*/ meltfptr[30]));
                                                                                                                    }
                                                                                                                    ;
                                                                                                                    MELT_LOCATION("warmelt-moremacro.melt:309:/ quasiblock");


                                                                                                                    /*epilog*/
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                        ;
                                                                                                        /*epilog*/

                                                                                                        MELT_LOCATION("warmelt-moremacro.melt:302:/ clear");
                                                                                                        /*clear*/ /*_#IS_MULTIPLE__L29*/ meltfnum[24] = 0 ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                            ;
                                                                                            /*_._IFELSE___V44*/ meltfptr[41] = /*_._IFELSE___V56*/ meltfptr[46];;
                                                                                            /*epilog*/

                                                                                            MELT_LOCATION("warmelt-moremacro.melt:283:/ clear");
                                                                                            /*clear*/ /*_#IS_LIST__L28*/ meltfnum[22] = 0 ;
                                                                                            /*^clear*/
                                                                                            /*clear*/ /*_._IFELSE___V56*/ meltfptr[46] = 0 ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                ;
                                                                                /*_._IFELSE___V41*/ meltfptr[40] = /*_._IFELSE___V44*/ meltfptr[41];;
                                                                                /*epilog*/

                                                                                MELT_LOCATION("warmelt-moremacro.melt:277:/ clear");
                                                                                /*clear*/ /*_#IS_A__L18*/ meltfnum[17] = 0 ;
                                                                                /*^clear*/
                                                                                /*clear*/ /*_._IFELSE___V44*/ meltfptr[41] = 0 ;
                                                                            }
                                                                            ;
                                                                        }
                                                                    ;
                                                                    /*_._IFELSE___V40*/ meltfptr[39] = /*_._IFELSE___V41*/ meltfptr[40];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-moremacro.melt:275:/ clear");
                                                                    /*clear*/ /*_#IS_A__L17*/ meltfnum[16] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_._IFELSE___V41*/ meltfptr[40] = 0 ;
                                                                }
                                                                ;
                                                            }
                                                        ;
                                                        /*_._IFELSE___V39*/ meltfptr[38] = /*_._IFELSE___V40*/ meltfptr[39];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-moremacro.melt:273:/ clear");
                                                        /*clear*/ /*_#IS_A__L16*/ meltfnum[15] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_._IFELSE___V40*/ meltfptr[39] = 0 ;
                                                    }
                                                    ;
                                                }
                                            ;
                                            /*_._IFELSE___V38*/ meltfptr[34] = /*_._IFELSE___V39*/ meltfptr[38];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-moremacro.melt:271:/ clear");
                                            /*clear*/ /*_#IS_STRING__L15*/ meltfnum[14] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_._IFELSE___V39*/ meltfptr[38] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V37*/ meltfptr[35] = /*_._IFELSE___V38*/ meltfptr[34];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:268:/ clear");
                                /*clear*/ /*_#IS_INTEGERBOX__L14*/ meltfnum[9] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V38*/ meltfptr[34] = 0 ;
                            }
                            ;
                        }
                    ;
                } /* end foreach_pair_component_in_list meltcit1__EACHLIST */
            /*_.CURPAIR__V33*/ meltfptr[31] = NULL;
            /*_.CURCOMP__V34*/ meltfptr[30] = NULL;


            /*citerepilog*/

            MELT_LOCATION("warmelt-moremacro.melt:264:/ clear");
            /*clear*/ /*_.CURPAIR__V33*/ meltfptr[31] = 0 ;
            /*^clear*/
            /*clear*/ /*_.CURCOMP__V34*/ meltfptr[30] = 0 ;
            /*^clear*/
            /*clear*/ /*_#NULL__L13*/ meltfnum[7] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V37*/ meltfptr[35] = 0 ;
        } /*endciterblock FOREACH_PAIR_COMPONENT_IN_LIST*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:313:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L31*/ meltfnum[20] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:313:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L31*/ meltfnum[20]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L32*/ meltfnum[21] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:313:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L32*/ meltfnum[21];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 313;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "expand_quoted_sexpr arglist=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.ARGLIST__V30*/ meltfptr[29];
                            /*_.MELT_DEBUG_FUN__V60*/ meltfptr[45] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V59*/ meltfptr[44] = /*_.MELT_DEBUG_FUN__V60*/ meltfptr[45];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:313:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L32*/ meltfnum[21] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V60*/ meltfptr[45] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V59*/ meltfptr[44] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:313:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L31*/ meltfnum[20] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V59*/ meltfptr[44] = 0 ;
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
            MELT_LOCATION("warmelt-moremacro.melt:314:/ locexp");
            meltgc_prepend_list((melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (melt_ptr_t)(/*_.LOCEXP__V28*/ meltfptr[26]));
        }
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:315:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L33*/ meltfnum[18] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:315:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L33*/ meltfnum[18]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L34*/ meltfnum[24] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:315:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L34*/ meltfnum[24];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 315;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "expand_quoted_sexpr final arglist=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.ARGLIST__V30*/ meltfptr[29];
                            /*_.MELT_DEBUG_FUN__V62*/ meltfptr[49] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V61*/ meltfptr[48] = /*_.MELT_DEBUG_FUN__V62*/ meltfptr[49];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:315:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L34*/ meltfnum[24] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V62*/ meltfptr[49] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V61*/ meltfptr[48] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:315:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L33*/ meltfnum[18] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V61*/ meltfptr[48] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:316:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:319:/ apply");
        /*apply*/
        {
            union meltparam_un argtab[1];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &(/*!DISCR_MULTIPLE*/ meltfrout->tabval[17]);
            /*_.LIST_TO_MULTIPLE__V64*/ meltfptr[41] =  melt_apply ((meltclosure_ptr_t)((/*!LIST_TO_MULTIPLE*/ meltfrout->tabval[16])), (melt_ptr_t)(/*_.ARGLIST__V30*/ meltfptr[29]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        MELT_LOCATION("warmelt-moremacro.melt:316:/ quasiblock");


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_APPLY*/ meltfrout->tabval[14])), (4), "CLASS_SOURCE_APPLY");
            /*_.INST__V66*/ meltfptr[39] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[39])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V66*/ meltfptr[39]), (1), (/*_.LOC__V20*/ meltfptr[19]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SAPP_FUN", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[39])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V66*/ meltfptr[39]), (3), ((/*!konst_15_MELT_MAKE_SEXPR*/ meltfrout->tabval[15])), "SAPP_FUN");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SARGOP_ARGS", melt_magic_discr((melt_ptr_t)(/*_.INST__V66*/ meltfptr[39])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V66*/ meltfptr[39]), (2), (/*_.LIST_TO_MULTIPLE__V64*/ meltfptr[41]), "SARGOP_ARGS");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V66*/ meltfptr[39], "newly made instance");
        ;
        /*_.XEXP__V65*/ meltfptr[40] = /*_.INST__V66*/ meltfptr[39];;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:321:/ cppif.then");
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
            /*_#MELT_NEED_DBG__L35*/ meltfnum[22] =
                /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                ;;
            MELT_LOCATION("warmelt-moremacro.melt:321:/ cond");
            /*cond*/ if (/*_#MELT_NEED_DBG__L35*/ meltfnum[22]) /*then*/
                {
                    /*^cond.then*/
                    /*^block*/
                    /*anyblock*/
                    {

                        /*_#MELT_CALLCOUNT__L36*/ meltfnum[17] =
                            /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                            meltcallcount  /* melt_callcount debugging */
#else
                            0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                            ;;

                        MELT_CHECK_SIGNAL();
                        ;
                        MELT_LOCATION("warmelt-moremacro.melt:321:/ apply");
                        /*apply*/
                        {
                            union meltparam_un argtab[5];
                            memset(&argtab, 0, sizeof(argtab));
                            /*^apply.arg*/
                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L36*/ meltfnum[17];
                            /*^apply.arg*/
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 321;
                            /*^apply.arg*/
                            argtab[3].meltbp_cstring =  "expand_quoted_sexpr result xexp=";
                            /*^apply.arg*/
                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.XEXP__V65*/ meltfptr[40];
                            /*_.MELT_DEBUG_FUN__V68*/ meltfptr[34] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[0])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IF___V67*/ meltfptr[38] = /*_.MELT_DEBUG_FUN__V68*/ meltfptr[34];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:321:/ clear");
                        /*clear*/ /*_#MELT_CALLCOUNT__L36*/ meltfnum[17] = 0 ;
                        /*^clear*/
                        /*clear*/ /*_.MELT_DEBUG_FUN__V68*/ meltfptr[34] = 0 ;
                    }
                    ;
                }
            else    /*^cond.else*/
                {

                    /*_._IF___V67*/ meltfptr[38] =  /*reallynil*/ NULL ;;
                }
            ;

            {
                MELT_LOCATION("warmelt-moremacro.melt:321:/ locexp");
                /*void*/(void)0;
            }
            ;
            /*^quasiblock*/


            /*epilog*/

            /*^clear*/
            /*clear*/ /*_#MELT_NEED_DBG__L35*/ meltfnum[22] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IF___V67*/ meltfptr[38] = 0 ;
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
        MELT_LOCATION("warmelt-moremacro.melt:322:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.XEXP__V65*/ meltfptr[40];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:322:/ locexp");
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
        /*_.LET___V63*/ meltfptr[46] = /*_.RETURN___V69*/ meltfptr[45];;

        MELT_LOCATION("warmelt-moremacro.melt:316:/ clear");
        /*clear*/ /*_.LIST_TO_MULTIPLE__V64*/ meltfptr[41] = 0 ;
        /*^clear*/
        /*clear*/ /*_.XEXP__V65*/ meltfptr[40] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V69*/ meltfptr[45] = 0 ;
        /*_.LET___V18*/ meltfptr[16] = /*_.LET___V63*/ meltfptr[46];;

        MELT_LOCATION("warmelt-moremacro.melt:251:/ clear");
        /*clear*/ /*_.CONT__V19*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_#DLINE__L6*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_MIXINT__L7*/ meltfnum[1] = 0 ;
        /*^clear*/
        /*clear*/ /*_.DFILNAM__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_.BOX__V25*/ meltfptr[23] = 0 ;
        /*^clear*/
        /*clear*/ /*_.TUPLE___V26*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOCEXP__V28*/ meltfptr[26] = 0 ;
        /*^clear*/
        /*clear*/ /*_.ARGLIST__V30*/ meltfptr[29] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V63*/ meltfptr[46] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:246:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V18*/ meltfptr[16];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:246:/ locexp");
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
        /*clear*/ /*_.IFCPP___V9*/ meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V12*/ meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V15*/ meltfptr[13] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V18*/ meltfptr[16] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("EXPAND_QUOTED_SEXPR", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR*/






melt_ptr_t MELT_MODULE_VISIBILITY
meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE(meltclosure_ptr_t meltclosp_, melt_ptr_t meltfirstargp_, const melt_argdescr_cell_t meltxargdescr_[], union meltparam_un *meltxargtab_,
        const melt_argdescr_cell_t meltxresdescr_[], union meltparam_un *meltxrestab_)
{
    long current_blocklevel_signals_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE_melt =  melt_blocklevel_signals;

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

    /* start of frame for routine meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE fromline 1752 */

    /** start of frame for meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE of CLASS_PROCROUTINEOBJ from 1555**/

    /*curframdeclclassy*/ class MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE// fromline 1568
        : public Melt_CallFrameWithValues<48>
    {
    public: /* fromline 1572*/
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
        MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE(meltclosure_ptr_t clos) //the closure constructor fromline 1630
            : Melt_CallFrameWithValues<48> (
#if ENABLE_CHECKING /*fromline 1634*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
                sizeof(MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE), clos) {};
        MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE() //the constructor fromline 1642
            : Melt_CallFrameWithValues<48> (
#if ENABLE_CHECKING /*fromline 1646*/
                __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
                sizeof(MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE)) {};
#if ENABLE_CHECKING /*fromline 1654*/
        MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE(const char*fil, int lin) //the constructor fromline 1656
            : Melt_CallFrameWithValues<48> (fil,lin, sizeof(MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE)) {};
        MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE(const char*fil, int lin, meltclosure_ptr_t clos) //the closure constructor fromline 1661
            : Melt_CallFrameWithValues<48> (fil,lin, sizeof(MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE), clos) {};
#endif /* ENABLE_CHECKING fromline 1666*/

    }; // end  class MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE


    /** end of frame for meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE fromline 1697**/

    /* end of frame for routine meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE fromline 1756 */

    /* classy proc frame meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE */ MeltFrame_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyprocarg meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE fromline 1785*/
#if ENABLE_CHECKING
    (__FILE__, __LINE__, meltclosp_) /* fromline 1789*/
#else /*ENABLE_CHECKING */
    (meltclosp_) /* fromline 1793*/
#endif /*ENABLE_CHECKING */

    ;
#define meltframe meltfram__

    melt_trace_start("MEXPAND_QUOTE", meltcallcount);
    /*use arguments*/ (void) meltclosp_;
    (void)meltfirstargp_;
    (void)meltxargdescr_;
    (void)meltxargtab_;
    (void)meltxresdescr_;
    (void)meltxrestab_;
    /*getargs*/

    /*getarg#0*/
    MELT_LOCATION("warmelt-moremacro.melt:327:/ getarg");
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
        MELT_LOCATION("warmelt-moremacro.melt:328:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L1*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[0])));;
            MELT_LOCATION("warmelt-moremacro.melt:328:/ cond");
            /*cond*/ if (/*_#IS_A__L1*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V7*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:328:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 328;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                            /*_.MELT_ASSERT_FAILURE_FUN__V8*/ meltfptr[7] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V7*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V8*/ meltfptr[7];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:328:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V8*/ meltfptr[7] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V6*/ meltfptr[5] = /*_._IFELSE___V7*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:328:/ clear");
            /*clear*/ /*_#IS_A__L1*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V7*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V6*/ meltfptr[5] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:329:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_A__L2*/ meltfnum[0] =
                melt_is_instance_of((melt_ptr_t)(/*_.ENV__V3*/ meltfptr[2]), (melt_ptr_t)((/*!CLASS_ENVIRONMENT*/ meltfrout->tabval[2])));;
            MELT_LOCATION("warmelt-moremacro.melt:329:/ cond");
            /*cond*/ if (/*_#IS_A__L2*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V10*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:329:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 329;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                            /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V10*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:329:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V11*/ meltfptr[10] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V9*/ meltfptr[7] = /*_._IFELSE___V10*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:329:/ clear");
            /*clear*/ /*_#IS_A__L2*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V10*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V9*/ meltfptr[7] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;

#if MELT_HAVE_DEBUG
        MELT_LOCATION("warmelt-moremacro.melt:330:/ cppif.then");
        /*^block*/
        /*anyblock*/
        {


            MELT_CHECK_SIGNAL();
            ;
            /*_#IS_OBJECT__L3*/ meltfnum[0] =
                (melt_magic_discr((melt_ptr_t)(/*_.MODCTX__V5*/ meltfptr[4])) == MELTOBMAG_OBJECT);;
            MELT_LOCATION("warmelt-moremacro.melt:330:/ cond");
            /*cond*/ if (/*_#IS_OBJECT__L3*/ meltfnum[0]) /*then*/
                {
                    /*^cond.then*/
                    /*_._IFELSE___V13*/ meltfptr[6] = (/*nil*/NULL);;
                }
            else
                {
                    MELT_LOCATION("warmelt-moremacro.melt:330:/ cond.else");

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
                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                            /*^apply.arg*/
                            argtab[2].meltbp_long = 330;
                            /*^apply.arg*/
                            argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                            /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_ASSERT_FAILURE_FUN*/ meltfrout->tabval[1])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_CSTRING MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                        }
                        ;
                        /*_._IFELSE___V13*/ meltfptr[6] = /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13];;
                        /*epilog*/

                        MELT_LOCATION("warmelt-moremacro.melt:330:/ clear");
                        /*clear*/ /*_.MELT_ASSERT_FAILURE_FUN__V14*/ meltfptr[13] = 0 ;
                    }
                    ;
                }
            ;
            /*_.IFCPP___V12*/ meltfptr[10] = /*_._IFELSE___V13*/ meltfptr[6];;
            /*epilog*/

            MELT_LOCATION("warmelt-moremacro.melt:330:/ clear");
            /*clear*/ /*_#IS_OBJECT__L3*/ meltfnum[0] = 0 ;
            /*^clear*/
            /*clear*/ /*_._IFELSE___V13*/ meltfptr[6] = 0 ;
        }

#else /*MELT_HAVE_DEBUG*/
        /*^cppif.else*/
        /*_.IFCPP___V12*/ meltfptr[10] = (/*nil*/NULL);
#endif /*MELT_HAVE_DEBUG*/
        ;
        MELT_LOCATION("warmelt-moremacro.melt:331:/ quasiblock");


        /*^getslot*/
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 2, "SEXP_CONTENTS");
            /*_.CONT__V16*/ meltfptr[6] = slot;
        };
        ;
        MELT_LOCATION("warmelt-moremacro.melt:332:/ getslot");
        {
            melt_ptr_t slot=NULL, obj=NULL;
            obj = (melt_ptr_t)(/*_.SEXPR__V2*/ meltfptr[1]) /*=obj*/;
            melt_object_get_field(slot,obj, 1, "LOCA_LOCATION");
            /*_.LOC__V17*/ meltfptr[16] = slot;
        };
        ;
        /*_.LIST_FIRST__V18*/ meltfptr[17] =
            (melt_list_first((melt_ptr_t)(/*_.CONT__V16*/ meltfptr[6])));;
        /*^compute*/
        /*_.CURPAIR__V19*/ meltfptr[18] =
            (melt_pair_tail((melt_ptr_t)(/*_.LIST_FIRST__V18*/ meltfptr[17])));;
        /*^compute*/
        /*_.QUOTED__V20*/ meltfptr[19] =
            (melt_pair_head((melt_ptr_t)(/*_.CURPAIR__V19*/ meltfptr[18])));;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_.PAIR_TAIL__V21*/ meltfptr[20] =
            (melt_pair_tail((melt_ptr_t)(/*_.CURPAIR__V19*/ meltfptr[18])));;
        MELT_LOCATION("warmelt-moremacro.melt:336:/ cond");
        /*cond*/ if (/*_.PAIR_TAIL__V21*/ meltfptr[20]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-moremacro.melt:337:/ apply");
                    /*apply*/
                    {
                        union meltparam_un argtab[3];
                        memset(&argtab, 0, sizeof(argtab));
                        /*^apply.arg*/
                        argtab[0].meltbp_cstring =  "QUOTE should have only one argument but is $1 in sexpr $2";
                        /*^apply.arg*/
                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.CONT__V16*/ meltfptr[6];
                        /*^apply.arg*/
                        argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.SEXPR__V2*/ meltfptr[1];
                        /*_.ERROR_AT__V23*/ meltfptr[22] =  melt_apply ((meltclosure_ptr_t)((/*!ERROR_AT*/ meltfrout->tabval[3])), (melt_ptr_t)(/*_.LOC__V17*/ meltfptr[16]), (MELTBPARSTR_CSTRING MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                    }
                    ;
                    /*_._IF___V22*/ meltfptr[21] = /*_.ERROR_AT__V23*/ meltfptr[22];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:336:/ clear");
                    /*clear*/ /*_.ERROR_AT__V23*/ meltfptr[22] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V22*/ meltfptr[21] =  /*reallynil*/ NULL ;;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*^compute*/
        /*_#IS_A__L4*/ meltfnum[0] =
            melt_is_instance_of((melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19]), (melt_ptr_t)((/*!CLASS_SYMBOL*/ meltfrout->tabval[4])));;
        MELT_LOCATION("warmelt-moremacro.melt:338:/ cond");
        /*cond*/ if (/*_#IS_A__L4*/ meltfnum[0]) /*then*/
            {
                /*^cond.then*/
                /*_._IFELSE___V24*/ meltfptr[22] = (/*nil*/NULL);;
            }
        else
            {
                MELT_LOCATION("warmelt-moremacro.melt:338:/ cond.else");

                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    /*_#IS_STRING__L5*/ meltfnum[4] =
                        (melt_magic_discr((melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19])) == MELTOBMAG_STRING);;
                    MELT_LOCATION("warmelt-moremacro.melt:341:/ cond");
                    /*cond*/ if (/*_#IS_STRING__L5*/ meltfnum[4]) /*then*/
                        {
                            /*^cond.then*/
                            /*_._IFELSE___V25*/ meltfptr[24] = (/*nil*/NULL);;
                        }
                    else
                        {
                            MELT_LOCATION("warmelt-moremacro.melt:341:/ cond.else");

                            /*^block*/
                            /*anyblock*/
                            {


                                MELT_CHECK_SIGNAL();
                                ;
                                /*_#IS_INTEGERBOX__L6*/ meltfnum[5] =
                                    (melt_magic_discr((melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19])) == MELTOBMAG_INT);;
                                MELT_LOCATION("warmelt-moremacro.melt:344:/ cond");
                                /*cond*/ if (/*_#IS_INTEGERBOX__L6*/ meltfnum[5]) /*then*/
                                    {
                                        /*^cond.then*/
                                        /*_._IFELSE___V26*/ meltfptr[25] = (/*nil*/NULL);;
                                    }
                                else
                                    {
                                        MELT_LOCATION("warmelt-moremacro.melt:344:/ cond.else");

                                        /*^block*/
                                        /*anyblock*/
                                        {


                                            MELT_CHECK_SIGNAL();
                                            ;
                                            /*_#IS_A__L7*/ meltfnum[6] =
                                                melt_is_instance_of((melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19]), (melt_ptr_t)((/*!CLASS_SOURCE*/ meltfrout->tabval[5])));;
                                            MELT_LOCATION("warmelt-moremacro.melt:347:/ cond");
                                            /*cond*/ if (/*_#IS_A__L7*/ meltfnum[6]) /*then*/
                                                {
                                                    /*^cond.then*/
                                                    /*^block*/
                                                    /*anyblock*/
                                                    {


#if MELT_HAVE_DEBUG
                                                        MELT_LOCATION("warmelt-moremacro.melt:348:/ cppif.then");
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
                                                            MELT_LOCATION("warmelt-moremacro.melt:348:/ cond");
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
                                                                        MELT_LOCATION("warmelt-moremacro.melt:348:/ apply");
                                                                        /*apply*/
                                                                        {
                                                                            union meltparam_un argtab[5];
                                                                            memset(&argtab, 0, sizeof(argtab));
                                                                            /*^apply.arg*/
                                                                            argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L9*/ meltfnum[8];
                                                                            /*^apply.arg*/
                                                                            argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                            /*^apply.arg*/
                                                                            argtab[2].meltbp_long = 348;
                                                                            /*^apply.arg*/
                                                                            argtab[3].meltbp_cstring =  "mexpand_quote sexpr return source=";
                                                                            /*^apply.arg*/
                                                                            argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.QUOTED__V20*/ meltfptr[19];
                                                                            /*_.MELT_DEBUG_FUN__V29*/ meltfptr[28] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[6])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                        }
                                                                        ;
                                                                        /*_._IF___V28*/ meltfptr[27] = /*_.MELT_DEBUG_FUN__V29*/ meltfptr[28];;
                                                                        /*epilog*/

                                                                        MELT_LOCATION("warmelt-moremacro.melt:348:/ clear");
                                                                        /*clear*/ /*_#MELT_CALLCOUNT__L9*/ meltfnum[8] = 0 ;
                                                                        /*^clear*/
                                                                        /*clear*/ /*_.MELT_DEBUG_FUN__V29*/ meltfptr[28] = 0 ;
                                                                    }
                                                                    ;
                                                                }
                                                            else    /*^cond.else*/
                                                                {

                                                                    /*_._IF___V28*/ meltfptr[27] =  /*reallynil*/ NULL ;;
                                                                }
                                                            ;

                                                            {
                                                                MELT_LOCATION("warmelt-moremacro.melt:348:/ locexp");
                                                                /*void*/(void)0;
                                                            }
                                                            ;
                                                            /*^quasiblock*/


                                                            /*epilog*/

                                                            /*^clear*/
                                                            /*clear*/ /*_#MELT_NEED_DBG__L8*/ meltfnum[7] = 0 ;
                                                            /*^clear*/
                                                            /*clear*/ /*_._IF___V28*/ meltfptr[27] = 0 ;
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
                                                        MELT_LOCATION("warmelt-moremacro.melt:349:/ quasiblock");


                                                        /*_._RETVAL___V1*/ meltfptr[0] = /*_.QUOTED__V20*/ meltfptr[19];;

                                                        {
                                                            MELT_LOCATION("warmelt-moremacro.melt:349:/ locexp");
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
                                                        MELT_LOCATION("warmelt-moremacro.melt:347:/ quasiblock");


                                                        /*_.PROGN___V31*/ meltfptr[27] = /*_.RETURN___V30*/ meltfptr[28];;
                                                        /*^compute*/
                                                        /*_._IFELSE___V27*/ meltfptr[26] = /*_.PROGN___V31*/ meltfptr[27];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-moremacro.melt:347:/ clear");
                                                        /*clear*/ /*_.RETURN___V30*/ meltfptr[28] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_.PROGN___V31*/ meltfptr[27] = 0 ;
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
                                                        /*_#IS_A__L10*/ meltfnum[8] =
                                                            melt_is_instance_of((melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19]), (melt_ptr_t)((/*!CLASS_SEXPR*/ meltfrout->tabval[0])));;
                                                        MELT_LOCATION("warmelt-moremacro.melt:350:/ cond");
                                                        /*cond*/ if (/*_#IS_A__L10*/ meltfnum[8]) /*then*/
                                                            {
                                                                /*^cond.then*/
                                                                /*^block*/
                                                                /*anyblock*/
                                                                {


#if MELT_HAVE_DEBUG
                                                                    MELT_LOCATION("warmelt-moremacro.melt:351:/ cppif.then");
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
                                                                        /*_#MELT_NEED_DBG__L11*/ meltfnum[7] =
                                                                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                                                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                                                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                                                            ;;
                                                                        MELT_LOCATION("warmelt-moremacro.melt:351:/ cond");
                                                                        /*cond*/ if (/*_#MELT_NEED_DBG__L11*/ meltfnum[7]) /*then*/
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
                                                                                    MELT_LOCATION("warmelt-moremacro.melt:351:/ apply");
                                                                                    /*apply*/
                                                                                    {
                                                                                        union meltparam_un argtab[5];
                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                        /*^apply.arg*/
                                                                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L12*/ meltfnum[11];
                                                                                        /*^apply.arg*/
                                                                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                                        /*^apply.arg*/
                                                                                        argtab[2].meltbp_long = 351;
                                                                                        /*^apply.arg*/
                                                                                        argtab[3].meltbp_cstring =  "mexpand_quote sexpr quoted=";
                                                                                        /*^apply.arg*/
                                                                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.QUOTED__V20*/ meltfptr[19];
                                                                                        /*_.MELT_DEBUG_FUN__V34*/ meltfptr[33] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[6])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                    }
                                                                                    ;
                                                                                    /*_._IF___V33*/ meltfptr[27] = /*_.MELT_DEBUG_FUN__V34*/ meltfptr[33];;
                                                                                    /*epilog*/

                                                                                    MELT_LOCATION("warmelt-moremacro.melt:351:/ clear");
                                                                                    /*clear*/ /*_#MELT_CALLCOUNT__L12*/ meltfnum[11] = 0 ;
                                                                                    /*^clear*/
                                                                                    /*clear*/ /*_.MELT_DEBUG_FUN__V34*/ meltfptr[33] = 0 ;
                                                                                }
                                                                                ;
                                                                            }
                                                                        else    /*^cond.else*/
                                                                            {

                                                                                /*_._IF___V33*/ meltfptr[27] =  /*reallynil*/ NULL ;;
                                                                            }
                                                                        ;

                                                                        {
                                                                            MELT_LOCATION("warmelt-moremacro.melt:351:/ locexp");
                                                                            /*void*/(void)0;
                                                                        }
                                                                        ;
                                                                        /*^quasiblock*/


                                                                        /*epilog*/

                                                                        /*^clear*/
                                                                        /*clear*/ /*_#MELT_NEED_DBG__L11*/ meltfnum[7] = 0 ;
                                                                        /*^clear*/
                                                                        /*clear*/ /*_._IF___V33*/ meltfptr[27] = 0 ;
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
                                                                    MELT_LOCATION("warmelt-moremacro.melt:352:/ quasiblock");



                                                                    MELT_CHECK_SIGNAL();
                                                                    ;
                                                                    /*^apply*/
                                                                    /*apply*/
                                                                    {
                                                                        union meltparam_un argtab[4];
                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                        /*^apply.arg*/
                                                                        argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_.ENV__V3*/ meltfptr[2];
                                                                        /*^apply.arg*/
                                                                        argtab[1].meltbp_aptr = /*nil*/(melt_ptr_t*)NULL;
                                                                        /*^apply.arg*/
                                                                        argtab[2].meltbp_aptr = (melt_ptr_t*) &/*_.MEXPANDER__V4*/ meltfptr[3];
                                                                        /*^apply.arg*/
                                                                        argtab[3].meltbp_aptr = (melt_ptr_t*) &/*_.MODCTX__V5*/ meltfptr[4];
                                                                        /*_.EXPQUO__V36*/ meltfptr[27] =  melt_apply ((meltclosure_ptr_t)((/*!EXPAND_QUOTED_SEXPR*/ meltfrout->tabval[7])), (melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19]), (MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                    }
                                                                    ;

#if MELT_HAVE_DEBUG
                                                                    MELT_LOCATION("warmelt-moremacro.melt:354:/ cppif.then");
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
                                                                        /*_#MELT_NEED_DBG__L13*/ meltfnum[11] =
                                                                            /*MELT_NEED_DBG*/
#if MELT_HAVE_DEBUG
                                                                            (/*melt_need_dbg*/ melt_need_debug ((int) 0))
#else
                                                                            0 /* no melt_need_dbg */
#endif /*MELT_HAVE_DEBUG*/
                                                                            ;;
                                                                        MELT_LOCATION("warmelt-moremacro.melt:354:/ cond");
                                                                        /*cond*/ if (/*_#MELT_NEED_DBG__L13*/ meltfnum[11]) /*then*/
                                                                            {
                                                                                /*^cond.then*/
                                                                                /*^block*/
                                                                                /*anyblock*/
                                                                                {

                                                                                    /*_#MELT_CALLCOUNT__L14*/ meltfnum[7] =
                                                                                        /* for melt_callcount */
#if MELT_HAVE_DEBUG && defined (meltcallcount)
                                                                                        meltcallcount  /* melt_callcount debugging */
#else
                                                                                        0L  /* melt_callcount without debug */
#endif /* MELT_HAVE_DEBUG melt_callcount */
                                                                                        ;;

                                                                                    MELT_CHECK_SIGNAL();
                                                                                    ;
                                                                                    MELT_LOCATION("warmelt-moremacro.melt:354:/ apply");
                                                                                    /*apply*/
                                                                                    {
                                                                                        union meltparam_un argtab[5];
                                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                                        /*^apply.arg*/
                                                                                        argtab[0].meltbp_long = /*_#MELT_CALLCOUNT__L14*/ meltfnum[7];
                                                                                        /*^apply.arg*/
                                                                                        argtab[1].meltbp_cstring =  "warmelt-moremacro.melt";
                                                                                        /*^apply.arg*/
                                                                                        argtab[2].meltbp_long = 354;
                                                                                        /*^apply.arg*/
                                                                                        argtab[3].meltbp_cstring =  "mexpander expquo=";
                                                                                        /*^apply.arg*/
                                                                                        argtab[4].meltbp_aptr = (melt_ptr_t*) &/*_.EXPQUO__V36*/ meltfptr[27];
                                                                                        /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37] =  melt_apply ((meltclosure_ptr_t)((/*!MELT_DEBUG_FUN*/ meltfrout->tabval[6])), (melt_ptr_t)((/*nil*/NULL)), (MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_LONG MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                                    }
                                                                                    ;
                                                                                    /*_._IF___V37*/ meltfptr[36] = /*_.MELT_DEBUG_FUN__V38*/ meltfptr[37];;
                                                                                    /*epilog*/

                                                                                    MELT_LOCATION("warmelt-moremacro.melt:354:/ clear");
                                                                                    /*clear*/ /*_#MELT_CALLCOUNT__L14*/ meltfnum[7] = 0 ;
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
                                                                            MELT_LOCATION("warmelt-moremacro.melt:354:/ locexp");
                                                                            /*void*/(void)0;
                                                                        }
                                                                        ;
                                                                        /*^quasiblock*/


                                                                        /*epilog*/

                                                                        /*^clear*/
                                                                        /*clear*/ /*_#MELT_NEED_DBG__L13*/ meltfnum[11] = 0 ;
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
                                                                    MELT_LOCATION("warmelt-moremacro.melt:355:/ quasiblock");


                                                                    /*_._RETVAL___V1*/ meltfptr[0] = /*_.EXPQUO__V36*/ meltfptr[27];;

                                                                    {
                                                                        MELT_LOCATION("warmelt-moremacro.melt:355:/ locexp");
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
                                                                    /*_.LET___V35*/ meltfptr[33] = /*_.RETURN___V39*/ meltfptr[37];;

                                                                    MELT_LOCATION("warmelt-moremacro.melt:352:/ clear");
                                                                    /*clear*/ /*_.EXPQUO__V36*/ meltfptr[27] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.RETURN___V39*/ meltfptr[37] = 0 ;
                                                                    MELT_LOCATION("warmelt-moremacro.melt:350:/ quasiblock");


                                                                    /*_.PROGN___V40*/ meltfptr[36] = /*_.LET___V35*/ meltfptr[33];;
                                                                    /*^compute*/
                                                                    /*_._IFELSE___V32*/ meltfptr[28] = /*_.PROGN___V40*/ meltfptr[36];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-moremacro.melt:350:/ clear");
                                                                    /*clear*/ /*_.LET___V35*/ meltfptr[33] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.PROGN___V40*/ meltfptr[36] = 0 ;
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
                                                                    MELT_LOCATION("warmelt-moremacro.melt:357:/ apply");
                                                                    /*apply*/
                                                                    {
                                                                        union meltparam_un argtab[2];
                                                                        memset(&argtab, 0, sizeof(argtab));
                                                                        /*^apply.arg*/
                                                                        argtab[0].meltbp_cstring =  "QUOTE should have a symbol, string, or integer or s-expr argument bit\
 is $1";
                                                                        /*^apply.arg*/
                                                                        argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_.CONT__V16*/ meltfptr[6];
                                                                        /*_.ERROR_AT__V41*/ meltfptr[27] =  melt_apply ((meltclosure_ptr_t)((/*!ERROR_AT*/ meltfrout->tabval[3])), (melt_ptr_t)(/*_.LOC__V17*/ meltfptr[16]), (MELTBPARSTR_CSTRING MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
                                                                    }
                                                                    ;
                                                                    MELT_LOCATION("warmelt-moremacro.melt:356:/ quasiblock");


                                                                    /*_.PROGN___V42*/ meltfptr[37] = /*_.ERROR_AT__V41*/ meltfptr[27];;
                                                                    /*^compute*/
                                                                    /*_._IFELSE___V32*/ meltfptr[28] = /*_.PROGN___V42*/ meltfptr[37];;
                                                                    /*epilog*/

                                                                    MELT_LOCATION("warmelt-moremacro.melt:350:/ clear");
                                                                    /*clear*/ /*_.ERROR_AT__V41*/ meltfptr[27] = 0 ;
                                                                    /*^clear*/
                                                                    /*clear*/ /*_.PROGN___V42*/ meltfptr[37] = 0 ;
                                                                }
                                                                ;
                                                            }
                                                        ;
                                                        /*_._IFELSE___V27*/ meltfptr[26] = /*_._IFELSE___V32*/ meltfptr[28];;
                                                        /*epilog*/

                                                        MELT_LOCATION("warmelt-moremacro.melt:347:/ clear");
                                                        /*clear*/ /*_#IS_A__L10*/ meltfnum[8] = 0 ;
                                                        /*^clear*/
                                                        /*clear*/ /*_._IFELSE___V32*/ meltfptr[28] = 0 ;
                                                    }
                                                    ;
                                                }
                                            ;
                                            /*_._IFELSE___V26*/ meltfptr[25] = /*_._IFELSE___V27*/ meltfptr[26];;
                                            /*epilog*/

                                            MELT_LOCATION("warmelt-moremacro.melt:344:/ clear");
                                            /*clear*/ /*_#IS_A__L7*/ meltfnum[6] = 0 ;
                                            /*^clear*/
                                            /*clear*/ /*_._IFELSE___V27*/ meltfptr[26] = 0 ;
                                        }
                                        ;
                                    }
                                ;
                                /*_._IFELSE___V25*/ meltfptr[24] = /*_._IFELSE___V26*/ meltfptr[25];;
                                /*epilog*/

                                MELT_LOCATION("warmelt-moremacro.melt:341:/ clear");
                                /*clear*/ /*_#IS_INTEGERBOX__L6*/ meltfnum[5] = 0 ;
                                /*^clear*/
                                /*clear*/ /*_._IFELSE___V26*/ meltfptr[25] = 0 ;
                            }
                            ;
                        }
                    ;
                    /*_._IFELSE___V24*/ meltfptr[22] = /*_._IFELSE___V25*/ meltfptr[24];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:338:/ clear");
                    /*clear*/ /*_#IS_STRING__L5*/ meltfnum[4] = 0 ;
                    /*^clear*/
                    /*clear*/ /*_._IFELSE___V25*/ meltfptr[24] = 0 ;
                }
                ;
            }
        ;

        MELT_CHECK_SIGNAL();
        ;
        /*_#IS_A__L15*/ meltfnum[7] =
            melt_is_instance_of((melt_ptr_t)(/*_.QUOTED__V20*/ meltfptr[19]), (melt_ptr_t)((/*!CLASS_KEYWORD*/ meltfrout->tabval[8])));;
        MELT_LOCATION("warmelt-moremacro.melt:359:/ cond");
        /*cond*/ if (/*_#IS_A__L15*/ meltfnum[7]) /*then*/
            {
                /*^cond.then*/
                /*^block*/
                /*anyblock*/
                {


                    MELT_CHECK_SIGNAL();
                    ;
                    MELT_LOCATION("warmelt-moremacro.melt:360:/ quasiblock");


                    /*_._RETVAL___V1*/ meltfptr[0] = /*_.QUOTED__V20*/ meltfptr[19];;

                    {
                        MELT_LOCATION("warmelt-moremacro.melt:360:/ locexp");
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
                    /*_._IF___V43*/ meltfptr[33] = /*_.RETURN___V44*/ meltfptr[36];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:359:/ clear");
                    /*clear*/ /*_.RETURN___V44*/ meltfptr[36] = 0 ;
                }
                ;
            }
        else    /*^cond.else*/
            {

                /*_._IF___V43*/ meltfptr[33] =  /*reallynil*/ NULL ;;
            }
        ;
        MELT_LOCATION("warmelt-moremacro.melt:361:/ quasiblock");



        MELT_CHECK_SIGNAL();
        ;
        /*^quasiblock*/


        /*^rawallocobj*/
        /*rawallocobj*/
        {
            melt_ptr_t newobj = 0;
            melt_raw_object_create(newobj,(melt_ptr_t)((/*!CLASS_SOURCE_QUOTE*/ meltfrout->tabval[9])), (3), "CLASS_SOURCE_QUOTE");
            /*_.INST__V47*/ meltfptr[28] =
                newobj;
        };
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @LOCA_LOCATION", melt_magic_discr((melt_ptr_t)(/*_.INST__V47*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V47*/ meltfptr[28]), (1), (/*_.LOC__V17*/ meltfptr[16]), "LOCA_LOCATION");
        ;
        /*^putslot*/
        /*putslot*/
        melt_assertmsg("checkobj putslot  _ @SQUOTED", melt_magic_discr((melt_ptr_t)(/*_.INST__V47*/ meltfptr[28])) == MELTOBMAG_OBJECT);
        melt_putfield_object((/*_.INST__V47*/ meltfptr[28]), (2), (/*_.QUOTED__V20*/ meltfptr[19]), "SQUOTED");
        ;
        /*^touchobj*/

        melt_dbgtrace_written_object (/*_.INST__V47*/ meltfptr[28], "newly made instance");
        ;
        /*_.SQU__V46*/ meltfptr[37] = /*_.INST__V47*/ meltfptr[28];;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:364:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.SQU__V46*/ meltfptr[37];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:364:/ locexp");
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
        /*_.LET___V45*/ meltfptr[27] = /*_.RETURN___V48*/ meltfptr[26];;

        MELT_LOCATION("warmelt-moremacro.melt:361:/ clear");
        /*clear*/ /*_.SQU__V46*/ meltfptr[37] = 0 ;
        /*^clear*/
        /*clear*/ /*_.RETURN___V48*/ meltfptr[26] = 0 ;
        /*_.LET___V15*/ meltfptr[13] = /*_.LET___V45*/ meltfptr[27];;

        MELT_LOCATION("warmelt-moremacro.melt:331:/ clear");
        /*clear*/ /*_.CONT__V16*/ meltfptr[6] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LOC__V17*/ meltfptr[16] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LIST_FIRST__V18*/ meltfptr[17] = 0 ;
        /*^clear*/
        /*clear*/ /*_.CURPAIR__V19*/ meltfptr[18] = 0 ;
        /*^clear*/
        /*clear*/ /*_.QUOTED__V20*/ meltfptr[19] = 0 ;
        /*^clear*/
        /*clear*/ /*_.PAIR_TAIL__V21*/ meltfptr[20] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V22*/ meltfptr[21] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L4*/ meltfnum[0] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IFELSE___V24*/ meltfptr[22] = 0 ;
        /*^clear*/
        /*clear*/ /*_#IS_A__L15*/ meltfnum[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_._IF___V43*/ meltfptr[33] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V45*/ meltfptr[27] = 0 ;

        MELT_CHECK_SIGNAL();
        ;
        MELT_LOCATION("warmelt-moremacro.melt:327:/ quasiblock");


        /*_._RETVAL___V1*/ meltfptr[0] = /*_.LET___V15*/ meltfptr[13];;

        {
            MELT_LOCATION("warmelt-moremacro.melt:327:/ locexp");
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
        /*clear*/ /*_.IFCPP___V6*/ meltfptr[5] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V9*/ meltfptr[7] = 0 ;
        /*^clear*/
        /*clear*/ /*_.IFCPP___V12*/ meltfptr[10] = 0 ;
        /*^clear*/
        /*clear*/ /*_.LET___V15*/ meltfptr[13] = 0 ;
    }

    ;
    goto meltlabend_rout;
meltlabend_rout:
    melt_trace_end("MEXPAND_QUOTE", meltcallcount);
    melt_blocklevel_signals = current_blocklevel_signals_meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE_melt;
    return (melt_ptr_t)(/*_._RETVAL___V1*/ meltfptr[0]);
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /*end meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE*/




/*no syntax testing generated*/


const char melt_module_is_gpl_compatible[]= "warmelt-moremacro: GPLv3+";

/* the frame for initial routine */
/** start of frame for melt_start_this_module of CLASS_INITIAL_MODULE_ROUTINEOBJ from 1555**/

/*curframdeclclassy*/ class Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074// fromline 1568
    : public Melt_CallFrameWithValues<140>
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
    Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074(meltclosure_ptr_t clos) //the closure constructor fromline 1630
        : Melt_CallFrameWithValues<140> (
#if ENABLE_CHECKING /*fromline 1634*/
            __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1638*/
            sizeof(Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074), clos) {};
    Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074() //the constructor fromline 1642
        : Melt_CallFrameWithValues<140> (
#if ENABLE_CHECKING /*fromline 1646*/
            __FILE__, __LINE__,
#endif /* ENABLE_CHECKING fromline 1650*/
            sizeof(Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074)) {};
#if ENABLE_CHECKING /*fromline 1654*/
    Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074(const char*fil, int lin) //the constructor fromline 1656
        : Melt_CallFrameWithValues<140> (fil,lin, sizeof(Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074)) {};
#endif /* ENABLE_CHECKING fromline 1666*/

}; // end  class Melt_InitialClassyFrame_WARMELTmiMOREMACRO_h503082074


/** end of frame for melt_start_this_module fromline 1697**/



static void melt_initialize_module_meltdata_WARMELTmiMOREMACRO (meltinitial_frame_t *iniframp__, char meltpredefinited[])
{
#define meltfram__  (*iniframp__)

    /* curframe_cdat_struct */ struct meltcdata_st
    {
        void* meltcdata_inigap[2]; /* could help debugging */

        struct MELT_OBJECT_STRUCT(3) dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER;
        struct MELT_STRING_STRUCT(38) dstr_2__HOOK_FRESH_ENVIRONMENT_R;
        struct MELT_ROUTINE_STRUCT(14) drout_3__EACH_COMPONENT_IN_LIST;
        struct MELT_CLOSURE_STRUCT(0) dclo_4__EACH_COMPONENT_IN_LIST;
        struct MELT_OBJECT_STRUCT(3) dsym_5__MELT_DEBUG_FUN;
        struct MELT_STRING_STRUCT(14) dstr_6__MELT_DEBUG_FUN;
        struct MELT_OBJECT_STRUCT(3) dsym_7__DEBUG_LESS;
        struct MELT_STRING_STRUCT(10) dstr_8__DEBUG_LESS;
        struct MELT_OBJECT_STRUCT(3) dsym_9__CLASS_LOCATED;
        struct MELT_STRING_STRUCT(13) dstr_10__CLASS_LOCATED;
        struct MELT_OBJECT_STRUCT(3) dsym_11__CLASS_SEXPR;
        struct MELT_STRING_STRUCT(11) dstr_12__CLASS_SEXPR;
        struct MELT_OBJECT_STRUCT(3) dsym_13__MELT_ASSERT_FAILURE_FUN;
        struct MELT_STRING_STRUCT(23) dstr_14__MELT_ASSERT_FAILURE_FUN;
        struct MELT_OBJECT_STRUCT(3) dsym_15__LIST_TO_MULTIPLE;
        struct MELT_STRING_STRUCT(16) dstr_16__LIST_TO_MULTIPLE;
        struct MELT_OBJECT_STRUCT(3) dsym_17__DISCR_MULTIPLE;
        struct MELT_STRING_STRUCT(14) dstr_18__DISCR_MULTIPLE;
        struct MELT_OBJECT_STRUCT(3) dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE;
        struct MELT_STRING_STRUCT(27) dstr_20__EXPAND_TUPLE_SLICE_AS_TU;
        struct MELT_OBJECT_STRUCT(3) dsym_21__CLASS_SYMBOL;
        struct MELT_STRING_STRUCT(12) dstr_22__CLASS_SYMBOL;
        struct MELT_OBJECT_STRUCT(3) dsym_23__CLONE_SYMBOL;
        struct MELT_STRING_STRUCT(12) dstr_24__CLONE_SYMBOL;
        struct MELT_OBJECT_STRUCT(3) dsym_25__CURPAIRINLISTSYMB;
        struct MELT_STRING_STRUCT(17) dstr_26__CURPAIRINLISTSYMB;
        struct MELT_OBJECT_STRUCT(3) dsym_27__MELT_MAKE_SEXPR;
        struct MELT_STRING_STRUCT(15) dstr_28__MELT_MAKE_SEXPR;
        struct MELT_OBJECT_STRUCT(3) dsym_29__HOOK_MELT_MAKE_LOCATION;
        struct MELT_STRING_STRUCT(23) dstr_30__HOOK_MELT_MAKE_LOCATION;
        struct MELT_OBJECT_STRUCT(3) dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST;
        struct MELT_STRING_STRUCT(30) dstr_32__FOREACH_PAIR_COMPONENT_I;
        struct MELT_OBJECT_STRUCT(3) dsym_33__EACH_COMPONENT_IN_LIST;
        struct MELT_STRING_STRUCT(22) dstr_34__EACH_COMPONENT_IN_LIST;
        struct MELT_ROUTINE_STRUCT(2) drout_35__FILTERGCCVERSION;
        struct MELT_CLOSURE_STRUCT(0) dclo_36__FILTERGCCVERSION;
        struct MELT_ROUTINE_STRUCT(8) drout_37__MEXPAND_GCCIF;
        struct MELT_CLOSURE_STRUCT(0) dclo_38__MEXPAND_GCCIF;
        struct MELT_OBJECT_STRUCT(3) dsym_39__CLASS_ENVIRONMENT;
        struct MELT_STRING_STRUCT(17) dstr_40__CLASS_ENVIRONMENT;
        struct MELT_OBJECT_STRUCT(3) dsym_41__EXPAND_PAIRLIST_AS_LIST;
        struct MELT_STRING_STRUCT(23) dstr_42__EXPAND_PAIRLIST_AS_LIST;
        struct MELT_OBJECT_STRUCT(3) dsym_43__TRUE;
        struct MELT_STRING_STRUCT(4) dstr_44__TRUE;
        struct MELT_OBJECT_STRUCT(3) dsym_45__INSTALL_INITIAL_MACRO;
        struct MELT_STRING_STRUCT(21) dstr_46__INSTALL_INITIAL_MACRO;
        struct MELT_OBJECT_STRUCT(3) dsym_47__GCCIF;
        struct MELT_STRING_STRUCT(5) dstr_48__GCCIF;
        struct MELT_ROUTINE_STRUCT(5) drout_49__MEXPANDOBSOLETE_CONTAINER;
        struct MELT_CLOSURE_STRUCT(0) dclo_50__MEXPANDOBSOLETE_CONTAINER;
        struct MELT_OBJECT_STRUCT(3) dsym_51__MEXPAND_REFERENCE;
        struct MELT_STRING_STRUCT(17) dstr_52__MEXPAND_REFERENCE;
        struct MELT_ROUTINE_STRUCT(5) drout_53__PATEXPANDOBSOLETE_CONTAINER;
        struct MELT_CLOSURE_STRUCT(0) dclo_54__PATEXPANDOBSOLETE_CONTAINER;
        struct MELT_OBJECT_STRUCT(3) dsym_55__PATEXPAND_REFERENCE;
        struct MELT_STRING_STRUCT(19) dstr_56__PATEXPAND_REFERENCE;
        struct MELT_OBJECT_STRUCT(3) dsym_57__INSTALL_INITIAL_PATMACRO;
        struct MELT_STRING_STRUCT(24) dstr_58__INSTALL_INITIAL_PATMACRO;
        struct MELT_OBJECT_STRUCT(3) dsym_59__CONTAINER;
        struct MELT_STRING_STRUCT(9) dstr_60__CONTAINER;
        struct MELT_ROUTINE_STRUCT(18) drout_61__EXPAND_QUOTED_SEXPR;
        struct MELT_CLOSURE_STRUCT(0) dclo_62__EXPAND_QUOTED_SEXPR;
        struct MELT_OBJECT_STRUCT(3) dsym_63__CLASS_SOURCE_HOOK_CALL;
        struct MELT_STRING_STRUCT(22) dstr_64__CLASS_SOURCE_HOOK_CALL;
        struct MELT_OBJECT_STRUCT(3) dsym_65__DISCR_LIST;
        struct MELT_STRING_STRUCT(10) dstr_66__DISCR_LIST;
        struct MELT_OBJECT_STRUCT(3) dsym_67__CLASS_KEYWORD;
        struct MELT_STRING_STRUCT(13) dstr_68__CLASS_KEYWORD;
        struct MELT_OBJECT_STRUCT(3) dsym_69__CLASS_SOURCE_QUOTE;
        struct MELT_STRING_STRUCT(18) dstr_70__CLASS_SOURCE_QUOTE;
        struct MELT_OBJECT_STRUCT(3) dsym_71__COMMA;
        struct MELT_STRING_STRUCT(5) dstr_72__COMMA;
        struct MELT_OBJECT_STRUCT(3) dsym_73__LIST_NTH_ELEMENT;
        struct MELT_STRING_STRUCT(16) dstr_74__LIST_NTH_ELEMENT;
        struct MELT_OBJECT_STRUCT(3) dsym_75__LIST_APPEND2LIST;
        struct MELT_STRING_STRUCT(16) dstr_76__LIST_APPEND2LIST;
        struct MELT_OBJECT_STRUCT(3) dsym_77__CLASS_SOURCE_APPLY;
        struct MELT_STRING_STRUCT(18) dstr_78__CLASS_SOURCE_APPLY;
        struct MELT_ROUTINE_STRUCT(10) drout_79__MEXPAND_QUOTE;
        struct MELT_CLOSURE_STRUCT(0) dclo_80__MEXPAND_QUOTE;
        struct MELT_OBJECT_STRUCT(3) dsym_81__ERROR_AT;
        struct MELT_STRING_STRUCT(8) dstr_82__ERROR_AT;
        struct MELT_OBJECT_STRUCT(3) dsym_83__CLASS_SOURCE;
        struct MELT_STRING_STRUCT(12) dstr_84__CLASS_SOURCE;
        struct MELT_OBJECT_STRUCT(3) dsym_85__QUOTE;
        struct MELT_STRING_STRUCT(5) dstr_86__QUOTE;
        struct MELT_ROUTINE_STRUCT(1) drout_87__ANTIQUOTER;
        struct MELT_CLOSURE_STRUCT(0) dclo_88__ANTIQUOTER;
        struct MELT_ROUTINE_STRUCT(4) drout_89__MEXPAND_BACKQUOTE;
        struct MELT_CLOSURE_STRUCT(0) dclo_90__MEXPAND_BACKQUOTE;
        struct MELT_OBJECT_STRUCT(3) dsym_91__BACKQUOTE;
        struct MELT_STRING_STRUCT(9) dstr_92__BACKQUOTE;
        struct MELT_ROUTINE_STRUCT(1) drout_93__MEXPAND_COMMA;
        struct MELT_CLOSURE_STRUCT(0) dclo_94__MEXPAND_COMMA;
        struct MELT_ROUTINE_STRUCT(7) drout_95__SUBSTITUTE_SEXPR;
        struct MELT_CLOSURE_STRUCT(0) dclo_96__SUBSTITUTE_SEXPR;
        struct MELT_OBJECT_STRUCT(3) dsym_97__CLASS_SEXPR_MACROSTRING;
        struct MELT_STRING_STRUCT(23) dstr_98__CLASS_SEXPR_MACROSTRING;
        struct MELT_OBJECT_STRUCT(3) dsym_99__SUBSTITUTE_SEXPR;
        struct MELT_STRING_STRUCT(16) dstr_100__SUBSTITUTE_SEXPR;
        long spare_;
    } *meltcdat = NULL;
    dbgprintf ("start melt_initialize_module_meltdata_WARMELTmiMOREMACRO iniframp__=%p", (void*) iniframp__);
    (void) meltpredefinited; /* avoid warning if non-used. */
    /*curframe_cdat_fill */
    meltcdat = (struct meltcdata_st*) meltgc_allocate(sizeof(*meltcdat),0);
    melt_prohibit_garbcoll = TRUE;
    /*initial routine predef*/
    /*initial routine fill*/


    /*iniobj dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER*/
    /*uniqueobj*/ if (!/*_._VALDATA___V34*/ meltfptr[33])
        /*_._VALDATA___V34*/ meltfptr[33] = (melt_ptr_t )&meltcdat->dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER.obj_hash = 824058733;
    meltcdat->dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER.obj_len = 3;


    /*inistring dstr_2__HOOK_FRESH_ENVIRONMENT_R*/
    /*_._VALSTR___V35*/ meltfptr[34] = (melt_ptr_t) &meltcdat->dstr_2__HOOK_FRESH_ENVIRONMENT_R;
    meltcdat->dstr_2__HOOK_FRESH_ENVIRONMENT_R.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_2__HOOK_FRESH_ENVIRONMENT_R.val, "HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER", sizeof (meltcdat->dstr_2__HOOK_FRESH_ENVIRONMENT_R.val)-1);
    meltcdat->dstr_2__HOOK_FRESH_ENVIRONMENT_R.val[38] = (char)0 ;
    meltcdat->dstr_2__HOOK_FRESH_ENVIRONMENT_R.slen = 38 ;

    /*inirout drout_3__EACH_COMPONENT_IN_LIST*/
    /*iniroutlocvar*/ /*_._VALROUT___V36*/ meltfptr[35] = (melt_ptr_t) &meltcdat->drout_3__EACH_COMPONENT_IN_LIST;
    meltcdat->drout_3__EACH_COMPONENT_IN_LIST.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_3__EACH_COMPONENT_IN_LIST.routdescr, "EACH_COMPONENT_IN_LIST @warmelt-moremacro.melt:44",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_3__EACH_COMPONENT_IN_LIST.nbval = 14;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_3__EACH_COMPONENT_IN_LIST, meltrout_1_WARMELTmiMOREMACRO_EACH_COMPONENT_IN_LIST);

    /*iniclos dclo_4__EACH_COMPONENT_IN_LIST*/
    /*_._VALCLO___V41*/ meltfptr[40] = (melt_ptr_t) &meltcdat->dclo_4__EACH_COMPONENT_IN_LIST;
    meltcdat->dclo_4__EACH_COMPONENT_IN_LIST.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_MACRO_CLOSURE))));
    meltcdat->dclo_4__EACH_COMPONENT_IN_LIST.nbval = 0;


    /*iniobj dsym_5__MELT_DEBUG_FUN*/
    /*uniqueobj*/ if (!/*_._VALDATA___V42*/ meltfptr[41])
        /*_._VALDATA___V42*/ meltfptr[41] = (melt_ptr_t )&meltcdat->dsym_5__MELT_DEBUG_FUN;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_5__MELT_DEBUG_FUN", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_5__MELT_DEBUG_FUN", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_5__MELT_DEBUG_FUN.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_5__MELT_DEBUG_FUN.obj_hash = 972123377;
    meltcdat->dsym_5__MELT_DEBUG_FUN.obj_len = 3;


    /*inistring dstr_6__MELT_DEBUG_FUN*/
    /*_._VALSTR___V43*/ meltfptr[42] = (melt_ptr_t) &meltcdat->dstr_6__MELT_DEBUG_FUN;
    meltcdat->dstr_6__MELT_DEBUG_FUN.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_6__MELT_DEBUG_FUN.val, "MELT_DEBUG_FUN", sizeof (meltcdat->dstr_6__MELT_DEBUG_FUN.val)-1);
    meltcdat->dstr_6__MELT_DEBUG_FUN.val[14] = (char)0 ;
    meltcdat->dstr_6__MELT_DEBUG_FUN.slen = 14 ;


    /*iniobj dsym_7__DEBUG_LESS*/
    /*uniqueobj*/ if (!/*_._VALDATA___V44*/ meltfptr[43])
        /*_._VALDATA___V44*/ meltfptr[43] = (melt_ptr_t )&meltcdat->dsym_7__DEBUG_LESS;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_7__DEBUG_LESS", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_7__DEBUG_LESS", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_7__DEBUG_LESS.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_7__DEBUG_LESS.obj_hash = 977096719;
    meltcdat->dsym_7__DEBUG_LESS.obj_len = 3;


    /*inistring dstr_8__DEBUG_LESS*/
    /*_._VALSTR___V45*/ meltfptr[44] = (melt_ptr_t) &meltcdat->dstr_8__DEBUG_LESS;
    meltcdat->dstr_8__DEBUG_LESS.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_8__DEBUG_LESS.val, "DEBUG_LESS", sizeof (meltcdat->dstr_8__DEBUG_LESS.val)-1);
    meltcdat->dstr_8__DEBUG_LESS.val[10] = (char)0 ;
    meltcdat->dstr_8__DEBUG_LESS.slen = 10 ;


    /*iniobj dsym_9__CLASS_LOCATED*/
    /*uniqueobj*/ if (!/*_._VALDATA___V46*/ meltfptr[45])
        /*_._VALDATA___V46*/ meltfptr[45] = (melt_ptr_t )&meltcdat->dsym_9__CLASS_LOCATED;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_9__CLASS_LOCATED", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_9__CLASS_LOCATED", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_9__CLASS_LOCATED.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_9__CLASS_LOCATED.obj_hash = 979003;
    meltcdat->dsym_9__CLASS_LOCATED.obj_len = 3;


    /*inistring dstr_10__CLASS_LOCATED*/
    /*_._VALSTR___V47*/ meltfptr[46] = (melt_ptr_t) &meltcdat->dstr_10__CLASS_LOCATED;
    meltcdat->dstr_10__CLASS_LOCATED.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_10__CLASS_LOCATED.val, "CLASS_LOCATED", sizeof (meltcdat->dstr_10__CLASS_LOCATED.val)-1);
    meltcdat->dstr_10__CLASS_LOCATED.val[13] = (char)0 ;
    meltcdat->dstr_10__CLASS_LOCATED.slen = 13 ;


    /*iniobj dsym_11__CLASS_SEXPR*/
    /*uniqueobj*/ if (!/*_._VALDATA___V48*/ meltfptr[47])
        /*_._VALDATA___V48*/ meltfptr[47] = (melt_ptr_t )&meltcdat->dsym_11__CLASS_SEXPR;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_11__CLASS_SEXPR", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_11__CLASS_SEXPR", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_11__CLASS_SEXPR.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_11__CLASS_SEXPR.obj_hash = 53411612;
    meltcdat->dsym_11__CLASS_SEXPR.obj_len = 3;


    /*inistring dstr_12__CLASS_SEXPR*/
    /*_._VALSTR___V49*/ meltfptr[48] = (melt_ptr_t) &meltcdat->dstr_12__CLASS_SEXPR;
    meltcdat->dstr_12__CLASS_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_12__CLASS_SEXPR.val, "CLASS_SEXPR", sizeof (meltcdat->dstr_12__CLASS_SEXPR.val)-1);
    meltcdat->dstr_12__CLASS_SEXPR.val[11] = (char)0 ;
    meltcdat->dstr_12__CLASS_SEXPR.slen = 11 ;


    /*iniobj dsym_13__MELT_ASSERT_FAILURE_FUN*/
    /*uniqueobj*/ if (!/*_._VALDATA___V50*/ meltfptr[49])
        /*_._VALDATA___V50*/ meltfptr[49] = (melt_ptr_t )&meltcdat->dsym_13__MELT_ASSERT_FAILURE_FUN;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_13__MELT_ASSERT_FAILURE_FUN", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_13__MELT_ASSERT_FAILURE_FUN", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_13__MELT_ASSERT_FAILURE_FUN.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_13__MELT_ASSERT_FAILURE_FUN.obj_hash = 215547874;
    meltcdat->dsym_13__MELT_ASSERT_FAILURE_FUN.obj_len = 3;


    /*inistring dstr_14__MELT_ASSERT_FAILURE_FUN*/
    /*_._VALSTR___V51*/ meltfptr[50] = (melt_ptr_t) &meltcdat->dstr_14__MELT_ASSERT_FAILURE_FUN;
    meltcdat->dstr_14__MELT_ASSERT_FAILURE_FUN.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_14__MELT_ASSERT_FAILURE_FUN.val, "MELT_ASSERT_FAILURE_FUN", sizeof (meltcdat->dstr_14__MELT_ASSERT_FAILURE_FUN.val)-1);
    meltcdat->dstr_14__MELT_ASSERT_FAILURE_FUN.val[23] = (char)0 ;
    meltcdat->dstr_14__MELT_ASSERT_FAILURE_FUN.slen = 23 ;


    /*iniobj dsym_15__LIST_TO_MULTIPLE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V52*/ meltfptr[51])
        /*_._VALDATA___V52*/ meltfptr[51] = (melt_ptr_t )&meltcdat->dsym_15__LIST_TO_MULTIPLE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_15__LIST_TO_MULTIPLE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_15__LIST_TO_MULTIPLE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_15__LIST_TO_MULTIPLE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_15__LIST_TO_MULTIPLE.obj_hash = 987171205;
    meltcdat->dsym_15__LIST_TO_MULTIPLE.obj_len = 3;


    /*inistring dstr_16__LIST_TO_MULTIPLE*/
    /*_._VALSTR___V53*/ meltfptr[52] = (melt_ptr_t) &meltcdat->dstr_16__LIST_TO_MULTIPLE;
    meltcdat->dstr_16__LIST_TO_MULTIPLE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_16__LIST_TO_MULTIPLE.val, "LIST_TO_MULTIPLE", sizeof (meltcdat->dstr_16__LIST_TO_MULTIPLE.val)-1);
    meltcdat->dstr_16__LIST_TO_MULTIPLE.val[16] = (char)0 ;
    meltcdat->dstr_16__LIST_TO_MULTIPLE.slen = 16 ;


    /*iniobj dsym_17__DISCR_MULTIPLE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V54*/ meltfptr[53])
        /*_._VALDATA___V54*/ meltfptr[53] = (melt_ptr_t )&meltcdat->dsym_17__DISCR_MULTIPLE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_17__DISCR_MULTIPLE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_17__DISCR_MULTIPLE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_17__DISCR_MULTIPLE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_17__DISCR_MULTIPLE.obj_hash = 91864583;
    meltcdat->dsym_17__DISCR_MULTIPLE.obj_len = 3;


    /*inistring dstr_18__DISCR_MULTIPLE*/
    /*_._VALSTR___V55*/ meltfptr[54] = (melt_ptr_t) &meltcdat->dstr_18__DISCR_MULTIPLE;
    meltcdat->dstr_18__DISCR_MULTIPLE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_18__DISCR_MULTIPLE.val, "DISCR_MULTIPLE", sizeof (meltcdat->dstr_18__DISCR_MULTIPLE.val)-1);
    meltcdat->dstr_18__DISCR_MULTIPLE.val[14] = (char)0 ;
    meltcdat->dstr_18__DISCR_MULTIPLE.slen = 14 ;


    /*iniobj dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V56*/ meltfptr[55])
        /*_._VALDATA___V56*/ meltfptr[55] = (melt_ptr_t )&meltcdat->dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE.obj_hash = 746513982;
    meltcdat->dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE.obj_len = 3;


    /*inistring dstr_20__EXPAND_TUPLE_SLICE_AS_TU*/
    /*_._VALSTR___V57*/ meltfptr[56] = (melt_ptr_t) &meltcdat->dstr_20__EXPAND_TUPLE_SLICE_AS_TU;
    meltcdat->dstr_20__EXPAND_TUPLE_SLICE_AS_TU.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_20__EXPAND_TUPLE_SLICE_AS_TU.val, "EXPAND_TUPLE_SLICE_AS_TUPLE", sizeof (meltcdat->dstr_20__EXPAND_TUPLE_SLICE_AS_TU.val)-1);
    meltcdat->dstr_20__EXPAND_TUPLE_SLICE_AS_TU.val[27] = (char)0 ;
    meltcdat->dstr_20__EXPAND_TUPLE_SLICE_AS_TU.slen = 27 ;


    /*iniobj dsym_21__CLASS_SYMBOL*/
    /*uniqueobj*/ if (!/*_._VALDATA___V58*/ meltfptr[57])
        /*_._VALDATA___V58*/ meltfptr[57] = (melt_ptr_t )&meltcdat->dsym_21__CLASS_SYMBOL;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_21__CLASS_SYMBOL", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_21__CLASS_SYMBOL", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_21__CLASS_SYMBOL.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_21__CLASS_SYMBOL.obj_hash = 53524182;
    meltcdat->dsym_21__CLASS_SYMBOL.obj_len = 3;


    /*inistring dstr_22__CLASS_SYMBOL*/
    /*_._VALSTR___V59*/ meltfptr[58] = (melt_ptr_t) &meltcdat->dstr_22__CLASS_SYMBOL;
    meltcdat->dstr_22__CLASS_SYMBOL.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_22__CLASS_SYMBOL.val, "CLASS_SYMBOL", sizeof (meltcdat->dstr_22__CLASS_SYMBOL.val)-1);
    meltcdat->dstr_22__CLASS_SYMBOL.val[12] = (char)0 ;
    meltcdat->dstr_22__CLASS_SYMBOL.slen = 12 ;


    /*iniobj dsym_23__CLONE_SYMBOL*/
    /*uniqueobj*/ if (!/*_._VALDATA___V60*/ meltfptr[59])
        /*_._VALDATA___V60*/ meltfptr[59] = (melt_ptr_t )&meltcdat->dsym_23__CLONE_SYMBOL;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_23__CLONE_SYMBOL", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_23__CLONE_SYMBOL", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_23__CLONE_SYMBOL.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_23__CLONE_SYMBOL.obj_hash = 213258240;
    meltcdat->dsym_23__CLONE_SYMBOL.obj_len = 3;


    /*inistring dstr_24__CLONE_SYMBOL*/
    /*_._VALSTR___V61*/ meltfptr[60] = (melt_ptr_t) &meltcdat->dstr_24__CLONE_SYMBOL;
    meltcdat->dstr_24__CLONE_SYMBOL.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_24__CLONE_SYMBOL.val, "CLONE_SYMBOL", sizeof (meltcdat->dstr_24__CLONE_SYMBOL.val)-1);
    meltcdat->dstr_24__CLONE_SYMBOL.val[12] = (char)0 ;
    meltcdat->dstr_24__CLONE_SYMBOL.slen = 12 ;


    /*iniobj dsym_25__CURPAIRINLISTSYMB*/
    /*uniqueobj*/ if (!/*_._VALDATA___V37*/ meltfptr[36])
        /*_._VALDATA___V37*/ meltfptr[36] = (melt_ptr_t )&meltcdat->dsym_25__CURPAIRINLISTSYMB;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_25__CURPAIRINLISTSYMB", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_25__CURPAIRINLISTSYMB", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_25__CURPAIRINLISTSYMB.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_25__CURPAIRINLISTSYMB.obj_hash = 580598334;
    meltcdat->dsym_25__CURPAIRINLISTSYMB.obj_len = 3;


    /*inistring dstr_26__CURPAIRINLISTSYMB*/
    /*_._VALSTR___V38*/ meltfptr[37] = (melt_ptr_t) &meltcdat->dstr_26__CURPAIRINLISTSYMB;
    meltcdat->dstr_26__CURPAIRINLISTSYMB.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_26__CURPAIRINLISTSYMB.val, "CURPAIRINLISTSYMB", sizeof (meltcdat->dstr_26__CURPAIRINLISTSYMB.val)-1);
    meltcdat->dstr_26__CURPAIRINLISTSYMB.val[17] = (char)0 ;
    meltcdat->dstr_26__CURPAIRINLISTSYMB.slen = 17 ;


    /*iniobj dsym_27__MELT_MAKE_SEXPR*/
    /*uniqueobj*/ if (!/*_._VALDATA___V62*/ meltfptr[61])
        /*_._VALDATA___V62*/ meltfptr[61] = (melt_ptr_t )&meltcdat->dsym_27__MELT_MAKE_SEXPR;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_27__MELT_MAKE_SEXPR", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_27__MELT_MAKE_SEXPR", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_27__MELT_MAKE_SEXPR.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_27__MELT_MAKE_SEXPR.obj_hash = 383667794;
    meltcdat->dsym_27__MELT_MAKE_SEXPR.obj_len = 3;


    /*inistring dstr_28__MELT_MAKE_SEXPR*/
    /*_._VALSTR___V63*/ meltfptr[62] = (melt_ptr_t) &meltcdat->dstr_28__MELT_MAKE_SEXPR;
    meltcdat->dstr_28__MELT_MAKE_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_28__MELT_MAKE_SEXPR.val, "MELT_MAKE_SEXPR", sizeof (meltcdat->dstr_28__MELT_MAKE_SEXPR.val)-1);
    meltcdat->dstr_28__MELT_MAKE_SEXPR.val[15] = (char)0 ;
    meltcdat->dstr_28__MELT_MAKE_SEXPR.slen = 15 ;


    /*iniobj dsym_29__HOOK_MELT_MAKE_LOCATION*/
    /*uniqueobj*/ if (!/*_._VALDATA___V64*/ meltfptr[63])
        /*_._VALDATA___V64*/ meltfptr[63] = (melt_ptr_t )&meltcdat->dsym_29__HOOK_MELT_MAKE_LOCATION;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_29__HOOK_MELT_MAKE_LOCATION", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_29__HOOK_MELT_MAKE_LOCATION", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_29__HOOK_MELT_MAKE_LOCATION.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_29__HOOK_MELT_MAKE_LOCATION.obj_hash = 753739361;
    meltcdat->dsym_29__HOOK_MELT_MAKE_LOCATION.obj_len = 3;


    /*inistring dstr_30__HOOK_MELT_MAKE_LOCATION*/
    /*_._VALSTR___V65*/ meltfptr[64] = (melt_ptr_t) &meltcdat->dstr_30__HOOK_MELT_MAKE_LOCATION;
    meltcdat->dstr_30__HOOK_MELT_MAKE_LOCATION.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_30__HOOK_MELT_MAKE_LOCATION.val, "HOOK_MELT_MAKE_LOCATION", sizeof (meltcdat->dstr_30__HOOK_MELT_MAKE_LOCATION.val)-1);
    meltcdat->dstr_30__HOOK_MELT_MAKE_LOCATION.val[23] = (char)0 ;
    meltcdat->dstr_30__HOOK_MELT_MAKE_LOCATION.slen = 23 ;


    /*iniobj dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST*/
    /*uniqueobj*/ if (!/*_._VALDATA___V39*/ meltfptr[38])
        /*_._VALDATA___V39*/ meltfptr[38] = (melt_ptr_t )&meltcdat->dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST.obj_hash = 535752972;
    meltcdat->dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST.obj_len = 3;


    /*inistring dstr_32__FOREACH_PAIR_COMPONENT_I*/
    /*_._VALSTR___V40*/ meltfptr[39] = (melt_ptr_t) &meltcdat->dstr_32__FOREACH_PAIR_COMPONENT_I;
    meltcdat->dstr_32__FOREACH_PAIR_COMPONENT_I.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_32__FOREACH_PAIR_COMPONENT_I.val, "FOREACH_PAIR_COMPONENT_IN_LIST", sizeof (meltcdat->dstr_32__FOREACH_PAIR_COMPONENT_I.val)-1);
    meltcdat->dstr_32__FOREACH_PAIR_COMPONENT_I.val[30] = (char)0 ;
    meltcdat->dstr_32__FOREACH_PAIR_COMPONENT_I.slen = 30 ;


    /*iniobj dsym_33__EACH_COMPONENT_IN_LIST*/
    /*uniqueobj*/ if (!/*_._VALDATA___V66*/ meltfptr[65])
        /*_._VALDATA___V66*/ meltfptr[65] = (melt_ptr_t )&meltcdat->dsym_33__EACH_COMPONENT_IN_LIST;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_33__EACH_COMPONENT_IN_LIST", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_33__EACH_COMPONENT_IN_LIST", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_33__EACH_COMPONENT_IN_LIST.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_33__EACH_COMPONENT_IN_LIST.obj_hash = 396791142;
    meltcdat->dsym_33__EACH_COMPONENT_IN_LIST.obj_len = 3;


    /*inistring dstr_34__EACH_COMPONENT_IN_LIST*/
    /*_._VALSTR___V67*/ meltfptr[66] = (melt_ptr_t) &meltcdat->dstr_34__EACH_COMPONENT_IN_LIST;
    meltcdat->dstr_34__EACH_COMPONENT_IN_LIST.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_34__EACH_COMPONENT_IN_LIST.val, "EACH_COMPONENT_IN_LIST", sizeof (meltcdat->dstr_34__EACH_COMPONENT_IN_LIST.val)-1);
    meltcdat->dstr_34__EACH_COMPONENT_IN_LIST.val[22] = (char)0 ;
    meltcdat->dstr_34__EACH_COMPONENT_IN_LIST.slen = 22 ;

    /*inirout drout_35__FILTERGCCVERSION*/
    /*iniroutlocvar*/ /*_._VALROUT___V68*/ meltfptr[67] = (melt_ptr_t) &meltcdat->drout_35__FILTERGCCVERSION;
    meltcdat->drout_35__FILTERGCCVERSION.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_35__FILTERGCCVERSION.routdescr, "FILTERGCCVERSION @warmelt-moremacro.melt:116",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_35__FILTERGCCVERSION.nbval = 2;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_35__FILTERGCCVERSION, meltrout_2_WARMELTmiMOREMACRO_FILTERGCCVERSION);

    /*iniclos dclo_36__FILTERGCCVERSION*/
    /*_._VALCLO___V69*/ meltfptr[68] = (melt_ptr_t) &meltcdat->dclo_36__FILTERGCCVERSION;
    meltcdat->dclo_36__FILTERGCCVERSION.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_36__FILTERGCCVERSION.nbval = 0;

    /*inirout drout_37__MEXPAND_GCCIF*/
    /*iniroutlocvar*/ /*_._VALROUT___V70*/ meltfptr[69] = (melt_ptr_t) &meltcdat->drout_37__MEXPAND_GCCIF;
    meltcdat->drout_37__MEXPAND_GCCIF.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_37__MEXPAND_GCCIF.routdescr, "MEXPAND_GCCIF @warmelt-moremacro.melt:143",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_37__MEXPAND_GCCIF.nbval = 8;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_37__MEXPAND_GCCIF, meltrout_3_WARMELTmiMOREMACRO_MEXPAND_GCCIF);

    /*iniclos dclo_38__MEXPAND_GCCIF*/
    /*_._VALCLO___V73*/ meltfptr[72] = (melt_ptr_t) &meltcdat->dclo_38__MEXPAND_GCCIF;
    meltcdat->dclo_38__MEXPAND_GCCIF.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_38__MEXPAND_GCCIF.nbval = 0;


    /*iniobj dsym_39__CLASS_ENVIRONMENT*/
    /*uniqueobj*/ if (!/*_._VALDATA___V74*/ meltfptr[73])
        /*_._VALDATA___V74*/ meltfptr[73] = (melt_ptr_t )&meltcdat->dsym_39__CLASS_ENVIRONMENT;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_39__CLASS_ENVIRONMENT", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_39__CLASS_ENVIRONMENT", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_39__CLASS_ENVIRONMENT.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_39__CLASS_ENVIRONMENT.obj_hash = 59212821;
    meltcdat->dsym_39__CLASS_ENVIRONMENT.obj_len = 3;


    /*inistring dstr_40__CLASS_ENVIRONMENT*/
    /*_._VALSTR___V75*/ meltfptr[74] = (melt_ptr_t) &meltcdat->dstr_40__CLASS_ENVIRONMENT;
    meltcdat->dstr_40__CLASS_ENVIRONMENT.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_40__CLASS_ENVIRONMENT.val, "CLASS_ENVIRONMENT", sizeof (meltcdat->dstr_40__CLASS_ENVIRONMENT.val)-1);
    meltcdat->dstr_40__CLASS_ENVIRONMENT.val[17] = (char)0 ;
    meltcdat->dstr_40__CLASS_ENVIRONMENT.slen = 17 ;


    /*iniobj dsym_41__EXPAND_PAIRLIST_AS_LIST*/
    /*uniqueobj*/ if (!/*_._VALDATA___V76*/ meltfptr[75])
        /*_._VALDATA___V76*/ meltfptr[75] = (melt_ptr_t )&meltcdat->dsym_41__EXPAND_PAIRLIST_AS_LIST;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_41__EXPAND_PAIRLIST_AS_LIST", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_41__EXPAND_PAIRLIST_AS_LIST", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_41__EXPAND_PAIRLIST_AS_LIST.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_41__EXPAND_PAIRLIST_AS_LIST.obj_hash = 1046865288;
    meltcdat->dsym_41__EXPAND_PAIRLIST_AS_LIST.obj_len = 3;


    /*inistring dstr_42__EXPAND_PAIRLIST_AS_LIST*/
    /*_._VALSTR___V77*/ meltfptr[76] = (melt_ptr_t) &meltcdat->dstr_42__EXPAND_PAIRLIST_AS_LIST;
    meltcdat->dstr_42__EXPAND_PAIRLIST_AS_LIST.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_42__EXPAND_PAIRLIST_AS_LIST.val, "EXPAND_PAIRLIST_AS_LIST", sizeof (meltcdat->dstr_42__EXPAND_PAIRLIST_AS_LIST.val)-1);
    meltcdat->dstr_42__EXPAND_PAIRLIST_AS_LIST.val[23] = (char)0 ;
    meltcdat->dstr_42__EXPAND_PAIRLIST_AS_LIST.slen = 23 ;


    /*iniobj dsym_43__TRUE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V71*/ meltfptr[70])
        /*_._VALDATA___V71*/ meltfptr[70] = (melt_ptr_t )&meltcdat->dsym_43__TRUE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_43__TRUE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_KEYWORD))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_43__TRUE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_KEYWORD)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_43__TRUE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_KEYWORD))));
    meltcdat->dsym_43__TRUE.obj_hash = 576485513;
    meltcdat->dsym_43__TRUE.obj_len = 3;


    /*inistring dstr_44__TRUE*/
    /*_._VALSTR___V72*/ meltfptr[71] = (melt_ptr_t) &meltcdat->dstr_44__TRUE;
    meltcdat->dstr_44__TRUE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_44__TRUE.val, "TRUE", sizeof (meltcdat->dstr_44__TRUE.val)-1);
    meltcdat->dstr_44__TRUE.val[4] = (char)0 ;
    meltcdat->dstr_44__TRUE.slen = 4 ;


    /*iniobj dsym_45__INSTALL_INITIAL_MACRO*/
    /*uniqueobj*/ if (!/*_._VALDATA___V78*/ meltfptr[77])
        /*_._VALDATA___V78*/ meltfptr[77] = (melt_ptr_t )&meltcdat->dsym_45__INSTALL_INITIAL_MACRO;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_45__INSTALL_INITIAL_MACRO", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_45__INSTALL_INITIAL_MACRO", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_45__INSTALL_INITIAL_MACRO.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_45__INSTALL_INITIAL_MACRO.obj_hash = 101362976;
    meltcdat->dsym_45__INSTALL_INITIAL_MACRO.obj_len = 3;


    /*inistring dstr_46__INSTALL_INITIAL_MACRO*/
    /*_._VALSTR___V79*/ meltfptr[78] = (melt_ptr_t) &meltcdat->dstr_46__INSTALL_INITIAL_MACRO;
    meltcdat->dstr_46__INSTALL_INITIAL_MACRO.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_46__INSTALL_INITIAL_MACRO.val, "INSTALL_INITIAL_MACRO", sizeof (meltcdat->dstr_46__INSTALL_INITIAL_MACRO.val)-1);
    meltcdat->dstr_46__INSTALL_INITIAL_MACRO.val[21] = (char)0 ;
    meltcdat->dstr_46__INSTALL_INITIAL_MACRO.slen = 21 ;


    /*iniobj dsym_47__GCCIF*/
    /*uniqueobj*/ if (!/*_._VALDATA___V80*/ meltfptr[79])
        /*_._VALDATA___V80*/ meltfptr[79] = (melt_ptr_t )&meltcdat->dsym_47__GCCIF;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_47__GCCIF", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_47__GCCIF", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_47__GCCIF.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_47__GCCIF.obj_hash = 796305141;
    meltcdat->dsym_47__GCCIF.obj_len = 3;


    /*inistring dstr_48__GCCIF*/
    /*_._VALSTR___V81*/ meltfptr[80] = (melt_ptr_t) &meltcdat->dstr_48__GCCIF;
    meltcdat->dstr_48__GCCIF.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_48__GCCIF.val, "GCCIF", sizeof (meltcdat->dstr_48__GCCIF.val)-1);
    meltcdat->dstr_48__GCCIF.val[5] = (char)0 ;
    meltcdat->dstr_48__GCCIF.slen = 5 ;

    /*inirout drout_49__MEXPANDOBSOLETE_CONTAINER*/
    /*iniroutlocvar*/ /*_._VALROUT___V82*/ meltfptr[81] = (melt_ptr_t) &meltcdat->drout_49__MEXPANDOBSOLETE_CONTAINER;
    meltcdat->drout_49__MEXPANDOBSOLETE_CONTAINER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_49__MEXPANDOBSOLETE_CONTAINER.routdescr, "MEXPANDOBSOLETE_CONTAINER @warmelt-moremacro.melt:225",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_49__MEXPANDOBSOLETE_CONTAINER.nbval = 5;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_49__MEXPANDOBSOLETE_CONTAINER, meltrout_4_WARMELTmiMOREMACRO_MEXPANDOBSOLETE_CONTAINER);

    /*iniclos dclo_50__MEXPANDOBSOLETE_CONTAINER*/
    /*_._VALCLO___V83*/ meltfptr[82] = (melt_ptr_t) &meltcdat->dclo_50__MEXPANDOBSOLETE_CONTAINER;
    meltcdat->dclo_50__MEXPANDOBSOLETE_CONTAINER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_50__MEXPANDOBSOLETE_CONTAINER.nbval = 0;


    /*iniobj dsym_51__MEXPAND_REFERENCE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V84*/ meltfptr[83])
        /*_._VALDATA___V84*/ meltfptr[83] = (melt_ptr_t )&meltcdat->dsym_51__MEXPAND_REFERENCE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_51__MEXPAND_REFERENCE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_51__MEXPAND_REFERENCE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_51__MEXPAND_REFERENCE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_51__MEXPAND_REFERENCE.obj_hash = 454324238;
    meltcdat->dsym_51__MEXPAND_REFERENCE.obj_len = 3;


    /*inistring dstr_52__MEXPAND_REFERENCE*/
    /*_._VALSTR___V85*/ meltfptr[84] = (melt_ptr_t) &meltcdat->dstr_52__MEXPAND_REFERENCE;
    meltcdat->dstr_52__MEXPAND_REFERENCE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_52__MEXPAND_REFERENCE.val, "MEXPAND_REFERENCE", sizeof (meltcdat->dstr_52__MEXPAND_REFERENCE.val)-1);
    meltcdat->dstr_52__MEXPAND_REFERENCE.val[17] = (char)0 ;
    meltcdat->dstr_52__MEXPAND_REFERENCE.slen = 17 ;

    /*inirout drout_53__PATEXPANDOBSOLETE_CONTAINER*/
    /*iniroutlocvar*/ /*_._VALROUT___V86*/ meltfptr[85] = (melt_ptr_t) &meltcdat->drout_53__PATEXPANDOBSOLETE_CONTAINER;
    meltcdat->drout_53__PATEXPANDOBSOLETE_CONTAINER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_53__PATEXPANDOBSOLETE_CONTAINER.routdescr, "PATEXPANDOBSOLETE_CONTAINER @warmelt-moremacro.melt:232",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_53__PATEXPANDOBSOLETE_CONTAINER.nbval = 5;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_53__PATEXPANDOBSOLETE_CONTAINER, meltrout_5_WARMELTmiMOREMACRO_PATEXPANDOBSOLETE_CONTAINER);

    /*iniclos dclo_54__PATEXPANDOBSOLETE_CONTAINER*/
    /*_._VALCLO___V87*/ meltfptr[86] = (melt_ptr_t) &meltcdat->dclo_54__PATEXPANDOBSOLETE_CONTAINER;
    meltcdat->dclo_54__PATEXPANDOBSOLETE_CONTAINER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_54__PATEXPANDOBSOLETE_CONTAINER.nbval = 0;


    /*iniobj dsym_55__PATEXPAND_REFERENCE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V88*/ meltfptr[87])
        /*_._VALDATA___V88*/ meltfptr[87] = (melt_ptr_t )&meltcdat->dsym_55__PATEXPAND_REFERENCE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_55__PATEXPAND_REFERENCE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_55__PATEXPAND_REFERENCE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_55__PATEXPAND_REFERENCE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_55__PATEXPAND_REFERENCE.obj_hash = 929282371;
    meltcdat->dsym_55__PATEXPAND_REFERENCE.obj_len = 3;


    /*inistring dstr_56__PATEXPAND_REFERENCE*/
    /*_._VALSTR___V89*/ meltfptr[88] = (melt_ptr_t) &meltcdat->dstr_56__PATEXPAND_REFERENCE;
    meltcdat->dstr_56__PATEXPAND_REFERENCE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_56__PATEXPAND_REFERENCE.val, "PATEXPAND_REFERENCE", sizeof (meltcdat->dstr_56__PATEXPAND_REFERENCE.val)-1);
    meltcdat->dstr_56__PATEXPAND_REFERENCE.val[19] = (char)0 ;
    meltcdat->dstr_56__PATEXPAND_REFERENCE.slen = 19 ;


    /*iniobj dsym_57__INSTALL_INITIAL_PATMACRO*/
    /*uniqueobj*/ if (!/*_._VALDATA___V90*/ meltfptr[89])
        /*_._VALDATA___V90*/ meltfptr[89] = (melt_ptr_t )&meltcdat->dsym_57__INSTALL_INITIAL_PATMACRO;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_57__INSTALL_INITIAL_PATMACRO", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_57__INSTALL_INITIAL_PATMACRO", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_57__INSTALL_INITIAL_PATMACRO.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_57__INSTALL_INITIAL_PATMACRO.obj_hash = 959787197;
    meltcdat->dsym_57__INSTALL_INITIAL_PATMACRO.obj_len = 3;


    /*inistring dstr_58__INSTALL_INITIAL_PATMACRO*/
    /*_._VALSTR___V91*/ meltfptr[90] = (melt_ptr_t) &meltcdat->dstr_58__INSTALL_INITIAL_PATMACRO;
    meltcdat->dstr_58__INSTALL_INITIAL_PATMACRO.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_58__INSTALL_INITIAL_PATMACRO.val, "INSTALL_INITIAL_PATMACRO", sizeof (meltcdat->dstr_58__INSTALL_INITIAL_PATMACRO.val)-1);
    meltcdat->dstr_58__INSTALL_INITIAL_PATMACRO.val[24] = (char)0 ;
    meltcdat->dstr_58__INSTALL_INITIAL_PATMACRO.slen = 24 ;


    /*iniobj dsym_59__CONTAINER*/
    /*uniqueobj*/ if (!/*_._VALDATA___V92*/ meltfptr[91])
        /*_._VALDATA___V92*/ meltfptr[91] = (melt_ptr_t )&meltcdat->dsym_59__CONTAINER;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_59__CONTAINER", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_59__CONTAINER", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_59__CONTAINER.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_59__CONTAINER.obj_hash = 910562261;
    meltcdat->dsym_59__CONTAINER.obj_len = 3;


    /*inistring dstr_60__CONTAINER*/
    /*_._VALSTR___V93*/ meltfptr[92] = (melt_ptr_t) &meltcdat->dstr_60__CONTAINER;
    meltcdat->dstr_60__CONTAINER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_60__CONTAINER.val, "CONTAINER", sizeof (meltcdat->dstr_60__CONTAINER.val)-1);
    meltcdat->dstr_60__CONTAINER.val[9] = (char)0 ;
    meltcdat->dstr_60__CONTAINER.slen = 9 ;

    /*inirout drout_61__EXPAND_QUOTED_SEXPR*/
    /*iniroutlocvar*/ /*_._VALROUT___V94*/ meltfptr[93] = (melt_ptr_t) &meltcdat->drout_61__EXPAND_QUOTED_SEXPR;
    meltcdat->drout_61__EXPAND_QUOTED_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_61__EXPAND_QUOTED_SEXPR.routdescr, "EXPAND_QUOTED_SEXPR @warmelt-moremacro.melt:246",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_61__EXPAND_QUOTED_SEXPR.nbval = 18;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_61__EXPAND_QUOTED_SEXPR, meltrout_6_WARMELTmiMOREMACRO_EXPAND_QUOTED_SEXPR);

    /*iniclos dclo_62__EXPAND_QUOTED_SEXPR*/
    /*_._VALCLO___V97*/ meltfptr[96] = (melt_ptr_t) &meltcdat->dclo_62__EXPAND_QUOTED_SEXPR;
    meltcdat->dclo_62__EXPAND_QUOTED_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_62__EXPAND_QUOTED_SEXPR.nbval = 0;


    /*iniobj dsym_63__CLASS_SOURCE_HOOK_CALL*/
    /*uniqueobj*/ if (!/*_._VALDATA___V98*/ meltfptr[97])
        /*_._VALDATA___V98*/ meltfptr[97] = (melt_ptr_t )&meltcdat->dsym_63__CLASS_SOURCE_HOOK_CALL;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_63__CLASS_SOURCE_HOOK_CALL", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_63__CLASS_SOURCE_HOOK_CALL", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_63__CLASS_SOURCE_HOOK_CALL.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_63__CLASS_SOURCE_HOOK_CALL.obj_hash = 317559930;
    meltcdat->dsym_63__CLASS_SOURCE_HOOK_CALL.obj_len = 3;


    /*inistring dstr_64__CLASS_SOURCE_HOOK_CALL*/
    /*_._VALSTR___V99*/ meltfptr[98] = (melt_ptr_t) &meltcdat->dstr_64__CLASS_SOURCE_HOOK_CALL;
    meltcdat->dstr_64__CLASS_SOURCE_HOOK_CALL.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_64__CLASS_SOURCE_HOOK_CALL.val, "CLASS_SOURCE_HOOK_CALL", sizeof (meltcdat->dstr_64__CLASS_SOURCE_HOOK_CALL.val)-1);
    meltcdat->dstr_64__CLASS_SOURCE_HOOK_CALL.val[22] = (char)0 ;
    meltcdat->dstr_64__CLASS_SOURCE_HOOK_CALL.slen = 22 ;


    /*iniobj dsym_65__DISCR_LIST*/
    /*uniqueobj*/ if (!/*_._VALDATA___V100*/ meltfptr[99])
        /*_._VALDATA___V100*/ meltfptr[99] = (melt_ptr_t )&meltcdat->dsym_65__DISCR_LIST;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_65__DISCR_LIST", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_65__DISCR_LIST", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_65__DISCR_LIST.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_65__DISCR_LIST.obj_hash = 98407634;
    meltcdat->dsym_65__DISCR_LIST.obj_len = 3;


    /*inistring dstr_66__DISCR_LIST*/
    /*_._VALSTR___V101*/ meltfptr[100] = (melt_ptr_t) &meltcdat->dstr_66__DISCR_LIST;
    meltcdat->dstr_66__DISCR_LIST.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_66__DISCR_LIST.val, "DISCR_LIST", sizeof (meltcdat->dstr_66__DISCR_LIST.val)-1);
    meltcdat->dstr_66__DISCR_LIST.val[10] = (char)0 ;
    meltcdat->dstr_66__DISCR_LIST.slen = 10 ;


    /*iniobj dsym_67__CLASS_KEYWORD*/
    /*uniqueobj*/ if (!/*_._VALDATA___V102*/ meltfptr[101])
        /*_._VALDATA___V102*/ meltfptr[101] = (melt_ptr_t )&meltcdat->dsym_67__CLASS_KEYWORD;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_67__CLASS_KEYWORD", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_67__CLASS_KEYWORD", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_67__CLASS_KEYWORD.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_67__CLASS_KEYWORD.obj_hash = 14992133;
    meltcdat->dsym_67__CLASS_KEYWORD.obj_len = 3;


    /*inistring dstr_68__CLASS_KEYWORD*/
    /*_._VALSTR___V103*/ meltfptr[102] = (melt_ptr_t) &meltcdat->dstr_68__CLASS_KEYWORD;
    meltcdat->dstr_68__CLASS_KEYWORD.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_68__CLASS_KEYWORD.val, "CLASS_KEYWORD", sizeof (meltcdat->dstr_68__CLASS_KEYWORD.val)-1);
    meltcdat->dstr_68__CLASS_KEYWORD.val[13] = (char)0 ;
    meltcdat->dstr_68__CLASS_KEYWORD.slen = 13 ;


    /*iniobj dsym_69__CLASS_SOURCE_QUOTE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V104*/ meltfptr[103])
        /*_._VALDATA___V104*/ meltfptr[103] = (melt_ptr_t )&meltcdat->dsym_69__CLASS_SOURCE_QUOTE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_69__CLASS_SOURCE_QUOTE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_69__CLASS_SOURCE_QUOTE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_69__CLASS_SOURCE_QUOTE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_69__CLASS_SOURCE_QUOTE.obj_hash = 488554331;
    meltcdat->dsym_69__CLASS_SOURCE_QUOTE.obj_len = 3;


    /*inistring dstr_70__CLASS_SOURCE_QUOTE*/
    /*_._VALSTR___V105*/ meltfptr[104] = (melt_ptr_t) &meltcdat->dstr_70__CLASS_SOURCE_QUOTE;
    meltcdat->dstr_70__CLASS_SOURCE_QUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_70__CLASS_SOURCE_QUOTE.val, "CLASS_SOURCE_QUOTE", sizeof (meltcdat->dstr_70__CLASS_SOURCE_QUOTE.val)-1);
    meltcdat->dstr_70__CLASS_SOURCE_QUOTE.val[18] = (char)0 ;
    meltcdat->dstr_70__CLASS_SOURCE_QUOTE.slen = 18 ;


    /*iniobj dsym_71__COMMA*/
    /*uniqueobj*/ if (!/*_._VALDATA___V95*/ meltfptr[94])
        /*_._VALDATA___V95*/ meltfptr[94] = (melt_ptr_t )&meltcdat->dsym_71__COMMA;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_71__COMMA", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_71__COMMA", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_71__COMMA.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_71__COMMA.obj_hash = 920286524;
    meltcdat->dsym_71__COMMA.obj_len = 3;


    /*inistring dstr_72__COMMA*/
    /*_._VALSTR___V96*/ meltfptr[95] = (melt_ptr_t) &meltcdat->dstr_72__COMMA;
    meltcdat->dstr_72__COMMA.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_72__COMMA.val, "COMMA", sizeof (meltcdat->dstr_72__COMMA.val)-1);
    meltcdat->dstr_72__COMMA.val[5] = (char)0 ;
    meltcdat->dstr_72__COMMA.slen = 5 ;


    /*iniobj dsym_73__LIST_NTH_ELEMENT*/
    /*uniqueobj*/ if (!/*_._VALDATA___V106*/ meltfptr[105])
        /*_._VALDATA___V106*/ meltfptr[105] = (melt_ptr_t )&meltcdat->dsym_73__LIST_NTH_ELEMENT;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_73__LIST_NTH_ELEMENT", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_73__LIST_NTH_ELEMENT", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_73__LIST_NTH_ELEMENT.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_73__LIST_NTH_ELEMENT.obj_hash = 329876278;
    meltcdat->dsym_73__LIST_NTH_ELEMENT.obj_len = 3;


    /*inistring dstr_74__LIST_NTH_ELEMENT*/
    /*_._VALSTR___V107*/ meltfptr[106] = (melt_ptr_t) &meltcdat->dstr_74__LIST_NTH_ELEMENT;
    meltcdat->dstr_74__LIST_NTH_ELEMENT.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_74__LIST_NTH_ELEMENT.val, "LIST_NTH_ELEMENT", sizeof (meltcdat->dstr_74__LIST_NTH_ELEMENT.val)-1);
    meltcdat->dstr_74__LIST_NTH_ELEMENT.val[16] = (char)0 ;
    meltcdat->dstr_74__LIST_NTH_ELEMENT.slen = 16 ;


    /*iniobj dsym_75__LIST_APPEND2LIST*/
    /*uniqueobj*/ if (!/*_._VALDATA___V108*/ meltfptr[107])
        /*_._VALDATA___V108*/ meltfptr[107] = (melt_ptr_t )&meltcdat->dsym_75__LIST_APPEND2LIST;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_75__LIST_APPEND2LIST", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_75__LIST_APPEND2LIST", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_75__LIST_APPEND2LIST.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_75__LIST_APPEND2LIST.obj_hash = 744841630;
    meltcdat->dsym_75__LIST_APPEND2LIST.obj_len = 3;


    /*inistring dstr_76__LIST_APPEND2LIST*/
    /*_._VALSTR___V109*/ meltfptr[108] = (melt_ptr_t) &meltcdat->dstr_76__LIST_APPEND2LIST;
    meltcdat->dstr_76__LIST_APPEND2LIST.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_76__LIST_APPEND2LIST.val, "LIST_APPEND2LIST", sizeof (meltcdat->dstr_76__LIST_APPEND2LIST.val)-1);
    meltcdat->dstr_76__LIST_APPEND2LIST.val[16] = (char)0 ;
    meltcdat->dstr_76__LIST_APPEND2LIST.slen = 16 ;


    /*iniobj dsym_77__CLASS_SOURCE_APPLY*/
    /*uniqueobj*/ if (!/*_._VALDATA___V110*/ meltfptr[109])
        /*_._VALDATA___V110*/ meltfptr[109] = (melt_ptr_t )&meltcdat->dsym_77__CLASS_SOURCE_APPLY;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_77__CLASS_SOURCE_APPLY", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_77__CLASS_SOURCE_APPLY", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_77__CLASS_SOURCE_APPLY.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_77__CLASS_SOURCE_APPLY.obj_hash = 908584793;
    meltcdat->dsym_77__CLASS_SOURCE_APPLY.obj_len = 3;


    /*inistring dstr_78__CLASS_SOURCE_APPLY*/
    /*_._VALSTR___V111*/ meltfptr[110] = (melt_ptr_t) &meltcdat->dstr_78__CLASS_SOURCE_APPLY;
    meltcdat->dstr_78__CLASS_SOURCE_APPLY.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_78__CLASS_SOURCE_APPLY.val, "CLASS_SOURCE_APPLY", sizeof (meltcdat->dstr_78__CLASS_SOURCE_APPLY.val)-1);
    meltcdat->dstr_78__CLASS_SOURCE_APPLY.val[18] = (char)0 ;
    meltcdat->dstr_78__CLASS_SOURCE_APPLY.slen = 18 ;

    /*inirout drout_79__MEXPAND_QUOTE*/
    /*iniroutlocvar*/ /*_._VALROUT___V112*/ meltfptr[111] = (melt_ptr_t) &meltcdat->drout_79__MEXPAND_QUOTE;
    meltcdat->drout_79__MEXPAND_QUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_79__MEXPAND_QUOTE.routdescr, "MEXPAND_QUOTE @warmelt-moremacro.melt:327",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_79__MEXPAND_QUOTE.nbval = 10;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_79__MEXPAND_QUOTE, meltrout_7_WARMELTmiMOREMACRO_MEXPAND_QUOTE);

    /*iniclos dclo_80__MEXPAND_QUOTE*/
    /*_._VALCLO___V113*/ meltfptr[112] = (melt_ptr_t) &meltcdat->dclo_80__MEXPAND_QUOTE;
    meltcdat->dclo_80__MEXPAND_QUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_80__MEXPAND_QUOTE.nbval = 0;


    /*iniobj dsym_81__ERROR_AT*/
    /*uniqueobj*/ if (!/*_._VALDATA___V114*/ meltfptr[113])
        /*_._VALDATA___V114*/ meltfptr[113] = (melt_ptr_t )&meltcdat->dsym_81__ERROR_AT;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_81__ERROR_AT", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_81__ERROR_AT", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_81__ERROR_AT.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_81__ERROR_AT.obj_hash = 1019046282;
    meltcdat->dsym_81__ERROR_AT.obj_len = 3;


    /*inistring dstr_82__ERROR_AT*/
    /*_._VALSTR___V115*/ meltfptr[114] = (melt_ptr_t) &meltcdat->dstr_82__ERROR_AT;
    meltcdat->dstr_82__ERROR_AT.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_82__ERROR_AT.val, "ERROR_AT", sizeof (meltcdat->dstr_82__ERROR_AT.val)-1);
    meltcdat->dstr_82__ERROR_AT.val[8] = (char)0 ;
    meltcdat->dstr_82__ERROR_AT.slen = 8 ;


    /*iniobj dsym_83__CLASS_SOURCE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V116*/ meltfptr[115])
        /*_._VALDATA___V116*/ meltfptr[115] = (melt_ptr_t )&meltcdat->dsym_83__CLASS_SOURCE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_83__CLASS_SOURCE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_83__CLASS_SOURCE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_83__CLASS_SOURCE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_83__CLASS_SOURCE.obj_hash = 656628255;
    meltcdat->dsym_83__CLASS_SOURCE.obj_len = 3;


    /*inistring dstr_84__CLASS_SOURCE*/
    /*_._VALSTR___V117*/ meltfptr[116] = (melt_ptr_t) &meltcdat->dstr_84__CLASS_SOURCE;
    meltcdat->dstr_84__CLASS_SOURCE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_84__CLASS_SOURCE.val, "CLASS_SOURCE", sizeof (meltcdat->dstr_84__CLASS_SOURCE.val)-1);
    meltcdat->dstr_84__CLASS_SOURCE.val[12] = (char)0 ;
    meltcdat->dstr_84__CLASS_SOURCE.slen = 12 ;


    /*iniobj dsym_85__QUOTE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V118*/ meltfptr[117])
        /*_._VALDATA___V118*/ meltfptr[117] = (melt_ptr_t )&meltcdat->dsym_85__QUOTE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_85__QUOTE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_85__QUOTE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_85__QUOTE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_85__QUOTE.obj_hash = 18202130;
    meltcdat->dsym_85__QUOTE.obj_len = 3;


    /*inistring dstr_86__QUOTE*/
    /*_._VALSTR___V119*/ meltfptr[118] = (melt_ptr_t) &meltcdat->dstr_86__QUOTE;
    meltcdat->dstr_86__QUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_86__QUOTE.val, "QUOTE", sizeof (meltcdat->dstr_86__QUOTE.val)-1);
    meltcdat->dstr_86__QUOTE.val[5] = (char)0 ;
    meltcdat->dstr_86__QUOTE.slen = 5 ;

    /*inirout drout_87__ANTIQUOTER*/
    /*iniroutlocvar*/ /*_._VALROUT___V120*/ meltfptr[119] = (melt_ptr_t) &meltcdat->drout_87__ANTIQUOTER;
    meltcdat->drout_87__ANTIQUOTER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_87__ANTIQUOTER.routdescr, "ANTIQUOTER @warmelt-moremacro.melt:379",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_87__ANTIQUOTER.nbval = 1;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_87__ANTIQUOTER, meltrout_8_WARMELTmiMOREMACRO_ANTIQUOTER);

    /*iniclos dclo_88__ANTIQUOTER*/
    /*_._VALCLO___V121*/ meltfptr[120] = (melt_ptr_t) &meltcdat->dclo_88__ANTIQUOTER;
    meltcdat->dclo_88__ANTIQUOTER.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_88__ANTIQUOTER.nbval = 0;

    /*inirout drout_89__MEXPAND_BACKQUOTE*/
    /*iniroutlocvar*/ /*_._VALROUT___V122*/ meltfptr[121] = (melt_ptr_t) &meltcdat->drout_89__MEXPAND_BACKQUOTE;
    meltcdat->drout_89__MEXPAND_BACKQUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_89__MEXPAND_BACKQUOTE.routdescr, "MEXPAND_BACKQUOTE @warmelt-moremacro.melt:393",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_89__MEXPAND_BACKQUOTE.nbval = 4;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_89__MEXPAND_BACKQUOTE, meltrout_9_WARMELTmiMOREMACRO_MEXPAND_BACKQUOTE);

    /*iniclos dclo_90__MEXPAND_BACKQUOTE*/
    /*_._VALCLO___V123*/ meltfptr[122] = (melt_ptr_t) &meltcdat->dclo_90__MEXPAND_BACKQUOTE;
    meltcdat->dclo_90__MEXPAND_BACKQUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_90__MEXPAND_BACKQUOTE.nbval = 0;


    /*iniobj dsym_91__BACKQUOTE*/
    /*uniqueobj*/ if (!/*_._VALDATA___V124*/ meltfptr[123])
        /*_._VALDATA___V124*/ meltfptr[123] = (melt_ptr_t )&meltcdat->dsym_91__BACKQUOTE;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_91__BACKQUOTE", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_91__BACKQUOTE", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_91__BACKQUOTE.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_91__BACKQUOTE.obj_hash = 727072914;
    meltcdat->dsym_91__BACKQUOTE.obj_len = 3;


    /*inistring dstr_92__BACKQUOTE*/
    /*_._VALSTR___V125*/ meltfptr[124] = (melt_ptr_t) &meltcdat->dstr_92__BACKQUOTE;
    meltcdat->dstr_92__BACKQUOTE.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_92__BACKQUOTE.val, "BACKQUOTE", sizeof (meltcdat->dstr_92__BACKQUOTE.val)-1);
    meltcdat->dstr_92__BACKQUOTE.val[9] = (char)0 ;
    meltcdat->dstr_92__BACKQUOTE.slen = 9 ;

    /*inirout drout_93__MEXPAND_COMMA*/
    /*iniroutlocvar*/ /*_._VALROUT___V126*/ meltfptr[125] = (melt_ptr_t) &meltcdat->drout_93__MEXPAND_COMMA;
    meltcdat->drout_93__MEXPAND_COMMA.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_93__MEXPAND_COMMA.routdescr, "MEXPAND_COMMA @warmelt-moremacro.melt:423",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_93__MEXPAND_COMMA.nbval = 1;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_93__MEXPAND_COMMA, meltrout_10_WARMELTmiMOREMACRO_MEXPAND_COMMA);

    /*iniclos dclo_94__MEXPAND_COMMA*/
    /*_._VALCLO___V127*/ meltfptr[126] = (melt_ptr_t) &meltcdat->dclo_94__MEXPAND_COMMA;
    meltcdat->dclo_94__MEXPAND_COMMA.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_94__MEXPAND_COMMA.nbval = 0;

    /*inirout drout_95__SUBSTITUTE_SEXPR*/
    /*iniroutlocvar*/ /*_._VALROUT___V128*/ meltfptr[127] = (melt_ptr_t) &meltcdat->drout_95__SUBSTITUTE_SEXPR;
    meltcdat->drout_95__SUBSTITUTE_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_ROUTINE))));
    strncpy (meltcdat->drout_95__SUBSTITUTE_SEXPR.routdescr, "SUBSTITUTE_SEXPR @warmelt-moremacro.melt:441",  MELT_ROUTDESCR_LEN - 1);
    meltcdat->drout_95__SUBSTITUTE_SEXPR.nbval = 7;
    MELT_ROUTINE_SET_ROUTCODE(&meltcdat->drout_95__SUBSTITUTE_SEXPR, meltrout_11_WARMELTmiMOREMACRO_SUBSTITUTE_SEXPR);

    /*iniclos dclo_96__SUBSTITUTE_SEXPR*/
    /*_._VALCLO___V129*/ meltfptr[128] = (melt_ptr_t) &meltcdat->dclo_96__SUBSTITUTE_SEXPR;
    meltcdat->dclo_96__SUBSTITUTE_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_CLOSURE))));
    meltcdat->dclo_96__SUBSTITUTE_SEXPR.nbval = 0;


    /*iniobj dsym_97__CLASS_SEXPR_MACROSTRING*/
    /*uniqueobj*/ if (!/*_._VALDATA___V130*/ meltfptr[129])
        /*_._VALDATA___V130*/ meltfptr[129] = (melt_ptr_t )&meltcdat->dsym_97__CLASS_SEXPR_MACROSTRING;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_97__CLASS_SEXPR_MACROSTRING", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_97__CLASS_SEXPR_MACROSTRING", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_97__CLASS_SEXPR_MACROSTRING.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_97__CLASS_SEXPR_MACROSTRING.obj_hash = 576848661;
    meltcdat->dsym_97__CLASS_SEXPR_MACROSTRING.obj_len = 3;


    /*inistring dstr_98__CLASS_SEXPR_MACROSTRING*/
    /*_._VALSTR___V131*/ meltfptr[130] = (melt_ptr_t) &meltcdat->dstr_98__CLASS_SEXPR_MACROSTRING;
    meltcdat->dstr_98__CLASS_SEXPR_MACROSTRING.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_98__CLASS_SEXPR_MACROSTRING.val, "CLASS_SEXPR_MACROSTRING", sizeof (meltcdat->dstr_98__CLASS_SEXPR_MACROSTRING.val)-1);
    meltcdat->dstr_98__CLASS_SEXPR_MACROSTRING.val[23] = (char)0 ;
    meltcdat->dstr_98__CLASS_SEXPR_MACROSTRING.slen = 23 ;


    /*iniobj dsym_99__SUBSTITUTE_SEXPR*/
    /*uniqueobj*/ if (!/*_._VALDATA___V132*/ meltfptr[131])
        /*_._VALDATA___V132*/ meltfptr[131] = (melt_ptr_t )&meltcdat->dsym_99__SUBSTITUTE_SEXPR;
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr isobj dsym_99__SUBSTITUTE_SEXPR", melt_magic_discr ((melt_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))))) == MELTOBMAG_OBJECT);
    if (MELT_LIKELY(!melt_prohibit_garbcoll)) melt_assertmsg("iniobj check.discr objmagic dsym_99__SUBSTITUTE_SEXPR", ((meltobject_ptr_t) (((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL)))))->meltobj_magic == MELTOBMAG_OBJECT);
    meltcdat->dsym_99__SUBSTITUTE_SEXPR.meltobj_class = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(CLASS_SYMBOL))));
    meltcdat->dsym_99__SUBSTITUTE_SEXPR.obj_hash = 33840324;
    meltcdat->dsym_99__SUBSTITUTE_SEXPR.obj_len = 3;


    /*inistring dstr_100__SUBSTITUTE_SEXPR*/
    /*_._VALSTR___V133*/ meltfptr[132] = (melt_ptr_t) &meltcdat->dstr_100__SUBSTITUTE_SEXPR;
    meltcdat->dstr_100__SUBSTITUTE_SEXPR.discr = (meltobject_ptr_t)(((melt_ptr_t)(MELT_PREDEF(DISCR_STRING))));
    /*small inistring*/ strncpy(meltcdat->dstr_100__SUBSTITUTE_SEXPR.val, "SUBSTITUTE_SEXPR", sizeof (meltcdat->dstr_100__SUBSTITUTE_SEXPR.val)-1);
    meltcdat->dstr_100__SUBSTITUTE_SEXPR.val[16] = (char)0 ;
    meltcdat->dstr_100__SUBSTITUTE_SEXPR.slen = 16 ;
    meltcdat = NULL;
    melt_prohibit_garbcoll = FALSE;

#undef meltfram__
} /*end melt_initialize_module_meltdata_WARMELTmiMOREMACRO*/



#if MELT_HAVE_DEBUG
const char meltmodule_WARMELTmiMOREMACRO__melt_have_debug_enabled[] = "MELT module warmelt-moremacro have debug enabled";
#else /*!MELT_HAVE_DEBUG*/
const char meltmodule_WARMELTmiMOREMACRO__melt_have_debug_disabled[] = "MELT module warmelt-moremacro have debug disabled";
#endif /*MELT_HAVE_DEBUG*/


void* melt_start_this_module (void* modargp_)
{

    char meltpredefinited[MELTGLOB__LASTGLOB+8];

#if MELT_HAVE_DEBUG
    static long melt_call_counter__;
    long melt_thiscallcounter__ ATTRIBUTE_UNUSED = ++ melt_call_counter__;
#undef meltcallcount
#define meltcallcount melt_thiscallcounter__
#else
#undef meltcallcount
#define meltcallcount 0L
#endif
//// emitted by output_curframe_declstruct_init using LAMBDA_ @warmelt-outobj.melt:2253

    /* start of frame for routine melt_start_this_module fromline 1752 */

    /*startiniframdecl*/

    /* end of frame for routine melt_start_this_module fromline 1756 */


    debugeprintf("sizeof Melt_InitialFrame in melt_start_this_module=%d", (int) sizeof(Melt_InitialFrame));
    /* classy initial frame melt_start_this_module fromline 1773*/ Melt_InitialFrame
    meltfram__ /*declfrastruct fromline 1780*/
    /*classyinitroutinearg melt_start_this_module fromline 1819*/
#if ENABLE_CHECKING
    /*classyinitroutfram fromline 1823:*/ (__FILE__, __LINE__)
#endif /*ENABLE_CHECKING fromline1825*/

    ;
#define meltframe meltfram__

    /**initial routine prologue**/
    /**COMMENT: get previous environment **/;

    /*^compute*/
    /*_._PREVENV___V4*/ meltfptr[3] = /*getprevenv*/ (melt_ptr_t) modargp_;
    /*^comment*/
    /**COMMENT: compute boxloc **/;

    /*^cond*/
    /*cond*/ if (/*_._CONTENV___V2*/ meltfptr[1]) /*then*/
        {
        }
    else    /*^cond.else*/
        {

            /*^compute*/

            /* compile2obj_initproc emitted initialization of environment reference for warmelt-moremacro */
            if (/*_._PREVENV___V4*/ meltfptr[3])
                {
                    /*_._CONTENV___V2*/ meltfptr[1] = melthookproc_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER
                                                      ((melt_ptr_t) /*_._PREVENV___V4*/ meltfptr[3], "warmelt-moremacro") ;
                }
            else /* no prevenv */
                {
#if MELT_HAS_INITIAL_ENVIRONMENT>0
                    if (!melt_flag_bootstrapping)
                        warning(0, "MELT is not creating a fresh environment reference for warmelt-moremacro without parent env.") ;
#endif /* MELT_HAS_INITIAL_ENVIRONMENT>0 */
                }
            ;;
        }

    /*^comment*/
    /**COMMENT: get symbols & keywords for initial procedure **/;

    /*^getnamedsymbol*/
    /*getnamedsym:HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER*/

    if (NULL == /*_._VALDATA___V34*/ meltfptr[33])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER = melthookproc_HOOK_NAMED_SYMBOL ("HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER", (long) MELT_GET);
            /*_._VALDATA___V34*/ meltfptr[33] = (melt_ptr_t) meltsy_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER;
        } /*endgetnamedsym HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER*/


    /*^getnamedsymbol*/
    /*getnamedsym:MELT_DEBUG_FUN*/

    if (NULL == /*_._VALDATA___V42*/ meltfptr[41])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol MELT_DEBUG_FUN without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_MELT_DEBUG_FUN = melthookproc_HOOK_NAMED_SYMBOL ("MELT_DEBUG_FUN", (long) MELT_GET);
            /*_._VALDATA___V42*/ meltfptr[41] = (melt_ptr_t) meltsy_MELT_DEBUG_FUN;
        } /*endgetnamedsym MELT_DEBUG_FUN*/


    /*^getnamedsymbol*/
    /*getnamedsym:DEBUG_LESS*/

    if (NULL == /*_._VALDATA___V44*/ meltfptr[43])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol DEBUG_LESS without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_DEBUG_LESS = melthookproc_HOOK_NAMED_SYMBOL ("DEBUG_LESS", (long) MELT_GET);
            /*_._VALDATA___V44*/ meltfptr[43] = (melt_ptr_t) meltsy_DEBUG_LESS;
        } /*endgetnamedsym DEBUG_LESS*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_LOCATED*/

    if (NULL == /*_._VALDATA___V46*/ meltfptr[45])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_LOCATED without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_LOCATED = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_LOCATED", (long) MELT_GET);
            /*_._VALDATA___V46*/ meltfptr[45] = (melt_ptr_t) meltsy_CLASS_LOCATED;
        } /*endgetnamedsym CLASS_LOCATED*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SEXPR*/

    if (NULL == /*_._VALDATA___V48*/ meltfptr[47])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SEXPR without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SEXPR = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SEXPR", (long) MELT_GET);
            /*_._VALDATA___V48*/ meltfptr[47] = (melt_ptr_t) meltsy_CLASS_SEXPR;
        } /*endgetnamedsym CLASS_SEXPR*/


    /*^getnamedsymbol*/
    /*getnamedsym:MELT_ASSERT_FAILURE_FUN*/

    if (NULL == /*_._VALDATA___V50*/ meltfptr[49])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol MELT_ASSERT_FAILURE_FUN without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_MELT_ASSERT_FAILURE_FUN = melthookproc_HOOK_NAMED_SYMBOL ("MELT_ASSERT_FAILURE_FUN", (long) MELT_GET);
            /*_._VALDATA___V50*/ meltfptr[49] = (melt_ptr_t) meltsy_MELT_ASSERT_FAILURE_FUN;
        } /*endgetnamedsym MELT_ASSERT_FAILURE_FUN*/


    /*^getnamedsymbol*/
    /*getnamedsym:LIST_TO_MULTIPLE*/

    if (NULL == /*_._VALDATA___V52*/ meltfptr[51])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol LIST_TO_MULTIPLE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_LIST_TO_MULTIPLE = melthookproc_HOOK_NAMED_SYMBOL ("LIST_TO_MULTIPLE", (long) MELT_GET);
            /*_._VALDATA___V52*/ meltfptr[51] = (melt_ptr_t) meltsy_LIST_TO_MULTIPLE;
        } /*endgetnamedsym LIST_TO_MULTIPLE*/


    /*^getnamedsymbol*/
    /*getnamedsym:DISCR_MULTIPLE*/

    if (NULL == /*_._VALDATA___V54*/ meltfptr[53])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol DISCR_MULTIPLE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_DISCR_MULTIPLE = melthookproc_HOOK_NAMED_SYMBOL ("DISCR_MULTIPLE", (long) MELT_GET);
            /*_._VALDATA___V54*/ meltfptr[53] = (melt_ptr_t) meltsy_DISCR_MULTIPLE;
        } /*endgetnamedsym DISCR_MULTIPLE*/


    /*^getnamedsymbol*/
    /*getnamedsym:EXPAND_TUPLE_SLICE_AS_TUPLE*/

    if (NULL == /*_._VALDATA___V56*/ meltfptr[55])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol EXPAND_TUPLE_SLICE_AS_TUPLE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_EXPAND_TUPLE_SLICE_AS_TUPLE = melthookproc_HOOK_NAMED_SYMBOL ("EXPAND_TUPLE_SLICE_AS_TUPLE", (long) MELT_GET);
            /*_._VALDATA___V56*/ meltfptr[55] = (melt_ptr_t) meltsy_EXPAND_TUPLE_SLICE_AS_TUPLE;
        } /*endgetnamedsym EXPAND_TUPLE_SLICE_AS_TUPLE*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SYMBOL*/

    if (NULL == /*_._VALDATA___V58*/ meltfptr[57])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SYMBOL without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SYMBOL = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SYMBOL", (long) MELT_GET);
            /*_._VALDATA___V58*/ meltfptr[57] = (melt_ptr_t) meltsy_CLASS_SYMBOL;
        } /*endgetnamedsym CLASS_SYMBOL*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLONE_SYMBOL*/

    if (NULL == /*_._VALDATA___V60*/ meltfptr[59])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLONE_SYMBOL without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLONE_SYMBOL = melthookproc_HOOK_NAMED_SYMBOL ("CLONE_SYMBOL", (long) MELT_GET);
            /*_._VALDATA___V60*/ meltfptr[59] = (melt_ptr_t) meltsy_CLONE_SYMBOL;
        } /*endgetnamedsym CLONE_SYMBOL*/


    /*^getnamedsymbol*/
    /*getnamedsym:CURPAIRINLISTSYMB*/

    if (NULL == /*_._VALDATA___V37*/ meltfptr[36])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CURPAIRINLISTSYMB without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CURPAIRINLISTSYMB = melthookproc_HOOK_NAMED_SYMBOL ("CURPAIRINLISTSYMB", (long) MELT_GET);
            /*_._VALDATA___V37*/ meltfptr[36] = (melt_ptr_t) meltsy_CURPAIRINLISTSYMB;
        } /*endgetnamedsym CURPAIRINLISTSYMB*/


    /*^getnamedsymbol*/
    /*getnamedsym:MELT_MAKE_SEXPR*/

    if (NULL == /*_._VALDATA___V62*/ meltfptr[61])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol MELT_MAKE_SEXPR without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_MELT_MAKE_SEXPR = melthookproc_HOOK_NAMED_SYMBOL ("MELT_MAKE_SEXPR", (long) MELT_GET);
            /*_._VALDATA___V62*/ meltfptr[61] = (melt_ptr_t) meltsy_MELT_MAKE_SEXPR;
        } /*endgetnamedsym MELT_MAKE_SEXPR*/


    /*^getnamedsymbol*/
    /*getnamedsym:HOOK_MELT_MAKE_LOCATION*/

    if (NULL == /*_._VALDATA___V64*/ meltfptr[63])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol HOOK_MELT_MAKE_LOCATION without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_HOOK_MELT_MAKE_LOCATION = melthookproc_HOOK_NAMED_SYMBOL ("HOOK_MELT_MAKE_LOCATION", (long) MELT_GET);
            /*_._VALDATA___V64*/ meltfptr[63] = (melt_ptr_t) meltsy_HOOK_MELT_MAKE_LOCATION;
        } /*endgetnamedsym HOOK_MELT_MAKE_LOCATION*/


    /*^getnamedsymbol*/
    /*getnamedsym:FOREACH_PAIR_COMPONENT_IN_LIST*/

    if (NULL == /*_._VALDATA___V39*/ meltfptr[38])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol FOREACH_PAIR_COMPONENT_IN_LIST without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_FOREACH_PAIR_COMPONENT_IN_LIST = melthookproc_HOOK_NAMED_SYMBOL ("FOREACH_PAIR_COMPONENT_IN_LIST", (long) MELT_GET);
            /*_._VALDATA___V39*/ meltfptr[38] = (melt_ptr_t) meltsy_FOREACH_PAIR_COMPONENT_IN_LIST;
        } /*endgetnamedsym FOREACH_PAIR_COMPONENT_IN_LIST*/


    /*^getnamedsymbol*/
    /*getnamedsym:EACH_COMPONENT_IN_LIST*/

    if (NULL == /*_._VALDATA___V66*/ meltfptr[65])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol EACH_COMPONENT_IN_LIST without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_EACH_COMPONENT_IN_LIST = melthookproc_HOOK_NAMED_SYMBOL ("EACH_COMPONENT_IN_LIST", (long) MELT_GET);
            /*_._VALDATA___V66*/ meltfptr[65] = (melt_ptr_t) meltsy_EACH_COMPONENT_IN_LIST;
        } /*endgetnamedsym EACH_COMPONENT_IN_LIST*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_ENVIRONMENT*/

    if (NULL == /*_._VALDATA___V74*/ meltfptr[73])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_ENVIRONMENT without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_ENVIRONMENT = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_ENVIRONMENT", (long) MELT_GET);
            /*_._VALDATA___V74*/ meltfptr[73] = (melt_ptr_t) meltsy_CLASS_ENVIRONMENT;
        } /*endgetnamedsym CLASS_ENVIRONMENT*/


    /*^getnamedsymbol*/
    /*getnamedsym:EXPAND_PAIRLIST_AS_LIST*/

    if (NULL == /*_._VALDATA___V76*/ meltfptr[75])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol EXPAND_PAIRLIST_AS_LIST without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_EXPAND_PAIRLIST_AS_LIST = melthookproc_HOOK_NAMED_SYMBOL ("EXPAND_PAIRLIST_AS_LIST", (long) MELT_GET);
            /*_._VALDATA___V76*/ meltfptr[75] = (melt_ptr_t) meltsy_EXPAND_PAIRLIST_AS_LIST;
        } /*endgetnamedsym EXPAND_PAIRLIST_AS_LIST*/


    /*^getnamedkeyword*/
    /*getnamedkeyw:TRUE*/
    {
        melt_ptr_t kw_TRUE = melthookproc_HOOK_NAMED_KEYWORD ("TRUE", (long) MELT_GET);
        if (kw_TRUE) /*_._VALDATA___V71*/ meltfptr[70] = (melt_ptr_t) kw_TRUE;
    }

    /*^getnamedsymbol*/
    /*getnamedsym:INSTALL_INITIAL_MACRO*/

    if (NULL == /*_._VALDATA___V78*/ meltfptr[77])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol INSTALL_INITIAL_MACRO without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_INSTALL_INITIAL_MACRO = melthookproc_HOOK_NAMED_SYMBOL ("INSTALL_INITIAL_MACRO", (long) MELT_GET);
            /*_._VALDATA___V78*/ meltfptr[77] = (melt_ptr_t) meltsy_INSTALL_INITIAL_MACRO;
        } /*endgetnamedsym INSTALL_INITIAL_MACRO*/


    /*^getnamedsymbol*/
    /*getnamedsym:GCCIF*/

    if (NULL == /*_._VALDATA___V80*/ meltfptr[79])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol GCCIF without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_GCCIF = melthookproc_HOOK_NAMED_SYMBOL ("GCCIF", (long) MELT_GET);
            /*_._VALDATA___V80*/ meltfptr[79] = (melt_ptr_t) meltsy_GCCIF;
        } /*endgetnamedsym GCCIF*/


    /*^getnamedsymbol*/
    /*getnamedsym:MEXPAND_REFERENCE*/

    if (NULL == /*_._VALDATA___V84*/ meltfptr[83])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol MEXPAND_REFERENCE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_MEXPAND_REFERENCE = melthookproc_HOOK_NAMED_SYMBOL ("MEXPAND_REFERENCE", (long) MELT_GET);
            /*_._VALDATA___V84*/ meltfptr[83] = (melt_ptr_t) meltsy_MEXPAND_REFERENCE;
        } /*endgetnamedsym MEXPAND_REFERENCE*/


    /*^getnamedsymbol*/
    /*getnamedsym:PATEXPAND_REFERENCE*/

    if (NULL == /*_._VALDATA___V88*/ meltfptr[87])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol PATEXPAND_REFERENCE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_PATEXPAND_REFERENCE = melthookproc_HOOK_NAMED_SYMBOL ("PATEXPAND_REFERENCE", (long) MELT_GET);
            /*_._VALDATA___V88*/ meltfptr[87] = (melt_ptr_t) meltsy_PATEXPAND_REFERENCE;
        } /*endgetnamedsym PATEXPAND_REFERENCE*/


    /*^getnamedsymbol*/
    /*getnamedsym:INSTALL_INITIAL_PATMACRO*/

    if (NULL == /*_._VALDATA___V90*/ meltfptr[89])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol INSTALL_INITIAL_PATMACRO without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_INSTALL_INITIAL_PATMACRO = melthookproc_HOOK_NAMED_SYMBOL ("INSTALL_INITIAL_PATMACRO", (long) MELT_GET);
            /*_._VALDATA___V90*/ meltfptr[89] = (melt_ptr_t) meltsy_INSTALL_INITIAL_PATMACRO;
        } /*endgetnamedsym INSTALL_INITIAL_PATMACRO*/


    /*^getnamedsymbol*/
    /*getnamedsym:CONTAINER*/

    if (NULL == /*_._VALDATA___V92*/ meltfptr[91])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CONTAINER without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CONTAINER = melthookproc_HOOK_NAMED_SYMBOL ("CONTAINER", (long) MELT_GET);
            /*_._VALDATA___V92*/ meltfptr[91] = (melt_ptr_t) meltsy_CONTAINER;
        } /*endgetnamedsym CONTAINER*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SOURCE_HOOK_CALL*/

    if (NULL == /*_._VALDATA___V98*/ meltfptr[97])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SOURCE_HOOK_CALL without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SOURCE_HOOK_CALL = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SOURCE_HOOK_CALL", (long) MELT_GET);
            /*_._VALDATA___V98*/ meltfptr[97] = (melt_ptr_t) meltsy_CLASS_SOURCE_HOOK_CALL;
        } /*endgetnamedsym CLASS_SOURCE_HOOK_CALL*/


    /*^getnamedsymbol*/
    /*getnamedsym:DISCR_LIST*/

    if (NULL == /*_._VALDATA___V100*/ meltfptr[99])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol DISCR_LIST without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_DISCR_LIST = melthookproc_HOOK_NAMED_SYMBOL ("DISCR_LIST", (long) MELT_GET);
            /*_._VALDATA___V100*/ meltfptr[99] = (melt_ptr_t) meltsy_DISCR_LIST;
        } /*endgetnamedsym DISCR_LIST*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_KEYWORD*/

    if (NULL == /*_._VALDATA___V102*/ meltfptr[101])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_KEYWORD without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_KEYWORD = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_KEYWORD", (long) MELT_GET);
            /*_._VALDATA___V102*/ meltfptr[101] = (melt_ptr_t) meltsy_CLASS_KEYWORD;
        } /*endgetnamedsym CLASS_KEYWORD*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SOURCE_QUOTE*/

    if (NULL == /*_._VALDATA___V104*/ meltfptr[103])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SOURCE_QUOTE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SOURCE_QUOTE = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SOURCE_QUOTE", (long) MELT_GET);
            /*_._VALDATA___V104*/ meltfptr[103] = (melt_ptr_t) meltsy_CLASS_SOURCE_QUOTE;
        } /*endgetnamedsym CLASS_SOURCE_QUOTE*/


    /*^getnamedsymbol*/
    /*getnamedsym:COMMA*/

    if (NULL == /*_._VALDATA___V95*/ meltfptr[94])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol COMMA without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_COMMA = melthookproc_HOOK_NAMED_SYMBOL ("COMMA", (long) MELT_GET);
            /*_._VALDATA___V95*/ meltfptr[94] = (melt_ptr_t) meltsy_COMMA;
        } /*endgetnamedsym COMMA*/


    /*^getnamedsymbol*/
    /*getnamedsym:LIST_NTH_ELEMENT*/

    if (NULL == /*_._VALDATA___V106*/ meltfptr[105])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol LIST_NTH_ELEMENT without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_LIST_NTH_ELEMENT = melthookproc_HOOK_NAMED_SYMBOL ("LIST_NTH_ELEMENT", (long) MELT_GET);
            /*_._VALDATA___V106*/ meltfptr[105] = (melt_ptr_t) meltsy_LIST_NTH_ELEMENT;
        } /*endgetnamedsym LIST_NTH_ELEMENT*/


    /*^getnamedsymbol*/
    /*getnamedsym:LIST_APPEND2LIST*/

    if (NULL == /*_._VALDATA___V108*/ meltfptr[107])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol LIST_APPEND2LIST without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_LIST_APPEND2LIST = melthookproc_HOOK_NAMED_SYMBOL ("LIST_APPEND2LIST", (long) MELT_GET);
            /*_._VALDATA___V108*/ meltfptr[107] = (melt_ptr_t) meltsy_LIST_APPEND2LIST;
        } /*endgetnamedsym LIST_APPEND2LIST*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SOURCE_APPLY*/

    if (NULL == /*_._VALDATA___V110*/ meltfptr[109])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SOURCE_APPLY without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SOURCE_APPLY = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SOURCE_APPLY", (long) MELT_GET);
            /*_._VALDATA___V110*/ meltfptr[109] = (melt_ptr_t) meltsy_CLASS_SOURCE_APPLY;
        } /*endgetnamedsym CLASS_SOURCE_APPLY*/


    /*^getnamedsymbol*/
    /*getnamedsym:ERROR_AT*/

    if (NULL == /*_._VALDATA___V114*/ meltfptr[113])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol ERROR_AT without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_ERROR_AT = melthookproc_HOOK_NAMED_SYMBOL ("ERROR_AT", (long) MELT_GET);
            /*_._VALDATA___V114*/ meltfptr[113] = (melt_ptr_t) meltsy_ERROR_AT;
        } /*endgetnamedsym ERROR_AT*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SOURCE*/

    if (NULL == /*_._VALDATA___V116*/ meltfptr[115])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SOURCE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SOURCE = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SOURCE", (long) MELT_GET);
            /*_._VALDATA___V116*/ meltfptr[115] = (melt_ptr_t) meltsy_CLASS_SOURCE;
        } /*endgetnamedsym CLASS_SOURCE*/


    /*^getnamedsymbol*/
    /*getnamedsym:QUOTE*/

    if (NULL == /*_._VALDATA___V118*/ meltfptr[117])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol QUOTE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_QUOTE = melthookproc_HOOK_NAMED_SYMBOL ("QUOTE", (long) MELT_GET);
            /*_._VALDATA___V118*/ meltfptr[117] = (melt_ptr_t) meltsy_QUOTE;
        } /*endgetnamedsym QUOTE*/


    /*^getnamedsymbol*/
    /*getnamedsym:BACKQUOTE*/

    if (NULL == /*_._VALDATA___V124*/ meltfptr[123])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol BACKQUOTE without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_BACKQUOTE = melthookproc_HOOK_NAMED_SYMBOL ("BACKQUOTE", (long) MELT_GET);
            /*_._VALDATA___V124*/ meltfptr[123] = (melt_ptr_t) meltsy_BACKQUOTE;
        } /*endgetnamedsym BACKQUOTE*/


    /*^getnamedsymbol*/
    /*getnamedsym:CLASS_SEXPR_MACROSTRING*/

    if (NULL == /*_._VALDATA___V130*/ meltfptr[129])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol CLASS_SEXPR_MACROSTRING without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_CLASS_SEXPR_MACROSTRING = melthookproc_HOOK_NAMED_SYMBOL ("CLASS_SEXPR_MACROSTRING", (long) MELT_GET);
            /*_._VALDATA___V130*/ meltfptr[129] = (melt_ptr_t) meltsy_CLASS_SEXPR_MACROSTRING;
        } /*endgetnamedsym CLASS_SEXPR_MACROSTRING*/


    /*^getnamedsymbol*/
    /*getnamedsym:SUBSTITUTE_SEXPR*/

    if (NULL == /*_._VALDATA___V132*/ meltfptr[131])
        {
#if !MELT_HAS_INITIAL_ENVIRONMENT
#error MELT getting named symbol SUBSTITUTE_SEXPR without initial environment
#endif /*!MELT_HAS_INITIAL_ENVIRONMENT*/
            melt_ptr_t meltsy_SUBSTITUTE_SEXPR = melthookproc_HOOK_NAMED_SYMBOL ("SUBSTITUTE_SEXPR", (long) MELT_GET);
            /*_._VALDATA___V132*/ meltfptr[131] = (melt_ptr_t) meltsy_SUBSTITUTE_SEXPR;
        } /*endgetnamedsym SUBSTITUTE_SEXPR*/


    /*^comment*/
    /**COMMENT: before getting imported values thru hook **/;

    MELT_LOCATION("warmelt-moremacro.melt:3:/ compute");
    /*_.HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER__V5*/ meltfptr[4] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:50:/ compute");
    /*_.MELT_DEBUG_FUN__V6*/ meltfptr[5] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "MELT_DEBUG_FUN",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    /*^compute*/
    /*_.DEBUG_LESS__V7*/ meltfptr[6] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "DEBUG_LESS",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:52:/ compute");
    /*_.CLASS_LOCATED__V8*/ meltfptr[7] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_LOCATED",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:53:/ compute");
    /*_.CLASS_SEXPR__V9*/ meltfptr[8] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SEXPR",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:56:/ compute");
    /*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "MELT_ASSERT_FAILURE_FUN",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:58:/ compute");
    /*_.LIST_TO_MULTIPLE__V11*/ meltfptr[10] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "LIST_TO_MULTIPLE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    /*^compute*/
    /*_.DISCR_MULTIPLE__V12*/ meltfptr[11] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "DISCR_MULTIPLE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:85:/ compute");
    /*_.EXPAND_TUPLE_SLICE_AS_TUPLE__V13*/ meltfptr[12] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "EXPAND_TUPLE_SLICE_AS_TUPLE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:92:/ compute");
    /*_.CLASS_SYMBOL__V14*/ meltfptr[13] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SYMBOL",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:96:/ compute");
    /*_.CLONE_SYMBOL__V15*/ meltfptr[14] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLONE_SYMBOL",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:98:/ compute");
    /*_.MELT_MAKE_SEXPR__V16*/ meltfptr[15] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "MELT_MAKE_SEXPR",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    /*^compute*/
    /*_.HOOK_MELT_MAKE_LOCATION__V17*/ meltfptr[16] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "HOOK_MELT_MAKE_LOCATION",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:145:/ compute");
    /*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_ENVIRONMENT",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:166:/ compute");
    /*_.EXPAND_PAIRLIST_AS_LIST__V19*/ meltfptr[18] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "EXPAND_PAIRLIST_AS_LIST",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:214:/ compute");
    /*_.INSTALL_INITIAL_MACRO__V20*/ meltfptr[19] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "INSTALL_INITIAL_MACRO",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:230:/ compute");
    /*_.MEXPAND_REFERENCE__V21*/ meltfptr[20] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "MEXPAND_REFERENCE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:237:/ compute");
    /*_.PATEXPAND_REFERENCE__V22*/ meltfptr[21] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "PATEXPAND_REFERENCE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:239:/ compute");
    /*_.INSTALL_INITIAL_PATMACRO__V23*/ meltfptr[22] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "INSTALL_INITIAL_PATMACRO",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:257:/ compute");
    /*_.CLASS_SOURCE_HOOK_CALL__V24*/ meltfptr[23] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SOURCE_HOOK_CALL",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:261:/ compute");
    /*_.DISCR_LIST__V25*/ meltfptr[24] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "DISCR_LIST",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:275:/ compute");
    /*_.CLASS_KEYWORD__V26*/ meltfptr[25] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_KEYWORD",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:278:/ compute");
    /*_.CLASS_SOURCE_QUOTE__V27*/ meltfptr[26] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SOURCE_QUOTE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:291:/ compute");
    /*_.LIST_NTH_ELEMENT__V28*/ meltfptr[27] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "LIST_NTH_ELEMENT",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:303:/ compute");
    /*_.LIST_APPEND2LIST__V29*/ meltfptr[28] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "LIST_APPEND2LIST",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:316:/ compute");
    /*_.CLASS_SOURCE_APPLY__V30*/ meltfptr[29] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SOURCE_APPLY",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:337:/ compute");
    /*_.ERROR_AT__V31*/ meltfptr[30] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "ERROR_AT",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:347:/ compute");
    /*_.CLASS_SOURCE__V32*/ meltfptr[31] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SOURCE",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    MELT_LOCATION("warmelt-moremacro.melt:457:/ compute");
    /*_.CLASS_SEXPR_MACROSTRING__V33*/ meltfptr[32] =
        /*hookcall*/ melthook_HOOK_SYMBOL_IMPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_SYMBOL_IMPORTER))),  "CLASS_SEXPR_MACROSTRING",  "warmelt-moremacro", /*_._PREVENV___V4*/ meltfptr[3]) ;
    /**COMMENT: after getting imported values **/;

    /**initial routine cdata initializer**/

    memset(meltpredefinited, 0, sizeof(meltpredefinited));
    melt_initialize_module_meltdata_WARMELTmiMOREMACRO (&meltfram__, meltpredefinited);
    /**initial routine body**/

    debugeprintf (" in initialization of warmelt-moremacro thru 3 chunk routines with frame @%p of %d bytes",
                  /*fromline 2338*/ (void*)&meltfram__, (int) sizeof(meltfram__));
    melt_debuggc_eprintf ("initialization of warmelt-moremacro thru 3 chunks, frame @%p of %d bytes",
                          (void*)&meltfram__, (int) sizeof(meltfram__));

    meltmod__WARMELTmiMOREMACRO__initialmeltchunk_0 (&meltfram__, meltpredefinited);
    meltmod__WARMELTmiMOREMACRO__initialmeltchunk_1 (&meltfram__, meltpredefinited);
    meltmod__WARMELTmiMOREMACRO__initialmeltchunk_2 (&meltfram__, meltpredefinited);;
    goto meltlabend_rout;
meltlabend_rout:
    ;
    {
        /* return out of initial fromline 2371 */ melt_ptr_t retval = /*_._RETINIT___V1*/ meltfptr[0];
        debugeprintf ("returning @%p from initial routine of warmelt-moremacro", (void*)retval); /*fromline 2379*/
        return retval;
    }
#undef meltcallcount
#undef meltfram__
#undef MELTFRAM_NBVARNUM
#undef MELTFRAM_NBVARPTR
} /* end melt_start_this_module fromline 2391 */


void meltmod__WARMELTmiMOREMACRO__initialmeltchunk_0 (meltinitial_frame_t* meltframptr__, char meltpredefinited[])
{
#define meltfram__ (*meltframptr__)
#undef meltcallcount
#define meltcallcount 0L
    (void) meltpredefinited;
    /**COMMENT: start of oinibody **/;

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V34*/ meltfptr[33])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_1__HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V34*/ meltfptr[33]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V34*/ meltfptr[33]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V35*/ meltfptr[34]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V34*/ meltfptr[33]);


    melt_dbgtrace_written_object (/*_._VALDATA___V34*/ meltfptr[33], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#1", NULL != (/*_.DEBUG_LESS__V7*/ meltfptr[6]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[1] = (melt_ptr_t)(/*_.DEBUG_LESS__V7*/ meltfptr[6]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#2", NULL != (/*_.CLASS_LOCATED__V8*/ meltfptr[7]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[2] = (melt_ptr_t)(/*_.CLASS_LOCATED__V8*/ meltfptr[7]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#3", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[3] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#4", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[4] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#5", NULL != (/*_.LIST_TO_MULTIPLE__V11*/ meltfptr[10]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[5] = (melt_ptr_t)(/*_.LIST_TO_MULTIPLE__V11*/ meltfptr[10]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#6", NULL != (/*_.DISCR_MULTIPLE__V12*/ meltfptr[11]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[6] = (melt_ptr_t)(/*_.DISCR_MULTIPLE__V12*/ meltfptr[11]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#7", NULL != (/*_.EXPAND_TUPLE_SLICE_AS_TUPLE__V13*/ meltfptr[12]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[7] = (melt_ptr_t)(/*_.EXPAND_TUPLE_SLICE_AS_TUPLE__V13*/ meltfptr[12]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#8", NULL != (/*_.CLASS_SYMBOL__V14*/ meltfptr[13]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[8] = (melt_ptr_t)(/*_.CLASS_SYMBOL__V14*/ meltfptr[13]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#9", NULL != (/*_.CLONE_SYMBOL__V15*/ meltfptr[14]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[9] = (melt_ptr_t)(/*_.CLONE_SYMBOL__V15*/ meltfptr[14]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_25__CURPAIRINLISTSYMB @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V37*/ meltfptr[36])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_25__CURPAIRINLISTSYMB @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V37*/ meltfptr[36]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V37*/ meltfptr[36]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V38*/ meltfptr[37]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V37*/ meltfptr[36]);


    melt_dbgtrace_written_object (/*_._VALDATA___V37*/ meltfptr[36], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#10", NULL != (/*_._VALDATA___V37*/ meltfptr[36]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[10] = (melt_ptr_t)(/*_._VALDATA___V37*/ meltfptr[36]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#11", NULL != (/*_.MELT_MAKE_SEXPR__V16*/ meltfptr[15]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[11] = (melt_ptr_t)(/*_.MELT_MAKE_SEXPR__V16*/ meltfptr[15]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#12", NULL != (/*_.HOOK_MELT_MAKE_LOCATION__V17*/ meltfptr[16]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[12] = (melt_ptr_t)(/*_.HOOK_MELT_MAKE_LOCATION__V17*/ meltfptr[16]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V39*/ meltfptr[38])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_31__FOREACH_PAIR_COMPONENT_IN_LIST @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V39*/ meltfptr[38]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V39*/ meltfptr[38]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V40*/ meltfptr[39]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V39*/ meltfptr[38]);


    melt_dbgtrace_written_object (/*_._VALDATA___V39*/ meltfptr[38], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_3__EACH_COMPONENT_IN_LIST#13", NULL != (/*_._VALDATA___V39*/ meltfptr[38]));
    ((meltroutine_ptr_t)/*_._VALROUT___V36*/ meltfptr[35])->tabval[13] = (melt_ptr_t)(/*_._VALDATA___V39*/ meltfptr[38]);

    MELT_LOCATION("warmelt-moremacro.melt:44:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V36*/ meltfptr[35]);

    /*putclosurout#2*/
    melt_assertmsg("putclosrout#2 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V41*/ meltfptr[40])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#2 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V36*/ meltfptr[35])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V41*/ meltfptr[40])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V36*/ meltfptr[35]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V41*/ meltfptr[40]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_5__MELT_DEBUG_FUN @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V42*/ meltfptr[41])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_5__MELT_DEBUG_FUN @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V42*/ meltfptr[41]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V42*/ meltfptr[41]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V43*/ meltfptr[42]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V42*/ meltfptr[41]);


    melt_dbgtrace_written_object (/*_._VALDATA___V42*/ meltfptr[41], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_7__DEBUG_LESS @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V44*/ meltfptr[43])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_7__DEBUG_LESS @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V44*/ meltfptr[43]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V44*/ meltfptr[43]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V45*/ meltfptr[44]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V44*/ meltfptr[43]);


    melt_dbgtrace_written_object (/*_._VALDATA___V44*/ meltfptr[43], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_9__CLASS_LOCATED @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V46*/ meltfptr[45])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_9__CLASS_LOCATED @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V46*/ meltfptr[45]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V46*/ meltfptr[45]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V47*/ meltfptr[46]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V46*/ meltfptr[45]);


    melt_dbgtrace_written_object (/*_._VALDATA___V46*/ meltfptr[45], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_11__CLASS_SEXPR @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V48*/ meltfptr[47])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_11__CLASS_SEXPR @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V48*/ meltfptr[47]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V48*/ meltfptr[47]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V49*/ meltfptr[48]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V48*/ meltfptr[47]);


    melt_dbgtrace_written_object (/*_._VALDATA___V48*/ meltfptr[47], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_13__MELT_ASSERT_FAILURE_FUN @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V50*/ meltfptr[49])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_13__MELT_ASSERT_FAILURE_FUN @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V50*/ meltfptr[49]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V50*/ meltfptr[49]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V51*/ meltfptr[50]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V50*/ meltfptr[49]);


    melt_dbgtrace_written_object (/*_._VALDATA___V50*/ meltfptr[49], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_15__LIST_TO_MULTIPLE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V52*/ meltfptr[51])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_15__LIST_TO_MULTIPLE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V52*/ meltfptr[51]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V52*/ meltfptr[51]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V53*/ meltfptr[52]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V52*/ meltfptr[51]);


    melt_dbgtrace_written_object (/*_._VALDATA___V52*/ meltfptr[51], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_17__DISCR_MULTIPLE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V54*/ meltfptr[53])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_17__DISCR_MULTIPLE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V54*/ meltfptr[53]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V54*/ meltfptr[53]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V55*/ meltfptr[54]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V54*/ meltfptr[53]);


    melt_dbgtrace_written_object (/*_._VALDATA___V54*/ meltfptr[53], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V56*/ meltfptr[55])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_19__EXPAND_TUPLE_SLICE_AS_TUPLE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V56*/ meltfptr[55]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V56*/ meltfptr[55]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V57*/ meltfptr[56]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V56*/ meltfptr[55]);


    melt_dbgtrace_written_object (/*_._VALDATA___V56*/ meltfptr[55], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_21__CLASS_SYMBOL @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V58*/ meltfptr[57])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_21__CLASS_SYMBOL @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V58*/ meltfptr[57]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V58*/ meltfptr[57]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V59*/ meltfptr[58]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V58*/ meltfptr[57]);


    melt_dbgtrace_written_object (/*_._VALDATA___V58*/ meltfptr[57], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_23__CLONE_SYMBOL @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V60*/ meltfptr[59])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_23__CLONE_SYMBOL @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V60*/ meltfptr[59]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V60*/ meltfptr[59]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V61*/ meltfptr[60]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V60*/ meltfptr[59]);


    melt_dbgtrace_written_object (/*_._VALDATA___V60*/ meltfptr[59], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_27__MELT_MAKE_SEXPR @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V62*/ meltfptr[61])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_27__MELT_MAKE_SEXPR @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V62*/ meltfptr[61]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V62*/ meltfptr[61]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V63*/ meltfptr[62]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V62*/ meltfptr[61]);


    melt_dbgtrace_written_object (/*_._VALDATA___V62*/ meltfptr[61], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_29__HOOK_MELT_MAKE_LOCATION @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V64*/ meltfptr[63])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_29__HOOK_MELT_MAKE_LOCATION @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V64*/ meltfptr[63]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V64*/ meltfptr[63]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V65*/ meltfptr[64]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V64*/ meltfptr[63]);


    melt_dbgtrace_written_object (/*_._VALDATA___V64*/ meltfptr[63], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_33__EACH_COMPONENT_IN_LIST @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V66*/ meltfptr[65])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_33__EACH_COMPONENT_IN_LIST @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V66*/ meltfptr[65]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V66*/ meltfptr[65]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V67*/ meltfptr[66]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V66*/ meltfptr[65]);


    melt_dbgtrace_written_object (/*_._VALDATA___V66*/ meltfptr[65], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:116:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V68*/ meltfptr[67])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_35__FILTERGCCVERSION#0", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V68*/ meltfptr[67])->tabval[0] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);

    MELT_LOCATION("warmelt-moremacro.melt:116:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V68*/ meltfptr[67])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_35__FILTERGCCVERSION#1", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V68*/ meltfptr[67])->tabval[1] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:116:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V68*/ meltfptr[67]);

    /*putclosurout#3*/
    melt_assertmsg("putclosrout#3 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V69*/ meltfptr[68])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#3 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V68*/ meltfptr[67])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V69*/ meltfptr[68])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V68*/ meltfptr[67]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V69*/ meltfptr[68]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#0", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[0] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#1", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[1] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#2", NULL != (/*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[2] = (melt_ptr_t)(/*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#3", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[3] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#4", NULL != (/*_.DEBUG_LESS__V7*/ meltfptr[6]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[4] = (melt_ptr_t)(/*_.DEBUG_LESS__V7*/ meltfptr[6]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconstnotnull*/
    /*putroutconstnotnull*/
    melt_assertmsg("putroutconstnotnull checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    melt_assertmsg("putroutconstnotnull notnullconst", NULL != /*_._VALCLO___V69*/ meltfptr[68]);
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[5] = (melt_ptr_t)(/*_._VALCLO___V69*/ meltfptr[68]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#6", NULL != (/*_.EXPAND_PAIRLIST_AS_LIST__V19*/ meltfptr[18]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[6] = (melt_ptr_t)(/*_.EXPAND_PAIRLIST_AS_LIST__V19*/ meltfptr[18]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_43__TRUE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V71*/ meltfptr[70])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_43__TRUE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V71*/ meltfptr[70]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V71*/ meltfptr[70]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V72*/ meltfptr[71]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V71*/ meltfptr[70]);


    melt_dbgtrace_written_object (/*_._VALDATA___V71*/ meltfptr[70], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_37__MEXPAND_GCCIF#7", NULL != (/*_._VALDATA___V71*/ meltfptr[70]));
    ((meltroutine_ptr_t)/*_._VALROUT___V70*/ meltfptr[69])->tabval[7] = (melt_ptr_t)(/*_._VALDATA___V71*/ meltfptr[70]);

    MELT_LOCATION("warmelt-moremacro.melt:143:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V70*/ meltfptr[69]);

    /*putclosurout#4*/
    melt_assertmsg("putclosrout#4 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V73*/ meltfptr[72])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#4 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V70*/ meltfptr[69])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V73*/ meltfptr[72])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V70*/ meltfptr[69]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V73*/ meltfptr[72]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_39__CLASS_ENVIRONMENT @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V74*/ meltfptr[73])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_39__CLASS_ENVIRONMENT @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V74*/ meltfptr[73]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V74*/ meltfptr[73]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V75*/ meltfptr[74]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V74*/ meltfptr[73]);


    melt_dbgtrace_written_object (/*_._VALDATA___V74*/ meltfptr[73], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_41__EXPAND_PAIRLIST_AS_LIST @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V76*/ meltfptr[75])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_41__EXPAND_PAIRLIST_AS_LIST @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V76*/ meltfptr[75]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V76*/ meltfptr[75]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V77*/ meltfptr[76]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V76*/ meltfptr[75]);


    melt_dbgtrace_written_object (/*_._VALDATA___V76*/ meltfptr[75], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_45__INSTALL_INITIAL_MACRO @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V78*/ meltfptr[77])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_45__INSTALL_INITIAL_MACRO @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V78*/ meltfptr[77]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V78*/ meltfptr[77]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V79*/ meltfptr[78]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V78*/ meltfptr[77]);


    melt_dbgtrace_written_object (/*_._VALDATA___V78*/ meltfptr[77], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_47__GCCIF @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V80*/ meltfptr[79])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_47__GCCIF @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V80*/ meltfptr[79]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V80*/ meltfptr[79]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V81*/ meltfptr[80]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V80*/ meltfptr[79]);


    melt_dbgtrace_written_object (/*_._VALDATA___V80*/ meltfptr[79], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:225:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V82*/ meltfptr[81])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_49__MEXPANDOBSOLETE_CONTAINER#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V82*/ meltfptr[81])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:225:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V82*/ meltfptr[81])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_49__MEXPANDOBSOLETE_CONTAINER#1", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V82*/ meltfptr[81])->tabval[1] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:225:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V82*/ meltfptr[81])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_49__MEXPANDOBSOLETE_CONTAINER#2", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V82*/ meltfptr[81])->tabval[2] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);

    MELT_LOCATION("warmelt-moremacro.melt:225:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V82*/ meltfptr[81])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_49__MEXPANDOBSOLETE_CONTAINER#3", NULL != (/*_.CLASS_LOCATED__V8*/ meltfptr[7]));
    ((meltroutine_ptr_t)/*_._VALROUT___V82*/ meltfptr[81])->tabval[3] = (melt_ptr_t)(/*_.CLASS_LOCATED__V8*/ meltfptr[7]);

    MELT_LOCATION("warmelt-moremacro.melt:225:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V82*/ meltfptr[81])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_49__MEXPANDOBSOLETE_CONTAINER#4", NULL != (/*_.MEXPAND_REFERENCE__V21*/ meltfptr[20]));
    ((meltroutine_ptr_t)/*_._VALROUT___V82*/ meltfptr[81])->tabval[4] = (melt_ptr_t)(/*_.MEXPAND_REFERENCE__V21*/ meltfptr[20]);

    MELT_LOCATION("warmelt-moremacro.melt:225:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V82*/ meltfptr[81]);

    /*putclosurout#5*/
    melt_assertmsg("putclosrout#5 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V83*/ meltfptr[82])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#5 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V82*/ meltfptr[81])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V83*/ meltfptr[82])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V82*/ meltfptr[81]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V83*/ meltfptr[82]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_51__MEXPAND_REFERENCE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V84*/ meltfptr[83])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_51__MEXPAND_REFERENCE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V84*/ meltfptr[83]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V84*/ meltfptr[83]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V85*/ meltfptr[84]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V84*/ meltfptr[83]);


    melt_dbgtrace_written_object (/*_._VALDATA___V84*/ meltfptr[83], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:232:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V86*/ meltfptr[85])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_53__PATEXPANDOBSOLETE_CONTAINER#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V86*/ meltfptr[85])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:232:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V86*/ meltfptr[85])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_53__PATEXPANDOBSOLETE_CONTAINER#1", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V86*/ meltfptr[85])->tabval[1] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:232:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V86*/ meltfptr[85])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_53__PATEXPANDOBSOLETE_CONTAINER#2", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V86*/ meltfptr[85])->tabval[2] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);

    MELT_LOCATION("warmelt-moremacro.melt:232:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V86*/ meltfptr[85])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_53__PATEXPANDOBSOLETE_CONTAINER#3", NULL != (/*_.CLASS_LOCATED__V8*/ meltfptr[7]));
    ((meltroutine_ptr_t)/*_._VALROUT___V86*/ meltfptr[85])->tabval[3] = (melt_ptr_t)(/*_.CLASS_LOCATED__V8*/ meltfptr[7]);

    MELT_LOCATION("warmelt-moremacro.melt:232:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V86*/ meltfptr[85])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_53__PATEXPANDOBSOLETE_CONTAINER#4", NULL != (/*_.PATEXPAND_REFERENCE__V22*/ meltfptr[21]));
    ((meltroutine_ptr_t)/*_._VALROUT___V86*/ meltfptr[85])->tabval[4] = (melt_ptr_t)(/*_.PATEXPAND_REFERENCE__V22*/ meltfptr[21]);

    MELT_LOCATION("warmelt-moremacro.melt:232:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V86*/ meltfptr[85]);

    /*putclosurout#6*/
    melt_assertmsg("putclosrout#6 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V87*/ meltfptr[86])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#6 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V86*/ meltfptr[85])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V87*/ meltfptr[86])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V86*/ meltfptr[85]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V87*/ meltfptr[86]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_55__PATEXPAND_REFERENCE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V88*/ meltfptr[87])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_55__PATEXPAND_REFERENCE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V88*/ meltfptr[87]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V88*/ meltfptr[87]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V89*/ meltfptr[88]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V88*/ meltfptr[87]);


    melt_dbgtrace_written_object (/*_._VALDATA___V88*/ meltfptr[87], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_57__INSTALL_INITIAL_PATMACRO @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V90*/ meltfptr[89])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_57__INSTALL_INITIAL_PATMACRO @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V90*/ meltfptr[89]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V90*/ meltfptr[89]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V91*/ meltfptr[90]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V90*/ meltfptr[89]);


    melt_dbgtrace_written_object (/*_._VALDATA___V90*/ meltfptr[89], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_59__CONTAINER @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V92*/ meltfptr[91])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_59__CONTAINER @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V92*/ meltfptr[91]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V92*/ meltfptr[91]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V93*/ meltfptr[92]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V92*/ meltfptr[91]);


    melt_dbgtrace_written_object (/*_._VALDATA___V92*/ meltfptr[91], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#1", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[1] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#2", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[2] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);


#undef meltfram__
} /*end of meltmod__WARMELTmiMOREMACRO__initialmeltchunk_0*/



void meltmod__WARMELTmiMOREMACRO__initialmeltchunk_1 (meltinitial_frame_t* meltframptr__, char meltpredefinited[])
{
#define meltfram__ (*meltframptr__)
#undef meltcallcount
#define meltcallcount 0L
    (void) meltpredefinited;
    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#3", NULL != (/*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[3] = (melt_ptr_t)(/*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#4", NULL != (/*_.CLASS_SOURCE_HOOK_CALL__V24*/ meltfptr[23]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[4] = (melt_ptr_t)(/*_.CLASS_SOURCE_HOOK_CALL__V24*/ meltfptr[23]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#5", NULL != (/*_.HOOK_MELT_MAKE_LOCATION__V17*/ meltfptr[16]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[5] = (melt_ptr_t)(/*_.HOOK_MELT_MAKE_LOCATION__V17*/ meltfptr[16]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#6", NULL != (/*_.DISCR_LIST__V25*/ meltfptr[24]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[6] = (melt_ptr_t)(/*_.DISCR_LIST__V25*/ meltfptr[24]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#7", NULL != (/*_.CLASS_KEYWORD__V26*/ meltfptr[25]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[7] = (melt_ptr_t)(/*_.CLASS_KEYWORD__V26*/ meltfptr[25]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#8", NULL != (/*_.CLASS_SYMBOL__V14*/ meltfptr[13]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[8] = (melt_ptr_t)(/*_.CLASS_SYMBOL__V14*/ meltfptr[13]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#9", NULL != (/*_.CLASS_SOURCE_QUOTE__V27*/ meltfptr[26]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[9] = (melt_ptr_t)(/*_.CLASS_SOURCE_QUOTE__V27*/ meltfptr[26]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_71__COMMA @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V95*/ meltfptr[94])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_71__COMMA @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V95*/ meltfptr[94]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V95*/ meltfptr[94]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V96*/ meltfptr[95]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V95*/ meltfptr[94]);


    melt_dbgtrace_written_object (/*_._VALDATA___V95*/ meltfptr[94], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#10", NULL != (/*_._VALDATA___V95*/ meltfptr[94]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[10] = (melt_ptr_t)(/*_._VALDATA___V95*/ meltfptr[94]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#11", NULL != (/*_.LIST_NTH_ELEMENT__V28*/ meltfptr[27]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[11] = (melt_ptr_t)(/*_.LIST_NTH_ELEMENT__V28*/ meltfptr[27]);

    /*putclosurout#7*/
    melt_assertmsg("putclosrout#7 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V97*/ meltfptr[96])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#7 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V97*/ meltfptr[96])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V94*/ meltfptr[93]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V97*/ meltfptr[96]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconstnotnull*/
    /*putroutconstnotnull*/
    melt_assertmsg("putroutconstnotnull checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    melt_assertmsg("putroutconstnotnull notnullconst", NULL != /*_._VALCLO___V97*/ meltfptr[96]);
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[12] = (melt_ptr_t)(/*_._VALCLO___V97*/ meltfptr[96]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#13", NULL != (/*_.LIST_APPEND2LIST__V29*/ meltfptr[28]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[13] = (melt_ptr_t)(/*_.LIST_APPEND2LIST__V29*/ meltfptr[28]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#14", NULL != (/*_.CLASS_SOURCE_APPLY__V30*/ meltfptr[29]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[14] = (melt_ptr_t)(/*_.CLASS_SOURCE_APPLY__V30*/ meltfptr[29]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#15", NULL != (/*_._VALDATA___V62*/ meltfptr[61]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[15] = (melt_ptr_t)(/*_._VALDATA___V62*/ meltfptr[61]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#16", NULL != (/*_.LIST_TO_MULTIPLE__V11*/ meltfptr[10]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[16] = (melt_ptr_t)(/*_.LIST_TO_MULTIPLE__V11*/ meltfptr[10]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V94*/ meltfptr[93])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_61__EXPAND_QUOTED_SEXPR#17", NULL != (/*_.DISCR_MULTIPLE__V12*/ meltfptr[11]));
    ((meltroutine_ptr_t)/*_._VALROUT___V94*/ meltfptr[93])->tabval[17] = (melt_ptr_t)(/*_.DISCR_MULTIPLE__V12*/ meltfptr[11]);

    MELT_LOCATION("warmelt-moremacro.melt:246:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V94*/ meltfptr[93]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_63__CLASS_SOURCE_HOOK_CALL @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V98*/ meltfptr[97])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_63__CLASS_SOURCE_HOOK_CALL @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V98*/ meltfptr[97]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V98*/ meltfptr[97]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V99*/ meltfptr[98]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V98*/ meltfptr[97]);


    melt_dbgtrace_written_object (/*_._VALDATA___V98*/ meltfptr[97], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_65__DISCR_LIST @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V100*/ meltfptr[99])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_65__DISCR_LIST @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V100*/ meltfptr[99]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V100*/ meltfptr[99]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V101*/ meltfptr[100]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V100*/ meltfptr[99]);


    melt_dbgtrace_written_object (/*_._VALDATA___V100*/ meltfptr[99], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_67__CLASS_KEYWORD @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V102*/ meltfptr[101])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_67__CLASS_KEYWORD @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V102*/ meltfptr[101]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V102*/ meltfptr[101]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V103*/ meltfptr[102]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V102*/ meltfptr[101]);


    melt_dbgtrace_written_object (/*_._VALDATA___V102*/ meltfptr[101], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_69__CLASS_SOURCE_QUOTE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V104*/ meltfptr[103])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_69__CLASS_SOURCE_QUOTE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V104*/ meltfptr[103]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V104*/ meltfptr[103]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V105*/ meltfptr[104]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V104*/ meltfptr[103]);


    melt_dbgtrace_written_object (/*_._VALDATA___V104*/ meltfptr[103], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_73__LIST_NTH_ELEMENT @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V106*/ meltfptr[105])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_73__LIST_NTH_ELEMENT @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V106*/ meltfptr[105]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V106*/ meltfptr[105]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V107*/ meltfptr[106]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V106*/ meltfptr[105]);


    melt_dbgtrace_written_object (/*_._VALDATA___V106*/ meltfptr[105], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_75__LIST_APPEND2LIST @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V108*/ meltfptr[107])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_75__LIST_APPEND2LIST @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V108*/ meltfptr[107]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V108*/ meltfptr[107]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V109*/ meltfptr[108]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V108*/ meltfptr[107]);


    melt_dbgtrace_written_object (/*_._VALDATA___V108*/ meltfptr[107], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_77__CLASS_SOURCE_APPLY @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V110*/ meltfptr[109])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_77__CLASS_SOURCE_APPLY @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V110*/ meltfptr[109]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V110*/ meltfptr[109]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V111*/ meltfptr[110]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V110*/ meltfptr[109]);


    melt_dbgtrace_written_object (/*_._VALDATA___V110*/ meltfptr[109], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#0", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[0] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#1", NULL != (/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[1] = (melt_ptr_t)(/*_.MELT_ASSERT_FAILURE_FUN__V10*/ meltfptr[9]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#2", NULL != (/*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[2] = (melt_ptr_t)(/*_.CLASS_ENVIRONMENT__V18*/ meltfptr[17]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#3", NULL != (/*_.ERROR_AT__V31*/ meltfptr[30]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[3] = (melt_ptr_t)(/*_.ERROR_AT__V31*/ meltfptr[30]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#4", NULL != (/*_.CLASS_SYMBOL__V14*/ meltfptr[13]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[4] = (melt_ptr_t)(/*_.CLASS_SYMBOL__V14*/ meltfptr[13]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#5", NULL != (/*_.CLASS_SOURCE__V32*/ meltfptr[31]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[5] = (melt_ptr_t)(/*_.CLASS_SOURCE__V32*/ meltfptr[31]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#6", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[6] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconstnotnull*/
    /*putroutconstnotnull*/
    melt_assertmsg("putroutconstnotnull checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    melt_assertmsg("putroutconstnotnull notnullconst", NULL != /*_._VALCLO___V97*/ meltfptr[96]);
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[7] = (melt_ptr_t)(/*_._VALCLO___V97*/ meltfptr[96]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#8", NULL != (/*_.CLASS_KEYWORD__V26*/ meltfptr[25]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[8] = (melt_ptr_t)(/*_.CLASS_KEYWORD__V26*/ meltfptr[25]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_79__MEXPAND_QUOTE#9", NULL != (/*_.CLASS_SOURCE_QUOTE__V27*/ meltfptr[26]));
    ((meltroutine_ptr_t)/*_._VALROUT___V112*/ meltfptr[111])->tabval[9] = (melt_ptr_t)(/*_.CLASS_SOURCE_QUOTE__V27*/ meltfptr[26]);

    MELT_LOCATION("warmelt-moremacro.melt:327:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V112*/ meltfptr[111]);

    /*putclosurout#8*/
    melt_assertmsg("putclosrout#8 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V113*/ meltfptr[112])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#8 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V112*/ meltfptr[111])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V113*/ meltfptr[112])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V112*/ meltfptr[111]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V113*/ meltfptr[112]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_81__ERROR_AT @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V114*/ meltfptr[113])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_81__ERROR_AT @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V114*/ meltfptr[113]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V114*/ meltfptr[113]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V115*/ meltfptr[114]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V114*/ meltfptr[113]);


    melt_dbgtrace_written_object (/*_._VALDATA___V114*/ meltfptr[113], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_83__CLASS_SOURCE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V116*/ meltfptr[115])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_83__CLASS_SOURCE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V116*/ meltfptr[115]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V116*/ meltfptr[115]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V117*/ meltfptr[116]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V116*/ meltfptr[115]);


    melt_dbgtrace_written_object (/*_._VALDATA___V116*/ meltfptr[115], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_85__QUOTE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V118*/ meltfptr[117])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_85__QUOTE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V118*/ meltfptr[117]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V118*/ meltfptr[117]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V119*/ meltfptr[118]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V118*/ meltfptr[117]);


    melt_dbgtrace_written_object (/*_._VALDATA___V118*/ meltfptr[117], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:379:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V120*/ meltfptr[119])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_87__ANTIQUOTER#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V120*/ meltfptr[119])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:379:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V120*/ meltfptr[119]);

    /*putclosurout#9*/
    melt_assertmsg("putclosrout#9 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V121*/ meltfptr[120])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#9 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V120*/ meltfptr[119])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V121*/ meltfptr[120])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V120*/ meltfptr[119]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V121*/ meltfptr[120]);

    MELT_LOCATION("warmelt-moremacro.melt:393:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V122*/ meltfptr[121])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_89__MEXPAND_BACKQUOTE#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V122*/ meltfptr[121])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:393:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V122*/ meltfptr[121])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_89__MEXPAND_BACKQUOTE#1", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V122*/ meltfptr[121])->tabval[1] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:393:/ initchunk");
    /*^putroutconstnotnull*/
    /*putroutconstnotnull*/
    melt_assertmsg("putroutconstnotnull checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V122*/ meltfptr[121])) == MELTOBMAG_ROUTINE);
    melt_assertmsg("putroutconstnotnull notnullconst", NULL != /*_._VALCLO___V97*/ meltfptr[96]);
    ((meltroutine_ptr_t)/*_._VALROUT___V122*/ meltfptr[121])->tabval[2] = (melt_ptr_t)(/*_._VALCLO___V97*/ meltfptr[96]);

    MELT_LOCATION("warmelt-moremacro.melt:393:/ initchunk");
    /*^putroutconstnotnull*/
    /*putroutconstnotnull*/
    melt_assertmsg("putroutconstnotnull checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V122*/ meltfptr[121])) == MELTOBMAG_ROUTINE);
    melt_assertmsg("putroutconstnotnull notnullconst", NULL != /*_._VALCLO___V121*/ meltfptr[120]);
    ((meltroutine_ptr_t)/*_._VALROUT___V122*/ meltfptr[121])->tabval[3] = (melt_ptr_t)(/*_._VALCLO___V121*/ meltfptr[120]);

    MELT_LOCATION("warmelt-moremacro.melt:393:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V122*/ meltfptr[121]);

    /*putclosurout#10*/
    melt_assertmsg("putclosrout#10 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V123*/ meltfptr[122])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#10 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V122*/ meltfptr[121])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V123*/ meltfptr[122])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V122*/ meltfptr[121]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V123*/ meltfptr[122]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_91__BACKQUOTE @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V124*/ meltfptr[123])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_91__BACKQUOTE @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V124*/ meltfptr[123]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V124*/ meltfptr[123]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V125*/ meltfptr[124]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V124*/ meltfptr[123]);


    melt_dbgtrace_written_object (/*_._VALDATA___V124*/ meltfptr[123], "new static instance");

    MELT_LOCATION("warmelt-moremacro.melt:423:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V126*/ meltfptr[125])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_93__MEXPAND_COMMA#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V126*/ meltfptr[125])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:423:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V126*/ meltfptr[125]);

    /*putclosurout#11*/
    melt_assertmsg("putclosrout#11 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V127*/ meltfptr[126])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#11 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V126*/ meltfptr[125])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V127*/ meltfptr[126])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V126*/ meltfptr[125]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V127*/ meltfptr[126]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_95__SUBSTITUTE_SEXPR#0", NULL != (/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]));
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[0] = (melt_ptr_t)(/*_.MELT_DEBUG_FUN__V6*/ meltfptr[5]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_95__SUBSTITUTE_SEXPR#1", NULL != (/*_.CLASS_SEXPR__V9*/ meltfptr[8]));
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[1] = (melt_ptr_t)(/*_.CLASS_SEXPR__V9*/ meltfptr[8]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_95__SUBSTITUTE_SEXPR#2", NULL != (/*_.DISCR_LIST__V25*/ meltfptr[24]));
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[2] = (melt_ptr_t)(/*_.DISCR_LIST__V25*/ meltfptr[24]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_95__SUBSTITUTE_SEXPR#3", NULL != (/*_.CLASS_SEXPR_MACROSTRING__V33*/ meltfptr[32]));
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[3] = (melt_ptr_t)(/*_.CLASS_SEXPR_MACROSTRING__V33*/ meltfptr[32]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_95__SUBSTITUTE_SEXPR#4", NULL != (/*_.CLASS_KEYWORD__V26*/ meltfptr[25]));
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[4] = (melt_ptr_t)(/*_.CLASS_KEYWORD__V26*/ meltfptr[25]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconst*/
    /*putroutconst*/
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_assertmsg("putroutconst checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    if (MELT_HAS_INITIAL_ENVIRONMENT) melt_checkmsg("putroutconst constnull.drout_95__SUBSTITUTE_SEXPR#5", NULL != (/*_.CLASS_SYMBOL__V14*/ meltfptr[13]));
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[5] = (melt_ptr_t)(/*_.CLASS_SYMBOL__V14*/ meltfptr[13]);

    /*putclosurout#12*/
    melt_assertmsg("putclosrout#12 checkclo", melt_magic_discr((melt_ptr_t)(/*_._VALCLO___V129*/ meltfptr[128])) == MELTOBMAG_CLOSURE);
    melt_assertmsg("putclosrout#12 checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    ((meltclosure_ptr_t)/*_._VALCLO___V129*/ meltfptr[128])->rout = (meltroutine_ptr_t) (/*_._VALROUT___V128*/ meltfptr[127]);

    /*touch:_DATACLOSURE_*/
    meltgc_touch(/*_._VALCLO___V129*/ meltfptr[128]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^putroutconstnotnull*/
    /*putroutconstnotnull*/
    melt_assertmsg("putroutconstnotnull checkrout", melt_magic_discr((melt_ptr_t)(/*_._VALROUT___V128*/ meltfptr[127])) == MELTOBMAG_ROUTINE);
    melt_assertmsg("putroutconstnotnull notnullconst", NULL != /*_._VALCLO___V129*/ meltfptr[128]);
    ((meltroutine_ptr_t)/*_._VALROUT___V128*/ meltfptr[127])->tabval[6] = (melt_ptr_t)(/*_._VALCLO___V129*/ meltfptr[128]);

    MELT_LOCATION("warmelt-moremacro.melt:441:/ initchunk");
    /*^touch*/
    /*touch:_IROUTVAL_*/
    meltgc_touch(/*_._VALROUT___V128*/ meltfptr[127]);

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_97__CLASS_SEXPR_MACROSTRING @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V130*/ meltfptr[129])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_97__CLASS_SEXPR_MACROSTRING @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V130*/ meltfptr[129]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V130*/ meltfptr[129]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V131*/ meltfptr[130]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V130*/ meltfptr[129]);


    melt_dbgtrace_written_object (/*_._VALDATA___V130*/ meltfptr[129], "new static instance");

    /*putslot*/
    melt_assertmsg("checkobj putslot  ~dsym_99__SUBSTITUTE_SEXPR @#1", melt_magic_discr((melt_ptr_t)(/*_._VALDATA___V132*/ meltfptr[131])) == MELTOBMAG_OBJECT);

    melt_assertmsg("checkoff putslot  ~dsym_99__SUBSTITUTE_SEXPR @#1", (1>=0 && 1< melt_object_length((melt_ptr_t)(/*_._VALDATA___V132*/ meltfptr[131]))));
    ((meltobject_ptr_t)(/*_._VALDATA___V132*/ meltfptr[131]))->obj_vartab[1] = (melt_ptr_t)(
                /*_._VALSTR___V133*/ meltfptr[132]);

    /*touch:_VALUEDATA_*/
    meltgc_touch(/*_._VALDATA___V132*/ meltfptr[131]);


    melt_dbgtrace_written_object (/*_._VALDATA___V132*/ meltfptr[131], "new static instance");

    /**COMMENT: before toplevel body **/;

    MELT_LOCATION("warmelt-moremacro.melt:3:/ initchunk");
    /*^block*/
    /*anyblock*/
    {

        /*^cond*/
        /*cond*/ if (
            /*quasi.cur.mod.env.ref cur.mod.env.cont : at very start*/
            /* check quasi.cur.mod.env.ref 554675637 */
            (/*_._CONTENV___V2*/ meltfptr[1])
        ) /*then*/
            {
                /*^cond.then*/
                /*_.OR___V134*/ meltfptr[133] =
                    /*quasi.cur.mod.env.ref cur.mod.env.cont : at very start*/
                    /* check quasi.cur.mod.env.ref 554675637 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                    ;;
            }
        else
            {
                MELT_LOCATION("warmelt-moremacro.melt:3:/ cond.else");

                /*^block*/
                /*anyblock*/
                {

                    /*_.HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER__V135*/ meltfptr[134] =
                        /*hookcall*/ melthook_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER ((melt_ptr_t) /*_.HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER__V5*/ meltfptr[4], /*_._PREVENV___V4*/ meltfptr[3],  "warmelt-moremacro") ;;
                    /*^compute*/
                    /*_.OR___V134*/ meltfptr[133] = /*_.HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER__V135*/ meltfptr[134];;
                    /*epilog*/

                    MELT_LOCATION("warmelt-moremacro.melt:3:/ clear");
                    /*clear*/ /*_.HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER__V135*/ meltfptr[134] = 0 ;
                }
                ;
            }
        ;
        /*^block*/
        /*com.block:upd.cur.mod.env.cont : at very start*/
        {
        }/*com.end block:upd.cur.mod.env.cont : at very start*/
        ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.OR___V134*/ meltfptr[133] = 0 ;
    }

    MELT_LOCATION("warmelt-moremacro.melt:112:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        {
            /*hookcall*/ melthook_HOOK_MACRO_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_MACRO_EXPORTER))), /*_._VALDATA___V66*/ meltfptr[65], /*_._VALCLO___V41*/ meltfptr[40],
                    /*quasi.cur.mod.env.ref norm.exp.val : EACH_COMPONENT_IN_LIST*/
                    /* check quasi.cur.mod.env.ref 455243675 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                                                      ) ;
        }
        ;
        /*epilog*/
    }

    MELT_LOCATION("warmelt-moremacro.melt:214:/ initchunk");
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
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_._VALCLO___V73*/ meltfptr[72];
            /*_.INSTALL_INITIAL_MACRO__V136*/ meltfptr[134] =  melt_apply ((meltclosure_ptr_t)(/*_.INSTALL_INITIAL_MACRO__V20*/ meltfptr[19]), (melt_ptr_t)(/*_._VALDATA___V80*/ meltfptr[79]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.INSTALL_INITIAL_MACRO__V136*/ meltfptr[134] = 0 ;
    }

    MELT_LOCATION("warmelt-moremacro.melt:215:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        {
            /*hookcall*/ melthook_HOOK_MACRO_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_MACRO_EXPORTER))), /*_._VALDATA___V80*/ meltfptr[79], /*_._VALCLO___V73*/ meltfptr[72],
                    /*quasi.cur.mod.env.ref norm.exp.val : GCCIF*/
                    /* check quasi.cur.mod.env.ref 1008021013 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                                                      ) ;
        }
        ;
        /*epilog*/
    }

    MELT_LOCATION("warmelt-moremacro.melt:239:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        MELT_CHECK_SIGNAL();
        ;
        /*^apply*/
        /*apply*/
        {
            union meltparam_un argtab[2];
            memset(&argtab, 0, sizeof(argtab));
            /*^apply.arg*/
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_._VALCLO___V87*/ meltfptr[86];
            /*^apply.arg*/
            argtab[1].meltbp_aptr = (melt_ptr_t*) &/*_._VALCLO___V83*/ meltfptr[82];
            /*_.INSTALL_INITIAL_PATMACRO__V137*/ meltfptr[133] =  melt_apply ((meltclosure_ptr_t)(/*_.INSTALL_INITIAL_PATMACRO__V23*/ meltfptr[22]), (melt_ptr_t)(/*_._VALDATA___V92*/ meltfptr[91]), (MELTBPARSTR_PTR MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.INSTALL_INITIAL_PATMACRO__V137*/ meltfptr[133] = 0 ;
    }

    MELT_LOCATION("warmelt-moremacro.melt:240:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        {
            /*hookcall*/ melthook_HOOK_PATMACRO_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_PATMACRO_EXPORTER))), /*_._VALDATA___V92*/ meltfptr[91], /*_._VALCLO___V83*/ meltfptr[82], /*_._VALCLO___V87*/ meltfptr[86],
                    /*quasi.cur.mod.env.ref norm.exp.pat : CONTAINER*/
                    /* check quasi.cur.mod.env.ref 344559395 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                                                         ) ;
        }
        ;
        /*epilog*/
    }

    MELT_LOCATION("warmelt-moremacro.melt:366:/ initchunk");
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
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_._VALCLO___V113*/ meltfptr[112];
            /*_.INSTALL_INITIAL_MACRO__V138*/ meltfptr[134] =  melt_apply ((meltclosure_ptr_t)(/*_.INSTALL_INITIAL_MACRO__V20*/ meltfptr[19]), (melt_ptr_t)(/*_._VALDATA___V118*/ meltfptr[117]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.INSTALL_INITIAL_MACRO__V138*/ meltfptr[134] = 0 ;
    }

    MELT_LOCATION("warmelt-moremacro.melt:367:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        {
            /*hookcall*/ melthook_HOOK_MACRO_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_MACRO_EXPORTER))), /*_._VALDATA___V118*/ meltfptr[117], /*_._VALCLO___V113*/ meltfptr[112],
                    /*quasi.cur.mod.env.ref norm.exp.val : QUOTE*/
                    /* check quasi.cur.mod.env.ref 957696318 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                                                      ) ;
        }
        ;
        /*epilog*/
    }

    MELT_LOCATION("warmelt-moremacro.melt:413:/ initchunk");
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
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_._VALCLO___V123*/ meltfptr[122];
            /*_.INSTALL_INITIAL_MACRO__V139*/ meltfptr[133] =  melt_apply ((meltclosure_ptr_t)(/*_.INSTALL_INITIAL_MACRO__V20*/ meltfptr[19]), (melt_ptr_t)(/*_._VALDATA___V124*/ meltfptr[123]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.INSTALL_INITIAL_MACRO__V139*/ meltfptr[133] = 0 ;
    }

    MELT_LOCATION("warmelt-moremacro.melt:414:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        {
            /*hookcall*/ melthook_HOOK_MACRO_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_MACRO_EXPORTER))), /*_._VALDATA___V124*/ meltfptr[123], /*_._VALCLO___V123*/ meltfptr[122],
                    /*quasi.cur.mod.env.ref norm.exp.val : BACKQUOTE*/
                    /* check quasi.cur.mod.env.ref 870072386 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                                                      ) ;
        }
        ;
        /*epilog*/
    }

    MELT_LOCATION("warmelt-moremacro.melt:431:/ initchunk");
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
            argtab[0].meltbp_aptr = (melt_ptr_t*) &/*_._VALCLO___V127*/ meltfptr[126];
            /*_.INSTALL_INITIAL_MACRO__V140*/ meltfptr[134] =  melt_apply ((meltclosure_ptr_t)(/*_.INSTALL_INITIAL_MACRO__V20*/ meltfptr[19]), (melt_ptr_t)(/*_._VALDATA___V95*/ meltfptr[94]), (MELTBPARSTR_PTR ""), argtab, "", (union meltparam_un*)0);
        }
        ;
        /*epilog*/

        /*^clear*/
        /*clear*/ /*_.INSTALL_INITIAL_MACRO__V140*/ meltfptr[134] = 0 ;
    }

    MELT_LOCATION("warmelt-moremacro.melt:432:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        {
            /*hookcall*/ melthook_HOOK_MACRO_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_MACRO_EXPORTER))), /*_._VALDATA___V95*/ meltfptr[94], /*_._VALCLO___V127*/ meltfptr[126],
                    /*quasi.cur.mod.env.ref norm.exp.val : COMMA*/
                    /* check quasi.cur.mod.env.ref 379678941 */
                    (/*_._CONTENV___V2*/ meltfptr[1])
                                                      ) ;
        }
        ;
        /*epilog*/
    }

    MELT_LOCATION("warmelt-moremacro.melt:525:/ initchunk");
    /*^block*/
    /*anyblock*/
    {


        /*hookcall*/ melthook_HOOK_VALUE_EXPORTER ((melt_ptr_t) ((melt_ptr_t)(MELT_PREDEF(HOOK_VALUE_EXPORTER))), /*_._VALDATA___V132*/ meltfptr[131], /*_._VALCLO___V129*/ meltfptr[128],
                /*quasi.cur.mod.env.ref norm.exp.val : SUBSTITUTE_SEXPR*/
                /* check quasi.cur.mod.env.ref 628768140 */
                (/*_._CONTENV___V2*/ meltfptr[1])
                                                  ) ;
        /*epilog*/
    }

    /**COMMENT: after toplevel body **/;

    /**COMMENT: compute boxloc again **/;

    /*cond*/ if (/*_._CONTENV___V2*/ meltfptr[1]) /*then*/
        {
        }
    else    /*^cond.else*/
        {

            /*^compute*/

            /* compile2obj_initproc emitted initialization of environment reference for warmelt-moremacro */
            if (/*_._PREVENV___V4*/ meltfptr[3])
                {
                    /*_._CONTENV___V2*/ meltfptr[1] = melthookproc_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER
                                                      ((melt_ptr_t) /*_._PREVENV___V4*/ meltfptr[3], "warmelt-moremacro") ;
                }
            else /* no prevenv */
                {
#if MELT_HAS_INITIAL_ENVIRONMENT>0
                    if (!melt_flag_bootstrapping)
                        warning(0, "MELT is not creating a fresh environment reference for warmelt-moremacro without parent env.") ;
#endif /* MELT_HAS_INITIAL_ENVIRONMENT>0 */
                }
            ;;
        }

    /**COMMENT: intern symbols **/;

    /*internsym:HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V34*/ meltfptr[33]));

    /*internsym:MELT_DEBUG_FUN*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V42*/ meltfptr[41]));

    /*internsym:DEBUG_LESS*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V44*/ meltfptr[43]));

    /*internsym:CLASS_LOCATED*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V46*/ meltfptr[45]));

    /*internsym:CLASS_SEXPR*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V48*/ meltfptr[47]));

    /*internsym:MELT_ASSERT_FAILURE_FUN*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V50*/ meltfptr[49]));

    /*internsym:LIST_TO_MULTIPLE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V52*/ meltfptr[51]));

    /*internsym:DISCR_MULTIPLE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V54*/ meltfptr[53]));

    /*internsym:EXPAND_TUPLE_SLICE_AS_TUPLE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V56*/ meltfptr[55]));

    /*internsym:CLASS_SYMBOL*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V58*/ meltfptr[57]));

    /*internsym:CLONE_SYMBOL*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V60*/ meltfptr[59]));

    /*internsym:CURPAIRINLISTSYMB*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V37*/ meltfptr[36]));


#undef meltfram__
} /*end of meltmod__WARMELTmiMOREMACRO__initialmeltchunk_1*/



void meltmod__WARMELTmiMOREMACRO__initialmeltchunk_2 (meltinitial_frame_t* meltframptr__, char meltpredefinited[])
{
#define meltfram__ (*meltframptr__)
#undef meltcallcount
#define meltcallcount 0L
    (void) meltpredefinited;
    /*internsym:MELT_MAKE_SEXPR*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V62*/ meltfptr[61]));

    /*internsym:HOOK_MELT_MAKE_LOCATION*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V64*/ meltfptr[63]));

    /*internsym:FOREACH_PAIR_COMPONENT_IN_LIST*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V39*/ meltfptr[38]));

    /*internsym:EACH_COMPONENT_IN_LIST*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V66*/ meltfptr[65]));

    /*internsym:CLASS_ENVIRONMENT*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V74*/ meltfptr[73]));

    /*internsym:EXPAND_PAIRLIST_AS_LIST*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V76*/ meltfptr[75]));

    /*internkeyw:TRUE*/
    (void) melthookproc_HOOK_INTERN_KEYWORD ((melt_ptr_t)(/*_._VALDATA___V71*/ meltfptr[70]));

    /*internsym:INSTALL_INITIAL_MACRO*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V78*/ meltfptr[77]));

    /*internsym:GCCIF*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V80*/ meltfptr[79]));

    /*internsym:MEXPAND_REFERENCE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V84*/ meltfptr[83]));

    /*internsym:PATEXPAND_REFERENCE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V88*/ meltfptr[87]));

    /*internsym:INSTALL_INITIAL_PATMACRO*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V90*/ meltfptr[89]));

    /*internsym:CONTAINER*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V92*/ meltfptr[91]));

    /*internsym:CLASS_SOURCE_HOOK_CALL*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V98*/ meltfptr[97]));

    /*internsym:DISCR_LIST*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V100*/ meltfptr[99]));

    /*internsym:CLASS_KEYWORD*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V102*/ meltfptr[101]));

    /*internsym:CLASS_SOURCE_QUOTE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V104*/ meltfptr[103]));

    /*internsym:COMMA*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V95*/ meltfptr[94]));

    /*internsym:LIST_NTH_ELEMENT*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V106*/ meltfptr[105]));

    /*internsym:LIST_APPEND2LIST*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V108*/ meltfptr[107]));

    /*internsym:CLASS_SOURCE_APPLY*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V110*/ meltfptr[109]));

    /*internsym:ERROR_AT*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V114*/ meltfptr[113]));

    /*internsym:CLASS_SOURCE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V116*/ meltfptr[115]));

    /*internsym:QUOTE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V118*/ meltfptr[117]));

    /*internsym:BACKQUOTE*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V124*/ meltfptr[123]));

    /*internsym:CLASS_SEXPR_MACROSTRING*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V130*/ meltfptr[129]));

    /*internsym:SUBSTITUTE_SEXPR*/
    (void) melthookproc_HOOK_INTERN_SYMBOL ((melt_ptr_t)(/*_._VALDATA___V132*/ meltfptr[131]));

    /**COMMENT: set retinit from boxloc **/;

    /*_._RETINIT___V1*/ meltfptr[0] =
        /* finalsetretinit */ melt_reference_value((melt_ptr_t)(/*_._CONTENV___V2*/ meltfptr[1]));
    /**COMMENT: end the initproc **/;


#undef meltfram__
} /*end of meltmod__WARMELTmiMOREMACRO__initialmeltchunk_2*/






/* exported 0 field offsets */

/* exported 0 class lengths */



/**** end of warmelt-moremacro ****/
