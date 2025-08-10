#pragma once

#include "JsonUtils.h"

#include <algorithm>
#include <corecrt_math_defines.h>
#include <functional>

namespace CppUtil
{
#define M_PI_F static_cast<float>(M_PI)

	struct Vector2i
	{
		Vector2i() = default;

		Vector2i(int x, int y)
			: x(x)
			, y(y)
		{
		}

		int x{0};
		int y{0};

		friend bool operator==(const Vector2i& lhs, const Vector2i& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

		nlohmann::json ToJson() const;

		static std::optional<Vector2i> FromJson(const nlohmann::json& j);
	};

	using Point2i = Vector2i;

	constexpr bool Equal(float a, float b, float precision = 0.00001f);
	constexpr float Rad2Deg(float rad);
	constexpr float Deg2Rad(float deg);

	template <typename T, typename... Args>
	constexpr T max(T first, Args... rest)
	{
		T result = first;
		result = std::max(result, std::max(rest...));
		return result;
	}

	constexpr int UniqueID(int x, int y);
}

namespace std
{
	template <>
	struct hash<CppUtil::Vector2i>
	{
		std::size_t operator()(const CppUtil::Vector2i& v) const noexcept
		{
			return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
		}
	};
}
