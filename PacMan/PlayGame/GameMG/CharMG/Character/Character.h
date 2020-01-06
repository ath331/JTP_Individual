#pragma once
#include "../../Map/MapEnum.h"

using namespace EnumMap;

enum MoveDirection
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
};

struct CharPos
{
public:
	int posX = 0;
	int posY = 0;
};

class Character
{
public:
	void Init(MapField charState,int startX, int startY);
	int GetCurPosX();
	int GetCurPosY();

	void SetCharPos(int posX, int posY);
	void MoveCharacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]);
private:
	MapField _charState = MapField::PLAYER_;
	MapField _map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];

	int _startX = 0;
	int _startY = 0;
	int _curPosX = 0;
	int _curPosY = 0;
	void _SetCurPosX(int posX);
	void _SetCurPosY(int posY);

	bool _IsPlayer();

	MoveDirection _curDirection = MoveDirection::DOWN;
	void _SetCurDirection(MoveDirection direction);

	MoveDirection _GetRandomDirection();
};