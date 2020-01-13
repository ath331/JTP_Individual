#pragma once

#include "..//MapEnum.h"

using namespace EnumMap;

class ItemMaker
{
public:
	void Init(int mapSizeX, int mapSizeY, int itemNum);
	void SettingItemDebuff(MapField* map[][MAX_MAP_SIZE_Y]);
	void SettingItemCoin(MapField* map[][MAX_MAP_SIZE_Y]);
private:
	int _itemNum = 0;
	int _mapSizeX = 0;
	int _mapSizeY = 0;
};