#ifndef _Tile_Included_
#define _Tile_Included_

#include <vector>
#include <string>

class Creature;
class Item;

class Tile
{
	private:
		int iPosX; //x coordinate
		int iPosY; //y coordinate
		std::vector<Item*> vItems; //vector containing item pointers
		char cAvatar; //display char of tile
		bool bPlayer; //to mark tiles that player can inhabit- everywhere but walls and spaces
		bool bElse;	//to mark tiles that other things can inhabit - no walls, spaces, or stairs
		Creature* c_Actor;		
		
	public:
		Tile(int x, int y); 
		~Tile();
		virtual int GetPosX();
		virtual void SetPosX(int x);
		virtual int GetPosY();
		virtual void SetPosY(int y);
		virtual char Get();
		virtual void Set(char cAvatar2);
		virtual void AddItem(Item* i_Item);
		virtual Item* GetItem(int iIndex);
		virtual std::vector<std::string> GetInventory();
		virtual void SetActor(Creature* c_Actor2);
		virtual Creature* GetActor();
		virtual bool IsGoodP();
		virtual bool IsGoodE();
};

#endif
