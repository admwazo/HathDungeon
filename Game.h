#ifndef _Game_Included_
#define _Game_Included_

#include <iostream>
#include <vector>
#include <string>

#include "Player.h"
#include "Creature.h"
#include <cmath>
#include <ncurses.h>

class Player;
class DungeonLevel;
class Creature;

class Game
{
	private:
		int iCurLevel; //level counter
		DungeonLevel* dlLevel; //current level
		std::vector<DungeonLevel*> vLevels; //vector of levels
		Player* p_Player; //game player
		char cPlayer; //holds the avatar for player
		int iMoves;		

		//graphics
		std::stringstream ssBorder;
		std::stringstream ssMessageBox;
		std::stringstream buffer_fight;
	public:
		Game();
		~Game();
		virtual bool Play();
		virtual void UpLevel();
		virtual void DownLevel();
		virtual bool Turn();
		virtual void Move(std::string sDirection, Creature* c_Actor);
		virtual void Display(std::string sInGameMsg);
		virtual void Pickup();
		virtual void Help();
		virtual void DriveCreatures();
		virtual void Drop();
		virtual bool Attack(Creature* c_Creature); 
};

#endif
