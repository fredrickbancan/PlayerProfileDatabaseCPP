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

	/*Binary searches for profile by name in elements. Returns true if there is a profile with the provided name, else returns false.*/
	/*resultIndex will be assigned the index of the profile found in elements array. This index can be used to then access that profile.*/
	/*Params: name, left most index of range, right most index of range, result index of found profile.*/
	bool binarySearchByNameRecursive(const char* name, unsigned int left, unsigned int right, unsigned int& resultIndex);

public:
	PlayerArray(PlayerProfile* data, unsigned int elementCount);
	~PlayerArray() { delete[] elements; };

	/*adds the provided profile to array*/
	void addProfile(const PlayerProfile& profile);

	/*returns true if a profile with the provided name is in the array and assigns result with that profile.*/
	bool findProfile(const char* name, PlayerProfile*& result);

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