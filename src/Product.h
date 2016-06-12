#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>


class Product
{
public:
	virtual void setMember(std::string method, void* value) = 0;
	virtual void print(std::string tabs = "") = 0;
};

#endif