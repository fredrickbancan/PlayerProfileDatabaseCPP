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

void DatabaseManager::init()
{
	changedData = new PlayerArray(new PlayerProfile[0], 0);//initializing changedData array to be empty to prepare it for use.
	tryToLoadDatabase();
}

void DatabaseManager::addNewPlayerProfile(const char* name, unsigned int score)
{
	changedData->addProfile(PlayerProfile(name, score).setLineNumber(0));
}

void DatabaseManager::printDatabaseToConsole()
{
	loadedData->sortAlphabetically();
	std::cout << loadedData->getCount() << std::endl;
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

/*returns a string which is the directory of the database file*/
std::string getDatabaseDir()
{
	//getting current working dir, 512 is the max bytes allowed for the directory. It shouldnt be more than that.
	char dir[512];
	const char* dirHandle = _getcwd(dir, 512);
	return std::string(dir + std::string("\\database.bin"));
}

void DatabaseManager::tryToSaveChangedDataToFile()
{
	if (changedData->getCount() == 0)//if theres no changed profiles
	{
		return;
	}

	//try to open file
	std::fstream fileStream;

	fileStream.open(getDatabaseDir(), std::ios::in | std::ios::out | std::ios::binary);
	if (fileStream.fail() || !fileStream.is_open())//if the file could not be opened
	{
		ProfileConsole::error("Could not access database to save profiles!");
		error = true;
		fileStream.close();
		ProfileConsole::pausePrompt();
		return;
	}

	if (fileStream.peek() == std::ifstream::traits_type::eof())//if the file is empty, we just need to append all changed (new) profiles to the file and return
	{
		fileStream.close();
		fileStream.open(getDatabaseDir(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);//re open filestream with append mode.
		for (unsigned int i = 0; i < changedData->getCount(); i++)//loop through each changed profile
		{
			ProfileConsole::announce(std::string("Saving profile: " + std::string(changedData->elementAt(i).name)).c_str());//print name of saved profile
			fileStream.write((const char*)&(changedData->elementAt(i)), sizeof(PlayerProfile));//write bytes of the profile
		}
		fileStream.close();
		return;//saving complete, exit method.
	}


	for (unsigned int i = 0; i < changedData->getCount(); i++)//loop through each changed profile and save all pre-existing profiles that have changed to their assigned line number (save index)
	{
		if (changedData->elementAt(i).originalLineNumber > 0)
		{
			ProfileConsole::announce(std::string("Saving profile: " + std::string(changedData->elementAt(i).name)).c_str());//print name of saved profile
			
			//move cursor to beginning of profile at specific line number (save index)
			//TODO: test if working correctly
			fileStream.seekp((long long)(changedData->elementAt(i).originalLineNumber - 1) * sizeof(PlayerProfile), std::ios::beg);
			fileStream.write((const char*)&(changedData->elementAt(i)), sizeof(PlayerProfile));//write bytes of the profile
		}
	}

	fileStream.close();
	fileStream.open(getDatabaseDir(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);//re open filestream with append mode for saving newly added profiles.
	for (unsigned int i = 0; i < changedData->getCount(); i++)//loop through each changed profile and save all new profiles at end of file
	{
		if (changedData->elementAt(i).originalLineNumber == 0)
		{
			ProfileConsole::announce(std::string("Saving profile: " + std::string(changedData->elementAt(i).name)).c_str());//print name of saved profile
			fileStream.write((const char*)&(changedData->elementAt(i)), sizeof(PlayerProfile));//write bytes of the profile
		}
	}
	fileStream.close();
}

void DatabaseManager::tryToLoadDatabase()
{
	bool previousDatabaseExists = false;
	ProfileConsole::announce(std::string("Checking directory for database file: " + getDatabaseDir()).c_str());

	//try to find file
	std::fstream fileStream(getDatabaseDir(), std::ios::in);

	if (fileStream.is_open())//if the file was found
	{
		ProfileConsole::list("Database file found, opening!");
		previousDatabaseExists = true;
	}
	else if (fileStream.fail())
	{
		ProfileConsole::announce("Database file not found, attempting to create new one.");
		previousDatabaseExists = false;

		/*Creating empty file using an ofstream at the directory*/
		fileStream.close();
		std::ofstream fileCreator;
		fileCreator.open(getDatabaseDir(), std::ios::out);
		fileCreator.close();
		fileStream.open(getDatabaseDir(), std::ios::in);
	}

	if (!previousDatabaseExists && (!fileStream.is_open() || fileStream.fail()))
	{
		ProfileConsole::error("Database file could not be created and/or opened!");
		error = true;
		ProfileConsole::pausePrompt();
	}
	else if(!previousDatabaseExists)
	{
		ProfileConsole::list("New database file created and opened!");
		ProfileConsole::pausePrompt();
	}

	if (!previousDatabaseExists)//if this is a brand new database
	{
		loadedData = new PlayerArray(new PlayerProfile[0], 0);//initialize the data to be empty if there was no existing database file
		fileStream.close();
		return;//exit method, loading is complete.
	}

	char currentProfileData[sizeof(PlayerProfile)] = { '\0' };
	loadedData = new PlayerArray(new PlayerProfile[0], 0);
	bool endOfData = false;
	char test;
	for (unsigned int i = 0; !endOfData; i++)//loop through all data in database file and construct playerprofiles for each chunk of bytes the size of a playerprofile.
	{
		for (unsigned int j = 0; j < sizeof(PlayerProfile); j++)//step over next playerprofile bytes to check if theres enough left to construct a profile.
		{
			fileStream.read(&test, 1);//apparently it is required to read each byte to detect end of file
			if (fileStream.eof())//if the end of the file is reached, break out of loop. loading is finished.
			{
				endOfData = true;
				break;
			}
		}
		if (endOfData)
		{
			break;//if the end of the file is reached, break out of loop. loading is finished.
		}

		fileStream.seekg(-(int)(sizeof(PlayerProfile)), std::ios::cur);//move back to the beginning of the current profile bytes.
		fileStream.read(currentProfileData, sizeof(PlayerProfile));//read bytes to buffer

		loadedData->addProfile(PlayerProfile(currentProfileData).setLineNumber(i + 1));//add new profile with data read, and set line number. Plus one because our line number starts from 1

		//clear buffer to zeros
		for (unsigned int j = 0; j < sizeof(PlayerProfile); j++)
		{
			currentProfileData[j] = '\0';
		}
	}
	fileStream.close();
}