#include "GameMG.h"
#include "../ProgramMG/ProgramMG.h"

#include <iostream>
#include <windows.h>

void GameMG::Start()
{
	_Init();
	ProgramMG::GetInstance()->SetGameOver(false);
	ProgramMG::GetInstance()->SetGameClear(false);
	while (true)
	{
		system("cls");
		_Update();
		_Draw();
		Sleep(400);
		if (ProgramMG::GetInstance()->IsGameClear())
			break;
		else if (ProgramMG::GetInstance()->IsGameOver())
			break;
	}
	ProgramMG::GetInstance()->ParsingGameResult();
}

void GameMG::_Init()
{
	std::fill(&_mapField[0][0], &_mapField[MAX_MAP_SIZE_Y - 1][MAX_MAP_SIZE_X], EnumMap::MapField::EMPTY);

	_mapMaker.Init(_mapField);
	_charMG.Init(_mapField);
}

void GameMG::_Update()
{
	_charMG.Update(_mapField);
}

void GameMG::_Draw()
{
	_mapMaker.Draw();
	_charMG.Draw();
}