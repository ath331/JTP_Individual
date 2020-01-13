#pragma once
#include "..//MapEnum.h"

using namespace EnumMap;

class RoadMaker
{
public:
	void Init(const int mapSizeX, const int mapSizeY, int wallRatio);
	void MakeLoad(MapField* map[][MAX_MAP_SIZE_X]); //정사각형의 길 만드는 함수

private:
	int _wallRatio = 0;
	int _emptyWall = 0; //장애물을 놓을수 있는 공간의 수(테두리를 제외한 공간)

	int _mapSizeX = 0;
	int _mapSizeY = 0;

	void _MakeBasicLoad(MapField* map[][MAX_MAP_SIZE_X]); //기본적인 길 세팅
	void _MakeAdditionalLoad(MapField* map[][MAX_MAP_SIZE_X]); //장애물 비율을 맞추기 위한 길 세팅
};