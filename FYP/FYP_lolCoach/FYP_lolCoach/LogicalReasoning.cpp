#include "LogicalReasoning.h"

LogicalReasoning::LogicalReasoning()
{
	currentRiskyness = 0;
	current_match_index = 0;
	match_time_emtry = 0;
}

void LogicalReasoning::ReasoningProcess()
{
	//sample method
}

void LogicalReasoning::MapMovementReasoning(MatchInfoData matchData)
{
	//timeDivide = matchData.GetEntries() / 5;
	//currentState = MatchInfoData::EARLY1;
	//UserChampionConsideration(matchData);
	//for (int i = 0; i < matchData.GetEntries(); i++)//cycle through all entires
	//{//loop though all entires
	//	TimeConsideration(matchData, i);
	//	MapPositionConsideration(matchData, i);
	//	LevelConsideration(matchData);
	//	EnemyStrengthConsideration(matchData);
	//	BaseConsideration(matchData);
	//	KD_Consideration(matchData);
	//	RoleConsideration(matchData);
	//}
}
//----------------------------------
void LogicalReasoning::UserChampionConsideration(MatchInfoData matchData)
{
	
}

void LogicalReasoning::RoleConsideration(MatchInfoData matchData)
{

}
//-----------------------------------

void LogicalReasoning::TimeConsideration(float time)
{	
	
}

void LogicalReasoning::MapPositionConsideration(MatchInfoData::Roles userRole, MatchInfoData::MapPositions userPosition, int entry, bool isTop)
{
	switch (userPosition)
	{
		//**********************************************************************************
	case MatchInfoData::B_BOT: case MatchInfoData::T_BOT://in bottom lane, either from bottom or top
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness*= TOO_SAFE; }//if spawned top and still top safe, playing it safe
			if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }//if spawned top and still top safe, playing it safe
			else{ currentRiskyness *= TOO_RISKY; }//else you are not top and 
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = MODERATE;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::SUPP:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		default:
			break;
		}
		break;

		//**********************************************************************************
	case MatchInfoData::B_MID:
		switch (userPosition)
		{
			//top------------------
		case MatchInfoData::T_TOP:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_MID:
			currentRiskyness = SAFE;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_BOT:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_BOTJNG:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_TOPJNG:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_BASE:
			currentRiskyness = MODERATE;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
			//bottom---------------------------
		case MatchInfoData::B_TOP:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_MID:
			currentRiskyness = SAFE;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_BOT:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_BOTJNG:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_TOPJNG:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_BASE:
			currentRiskyness = MODERATE;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		default:
			break;
		}

		break;
	case MatchInfoData::B_TOP:
		switch (userPosition)
		{
			//top------------------
		case MatchInfoData::T_TOP:
			currentRiskyness = SAFE;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_MID:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_BOT:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_BOTJNG:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_TOPJNG:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::T_BASE:
			currentRiskyness = MODERATE;
			if (isTop) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
			//bottom---------------------------
		case MatchInfoData::B_TOP:
			currentRiskyness = SAFE;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_MID:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_BOT:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_BOTJNG:
			currentRiskyness = RISKY;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_TOPJNG:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		case MatchInfoData::B_BASE:
			currentRiskyness = MODERATE;
			if (isTop) { currentRiskyness *= TOO_RISKY; }
			else { currentRiskyness *= TOO_SAFE; }
			break;
		default:
			break;
		}

		break;
	case MatchInfoData::B_BOTJNG:

		break;
	case MatchInfoData::B_TOPJNG:

		break;
	case MatchInfoData::B_BASE:

		break;
		//don't need
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