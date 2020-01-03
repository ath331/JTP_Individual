#include "MapMaker.h"
#include "MapEnum.h"
#include "Load/LoadMaker.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

void MapMaker::Init(MapField map[][MAX_MAP_SIZE_Y])
{
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

	//_MakeLoad();
}

bool MapMaker::_IsChangeWall()
{
	if (_wallNum <= 0)
		return false;

	else
	{
		int num = rand();
		if (num % 4 == 1)
		{
			_wallNum--;
			return true;
		}
		else
			return false;
	}
}

void MapMaker::_CalculateWallRatio()
{
	emptyWall = (_mapSizeX * _mapSizeY) - _mapSizeX - _mapSizeX - _mapSizeY - _mapSizeY + 4; //�׵θ��� �����ϰ� ������� ������ ���Ѵ� +4�� �𼭸��κ��� �ι������Ƿ� �����ϴ� ��
	_wallNum = (emptyWall / 100) * _wallRatio;
	if (_wallNum <= 0)
		_wallNum = 1;
}

void MapMaker::_MakeLoad()
{
	boost::thread_group tg;
	//LoadMaker* _loadMaker[4];
	//for (int i = 1; i <= 4; i++) //�����¿� 4���� ������ �ʿ�
	//{
	//	_loadMaker[i - 1] = new LoadMaker;
	//	_loadMaker[i-1]->Init(&_wallNum, (EnumLoad::LoadWay)i);
	//	tg.create_thread(boost::bind(&LoadMaker::MakeLoad, _loadMaker));
	//}
	//tg.join_all();
}

void MapMaker::InputMapInfo()
{
	std::cout << "MAX SIZE = 25" << std::endl;
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
			else if (map[x][y] == MapField::WALL)
				std::cout << "��";
		}
		std::cout << std::endl;
	}
}