#include "DatabaseManager.h"
#include "PlayerArray.h"
#include "PlayerProfile.h"
#include "ProfileConsole.h"
#include "direct.h"//for getting working directory
#include <string>
#include <fstream>//for editing directory file

DatabaseManager* DatabaseManager::instance = nullptr;
DatabaseManager* DatabaseManager::get()
{
	if (instance == nullptr)
	{
		instance = new DatabaseManager();
	}
	return instance;
}

DatabaseManager::~DatabaseManager()
{
	delete loadedData;
	delete changedData;
}

void DatabaseManager::addNewPlayerProfile(const char* name, unsigned int score)
{
	//TODO: impliment
}

void DatabaseManager::printDatabaseToConsole()
{
	loadedData->sortAlphabetically();
	for (unsigned int i = 0; i < loadedData->getCount(); i++)
	{
		std::string entry = std::string("Name: ") + loadedData->getElements()[i].name + std::string(" | High Score: ") + std::to_string(loadedData->getElements()[i].highScore);
		ProfileConsole::list(entry.c_str());
	}
}

bool DatabaseManager::tryToChangeExistingPlayerProfile(const char* name, unsigned int score)
{
	//TODO: impliment
	return false;
}

void DatabaseManager::tryToSaveChangedDataToFile()
{
	//TODO: impliment
}

std::string getWorkingDir()
{
	//getting current working dir, 1000 is the max bytes allowed for the directory. It shouldnt be more than that.
	char dir[1000];
	const char* dirHandle = _getcwd(dir, 1000);
	return std::string(dir);
}

void DatabaseManager::tryToLoadDatabase()
{
	bool databaseExists = false;
	std::string dir = getWorkingDir();
	ProfileConsole::announce(std::string("Checking directory for database file: "  + dir + "\n").c_str());

	//try to find file
	std::ifstream fileCheck((dir + "\\database.bin").c_str());

	if (!fileCheck.fail())//if the file was found
	{
		ProfileConsole::list("Database file found, opening!");
	}
	else
	{
		ProfileConsole::announce("Database file not found, attempting to create new one.");
		databaseExists = false;
	}

	//try to open file
	std::ofstream fileStream;
	fileStream.open(dir + "\\database.bin");

	if (fileStream.fail())//if the file could not be opened
	{
		ProfileConsole::error(std::string("Could not open or create database file (.bin) at directory!\nDir: " + dir).c_str());
		error = true;
		databaseExists = false;
	}
	else
	{
		ProfileConsole::list("Opened directory file!");
		databaseExists = true;
	}
	ProfileConsole::pausePrompt();

	if (databaseExists)//attempt to load data from file.
	{
		//TODO: load actual binary data into player array.
		loadedData = new PlayerArray(new PlayerProfile[2]{ {"test1ffffffffff", 420}, {"test2", 69} }, 2);
	}

	fileCheck.close();//do last
	fileStream.close();//do last
}