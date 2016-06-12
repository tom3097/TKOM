#include "Testcase1.h"


std::string ClassA::getID()
{
	return std::string("ClassA");
}


void ClassA::setMember(std::string member, void* value)
{
	if(member == "\"intMember1\"")
		intMember1 = *(static_cast<int*>(value));
	else if(member == "\"doubleMember1\"")
		doubleMember1 = *(static_cast<double*>(value));
	else if(member == "\"intVectorMember1\"")
		intVectorMember1 = *(static_cast<std::vector<int> *>(value));
}


void ClassA::print(std::string tabs)
{
	std::cout << tabs << "intMember1 = " << intMember1 << std::endl;
	std::cout << tabs << "doubleMember1 = " << doubleMember1 << std::endl;
	std::cout << tabs << "intVectorMember1 = ";
	for(unsigned idx = 0; idx < intVectorMember1.size(); ++idx)
		std::cout << intVectorMember1[idx] << "\t";
	std::cout << std::endl;
}


std::string ClassB::getID()
{
	return std::string("ClassB");
}


void ClassB::setMember(std::string member, void* value)
{
	if(member == "\"floatMember1\"")
		floatMember1 = *(static_cast<float*>(value));
	else if(member == "\"boolMember1\"")
		boolMember1 = *(static_cast<bool*>(value));
	else if(member == "\"classAMember\"")
	{
		Product* product = static_cast<Product*>(value);
		classAMember = *(dynamic_cast<ClassA*>(product));
	}
}


void ClassB::print(std::string tabs)
{
	std::cout << tabs << "floatMember1 = " << floatMember1 << std::endl;
	std::cout << tabs << "boolMember1 = " << boolMember1 << std::endl;
	std::cout << tabs << "classAMember = " << std::endl;
	classAMember.print(tabs+"\t");
}


std::string ClassC::getID()
{
	return std::string("ClassC");
}


void ClassC::setMember(std::string member, void* value)
{
	if(member == "\"stringMember2\"")
		stringMember2 = *(static_cast<std::string*>(value));
	else if(member == "\"stringMember1\"")
		stringMember1 = *(static_cast<std::string*>(value));
	else if(member == "\"classAMember\"")
	{
		Product* product = static_cast<Product*>(value);
		classAMember = *(dynamic_cast<ClassA*>(product));
	}
	else if(member == "\"classBVectorMember1\"")
	{
		std::vector<Product*> *products = static_cast<std::vector<Product*> *>(value);
		for(unsigned idx = 0; idx < products->size(); ++idx)
			classBVectorMember1.push_back(*(dynamic_cast<ClassB*>( (*products)[idx] )));
	}
}


void ClassC::print(std::string tabs)
{
	std::cout << tabs << "classBVectorMember1 = " << std::endl;
	for(unsigned idx = 0; idx < classBVectorMember1.size(); ++idx)
		classBVectorMember1[idx].print(tabs+"\t");
	std::cout << tabs << "classAMember = " << std::endl;
	classAMember.print(tabs+"\t");
	std::cout << tabs << "stringMember1 = " << stringMember1 << std::endl;
	std::cout << tabs << "stringMember2 = " << stringMember2 << std::endl;
}


