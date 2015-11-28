#pragma once

namespace saar {
	namespace asm64 {
		namespace type {
			class byte {
			private:
				unsigned char value;

			public:
				byte() : value(0) {}
				byte(unsigned char value) : value(value) {}
				byte(char value) : value((unsigned char)value) {}
				byte(int value) : value((unsigned char)value) {}

				operator unsigned char() const { return value; }
				operator char() const { return (char)value; }
				operator unsigned short() const { return value; }
				operator short() const { return value; }
				operator unsigned long() const { return value; }
				operator long() const { return value; }
				operator unsigned int() const { return value; }
				operator int() const { return value; }
				operator unsigned long long() const { return value; }
				operator long long() const { return value; }
			};

			class word {
			private:
				unsigned short value;

			public:
				word() : value(0) {}
				word(unsigned char value) : value(value) {}
				word(char value) : value(value) {}
				word(unsigned short value) : value(value) {}
				word(short value) : value((unsigned short)value) {}
				word(int value) : value((unsigned short)value) {}

				explicit operator unsigned char() const { return (unsigned char)value; }
				explicit operator char() const { return (char)value; }
				operator unsigned short() const { return value; }
				operator short() const { return (short)value; }
				operator unsigned long() const { return value; }
				operator long() const { return value; }
				operator unsigned int() const { return value; }
				operator int() const { return value; }
				operator unsigned long long() const { return value; }
				operator long long() const { return value; }
			};

			class dword {
			private:
				unsigned long value;

			public:
				dword() : value(0) {}
				dword(unsigned char value) : value(value) {}
				dword(char value) : value(value) {}
				dword(unsigned short value) : value(value) {}
				dword(short value) : value(value) {}
				dword(unsigned long value) : value(value) {}
				dword(long value) : value((unsigned long)value) {}
				dword(unsigned int value) : value(value) {}
				dword(int value) : value((unsigned long)value) {}

				explicit operator unsigned char() const { return (unsigned char)value; }
				explicit operator char() const { return (char)value; }
				explicit operator unsigned short() const { return (unsigned short)value; }
				explicit operator short() const { return (short)value; }
				operator unsigned long() const { return value; }
				operator long() const { return (long)value; }
				operator unsigned int() const { return value; }
				operator int() const { return (int)value; }
				operator unsigned long long() const { return value; }
				operator long long() const { return value; }
			};

			class qword {
			private:
				unsigned long long value;

			public:
				qword() : value(0) {}
				qword(unsigned char value) : value(value) {}
				qword(char value) : value(value) {}
				qword(unsigned short value) : value(value) {}
				qword(short value) : value(value) {}
				qword(unsigned long value) : value(value) {}
				qword(long value) : value(value) {}
				qword(unsigned int value) : value(value) {}
				qword(int value) : value(value) {}
				qword(unsigned long long value) : value(value) {}
				qword(long long value) : value((unsigned long long)value) {}
				qword(void *value) : value((unsigned long long)value) {}

				explicit operator unsigned char() const { return (unsigned char)value; }
				explicit operator char() const { return (char)value; }
				explicit operator unsigned short() const { return (unsigned short)value; }
				explicit operator short() const { return (short)value; }
				explicit operator unsigned long() const { return (unsigned long)value; }
				explicit operator long() const { return (long)value; }
				explicit operator unsigned int() const { return (unsigned int)value; }
				explicit operator int() const { return (int)value; }
				operator unsigned long long() const { return value; }
				operator long long() const { return (long long)value; }

				template<typename T>
				operator T*() const { return (T*)value; }
			};
		}
	}
}