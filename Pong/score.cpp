#include "stdafx.h"
#include "score.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <iostream>

Score::Score(sf::RenderWindow &window)
:
	window{ window }
{
	// Load font
	if (!scoreFont.loadFromFile("Fonts/AldotheApache.ttf"))
		std::cerr << "Error: could not load font AldotheApache.ttf" << std::endl;

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

int Score::getValue()
{
	return score;
}