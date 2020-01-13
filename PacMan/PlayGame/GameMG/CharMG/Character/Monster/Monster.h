#pragma once

#include "..//Character.h"

class Monster : public Character
{
public:
	void SetGoalPos();
	virtual void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]);
private:
	bool _playerStateGetItem = false;

	bool _IsNextTilePlayer(int x, int y);
	void _SetEnemyPath(MoveDirection curDirection);
	void _InitEnemyPath(MoveDirection curDirection);

	virtual MoveDirection _GetRandomDirection();
	virtual void _MoveChacter(int x, int y); //실질적인 움직임 함수
	virtual void _SetPossibleDirection();
};