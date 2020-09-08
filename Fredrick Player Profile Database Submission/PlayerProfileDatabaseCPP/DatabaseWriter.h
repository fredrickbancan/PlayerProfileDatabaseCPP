#pragma once
/*static class for writing to database*/
class DatabaseWriter
{
	//fields
private:
	/*singleton instance*/
	static DatabaseWriter* instance;
public:

	//functions
private:
public:
	/*returns singleton instance*/
	static DatabaseWriter* get();
	/*writes the provided player profile data to database.*/
	void writePlayerProfileToDatabase(const struct PlayerProfile& player);
};