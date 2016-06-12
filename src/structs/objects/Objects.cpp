#include "Objects.h"


Object::Object(std::string val): value(val)
{
}


Object::~Object()
{
}


std::string Object::getValue()
{
	return value;
}


void Object::addChild(PObject pobj)
{
	children.push_back(pobj);
}


PObject Object::getChild(unsigned idx)
{
	return children[idx];
}


unsigned Object::getChildrenSize()
{
	return children.size();
}


void Object::pvPrint(std::string tabs)
{
	std::cout << tabs << getObjectTypeName(getType()) << "-->" << value << std::endl;
	for(std::vector<PObject>::iterator it = children.begin(); it != children.end(); ++it)
		it->get()->pvPrint("\t"+tabs);
}


void Object::print()
{
	std::cout << "Printing:\n";
	pvPrint("");
}


StringObject::StringObject(std::string val): Object(val)
{
}


StringObject::~StringObject()
{
}


ObjectType StringObject::getType()
{
	return ObjectType::String;
}


IntObject::IntObject(std::string val): Object(val)
{
}


IntObject::~IntObject()
{
}


ObjectType IntObject::getType()
{
	return ObjectType::Int;
}


IntFracObject::IntFracObject(std::string val): Object(val)
{
}


IntFracObject::~IntFracObject()
{
}


ObjectType IntFracObject::getType()
{
	return ObjectType::IntFrac;
}


IntExpObject::IntExpObject(std::string val): Object(val)
{
}


IntExpObject::~IntExpObject()
{
}


ObjectType IntExpObject::getType()
{
	return ObjectType::IntExp;
}


IntFracExpObject::IntFracExpObject(std::string val): Object(val)
{
}


IntFracExpObject::~IntFracExpObject()
{
}


ObjectType IntFracExpObject::getType()
{
	return ObjectType::IntFracExp;
}


TrueObject::TrueObject(): Object("true")
{
}


TrueObject::~TrueObject()
{
}


ObjectType TrueObject::getType()
{
	return ObjectType::True;
}


FalseObject::FalseObject(): Object("false")
{
}


FalseObject::~FalseObject()
{
}


ObjectType FalseObject::getType()
{
	return ObjectType::False;
}


NullObject::NullObject(): Object("null")
{
}


NullObject::~NullObject()
{
}


ObjectType NullObject::getType()
{
	return ObjectType::Null;
}


JSONArrayObject::JSONArrayObject(): Object("JSONArray")
{
}


JSONArrayObject::~JSONArrayObject()
{
}


ObjectType JSONArrayObject::getType()
{
	return ObjectType::JSONArray;
}


JSONObject::JSONObject(): Object("JSON")
{
}


JSONObject::~JSONObject()
{
}


ObjectType JSONObject::getType()
{
	return ObjectType::JSON;
}


PairObject::PairObject(): Object("Pair")
{
}


PairObject::~PairObject()
{
}


ObjectType PairObject::getType()
{
	return ObjectType::Pair;
}


ArrayObject::ArrayObject(): Object("Array")
{
}


ArrayObject::~ArrayObject()
{
}


ObjectType ArrayObject::getType()
{
	return ObjectType::Array;
}


EndOfFileObject::EndOfFileObject(): Object("EndOfFile")
{
}


EndOfFileObject::~EndOfFileObject()
{
}


ObjectType EndOfFileObject::getType()
{
	return ObjectType::EndOfFile;
}
