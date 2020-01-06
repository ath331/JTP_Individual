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
	for (int x = 0; x < _mapSizeX; x++)
	{
		for (int y = 0; y < _mapSizeY; y++)
		{
			if (_mapField[y][x] == MapField::EMPTY || _mapField[y][x] == MapField::PRISON_ZONE)
				std::cout << "  ";
			else if (_mapField[y][x] == MapField::PORTAL || _mapField[y][x] == MapField::LOAD)
				std::cout << "  ";
			else if (_mapField[y][x] == MapField::WALL || _mapField[y][x] == MapField::PRISON_WALL)
				std::cout << "¡á";
			else if (_mapField[y][x] == MapField::ITEM_COIN)
				std::cout << "* ";
			else if (_mapField[y][x] == MapField::ITEM_Debuff)
				std::cout << "¡Ú";
			else if (_mapField[y][x] == MapField::PLAYER_)
				std::cout << "¡ã";
			else if (_mapField[y][x] == MapField::ENEMY_)
				std::cout << "¡â";
		}
		std::cout << std::endl;
	}
}