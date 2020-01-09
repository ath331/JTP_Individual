#pragma once

const static int MAX_MAP_SIZE_X = 23;
const static int MAX_MAP_SIZE_Y = 23;

namespace EnumMap
{
	enum MapField
	{
		EMPTY = 0,
		//////////////////
		WALL,
		ROAD,
		PORTAL,
		PRISON_WALL,
		PRISON_ZONE,
		//////////////////
		ITEM_COIN,
		ITEM_Debuff,
		/////////////////
		PLAYER_,
		ENEMY_,
		ENEMY_PATH,
	};
}