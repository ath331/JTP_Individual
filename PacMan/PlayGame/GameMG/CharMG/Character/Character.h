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
	void Init(bool* isGamePlaying, MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY, int mapSizeX, int mapSizeY);
	int GetCurPosX();
	int GetCurPosY();

	MapField GetCharState();
	void SetCharPos(int posX, int posY);
	void MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //_MoveChacater�� �ܺο��� ȣ���ϱ� ���� �Լ�
private:
	int enemyPath = 3;
	bool* _isGamePlaying;
	bool _possibleDirectionArr[4] = { false,true,true,true };

	MapField _charState = MapField::PLAYER_;
	void _CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X]);

	MapField* _mapPtr[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	MapField* _enemyPathPtr[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];
	MapField _charMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X];

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
	bool _IsNextTileEnemy(int x, int y);
	bool _IsNextTilePlayer(int x, int y);
	bool _IsNextTileWall(int x, int y);
	bool _IsNextTilePotal(int x);

	MoveDirection _curDirection = MoveDirection::DOWN;
	MoveDirection _GetRandomDirection();
	void _MoveChacter(int x, int y); //�������� ������ �Լ�
	void _PossibleDirection();
	void _SetCurDirection(MoveDirection direction);
	void _SetEnemyPath(MoveDirection curDirection);
	bool _CheckEnemyPath(MoveDirection curDirection);
};