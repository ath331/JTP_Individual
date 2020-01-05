#include "MapMaker.h"
#include "MapEnum.h"

#include <iostream>

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

	_MakeItem();
}

void MapMaker::_CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y])
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
}

void MapMaker::_MakePotal()
{
	int centerY = _mapSizeY / 2;

	for (int i = 0; i < 2; i++)
	{
		_map[centerY - i][_mapSizeX - 1] = MapField::PORTAL;
		_map[centerY - i][0] = MapField::PORTAL;
		if (_mapSizeY % 2 == 1)
		{
			_map[centerY + i][_mapSizeX - 1] = MapField::PORTAL;
			_map[centerY + i][0] = MapField::PORTAL;
		}
	}
}

void MapMaker::_MakeLoad()
{
	int prisonLoadStartX = (_mapSizeX / 2) - 3;
	int prisonLoadStartY = (_mapSizeY / 2) - 2;
	int prisonLoadEndX = (_mapSizeX / 2) + 4;
	int prisonLoadEndY = (_mapSizeY / 2) + 3;

	//감옥주위 길생성(필수)
	for (int y = prisonLoadStartY; y < prisonLoadEndY; y++)
	{
		for (int x = prisonLoadStartX; x < prisonLoadEndX; x++)
		{
			if (_map[y][x] == MapField::EMPTY)
				_map[y][x] = MapField::LOAD;
		}
	}

	_loadMaker.Init(_wallRatio,_mapSizeX,_mapSizeY);
	_loadMaker.MakeLoad(_map);
}

void MapMaker::_MakeFieldWall()
{
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			//벽생성(남은 EMPTY는 모두 WALL이다)
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
	std::cout << "Input MapSize_X,  MapSize_Y,  WallRatio(%), ItemNum : " << std::endl;
	std::cin >> _mapSizeX >> _mapSizeY >> _wallRatio >> _itemNum;
}

void MapMaker::Draw()
{
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			if (_map[x][y] == MapField::EMPTY || _map[x][y] == MapField::PRISON_ZONE)
				std::cout << "  ";
			else if (_map[x][y] == MapField::PORTAL || _map[x][y] == MapField::LOAD)
				std::cout << "  ";
			else if (_map[x][y] == MapField::WALL || _map[x][y] == MapField::PRISON_WALL)
				std::cout << "■";
			else if (_map[x][y] == MapField::ITEM_COIN)
				std::cout << "* ";
			else if(_map[x][y] == MapField::ITEM_Debuff)
				std::cout << "★";
		}
		std::cout << std::endl;
	}
}


void MapMaker::_MakeItem()
{
	_itemMaker.Init(_itemNum,_mapSizeX,_mapSizeY);
	_itemMaker.SettingItemDebuff(_map);
	_itemMaker.SettingItemCoin(_map);
}
