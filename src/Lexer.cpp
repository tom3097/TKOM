#include "Lexer.h"


Lexer::Lexer(std::string JSONpath)
{
	source.setJSON(JSONpath);
}

Lexer::Lexer()
{
}

Lexer::~Lexer()
{
}

void Lexer::setJSON(std::string JSONpath)
{
	source.setJSON(JSONpath);
}


void Lexer::goToBegin()
{
	source.goToBegin();
}


void Lexer::skipWhitespaces()
{
	while (!source.getFoundEOF() && isspace(source.currentChar()))
		source.nextChar();
}


Lexer::checkResult Lexer::EOFToken()
{
	if (source.getFoundEOF())
		return std::make_pair(true, Token("EndOfFile", TokenType::EndOfFile, source.getPosition()));
	return std::make_pair(false, Token());
}


Lexer::checkResult Lexer::SingleCharToken()
{
	Token token;
	switch (source.currentChar())
	{
	case '{': token = Token("{", TokenType::LeftCurlyBracket, source.getPosition()); source.nextChar();
		return std::make_pair(true, token);
	case '}': token = Token("}", TokenType::RightCurlyBracket, source.getPosition()); source.nextChar();
		return std::make_pair(true, token);
	case '[': token = Token("[", TokenType::LeftSquareBracket, source.getPosition()); source.nextChar();
		return std::make_pair(true, token);
	case ']': token = Token("]", TokenType::RightSquareBracket, source.getPosition()); source.nextChar();
		return std::make_pair(true, token);
	case ':': token = Token(":", TokenType::Colon, source.getPosition()); source.nextChar();
		return std::make_pair(true, token);
	case ',': token = Token(",", TokenType::Comma, source.getPosition()); source.nextChar();
		return std::make_pair(true, token);
	default:
		return std::make_pair(false, token);
	}
}


Lexer::checkResult Lexer::NonQuotWordToken()
{
	Token token;
	token.setPosition(source.getPosition());
	std::string value;
	if (isalpha(source.currentChar()))
	{
		do
		{
			value.push_back(source.currentChar());
			source.nextChar();
		} while (!source.getFoundEOF() && isalpha(source.currentChar()));
		token.setValue(value);
		if (value == "true")
		{
			token.setType(TokenType::True);
			return std::make_pair(true, token);
		}
		if (value == "false")
		{
			token.setType(TokenType::False);
			return std::make_pair(true, token);
		}
		if (value == "null")
		{
			token.setType(TokenType::Null);
			return std::make_pair(true, token);
		}
		ErrorsCommunicator::communicateAndExit("LEXER", token.getPosition(), "'true' or 'false' or 'null'", value);
	}
	return std::make_pair(false, token);
}


std::string Lexer::getExpPart()
{
	std::string value;
	value.push_back(source.currentChar());
	source.nextChar();
	if (source.getFoundEOF())
		ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "'+' or '-' or digit", "End Of File");
	if (source.currentChar() == '+' || source.currentChar() == '-')
	{
		value.push_back(source.currentChar());
		source.nextChar();
		if (source.getFoundEOF())
			ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "digit", "End Of File");
	}
	if (isdigit(source.currentChar()))
	{
		do
		{
			value.push_back(source.currentChar());
			source.nextChar();
		} while (!source.getFoundEOF() && isdigit(source.currentChar()));
		return value;
	}
	std::string found;
	found.push_back(source.currentChar());
	ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "digit", found);
}


std::string Lexer::getDotPart()
{
	std::string value;
	value.push_back(source.currentChar());
	source.nextChar();
	if (source.getFoundEOF())
		ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "digit", "End Of File");
	if (isdigit(source.currentChar()))
	{
		do
		{
			value.push_back(source.currentChar());
			source.nextChar();
		} while (!source.getFoundEOF() && isdigit(source.currentChar()));
		return value;
	}
	std::string found;
	found.push_back(source.currentChar());
	ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "digit", found);
}


