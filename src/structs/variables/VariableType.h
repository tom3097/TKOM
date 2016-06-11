#ifndef VARIABLETYPE_H
#define VARIABLETYPE_H

#include <unordered_map>
#include <vector>
#include <string>
#include "../objects/ObjectType.h"

class VariableType
{
	std::unordered_map<std::string,std::vector<ObjectType> > typesTranslator;
	VariableType();
	~VariableType();
	VariableType(const VariableType&) = delete;
public:
	static VariableType& getInstance();
	std::vector<std::string> getTypes();
	std::vector<ObjectType> translateType(std::string type);
};

#endif