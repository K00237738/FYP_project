#pragma once
#ifndef DATA_EXTRACTION
#define DATA_EXTRACTION

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
	void MapMovementDataGathering();
	void ReturnData();
};

#endif // !DATA_EXTRACTION

