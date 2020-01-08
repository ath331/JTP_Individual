#include "GameMG.h"

#include <iostream>

void GameMG::Init(bool* isGamePlaying)
{
	std::fill(&_mapField[0][0], &_mapField[MAX_MAP_SIZE_Y - 1 ][MAX_MAP_SIZE_X], EnumMap::MapField::EMPTY);

	std::cout << "Input MapSize_ : " << std::endl;
	std::cout << "MAX SIZE = " << MAX_MAP_SIZE_X << std::endl;
	std::cin >> _mapSizeX;
	_mapSizeY = _mapSizeX;

	_mapMaker.InputMapInfo();
	_mapMaker.Init(_mapField, _mapSizeX, _mapSizeY);
	_charMG.InputCharInfo();
	_charMG.Init(isGamePlaying, _mapField, _mapSizeX, _mapSizeY);
}

void GameMG::Update()
{
	_charMG.Update(_mapField);
}

void GameMG::Draw()
{
	_mapMaker.Draw();
	_charMG.Draw();
}