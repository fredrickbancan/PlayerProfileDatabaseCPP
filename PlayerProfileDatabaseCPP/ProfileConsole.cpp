#include "ProfileConsole.h"
#include "DatabaseManager.h"
#include "MenuAddPlayerProfile.h"
#include "MenuChangePlayerProfile.h"
#include "conio.h"

ProfileConsole* ProfileConsole::instance = nullptr;
ProfileConsole* ProfileConsole::get()
{
	if (instance == nullptr)
	{
		instance = new ProfileConsole();
	}
	return instance;
}

ProfileConsole::~ProfileConsole()
{
	delete playerAddMenu;
	delete playerChangeMenu;
}

void ProfileConsole::init()
{
	playerAddMenu = new MenuAddPlayerProfile();
	playerChangeMenu = new MenuChangePlayerProfile();
}

void ProfileConsole::doUserInput()
{
	bool quitting = false;

	announce("Welcome to the player database console.");
	pausePrompt();

	char pressedChar = 0;
	while (!quitting)
	{
		clearPrompt();
		announce("What would you like to do?");
		announce("Press the corrisponding number for your choice:");
		announce("0: Save and Quit.");
		announce("1: View Database.");
		announce("2: Add new player profile to database.");
		announce("3: Change existing entry in database.");
		pressedChar = 0;
		switch (pressedChar = _getch())
		{
			case 48://0
				quitting = true;
			break;

			case 49://1
				clearPrompt();
				announce("All found entries in database: ");
				DatabaseManager::get()->printDatabaseToConsole();
				pausePrompt();
				break;

			case 50://2
				clearPrompt();
				playerAddMenu->doMenu();
				pausePrompt();
				break;

			case 51://3
				clearPrompt();
				playerChangeMenu->doMenu();
				pausePrompt();
				break;

			default:
				clearPrompt();
				error("Invalid input. Please try again.");
				pausePrompt();
				break;
		}
	}

	clearPrompt();
	list("Goodbye!");
	pausePrompt();
}