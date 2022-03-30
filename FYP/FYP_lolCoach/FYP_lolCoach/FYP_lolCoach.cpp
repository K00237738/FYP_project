// FYP_lolCoach.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TestHeader.h"
#include "SystemMain.h"

int main()
{
    std::cout << "This is gonna be my FYP!\n";
    //TestHeader t1;
    //t1.ReadJsonMethod();
    SystemMain h1;
    h1.EngineMain();



	/*int delay;

	cout << "Enter the time in seconds to be delayed:" << flush;

	cin >> delay;

	delay *= CLOCKS_PER_SEC;

	clock_t now = clock();

	while (clock() - now < delay);

	cout << "Message Show after delay that you entered" << endl;*/

	//bool gameRunning = true;
	//int timePull = 35, gameTime = 3600/*hour*/, fiveMins = 0, fiveMinLoops = 0;

	//timePull *= CLOCKS_PER_SEC;
	//gameTime *= CLOCKS_PER_SEC;
	////fiveMins *= CLOCKS_PER_SEC;

	//clock_t clockTimer;
	//clockTimer = clock();

	//while (gameRunning)
	//{
	//	//every 35 seconds, read file
	//	//every 5 mins, ask player questions on whereabouts and
	//	//info that can't aquire through api

	//	while ((clock() - clockTimer) < timePull);
	//	//reach 35 seconds, pull
	//	//gameRunning = PullFromFile();
	//	/*timePull = 35* CLOCKS_PER_SEC;*/
	//	~clock();//destroy clock object and create new instance
	//	clockTimer = clock();
	//	fiveMins += timePull;
	//	cout << "35 seconds passed" << endl;
	//	if (fiveMins >= (60 * CLOCKS_PER_SEC)/*5 mins*/)
	//	{//ask player, maybe could look into forking?
	//		//MapPositionData();
	//		//WasBaseVulnerableData();
	//		cout << "1 mins passed" << endl;
	//		fiveMins = 0;
	//		fiveMinLoops++;
	//	}
	//	
	//	if (fiveMinLoops >= 1)
	//	{
	//		gameRunning = false;
	//	}
	//}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
