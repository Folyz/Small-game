#pragma once

#include <SFML/Graphics.hpp>

#include "statemachine.h"
#include "introstate.h"

class Application
{
	private:
		// Game constants
		static const int FPS = 60;
		static const unsigned int screenWidth = 800;
		static const unsigned int screenHeight = 600;

		// RenderWindow
		sf::RenderWindow window;
		StateMachine machine;

	public:
		Application() = default;
		void run();
};