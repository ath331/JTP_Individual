#include "LoadMaker.h"

#include <iostream>

void LoadMaker::Init(const int wallNum, const int mapSizeX, const int mapSizeY)
{
	_wallNum = wallNum;
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;
}

void LoadMaker::MakeLoad(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	//정사각형의 가로줄 세팅
	int startX = 1;
	int endX = _mapSizeX - 1;
	for (int y = 1; y < _mapSizeY - 1; y += 2)
	{
		for (int x = startX; x < endX; x)
		{
			if (map[y][x] == EnumMap::MapField::EMPTY)
				map[y][x] = EnumMap::MapField::LOAD;
			x++;
		}

		if (y < _mapSizeY / 2)
		{
			endX -= 2;
			startX += 2;
		}
		else if (y >= _mapSizeY / 2)
		{
			endX += 2;
			startX -= 2;
		}
	}

	//정사각형의 세로줄 세팅
	startX = 1;
	endX = _mapSizeX - 1;
	for (int y = 1; y < _mapSizeY - 1; y += 2)
	{
		for (int x = startX; x < endX; x)
		{
			if (map[x][y] == EnumMap::MapField::EMPTY)
				map[x][y] = EnumMap::MapField::LOAD;
			x++;
		}

		if (y < _mapSizeY / 2)
		{
			endX -= 2;
			startX += 2;
		}
		else if (y >= _mapSizeY / 2)
		{
			endX += 2;
			startX -= 2;
		}
	}
}

void LoadMaker::_MakeAdditionalLoad(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{

}

