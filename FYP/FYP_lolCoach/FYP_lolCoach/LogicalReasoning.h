#pragma once
#ifndef LOGICAL_REASONING
#define LOGICAL_REASONING

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
	void MapMovementReasoning();
	void UserChampionConsideration();
	void TimeConsideration();
	void MapPositionConsideration();
	void LevelConsideration();
	void EnemyStrengthConsideration();
};

#endif // !LOGICAL_REASONING

