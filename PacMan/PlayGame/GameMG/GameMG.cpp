#include "GameMG.h"

#include <iostream>

void GameMG::Init()
{
	std::fill(&_mapField[0][0], &_mapField[MAX_MAP_SIZE_X - 1][MAX_MAP_SIZE_Y], EnumMap::MapField::EMPTY);

	_mapMaker.InputMapInfo();
	_mapMaker.Init(_mapField);
	_charMG.Init(_mapField);
	_charMG.InputCharInfo(5.0f);
}

void GameMG::Update()
{
	_charMG.Update();
}

void GameMG::Draw()
{
	_mapMaker.Draw();
	_charMG.Draw();
}