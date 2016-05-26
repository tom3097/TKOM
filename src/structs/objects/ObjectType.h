#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include <unordered_map>
#include <string>

enum class ObjectType : unsigned int
{
	String = 0,
	Int = 1,
	IntFrac = 2,
	IntExp = 3,
	IntFracExp = 4,
	True = 5,
	False = 6,
	Null = 7,
	JSONArray = 8,
	JSON = 9,
	Pair = 10,
	Array = 11,
	None = 12,
};

const std::unordered_map<unsigned int, std::string> objectTypeNames = {
	{ 0, "String" },
	{ 1, "Int" },
	{ 2, "IntFrac" },
	{ 3, "IntExp" },
	{ 4, "IntFracExp" },
	{ 5, "True" },
	{ 6, "False" },
	{ 7, "Null" },
	{ 8, "JSONArray" },
	{ 9, "JSON" },
	{ 10, "Pair" },
	{ 11, "Array" },
	{ 12, "None" },
};

inline const std::string getObjectTypeName(const ObjectType& objectType)
{
	return objectTypeNames.at(static_cast<unsigned int>(objectType));
};

#endif
