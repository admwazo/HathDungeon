#include <iostream>
#include <vector>

#include "DungeonLevel.h"

using namespace std;

void MarkPosition(int x, int y, DungeonLevel & dl)
{
    if(dl.GetHeight() <= y) //must be within size of vector on large end
        return;
    if(y < 0)   //must not be less than 0
        return;
    if(dl.GetWidth(y) <= x) //making sure that the row
        return;
    if(x < 0)   //making sure the length of the row is greater than 0
        return;

    char cTile = dl.Get(y, x);  //getting one tile

    if(cTile != '#' && cTile != '.' && cTile != '<' && cTile != '>')
        return;


    dl.Set(y, x, 'X');  //marking position

    MarkPosition(x+1, y, dl);   //calling on adjacent
    MarkPosition(x-1, y, dl);
    MarkPosition(x, y+1, dl);
    MarkPosition(x, y-1, dl);
}

void RunTests(DungeonLevel dl)
{
	bool pass = true;
	vector<DungeonLevel*> vSectors = dl.GetVSectors();

//Test 1
	cout << "Test 1: " << endl;
	cout << "	Dungeon must be 79 tiles long and 20 tiles high. " << endl << endl;
	if(dl.GetHeight() != 20)
	{		
		cout << "		FAIL: Height not equal to 20..." << endl;
		pass = false;
	}
	for(int i = 0; (i < dl.GetHeight()); i++)
		if(dl.GetWidth(i) != 79)
		{
			cout << "		FAIL: Length not equal to 79..." << endl;
			pass = false;
		}
	if(pass)
		cout << "		Pass: All Test 1 requirements passed." << endl;
	cout << endl;	

//Test 2
	pass = true;
    cout << "Test 2: " << endl;
    cout << "	Dungeon must contain 200 room tiles. " << endl << endl;
	
	int iCount = 0;
    for(int i = 0; i < 19; i++)
		for(int j = 0; j < 78; j++)
        	if(dl.Get(i, j) == '.')
				iCount++;

	if(iCount < 200)
	   	cout << "		FAIL: Less than 200 room tiles in dungeon..." << endl;
    else
       	cout << "		Pass: All Test 2 requirements passed." << endl;
	cout << endl;

//Test 3
	pass = true;
    cout << "Test 3: " << endl;
    cout << "	Rooms must be rectangular and not overlap. " << endl << endl;
	//just using findSector to make sure each room tile only exists in one room
	//this should satisfy the rectangular requirements as well because I'm using 
	//start/end row/column variables to both create and traverse the rooms. can't
	//walk tiles to check geometry because i have the wall tiles and openings for doors
	for(int i = 0; i < (vSectors.size()); i++)		
		for(int j = (vSectors[i]->GetStartRow());
			(j <= (vSectors[i]->GetEndRow()));
			j++)
			
			for(int k = (vSectors[i]->GetStartColumn());
			(k <= (vSectors[i]->GetEndColumn()));
			k++)
			
				if(dl.FindSector(j, k, vSectors) != i)
				{
					cout << "		FAIL: Same position exists in multiple rooms" << endl;
					pass = false;
				}
	if(pass)
		cout << "		Pass: All Test 3 requirements passed." << endl;
	cout << endl;

//Test 4
    pass = true;
    bool upStairs = false;
    bool downStairs = false;
    cout << "Test 4: " << endl;
    cout << "   Must contain upstairs / downstairs. " << endl << endl;
    for(int i = 0; i < 19; i++)
        for(int j = 0; j < 78; j++)
        {
            if(dl.Get(i, j) == '<')
                upStairs = true;
            if(dl.Get(i, j) == '>')
                downStairs = true;
        }
    if((upStairs)&&(downStairs))
        cout << "		Pass: All Test 4 requirements passed. " << endl;
    else
        cout << "		FAIL: Upstairs and Downstairs tiles do not exist in dungeon. " << endl;
    cout << endl;


//Test 5
	pass = true;
    cout << "Test 5: " << endl;
    cout << "	All rooms must be connected by tunnels. " << endl << endl;
	MarkPosition(((vSectors[0]->GetStartColumn()) + 1), ((vSectors[0]->GetStartRow()) + 1), dl);
	dl.Display();
	
	for(int i = 0; i < 19; i++)
        for(int j = 0; j < 78; j++)
            if((dl.Get(i, j) == '.')||(dl.Get(i, j) == '#'))
				pass = false;
	
    if(pass)
        cout << "		Pass: All Test 5 requirements passed. " << endl;
    else
        cout << "		FAIL: All rooms are not connected by tunnels. " << endl;

	cout << endl;

//Test 6
	pass = true;
    cout << "Test 6: " << endl;
    cout << "	All rooms must contain 16 tiles. " << endl << endl;
	for(int i = 0; i < (vSectors.size()); i++)
		if((vSectors[i]->GetTiles()) < 16)
		{	
			cout << "		FAIL: Number of tiles in room is less than 16." << endl;
			pass = false;
		}
	if(pass)
		cout << "		Pass: All Test 6 requirements passed." << endl;	
	cout << endl;

//Test 7
	pass = true;
	bool wallTileFound = false;
    cout << "Test 7: " << endl;
    cout << "	One room must border each edge of level. " << endl << endl;
	//left dungeon wall	
	for(int i = 0; i < 20; i++)
		if(dl.Get(i, 0) == '|')
			wallTileFound = true;
	if(!wallTileFound)
		pass = false;
	//right dungeon wall
    for(int i = 0; i < 20; i++)
        if(dl.Get(i, 78) == '|')
            wallTileFound = true;
    if(!wallTileFound)
        pass = false;
	//top dungeon wall
    for(int i = 0; i < 79; i++)
        if(dl.Get(19, i) == '-')
            wallTileFound = true;
    if(!wallTileFound)
        pass = false;
	//bottom dungeon wall
    for(int i = 0; i < 79; i++)
        if(dl.Get(0, i) == '-')
            wallTileFound = true;
    if(!wallTileFound)
        pass = false;

	if(pass)
		cout << "		Pass: All Test 7 requirements passed. " << endl;
	else
		cout << "		FAIL: At least one dungeon wall does not have a bordering room wall. " << endl;
	cout << endl;
}

int main(int argc, char * argv[])
{
    // Construct a new dungeon level with
    // width 79 and height 20.
    
    DungeonLevel dl(79,20);
    dl.BuildRooms();
	dl.Display();

	RunTests(dl);
    return 0;
}
