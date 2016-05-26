#include <iostream>
#include <fstream>
#include "Source.h"
#include "Lexer.h"
#include "Parser.h"


int main()
{
	Parser parser("../src/tests/JSON.json");
	PObject pobj = parser.parse();
	pobj.get()->print();
	return 0;
}
