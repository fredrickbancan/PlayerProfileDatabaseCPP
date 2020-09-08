#pragma once
constexpr unsigned int nameLength = 16;//15 characters plus 1 for null terminator
/*Simple player struct for storing player data*/
struct PlayerProfile
{
	PlayerProfile(const char* name, unsigned int score)//constructor for creating new and loading profiles
	{
		for (unsigned int i = 0; name[i] != '\0' && i < nameLength-1; i++)
		{
			this->name[i] = name[i];
		}
		highScore = score;
	}

	PlayerProfile()//default constructor
	{

	}
	
	/*overwritten assignment operator for preserving original line number.*/
	PlayerProfile& operator = (const PlayerProfile& replacer)
	{
		if (this == &replacer) return *this;

		for (unsigned int i = 0;  i < nameLength - 1; i++)//overwrite name
		{
			name[i] = replacer.name[i];
		}
		highScore = replacer.highScore;

		/*Only overwrite line number if its zero.*/
		if (originalLineNumber == 0)
		{
			originalLineNumber = replacer.originalLineNumber;
		}
		return *this;
	}

	const PlayerProfile& setLineNumber(unsigned int num)//builder method
	{
		originalLineNumber = num;
		return *this;
	}

	char name[nameLength] = {'\0'};
	unsigned int highScore = 0;
	unsigned int originalLineNumber = 0;//the line number in which this profile was located in the database file starting from 1. 0 if it has not been saved yet.
};

