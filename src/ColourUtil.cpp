#include "ColourUtil.h"

namespace CppUtil
{
	Colour CppUtil::Colour::FromHex(const std::string& hex)
	{
		if (hex.size() != 7 || hex[0] != '#')
		{
			return Colour::Black();
		}

		int r = std::stoi(hex.substr(1, 2), nullptr, 16);
		int g = std::stoi(hex.substr(3, 2), nullptr, 16);
		int b = std::stoi(hex.substr(5, 2), nullptr, 16);

		return Colour(r / 255.f, g / 255.f, b / 255.f);
	}
}
