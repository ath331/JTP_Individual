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
	while (1)
	{
		boost::thread th1(boost::bind(&GameMG::Start, gameMG));
		th1.join();
		ProgramMG::GetInstance()->SetGameOver(false);
		ProgramMG::GetInstance()->SetGameClear(false);
	}
}