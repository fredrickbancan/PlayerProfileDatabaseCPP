#include "MenuChangePlayerProfile.h"
#include "DatabaseManager.h"
#include "PlayerProfile.h"
#include "ProfileConsole.h"

void MenuChangePlayerProfile::doMenu()
{
	PlayerProfile* foundProfile;
	ProfileConsole::announce("Enter the name of the player whos high score you wish to edit:");
	ProfileConsole::announce("(1-15 characters)");

	//get player name
	while (true)
	{
		char input[16];
		std::cin.get(input, 16);
		std::cout << std::endl;

		input[15] = '\0';//make sure string is null terminated

		/*check if name was legit*/
		if (ProfileConsole::isNullOrWhiteSpace(input) || std::cin.fail())
		{
			ProfileConsole::error("Please enter atleast 1 character for the players name!");
			std::cout << std::endl;
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more
			continue;
		}

		if (DatabaseManager::get()->findProfile(input, foundProfile))
		{
			break; 
		}
		else
		{
			ProfileConsole::error("Could not find profile with provided name.");
			std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more
			return;
		}
	}

	std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more

	ProfileConsole::announce("Enter new high score for found player:");
	ProfileConsole::announce("(must be numerical value)");

	//get player new score
	while (true)
	{
		unsigned long number;
		std::string numbuf;
		std::cin >> numbuf;
		std::cout << std::endl;
		number = strtoul(numbuf.c_str(), nullptr, 10);

		/*If the input buffer is empty, contains non numbers or str to ul has error*/
		if (ProfileConsole::isNullOrWhiteSpace(numbuf.c_str()) || numbuf.find_first_not_of("0123456789") != std::string::npos || errno != 0)
		{
			ProfileConsole::error("Invalid input, try again!");
			std::cout << std::endl;
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more
			errno = 0;//reset error flag
			continue;
		}
		
		foundProfile->highScore = (unsigned int)number;
		DatabaseManager::get()->addProfileToChangedList(foundProfile);
		ProfileConsole::list("Changed profile high score.");

		std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more
		return;
	}
}
