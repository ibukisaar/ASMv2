#pragma once

#include "asm_build.h"

#define def_binary_operator(name, al_i8, eax_i32, sub_op, rm_r8, rm_r32, r_rm8, r_rm32)\
	using name##_al_i8 = make_asm<al_i8, arg::byte>;\
	using name##_ax_i16 = make_asm<arg::data16, eax_i32, arg::word>;\
	using name##_eax_i32 = make_asm<eax_i32, arg::dword>;\
	using name##_rax_i32 = make_asm<arg::rex_w, eax_i32, arg::dword>;\
	using name##_r8_i8 = make_asm<0x80, arg::reg | sub_op, arg::byte>;\
	using name##_r16_i16 = make_asm<arg::data16, 0x81, arg::reg | sub_op, arg::word>;\
	using name##_r32_i32 = make_asm<0x81, arg::reg | sub_op, arg::dword>;\
	using name##_r64_i32 = make_asm<arg::rex_w, 0x81, arg::reg | sub_op, arg::dword>;\
	using name##_r16_i8 = make_asm<arg::data16, 0x83, arg::reg | sub_op, arg::byte>;\
	using name##_r32_i8 = make_asm<0x83, arg::reg | sub_op, arg::byte>;\
	using name##_m8_i8 = make_asm<0x80, arg::mem | sub_op, arg::byte>;\
	using name##_m16_i16 = make_asm<arg::data16, 0x81, arg::mem | sub_op, arg::word>;\
	using name##_m32_i32 = make_asm<0x81, arg::mem | sub_op, arg::dword>;\
	using name##_m64_i32 = make_asm<arg::rex_w, 0x81, arg::mem | sub_op, arg::dword>;\
	using name##_m16_i8 = make_asm<arg::data16, 0x83, arg::mem | sub_op, arg::byte>;\
	using name##_m32_i8 = make_asm<0x83, arg::mem | sub_op, arg::byte>;\
	using name##_r8_r8 = make_asm<rm_r8, arg::reg2mreg>;\
	using name##_r16_r16 = make_asm<arg::data16, rm_r32, arg::reg2mreg>;\
	using name##_r32_r32 = make_asm<rm_r32, arg::reg2mreg>;\
	using name##_r64_r64 = make_asm<arg::rex_w, rm_r32, arg::reg2mreg>;\
	using name##_m8_r8 = make_asm<rm_r8, arg::reg2mem>;\
	using name##_m16_r16 = make_asm<arg::data16, rm_r32, arg::reg2mem>;\
	using name##_m32_r32 = make_asm<rm_r32, arg::reg2mem>;\
	using name##_m64_r64 = make_asm<arg::rex_w, rm_r32, arg::reg2mem>;\
	using name##_r8_m8 = make_asm<r_rm8, arg::mem2reg>;\
	using name##_r16_m16 = make_asm<arg::data16, r_rm32, arg::mem2reg>;\
	using name##_r32_m32 = make_asm<r_rm32, arg::mem2reg>;\
	using name##_r64_m64 = make_asm<arg::rex_w, r_rm32, arg::mem2reg>

#define def_unary_operator(name, sub_op)\
	using name##_r8 = make_asm<0xFE, arg::reg | sub_op>;\
	using name##_r16 = make_asm<arg::data16, 0xFF, arg::reg | sub_op>;\
	using name##_r32 = make_asm<0xFF, arg::reg | sub_op>;\
	using name##_r64 = make_asm<arg::rex_w, 0xFF, arg::reg | sub_op>;\
	using name##_m8 = make_asm<0xFE, arg::mem | sub_op>;\
	using name##_m16 = make_asm<arg::data16, 0xFF, arg::mem | sub_op>;\
	using name##_m32 = make_asm<0xFF, arg::mem | sub_op>;\
	using name##_m64 = make_asm<arg::rex_w, 0xFF, arg::mem | sub_op>

#define def_al_ax_eax_operator(name, sub_op)\
	using name##_r8 = make_asm<0xF6, arg::reg | sub_op>;\
	using name##_r16 = make_asm<arg::data16, 0xF7, arg::reg | sub_op>;\
	using name##_r32 = make_asm<0xF7, arg::reg | sub_op>;\
	using name##_r64 = make_asm<arg::rex_w, 0xF7, arg::reg | sub_op>;\
	using name##_m8 = make_asm<0xF6, arg::mem | sub_op>;\
	using name##_m16 = make_asm<arg::data16, 0xF7, arg::mem | sub_op>;\
	using name##_m32 = make_asm<0xF7, arg::mem | sub_op>;\
	using name##_m64 = make_asm<arg::rex_w, 0xF7, arg::mem | sub_op>

#define def_not_neg(name, sub_op)\
	using name##_r8 = make_asm<0xF6, arg::reg | sub_op>;\
	using name##_r16 = make_asm<arg::data16, 0xF7, arg::reg | sub_op>;\
	using name##_r32 = make_asm<0xF7, arg::reg | sub_op>;\
	using name##_r64 = make_asm<arg::rex_w, 0xF7, arg::reg | sub_op>;\
	using name##_m8 = make_asm<0xF6, arg::mem | sub_op>;\
	using name##_m16 = make_asm<arg::data16, 0xF7, arg::mem | sub_op>;\
	using name##_m32 = make_asm<0xF7, arg::mem | sub_op>;\
	using name##_m64 = make_asm<arg::rex_w, 0xF7, arg::mem | sub_op>

#define def_bit_test(name, m2r, sub_op)\
	using name##_r16_r16 = make_asm<arg::data16, 0x0F, m2r, arg::reg2mreg>;\
	using name##_m16_r16 = make_asm<arg::data16, 0x0F, m2r, arg::reg2mem>;\
	using name##_r32_r32 = make_asm<0x0F, m2r, arg::reg2mreg>;\
	using name##_m32_r32 = make_asm<0x0F, m2r, arg::reg2mem>;\
	using name##_r64_r64 = make_asm<arg::rex_w, 0x0F, m2r, arg::reg2mreg>;\
	using name##_m64_r64 = make_asm<arg::rex_w, 0x0F, m2r, arg::reg2mem>;\
	using name##_r16_i8 = make_asm<arg::data16, 0x0F, 0xBA, arg::reg | sub_op, arg::byte>;\
	using name##_m16_i8 = make_asm<arg::data16, 0x0F, 0xBA, arg::mem | sub_op, arg::byte>;\
	using name##_r32_i8 = make_asm<0x0F, 0xBA, arg::reg | sub_op, arg::byte>;\
	using name##_m32_i8 = make_asm<0x0F, 0xBA, arg::mem | sub_op, arg::byte>;\
	using name##_r64_i8 = make_asm<arg::rex_w, 0x0F, 0xBA, arg::reg | sub_op, arg::byte>;\
	using name##_m64_i8 = make_asm<arg::rex_w, 0x0F, 0xBA, arg::mem | sub_op, arg::byte>

#define def_jmp(name, jmp_i8, jmp_i32)\
	using name##_i8 = make_asm<jmp_i8, arg::byte>;\
	using name##_i32 = make_asm<0x0F, jmp_i32, arg::dword>

