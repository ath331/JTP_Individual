#include "Monster.h"
#include "..//..//..//..//ProgramMG/ProgramMG.h"

bool Monster::_IsNextTilePlayer(int x, int y)
{
	if (*_enemyPathPtr[_curPosX + x][_curPosY + y] == MapField::PLAYER_)
		return true;
	else
		return false;
}
MoveDirection Monster::_GetRandomDirection()
{
	/*if (_playerStateGetItem)
	{
		return _GetNearGoalPosDirection();
	}

	else if (!_playerStateGetItem)*/
	{
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
}

void Monster::_SetPossibleDirection()
{
	if (*_mapPtr[_curPosX][_curPosY] == MapField::PRISON_ZONE)
		_playerStateGetItem = false;

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


void Monster::_SetEnemyPath(MoveDirection curDirection)
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

void Monster::_MoveChacter(int x, int y)
{
	_SetEnemyPath(_curDirection);
	if (!_IsNextTileWall(x, y))
	{
		_InitCurPosState();
		SetCharPos(_curPosX + x, _curPosY + y);

		if (_IsNextTilePlayer(x, y) || *_mapPtr[_curPosX][_curPosY] == MapField::PLAYER_)
		{
			_inputMG->SetGameOver(true);
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
void Monster::MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	_InitEnemyPath(_curDirection);

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
void Monster::_InitEnemyPath(MoveDirection curDirection)
{
	switch (curDirection)
	{
	case UP:
		for (int i = 0; i <= _enemyPath; i++)
		{
			if (*_enemyPathPtr[_curPosX][_curPosY - i] == MapField::ENEMY_PATH)
				*_enemyPathPtr[_curPosX][_curPosY - i] = MapField::ROAD;
			else if (_IsNextTileWall(0, -i))
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