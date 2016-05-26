#include "Parser.h"


Parser::Parser(std::string JSONpath)
{
	lexer.setJSON(JSONpath);
	nextToken();
}

Parser::Parser()
{
}


Parser::~Parser()
{
}


void Parser::setJSON(std::string JSONpath)
{
	lexer.setJSON(JSONpath);
	nextToken();
}


void Parser::nextToken()
{
	currToken = lexer.nextToken();
}


bool Parser::isCurrTokenType(TokenType type)
{
	return currToken.getType() == type;
}


void Parser::accept(TokenType type)
{
	if(isCurrTokenType(type))
		nextToken();
	else
	{
		ErrorsCommunicator::communicateAndExit("PARSER", currToken.getPosition(),
			 getTokenTypeName(type), getTokenTypeName(currToken.getType()));
	}
}


PObject Parser::parse()
{
	if(isCurrTokenType(TokenType::LeftSquareBracket))
		return parseJSONArray();
	else
		return parseJSON();
}


PObject Parser::parseJSONArray()
{
	PObject pobj = std::make_shared<JSONArrayObject>();
	accept(TokenType::LeftSquareBracket);
	if(!isCurrTokenType(TokenType::RightSquareBracket))
	{
		PObject js = parseJSON();
		pobj.get()->addChild(js);
		while(isCurrTokenType(TokenType::Comma))
		{
			accept(TokenType::Comma);
			PObject js = parseJSON();
			pobj.get()->addChild(js);
		}
	}
	accept(TokenType::RightSquareBracket);
	return pobj;
}


PObject Parser::parseJSON()
{
	PObject pobj = std::make_shared<JSONObject>();
	accept(TokenType::LeftCurlyBracket);
	if(!isCurrTokenType(TokenType::RightCurlyBracket))
	{
		PObject pair = parsePair();
		pobj.get()->addChild(pair);
		while(isCurrTokenType(TokenType::Comma))
		{
			accept(TokenType::Comma);
			PObject pair = parsePair();
			pobj.get()->addChild(pair);
		}
	}
	accept(TokenType::RightCurlyBracket);
	return pobj;
}


PObject Parser::parseKey()
{
	PObject pobj = std::make_shared<StringObject>(currToken.getValue());
	accept(TokenType::String);
	return pobj;
}


PObject Parser::parseValue()
{
	if(isCurrTokenType(TokenType::True))
	{
		PObject pobj = std::make_shared<TrueObject>();
		accept(TokenType::True);
		return pobj;
	}
	if(isCurrTokenType(TokenType::False))
	{
		PObject pobj = std::make_shared<FalseObject>();
		accept(TokenType::False);
		return pobj;
	}
	if(isCurrTokenType(TokenType::Null))
	{
		PObject pobj = std::make_shared<NullObject>();
		accept(TokenType::Null);
		return pobj;
	}
	if(isCurrTokenType(TokenType::Int))
	{
		PObject pobj = std::make_shared<IntObject>(currToken.getValue());
		accept(TokenType::Int);
		return pobj;
	}
	if(isCurrTokenType(TokenType::IntFrac))
	{
		PObject pobj = std::make_shared<IntFracObject>(currToken.getValue());
		accept(TokenType::IntFrac);
		return pobj;
	}
	if(isCurrTokenType(TokenType::IntExp))
	{
		PObject pobj = std::make_shared<IntExpObject>(currToken.getValue());
		accept(TokenType::IntExp);
		return pobj;
	}
	if(isCurrTokenType(TokenType::IntFracExp))
	{
		PObject pobj = std::make_shared<IntFracExpObject>(currToken.getValue());
		accept(TokenType::IntFracExp);
		return pobj;
	}
	if(isCurrTokenType(TokenType::String))
	{
		PObject pobj = std::make_shared<StringObject>(currToken.getValue());
		accept(TokenType::String);
		return pobj;
	}
	if(isCurrTokenType(TokenType::LeftCurlyBracket))
	{
		return parseJSON();
	}
	return parseArray();
}


PObject Parser::parseArray()
{
	PObject pobj = std::make_shared<ArrayObject>();
	accept(TokenType::LeftSquareBracket);
	if(!isCurrTokenType(TokenType::RightSquareBracket))
	{
		PObject val = parseValue();
		pobj.get()->addChild(val);
		while(isCurrTokenType(TokenType::Comma))
		{
			accept(TokenType::Comma);
			PObject val = parseValue();
			pobj.get()->addChild(val);
		}
	}
	accept(TokenType::RightSquareBracket);
	return pobj; 
}


PObject Parser::parsePair()
{
	PObject pobj = std::make_shared<PairObject>();
	PObject key = parseKey();
	pobj.get()->addChild(key);
	accept(TokenType::Colon);
	PObject val = parseValue();
	pobj.get()->addChild(val);
	return pobj;
}
