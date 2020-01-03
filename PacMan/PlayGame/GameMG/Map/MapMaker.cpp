#include "MapMaker.h"
#include "MapEnum.h"

#include <iostream>

void MapMaker::Init(EnumMap::MapField map[][MAX_MAP_SIZE_Y])
{
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			//벽생성(테두리)
			if (x == 0 || y == 0 || x == _mapSizeX - 1 || y == _mapSizeY - 1)
			{
				map[x][y] = EnumMap::MapField::WALL;
			}
		}
	}
}

void MapMaker::InputMapSize()
{
	std::cout << "Input MapSize_X,  MapSize_Y : " << std::endl;
	std::cin >> _mapSizeX >> _mapSizeY;
}

void MapMaker::Draw(EnumMap::MapField map[][MAX_MAP_SIZE_Y])
{
	for (int x = 0; x < MAX_MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAX_MAP_SIZE_Y; y++)
		{
			if (map[x][y] == EnumMap::MapField::EMPTY)
				std::cout << "  ";
			else if(map[x][y] == EnumMap::MapField::WALL)
				std::cout << "■";

		}
		std::cout << std::endl;
	}
}