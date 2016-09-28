#pragma once

#include "REGISTER.h"

/*
	intel 80386 (page 244)
	*/
namespace saar {
	namespace asm32 {
		struct memory {
			typedef unsigned char byte;

			struct except {
				const char *const value;

				except() : value("未知的错误") {}
				except(const char *const value) : value(value) {}
			};

			enum ptr_type : byte { BYTE = 0, WORD = 1, DWORD = 2, QWORD = 3 };

			union {
				struct {
					byte m2r : 3;
					byte reg : 3;
					byte mod : 2;
				};
				byte mod_rm;
			};
			union {
				struct {
					byte base : 3;
					byte index : 3;
					ptr_type scale : 2;
				};
				byte sib;
			};
			int offset;

			explicit memory(int offset) {
				mod_rm = 0b00'000'101;
				//mod_rm = 0b00'000'100;
				//sib = 0b00'100'101;
				this->offset = offset;
			}

			explicit memory(register_t base) {
				if ((base & 0b110) != 0b100) { // 排除[ESP]，[EBP]
					mod_rm = REG(base);
				} else if (REG(base) == 0b100) { // [ESP]
					mod_rm = 0b00'000'100; // [base+index*scale]
					sib = 0b00'100'100; // scale=1, index=NONE, base=ESP
				} else { // [EBP]
					mod_rm = 0b01'000'101; // [EBP+offset8]
					offset = 0; // offset8 = 0
				}
			}

			template<typename T>
			memory(T& val) : memory((int)&val) {}

			memory(const memory& other) {
				*this = other;
			}

			memory(register_t base, int offset) {
				set_mod_rm(offset);
				if (REG(base) == 0b100) { // [ESP+offset]
					sib = 0b00'100'100; // scale=1, index=NONE, base=ESP
				}
				this->offset = offset;
			}

			memory(register_t index, ptr_type scale, int offset) {
				if (REG(index) == 0b100) {
					throw except("[index*scale+offset]的index不能为ESP");
				}

				mod_rm = 0b00'000'100;
				sib = (scale << 6) | (REG(index) << 3) | 0b101;
				this->offset = offset;
			}


			memory(register_t base, register_t index, ptr_type scale) {
				if (REG(index) == 0b100) {
					throw except("[base+index*scale]的index不能为ESP");
				}

				if (REG(base) == 0b101) { // base = EBP
					mod_rm = 0b01'000'100; // [base+index*scale+offset8]
					offset = 0; // offset8 = 0
				} else {
					mod_rm = 0b00'000'100;
				}
				sib = (scale << 6) | (REG(index) << 3) | REG(base);
			}

			memory(register_t base, register_t index, ptr_type scale, int offset) {
				if (REG(index) == 0b100) {
					throw except("[base+index*scale+offset]的index不能为ESP");
				}

				set_mod_rm(offset);
				sib = (scale << 6) | (REG(index) << 3) | REG(base);
				this->offset = offset;
			}

			inline void set_mod_rm(int offset) {
				if (offset >= -128 && offset <= 127) {
					mod_rm = 0b01'000'100;
				} else {
					mod_rm = 0b10'000'100;
				}
			}

			inline int offset_size() const {
				byte temp = mod_rm & 0b11'000'111;
				if (temp == 0b00'000'101 || temp == 0b10'000'100 || (temp == 0b00'000'100 && base == 0b101)) {
					return 4;
				} else if (temp == 0b01'000'100) {
					return 1;
				}
				return 0;
			}

			inline bool has_sib() const {
				return mod != 0b11 && m2r == 0b100;
			}

			inline int byte_size() const {
				return 1 + (has_sib() ? 1 : 0) + offset_size();
			}
		};
	}
}