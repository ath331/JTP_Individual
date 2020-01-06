#include "Character.h"

#include <cstdlib>
#include <ctime>

void Character::Init(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY, int mapSizeX, int mapSizeY)
{
	_CopyArr(map, _map);
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;

	_startX = startX;
	_startY = startY;
	_curPosX = _startX;
	_curPosY = _startY;
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
	if (!_IsWall(map, x, y))
	{
		if (_IsPlayer())
		{
			map[_curPosX][_curPosY] = MapField::LOAD;
		}
		else
		{
			map[_curPosX][_curPosY] = MapField::LOAD;
		}
		/*else
		{
			MapField temp = map[_curPosX][_curPosY];
			map[_curPosX][_curPosY] = MapField::LOAD;
			map[_curPosX][_curPosY] = temp;
		}*/

		map[_curPosX + x][_curPosY + y] = _charState;
		SetCharPos(_curPosX + x, _curPosY + y);
	}

	if (_IsPotal(_map, x))
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

void Character::MoveCharacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	_PossibleDirection();
	_curDirection = _GetRandomDirection();

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

void Character::_PossibleDirection()
{
	//현재위치에서 갈수있는 방향을 체크. UP, DOWN, LEFT, RIGHT
	{
		if (!_IsWall(_map, 0, -1))
			_possibleDirectionArr[0] = true;
		else
			_possibleDirectionArr[0] = false;
	}
	{
		if (!_IsWall(_map, 0, 1))
			_possibleDirectionArr[1] = true;
		else
			_possibleDirectionArr[1] = false;
	}
	{
		if (!_IsWall(_map, -1, 0))
			_possibleDirectionArr[2] = true;
		else
			_possibleDirectionArr[2] = false;
	}
	{
		if (!_IsWall(_map, 1, 0))
			_possibleDirectionArr[3] = true;
		else
			_possibleDirectionArr[3] = false;
	}

	switch (_curDirection)
	{
	case UP:
		_possibleDirectionArr[1] = false;
		break;
	case DOWN:
		_possibleDirectionArr[0] = false;
		break;
	case LEFT:
		_possibleDirectionArr[3] = false;
		break;
	case RIGHT:
		_possibleDirectionArr[2] = false;
		break;
	default:
		break;
	}
}

MoveDirection Character::_GetRandomDirection()
{
	int possibleDirectionNum = 0;
	for (int i = 0; i < 4; i++)
	{
		if (_possibleDirectionArr[i] == true)
			possibleDirectionNum++;
	}

	int randDirection = rand() % 4;
	while (_possibleDirectionArr[randDirection] == false)
	{
		randDirection = rand() % 4;
	}

	return (MoveDirection)randDirection;
}

bool Character::_IsPotal(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x)
{
	if (map[_curPosX + x][_curPosY] == MapField::PORTAL)
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
}
void Character::_SetCurPosX(int posX)
{
	_curPosX = posX;
}
void Character::_SetCurPosY(int posY)
{
	_curPosY = posY;

}