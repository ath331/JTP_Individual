#pragma once
#include "MapEnum.h"

const static int MAX_MAP_SIZE_X = 25;
const static int MAX_MAP_SIZE_Y = 25;

using namespace EnumMap;

class MapMaker
{
public:
	void InputMapInfo();
	void Init(MapField map[][MAX_MAP_SIZE_Y]);
	void Draw();
private:
	MapField _map[MAX_MAP_SIZE_X][MAX_MAP_SIZE_Y];
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _wallRatio = 0; //장애물 비율
	int _wallNum = 0; //필요한 장애물 개수
	float _emptyWall = 0.0f; //장애물을 놓을수 있는 공간의 수(테두리를 제외한 공간)

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y]);
	void _CalculateWallRatio();

	void _MakePrison();

	void _MakeLoad();
};

