#pragma once
#ifndef MATCHINFODATA
#define MATCHINFODATA

#include <vector>

using namespace std;

class MatchInfoData
{
public:
	enum MapPositions {B_BOT, B_MID, B_TOP, B_BOTJNG, B_TOPJNG, B_BASE,
	T_BOT, T_MID, T_TOP, T_BOTJNG, T_TOPJNG, T_BASE};
	//enum
	enum GameTime{EARLY1, EARLY2, MID, LATE1, LATE2};


private:
	vector<GameTime> timestamps;
	vector<MapPositions> timePositions;
	vector<short> timeLevels;
	vector<bool> wasEnemyStronger;
	vector<bool> baseInDanger;
	vector<short> KDstates;
	int entries;

	void AddEntry(GameTime time, MapPositions mposition, short level, bool Estrong, bool baseAttack, int KDstate);
	int GetEntries();
	//--------------------------
	GameTime GetTime(int entry);
	MapPositions GetPosition(int entry);
	short GetLevel(int entry);
	bool WasEnemyStronger(int entry);
	bool IsBaseUnderAttack(int entry);
	short GetKD(int entry);

protected:

};

#endif // !MATCHINFODATA
