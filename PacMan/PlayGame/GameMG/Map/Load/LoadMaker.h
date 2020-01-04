#pragma once
#include "..//MapEnum.h"

using namespace EnumMap;

class LoadMaker
{
public:
	void Init(const int wallNum, const int mapSizeX, const int mapSizeY);
	void MakeLoad(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //정사각형의 길 만드는 함수

private:
	int _wallNum = 0;
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	//장애물 비율을 맞추기 위해 추가로 길을 생성하는 함수
	void _MakeAdditionalLoad(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]);
};