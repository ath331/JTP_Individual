#pragma once
#include "LoadEnum.h"

using namespace EnumLoad;

class LoadMaker
{
public:
	void Init(int* wallNum, LoadWay way);
	void MakeLoad();
private:
	LoadWay _way;

	int* _wallNum;
};