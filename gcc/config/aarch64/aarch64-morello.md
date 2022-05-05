;; AArch64 ldp/stp peephole optimizations.
;; Copyright (C) 2021 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;; General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

; TODO: check syntax is OK for TARGET_MORELLO.
; TODO: more alternatives.
(define_insn "pointer_plus_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk,rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "rk,rk")
	  (match_operand:DI 2 "aarch64_pluslong_operand" "Ir,J")))]
  "TARGET_CAPABILITY_ANY"
  "@
  add\\t%0, %1, %2
  sub\\t%0, %1, #%n2"
)

(define_insn "*pointer_plus_lsl_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=r")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (ashift:DI (match_operand:DI 2 "register_operand" "r")
		     (match_operand:QI 3 "aarch64_imm3"))))]
  "TARGET_CAPABILITY_ANY"
  "add\\t%0, %1, %2, lsl %3"
  [(set_attr "type" "alu_shift_imm")]
)

(define_insn "*pointer_plus_multp2_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (mult:DI (match_operand:DI 2 "register_operand" "r")
		   (match_operand:DI 3 "aarch64_pwr_imm3"))))]
  "TARGET_CAPABILITY_ANY"
  "add\t%0, %1, %2, lsl %p3"
  [(set_attr "type" "alu_shift_imm")]
)

(define_insn "*pointer_plus_<optab><ALLX:mode>_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (ANY_EXTEND:DI (match_operand:ALLX 2 "register_operand" "r"))))]
  "TARGET_CAPABILITY_ANY"
  "add\t%0, %1, %w2, <su>xt<ALLX:size>"
  [(set_attr "type" "alu_ext")]
)

(define_insn "*pointer_plus_<optab><ALLX:mode>_lsl_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (ashift:DI
	    (ANY_EXTEND:DI
	      (match_operand:ALLX 2 "register_operand" "r"))
	    (match_operand 3 "aarch64_imm3"))))]
  "TARGET_CAPABILITY_ANY"
  "add\t%0, %1, %w2, <su>xt<ALLX:size> %3"
  [(set_attr "type" "alu_ext")]
)

(define_insn "*pointer_plus_<optab><ALLX:mode>_multp2_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (mult:DI
	    (ANY_EXTEND:DI
	      (match_operand:ALLX 2 "register_operand" "r"))
	    (match_operand:DI 3 "aarch64_pwr_imm3"))))]
  "TARGET_CAPABILITY_ANY"
  "add\t%0, %1, %w2, <su>xt<ALLX:size> %p3"
  [(set_attr "type" "alu_ext")]
)

(define_insn "*pointer_plus_<optab>_multp2_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (ANY_EXTRACT:DI
	    (mult:DI (match_operand:DI 2 "register_operand" "r")
		     (match_operand:DI 3 "aarch64_pwr_imm3"))
	    (match_operand 4 "const_int_operand")
	    (const_int 0))))]
  "TARGET_CAPABILITY_ANY
   && aarch64_is_extend_from_extract (DImode, operands[3], operands[4])"
  "add\t%0, %1, %w2, <su>xt%e4 %p3"
  [(set_attr "type" "alu_ext")]
)

(define_insn "*pointer_plus_and_lsl_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (and:DI
	    (ashift:DI (match_operand:DI 2 "register_operand" "r")
		       (match_operand 3 "aarch64_imm3"))
	    (match_operand:DI 4 "const_int_operand"))))]
  "TARGET_CAPABILITY_ANY
   && aarch64_uxt_size (INTVAL (operands[3]), INTVAL (operands[4])) != 0"
  {
    operands[4] = GEN_INT (aarch64_uxt_size (INTVAL (operands[3]),
					     INTVAL (operands[4])));
    return "add\t%0, %1, %w2, uxt%e4 %3";
  }
  [(set_attr "type" "alu_ext")]
)

(define_insn "*pointer_plus_uxt_multp2_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
	(pointer_plus:CADI
	  (match_operand:CADI 1 "register_operand" "r")
	  (and:DI
	    (mult:DI (match_operand:DI 2 "register_operand" "r")
		     (match_operand 3 "aarch64_pwr_imm3"))
	    (match_operand 4 "const_int_operand"))))]
  "TARGET_CAPABILITY_ANY
   && aarch64_uxt_size (exact_log2 (INTVAL (operands[3])),
			INTVAL (operands[4])) != 0"
  {
    operands[4] = GEN_INT (aarch64_uxt_size (exact_log2 (INTVAL (operands[3])),
					     INTVAL (operands[4])));
    return "add\t%0, %1, %w2, uxt%e4 %p3";
  }
  [(set_attr "type" "alu_ext")]
)

; TODO: many more alternatives.
(define_insn "*movcadi_aarch64"
  [(set (match_operand:CADI 0 "nonimmediate_operand" "=rk,r,r,m,r,r")
	(match_operand:CADI 1 "aarch64_mov_operand" "rk,Z,m,rZ,Usa,Ush"))]
  "TARGET_CAPABILITY_FAKE"
  "@
   mov\\t%0, %1
   mov\\t%0, xzr
   ldr\\t%0, %1
   str\\t%1, %0
   adr\\t%0, %c1
   adrp\\t%0, %A1"
)

