#pragma once

#include "Map/MapMaker.h"
#include "Map/MapEnum.h"
#include "CharMG/CharMG.h"

class GameMG
{
public:
	void Start();

private:
	MapMaker _mapMaker;
	CharMG _charMG;

	EnumMap::MapField _mapField[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X] = { EnumMap::MapField::EMPTY,};

	void _Init();
	void _Update();
	void _Draw();
};