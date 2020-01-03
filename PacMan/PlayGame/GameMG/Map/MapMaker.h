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

	int _wallRatio = 0; //��ֹ� ����
	int _wallNum = 0; //�ʿ��� ��ֹ� ����
	float _emptyWall = 0.0f; //��ֹ��� ������ �ִ� ������ ��(�׵θ��� ������ ����)

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y]);
	void _CalculateWallRatio();

	void _MakePrison();

	void _MakeLoad();
};

