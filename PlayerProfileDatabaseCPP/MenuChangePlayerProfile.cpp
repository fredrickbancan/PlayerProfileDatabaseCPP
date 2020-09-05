#include "MenuChangePlayerProfile.h"
#include "DatabaseManager.h"
#include "PlayerProfile.h"
#include <iostream>
void MenuChangePlayerProfile::doMenu()
{
	//TODO: impliment
	bool found = false;
	found = DatabaseManager::get()->tryToChangeExistingPlayerProfile("bancan", 420);
	std::cout << found << std::endl;

}
