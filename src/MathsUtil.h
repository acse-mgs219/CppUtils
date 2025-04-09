#pragma once

#include <algorithm>
#include <corecrt_math_defines.h>

namespace CppUtil
{
#define M_PI_F static_cast<float>(M_PI)

	bool Equal(float a, float b, float precision = 0.00001f);
	float Rad2Deg(float rad);
	float Deg2Rad(float deg);

	template <typename T, typename... Args>
	T max(T first, Args... rest)
	{
		T result = first;
		result = std::max(result, std::max(rest...));
		return result;
	}

	int UniqueID(int x, int y);
}
