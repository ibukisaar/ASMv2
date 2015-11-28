#pragma once
namespace saar {
	namespace asm64 {

#ifndef REG_X64
#define REG_X64 (1 << 16)
#endif

#ifndef REG_8BITS
#define REG_8BITS (0 << 17)
#endif

#ifndef REG_16BITS
#define REG_16BITS (1 << 17)
#endif

#ifndef REG_32BITS
#define REG_32BITS (2 << 17)
#endif

#ifndef REG_64BITS
#define REG_64BITS (3 << 17)
#endif

#ifndef REG_SIZE_MASK
#define REG_SIZE_MASK (0b11 << 17)
#endif

#ifndef MODE_16
#define MODE_16 (1 << 18)
#endif

#ifndef MODE_32
#define MODE_32 (1 << 19)
#endif

#ifndef MODE_64
#define MODE_64 (1 << 20)
#endif

#ifndef MODE_16_32
#define MODE_16_32 (MODE_16 | MODE_32)
#endif

#ifndef MODE_ALL
#define MODE_ALL (MODE_16 | MODE_32 | MODE_64)
#endif

#ifndef MODE_MASK
#define MODE_MASK (MODE_16 | MODE_32 | MODE_64)
#endif

		// bit[0~15]: 寄存器编号，其中bit[0~2]为CPU指令中的寄存器编号，bit[3]为扩展位
		// bit[16]: 是否64位模式下的寄存器
		// bit[17~18]: 寄存器大小，00: 8 bits，01: 16 bits，10: 32 bits，11: 64 bits
		enum register_t : int {
			NONE = -1,

			// 32位模式，w = 0
			AL = MODE_ALL | REG_8BITS, CL, DL, BL, AH = 4 | MODE_16_32 | REG_8BITS, CH, DH, BH,
			// 16位模式
			AX = 8 | MODE_ALL | REG_16BITS, CX, DX, BX, SP, BP, SI, DI,
			// 32位模式，w = 1
			EAX = 16 | MODE_ALL | REG_32BITS, ECX, EDX, EBX, ESP, EBP, ESI, EDI,
			// 64位模式，w = 0
			/*AL, CL, DL, BL,*/ SPL = 0x20 + 4 | MODE_64 | REG_X64 | REG_8BITS, BPL, SIL, DIL, R8B, R9B, R10B, R11B, R12B, R13B, R14B, R15B,
			R8L = R8B, R9L, R10L, R11L, R12L, R13L, R14L, R15L,
			// 64位模式下的16位模式
			/*AX, CX, DX, BX, SP, BP, SI, DI,*/ R8W = 0x30 + 8 | MODE_64 | REG_X64 | REG_16BITS, R9W, R10W, R11W, R12W, R13W, R14W, R15W,
			// 64位模式
			/*EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI,*/ R8D = 0x40 + 8 | MODE_64 | REG_X64 | REG_32BITS, R9D, R10D, R11D, R12D, R13D, R14D, R15D,
			// 64位模式
			RAX = 0x50 | MODE_64 | REG_X64 | REG_64BITS, RCX, RDX, RBX, RSP, RBP, RSI, RDI, R8, R9, R10, R11, R12, R13, R14, R15,
			// 段寄存器
			ES = 0x60, CS, SS, DS, FS, GS, /*Reserved*/ /*Reserved*/
			// 控制寄存器
			CR0 = 0x68, /*Reserved*/ CR2 = CR0 + 2, CR3, CR4, /*Reserved*/ /*Reserved*/ /*Reserved*/
			// 调试寄存器
			DR0 = 0x70, DR1, DR2, DR3, /*Reserved*/ /*Reserved*/ DR6 = DR3 + 3, DR7,
			// 任务寄存器
			/*Reserved*/ /*Reserved*/ /*Reserved*/ /*Reserved*/ /*Reserved*/ /*Reserved*/ TR6 = 0x78 + 6, TR7,
			// 浮点寄存器
			ST0 = 0x80, ST1, ST2, ST3, ST4, ST5, ST6, ST7, ST8
		};

		//

#ifndef REG
// 取得寄存器的编号
#define REG(R) ((R) & 7U)
#endif

#ifndef REGX
#define REGX(R) ((R) & 15U)
#endif

#ifndef REX
#define REX(R) ((R) & REG_X64)
#endif

#ifndef REG_EX
#define REG_EX(R) ((R) & 8U)
#endif

#ifndef REG_SIZE
#define REG_SIZE(R) ((R) & REG_SIZE_MASK)
#endif

#ifndef REG_IS_X64
#define REG_IS_X64(R) (REG_SIZE(R) == REG_64BITS)
#endif

#ifndef REG_MODE
#define REG_MODE(R) ((R) & MODE_MASK)
#endif

#ifndef REG_MODE_CMP
#define REG_MODE_CMP(R1,R2) (((R1) & (R2) & MODE_MASK) != 0)
#endif

#ifndef REG_IS_ADDR
#define REG_IS_ADDR(R) (((R) & (1 << 18)) != 0)
#endif
	}
}