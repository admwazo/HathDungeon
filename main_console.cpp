#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ostream>
#include <cstring>
#include <vector>

#include "XMLSerializable.h"
#include "Parser.h"
#include "DungeonLevel.h"

using namespace std;

typedef XMLSerializable* ptr;

void runParser(); //prototype for runParser since it's defined in main.cpp

int main()
{
	runParser(); //runs the xml-parser
	DungeonLevel dl(79,20); //builds dungeonLevel
    dl.BuildRooms(); //builds dungeonLevelrooms
	dl.Display(); //displays dungeonlevel
}
