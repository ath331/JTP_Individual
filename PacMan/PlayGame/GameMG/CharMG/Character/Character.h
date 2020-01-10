#pragma once
#include "../../Map/MapEnum.h"

using namespace EnumMap;

enum MoveDirection
{
	UP,
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
	void Init(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY);
	int GetCurPosX();
	int GetCurPosY();

	MapField GetCharState();
	void SetCharPos(int posX, int posY);
	void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //_MoveChacater를 외부에서 호출하기 위한 함수
private:
	int _enemyPath = 3;
	bool _possibleDirectionArr[4] = { true,true,true,true };
	int _impossibleDirectionNum = 0;

	MapField _charState = MapField::PLAYER_;
	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);
	void _CopyArrPtr(MapField array1[][MAX_MAP_SIZE_X], MapField* array2[][MAX_MAP_SIZE_X]);

	MapField* _mapPtr[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	MapField* _enemyPathPtr[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	MapField _charMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];

	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _startX = 0;
	int _startY = 0;
	int _curPosX = 0;
	int _curPosY = 0;

	int _goalPosX = 0;
	int _goalPosY = 0;

	void _SetCurPosX(int posX);
	void _SetCurPosY(int posY);
	void _InitCurPosState();

	bool _IsPlayer();
	bool _IsNextTileEnemy(int x, int y);
	bool _IsNextTileEnemyPath(MoveDirection direction);
	bool _IsNextTilePlayer(int x, int y);
	bool _IsNextTileWall(int x, int y);
	bool _IsNextTilePotal(int x);
	bool _IsNextTileItem(int tempCurPosX, int tempCurPosY, int x, int y);

	MoveDirection _curDirection = MoveDirection::DOWN;
	MoveDirection _GetRandomDirection();
	void _MoveChacter(int x, int y); //실질적인 움직임 함수
	void _SetPossibleDirection();
	void _SetCurDirection(MoveDirection direction);
	void _SetEnemyPath(MoveDirection curDirection);
	void _InitEnemyPath(MoveDirection curDirection);

	void _FindNearItem();
	MoveDirection _GetNearItemDirection();
};