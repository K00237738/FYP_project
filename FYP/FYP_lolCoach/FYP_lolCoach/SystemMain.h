#pragma once
#ifndef SYSTEM_MAIN
#define SYSTEM_MAIN
#include <string.h>
#include <iostream>

using namespace std;

class SystemMain
{
	/*
	This is the main class where everything runs
	similar to a game manager or game engine class
	*/
public:
	SystemMain();
	void EngineMain();
	bool LoginProcdure();
	void GetUserRole();
	void GetPreferedChamp();
	void DecideAdvice();
	void MapMovement();
	void CombatEngagemnet();
	void ItemPurchasing();
	void GeneralStrategy();
	void DeliverDecision();
	void ExitProcedure();
private:

protected:
	enum Roles
	{
		TOP, MID, BOTTOM, SUPP, JNGL
	};
	enum ChampionTypes
	{
		CONTROLLER, FIGHTER, MAGE, MARKSMAN, SLAYER, TANK, SPECIAL
	};
	string userName, passWord, apiKey,
		gameRole, perferedType;
};
#endif // !SYSTEM_MAIN

