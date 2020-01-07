#include "MapMaker.h"
#include "MapEnum.h"

#include <iostream>

void MapMaker::Init(MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY)
{
	_CopyArr(map, _map);

	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			//������(�׵θ�)
			if (x == 0 || y == 0 || x == _mapSizeX - 1 || y == _mapSizeY - 1)
			{
				_map[y][x] = MapField::WALL;
			}
		}
	}

	//_MakePotal();
	_MakePrison();
	_MakeLoad();
	_MakeFieldWall();

	//_MakeItem();

	_CopyArr(_map, map);
}

void MapMaker::_CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X])
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
		//����� ����
		_map[centerY][centerX] = MapField::PRISON_ZONE;
		_map[centerY][centerX - 1] = MapField::PRISON_ZONE;
		_map[centerY + 1][centerX] = MapField::PRISON_ZONE;
		_map[centerY - 1][centerX] = MapField::PRISON_ZONE;
	}
	{
		//���� ������
		_map[centerY + 2][centerX] = MapField::PRISON_WALL;
		_map[centerY - 2][centerX] = MapField::PRISON_WALL;
		_map[centerY][centerX + 1] = MapField::PRISON_WALL;

		_map[centerY + 1][centerX + 1] = MapField::PRISON_WALL;
		_map[centerY + 1][centerX - 1] = MapField::PRISON_WALL;
		_map[centerY - 2][centerX + 1] = MapField::PRISON_WALL;
		_map[centerY + 2][centerX + 1] = MapField::PRISON_WALL;

		_map[centerY - 1][centerX + 1] = MapField::PRISON_WALL;
		_map[centerY + 2][centerX - 1] = MapField::PRISON_WALL;
		_map[centerY - 1][centerX - 1] = MapField::PRISON_WALL;
		_map[centerY - 2][centerX - 1] = MapField::PRISON_WALL;
	}
}

void MapMaker::_MakePotal()
{
	int centerY = _mapSizeY / 2;

	for (int i = 0; i < 2; i++)
	{
		_map[_mapSizeX - 1][centerY - i] = MapField::PORTAL;
		_map[0][centerY - i] = MapField::PORTAL;

		if (_mapSizeY % 2 == 1)
		{
			_map[_mapSizeX - 1][centerY + i] = MapField::PORTAL;
			_map[0][centerY + i] = MapField::PORTAL;
		}
	}
}

void MapMaker::_MakeLoad()
{
	int prisonRoadStartX = (_mapSizeX / 2) - 2;
	int prisonRoadStartY = (_mapSizeY / 2) - 3;
	int prisonRoadEndX = (_mapSizeX / 2) + 3;
	int prisonRoadEndY = (_mapSizeY / 2) + 4;

	//�������� �����(�ʼ�)
	for (int y = prisonRoadStartY; y < prisonRoadEndY; y++)
	{
		for (int x = prisonRoadStartX; x < prisonRoadEndX; x++)
		{
			if (_map[y][x] == MapField::EMPTY)
				_map[y][x] = MapField::LOAD;
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
			//������(���� EMPTY�� ��� WALL�̴�)
			if (_map[y][x] == MapField::EMPTY)
			{
				_map[y][x] = MapField::WALL;
			}
		}
	}
}

void MapMaker::InputMapInfo()
{
	std::cout << "Input MapInfo_ WallRatio(%), ItemNum : " << std::endl;
	std::cin >> _wallRatio >> _itemNum;
}

void MapMaker::_MakeItem()
{
	_itemMaker.Init(_itemNum, _mapSizeX, _mapSizeY);
	_itemMaker.SettingItemDebuff(_map);
	_itemMaker.SettingItemCoin(_map);
}
