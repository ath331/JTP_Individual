#include "CharMG.h"

#include <iostream>

void CharMG::Init(MapField map[][MAX_MAP_SIZE_X])
{
	_CopyArr(map, _map);
}
void CharMG::Update()
{

}

void CharMG::InputCharInfo(float speed)
{
	std::cout << "Input CharInfo_ speed(float), enemyNum(int)" << std::endl;
	std::cin >> _speed >> _enemyNum;

}
void CharMG::_CopyArr(MapField array1[][MAX_MAP_SIZE_Y], MapField array2[][MAX_MAP_SIZE_Y])
{
	MapField* p1 = nullptr, * endp1 = nullptr;
	MapField* p2 = nullptr;
	p1 = &array1[0][0];
	p2 = &array2[0][0];
	endp1 = &array1[MAX_MAP_SIZE_X - 1][MAX_MAP_SIZE_X - 1];
	while (p1 <= endp1)
	{
		*p2 = *p1;
		p1++; p2++;
	}
}
void CharMG::Draw()
{

}

