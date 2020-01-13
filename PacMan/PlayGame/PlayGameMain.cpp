#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"
#include "Lock.h"

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <process.h>


int main()
{
	Lock randomSettingLock;
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	ProgramMG::GetInstance()->SelectMode();

	GameMG gameMG[12];
	boost::thread_group tg;
	while (true)
	{
		tg.create_thread(boost::bind(&GameMG::Start, gameMG[0]));
		if (ProgramMG::GetInstance()->GetMode() == 1)
			for (int i = 1; i < systemInfo.dwNumberOfProcessors; i++)
			{
				tg.create_thread(boost::bind(&GameMG::Start, gameMG[i]));
			}
		tg.join_all();
	}
}