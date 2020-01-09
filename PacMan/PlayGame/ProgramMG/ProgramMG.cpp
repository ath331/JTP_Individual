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
