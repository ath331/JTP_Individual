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

	void ParsingGameResult(int mapSize,int wallRatio, int itemNum, int enemyNum, bool gameClear);
	int GetMode();

private:
	static Lock _dclpLock;
	Lock _writeDataLock;

	ProgramMG() {};
	ProgramMG(const ProgramMG& other);
	static ProgramMG* volatile _instance;

	int _mode = 0;
};

