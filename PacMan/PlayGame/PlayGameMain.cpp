#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <process.h>

//MG = Manager = ¸Å´ÏÀú 

int main()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	ProgramMG::GetInstance()->SelectMode();

	GameMG gameMG;
	boost::thread_group tg;
	while (true)
	{
		tg.create_thread(boost::bind(&GameMG::Start, gameMG));

		if (ProgramMG::GetInstance()->GetMode() == 1)
			for (int i = 0; i < systemInfo.dwNumberOfProcessors - 1 ; i++)
			{
				tg.create_thread(boost::bind(&GameMG::Start, gameMG));
			}
		tg.join_all();
	}
}