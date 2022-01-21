#pragma once
#ifndef SYSTEM_MAIN
#define SYSTEM_MAIN

using namespace std;

class SystemMain
{
	/*
	This is the main class where everything runs
	similar to a game manager or game engine class
	*/
public:
	SystemMain();
	bool LoginProcdure();
	void GetUserRole();
	void GetPreferedChamp();
};
#endif // !SYSTEM_MAIN

