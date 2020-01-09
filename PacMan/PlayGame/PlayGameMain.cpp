#include "GameMG/GameMG.h"
#include "ProgramMG/ProgramMG.h"

#include <windows.h>

int main()
{
	bool isGamePlaying = true;

	GameMG gameMG;
	gameMG.Init(&isGamePlaying);
	ProgramMG::GetInstance()->ParsingGameResult();

	while (isGamePlaying)
	{
		system("cls");
		gameMG.Update();
		gameMG.Draw();
		Sleep(400);
	}
}