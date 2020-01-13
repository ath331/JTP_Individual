#include "ProgramMG.h"
#include "../tinyxml/tinyxml.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <Windows.h>

using namespace std;

ProgramMG* volatile ProgramMG::_instance = nullptr;
Lock ProgramMG::_dclpLock;

void ProgramMG::SelectMode()
{
	while (true)
	{
		cout << "Select Mode : (1. Auto Parameters, 2. Input Parameters )";
		cin >> _mode;
		if (_mode == 1 || _mode == 2)
			break;
	}
}

int ProgramMG::GetMode()
{
	return _mode;
}

void ProgramMG::ParsingGameResult(int mapSize, int wallRatio, int itemNum, int enemyNum, bool gameClear)
{
	LockGuard pasingLockGuard(_writeDataLock);
	fstream fs("GameResult.csv", ios::out | ios::app);

	if (fs.is_open())
	{
		fs << "\n" << mapSize << ","
			<< wallRatio << "," << itemNum << ","
			<< enemyNum << "," << !gameClear << "," << gameClear;

		fs.close();
	}
	else
		std::cout << "File Open error" << std::endl;
}