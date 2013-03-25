#include <string>
#include <iostream>
#include <ostream>
#include <cstdlib>


#include "XMLSerializable.h"

using namespace std;

 // constructor
XMLSerializable::XMLSerializable()
{
	S_DEFAULT = "default";
	I_DEFAULT = 0;
	C_DEFAULT = '0';
}

 // deconstructor
XMLSerializable::~XMLSerializable()
{

}

// dumps contents of objects to console. overridden in every derived class.
void XMLSerializable::dumpObject()
{

}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void XMLSerializable::dumpObjectData()
{

}

// writes current object as an xml fragment to specified output
void XMLSerializable::writeFragment(ostream & output)
{

}

// writes data members of current object as xml fragment to specified output
void XMLSerializable::writeDataAsFragment(ostream & output)
{

}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void XMLSerializable::setElementData(string sElementName, string sContent)
{

}

