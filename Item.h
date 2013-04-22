// Include guard:
#ifndef _Item_Included_
#define _Item_Included_

#include "Entity.h"
#include <string>
#include <ostream>

class Item : public Entity
{
public:
	Item(); // constructor
	~Item(); // deconstructor
	virtual std::string getDescription();
	virtual void pickup();
	virtual int getWeight();
	virtual void setWeight(int iWeight);
	virtual int getValue();
	virtual void setValue(int iValue);
	virtual int getRarity();
	virtual void setRarity(int iRarity);
	virtual int getEnchantment();
	virtual void setEnchantment(int iEnchantment);
	virtual int getQuantity();
	virtual void setQuantity(int iQuantity);
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int weight;
	int value;
	int rarity;
	int enchantment;
	int quantity;
};

// End of the include guard:
#endif
