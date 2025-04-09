#pragma once

#include "spdlog/spdlog.h"

namespace CppUtil
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
#define LOG_TRACE(...) ::CppUtil::GetMinimalistLogger().trace(__VA_ARGS__)
#define LOG_INFO(...) ::CppUtil::GetMinimalistLogger().info(__VA_ARGS__)
#define LOG_DEBUG(...) ::CppUtil::GetMinimalistLogger().debug(__VA_ARGS__)
#define LOG_WARNING(...) ::CppUtil::GetMinimalistLogger().warn(__VA_ARGS__)
#define LOG_CRITICAL(...) ::CppUtil::GetMinimalistLogger().error(__VA_ARGS__)

#define RECORD_TRACE(...) ::CppUtil::GetFileLogger().trace(__VA_ARGS__)
#define RECORD_INFO(...) ::CppUtil::GetFileLogger().info(__VA_ARGS__)
#define RECORD_DEBUG(...) ::CppUtil::GetFileLogger().debug(__VA_ARGS__)
#define RECORD_WARNING(...) ::CppUtil::GetFileLogger().warn(__VA_ARGS__)
#define RECORD_CRITICAL(...) ::CppUtil::GetFileLogger().error(__VA_ARGS__)

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
