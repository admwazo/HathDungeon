#ifndef _Game_Included_
#define _Game_Included_

#include <iostream>
#include <vector>

#include "Player.h"
#include "Creature.h"

class Player;
class DungeonLevel;
class Creature;

class Game
{
	private:
		int iCurLevel; //level counter
		DungeonLevel* dlLevel; //current level
		std::vector<DungeonLevel*> vLevels; //vector of levels
		Player p_Player; //game player
		char cTemp; //holder for current tile
		char cPlayer; //holds the avatar for player
	public:
		Game();
		~Game();
		virtual bool Play();
		virtual void UpLevel();
		virtual void DownLevel();
		virtual bool Turn();
		virtual void MoveLeft(Creature* c_Actor);
		virtual void MoveRight(Creature* c_Actor);
		virtual void MoveDown(Creature* c_Actor);
		virtual void MoveUp(Creature* c_Actor); 
};

#endif
