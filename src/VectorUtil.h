#pragma once

#include <vector>

namespace CppUtil
{
	template <typename T, typename... Vectors>
	std::vector<T> CollapseVectors(const std::vector<T>& first, const Vectors&... rest)
	{
		std::vector<T> result;

		result.reserve((first.size() + ... + rest.size()));

		result.insert(result.end(), first.begin(), first.end());
		(..., result.insert(result.end(), rest.begin(), rest.end()));

		return result;
	}
} // namespace CppUtil
