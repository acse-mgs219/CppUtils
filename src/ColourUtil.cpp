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

	void to_json(nlohmann::json& j, const Colour& colour)
	{
		j = nlohmann::json::array();
		j.push_back(colour.r);
		j.push_back(colour.g);
		j.push_back(colour.b);
		j.push_back(colour.a);
	}

	void from_json(const nlohmann::json& j, Colour& colour)
	{
		if (j.is_array() && j.size() == 4)
		{
			colour = Colour(j[0].get<int>(), j[1].get<int>(), j[2].get<int>(), j[3].get<int>());
		}

		if (j.is_string())
		{
			colour = Colour::FromHex(j.get<std::string>());
		}

		LOG_CRITICAL("Invalid Colour JSON format");
		colour = Colour::Black();
	}
}
