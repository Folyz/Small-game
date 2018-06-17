#include "stdafx.h"
#include "application.h"

void Application::run()
{
	// Create render window
	window.create(sf::VideoMode{ screenWidth, screenHeight}, "Pong", sf::Style::Close);
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