#include <vector>

#include "Game.h"
#include "DungeonLevel.h"
#include "Player.h"
#include "Creature.h"

using namespace std;

Game::Game()
{
	cTemp = '.'; 
	iCurLevel = 0;
	int iCol;
    int iRow;

	UpLevel();
    //spawning player
	cPlayer = p_Player.getDisplayChar();
    dlLevel->GetDownStairs(iRow, iCol);
	p_Player.setPosX(iCol);
	p_Player.setPosY(iRow);
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
		MoveUp(&p_Player);
	else if(input == 's')
		MoveDown(&p_Player);
	else if(input == 'a')
		MoveLeft(&p_Player);
	else if(input == 'd')
		MoveRight(&p_Player);
	else if(input == 'h');
		//help sequence
	else if(input == 'p');
		//pickup sequence
	else if(input == 32);
		//attack sequence
	else if(input == '1');
		//change to first item in inventory
	else if(input == '2');
		//change to second item in inventory
	else if(input == 'u');
		//use current holding item

	//Hunt(dlLevel->GetVMonsters());

	return true;
}

bool Game::Play()
{
	dlLevel->Display();
	while(Turn())
		dlLevel->Display();
	
	return false;
}

void Game::MoveLeft(Creature* c_Actor)
{
	int iPosY = c_Actor->getPosY();
	int iPosX = c_Actor->getPosX();
	char cTemp2 = dlLevel->Get(iPosY, iPosX-1);
	
	if((cTemp2 != '|')&&(cTemp2 != ' ')) //if forward tile is not a wall
	{
		dlLevel->Set(iPosY, iPosX, cTemp); //setting the dungeon tile to backward tile
		cTemp = cTemp2; //holding the current tile
		c_Actor->setPosX(iPosX-1); //setting updated pos of actor
		dlLevel->Set(iPosY, iPosX-1, cPlayer); //actually moving the player
	}
}

void Game::MoveRight(Creature* c_Actor)
{
    int iPosY = c_Actor->getPosY();
    int iPosX = c_Actor->getPosX();
    char cTemp2 = dlLevel->Get(iPosY, iPosX+1);

    if((cTemp2 != '|')&&(cTemp2 != ' ')) //if forward tile is not a wall
	{
        dlLevel->Set(iPosY, iPosX, cTemp); //setting the dungeon tile to backward tile
		cTemp = cTemp2;
        c_Actor->setPosX(iPosX+1); //setting updated pos of actor
        dlLevel->Set(iPosY, iPosX+1, cPlayer); //actually moving the player
    }
}

void Game::MoveUp(Creature* c_Actor)
{
    int iPosY = c_Actor->getPosY();
    int iPosX = c_Actor->getPosX();
    char cTemp2 = dlLevel->Get(iPosY-1, iPosX);

    if((cTemp2 != '-')&&(cTemp2 != ' ')) //if forward tile is not a wall
    {
        dlLevel->Set(iPosY, iPosX, cTemp); //setting the dungeon tile to backward tile
        cTemp = cTemp2;
		c_Actor->setPosY(iPosY-1); //setting updated pos of actor
        dlLevel->Set(iPosY-1, iPosX, cPlayer); //actually moving the player
    }
}

void Game::MoveDown(Creature* c_Actor)
{
    int iPosY = c_Actor->getPosY();
    int iPosX = c_Actor->getPosX();
    char cTemp2 = dlLevel->Get(iPosY+1, iPosX);

    if((cTemp2 != '-')&&(cTemp2 != ' ')) //if forward tile is not a wall
    {
        dlLevel->Set(iPosY, iPosX, cTemp); //setting the dungeon tile to backward tile
        cTemp = cTemp2;
		c_Actor->setPosY(iPosY+1); //setting updated pos of actor
        dlLevel->Set(iPosY+1, iPosX, cPlayer); //actually moving the player
    }
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
