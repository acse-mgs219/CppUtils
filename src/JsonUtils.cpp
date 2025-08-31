#include "JsonUtils.h"

#include "LogUtils.h"

#include <fstream>

namespace CppUtil
{
	bool LoadFileIntoJson(const std::string& filePath, nlohmann::json& j) 
	{
		if (filePath.empty())
		{
			return false;
		}

		std::ifstream file(filePath);
		if (!file.is_open())
		{
			LOG_CRITICAL("Failed to open file at path: {}", filePath);
			return false;
		}

		file >> j;

		return !j.empty();
	}
}