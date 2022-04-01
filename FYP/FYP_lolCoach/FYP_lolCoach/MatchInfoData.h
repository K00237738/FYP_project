#pragma once
#ifndef MATCHINFODATA
#define MATCHINFODATA

#include <vector>

using namespace std;

class MatchInfoData
{
public:
	enum MapPositions {B_BOT = 1, B_MID, B_TOP, B_BOTJNG, B_TOPJNG, B_BASE,
	T_BOT, T_MID, T_TOP, T_BOTJNG, T_TOPJNG, T_BASE};
	//enum
	enum GameTime{EARLY1 = 1, EARLY2, MID, LATE1, LATE2};
	enum Roles{TOP = 1, MIDLANE, BOTTOM, SUPP, JNGL};
	enum ChampionTypes{CONTROLLER = 1, FIGHTER, MAGE, 
		MARKSMAN, SLAYER, TANK, SPECIAL};
	//--------------------------

	MatchInfoData();
	int GetEntries();
	//--------------------------
	void AddEntry(GameTime timeEnum, float time, MapPositions mposition, short level,
		int averagelevel, bool baseAttack, float KDstate);
	//--------------------------
	GameTime GetTime(int entry);
	MapPositions GetPosition(int entry);
	short GetLevel(int entry);
	int GetAverageLvl(int entry);
	bool IsBaseUnderAttack(int entry);
	float GetKD(int entry);


private:
	vector<GameTime> timestampsEnum;
	vector<float> timestampsFloats;//for game time parsed
	vector<MapPositions> timePositions;
	vector<short> playerlevel;
	vector<int> avgLvls;
	vector<bool> baseInDanger;
	vector<float> KDstates;
	int entries;
	//-----not sure if will use theses below
	Roles userRole;
	ChampionTypes userChampion;

protected:

};

#endif // !MATCHINFODATA
