#include "VectorUtil.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace CppUtil
{
	std::vector<std::vector<int>> ReadIntInputsIntoVector(std::string path)
	{
		std::ifstream infile(path);
		if (!infile)
		{
			std::cerr << "Error opening file" << std::endl;
			return {};
		}

		std::vector<std::vector<int>> allReports;
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream ss(line);

			std::vector<int> newReport = {};

			int x;
			while (ss >> x)
			{
				newReport.push_back(x);
			}

			allReports.push_back(newReport);
		}
		return allReports;
	}

	std::vector<std::vector<char>> ReadCharInputsIntoVector(std::string path)
	{
		std::ifstream infile(path);
		if (!infile)
		{
			std::cerr << "Error opening file" << std::endl;
			return {};
		}

		std::vector<std::vector<char>> input;
		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream ss(line);

			std::vector<char> newLine = {};

			char x;
			while (ss >> x)
			{
				newLine.push_back(x);
			}

			input.push_back(newLine);
		}
		return input;
	}
}
