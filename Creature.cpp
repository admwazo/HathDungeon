#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Creature.h"

using namespace std;


Creature::Creature()
{
	level = I_DEFAULT;
	HP = I_DEFAULT;
	maxHP = I_DEFAULT;
}

Creature::~Creature()
{

}

int Creature::getPosX()
{
	return iPosX;
}

void Creature::setPosX(int x)
{
	iPosX = x;
}

int Creature::getPosY()
{
	return iPosY;
}

void Creature::setPosY(int y)
{
	iPosY = y;
}

int Creature::getLevel()
{
	return level;
}

void Creature::setLevel(int iLevel)
{
	level = iLevel;
}

int Creature::getHP()
{
	return HP;
}

void Creature::setHP(int iHP)
{
	HP = iHP;
}

int Creature::getMaxHP()
{
	return maxHP;
}

void Creature::setMaxHP(int iMaxHP)
{
	maxHP = iMaxHP;
}
/*
void Creature::moveLeft()
{
	iPosX--;
}

void Creature::moveRight()
{
	iPosX++;
}

void Creature::moveUp()
{
	iPosY--;
}

void Creature::moveDown()
{
	iPosY++;
}
*/

/*
void setInventory(vector<Item*> inventory)
{

}

vector<Item*> getInventory()
{
	vector<Item*> inventory;
	return inventory;
}
*/

// dumps contents of objects to console. overridden in every derived class.
void Creature::dumpObject()
{
	cout << '\t' << "Creature" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Creature::dumpObjectData()
{
	Entity::dumpObjectData();

	// And output the variables unique to
	// Creature.
	cout << '\t' << '\t' << "Level = " << getLevel() << endl;
	cout << '\t' << '\t' << "HP = " << getHP() << endl;
	cout << '\t' << '\t' << "MaxHP = " << getMaxHP() << endl;
	//cout << "  - Inventory = " << getInventory() << endl;
}

// writes current object as an xml fragment to specified output
void Creature::writeFragment(ostream & output)
{
	output << '\t' << "<Creature>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Creature>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Creature::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output << '\t' << '\t' << "<level>" << getLevel() 
		<< "</level>" << endl;
	output << '\t' << '\t' << "<hp>" << getHP() 
		<< "</hp>" << endl;
	output << '\t' << '\t' << "<maxHP>" << getMaxHP() 
		<< "</maxHP>" << endl;
	//output << "  <inventory>" << getInventory()
	//	<< "</inventory>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Creature::setElementData(string sElementName, string sContent)
{
	Entity::setElementData(sElementName, sContent);

	if (sElementName == "level")
		setLevel(atoi(sContent.c_str()));
	else if (sElementName == "hp")
		setHP(atoi(sContent.c_str()));
	else if (sElementName == "maxHP")
		setMaxHP(atoi(sContent.c_str()));
	//else if (sElementName == "inventory")
	//	setInventory(atoi(sContent.c_str()));
}
