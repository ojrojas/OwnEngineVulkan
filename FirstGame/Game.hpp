﻿// FirstGame.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "../OwnEngine/Window.hpp"
#include "../OwnEngine/Device.hpp"
#include "../OwnEngine/SwapChain.hpp"

namespace TestGame {

	class Game {
	public:
		Game();
		~Game();
		void Run();
	private:

		VkExtent2D _windowExtent;

		OwnEngine::Window _window{ 1024,768,"FirstGame" };
		OwnEngine::Device _device{
			_window,
			"FirstGame",
			OwnEngine::MakeVersion{1,0,0},
			"OwnEngine", OwnEngine::MakeVersion{1,0,0}
		};

		OwnEngine::SwapChain _swapChain{ _device, _windowExtent };
	};
}

// TODO: Reference additional headers your program requires here.
