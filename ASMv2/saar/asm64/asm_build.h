#pragma once

#include "MEMORY.h"
#include "context.h"
#include "type.h"
#include <type_traits>

/*
op type:

op1
op1 op2
op1|r
op1 d
op1 m(sub_op) d
op1 r(sub_op) d
op1 m(sub_op)
op1 r(sub_op)
op1 m(r)
op1 r(r)
op1 op2 m(sub_op) d
op1 op2 r(sub_op) d
op1 op2 m(r)
op1 op2 r(r)
op1 op2 m(r) d
op1 op2 r(r) d
*/
namespace saar {
	namespace asm64 {
		namespace build {

			typedef size_t op_t;

			enum arg : op_t {
				byte = 1 << 8,
				word = 2 << 8,
				dword = 3 << 8,
				qword = 4 << 8,
				mem = 5 << 8,
				reg = 6 << 8,
				mem_reg = 7 << 8,
				reg_mem = 8 << 8,
				reg2mreg = 9 << 8,
				mreg2reg = 10 << 8,
				op_reg = 11 << 8,
				rex = 12 << 8,
				rex_w = (12 << 8) | 0b1000,
				rex_r = (12 << 8) | 0b0100,
				rex_x = (12 << 8) | 0b0010,
				rex_b = (12 << 8) | 0b0001,
				data16 = 13 << 8,
				addr16 = 14 << 8,
				lock_repeat = 15 << 8,
				seg_override = 16 << 8
			};

			enum class op_type : int {
				none = -1,
				b,
				w,
				d,
				q,
				m,
				r,
				mr,
				rm,
				r2mr,
				mr2r,
				op_reg,
				rex,
				data16,
				addr16,
				lock_repeat,
				seg_override,
			};

			template<typename...Args>
			struct asm_args {};

			template<op_type value>
			struct sel_arg { typedef asm_args<> type; };
			template<>
			struct sel_arg<op_type::b> { typedef asm_args<type::byte> type; };
			template<>
			struct sel_arg<op_type::w> { typedef asm_args<type::word> type; };
			template<>
			struct sel_arg<op_type::d> { typedef asm_args<type::dword> type; };
			template<>
			struct sel_arg<op_type::q> { typedef asm_args<type::qword> type; };
			template<>
			struct sel_arg<op_type::r> { typedef asm_args<register_t> type; };
			template<>
			struct sel_arg<op_type::m> { typedef asm_args<memory> type; };
			template<>
			struct sel_arg<op_type::mr> { typedef asm_args<memory, register_t> type; };
			template<>
			struct sel_arg<op_type::rm> { typedef asm_args<register_t, memory> type; };
			template<>
			struct sel_arg<op_type::r2mr> { typedef asm_args<register_t, register_t> type; };
			template<>
			struct sel_arg<op_type::mr2r> { typedef asm_args<register_t, register_t> type; };
			template<>
			struct sel_arg<op_type::op_reg> { typedef asm_args<register_t> type; };

			template<op_t V>
			struct make_arg {
				enum : int {
					value =
					V == arg::byte ? (int)op_type::b :
					V == arg::word ? (int)op_type::w :
					V == arg::dword ? (int)op_type::d :
					V == arg::qword ? (int)op_type::q :
					(V & 0xFF00) == arg::reg ? (int)op_type::r :
					(V & 0xFF00) == arg::mem ? (int)op_type::m :
					V == arg::mem_reg ? (int)op_type::mr :
					V == arg::reg_mem ? (int)op_type::rm :
					V == arg::reg2mreg ? (int)op_type::r2mr :
					V == arg::mreg2reg ? (int)op_type::mr2r :
					(V & 0xFF00) == arg::op_reg ? (int)op_type::op_reg :
					(V & 0xFF00) == arg::rex ? (int)op_type::rex :
					V == arg::data16 ? (int)op_type::data16 :
					V == arg::addr16 ? (int)op_type::addr16 :
					(V & 0xFF00) == arg::lock_repeat ? (int)op_type::lock_repeat :
					(V & 0xFF00) == arg::seg_override ? (int)op_type::seg_override :
					(int)op_type::none
				};

				typedef typename sel_arg<(op_type)value>::type type;
			};

			template<typename T>
			struct remove_const_ref {
				typedef T type;
			};

