// main.cpp

#include <RiotCPP/Riot.hpp>

int main(int argc, char** argv)
{
	Riot::api_key = "XXX";
	Riot::region = Riot::Region::EUW;    // Note: these values default to NA
	Riot::locale = Riot::Locale::en_US; // and en_US and do not need to be set

	// We are now ready to use riot-cpp!
	// See below for the list of API functions
}