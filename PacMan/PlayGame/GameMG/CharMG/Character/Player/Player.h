#pragma once
#include "..//Character.h"
class Player : public Character
{
public:
	virtual void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //_MoveCharacter를 외부에서 호출하기 위한 함수
private:
	int _goalPosX = 0; //p
	int _goalPosY = 0; //p

	bool _IsNextTileEnemy(int x, int y); //p
	bool _IsNextTileEnemyPath(MoveDirection direction); //p
	bool _IsNextTileItem(int tempCurPosX, int tempCurPosY, int x, int y); //p

	virtual void _SetPossibleDirection();
	virtual void _MoveChacter(int x, int y); //실질적인 움직임 함수

	void _FindNearItem(); //p
	virtual MoveDirection _GetRandomDirection();
	MoveDirection _GetNearItemDirection(); //p
	MoveDirection _GetDirection(MoveDirection direction); //목표지점과 상대위치를 비교해서 우선순위로 방향을 리턴 //p
};