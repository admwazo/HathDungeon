#ifndef _Parser_included_
#define _Parser_included_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ostream>
#include <cstring>

#include "XMLSerializable.h"
#include "Item.h"
#include "Armor.h"
#include "Consumable.h"
#include "Creature.h"
#include "Entity.h"
#include "Potion.h"
#include "Scroll.h"
#include "Weapon.h"

typedef XMLSerializable* ptr;

//bool parseElement(std::ifstream & input, std::vector<ptr> & vObjects, ptr xmlsClass);

bool parseXML(std::vector<ptr> & vObjects, std::istream & input);

bool outputXMLToFile(std::vector<ptr> & vObjects, std::ostream & output);

bool outputXMLToConsole(std::vector<ptr> & vObjects);

void requestInput(std::string & xmlFile, std::string mode);

#endif
