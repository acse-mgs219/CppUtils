#include "TextUtils.h"

#include <codecvt>
#include <corecrt_io.h>
#include <ctype.h>
#include <fcntl.h>
#include <iostream>
#include <locale>
#include <sstream>

namespace CppUtil
{
	char* Char32ToUtf8Char(char32_t utf32, const char* buffer)
	// Encodes the UTF-32 encoded char into a UTF-8 string.
	// Stores the result in the buffer and returns the position
	// of the end of the buffer
	// (unchecked access, be sure to provide a buffer that is big enough)
	{
#pragma warning(push)
#pragma warning(disable : 4244)
		char* end = const_cast<char*>(buffer);
		if (utf32 < 0x7F)
			*(end++) = static_cast<unsigned>(utf32);
		else if (utf32 < 0x7FF)
		{
			*(end++) = 0b1100'0000 + static_cast<unsigned>(utf32 >> 6);
			*(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
		}
		else if (utf32 < 0x10000)
		{
			*(end++) = 0b1110'0000 + static_cast<unsigned>(utf32 >> 12);
			*(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 6) & 0b0011'1111);
			*(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
		}
		else if (utf32 < 0x110000)
		{
			*(end++) = 0b1111'0000 + static_cast<unsigned>(utf32 >> 18);
			*(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 12) & 0b0011'1111);
			*(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 6) & 0b0011'1111);
			*(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
		}
		*end = '\0';
		return end;
#pragma warning(pop)
	}

	std::string Char32ToUtf8Str(const char32_t* s)
	{
		std::stringstream ss{};

		const char buffer[5]{0};
		while (s && *s)
		{
			Char32ToUtf8Char(*(s++), buffer);
			ss << buffer;
		}
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& os, const char32_t* s)
	{
		const char buffer[5]{0}; // That's the famous "big-enough buffer"
		while (s && *s)
		{
			Char32ToUtf8Char(*(s++), buffer);
			os << buffer;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const std::u32string& s)
	{
		return (os << s.c_str());
	}
}
