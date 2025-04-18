#pragma once

#include "JsonUtils.h"
#include "MathsUtil.h"

#include "imgui.h"

#include <string>

namespace CppUtil
{
	struct Colour
	{
		int r{0};
		int g{0};
		int b{0};
		int a{255};

		constexpr Colour(int r, int g, int b, int a = 255)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{
		}

		constexpr Colour(const Colour& other)
			: r(other.r)
			, g(other.g)
			, b(other.b)
			, a(other.a)
		{
		}

		// Equality operator
		constexpr bool operator==(const Colour& other) const
		{
			return r == other.r && g == other.g && b == other.b && a == other.a;
		}

		ImVec4 ToImVec4() const;
		std::string ToHex() const;

		Colour WithAlpha(int alpha) const { return {r, g, b, alpha}; }

		static Colour FromHex(const std::string& hex);

		static constexpr Colour White() { return {255, 255, 255}; }

		static constexpr Colour Black() { return {0, 0, 0}; }

		static constexpr Colour Red() { return {255, 0, 0}; }

		static constexpr Colour Green() { return {0, 255, 0}; }

		static constexpr Colour Blue() { return {0, 0, 255}; }

		static constexpr Colour Yellow() { return {255, 255, 0}; }

		static constexpr Colour Cyan() { return {0, 255, 255}; }

		static constexpr Colour Magenta() { return {255, 0, 255}; }

		nlohmann::json ToJson() const;
		static Colour FromJson(const nlohmann::json& j);
	};
}
