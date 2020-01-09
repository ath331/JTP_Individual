#pragma once
#include "..//Map/MapEnum.h"

#include <vector>

using namespace EnumMap;

class Character;
class CharMG
{
public:
	void Init( MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY);
	void InputCharInfo();
	void Update(MapField map[][MAX_MAP_SIZE_X]);
	void Draw();

private:
	MapField _enemyPathMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	std::vector<Character*> charVec;

	int _enemyNum = 0;

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);
	void gotoxy(int x, int y);
};