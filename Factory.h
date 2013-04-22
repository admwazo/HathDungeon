#ifndef _Factory_Included_
#define _Factory_Included_

#include "Factory.h"
#include "Item.h"
#include "Creature.h"
#include "XMLSerializable.h"
#include "Parser.h"

#include <vector>
#include <random>
#include <string>

class Factory
{
	public:
		static Factory & Instance();
		virtual ~Factory();
		virtual Creature* GenerateCreature(int iMaxLevel);
		virtual Item* GenerateItem();
		virtual Item* GenerateItem(std::string sItem);
		virtual Weapon* GenerateWeapon();
	
	private:
		Factory();
		std::vector<Creature*> vCreatures;
		std::vector<Item*> vItems;
		std::vector<Weapon*> vWeapons;
		std::vector<Potion*> vPotions;
		std::mt19937 mtRandom;
};

#endif
