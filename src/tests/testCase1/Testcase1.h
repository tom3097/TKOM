#ifndef TESTCASE1_H
#define TESTCASE1_H

#include "../../Product.h"
#include <vector>
#include <string>
#include <iostream>


class ClassA: public Product
{
	int intMember1;
	double doubleMember1;
	std::vector<int> intVectorMember1;
public:
	static std::string getID();
	virtual void setMember(std::string member, void* value);
	virtual void print(std::string tabs);
};


class ClassB: public Product
{
	float floatMember1;
	bool boolMember1;
	ClassA classAMember;
public:
	static std::string getID();
	virtual void setMember(std::string member, void* value);
	virtual void print(std::string tabs);
};


class ClassC: public Product
{
	std::vector<ClassB> classBVectorMember1;
	ClassA classAMember;
	std::string stringMember1;
	std::string stringMember2;
public:
	static std::string getID();
	virtual void setMember(std::string member, void* value);
	virtual void print(std::string tabs);
};

#endif