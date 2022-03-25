#include "TestHeader.h"
#include <rapidjson/document.h> 
#include <rapidjson/istreamwrapper.h>
//#include <rapidjson/stringbuffer.h>
//#include <rapidjson/writer.h>
#include <fstream>

using namespace rapidjson;
using namespace std;

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
	try
	{
		ifstream  jsonIn("results.json");
		/*if (!jsonIn.is_open())
		{
			std::cerr << "Could not open file for reading!\n";
			exit(1);
		}*/
		//jsonIn.open("C:\\Users\\student\\Documents\\Sem8\\FYPstuffSem8\\FYP_GitRepos\\FYP_project\\AccessRiotAPI\\results.json", ios::in);//only reading in
		//jsonIn.open("C:\\Users\\student\\Documents\\Sem8\\FYPstuffSem8\\FYP_GitRepos\\FYP_project\\AccessRiotAPI\\results.json", ios::in);//only reading in
		//jsonIn.open("results.json");//only reading in
		/*string data;
		jsonIn >> data;
		cout << data << endl;*/
		IStreamWrapper wrapper(jsonIn);
		//jsonIn.close();

		Document d;
		d.ParseStream(wrapper);

		/*StringBuffer buffer{};
		Writer<StringBuffer> writer{ buffer };
		d.Accept(writer);

		if (d.HasParseError())
		{
			std::cout << "Error  : " << d.GetParseError() << '\n'
				<< "Offset : " << d.GetErrorOffset() << '\n';
			exit(1);
		}

		string jsonStr(buffer.GetString());
		if (jsonStr == "null")
		{
			cout << "Dcoument is null..." << endl;
		}
		else
		{
			cout << jsonStr << endl;
		}*/
		////int kills << document["kills"].get;
		////cout << "Kills: " + document["kills"].GetInt() << endl;
		//assert(document.Null());
		if (d.HasMember("kills") == true || d["kills"].IsInt() == true)
		{
			cout << "Document has kills" << endl;
			cout << d["kills"].GetInt() << endl;

		}
		else
		{
			cout << "Document hasn't kills" << endl;
		}
	}
	catch (exception e)
	{
		cout << "Error occured" << endl;
	}
}