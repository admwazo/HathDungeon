#ifndef _Player_included_
#define _Player_included_

#include "Creature.h"
#include "Item.h"
#include <sstream>
#include <vector>
#include <string>

class Player : public Creature
{
	private:
		int XP;
		Item* i_Active; //holds the active item in inventory
		
	public:
		Player();
		~Player();
		virtual int GetXP();
		virtual void SetXP(int iXP2);
		virtual void SetIActive(int iIndex);
		virtual Item* GetIActive();
		virtual void Use(Item* i_Item);
		virtual void Drop(Item* i_Item);
		virtual void LevelUp();
};

#endif
