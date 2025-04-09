#pragma once

#include <string>

namespace std::filesystem
{
	class path;
}

namespace CppUtil
{
	const std::filesystem::path& GetDataDirectoryPath(const std::string& projectPath);
}
