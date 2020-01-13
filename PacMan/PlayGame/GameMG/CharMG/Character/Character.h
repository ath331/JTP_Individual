#pragma once
#include "../../Map/MapEnum.h"
#include"../../InputMG/InputMG.h"

using namespace EnumMap;

enum MoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
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
	void Init(InputMG* inputMG, MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY);
	int GetCurPosX();
	int GetCurPosY();
	bool IsGetItem();
	void SetGoalPos();

	void SetgetItem(bool state);

	MapField GetCharState();
	void SetCharPos(int posX, int posY);
	virtual void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]) = 0; //_MoveCharacter�� �ܺο��� ȣ���ϱ� ���� �Լ�
protected:
	bool _getItem = false;
	bool _playerStateGetItem = false;

	InputMG* _inputMG;
	int _enemyPath = 3;
	bool _possibleDirectionArr[4] = { true,true,true,true };
	int _impossibleDirectionNum = 0;

	MapField _charState = MapField::PLAYER_;
	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);
	void _CopyArrPtr(MapField array1[][MAX_MAP_SIZE_X], MapField* array2[][MAX_MAP_SIZE_X]);

	MapField* _mapPtr[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	MapField* _enemyPathPtr[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	MapField _charMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];

	int _goalPosX = 0;
	int _goalPosY = 0;

	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _startX = 0;
	int _startY = 0;
	int _curPosX = 0;
	int _curPosY = 0;

	void _SetCurPosX(int posX);
	void _SetCurPosY(int posY);
	void _InitCurPosState();

	bool _IsPlayer();
	bool _IsNextTileWall(int x, int y);
	bool _IsNextTilePotal(int x);

	MoveDirection _curDirection = MoveDirection::DOWN;
	virtual MoveDirection _GetRandomDirection() =0;
	virtual void _MoveChacter(int x, int y) = 0; //�������� ������ �Լ�
	virtual void _SetPossibleDirection();
	void _SetCurDirection(MoveDirection direction);

	MoveDirection _GetNearGoalPosDirection();
	MoveDirection _GetDirection(MoveDirection direction); //��ǥ������ �����ġ�� ���ؼ� �켱������ ������ ����
};