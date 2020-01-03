#pragma once
#include "MapEnum.h"

const static int MAX_MAP_SIZE_X = 25;
const static int MAX_MAP_SIZE_Y = 25;

class MapMaker
{
public:
	void Init(EnumMap::MapField map[][MAX_MAP_SIZE_Y]);
	void InputMapSize();
	void Draw(EnumMap::MapField map[][MAX_MAP_SIZE_Y]);
private:
	int _mapSizeX = 0;
	int _mapSizeY = 0;
};

