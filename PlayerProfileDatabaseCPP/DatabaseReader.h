#pragma once
/*static class for reading database*/
class DatabaseReader
{
	//fields
private:
	/*singleton instance*/
	static DatabaseReader* instance;
public:

	//functions
private:
public:
	/*returns singleton instance*/
	static DatabaseReader* get();
};