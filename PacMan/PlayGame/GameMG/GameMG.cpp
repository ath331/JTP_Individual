#include "GameMG.h"
#include <iostream>
void GameMG::Init()
{

	_mapMaker.InputMapInfo();
	_mapMaker.Init();
}

void GameMG::Update()
{
	//TODO : ĳ���� �̵��Լ�
}

void GameMG::Draw()
{
	_mapMaker.Draw();
}