#include "Character.h"
#include "../../../ProgramMG/ProgramMG.h"

#include<iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

void Character::Init(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY)
{
	_CopyArr(map, _charMap);

	_mapSizeX = ProgramMG::GetInstance()->GetMapSize();
	_mapSizeY = _mapSizeX;
	_CopyArrPtr(enemyPath, _enemyPathPtr);
	_CopyArrPtr(map, _mapPtr);

	_startX = startX;
	_startY = startY;
	_curPosX = _startX;
	_curPosY = _startY;
	_charState = charState;

	_curDirection = _GetRandomDirection();

	_charMap[startX][startY] = charState;
}
void Character::_CopyArrPtr(MapField array1[][MAX_MAP_SIZE_X], MapField* array2[][MAX_MAP_SIZE_X])
{
	for (int y = 0; y < _mapSizeY; y++)
	{
		for (int x = 0; x < _mapSizeX; x++)
		{
			array2[x][y] = &array1[x][y];
		}
	}
}

bool Character::_IsPlayer()
{
	if (_charState == MapField::PLAYER_)
		return true;
	else
		return false;
}
bool Character::_IsNextTileWall(int x, int y)
{
	if (_charMap[_curPosX + x][_curPosY + y] == MapField::WALL || _charMap[_curPosX + x][_curPosY + y] == MapField::PRISON_WALL)
		return true;
	else
		return false;
}
bool Character::_IsNextTileEnemy(int x, int y)
{
	if (*_enemyPathPtr[_curPosX + x][_curPosY + y] == MapField::ENEMY_)
		return true;
	else
		return false;
}
bool Character::_IsNextTilePlayer(int x, int y)
{
	if (*_enemyPathPtr[_curPosX + x][_curPosY + y] == MapField::PLAYER_)
		return true;
	else
		return false;
}

void Character::_SetEnemyPath(MoveDirection curDirection)
{
	switch (curDirection)
	{
	case UP:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY - i] != MapField::WALL && *_enemyPathPtr[_curPosX][_curPosY - i] != MapField::PRISON_WALL)
				*_enemyPathPtr[_curPosX][_curPosY - i] = MapField::ENEMY_PATH;
			else if (_IsNextTileWall(0, -i))
				break;
		}
		break;
	case DOWN:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY + i] != MapField::WALL && *_enemyPathPtr[_curPosX][_curPosY + i] != MapField::PRISON_WALL)
				*_enemyPathPtr[_curPosX][_curPosY + i] = MapField::ENEMY_PATH;
			else if (_IsNextTileWall(0, i))
				break;
		}
		break;
	case LEFT:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX - i][_curPosY] != MapField::WALL && *_enemyPathPtr[_curPosX - i][_curPosY] != MapField::PRISON_WALL)
				*_enemyPathPtr[_curPosX - i][_curPosY] = MapField::ENEMY_PATH;
			else if (_IsNextTileWall(-i, 0))
				break;
		}
		break;
	case RIGHT:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX + i][_curPosY] != MapField::WALL && *_enemyPathPtr[_curPosX + i][_curPosY] != MapField::PRISON_WALL)
				*_enemyPathPtr[_curPosX + i][_curPosY] = MapField::ENEMY_PATH;
			else if (_IsNextTileWall(i, 0))
				break;
		}
		break;
	default:
		break;
	}
}

void Character::_MoveChacter(int x, int y)
{
	if (!_IsPlayer())
	{
		_SetEnemyPath(_curDirection);
	}

	if (!_IsNextTileWall(x, y))
	{
		if (_IsPlayer())
		{
			*_mapPtr[_curPosX][_curPosY] = MapField::ROAD;
		}
		_InitCurPosState();
		SetCharPos(_curPosX + x, _curPosY + y);

		if (_IsNextTileEnemy(x, y) && _IsPlayer())
		{
			ProgramMG::GetInstance()->SetGameOver(true);
			return;
		}

		else if (_IsNextTilePlayer(x, y) && !_IsPlayer())
		{
			ProgramMG::GetInstance()->SetGameOver(true);
			return;
		}
	}

	if (_IsNextTilePotal(x))
	{
		if (_curPosX + x == 0)
		{
			SetCharPos(_mapSizeX - 1, _curPosY);
			_curDirection = MoveDirection::LEFT;
		}
		else if (_curPosX + x == _mapSizeX - 1)
		{
			SetCharPos(0, _curPosY);
			_curDirection = MoveDirection::RIGHT;
		}
	}
}

