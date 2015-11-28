#pragma once

#include "asm_build.h"

#define def_binary_operator(name, al_i8, eax_i32, sub_op, rm_r8, rm_r32, r_rm8, r_rm32)\
	using name##_al_i8 = make_asm<al_i8, arg::byte>;\
	using name##_ax_i16 = make_asm<0x66, eax_i32, arg::word>;\
	using name##_eax_i32 = make_asm<eax_i32, arg::dword>;\
	using name##_r_i8 = make_asm<0x80, arg::reg | sub_op, arg::byte>;\
	using name##_r_i16 = make_asm<0x66, 0x81, arg::reg | sub_op, arg::word>;\
	using name##_r_i32 = make_asm<0x81, arg::reg | sub_op, arg::dword>;\
	using name##_r16_i8 = make_asm<0x66, 0x83, arg::reg | sub_op, arg::byte>;\
	using name##_r32_i8 = make_asm<0x83, arg::reg | sub_op, arg::byte>;\
	using name##_m_i8 = make_asm<0x80, arg::mem | sub_op, arg::byte>;\
	using name##_m_i16 = make_asm<0x66, 0x81, arg::mem | sub_op, arg::word>;\
	using name##_m_i32 = make_asm<0x81, arg::mem | sub_op, arg::dword>;\
	using name##_m16_i8 = make_asm<0x66, 0x83, arg::mem | sub_op, arg::byte>;\
	using name##_m32_i8 = make_asm<0x83, arg::mem | sub_op, arg::byte>;\
	using name##_r_r8 = make_asm<rm_r8, arg::reg2mreg>;\
	using name##_r_r16 = make_asm<0x66, rm_r32, arg::reg2mreg>;\
	using name##_r_r32 = make_asm<rm_r32, arg::reg2mreg>;\
	using name##_m_r8 = make_asm<rm_r8, arg::mem_reg>;\
	using name##_m_r16 = make_asm<0x66, rm_r32, arg::mem_reg>;\
	using name##_m_r32 = make_asm<rm_r32, arg::mem_reg>;\
	using name##_r_m8 = make_asm<r_rm8, arg::reg_mem>;\
	using name##_r_m16 = make_asm<0x66, r_rm32, arg::reg_mem>;\
	using name##_r_m32 = make_asm<r_rm32, arg::reg_mem>

#define def_unary_operator(name, sub_op, r)\
	using name##_r8 = make_asm<0xFE, arg::reg | sub_op>;\
	using name##_r16 = make_asm<0x66, r | arg::op_reg>;\
	using name##_r32 = make_asm<r | arg::op_reg>;\
	using name##_m8 = make_asm<0xFE, arg::mem | sub_op>;\
	using name##_m16 = make_asm<0x66, 0xFF, arg::mem | sub_op>;\
	using name##_m32 = make_asm<0xFF, arg::mem | sub_op>

#define def_al_ax_eax_operator(name, sub_op)\
	using name##_al_r8 = make_asm<0xF6, arg::reg | sub_op>;\
	using name##_ax_r16 = make_asm<0x66, 0xF7, arg::reg | sub_op>;\
	using name##_eax_r32 = make_asm<0xF7, arg::reg | sub_op>;\
	using name##_al_m8 = make_asm<0xF6, arg::mem | sub_op>;\
	using name##_ax_m16 = make_asm<0x66, 0xF7, arg::mem | sub_op>;\
	using name##_eax_m32 = make_asm<0xF7, arg::mem | sub_op>

#define def_not_neg(name, sub_op)\
	using name##_r8 = make_asm<0xF6, arg::reg | sub_op>;\
	using name##_r16 = make_asm<0x66, 0xF7, arg::reg | sub_op>;\
	using name##_r32 = make_asm<0xF7, arg::reg | sub_op>;\
	using name##_m8 = make_asm<0xF6, arg::mem | sub_op>;\
	using name##_m16 = make_asm<0x66, 0xF7, arg::mem | sub_op>;\
	using name##_m32 = make_asm<0xF7, arg::mem | sub_op>

