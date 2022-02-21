#include "DataExtraction.h"
#include <iostream>
#include <string.h>

DataExtraction::DataExtraction()
{

}

void DataExtraction::AskQuestions()
{

}

//-------------------------- General info
void DataExtraction::UserChampionData()
{

}

void DataExtraction::RoleData()
{

}

//-------------------------- Data Gathering sequences
void DataExtraction::MapMovementDataGathering()
{
	for (int i = 0; i < 5; i++)//match is always split into 5 segments
	{

	}
}

void DataExtraction::CombatEngagementDataGathering()
{

}

void DataExtraction::ItemPurchaseDataGathering()
{

}

//-------------------------- Specific Info
void DataExtraction::TimeData()
{

}

void DataExtraction::MapPositionData()
{

}

void DataExtraction::LevelData()
{

}

void DataExtraction::EnemyStrengthData()
{

}

void DataExtraction::WasBaseVulnerableData()
{

}

void DataExtraction::KD_Data()
{

}

//-------------------------- Return Info
MatchInfoData DataExtraction::ReturnData()
{
	return MatchInfoData();
}