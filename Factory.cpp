#include "Factory.h"
#include "XMLSerializable.h"
#include "Parser.h"
#include "Creature.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

#include <vector>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

Factory & Factory::Instance()
{
    static Factory factory;

    return factory;
}

Factory::Factory()
{
    mtRandom.seed((unsigned int) time(NULL));

    ifstream input;
    input.open("test.xml");

    vector<XMLSerializable*> vObjects;
	
    parseXML(vObjects, input);

    for( auto it = vObjects.begin();
        it != vObjects.end();
        it++ )
    {
        //use dynamic_cast because it will return a NULL pointer
        //if (*it) is not of Creature* type
        Creature* c_Creature = dynamic_cast<Creature*>(*it);
		Item* i_Item = dynamic_cast<Item*>(*it);
		Weapon* w_Weapon = dynamic_cast<Weapon*>(*it);
		Potion* p_Potion = dynamic_cast<Potion*>(*it);

		if(p_Potion != NULL)
		{
			vPotions.push_back(p_Potion);
		}
        if(c_Creature != NULL)
        {
            vCreatures.push_back(c_Creature);
        }

		if(w_Weapon != NULL)
		{
			vWeapons.push_back(w_Weapon);
		}

        if(i_Item != NULL)
        {
            vItems.push_back(i_Item);
        }

    }
}

Factory::~Factory()
{

}

Creature* Factory::GenerateCreature(int iMaxLevel)
{
    vector<Creature*> vProperCreatures;

    for( auto it = vCreatures.begin();
        it != vCreatures.end();
        it++)
    {
        if((*it)->getLevel() <= iMaxLevel)
        {
            vProperCreatures.push_back(*it);
        }
    }

    if(vProperCreatures.size() != 0)
    {
        int iIndex = (mtRandom() % vProperCreatures.size());
        Creature* c_Creature = vProperCreatures[iIndex];

        //use copy constructor to return a copy that is a seperate object
        Creature* pReturnValue = new Creature(*c_Creature);

		//arming creature
		pReturnValue->AddItem(GenerateWeapon());
		
        return pReturnValue;
    }

    return NULL;
}

/*
Item* Factory::GenerateItem()
{
	vector<Item*> vProperItems;

	for(auto it = vItems.begin();
		it != vItems.end();
		it++)
	{
		//need something here to validate proper item
		vProperItems.push_back(*it);
	}

	if(vProperItems.size() != 0)
	{
		int iIndex = (mtRandom() % vProperItems.size());
		Item* i_Item = vProperItems[iIndex];

		Item* pReturnValue = new Item(*i_Item);
		return pReturnValue;
	}

	return NULL;
}
*/

Item* Factory::GenerateItem()
{
	int iIndex = (mtRandom() % vItems.size());
    
    Weapon* w_Weapon = dynamic_cast<Weapon*>(vItems[iIndex]);
    Potion* p_Potion = dynamic_cast<Potion*>(vItems[iIndex]);
	Armor* a_Armor = dynamic_cast<Armor*>(vItems[iIndex]);

    if(p_Potion != NULL)
    {
        Potion* pReturn = new Potion(*p_Potion);
		return pReturn;
    }
    if(w_Weapon != NULL)
    {
		Weapon* pReturn = new Weapon(*w_Weapon);
		return pReturn;
    }
	if(a_Armor != NULL)
	{
		Armor* pReturn = new Armor(*a_Armor);
		return pReturn;
	}
	
	return NULL;
}

Weapon* Factory::GenerateWeapon()
{
    vector<Weapon*> vProperWeapons;

    for(auto it = vWeapons.begin();
        it != vWeapons.end();
        it++)
    {
        //need something here to validate proper item
        vProperWeapons.push_back(*it);
    }

    if(vProperWeapons.size() != 0)
    {
        int iIndex = (mtRandom() % vProperWeapons.size());
        Weapon* w_Weapon = vProperWeapons[iIndex];

        Weapon* pReturnValue = new Weapon(*w_Weapon);
        return pReturnValue;
    }

    return NULL;
}

Item* Factory::GenerateItem(string sItem)
{
	if(vItems.size() != 0)
	{
		for(int i = 0; i < vItems.size(); i++)
		{
			if(vItems[i]->getName() == sItem)
				return(vItems[i]);
		}
	}
}