#define def_shift(name, sub_op, rm8_1, rm8_cl, rm8_i, rm32_1, rm32_cl, rm32_i)\
	using name##_r8_1 = make_asm<rm8_1, arg::reg | sub_op>;\
	using name##_r8_cl = make_asm<rm8_cl, arg::reg | sub_op>;\
	using name##_r8_i8 = make_asm<rm8_i, arg::reg | sub_op, arg::byte>;\
	using name##_r16_1 = make_asm<arg::data16, rm32_1, arg::reg | sub_op>;\
	using name##_r16_cl = make_asm<arg::data16, rm32_cl, arg::reg | sub_op>;\
	using name##_r16_i8 = make_asm<arg::data16, rm32_i, arg::reg | sub_op, arg::byte>;\
	using name##_r32_1 = make_asm<rm32_1, arg::reg | sub_op>;\
	using name##_r32_cl = make_asm<rm32_cl, arg::reg | sub_op>;\
	using name##_r32_i8 = make_asm<rm32_i, arg::reg | sub_op, arg::byte>;\
	using name##_r64_1 = make_asm<arg::rex_w, rm32_1, arg::reg | sub_op>;\
	using name##_r64_cl = make_asm<arg::rex_w, rm32_cl, arg::reg | sub_op>;\
	using name##_r64_i8 = make_asm<arg::rex_w, rm32_i, arg::reg | sub_op, arg::byte>;\
	using name##_m8_1 = make_asm<rm8_1, arg::mem | sub_op>;\
	using name##_m8_cl = make_asm<rm8_cl, arg::mem | sub_op>;\
	using name##_m8_i8 = make_asm<rm8_i, arg::mem | sub_op, arg::byte>;\
	using name##_m16_1 = make_asm<arg::data16, rm32_1, arg::mem | sub_op>;\
	using name##_m16_cl = make_asm<arg::data16, rm32_cl, arg::mem | sub_op>;\
	using name##_m16_i8 = make_asm<arg::data16, rm32_i, arg::mem | sub_op, arg::byte>;\
	using name##_m32_1 = make_asm<rm32_1, arg::mem | sub_op>;\
	using name##_m32_cl = make_asm<rm32_cl, arg::mem | sub_op>;\
	using name##_m32_i8 = make_asm<rm32_i, arg::mem | sub_op, arg::byte>;\
	using name##_m64_1 = make_asm<arg::rex_w, rm32_1, arg::mem | sub_op>;\
	using name##_m64_cl = make_asm<arg::rex_w, rm32_cl, arg::mem | sub_op>;\
	using name##_m64_i8 = make_asm<arg::rex_w, rm32_i, arg::mem | sub_op, arg::byte>

#define def_double_shift(name, i8, cl)\
	using name##_r16_r16_i8 = make_asm<arg::data16, 0x0F, i8, arg::reg2mreg, arg::byte>;\
	using name##_r32_r32_i8 = make_asm<0x0F, i8, arg::reg2mreg, arg::byte>;\
	using name##_r64_r64_i8 = make_asm<arg::rex_w, 0x0F, i8, arg::reg2mreg, arg::byte>;\
	using name##_r16_r16_cl = make_asm<arg::data16, 0x0F, cl, arg::reg2mreg>;\
	using name##_r32_r32_cl = make_asm<0x0F, cl, arg::reg2mreg>;\
	using name##_r64_r64_cl = make_asm<arg::rex_w, 0x0F, cl, arg::reg2mreg>;\
	using name##_m16_r16_i8 = make_asm<arg::data16, 0x0F, i8, arg::reg2mem, arg::byte>;\
	using name##_m32_r32_i8 = make_asm<0x0F, i8, arg::reg2mem, arg::byte>;\
	using name##_m64_r64_i8 = make_asm<arg::rex_w, 0x0F, i8, arg::reg2mem, arg::byte>;\
	using name##_m16_r16_cl = make_asm<arg::data16, 0x0F, cl, arg::reg2mem>;\
	using name##_m32_r32_cl = make_asm<0x0F, cl, arg::reg2mem>;\
	using name##_m64_r64_cl = make_asm<arg::rex_w, 0x0F, cl, arg::reg2mem, arg::byte>

#define def_set(name, op)\
	using name##_r8 = make_asm<0x0F, op, arg::reg | 0>;\
	using name##_m8 = make_asm<0x0F, op, arg::mem | 0>

#define def_cmov(name, op)\
	using name##_r16_r16 = make_asm<arg::data16, 0x0F, op, arg::mreg2reg>;\
	using name##_r32_r32 = make_asm<0x0F, op, arg::mreg2reg>;\
	using name##_r64_r64 = make_asm<arg::rex_w, 0x0F, op, arg::mreg2reg>;\
	using name##_r16_m16 = make_asm<arg::data16, 0x0F, op, arg::mem2reg>;\
	using name##_r32_m32 = make_asm<0x0F, op, arg::mem2reg>;\
	using name##_r64_m64 = make_asm<arg::rex_w, 0x0F, op, arg::mem2reg>

#define def_float_binary_operator(name, op2, sub_op)\
	using f##name##_m32 = make_asm<0xD8, arg::mem | sub_op>;\
	using f##name##_m64 = make_asm<0xDC, arg::mem | sub_op>;\
	using f##name##_st0_st = make_asm<0xD8, op2 | arg::op_reg>;\
	using f##name##_st_st0 = make_asm<0xDC, op2 | arg::op_reg>;\
	using f##name##p_st_st0 = make_asm<0xDE, op2 | arg::op_reg>;\
	using fi##name##_m32 = make_asm<0xDA, arg::mem | sub_op>;\
	using fi##name##_m16 = make_asm<0xDE, arg::mem | sub_op>

#define def_mem_reg_binary_operator(name, op, op_w)\
	using name##_r8_r8 = make_asm<0x0F, op, arg::reg2mreg>;\
	using name##_r16_r16 = make_asm<arg::data16, 0x0F, op_w, arg::reg2mreg>;\
	using name##_r32_r32 = make_asm<0x0F, op_w, arg::reg2mreg>;\
	using name##_r64_r64 = make_asm<arg::rex_w, 0x0F, op_w, arg::reg2mreg>;\
	using name##_m8_r8 = make_asm<0x0F, op, arg::reg2mem>;\
	using name##_m16_r16 = make_asm<arg::data16, 0x0F, op_w, arg::reg2mem>;\
	using name##_m32_r32 = make_asm<0x0F, op_w, arg::reg2mem>;\
	using name##_m64_r64 = make_asm<arg::rex_w, 0x0F, op_w, arg::reg2mem>

namespace saar {
	namespace asm64 {
		using saar::asm64::build::arg;
		using saar::asm64::build::make_asm;

		namespace instruction {
			using aaa = make_asm<0x37>;
			using aad = make_asm<0xD5, 0x0A>;
			using aam = make_asm<0xD4, 0x0A>;
			using aas = make_asm<0x3F>;

			def_binary_operator(adc, 0x14, 0x15, 2, 0x10, 0x11, 0x12, 0x13);
			def_binary_operator(add, 0x04, 0x05, 0, 0x00, 0x01, 0x02, 0x03);
			def_binary_operator(and, 0x24, 0x25, 4, 0x20, 0x21, 0x22, 0x23);

			using arpl_r16_r16 = make_asm<0x63, arg::reg2mreg>;
			using arpl_m16_r16 = make_asm<0x63, arg::reg2mem>;

			using bound_r16_r16 = make_asm<arg::data16, 0x62, arg::mreg2reg>;
			using bound_r16_m16 = make_asm<arg::data16, 0x62, arg::mem2reg>;
			using bound_r16_r32 = make_asm<0x62, arg::mreg2reg>;
			using bound_r16_m32 = make_asm<0x62, arg::mem2reg>;

