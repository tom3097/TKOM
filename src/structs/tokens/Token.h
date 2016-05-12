#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include "TextPosition.h"
#include <sstream>

class Token
{
	std::string value;
	TokenType type;
	TextPosition position;
public:
	Token();
	Token(std::string _value, TokenType _type, TextPosition _position);
	~Token();

	std::string getValue();
	TokenType getType();
	TextPosition getPosition();

	void setValue(std::string newValue);
	void setType(TokenType newType);
	void setPosition(TextPosition newPosition);

	std::string toString();
};

#endif
