#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "structs/objects/Objects.h"
#include "ErrorsCommunicator.h"
#include <iostream>
#include <string>
#include <functional>

class Parser
{
	void nextToken();
	void accept(TokenType type);
	bool isCurrTokenType(TokenType type);

	PObject parseJSONArray();
	PObject parseJSON();
	PObject parsePair();
	PObject parseKey();
	PObject parseValue();
	PObject parseArray();

	PObject parseEndOfFile();

	PObject beginSingleJSON();
	PObject beginMultiJSON();
	PObject middleMultiJSON();
	PObject endSingleMultiJSON();

	Lexer lexer;
	Token currToken;
public:
	Parser(std::string JSONpath);
	Parser();
	~Parser();

	std::function<PObject ()> nextJSON;

	void goToBegin();

	void setJSON(std::string JSONpath);

	PObject parseAll();

};

#endif
