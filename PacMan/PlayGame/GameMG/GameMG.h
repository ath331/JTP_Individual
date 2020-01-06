#pragma once

#include "Map/MapMaker.h"
#include "Map/MapEnum.h"
#include "CharMG/CharMG.h"

class GameMG
{
public:
	void Init(bool* isGamePlaying);
	void Update();
	void Draw();

private:
	MapMaker _mapMaker;
	CharMG _charMG;

	EnumMap::MapField _mapField[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X] = { EnumMap::MapField::EMPTY,};

	int _mapSizeX = 0;
	int _mapSizeY = 0;
};