#include <iostream>
#include "Game.h"

int main()
{
	try
	{
		Game(1344, 768, "Arkanoid");
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}