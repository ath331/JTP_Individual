#include "GameMG/GameMG.h"
#include <windows.h>
int main()
{
	GameMG gameMG;
	gameMG.Init();

	while (true)
	{
		gameMG.Draw();
		gameMG.Update();
		Sleep(300);
		system("cls");
	}
}