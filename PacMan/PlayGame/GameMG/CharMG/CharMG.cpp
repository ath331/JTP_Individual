#include "CharMG.h"

#include <iostream>

void CharMG::Init(MapField map[][MAX_MAP_SIZE_X])
{
	_CopyArr(map, _map);

	int mapSizeX = sizeof(map[0]) / sizeof(MapField);
	int mapSizeY = sizeof(map) / sizeof(map[0]);

	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	_MakePlayerPos(map, _mapSizeX / 2, (_mapSizeY / 2 + 2));
}
void CharMG::Update()
{

}

void CharMG::InputCharInfo()
{
	std::cout << "Input CharInfo_ speed(float), enemyNum(int)" << std::endl;
	std::cin >> _speed >> _enemyNum;

}
void CharMG::Draw()
{
	for (int y = 1; y < _mapSizeY; y++)
	{
		for (int x = 1; x < _mapSizeX; x++)
		{
			if (_map[y][x] == MapField::PLAYER_START)
				std::cout << "¡ã" << std::endl;
			if (_map[y][x] == MapField::ENEMY)
				std::cout << "¡â" << std::endl;
		}
	}
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