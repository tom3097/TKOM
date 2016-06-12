#include "Factory.h"


Factory::Factory(std::string configJSONpath, std::string dataJSONpath)
{
	storehouse.setJSON(configJSONpath);
	parser.setJSON(dataJSONpath);
}


Factory::~Factory()
{
}


void Factory::fulfillJSON(Product* product, PObject patternJSON, PObject dataJSON)
{
	for(unsigned idx = 0; idx < dataJSON.get()->getChildrenSize(); ++idx)
		findAndFulfillField(product, patternJSON, dataJSON.get()->getChild(idx));
}


void Factory::findAndFulfillField(Product* product, PObject patternJSON, PObject dataField)
{
	for(unsigned idx = 0; idx < patternJSON.get()->getChildrenSize(); ++idx)
	{
		PObject child = patternJSON.get()->getChild(idx);
		if(dataField.get()->getChild(0).get()->getValue()
		 == child.get()->getChild(0).get()->getValue())
			fulfillField(product, child, dataField);
	}
}


void Factory::fulfillField(Product* product, PObject patternField, PObject dataField)
{
	std::string member = dataField.get()->getChild(0).get()->getValue();
	if(dataField.get()->getChild(1).get()->getType() == ObjectType::JSON)
	{
		PObject jsonPattern = patternField.get()->getChild(1);
		PObject jsonData = dataField.get()->getChild(1);
		void* value = static_cast<void*>(getJSONValue(jsonPattern, jsonData));
		product->setMember(member, value);
		deleteJSONValue(value);
	}
	else if(dataField.get()->getChild(1).get()->getType() == ObjectType::Array)
	{
		void* value = getArrayValue(patternField, dataField);
		product->setMember(member, value);
		deleteArrayValue(patternField, value);
	}
	else
	{
	  void* value = getSampleTypeValue(patternField, dataField);
		product->setMember(member, value);
		deleteSampleTypeValue(patternField, value);
	}
}


Product* Factory::getJSONValue(PObject patternJSON, PObject dataJSON)
{
	std::string quotedId = findID(patternJSON);
	std::string id = quotedId.substr(1, quotedId.size()-2);
	Product* product = createProduct(id);
	for(unsigned idx = 0; idx < dataJSON.get()->getChildrenSize(); ++idx)
		findAndFulfillField(product, patternJSON, dataJSON.get()->getChild(idx));
	return product;
}


void* Factory::getArrayValue(PObject patternField, PObject dataField)
{
	std::string dataType = patternField.get()->getChild(1).get()->getChild(0).get()->getValue();
	PObject dataValues = dataField.get()->getChild(1);
	if(dataType == "\"int\"")
	{
		std::vector<int>* values = new std::vector<int>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			std::string childValue = dataValues.get()->getChild(idx).get()->getValue();
			int value = std::stoi(childValue);
			values->push_back(value);
		}
		return static_cast<void*>(values);
	}
	else if(dataType == "\"long\"")
	{
		std::vector<long>* values = new std::vector<long>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			std::string childValue = dataValues.get()->getChild(idx).get()->getValue();
			long value = std::stol(childValue);
			values->push_back(value);
		}
		return static_cast<void*>(values);
	}
	else if(dataType == "\"float\"")
	{
		std::vector<float>* values = new std::vector<float>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			std::string childValue = dataValues.get()->getChild(idx).get()->getValue();
			float value = std::stof(childValue);
			values->push_back(value);
		}
		return static_cast<void*>(values);
	}
	else if(dataType == "\"double\"")
	{
		std::vector<double>* values = new std::vector<double>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			std::string childValue = dataValues.get()->getChild(idx).get()->getValue();
			double value = std::stod(childValue);
			values->push_back(value);
		}
		return static_cast<void*>(values);
	}
	else if(dataType == "\"bool\"")
	{
		std::vector<bool>* values = new std::vector<bool>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			std::string childValue = dataValues.get()->getChild(idx).get()->getValue();
			bool value = (childValue == "true") ? new bool(true) : new bool(false);
			values->push_back(value);
		}
		return static_cast<void*>(values);
	}
	else if(dataType == "\"string\"")
	{
		std::vector<std::string>* values = new std::vector<std::string>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			std::string childValue = dataValues.get()->getChild(idx).get()->getValue();
			values->push_back(childValue);
		}
		return static_cast<void*>(values);
	}
	if(dataType == "JSON")
	{
		PObject pattern = patternField.get()->getChild(1).get()->getChild(0);
		std::vector<Product*>* values = new std::vector<Product*>();
		for(unsigned idx = 0; idx < dataValues.get()->getChildrenSize(); ++idx)
		{
			PObject JSONobject = dataValues.get()->getChild(idx);;
		 	Product* product = getJSONValue(pattern, JSONobject);
		 	if(product == nullptr)
		 		return static_cast<void*>(values);
		 	values->push_back(product);
		 }
		 return static_cast<void*>(values);
	}
}


