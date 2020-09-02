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
		std::string entry = std::string("Name: ") + loadedData->elementAt(i).name + std::string(" | High Score: ") + std::to_string(loadedData->elementAt(i).highScore);
		ProfileConsole::list(entry.c_str());
	}
}

bool DatabaseManager::tryToChangeExistingPlayerProfile(const char* name, unsigned int score)
{
	//TODO: impliment, after changing existing player data, add to changed player data array for saving.
	return false;
}

std::string getWorkingDir()
{
	//getting current working dir, 1000 is the max bytes allowed for the directory. It shouldnt be more than that.
	char dir[1000];
	const char* dirHandle = _getcwd(dir, 1000);
	return std::string(dir);
}

void DatabaseManager::tryToSaveChangedDataToFile()
{
	std::string dir = getWorkingDir();

	//try to open file
	std::fstream fileStream;
	fileStream.open(dir + "\\database.bin", std::ios::in | std::ios::out | std::ios::binary);

	if (fileStream.fail() || !fileStream.is_open())//if the file could not be opened
	{
		error = true;
		fileStream.close();
		return;
	}

	if (true)//if theres any changed profiles to save
	{
		unsigned int databaseEntryCount = 0;
		char* entryData = new char[sizeof(PlayerProfile)];
		for (unsigned int i = 0; i < 1; i++)//loop through each changed profile
		{
			if (fileStream.peek() != std::ifstream::traits_type::eof())//if the file is not empty
			{
				//TODO: impliment, set error to true if fail to save data
				while (!fileStream.eof())//while the file stream has not reached end of file
				{
					fileStream.read(entryData, sizeof(PlayerProfile));
					std::cout << sizeof(PlayerProfile) << std::endl;
					ProfileConsole::list(entryData);
					ProfileConsole::pausePrompt();
				}
			}
		}
		delete[] entryData;
	}

	fileStream.close();//do last
}

void DatabaseManager::tryToLoadDatabase()
{
	bool databaseExists = false;
	std::string dir = getWorkingDir();
	ProfileConsole::announce(std::string("Checking directory for database file: "  + dir + "\n").c_str());

	//try to find file
	std::ifstream inFileStream((dir + "\\database.bin").c_str());

	if (!inFileStream.fail() && inFileStream.is_open())//if the file was found
	{
		ProfileConsole::list("Database file found, opening!");
		databaseExists = true;
	}
	else
	{
		ProfileConsole::announce("Database file not found, attempting to create new one.");
		databaseExists = false;
	}

	//try to open file
	//std::ofstream outFileStream;
	//outFileStream.open(dir + "\\database.bin");

	//if (outFileStream.fail() || !outFileStream.is_open())//if the file could not be opened
	//{
	//	ProfileConsole::error(std::string("Could not open or create database file (.bin) at directory!\nDir: " + dir).c_str());
	//	error = true;
	//	databaseExists = false;
	//}
	//else
	//{
	//	ProfileConsole::list("Opened directory file!");
	//}
	//outFileStream.close();

	ProfileConsole::pausePrompt();

	if (databaseExists)//attempt to load data from file using inFileStream
	{
		//TODO: load actual binary data into player array.
		loadedData = new PlayerArray(new PlayerProfile[2]{ {"test1ffffffffff", 420}, {"test2", 69} }, 2);
	}
	else
	{
		loadedData = new PlayerArray(new PlayerProfile[0], 0);//initialize the data to be empty if there was no existing database file
	}

	inFileStream.close();//do last
}