#pragma once

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

namespace CppUtil
{
	template <typename T>
	typename std::vector<T>::iterator insert_sorted(std::vector<T>& vec, const T& item)
	{
		return vec.insert(std::upper_bound(vec.begin(), vec.end(), item), item);
	}

	template <typename T, typename Pred>
	typename std::vector<T>::iterator insert_sorted(std::vector<T>& vec, const T& item, Pred pred)
	{
		return vec.insert(std::upper_bound(vec.begin(), vec.end(), item, pred), item);
	}

	std::vector<std::string> split(const std::string& cs, const std::string& delimiter)
	{
		std::vector<std::string> tokens;
		size_t pos = 0;
		std::string token;
		std::string s = cs;

		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);
			tokens.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		tokens.push_back(s);

		return tokens;
	}

	template <typename T>
	bool InsertIfUnique(std::vector<T>& vec, const T& value)
	{
		if (std::find(vec.begin(), vec.end(), value) == vec.end())
		{
			vec.push_back(value);
			return true;
		}
		return false;
	}

	template <typename T, typename Hash>
	std::size_t CountUnique(const std::vector<T>& vec)
	{
		std::unordered_set<T, Hash> uniqueElements(vec.begin(), vec.end());
		return uniqueElements.size();
	}

	template <typename T, typename... Vectors>
	std::vector<T> CollapseVectors(const std::vector<T>& first, const Vectors&... rest)
	{
		std::vector<T> result;

		result.reserve((first.size() + ... + rest.size()));

		result.insert(result.end(), first.begin(), first.end());
		(..., result.insert(result.end(), rest.begin(), rest.end()));

		return result;
	}

	std::vector<std::vector<int>> ReadIntInputsIntoVector(std::string path = "Data//input.txt");
	std::vector<std::vector<char>> ReadCharInputsIntoVector(std::string path = "Data//input.txt");
} // namespace CppUtil
