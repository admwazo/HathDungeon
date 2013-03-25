// Include guard:
#ifndef _Gold_Included_
#define _Gold_Included_

#include "Item.h"
#include <ostream>
#include <string>

class Gold : public Item
{
public:
	Gold(); // constructor
	~Gold(); // deconstructor
	virtual void pickUp();
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