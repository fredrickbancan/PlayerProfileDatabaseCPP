#pragma once
class PlayerArray;
struct PlayerProfile;
/*static class for loading, editing and saving player profile database*/
class DatabaseManager
{
	//fields
private:
	/*singleton instance*/
	static DatabaseManager* instance;

	/*Database loaded from file, or made new.*/
	PlayerArray* loadedData = nullptr;

	/*array of changed/new entries. This array is used for saving to file.
	  Only entries in this array are saved to file, meaning only changed entries are saved,
	  increasing saving efficiency.*/
	PlayerArray* changedData = nullptr;

	/*Bool will be true if there was an error loading/opening the database file.*/
	bool error = false;
public:

	//functions
private:
	/*attempts to load database from file, otherwise creates empty.*/
	void tryToLoadDatabase();
public:
	/*returns singleton instance*/
	static DatabaseManager* get();

	~DatabaseManager();

	/*initialize database manager*/
	void init();

	/*adds the provided profile to the changed list so it will be saved to file*/
	void addProfileToChangedList(const PlayerProfile* profile);

	/*adds or replaces a profile depending if its already in the data. This avoids creating duplicate profiles.*/
	void addOrReplaceProfile(const char* name, unsigned int score);

	/*Prints the loaded database to console in alphabetical order*/
	void printDatabaseToConsole();

	/*returns true if profile is found in database and assigns it to result pointer for use*/
	bool findProfile(const char* name, PlayerProfile*& result);

	/*Attempts to find a provided player profile by name and changes its high score to the one provided.
	  Returns: true if found, false if not found.*/
	bool tryToChangeExistingPlayerProfile(const char* name, unsigned int score);

	/*Attempts to save all of the changed data to the binary file.*/
	void tryToSaveChangedDataToFile();

	/*Returns true if there was an error in opening / loading the database file.*/
	bool getHasError() { return error; }
};