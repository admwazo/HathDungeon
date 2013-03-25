#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Weapon.h"

using namespace std;


Weapon::Weapon()
{
	damage = I_DEFAULT;
	accuracy = I_DEFAULT;
	range = I_DEFAULT;
	ammoType = S_DEFAULT;
	type = S_DEFAULT;
}

Weapon::~Weapon()
{

}

int Weapon::getDamage()
{
	return damage;
}

void Weapon::setDamage(int iDamage)
{
	damage = iDamage;
}

int Weapon::getAccuracy()
{
	return accuracy;
}

void Weapon::setAccuracy(int iAccuracy)
{
	accuracy = iAccuracy;
}

long Weapon::getRange()
{
	return range;
}

void Weapon::setRange(long lRange)
{
	range = lRange;
}

string Weapon::getAmmoType()
{
	return ammoType;
}

void Weapon::setAmmoType(string sAmmoType)
{
	ammoType = sAmmoType;
}

string Weapon::getType()
{
	return type;
}

void Weapon::setType(string sType)
{
	type = sType;
}

// dumps contents of objects to console. overridden in every derived class.
void Weapon::dumpObject()
{
	cout << '\t' << "Weapon" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Weapon::dumpObjectData()
{
	Item::dumpObjectData();

	// And output the variables unique to
	// Consumable.
	cout << '\t' << '\t' << "Damage = " << getDamage() << endl;
	cout << '\t' << '\t' << "Type = " << getType() << endl;
	cout << '\t' << '\t' << "Accuracy = " << getAccuracy() << endl;
	cout << '\t' << '\t' << "Range = " << getRange() << endl;
	cout << '\t' << '\t' << "Ammo Type = " << getAmmoType() << endl;
}


// writes current object as an xml fragment to specified output
void Weapon::writeFragment(ostream & output)
{
	output << '\t' << "<Weapon>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Weapon>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Weapon::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output << '\t' << '\t' << "<damage>" << getDamage() 
		<< "</damage>" << endl;
	output << '\t' << '\t' << "<type>" << getType() 
		<< "</type>" << endl;
	output << '\t' << '\t' << "<accuracy>" << getAccuracy() 
		<< "</accuracy>" << endl;
	output << '\t' << '\t' << "<range>" << getRange() 
		<< "</range>" << endl;
	output << '\t' << '\t' << "<ammoType>" << getAmmoType() 
		<< "</ammoType>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Weapon::setElementData(string sElementName, string sContent)
{
	Item::setElementData(sElementName, sContent);

	if (sElementName == "damage")
		setDamage(atoi(sContent.c_str()));
	else if (sElementName == "type")
		setType(sContent);
	else if (sElementName == "accuracy")
		setAccuracy(atoi(sContent.c_str()));
	else if (sElementName == "range")
		setRange(atol(sContent.c_str()));
	else if (sElementName == "ammoType")
		setAmmoType(sContent);
}
