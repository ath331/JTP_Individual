#pragma once
#include "..//MapEnum.h"

using namespace EnumMap;

class RoadMaker
{
public:
	void Init(const int mapSizeX, const int mapSizeY, int wallRatio);
	void MakeLoad(MapField* map[][MAX_MAP_SIZE_X]); //���簢���� �� ����� �Լ�

private:
	int _wallRatio = 0;
	int _emptyWall = 0; //��ֹ��� ������ �ִ� ������ ��(�׵θ��� ������ ����)

	int _mapSizeX = 0;
	int _mapSizeY = 0;

	void _MakeBasicLoad(MapField* map[][MAX_MAP_SIZE_X]); //�⺻���� �� ����
	void _MakeAdditionalLoad(MapField* map[][MAX_MAP_SIZE_X]); //��ֹ� ������ ���߱� ���� �� ����
};