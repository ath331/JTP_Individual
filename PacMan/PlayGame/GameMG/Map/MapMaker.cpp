#include "MapMaker.h"
#include "MapEnum.h"
#include "Load/LoadMaker.h"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

void MapMaker::Init(MapField map[][MAX_MAP_SIZE_Y])
{
	_CopyArr(map, _map);

	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			//벽생성(테두리)
			if (x == 0 || y == 0 || x == _mapSizeX - 1 || y == _mapSizeY - 1)
			{
				_map[x][y] = MapField::WALL;
			}
		}
	}

	_MakePotal();
	_MakePrison();
	_MakeLoad();
	_MakeFieldWall();
}

void MapMaker::_CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y])
{
	MapField* p1, * endp1;
	MapField* p2;
	p1 = &array1[0][0];
	p2 = &array2[0][0];
	endp1 = &array1[MAX_MAP_SIZE_X - 1][MAX_MAP_SIZE_X - 1];
	while (p1 <= endp1)
	{
		*p2 = *p1;
		p1++; p2++;
	}
}

void MapMaker::_MakePrison()
{
	int centerX = _mapSizeX / 2;
	int centerY = _mapSizeY / 2;

	{
		//빈공간 생성
		_map[centerX][centerY] = MapField::PRISON_ZONE;
		_map[centerX - 1][centerY] = MapField::PRISON_ZONE;
		_map[centerX][centerY + 1] = MapField::PRISON_ZONE;
		_map[centerX][centerY - 1] = MapField::PRISON_ZONE;
	}
	{
		//감옥 벽생성
		_map[centerX][centerY + 2] = MapField::PRISON_WALL;
		_map[centerX][centerY - 2] = MapField::PRISON_WALL;
		_map[centerX + 1][centerY] = MapField::PRISON_WALL;

		_map[centerX + 1][centerY + 1] = MapField::PRISON_WALL;
		_map[centerX - 1][centerY + 1] = MapField::PRISON_WALL;
		_map[centerX + 1][centerY - 2] = MapField::PRISON_WALL;
		_map[centerX + 1][centerY + 2] = MapField::PRISON_WALL;

		_map[centerX + 1][centerY - 1] = MapField::PRISON_WALL;
		_map[centerX - 1][centerY + 2] = MapField::PRISON_WALL;
		_map[centerX - 1][centerY - 1] = MapField::PRISON_WALL;
		_map[centerX - 1][centerY - 2] = MapField::PRISON_WALL;
	}
	{
		//감옥 주위에 길생성

	}
}

void MapMaker::_CalculateWallRatio()
{
	_emptyWall = (_mapSizeX * _mapSizeY) - _mapSizeX - _mapSizeX - _mapSizeY - _mapSizeY + 4; //테두리를 제외하고 빈공간의 개수만 구한다 +4는 모서리부분이 두번빠지므로 보정하는 값
	_wallNum = (_emptyWall / 100) * _wallRatio;
	if (_wallNum <= 0)
		_wallNum = 1;
}

void MapMaker::_MakePotal()
{
	int centerY = _mapSizeY / 2;

	for (int i = 0; i < 2; i++)
	{
		_map[centerY + i][_mapSizeX - 1] = MapField::PORTAL;
		_map[centerY + i][0] = MapField::PORTAL;
	}
}

void MapMaker::_MakeLoad()
{
	int prisonLoadStartX = (_mapSizeX / 2) - 3;
	int prisonLoadStartY = (_mapSizeY / 2) - 2;
	int prisonLoadEndX = (_mapSizeX / 2) + 4;
	int prisonLoadEndY = (_mapSizeY / 2) + 3;

	for (int y = prisonLoadStartY; y < prisonLoadEndY; y++)
	{
		for (int x = prisonLoadStartX; x < prisonLoadEndX; x++)
		{
			if (_map[y][x] == MapField::EMPTY)
				_map[y][x] = MapField::LOAD;
		}

	}
	//boost::thread_group tg;
	//LoadMaker* _loadMaker[4];
	//for (int i = 1; i <= 4; i++) //상하좌우 4개의 스레드 필요
	//{
	//	_loadMaker[i - 1] = new LoadMaker;
	//	_loadMaker[i-1]->Init(&_wallNum, (EnumLoad::LoadWay)i);
	//	tg.create_thread(boost::bind(&LoadMaker::MakeLoad, _loadMaker));
	//}
	//tg.join_all();
}

void MapMaker::_MakeFieldWall()
{
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			//벽생성(테두리)
			if (_map[y][x] == MapField::EMPTY)
			{
				_map[y][x] = MapField::WALL;
			}
		}
	}
}

void MapMaker::InputMapInfo()
{
	std::cout << "MAX SIZE = " << MAX_MAP_SIZE_X << std::endl;
	std::cout << "Input MapSize_X,  MapSize_Y,  WallRatio(%) : " << std::endl;
	std::cin >> _mapSizeX >> _mapSizeY >> _wallRatio;
	_CalculateWallRatio();
}

void MapMaker::Draw()
{
	for (int x = 0; x < MAX_MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAX_MAP_SIZE_Y; y++)
		{
			if (_map[x][y] == MapField::EMPTY || _map[x][y] == MapField::PRISON_ZONE)
				std::cout << "  ";
			else if (_map[x][y] == MapField::PORTAL || _map[x][y] == MapField::LOAD)
				std::cout << "  ";
			else if (_map[x][y] == MapField::WALL || _map[x][y] == MapField::PRISON_WALL)
				std::cout << "■";
		}
		std::cout << std::endl;
	}
}