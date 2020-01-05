#include "ItemMaker.h"


void ItemMaker::Init(int itemNum,int mapSizeX, int mapSizeY)
{
	_itemNum = itemNum;
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;
}

void ItemMaker::SettingItemDebuff(MapField map[][MAX_MAP_SIZE_Y])
{

}

void ItemMaker::SettingItemCoin(MapField map[][MAX_MAP_SIZE_Y])
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