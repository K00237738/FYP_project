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


private:
	vector<float> timestamps;
	vector<MapPositions> timePositions;
	vector<short> timeLevels;
	vector<bool> wasEnemyStronger;
	int entries;

	void AddEntry(float time, MapPositions mposition, short level, bool Estrong);
	int GetEntries();
	float GetTime(int entry);
	MapPositions GetPosition(int entry);
	short GetLevel(int entry);
	bool WasEnemyStronger(int entry);
	bool IsBaseUnderAttack(int entry);

protected:

};

#endif // !MATCHINFODATA
