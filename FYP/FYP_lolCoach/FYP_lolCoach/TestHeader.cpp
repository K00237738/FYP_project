#include "TestHeader.h"

TestHeader::TestHeader()
{
	x = 1;
	y = 2;
	z = 4;
	word = "bird";
}

void TestHeader::MethodTest()
{
	cout << "X = " << x << ", Y = " << y << " and Z = " << z << "\n . . . so x + y = " 
		<< x + y << ", and if you add z it equals " << x + y + z 
		<< " \nand with that conclusion we get that \'" << word << "\' is the word!" << endl;
}