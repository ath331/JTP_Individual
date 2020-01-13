#define _CRT_RAND_S  

#include "InputMG.h"

#include <stdlib.h> 
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

#include <boost/thread.hpp>

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
	unsigned int uNumber = 0U;
	int randomMapSize = 0;
	rand_s(&uNumber);
	randomMapSize = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 3) + 0);
	if (randomMapSize == 0)
		_mapSize = 11;
	else if (randomMapSize == 1)
		_mapSize = 15;
	else if (randomMapSize == 2)
		_mapSize = 19;

	unsigned int uNumber2 = 0U;
	int randomWallRatio = 0;
	rand_s(&uNumber2);
	randomWallRatio = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 50) + 30);
	randomWallRatio = (randomWallRatio / 5) * 5;
	_wallRatio = randomWallRatio;

	unsigned int uNumber3 = 0U;
	int randomItemNum = 0;
	rand_s(&uNumber3);
	//난이도에 따라서 랜덤값 조절
	if (randomMapSize == 0)
		randomItemNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 3) + 0);
	else if (randomMapSize == 1)
		randomItemNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 3) + 5);
	else if (randomMapSize == 2)
		randomItemNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 3) + 7);
	randomItemNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 10) + 1);
	_itemNum = randomItemNum;

	unsigned int uNumber4 = 0U;
	int randEnemyNum = 0;
	rand_s(&uNumber4);
	//난이도에 따라서 랜덤값 조절
	if (randomMapSize == 0)
		randEnemyNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 2) + 1);
	else if (randomMapSize == 1)
		randEnemyNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 2) + 3);
	else if(randomMapSize == 2)
		randEnemyNum = (int)((unsigned int)((double)uNumber / ((double)UINT_MAX + 1.0) * 2) + 5);
	_enemyNum = randEnemyNum;
}

void InputMG::init_number_generator()
{
	static boost::thread_specific_ptr<bool> tls;
	if (!tls.get())
		tls.reset(new bool(false));
	if (!*tls)
	{
		Sleep(0.01);
		*tls = true;
		std::srand(static_cast<unsigned int>(std::time(NULL)));
	}
}