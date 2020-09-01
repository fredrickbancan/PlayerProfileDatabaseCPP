#include "ProfileConsole.h"

ProfileConsole* ProfileConsole::instance = nullptr;
ProfileConsole* ProfileConsole::get()
{
	if (instance == nullptr)
	{
		instance = new ProfileConsole();
	}
	return instance;
}

void ProfileConsole::open()
{
	std::cout << "Hello World!" << std::endl;
	system("PAUSE");
}