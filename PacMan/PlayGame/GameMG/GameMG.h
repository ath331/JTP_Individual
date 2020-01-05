#pragma once

#include "Map/MapMaker.h"
#include "Map/MapEnum.h"
#include "CharMG/CharMG.h"

class GameMG
{
public:
	void Init();
	void Update();
	void Draw();

private:
	MapMaker _mapMaker;
	CharMG _charMG;
};