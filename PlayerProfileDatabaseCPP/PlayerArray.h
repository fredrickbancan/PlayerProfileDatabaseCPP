#pragma once
#include "PlayerProfile.h"
/*class for storing arrays of player data and dynamically changing its size.*/
class PlayerArray
{
	//fields
private:
	bool isSorted = false;//true if elements have been sorted
    unsigned int count;//count of elements
	unsigned int size;//size in bytes
	PlayerProfile* elements = nullptr;
public:

	//functions
private:
	/*called to increase count of  elements array. Copies, deletes and reallocates*/
	void growElements(unsigned int additionalCount);

	/*Swaps the two values in the elements array at the two provided indices. Used for sorting.*/
	void swap(unsigned int a, unsigned int b);

public:
	PlayerArray(PlayerProfile* data, unsigned int elementCount);
	~PlayerArray() { delete[] elements; };

	/*adds the provided profile to array*/
	void addProfile(const PlayerProfile& profile);

	/*returns the line number of the found profile (starting from 1). Returns 0 if there is none. Returns -1 if the profile has not been saved to file yet. Uses binary search.*/
	int findProfile(const char* name);

	/*sorts elements by name using bubble sort*/
	void sortAlphabetically();

	/*returns the pointer to array of playerprofiles*/
	PlayerProfile* getElements() const { return elements; }

	/*returns reference to element at provided index*/
	PlayerProfile& elementAt(unsigned int i) const { return elements[i]; };

	/*returns number of elements in array*/
	unsigned int getCount() const { return count; }

	/*returns size of array in bytes*/
	unsigned int getSize() const { return size; }
};