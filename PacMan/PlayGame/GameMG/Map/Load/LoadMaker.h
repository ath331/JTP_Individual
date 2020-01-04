#pragma once
#include "..//MapEnum.h"

using namespace EnumMap;

class LoadMaker
{
public:
	void Init(const int wallNum, const int mapSizeX, const int mapSizeY);
	void MakeLoad(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]); //���簢���� �� ����� �Լ�

private:
	int _wallNum = 0;
	int _mapSizeX = 0;
	int _mapSizeY = 0;

	//��ֹ� ������ ���߱� ���� �߰��� ���� �����ϴ� �Լ�
	void _MakeAdditionalLoad(MapField map[MAX_MAP_SIZE_Y][MAX_MAP_SIZE_X]);
};