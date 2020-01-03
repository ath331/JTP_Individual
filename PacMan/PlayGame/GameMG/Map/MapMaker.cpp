#include "MapMaker.h"
#include "MapEnum.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

void MapMaker::Init(MapField map[][MAX_MAP_SIZE_Y])
{
	std::srand((unsigned int)time(NULL));

	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			//������(�׵θ�)
			if (x == 0 || y == 0 || x == _mapSizeX - 1 || y == _mapSizeY - 1)
			{
				map[x][y] = MapField::WALL;
			}

			if (map[x][y] == MapField::EMPTY)
			{
				if (_IsChangeWall())
					map[x][y] = MapField::WALL;
			}
		}
	}
}

void MapMaker::_CalculateWallRatio()
{
	float emptyWall = 0.0f;
	emptyWall = (_mapSizeX * _mapSizeY) - _mapSizeX - _mapSizeX - _mapSizeY - _mapSizeY + 4; //�׵θ��� �����ϰ� ������� ������ ���Ѵ� +4�� �𼭸��κ��� �ι������Ƿ� �����ϴ� ��
	_wallNum = (emptyWall / 100) * _wallRatio;
}

bool MapMaker::_IsChangeWall()
{
	if (_wallNum <= 0)
		return false;
	
	else
	{
		int num = rand();
		if (num % 2 == 1)
		{
			_wallNum--;
			return true;
		}
		else
			return false;
	}
}

void MapMaker::InputMapInfo()
{
	std::cout << "Input [MapSize_X],  [MapSize_Y],  [WallRatio(%)] : " << std::endl;
	std::cin >> _mapSizeX >> _mapSizeY >> _wallRatio;
	_CalculateWallRatio();
}

void MapMaker::Draw(MapField map[][MAX_MAP_SIZE_Y])
{
	for (int x = 0; x < MAX_MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAX_MAP_SIZE_Y; y++)
		{
			if (map[x][y] == MapField::EMPTY)
				std::cout << "  ";
			else if(map[x][y] == MapField::WALL)
				std::cout << "��";

		}
		std::cout << std::endl;
	}
}