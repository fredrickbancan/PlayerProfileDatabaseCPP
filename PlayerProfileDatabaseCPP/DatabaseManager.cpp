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

void DatabaseManager::addProfileToChangedList(const PlayerProfile* profile)
{
	if (changedData->contains(profile->name))
	{
		changedData->replaceProfile(*profile);
	}
	else
	{
		changedData->addNewProfile(*profile);
	}

	for (unsigned int i = 0; i < changedData->getCount(); i++)
	{
		std::cout << changedData->elementAt(i).name << std::endl;
		std::cout << changedData->elementAt(i).highScore << std::endl;
		std::cout << changedData->elementAt(i).originalLineNumber << std::endl;
	}
}

void DatabaseManager::addOrReplaceProfile(const char* name, unsigned int score)
{

	//if profile exists in database then we need to overwrite score and add it to changed array
	if (loadedData->contains(name))
	{
		PlayerProfile* result;
		loadedData->findProfile(name, result);
		result->highScore = score;

		if (changedData->contains(name))
		{
			changedData->replaceProfile(*result);
		}
		else
		{
			changedData->addNewProfile(*result);
		}
	}
	else
	{
		loadedData->addNewProfile(PlayerProfile(name, score));
		if (changedData->contains(name))
		{
			PlayerProfile* result;
			changedData->findProfile(name, result);
			result->highScore = score;
		}
		else
		{
			changedData->addNewProfile(PlayerProfile(name, score));
		}
	}
}

void DatabaseManager::printDatabaseToConsole()
{
	loadedData->sortAlphabetically();
	ProfileConsole::announce(std::string("Count of entries: " + std::to_string(loadedData->getCount())).c_str());
	for (unsigned int i = 0; i < loadedData->getCount(); i++)
	{
		std::string entry = std::string("Name: ") + loadedData->elementAt(i).name + std::string(" | High Score: ") + std::to_string(loadedData->elementAt(i).highScore);
		ProfileConsole::list(entry.c_str());
	}
}

bool DatabaseManager::findProfile(const char* name, PlayerProfile*& result)
{
	return loadedData->findProfile(name, result);
}

bool DatabaseManager::tryToChangeExistingPlayerProfile(const char* name, unsigned int score)
{
	PlayerProfile* result = nullptr;
	if (loadedData->findProfile(name, result))
	{
		if (result != nullptr)
		{
			result->highScore = score;

			//add changed profile to changed data to be saved
			if (changedData->contains(result->name))
			{
				changedData->replaceProfile(*result);
			}
			else
			{
				changedData->addNewProfile(*result);
			}
		}
		return true;
	}
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

	std::fstream fileStream;

	//try to open file
	fileStream.open(getDatabaseDir(), std::ios::in | std::ios::out | std::ios::binary);
	if (fileStream.fail() || !fileStream.is_open())//if the file could not be opened
	{
		ProfileConsole::error("Could not access database to save profiles!");
		error = true;
		fileStream.close();
		ProfileConsole::pausePrompt();
		return;
	}

	//if the file is empty, we just need to append all changed (new) profiles to the file and return
	if (fileStream.peek() == std::ifstream::traits_type::eof())
	{
		fileStream.close();
		fileStream.open(getDatabaseDir(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);//re open filestream with append mode.
		for (unsigned int i = 0; i < changedData->getCount(); i++)//loop through each changed profile
		{
			ProfileConsole::announce(std::string("Saving new profile: " + std::string(changedData->elementAt(i).name)).c_str());//print name of saved profile
			fileStream.write((const char*)&(changedData->elementAt(i)), sizeof(PlayerProfile));//write bytes of the profile
		}
		fileStream.close();
		return;//saving complete, exit method.
	}

	//loop through each changed profile and save all pre-existing profiles that have changed to their assigned line number (save index)
	for (unsigned int i = 0; i < changedData->getCount(); i++)
	{
		if (changedData->elementAt(i).originalLineNumber > 0)
		{
			ProfileConsole::announce(std::string("Saving changed profile: " + std::string(changedData->elementAt(i).name)).c_str());//print name of saved profile
			
			//move cursor to beginning of profile at specific line number (save index)
			fileStream.seekp((long long)(changedData->elementAt(i).originalLineNumber - 1) * sizeof(PlayerProfile), std::ios::beg);
			fileStream.write((const char*)&(changedData->elementAt(i)), sizeof(PlayerProfile));//write bytes of the profile
		}
	}

	//re open filestream with append mode for saving newly added profiles.
	fileStream.close();
	fileStream.open(getDatabaseDir(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

	//loop through each changed profile and save all new profiles at end of file
	for (unsigned int i = 0; i < changedData->getCount(); i++)
	{
		if (changedData->elementAt(i).originalLineNumber == 0)//0 means new profile.
		{
			ProfileConsole::announce(std::string("Saving new profile: " + std::string(changedData->elementAt(i).name)).c_str());//print name of saved profile
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
	std::fstream fileStream(getDatabaseDir(), std::ios::in | std::ios::binary);

	if (fileStream.is_open())//if the file was found
	{
		ProfileConsole::list("");
		ProfileConsole::list("Database file found, opening!");
		previousDatabaseExists = true;
		ProfileConsole::pausePrompt();
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
		ProfileConsole::error("");
		ProfileConsole::error("Database file could not be created and/or opened!");
		error = true;
		ProfileConsole::pausePrompt();
	}
	else if(!previousDatabaseExists)
	{
		ProfileConsole::list("");
		ProfileConsole::list("New database file created and opened!");
		ProfileConsole::pausePrompt();
	}

	if (!previousDatabaseExists)//if this is a brand new database
	{
		loadedData = new PlayerArray(new PlayerProfile[0], 0);//initialize the data to be empty if there was no existing database file
		fileStream.close();
		return;//exit method, loading is complete.
	}

	char currentProfileName[nameLength] = { '\0' };
	unsigned int readScore = 0;//highscore read from bytes
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
		fileStream.read(currentProfileName, nameLength);//read bytes to name buffer
		fileStream.read(reinterpret_cast<char*>(&readScore), sizeof(readScore));//read next 4 bytes to score

		//skip over the remaining bytes of the profile (line number unsigned int, 4 bytes)
		fileStream.seekg(sizeof(PlayerProfile) - (nameLength + sizeof(readScore)), std::ios::cur);

		loadedData->addNewProfile(PlayerProfile(currentProfileName, readScore).setLineNumber(i + 1));//add new profile with name and score read, and set line number. Plus one because our line number starts from 1

		//clear buffer to zeros
		for (unsigned int j = 0; j < nameLength; j++)
		{
			currentProfileName[j] = '\0';
		}
		readScore = 0;//reset score
	}
	fileStream.close();
}