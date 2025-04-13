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

	template <class T>
	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;

		virtual nlohmann::json ToJson() const = 0;

		static T FromJson(const nlohmann::json& j) { return T::FromJson(j); }
	};
}
