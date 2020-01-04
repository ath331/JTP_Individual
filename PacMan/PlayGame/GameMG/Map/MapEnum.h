#pragma once

const static int MAX_MAP_SIZE_X = 50;
const static int MAX_MAP_SIZE_Y = 50;

namespace EnumMap
{
	enum MapField
	{
		EMPTY = 0,
		WALL,
		LOAD,
		PORTAL,
		PRISON_WALL,
		PRISON_ZONE,
	};
}