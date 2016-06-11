#ifndef OBJECTS_H
#define OBJECTS_H

#include "ObjectType.h"
#include <memory>
#include <vector>
#include <iostream>

class Object;

typedef std::shared_ptr<Object> PObject;

class Object
{
protected:
	std::string value;
	std::vector<PObject> children;
	void pvPrint(std::string tabs);
public:
	Object(std::string val);
	~Object();
	std::string getValue();
	void addChild(PObject pobj);
	PObject getChild(unsigned idx);
	unsigned getChildrenSize();
	void print();
	virtual ObjectType getType() = 0;
};


class StringObject: public Object
{
public:
	StringObject(std::string val);
	~StringObject();
	ObjectType getType();
};


class IntObject: public Object
{
public:
	IntObject(std::string val);
	~IntObject();
	ObjectType getType();
};


class IntFracObject: public Object
{
public:
	IntFracObject(std::string val);
	~IntFracObject();
	ObjectType getType();
};


class IntExpObject: public Object
{
public:
	IntExpObject(std::string val);
	~IntExpObject();
	ObjectType getType();
};


class IntFracExpObject: public Object
{
public:
	IntFracExpObject(std::string val);
	~IntFracExpObject();
	ObjectType getType();
};


class TrueObject: public Object
{
public:
	TrueObject();
	~TrueObject();
	ObjectType getType();
};


class FalseObject: public Object
{
public:
	FalseObject();
	~FalseObject();
	ObjectType getType();
};


class NullObject: public Object
{
public:
	NullObject();
	~NullObject();
	ObjectType getType();
};


class JSONArrayObject: public Object
{
public:
	JSONArrayObject();
	~JSONArrayObject();
	ObjectType getType();
};


class JSONObject: public Object
{
public:
	JSONObject();
	~JSONObject();
	ObjectType getType();
};


class PairObject: public Object
{
public:
	PairObject();
	~PairObject();
	ObjectType getType();
};


class ArrayObject: public Object
{
public:
	ArrayObject();
	~ArrayObject();
	ObjectType getType();
};

class EndOfFileObject: public Object
{
public:
	EndOfFileObject();
	~EndOfFileObject();
	ObjectType getType();
};

#endif