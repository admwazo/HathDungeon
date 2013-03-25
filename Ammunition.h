// Include guard:
#ifndef _Ammunition_Included_
#define _Ammunition_Included_

#include "Item.h"
#include <ostream>
#include <string>

class Ammunition : public Item
{
public:
	Ammunition(); // constructor
	~Ammunition(); // deconstructor
	virtual void memberName();
	virtual std::string getType();
	virtual void setType(std::string sType);
	virtual int getDamageBonus();
	virtual void setDamageBonus(int iDamageBonus);
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int damageBonus;
	std::string type;
};

// End of the include guard:
#endif