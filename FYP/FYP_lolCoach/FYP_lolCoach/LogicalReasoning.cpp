#include "LogicalReasoning.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

LogicalReasoning::LogicalReasoning()
{
	currentRiskyness = 0;
	current_match_index = 0;
	match_time_entry = 0;
}

void LogicalReasoning::ReasoningProcess()
{
	//sample method
}

string LogicalReasoning::MapMovementReasoning(MatchInfoData& matchData)
{
	riskAmplifications = 0;//reset risk levels value
	string advice = "";
	int index = matchData.GetEntries()-1;
	int positionrisk = MapPositionConsideration(matchData.GetUserRole(), matchData.GetPosition(index), index, matchData.IsUserTopSpawn());
	TimeConsideration(matchData.GetTime(matchData.GetEntries() - 1), positionrisk);
	LevelConsideration(matchData);
	BaseConsideration(matchData);
	KD_Consideration(matchData);
	RoleConsideration(matchData);

	//------------Make a decision----------
	float safeFactor = currentRiskyness / (TOO_RISKY * riskAmplifications/*get mask risk from all the calulations*/);
	//gets how risky the player is on a scale of 0 - 1. Then use that as a measure of how safe to play
	// so if too risky, play safer. if too safe, player more risky
	//decide whether to push forward or pull back player (move or stay)
	srand(time(0));
	int randomPercent = (rand()%20)+1;//use random num
	if (randomPercent < 10) { randomPercent += 10; }//make sure its between 10 - 20% incvrease
	float randomrisk = (1 - safeFactor)* (randomPercent/100);//get 10 - 20% of less favoured judgement 
	//and increase less favoured judgement by given amount by docking down safefactor
	safeFactor -= randomrisk;//dock down safe factor

	srand(time(0));
	randomPercent = (rand() % 100)+1;//get value between 1 - 100
	float reasoningRoll = randomPercent/100;//so it will be between 0 - 1
	if (reasoningRoll <= safeFactor)
	{//stay
		srand(time(0));
		randomPercent = (rand() % 20) + 1;
		randomrisk = (1 - safeFactor) * (randomPercent / 100);

		srand(time(0));
		randomPercent = (rand() % 100) + 1;
		reasoningRoll = randomPercent / 100;
		if (reasoningRoll <= safeFactor)
		{//protect lane
			if (!matchData.GetUserRole() == MatchInfoData::JNGL)
			{//top, mid, bot, support roles
				advice = "\nStay in current lane and protect turret.\n";
				if(matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
				{//lane turrets may be defeated by then
					advice += "If lane turrets are defated, defend base turret areas for lane.";
				}
				return advice;
			}
			else
			{//jungle role
				switch (matchData.GetPosition(match_time_entry))
				{
					case MatchInfoData::B_TOPJNG: case MatchInfoData::B_BOTJNG: case MatchInfoData::T_TOPJNG:
					case MatchInfoData::T_BOTJNG:
						advice = "\nStay and clear out camps.\n";
						break;
					default://every other lane
						advice = "\nStay in current lane and protect turret.\n";
						if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
						{//lane turrets may be defeated by then
							advice += "If lane turrets are defated, defend base turret areas for lane.";
						}
						break;
				}
				return advice;
			}
		}
		else
		{//push lane
			if (!matchData.GetUserRole() == MatchInfoData::JNGL)
			{//top, mid, bot, support roles
				advice = "\nPush opposing lane and turret.\n";
				if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
				{//lane turrets may be defeated by then
					advice += "If opposing lane turrets defated, push enemy base.";
				}
				return advice;
			}
			else
			{//jungle role
				switch (matchData.GetPosition(match_time_entry))
				{
				case MatchInfoData::B_TOPJNG: case MatchInfoData::B_BOTJNG: case MatchInfoData::T_TOPJNG:
				case MatchInfoData::T_BOTJNG:
					advice = "\nExplore and push enemy jungle across from your current position.\n";
					break;
				default://every other lane
					advice = "\nPush opposing lane and turret.\n";
					if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
					{//lane turrets may be defeated by then
						advice += "If lane turrets are defated, defend base turret areas for lane.";
					}
					break;
				}
				return advice;
			}

		}
	}//stay end----------------------------------------------
	else
	{//shift
		int top, mid, bot, t_jungle, b_jungle;
		switch (matchData.GetUserRole())
		{
			case MatchInfoData::TOP:
				top = 50;
				mid = 25;
				bot = 15;
				t_jungle = 5;
				b_jungle = 5;//all adds up to 100
					break;
			case MatchInfoData::MIDLANE:
				mid = 50;
				top = 25;
				bot = 15;
				t_jungle = 5;
				b_jungle = 5;
				break;
			case MatchInfoData::BOTTOM: case MatchInfoData::SUPP:
				bot = 50;
				mid = 25;
				top = 15;
				t_jungle = 5;
				b_jungle = 5;
				break;
			default://jungle
				t_jungle = 35;
				b_jungle = 35;
				bot = 10;
				top = 10;
				mid = 10;
				break;
		}

		//decide where to shift
		advice += MapShifting(top, mid, bot, t_jungle, b_jungle, matchData.GetUserRole(), matchData.IsUserTopSpawn());

		//decide to push or protect shifted lane
		srand(time(0));
		randomPercent = (rand() % 20) + 1;
		randomrisk = (1 - safeFactor) * (randomPercent / 100);

		srand(time(0));
		randomPercent = (rand() % 100) + 1;
		reasoningRoll = randomPercent / 100;
		if (reasoningRoll <= safeFactor)
		{//protect lane
			if (!matchData.GetUserRole() == MatchInfoData::JNGL)
			{//top, mid, bot, support roles
				advice += "\nProtect lane turret.\n";
				if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
				{//lane turrets may be defeated by then
					advice += "If lane turrets are defated, defend base turret areas for lane.";
				}
				return advice;
			}
			else
			{//jungle role
				switch (matchData.GetPosition(match_time_entry))
				{
				case MatchInfoData::B_TOPJNG: case MatchInfoData::B_BOTJNG: case MatchInfoData::T_TOPJNG:
				case MatchInfoData::T_BOTJNG:
					advice = "\nClear out camps.\n";
					break;
				default://every other lane
					advice = "\nProtect lane turret.\n";
					if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
					{//lane turrets may be defeated by then
						advice += "If lane turrets are defated, defend base turret areas for lane.";
					}
					break;
				}
				return advice;
			}
		}
		else
		{//push lane
			if (!matchData.GetUserRole() == MatchInfoData::JNGL)
			{//top, mid, bot, support roles
				advice = "\nPush opposing lane and turret.\n";
				if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
				{//lane turrets may be defeated by then
					advice += "If opposing lane turrets defated, push enemy base.";
				}
				return advice;
			}
			else
			{//jungle role
				switch (matchData.GetPosition(match_time_entry))
				{
				case MatchInfoData::B_TOPJNG: case MatchInfoData::B_BOTJNG: case MatchInfoData::T_TOPJNG:
				case MatchInfoData::T_BOTJNG:
					advice = "\nExplore and push enemy jungle across from your current position.\n";
					break;
				default://every other lane
					advice = "\nPush opposing lane and turret.\n";
					if (matchData.GetTime(match_time_entry) >= MatchInfoData::MID)//if time is mid or over
					{//lane turrets may be defeated by then
						advice += "If lane turrets are defated, defend base turret areas for lane.";
					}
					break;
				}
				return advice;
			}
		}
	}//shift end ----------------------------------------------
}

string LogicalReasoning::MapShifting(int& top, int& mid, int& bot, int& t_jungle, int& b_jungle, MatchInfoData::Roles userRole, bool isTop)
{
	string advice = "";
	srand(time(0));
	int randomPercent = (rand() % 100) + 1;//use random num
	if (isTop)
	{
		advice += "\nShift to top side ";
	}
	else
	{
		advice += "\nShift to bottom side ";
	}

	switch (userRole)
	{
	case MatchInfoData::TOP:		
		if (randomPercent <= (top))
		{
			advice += "top lane ";
		}
		else if (randomPercent <= (top+mid))
		{
			advice += "mid lane ";
		}
		else if (randomPercent <= (top + mid + bot))
		{
			advice += "bottom lane ";
		}
		else if (randomPercent <= (top + mid + bot+ t_jungle))
		{
			advice += "top jungle area ";
		}
		else
		{
			advice += "bottom jungle area ";
		}
		break;
	case MatchInfoData::MIDLANE:
		if (randomPercent <= (mid))
		{
			advice += "mid lane ";
		}
		else if (randomPercent <= (mid + top))
		{
			advice += "top lane ";
		}
		else if (randomPercent <= (mid + top + bot))
		{
			advice += "bottom lane ";
		}
		else if (randomPercent <= (top + mid + bot + t_jungle))
		{
			advice += "top jungle area ";
		}
		else
		{
			advice += "bottom jungle area ";
		}

		break;
	case MatchInfoData::BOTTOM: case MatchInfoData::SUPP:
		if (randomPercent <= (bot))
		{
			advice += "bottom lane ";
		}
		else if (randomPercent <= (bot + mid))
		{
			advice += "mid lane ";
		}
		else if (randomPercent <= (bot + mid + top))
		{
			advice += "top lane ";
		}
		else if (randomPercent <= (bot + mid + top + b_jungle))
		{
			advice += "bottom jungle area ";
		}
		else
		{
			advice += "top jungle area ";
		}

		break;
	default://jungle
		if (randomPercent <= (t_jungle))
		{
			advice += "top jungle area ";
		}
		else if (randomPercent <= (t_jungle + b_jungle))
		{
			advice += "bottom jungle area ";
		}
		else if (randomPercent <= (t_jungle + b_jungle + top))
		{
			advice += "top lane ";
		}
		else if (randomPercent <= (t_jungle + b_jungle + top + bot))
		{
			advice += "bot lane ";
		}
		else
		{
			advice += "mid lane ";
		}

		break;
	}
	return advice;
}
//----------------------------------
void LogicalReasoning::UserChampionConsideration(MatchInfoData matchData)
{
	
}

void LogicalReasoning::RoleConsideration(MatchInfoData matchData)
{

}
//-----------------------------------

int LogicalReasoning::MapPositionConsideration(MatchInfoData::Roles userRole, MatchInfoData::MapPositions userPosition, int entry, bool isTop)
{
	switch (userPosition)
	{
		//**********************************************************************************
	case MatchInfoData::B_BOT: case MatchInfoData::T_BOT://in bottom lane, either from bottom or top
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = TOO_RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness*= TOO_SAFE; }//if spawned top and still top side, playing it safe
			else if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }//if spawned bot and still bot side, playing it safe
			//basically, if you still on your spawned side, you are playing it safer
			else{ currentRiskyness *= TOO_RISKY; }//else you are not on your spawned side, it is risky
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::SUPP:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOT) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOT) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		default:
			break;
		}
		//-------------------------------role switch end
		break;

		//**********************************************************************************
	case MatchInfoData::B_MID: case MatchInfoData::T_MID:
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_MID) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_MID) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_MID) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_MID) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_MID) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_MID) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::SUPP:
			currentRiskyness = TOO_RISKY;
			if (isTop && userPosition == MatchInfoData::T_MID) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_MID) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = MODERATE;
			if (isTop && userPosition == MatchInfoData::T_MID) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_MID) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		default:
			break;
		}
		//-------------------------------role switch end
		break;

		//**********************************************************************************
	case MatchInfoData::B_TOP: case MatchInfoData::T_TOP:
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_TOP) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOP) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_TOP) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOP) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = TOO_RISKY;
			if (isTop && userPosition == MatchInfoData::T_TOP) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOP) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::SUPP://support and jungle tend to have different principles than the core three lanes (top, bottom and mid)
			currentRiskyness = MODERATE;
			if (isTop && userPosition == MatchInfoData::T_TOP) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOP) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_TOP) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOP) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		default:
			break;
		}
		//-------------------------------role switch end
		break;

		//**********************************************************************************
	case MatchInfoData::B_BOTJNG: case MatchInfoData::T_BOTJNG:
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop && userPosition == MatchInfoData::T_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::SUPP://support and jungle tend to have different principles than the core three lanes (top, bottom and mid)
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BOTJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		default:
			break;
		}
		//-------------------------------role switch end
		break;

		//**********************************************************************************
	case MatchInfoData::B_TOPJNG: case MatchInfoData::T_TOPJNG:
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = LITTLE_MODERATE;
			if (isTop && userPosition == MatchInfoData::T_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::SUPP:
			currentRiskyness = RISKY;
			if (isTop && userPosition == MatchInfoData::T_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = SAFE;
			if (isTop && userPosition == MatchInfoData::T_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_TOPJNG) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= TOO_RISKY; }
			break;
		default:
			break;
		}
		//-------------------------------role switch end
		break;

	case MatchInfoData::B_BASE: case MatchInfoData::T_BASE:
		switch (userRole)
		{
		case MatchInfoData::TOP:
			currentRiskyness = TOO_SAFE;
			if (isTop && userPosition == MatchInfoData::T_BASE) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BASE) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= RISKY; }//risky, rather not too risky as we don't want to discourage attacking base when can
			break;
		case MatchInfoData::MIDLANE:
			currentRiskyness = TOO_SAFE;
			if (isTop && userPosition == MatchInfoData::T_BASE) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BASE) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= RISKY; }
			break;
		case MatchInfoData::BOTTOM:
			currentRiskyness = TOO_SAFE;
			if (isTop && userPosition == MatchInfoData::T_BASE) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BASE) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= RISKY; }
			break;
		case MatchInfoData::SUPP:
			currentRiskyness = TOO_SAFE;
			if (isTop && userPosition == MatchInfoData::T_BASE) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BASE) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= RISKY; }
			break;
		case MatchInfoData::JNGL:
			currentRiskyness = TOO_SAFE;
			if (isTop && userPosition == MatchInfoData::T_BASE) { currentRiskyness *= TOO_SAFE; }
			else if (!isTop && userPosition == MatchInfoData::B_BASE) { currentRiskyness *= TOO_SAFE; }
			else { currentRiskyness *= RISKY; }
			break;
		default:
			break;
		}
		//-------------------------------role switch end
		break;

		//**********************************************************************************
	default:
		break;
	}
	riskAmplifications += 2;
	return (TOO_RISKY * TOO_RISKY);//return mask risklevel of this method
}

