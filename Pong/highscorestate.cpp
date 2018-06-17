#include "stdafx.h"
#include "highscorestate.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>

#include "introstate.h"
#include "statemachine.h"

HighscoreState::HighscoreState(StateMachine& machine, sf::RenderWindow& window, bool replace)
:
	State{ machine, window, replace }
{
	// Load font
	font.loadFromFile("Fonts/CaviarDreams.ttf");

	// Score heading text
	scoreHeadingText.setFont(font);
	scoreHeadingText.setString("Your score is");
	scoreHeadingText.setCharacterSize(40);
	scoreHeadingText.setFillColor(sf::Color::White);

	sf::FloatRect scoreHeadingTextRect = scoreHeadingText.getLocalBounds();
	scoreHeadingText.setOrigin(scoreHeadingTextRect.left + scoreHeadingTextRect.width / 2.0f, scoreHeadingTextRect.top + scoreHeadingTextRect.height / 2.0f);
	scoreHeadingText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - scoreHeadingTextYPos));

	// Score text
	scoreText.setFont(font);
	scoreText.setString("500");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);

	sf::FloatRect scoreTextRect = scoreText.getLocalBounds();
	scoreText.setOrigin(scoreTextRect.left + scoreTextRect.width / 2.0f, scoreTextRect.top + scoreTextRect.height / 2.0f);
	scoreText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - scoreTextYPos));

	// Name heading text
	nameHeadingText.setFont(font);
	nameHeadingText.setString("Enter your name");
	nameHeadingText.setCharacterSize(40);
	nameHeadingText.setFillColor(sf::Color::White);

	sf::FloatRect nameHeadingTextRect = nameHeadingText.getLocalBounds();
	nameHeadingText.setOrigin(nameHeadingTextRect.left + nameHeadingTextRect.width / 2.0f, nameHeadingTextRect.top + nameHeadingTextRect.height / 2.0f);
	nameHeadingText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - nameHeadingTextYPos));

	// Name text
	nameText.setFont(font);
	nameText.setString("o");
	nameText.setCharacterSize(50);
	nameText.setFillColor(sf::Color::White);
	nameText.setStyle(sf::Text::Bold);
	
	sf::FloatRect nameTextRect = nameText.getLocalBounds();
	nameText.setOrigin(nameTextRect.left + nameTextRect.width / 2.0f, nameTextRect.top + nameTextRect.height / 2.0f);
	nameText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - nameTextYPos));

	nameText.setString("");

	// Press enter text
	pressEnterText.setFont(font);
	pressEnterText.setString("Press enter to submit...");
	pressEnterText.setCharacterSize(30);
	pressEnterText.setFillColor(sf::Color::White);

	sf::FloatRect pressEnterTextRect = pressEnterText.getLocalBounds();
	pressEnterText.setOrigin(pressEnterTextRect.left + pressEnterTextRect.width / 2.0f, pressEnterTextRect.top + pressEnterTextRect.height / 2.0f);
	pressEnterText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - pressEnterTextYPos));

	std::cerr << "HighscoreState initialized..." << std::endl;
}

void HighscoreState::initializeText(sf::Text *text, sf::Font const &font, std::string content, int fontSize, int YPos)
{
	text->setFont(font);
	text->setString(content);
	text->setCharacterSize(fontSize);
	text->setFillColor(sf::Color::White);

	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text->setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - YPos));
}

void HighscoreState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void HighscoreState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void HighscoreState::input()
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
			case sf::Keyboard::Enter:				// Start the game (playstate)
				nextState = StateMachine::build<IntroState>(machine, window, true);
				break;

			case sf::Keyboard::Escape:
				machine.quit();						// Quit the game
				break;

			default:
				break;
			}
			break;
		}

		case (sf::Event::TextEntered):
			// Only allow letters and numbers, lets not get ourselfs an SQL injection...
			if (event.text.unicode > 47 && event.text.unicode < 58 ||
				event.text.unicode > 64 && event.text.unicode < 91 ||
				event.text.unicode > 96 && event.text.unicode < 123)		// Add character to the name
			{
				std::string newNameText = nameText.getString();
				if (newNameText.length() < maxNameLength)
				{
					newNameText += static_cast<char>(event.text.unicode);
					nameText.setString(newNameText);

					sf::FloatRect nameTextRect = nameText.getLocalBounds();
					sf::Vector2f currentOrigin = nameText.getOrigin();
					nameText.setOrigin(nameTextRect.left + nameTextRect.width / 2.0f, currentOrigin.y);
					
					sf::Vector2f currentPos = nameText.getPosition();
					nameText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, currentPos.y));
				}
			}
			else if (event.text.unicode == '\b')	// Backspace to remove character
			{
				std::string newNameText = nameText.getString();
				if (newNameText.length() > 0)
				{
					newNameText.pop_back();
					nameText.setString(newNameText);

					sf::FloatRect nameTextRect = nameText.getLocalBounds();
					sf::Vector2f currentOrigin = nameText.getOrigin();
					nameText.setOrigin(nameTextRect.left + nameTextRect.width / 2.0f, currentOrigin.y);
					
					sf::Vector2f currentPos = nameText.getPosition();
					nameText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, currentPos.y));
				}
			}
			break;

		default:
			break;
		}
	}
}

void HighscoreState::update()
{
	fader.update();

	// Press space text
	if (counter++ < 40)
		pressEnterText.setFillColor(sf::Color::White);
	else if (counter < 80)
		pressEnterText.setFillColor(sf::Color{ 255, 255, 255, 0 });
	else
		counter = 0;
}

void HighscoreState::draw()
{
	// Clear the previous drawing
	window.clear();

	// Draw all text
	window.draw(scoreHeadingText);
	window.draw(scoreText);
	window.draw(nameHeadingText);
	window.draw(nameText);
	window.draw(pressEnterText);

	// Display
	window.display();
}