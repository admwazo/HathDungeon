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
	cPlayer = p_Player.getDisplayChar();
	
	UpLevel();
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
		Move("up", &p_Player);
	else if(input == 's')
		Move("down", &p_Player);
	else if(input == 'a')
		Move("left", &p_Player);
	else if(input == 'd')
		Move("right", &p_Player);
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

void Game::Move(string sDirection, Creature* c_Actor)
{
	int iPosY, iPosX, iToPosY, iToPosX;	

	iPosY = c_Actor->getPosY();
	iPosX = c_Actor->getPosX();
	if(sDirection == "left")
	{
		iToPosX = iPosX-1;
		iToPosY = iPosY;
	}
	else if(sDirection == "right")
	{
		iToPosX = iPosX+1;
		iToPosY = iPosY;
	}
	else if(sDirection == "up")
	{
		iToPosY = iPosY-1;
		iToPosX = iPosX;
	}
	else if(sDirection == "down")
	{
		iToPosY = iPosY+1;
		iToPosX = iPosX;
	}
	else
	{
		cout << "Wrong parameter, should be: up/down/left/right" << endl;
	}
	
	char cTemp2 = dlLevel->Get(iToPosY, iToPosX);

	if(cTemp2 == '<')	//if we hit an upstairs tile
	{
		dlLevel->Set(iPosY, iPosX, cTemp); //reset current tile
		cTemp = '>';	//hold a downstairs tile for next turn, because we will be standing on one
		UpLevel();	//go up a level
	}

	else if(cTemp2 == '>')
	{
		dlLevel->Set(iPosY, iPosX, cTemp); //reset current tile
		cTemp = '<';	//hold an upstairs tile
		DownLevel();	//go down a level
	}	

	else if((cTemp2 != '|')&&(cTemp2 != ' ')&&(cTemp2 != '-'))
	{
		dlLevel->Set(iPosY, iPosX, cTemp);
		cTemp = cTemp2;
		c_Actor->setPosX(iToPosX);
		c_Actor->setPosY(iToPosY);
		dlLevel->Set(iToPosY, iToPosX, cPlayer);
	}
}

//Cycles thru vector of DL objects, and returns one higher than what iCurLevel is set to
void Game::UpLevel()
{
	int iCol, iRow;
	
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
		dlLevel = vLevels[iCurLevel];
	}

	iCurLevel++; //incrementing current level counter

	dlLevel->GetDownStairs(iRow, iCol);		//get position of next levels downstairs
	p_Player.setPosX(iCol);		//set players x pos
	p_Player.setPosY(iRow);		//set players y pos
	
	dlLevel->Set(iRow, iCol, cPlayer);	//set dungeon tile to display Player
}

void Game::DownLevel()
{
	int iCol, iRow;
	cout << "going down a level from iCurLevel: " << iCurLevel << endl;
	iCurLevel--;	//decrement current level counter
	cout << "now current level is: " << iCurLevel << endl;
	dlLevel = vLevels[iCurLevel-1];	//accessing level in index

	dlLevel->GetUpStairs(iRow, iCol);	//get position of lower level's upstairs
	p_Player.setPosX(iCol);		//set players x pos
	p_Player.setPosY(iRow);		//set players y pos

	dlLevel->Set(iRow, iCol, cPlayer);	//set dungeon til to display Player
}
