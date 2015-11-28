#pragma once
namespace saar {
	namespace asm32 {
		// 有一些指令格式如下：
		// xxxxxxxw ...
		// x表示指令代码，w表示操作大小
		// 在32位模式下，w=0表示操作大小8 bits，w=1表示操作大小32 bits
		// 在16位模式下，w=0表示操作大小8 bits，w=1表示操作大小16 bits
		// 因为16位模式有0x66前缀，因此直接在32位模式下操作大小为8 bits的数据可以减小指令长度
		enum register_t : int {
			NONE = -1,
			// 32位模式，w = 0
			AL, CL, DL, BL,
			AH, CH, DH, BH,
			// 16位模式
			AX, CX, DX, BX,
			SP, BP, SI, DI,
			// 32位模式，w = 1
			EAX, ECX, EDX, EBX,
			ESP, EBP, ESI, EDI,
			// 段寄存器
			ES, CS, SS, DS,
			FS, GS, /*Reserved*/ /*Reserved*/
								 // 控制寄存器
			CR0 = GS + 3, /*Reserved*/ CR2 = CR0 + 2, CR3,
			CR4, /*Reserved*/ /*Reserved*/ /*Reserved*/
										   // 调试寄存器
			DR0 = CR4 + 4, DR1, DR2, DR3,
			/*Reserved*/ /*Reserved*/ DR6 = DR3 + 3, DR7,
			// 任务寄存器
			/*Reserved*/ /*Reserved*/ /*Reserved*/ /*Reserved*/
			/*Reserved*/ /*Reserved*/ TR6 = DR7 + 7, TR7,
		};

		//

#ifndef REG
// 取得寄存器的编号，在CPU指令中的寄存器所占位数只有3 bits，即编号只有0~7
#define REG(R) ((R) & 7U)
#endif

	}
}