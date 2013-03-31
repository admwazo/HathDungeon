#ifndef _Player_included_
#define _Player_included_

#include "Creature.h"

class Player : public Creature
{
	private:
		int XP;
		
	public:
		Player();
		~Player();
};

#endif
