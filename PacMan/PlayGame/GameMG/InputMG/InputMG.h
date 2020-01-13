#pragma once
class InputMG
{
public:

	int GetMapSize();
	int GetWallRatio();
	int GetItemNum();
	int GetEnemyNum();

	bool IsGameOver();
	bool IsGameClear();
	void SetGameOver(bool state);
	void SetGameClear(bool state);

	void SetRandomParameter();
	void SetGameInfo();
private:
	void init_number_generator();

	void _InputMapSize();
	void _InputGameInfo();
	void _InputEnemyNum();

	int _mapSize = 0;
	int _wallRatio = 0;
	int _itemNum = 0;
	int _enemyNum = 0;

	int _mode = 0;

	bool _gameOver = false;
	bool _gameClear = false;
};

