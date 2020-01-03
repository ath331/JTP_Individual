#include "GameMG.h"

void GameMG::Init()
{
	_mapMaker.InputMapSize();
	_mapMaker.Init(_mapField);
}

void GameMG::Update()
{
	//TODO : 캐릭터 이동함수
}

void GameMG::Draw()
{
	_mapMaker.Draw(_mapField);
}

void GameMG::_InitMapField()
{
	_mapMaker.Init(_mapField);
}
