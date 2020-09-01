#include "DatabaseReader.h"

DatabaseReader* DatabaseReader::instance = nullptr;
DatabaseReader* DatabaseReader::get()
{
	if (instance == nullptr)
	{
		instance = new DatabaseReader();
	}
	return instance;
}