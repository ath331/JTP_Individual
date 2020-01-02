#include <iostream>

#include "ConsoleLogger/ConsoleLogger.h"

int main()
{
	std::cout << "Hi" << std::endl;
	CConsoleLogger secondConsole;
	secondConsole.Create("secondConsole");
	secondConsole.printf("EndKey : Enter\n");
}