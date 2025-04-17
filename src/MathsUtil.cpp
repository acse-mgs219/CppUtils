#include "MathsUtil.h"

namespace CppUtil
{
	constexpr bool Equal(float a, float b, float precision)
	{
		if (a > b)
		{
			return a - b < precision;
		}

		return b - a < precision;
	}

	constexpr float Rad2Deg(float rad)
	{
		return rad * 180.f / M_PI_F;
	}

	constexpr float Deg2Rad(float deg)
	{
		return deg / 180.f * M_PI_F;
	}

	constexpr int UniqueID(int x, int y)
	{
		// Cantor pairing function NxN->N, given by: F(a,b)=12(a+b)(a+b+1)+b.
		// Note: NOT commutative so F(a,b) != F(b,a)
		const auto mult = static_cast<float>((x + y) * (x + y + 1));
		const auto div = static_cast<int>(mult / 2.f) + y;
		return div;
	}
}