(define_insn "replace_address_value_cadi"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (replace_address_value:CADI
	      (match_operand:CADI 1 "register_operand" "rk")
	      (match_operand:DI 2 "register_operand" "r")))]
  "TARGET_CAPABILITY_ANY"
{
  return TARGET_MORELLO ? "scvalue\t%0, %1, %2" : "mov\t%0, %2";
})

(define_insn "*movcadi_aarch64"
  [(set (match_operand:CADI 0 "nonimmediate_operand" "=rk,r,r,m, r  ,r  ")
	(match_operand:CADI 1 "aarch64_mov_operand"  "rk ,Z,m,rZ,Usa,Ush"))]
  "TARGET_MORELLO"
  "@
  mov\\t%0, %1
  mov\\t%x0, xzr
  ldr\\t%0, %1
  str\\t%B1, %0
  adr\\t%0, %c1
  adrp\\t%0, %A1"
)

;; CHERI builtins helpers.

(define_insn "aarch64_cap_base_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_BASE_GET))
  ]
  "TARGET_MORELLO"
  "gcbase\\t%0, %1"
)

(define_insn "aarch64_cap_length_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_LEN_GET))
  ]
  "TARGET_MORELLO"
  "gclen\\t%0, %1"
)

(define_insn "aarch64_cap_repr_align_mask"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")]
            UNSPEC_CHERI_REPR_ALIGN_MASK)
    )]
  "TARGET_MORELLO"
  "rrmask\\t%0, %1"
)

(define_insn "aarch64_cap_round_repr_len"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")]
           UNSPEC_CHERI_ROUND_REPR_LEN)
    )]
  "TARGET_MORELLO"
  "rrlen\\t%0, %1"
)

(define_insn "aarch64_cap_bounds_set"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:DI 2 "register_operand" "r")]
            UNSPEC_CHERI_BOUNDS_SET))
  ]
  "TARGET_MORELLO"
  "scbnds\\t%0, %1, %2"
)

(define_insn "aarch64_cap_bounds_set_exact"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:DI 2 "register_operand" "r")]
            UNSPEC_CHERI_BOUNDS_SET_EXACT))
  ]
  "TARGET_MORELLO"
  "scbndse\\t%0, %1, %2"
)

(define_insn "aarch64_cap_seal"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:CADI 2 "register_operand" "rk")]
            UNSPEC_CHERI_SEAL))
  ]
  "TARGET_MORELLO"
  "seal\\t%0, %1, %2"
)

(define_insn "aarch64_cap_clear_perm"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:DI 2 "register_operand" "r")]
            UNSPEC_CHERI_CLEAR_PERM))
  ]
  "TARGET_MORELLO"
  "clrperm\\t%0, %1, %2"
)

(define_insn "cap_global_data_get"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(const_int 0)]
            UNSPEC_CHERI_GLOBAL_DATA_GET))]
  "TARGET_MORELLO"
  "mrs\\t%0, DDC"
)

(define_expand "aarch64_cap_perms_and"
  [(match_operand:CADI 0 "register_operand")
   (match_operand:CADI 1 "register_operand")
   (match_operand:DI 2 "register_operand")]
  "TARGET_MORELLO"
  {
    emit_insn (gen_one_cmpldi2 (operands[2], operands[2]));
    emit_insn (gen_aarch64_cap_clear_perm (operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn "aarch64_cap_offset_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_OFFSET_GET))
  ]
  "TARGET_MORELLO"
  "gcoff\\t%0, %1"
)

(define_insn "aarch64_cap_offset_set"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:DI 2 "register_operand" "r")]
            UNSPEC_CHERI_OFFSET_SET))
     ]
  "TARGET_MORELLO"
  "scoff\\t%0, %1, %2"
)

(define_insn "aarch64_cap_address_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_ADDR_GET))
  ]
  "TARGET_MORELLO"
  "gcvalue\\t%0, %1"
)

(define_insn "aarch64_cap_tag_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_TAG_GET))
  ]
  "TARGET_MORELLO"
  "gctag\\t%0, %1"
)

(define_insn "aarch64_cap_tag_clear"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_TAG_CLEAR))
  ]
  "TARGET_MORELLO"
  "clrtag\\t%0, %1"
)

(define_insn "aarch64_cap_build"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:CADI 2 "register_operand" "rk")]
            UNSPEC_CHERI_CAP_BUILD))
     ]
  "TARGET_MORELLO"
  "build\\t%0, %2, %1"
)

(define_insn "aarch64_cap_cond_seal"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:CADI 2 "register_operand" "rk")]
            UNSPEC_CHERI_COND_SEAL))
     ]
  "TARGET_MORELLO"
  "cseal\\t%0, %1, %2"
)

