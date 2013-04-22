#include "Tile.h"
#include "Item.h"
#include <iostream>
#include "Creature.h"

using namespace std;

Tile::Tile(int x, int y)
{
	SetPosX(x);
	SetPosY(y);
	Set(' ');
}

Tile::~Tile()
{

}

int Tile::GetPosX()
{
	return iPosX;
}

void Tile::SetPosX(int x)
{
	iPosX = x;
}

int Tile::GetPosY()
{
	return iPosY;
}

void Tile::SetPosY(int y)
{
	iPosY = y;
}

char Tile::Get()
{
	if(vItems.size() != 0)
		return(vItems[0]->getDisplayChar());
	else
		return(cAvatar);
}

void Tile::Set(char cAvatar2)
{
	cAvatar = cAvatar2;
	if((cAvatar != '|')&&		//if not a wall
		(cAvatar != '-')&&		//nor a wall
		(cAvatar != ' '))		//nor a void
	{
		bPlayer = true;
		if((cAvatar != '<')&&		//nor stairs
			(cAvatar != '>'))		//nor stairs
			bElse = true;
		else
			bElse = false;
	}
	else
	{
		bElse = false;
		bPlayer = false;
	}
}

//indicates whether tile can be inhabited by a player
bool Tile::IsGoodP()
{
	return bPlayer;
}

//indicates whether tile can be inhabited by things other than a Player
bool Tile::IsGoodE()
{
	return bElse;
}

void Tile::AddItem(Item* i_Item)
{
	vItems.push_back(i_Item);
}

vector<string> Tile::GetInventory()
{
	vector<string> vsInventory;
	if(vItems.size() != 0)
		for(int i = 0; i < vItems.size(); i++)
		{
			vsInventory.push_back(vItems[i]->getName());
		}
	return(vsInventory);
}

Item* Tile::GetItem(int iIndex)
{
	if((iIndex >= 0)&&(iIndex < vItems.size()))
	{
		Item* i_Temp = vItems[iIndex];
		vItems.erase(vItems.begin() + iIndex);
		return i_Temp;
	}
	else
		return NULL;
}

void Tile::SetActor(Creature* c_Actor2)
{
	c_Actor = c_Actor2;
}

Creature* Tile::GetActor()
{
	return(c_Actor);
}