#define def_bit_test(name, rm, sub_op)\
	using name##_r_r16 = make_asm<0x66, 0x0F, rm, arg::reg2mreg>;\
	using name##_m_r16 = make_asm<0x66, 0x0F, rm, arg::mem_reg>;\
	using name##_r_r32 = make_asm<0x0F, rm, arg::reg2mreg>;\
	using name##_m_r32 = make_asm<0x0F, rm, arg::mem_reg>;\
	using name##_r16_i8 = make_asm<0x66, 0x0F, 0xBA, arg::reg | sub_op, arg::byte>;\
	using name##_m16_i8 = make_asm<0x66, 0x0F, 0xBA, arg::mem | sub_op, arg::byte>;\
	using name##_r32_i8 = make_asm<0x0F, 0xBA, arg::reg | sub_op, arg::byte>;\
	using name##_m32_i8 = make_asm<0x0F, 0xBA, arg::mem | sub_op, arg::byte>

#define def_jmp(name, jmp_i8, jmp_i32)\
	using name##_i8 = make_asm<jmp_i8, arg::byte>;\
	using name##_i32 = make_asm<0x0F, jmp_i32, arg::dword>

#define def_shift(name, sub_op, rm8_1, rm8_cl, rm8_i, rm32_1, rm32_cl, rm32_i)\
	using name##_r8_1 = make_asm<rm8_1, arg::reg | sub_op>;\
	using name##_r8_cl = make_asm<rm8_cl, arg::reg | sub_op>;\
	using name##_r8_i = make_asm<rm8_i, arg::reg | sub_op, arg::byte>;\
	using name##_r16_1 = make_asm<0x66, rm32_1, arg::reg | sub_op>;\
	using name##_r16_cl = make_asm<0x66, rm32_cl, arg::reg | sub_op>;\
	using name##_r16_i = make_asm<0x66, rm32_i, arg::reg | sub_op, arg::word>;\
	using name##_r32_1 = make_asm<rm32_1, arg::reg | sub_op>;\
	using name##_r32_cl = make_asm<rm32_cl, arg::reg | sub_op>;\
	using name##_r32_i = make_asm<rm32_i, arg::reg | sub_op, arg::dword>;\
	using name##_m8_1 = make_asm<rm8_1, arg::mem | sub_op>;\
	using name##_m8_cl = make_asm<rm8_cl, arg::mem | sub_op>;\
	using name##_m8_i = make_asm<rm8_i, arg::mem | sub_op, arg::byte>;\
	using name##_m16_1 = make_asm<0x66, rm32_1, arg::mem | sub_op>;\
	using name##_m16_cl = make_asm<0x66, rm32_cl, arg::mem | sub_op>;\
	using name##_m16_i = make_asm<0x66, rm32_i, arg::mem | sub_op, arg::word>;\
	using name##_m32_1 = make_asm<rm32_1, arg::mem | sub_op>;\
	using name##_m32_cl = make_asm<rm32_cl, arg::mem | sub_op>;\
	using name##_m32_i = make_asm<rm32_i, arg::mem | sub_op, arg::dword>

#define def_double_shift(name, i8, cl)\
	using name##_r_r16_i8 = make_asm<0x66, 0x0F, i8, arg::reg2mreg, arg::byte>;\
	using name##_r_r32_i8 = make_asm<0x0F, i8, arg::reg2mreg, arg::byte>;\
	using name##_r_r16_cl = make_asm<0x66, 0x0F, cl, arg::reg2mreg>;\
	using name##_r_r32_cl = make_asm<0x0F, cl, arg::reg2mreg>;\
	using name##_m_r16_i8 = make_asm<0x66, 0x0F, i8, arg::mem_reg, arg::byte>;\
	using name##_m_r32_i8 = make_asm<0x0F, i8, arg::mem_reg, arg::byte>;\
	using name##_m_r16_cl = make_asm<0x66, 0x0F, cl, arg::mem_reg>;\
	using name##_m_r32_cl = make_asm<0x0F, cl, arg::mem_reg>

#define def_set(name, op)\
	using name##_r = make_asm<0x0F, op, arg::reg>;\
	using name##_m = make_asm<0x0F, op, arg::mem>

#define def_cmov(name, op)\
	using name##_r_r16 = make_asm<0x66, 0x0F, op, arg::mreg2reg>;\
	using name##_r_r32 = make_asm<0x0F, op, arg::mreg2reg>;\
	using name##_r_m16 = make_asm<0x66, 0x0F, op, arg::reg_mem>;\
	using name##_r_m32 = make_asm<0x0F, op, arg::reg_mem>

namespace saar {
	namespace asm32 {
		using saar::asm32::build::arg;
		using saar::asm32::build::make_asm;

