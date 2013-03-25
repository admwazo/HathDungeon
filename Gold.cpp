#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Gold.h"

using namespace std;


Gold::Gold()
{

}

Gold::~Gold()
{

}

void Gold::pickUp()
{

}

// dumps contents of objects to console. overridden in every derived class.
void Gold::dumpObject()
{
	cout << '\t' << "Gold" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Gold::dumpObjectData()
{
	Item::dumpObjectData();
}

// writes current object as an xml fragment to specified output
void Gold::writeFragment(ostream & output)
{
	output << '\t' << "<Gold>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Gold>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Gold::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Gold::setElementData(string sElementName, string sContent)
{
	Item::setElementData(sElementName, sContent);
}
