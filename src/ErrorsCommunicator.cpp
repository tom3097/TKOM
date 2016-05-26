#include "ErrorsCommunicator.h"


ErrorsCommunicator::ErrorsCommunicator()
{
}


ErrorsCommunicator::~ErrorsCommunicator()
{
}


void ErrorsCommunicator::communicateAndExit(std::string module, TextPosition position, 
	std::string expected, std::string found)
{
	std::stringstream buf;
	buf << "[ " << module << " ] ";
	buf << "Error in line " << position.getLineNumber() << " char " << position.getCharNumber() << ".\n";
	buf << "Expected: " << expected << ". Found: " << found << ".\n";
	std::cerr << buf.str();
	std::exit(-1);
}
