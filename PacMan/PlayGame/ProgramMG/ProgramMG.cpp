#include "ProgramMG.h"

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
	fstream fs("GameResult.csv", ios::out | ios::app);

	if (fs.is_open())
	{
		cout << "File Open" << endl;
		fs <<"\n"<< _mapSize << ","
			<< _wallRatio << "," << _itemNum << ","
			<< _enemyNum;

		fs.close();
	}
	else
		exit(1);
}