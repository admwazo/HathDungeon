// Include guard:
#ifndef _Entity_Included_
#define _Entity_Included_

#include "XMLSerializable.h"
#include <string>
#include <vector>
#include <ostream>

class Entity : public XMLSerializable
{
public:
	Entity(); // constructor
	~Entity(); // deconstructor
	virtual std::string getDescription();
	virtual void setDescription(std::string sDescription);
	virtual bool hasProperty(std::string value);
	virtual std::vector<std::string> getProperties();
	virtual void setProperties(std::string sProperties);
	virtual std::string getName();
	virtual void setName(std::string sName);
	virtual char getDisplayChar();
	virtual void setDisplayChar(char cDisplayChar);
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	std::string name;
	std::vector<std::string> properties;
	char displayChar;
};

// End of the include guard:
#endif
