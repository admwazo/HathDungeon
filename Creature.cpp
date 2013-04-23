#include <string>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include "Creature.h"
#include "Tile.h"
#include "Item.h"
#include "Weapon.h"

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

int Creature::getPosY()
{
	return iPosY;
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

string Creature::getGraphic()
{
	return sGraphic;
}

void Creature::setGraphic(string sGraphic2)
{
	sGraphic = sGraphic2;
}

Tile* Creature::GetTile()
{
	return(t_CurTile);
}

void Creature::SetTile(Tile* t_Tile)
{
	//clearing current tile's actor
	if(t_CurTile != NULL)
		t_CurTile->SetActor(NULL);
	
	t_CurTile = t_Tile;
	iPosY = (t_CurTile->GetPosY());
	iPosX = (t_CurTile->GetPosX());

	//setting NEW current tile's actor
	t_CurTile->SetActor(this);
}

Item* Creature::GetItem(int iIndex)
{
	if((iIndex >= 0)&&(iIndex < vItems.size()))
		return(vItems[iIndex]);
}

void Creature::RemoveItem(Item* i_Item)
{
	if(vItems.size() == 1)
	{
		vItems.clear();
		vector<Item*>(vItems).swap(vItems);
		return;
	}    
	for(int i = 0; i < vItems.size(); i++)
    {
        if(vItems[i] == i_Item)
            vItems.erase(vItems.begin() + i);
    }
}

void Creature::AddItem(Item* i_Item2)
{
	Weapon* w_Weapon2 = dynamic_cast<Weapon*>(i_Item2);

    if(w_Weapon2 != NULL)
	{
		SetWeapon(w_Weapon2);
	}

	vItems.push_back(i_Item2);
}

vector<string> Creature::GetInventory()
{
	vector<string> vTempItems;

    if(vItems.size() != 0)
    {
        for(int i = 0; i < vItems.size(); i++)
        {
            vTempItems.push_back(vItems[i]->getName());
        }
    }

    return(vTempItems);
}

Weapon* Creature::GetWeapon()
{
	return w_Weapon;
}

void Creature::SetWeapon(Weapon* w_Weapon2)
{
	w_Weapon = w_Weapon2;
}

void Creature::Drop(Item* i_Item)
{
    RemoveItem(i_Item);

    GetTile()->AddItem(i_Item);
}

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
	else if (sElementName == "graphic")
		setGraphic(sContent);
	//else if (sElementName == "inventory")
	//	setInventory(atoi(sContent.c_str()));
}
