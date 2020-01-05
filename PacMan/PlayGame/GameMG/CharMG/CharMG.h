#pragma once
#include "..//Map/MapEnum.h"

using namespace EnumMap;

class CharMG
{
public:
	void Init(MapField map[][MAX_MAP_SIZE_X]);
	void InputCharInfo();
	void Update();
	void Draw();
private:
	MapField _map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);

	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _enemyNum = 0;
	int _speed = 0;

	void _MakePlayerPos(MapField map[][MAX_MAP_SIZE_X],int posX,int posY);
};