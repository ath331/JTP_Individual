#include "ProgramMG.h"

ProgramMG* ProgramMG::_instance = nullptr;

void ProgramMG::SetMapSize(int mapSize)
{
	_mapSize = mapSize;
}
void ProgramMG::SetGameInfo(int wallRatio, int itemNum)
{
	_wallRatio = wallRatio;
	_itemNum = itemNum;
}
void ProgramMG::SetEnemyNum(int enemyNum)
{
	_enemyNum = enemyNum;
}
