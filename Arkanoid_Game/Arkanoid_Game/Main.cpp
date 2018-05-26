#include <iostream>
#include "Game.h"

int main()
{
	try
	{
		Game(800, 600, "Hello");  // won't run without any initial state
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}