			using bsf_r16_r16 = make_asm<arg::data16, 0xF0, 0xBC, arg::mreg2reg>;
			using bsf_r16_m16 = make_asm<arg::data16, 0xF0, 0xBC, arg::mem2reg>;
			using bsf_r32_r32 = make_asm<0xF0, 0xBC, arg::mreg2reg>;
			using bsf_r32_m32 = make_asm<0xF0, 0xBC, arg::mem2reg>;
			using bsf_r64_r64 = make_asm<arg::rex_w, 0xF0, 0xBC, arg::mreg2reg>;
			using bsf_r64_m64 = make_asm<arg::rex_w, 0xF0, 0xBC, arg::mem2reg>;

			using bsr_r16_r16 = make_asm<arg::data16, 0x0F, 0xBD, arg::mreg2reg>;
			using bsr_r16_m16 = make_asm<arg::data16, 0x0F, 0xBD, arg::mem2reg>;
			using bsr_r32_r32 = make_asm<0x0F, 0xBD, arg::mreg2reg>;
			using bsr_r32_m32 = make_asm<0x0F, 0xBD, arg::mem2reg>;
			using bsr_r64_r64 = make_asm<arg::rex_w, 0x0F, 0xBD, arg::mreg2reg>;
			using bsr_r64_m64 = make_asm<arg::rex_w, 0x0F, 0xBD, arg::mem2reg>;

			using bswap_r32 = make_asm<0x0F, 0xC8 | arg::op_reg>;
			using bswap_r64 = make_asm<arg::rex_w, 0x0F, 0xC8 | arg::op_reg>;

			def_bit_test(bt, 0xA3, 4);
			def_bit_test(btc, 0xBB, 7);
			def_bit_test(btr, 0xB3, 6);
			def_bit_test(bts, 0xAB, 5);

			using call_offs32 = make_asm<0xE8, arg::dword>;
			using call_r64 = make_asm<arg::rex_w, 0xFF, arg::reg | 2>;
			using call_m64 = make_asm<arg::rex_w, 0xFF, arg::mem | 2>;
			using call_m16_64 = make_asm<arg::rex_w, 0xFF, arg::mem | 3>;

			using cbw = make_asm<arg::data16, 0x98>;
			using cwde = make_asm<0x98>;
			using cdqe = make_asm<arg::rex_w, 0x98>;

			using clc = make_asm<0xF8>;
			using cld = make_asm<0xFC>;
			using cli = make_asm<0xFA>;
			using clts = make_asm<0x0F, 0x06>;
			using cmc = make_asm<0xF5>;

			def_cmov(cmova, 0x47);
			def_cmov(cmovae, 0x43);
			def_cmov(cmovb, 0x42);
			def_cmov(cmovbe, 0x46);
			def_cmov(cmovc, 0x42);
			def_cmov(cmove, 0x44);
			def_cmov(cmovg, 0x4F);
			def_cmov(cmovge, 0x4D);
			def_cmov(cmovl, 0x4C);
			def_cmov(cmovle, 0x4E);
			def_cmov(cmovna, 0x46);
			def_cmov(cmovnae, 0x42);
			def_cmov(cmovnb, 0x43);
			def_cmov(cmovnbe, 0x47);
			def_cmov(cmovnc, 0x43);
			def_cmov(cmovne, 0x45);
			def_cmov(cmovng, 0x4E);
			def_cmov(cmovnge, 0x4C);
			def_cmov(cmovnl, 0x4D);
			def_cmov(cmovnle, 0x4F);
			def_cmov(cmovno, 0x41);
			def_cmov(cmovnp, 0x4B);
			def_cmov(cmovns, 0x49);
			def_cmov(cmovnz, 0x45);
			def_cmov(cmovo, 0x40);
			def_cmov(cmovp, 0x4A);
			def_cmov(cmovpe, 0x4A);
			def_cmov(cmovpo, 0x4B);
			def_cmov(cmovs, 0x48);
			def_cmov(cmovz, 0x44);

			def_binary_operator(cmp, 0x3C, 0x3D, 7, 0x38, 0x39, 0x3A, 0x3B);

			using cmpsb = make_asm<0xA6>;
			using cmpsw = make_asm<arg::data16, 0xA7>;
			using cmpsd = make_asm<0xA7>;
			using cmpsq = make_asm<arg::rex_w, 0xA7>;

			def_mem_reg_binary_operator(cmpxchg, 0xB0, 0xB1);

			using cmpxchg8b_m64 = make_asm<0x0F, 0xC7, arg::mem | 1>;
			using cmpxchg16b_m128 = make_asm<arg::rex_w, 0x0F, 0xC7, arg::mem | 1>;

			using cpuid = make_asm<0x0F, 0xA2>;

			using crc32_r32_r8 = make_asm<arg::lock_repeat | 0xF2, 0x0F, 0x38, 0xF0, arg::mreg2reg>;
			using crc32_r32_r16 = make_asm<arg::lock_repeat | 0xF2, arg::data16, 0x0F, 0x38, 0xF1, arg::mreg2reg>;
			using crc32_r32_r32 = make_asm<arg::lock_repeat | 0xF2, 0x0F, 0x38, 0xF1, arg::mreg2reg>;
			using crc32_r64_r8 = make_asm<arg::lock_repeat | 0xF2, arg::rex_w, 0x0F, 0x38, 0xF0, arg::mreg2reg>;
			using crc32_r64_r64 = make_asm<arg::lock_repeat | 0xF2, arg::rex_w, 0x0F, 0x38, 0xF1, arg::mreg2reg>;
			using crc32_r32_m8 = make_asm<arg::lock_repeat | 0xF2, 0x0F, 0x38, 0xF0, arg::mem2reg>;
			using crc32_r32_m16 = make_asm<arg::lock_repeat | 0xF2, arg::data16, 0x0F, 0x38, 0xF1, arg::mem2reg>;
			using crc32_r32_m32 = make_asm<arg::lock_repeat | 0xF2, 0x0F, 0x38, 0xF1, arg::mem2reg>;
			using crc32_r64_m8 = make_asm<arg::lock_repeat | 0xF2, arg::rex_w, 0x0F, 0x38, 0xF0, arg::mem2reg>;
			using crc32_r64_m64 = make_asm<arg::lock_repeat | 0xF2, arg::rex_w, 0x0F, 0x38, 0xF1, arg::mem2reg>;

			using cwd = make_asm<arg::data16, 0x99>;
			using cdq = make_asm<0x99>;
			using cqo = make_asm<arg::rex_w, 0x99>;

			using daa = make_asm<0x27>;
			using das = make_asm<0x2F>;

			def_unary_operator(dec, 1);

			def_al_ax_eax_operator(div, 6);

			using enter = make_asm<0xC8, arg::word, arg::byte>;

