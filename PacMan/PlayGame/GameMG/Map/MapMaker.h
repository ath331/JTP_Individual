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
	void Draw(MapField map[][MAX_MAP_SIZE_Y]);
private:
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _wallRatio = 0; //��ֹ� ����
	int _wallNum = 0; //�ʿ��� ��ֹ� ����
	float emptyWall = 0.0f; //��ֹ��� ������ �ִ� ������ ��(�׵θ��� ������ ����)

	void _CalculateWallRatio();
	bool _IsChangeWall();
	void _MakeLoad();
};

