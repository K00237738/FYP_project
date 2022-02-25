#pragma once
#ifndef DATA_EXTRACTION
#define DATA_EXTRACTION

#include "MatchInfoData.h"

using namespace std;

class DataExtraction
{
	/*
	This class is for data extraction or gathering
	This can be from the API or from the user, such as questioning
	*/
public:
	DataExtraction();
	void AskQuestions();//sample method so class has something for now
	//-------------------------- General info
	void UserChampionData();
	void RoleData();
	//-------------------------- Data Gathering sequences
	void MapMovementDataGathering();
	void CombatEngagementDataGathering();
	void ItemPurchaseDataGathering();
	//-------------------------- Specific Info
	void TimeData(int timeEntry);
	void MapPositionData();
	void LevelData();
	void EnemyStrengthData();
	void WasBaseVulnerableData();
	void KD_Data();
	//-------------------------- Return Info
	MatchInfoData ReturnData();

private:
	MatchInfoData::GameTime gameTimeEntry = MatchInfoData::EARLY1;//default values
	MatchInfoData::MapPositions mapPosEntry = MatchInfoData::B_BASE;
	MatchInfoData::Roles userRoleInput = MatchInfoData::BOTTOM;
	MatchInfoData::ChampionTypes userChampionInput = MatchInfoData::FIGHTER;
	short level, kd;
	bool enemyStrength, baseVulnerable;


protected:

};

#endif // !DATA_EXTRACTION

