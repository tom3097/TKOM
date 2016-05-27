#include <iostream>
#include <fstream>
#include "Source.h"
#include "Lexer.h"
#include "Parser.h"


int main()
{
	Parser parser("../src/tests/JSON.json");
	PObject pobj = parser.parseAll();
	pobj.get()->print();
	std::cout << "____Whoops! Cant find any json____" << std::endl;
	parser.nextJSON().get()->print();

	parser.goToBegin();
	std::cout << "______________Pierwszy____________" << std::endl;
	parser.nextJSON().get()->print();
	std::cout << "_______________Drugi______________" << std::endl;
	parser.nextJSON().get()->print();

	for(int i = 0; i < 100; ++i)
		parser.nextJSON();

	std::cout << "____Whoops! Cant find any json____" << std::endl;
	parser.nextJSON().get()->print();
	std::cout << "____Whoops! Cant find any json____" << std::endl;
	parser.nextJSON().get()->print();
	return 0;
}
