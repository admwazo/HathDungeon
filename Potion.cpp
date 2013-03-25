#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Potion.h"

using namespace std;


Potion::Potion()
{

}

Potion::~Potion()
{

}

void Potion::Use()
{

}

// dumps contents of objects to console. overridden in every derived class.
void Potion::dumpObject()
{
	cout << '\t' << "Potion" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Potion::dumpObjectData()
{
	Consumable::dumpObjectData();
}

// writes current object as an xml fragment to specified output
void Potion::writeFragment(ostream & output)
{
	output << '\t' << "<Potion>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Potion>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Potion::writeDataAsFragment(ostream & output)
{
	Consumable::writeDataAsFragment(output);
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Potion::setElementData(string sElementName, string sContent)
{
	Consumable::setElementData(sElementName, sContent);
}