		namespace instruction {
			using aaa = make_asm<0x37>;
			using aad = make_asm<0xD5, 0x0A>;
			using aam = make_asm<0xD4, 0x0A>;
			using aas = make_asm<0x3F>;

			def_binary_operator(adc, 0x14, 0x15, 2, 0x10, 0x11, 0x12, 0x13);
			def_binary_operator(add, 0x04, 0x05, 0, 0x00, 0x01, 0x02, 0x03);
			def_binary_operator(and, 0x24, 0x25, 4, 0x20, 0x21, 0x22, 0x23);

			using arpl_r_r = make_asm<0x63, arg::reg2mreg>;
			using arpl_m_r = make_asm<0x63, arg::mem_reg>;

			using bound_r_r16 = make_asm<0x66, 0x62, arg::mreg2reg>;
			using bound_r_m16 = make_asm<0x66, 0x62, arg::reg_mem>;
			using bound_r_r32 = make_asm<0x62, arg::mreg2reg>;
			using bound_r_m32 = make_asm<0x62, arg::reg_mem>;

			using bsf_r_r16 = make_asm<0x66, 0xF0, 0xBC, arg::mreg2reg>;
			using bsf_r_m16 = make_asm<0x66, 0xF0, 0xBC, arg::reg_mem>;
			using bsf_r_r32 = make_asm<0xF0, 0xBC, arg::mreg2reg>;
			using bsf_r_m32 = make_asm<0xF0, 0xBC, arg::reg_mem>;

			using bsr_r_r16 = make_asm<0x66, 0x0F, 0xBD, arg::mreg2reg>;
			using bsr_r_m16 = make_asm<0x66, 0x0F, 0xBD, arg::reg_mem>;
			using bsr_r_r32 = make_asm<0x0F, 0xBD, arg::mreg2reg>;
			using bsr_r_m32 = make_asm<0x0F, 0xBD, arg::reg_mem>;

			def_bit_test(bt, 0xA3, 4);
			def_bit_test(btc, 0xBB, 7);
			def_bit_test(btr, 0xB3, 6);
			def_bit_test(bts, 0xAB, 5);

			using call_i32 = make_asm<0xE8, arg::dword>;
			using call_r = make_asm<0xFF, arg::reg | 2>;
			using call_m = make_asm<0xFF, arg::mem | 2>;
			using call_i32_i16 = make_asm<0x9A, arg::dword, arg::word>;

			using cbw = make_asm<0x66, 0x98>;
			using cwde = make_asm<0x98>;

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
			using cmpsw = make_asm<0x66, 0xA7>;
			using cmpsd = make_asm<0xA7>;

			using cmpxchg_r8_r8 = make_asm<0x0F, 0xB0, arg::reg2mreg>;
			using cmpxchg_r16_r16 = make_asm<0x66, 0x0F, 0xB1, arg::reg2mreg>;
			using cmpxchg_r32_r32 = make_asm<0x0F, 0xB1, arg::reg2mreg>;
			using cmpxchg_m8_r8 = make_asm<0x0F, 0xB0, arg::mem_reg>;
			using cmpxchg_m16_r16 = make_asm<0x66, 0x0F, 0xB1, arg::mem_reg>;
			using cmpxchg_m32_r32 = make_asm<0x0F, 0xB1, arg::mem_reg>;

			using cmpxchg8b_m64 = make_asm<0x0F, 0xC7, arg::mem | 1>;

			using cpuid = make_asm<0x0F, 0xA2>;

			using cwd = make_asm<0x66, 0x99>;
			using cdq = make_asm<0x99>;

			using daa = make_asm<0x27>;
			using das = make_asm<0x2F>;

			def_unary_operator(dec, 1, 0x48);

			def_al_ax_eax_operator(div, 6);

			using enter = make_asm<0xC8, arg::word, arg::byte>;
			using hlt = make_asm<0xF4>;

			def_al_ax_eax_operator(idiv, 7);

