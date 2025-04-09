#pragma once

#include <string>

namespace CppUtil
{
	bool FilesMatch(const std::string& expectedFile, const std::string& actualFile, int numLinesToCompare = -1);
}
