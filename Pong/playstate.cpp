#include "stdafx.h"
#include "playstate.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <iostream>

#include "statemachine.h"
#include "highscorestate.h"

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

				default:
					break;
			}
			break;

		default:
			break;
		}
	}

	// Gain user input for player movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		player.rotate(Player::ERotation::Left);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		player.rotate(Player::ERotation::Right);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		player.moveForward();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		player.moveBackward();
	}

	// Player shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player.shoot();
	}
}

void PlayState::update()
{
	fader.update();

	bulletPool.update();
	enemyPool.update();
	collissionEngine.update();
	enemySpawner.update();

	player.update();

	if (player.getState() == Entity::EState::Dead)
		nextState = StateMachine::build<HighscoreState>(machine, window, true);
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