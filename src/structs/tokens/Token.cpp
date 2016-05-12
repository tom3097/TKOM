#include "Token.h"

Token::Token() : value(""), position(TextPosition()), type(TokenType::None)
{
}


Token::Token(std::string _value, TokenType _type, TextPosition _position) : value(_value), type(_type), position(_position)
{
}


Token::~Token()
{
}


std::string Token::getValue()
{
	return value;
}


TokenType Token::getType()
{
	return type;
}


TextPosition Token::getPosition()
{
	return position;
}


void Token::setValue(std::string newValue)
{
	value = newValue;
}


void Token::setType(TokenType newType)
{
	type = newType;
}


void Token::setPosition(TextPosition newPosition)
{
	position = newPosition;
}


std::string Token::toString()
{
	std::stringstream buf;
	buf << "VAL: " << value;
	buf << " TYPE: " << getTokenTypeName(type);
	buf << " LINE: " << position.getLineNumber();
	buf << " CHAR: " << position.getCharNumber();
	return buf.str();
}
