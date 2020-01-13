#include "ProgramMG.h"
#include "../tinyxml/tinyxml.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

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

	if (_mode == 2)
	{
		_InputMapSize();
		_InputGameInfo();
		_InputEnemyNum();
	}

}

void ProgramMG::SetRandomParameter()
{
	srand((unsigned int)time(NULL));

	int randMapSize = rand() % 3;

	if (randMapSize == 0)
		_mapSize = 11;
	else if (randMapSize == 1)
		_mapSize = 15;
	else if (randMapSize == 2)
		_mapSize = 19;

	int randWallRatioNum = ((rand() % 10) + 1) * 10;
	_wallRatio = randWallRatioNum;

	int randItemNum = rand() % 21;
	_itemNum = randItemNum;

	int randEnemyNum = (rand() % 5) + 1;
	_enemyNum = randEnemyNum;
}

int ProgramMG::GetMode()
{
	return _mode;
}
void ProgramMG::ParsingGameResult()
{
	LockGuard pasingLockGuard(_writeDataLock);

	fstream fs("GameResult.csv", ios::out | ios::app);

	if (fs.is_open())
	{
		cout << "File Open" << endl;
		if (_gameOver)
			fs << "\n" << _mapSize << ","
			<< _wallRatio << "," << _itemNum << ","
			<< _enemyNum << "," << true << "," << false;

		else if (_gameClear)
			fs << "\n" << _mapSize << ","
			<< _wallRatio << "," << _itemNum << ","
			<< _enemyNum << "," << false << "," << true;

		fs.close();
	}

	else
		exit(1);
}
bool ProgramMG::IsGameOver()
{
	LockGuard gameEndCheckLockGuard(_gameEndCheckLock);
	return _gameOver;
}
bool ProgramMG::IsGameClear()
{
	LockGuard gameEndCheckLockGuard(_gameEndCheckLock);
	return _gameClear;
}
void ProgramMG::SetGameOver(bool state)
{
	LockGuard gameEndCheckLockGuard(_gameEndCheckLock);
	_gameOver = state;
}
void ProgramMG::SetGameClear(bool state)
{
	LockGuard gameEndCheckLockGuard(_gameEndCheckLock);
	_gameClear = state;
}
int ProgramMG::GetMapSize()
{
	return _mapSize;
}
int ProgramMG::GetWallRatio()
{
	return _wallRatio;
}
int ProgramMG::GetItemNum()
{
	return _itemNum;
}
int ProgramMG::GetEnemyNum()
{
	return _enemyNum;
}

void ProgramMG::_InputMapSize()
{
	while (true)
	{
		std::cout << "Input MapSize_ (11, 15, 19) : ";
		std::cin >> _mapSize;
		if (_mapSize == 11 || _mapSize == 15 || _mapSize == 19)
			break;
	}
}
void ProgramMG::_InputGameInfo()
{
	while (true)
	{
		std::cout << "Input MapInfo_ WallRatio(min 0 ~ max 100) : ";
		std::cin >> _wallRatio;
		if (_wallRatio >= 0 && _wallRatio <= 100)
			break;
	}
	while (true)
	{
		std::cout << "Input MapInfo_ ItemNum(min 0 ~ max 20) : ";
		std::cin >> _itemNum;
		if (_itemNum >= 0 && _itemNum <= 20)
			break;
	}
}
void ProgramMG::_InputEnemyNum()
{
	while (true)
	{
		std::cout << "Input CharInfo_ enemyNum(min 0 ~ max 5) : ";
		std::cin >> _enemyNum;
		if (_enemyNum >= 0 && _enemyNum <= 5)
			break;
	}
}