#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include "Product.h"
#include "structs/objects/Objects.h"
#include "Storehouse.h"


class Factory
{
private:
	typedef Product* (*handler)(void);
	Storehouse storehouse;
	Parser parser;
	void printCommunicate(std::string);
	void deleteJSONValue(void* value);
	std::unordered_map<std::string, handler > idsTranslator; 
	std::string findID(PObject JSONdata);
	void* getArrayValue(PObject patternField, PObject dataField);
	void* getSampleTypeValue(PObject dataField, PObject patternField);
	void fulfillField(Product* product, PObject patternField, PObject dataField);
	void findAndFulfillField(Product* product, PObject patternJSON, PObject dataField);
	Product* getJSONValue(PObject patternJSON, PObject dataJSON);
	void fulfillJSON(Product* product, PObject patternJSON, PObject dataJSON);
	Product* createProduct(std::string id);
	void deleteSampleTypeValue(PObject patternField, void* value);
	void deleteArrayValue(PObject patternField, void* value);
public:
	Factory(std::string configJSONpath, std::string dataJSONpath);
	~Factory();
	std::vector<Product*> getProductsByID(std::string id);
	void registerProduct(std::string id, handler creator);
	void printProducts();
};

#endif