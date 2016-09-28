#pragma once

#include "REGISTER.h"

/*
	intel 80386 (page 244)
	*/
namespace saar {
	namespace asm64 {
		// REX: 0100WRXB
		// ------------------------------------------------------------------------
		//      ModRM                                        SIB
		// mod  reg/op  r/m                scale      index              base
		// =00   Rrrr  Bbbb[bbb≠100,101]                                             ->  [Bbbb]
		// ≠11   Rrrr  Bbbb[bbb≠100]                                                 ->  [Bbbb]
		// =11   Rrrr  Bbbb                                                          ->  Bbbb
		// =00   Rrrr   100                 ss    Xxxx[0100:none]   Bbbb[0101:none]  ->  [Bbbb+Xxxx*ss], if Bbbb=0101 then [Xxxx*ss+offset32]
		// ≠11   Rrrr   100                 ss    Xxxx[0100:none]   Bbbb             ->  [Bbbb+Xxxx*ss+offset8/32]
		// ------------------------------------------------------------------------
		// opcode|reg
		// ttttt |Bbbb

		//
		struct memory {
			typedef unsigned char byte;

			struct except {
				const char *const value;

				except() : value("未知的错误") {}
				except(const char *const value) : value(value) {}
			};

			enum ptr_type : byte { BYTE = 0, WORD = 1, DWORD = 2, QWORD = 3 };

			byte rex_rxb;
			union {
				struct {
					byte mod : 2;
					byte reg : 3;
					byte m2r : 3;
				};
				byte mod_rm;
			};
			union {
				struct {
					ptr_type scale : 2;
					byte index : 3;
					byte base : 3;
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
				if (!REG_IS_ADDR(base)) {
					throw except("base必须是32位或64位");
				}

				if ((base & 0b110) != 0b100) { // 排除[ESP],[EBP],[RSP],[RBP],[R12],[R13]
					mod_rm = REG(base);
				} else if (REGX(base) == REG(ESP)) { // [ESP],[RSP],[R12]
					mod_rm = 0b00'000'100; // [base+index*scale]
					sib = 0b00'100'100; // scale=1, index=NONE, base=ESP
				} else { // [EBP],[RBP],[R13]
					mod_rm = 0b01'000'101; // [EBP+offset8]
					offset = 0; // offset8 = 0
				}

				if (REX(base)) {
					set_rex();
					if (REG_EX(base)) {
						set_rex_b();
					}
				}
			}

			memory(register_t base, int offset) {
				if (!REG_IS_ADDR(base)) {
					throw except("[base+offset]的base必须是32位或64位");
				}

				set_mod_rm(offset);
				if (REG(base) == REG(ESP)) {
					sib = 0b00'100'100; // scale=1, index=NONE, base=ESP
				}
				this->offset = offset;

				if (REX(base)) {
					set_rex();
					if (REG_EX(base)) {
						set_rex_b();
					}
				}
			}

			memory(register_t index, ptr_type scale, int offset) {
				if (!REG_IS_ADDR(index)) {
					throw except("[index*scale+offset]的index必须是32位或64位");
				}
				if (REG(index) == REG(EBP)) {
					throw except("[index*scale+offset]的index不能为ESP");
				}

				mod_rm = 0b00'000'100;
				sib = (scale << 6) | (REG(index) << 3) | 0b101;
				this->offset = offset;

				if (REX(index)) {
					set_rex();
					if (REG_EX(index)) {
						set_rex_x();
					}
				}
			}

			memory(register_t base, register_t index, ptr_type scale) {
				if (!REG_IS_ADDR(base) || !REG_IS_ADDR(index)) {
					throw except("[base+index*scale]的base与index必须是32位或64位");
				}
				if (REG_SIZE(base) != REG_SIZE(index)) {
					throw except("[base+index*scale]的base与index大小不一致");
				}
				if (REG(index) == REG(ESP)) {
					throw except("[base+index*scale]的index不能为ESP");
				}

				if (REGX(base) == REG(EBP)) { // base = EBP,RBP,R13
					mod_rm = 0b01'000'100; // [base+index*scale+offset8]
					offset = 0; // offset8 = 0
				} else {
					mod_rm = 0b00'000'100;
				}
				sib = (scale << 6) | (REG(index) << 3) | REG(base);
				if (REX(base)) {
					set_rex();
					if (REG_EX(base)) {
						set_rex_b();
					}
					if (REG_EX(index)) {
						set_rex_x();
					}
				}
			}

			memory(register_t base, register_t index, ptr_type scale, int offset) {
				if (!REG_IS_ADDR(base) || !REG_IS_ADDR(index)) {
					throw except("[base+index*scale+offset]的base与index必须是32位或64位");
				}
				if (REG_SIZE(base) != REG_SIZE(index)) {
					throw except("[base+index*scale+offset]的base与index大小不一致");
				}
				if (REG(index) == REG(ESP)) {
					throw except("[base+index*scale+offset]的index不能为ESP");
				}

				set_mod_rm(offset);
				sib = (scale << 6) | (REG(index) << 3) | REG(base);
				this->offset = offset;
				if (REX(base)) {
					set_rex();
					if (REG_EX(base)) {
						set_rex_b();
					}
					if (REG_EX(index)) {
						set_rex_x();
					}
				}
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
				return (has_sib() ? 2 : 1) + offset_size();
			}

			inline void set_rex() {
				rex_rxb |= 0b0100'0000;
			}

			inline void set_rex_w() {
				rex_rxb |= 0b0100'1000;
			}

			inline void set_rex_r() {
				rex_rxb |= 0b0100'0100;
			}

			inline void set_rex_x() {
				rex_rxb |= 0b0100'0010;
			}

			inline void set_rex_b() {
				rex_rxb |= 0b0100'0001;
			}

			inline bool has_rex() const {
				return (rex_rxb & 0b0100'0000) != 0;
			}

			inline bool rex_w() const {
				return (rex_rxb & 0b1000) != 0;
			}

			inline bool rex_r() const {
				return (rex_rxb & 0b0100) != 0;
			}

			inline bool rex_x() const {
				return (rex_rxb & 0b0010) != 0;
			}

			inline bool rex_b() const {
				return (rex_rxb & 0b0001) != 0;
			}

			inline void set_reg(register_t reg) {
				this->reg = reg;
				if (REX(reg)) set_rex();
				if (REG_EX(reg)) set_rex_r();
			}
		};
	}
}