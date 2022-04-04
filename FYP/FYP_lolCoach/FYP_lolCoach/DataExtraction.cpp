#include "DataExtraction.h"
#include "MatchInfoData.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <rapidjson/document.h> 
#include <rapidjson/istreamwrapper.h>
//#include <rapidjson/stringbuffer.h>
//#include <rapidjson/writer.h>
#include <fstream>
#include <thread>

using namespace rapidjson;
using namespace std;

DataExtraction::DataExtraction()
{
	//default values
	level = 0;
	kd = 0;
	kills = 0;
	deaths = 0;
	current_match = 0;
	enemyStrength = false;
	baseVulnerable = false;
	startingTop = false;
	reasoning = LogicalReasoning();
}

void DataExtraction::AskQuestions()
{
	//temp method
}

//-------------------------- General info
void DataExtraction::UserChampionData()
{//get chosen champion info

}

void DataExtraction::RoleData()
{//get chosen role data
	short userInput;
	bool checkLoop = true;
	while (checkLoop)
	{
		cout << "\nPlease input what role you chose?\n1.Top lane\t2.Mid lane\n3.Bottom lane\t4.Support\n5.Jungle\n";
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			userRoleInput = MatchInfoData::TOP;
			checkLoop = false;
			break;
		case 2:
			userRoleInput = MatchInfoData::MIDLANE;
			checkLoop = false;
			break;
		case 3:
			userRoleInput = MatchInfoData::BOTTOM;
			checkLoop = false;
			break;
		case 4:
			userRoleInput = MatchInfoData::TOP;
			checkLoop = false;
			break;
		case 5:
			userRoleInput = MatchInfoData::SUPP;
			checkLoop = false;
			break;
		case 6:
			userRoleInput = MatchInfoData::JNGL;
			checkLoop = false;
			break;
		default:
			cout << "\nInput unknown, try again\n";
			break;
		}
	}
	checkLoop = true;
	while (checkLoop)
	{
		cout << "\nPlease input if you are starting at the top or bottom of the map?\n1.Top\t2.Bottom\n";
		cin >> userInput;
		switch (userInput)
		{
		case 1://top
			startingTop = true;
			checkLoop = false;
			break;
		case 2://bot
			startingTop = false;
			checkLoop = false;
			break;
		default:
			cout << "\nInput unknown, try again\n";
			break;
		}
	}
}

//-------------------------- Data Gathering sequences
void DataExtraction::PythonThread()
{//run pyth script for a thread
	cout << "Running python script" << endl;
	string command = "python main.py";
	system(command.c_str());
}
void DataExtraction::MapMovementDataGathering()
{
	cout << "Starting map movement gathering" << endl;
	matches.push_back(MatchInfoData(userRoleInput, startingTop));
	current_match++;
	RoleData();
	//matches.at(current_match-1);
	bool gameRunning = false;
	int timePull = 35, gameTime = 0/*hour*/, fiveMins = 0;
	string userinput;

	while (gameRunning == false)
	{
		cout << "\nThis program requires the game to be running, are you spawned in the game map?\n1.Yes\t2.No\n";
		cin >> userinput;
		if (userinput.compare("Yes") || userinput.compare("1"))
		{
			gameRunning = true;
		}
		else if (userinput.compare("No") || userinput.compare("2"))
		{
			cout << "\nWould you like to stop this program prematurely?\n1.Yes\t2.No\n";
			cin >> userinput;
			if (userinput.compare("Yes") || userinput.compare("1"))
			{
				return;
			}
			else
			{
				cout << "\nInput not recognized, try again\n";
			}
		}
		else
		{
			cout << "\nInput not recognized, try again\n";
		}
	}
	//call thread to execute python script
	//thread pthyonthreadcall(&DataExtraction::PythonThread, DataExtraction());
	//this was removed as it halted up parent process sometimes

	clock_t clockTimer;
	clockTimer = clock();
	timePull *= CLOCKS_PER_SEC;


	cout << "Starting gatherloop" << endl;
	while (gameRunning == true)
	{
		//every 35 seconds, read file
		//every 5 mins, ask player questions on whereabouts and
		//info that can't aquire through api

		while ((clock() - clockTimer) < timePull);//loop for 35secs
		//reach 35 seconds, pull
		gameRunning = PullFromFile();
		/*timePull = 35* CLOCKS_PER_SEC;*/
		~clock();//destroy clock object and create new instance
		clockTimer = clock();
		fiveMins += timePull;
		gameTime += timePull;

		if (fiveMins >= (300 * CLOCKS_PER_SEC)/*5 mins*/)
		{//ask player, maybe could look into forking?
			MapPositionData();
			WasBaseVulnerableData();
			fiveMins = 0;//reset fivemins mark
		}
		if (gameTime >= (3600 * CLOCKS_PER_SEC)/*5 mins*/)
		{//hour reached, stop pulling from file
			gameRunning = false;
		}
		//cout << reasoning.MapMovementReasoning(matches.at(current_match - 1));
		cout << "Stored entry" << endl;
		matches.at(current_match - 1).AddEntry(gameTimeEntry, gameTimefloat, mapPosEntry, level, matchaveragelevel, baseVulnerable, kd);
		//call logical reasoning
		cout << reasoning.MapMovementReasoning(matches.at(current_match - 1)) << endl;

	}
	//pthyonthreadcall.join();
}

