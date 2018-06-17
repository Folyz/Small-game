#include "stdafx.h"
#include "score.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

Score::Score(sf::RenderWindow &window)
:
	window{ window }
{
	// Load font
	scoreFont.loadFromFile("Fonts/AldotheApache.ttf");

	// Set text
	scoreText.setFont(scoreFont);
	scoreText.setString("Score " + std::to_string(score));
	scoreText.setCharacterSize(textSize);
	scoreText.setFillColor(scoreColor);
	scoreText.setPosition(textPosition);
}

void Score::add(int amount)
{
	score += amount;
	scoreText.setString("Score " + std::to_string(score));
}

void Score::draw()
{
	window.draw(scoreText);
}