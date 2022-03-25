#include "LogicalReasoning.h"

LogicalReasoning::LogicalReasoning()
{

}

void LogicalReasoning::ReasoningProcess()
{
	//sample method
}

void LogicalReasoning::MapMovementReasoning(MatchInfoData matchData)
{
	timeDivide = matchData.GetEntries() / 5;
	currentState = MatchInfoData::EARLY1;
	UserChampionConsideration(matchData);
	for (int i = 0; i < matchData.GetEntries(); i++)//cycle through all entires
	{//loop though all entires
		TimeConsideration(matchData, i);
		MapPositionConsideration(matchData, i);
		LevelConsideration(matchData);
		EnemyStrengthConsideration(matchData);
		BaseConsideration(matchData);
		KD_Consideration(matchData);
		RoleConsideration(matchData);
	}
}
//----------------------------------
void LogicalReasoning::UserChampionConsideration(MatchInfoData matchData)
{
	
}

void LogicalReasoning::RoleConsideration(MatchInfoData matchData)
{

}
//-----------------------------------

void LogicalReasoning::TimeConsideration(MatchInfoData matchData, int entry)
{
	
	if (entry > timeDivide)
	{
		timeDivide += timeDivide;
		switch (currentState)
		{//move enum state up by one
		case MatchInfoData::EARLY1:
			currentState = MatchInfoData::EARLY2;
			break;
		case MatchInfoData::EARLY2:
			MatchInfoData::MID;
			break;
		case MatchInfoData::MID:
			MatchInfoData::LATE1;
			break;
		case MatchInfoData::LATE1:
			MatchInfoData::EARLY2;
			break;
		}
	}//will have to add a risk level for each of the time states
}

void LogicalReasoning::MapPositionConsideration(MatchInfoData matchData, int entry)
{
	switch (matchData.GetPosition(entry))
	{
	case MatchInfoData::B_BOT:

		break;
	case MatchInfoData::B_MID:

		break;
	case MatchInfoData::B_TOP:

		break;
	case MatchInfoData::B_BOTJNG:

		break;
	case MatchInfoData::B_TOPJNG:

		break;
	case MatchInfoData::B_BASE:

		break;
	case MatchInfoData::T_BOT:

		break;
	case MatchInfoData::T_MID:

		break;
	case MatchInfoData::T_TOP:

		break;
	case MatchInfoData::T_BOTJNG:

		break;
	case MatchInfoData::T_TOPJNG:

		break;
	case MatchInfoData::T_BASE:

		break;
	default:
		break;
	}
}

void LogicalReasoning::LevelConsideration(MatchInfoData matchData)
{

}

void LogicalReasoning::EnemyStrengthConsideration(MatchInfoData matchData)
{

}

void LogicalReasoning::BaseConsideration(MatchInfoData matchData)
{

}

void LogicalReasoning::KD_Consideration(MatchInfoData matchData)
{

}