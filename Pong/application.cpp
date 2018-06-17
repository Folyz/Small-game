#include "stdafx.h"
#include "application.h"

#include "highscorestate.h"

#include <iostream>

void Application::run()
{
	std::cerr << "Start" << std::endl;

	// Create render window
	window.create(sf::VideoMode{ screenWidth, screenHeight}, "Space invaders", sf::Style::Close);
	window.setFramerateLimit(FPS);

	// Initialize the engine
	machine.run(StateMachine::build<IntroState>(machine, window, true));

	// Application loop
	while (machine.running())
	{
		machine.nextState();
		machine.input();
		machine.update();
		machine.draw();
	}
}