#include "Lexer.h"


Lexer::Lexer(std::string JSONpath)
{
	source.setJSON(JSONpath);
}


Lexer::~Lexer()
{
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
		ErrorsCommunicator::communicateAndExit(token.getPosition(), "'true' or 'false' or 'null'", value);
	}
	return std::make_pair(false, token);
}


Lexer::checkResult Lexer::NumberToken()
{
	Token token;
	token.setPosition(source.getPosition());
	std::string value;
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
			value.push_back(source.currentChar());
			source.nextChar();
			if (source.getFoundEOF())
				ErrorsCommunicator::communicateAndExit(source.getPosition(), "'+' or '-' or digit", "End Of File");
			if (source.currentChar() == '+' || source.currentChar() == '-')
			{
				value.push_back(source.currentChar());
				source.nextChar();
				if (source.getFoundEOF())
					ErrorsCommunicator::communicateAndExit(source.getPosition(), "digit", "End Of File");
			}
			if (isdigit(source.currentChar()))
			{
				do
				{
					value.push_back(source.currentChar());
					source.nextChar();
				} while (!source.getFoundEOF() && isdigit(source.currentChar()));
				token.setValue(value);
				token.setType(TokenType::IntExp);
				return std::make_pair(true, token);
			}
			std::string found;
			found.push_back(source.currentChar());
			ErrorsCommunicator::communicateAndExit(source.getPosition(), "digit", found);
		}
		if (source.currentChar() == '.')
		{
			value.push_back(source.currentChar());
			source.nextChar();
			if (source.getFoundEOF())
				ErrorsCommunicator::communicateAndExit(source.getPosition(), "digit", "End Of File");
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
					token.setType(TokenType::IntFrac);
					return std::make_pair(true, token);
				}
				if (source.currentChar() == 'e' || source.currentChar() == 'E')
				{
					value.push_back(source.currentChar());
					source.nextChar();
					if (source.getFoundEOF())
						ErrorsCommunicator::communicateAndExit(source.getPosition(), "'+' or '-' or digit", "End Of File");
					if (source.currentChar() == '+' || source.currentChar() == '-')
					{
						value.push_back(source.currentChar());
						source.nextChar();
						if (source.getFoundEOF())
							ErrorsCommunicator::communicateAndExit(source.getPosition(), "digit", "End Of File");
					}
					if (isdigit(source.currentChar()))
					{
						do
						{
							value.push_back(source.currentChar());
							source.nextChar();
						} while (!source.getFoundEOF() && isdigit(source.currentChar()));
						token.setValue(value);
						token.setType(TokenType::IntFracExp);
						return std::make_pair(true, token);
					}
					std::string found;
					found.push_back(source.currentChar());
					ErrorsCommunicator::communicateAndExit(source.getPosition(), "digit", found);
				}
				token.setValue(value);
				token.setType(TokenType::IntFrac);
				return std::make_pair(true, token);
			}
			std::string found;
			found.push_back(source.currentChar());
			ErrorsCommunicator::communicateAndExit(source.getPosition(), "digit", found);
		}
		token.setValue(value);
		token.setType(TokenType::Int);
		return std::make_pair(true, token);
	}
	return std::make_pair(false, token);
}


Lexer::checkResult Lexer::QuotWordToken()
{
	Token token;
	token.setPosition(source.getPosition());
	std::string value;
	if (source.currentChar() == '"')
	{
		do
		{
			value.push_back(source.currentChar());
			source.nextChar();
		} while (!source.getFoundEOF() && source.currentChar() != '"');
		if (source.getFoundEOF())
			ErrorsCommunicator::communicateAndExit(source.getPosition(), "char or \"", "End Of File");
		value.push_back(source.currentChar());
		source.nextChar();
		token.setValue(value);
		token.setType(TokenType::String);
		return std::make_pair(true, token);
	}
	return std::make_pair(false, token);
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
	ErrorsCommunicator::communicateAndExit(source.getPosition(), expected, found);
}
