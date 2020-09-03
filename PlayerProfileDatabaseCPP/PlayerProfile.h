#pragma once
/*Simple player struct for storing player data*/
struct PlayerProfile
{
	PlayerProfile(const char* name, unsigned int score)//constructor for creating new profiles
	{
		for (unsigned int i = 0; name[i] != '\0' && i < 16; i++)
		{
			this->name[i] = name[i];
		}
		highScore = score;
	}
	PlayerProfile()
	{

	}
	char name[16] = {'\0'};
	unsigned int highScore = 0;
	unsigned int originalLineNumber = 0;//the line number in which this profile is/was located in the database file starting from 1. 0 if it has not been saved yet.
};
