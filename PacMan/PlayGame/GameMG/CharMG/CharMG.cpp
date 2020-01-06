#include "CharMG.h"
#include "Character/Character.h"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

void CharMG::InputCharInfo()
{
	std::cout << "Input CharInfo_ enemyNum(int)" << std::endl;
	std::cin >> _enemyNum;
}

void CharMG::Init(MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY)
{
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	_MakePlayerPos(map, _mapSizeX / 2, (_mapSizeY / 2 + 2));

	/*for (int i = 0; i < _enemyNum; i++)
	{
		Character* enemyCharacter = new Character;
		enemyCharacter->Init();
		charVec.push_back(enemyCharacter);
	}*/
}

void CharMG::Update(MapField map[][MAX_MAP_SIZE_X])
{
	charVec[0]->MoveCharacter(map);
}

void CharMG::_SetCharacterPos(int charNum, int posX, int posY)
{
	charVec[charNum]->SetCharPos(posX, posY);
}

void CharMG::_MakePlayerPos(MapField map[][MAX_MAP_SIZE_X], int posX, int posY)
{
	Character* playerCharacter = new Character;
	playerCharacter->Init(map, MapField::PLAYER_, posX, posY);
	charVec.push_back(playerCharacter);

	_SetCharacterPos(0, posX, posY);
	int playerCurPosX = charVec[0]->GetCurPosX();
	int playerCurPosY = charVec[0]->GetCurPosY();

	map[playerCurPosX][playerCurPosY] = MapField::PLAYER_;
}