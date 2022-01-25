#pragma once
#ifndef MATCHINFODATA
#define MATCHINFODATA

#include <vector>

using namespace std;

class MatchInfoData
{
public:
	enum MapPositions {TEMP};


private:
	vector<float> timestamps;
	vector<MapPositions> timePositions;
	vector<short> timeLevels;
	vector<bool> wasEnemyStronger;
	int entries;

	void AddEntry(/*needs params*/);
	int GetEntries();
	float GetTime(int entry);
	MapPositions GetPosition(int entry);
	short GetLevel(int entry);
	bool WasEnemyStronger(int entry);

protected:

};

#endif // !MATCHINFODATA
