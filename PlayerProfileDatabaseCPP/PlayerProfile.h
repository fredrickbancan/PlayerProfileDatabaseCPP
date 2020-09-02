#pragma once
/*Simple player struct for storing player data*/
struct PlayerProfile
{
	char name[16];
	unsigned int highScore;
	unsigned int originalLineNumber;//the line number in which this profile is/was located in the database file starting from 1. 0 if it has not been saved yet.
};
