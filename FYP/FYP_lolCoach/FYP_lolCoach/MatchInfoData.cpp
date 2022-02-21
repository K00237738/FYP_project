#include "MatchInfoData.h"

MatchInfoData::MatchInfoData()
{
	//might have to add a match id for each packet
}

void MatchInfoData::AddEntry(GameTime time, MapPositions mposition, short level, 
	bool Estrong, bool baseAttack, int KDstate)
{//add entry for specifically feature 1
	//add an entry, push back to the end so they are in order, e.g. first entry is first in vector
	timestamps.push_back(time);//will use gametime enums
	timePositions.push_back(mposition);//will use mapposition enums
	timeLevels.push_back(level);//will take in a value from 1 - 18
	wasEnemyStronger.push_back(Estrong);//boolean
	baseInDanger.push_back(baseAttack);//boolean
	KDstates.push_back(KDstate);//will take a -1, 1, or 0
	entries++;
	//might have data check for correct input in data gathering class
}

//access methods
int MatchInfoData::GetEntries()
{
	return entries;
}

MatchInfoData::GameTime MatchInfoData::GetTime(int entry)
{
	return timestamps.at(entry);
}

MatchInfoData::MapPositions MatchInfoData::GetPosition(int entry)
{
	return timePositions.at(entry);
}

short MatchInfoData::GetLevel(int entry)
{
	return timeLevels.at(entry);
}

bool MatchInfoData::WasEnemyStronger(int entry)
{
	return wasEnemyStronger.at(entry);
}

bool MatchInfoData::IsBaseUnderAttack(int entry)
{
	return baseInDanger.at(entry);
}

short MatchInfoData::GetKD(int entry)
{
	return entries;
}