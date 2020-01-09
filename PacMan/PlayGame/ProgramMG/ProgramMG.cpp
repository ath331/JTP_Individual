#include "ProgramMG.h"
#include "../tinyxml/tinyxml.h"

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

ProgramMG* ProgramMG::_instance = nullptr;

void ProgramMG::SetMapSize(int mapSize)
{
	_mapSize = mapSize;
}
void ProgramMG::SetGameInfo(int wallRatio, int itemNum)
{
	_wallRatio = wallRatio;
	_itemNum = itemNum;
}
void ProgramMG::SetEnemyNum(int enemyNum)
{
	_enemyNum = enemyNum;
}

void ProgramMG::ParsingGameResult()
{
	fstream fs("GameResult.csv", ios::out | ios::app);

	if (fs.is_open())
	{
		cout << "File Open" << endl;
		fs <<"\n"<< _mapSize << ","
			<< _wallRatio << "," << _itemNum << ","
			<< _enemyNum;

		fs.close();
	}
	else
		exit(1);

	/*TiXmlDocument doc;
	TiXmlDeclaration* dec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(dec1);
	TiXmlElement* root = new TiXmlElement("GameInfo");
	doc.LinkEndChild(root);

	doc.SaveFile("GameInfo.xml");*/
}