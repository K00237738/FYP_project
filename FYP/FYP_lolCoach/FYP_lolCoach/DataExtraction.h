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
	//-------------------------- Specific Info
	void TimeData();
	void MapPositionData();
	void LevelData();
	void EnemyStrengthData();
	void WasBaseVulnerableData();
	void KD_Data();
	//-------------------------- Return Info
	MatchInfoData ReturnData();

private:

protected:

};

#endif // !DATA_EXTRACTION

