#pragma once

#include "LogUtils.h"

#include <string>
#include <type_traits>

// Macro to automatically log GUID creation
#define LOG_GUID_CREATION(className) LOG_INFO(#className " created with GUID: {}", mGUID.ID)

template <typename T>
struct TGUID
{
	TGUID() { ID = generateID(); }

	int ID;

	template <typename U>
	bool operator==(const TGUID<U>& other) const
	{
		const bool typesAreSame = std::is_same_v<U, T>;
		const bool valuesAreSame = ID == other.ID;
		return typesAreSame && valuesAreSame;
	}

	std::string ToString() const
	{
#ifdef _DEBUG
		return std::to_string(ID);
#else
		return {};
#endif
	}

private:
	// #TODO_LIB: Persist the ID generation across program runs to avoid duplicates
	static int generateID()
	{
		static int id = 0;
		return id++;
	}
};
