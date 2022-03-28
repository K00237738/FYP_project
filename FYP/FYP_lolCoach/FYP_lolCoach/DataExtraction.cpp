#include "DataExtraction.h"
#include "MatchInfoData.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <rapidjson/document.h> 
#include <rapidjson/istreamwrapper.h>
//#include <rapidjson/stringbuffer.h>
//#include <rapidjson/writer.h>
#include <fstream>

using namespace rapidjson;
using namespace std;

DataExtraction::DataExtraction()
{
	//default values
	level = 0;
	kd = 0;
	enemyStrength = false;
	baseVulnerable = false;
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

}

//-------------------------- Data Gathering sequences
void DataExtraction::MapMovementDataGathering()
{
	bool gameRunning = true;
	short timePull = 35, gameTime = 3600/*hour*/, fiveMins = 0;
	//for (int i = 0; i < 5; i++)//match is always split into 5 segments
	//{
	//	TimeData(i);
	//	MapPositionData();
	//	LevelData();
	//	EnemyStrengthData();
	//	WasBaseVulnerableData();
	//	KD_Data();
	//}
	while (gameRunning)
	{
		//every 35 seconds, read file
		//every 5 mins, ask player questions on whereabouts and
		//info that can't aquire through api
		if (timePull > 0)
		{
			gameRunning = PullFromFile();
			if (fiveMins >= 300/*5 mins*/)
			{//ask player, maybe could look into forking?
				MapPositionData();
				WasBaseVulnerableData();
				fiveMins = 0;
			}
			timePull = 35;
		}
		else
		{
			sleep(1);//sleep for 1 second
			timePull--;
			fiveMins++;
		}
	}
}

void DataExtraction::CombatEngagementDataGathering()
{

}

void DataExtraction::ItemPurchaseDataGathering()
{

}

bool DataExtraction::PullFromFile()
{
	string playername;
	short kills = 0, deaths = 0, playerlevel = 0, avglvl = 0;
	float gameTime;
	//pull from file info
	bool isGameRunning = false;

	try
	{
		ifstream  jsonIn("results.json");
		IStreamWrapper wrapper(jsonIn);
		Document d;
		d.ParseStream(wrapper);
		if (d.HasMember("playername") == true || d["kills"].IsString() == true)
		{
			playername = d["playername"].GetInt();
		}
		if (d.HasMember("kills") == true || d["kills"].IsInt() == true)
		{
			kills = d["kills"].GetInt();
		}
		if (d.HasMember("deaths") == true || d["deaths"].IsInt() == true)
		{
			kills = d["deaths"].GetInt();
		}
		if (d.HasMember("playerlevel") == true || d["playerlevel"].IsInt() == true)
		{
			kills = d["playerlevel"].GetInt();
		}
		if (d.HasMember("avglevel") == true || d["avglevel"].IsInt() == true)
		{
			avglvl = d["avglevel"].GetInt();
		}
		if (d.HasMember("time") == true || d["time"].IsFloat() == true)
		{
			gameTime = d["time"].GetFloat();
		}
		TimeData(gameTime);
		LevelData();
		EnemyStrengthData();
		KD_Data();
		return isGameRunning;
	}
	catch (exception e)
	{

	}
}

//-------------------------- Specific Info
void DataExtraction::TimeData(int timeEntry)
{
	/*
	Game time breakdown
	early1 - 5
	early2 - 15
	mid - 25
	late1 - 35
	late2 - 45

	average game tends to be about 45 - 50 mins or more for longer games.
	Typically when hitting 50 mins, some players are very high levels, sometimes max
	So that is why it shall be cataegorized under late 2
	*/

	cout << "\n******************************************\n";
	switch (timeEntry)
	{
	case 1:
		cout << "\nPhase of game: Early 1 (first early phase of the game length)\n";
		gameTimeEntry = MatchInfoData::EARLY1;
		break;
	case 2:
		cout << "\nPhase of game: Early 1 (second early phase of the game length, close to mid game)\n";
		gameTimeEntry = MatchInfoData::EARLY2;
		break;
	case 3:
		cout << "\nPhase of game: Early 1 (mid phase of the game length)\n";
		gameTimeEntry = MatchInfoData::MID;
		break;
	case 4:
		cout << "\nPhase of game: Early 1 (first late phase of the game length, a bit after mid game)\n";
		gameTimeEntry = MatchInfoData::LATE1;
		break;
	default://default is last entry of a game
		cout << "\nPhase of game: Early 1 (second late phase of the game length, near end game)\n";
		gameTimeEntry = MatchInfoData::LATE2;
		break;
	}

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

void DataExtraction::LevelData()
{
	short userInput1;
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
	}
}

void DataExtraction::EnemyStrengthData()
{
	short userInput1;
	while (true)
	{
		cout << "\nWas the opposing enemy strong (over all higher level and more items): \n1.Yes\t2.No \n";
		cin >> userInput1;
		if (userInput1 == 1)
		{
			enemyStrength = true;//they were stronger
			break;
		}
		else if (userInput1 == 2)
		{
			enemyStrength = false;//they weren't stronger
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}
}

void DataExtraction::WasBaseVulnerableData()
{
	short userInput1;
	while (true)
	{
		cout << "\nWas the Base vulnerable (base turrets were exposed or under attack): \n1.Yes\t2.No \n";
		cin >> userInput1;
		if (userInput1 == 1)
		{
			baseVulnerable = true;//they were stronger
			break;
		}
		else if (userInput1 == 2)
		{
			baseVulnerable = false;//they weren't stronger
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}
}

void DataExtraction::KD_Data()
{
	short userInput1;
	while (true)
	{
		cout << "\nWas your Kill/Death ration: \n1.Good\t2.Even\n3.Bad \n";
		cin >> userInput1;
		if (userInput1 == 1 || userInput1 == 2 || userInput1 == 3)
		{
			switch (userInput1)
			{
			case 1:
				userInput1 = 1;//had a better kd
				break;
			case 2:
				userInput1 = 0;//even kd
				break;
			default:
				userInput1 = -1;//bad kd
				break;
			}
			break;
		}
		else
		{
			cout << "\nInput not recognized, please try again. \n";
		}
	}
}

//-------------------------- Return Info
MatchInfoData DataExtraction::ReturnData()
{
	return MatchInfoData();
}