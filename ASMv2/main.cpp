#include <stdio.h>
//#include "saar\asm32\asm.h"
//#include "saar\asm32\runner.h"
#include "saar\asm64\asm.h"
#include "saar\asm64\runner.h"
#include <iostream>
#include <memory>
#include <type_traits>

using namespace std;
// using namespace saar::asm32;
// using namespace saar::asm32::instruction;
using namespace saar::asm64;
using namespace saar::asm64::instruction;

int main() {
	
	//make_asm<0x40 | asm_t::op_reg>::op(a, EAX);
	//make_asm<0x81, asm_t::reg, asm_t::dword>::op(a, EAX, 0);
	//make_asm<0x80, asm_t::mem | 0, asm_t::byte>::op(a, memory(EAX), 0);
	//make_asm<0x01, asm_t::mreg2reg>::op(a, EAX, ECX);
	//make_asm<0xF0>::op(a);
	//saar_asm::adc_al_i8::op(a, 0);
	/*saar_asm::mov_r_r32::op(a, ECX, EAX);
	saar_asm::mov_cr_r::op(a, (register_t)cr_t::cr1, EAX);
	saar_asm::movsx_r16_r8::op(a, CX, AL);
	saar_asm::xchg_r_r8::op(a, CL, AL);
	saar_asm::cmp_r_m32::op(a, memory(0), EAX);*/

	/*lea_r_m32::op(ctx, EAX, a);
	push_m32::op(ctx, memory(EAX));
	push_i32::op(ctx, "%d\n");
	mov_r_i32::op(ctx, EAX, printf);
	call_r::op(ctx, EAX);
	add_r_i32::op(ctx, ESP, 8);
	ret::op(ctx);
	runner::call(ctx);*/
	
	
	context ctx;

	sub_r64_i32::op(ctx, RSP, 0x20);
	mov_r64_i64::op(ctx, RCX, "hello world");
	mov_r64_i64::op(ctx, RAX, puts);
	call_r64::op(ctx, RAX);
	add_r64_i32::op(ctx, RSP, 0x20);
	ret::op(ctx);

	runner::call(ctx);
	
	return 0;
}