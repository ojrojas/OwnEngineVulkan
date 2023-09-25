#include "Game.hpp"
#include <iostream>
#include <exception>

int main()
{
	try
	{
		TestGame::Game Game{};

		Game.Run();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}