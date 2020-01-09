#include "GameMG/GameMG.h"
#include <windows.h>
int main()
{
	static HANDLE a;
	bool isGamePlaying = true;

	GameMG gameMG;
	gameMG.Init(&isGamePlaying);

	while (isGamePlaying)
	{
		system("cls");
		gameMG.Update();
		gameMG.Draw();
		Sleep(400);
	}
}