void DataExtraction::CombatEngagementDataGathering()
{

}

void DataExtraction::ItemPurchaseDataGathering()
{

}

bool DataExtraction::PullFromFile()
{
	cout << "Pulling from file" << endl;
	string playername;
	int gameRunning = 0, kills = 0, deaths = 0, playerlevel = 0, avglvl = 0;
	float gameTime = 0.0f;
	//bool isGameRunning = false;
	// 
	//pull from file info
	/*
	gameRunning = 
	0 = it is not running
	1 = it is running
	-1 = the game is running but not started yet
	*/

	try
	{
		ifstream  jsonIn("results.json");
		IStreamWrapper wrapper(jsonIn);
		Document d;
		d.ParseStream(wrapper);
		if (d.HasMember("isGameRunning") == true && d["isGameRunning"].IsInt() == true)
		{
			gameRunning = d["isGameRunning"].GetInt();
		}
		if (d.HasMember("playername") == true && d["playername"].IsString() == true)
		{
			playername = d["playername"].GetString();
		}
		if (d.HasMember("kills") == true && d["kills"].IsInt() == true)
		{
			kills = d["kills"].GetInt();
		}
		if (d.HasMember("deaths") == true && d["deaths"].IsInt() == true)
		{
			deaths = d["deaths"].GetInt();
		}
		if (d.HasMember("playerlevel") == true && d["playerlevel"].IsInt() == true)
		{
			playerlevel = d["playerlevel"].GetInt();
		}
		if (d.HasMember("avglevel") == true && d["avglevel"].IsInt() == true)
		{
			avglvl = d["avglevel"].GetInt();
		}
		if (d.HasMember("time") == true && d["time"].IsFloat() == true)
		{
			gameTime = d["time"].GetFloat();
		}
		TimeData(gameTime);
		LevelData(playerlevel, avglvl);
		EnemyStrengthData(avglvl);
		KD_Data(kills, deaths);

	}
	catch (exception e)
	{
		cout << "\n***Trobule pulling from the json file***" << endl;
	}
	if (gameRunning == -1 || gameRunning == 1)
	{//game is running
		return true;
	}
	else
	{//its finished
		return false;
	}
}

//-------------------------- Specific Info
void DataExtraction::TimeData(float timeInput)
{
	int timeEntry = timeInput/60;
	gameTimefloat = timeInput;
	/*
	* Time break down
	Early 1		<=6
	Early 2		<=12
	Mid			<=18
	Late 1		<=24
	Late 2		<=30+
	
	average game tends to be about 30 - 40 mins or more for longer games.
	Typically when hitting 40 mins, some players are very high levels, sometimes max
	So that is why it shall be cataegorized under late 2
	*/
	if (timeEntry <= 6)
	{
		cout << "\nPhase of game: Early 1 (first early phase of the game length)\n";
		gameTimeEntry = MatchInfoData::EARLY1;
	}
	else if (timeEntry <= 12)
	{
		cout << "\nPhase of game: Early 2 (second early phase of the game length, close to mid game)\n";
		gameTimeEntry = MatchInfoData::EARLY2;
	}
	else if (timeEntry <= 18)
	{
		cout << "\nPhase of game: Mid (mid phase of the game length)\n";
		gameTimeEntry = MatchInfoData::MID;
	}
	else if (timeEntry <= 24)
	{
		cout << "\nPhase of game: Late 1 (first late phase of the game length, a bit after mid game)\n";
		gameTimeEntry = MatchInfoData::LATE1;
	}
	else//else is 30+
	{
		cout << "\nPhase of game: Late 2 (second late phase of the game length, near end game)\n";
		gameTimeEntry = MatchInfoData::LATE2;
	}

	cout << "\n******************************************\n";
	//switch (timeEntry)
	//{
	//case 1:
	//	cout << "\nPhase of game: Early 1 (first early phase of the game length)\n";
	//	gameTimeEntry = MatchInfoData::EARLY1;
	//	break;
	//case 2:
	//	cout << "\nPhase of game: Early 1 (second early phase of the game length, close to mid game)\n";
	//	gameTimeEntry = MatchInfoData::EARLY2;
	//	break;
	//case 3:
	//	cout << "\nPhase of game: Early 1 (mid phase of the game length)\n";
	//	gameTimeEntry = MatchInfoData::MID;
	//	break;
	//case 4:
	//	cout << "\nPhase of game: Early 1 (first late phase of the game length, a bit after mid game)\n";
	//	gameTimeEntry = MatchInfoData::LATE1;
	//	break;
	//default://default is last entry of a game
	//	cout << "\nPhase of game: Early 1 (second late phase of the game length, near end game)\n";
	//	gameTimeEntry = MatchInfoData::LATE2;
	//	break;
	//}

}

