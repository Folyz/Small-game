#include "stdafx.h"
#include "playstate.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <iostream>

#include "statemachine.h"
#include "introstate.h"

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
:
	State{ machine, window, replace }
{
	// Initialize fader
	sf::Color targetColor = fader.getColor();
	targetColor.a = 0;
	fader.setTargetColor(targetColor);

	std::cerr << "PlayState initialized..." << std::endl;
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::input()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:						// Quit application
			machine.quit();							
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:			// Quit application
					machine.quit();					
					break;

				case sf::Keyboard::Space:			// Shoot player bullet
					bulletPool.create(player.getPosition(), player.getDirection());
					break;

				default:
					break;
			}
			break;

		default:
			break;
		}
	}

	// Gain user input for player movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.rotate(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.rotate(false);
	}

	player.setSpeed(0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.setSpeed(4);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.setSpeed(-2);
	}

	if (player.getState() == Player::State::dead)
		nextState = StateMachine::build<IntroState>(machine, window, true);
}

void PlayState::update()
{
	fader.update();

	bulletPool.update();
	enemyPool.update();
	collissionEngine.update();
	enemySpawner.update();

	player.update();
}

void PlayState::draw()
{
	window.clear();

	fader.draw();

	bulletPool.draw();
	enemyPool.draw();

	player.draw();

	score.draw();

	window.display();
}