			def_al_ax_eax_operator(imul, 5);
			using imul_r_r16 = make_asm<0x66, 0x0F, 0xAF, arg::mreg2reg>;
			using imul_r_r32 = make_asm<0x0F, 0xAF, arg::mreg2reg>;
			using imul_r_m16 = make_asm<0x66, 0x0F, 0xAF, arg::reg_mem>;
			using imul_r_m32 = make_asm<0x0F, 0xAF, arg::reg_mem>;
			using imul_r_r16_i8 = make_asm<0x66, 0x6B, arg::mreg2reg, arg::byte>;
			using imul_r_r32_i8 = make_asm<0x6B, arg::mreg2reg, arg::byte>;
			using imul_r_m16_i8 = make_asm<0x66, 0x6B, arg::mem_reg, arg::byte>;
			using imul_r_m32_i8 = make_asm<0x6B, arg::mem_reg, arg::byte>;
			using imul_r_r16_i16 = make_asm<0x66, 0x69, arg::mreg2reg, arg::word>;
			using imul_r_r32_i32 = make_asm<0x69, arg::mreg2reg, arg::dword>;
			using imul_r_m16_i16 = make_asm<0x66, 0x69, arg::mem_reg, arg::word>;
			using imul_r_m32_i32 = make_asm<0x69, arg::mem_reg, arg::dword>;

			using in_al = make_asm<0xE4, arg::byte>;
			using in_ax = make_asm<0x66, 0xE5, arg::byte>;
			using in_eax = make_asm<0xE5, arg::byte>;
			using in_al_dx = make_asm<0xEC>;
			using in_ax_dx = make_asm<0x66, 0xED>;
			using in_eax_dx = make_asm<0xED>;

			def_unary_operator(inc, 0, 0x40);

			using insb = make_asm<0x6C>;
			using insw = make_asm<0x66, 0x6D>;
			using insd = make_asm<0x6D>;

			using int_3 = make_asm<0xCC>;
			using int_i8 = make_asm<0xCD, arg::byte>;
			using into = make_asm<0xCE>;

			using iret = make_asm<0x66, 0xCF>;
			using iretd = make_asm<0xCF>;

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
			using jmp_i16 = make_asm<0x66, 0xE9, arg::word>;
			using jmp_i32 = make_asm<0xE9, arg::dword>;
			using jmp_i32_i16 = make_asm<0xEA, arg::dword, arg::word>;
			using jmp_r = make_asm<0xFF, arg::reg | 4>;
			using jmp_m = make_asm<0xFF, arg::mem | 4>;
			using jmp_far_m48 = make_asm<0xFF, arg::mem | 5>;

			using lahf = make_asm<0x9F>;

			using lar_r_r16 = make_asm<0x66, 0x0F, 0x02, arg::mreg2reg>;
			using lar_r_m16 = make_asm<0x66, 0x0F, 0x02, arg::reg_mem>;
			using lar_r_r32 = make_asm<0x0F, 0x02, arg::mreg2reg>;
			using lar_r_m32 = make_asm<0x0F, 0x02, arg::reg_mem>;

			using lea_r_m16 = make_asm<0x66, 0x8D, arg::reg_mem>;
			using lea_r_m32 = make_asm<0x8D, arg::reg_mem>;

			using leave_16 = make_asm<0x66, 0xC9>;
			using leave_32 = make_asm<0xC9>;

			using lgdt = make_asm<0x0F, 0x01, arg::mem | 2>;
			using lidt = make_asm<0x0F, 0x01, arg::mem | 3>;

			using lds_r_m16 = make_asm<0x66, 0xC5, arg::reg_mem>;
			using lds_r_m32 = make_asm<0xC5, arg::reg_mem>;
			using lss_r_m16 = make_asm<0x66, 0x0F, 0xB2, arg::reg_mem>;
			using lss_r_m32 = make_asm<0x0F, 0xB2, arg::reg_mem>;
			using les_r_m16 = make_asm<0x66, 0xC4, arg::reg_mem>;
			using les_r_m32 = make_asm<0xC4, arg::reg_mem>;
			using lfs_r_m16 = make_asm<0x66, 0x0F, 0xB4, arg::reg_mem>;
			using lfs_r_m32 = make_asm<0x0F, 0xB4, arg::reg_mem>;
			using lgs_r_m16 = make_asm<0x66, 0x0F, 0xB5, arg::reg_mem>;
			using lgs_r_m32 = make_asm<0x0F, 0xB5, arg::reg_mem>;

			using lldt_r = make_asm<0x0F, 0x00, arg::reg | 2>;
			using lldt_m = make_asm<0x0F, 0x00, arg::mem | 2>;
			using lmsw_r = make_asm<0x0F, 0x01, arg::reg | 6>;
			using lmsw_m = make_asm<0x0F, 0x01, arg::mem | 6>;

