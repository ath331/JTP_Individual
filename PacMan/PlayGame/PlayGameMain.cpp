#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"

#include <windows.h>

int main()
{
	GameMG gameMG;
	gameMG.Init();

	while (true)
	{
		system("cls");
		gameMG.Update();
		gameMG.Draw();
		Sleep(400);
		if (ProgramMG::GetInstance()->IsGameClear())
			break;
		else if (ProgramMG::GetInstance()->IsGameOver())
			break;
	}
	ProgramMG::GetInstance()->ParsingGameResult();
}