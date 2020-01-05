#pragma once
#include "..//Map/MapEnum.h"

using namespace EnumMap;

class CharMG
{
public:
	void Init(MapField map[][MAX_MAP_SIZE_X]);
	void InputCharInfo(float speed);
	void Update();
	void Draw();
private:
	MapField _map[MAX_MAP_SIZE_X][MAX_MAP_SIZE_X];

	int _enemyNum = 0;
	int _speed = 0;

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y]);

};