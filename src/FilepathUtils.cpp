#include "FilepathUtils.h"

#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <windows.h>

namespace CppUtil
{
	namespace fs = std::filesystem;

	const fs::path& GetDataDirectoryPath(const std::string& projectPath)
	{
		static std::unordered_map<const char*, fs::path> projectPaths{};
		const char* projectPathCstr = projectPath.c_str();

		if (projectPaths.contains(projectPathCstr))
		{
			return projectPaths[projectPathCstr];
		}

		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		fs::path exePath(buffer);
		fs::path exeDir = exePath.parent_path().parent_path();
		fs::path dataRelativePath = projectPath + "\\Data";
		fs::path dataFullPath = exeDir / dataRelativePath;
		projectPaths[projectPathCstr] = dataFullPath;

		return projectPaths[projectPathCstr];
	}
}
