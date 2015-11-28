#pragma once

#include <type_traits>
#include "LABEL.h"
#include "MEMORY.h"
#include "allocator.h"

/*
op type:

op|r
ops..
ops.. d
ops.. rm(sub_op) d
ops.. rm(sub_op)
ops.. rm r
ops.. r rm
ops.. m(sub_op)
ops.. r m

*/

typedef size_t op_t;

enum asm_t : op_t {
	byte = 1 << 8,
	word = 2 << 8,
	dword = 3 << 8,
	mem = 4 << 8,
	reg = 5 << 8,
	mem_reg = 6 << 8,
	reg2mreg = 7 << 8,
	mreg2reg = 8 << 8,
	op_reg = 9 << 8,
};

enum op_type : int {
	none = -1,
	b,
	w,
	d,
	m,
	r,
	m2r,
	r2mr,
	mr2r,
	opr,
};

namespace saar {
	template<typename...Args>
	struct asm_args {};

	template<int value>
	struct sel_arg { typedef asm_args<asm_args<>> type; };
	template<>
	struct sel_arg<op_type::b> { typedef asm_args<asm_args<unsigned char>> type; };
	template<>
	struct sel_arg<op_type::w> { typedef asm_args<asm_args<unsigned short>> type; };
	template<>
	struct sel_arg<op_type::d> { typedef asm_args<asm_args<unsigned long>, asm_args<const label &>> type; };
	template<>
	struct sel_arg<op_type::r> { typedef asm_args<asm_args<register_t>> type; };
	template<>
	struct sel_arg<op_type::m> { typedef asm_args<asm_args<const memory &>> type; };
	template<>
	struct sel_arg<op_type::m2r> { typedef asm_args<asm_args<const memory &, register_t>> type; };
	template<>
	struct sel_arg<op_type::r2mr> { typedef asm_args<asm_args<register_t, register_t>> type; };
	template<>
	struct sel_arg<op_type::mr2r> { typedef asm_args<asm_args<register_t, register_t>> type; };
	template<>
	struct sel_arg<op_type::opr> { typedef asm_args<asm_args<register_t>> type; };

	template<op_t V>
	struct make_arg {
		const static int value =
			V == asm_t::byte ? op_type::b :
			V == asm_t::word ? op_type::w :
			V == asm_t::dword ? op_type::d :
			(V & 0xFF00) == asm_t::reg ? op_type::r :
			(V & 0xFF00) == asm_t::mem ? op_type::m :
			V == asm_t::mem_reg ? op_type::m2r :
			V == asm_t::reg2mreg ? op_type::r2mr :
			V == asm_t::mreg2reg ? op_type::mr2r :
			(V & 0xFF00) == asm_t::op_reg ? op_type::opr :
			op_type::none;

		typedef typename sel_arg<value>::type type;
	};

	template<typename arg_t1, typename args_t2>
	struct args_add {};

	template<typename...args1, typename...args2>
	struct args_add<asm_args<args1...>, asm_args<args2...>> {
		typedef asm_args<args1..., args2...> type;
	};


	// make_args_list op, ops... = op <= 255 ? make_args_list ops... : (make_arg op) ++ make_args_list ops...
	// make_args_list = []
	template<op_t...ops>
	struct make_args_list {};

	template<op_t op, op_t...ops>
	struct make_args_list<op, ops...> {
		typedef typename std::conditional<(op <= 255),
			typename make_args_list<ops...>::type,
			typename args_add<asm_args<typename make_arg<op>::type>, typename make_args_list<ops...>::type>::type
		>::type type;
	};

	template<>
	struct make_args_list<> {
		typedef asm_args<> type;
	};

	// arr_union [arg, args...] = arg ++ arr_union [args...]
	// arr_union [] = []
	template<typename args_t>
	struct arr_union {};

	template<typename arg, typename...args>
	struct arr_union<asm_args<arg, args...>> {
		typedef typename args_add<arg, typename arr_union<asm_args<args...>>::type>::type type;
	};

	template<>
	struct arr_union<asm_args<>> {
		typedef asm_args<> type;
	};

	// arr_union2 [arg, args...] = [arr_union arg] ++ arr_union2 [args...]
	// arr_union2 [] = []
	template<typename args_t>
	struct arr_union2 {};

	template<typename arg, typename...args>
	struct arr_union2<asm_args<arg, args...>> {
		typedef typename args_add<asm_args<typename arr_union<arg>::type>, typename arr_union2<asm_args<args...>>::type>::type type;
	};

	template<>
	struct arr_union2<asm_args<>> {
		typedef asm_args<> type;
	};

	// multiple_add [x...] [y...] = [[x, y...]...]
	template<typename x/*[...]*/, typename y/*[...]*/>
	struct multiple_add {};

