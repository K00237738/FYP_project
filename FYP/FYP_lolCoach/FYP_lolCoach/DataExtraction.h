#pragma once
#ifndef DATA_EXTRACTION
#define DATA_EXTRACTION

#include "MatchInfoData.h"
#include "LogicalReasoning.h"

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
	bool PullFromFile();
	//-------------------------- Specific Info
	void TimeData(float timeInput);
	void MapPositionData();
	void LevelData(int lvlInput, int avglvl);
	void EnemyStrengthData(short avglvl);
	void WasBaseVulnerableData();
	void KD_Data(short k, short d);
	//-------------------------- Return Info
	MatchInfoData ReturnData(int matchindex);

private:
	MatchInfoData::GameTime gameTimeEntry = MatchInfoData::EARLY1;//default values
	MatchInfoData::MapPositions mapPosEntry = MatchInfoData::B_BASE;
	MatchInfoData::Roles userRoleInput = MatchInfoData::BOTTOM;
	MatchInfoData::ChampionTypes userChampionInput = MatchInfoData::FIGHTER;
	float kd, gameTimefloat;
	bool enemyStrength, baseVulnerable, startingTop;
	vector<MatchInfoData> matches;
	int current_match, level, matchaveragelevel, kills, deaths;
	LogicalReasoning reasoning;
	void PythonThread();


protected:

};

#endif // !DATA_EXTRACTION

