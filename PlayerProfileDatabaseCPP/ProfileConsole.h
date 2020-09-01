#pragma once
#include "Windows.h"
#include <iostream>

/*an enum class for chosing console colours*/
enum class ConsoleColor
{
	BLACK = 128,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	DARKMAGENTA = 5,
	GOLD = 6,
	LIGHTGREY = 7,
	GREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	PINK = 12,
	MAGENTA = 13,
	LIGHTYELLOW = 14,
	WHITE = 15,
};

/*Singleton abstraction of the console for user input and reading player profiles*/
class ProfileConsole
{
	//fields
private:
	/*singleton instance*/
	static ProfileConsole* instance;
public:
	static const ConsoleColor defaultConsoleColor = ConsoleColor::BLACK;
	//functions
private:
public:

	/*Function for getting a pointer to the singleton instance of profileconsole*/
	static ProfileConsole* get();

	/*Opens the console to screen, and asks for user input.*/
	void open();

	/*Can be called to announce a string into console using the console default text color*/
	static void announce(const char* input)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)defaultConsoleColor);
		std::cout << input;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)ConsoleColor::WHITE);
		std::cout << std::endl;
	}

	/*Can be called to print an error to console.*/
	static void error(const char* input)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)ConsoleColor::RED);
		std::cout << "ERROR: " << input;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)ConsoleColor::WHITE);
		std::cout << std::endl;
	}

	/*can be called to pause the console prompt, asks the current user to press enter to continue.*/
	static void pausePrompt()
	{
		std::cout << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)defaultConsoleColor);
		system("PAUSE");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)ConsoleColor::WHITE);
		std::cout << std::endl;
	}
};