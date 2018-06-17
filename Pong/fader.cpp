#include "stdafx.h"
#include "fader.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

#include <stdexcept>
#include <stdlib.h>
#include <math.h>

Fader::Fader(sf::RenderWindow &window, sf::Color const &iniColor)
:
	window{ window },
	currentRed(iniColor.r),
	currentGreen(iniColor.g),
	currentBlue(iniColor.b),
	currentAlpha(iniColor.a),
	targetRed(iniColor.r),
	targetGreen(iniColor.g),
	targetBlue(iniColor.b),
	targetAlpha(iniColor.a)
{
	background.setFillColor(iniColor);
	background.setSize(static_cast<sf::Vector2f>(window.getSize()));
}

void Fader::setTargetColor(sf::Color const &color) 
{
	targetRed = color.r;
	targetGreen = color.g;
	targetBlue = color.b;
	targetAlpha = color.a;

	transitionSpeedRed = (targetRed - currentRed) / transitionSteps;
	transitionSpeedGreen = (targetGreen - currentGreen) / transitionSteps;
	transitionSpeedBlue = (targetBlue - currentBlue) / transitionSteps;
	transitionSpeedAlpha = (targetAlpha - currentAlpha) / transitionSteps;

	doingTransition = true;
}

void Fader::setTransitionSteps(int steps) 
{
	if (steps <= 0)
		throw std::out_of_range("Fader transition steps must be larger than 0");
	else
		transitionSteps = steps;
}

bool Fader::getDoingTransition() 
{
	return doingTransition;
}

sf::Color Fader::getColor() 
{
	return background.getFillColor();
}

void Fader::update() 
{
	if (doingTransition) 
	{
		bool targetReached = (abs(currentRed - targetRed) - 0.0001 <= abs(transitionSpeedRed)) &&
							 (abs(currentGreen - targetGreen) - 0.0001 <= abs(transitionSpeedGreen)) &&
							 (abs(currentBlue - targetBlue) - 0.0001 <= abs(transitionSpeedBlue)) &&
							 (abs(currentAlpha - targetAlpha) - 0.0001 <= abs(transitionSpeedAlpha));

		if (targetReached)									// Stop transition if target is reached
			doingTransition = false;
		else 
		{													// Update the color if target not yet reached
			currentRed += transitionSpeedRed;
			currentGreen += transitionSpeedGreen;
			currentBlue += transitionSpeedBlue;
			currentAlpha += transitionSpeedAlpha;

			sf::Color faderColor;
			faderColor.r = static_cast<int>(std::round(currentRed));
			faderColor.g = static_cast<int>(std::round(currentGreen));
			faderColor.b = static_cast<int>(std::round(currentBlue));
			faderColor.a = static_cast<int>(std::round(currentAlpha));

			background.setFillColor(faderColor);
		}	
	}
}

void Fader::draw() 
{
	window.draw(background);
}