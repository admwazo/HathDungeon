// Include guard:
#ifndef _Weapon_Included_
#define _Weapon_Included_

#include "Item.h"
#include <string>
#include <ostream>

class Weapon : public Item
{
public:
	Weapon(); // constructor
	~Weapon(); // deconstructor
	virtual int getDamage();
	virtual void setDamage(int iDamage);
	virtual int getAccuracy();
	virtual void setAccuracy(int iAccuracy);
	virtual long getRange();
	virtual void setRange(long lRange);
	virtual std::string getAmmoType();
	virtual void setAmmoType(std::string sAmmoType);
	virtual std::string getType();
	virtual void setType(std::string sType);
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int damage;
	int accuracy;
	long range;
	std::string ammoType;
	std::string type;
};

// End of the include guard:
#endif
