#include "MathsUtil.h"

#include "LogUtils.h"

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

	void to_json(nlohmann::json& j, const Vector2i& vector2i)
	{
		j = nlohmann::json::array();
		j.push_back(vector2i.x);
		j.push_back(vector2i.y);
	}

	void from_json(const nlohmann::json& j, Vector2i& vector2i)
	{
		if (j.is_array() && j.size() == 2)
		{
			vector2i = Vector2i{j[0].get<int>(), j[1].get<int>()};
		}

		LOG_CRITICAL("Invalid Vector2i JSON format");
		vector2i = Vector2i{};
	}
}
