#pragma once
namespace saar {
	namespace asm32 {
		// ��һЩָ���ʽ���£�
		// xxxxxxxw ...
		// x��ʾָ����룬w��ʾ������С
		// ��32λģʽ�£�w=0��ʾ������С8 bits��w=1��ʾ������С32 bits
		// ��16λģʽ�£�w=0��ʾ������С8 bits��w=1��ʾ������С16 bits
		// ��Ϊ16λģʽ��0x66ǰ׺�����ֱ����32λģʽ�²�����СΪ8 bits�����ݿ��Լ�Сָ���
		enum register_t : int {
			NONE = -1,
			// 32λģʽ��w = 0
			AL, CL, DL, BL,
			AH, CH, DH, BH,
			// 16λģʽ
			AX, CX, DX, BX,
			SP, BP, SI, DI,
			// 32λģʽ��w = 1
			EAX, ECX, EDX, EBX,
			ESP, EBP, ESI, EDI,
			// �μĴ���
			ES, CS, SS, DS,
			FS, GS, /*Reserved*/ /*Reserved*/
								 // ���ƼĴ���
			CR0 = GS + 3, /*Reserved*/ CR2 = CR0 + 2, CR3,
			CR4, /*Reserved*/ /*Reserved*/ /*Reserved*/
										   // ���ԼĴ���
			DR0 = CR4 + 4, DR1, DR2, DR3,
			/*Reserved*/ /*Reserved*/ DR6 = DR3 + 3, DR7,
			// ����Ĵ���
			/*Reserved*/ /*Reserved*/ /*Reserved*/ /*Reserved*/
			/*Reserved*/ /*Reserved*/ TR6 = DR7 + 7, TR7,
		};

		//

#ifndef REG
// ȡ�üĴ����ı�ţ���CPUָ���еļĴ�����ռλ��ֻ��3 bits�������ֻ��0~7
#define REG(R) ((R) & 7U)
#endif

	}
}