void LogicalReasoning::TimeConsideration(MatchInfoData::GameTime time, int maxriskyness)
{//maxriskyness - max riskyness from last reasoning so the last steps for reasoing can be considered with the time
	//however, this iteration of time consideration nearly is tailored just for the map positioning feature. 
	//it would need modification so it can be more abstract, be able to work with other combinations of reasoning, not just the one
	/*
	* Time break down
	Early 1		<=6
	Early 2		<=12
	Mid			<=18
	Late 1		<=24
	Late 2		<=30+
	*/

	float riskdivision = ((float)currentRiskyness / (float)maxriskyness);
	//get current risk level in terms of max riskyness, e.g. say it is 14 (2(SAFE)*7(TOO_RISKY)) and max is 49 (7*7)
	//then 14/49 = 2/7 = 0.2857
	//then that is taken along with the current time and reasoned with
	//early1
	switch (time)
	{
	case MatchInfoData::EARLY1:
		if (riskdivision <= 0.1428)//riskdivision compared to 1/7 and so on (0 - 1)
		{//too safe
			currentRiskyness *= TOO_SAFE;
		}
		else if (riskdivision <= 0.2857)
		{
			currentRiskyness *= SAFE;
		}
		else if (riskdivision <= 0.4285)
		{
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.5714)
		{
			currentRiskyness *= MODERATE;
		}
		else if (riskdivision <= 0.7142)
		{
			currentRiskyness *= OVER_MODERATE;
		}
		else if (riskdivision <= 0.8571)
		{
			currentRiskyness *= RISKY;
		}
		else
		{//too risky
			currentRiskyness *= TOO_RISKY;
		}

		break;
	case MatchInfoData::EARLY2:
		if (riskdivision <= 0.1428)//riskdivision compared to 1/7 and so on (0 - 1)
		{//too safe
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.2857)
		{
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.4285)
		{
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.5714)
		{
			currentRiskyness *= MODERATE;
		}
		else if (riskdivision <= 0.7142)
		{
			currentRiskyness *= OVER_MODERATE;
		}
		else if (riskdivision <= 0.8571)
		{
			currentRiskyness *= RISKY;
		}
		else
		{//too risky
			currentRiskyness *= RISKY;
		}

		break;
	case MatchInfoData::MID:
		if (riskdivision <= 0.1428)//riskdivision compared to 1/7 and so on (0 - 1)
		{//too safe
			currentRiskyness *= OVER_MODERATE;
		}
		else if (riskdivision <= 0.2857)
		{
			currentRiskyness *= MODERATE;
		}
		else if (riskdivision <= 0.4285)
		{
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.5714)
		{
			currentRiskyness *= SAFE;
		}
		else if (riskdivision <= 0.7142)
		{
			currentRiskyness *= MODERATE;
		}
		else if (riskdivision <= 0.8571)
		{
			currentRiskyness *= OVER_MODERATE;
		}
		else
		{//too risky
			currentRiskyness *= RISKY;
		}

		break;
	case MatchInfoData::LATE1:
		if (riskdivision <= 0.1428)//riskdivision compared to 1/7 and so on (0 - 1)
		{//too safe
			currentRiskyness *= RISKY;
		}
		else if (riskdivision <= 0.2857)
		{
			currentRiskyness *= OVER_MODERATE;
		}
		else if (riskdivision <= 0.4285)
		{
			currentRiskyness *= MODERATE;
		}
		else if (riskdivision <= 0.5714)
		{
			currentRiskyness *= SAFE;
		}
		else if (riskdivision <= 0.7142)
		{
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.8571)
		{
			currentRiskyness *= MODERATE;
		}
		else
		{//too risky
			currentRiskyness *= OVER_MODERATE;
		}

		break;
	case MatchInfoData::LATE2:
		if (riskdivision <= 0.1428)//riskdivision compared to 1/7 and so on (0 - 1)
		{//too safe
			currentRiskyness *= TOO_RISKY;
		}
		else if (riskdivision <= 0.2857)
		{
			currentRiskyness *= RISKY;
		}
		else if (riskdivision <= 0.4285)
		{
			currentRiskyness *= OVER_MODERATE;
		}
		else if (riskdivision <= 0.5714)
		{
			currentRiskyness *= LITTLE_MODERATE;
		}
		else if (riskdivision <= 0.7142)
		{
			currentRiskyness *= MODERATE;
		}
		else if (riskdivision <= 0.8571)
		{
			currentRiskyness *= OVER_MODERATE;
		}
		else
		{//too risky
			currentRiskyness *= OVER_MODERATE;
		}

		break;
	default:
		break;
	}
	riskAmplifications += 1;
}

