#include "ItemMaker.h"

#include <cstdlib>
#include <ctime>
#include <vector>

void ItemMaker::Init(int itemNum,int mapSizeX, int mapSizeY)
{
	srand((unsigned int)time(NULL));

	_itemNum = itemNum;
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;
}

void ItemMaker::SettingItemDebuff(MapField map[][MAX_MAP_SIZE_X])
{
	int curLoadNum = 0;

	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			if (map[y][x] == MapField::LOAD)
			{
				curLoadNum++;
			}
		}
	}

	struct tempPosXY
	{
		int posX, posY;
	};
	std::vector<tempPosXY> tempPosVec(curLoadNum);
	int i = 0;
	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			if (map[y][x] == MapField::LOAD)
			{
				tempPosVec[i].posX = x;
				tempPosVec[i].posY = y;
				i++;
			}
		}
	}

	//Debuff Item ·£´ý ¹èÄ¡
	while (_itemNum > 0)
	{
		int randNum = rand() % tempPosVec.size();
		int tempX = tempPosVec[randNum].posX;
		int tempY = tempPosVec[randNum].posY;

		map[tempY][tempX] = MapField::ITEM_Debuff;

		int i = 0;
		for (auto iter = tempPosVec.begin(); iter < tempPosVec.end(); iter++)
		{
			if (i == randNum)
			{
				iter = tempPosVec.erase(iter);
				_itemNum--;
				break;
			}
			i++;
		}
	}
}

void ItemMaker::SettingItemCoin(MapField map[][MAX_MAP_SIZE_X])
{
	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			if (map[y][x] == MapField::LOAD)
				map[y][x] = MapField::ITEM_COIN;
		}
	}
}