#include "GameMG.h"
#include "../ProgramMG/ProgramMG.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

void GameMG::Start()
{
	srand((unsigned int)time(NULL));

	if (ProgramMG::GetInstance()->GetMode() == 1)
	{
		ProgramMG::GetInstance()->SetRandomParameter();
	}
	_Init();
	ProgramMG::GetInstance()->SetGameOver(false);
	ProgramMG::GetInstance()->SetGameClear(false);
	while (true)
	{
		system("cls");
		_Update();
		_Draw();
		_IsItemNumZero();
		if (ProgramMG::GetInstance()->IsGameClear())
			break;
		else if (ProgramMG::GetInstance()->IsGameOver())
			break;
		Sleep(400);
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

void GameMG::_IsItemNumZero()
{
	int itemNum = 0;
	int mapSizeY = ProgramMG::GetInstance()->GetMapSize();
	int mapSizeX = mapSizeY;
	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{
			if (_mapField[y][x] == MapField::ITEM_COIN || _mapField[y][x] == MapField::ITEM_Debuff)
				itemNum++;
		}
	}

	if (itemNum <= 0)
	{
		ProgramMG::GetInstance()->SetGameClear(true);
	}
}