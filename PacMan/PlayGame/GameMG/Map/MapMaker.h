#pragma once
#include "MapEnum.h"
#include "Load/LoadMaker.h"
#include "Item/ItemMaker.h"

using namespace EnumMap;

class MapMaker
{
public:
	void InputMapInfo();
	void Init(MapField map[][MAX_MAP_SIZE_Y]);
	void Draw();
private:
	LoadMaker _loadMaker;
	ItemMaker _itemMaker;

	MapField _map[MAX_MAP_SIZE_X][MAX_MAP_SIZE_Y];

	int _mapSizeX = 0;
	int _mapSizeY = 0;
	int _wallRatio = 0; //장애물 비율
	int _itemNum = 0;

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y]);


	//맵배치
	void _MakePrison();
	void _MakePotal();
	void _MakeLoad();
	void _MakeFieldWall();

	//아이템배치
	void _MakeItem();
};

