#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "Source.h"
#include "structs/tokens/Token.h"
#include "ErrorsCommunicator.h"
#include <iostream>
#include <string>

class Lexer
{
	typedef std::pair<bool, Token> checkResult;
	std::vector<Token> tokens;
	Source source;

	void skipWhitespaces();
	checkResult EOFToken();
	checkResult SingleCharToken();
	checkResult NonQuotWordToken();
	checkResult QuotWordToken();
	checkResult NumberToken();
public:
	Lexer(std::string JSONpath);
	~Lexer();

	Token nextToken();
};

#endif
