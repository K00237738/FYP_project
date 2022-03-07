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
	void MapMovementReasoning(MatchInfoData matchData);
	//-------------------------
	void UserChampionConsideration(MatchInfoData matchData);
	void RoleConsideration(MatchInfoData matchData);
	//-------------------------
	void TimeConsideration(MatchInfoData matchData, int entry);
	void MapPositionConsideration(MatchInfoData matchData, int entry);
	void LevelConsideration(MatchInfoData matchData);
	void EnemyStrengthConsideration(MatchInfoData matchData);
	void BaseConsideration(MatchInfoData matchData);
	void KD_Consideration(MatchInfoData matchData);

private:
	enum RISKLEVEL { TOO_SAFE = 1, SAFE, LITTLE_MODERATE, 
		MODERATE, OVER_MODERATE, RISKY, TOO_RISKY };
	RISKLEVEL riskyness;
	int timeDivide = 0;
	MatchInfoData::GameTime currentState;
	int matchBreakUp, timeRisk, mapPosRisk;

protected:

};

#endif // !LOGICAL_REASONING

