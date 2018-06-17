#include "stdafx.h"
/*#include "rotator.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

Rotator::Rotator(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection)
:
	window{ window },
	position{ iniPosition },
	direction{ iniDirection },
	shape{ radius, vertices }
{
	shape.setFillColor(color);
	shape.setOrigin(radius, radius);
	shape.setPosition(position);
}

Rotator::State Rotator::getState()
{
	return state;
}

int Rotator::getWorthPoints()
{
	return worthPoints;
}

sf::CircleShape const &Rotator::getShape()
{
	return shape;
}

sf::Vector2f const &Rotator::getPosition()
{
	return position;
}

float Rotator::getRadius()
{
	return radius;
}

void Rotator::setState(State newState)
{
	state = newState;
}

void Rotator::update()
{
	// Animation
	angle += animationSpeed;
	angle = fmod(angle, 360);
	shape.setRotation(angle);

	// Position
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);
	shape.setPosition(position);

	// Screen collission
	if (position.x - radius < 0)
	{
		position.x = radius;
		direction += fmod(180 - 2 * direction, 360);
	}
	else if (position.x + radius > window.getSize().x)
	{
		position.x = window.getSize().x - radius;
		direction += fmod(180 - 2 * direction, 360);
	}

	if (position.y - radius < 0)
	{
		position.y = radius;
		direction += fmod(-2 * direction, 360);		
	}
	else if (position.y + radius > window.getSize().y)
	{
		position.y = window.getSize().y - radius;
		direction += fmod(-2 * direction, 360);
	}
}

void Rotator::draw()
{
	window.draw(shape);
}*/