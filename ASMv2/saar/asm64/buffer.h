#pragma once

#include <malloc.h>
#include <memory.h>

namespace saar {
	namespace asm64 {
		class buffer {
		private:
			typedef unsigned char byte;

			byte *_buf;
			size_t _base_size;
			size_t _size;

			void resize(size_t alloc_size) {
				size_t x = _size + alloc_size;
				if (x > _base_size) {
					size_t y = _base_size * 2;
					_base_size = x > y ? x : y;
					_buf = (byte *)realloc(_buf, _base_size);
				}
			}

		public:
			buffer() : buffer(2048) {}
			buffer(size_t _base_size) : _buf((byte *)malloc(_base_size)), _base_size(_base_size), _size(0) {}

			~buffer() {
				free(_buf);
			}

			byte * buf() const { return _buf; }
			size_t size() const { return _size; }

			byte *alloc(size_t size) {
				byte *buf = _buf + _size;
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

			void push_buf(void *buf, size_t bytes_size) {
				resize(bytes_size);
				memcpy(_buf + _size, buf, bytes_size);
				_size += bytes_size;
			}

			void push_ll(unsigned long long data, size_t bytes_size) {
				resize(8);
				*(unsigned long long *)(_buf + _size) = data;
				_size += bytes_size;
			}

			void clear() {
				_size = 0;
			}
		};
	}
}