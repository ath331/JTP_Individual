#pragma once
#include "MapEnum.h"
#include "Road/RoadMaker.h"
#include "Item/ItemMaker.h"

using namespace EnumMap;

class MapMaker
{
public:
	void Init(MapField map[][MAX_MAP_SIZE_X]);
	void Draw();
private:
	RoadMaker _roadMaker;
	ItemMaker _itemMaker;

	MapField* _map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];

	int _mapSizeX = 0;
	int _mapSizeY = 0;
	int _itemNum = 0;

	void _CopyArrPtr(MapField array1[][MAX_MAP_SIZE_X], MapField* array2[][MAX_MAP_SIZE_X]);


	//맵배치
	void _MakePrison();
	void _MakePotal();
	void _MakeLoad();
	void _MakeFieldWall();

	//아이템배치
	void _MakeItem();
};

