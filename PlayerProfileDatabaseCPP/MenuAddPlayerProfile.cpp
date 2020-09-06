#include "MenuAddPlayerProfile.h"
#include "ProfileConsole.h"
#include "PlayerProfile.h"
#include "DatabaseManager.h"

void MenuAddPlayerProfile::doMenu()
{
	char inputName[16];
	ProfileConsole::announce("Enter the name of the player you want to add:");
	ProfileConsole::announce("(1-15 characters)");

	//get player name
	while (true)
	{
		for (unsigned short i = 0; i < 16; i++)//reset name buffer to 0
		{
			inputName[i] = '\0';
		}

		std::cin.get(inputName, 16);
		std::cout << std::endl;

		inputName[15] = '\0';//make sure string is null terminated

		/*check if name was legit*/
		if (ProfileConsole::isNullOrWhiteSpace(inputName) || std::cin.fail())
		{
			ProfileConsole::error("Please enter atleast 1 character for the players name!");
			std::cout << std::endl;
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more
			continue;
		}
		break;
	}

	std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more

	ProfileConsole::announce("Enter high score for the player:");
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

		DatabaseManager::get()->addOrReplaceProfile(inputName, number);
		ProfileConsole::list("Added new player profile.");

		std::cin.ignore(std::cin.rdbuf()->in_avail());//resets the console input so we can provide more
		return;
	}
}
