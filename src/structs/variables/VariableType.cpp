#include "VariableType.h"


VariableType::VariableType()
{
	std::vector<ObjectType> boolType = { ObjectType::True, ObjectType::False };
	std::vector<ObjectType> intType = { ObjectType::Int, ObjectType::IntExp };
	std::vector<ObjectType> longType = { ObjectType::Int, ObjectType::IntExp };
	std::vector<ObjectType> floatType = { ObjectType::IntFrac };
	std::vector<ObjectType> doubleType = { ObjectType::IntFrac, ObjectType::IntFracExp };
	std::vector<ObjectType> stringType = { ObjectType::String };
	typesTranslator = {
		{ "\"bool\"", boolType },
	 	{ "\"int\"", intType },
	 	{ "\"long\"", longType },
	 	{ "\"float\"", floatType },
	 	{ "\"double\"", doubleType },
	 	{ "\"string\"", stringType }
  };
}


VariableType::~VariableType()
{
}


std::vector<std::string> VariableType::getTypes()
{
	std::vector<std::string> keys;
	for(auto pair: typesTranslator)
		keys.push_back(pair.first);
	return keys;
}


std::vector<ObjectType> VariableType::translateType(std::string type)
{
	return typesTranslator.at(type);
}


VariableType& VariableType::getInstance()
{
	static VariableType instance;
	return instance;
}