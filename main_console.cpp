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
#include "Game.h"

using namespace std;

typedef XMLSerializable* ptr;

void runParser(); //prototype for runParser since it's defined in main.cpp

int main()
{
	//runParser(); //runs the xml-parser
	Game g;
	g.Play();
}
