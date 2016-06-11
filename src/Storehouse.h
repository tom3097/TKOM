#ifndef STOREHOUSE_H
#define STOREHOUSE_H

#include "Parser.h"
#include "VariableType.h"
#include <vector>
#include <string>

class Storehouse
{
	const std::string typeClass = "\"classID\"";
	std::vector<std::pair<std::string,PObject> > roots;
	void communicateErrorAndExit(std::string str);
	void analyzeAndInit(PObject pobj);
	void analyzeJSON(PObject pobj);
	bool compareTypes(PObject patternValue, PObject dataValue);
	bool findPair(PObject pattern, PObject pair);
	bool compareJSONs(PObject pattern, PObject data);
public:
	Storehouse(std::string configJSONpath);
	Storehouse();
	~Storehouse();
	void printRoots();
	int findPattern(PObject pobj);
};

#endif