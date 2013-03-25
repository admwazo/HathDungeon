// Include guard:
#ifndef _Armor_Included_
#define _Armor_Included_

#include <ostream>
#include <string>
#include "Item.h"


class Armor : public Item
{
public:
	Armor(); // constructor
	~Armor(); // deconstructor
	virtual int getArmorValue();
	virtual void setArmorValue(int iArmorValue);
	virtual std::string getSlot();
	virtual void setSlot(std::string sSlot);
	virtual std::string getType();
	virtual void setType(std::string sType);
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int armorValue;
	std::string slot;
	std::string type;
};

// End of the include guard:
#endif