void DataExtraction::MapPositionData()
{
	//should keep this as need to ask player data
	short userInput1, userInput2;
	while (true)
	{
		cout << "\nWhere you in the bottom (1) area of the map or top (2) area? \n";
		cin >> userInput1;
		if (userInput1 <= 5 && userInput1 >= 1)
		{
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}
	while (true)
	{
		cout << "\nOf the areas, where were you? \n1.Bottom lane \t2.Top lane"
			<< "\n3.Mid lane \t4.Jungle Top\n5.Jungle Bottom \t6.Base\n";
		cin >> userInput2;
		if (userInput2 <= 6 && userInput2 >= 1)
		{
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}
	if (userInput1 == 1)
	{//bottom map area
		switch (userInput2)
		{
			case 1:
				mapPosEntry = MatchInfoData::B_BOT;
				break;
			case 2:
				mapPosEntry = MatchInfoData::B_TOP;
				break;
			case 3:
				mapPosEntry = MatchInfoData::B_MID;
				break;
			case 4:
				mapPosEntry = MatchInfoData::B_TOPJNG;
				break;
			case 5:
				mapPosEntry = MatchInfoData::B_BOTJNG;
				break;
			default://default is base area
				mapPosEntry = MatchInfoData::B_BASE;
				break;
		}
	}
	else
	{//top map area
		switch (userInput2)
		{
		case 1:
			mapPosEntry = MatchInfoData::T_BOT;
			break;
		case 2:
			mapPosEntry = MatchInfoData::T_TOP;
			break;
		case 3:
			mapPosEntry = MatchInfoData::T_MID;
			break;
		case 4:
			mapPosEntry = MatchInfoData::T_TOPJNG;
			break;
		case 5:
			mapPosEntry = MatchInfoData::T_BOTJNG;
			break;
		default://default is base area
			mapPosEntry = MatchInfoData::T_BASE;
			break;
		}
	}
}

void DataExtraction::LevelData(int lvlInput, int avglvl)
{
	level = lvlInput;
	matchaveragelevel = avglvl;
	/*short userInput1;
	while (true)
	{
		cout << "\nPlease input your level (1 - 18) roughly at the time of game: \n";
		cin >> userInput1;
		if (userInput1 <= 18 && userInput1 >= 1)
		{
			level = userInput1;
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}*/
}

void DataExtraction::EnemyStrengthData(short avglvl)
{//get match average level
	matchaveragelevel = avglvl;
	//pobably wont need method
	// 
	// 
	// 
	//short userInput1;
	//while (true)
	//{
	//	cout << "\nWas the opposing enemy strong (over all higher level and more items): \n1.Yes\t2.No \n";
	//	cin >> userInput1;
	//	if (userInput1 == 1)
	//	{
	//		enemyStrength = true;//they were stronger
	//		break;
	//	}
	//	else if (userInput1 == 2)
	//	{
	//		enemyStrength = false;//they weren't stronger
	//		break;
	//	}
	//	else
	//	{
	//		cout << "\nInput not recognized, please try again. \n";
	//	}
	//}
}

void DataExtraction::WasBaseVulnerableData()
{
	short userInput1;
	while (true)
	{
		cout << "\nIs the Base vulnerable (base turrets under attack or inhibitor(s) exposed): \n1.Yes\t2.No \n";
		cin >> userInput1;
		if (userInput1 == 1)
		{
			baseVulnerable = true;
			break;
		}
		else if (userInput1 == 2)
		{
			baseVulnerable = false;
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}
}

void DataExtraction::KD_Data(short k, short d)
{
	kills = k;
	deaths = d;
	kd = (float)k / (float)d;
}

//-------------------------- Return Info
MatchInfoData DataExtraction::ReturnData(int matchindex)
{
	if (matchindex >= matches.size() || matchindex < 0)
	{
		return matches.at(matches.size() - 1);
	}
	else
	{
		return matches.at(matchindex);
	}
}