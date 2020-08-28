#pragma once

/*Singleton abstraction of the console for user input and reading player profiles*/
class ProfileConsole
{
	//fields
private:
	static ProfileConsole* instance;
public:
	//functions
private:
public:
	/*Function for getting a pointer to the singleton instance of profileconsole*/
	static ProfileConsole* get();

	/*Opens the console to screen, and asks for user input.*/
	void open();
};