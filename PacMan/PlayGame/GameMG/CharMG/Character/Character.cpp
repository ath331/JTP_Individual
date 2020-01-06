#include "Character.h"

#include <cstdlib>
#include <ctime>

void Character::Init(MapField charState, int startX, int startY)
{
	_startX = startX;
	_startY = startY;
	_charState = charState;
}

bool Character::_IsPlayer()
{
	if (_charState == MapField::PLAYER_)
		return true;
	else
		return false;
}

void Character::MoveCharacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	switch (_curDirection)
	{
	case UP:
		break;
	case DOWN:
		if (map[_curPosX][_curPosY + 1] != MapField::WALL)
		{
			if (_IsPlayer())
			{
				map[_curPosX][_curPosY] = MapField::LOAD;
			}
			map[_curPosX][_curPosY + 1] = MapField::PLAYER_;
			SetCharPos(_curPosX, _curPosY + 1);
		}
		break;
	case LEFT:
		break;
	case RIGHT:
		break;
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