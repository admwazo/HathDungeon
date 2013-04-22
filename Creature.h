// Include guard:
#ifndef _Creature_Included_
#define _Creature_Included_

#include "Entity.h"
#include <vector>
#include <ostream>
#include <string>
#include <sstream>

class Item;
class Tile;
class Weapon;

class Creature : public Entity
{
public:
	Creature(); // constructor
	~Creature(); // deconstructor
	virtual int getLevel();
	virtual void setLevel(int iLevel);
	virtual int getHP();
	virtual void setHP(int iHP);
	virtual int getMaxHP();
	virtual void setMaxHP(int iMaxHP);
	virtual int getPosX();
	virtual int getPosY();
	virtual Tile* GetTile();
	virtual void SetTile(Tile* t_Tile);
	virtual std::string getGraphic();
	virtual void setGraphic(std::string sGraphic2);
    virtual void AddItem(Item* i_Item2);
	virtual void RemoveItem(Item* i_Item);
	virtual Item* GetItem(int iIndex);
    virtual std::vector<std::string> GetInventory();
	virtual Weapon* GetWeapon();
	virtual void SetWeapon(Weapon* w_Weapon2);
	virtual void Drop(Item* i_Item);
	
	// overridden from XMLSerializable
	virtual void writeFragment(std::ostream & output);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sContent);

private:
	int level;
	int HP;
	int maxHP;
	std::vector<Item*> vItems;
	int iPosX;
	int iPosY;
	Tile* t_CurTile;
	std::string sGraphic; //contains the file location of the avatar graphic
	int iVectorPos;  //contains the position of the creature within dlLevel's creature vector
	Weapon* w_Weapon;
};

// End of the include guard:
#endif
