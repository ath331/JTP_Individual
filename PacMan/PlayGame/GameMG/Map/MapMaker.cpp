#include "MapMaker.h"
#include "MapEnum.h"
#include "../../ProgramMG/ProgramMG.h"

#include <iostream>

void MapMaker::Init(MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY)
{
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	_CopyArrPtr(map,_map);

	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			//벽생성(테두리)
			if (x == 0 || y == 0 || x == _mapSizeX - 1 || y == _mapSizeY - 1)
			{
				*_map[y][x] = MapField::WALL;
			}
		}
	}

	//_MakePotal();
	_MakePrison();
	_MakeLoad();
	_MakeFieldWall();

	_MakeItem();
}

void MapMaker::_CopyArrPtr(MapField array1[][MAX_MAP_SIZE_X], MapField* array2[][MAX_MAP_SIZE_X])
{
	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			array2[y][x] = &array1[y][x];
		}
	}
}

void MapMaker::Draw()
{
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			if (*_map[y][x] == MapField::EMPTY || *_map[y][x] == MapField::PRISON_ZONE)
				std::cout << "  ";
			else if (*_map[y][x] == MapField::PORTAL || *_map[y][x] == MapField::ROAD)
				std::cout << "  ";
			else if (*_map[y][x] == MapField::WALL || *_map[y][x] == MapField::PRISON_WALL)
				std::cout << "■";
			else if (*_map[y][x] == MapField::ITEM_COIN)
				std::cout << "* ";
			else if (*_map[y][x] == MapField::ITEM_Debuff)
				std::cout << "★";
		}
		std::cout << std::endl;
	}
}

void MapMaker::_MakePrison()
{
	int centerX = _mapSizeX / 2;
	int centerY = _mapSizeY / 2;

	{
		//빈공간 생성
		*_map[centerY][centerX] = MapField::PRISON_ZONE;
		*_map[centerY][centerX - 1] = MapField::PRISON_ZONE;
		*_map[centerY + 1][centerX] = MapField::PRISON_ZONE;
		*_map[centerY - 1][centerX] = MapField::PRISON_ZONE;
	}
	{
		//감옥 벽생성
		*_map[centerY + 2][centerX] = MapField::PRISON_WALL;
		*_map[centerY - 2][centerX] = MapField::PRISON_WALL;
		*_map[centerY][centerX + 1] = MapField::PRISON_WALL;

		*_map[centerY + 1][centerX + 1] = MapField::PRISON_WALL;
		*_map[centerY + 1][centerX - 1] = MapField::PRISON_WALL;
		*_map[centerY - 2][centerX + 1] = MapField::PRISON_WALL;
		*_map[centerY + 2][centerX + 1] = MapField::PRISON_WALL;

		*_map[centerY - 1][centerX + 1] = MapField::PRISON_WALL;
		*_map[centerY + 2][centerX - 1] = MapField::PRISON_WALL;
		*_map[centerY - 1][centerX - 1] = MapField::PRISON_WALL;
		*_map[centerY - 2][centerX - 1] = MapField::PRISON_WALL;
	}
}

void MapMaker::_MakePotal()
{
	int centerY = _mapSizeY / 2;

	for (int i = 0; i < 2; i++)
	{
		*_map[_mapSizeX - 1][centerY - i] = MapField::PORTAL;
		*_map[0][centerY - i] = MapField::PORTAL;

		if (_mapSizeY % 2 == 1)
		{
			*_map[_mapSizeX - 1][centerY + i] = MapField::PORTAL;
			*_map[0][centerY + i] = MapField::PORTAL;
		}
	}
}

void MapMaker::_MakeLoad()
{
	int prisonRoadStartX = (_mapSizeX / 2) - 2;
	int prisonRoadStartY = (_mapSizeY / 2) - 3;
	int prisonRoadEndX = (_mapSizeX / 2) + 3;
	int prisonRoadEndY = (_mapSizeY / 2) + 4;

	//감옥주위 길생성(필수)
	for (int y = prisonRoadStartY; y < prisonRoadEndY; y++)
	{
		for (int x = prisonRoadStartX; x < prisonRoadEndX; x++)
		{
			if (*_map[y][x] == MapField::EMPTY)
				*_map[y][x] = MapField::ROAD;
		}
	}

	_roadMaker.Init(_wallRatio, _mapSizeX, _mapSizeY);
	_roadMaker.MakeLoad(_map);
}

void MapMaker::_MakeFieldWall()
{
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			//벽생성(남은 EMPTY는 모두 WALL이다)
			if (*_map[y][x] == MapField::EMPTY)
			{
				*_map[y][x] = MapField::WALL;
			}
		}
	}
}

void MapMaker::InputMapInfo()
{
	std::cout << "Input MapInfo_ WallRatio(%), ItemNum : " << std::endl;
	std::cin >> _wallRatio >> _itemNum;
	ProgramMG::GetInstance()->SetGameInfo(_wallRatio, _itemNum);
}

void MapMaker::_MakeItem()
{
	_itemMaker.Init(_itemNum, _mapSizeX, _mapSizeY);
	_itemMaker.SettingItemDebuff(_map);
	_itemMaker.SettingItemCoin(_map);
}
