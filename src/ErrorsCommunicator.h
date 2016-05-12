#ifndef ERRORSCOMMUNICATOR_H
#define ERRORSCOMMUNICATOR_H

#include "structs/TextPosition.h"
#include <string>
#include <sstream>
#include <iostream>

class ErrorsCommunicator
{
	ErrorsCommunicator();
public:
	~ErrorsCommunicator();
	static void communicateAndExit(TextPosition position, std::string expected, std::string found);
};

#endif

