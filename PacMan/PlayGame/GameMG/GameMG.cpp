#include "GameMG.h"
#include "../ProgramMG/ProgramMG.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

void GameMG::Start()
{

	if (ProgramMG::GetInstance()->GetMode() == 1) //Auto Mode
	{
		_inputMG.SetRandomParameter();
	}

	else if (ProgramMG::GetInstance()->GetMode() != 1) //Select Mode
	{
		_inputMG.SetGameInfo();
	}
	_Init();
	_inputMG.SetGameOver(false);
	_inputMG.SetGameClear(false);
	while (true)
	{
		_Update();
		if (ProgramMG::GetInstance()->GetMode() != 1) //Select Mode
		{
			system("cls");
			_Draw();
		}
		_IsItemNumZero();
		if (_inputMG.IsGameClear() || _inputMG.IsGameOver())
			break;
		Sleep(400);
	}
	{
		ProgramMG::GetInstance()->ParsingGameResult(_inputMG.GetMapSize(), _inputMG.GetWallRatio(), _inputMG.GetItemNum(), _inputMG.GetEnemyNum(), _inputMG.IsGameClear());
	}

}

void GameMG::_Init()
{
	std::fill(&_mapField[0][0], &_mapField[MAX_MAP_SIZE_Y - 1][MAX_MAP_SIZE_X], EnumMap::MapField::EMPTY);

	_mapMaker.Init(&_inputMG, _mapField);
	_charMG.Init(&_inputMG, _mapField);
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
	int mapSizeY = _inputMG.GetMapSize();
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
		_inputMG.SetGameClear(true);
	}
}