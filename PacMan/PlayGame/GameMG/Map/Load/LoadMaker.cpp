#include "LoadMaker.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void LoadMaker::Init(const int wallRatio, const int mapSizeX, const int mapSizeY)
{
	srand((unsigned int)time(NULL));

	_wallRatio = wallRatio;
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;
}

void LoadMaker::MakeLoad(MapField map[][MAX_MAP_SIZE_X])
{
	//���簢���� ������ ����
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

	//���簢���� ������ ����
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

	_MakeBasicLoad(map);
	_MakeAdditionalLoad(map);
}

void LoadMaker::_MakeBasicLoad(MapField map[][MAX_MAP_SIZE_X])
{
	//�⺻���� �� ����
	for (int y = 1; y < _mapSizeY; y++)
	{
		for (int x = 1; x < _mapSizeX; x++)
		{
			if (map[_mapSizeY / 2][x] == EnumMap::MapField::EMPTY)
				map[_mapSizeY / 2][x] = EnumMap::MapField::LOAD;

			if (map[y][_mapSizeX / 2] == EnumMap::MapField::EMPTY)
				map[y][_mapSizeX / 2] = EnumMap::MapField::LOAD;
		}
	}
}
void LoadMaker::_MakeAdditionalLoad(MapField map[][MAX_MAP_SIZE_X])
{
	int curWallNum = 0;

	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			if (map[y][x] == MapField::EMPTY)
			{
				curWallNum++;
			}
		}
	}

	struct tempPosXY
	{
		int posX, posY;
	};
	std::vector<tempPosXY> tempPosVec(curWallNum);
	int i = 0;
	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			if (map[y][x] == MapField::EMPTY)
			{
				tempPosVec[i].posX = x;
				tempPosVec[i].posY = y;
				i++;
			}
		}
	}

	//�����־���ϴ� ��ֹ��� ��
	int temp = ((float)curWallNum / 100.0f) * _wallRatio;
	int wallNum = curWallNum - temp;

	while (wallNum > 0)
	{
		int randNum = rand() % tempPosVec.size();
		int tempX = tempPosVec[randNum].posX;
		int tempY = tempPosVec[randNum].posY;

		map[tempY][tempX] = MapField::LOAD;

		int i = 0;
		for (auto iter = tempPosVec.begin(); iter < tempPosVec.end(); iter++)
		{
			if (i == randNum)
			{
				iter = tempPosVec.erase(iter);
				wallNum--;
				break;
			}
			i++;
		}
	}
}