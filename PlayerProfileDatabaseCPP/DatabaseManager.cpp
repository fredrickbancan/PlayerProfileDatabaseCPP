#include "DatabaseManager.h"
#include "PlayerArray.h"
#include "PlayerProfile.h"
#include <string>
#include "ProfileConsole.h"
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

void DatabaseManager::tryToLoadDatabase()
{
	loadedData = new PlayerArray(new PlayerProfile[2]{ {"test1ffffffffff", 420}, {"test2", 69} }, 2);
}