#pragma once
#include "../Lock.h"
#include <mutex>

//게임 정보, 결과를 파싱하는 클래스
class ProgramMG
{
public:
	static ProgramMG* volatile GetInstance()
	{
		if (_instance == nullptr)
			LockGuard _dclpLockGuard(_dclpLock);

		if (_instance == nullptr)
		{
			_instance = new ProgramMG();
		}

		return _instance;
	}
	~ProgramMG() {};

	void SelectMode();

	void ParsingGameResult();

	bool IsGameOver();
	bool IsGameClear();
	void SetGameOver(bool state);
	void SetGameClear(bool state);

	int GetMapSize();
	int GetWallRatio();
	int GetItemNum();
	int GetEnemyNum();

	int GetMode();
	void SetRandomParameter();

private:
	void _InputMapSize();
	void _InputGameInfo();
	void _InputEnemyNum();

	static Lock _dclpLock;
	Lock _writeDataLock;
	Lock _gameEndCheckLock;

	ProgramMG() {};
	ProgramMG(const ProgramMG& other);
	static ProgramMG* volatile _instance;

	int _mode = 0;

	int _mapSize = 0;
	int _wallRatio = 0;
	int _itemNum = 0;
	int _enemyNum = 0;

	bool _gameOver = false;
	bool _gameClear = false;
};

