#include <iostream>
#include "Game.h"
#include "Definitions.h"


int main()
{
	try
	{
		Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid");
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}