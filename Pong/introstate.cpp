#include "stdafx.h"
#include "introstate.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

#include "playstate.h"
#include "statemachine.h"

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
:
	State{ machine, window, replace }
{
	// Set the fader target alpha and start the fader
	sf::Color targetColor = fader.getColor();
	targetColor.a = 255;
	fader.setTargetColor(targetColor);
	fader.setTransitionSteps(30);

	// Load font
	font.loadFromFile("Fonts/CaviarDreams.ttf");

	// Intro title
	title.setFont(font);
	title.setString("Pong");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color{ 255, 255, 255, 0 });

	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - horTextSpacing));

	// Press space text
	pressSpace.setFont(font);
	pressSpace.setString("Press space to start...");
	pressSpace.setCharacterSize(30);
	pressSpace.setFillColor(sf::Color{ 255, 255, 255, 0 });

	sf::FloatRect pressSpaceRect = pressSpace.getLocalBounds();
	pressSpace.setOrigin(pressSpaceRect.left + pressSpaceRect.width / 2.0f, pressSpaceRect.top + pressSpaceRect.height / 2.0f);
	pressSpace.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + horTextSpacing));

	std::cerr << "IntroState initialized..." << std::endl;
}

void IntroState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::input()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			machine.quit();
			break;

		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:				// Start the game (playstate)
				nextState = StateMachine::build<PlayState>(machine, window, true);
				break;

			case sf::Keyboard::Escape:
				machine.quit();						// Quit the game
				break;

			default:
				break;
			}
			break;
		}

		default:
			break;
		}
	}
}

void IntroState::update()
{
	fader.update();

	// Title text
	sf::Color titleColor = title.getFillColor();
	if (titleColor.a < 252)
		titleColor.a += 4;

	title.setFillColor(titleColor);

	// Press space text
	if (titleColor.a >= 252)
	{
		counter++;

		if (counter < 30)
		{
			pressSpace.setFillColor(sf::Color::White);
		}
		else if (counter < 60)
		{
			pressSpace.setFillColor(sf::Color{ 255, 255, 255, 0 });
		}
		else
			counter = 0;
	}
}

void IntroState::draw()
{
	// Clear the previous drawing
	window.clear();

	// Draw fader
	fader.draw();

	// Draw intro text
	window.draw(title);
	window.draw(pressSpace);

	window.display();
}