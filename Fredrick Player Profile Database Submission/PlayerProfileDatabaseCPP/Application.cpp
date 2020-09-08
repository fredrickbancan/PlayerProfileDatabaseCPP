#include "ProfileConsole.h"
#include "DatabaseManager.h"
int main()
{
	DatabaseManager::get()->init();
	ProfileConsole::get()->init();
	ProfileConsole::get()->doUserInput();
	delete DatabaseManager::get();
	delete ProfileConsole::get();
}