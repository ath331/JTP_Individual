#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>


int main()
{
	ProgramMG::GetInstance()->SelectMode();

	GameMG gameMG;
	boost::thread_group tg;
	while (1)
	{
		tg.create_thread(boost::bind(&GameMG::Start, gameMG));
		tg.join_all();
	}
}