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
	void Init(bool* isGamePlaying,MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X],MapField charState,int startX, int startY,int mapSizeX, int mapSizeY);
	int GetCurPosX();
	int GetCurPosY();

	void SetCharPos(int posX, int posY);
	void MoveCharacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField copyMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //_MoveChacater를 외부에서 호출하기 위한 함수
private:
	int _enemyPath = 3;
	bool* _isGamePlaying;
	bool _possibleDirectionArr[4] = { false,true,true,true };

	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);
	MapField _charState = MapField::PLAYER_;
	MapField _map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];

	int _mapSizeX = 0;
	int _mapSizeY = 0;

	int _startX = 0;
	int _startY = 0;
	int _curPosX = 0;
	int _curPosY = 0;

	void _SetCurPosX(int posX);
	void _SetCurPosY(int posY);

	bool _IsPlayer();
	bool _IsNextTileEnemy(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y);
	bool _IsNextTilePlayer(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y);
	bool _IsNextTileWall(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y);
	bool _IsNextTilePotal(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X],int x);

	MoveDirection _curDirection = MoveDirection::DOWN;
	MoveDirection _GetRandomDirection();
	void _MoveChacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField copyMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y); //실질적인 움직임 함수
	void _PossibleDirection();
	void _SetCurDirection(MoveDirection direction);
	void _SetEnemyPath(MoveDirection curDirection, MapField copyMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]);
	bool _CheckEnemyPath(MoveDirection curDirection);
};