			using lock = make_asm<0xF0>;

			using lodsb = make_asm<0xAC>;
			using lodsw = make_asm<0x66, 0xAD>;
			using lodsd = make_asm<0xAD>;

			using loop = make_asm<0xE2, arg::byte>;
			using loope = make_asm<0xE1, arg::byte>;
			using loopz = make_asm<0xE1, arg::byte>;
			using loopne = make_asm<0xE0, arg::byte>;
			using loopnz = make_asm<0xE0, arg::byte>;

			using lsl_r_r16 = make_asm<0x66, 0x0F, 0x03, arg::mreg2reg>;
			using lsl_r_r32 = make_asm<0x0F, 0x03, arg::mreg2reg>;
			using lsl_r_m16 = make_asm<0x66, 0x0F, 0x03, arg::mem_reg>;
			using lsl_r_m32 = make_asm<0x0F, 0x03, arg::mem_reg>;

			using ltr_r = make_asm<0x0F, 0x00, arg::reg | 3>;
			using ltr_m = make_asm<0x0F, 0x00, arg::mem | 3>;

			using mov_r_r8 = make_asm<0x88, arg::reg2mreg>;
			using mov_r_r16 = make_asm<0x66, 0x89, arg::reg2mreg>;
			using mov_r_r32 = make_asm<0x89, arg::reg2mreg>;
			using mov_m_r8 = make_asm<0x88, arg::mem_reg>;
			using mov_m_r16 = make_asm<0x66, 0x89, arg::mem_reg>;
			using mov_m_r32 = make_asm<0x89, arg::mem_reg>;
			using mov_r_m8 = make_asm<0x8A, arg::reg_mem>;
			using mov_r_m16 = make_asm<0x66, 0x8B, arg::reg_mem>;
			using mov_r_m32 = make_asm<0x8B, arg::reg_mem>;
			using mov_r_seg = make_asm<0x8C, arg::reg2mreg>;
			using mov_m_seg = make_asm<0x8C, arg::mem_reg>;
			using mov_seg_r = make_asm<0x8D, arg::mreg2reg>;
			using mov_seg_m = make_asm<0x8D, arg::mem_reg>;
			using mov_al_moffs = make_asm<0xA0, arg::dword>;
			using mov_ax_moffs = make_asm<0x66, 0xA1, arg::dword>;
			using mov_eax_moffs = make_asm<0xA1, arg::dword>;
			using mov_moffs_al = make_asm<0xA2, arg::dword>;
			using mov_moffs_ax = make_asm<0x66, 0xA3, arg::dword>;
			using mov_moffs_eax = make_asm<0xA3, arg::dword>;
			using mov_r_i8 = make_asm<0xB0 | arg::op_reg, arg::byte>;
			using mov_r_i16 = make_asm<0x66, 0xB8 | arg::op_reg, arg::word>;
			using mov_r_i32 = make_asm<0xB8 | arg::op_reg, arg::dword>;
			using mov_m_i8 = make_asm<0xC6, arg::mem | 0, arg::byte>;
			using mov_m_i16 = make_asm<0x66, 0xC7, arg::mem | 0, arg::word>;
			using mov_m_i32 = make_asm<0xC7, arg::mem | 0, arg::dword>;

			using mov_r_cr = make_asm<0x0F, 0x20, arg::reg2mreg>;
			using mov_cr_r = make_asm<0x0F, 0x22, arg::mreg2reg>;
			using mov_r_dr = make_asm<0x0F, 0x21, arg::reg2mreg>;
			using mov_dr_r = make_asm<0x0F, 0x23, arg::mreg2reg>;

			using movbe_r_m16 = make_asm<0x66, 0x0F, 0x38, 0xF0, arg::reg_mem>;
			using movbe_r_m32 = make_asm<0x0F, 0x38, 0xF0, arg::reg_mem>;
			using movbe_m_r16 = make_asm<0x66, 0x0F, 0x38, 0xF1, arg::mem_reg>;
			using movbe_m_r32 = make_asm<0x0F, 0x38, 0xF1, arg::mem_reg>;

			using movsb = make_asm<0xA4>;
			using movsw = make_asm<0x66, 0xA5>;
			using movsd = make_asm<0xA5>;

