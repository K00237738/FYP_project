#include "TestHeader.h"
#include <rapidjson/document.h> 
#include <rapidjson/istreamwrapper.h>
#include <fstream>

using namespace rapidjson;

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

void TestHeader::ReadJsonMethod()
{//read json from file and parse
	fstream  jsonIn;
	jsonIn.open("results.json", ios::in);//only reading in
	IStreamWrapper wrapper(jsonIn);
	jsonIn.close();

	Document document;
	document.ParseStream(wrapper);
}