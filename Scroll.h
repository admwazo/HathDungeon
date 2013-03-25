// Include guard:
#ifndef _Scroll_Included_
#define _Scroll_Included_

#include <ostream>
#include <string>
#include "Consumable.h"

class Scroll : public Consumable
{
public:
	Scroll(); // constructor
	~Scroll(); // deconstructor
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