	template<typename...x, typename...y>
	struct multiple_add<asm_args<x...>, asm_args<y...>> {
		typedef asm_args<asm_args<x, y...>...> type;/*[[...]...]*/
	};

	// link_args a [x,y...] = args_add (multiple_add a x) (link_args a [y...])
	// link_args a [] = []
	template<typename a, typename args>
	struct link_args {};

	template<typename a, typename x, typename...y>
	struct link_args<a, asm_args<x, y...>> {
		typedef typename args_add<typename multiple_add<a, x>::type, typename link_args<a, asm_args<y...>>::type>::type type;
	};

	template<typename a>
	struct link_args<a, asm_args<>> {
		typedef asm_args<> type;
	};

	// make_args [x,y...] = link_args x (make_args [y...])
	// make_args [] = [[]]
	template<typename args>
	struct make_args {};

	template<typename x, typename...y>
	struct make_args<asm_args<x, y...>> {
		typedef typename link_args<x, typename make_args<asm_args<y...>>::type>::type type;
	};

	template<>
	struct make_args<asm_args<>> {
		typedef asm_args<asm_args<>> type;
	};

	template<size_t I, class args_t, op_t...ops>
	struct make_asm_args;

	template<size_t I, int op_v, op_t...ops>
	struct call_asm_args {};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::none, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, Args...args) {
			ator.push_c((unsigned char)op);
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::b, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, unsigned char b, Args...args) {
			ator.push_c((unsigned char)b);
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::w, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, unsigned short w, Args...args) {
			ator.push_s((unsigned short)w);
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::d, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, unsigned long d, Args...args) {
			ator.push_l((unsigned long)d);
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}

		template<typename...Args>
		static void _op(allocator &ator, size_t i, const label &l, Args...args) {
			ator.push_l((unsigned long)0);
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::r, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, register_t r, Args...args) {
			ator.push_c(0xC0 | (REG(op) << 3) | REG(r));
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::m, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, const memory &mem, Args...args) {
			ator.push_mem(mem, (register_t)REG(op));
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::m2r, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, const memory &mem, register_t reg, Args...args) {
			ator.push_mem(mem, reg);
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::r2mr, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, register_t dst, register_t src, Args...args) {
			ator.push_c(0xC0 | (REG(src) << 3) | REG(dst));
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::mr2r, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, register_t dst, register_t src, Args...args) {
			ator.push_c(0xC0 | (REG(dst) << 3) | REG(src));
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, op_t op, op_t...ops>
	struct call_asm_args<I, op_type::opr, op, ops...> {
		template<typename...Args>
		static void _op(allocator &ator, size_t i, register_t reg, Args...args) {
			ator.push_c((op & 0xF8) | REG(reg));
			make_asm_args<I, asm_args<Args...>, ops...>::_op(ator, i, args...);
		}
	};

	template<size_t I, class args_t, op_t...ops>
	struct make_asm_args {};

	template<size_t I, class...Args, op_t op, op_t...ops>
	struct make_asm_args<I, asm_args<Args...>, op, ops...> {
	private:
		const static int op_v = make_arg<op>::value;
		typedef call_asm_args<I, op_v, op, ops...> call_t;

	public:
		static void _op(allocator &ator, size_t i, Args...args) {
			call_t::_op(ator, i, args...);
		}

		static size_t op(allocator &ator, Args...args) {
			size_t count = ator.size();
			_op(ator, 0, args...);
			return ator.size() - count;
		}
	};

	template<size_t I>
	struct make_asm_args<I, asm_args<>> {
		static void _op(allocator &, size_t) {}
	};

	template<size_t I, typename T, typename...Args>
	struct args_get {
		typedef typename args_get<I - 1, Args...>::type type;
	};

	template<typename T, typename...Args>
	struct args_get<0, T, Args...> {
		typedef T type;
	};

	template<size_t I, class args_list, op_t...ops>
	struct make_multiple_asm_args {};

	template<size_t I, class arg, class...Args, op_t...ops>
	struct make_multiple_asm_args<I, asm_args<arg, Args...>, ops...>
		: make_multiple_asm_args<I - 1, asm_args<Args...>, ops...>, make_asm_args<I, arg, ops...>{

	};

	template<class arg, op_t...ops>
	struct make_multiple_asm_args<0, asm_args<arg>, ops...> : make_asm_args<0, arg, ops...>{
	};

	template<class args_list, op_t...ops>
	struct make_asm_args_list {};

	template<class...Args, op_t...ops>
	struct make_asm_args_list<asm_args<Args...>, ops...> : make_multiple_asm_args<sizeof...(Args)-1, asm_args<Args...>, ops...>{};

}

template<op_t...ops>
struct make_asm : saar::make_asm_args_list<
	typename saar::arr_union2<
	typename saar::make_args<
	typename saar::make_args_list<ops...>::type
	>::type
	>::type, ops...> {};
