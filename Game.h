#ifndef _Game_Included_
#define _Game_Included_

#include <iostream>
#include <vector>

class DungeonLevel;

class Game
{
	private:
		int iCurLevel;
		std::vector<DungeonLevel*> vLevels;
	public:
		Game();
		~Game();
		virtual void Play();
		virtual DungeonLevel* UpLevel();
		virtual DungeonLevel* DownLevel();
};

#endif