void Character::_InitCurPosState()
{
	*_enemyPathPtr[_curPosX][_curPosY] = MapField::ROAD;
}

void Character::_InitEnemyPath(MoveDirection curDirection)
{
	switch (curDirection)
	{
	case UP:
		for (int i = 0; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY - i] == MapField::ENEMY_PATH)
				*_enemyPathPtr[_curPosX][_curPosY - i] = MapField::ROAD;
			else if (_IsNextTileWall(0, -i));
			break;
		}
	case DOWN:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY + i] == MapField::ENEMY_PATH)
				*_enemyPathPtr[_curPosX][_curPosY + i] = MapField::ROAD;
			else if (_IsNextTileWall(0, i))
				break;
		}
	case LEFT:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX - i][_curPosY] == MapField::ENEMY_PATH)
				*_enemyPathPtr[_curPosX - i][_curPosY] = MapField::ROAD;
			else if (_IsNextTileWall(-i, 0))
				break;
		}
	case RIGHT:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX + i][_curPosY] == MapField::ENEMY_PATH)
				*_enemyPathPtr[_curPosX + i][_curPosY] = MapField::ROAD;
			else if (_IsNextTileWall(i, 0))
				break;
		}
	default:
		break;
	}
}


void Character::MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	if (!_IsPlayer())
	{
		_InitEnemyPath(_curDirection);
	}

	_SetPossibleDirection();
	if (_impossibleDirectionNum == 4)
		return;

	_curDirection = _GetRandomDirection();

	switch (_curDirection)
	{
	case UP:
		_MoveChacter(0, -1);
		break;
	case DOWN:
		_MoveChacter(0, 1);
		break;
	case LEFT:
		_MoveChacter(-1, 0);
		break;
	case RIGHT:
		_MoveChacter(1, 0);
		break;
	default:
		break;
	}
}
bool Character::_IsNextTileEnemyPath(MoveDirection direction)
{
	switch (direction)
	{
	case UP:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY - i] == MapField::ENEMY_PATH || *_enemyPathPtr[_curPosX][_curPosY - i] == MapField::ENEMY_)
				return true;
			else if (_IsNextTileWall(0, -i))
				break;
		}
		break;
	case DOWN:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY + i] == MapField::ENEMY_PATH || *_enemyPathPtr[_curPosX][_curPosY + i] == MapField::ENEMY_)
				return true;
			else if (_IsNextTileWall(0, i))
				break;
		}
		break;
	case LEFT:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX - i][_curPosY] == MapField::ENEMY_PATH || *_enemyPathPtr[_curPosX - i][_curPosY] == MapField::ENEMY_)
				return true;
			else if (_IsNextTileWall(-i, 0))
				break;
		}
		break;
	case RIGHT:
		for (int i = 1; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX + i][_curPosY] == MapField::ENEMY_PATH || *_enemyPathPtr[_curPosX + i][_curPosY] == MapField::ENEMY_)
				return true;
			else if (_IsNextTileWall(i, 0))
				break;
		}
		break;
	default:
		break;
	}
	return false;
}



