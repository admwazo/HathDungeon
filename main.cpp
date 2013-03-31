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
#include "Parser.h"

using namespace std;

typedef XMLSerializable* ptr; 

//takes an istream by reference and a string to hold the current position in XML doc's object hierarchy
//assumes we are on the first char after the opening <. does not properly check for end of input
bool parseElement(istream & input, vector<ptr> & vObjects, ptr xmlsClass)
{	
	// char to hold data as we process it
	char c;

	// The name of the element; initialized to
	// an empty string (as all strings are by default);
	string sElementName;


	// Read in the XML one character at a time, checking
	// for the > at the end of the tag
	do
	{
		// Get the character off the stream		
		c = input.get();

		// If it's not the end tag, add it to the element name
		if( c != '>' )
			sElementName.push_back(c);

	} while( c != '>' );

	if (sElementName == "Armor")
	{
		xmlsClass = new Armor;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Consumable")
	{
		xmlsClass = new Consumable;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Creature")
	{
		xmlsClass = new Creature;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Entity")
	{
		xmlsClass = new Entity;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Item")
	{
		xmlsClass = new Item;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Potion")
	{
		xmlsClass = new Potion;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Scroll")
	{
		xmlsClass = new Scroll;
		vObjects.push_back(xmlsClass);
	}
	else if (sElementName == "Weapon")
	{
		xmlsClass = new Weapon;
		vObjects.push_back(xmlsClass);
	}
	else;

	// Holds the non-element content of the element
	string sContent;

	// while(true) can be dangerous, but we do have paths
	// out of the function.
	while( true )
	{
		// Read a character off the stream
		c = input.get();

		// The important thing is to check to see if
		// it is an open angled bracket.
		if( c == '<' )
		{
			// If it is, we have two possibilities (assuming
			// the XML is valid):
			//
			// Either this is the start tag for a new element
			// contained in the current element, or it's
			// the end tag for our current element.
			//
			// Note that if it is an end tag -- and the XML is
			// valid -- it MUST be the end tag of the current element
			// as elements are not allowed to overlap.

			// So we check for the first character
			// being a / -- which indicated an end tag
			if( input.peek() == '/' )
			{
				// We must burn off the / since
				// we only peeked it, and haven't
				// gotten it yet!
				input.get();

				// Variable to hold the end tag as
				// we read it in
				string sEndTag;

				// Read in the end tag until we get
				// to the > at the end of the tag
				do
				{
					c = input.get();
					if( c != '>' )
						sEndTag.push_back(c);

				} while( c != '>' );

				// Now, we test for the validity of the XML -- the 
				// end tag's name must match the element's name...
				if( sEndTag != sElementName )
				{
					cout << "Tag name mismatch" << endl;
					return false;
				}

				if( sEndTag == "World")
					return true;

				// Output what we know to the console --
				// the hierarchy (where we are in the document),
				// the current element, and its content
				if(xmlsClass != NULL)
					xmlsClass->setElementData(sElementName, sContent);
				else;

				// And since we have fully parsed an element, we
				// return to whatever called us in the first place
				return true;

			}
			else
			{
				// In this branch, we have already read in a <,
				// but it was NOT an end tag -- the input file
				// is currently positioned on the first character
				// after the opening <, so we can call parseElement
				// on it...
				//
				// Here we're passing the hierarchy we know plus
				// the current element name, so this next element
				// knows where it is in the overal document 
				// hiearchy
				if(!parseElement(input, vObjects, xmlsClass))
					return false;
			}
		}
		else
		{
			// In this branch, we have read in a character inside
			// the element which is not a < -- since it's not
			// part of an interior element, it's content, so
			// we add it to our variable which stores the
			// content (ignoring end-of-line characters).
			if( c != '\n' )
				sContent.push_back(c);
		}
	}

	return true;
}

// parseXML -- parses an XML document.  First it
// makes a very half-hearted check for the validity
// of the XML header, then it parses the root
// element of the document.
bool parseXML(vector<ptr> & vObjects, istream & input)
{
	char c;

	// Read in the XML, one character at a time,
	// until we hit a <.
	do
	{
		c = input.get();
	} while( c != '<' );

	// Check the character after the < -- if it's
	// not a ?, we aren't seeing a valid XML header
	if( input.get() != '?' )
	{
		cout << "Invalid XML header" << endl;
		return false;
	}

	// Burn off the rest of the header, looking for
	// a ?
	do
	{
		c = input.get();
	} while( c != '?' );

	// Then we check for a > -- which tests for
	// the header ending with ?>
	if( input.get() != '>' )
	{
		cout << "Invalid XML header" << endl;
		return false;
	}

	// Now burn off characters until we get to the first
	// tag after the XML header...
	do
	{
		c = input.get();
	} while( c != '<' );

	ptr pXmlsClass;
	// And so, we're now on the first character after
	// the opening < -- which is exactly what parseElement
	// expects.  So we call it.
	return parseElement(input, vObjects, pXmlsClass);
}

// And an example function to generate an output XML
// document given a vector of parsed objects and 
// an output stream.
bool outputXMLToFile(vector<ptr> & vObjects, ostream & output)
{
	// Write the XML header to the output
	output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;

	// Write the opening World tag (as an XML document
	// needs a root element to be valid)
	output << "<World>" << endl;

	// And iterate through the vector of objects...
	for(vector<ptr>::const_iterator it = vObjects.begin(); 
		it != vObjects.end(); it++ )
	{
		(*it)->writeFragment(output);
	}

	// And output the end tag for the root
	// element.
	output << "</World>" << endl;
}

bool outputXMLToConsole(vector<ptr> & vObjects)
{
	cout << "World" << endl; 
	for(vector<ptr>::const_iterator it = vObjects.begin(); 
		it != vObjects.end(); it++ )
	{
		(*it)->dumpObject();
	}
}

void requestInput(string & xmlFile, string mode)
{
	cout << "Please enter the name of an XML file to " << mode << ": ";

	cin >> xmlFile;
	while (!cin.good())
	{    
        cin.clear();        // clearing input buffer
        cin.ignore(80,'\n'); 
        cout << "Invalid type, should be a string. Try again: ";
        cin >> xmlFile; // Storage location is at main function
    }
}

void runParser()
{
	vector<ptr> vObjects; 	// This is the object vector to loop thru at output
	ifstream input;
	ofstream output;
	string sInputFilename;	// Declaring filenams for i/o
	string sOutputFilename;

	// This loop just makes sure that the input is a string, and is a file that
	// exists
	do
	{
		requestInput(sInputFilename, "INPUT");
		input.open(sInputFilename.c_str());
		if (input.fail())
            cout << "That file doesn't exist, ";
	}while(input.fail());

	parseXML(vObjects, input);

	outputXMLToConsole(vObjects);
	
	requestInput(sOutputFilename, "OUTPUT");
	output.open(sOutputFilename.c_str());
	outputXMLToFile(vObjects, output);
}
