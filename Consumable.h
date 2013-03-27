// Include guard:
#ifndef _Consumable_Included_
#define _Consumable_Included_

#include "Item.h"
#include <ostream>
#include <string>

class Consumable : public Item
{
public:
	Consumable(); // constructor
	~Consumable(); // deconstructor
	virtual void Use();
	virtual int getHealth();
	virtual void setHealth(int iHealth);
	virtual int getNutrition();
	virtual void setNutrition(int iNutrition);
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int health;
	int nutrition;
};

// End of the include guard:
#endif