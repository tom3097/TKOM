#include "TextPosition.h"


TextPosition::TextPosition(int _linenumber, int _charNumber) : lineNumber(_linenumber), charNumber(_charNumber)
{
}


TextPosition::~TextPosition()
{
}


int TextPosition::getLineNumber()
{
	return lineNumber;
}


int TextPosition::getCharNumber()
{
	return charNumber;
}


void TextPosition::setLineNumber(int newLineNumber)
{
	lineNumber = newLineNumber;
}


void TextPosition::setCharNumber(int newCharNumber)
{
	charNumber = newCharNumber;
}


void TextPosition::incrementLineNumber()
{
	++lineNumber;
	charNumber = 1;
}


void TextPosition::incrementCharNumber()
{
	++charNumber;
}