void* Factory::getSampleTypeValue(PObject patternField, PObject dataField)
{
	std::string dataValue = dataField.get()->getChild(1).get()->getValue();
	std::string dataType = patternField.get()->getChild(1).get()->getValue();
	if(dataType == "\"int\"")
	{
		void* intVal = new int(std::stoi(dataValue));
		return intVal;
	}
	else if(dataType == "\"long\"")
	{
		void* longVal = new long(std::stol(dataValue));
		return longVal;
	}
	else if(dataType == "\"float\"")
	{
		void* floatVal = new float(std::stof(dataValue));
		return floatVal;
	}
	else if(dataType == "\"double\"")
	{
		void* doubleVal = new double(std::stod(dataValue));
		return doubleVal;
	}
	else if(dataType == "\"bool\"")
	{
		void* boolVal = (dataValue == "true") ? new bool(true) : new bool(false);
		return boolVal;
	}
	else if(dataType == "\"string\"")
	{
		dataValue = dataValue.substr(1, dataValue.size()-2);
		void* stringVal = new std::string(dataValue);
		return stringVal;
	}
}


void Factory::deleteJSONValue(void* value)
{
	Product* product = static_cast<Product*>(value);
	delete product;
}


void Factory::deleteSampleTypeValue(PObject patternField, void* value)
{
	std::string dataType = patternField.get()->getChild(1).get()->getValue();
	if(dataType == "\"int\"")
	{
		int* castValue = static_cast<int*>(value);
		delete castValue;
	}
	else if(dataType == "\"long\"")
	{
		long* castValue = static_cast<long*>(value);
		delete castValue;
	}
	else if(dataType == "\"float\"")
	{
		float* castValue = static_cast<float*>(value);
		delete castValue;
	}
	else if(dataType == "\"double\"")
	{
		double* castValue = static_cast<double*>(value);
		delete castValue;
	}
	else if(dataType == "\"bool\"")
	{
		bool* castValue = static_cast<bool*>(value);
		delete castValue;
	}
	else if(dataType == "\"string\"")
	{
		std::string* castValue = static_cast<std::string*>(value);
		delete castValue;
	}
}


void Factory::deleteArrayValue(PObject patternField, void* value)
{
	std::string dataType = patternField.get()->getChild(1).get()->getChild(0).get()->getValue();
	if(dataType == "\"int\"")
	{
		std::vector<int>* castValue = static_cast< std::vector<int>* >(value);
		delete castValue;
	}
	else if(dataType == "\"long\"")
	{
		std::vector<long>* castValue = static_cast< std::vector<long>* >(value);
		delete castValue;
	}
	else if(dataType == "\"float\"")
	{
		std::vector<float>* castValue = static_cast< std::vector<float>* >(value);
		delete castValue;
	}
	else if(dataType == "\"double\"")
	{
		std::vector<double>* castValue = static_cast< std::vector<double>* >(value);
		delete castValue;
	}
	else if(dataType == "\"bool\"")
	{
		std::vector<bool>* castValue = static_cast< std::vector<bool>* >(value);
		delete castValue;
	}
	else if(dataType == "\"string\"")
	{
		std::vector<std::string>* castValue = static_cast< std::vector<std::string>* >(value);
		delete castValue;
	}
	else if(dataType == "JSON")
	{
		std::vector<Product*>* castValue = static_cast< std::vector<Product*>* >(value);
		for(unsigned idx = 0; idx < castValue->size(); ++idx)
			delete (*castValue)[idx];
		delete castValue;
	}
}


void Factory::printCommunicate(std::string comm)
{
	std::cout << "[FACTORY] " << comm << std::endl;
}


Product* Factory::createProduct(std::string id)
{
	std::unordered_map<std::string, handler >::const_iterator i = idsTranslator.find(id);
	if(i == idsTranslator.end())
	{
		printCommunicate("Handler for id: " + id + " is not registered.\n");
		std::exit(-1);
	}
	return i->second(); 
}


std::string Factory::findID(PObject JSONdata)
{
	for(unsigned idx = 0; idx < JSONdata.get()->getChildrenSize(); ++idx)
	{
		PObject child = JSONdata.get()->getChild(idx);
		if(child.get()->getChild(1).get()->getType() == ObjectType::String
			&& child.get()->getChild(1).get()->getValue() == "\"classID\"")
			return child.get()->getChild(0).get()->getValue();
	}
}


void Factory::registerProduct(std::string id, handler creator)
{
	idsTranslator[id] = creator;
}


void Factory::printProducts()
{
	for(auto pair: idsTranslator)
		std::cout << pair.first << std::endl;
}


std::vector<Product*> Factory::getProductsByID(std::string id)
{
	std::vector<Product*> products;
	int JSONidx = storehouse.getJSONbyID(id);
	if(JSONidx < 0)
	{
		printCommunicate("Object with id: " + id +" has no defined pattern");
		return products;
	}
	PObject patternJSON = storehouse.getRoot(JSONidx);
	while(true)
	{
		PObject currentJSON = parser.nextJSON();
		if(currentJSON.get()->getType() == ObjectType::EndOfFile)
			return products;
		if(storehouse.compareJSONs(patternJSON, currentJSON))
		{
			Product* product = createProduct(id);
			fulfillJSON(product, patternJSON, currentJSON);
			products.push_back(product);
		}
	}
}

