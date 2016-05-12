#include <iostream>
#include <fstream>
#include "Source.h"
#include "Lexer.h"


int main()
{
	Lexer lexer("../src/tests/JSON.json");
	std::ofstream writer;
	writer.open("../src/tests/JSON_tokens.out");
	Token token;
	while (true)
	{
		token = lexer.nextToken();
		std::cout << token.toString() << std::endl;
		writer << token.toString() << std::endl;
		if (token.getType() == TokenType::EndOfFile) break;
	}
	writer.close();
	return 0;
}
