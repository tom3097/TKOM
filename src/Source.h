#ifndef SOURCE_H
#define SOURCE_H

#include <string>
#include "structs/TextPosition.h"
#include <iostream>
#include <fstream>

class Source
{
	std::fstream JSON;
	TextPosition position;
	char currentCharValue;
	bool foundEOFValue;
public:
	Source();
	Source(std::string JSONpath);
	~Source();

	void setPosition(TextPosition newPosition);
	void setJSON(std::string JSONpath);

	TextPosition getPosition();
	bool getFoundEOF();

	char currentChar();
	void nextChar();
};

#endif
