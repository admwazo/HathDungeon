// Include guard:
#ifndef _Creature_Included_
#define _Creature_Included_

#include "Entity.h"
#include <vector>
#include <ostream>
#include <string>

class Item;	//forward declaration...???? why?

class Creature : public Entity
{
public:
	Creature(); // constructor
	~Creature(); // deconstructor
	virtual int getLevel();
	virtual void setLevel(int iLevel);
	virtual int getHP();
	virtual void setHP(int iHP);
	virtual int getMaxHP();
	virtual void setMaxHP(int iMaxHP);
	//virtual void setInventory(std::vector<Item*> inventory);
	//virtual std::vector<Item*> getInventory();
	
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int level;
	int HP;
	int maxHP;
	std::vector<Item*> inventory;
};

// End of the include guard:
#endif