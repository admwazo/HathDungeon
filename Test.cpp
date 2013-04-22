#include <vector>
#include <string>

using namespace std;

class Item;
class Tile;

class Item
{
	private:
		string name;
		int XP;
	public:
		Item();
		~Item();
		void SetString(string sString);
		string GetString();
};

class Tile
{
	private:
		vector<Item*> vItems;
	public:
		Tile();
		~Tile();
		Item* GetItem(int iIndex);
		void AddItem(Item* i_Item);
};

void Item::SetString(string sString)
{
	name = sString;
}

string Item::GetString()
{
	return name;
}

void Tile::AddItem(Item* i_Item)
{
	vItems.push_back(i_Item);
}

Item* Tile::GetItem(int iIndex)
{
	Item* i_Item = vItems[iIndex];

	vItems[iIndex] = vItems.back();
	delete vItems.back();
	vItems.pop_back();

	return(i_Item);
}

int main()
{
	Tile t_Tile;  //test tile

	Item i_Item1; //test item1
	Item i_Item2; //test item2
	Item i_Item3; //test item3
	
	i_Item1.SetString("the item1");
	i_Item2.SetString("the item2");
	i_Item3.SetString("the item3");

	t_Tile.AddItem(&i_Item1);
	t_Tile.AddItem(&i_Item2);
	t_Tile.AddItem(&i_Item3);
}
