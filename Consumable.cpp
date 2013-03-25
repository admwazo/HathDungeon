#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Consumable.h"

using namespace std;


Consumable::Consumable()
{
	health = I_DEFAULT;
	nutrition = I_DEFAULT;
}

Consumable::~Consumable()
{

}

void Consumable::Use()
{

}

int Consumable::getHealth()
{
	return health;
}

void Consumable::setHealth(int iHealth)
{
	health = iHealth;
}

int Consumable::getNutrition()
{
	return nutrition;
}

void Consumable::setNutrition(int iNutrition)
{
	nutrition = iNutrition;
}

// dumps contents of objects to console. overridden in every derived class.
void Consumable::dumpObject()
{
	cout << '\t' << "Consumable" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Consumable::dumpObjectData()
{
	Item::dumpObjectData();

	// And output the variables unique to
	// Consumable.
	cout << '\t' << '\t' << "Health = " << getHealth() << endl;
	cout << '\t' << '\t' << "Nutrition = " << getNutrition() << endl;
}

// writes current object as an xml fragment to specified output
void Consumable::writeFragment(ostream & output)
{
	output << '\t' << "<Consumable>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Consumable>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Consumable::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output << '\t' << '\t' << "<health>" << getHealth() 
		<< "</health>" << endl;
	output << '\t' << '\t' << "<nutrition>" << getNutrition() 
		<< "</nutrition>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Consumable::setElementData(string sElementName, string sContent)
{
	Item::setElementData(sElementName, sContent);

	if (sElementName == "health")
		setHealth(atoi(sContent.c_str()));
	else if (sElementName == "nutrition")
		setNutrition(atoi(sContent.c_str()));
}
