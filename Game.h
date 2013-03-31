#ifndef _Game_Included_
#define _Game_Included_

#include <iostream>
#include <vector>

#include "Player.h"

class Player;
class DungeonLevel;

class Game
{
	private:
		int iCurLevel;
		DungeonLevel* dlLevel;
		std::vector<DungeonLevel*> vLevels;
		Player pPlayer;
		char cTemp;
	public:
		Game();
		~Game();
		virtual bool Play();
		virtual void UpLevel();
		virtual void DownLevel();
		virtual bool Turn();
};

#endif
