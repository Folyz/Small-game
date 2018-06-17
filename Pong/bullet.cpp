#include "stdafx.h"
#include "bullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <math.h>

#define PI 3.14159265

Bullet::Bullet(sf::RenderWindow &window, sf::Vector2f &position, float direction)
:
	window{ window },
	position{ position },
	direction{ direction }
{
	shape.setRadius(2);
	shape.setOutlineColor(sf::Color::White);
	shape.setOrigin(radius / 2.0f, radius / 2.0f);

	// Spawn bullet in front of the player
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);

	shape.setPosition(position);
}

sf::CircleShape const &Bullet::getShape()
{
	return shape;
}

Bullet::State Bullet::getState()
{
	return state;
}

void Bullet::setState(State newState) 
{
	state = newState;
}

sf::Vector2f const &Bullet::getPosition() 
{
	return position;
}

float Bullet::getRadius() 
{
	return radius;
}

void Bullet::update()
{
	// Position
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);

	shape.setPosition(position);

	// Lifetime
	if (lifeTime-- == 0)
		state = State::dead;
}

void Bullet::draw()
{
	window.draw(shape);
}