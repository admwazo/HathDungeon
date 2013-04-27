#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <istream>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Armor.h"
#include "Weapon.h"
#include "Game.h"
#include "DungeonLevel.h"
#include "Player.h"
#include "Creature.h"
#include "Tile.h"
#include <cmath>
#include <ncurses.h>

using namespace std;

Game::Game()
{
	iCurLevel = 0;
	p_Player = new Player();
	cPlayer = p_Player->getDisplayChar();
	iMoves = 0;
	
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	int raw(void);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	
	//setting ssBorder
    string sBorder = "==============================================================================";
	ssBorder << sBorder;

	//setting ssMessageBox
    ssMessageBox << sBorder << endl
                 << "==                                                                          ==" << endl
                 << sBorder << endl;
	
	//setting ssFight
    ifstream stream_fight("./graphics/fight.txt");
    buffer_fight << stream_fight.rdbuf();	
	
	//setting intro
    ifstream stream_intro("./graphics/dungeon.txt");
    buffer_intro << stream_intro.rdbuf();

	DownLevel();
}

Game::~Game()
{
	stringstream ssEnd;
	ssEnd << "HathDungeon hath claimed another soul... Your score was: " << p_Player->getLevel();

	Display(ssEnd.str().c_str());
	sleep(1);
	endwin();
}

bool Game::Turn()
{
	int input = getch();
	
	if(input == 'q')
		return false;
	else if(input == KEY_UP)
	{
		Move("up", p_Player);
		DriveCreatures();
	}
	else if(input == KEY_DOWN)
	{
		Move("down", p_Player);
		DriveCreatures();
	}
	else if(input == KEY_LEFT)
	{
		Move("left", p_Player);
		DriveCreatures();
	}
	else if(input == KEY_RIGHT)
	{
		Move("right", p_Player);
		DriveCreatures();
	}
	else if(input == 'h')
		Help();
	else if(input == 'p')
		Pickup();
	else if(input == '0')
		p_Player->SetIActive(0);
	else if(input == '1')
		p_Player->SetIActive(1);
	else if(input == '2')
	    p_Player->SetIActive(2);
	else if(input == '3')
	    p_Player->SetIActive(3);
	else if(input == '4')
		p_Player->SetIActive(4);
	else if(input == 'u')
		p_Player->Use(p_Player->GetIActive());
	else if(input == 'd')
		Drop();
	
	return true;
}

void Game::Drop()
{
	if(p_Player->GetItem(1) != NULL)
    {
    	if(p_Player->GetIActive() == p_Player->GetWeapon())
        {
        	Display("Can't drop your weapon!...Press any key to continue");
            getch();
            return;
        }
		if(p_Player->GetIActive() == p_Player->GetArmor())
		{
			p_Player->SetArmor(NULL);
		}
        p_Player->Drop(p_Player->GetIActive());
        p_Player->SetIActive(0);
    }
    else
    {
     	Display("Can't drop your last item!...Press any key to continue");
        getch();
	}
}

void Game::DriveCreatures()
{
	iMoves++; //incrementing iMoves++ because if DriveCreatures is called, then the player just moved	

	Tile* t_CurTile = p_Player->GetTile();
	vector<Creature*> vCreatures = dlLevel->GetVCreatures();

	for(int i = 0; i < vCreatures.size(); i++)
	{
		int iX1 = vCreatures[i]->getPosX();
		int iY1 = vCreatures[i]->getPosY();
		int iX2 = p_Player->getPosX();
		int iY2 = p_Player->getPosY();
		bool xClose = false;	

		int dist = sqrt(pow((iX2 - iX1),2) + pow((iY2 - iY1),2));

		if((dist >= -1)&&(dist <= 1))
			Attack(vCreatures[i]);	

		//if creatureX > playerX and they are within 10 tiles
		else if(dist <= 10)
		{
			if(iX1 > iX2)	
				Move("left", vCreatures[i]);
			else
				Move("right", vCreatures[i]);
			if(iY1 > iY2)
				Move("up", vCreatures[i]);
			else
				Move("down", vCreatures[i]);
		}
	}
}

