#include <fstream>
#include "PlayerProfile.h"
#include "DatabaseWriter.h"
#include "ProfileConsole.h"

DatabaseWriter* DatabaseWriter::instance = nullptr;
DatabaseWriter* DatabaseWriter::get()
{
	if (instance == nullptr)
	{
		instance = new DatabaseWriter();
	}
	return instance;
}

void DatabaseWriter::writePlayerProfileToDatabase(const PlayerProfile& player)
{

}
