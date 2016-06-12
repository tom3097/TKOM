#include <iostream>
#include <fstream>
#include "Factory.h"
#include "src/tests/testCase1/Testcase1.h"


Product* createClassA()
{
	return new ClassA();
}

Product * createClassB()
{
	return new ClassB();
}

Product * createClassC()
{
	return new ClassC();
}

int main()
{
	Factory factory("../src/tests/testCase1/confJSON.json", "../src/tests/testCase1/dataJSON.json");
	factory.registerProduct(ClassA::getID(), createClassA);
	factory.registerProduct(ClassB::getID(), createClassB);
	factory.registerProduct(ClassC::getID(), createClassC);
	std::vector<Product*> products = factory.getProductsByID(ClassC::getID());
	for (unsigned i = 0; i < products.size(); ++i)
		products[i]->print();
	return 0;
}
