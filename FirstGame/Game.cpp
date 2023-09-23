// FirstGame}.cpp : Defines the entry point for the application.
//

#include "Game.hpp"

namespace TestGame {

	Game::Game()
	{
	}

	Game::~Game()
	{
	}

	void Game::Run()
	{
		while (!_window.ShouldWindowClose())
		{
			_window.WindowPollEvents();
		}
	}
}