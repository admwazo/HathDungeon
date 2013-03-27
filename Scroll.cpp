#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Scroll.h"

using namespace std;


Scroll::Scroll()
{

}

Scroll::~Scroll()
{

}

void Scroll::Use()
{

}

// dumps contents of objects to console. overridden in every derived class.
void Scroll::dumpObject()
{
	cout << '\t' << "Scroll" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Scroll::dumpObjectData()
{
	Consumable::dumpObjectData();
}

// writes current object as an xml fragment to specified output
void Scroll::writeFragment(ostream & output)
{
	output << '\t' << "<Scroll>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Scroll>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Scroll::writeDataAsFragment(ostream & output)
{
	Consumable::writeDataAsFragment(output);
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Scroll::setElementData(string sElementName, string sContent)
{
	Consumable::setElementData(sElementName, sContent);
}