			using f2xm1 = make_asm<0xD9, 0xF0>; // ST0 = pow(2, ST0) - 1
			using fabs = make_asm<0xD9, 0xE1>; // ST0 = abs(ST0)
			def_float_binary_operator(add, 0xC0, 0);
			using fbstp_m80 = make_asm<0xDF, arg::mem | 6>;
			using fchs = make_asm<0xD9, 0xE0>;
			using fclex = make_asm<0x9B, 0xDB, 0xE2>;
			using fnclex = make_asm<0xDB, 0xE2>;
			using fcmovb = make_asm<0xDA, 0xC0 | arg::op_reg>;
			using fcmove = make_asm<0xDA, 0xC8 | arg::op_reg>;
			using fcmovbe = make_asm<0xDA, 0xD0 | arg::op_reg>;
			using fcmovu = make_asm<0xDA, 0xD8 | arg::op_reg>;
			using fcmovnb = make_asm<0xDB, 0xC0 | arg::op_reg>;
			using fcmovne = make_asm<0xDB, 0xC8 | arg::op_reg>;
			using fcmovnbe = make_asm<0xDB, 0xD0 | arg::op_reg>;
			using fcmovnu = make_asm<0xDB, 0xD8 | arg::op_reg>;
			using fcom_m32 = make_asm<0xD8, arg::mem | 2>;
			using fcom_m64 = make_asm<0xDC, arg::mem | 2>;
			using fcom_st = make_asm<0xD8, 0xD0 | arg::op_reg>;
			using fcomp_m32 = make_asm<0xD8, arg::mem | 3>;
			using fcomp_m64 = make_asm<0xDC, arg::mem | 3>;
			using fcomp_st = make_asm<0xD8, 0xD8 | arg::op_reg>;
			using fcompp = make_asm<0xDE, 0xD9>;
			using fcomi_st = make_asm<0xDB, 0xF0 | arg::op_reg>;
			using fcomip_st = make_asm<0xDF, 0xF0 | arg::op_reg>;
			using fucomi_st = make_asm<0xDB, 0xE8 | arg::op_reg>;
			using fucomip_st = make_asm<0xDF, 0xE8 | arg::op_reg>;
			using fcos = make_asm<0xD9, 0xFF>;
			using fdecstp = make_asm<0xD9, 0xF6>;
			def_float_binary_operator(div, 0xF0, 6);
			def_float_binary_operator(divr, 0xF8, 7);
			using ffree_st = make_asm<0xDD, 0xC0 | arg::op_reg>;
			using ficom_m16 = make_asm<0xDE, arg::mem | 2>;
			using ficom_m32 = make_asm<0xDA, arg::mem | 2>;
			using ficomp_m16 = make_asm<0xDE, arg::mem | 3>;
			using ficomp_m32 = make_asm<0xDA, arg::mem | 3>;
			using fild_m16 = make_asm<0xDF, arg::mem | 0>;
			using fild_m32 = make_asm<0xDB, arg::mem | 0>;
			using fild_m64 = make_asm<0xDF, arg::mem | 5>;
			using fincstp = make_asm<0xD9, 0xF7>;
			using finit = make_asm<0x9B, 0xDB, 0xE3>;
			using fninit = make_asm<0xDB, 0xE3>;
			using fist_m16 = make_asm<0xDF, arg::mem | 2>;
			using fist_m32 = make_asm<0xDB, arg::mem | 2>;
			using fistp_m16 = make_asm<0xDF, arg::mem | 3>;
			using fistp_m32 = make_asm<0xDB, arg::mem | 3>;
			using fistp_m64 = make_asm<0xDF, arg::mem | 7>;
			using fisttp_m16 = make_asm<0xDF, arg::mem | 1>;
			using fisttp_m32 = make_asm<0xDB, arg::mem | 1>;
			using fisttp_m64 = make_asm<0xDD, arg::mem | 1>;
			using fld_m32 = make_asm<0xD9, arg::mem | 0>;
			using fld_m64 = make_asm<0xDD, arg::mem | 0>;
			using fld_m80 = make_asm<0xDB, arg::mem | 5>;
			using fld_st = make_asm<0xD9, 0xC0 | arg::op_reg>;
			using fld1 = make_asm<0xD9, 0xE8>;
			using fldl2t = make_asm<0xD9, 0xE9>;
			using fldl2e = make_asm<0xD9, 0xEA>;
			using fldpi = make_asm<0xD9, 0xEB>;
			using fldlg2 = make_asm<0xD9, 0xEC>;
			using fldln2 = make_asm<0xD9, 0xED>;
			using fldz = make_asm<0xD9, 0xEE>;
			using fldcw_m2byte = make_asm<0xD9, arg::mem | 5>;
			using fldenv_m14byte = make_asm<arg::data16, 0xD9, arg::mem | 4>;
			using fldenv_m28byte = make_asm<0xD9, arg::mem | 4>;
			def_float_binary_operator(mul, 0xC8, 1);
			using fnop = make_asm<0xD9, 0xD0>;
			using fpatan = make_asm<0xD9, 0xF3>;
			using fprem = make_asm<0xD9, 0xF8>;
			using fprem1 = make_asm<0xD9, 0xF5>;
			using fptan = make_asm<0xD9, 0xF2>;
			using frndint = make_asm<0xD9, 0xFC>;
			using frstor_m94byte = make_asm<arg::data16, 0xDD, arg::mem | 4>;
			using frstor_m104byte = make_asm<0xDD, arg::mem | 4>;
			using fsave_m94byte = make_asm<arg::data16, 0x9B, 0xDD, arg::mem | 6>;
			using fsave_m104byte = make_asm<0x9B, 0xDD, arg::mem | 6>;
			using fnsave_m94byte = make_asm<arg::data16, 0xDD, arg::mem | 6>;
			using fnsave_m104byte = make_asm<0xDD, arg::mem | 6>;
			using fscale = make_asm<0xD9, 0xFD>;
			using fsin = make_asm<0xD9, 0xFE>;
			using fsincos = make_asm<0xD9, 0xFB>;
			using fsqrt = make_asm<0xD9, 0xFA>;
			using fst_m32 = make_asm<0xD9, arg::mem | 2>;
			using fst_m64 = make_asm<0xDD, arg::mem | 2>;
			using fst_st = make_asm<0xDD, 0xD0 | arg::op_reg>;
			using fstp_m32 = make_asm<0xD9, arg::mem | 3>;
			using fstp_m64 = make_asm<0xDD, arg::mem | 3>;
			using fstp_m80 = make_asm<0xDB, arg::mem | 7>;
			using fstp_st = make_asm<0xDD, 0xD8 | arg::op_reg>;
			using fstcw_m2byte = make_asm<0x9B, 0xD9, arg::mem | 7>;
			using fnstcw_m2byte = make_asm<0xD9, arg::mem | 7>;
			using fstenv_m14byte = make_asm<arg::data16, 0x9B, 0xD9, arg::mem | 6>;
			using fstenv_m28byte = make_asm<0x9B, 0xD9, arg::mem | 6>;
			using fnstenv_m14byte = make_asm<arg::data16, 0xD9, arg::mem | 6>;
			using fnstenv_m28byte = make_asm<0xD9, arg::mem | 6>;
			using fstsw_m2byte = make_asm<0x9B, 0xDD, arg::mem | 2>;
			using fstsw_ax = make_asm<0x9B, 0xDF, 0xE0>;
			using fnstsw_m2byte = make_asm<0xDD, arg::mem | 7>;
			using fnstsw_ax = make_asm<0xDF, 0xE0>;
			def_float_binary_operator(sub, 0xE0, 4);
			def_float_binary_operator(sur, 0xE8, 5);
			using ftst = make_asm<0xD9, 0xE4>;
			using fucom_st = make_asm<0xDD, 0xE0 | arg::op_reg>;
			using fucomp_st = make_asm<0xDD, 0xE8 | arg::op_reg>;
			using fucompp = make_asm<0xDA, 0xE9>;
			using fxam = make_asm<0xD9, 0xE5>;
			using fxch_st = make_asm<0xD9, 0xC8 | arg::op_reg>;
			using fxrstor_m512byte = make_asm<0x0F, 0xAE, arg::mem | 1>;
			using fxrstor64_m512byte = make_asm<arg::rex_w, 0x0F, 0xAE, arg::mem | 1>;
			using fxsave_m512byte = make_asm<0x0F, 0xAE, arg::mem | 0>;
			using fxsave64_m512byte = make_asm<arg::rex_w, 0x0F, 0xAE, arg::mem | 0>;
			using fxtract = make_asm<0xD9, 0xF4>;
			using fyl2x = make_asm<0xD9, 0xF1>;
			using fyl2xp1 = make_asm<0xD9, 0xF9>;

			using hlt = make_asm<0xF4>;

