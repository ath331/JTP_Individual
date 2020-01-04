#pragma once
#include "MapEnum.h"
#include "Load/LoadMaker.h"

using namespace EnumMap;

class MapMaker
{
public:
	void InputMapInfo();
	void Init(MapField map[][MAX_MAP_SIZE_Y]);
	void Draw();
private:
	LoadMaker loadMaker;
	MapField _map[MAX_MAP_SIZE_X][MAX_MAP_SIZE_Y];
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _wallRatio = 0; //장애물 비율

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y]);

	void _MakePrison();
	void _MakePotal();
	void _MakeLoad();
	void _MakeFieldWall();
};

