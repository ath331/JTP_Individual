#include "CharMG.h"

#include <iostream>

void CharMG::Init(MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY)
{
	_CopyArr(map, _map);

	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	_MakePlayerPos(_map, _mapSizeX / 2, (_mapSizeY / 2 + 2));
}
void CharMG::Update()
{

}

void CharMG::InputCharInfo()
{
	std::cout << "Input CharInfo_ speed(float), enemyNum(int)" << std::endl;
	std::cin >> _speed >> _enemyNum;

}

void CharMG::_MakePlayerPos(MapField map[][MAX_MAP_SIZE_X], int posX, int posY)
{
	map[posY][posX] = MapField::PLAYER_START;
}

void CharMG::_CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X])
{
	MapField* p1 = nullptr, * endp1 = nullptr;
	MapField* p2 = nullptr;
	p1 = &array1[0][0];
	p2 = &array2[0][0];
	endp1 = &array1[MAX_MAP_SIZE_X - 1][MAX_MAP_SIZE_X - 1];
	while (p1 <= endp1)
	{
		*p2 = *p1;
		p1++; p2++;
	}
}