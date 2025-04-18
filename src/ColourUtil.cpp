#include "ColourUtil.h"

#include "LogUtils.h"

namespace CppUtil
{
	Colour CppUtil::Colour::FromHex(const std::string& hex)
	{
		if (hex.size() != 7 || hex[0] != '#')
		{
			return Colour::Black();
		}

		const int r = std::stoi(hex.substr(1, 2), nullptr, 16);
		const int g = std::stoi(hex.substr(3, 2), nullptr, 16);
		const int b = std::stoi(hex.substr(5, 2), nullptr, 16);

		return {r, g, b};
	}

	ImVec4 Colour::ToImVec4() const
	{
		return ImVec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
	}

	std::string Colour::ToHex() const
	{
		char hex[10];
		sprintf_s(hex, "#%02X%02X%02X", r, g, b);
		return std::string(hex);
	}

	nlohmann::json Colour::ToJson() const
	{
		auto j = nlohmann::json::array();
		j.push_back(r);
		j.push_back(g);
		j.push_back(b);
		j.push_back(a);
		return j;
	}

	Colour Colour::FromJson(const nlohmann::json& j)
	{
		if (j.is_array() && j.size() == 4)
		{
			return Colour(j[0].get<int>(), j[1].get<int>(), j[2].get<int>(), j[3].get<int>());
		}

		if (j.is_string())
		{
			return FromHex(j.get<std::string>());
		}

		LOG_CRITICAL("Invalid Colour JSON format");
		return Colour::Black();
	}
}
