#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <vector>
#include "Entity.h"

using namespace std;


Entity::Entity()
{
	name = S_DEFAULT;
	properties.push_back(S_DEFAULT);
	displayChar = C_DEFAULT;
}

Entity::~Entity()
{

}

bool Entity::hasProperty(string value)
{
	return (1 > 2);
}

vector<string> Entity::getProperties()
{
	return properties;
}

void Entity::setProperties(string sProperties)
{
	if (properties.at(0) == S_DEFAULT)
		properties.at(0) = sProperties;
	else
		properties.push_back(sProperties);
}

void Entity::setDescription(string sDescription)
{

}

string Entity::getDescription()
{
	string test = "test";
	return test;
}

string Entity::getName()
{
	return name;
}

void Entity::setName(string sName)
{
	name = sName;
}

char Entity::getDisplayChar()
{
	return displayChar;
}

void Entity::setDisplayChar(char cDisplayChar)
{
	displayChar = cDisplayChar;
}

// dumps contents of objects to console. overridden in every derived class.
void Entity::dumpObject()
{
	cout << '\t' << "Entity" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Entity::dumpObjectData()
{
	// And output the variables unique to
	// Entity.
	cout << '\t' << '\t' << "Name = " << getName() << endl;

	// Getting the vector of properties and iterating through
	vector<string> vProperties = getProperties();
	cout << '\t' << '\t' << "Properties" << endl;
	for(vector<string>::const_iterator it = vProperties.begin(); 
		it != vProperties.end(); it++ )
	{
		cout << '\t' << '\t' << '\t' << "Property = " << *it << endl;
	}
	cout << '\t' << '\t' << "Display Character = " << getDisplayChar() << endl;
}

// writes current object as an xml fragment to specified output
void Entity::writeFragment(ostream & output)
{
	output << '\t' << "<Entity>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Entity>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Entity::writeDataAsFragment(ostream & output)
{
	output << '\t' << '\t' << "<name>" << getName() 
		<< "</name>" << endl;
	output << '\t' << '\t' << "<properties>" << endl;

	// Getting the vector of properties and iterating through
	vector<string> vProperties = getProperties();
	for(vector<string>::const_iterator it = vProperties.begin(); 
		it != vProperties.end(); it++ )
	{
		output << '\t' << '\t' << '\t' << "<property>" << *it << "</property>" 
			<< endl;
	}

	output << '\t' << '\t' << "</properties>" << endl;
	output << '\t' << '\t' << "<displayChar>" << getDisplayChar() 
		<< "</displayChar>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Entity::setElementData(string sElementName, string sContent)
{
	if (sElementName == "name")
		setName(sContent);
	else if (sElementName == "property")
		setProperties(sContent);
	else if (sElementName == "displayChar")
		setDisplayChar(sContent.at(0));
}