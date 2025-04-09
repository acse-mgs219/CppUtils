#include "TestUtil.h"

#include <fstream>
#include <iostream>

namespace CppUtil
{
	bool FilesMatch(const std::string& expectedFile, const std::string& actualFile, int numLinesToCompare)
	{
		// Open file 1 for reading
		std::ifstream eFile(expectedFile);
		if (!eFile.is_open())
		{
			return false;
		}

		// Open file 2 for reading
		std::ifstream aFile(actualFile);
		if (!aFile.is_open())
		{
			return false;
		}

		std::string eLine;
		std::string aLine;
		while (std::getline(eFile, eLine) && std::getline(aFile, aLine))
		{
			if (aLine != eLine)
			{
				return false;
			}

			if (--numLinesToCompare == 0)
			{
				return true;
			}
		}

		if (eFile.eof())
		{
			const bool aAlsoEnded = std::getline(aFile, aLine).fail();
			return aAlsoEnded && aLine == eLine;
		}

		return false;
	}
}