(define_insn "aarch64_cap_type_copy"
  [(set (match_operand:CADI 0 "register_operand" "=r")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "r")
          (match_operand:CADI 2 "register_operand" "r")]
            UNSPEC_CHERI_CAP_TYPE_COPY))
     ]
  "TARGET_MORELLO"
  "cpytype\\t%0, %1, %2"
)

(define_insn "aarch64_cap_bit_equality"
  [(set (reg:CC_Z CC_REGNUM)
        (unspec:CC_Z [(match_operand:CADI 0 "register_operand" "rk")
                    (match_operand:CADI 1 "register_operand" "r")]
          UNSPEC_CHERI_BIT_EQ)
        )]
  "TARGET_MORELLO"
  "chkeq\\t%0, %1"
)

(define_expand "aarch64_cap_equal_exact"
  [(match_operand:SI 0 "register_operand")
   (match_operand:CADI 1 "register_operand")
   (match_operand:CADI 2 "register_operand")]
  "TARGET_MORELLO"
  {
    rtx chkeq = gen_aarch64_cap_bit_equality (operands[1], operands[2]);
    rtx cc = SET_DEST (chkeq);
    emit_insn (chkeq);
    rtx compare = gen_rtx_EQ (GET_MODE (operands[0]), cc, const0_rtx);
    emit_insn (gen_rtx_SET (operands[0], compare));
    DONE;
  }
)

(define_insn "aarch64_cap_flags_set"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "rk")
          (match_operand:DI 2 "register_operand" "r")]
            UNSPEC_CHERI_FLAGS_SET))
     ]
  "TARGET_MORELLO"
  "scflgs\\t%0, %1, %2"
)

(define_insn "aarch64_cap_flags_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_FLAGS_GET))
  ]
  "TARGET_MORELLO"
  "gcflgs\\t%0, %1"
)

(define_insn "aarch64_cap_perms_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_PERMS_GET))
  ]
  "TARGET_MORELLO"
  "gcperm\\t%0, %1"
)

(define_insn "aarch64_cap_pc_get"
  [(set (match_operand:CADI 0 "register_operand" "=r")
        (unspec_volatile:CADI [(const_int 0)]
            UNSPECV_CHERI_PC_GET))]
  "TARGET_MORELLO"
  "adr\\t%0, #0"
)

(define_insn "aarch64_cap_seal_entry"
  [(set (match_operand:CADI 0 "register_operand" "=r")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "r")]
            UNSPEC_CHERI_SEAL_ENTRY))
  ]
  "TARGET_MORELLO"
  "seal\\t%0, %1, rb"
)

(define_insn "aarch64_cap_sealed_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_SEALED_GET))
  ]
  "TARGET_MORELLO"
  "gcseal\\t%0, %1"
)

(define_insn "aarch64_cap_subset_of"
  [(set (reg:CC_N CC_REGNUM)
        (unspec:CC_N [(match_operand:CADI 0 "register_operand" "rk")
                    (match_operand:CADI 1 "register_operand" "rk")]
          UNSPEC_CHERI_SUBSET_TEST)
        )]
  "TARGET_MORELLO"
  "chkss\\t%0, %1"
)

(define_expand "aarch64_cap_subset_test"
  [(match_operand:SI 0 "register_operand")
   (match_operand:CADI 1 "register_operand")
   (match_operand:CADI 2 "register_operand")]
  "TARGET_MORELLO"
  {
    rtx chkss = gen_aarch64_cap_subset_of (operands[1], operands[2]);
    rtx cc = SET_DEST (chkss);
    emit_insn (chkss);
    rtx compare = gen_rtx_LT (GET_MODE (operands[0]), cc, const0_rtx);
    emit_insn (gen_rtx_SET (operands[0], compare));
    DONE;
  }
)

(define_insn "aarch64_cap_type_get"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_TYPE_GET))
  ]
  "TARGET_MORELLO"
  "gctype\\t%0, %1"
)

(define_insn "aarch64_cap_unseal"
  [(set (match_operand:CADI 0 "register_operand" "=r")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "r")
          (match_operand:CADI 2 "register_operand" "r")]
            UNSPEC_CHERI_UNSEAL))
     ]
  "TARGET_MORELLO"
  "unseal\\t%0, %1, %2"
)

(define_insn "aarch64_cap_copy_to_high"
  [(set (match_operand:CADI 0 "register_operand" "=rk")
        (unspec:CADI [(match_operand:CADI 1 "register_operand" "r")
          (match_operand:DI 2 "register_operand" "r")]
            UNSPEC_CHERI_COPY_TO_HIGH))
  ]
  "TARGET_MORELLO"
  "cthi\\t%0, %1, %2"
)

(define_insn "aarch64_cap_copy_from_high"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:CADI 1 "register_operand" "rk")]
            UNSPEC_CHERI_COPY_TO_HIGH))
  ]
  "TARGET_MORELLO"
  "cfhi\\t%0, %1"
)