			using movsx_r16_r8 = make_asm<0x66, 0x0F, 0xBE, arg::mreg2reg>;
			using movsx_r32_r8 = make_asm<0x0F, 0xBE, arg::mreg2reg>;
			using movsx_r32_r16 = make_asm<0x0F, 0xBF, arg::mreg2reg>;
			using movsx_r16_m8 = make_asm<0x66, 0x0F, 0xBE, arg::reg_mem>;
			using movsx_r32_m8 = make_asm<0x0F, 0xBE, arg::reg_mem>;
			using movsx_r32_m16 = make_asm<0x0F, 0xBF, arg::reg_mem>;

			using movzx_r16_r8 = make_asm<0x66, 0x0F, 0xB6, arg::mreg2reg>;
			using movzx_r32_r8 = make_asm<0x0F, 0xB6, arg::mreg2reg>;
			using movzx_r32_r16 = make_asm<0x0F, 0xB7, arg::mreg2reg>;
			using movzx_r16_m8 = make_asm<0x66, 0x0F, 0xB6, arg::reg_mem>;
			using movzx_r32_m8 = make_asm<0x0F, 0xB6, arg::reg_mem>;
			using movzx_r32_m16 = make_asm<0x0F, 0xB7, arg::reg_mem>;

			def_al_ax_eax_operator(mul, 4);
			def_not_neg(neg, 3);

			using nop = make_asm<0x90>;
			using nop_r16 = make_asm<0x66, 0x0F, 0x1F, arg::reg | 0>;
			using nop_r32 = make_asm<0x0F, 0x1F, arg::reg | 0>;
			using nop_m16 = make_asm<0x66, 0x0F, 0x1F, arg::mem | 0>;
			using nop_m32 = make_asm<0x0F, 0x1F, arg::mem | 0>;

			def_not_neg(not, 2);
			def_binary_operator(or , 0x0C, 0x0D, 1, 0x08, 0x09, 0x0A, 0x0B);

			using out_al = make_asm<0xE6, arg::byte>;
			using out_ax = make_asm<0x66, 0x75, arg::byte>;
			using out_eax = make_asm<0xE7, arg::byte>;
			using out_dx_al = make_asm<0xEE>;
			using out_dx_ax = make_asm<0x66, 0xEF>;
			using out_dx_eax = make_asm<0xEF>;

			using outsb = make_asm<0x6E>;
			using outsw = make_asm<0x66, 0x6F>;
			using outsd = make_asm<0x6F>;

			using pop_m16 = make_asm<0x66, 0x8F, arg::mem | 0>;
			using pop_m32 = make_asm<0x8F, arg::mem | 0>;
			using pop_r16 = make_asm<0x66, 0x58 | arg::op_reg>;
			using pop_r32 = make_asm<0x58 | arg::op_reg>;
			using pop_ds = make_asm<0x1F>;
			using pop_es = make_asm<0x07>;
			using pop_ss = make_asm<0x17>;
			using pop_fs = make_asm<0x0F, 0xA1>;
			using pop_gs = make_asm<0x0F, 0xA9>;

			using popa = make_asm<0x66, 0x61>;
			using popad = make_asm<0x61>;

			using popf = make_asm<0x66, 0x9D>;
			using popfd = make_asm<0x9D>;

			using push_m16 = make_asm<0x66, 0xFF, arg::mem | 6>;
			using push_m32 = make_asm<0xFF, arg::mem | 6>;
			using push_r16 = make_asm<0x66, 0x50 | arg::op_reg>;
			using push_r32 = make_asm<0x50 | arg::op_reg>;
			using push_i8 = make_asm<0x6A, arg::byte>;
			using push_i16 = make_asm<0x66, 0x68, arg::word>;
			using push_i32 = make_asm<0x68, arg::dword>;
			using push_cs = make_asm<0x0E>;
			using push_ds = make_asm<0x1E>;
			using push_es = make_asm<0x06>;
			using push_ss = make_asm<0x16>;
			using push_fs = make_asm<0x0F, 0xA0>;
			using push_gs = make_asm<0x0F, 0xA8>;

			using pusha = make_asm<0x66, 0x60>;
			using pushad = make_asm<0x60>;

			using pushf = make_asm<0x66, 0x9C>;
			using pushfd = make_asm<0x9C>;

