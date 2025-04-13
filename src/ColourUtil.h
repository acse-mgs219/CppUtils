#pragma once

#include "MathsUtil.h"

#include <string>

namespace CppUtil
{
	struct Colour
	{
		float r{0};
		float g{0};
		float b{0};
		float a{1};

		constexpr Colour(float r, float g, float b, float a = 1.0f)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{
		}

		// Equality operator
		constexpr bool operator==(const Colour& other) const
		{
			return CppUtil::Equal(r, other.r) && CppUtil::Equal(g, other.g) && CppUtil::Equal(b, other.b) &&
				CppUtil::Equal(a, other.a);
		}

		static Colour FromHex(const std::string& hex);

		Colour WithAlpha(float alpha) const { return Colour(r, g, b, alpha); }

		static constexpr Colour White() { return Colour(1.0f, 1.0f, 1.0f); }

		static constexpr Colour Black() { return Colour(0.0f, 0.0f, 0.0f); }

		static constexpr Colour Red() { return Colour(1.0f, 0.0f, 0.0f); }

		static constexpr Colour Green() { return Colour(0.0f, 1.0f, 0.0f); }

		static constexpr Colour Blue() { return Colour(0.0f, 0.0f, 1.0f); }

		static constexpr Colour Yellow() { return Colour(1.0f, 1.0f, 0.0f); }

		static constexpr Colour Cyan() { return Colour(0.0f, 1.0f, 1.0f); }

		static constexpr Colour Magenta() { return Colour(1.0f, 0.0f, 1.0f); }
	};
}
