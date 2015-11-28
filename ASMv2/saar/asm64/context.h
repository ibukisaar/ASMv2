#pragma once

#include "buffer.h"
#include "MEMORY.h"
#include <malloc.h>

namespace saar {
	namespace asm64 {
		class context {
		public:
			struct except {
				const char *const value;

				except() : value("未知的错误") {}
				except(const char *const value) : value(value) {}
			};

		private:
			typedef unsigned char byte;

			enum opcode_t : byte { NONE, MEMORY };

			union {
				struct {
					byte operand_size_prefixes : 1;
					byte address_size_prefixes : 1;
					opcode_t opcode_type : 1;
					byte data_size : 4;
				};
				byte flags;
			};

			buffer _buf;
			byte lock_repeat_prefixes;
			byte segment_override_prefixes;
			byte rex_prefixes;
			buffer opcode_buf; // opcode or bytes
			memory mem;
			long long data;

		public:
			context() : mem(0) {}

			inline byte *buf() {
				return _buf.buf();
			}

			inline size_t buf_size() {
				return _buf.size();
			}

			inline void reset_status() {
				lock_repeat_prefixes = 0;
				segment_override_prefixes = 0;
				flags = 0;
				rex_prefixes = 0;
				opcode_buf.clear();
			}

			inline void set_lock_repeat_prefixes(byte value) {
				lock_repeat_prefixes = value;
			}

			inline void set_segment_override_prefixes(byte value) {
				segment_override_prefixes = value;
			}

			inline void set_operand_size_prefixes() {
				operand_size_prefixes = 1;
			}

			inline void set_address_size_prefixes() {
				address_size_prefixes = 1;
			}

			inline void set_rex_prefixes(byte flags) {
				rex_prefixes = 0b0100'0000 | (flags & 0b1111);
			}

			inline void push_opcode(byte opcode) {
				opcode_buf.push_c(opcode);
			}

			inline bool has_rex_prefixes() {
				return (rex_prefixes & 0b1111'0000) == 0b0100'0000;
			}

			void push_opcode_reg(byte opcode, register_t reg) {
				opcode_buf.push_c(opcode | REG(reg));
				if (has_rex_prefixes() && REG_EX(reg)) {
					set_rex_b();
				}
			}

			void set_mem_reg(const memory &mem, register_t reg) {
				this->mem = mem;
				this->mem.set_reg(reg);
				opcode_type = MEMORY;
			}

			void set_reg_reg(register_t reg, register_t mreg) {
				if (!REG_MODE_CMP(reg, mreg)) {
					throw except("两个寄存器模式不匹配");
				}

				mem.rex_rxb = 0;
				mem.mod_rm = 0b11'000'000 | (REG(reg) << 3) | REG(mreg);
				if (REX(reg) || REX(mreg)) mem.set_rex();
				if (REG_EX(reg)) mem.set_rex_r();
				if (REG_EX(mreg)) mem.set_rex_b();
				opcode_type = MEMORY;
			}

			void set_reg_opcode(size_t op, register_t mreg) {
				mem.rex_rxb = 0;
				mem.mod_rm = 0b11'000'000 | (REG(op) << 3) | REG(mreg);
				if (has_rex_prefixes() || (REX(mreg) && REG_SIZE(mreg) == REG_8BITS)) {
					mem.set_rex();
					if (REG_IS_X64(mreg)) mem.set_rex_w();
					if (REG_EX(mreg)) mem.set_rex_b();
				}
				opcode_type = MEMORY;
			}

			void push_data_b(char data) {
				*((char *)&this->data + data_size) = data;
				data_size += 1;
			}

			void push_data_w(short data) {
				*((short *)&this->data + data_size) = data;
				data_size += 2;
			}

			void push_data_l(long data) {
				*((long *)&this->data + data_size) = data;
				data_size += 4;
			}

			void push_data_q(long long data) {
				*((long long *)&this->data + data_size) = data;
				data_size += 8;
			}

			void flush() {
				if (lock_repeat_prefixes) {
					_buf.push_c(lock_repeat_prefixes);
				}

				if (segment_override_prefixes) {
					_buf.push_c(segment_override_prefixes);
				}

				if (operand_size_prefixes) {
					_buf.push_c(0x66);
				}

				if (address_size_prefixes) {
					_buf.push_c(0x67);
				}

				if (opcode_type == MEMORY) {
					if (mem.has_rex()) {
						rex_prefixes |= 0b0100'0000 | (mem.rex_rxb & 0b1111);
						_buf.push_c(rex_prefixes);
					}
				} else if (has_rex_prefixes()) {
					_buf.push_c(rex_prefixes);
				}

				_buf.push_buf(opcode_buf.buf(), opcode_buf.size());

				if (opcode_type == MEMORY) {
					_buf.push_c(mem.mod_rm);
					if (mem.has_sib()) _buf.push_c(mem.sib);

					switch (mem.offset_size()) {
					case 4: _buf.push_l(mem.offset); break;
					case 1: _buf.push_c(mem.offset); break;
					}
				}

				if (data_size > 0) {
					_buf.push_ll(data, data_size);
				}
			}

			inline void set_rex_r() {
				rex_prefixes |= 0b0100'0100;
			}

			inline void set_rex_x() {
				rex_prefixes |= 0b0100'0010;
			}

			inline void set_rex_b() {
				rex_prefixes |= 0b0100'0001;
			}
		};
	}
}