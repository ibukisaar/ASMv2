#pragma once

#include <string>

namespace saar {
	namespace asm64 {
		using std::string;

		class label {
		private:
			const string _name;

		public:
			label(string name) : _name(name) {}

			inline const string & name() const { return _name; }

			inline friend const bool operator==(const label &l1, const label &l2) {
				return l1._name == l2._name;
			}
		};
	}
}

template<>
class std::hash<saar::asm64::label> {
public:
	inline const size_t operator()(const saar::asm64::label &l) {
		return std::hash<string>()(l.name());
	}
};