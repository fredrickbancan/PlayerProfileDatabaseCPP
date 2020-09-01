#pragma once
/*Simple player struct for storing player data*/
struct PlayerProfile
{
	char name[16];
	unsigned int highScore;
	int originalLineNumber;//the line number in which this profile is/was located in the database file. -1 if it has not been saved yet.
};
