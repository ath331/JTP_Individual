#include "GameMG.h"
#include "../ProgramMG/ProgramMG.h"

#include <iostream>

void GameMG::Init()
{
	std::fill(&_mapField[0][0], &_mapField[MAX_MAP_SIZE_Y - 1][MAX_MAP_SIZE_X], EnumMap::MapField::EMPTY);

	while (true)
	{
		std::cout << "Input MapSize_ (11, 19, 23) : ";
		std::cin >> _mapSizeX;
		if (_mapSizeX == 11 || _mapSizeX == 19 || _mapSizeX == 23)
			break;
	}
	_mapSizeY = _mapSizeX;

	ProgramMG::GetInstance()->SetMapSize(_mapSizeX);

	_mapMaker.InputMapInfo();
	_mapMaker.Init(_mapField, _mapSizeX, _mapSizeY);
	_charMG.InputCharInfo();
	_charMG.Init(_mapField, _mapSizeX, _mapSizeY);
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