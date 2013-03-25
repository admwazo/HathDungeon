#include <iostream>
#include <vector>

#include "DungeonLevel.h"

using namespace std;

int main(int argc, char * argv[])
{
    // Construct a new dungeon level with
    // width 79 and height 20.
    
    DungeonLevel dl(79,20);
    dl.BuildRooms();
	dl.Display();
    return 0;
}
