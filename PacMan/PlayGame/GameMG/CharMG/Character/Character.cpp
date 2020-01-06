#include "Character.h"

#include <cstdlib>
#include <ctime>

void Character::Init(MapField charState, int startX, int startY)
{
	_startX = startX;
	_startY = startY;
	_charState = charState;
	_curDirection = _GetRandomDirection();
}

bool Character::_IsPlayer()
{
	if (_charState == MapField::PLAYER_)
		return true;
	else
		return false;
}
bool Character::_IsWall(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y)
{
	if (map[_curPosX + x][_curPosY + y] == MapField::WALL || map[_curPosX + x][_curPosY + y] == MapField::PRISON_WALL)
		return true;
	else
		return false;
}
void Character::_MoveChacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y)
{
	if(!_IsWall(map,x,y))
	{
		if (_IsPlayer())
		{
			map[_curPosX][_curPosY] = MapField::LOAD;
		}
		map[_curPosX + x][_curPosY + y] = MapField::PLAYER_;
		SetCharPos(_curPosX + x, _curPosY + y);
	}
	else
		_curDirection = _GetRandomDirection();
}

void Character::MoveCharacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	switch (_curDirection)
	{
	case UP:
		_MoveChacter(map, 0, -1);
		break;
	case DOWN:
		_MoveChacter(map, 0, 1);
		break;
	case LEFT:
		_MoveChacter(map, -1, 0);
		break;
	case RIGHT:
		_MoveChacter(map, 1, 0);

	default:
		break;
	}
}

MoveDirection Character::_GetRandomDirection()
{
	int randDirection = rand() % 4;

	return (MoveDirection)randDirection;
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
}
void Character::_SetCurPosX(int posX)
{
	_curPosX = posX;
}
void Character::_SetCurPosY(int posY)
{
	_curPosY = posY;

}