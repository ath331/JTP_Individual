#pragma once

//게임 정보, 결과를 파싱하는 클래스
class ProgramMG
{
public:
	static ProgramMG* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new ProgramMG;
		}

		return _instance;
	}
	~ProgramMG() {};

	void SetMapSize(int mapSize);
	void SetGameInfo(int wallRatio, int itemNum);
	void SetEnemyNum(int enemyNum);

private:
	ProgramMG() {};
	ProgramMG(const ProgramMG& other);
	static ProgramMG* _instance;

	int _mapSize = 0;
	int _wallRatio = 0;
	int _itemNum = 0;
	int _enemyNum = 0;
};

