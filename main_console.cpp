#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ostream>
#include <cstring>

#include "XMLSerializable.h"
#include "Parser.h"

using namespace std;

typedef XMLSerializable* ptr;

int main()
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

	return 0;
}