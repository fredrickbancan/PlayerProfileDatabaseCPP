#pragma once
class PlayerArray;
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
	void init() { tryToLoadDatabase(); }

	/*adds new player profile to database with provided name and high score*/
	void addNewPlayerProfile(const char* name, unsigned int score);

	/*Prints the loaded database to console in alphabetical order*/
	void printDatabaseToConsole();

	/*Attempts to find a provided player profile by name and changes its high score to the one provided.
	  Returns: true if found, false if not found.*/
	bool tryToChangeExistingPlayerProfile(const char* name, unsigned int score);

	/*Attempts to save all of the changed data to the binary file. If there is no file, creates a new one.*/
	void tryToSaveChangedDataToFile();
};