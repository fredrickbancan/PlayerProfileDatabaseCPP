#pragma once
constexpr unsigned int nameLength = 16;//15 characters plus 1 for null terminator
/*Simple player struct for storing player data*/
struct PlayerProfile
{
	PlayerProfile(const char* name, unsigned int score)//constructor for creating new profiles
	{
		for (unsigned int i = 0; name[i] != '\0' && i < nameLength-1; i++)
		{
			this->name[i] = name[i];
		}
		highScore = score;
	}

	PlayerProfile(const char* loadedData/*char array 24 bytes long*/)//constructor for loading profiles
	{
		for (unsigned int i = 0; i < nameLength-1; i++)//load name from bytes
		{
			name[i] = loadedData[i];
		}

		highScore = (unsigned int)(loadedData[nameLength + 3] << 24 | loadedData[nameLength + 2] << 16 | loadedData[nameLength + 1] << 8 | loadedData[nameLength]);
		//We shouldnt load the line number from what is saved on file. The line number should be assigned when the data is loaded depending on where the cursor is when it was read.
		//originalLineNumber = (unsigned int)(loadedData[nameLength + 7] << 24 | loadedData[nameLength + 6] << 16 | loadedData[nameLength + 5] << 8 | loadedData[nameLength + 4]);
	}

	PlayerProfile()//default constructor
	{

	}

	const PlayerProfile& setLineNumber(unsigned int num)//builder method
	{
		originalLineNumber = num;
		return *this;
	}

	char name[nameLength] = {'\0'};
	unsigned int highScore = 0;
	unsigned int originalLineNumber = 0;//the line number in which this profile is/was located in the database file starting from 1. 0 if it has not been saved yet.
};
