#include "Player.h"
#include <sstream>
#include "Factory.h"
#include "Potion.h"
#include "Tile.h"

using namespace std;

Player::~Player()
{

}

Player::Player()
{
	setHP(100);
	setDisplayChar('@');
	setName("Wilfred");
	AddItem(Factory::Instance().GenerateItem("Longsword"));
	AddItem(Factory::Instance().GenerateItem("Potion"));
	SetIActive(0);
}

Item* Player::GetIActive()
{
	return i_Active;
}

void Player::SetIActive(int iIndex)
{
	if((iIndex >= 0)&&(iIndex < GetInventory().size()))
		i_Active = GetItem(iIndex);
}

int Player::GetXP()
{
	return XP;
}

void Player::SetXP(int iXP2)
{
	XP = iXP2;
}

void Player::Use(Item* i_Item)
{
	Potion* p_Potion = dynamic_cast<Potion*>(i_Item);
	if(p_Potion != NULL)
	{
		setHP(p_Potion->getHealth() + getHP());
	    RemoveItem(i_Item);
		delete i_Item;
		i_Active = GetItem(0);
	}
}

void Player::Drop(Item* i_Item)
{
    RemoveItem(i_Item);

	GetTile()->AddItem(i_Item);
	
	if(GetInventory().size() > 0)
		SetIActive(0);
}

void Player::LevelUp()
{
	setLevel(getLevel() + 1);
}
