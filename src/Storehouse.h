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
public:
	Storehouse(std::string configJSONpath);
	Storehouse();
	~Storehouse();
	void setJSON(std::string configJSONpath);
	void printRoots();
	bool compareJSONs(PObject pattern, PObject data);
	int findPattern(PObject pobj);
	int getJSONbyID(std::string id);
	PObject getRoot(int idx);
};

#endif