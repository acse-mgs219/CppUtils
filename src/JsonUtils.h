#pragma once

#include <concepts>

#include <nlohmann/json.hpp>

namespace CppUtil
{
	template <typename T>
	concept JsonSerializable = requires(const T& obj, const nlohmann::json& j) {
		{
			T::FromJson(j)
		} -> std::same_as<T>;
		{
			obj.ToJson()
		} -> std::same_as<nlohmann::json>;
	};
}
