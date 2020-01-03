#include "LoadMaker.h"
#include <iostream>

void LoadMaker::Init(int* wallNum, LoadWay way)
{
	_way = way;
	_wallNum = wallNum;
}


void LoadMaker::MakeLoad()
{
	std::cout << _way << " MakeLoad()" << std::endl;
}
