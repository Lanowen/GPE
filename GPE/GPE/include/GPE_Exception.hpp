#pragma once

#include <exception>
#include <string>

using namespace std;

namespace gpe {

	class General_Exception : public std::exception { //salutes
	public:
		General_Exception(const char* err) : exception(err) {}

		~General_Exception() {}
	};

}
