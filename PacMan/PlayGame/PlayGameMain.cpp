#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <process.h>

#include "ConsoleLogger/ConsoleLogger.h"

int main()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	int sum = 0;
	CConsoleLogger secondConsole;
	secondConsole.Create("secondConsole");
	secondConsole.printf("EndKey : Enter\n");

	while (sum < 100)
	{
		std::string a = boost::lexical_cast<std::string>(sum);
		secondConsole.printf(a.c_str());
		sum++;
	}

	while (1)
	{
		std::cout << "aa" << std::endl;
	}
}