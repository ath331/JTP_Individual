#include "GameMG.h"
#include <iostream>
void GameMG::Init()
{

	_mapMaker.InputMapInfo();
	_mapMaker.Init();
}

void GameMG::Update()
{
	//TODO : 캐릭터 이동함수
}

void GameMG::Draw()
{
	_mapMaker.Draw();
}