#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Ammunition.h"

using namespace std;


Ammunition::Ammunition()
{
	damageBonus = I_DEFAULT;
	type = S_DEFAULT;
}

Ammunition::~Ammunition()
{

}

void Ammunition::memberName()
{

}

int Ammunition::getDamageBonus()
{
	return damageBonus;
}

void Ammunition::setDamageBonus(int iDamageBonus)
{
	damageBonus = iDamageBonus;
}

string Ammunition::getType()
{
	return type;
}

void Ammunition::setType(string sType)
{
	type = sType;
}

// dumps contents of objects to console. overridden in every derived class.
void Ammunition::dumpObject()
{
	cout << '\t' << "Ammunition" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Ammunition::dumpObjectData()
{
	Item::dumpObjectData();

	// And output the variables unique to
	// Ammunition.
	cout << '\t' << '\t' << "Damage Bonus = " << getDamageBonus() << endl;
	cout << '\t' << '\t' << "Type = " << getType() << endl;
}

// writes current object as an xml fragment to specified output
void Ammunition::writeFragment(ostream & output)
{
	output << '\t' << "<Ammunition>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Ammunition>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Ammunition::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output << '\t' << '\t' << "<damageBonus>" << getDamageBonus() 
		<< "</damageBonus>" << endl;
	output << '\t' << '\t' << "<type>" << getType()
		<< "</type>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Ammunition::setElementData(string sElementName, string sContent)
{
	Item::setElementData(sElementName, sContent);

	if (sElementName == "damageBonus")
		setDamageBonus(atoi(sContent.c_str()));
	else if (sElementName == "type")
		setType(sContent);
}
