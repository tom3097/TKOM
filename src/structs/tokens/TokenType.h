#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <unordered_map>
#include <string>

enum class TokenType : unsigned int
{
	LeftCurlyBracket = 0,
	RightCurlyBracket = 1,
	String = 2,
	Int = 3,
	IntFrac = 4,
	IntExp = 5,
	IntFracExp = 6,
	LeftSquareBracket = 7,
	RightSquareBracket = 8,
	True = 9,
	False = 10,
	Null = 11,
	Colon = 12,
	Comma = 13,
	None = 14,
	EndOfFile = 15,
};

const std::unordered_map<unsigned int, std::string> tokenTypeNames = {
	{ 0, "LeftCurlyBracket" },
	{ 1, "RightCurlyBracket" },
	{ 2, "String" },
	{ 3, "Int" },
	{ 4, "IntFrac" },
	{ 5, "IntExp" },
	{ 6, "IntFracExp" },
	{ 7, "LeftSquareBracket" },
	{ 8, "RightSquareBracket" },
	{ 9, "True" },
	{ 10, "False" },
	{ 11, "Null" },
	{ 12, "Colon" },
	{ 13, "Comma" },
	{ 14, "None" },
	{ 15, "EndOfFile" },
};

inline const std::string getTokenTypeName(const TokenType& tokenType)
{
	return tokenTypeNames.at(static_cast<unsigned int>(tokenType));
};

#endif
