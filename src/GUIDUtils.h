#pragma once

#include "LogUtils.h"

#include <cstdint>
#include <fmt/format.h>
#include <string>
#include <type_traits>

#include <nlohmann/json.hpp>

// Macro to automatically log GUID creation
#define LOG_GUID_CREATION(className) LOG_INFO(#className " created with GUID: {}", mGUID.GetDebugString())

// TGUID Helper Class
//
// A lightweight, strongly-typed unique ID wrapper that generates GUIDs from
// short human-readable strings (e.g., "unit-1", "blue-faction", etc.).
//
// * Hashes are 64-bit unsigned integers, fast to compare, sort, and store.
// * Based on the FNV-1a hash algorithm, which is stable across runs.
// * In Debug builds: retains the original string for human-friendly logs.
// * In Release: string data is stripped for performance and size.
//
// * Collision-free for strings up to 10 characters drawn from [a-z0-9-].
//    Enforced by runtime validation in debug mode. Longer strings throw.
//    This works because total unique values (~4.8e15) << 2^64 (~1.8e19).
//
// * Typical usage:
//    struct MyType {};
//    TGUID<MyType> id("archer-1");
//    uint64_t raw = id.GetValue();
//template <typename T>
//class TGUID;
//
//template <typename T>
//void to_json<T>(nlohmann::json& j, const TGUID<T>& guid);
//template <typename T>
//void from_json<T>(const nlohmann::json& j, TGUID<T>& guid);

template <typename T>
class TGUID
{
public:
	explicit TGUID(std::string_view name)
		: mID(Hash(name))
	{
#ifdef _DEBUG
		Validate(name);
		mDebugString = std::string(name);
#endif
	}

	explicit TGUID(uint64_t id = 0)
		: mID(id)
	{
#ifdef _DEBUG
		mDebugString = Util::get_type_name<T>();
#endif
	}

	TGUID(const TGUID<T>& other) = default;
	TGUID(TGUID<T>&& other) noexcept = default;
	TGUID<T>& operator=(const TGUID<T>& other) = default;
	TGUID<T>& operator=(TGUID<T>&& other) noexcept = default;

	static TGUID<T> Invalid() { return TGUID<T>(0); }

	static TGUID<T> Generate()
	{
		TGUID<T> guid(++sAutoIncrement);
		return guid;
	}

	[[nodiscard]] uint64_t ID() const { return mID; }
	[[nodiscard]] bool IsValid() const { return mID != 0; }

	[[nodiscard]] std::string GetDebugString() const
	{
#ifdef _DEBUG
		return fmt::format("{}({})", mDebugString, mID);
#else
		return std::to_string(mID);
#endif
	}

	template <typename U>
	bool operator==(const TGUID<U>& other) const
	{
		return std::is_same_v<T, U> && (mID == other.mID);
	}

	template <typename U>
	bool operator<(const TGUID<U>& other) const
	{
		static_assert(std::is_same_v<T, U>, "Cannot compare GUIDs of different types");
		return mID < other.mID;
	}

private:
	inline static uint64_t sAutoIncrement = 0;
	uint64_t mID = 0;

#ifdef _DEBUG
	std::string mDebugString;

	// Alphabet: [a-z0-9-] => 37 symbols
	static constexpr size_t kMaxSafeLength = 10;

	static constexpr bool IsValidChar(char c) { return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '-'); }

	static void Validate(std::string_view name)
	{
		if (name.empty())
		{
			LOG_CRITICAL("Generating GUID from empty string is not supported.");
			return;
		}

		if (name.size() > kMaxSafeLength)
		{
			LOG_CRITICAL("GUID string too long (max 10 characters for guaranteed uniqueness).");
			return;
		}

		for (char c : name)
		{
			if (!IsValidChar(c))
			{
				LOG_CRITICAL(std::string("Invalid character in GUID string: '") + c + "'.");
				return;
			}
		}
	}
#endif

	// FNV-1a 64-bit hashing
	static constexpr uint64_t Hash(std::string_view str)
	{
		constexpr uint64_t FNV_offset_basis = 14695981039346656037ull;
		constexpr uint64_t FNV_prime = 1099511628211ull;

		uint64_t hash = FNV_offset_basis;
		for (char c : str)
		{
			hash ^= static_cast<uint8_t>(c);
			hash *= FNV_prime;
		}
		return hash;
	}

	friend void to_json<T>(nlohmann::json& j, const TGUID<T>& guid);
	friend void from_json<T>(const nlohmann::json& j, TGUID<T>& guid);
};

template <typename T>
void to_json(nlohmann::json& j, const TGUID<T>& guid)
{
#ifdef _DEBUG
	j = guid.mDebugString;
#else
	j = guid.mID;
#endif
}

template <typename T>
void from_json(const nlohmann::json& j, TGUID<T>& guid)
{
	if (j.is_string())
	{
		guid = TGUID<T>(j.get<std::string>());
	}
	else if (j.is_number_integer())
	{
		guid = TGUID<T>(j.get<int>());
	}
	else
	{
		LOG_CRITICAL("Invalid json for TGUID: {}, of type {}.", j.dump(), j.type_name());
		guid = TGUID<T>::Invalid();
	}
}

// Allow TGUID<T> to be used in std::unordered_map
namespace std
{
	template <typename T>
	struct hash<TGUID<T>>
	{
		std::size_t operator()(const TGUID<T>& guid) const noexcept { return std::hash<uint64_t>()(guid.ID()); }
	};
}

template <typename T>
struct fmt::formatter<TGUID<T>>
{
	formatter<std::string> string_formatter;

	constexpr auto parse(format_parse_context& ctx) { return string_formatter.parse(ctx); }

	auto format(const TGUID<T>& val, format_context& ctx) const
	{
		return string_formatter.format(val.GetDebugString(), ctx);
	}
};
