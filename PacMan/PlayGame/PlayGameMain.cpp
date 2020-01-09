#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>


int main()
{
	ProgramMG::GetInstance()->InputMapSize();
	ProgramMG::GetInstance()->InputGameInfo();
	ProgramMG::GetInstance()->InputEnemyNum();

	GameMG gameMG;
	gameMG.Start();
}