#include "GameMG/GameMG.h"
#include <windows.h>
int main()
{
	//ƒ‹º÷ ±Ù∫˝¿” ¡Ÿ¿Ã±‚
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 3, 6 };
	SetConsoleCursorPosition(hConsole, pos);*/

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