#pragma once
#include "..//Map/MapEnum.h"
#include "../InputMG/InputMG.h"
#include <vector>

using namespace EnumMap;

class Character;
class CharMG
{
public:
	void Init(InputMG* inputMG, MapField map[][MAX_MAP_SIZE_X]);
	void Update(MapField map[][MAX_MAP_SIZE_X]);
	void Draw();

private:
	InputMG* _inputMG;
	MapField _enemyPathMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	std::vector<Character*> charVec;

	int _enemyNum = 0;

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);
	void _gotoxy(int x, int y);
};