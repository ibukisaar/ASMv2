#include <stdio.h>

#ifndef _WIN64
#include "saar\asm32\asm.h"
#include "saar\asm32\runner.h"

using namespace saar::asm32;
using namespace saar::asm32::instruction;
#else
#include "saar\asm64\asm.h"
#include "saar\asm64\runner.h"

using namespace saar::asm64;
using namespace saar::asm64::instruction;
#endif

int main() {
#ifndef _WIN64
	context ctx;

	int a = 123;
	lea_r_m32::op(ctx, EAX, a);
	push_m32::op(ctx, memory(EAX));
	push_i32::op(ctx, "%d\n");
	mov_r_i32::op(ctx, EAX, printf);
	call_r::op(ctx, EAX);
	add_r_i32::op(ctx, ESP, 8);
	ret::op(ctx);

	runner::call(ctx);
#endif
	return 0;
}