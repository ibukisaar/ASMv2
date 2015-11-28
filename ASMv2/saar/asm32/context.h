#pragma once

#include "MEMORY.h"
#include <malloc.h>

namespace saar {
	namespace asm32 {
		class context {
		private:
			char *_buf;
			size_t _base_size;
			size_t _size;

			void resize(size_t alloc_size) {
				size_t x = _size + alloc_size;
				if (x > _base_size) {
					size_t y = _base_size * 2;
					_base_size = x > y ? x : y;
					_buf = (char *)realloc(_buf, _base_size);
				}
			}

		public:
			context() : context(2048) {}
			context(size_t _base_size) : _buf((char *)malloc(_base_size)), _base_size(_base_size), _size(0) {}

			~context() {
				free(_buf);
			}

			char *const buf() const { return _buf; }
			const size_t size() const { return _size; }

			char *alloc(size_t size) {
				char *buf = _buf + _size;
				resize(size);
				_size += size;
				return buf;
			}

			void push_ll(unsigned long long data) {
				resize(sizeof data);
				*(unsigned long long *)(_buf + _size) = data;
				_size += sizeof data;
			}

			void push_l(unsigned long data) {
				resize(sizeof data);
				*(unsigned long *)(_buf + _size) = data;
				_size += sizeof data;
			}

			void push_s(unsigned short data) {
				resize(sizeof data);
				*(unsigned short *)(_buf + _size) = data;
				_size += sizeof data;
			}

			void push_c(unsigned char data) {
				resize(sizeof data);
				*(unsigned char *)(_buf + _size) = data;
				_size += sizeof data;
			}

			void push_mem(const memory &mem, register_t reg) {
				push_c(mem.mod_rm | (REG(reg) << 3));
				if (mem.has_sib()) push_c(mem.sib);

				switch (mem.offset_size()) {
				case 4: push_l(mem.offset); break;
				case 1: push_c(mem.offset); break;
				case 2: push_s(mem.offset); break;
				}
			}
		};
	}
}