#include "Player.h"
#include "..//..//..//..//ProgramMG/ProgramMG.h"

bool Player::_IsNextTileEnemy(int x, int y)
{
	if (*_enemyPathPtr[_curPosX + x][_curPosY + y] == MapField::ENEMY_)
		return true;
	else
		return false;
}

bool Player::_IsNextTileEnemyPath(MoveDirection direction)
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

bool Player::_IsNextTileItem(int tempCurPosX, int tempCurPosY, int x, int y)
{
	if (tempCurPosX + x < _mapSizeX && tempCurPosX + x > 0)
	{
		if (tempCurPosY + y < _mapSizeY && tempCurPosY + y > 0)
		{
			if (*_mapPtr[tempCurPosX + x][tempCurPosY + y] == MapField::ITEM_COIN || *_mapPtr[tempCurPosX + x][tempCurPosY + y] == MapField::ITEM_Debuff)
				return true;
			else
				return false;
		}
	}
}

void Player::_FindNearItem()
{
	int tempCurPosX = _curPosX;
	int tempCurPosY = _curPosY;

	int tempRow = 1; //상하로 가야하는 칸수
	int tempCol = 1; //좌우로 가야하는 칸수

	int tempCurRowNum = 0; //현재 진행한 상하의 칸수
	int tempCurColNum = 0; //현재 진행한 좌우의 칸수

	while (true)
	{
		while (tempCurRowNum < tempRow) //아래로 탐색
		{
			if (_IsNextTileItem(tempCurPosX, tempCurPosY, 0, 1))
			{
				_goalPosX = tempCurPosX;
				_goalPosY = ++tempCurPosY;
				return;
			}
			tempCurPosY++;
			tempCurRowNum++;

		}
		tempCurRowNum = 0;
		tempRow++;

		while (tempCurColNum < tempCol) //좌로 탐색
		{
			if (_IsNextTileItem(tempCurPosX, tempCurPosY, -1, 0))
			{
				_goalPosX = --tempCurPosX;
				_goalPosY = tempCurPosY;
				return;
			}
			tempCurPosX--;
			tempCurColNum++;
		}
		tempCurColNum = 0;
		tempCol++;

		while (tempCurRowNum < tempRow) //위로 탐색
		{
			if (_IsNextTileItem(tempCurPosX, tempCurPosY, 0, -1))
			{
				_goalPosX = tempCurPosX;
				_goalPosY = --tempCurPosY;
				return;
			}
			tempCurPosY--;
			tempCurRowNum++;
		}
		tempCurRowNum = 0;
		tempRow++;

		while (tempCurColNum < tempCol) //우로 탐색
		{
			if (_IsNextTileItem(tempCurPosX, tempCurPosY, 1, 0))
			{
				_goalPosX = ++tempCurPosX;
				_goalPosY = tempCurPosY;
				return;
			}
			tempCurPosX++;
			tempCurColNum++;
		}
		tempCurColNum = 0;
		tempCol++;
	}
}

MoveDirection Player::_GetRandomDirection()
{
	return _GetNearItemDirection();
}

void Player::MoveCharacter(MapField enemyPath[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X])
{
	_FindNearItem();
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
void Player::_SetPossibleDirection()
{
	//현재위치에서 갈수있는 방향을 체크. UP, DOWN, LEFT, RIGHT

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
		_inputMG->SetGameOver(true);
	}
}

void Player::_MoveChacter(int x, int y)
{
	if (!_IsNextTileWall(x, y))
	{
		*_mapPtr[_curPosX][_curPosY] = MapField::ROAD;

		_InitCurPosState();
		SetCharPos(_curPosX + x, _curPosY + y);

		if (_IsNextTileEnemy(x, y))
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

MoveDirection Player::_GetNearItemDirection()
{
	//1 왼쪽위 2오른쪽위 3왼쪽아래 4오른쪽아래
	//5 위직선 6왼직선 7아래직선 8우직선     
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

MoveDirection Player::_GetDirection(MoveDirection direction)
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