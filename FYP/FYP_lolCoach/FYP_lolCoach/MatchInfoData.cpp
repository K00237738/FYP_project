#include "MatchInfoData.h"

MatchInfoData::MatchInfoData()
{
	//might have to add a match id for each packet
	entries = 0;
}

void MatchInfoData::AddEntry(GameTime timeEnum, float time, MapPositions mposition, short level,
	int averagelevel, bool baseAttack, float KDstate)
{//add entry for specifically feature 1
	//add an entry, push back to the end so they are in order, e.g. first entry is first in vector
	timestampsEnum.push_back(timeEnum);//will use gametime enums
	timestampsFloats.push_back(time);
	timePositions.push_back(mposition);//will use mapposition enums
	playerlevel.push_back(level);//will take in a value from 1 - 18
	avgLvls.push_back(averagelevel);//boolean
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
	return timestampsEnum.at(entry);
}

MatchInfoData::MapPositions MatchInfoData::GetPosition(int entry)
{
	return timePositions.at(entry);
}

short MatchInfoData::GetLevel(int entry)
{
	return playerlevel.at(entry);
}

int MatchInfoData::GetAverageLvl(int entry)
{
	return avgLvls.at(entry);
}

bool MatchInfoData::IsBaseUnderAttack(int entry)
{
	return baseInDanger.at(entry);
}

float MatchInfoData::GetKD(int entry)
{
	return KDstates.at(entry);
}