#include "ProgramMG.h"
#include "../tinyxml/tinyxml.h"

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

ProgramMG* ProgramMG::_instance = nullptr;

void ProgramMG::SetMapSize(int mapSize)
{
	_mapSize = mapSize;
}
void ProgramMG::SetGameInfo(int wallRatio, int itemNum)
{
	_wallRatio = wallRatio;
	_itemNum = itemNum;
}
void ProgramMG::SetEnemyNum(int enemyNum)
{
	_enemyNum = enemyNum;
}

void ProgramMG::ParsingGameResult()
{
	LockGuard pasingLockGuard(pasingLock);

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
	LockGuard gameEndCheckLockGuard(gameEndCheckLock);
	return _gameOver;
}
bool ProgramMG::IsGameClear()
{
	LockGuard gameEndCheckLockGuard(gameEndCheckLock);
	return _gameClear;
}
void ProgramMG::SetGameOver(bool state)
{
	LockGuard gameEndCheckLockGuard(gameEndCheckLock);
	_gameOver = state;
}
void ProgramMG::SetGameClear(bool state)
{
	LockGuard gameEndCheckLockGuard(gameEndCheckLock);
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

void ProgramMG::InputMapSize()
{
	while (true)
	{
		std::cout << "Input MapSize_ (11, 19, 23) : ";
		std::cin >> _mapSize;
		if (_mapSize == 11 || _mapSize == 19 || _mapSize == 23)
			break;
	}
}
void ProgramMG::InputGameInfo()
{
	while (true)
	{
		std::cout << "Input MapInfo_ WallRatio(min 0 ~ max 100), ItemNum(min 0 ~ max 20) : ";
		std::cin >> _wallRatio >> _itemNum;
		if ((_wallRatio >= 0 || _wallRatio <= 100) && (_itemNum >= 0 || _itemNum <= 20))
			break;
	}
}
void ProgramMG::InputEnemyNum()
{
	while (_enemyNum < 1 || _enemyNum > 5)
	{
		std::cout << "Input CharInfo_ enemyNum(min 1 ~ max 5) : ";
		std::cin >> _enemyNum;
	}
}