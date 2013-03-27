#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Item.h"

using namespace std;


Item::Item()
{
	weight = I_DEFAULT;
	value = I_DEFAULT;
	rarity = I_DEFAULT;
	enchantment = I_DEFAULT;
	quantity = I_DEFAULT;
}

Item::~Item()
{

}


void Item::pickup()
{

}

string Item::getDescription()
{
	string test = "test";
	return test;
}

int Item::getWeight()
{
	return weight;
}

void Item::setWeight(int iWeight)
{
	weight = iWeight;
}

int Item::getValue()
{
	return value;
}

void Item::setValue(int iValue)
{
	value = iValue;
}

int Item::getRarity()
{
	return rarity;
}

void Item::setRarity(int iRarity)
{
	rarity = iRarity;
}

int Item::getEnchantment()
{
	return enchantment;
}

void Item::setEnchantment(int iEnchantment)
{
	enchantment = iEnchantment;
}

int Item::getQuantity()
{
	return quantity;
}

void Item::setQuantity(int iQuantity)
{
	quantity = iQuantity;
}

// dumps contents of objects to console. overridden in every derived class.
void Item::dumpObject()
{
	cout << '\t' << "Item" << endl;
	dumpObjectData();
}

// dumps contents of only data members to console. overridden in every derived 
// class. should be called from immediate class to make sure all data along 
// inheritance chain is output.
void Item::dumpObjectData()
{
	Entity::dumpObjectData();

	// And output the unique variables.
	cout << '\t' << '\t' << "Weight = " << getWeight() << endl;
	cout << '\t' << '\t' << "Value = " << getValue() << endl;
	cout << '\t' << '\t' << "Rarity = " << getRarity() << endl;
	cout << '\t' << '\t' << "Enchantment = " << getEnchantment() << endl;
	cout << '\t' << '\t' << "Quantity = " << getQuantity() << endl;
}

// writes current object as an xml fragment to specified output
void Item::writeFragment(ostream & output)
{
	output << '\t' << "<Item>" << endl;
	writeDataAsFragment(output);
	output << '\t' << "</Item>" << endl << endl;
}

// writes data members of current object as xml fragment to specified output
void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output << '\t' << '\t' << "<weight>" << getWeight() 
		<< "</weight>" << endl;
	output << '\t' << '\t' << "<value>" << getValue() 
		<< "</value>" << endl;
	output << '\t' << '\t' << "<rarity>" << getRarity() 
		<< "</rarity>" << endl;
	output << '\t' << '\t' << "<enchantment>" << getEnchantment() 
		<< "</enchantment>" << endl;
	output << '\t' << '\t' << "<quantity>" << getQuantity() 
		<< "</quantity>" << endl;
}

// reads data back from xml stored on disk. should be overridden in every class,
// and called from immediate class.
void Item::setElementData(string sElementName, string sContent)
{
	Entity::setElementData(sElementName,sContent);

	if (sElementName == "weight")
		setWeight(atoi(sContent.c_str()));
	else if (sElementName == "value")
		setValue(atoi(sContent.c_str()));
	else if (sElementName == "rarity")
		setRarity(atoi(sContent.c_str()));
	else if (sElementName == "enchantment")
		setEnchantment(atoi(sContent.c_str()));
	else if (sElementName == "quantity")
		setQuantity(atoi(sContent.c_str()));
}
