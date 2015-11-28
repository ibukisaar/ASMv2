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
	namespace asm32 {
		namespace build {

			typedef size_t op_t;

			enum arg : op_t {
				byte = 1 << 8,
				word = 2 << 8,
				dword = 3 << 8,
				mem = 4 << 8,
				reg = 5 << 8,
				mem_reg = 6 << 8,
				reg_mem = 7 << 8,
				reg2mreg = 8 << 8,
				mreg2reg = 9 << 8,
				op_reg = 10 << 8,
			};

			enum op_type : int {
				none = -1,
				b,
				w,
				d,
				m,
				r,
				mr,
				rm,
				r2mr,
				mr2r,
				opr,
			};

			template<typename...Args>
			struct asm_args {};

			template<int value>
			struct sel_arg { typedef asm_args<> type; };
			template<>
			struct sel_arg<op_type::b> { typedef asm_args<type::byte> type; };
			template<>
			struct sel_arg<op_type::w> { typedef asm_args<type::word> type; };
			template<>
			struct sel_arg<op_type::d> { typedef asm_args<type::dword> type; };
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
			struct sel_arg<op_type::opr> { typedef asm_args<register_t> type; };

			template<op_t V>
			struct make_arg {
				enum : int {
					value =
					V == arg::byte ? op_type::b :
					V == arg::word ? op_type::w :
					V == arg::dword ? op_type::d :
					(V & 0xFF00) == arg::reg ? op_type::r :
					(V & 0xFF00) == arg::mem ? op_type::m :
					V == arg::mem_reg ? op_type::mr :
					V == arg::reg_mem ? op_type::rm :
					V == arg::reg2mreg ? op_type::r2mr :
					V == arg::mreg2reg ? op_type::mr2r :
					(V & 0xFF00) == arg::op_reg ? op_type::opr :
					op_type::none
				};

				typedef typename sel_arg<value>::type type;
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

			template<bool b, typename T, typename F>
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

			template<int op_v, op_t...ops>
			struct call_asm_args;

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::none, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, Args&&...args) {
					ator.push_c((unsigned char)op);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::b, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, type::byte b, Args&&...args) {
					ator.push_c(b);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::w, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, type::word w, Args&&...args) {
					ator.push_s(w);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::d, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, type::dword d, Args&&...args) {
					ator.push_l(d);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::r, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, register_t r, Args&&...args) {
					ator.push_c(0xC0 | (REG(op) << 3) | REG(r));
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::m, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, const memory &mem, Args&&...args) {
					ator.push_mem(mem, (register_t)REG(op));
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::mr, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, const memory &mem, register_t reg, Args&&...args) {
					ator.push_mem(mem, reg);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::rm, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, register_t reg, const memory &mem, Args&&...args) {
					ator.push_mem(mem, reg);
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::r2mr, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, register_t dst, register_t src, Args&&...args) {
					ator.push_c(0xC0 | (REG(src) << 3) | REG(dst));
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::mr2r, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, register_t dst, register_t src, Args&&...args) {
					ator.push_c(0xC0 | (REG(dst) << 3) | REG(src));
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<op_t op, op_t...ops>
			struct call_asm_args<op_type::opr, op, ops...> {
				template<typename...Args>
				static void _op(context &ctx, register_t reg, Args&&...args) {
					ator.push_c((op & 0xF8) | REG(reg));
					make_asm_args<asm_args<typename remove_const_ref<Args>::type...>, ops...>::_op(ator, args...);
				}
			};

			template<class args_t, op_t...ops>
			struct make_asm_args;

			template<class...Args, op_t op, op_t...ops>
			struct make_asm_args<asm_args<Args...>, op, ops...> {
			private:
				typedef call_asm_args<make_arg<op>::value, op, ops...> call_t;

			public:
				static void _op(context &ctx, typename optimize<Args>::type...args) {
					call_t::_op(ator, args...);
				}

				static size_t op(context &ctx, typename optimize<Args>::type...args) {
					size_t count = ator.size();
					_op(ator, args...);
					return ator.size() - count;
				}
			};

			template<>
			struct make_asm_args<asm_args<>> {
				static void _op(context &ctx) {
				}
			};

			template<op_t...ops>
			struct make_asm : make_asm_args<typename make_args<ops...>::type, ops...> {};
		}
	}
}


