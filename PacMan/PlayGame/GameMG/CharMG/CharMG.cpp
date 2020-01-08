#include "CharMG.h"
#include "Character/Character.h"

#include <iostream>
#include <conio.h>
#include <windows.h>

void CharMG::InputCharInfo()
{
	std::cout << "Input CharInfo_ enemyNum(int)" << std::endl;
	std::cin >> _enemyNum;
}

void CharMG::Init(bool* isGamePlaying, MapField map[][MAX_MAP_SIZE_X], int mapSizeX, int mapSizeY)
{
	_CopyArr(map, _enemyPathMap);
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	//_MakePlayer
	Character* playerCharacter = new Character;
	playerCharacter->Init(isGamePlaying, map, _enemyPathMap, MapField::PLAYER_, (_mapSizeX / 2), (_mapSizeY / 2) + 2, _mapSizeX, _mapSizeY);
	charVec.push_back(playerCharacter);

	//_MakeEnemy
	for (int i = 0; i < _enemyNum; i++)
	{
		Character* enemyCharacter = new Character;
		enemyCharacter->Init(isGamePlaying, map, _enemyPathMap, MapField::ENEMY_, ((_mapSizeX / 2) - 1) + i, _mapSizeY / 2, _mapSizeX, _mapSizeY);
		charVec.push_back(enemyCharacter);

		int startPosX = ((_mapSizeX / 2) - 1) + i;
		int startPosY = _mapSizeY / 2;
	}
}
void CharMG::gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void CharMG::Draw()
{
	int posX = 0, posY = 0;
	for (auto iter = charVec.begin(); iter != charVec.end(); iter++)
	{
		posX = (*iter)->GetCurPosX();
		posY = (*iter)->GetCurPosY();

		gotoxy(posX * 2, posY);

		if ((*iter)->GetCharState() == MapField::ENEMY_)
			std::cout << "��";
		else if ((*iter)->GetCharState() == MapField::PLAYER_)
			std::cout << "��";
	}
}
void CharMG::_CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X])
{
	MapField* p1 = nullptr, * endp1 = nullptr;
	MapField* p2 = nullptr;
	p1 = &array1[0][0];
	p2 = &array2[0][0];
	endp1 = &array1[MAX_MAP_SIZE_X - 1][MAX_MAP_SIZE_X - 1];
	while (p1 <= endp1)
	{
		*p2 = *p1;
		p1++; p2++;
	}
}

void CharMG::Update(MapField map[][MAX_MAP_SIZE_X])
{
	for (auto iter = charVec.begin(); iter < charVec.end(); iter++)
	{
		(*iter)->MoveCharacter(_enemyPathMap);
	}
}