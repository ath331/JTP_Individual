#include "GameMG.h"
#include <iostream>
void GameMG::Init()
{
	std::fill(&_mapField[0][0], &_mapField[MAX_MAP_SIZE_X - 1][MAX_MAP_SIZE_Y], EnumMap::MapField::EMPTY);

	_mapMaker.InputMapInfo();
	_mapMaker.Init(_mapField);
}

void GameMG::Update()
{
	//TODO : 캐릭터 이동함수
}

void GameMG::Draw()
{
	_mapMaker.Draw();
}