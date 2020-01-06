#pragma once
#include "..//Map/MapEnum.h"

#include <vector>

using namespace EnumMap;

class Character;
class CharMG
{
public:
	void Init(bool* isGamePlaying, MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY);
	void InputCharInfo();
	void Update(MapField map[][MAX_MAP_SIZE_X]);
private:
	MapField _map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	std::vector<Character*> charVec;

	int _enemyNum = 0;

	void _MakePlayerPos(bool* isGamePlaying, MapField map[][MAX_MAP_SIZE_X],int posX,int posY);
};