#include "Source.h"


Source::Source(std::string JSONpath) : position(TextPosition()), foundEOFValue(false)
{
	JSON.open(JSONpath, std::ios::in);
	if (!JSON.is_open())
	{
		std::cerr << "FATAL ERROR: Can not open file " << JSONpath << std::endl;
		std::exit(-1);
	}
	nextChar();
}


Source::Source() : foundEOFValue(true)
{
}


Source::~Source()
{
	JSON.close();
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
	nextChar();
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



