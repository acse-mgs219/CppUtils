#pragma once

#include "spdlog/spdlog.h"

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
