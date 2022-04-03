#include "SystemMain.h"
#include "DataExtraction.h"

SystemMain::SystemMain()
{
	//initialize variables
	/*userName = "RetroTiger";
	passWord = "theBestGamer97";*/
	userName = "student";
	passWord = "password";
	apiKey = "559-889-723";
}

void SystemMain::EngineMain()
{
	if (LoginProcdure() == false)
	{
		ExitProcedure();
	}
	//GetUserRole();
	GetPreferedChamp();
	DecideAdvice();
}

bool SystemMain::LoginProcdure()
{
	//authenticate the user name, password and API key
	string nameTemp, psswrdTemp, inputTemp;
	bool checkNameNPassword = false;
	{
		cout << "\nPlease input name: ";
		cin >> nameTemp;
		cout << "\nPlease input the password: ";
		cin >> psswrdTemp;
		cout << "\nauthenticating . . . ";
		if (userName.compare(nameTemp) == true && passWord.compare(psswrdTemp) == true)
		{
			cout << "\n Welcome " << userName;
		}
		else
		{
			cout << "\nUsername or Password incorrect, would you like to try again or exit?: y/n \n";
			cin >> inputTemp;
			if (inputTemp.compare("y") || inputTemp.compare("Y"))
			{
				cout << "\ntrying again . . .";
			}
			else
			{
				ExitProcedure();
			}
		}
	}
	return true;
}

void SystemMain::ExitProcedure()
{//used for exiting the program any time.
	//put into a method just incase I have to deconstruct/destroy any objects needed.
	exit(0);
}

void SystemMain::GetUserRole()
{
	bool check = false;
	int inputTemp;
	while (check == false)
	{
		cout << "\nPlease choose one of the following options for your prefered role in the game, which lane: " <<
			"\n1. Top\n2. Mid\n3. Bottom\n4. Support\n5. Jungle";
		cin >> inputTemp;
		switch (inputTemp)
		{
		case 1:
			userRole = MatchInfoData::TOP;
			check = true;
			break;
		case 2:
			userRole = MatchInfoData::MIDLANE;
			check = true;
			break;
		case 3:
			userRole = MatchInfoData::BOTTOM;
			check = true;
			break;
		case 4:
			userRole = MatchInfoData::SUPP;
			check = true;
			break;
		case 5:
			userRole = MatchInfoData::JNGL;
			check = true;
			break;
		default:
			cout << "\nInput not valid, try again";
			break;
		}
	}
}

void SystemMain::GetPreferedChamp()
{
	bool check = false;
	int inputTemp;
	while (check == false)
	{
		cout << "\nPlease choose one of the following options for your prefered champion type in the game: " <<
			"\n1. Controller\n2. Fighter\n3. Mage\n4. Marksman\n5. Slayer\n6. Tank\n7. Special";
		cin >> inputTemp;
		switch (inputTemp)
		{
		case 1:
			userChampType = MatchInfoData::CONTROLLER;
			check = true;
			break;
		case 2:
			userChampType = MatchInfoData::FIGHTER;
			check = true;
			break;
		case 3:
			userChampType = MatchInfoData::MAGE;
			check = true;
			break;
		case 4:
			userChampType = MatchInfoData::MARKSMAN;
			check = true;
			break;
		case 5:
			userChampType = MatchInfoData::SLAYER;
			check = true;
			break;
		case 6:
			userChampType = MatchInfoData::TANK;
			check = true;
			break;
		case 7:
			userChampType = MatchInfoData::SPECIAL;
			check = true;
			break;
		default:
			cout << "\nInput not valid, try again";
			break;
		}
	}
}

void SystemMain::DecideAdvice()
{
	bool check = false;
	int inputTemp;
	while (check == false)
	{
		cout << "\nPlease choose one of the following options for your advice area: " <<
			"\n1. Map Movement\n2. Combat Engagement\n3. Item Purchasing\n4. General Strategy\n5. Exit";
		cin >> inputTemp;
		switch (inputTemp)
		{
		case 1:
			MapMovement();
			break;
		/*case 2:
			CombatEngagemnet();
			break;
		case 3:
			ItemPurchasing();
			break;
		case 4:
			GeneralStrategy();
			break;
		case 5:
			ExitProcedure();
			break;*/
		default:
			cout << "\nInput not valid, try again";
			break;
		}
	}
}

void SystemMain::MapMovement()
{
	DataExtraction mapinfogathering;
	mapinfogathering.MapMovementDataGathering();
}