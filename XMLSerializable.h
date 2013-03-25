// Include guard:
#ifndef _XMLSerializable_Included_
#define _XMLSerializable_Included_

#include <string>
#include <ostream>

class XMLSerializable
{
public:
	XMLSerializable(); // constructor
	~XMLSerializable(); // deconstructor
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);
	
	// These are my default values for use in the program. They are initialized
	// in the XMLSerializable constructor
	std::string S_DEFAULT;
	int I_DEFAULT;
	char C_DEFAULT;

private:

};

// End of the include guard:
#endif