			def_al_ax_eax_operator(idiv, 7);

			def_al_ax_eax_operator(imul, 5);
			using imul_r16_r16 = make_asm<arg::data16, 0x0F, 0xAF, arg::mreg2reg>;
			using imul_r32_r32 = make_asm<0x0F, 0xAF, arg::mreg2reg>;
			using imul_r64_r64 = make_asm<arg::rex_w, 0x0F, 0xAF, arg::mreg2reg>;
			using imul_r16_m16 = make_asm<arg::data16, 0x0F, 0xAF, arg::mem2reg>;
			using imul_r32_m32 = make_asm<0x0F, 0xAF, arg::mem2reg>;
			using imul_r64_m64 = make_asm<arg::rex_w, 0x0F, 0xAF, arg::mem2reg>;
			using imul_r16_r16_i8 = make_asm<arg::data16, 0x6B, arg::mreg2reg, arg::byte>;
			using imul_r32_r32_i8 = make_asm<0x6B, arg::mreg2reg, arg::byte>;
			using imul_r64_r64_i8 = make_asm<arg::rex_w, 0x6B, arg::mreg2reg, arg::byte>;
			using imul_r16_m16_i8 = make_asm<arg::data16, 0x6B, arg::reg2mem, arg::byte>;
			using imul_r32_m32_i8 = make_asm<0x6B, arg::reg2mem, arg::byte>;
			using imul_r64_m64_i8 = make_asm<arg::rex_w, 0x6B, arg::reg2mem, arg::byte>;
			using imul_r16_r16_i16 = make_asm<arg::data16, 0x69, arg::mreg2reg, arg::word>;
			using imul_r32_r32_i32 = make_asm<0x69, arg::mreg2reg, arg::dword>;
			using imul_r64_r64_i32 = make_asm<arg::rex_w, 0x69, arg::mreg2reg, arg::dword>;
			using imul_r16_m16_i16 = make_asm<arg::data16, 0x69, arg::reg2mem, arg::word>;
			using imul_r32_m32_i32 = make_asm<0x69, arg::reg2mem, arg::dword>;
			using imul_r64_m64_i32 = make_asm<arg::rex_w, 0x69, arg::reg2mem, arg::dword>;

			using in_al = make_asm<0xE4, arg::byte>;
			using in_ax = make_asm<arg::data16, 0xE5, arg::byte>;
			using in_eax = make_asm<0xE5, arg::byte>;
			using in_al_dx = make_asm<0xEC>;
			using in_ax_dx = make_asm<arg::data16, 0xED>;
			using in_eax_dx = make_asm<0xED>;

			def_unary_operator(inc, 0);

			using insb = make_asm<0x6C>;
			using insw = make_asm<arg::data16, 0x6D>;
			using insd = make_asm<0x6D>;

			using int_3 = make_asm<0xCC>;
			using int_i8 = make_asm<0xCD, arg::byte>;
			using into = make_asm<0xCE>;

			using invd = make_asm<0x0F, 0x08>;
			using invlpg = make_asm<0x0F, 0x01, arg::mem | 7>;

			using iret = make_asm<arg::data16, 0xCF>;
			using iretd = make_asm<0xCF>;
			using iretq = make_asm<arg::rex_w, 0xCF>;

			def_jmp(ja, 0x77, 0x87);
			def_jmp(jae, 0x73, 0x83);
			def_jmp(jb, 0x72, 0x82);
			def_jmp(jbe, 0x76, 0x86);
			def_jmp(jc, 0x72, 0x82);
			def_jmp(je, 0x74, 0x84);
			def_jmp(jg, 0x7F, 0x8F);
			def_jmp(jge, 0x7D, 0x8D);
			def_jmp(jl, 0x7C, 0x8C);
			def_jmp(jle, 0x7E, 0x8E);
			def_jmp(jna, 0x76, 0x86);
			def_jmp(jnae, 0x72, 0x82);
			def_jmp(jnb, 0x73, 0x83);
			def_jmp(jnbe, 0x77, 0x87);
			def_jmp(jnc, 0x73, 0x83);
			def_jmp(jne, 0x75, 0x85);
			def_jmp(jng, 0x7E, 0x8E);
			def_jmp(jnge, 0x7C, 0x8C);
			def_jmp(jnl, 0x7D, 0x8D);
			def_jmp(jnle, 0x7F, 0x8F);
			def_jmp(jno, 0x71, 0x81);
			def_jmp(jnp, 0x7B, 0x8B);
			def_jmp(jns, 0x79, 0x89);
			def_jmp(jnz, 0x75, 0x85);
			def_jmp(jo, 0x70, 0x80);
			def_jmp(jp, 0x7A, 0x8A);
			def_jmp(jpe, 0x7A, 0x8A);
			def_jmp(jpo, 0x7B, 0x8B);
			def_jmp(js, 0x78, 0x88);
			def_jmp(jz, 0x74, 0x84);
			using jcxz = make_asm<0xE3, arg::byte>;
			using jeczx = make_asm<0xE3, arg::byte>;

			using jmp_i8 = make_asm<0xEB, arg::byte>;
			using jmp_i16 = make_asm<arg::data16, 0xE9, arg::word>;
			using jmp_i32 = make_asm<0xE9, arg::dword>;
			using jmp_i32_i16 = make_asm<0xEA, arg::dword, arg::word>;
			using jmp_r64 = make_asm<0xFF, arg::reg | 4>;
			using jmp_m64 = make_asm<0xFF, arg::mem | 4>;
			using jmp_far_m16_m64 = make_asm<arg::rex_w, 0xFF, arg::mem | 5>;

			using lahf = make_asm<0x9F>;

			using lar_r16_r16 = make_asm<arg::data16, 0x0F, 0x02, arg::mreg2reg>;
			using lar_r16_m16 = make_asm<arg::data16, 0x0F, 0x02, arg::mem2reg>;
			using lar_r32_r32 = make_asm<0x0F, 0x02, arg::mreg2reg>;
			using lar_r32_m16 = make_asm<0x0F, 0x02, arg::mem2reg>;
			using lar_r64_r32 = make_asm<arg::rex_w, 0x0F, 0x02, arg::mreg2reg>;
			using lar_r64_m16 = make_asm<arg::rex_w, 0x0F, 0x02, arg::mem2reg>;

			using lea_r16_m = make_asm<arg::data16, 0x8D, arg::mem2reg>;
			using lea_r32_m = make_asm<0x8D, arg::mem2reg>;
			using lea_r64_m = make_asm<arg::rex_w, 0x8D, arg::mem2reg>;

			using leavew = make_asm<arg::data16, 0xC9>;
			using leaveq = make_asm<0xC9>;

			using lgdt = make_asm<0x0F, 0x01, arg::mem | 2>;
			using lidt = make_asm<0x0F, 0x01, arg::mem | 3>;

			using lds_r_m16 = make_asm<arg::data16, 0xC5, arg::mem2reg>;
			using lds_r_m32 = make_asm<0xC5, arg::mem2reg>;
			using lss_r_m16 = make_asm<arg::data16, 0x0F, 0xB2, arg::mem2reg>;
			using lss_r_m32 = make_asm<0x0F, 0xB2, arg::mem2reg>;
			using les_r_m16 = make_asm<arg::data16, 0xC4, arg::mem2reg>;
			using les_r_m32 = make_asm<0xC4, arg::mem2reg>;
			using lfs_r_m16 = make_asm<arg::data16, 0x0F, 0xB4, arg::mem2reg>;
			using lfs_r_m32 = make_asm<0x0F, 0xB4, arg::mem2reg>;
			using lgs_r_m16 = make_asm<arg::data16, 0x0F, 0xB5, arg::mem2reg>;
			using lgs_r_m32 = make_asm<0x0F, 0xB5, arg::mem2reg>;

