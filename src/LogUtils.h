#pragma once

#include "spdlog/spdlog.h"

#include <string>
#include <type_traits>

namespace Util
{
	// #TODO_LIB: Not used, could be used to set the log level
	enum class Severity
	{
		TRACE,
		INFO,
		DEBUG,
		WARNING,
		CRITICAL
	};

	spdlog::logger& GetDefaultLogger();
	spdlog::logger& GetMinimalistLogger();
	spdlog::logger& GetFileLogger();
};

#ifndef NDEBUG
#define LOG_TRACE(...) ::Util::GetMinimalistLogger().trace(__VA_ARGS__)
#define LOG_INFO(...) ::Util::GetMinimalistLogger().info(__VA_ARGS__)
#define LOG_DEBUG(...) ::Util::GetMinimalistLogger().debug(__VA_ARGS__)
#define LOG_WARNING(...) ::Util::GetMinimalistLogger().warn(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Util::GetMinimalistLogger().error(__VA_ARGS__)

#define RECORD_TRACE(...) ::Util::GetFileLogger().trace(__VA_ARGS__)
#define RECORD_INFO(...) ::Util::GetFileLogger().info(__VA_ARGS__)
#define RECORD_DEBUG(...) ::Util::GetFileLogger().debug(__VA_ARGS__)
#define RECORD_WARNING(...) ::Util::GetFileLogger().warn(__VA_ARGS__)
#define RECORD_CRITICAL(...) ::Util::GetFileLogger().error(__VA_ARGS__)

#define LOG(severity, ...) LOG_##severity(__VA_ARGS__)

#define ASSERT(condition, ...)     \
	if (!(condition))              \
	{                              \
		LOG_CRITICAL(__VA_ARGS__); \
		__debugbreak();            \
	}
#define EXPECT(condition, ...)    \
	if (!(condition))             \
	{                             \
		LOG_WARNING(__VA_ARGS__); \
	}

#else

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_DEBUG(...)
#define LOG_WARNING(...)
#define LOG_CRITICAL(...)

#define LOG(severity, ...)

#define ASSERT(condition, ...)
#define EXPECT(condition, ...)

#endif

namespace Util
{
	template <typename T>
	std::string get_type_name()
	{
#if defined(_MSC_VER)
		const std::string func_sig = __FUNCSIG__;
		const std::string prefix = "std::string __cdecl get_type_name<";
		const std::string suffix = ">(void)";
#elif defined(__clang__) || defined(__GNUC__)
		const std::string func_sig = __PRETTY_FUNCTION__;
		const std::string prefix = "std::string get_type_name() [with T = ";
		const std::string suffix = "]";
#else
		return "Unsupported compiler";
#endif

		auto start = func_sig.find(prefix) + prefix.size();
		auto end = func_sig.rfind(suffix);

		return func_sig.substr(start, end - start);
	}
}
