#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>


int main()
{
	ProgramMG::GetInstance()->SelectMode();

	GameMG gameMG;
	//thread 그룹화시키기
	while (1)
	{
		boost::thread th1(boost::bind(&GameMG::Start, gameMG));
		th1.join();
	}
}