			using lldt_r16 = make_asm<0x0F, 0x00, arg::reg | 2>;
			using lldt_m16 = make_asm<0x0F, 0x00, arg::mem | 2>;
			using lmsw_r16 = make_asm<0x0F, 0x01, arg::reg | 6>;
			using lmsw_m16 = make_asm<0x0F, 0x01, arg::mem | 6>;

			using lock = make_asm<0xF0>;

			using lodsb = make_asm<0xAC>;
			using lodsw = make_asm<arg::data16, 0xAD>;
			using lodsd = make_asm<0xAD>;
			using lodsq = make_asm<arg::rex_w, 0xAD>;

			using loop = make_asm<0xE2, arg::byte>;
			using loope = make_asm<0xE1, arg::byte>;
			using loopz = make_asm<0xE1, arg::byte>;
			using loopne = make_asm<0xE0, arg::byte>;
			using loopnz = make_asm<0xE0, arg::byte>;

			using lsl_r16_r16 = make_asm<arg::data16, 0x0F, 0x03, arg::mreg2reg>;
			using lsl_r32_r32 = make_asm<0x0F, 0x03, arg::mreg2reg>;
			using lsl_r64_r64 = make_asm<arg::rex_w, 0x0F, 0x03, arg::mreg2reg>;
			using lsl_r16_m16 = make_asm<arg::data16, 0x0F, 0x03, arg::reg2mem>;
			using lsl_r32_m32 = make_asm<0x0F, 0x03, arg::reg2mem>;
			using lsl_r64_m64 = make_asm<arg::rex_w, 0x0F, 0x03, arg::reg2mem>;

			using ltr_r16 = make_asm<0x0F, 0x00, arg::reg | 3>;
			using ltr_m16 = make_asm<0x0F, 0x00, arg::mem | 3>;

			using monitor = make_asm<0x0F, 0x01, 0xC8>;

			using mov_r8_r8 = make_asm<0x88, arg::reg2mreg>;
			using mov_r16_r16 = make_asm<arg::data16, 0x89, arg::reg2mreg>;
			using mov_r32_r32 = make_asm<0x89, arg::reg2mreg>;
			using mov_r64_r64 = make_asm<arg::rex_w, 0x89, arg::reg2mreg>;
			using mov_m8_r8 = make_asm<0x88, arg::reg2mem>;
			using mov_m16_r16 = make_asm<arg::data16, 0x89, arg::reg2mem>;
			using mov_m32_r32 = make_asm<0x89, arg::reg2mem>;
			using mov_m64_r64 = make_asm<arg::rex_w, 0x89, arg::reg2mem>;
			using mov_r8_m8 = make_asm<0x8A, arg::mem2reg>;
			using mov_r16_m16 = make_asm<arg::data16, 0x8B, arg::mem2reg>;
			using mov_r32_m32 = make_asm<0x8B, arg::mem2reg>;
			using mov_r64_m64 = make_asm<arg::rex_w, 0x8B, arg::mem2reg>;
			using mov_r16_seg = make_asm<0x8C, arg::reg2mreg>;
			using mov_m16_seg = make_asm<0x8C, arg::reg2mem>;
			using mov_r64_seg = make_asm<arg::rex_w, 0x8C, arg::reg2mreg>;
			using mov_m64_seg = make_asm<arg::rex_w, 0x8C, arg::reg2mem>;
			using mov_seg_r16 = make_asm<0x8E, arg::mreg2reg>;
			using mov_seg_m16 = make_asm<0x8E, arg::reg2mem>;
			using mov_seg_r64 = make_asm<arg::rex_w, 0x8E, arg::mreg2reg>;
			using mov_seg_m64 = make_asm<arg::rex_w, 0x8E, arg::reg2mem>;
			using mov_al_moffs8 = make_asm<0xA0, arg::qword>;
			using mov_ax_moffs16 = make_asm<arg::data16, 0xA1, arg::qword>;
			using mov_eax_moffs32 = make_asm<0xA1, arg::qword>;
			using mov_rax_moffs64 = make_asm<arg::rex_w, 0xA1, arg::qword>;
			using mov_moffs8_al = make_asm<0xA2, arg::qword>;
			using mov_moffs16_ax = make_asm<arg::data16, 0xA3, arg::qword>;
			using mov_moffs32_eax = make_asm<0xA3, arg::qword>;
			using mov_moffs64_rax = make_asm<arg::rex_w, 0xA3, arg::qword>;
			using mov_r8_i8 = make_asm<0xB0 | arg::op_reg, arg::byte>;
			using mov_r16_i16 = make_asm<arg::data16, 0xB8 | arg::op_reg, arg::word>;
			using mov_r32_i32 = make_asm<0xB8 | arg::op_reg, arg::dword>;
			using mov_r64_i64 = make_asm<arg::rex_w, 0xB8 | arg::op_reg, arg::qword>;
			using mov_m8_i8 = make_asm<0xC6, arg::mem | 0, arg::byte>;
			using mov_m16_i16 = make_asm<arg::data16, 0xC7, arg::mem | 0, arg::word>;
			using mov_m32_i32 = make_asm<0xC7, arg::mem | 0, arg::dword>;
			using mov_m64_i32 = make_asm<arg::rex_w, 0xC7, arg::mem | 0, arg::dword>;

			using mov_r64_cr = make_asm<0x0F, 0x20, arg::reg2mreg>;
			using mov_r64_cr8 = make_asm<arg::rex_r, 0x0F, 0x20, arg::reg | 0>;
			using mov_cr_r64 = make_asm<0x0F, 0x22, arg::mreg2reg>;
			using mov_cr8_r64 = make_asm<arg::rex_r, 0x0F, 0x22, arg::reg | 0>;

			using mov_r64_dr = make_asm<0x0F, 0x21, arg::reg2mreg>;
			using mov_dr_r64 = make_asm<0x0F, 0x23, arg::mreg2reg>;

			using movbe_r16_m16 = make_asm<arg::data16, 0x0F, 0x38, 0xF0, arg::mem2reg>;
			using movbe_r32_m32 = make_asm<0x0F, 0x38, 0xF0, arg::mem2reg>;
			using movbe_r64_m64 = make_asm<arg::rex_w, 0x0F, 0x38, 0xF0, arg::mem2reg>;
			using movbe_m16_r16 = make_asm<arg::data16, 0x0F, 0x38, 0xF1, arg::reg2mem>;
			using movbe_m32_r32 = make_asm<0x0F, 0x38, 0xF1, arg::reg2mem>;
			using movbe_m64_r64 = make_asm<arg::rex_w, 0x0F, 0x38, 0xF1, arg::reg2mem>;

			using movsb = make_asm<0xA4>;
			using movsw = make_asm<arg::data16, 0xA5>;
			using movsd = make_asm<0xA5>;
			using movsq = make_asm<arg::rex_w, 0xA5>;

