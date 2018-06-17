#include "stdafx.h"
#include "player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <math.h>

#define PI 3.14159265

Player::Player(sf::RenderWindow &window)
:
	window{ window }
{
	// Construct the player shape
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(0, 10));
	shape.setPoint(2, sf::Vector2f(25, 5));
	shape.setOutlineColor(sf::Color::White);

	sf::FloatRect shapeRect = shape.getLocalBounds();
	shape.setOrigin(shapeRect.left + shapeRect.width / 2.0f, shapeRect.top + shapeRect.height / 2.0f);

	// Start position
	position.x = window.getSize().x / 2.0f;
	position.y = window.getSize().y / 2.0f;
	shape.setPosition(position);
}

sf::ConvexShape const &Player::getShape()
{
	return shape;
}

float Player::getRadius()
{
	return radius;
}

Player::State Player::getState()
{
	return state;
}

void Player::update()
{
	// Position
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);

	// Window boundary
	if (position.x < 0)
		position.x = 0;

	if (position.y < 0)
		position.y = 0;

	if (position.x > window.getSize().x)
		position.x = window.getSize().x;

	if (position.y > window.getSize().y)
		position.y = window.getSize().y;

	shape.setPosition(position);
	shape.setRotation(direction);
}

void Player::draw()
{
	window.draw(shape);
}

void Player::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Player::setState(State newState)
{
	state = newState;
}

void Player::rotate(bool rotateLeft)
{
	if (rotateLeft)
		direction -= rotationSpeed;
	else
		direction += rotationSpeed;
}

sf::Vector2f const &Player::getPosition()
{
	return position;
}

float Player::getDirection()
{
	return direction;
}