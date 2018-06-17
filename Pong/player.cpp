#include "stdafx.h"
#include "player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include "standardGun.h"
#include "growGun.h"
#include "gun.h"
#include <math.h>

#define PI 3.14159265

Player::Player(sf::RenderWindow &window, EntityPool<Bullet> &bulletPool)
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

	radius = INITIAL_RADIUS;

	// Attributes
	gun = Gun::create<GrowGun>(window, *this, bulletPool);

	// Start position and physics
	position.x = window.getSize().x / 2.0f;
	position.y = window.getSize().y / 2.0f;
	shape.setPosition(position);

	speed = INITIAL_SPEED;
	direction = INITIAL_DIRECTION;
}

sf::Shape const &Player::getShape()
{
	return shape;
}

void Player::moveForward()
{
	speed += 4;
}

void Player::moveBackward()
{
	speed -= 2;
}

void Player::update()
{
	// Position
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);

	speed = 0;

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

	// Gun
	gun->update();
}

void Player::draw()
{
	window.draw(shape);
}

void Player::shoot()
{
	gun->shoot();
}

void Player::rotate(ERotation rotation)
{
	if (rotation == ERotation::Left)
		direction -= ROTATION_SPEED;
	else
		direction += ROTATION_SPEED;
}