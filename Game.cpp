#include <vector>

#include "Game.h"
#include "DungeonLevel.h"
#include "Player.h"

using namespace std;

Game::Game()
{
	iCurLevel = 0;
	int iCol;
    int iRow;

	UpLevel();
    //spawning player
    dlLevel->GetDownStairs(iRow, iCol);
	pPlayer.setPosX(iCol);
	pPlayer.setPosY(iRow);
}

Game::~Game()
{

}

bool Game::Turn()
{
	char input;
	cin >> input;
	
	if(input == 'q')
		return false;
	else if(input == 'w')
		pPlayer.moveUp();
	else if(input == 's')
		pPlayer.moveDown();
	else if(input == 'a')
		pPlayer.moveLeft();
	else if(input == 'd')
		pPlayer.moveRight();
	
	dlLevel->Set(pPlayer.getPosY(), pPlayer.getPosX(), pPlayer.getDisplayChar()); 
	
	return true;
}

bool Game::Play()
{
	dlLevel->Display();
	while(Turn())
		dlLevel->Display();
	
	return false;
}

void Game::moveLeft(Creature* cActor)
{
	char cTempTile = dlLevel->Get((cActor->getPosY), ((cActor->getPosX)-1));
	if(cTempTile != '|')
		cActor->setPosX = 
}

void Game::moveRight(Creature* cActor)
{

}

void Game::moveUp(Creature* cActor)
{

}

void Game::moveDown(Creature* cActor)
{

}

//Cycles thru vector of DL objects, and returns one higher than what iCurLevel is set to
void Game::UpLevel()
{
	//if we are playing currently highest level
	if(vLevels.size() == iCurLevel)
	{
		dlLevel = new DungeonLevel(79,20);
		dlLevel -> BuildRooms();
		vLevels.push_back(dlLevel);
	}
	//else, a level higher than current one already exists
	else
	{
		dlLevel = vLevels[iCurLevel+1];
	}

	iCurLevel++; //incrementing current level counter
}

void Game::DownLevel()
{
	iCurLevel--;
	dlLevel = vLevels[iCurLevel];
}