void Character::_SetPossibleDirection()
{
	//현재위치에서 갈수있는 방향을 체크. UP, DOWN, LEFT, RIGHT
	if (_IsPlayer())
	{
		_impossibleDirectionNum = 0;
		if (_IsNextTileWall(0, -1) || _IsNextTileEnemyPath(MoveDirection::UP))
		{
			_possibleDirectionArr[0] = false;
			_impossibleDirectionNum++;
		}
		else
			_possibleDirectionArr[0] = true;

		if (_IsNextTileWall(0, 1) || _IsNextTileEnemyPath(MoveDirection::DOWN))
		{
			_possibleDirectionArr[1] = false;
			_impossibleDirectionNum++;
		}
		else
			_possibleDirectionArr[1] = true;

		if (_IsNextTileWall(-1, 0) || _IsNextTileEnemyPath(MoveDirection::LEFT))
		{
			_possibleDirectionArr[2] = false;
			_impossibleDirectionNum++;
		}
		else
			_possibleDirectionArr[2] = true;

		if (_IsNextTileWall(1, 0) || _IsNextTileEnemyPath(MoveDirection::RIGHT))
		{
			_possibleDirectionArr[3] = false;
			_impossibleDirectionNum++;
		}
		else
			_possibleDirectionArr[3] = true;

		if (_impossibleDirectionNum == 4)
		{
			ProgramMG::GetInstance()->SetGameOver(true);
		}
	}
	else
	{
		if (!_IsNextTileWall(0, -1))
			_possibleDirectionArr[0] = true;
		else
			_possibleDirectionArr[0] = false;

		if (!_IsNextTileWall(0, 1))
			_possibleDirectionArr[1] = true;
		else
			_possibleDirectionArr[1] = false;

		if (!_IsNextTileWall(-1, 0))
			_possibleDirectionArr[2] = true;
		else
			_possibleDirectionArr[2] = false;

		if (!_IsNextTileWall(1, 0))
			_possibleDirectionArr[3] = true;
		else
			_possibleDirectionArr[3] = false;
	}
}

MoveDirection Character::_GetRandomDirection()
{
	int randDirection = rand() % 4;
	while (_possibleDirectionArr[randDirection] == false)
	{
		randDirection = rand() % 4; //랜덤이 아닌 목표지점과의 거리,위치를 계산해서 우선순위로 방행을 뿌리기
	}

	int possibleDirectionNum = 0;
	for (int i = 0; i < 4; i++)
	{
		if (_possibleDirectionArr[i] == true)
			possibleDirectionNum++;
	}

	MoveDirection tempCurMoveDirection = _curDirection;
	if (possibleDirectionNum != 1) //진행방향이 뒤만 있는게 아니라면 뒤로 가지 않는다
	{
		switch ((MoveDirection)randDirection)
		{
		case UP:
			if (_curDirection == DOWN)
			{
				randDirection = (int)tempCurMoveDirection;
			}
			break;
		case DOWN:
			if (_curDirection == UP)
			{
				randDirection = (int)tempCurMoveDirection;
			}
			break;
		case LEFT:
			if (_curDirection == RIGHT)
			{
				randDirection = (int)tempCurMoveDirection;
			}
			break;
		case RIGHT:
			if (_curDirection == LEFT)
			{
				randDirection = (int)tempCurMoveDirection;
			}
			break;

		default:
			break;
		}
	}

	return (MoveDirection)randDirection;
}

MapField Character::GetCharState()
{
	return _charState;
}
bool Character::_IsNextTilePotal(int x)
{
	if (_charMap[_curPosX + x][_curPosY] == MapField::PORTAL)
		return true;
	else
		return false;
}

void Character::_CopyArr(MapField array1[][MAX_MAP_SIZE_X], MapField array2[][MAX_MAP_SIZE_X])
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


void Character::_SetCurDirection(MoveDirection direction)
{
	_curDirection = direction;
}

int Character::GetCurPosX()
{
	return _curPosX;
}
int Character::GetCurPosY()
{
	return _curPosY;
}
void Character::SetCharPos(int posX, int posY)
{
	_SetCurPosX(posX);
	_SetCurPosY(posY);
	*_enemyPathPtr[posX][posY] = _charState;
}
void Character::_SetCurPosX(int posX)
{
	_curPosX = posX;
}
void Character::_SetCurPosY(int posY)
{
	_curPosY = posY;

}