Lexer::checkResult Lexer::NumberToken()
{
	Token token;
	token.setPosition(source.getPosition());
	std::string value;
	if (isdigit(source.currentChar()) || source.currentChar() == '-')
	{
		if(source.currentChar() == '-')
		{
			value.push_back(source.currentChar());
			source.nextChar();
		}

		if (isdigit(source.currentChar()))
		{
			do
			{
				value.push_back(source.currentChar());
				source.nextChar();
			} while (!source.getFoundEOF() && isdigit(source.currentChar()));
			if (source.getFoundEOF())
			{
				token.setValue(value);
				token.setType(TokenType::Int);
				return std::make_pair(true, token);
			}
			if (source.currentChar() == 'e' || source.currentChar() == 'E')
			{
				value = value + getExpPart();
				token.setValue(value);
				token.setType(TokenType::IntExp);
				return std::make_pair(true, token);
			}
			if (source.currentChar() == '.')
			{
				value = value + getDotPart();
				if (source.getFoundEOF())
				{
					token.setValue(value);
					token.setType(TokenType::IntFrac);
					return std::make_pair(true, token);
				}
				if (source.currentChar() == 'e' || source.currentChar() == 'E')
				{
					value = value + getExpPart();
					token.setValue(value);
					token.setType(TokenType::IntFracExp);
					return std::make_pair(true, token);
				}
				token.setValue(value);
				token.setType(TokenType::IntFrac);
				return std::make_pair(true, token);
			}
			token.setValue(value);
			token.setType(TokenType::Int);
			return std::make_pair(true, token);
		}
		else
		{
			std::string found;
			found.push_back(source.currentChar());
			ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "digit", found);
		}
	}
	return std::make_pair(false, token);
}


Lexer::checkResult Lexer::QuotWordToken()
{
	Token token;
	token.setPosition(source.getPosition());
	std::string value;
	std::array<char,9> arr{ {'"','\\','/','b','f','n','r','t','u'} };
	if (source.currentChar() == '"')
	{
		bool backslashFound = false;
		do
		{
			if(!backslashFound && source.currentChar() == '\\')
				backslashFound = true;
			else if (backslashFound && std::find(arr.begin(), arr.end(), source.currentChar()) != arr.end())
			{
				backslashFound = false;
				if(source.currentChar() == 'u')
				{
					value.push_back(source.currentChar());
					source.nextChar();
					value = value + check4Get3HexDigits();
				}
			}
			else if(backslashFound)
			{
				std::string expected = "'\"'' or '\\'' or '/'' or 'b' or 'f' or 'n' or 'r' or 't' or 'u'";
				std::string found;
				found.push_back(source.currentChar());
				ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), expected, found);
			}
			value.push_back(source.currentChar());
			source.nextChar();
		} while (!source.getFoundEOF() && (source.currentChar() != '"' || backslashFound));
		if (source.getFoundEOF() && !backslashFound)
			ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "char", "End Of File");
		if (source.getFoundEOF() && backslashFound)
		{
			std::string expected = "'\"'' or '\\'' or '/'' or 'b' or 'f' or 'n' or 'r' or 't' or 'u'";
			ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), expected, "End Of File");
		}
		value.push_back(source.currentChar());
		source.nextChar();
		token.setValue(value);
		token.setType(TokenType::String);
		return std::make_pair(true, token);
	}
	return std::make_pair(false, token);
}


std::string Lexer::check4Get3HexDigits()
{
	std::string value;
	std::array<char,12> arr{ {'A','B','C','D','E','F','a','b','c','d','e','f'} };
	for(int i = 0; i < 3; ++i)
	{
		if (source.getFoundEOF())
			ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "hexadecimal digit", "End Of File");
		if(!isdigit(source.currentChar()) && std::find(arr.begin(), arr.end(), source.currentChar()) == arr.end())
		{
			std::string found;
			found.push_back(source.currentChar());
			ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "hexadecimal digit", found);
		}
		value.push_back(source.currentChar());
		source.nextChar();
	}
	if (source.getFoundEOF())
		ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "hexadecimal digit", "End Of File");
	if(!isdigit(source.currentChar()) && std::find(arr.begin(), arr.end(), source.currentChar()) == arr.end())
	{
		std::string found;
		found.push_back(source.currentChar());
		ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), "hexadecimal digit", found);
	}
	return value;
}


Token Lexer::nextToken()
{
	checkResult result;
	skipWhitespaces();
	result = EOFToken();
	if (result.first)
		return result.second;
	result = SingleCharToken();
	if (result.first)
		return result.second;
	result = NonQuotWordToken();
	if (result.first)
		return result.second;
	result = QuotWordToken();
	if (result.first)
		return result.second;
	result = NumberToken();
	if (result.first)
		return result.second;
	std::string expected = "End Of File or '{' or '}' or '[' or ']' or ':' or ',' or \" or \" or alpha or digit";
	std::string found;
	found.push_back(source.currentChar());
	ErrorsCommunicator::communicateAndExit("LEXER", source.getPosition(), expected, found);
}
