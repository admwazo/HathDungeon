#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Armor.h"

using namespace std;


Armor::Armor()
{
	armorValue = I_DEFAULT;
	slot = S_DEFAULT;
	type = S_DEFAULT;
}

Armor::~Armor()
{

}

int Armor::getArmorValue()
{
	return armorValue;
}

void Armor::setArmorValue(int iArmorValue)
{
	armorValue = iArmorValue;
}

string Armor::getSlot()
{
	return slot;
}

void Armor::setSlot(string sSlot)
{
	slot = sSlot;
}

string Armor::getType()
{
	return type;
}

void Armor::setType(string sType)
{
	type = sType;
}

// dumps contents of objects to console. overridden in every derived class.
void Armor::dumpObject()
{
	cout << '\t' << "Armor" <<endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Armor::dumpObjectData()
{
	Item::dumpObjectData();

	// And output the variables unique to
	// Consumable.
	cout << '\t' << '\t' << "Slot = " << getSlot() << endl;
	cout << '\t' << '\t' << "Type = " << getType() << endl;
	cout << '\t' << '\t' << "Armor Value = " << getArmorValue() << endl;
}

// writes current object as an xml fragment to specified output
void Armor::writeFragment(ostream & output)
{
	output << '\t' << "<Armor>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Armor>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Armor::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output << '\t' << '\t' << "<slot>" << getSlot() 
		<< "</slot>" << endl;
	output << '\t' << '\t' << "<type>" << getType() 
		<< "</type>" << endl;
	output << '\t' << '\t' << "<armorValue>" << getArmorValue() 
		<< "</armorValue>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Armor::setElementData(string sElementName, string sContent)
{
	Item::setElementData(sElementName, sContent);

	if (sElementName == "armorValue")
		setArmorValue(atoi(sContent.c_str()));
	else if (sElementName == "type")
		setType(sContent);
	else if (sElementName == "slot")
		setSlot(sContent);
}
