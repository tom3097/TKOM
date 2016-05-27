#include "Source.h"


Source::Source(std::string JSONpath) : position(TextPosition()), foundEOFValue(false)
{
	JSON.open(JSONpath, std::ios::in);
	if (!JSON.is_open())
	{
		std::cerr << "FATAL ERROR: Can not open file " << JSONpath << std::endl;
		std::exit(-1);
	}
	if (!JSON.get(currentCharValue))
		foundEOFValue = true;
}


Source::Source() : foundEOFValue(true), JSON(nullptr)
{
}


Source::~Source()
{
	JSON.close();
}


void Source::goToBegin()
{
	if(!JSON.is_open())
		return;
	JSON.clear();
	JSON.seekg(0, std::ios::beg);
	foundEOFValue = false;
	if (!JSON.get(currentCharValue))
		foundEOFValue = true;
}


TextPosition Source::getPosition()
{
	return position;
}


bool Source::getFoundEOF()
{
	return foundEOFValue;
}


void Source::setPosition(TextPosition newPosition)
{
	position = newPosition;
}


void Source::setJSON(std::string JSONpath)
{
	foundEOFValue = false;
	JSON.open(JSONpath, std::ios::in);
	if (!JSON.is_open())
	{
		std::cerr << "FATAL ERROR: Can not open file " << JSONpath << std::endl;
		std::exit(-1);
	}
	if (!JSON.get(currentCharValue))
		foundEOFValue = true;
}


char Source::currentChar()
{
	return currentCharValue;
}


void Source::nextChar()
{
	if (foundEOFValue)
		return;
	if (currentCharValue == '\n')
	{
		position.incrementLineNumber();
	}
	else
	{
		position.incrementCharNumber();
	}
	if (!JSON.get(currentCharValue))
		foundEOFValue = true;
}