bool Game::Attack(Creature* c_Creature)
{
	clear();

    ifstream stream_avatar(c_Creature->getGraphic());
    stringstream buffer_avatar;
    buffer_avatar << stream_avatar.rdbuf();
	
	//fight sequence graphic	
	move(0,0);
	addstr(buffer_fight.str().c_str());
	refresh();	

	sleep(1);
	
	int reply;
	do{
		clear();		
		
		//creature inventory
		stringstream ssCreInventory;
		vector<string> vCreInventory = c_Creature->GetInventory();

		ssCreInventory << c_Creature->getName() << " using " << vCreInventory[0] << " || Health: " << c_Creature->getHP() << endl;
		move(0,0);
		addstr(ssCreInventory.str().c_str());

		//border
		move(1,0);
		addstr(ssBorder.str().c_str());
		
		//creature avatar
		move(2,0);
		addstr(buffer_avatar.str().c_str());	
		
		//controls
		stringstream ssControls;
		ssControls << "       || (a) to attack! || (r) to run! ||" << endl;
		move(18,0);
		addstr(ssControls.str().c_str());

		//border
		move(19,0);
		addstr(ssBorder.str().c_str());
    	
		//status
		stringstream ssStatus;
		ssStatus << "{ GAME STATUS } Level: " << iCurLevel << " || Health: " << p_Player->getHP() <<  " || XP: " <<
            p_Player->GetXP() << " || Evolution: " << p_Player->getLevel() << endl;
		move(20,0);
		addstr(ssStatus.str().c_str());

		refresh();		

		reply = getch();
		if(reply == 'k')
			{
                    dlLevel->KillCreature(c_Creature);
                    break;
			}
		if(reply == 'a')
			{
				//increasing players experience points and checking for a level up
 		        p_Player->SetXP(p_Player->GetXP() + c_Creature->getLevel());
				if(p_Player->GetXP() > ((p_Player->getLevel() + 1) * 3))
				{
					p_Player->SetXP(0);
					p_Player->LevelUp();
					Display("Congratulations, you evolved!");
					sleep(1);
				}
				Weapon* w_CreWeapon = c_Creature->GetWeapon();
				Weapon* w_PlaWeapon = p_Player->GetWeapon();
				Armor* a_PlaArmor = p_Player->GetArmor();
				//dealing damage
				c_Creature->setHP((c_Creature->getHP()) - ((w_PlaWeapon->getDamage() * 2 )));
				if(a_PlaArmor != NULL)
					p_Player->setHP((p_Player->getHP()) - (w_CreWeapon->getDamage() - a_PlaArmor->getArmorValue()));
				else
                    p_Player->setHP((p_Player->getHP()) - (w_CreWeapon->getDamage()));

                if(p_Player->getHP() < 0)
                {
                    break;
                }
				if(c_Creature->getHP() < 0)
				{
					dlLevel->KillCreature(c_Creature);
					move(11,0);
					addstr(ssMessageBox.str().c_str());

					move(12,35);
					string sVictory = "Victory!!!";
					addstr(sVictory.c_str());
					refresh();
					sleep(1);
					break;
				}
			}
	}while(reply != 'r');
}

void Game::Pickup()
{
	clear();

	int iIndex;
	Tile* t_CurTile = p_Player->GetTile();	//getting current tile
	vector<string> vsInventory = t_CurTile->GetInventory();
	if(vsInventory.size() > 0)
	{
		//displaying inventory of tile
		stringstream ss;
		ss << "Which item would you like to pick up?  (q) to quit ";
		for(int i = 0; i < vsInventory.size(); i++)
			{
				ss << "(" << i << ") " << vsInventory[i] << " ";
			}
		Display(ss.str()); //sending the tile inventory to display to show
		int x = getch();
		
		//making sure players inventory not full
		if(p_Player->GetItem(4) != NULL)
		{
			stringstream ssInventoryFull;
			ssInventoryFull << "Inventory is full!... Press any key to continue";
			Display(ssInventoryFull.str());
			getch();
			return;
		}
		//because of ncurses getch returns integers as ascii
		int y = (x - 48);
		//if player chose quit
		if(x == 'q')
			return;
		//getting item
		Item* i_Item = t_CurTile->GetItem(y);
		if(i_Item != NULL)
		{
			//casting as weapon/armor
			Armor* a_Temp = dynamic_cast<Armor*>(i_Item);
			Weapon* w_Temp = dynamic_cast<Weapon*>(i_Item);
			if(w_Temp != NULL)
			{
				p_Player->Drop(p_Player->GetWeapon());
			}
			if(a_Temp != NULL)
			{
				if(p_Player->GetArmor() != NULL)
					p_Player->Drop(p_Player->GetArmor());
			}
			//adding the item either way, because it's valid
            p_Player->AddItem(i_Item);  //giving the player the item pointer
			p_Player->SetIActive(p_Player->GetInventory().size() - 1);
		}
		else
		{
			Display("Incorrect selection... Press any key to continue");
			getch();
		}
	}
	else
	{
		Display("Nothing to pick up here... Press any key to continue");
		getch();
	}	
}

bool Game::Play()
{
	clear();
	move(0,0);
	addstr(buffer_intro.str().c_str());
	move(7,19);
	string sIntro = "{...Press any key...}";
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	addstr(sIntro.c_str());
	attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
	refresh();
	getch();

	Display("What is your warriors name: ");
	move(12,40);
	char str[80];
	getstr(str);
	stringstream ss;
	ss << str;
	p_Player->setName(ss.str());

	Display("");

	while(Turn() && (p_Player->getHP() > 0))
	{
		if(iMoves > 15)
		{
			dlLevel->SpawnElements();
			iMoves = 0;
		}
		Display("");
	}
	return false;
}

