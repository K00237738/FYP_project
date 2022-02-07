// main.cpp

#include <RiotCPP/Riot.hpp>

int main(int argc, char** argv)
{
	Riot::api_key = "RGAPI-33def720-b42d-4512-90c4-abcae1b53fd1";
	Riot::region = Riot::Region::EUW;    // Note: these values default to NA
	Riot::locale = Riot::Locale::en_US; // and en_US and do not need to be set

	// We are now ready to use riot-cpp!
	// See below for the list of API functions
}