			using movsx_r16_r8 = make_asm<arg::data16, 0x0F, 0xBE, arg::mreg2reg>;
			using movsx_r32_r8 = make_asm<0x0F, 0xBE, arg::mreg2reg>;
			using movsx_r64_r8 = make_asm<arg::rex_w, 0x0F, 0xBE, arg::mreg2reg>;
			using movsx_r32_r16 = make_asm<0x0F, 0xBF, arg::mreg2reg>;
			using movsx_r64_r16 = make_asm<arg::rex_w, 0x0F, 0xBF, arg::mreg2reg>;
			using movsx_r64_r32 = make_asm<arg::rex_w, 0x63, arg::mreg2reg>;
			using movsx_r16_m8 = make_asm<arg::data16, 0x0F, 0xBE, arg::mem2reg>;
			using movsx_r32_m8 = make_asm<0x0F, 0xBE, arg::mem2reg>;
			using movsx_r64_m8 = make_asm<arg::rex_w, 0x0F, 0xBE, arg::mem2reg>;
			using movsx_r32_m16 = make_asm<0x0F, 0xBF, arg::mem2reg>;
			using movsx_r64_m16 = make_asm<arg::rex_w, 0x0F, 0xBF, arg::mem2reg>;
			using movsx_r64_m32 = make_asm<arg::rex_w, 0x63, arg::mem2reg>;

			using movzx_r16_r8 = make_asm<arg::data16, 0x0F, 0xB6, arg::mreg2reg>;
			using movzx_r32_r8 = make_asm<0x0F, 0xB6, arg::mreg2reg>;
			using movzx_r64_r8 = make_asm<arg::rex_w, 0x0F, 0xB6, arg::mreg2reg>;
			using movzx_r32_r16 = make_asm<0x0F, 0xB7, arg::mreg2reg>;
			using movzx_r64_r16 = make_asm<arg::rex_w, 0x0F, 0xB7, arg::mreg2reg>;
			using movzx_r16_m8 = make_asm<arg::data16, 0x0F, 0xB6, arg::mem2reg>;
			using movzx_r32_m8 = make_asm<0x0F, 0xB6, arg::mem2reg>;
			using movzx_r64_m8 = make_asm<arg::rex_w, 0x0F, 0xB6, arg::mem2reg>;
			using movzx_r32_m16 = make_asm<0x0F, 0xB7, arg::mem2reg>;
			using movzx_r64_m16 = make_asm<arg::rex_w, 0x0F, 0xB7, arg::mem2reg>;

			def_al_ax_eax_operator(mul, 4);

			using mwait = make_asm<0x0F, 0x01, 0xC9>;

			def_not_neg(neg, 3);

			using nop = make_asm<0x90>;
			using nop_r16 = make_asm<arg::data16, 0x0F, 0x1F, arg::reg | 0>;
			using nop_r32 = make_asm<0x0F, 0x1F, arg::reg | 0>;
			using nop_m16 = make_asm<arg::data16, 0x0F, 0x1F, arg::mem | 0>;
			using nop_m32 = make_asm<0x0F, 0x1F, arg::mem | 0>;

			def_not_neg(not, 2);
			def_binary_operator(or , 0x0C, 0x0D, 1, 0x08, 0x09, 0x0A, 0x0B);

			using out_al = make_asm<0xE6, arg::byte>;
			using out_ax = make_asm<arg::data16, 0x75, arg::byte>;
			using out_eax = make_asm<0xE7, arg::byte>;
			using out_dx_al = make_asm<0xEE>;
			using out_dx_ax = make_asm<arg::data16, 0xEF>;
			using out_dx_eax = make_asm<0xEF>;

			using outsb = make_asm<0x6E>;
			using outsw = make_asm<arg::data16, 0x6F>;
			using outsd = make_asm<0x6F>;

			using pause = make_asm<0xF3, 0x90>;

			using pop_m16 = make_asm<arg::data16, 0x8F, arg::mem | 0>;
			using pop_m64 = make_asm<0x8F, arg::mem | 0>;
			using pop_r16 = make_asm<arg::data16, 0x58 | arg::op_reg>;
			using pop_r64 = make_asm<0x58 | arg::op_reg>;
			using pop_fs = make_asm<0x0F, 0xA1>;
			using pop_gs = make_asm<0x0F, 0xA9>;

			using popcnt_r16_r16 = make_asm<arg::lock_repeat | 0xF3, arg::data16, 0xF3, 0x0F, 0xB8, arg::mreg2reg>;
			using popcnt_r32_r32 = make_asm<arg::lock_repeat | 0xF3, 0xF3, 0x0F, 0xB8, arg::mreg2reg>;
			using popcnt_r64_r64 = make_asm<arg::lock_repeat | 0xF3, arg::rex_w, 0xF3, 0x0F, 0xB8, arg::mreg2reg>;
			using popcnt_r16_m16 = make_asm<arg::lock_repeat | 0xF3, arg::data16, 0xF3, 0x0F, 0xB8, arg::mem2reg>;
			using popcnt_r32_m32 = make_asm<arg::lock_repeat | 0xF3, 0xF3, 0x0F, 0xB8, arg::mem2reg>;
			using popcnt_r64_m64 = make_asm<arg::lock_repeat | 0xF3, arg::rex_w, 0xF3, 0x0F, 0xB8, arg::mem2reg>;

			using popfw = make_asm<arg::data16, 0x9D>;
			using popfq = make_asm<0x9D>;

			using prefetcht0_m8 = make_asm<0x0F, 0x18, arg::mem | 1>;
			using prefetcht1_m8 = make_asm<0x0F, 0x18, arg::mem | 2>;
			using prefetcht2_m8 = make_asm<0x0F, 0x18, arg::mem | 3>;
			using prefetchtnta_m8 = make_asm<0x0F, 0x18, arg::mem | 0>;

			using push_m16 = make_asm<arg::data16, 0xFF, arg::mem | 6>;
			using push_m64 = make_asm<0xFF, arg::mem | 6>;
			using push_r16 = make_asm<arg::data16, 0x50 | arg::op_reg>;
			using push_r64 = make_asm<0x50 | arg::op_reg>;
			using push_i8 = make_asm<0x6A, arg::byte>;
			using push_i16 = make_asm<arg::data16, 0x68, arg::word>;
			using push_i32 = make_asm<0x68, arg::dword>;
			using push_fs = make_asm<0x0F, 0xA0>;
			using push_gs = make_asm<0x0F, 0xA8>;

			using pushfw = make_asm<arg::data16, 0x9C>;
			using pushfq = make_asm<0x9C>;

