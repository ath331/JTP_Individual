#include "Character.h"

#include <cstdlib>
#include <ctime>

void Character::Init(bool* isGamePlaying, MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField charState, int startX, int startY, int mapSizeX, int mapSizeY)
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
	_PossibleDirection();

	map[startX][startY] = charState;
	_isGamePlaying = isGamePlaying;
}

bool Character::_IsPlayer()
{
	if (_charState == MapField::PLAYER_)
		return true;
	else
		return false;
}
bool Character::_IsNextTileWall(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y)
{
	if (map[_curPosX + x][_curPosY + y] == MapField::WALL || map[_curPosX + x][_curPosY + y] == MapField::PRISON_WALL)
		return true;
	else
		return false;
}
bool Character::_IsNextTileEnemy(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y)
{
	if (map[_curPosX + x][_curPosY + y] == MapField::ENEMY_)
		return true;
	else
		return false;
}
bool Character::_IsNextTilePlayer(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y)
{
	if (map[_curPosX + x][_curPosY + y] == MapField::PLAYER_ || map[_curPosX][_curPosY] == MapField::PLAYER_)
		return true;
	else
		return false;
}

void Character::_SetEnemyPath(MoveDirection curDirection, MapField copyMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	switch (curDirection)
	{
	case UP:
		for (int i = 0; i < _enemyPath; i++)
			copyMap[_curPosX][_curPosY - i] = MapField::ENEMY_PATH;
		break;
	case DOWN:
		for (int i = 0; i < _enemyPath; i++)
			copyMap[_curPosX][_curPosY + i] = MapField::ENEMY_PATH;
		break;
	case LEFT:
		for (int i = 0; i < _enemyPath; i++)
			copyMap[_curPosX - i][_curPosY] = MapField::ENEMY_PATH;
		break;
	case RIGHT:
		for (int i = 0; i < _enemyPath; i++)
			copyMap[_curPosX + i][_curPosY] = MapField::ENEMY_PATH;
		break;
	default:
		break;
	}
}

void Character::_MoveChacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField copyMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x, int y)
{
	if (!_IsNextTileWall(map, x, y))
	{
		if (!_IsNextTileEnemy(map, x, y))
		{
			MapField temp = map[_curPosX + x][_curPosY + y];
			map[_curPosX + x][_curPosY + y] = _charState;
			map[_curPosX][_curPosY] = MapField::LOAD;

			if (!_IsPlayer())
			{
				map[_curPosX][_curPosY] = temp;
			}
			SetCharPos(_curPosX + x, _curPosY + y);
		}

		else if (_IsNextTileEnemy(map, x, y) && _IsPlayer())
		{
			*_isGamePlaying = false;
		}

		else if (_IsNextTilePlayer(map, x, y) && !_IsPlayer())
		{
			*_isGamePlaying = false;
		}
	}

	if (_IsNextTilePotal(map, x))
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

void Character::MoveCharacter(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], MapField copyMap[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	_PossibleDirection();
	_curDirection = _GetRandomDirection();

	switch (_curDirection)
	{
	case UP:
		_MoveChacter(map, copyMap, 0, -1);
		break;
	case DOWN:
		_MoveChacter(map, copyMap, 0, 1);
		break;
	case LEFT:
		_MoveChacter(map, copyMap, -1, 0);
		break;
	case RIGHT:
		_MoveChacter(map, copyMap, 1, 0);

	default:
		break;
	}
}

void Character::_PossibleDirection()
{
	//현재위치에서 벽이 아닌 방향을 체크. UP, DOWN, LEFT, RIGHT
	{
		if (!_IsNextTileWall(_map, 0, -1))
			_possibleDirectionArr[0] = true;
		else
			_possibleDirectionArr[0] = false;

		if (!_IsNextTileWall(_map, 0, 1))
			_possibleDirectionArr[1] = true;
		else
			_possibleDirectionArr[1] = false;

		if (!_IsNextTileWall(_map, -1, 0))
			_possibleDirectionArr[2] = true;
		else
			_possibleDirectionArr[2] = false;

		if (!_IsNextTileWall(_map, 1, 0))
			_possibleDirectionArr[3] = true;
		else
			_possibleDirectionArr[3] = false;
	}
}

MoveDirection Character::_GetRandomDirection()
{
	MoveDirection tempCurMoveDirection = _curDirection;

	int randDirection = rand() % 4;
	while (_possibleDirectionArr[randDirection] == false)
	{
		randDirection = rand() % 4;
	}

	int possibleDirectionNum = 0;
	for (int i = 0; i < 4; i++)
	{
		if (_possibleDirectionArr[i] == true)
			possibleDirectionNum++;
	}

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

bool Character::_CheckEnemyPath(MoveDirection curDirection)
{
	switch (curDirection)
	{
	case UP:
		for (int i = 0; i < _enemyPath; i++)
		{
			if (_map[_curPosX][_curPosY - i] == MapField::ENEMY_PATH)
				return false;
		}
		return true;

	case DOWN:
		for (int i = 0; i < _enemyPath; i++)
		{
			if (_map[_curPosX][_curPosY + i] == MapField::ENEMY_PATH)
				return false;
		}
		return true;

	case LEFT:
		for (int i = 0; i < _enemyPath; i++)
		{
			if (_map[_curPosX - i][_curPosY] == MapField::ENEMY_PATH)
				return false;
		}
		return true;

	case RIGHT:
		for (int i = 0; i < _enemyPath; i++)
		{
			if (_map[_curPosX + i][_curPosY] == MapField::ENEMY_PATH)
				return false;
		}
		return true;

	default:
		break;
	}
	return true;

}


bool Character::_IsNextTilePotal(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X], int x)
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