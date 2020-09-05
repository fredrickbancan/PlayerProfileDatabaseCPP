#include "PlayerArray.h"
#include <string>
PlayerArray::PlayerArray(PlayerProfile* data, unsigned int elementCount) : elements(data), count(elementCount)
{
	size = sizeof(PlayerProfile) * elementCount;
}

void PlayerArray::sortAlphabetically()
{
	if (isSorted || count < 2)//no need to sort if elements are previously sorted or if there are less than 2 elements
	{
		return;
	}

	//bubble sort here using std string
	std::string leftName;
	std::string rightName;
	bool moreSortingNeeded = true;
	bool passMadeChanges = false;//gets set to true if a sort pass makes any changes
	 
	do
	{
		passMadeChanges = false;
		for (unsigned int i = 0; i < count - 1; i++)
		{
			leftName = elements[i].name;
			rightName = elements[i + 1].name;

			if (leftName > rightName)//if the left name is higher on the alphabet than right name
			{
				swap(i, i + 1);//swap values
				passMadeChanges = true;
			}
		}

		//If the pass made any changes, then it needs to be ran again. 
		//otherwise if the previous pass made no changes then the sorting is finished.
		moreSortingNeeded = passMadeChanges;
	} 
	while (moreSortingNeeded);

	isSorted = true;//do last
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

void PlayerArray::swap(unsigned int a, unsigned int b)
{
	PlayerProfile temp;

	if (a > count || b > count || a == b)return;//skip swap if out of range or if the indices are the same
	
	/*swap*/
	temp = elements[a];
	elements[a] = elements[b];
	elements[b] = temp;
}

bool PlayerArray::binarySearchByNameRecursive(const char* name, unsigned int left, unsigned int right, unsigned int& resultIndex)
{
	if (left >= right || right > count)
	{
		return false;
	}

	unsigned int midPoint = (left + right) / 2;
	if (std::string(elements[midPoint].name) == std::string(name))
	{
		resultIndex = midPoint;
		return true;
	}

	bool greater = std::string(name) > std::string(elements[midPoint].name);

	if (greater)
	{
		return binarySearchByNameRecursive(name, midPoint +1, right, resultIndex);
	}
	return binarySearchByNameRecursive(name, left, midPoint - 1, resultIndex);
}

bool PlayerArray::findProfile(const char* name, PlayerProfile*& result)
{
	sortAlphabetically();
	unsigned int resultIndex = 0;

	if (binarySearchByNameRecursive(name, 0, count-1, resultIndex))
	{
		result = &(elements[resultIndex]);
		return true;
	}

	return false;
}

void PlayerArray::addProfile(const PlayerProfile& profile)
{
	PlayerProfile* searchResult = nullptr;
	if (findProfile(profile.name, searchResult))//check to see if profile is already in elements
	{
		if (searchResult != nullptr)
		{
			(*searchResult) = profile;//replace existing profile
		}
	}
	else
	{
		growElements(1);
		elements[count - 1] = profile;
	}

	isSorted = false;//do last
}

