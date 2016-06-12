#include "Storehouse.h"


Storehouse::Storehouse(std::string configJSONpath)
{
	Parser parser(configJSONpath);
	PObject pobj = parser.parseAll();
	analyzeAndInit(pobj);
}


Storehouse::Storehouse()
{
}


Storehouse::~Storehouse()
{
}


void Storehouse::setJSON(std::string configJSONpath)
{
	Parser parser(configJSONpath);
	PObject pobj = parser.parseAll();
	analyzeAndInit(pobj);
}


void Storehouse::communicateErrorAndExit(std::string str)
{
	std::cout << "[STOREHOUSE] Error: " << str << std::endl;
	std::exit(-1);
}


void Storehouse::printRoots()
{
	for(unsigned idx = 0; idx < roots.size(); ++idx)
	{
		std::cout << "Class name: " << roots[idx].first << std::endl;
		roots[idx].second.get()->print();
	}
}


PObject Storehouse::getRoot(int idx)
{
	return roots[idx].second;
}


int Storehouse::getJSONbyID(std::string id)
{
	for(unsigned idx = 0; idx < roots.size(); idx ++)
	{
		if(roots[idx].first == id)
			return idx;
	}
	return -1;
}


void Storehouse::analyzeAndInit(PObject pobj)
{
	if(pobj.get()->getType() == ObjectType::JSON)
		analyzeJSON(pobj);
	else
		for(unsigned idx = 0; idx < pobj.get()->getChildrenSize(); ++idx)
			analyzeAndInit(pobj.get()->getChild(idx));
}


void Storehouse::analyzeJSON(PObject pobj)
{
	bool classIDfound = false;
	std::string className = "";
	std::vector<std::string> types = VariableType::getInstance().getTypes();
	for(unsigned idx = 0; idx < pobj.get()->getChildrenSize(); ++idx)
	{
		PObject value = pobj.get()->getChild(idx).get()->getChild(1);
		if(value.get()->getType() == ObjectType::String)
		{
			if(value.get()->getValue() == typeClass && !classIDfound)
			{
				classIDfound = true;
				className = pobj.get()->getChild(idx).get()->getChild(0).get()->getValue();
			}
			else if(std::find(types.begin(), types.end(), value.get()->getValue()) == types.end())
				communicateErrorAndExit("undefined type found" + value.get()->getValue()); 
		}
		else if(value.get()->getType() == ObjectType::JSON)
			analyzeJSON(value);
		else if(value.get()->getType() == ObjectType::Array)
		{
			if(value.get()->getChildrenSize() != 1)
				communicateErrorAndExit("array size should be 1, current size" + value.get()->getChildrenSize());
			PObject child = value.get()->getChild(0);
			if(child.get()->getType() == ObjectType::String)
			{
				if(std::find(types.begin(), types.end(), child.get()->getValue()) == types.end())
					communicateErrorAndExit("undefined type found" + value.get()->getValue()); 
			}
			else if(child.get()->getType() == ObjectType::JSON)
				analyzeJSON(child);
			else
				communicateErrorAndExit("found bad object type:" + getObjectTypeName(child.get()->getType()));
		}
		else
			communicateErrorAndExit("found bad object type:" + getObjectTypeName(value.get()->getType()));
	}
	if(!classIDfound)
		communicateErrorAndExit("class type not found");
	roots.push_back(std::make_pair(className.substr(1, className.size()-2), pobj));
}


int Storehouse::findPattern(PObject pobj)
{
	for(unsigned idx = 0; idx < roots.size(); ++idx)
	{
		if(compareJSONs(roots[idx].second, pobj))
			return idx;
	}
	return -1;
}


bool Storehouse::compareJSONs(PObject pattern, PObject data)
{
	if(pattern.get()->getChildrenSize() - 1 != data.get()->getChildrenSize())
		return false;
	for(unsigned idx = 0; idx < data.get()->getChildrenSize(); ++idx)
	{
		if(!findPair(pattern, data.get()->getChild(idx)))
			return false;
	}
	return true;
}


bool Storehouse::findPair(PObject pattern, PObject pair)
{
	PObject dataKey = pair.get()->getChild(0);
	PObject dataValue = pair.get()->getChild(1);
	for(unsigned idx = 0; idx < pattern.get()->getChildrenSize(); ++idx)
	{
		PObject patternKey = pattern.get()->getChild(idx).get()->getChild(0);
		PObject patternValue = pattern.get()->getChild(idx).get()->getChild(1);
		if(dataKey.get()->getValue() == patternKey.get()->getValue()
			&& (compareTypes(patternValue, dataValue)))
			return true;
	}
	return false;
}


bool compareSampleTypes(PObject patternValue, PObject dataValue)
{
	std::vector<ObjectType> objectTypes = VariableType::getInstance().translateType(patternValue.get()->getValue());
	if(std::find(objectTypes.begin(), objectTypes.end(), dataValue.get()->getType()) == objectTypes.end())
		return false;
	return true;
}


bool Storehouse::compareTypes(PObject patternValue, PObject dataValue)
{
	if(patternValue.get()->getType() == ObjectType::JSON)
	{
		if(dataValue.get()->getType() == ObjectType::JSON)
			return compareJSONs(patternValue, dataValue);
		return false;
	}
	if(patternValue.get()->getType() == ObjectType::Array)
	{
		PObject childType = patternValue.get()->getChild(0);
		if(dataValue.get()->getType() == ObjectType::Array)
		{
			for(unsigned idx = 0; idx < dataValue.get()->getChildrenSize(); ++idx)
			{
				PObject arrayChild = dataValue.get()->getChild(idx);
				if(!compareTypes(childType, arrayChild))
					return false;
			}
			return true;
		}
		return false;
	}
	return compareSampleTypes(patternValue, dataValue);
}

