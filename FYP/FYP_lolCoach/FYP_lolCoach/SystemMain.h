#pragma once
#ifndef SYSTEM_MAIN
#define SYSTEM_MAIN

#include <string.h>
#include <iostream>
#include "MatchInfoData.h"

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
	/*void MapMovement();
	void CombatEngagemnet();
	void ItemPurchasing();
	void GeneralStrategy();
	void DeliverDecision();*/
	void ExitProcedure();
private:

protected:
	string userName, passWord, apiKey,
		gameRole, perferedType;
	MatchInfoData::Roles userRole;
	MatchInfoData::ChampionTypes userChampType;
};
#endif // !SYSTEM_MAIN

