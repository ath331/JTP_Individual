#pragma once

const static int MAX_MAP_SIZE_X = 47;
const static int MAX_MAP_SIZE_Y = 47;

namespace EnumMap
{
	enum MapField
	{
		EMPTY = 0,
		//////////////////
		WALL,
		LOAD,
		PORTAL,
		PRISON_WALL,
		PRISON_ZONE,
		//////////////////
		ITEM_COIN,
		ITEM_Debuff,
		/////////////////
		PLAYER_START,
		ENEMY,
	};
}