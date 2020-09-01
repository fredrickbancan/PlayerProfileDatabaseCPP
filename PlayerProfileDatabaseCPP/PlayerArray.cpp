#include "PlayerArray.h"

PlayerArray::PlayerArray(PlayerProfile* data, unsigned int elementCount) : elements(data), count(elementCount)
{
	size = sizeof(PlayerProfile) * elementCount;
}

void PlayerArray::sortAlphabetically()
{
	if (!isSorted)
	{
		//TODO: impliment
		//bubble sort here using std string

		isSorted = true;//do last
	}
}

void PlayerArray::growElements(unsigned int additionalCount)
{
	PlayerProfile* newArray = new PlayerProfile[count + additionalCount];//creating new array increased by size

	for (unsigned int i = 0; i < count; i++)//copying elements to new array
	{
		newArray[i] = elements[i];
	}

	delete[] elements;
	elements = newArray;
	count += additionalCount;
	size = count * sizeof(PlayerProfile);
	
}

void PlayerArray::addProfile(const PlayerProfile profile)
{
	growElements(1);
	elements[count - 1] = profile;
	isSorted = false;
}

int PlayerArray::findProfile(const char* name)
{
	sortAlphabetically();
	//TODO: impliment
	//do binary search here

	return false;
}