void Game::Display(string sInGameMsg)
{
	//clearing screen
	clear();

	//displaying the player inventory
	int iCount = 0;
	int iDone;
	stringstream ssInventory;
	vector<string> vInventory = p_Player->GetInventory();
	ssInventory << p_Player->getName() << " Inventory ||";
	Item* i_Active = p_Player->GetIActive();

	for(int i = 0; i < vInventory.size(); i++)
	{
		Item* i_Item = p_Player->GetItem(i);	
		ssInventory << "  (" << i << ") ";
		iCount += ((ssInventory.str()).size() - iCount);
		if(i_Item == i_Active)
			iDone = iCount;
		ssInventory << vInventory[i];
	}

	//displaying inventory
	move(0,0);
	addstr(ssInventory.str().c_str());

	//displaying active item
	move(0,iDone);
	attron(A_BOLD);
	addstr(i_Active->getName().c_str());
	attroff(A_BOLD);

	//displaying the char vector
	vector<vector<char>> vvChars = dlLevel->Dump();

    for(size_t x = 0; x <= dlLevel->GetEndColumn(); x++)
    {
        for(size_t y = 0; y <= dlLevel->GetEndRow(); y++)
        {
            move(y+1,x+1);
            addch(vvChars[y][x]);
        }
    }

	//displaying the player
	move(p_Player->getPosY()+1,p_Player->getPosX()+1);
	attron(COLOR_PAIR(1));
	addch(cPlayer);
	attroff(COLOR_PAIR(1));

	//displaying the monsters
    vector<Creature*> vCreatures = dlLevel->GetVCreatures();
    for(int i = 0; i < vCreatures.size(); i++)
    {
		move(vCreatures[i]->getPosY()+1,vCreatures[i]->getPosX()+1);
		attron(COLOR_PAIR(2));
		addch(vCreatures[i]->getDisplayChar());
		attroff(COLOR_PAIR(2));
	}
	
	//displaying the ingame messagebox
	if(sInGameMsg != "")
	{
		//adding box
		move(11,0);
		addstr(ssMessageBox.str().c_str());

		//displaying the ingame message
		stringstream ssInGameMsg;
		ssInGameMsg << sInGameMsg;
		move(12,10);
		addstr(ssInGameMsg.str().c_str());
	}

	//adding border
	move(21,0);
	addstr(ssBorder.str().c_str());

	//adding status
	stringstream ssStatus;
	ssStatus << "{ GAME STATUS } Level: " << iCurLevel << " || Health: " << p_Player->getHP() <<  " || XP: " <<
        p_Player->GetXP() << " || Evolution: " << p_Player->getLevel() << " || (q) to quit";
	move(22,0);
	addstr(ssStatus.str().c_str());

	refresh();
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
		cout << "wrong param" << endl;
	}	

	//saving the tile to move to
	Tile* t_Temp = dlLevel->GetTileObj(iToPosY, iToPosX);
	
	//if the tile can be inhabited by all actors and there is no actor on tile
    if((t_Temp->IsGoodE())&&(t_Temp->GetActor() == NULL))
    {
	    c_Actor->SetTile(t_Temp);
	}

	//if actor is not the player, move is complete
	if(c_Actor != p_Player)
	{
		return;
	}

	if(t_Temp == dlLevel->GetUpStairs())
	{
		UpLevel();
	}
	
	else if(t_Temp == dlLevel->GetDownStairs())
	{
		DownLevel();
	}
}

//Cycles thru vector of DL objects, and returns one higher than what iCurLevel is set to
void Game::DownLevel()
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
	dlLevel->SetLevel(iCurLevel);
	p_Player->SetTile(dlLevel->GetUpStairs());
}

void Game::UpLevel()
{
	if(iCurLevel == 1)
	{
		p_Player->setHP(0);
		return;
	}
	int iCol, iRow;
	iCurLevel--;	//decrement current level counter
	dlLevel = vLevels[iCurLevel-1];	//accessing level in index (vLevels[0] == level 1)
	
	p_Player->SetTile(dlLevel->GetDownStairs());
}

void Game::Help()
{
	clear();
	stringstream ssHelp;	

	Tile* t_Tile = p_Player->GetTile();
	vector<string> vsInventory = t_Tile->GetInventory();
	
	ssHelp << "HathDungeon Help: " << endl << endl

	<< "Active item is [" << (p_Player->GetIActive())->getName() << "] and Weapon is [" << (p_Player->GetWeapon())->getName() << "]" << endl << endl

		 << '\t' << "Controls: " << endl
		 << '\t' << '\t' << "up key     - Move Player Up " << endl
		 << '\t' << '\t' << "down key   - Move Player Down " << endl
		 << '\t' << '\t' << "left key   - Move Player Left " << endl
		 << '\t' << '\t' << "right key  - Move Player Right " << endl
	 	 << '\t' << '\t' << "Numbers    - Cycle through items in inventory " << endl
		 << '\t' << '\t' << "p          - Pickup Item " << endl
		 << '\t' << '\t' << "u          - Use Current Item " << endl
		 << '\t' << '\t' << "d			- Drop Current Item " << endl
		 << '\t' << '\t' << "k			- AutoKill (cheat) " << endl << endl
		 << "Press any key to return to the game: " << endl;
	move(0,0);
	addstr(ssHelp.str().c_str());
	refresh();
	getch();
}
