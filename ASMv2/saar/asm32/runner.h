#pragma once

#include "context.h"
#include <Windows.h>

#pragma warning(disable: 4229)

namespace saar {
	namespace asm32 {

		struct runner {
			static void call(context &ctx) {
				DWORD old;
				if (0 != VirtualProtect(ctx.buf(), ctx.size(), PAGE_EXECUTE_READWRITE, &old)) {
					void *p = ctx.buf();
					((void(*__stdcall)())p)();
					VirtualProtect(ctx.buf(), ctx.size(), old, nullptr);
				}
			}
		};

	}
}