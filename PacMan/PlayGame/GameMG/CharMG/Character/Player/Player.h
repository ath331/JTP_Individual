#pragma once
#include "..//Character.h"
class Player : public Character
{
public:
	virtual void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]);
private:
	int _goalPosX = 0;
	int _goalPosY = 0;

	bool _IsNextTileEnemy(int x, int y);
	bool _IsNextTileEnemyPath(MoveDirection direction);
	bool _IsNextTileItem(int tempCurPosX, int tempCurPosY, int x, int y);

	virtual void _SetPossibleDirection();
	virtual void _MoveChacter(int x, int y);

	void _FindNearItem();
	virtual MoveDirection _GetRandomDirection();
	MoveDirection _GetNearItemDirection();
	MoveDirection _GetDirection(MoveDirection direction); //목표지점과 상대위치를 비교해서 우선순위로 방향을 리턴
};