#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "Source.h"
#include "structs/tokens/Token.h"
#include "ErrorsCommunicator.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <array>

class Lexer
{
	typedef std::pair<bool, Token> checkResult;
	std::vector<Token> tokens;
	Source source;

	std::string check4Get3HexDigits();
	std::string getExpPart();
	std::string getDotPart();

	void skipWhitespaces();
	checkResult EOFToken();
	checkResult SingleCharToken();
	checkResult NonQuotWordToken();
	checkResult QuotWordToken();
	checkResult NumberToken();
public:
	Lexer(std::string JSONpath);
	Lexer();
	~Lexer();

	void setJSON(std::string JSONpath);

	Token nextToken();
};

#endif