			def_shift(rcl, 2, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(rcr, 3, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(rol, 0, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(ror, 1, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);

			using rdmsr = make_asm<0x0F, 0x32>;
			using rdpmc = make_asm<0x0F, 0x33>;
			using rdtsc = make_asm<0x0F, 0x31>;
			using rdtscp = make_asm<0x0F, 0x01, 0xF9>;

			using repe = make_asm<0xF3>;
			using repne = make_asm<0xF2>;

			using ret = make_asm<0xC3>;
			using ret_far = make_asm<0xCB>;
			using ret_i16 = make_asm<0xC2, arg::word>;
			using ret_far_i16 = make_asm<0xCA, arg::word>;

			def_shift(sal, 4, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(sar, 7, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(shl, 4, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(shr, 5, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);

			def_binary_operator(sbb, 0x1C, 0x1D, 3, 0x18, 0x19, 0x1A, 0x1B);

			using scasb = make_asm<0xAE>;
			using scasw = make_asm<arg::data16, 0xAF>;
			using scasd = make_asm<0xAF>;
			using scasq = make_asm<arg::rex_w, 0xAF>;

			def_set(seta, 0x97);
			def_set(setae, 0x93);
			def_set(setb, 0x92);
			def_set(setbe, 0x96);
			def_set(setc, 0x92);
			def_set(sete, 0x94);
			def_set(setg, 0x9F);
			def_set(setge, 0x9D);
			def_set(setl, 0x9C);
			def_set(setle, 0x9E);
			def_set(setna, 0x96);
			def_set(setnae, 0x92);
			def_set(setnb, 0x93);
			def_set(setnbe, 0x97);
			def_set(setnc, 0x93);
			def_set(setne, 0x95);
			def_set(setng, 0x9E);
			def_set(setnge, 0x9C);
			def_set(setnl, 0x9D);
			def_set(setnle, 0x9F);
			def_set(setno, 0x91);
			def_set(setnp, 0x9B);
			def_set(setns, 0x99);
			def_set(setnz, 0x95);
			def_set(seto, 0x90);
			def_set(setp, 0x9A);
			def_set(setpe, 0x9A);
			def_set(setpo, 0x9B);
			def_set(sets, 0x98);
			def_set(setz, 0x94);

			using sfence = make_asm<0x0F, 0xAE, 0xF8>;

			using sgdt = make_asm<0x0F, 0x01, arg::mem | 0>;
			using sidt = make_asm<0x0F, 0x01, arg::mem | 1>;

			def_double_shift(shld, 0xA4, 0xA5);
			def_double_shift(shrd, 0xAC, 0xAD);

			using sldt_r16 = make_asm<arg::data16, 0x0F, 0x00, arg::reg | 0>;
			using sldt_r32 = make_asm<0x0F, 0x00, arg::reg | 0>;
			using sldt_r64 = make_asm<arg::rex_w, 0x0F, 0x00, arg::reg | 0>;
			using sldt_m16 = make_asm<0x0F, 0x00, arg::mem | 0>;

			using smsw_r16 = make_asm<arg::data16, 0x0F, 0x01, arg::reg | 4>;
			using smsw_r32 = make_asm<0x0F, 0x01, arg::reg | 4>;
			using smsw_r64 = make_asm<arg::rex_w, 0x0F, 0x01, arg::reg | 4>;
			using smsw_m16 = make_asm<0x0F, 0x01, arg::mem | 4>;

			using stc = make_asm<0xF9>;
			using std = make_asm<0xFD>;
			using sti = make_asm<0xFB>;

			using stosb = make_asm<0xAA>;
			using stosw = make_asm<arg::data16, 0xAB>;
			using stosd = make_asm<0xAB>;
			using stosq = make_asm<arg::rex_w, 0xAB>;

			using str_r16 = make_asm<0x0F, 0x00, arg::reg | 1>;
			using str_m16 = make_asm<0x0F, 0x00, arg::mem | 1>;

			def_binary_operator(sub, 0x2C, 0x2D, 5, 0x28, 0x29, 0x2A, 0x2B);

			using swapgs = make_asm<0x0F, 0x01, 0xF8>;

			using syscall = make_asm<0x0F, 0x05>;
			using sysenter = make_asm<0x0F, 0x34>;
			using sysexit = make_asm<0x0F, 0x35>;
			using sysret = make_asm<0x0F, 0x07>;

			using test_al_i8 = make_asm<0xA8, arg::byte>;
			using test_ax_i16 = make_asm<arg::data16, 0xA9, arg::word>;
			using test_eax_i32 = make_asm<0xA9, arg::dword>;
			using test_rax_i32 = make_asm<arg::rex_w, 0xA9, arg::dword>;
			using test_r8_i8 = make_asm<0xF6, arg::reg | 0, arg::byte>;
			using test_r16_i16 = make_asm<arg::data16, 0xF7, arg::reg | 0, arg::word>;
			using test_r32_i32 = make_asm<0xF7, arg::reg | 0, arg::dword>;
			using test_r64_i32 = make_asm<arg::rex_w, 0xF7, arg::reg | 0, arg::dword>;
			using test_m8_i8 = make_asm<0xF6, arg::mem | 0, arg::byte>;
			using test_m16_i16 = make_asm<arg::data16, 0xF7, arg::mem | 0, arg::word>;
			using test_m32_i32 = make_asm<0xF7, arg::mem | 0, arg::dword>;
			using test_m64_i32 = make_asm<arg::rex_w, 0xF7, arg::mem | 0, arg::dword>;
			using test_r8_r8 = make_asm<0x84, arg::reg2mreg>;
			using test_r16_r16 = make_asm<arg::data16, 0x85, arg::reg2mreg>;
			using test_r32_r32 = make_asm<0x85, arg::reg2mreg>;
			using test_r64_r64 = make_asm<arg::rex_w, 0x85, arg::reg2mreg>;
			using test_m8_r8 = make_asm<0x84, arg::reg2mem>;
			using test_m16_r16 = make_asm<arg::data16, 0x85, arg::reg2mem>;
			using test_m32_r32 = make_asm<0x85, arg::reg2mem>;
			using test_m64_r64 = make_asm<arg::rex_w, 0x85, arg::reg2mem>;

			using ud2 = make_asm<0x0F, 0x0B>;

			using verr_r16 = make_asm<0x0F, 0x00, arg::reg | 4>;
			using verr_m16 = make_asm<0x0F, 0x00, arg::mem | 4>;
			using verw_r16 = make_asm<0x0F, 0x00, arg::reg | 5>;
			using verw_m16 = make_asm<0x0F, 0x00, arg::mem | 5>;

			using wait = make_asm<0x9B>;
			using fwait = make_asm<0x9B>;

			using wbinvd = make_asm<0x0F, 0x09>;
			using wrmsr = make_asm<0x0F, 0x30>;

			def_mem_reg_binary_operator(xadd, 0xC0, 0xC1);

			using xchg_ax_r16 = make_asm<arg::data16, 0x90 | arg::op_reg>;
			using xchg_eax_r32 = make_asm<0x90 | arg::op_reg>;
			using schg_rax_r64 = make_asm<arg::rex_w, 0x90 | arg::op_reg>;
			using xchg_r8_r8 = make_asm<0x86, arg::reg2mreg>;
			using xchg_r16_r16 = make_asm<arg::data16, 0x87, arg::reg2mreg>;
			using xchg_r32_r32 = make_asm<0x87, arg::reg2mreg>;
			using xchg_r64_r64 = make_asm<arg::rex_w, 0x87, arg::reg2mreg>;
			using xchg_m8_r8 = make_asm<0x86, arg::reg2mem>;
			using xchg_m16_r16 = make_asm<arg::data16, 0x87, arg::reg2mem>;
			using xchg_m32_r32 = make_asm<0x87, arg::reg2mem>;
			using xchg_m64_r64 = make_asm<arg::rex_w, 0x87, arg::reg2mem>;
			using xchg_r8_m8 = make_asm<0x86, arg::mem2reg>;
			using xchg_r16_m16 = make_asm<arg::data16, 0x87, arg::mem2reg>;
			using xchg_r32_m32 = make_asm<0x87, arg::mem2reg>;
			using xchg_r64_m64 = make_asm<arg::rex_w, 0x87, arg::mem2reg>;

			using xgetbv = make_asm<0x0F, 0x01, 0xD0>;

			using xlat = make_asm<0xD7>;

			def_binary_operator(xor, 0x34, 0x35, 6, 0x30, 0x31, 0x32, 0x33);

			using xrstor = make_asm<0x0F, 0xAE, arg::mem | 5>;
			using xrstor64 = make_asm<arg::rex_w, 0x0F, 0xAE, arg::mem | 5>;

			using xsave = make_asm<0x0F, 0xAE, arg::mem | 4>;
			using xsave64 = make_asm<arg::rex_w, 0x0F, 0xAE, arg::mem | 4>;

			using xsetbv = make_asm<0x0F, 0x01, 0xD1>;
		}
	}
}

#undef def_binary_operator
#undef def_unary_operator
#undef def_al_ax_eax_operator
#undef def_not_neg
#undef def_bit_test
#undef def_jmp
#undef def_shift
#undef def_double_shift
#undef def_set
#undef def_cmov
#undef def_float_binary_operator
#undef def_mem_reg_binary_operator