#include "stdafx.h"
#include "enemy.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

Enemy::Enemy(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection)
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

Enemy::State Enemy::getState()
{
	return state;
}

int Enemy::getWorthPoints()
{
	return worthPoints;
}

sf::CircleShape const &Enemy::getShape()
{
	return shape;
}

sf::Vector2f const &Enemy::getPosition()
{
	return position;
}

float Enemy::getRadius()
{
	return radius;
}

void Enemy::setState(State newState)
{
	state = newState;
}

void Enemy::update()
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

void Enemy::draw()
{
	window.draw(shape);
}