			template<typename T>
			struct remove_const_ref<const T&> {
				typedef T type;
			};

			template<typename T>
			struct remove_const_ref<T&> {
				typedef T type;
			};

			template<typename T>
			struct remove_const_ref<T&&> {
				typedef T type;
			};

			template<typename arg_t1, typename args_t2>
			struct args_add;

			template<typename...args1, typename...args2>
			struct args_add<asm_args<args1...>, asm_args<args2...>> {
				typedef asm_args<args1..., args2...> type;
			};

			template<op_t...>
			struct make_args;

			template<bool, typename T, typename F>
			struct _If {
				typedef T type;
			};

			template<typename T, typename F>
			struct _If<false, T, F> {
				typedef F type;
			};

			template<typename T>
			struct optimize {
				typedef typename _If<(sizeof(T) <= sizeof(void*) && ::std::is_trivially_destructible<T>::value) || ::std::is_enum<T>::value, T, const T&>::type type;
			};

			template<op_t op, op_t...ops>
			struct make_args<op, ops...> {
				typedef typename _If<(op <= 255),
					typename make_args<ops...>::type,
					typename args_add<typename make_arg<op>::type, typename make_args<ops...>::type>::type
				>::type type;
			};

			template<>
			struct make_args<> {
				typedef asm_args<> type;
			};

			template<class args_t, op_t...ops>
			struct make_asm_args;

			template<op_type op_v, op_t...ops>
			struct call_asm_args;

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::none, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, Args&&...args) {
					ctx.push_opcode(op);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::rex, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, Args&&...args) {
					ctx.set_rex_prefixes((unsigned char)op);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::data16, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, Args&&...args) {
					ctx.set_operand_size_prefixes();
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::addr16, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, Args&&...args) {
					ctx.set_address_size_prefixes();
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::lock_repeat, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, Args&&...args) {
					ctx.set_lock_repeat_prefixes((unsigned char)op);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::seg_override, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, Args&&...args) {
					ctx.set_segment_override_prefixes((unsigned char)op);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::b, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, type::byte b, Args&&...args) {
					ctx.push_data_b(b);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::w, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, type::word w, Args&&...args) {
					ctx.push_data_w(w);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::d, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, type::dword d, Args&&...args) {
					ctx.push_data_l(d);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::q, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, type::qword q, Args&&...args) {
					ctx.push_data_q(q);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::r, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, register_t r, Args&&...args) {
					ctx.set_reg_opcode(op, r);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::m, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, const memory &mem, Args&&...args) {
					ctx.set_mem_reg(mem, (register_t)REGX(op));
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::mr, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, const memory &mem, register_t reg, Args&&...args) {
					ctx.set_mem_reg(mem, reg);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::rm, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, register_t reg, const memory &mem, Args&&...args) {
					ctx.set_mem_reg(mem, reg);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::r2mr, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, register_t dst, register_t src, Args&&...args) {
					ctx.set_reg_reg(src, dst);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::mr2r, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, register_t dst, register_t src, Args&&...args) {
					ctx.set_reg_reg(dst, src);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::op_reg, op, ops...> {
				template<typename...Args>
				inline static void _op(context &ctx, register_t reg, Args&&...args) {
					ctx.push_opcode_reg((unsigned char)op, reg);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ctx, args...);
				}
			};

			template<class args_t, op_t...ops>
			struct make_asm_args;

			template<class...Args, op_t op, op_t...ops>
			struct make_asm_args<asm_args<Args...>, op, ops...> {
			private:
				typedef call_asm_args<(op_type)make_arg<op>::value, op, ops...> call_t;

			public:
				inline static void _op(context &ctx, typename optimize<Args>::type...args) {
					call_t::_op(ctx, args...);
				}

				static size_t op(context &ctx, typename optimize<Args>::type...args) {
					ctx.reset_status();
					size_t count = ctx.buf_size();
					_op(ctx, args...);
					ctx.flush();
					return ctx.buf_size() - count;
				}
			};

			template<>
			struct make_asm_args<asm_args<>> {
				inline static void _op(context &ctx) {
				}
			};

			template<op_t...ops>
			struct make_asm : make_asm_args<typename make_args<ops...>::type, ops...> {};
		}
	}
}


