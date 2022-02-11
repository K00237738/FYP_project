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
	void UserChampionData();
	void RoleData();
	void MapPositionData();
	void TimeData();
	void LevelData();
	void EnemyStrengthData();
	void KD_Data();
	MatchInfoData ReturnData();
};

#endif // !DATA_EXTRACTION

