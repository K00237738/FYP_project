#include "SystemMain.h"

SystemMain::SystemMain()
{
	//initialize variables
	userName = "RetroTiger";
	passWord = "theBestGamer97";
	apiKey = "559-889-723";
}

void SystemMain::EngineMain()
{
	if (LoginProcdure() == false)
	{
		ExitProcedure();
	}
	GetUserRole();
	GetPreferedChamp();

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
	
}

void SystemMain::GetPreferedChamp()
{

}

void SystemMain::DecideAdvice()
{

}