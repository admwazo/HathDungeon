#include <vector>

#include "Game.h"

using namespace std;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Play()
{
	DungeonLevel* dlLevel = UpLevel();	
}

//Cycles thru vector of DL objects, and returns one higher than what iCurLevel is set to
DungeonLevel* Game::UpLevel()
{
	//if we are playing currently highest level
	if((vLevels.size() - 1) == iCurLevel)
	{
		DungeonLevel* dlLevel = new DungeonLevel(79,20);
		vLevels.push_back(dlLevel);
	}
	//else, a level higher than current one already exists
	else
	{
		DungeonLevel* dlLevel = vLevels[iCurLevel + 1];
	}
	
	iCurLevel++;	//incrementing current level counter
	return dlLevel; //returning proper level
}

DungeonLevel* Game::DownLevel()
{
	iCurLevel--;
	return vLevel[iCurLevel - 1];
}
