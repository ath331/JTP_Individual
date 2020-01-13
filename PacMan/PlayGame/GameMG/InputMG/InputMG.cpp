#include "InputMG.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

void InputMG::SetGameInfo()
{
	_InputMapSize();
	_InputGameInfo();
	_InputEnemyNum();
}


int InputMG::GetMapSize()
{
	return _mapSize;
}
int InputMG::GetWallRatio()
{
	return _wallRatio;
}
int InputMG::GetItemNum()
{
	return _itemNum;
}
int InputMG::GetEnemyNum()
{
	return _enemyNum;
}

bool InputMG::IsGameOver()
{
	return _gameOver;
}
bool InputMG::IsGameClear()
{
	return _gameClear;
}
void InputMG::SetGameOver(bool state)
{
	_gameOver = state;
}
void InputMG::SetGameClear(bool state)
{
	_gameClear = state;
}

void InputMG::_InputMapSize()
{
	while (true)
	{
		std::cout << "Input MapSize_ (11, 15, 19) : ";
		std::cin >> _mapSize;
		if (_mapSize == 11 || _mapSize == 15 || _mapSize == 19)
			break;
	}
}

void InputMG::_InputGameInfo()
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
void InputMG::_InputEnemyNum()
{
	while (true)
	{
		std::cout << "Input CharInfo_ enemyNum(min 0 ~ max 5) : ";
		std::cin >> _enemyNum;
		if (_enemyNum >= 0 && _enemyNum <= 5)
			break;
	}
}

void InputMG::SetRandomParameter()
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

