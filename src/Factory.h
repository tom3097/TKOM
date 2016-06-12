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
	std::unordered_map<std::string, handler > idsTranslator;

	void fulfillJSON(Product* product, PObject patternJSON, PObject dataJSON);
	void findAndFulfillField(Product* product, PObject patternJSON, PObject dataField);
	void fulfillField(Product* product, PObject patternField, PObject dataField);

	Product* getJSONValue(PObject patternJSON, PObject dataJSON);
	void* getArrayValue(PObject patternField, PObject dataField);
	void* getSampleTypeValue(PObject dataField, PObject patternField);

	void deleteSampleTypeValue(PObject patternField, void* value);
	void deleteArrayValue(PObject patternField, void* value);
	void deleteJSONValue(void* value);

	void printCommunicate(std::string);
	std::string findID(PObject JSONdata);
	Product* createProduct(std::string id);
public:
	Factory(std::string configJSONpath, std::string dataJSONpath);
	~Factory();

	void registerProduct(std::string id, handler creator);
	void printProducts();
	
	std::vector<Product*> getProductsByID(std::string id);
};

#endif