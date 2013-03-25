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

int main(int argc, char * argv[])
{
	string sInputFilename;	// Declaring filenams for i/o
	string sOutputFilename;

	vector<ptr> vObjects; 	// This is the object vector to loop thru at output
	ifstream input;
	ofstream output;

	if(argc >= 3)	// making sure there are 3 arguments
	{
		sInputFilename = argv[1];
		input.open(sInputFilename.c_str());	// opening input file

		sOutputFilename = argv[2];
	}
	else
	{
		// This loop just makes sure that the input is a string, and is a file
		// that exists
		do
		{
			requestInput(sInputFilename, "INPUT");
			input.open(sInputFilename.c_str());
			if (input.fail())
	            cout << "That file doesn't exist, ";
		}while(input.fail());

		requestInput(sOutputFilename, "OUTPUT");   //requesting output file name
											   //does not require error checking
	}

	parseXML(vObjects, input);

	outputXMLToConsole(vObjects);
	output.open(sOutputFilename.c_str());
	outputXMLToFile(vObjects, output);

	return 0;
}