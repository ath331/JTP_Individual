#include "CharMG.h"
#include "Character/Character.h"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

void CharMG::InputCharInfo()
{
	std::cout << "Input CharInfo_ speed(float), enemyNum(int)" << std::endl;
	std::cin >> _speed >> _enemyNum;
}

void CharMG::Init(MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY)
{
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	_MakePlayerPos(map, _mapSizeX / 2, (_mapSizeY / 2 + 2));

	for (int i = 0; i < _enemyNum; i++)
	{
		Character* enemyCharacter = new Character;
		charVec.push_back(enemyCharacter);
	}
}

void CharMG::Update()
{
	//charVec의 원소들에서 움직이는 함수 실행
}

void CharMG::_MakePlayerPos(MapField map[][MAX_MAP_SIZE_X], int posX, int posY)
{
	map[posX][posY] = MapField::PLAYER_;
	Character* enemyCharacter = new Character;
	charVec.push_back(enemyCharacter);
}