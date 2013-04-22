#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	stringstream ss;
	ss.str("");
	ss << "which item would you like to pick up? ";
	
	string sItem1 = "firstie";
	int i = 1;	
	
	ss << i << " " << sItem1 << " "; 
	
	string sItem2 = "secondie";

	cout << ss.str() << endl;
} 
