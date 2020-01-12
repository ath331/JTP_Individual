#pragma once
#include "..//Character.h"
class Player : public Character
{
public:
	virtual void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //_MoveCharacter�� �ܺο��� ȣ���ϱ� ���� �Լ�
private:
	int _goalPosX = 0; //p
	int _goalPosY = 0; //p

	bool _IsNextTileEnemy(int x, int y); //p
	bool _IsNextTileEnemyPath(MoveDirection direction); //p
	bool _IsNextTileItem(int tempCurPosX, int tempCurPosY, int x, int y); //p

	virtual void _SetPossibleDirection();
	virtual void _MoveChacter(int x, int y); //�������� ������ �Լ�

	void _FindNearItem(); //p
	virtual MoveDirection _GetRandomDirection();
	MoveDirection _GetNearItemDirection(); //p
	MoveDirection _GetDirection(MoveDirection direction); //��ǥ������ �����ġ�� ���ؼ� �켱������ ������ ���� //p
};