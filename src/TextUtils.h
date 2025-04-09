#pragma once

#include <string>

namespace CppUtil
{
	// #TODO_LIB: I don't think this works properly
	char* Char32ToUtf8Char(char32_t utf32, const char* buffer);
	std::string Char32ToUtf8Str(const char32_t* s);
	std::ostream& operator<<(std::ostream& os, const char32_t* s);
	std::ostream& operator<<(std::ostream& os, const std::u32string& s);
};
