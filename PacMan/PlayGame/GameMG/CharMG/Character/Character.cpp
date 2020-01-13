#include "Character.h"
#include "../../../ProgramMG/ProgramMG.h"

#include<iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

void Character::Init(InputMG* inputMG,MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY)
{
	_CopyArr(map, _charMap);
	_inputMG = inputMG;
	_mapSizeX = _inputMG->GetMapSize();
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


MoveDirection Character::_GetDirection(MoveDirection direction)
{
	switch (direction)
	{
	case UP:
		if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		else if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		break;
	case DOWN:
		if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		else if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		else if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		break;
	case LEFT:
		if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		else if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		else if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		break;
	case RIGHT:
		if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		else if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		else if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		break;
	case UP_LEFT:
		if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		else if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		break;
	case UP_RIGHT:
		if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		else if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		else if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		break;
	case DOWN_LEFT:
		if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		else if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		else if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		break;
	case DOWN_RIGHT:
		if (_possibleDirectionArr[1])
			return MoveDirection::DOWN;
		else if (_possibleDirectionArr[3])
			return MoveDirection::RIGHT;
		else if (_possibleDirectionArr[0])
			return MoveDirection::UP;
		else if (_possibleDirectionArr[2])
			return MoveDirection::LEFT;
		break;
	default:
		break;
	}
}
MoveDirection Character::_GetNearGoalPosDirection()
{
	MoveDirection direction = MoveDirection::DOWN;
	int tempX = _curPosX - _goalPosX;
	int tempY = _curPosY - _goalPosY;

	//목표지점이 대각선인지 체크
	{
		if (tempX > 0 && tempY > 0)
			direction = MoveDirection::UP_LEFT;
		else if (tempX < 0 && tempY > 0)
			direction = MoveDirection::UP_RIGHT;
		else if (tempX > 0 && tempY < 0)
			direction = MoveDirection::DOWN_LEFT;
		else if (tempX < 0 && tempY < 0)
			direction = MoveDirection::DOWN_RIGHT;
	}
	//목표지점이 일직선방향인지 체크
	{
		if (tempX == 0 && tempY > 0)
			direction = MoveDirection::UP;
		else if (tempX == 0 && tempY < 0)
			direction = MoveDirection::DOWN;
		else if (tempX > 0 && tempY == 0)
			direction = MoveDirection::LEFT;
		else if (tempX < 0 && tempY == 0)
			direction = MoveDirection::RIGHT;
	}

	return _GetDirection(direction);
}

bool Character::IsGetItem()
{
	return _getItem;
}


void Character::SetGoalPos()
{
	_goalPosX = _mapSizeX / 2;
	_goalPosY = _mapSizeY / 2;

	_playerStateGetItem = true;
}

void Character::SetgetItem(bool state)
{
	_getItem = state;
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

void Character::_InitCurPosState()
{
	*_enemyPathPtr[_curPosX][_curPosY] = MapField::ROAD;
}

void Character::_SetPossibleDirection()
{
	//현재위치에서 갈수있는 방향을 체크. UP, DOWN, LEFT, RIGHT
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