			def_shift(rcl, 2, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(rcr, 3, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(rol, 0, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(ror, 1, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);

			using repe = make_asm<0xF3>;
			using repne = make_asm<0xF2>;

			using ret = make_asm<0xC3>;
			using ret_far = make_asm<0xCB>;
			using ret_i16 = make_asm<0xC2, arg::word>;
			using ret_far_i16 = make_asm<0xCA, arg::word>;

			using sahf = make_asm<0x9E>;

			def_shift(sal, 4, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(sar, 7, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(shl, 4, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);
			def_shift(shr, 5, 0xD0, 0xD2, 0xC0, 0xD1, 0xD3, 0xC1);

			def_binary_operator(sbb, 0x1C, 0x1D, 3, 0x18, 0x19, 0x1A, 0x1B);

			using scasb = make_asm<0xAE>;
			using scasw = make_asm<0x66, 0xAF>;
			using scasd = make_asm<0xAF>;

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

			using sgdt = make_asm<0x0F, 0x01, arg::mem | 0>;
			using sidt = make_asm<0x0F, 0x01, arg::mem | 1>;

			def_double_shift(shld, 0xA4, 0xA5);
			def_double_shift(shrd, 0xAC, 0xAD);

			using sldt_r = make_asm<0x0F, 0x00, arg::reg | 0>;
			using sldt_m = make_asm<0x0F, 0x00, arg::mem | 0>;

			using smsw_r = make_asm<0x0F, 0x01, arg::reg | 4>;
			using smsw_m = make_asm<0x0F, 0x01, arg::mem | 4>;

			using stc = make_asm<0xF9>;
			using std = make_asm<0xFD>;
			using sti = make_asm<0xFB>;

			using stosb = make_asm<0xAA>;
			using stosw = make_asm<0x66, 0xAB>;
			using stosd = make_asm<0xAB>;

			using str_r = make_asm<0x0F, 0x00, arg::reg | 1>;
			using str_m = make_asm<0x0F, 0x00, arg::mem | 1>;

			def_binary_operator(sub, 0x2C, 0x2D, 5, 0x28, 0x29, 0x2A, 0x2B);

			using test_al_i8 = make_asm<0xA8, arg::byte>;
			using test_ax_i16 = make_asm<0x66, 0xA9, arg::word>;
			using test_eax_i32 = make_asm<0xA9, arg::dword>;
			using test_r_i8 = make_asm<0xF6, arg::reg | 0, arg::byte>;
			using test_r_i16 = make_asm<0x66, 0xF7, arg::reg | 0, arg::word>;
			using test_r_i32 = make_asm<0xF7, arg::reg | 0, arg::word>;
			using test_m_i8 = make_asm<0xF6, arg::mem | 0, arg::byte>;
			using test_m_i16 = make_asm<0x66, 0xF7, arg::mem | 0, arg::word>;
			using test_m_i32 = make_asm<0xF7, arg::mem | 0, arg::word>;
			using test_r_r8 = make_asm<0x84, arg::reg2mreg>;
			using test_r_r16 = make_asm<0x66, 0x85, arg::reg2mreg>;
			using test_r_r32 = make_asm<0x85, arg::reg2mreg>;
			using test_m_r8 = make_asm<0x84, arg::mem_reg>;
			using test_m_r16 = make_asm<0x66, 0x85, arg::mem_reg>;
			using test_m_r32 = make_asm<0x85, arg::mem_reg>;

			using verr_r = make_asm<0x0F, 0x00, arg::reg | 4>;
			using verr_m = make_asm<0x0F, 0x00, arg::mem | 4>;
			using verw_r = make_asm<0x0F, 0x00, arg::reg | 5>;
			using verw_m = make_asm<0x0F, 0x00, arg::mem | 5>;

			using wait = make_asm<0x9B>;

			using xchg_ax_r16 = make_asm<0x66, 0x90 | arg::op_reg>;
			using xchg_eax_r32 = make_asm<0x90 | arg::op_reg>;
			using xchg_r_r8 = make_asm<0x86, arg::reg2mreg>;
			using xchg_r_r16 = make_asm<0x66, 0x87, arg::reg2mreg>;
			using xchg_r_r32 = make_asm<0x87, arg::reg2mreg>;
			using xchg_m_r8 = make_asm<0x86, arg::mem_reg>;
			using xchg_m_r16 = make_asm<0x66, 0x87, arg::mem_reg>;
			using xchg_m_r32 = make_asm<0x87, arg::mem_reg>;

			using xlat = make_asm<0xD7>;

			def_binary_operator(xor, 0x34, 0x35, 6, 0x30, 0x31, 0x32, 0x33);
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