#pragma once
#ifndef LOGICAL_REASONING
#define LOGICAL_REASONING
#include "MatchInfoData.h"

using namespace std;

class LogicalReasoning
{
	/*
	This is the class where the decision making and reasoning will happen
	This is here the tree for behavior or reasoing will be stored
	Hopefully, tree data can be stored in a csv so it can be bought up later
	*/
public:
	LogicalReasoning();
	void ReasoningProcess();//sample method so class has something for now
	void MapMovementReasoning(MatchInfoData& matchData);
	//-------------------------
	void UserChampionConsideration(MatchInfoData matchData);
	void RoleConsideration(MatchInfoData matchData);
	//-------------------------
	int MapPositionConsideration(MatchInfoData::Roles, MatchInfoData::MapPositions, int entry, bool isTop);
	void TimeConsideration(MatchInfoData::GameTime time, int maxriskyness);
	void LevelConsideration(MatchInfoData& matchData);
	void EnemyStrengthConsideration(MatchInfoData& matchData);
	void BaseConsideration(MatchInfoData& matchData);
	void KD_Consideration(MatchInfoData& matchData);

private:
	/*
	Too safe			1
	Safe				2
	Little moderate		3
	Moderate			4
	Over moderate		5
	Risky				6
	Too risky			7
	*/
	enum RISKLEVEL { TOO_SAFE = 1, SAFE, LITTLE_MODERATE, 
		MODERATE, OVER_MODERATE, RISKY, TOO_RISKY };
	RISKLEVEL riskyness;
	int timeDivide = 0;
	MatchInfoData::GameTime currentState;
	int matchBreakUp, timeRisk, mapPosRisk;
	int currentRiskyness, current_match_index, match_time_entry;

protected:

};

#endif // !LOGICAL_REASONING