void LogicalReasoning::LevelConsideration(MatchInfoData& matchData)
{
	float levelratio = (matchData.GetLevel(match_time_entry)/ matchData.GetAverageLvl(match_time_entry));
	/*switch (matchData.GetTime(match_time_entry))
	{
	case MatchInfoData::EARLY1:
		break;
	case MatchInfoData::EARLY2:
		break;
	case MatchInfoData::MID:
		break;
	case MatchInfoData::LATE1:
		break;
	case MatchInfoData::LATE2:
		break;

	}*/
	if (levelratio <= 0.1)
	{
		currentRiskyness *= TOO_RISKY;
	}
	else if (levelratio <= 0.5)
	{
		currentRiskyness *= RISKY;
	}
	else if (levelratio <= 0.75)
	{
		currentRiskyness *= OVER_MODERATE;
	}
	else if(levelratio <= 1)
	{
		currentRiskyness *= MODERATE;
	}
	else if (levelratio <= 1.25)
	{
		currentRiskyness *= LITTLE_MODERATE;
	}
	else if (levelratio <= 1.75)
	{
		currentRiskyness *= SAFE;
	}
	else//above 1.75+
	{
		currentRiskyness *= TOO_SAFE;
	}
	riskAmplifications += 1;
}

//void LogicalReasoning::EnemyStrengthConsideration(MatchInfoData& matchData)
//{
//	//may not need this
//}

void LogicalReasoning::BaseConsideration(MatchInfoData& matchData)
{	
	if (matchData.IsBaseUnderAttack(match_time_entry))
	{//base under attack
		currentRiskyness *= RISKY;
	}
	else
	{
		currentRiskyness *= SAFE;
	}
	riskAmplifications += 1;
}

void LogicalReasoning::KD_Consideration(MatchInfoData& matchData)
{
	if (matchData.GetKD(match_time_entry) <= -1)
	{
		currentRiskyness *= RISKY;
	}
	if (matchData.GetKD(match_time_entry) <= -0.5)
	{
		currentRiskyness *= OVER_MODERATE;
	}
	else if (matchData.GetKD(match_time_entry) <= 0.0f)
	{
		currentRiskyness *= MODERATE;
	}
	if (matchData.GetKD(match_time_entry) <= 0.5)
	{
		currentRiskyness *= LITTLE_MODERATE;
	}
	else if (matchData.GetKD(match_time_entry) <= 1)
	{
		currentRiskyness *= SAFE;
	}
	riskAmplifications += 1;
}