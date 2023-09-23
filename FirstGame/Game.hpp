// FirstGame.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "../OwnEngine/Window.hpp"
#include "../OwnEngine/Device.hpp"

namespace TestGame {

	class Game {
	public:
		Game();
		~Game();
		void Run();
	private:
		OwnEngine::Window _window{ 1024,768,"FirstGame" };
		OwnEngine::Device _device{ 
			_window, 
			"FirstGame", 
			OwnEngine::MakeVersion{1,0,0}, 
			"OwnEngine", OwnEngine::MakeVersion{1,0,0} 
		};
	};
}



// TODO: Reference additional headers your program requires here.
