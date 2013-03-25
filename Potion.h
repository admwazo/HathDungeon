// Include guard:
#ifndef _Potion_Included_
#define _Potion_Included_

#include <ostream>
#include <string>
#include "Consumable.h"

class Potion : public Consumable
{
public:
	Potion(); // constructor
	~Potion(); // deconstructor
	virtual void Use();
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:

};

// End of the include guard:
#endif