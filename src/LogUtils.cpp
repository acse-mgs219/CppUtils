#include "LogUtils.h"

#include <spdlog/sinks/basic_file_sink.h>

namespace Util
{
	spdlog::logger& GetDefaultLogger()
	{
		static auto console_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_st>();
		static spdlog::logger logger("default", console_sink);
		logger.set_level(spdlog::level::trace);
		return logger;
	}

	spdlog::logger& GetMinimalistLogger()
	{
		static auto console_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_st>();
		static spdlog::logger logger("minimalist", console_sink);
		logger.set_level(spdlog::level::trace);
		logger.set_pattern("%v");
		return logger;
	}

	spdlog::logger& GetFileLogger()
	{
		static auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("traycer.log", true);
		static spdlog::logger logger("file", file_sink);
		logger.set_level(spdlog::level::trace);
		return logger;
	}
}
