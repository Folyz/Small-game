#include "stdafx.h"
#include "standardBullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <math.h>

#define PI 3.14159265

StandardBullet::StandardBullet(sf::RenderWindow &window, sf::Vector2f iniPosition, float iniDirection)
:
	Bullet{ window, iniPosition, iniDirection }
{
	// Initialize physics
	damage = INITIAL_DAMAGE;
	lifeTime = INITIAL_LIFETIME;
	radius = INITIAL_RADIUS;
	speed = INITIAL_SPEED;

	// Initialize shape
	shape.setRadius(radius);
	shape.setOutlineColor(sf::Color::White);
	shape.setOrigin(radius / 2.0f, radius / 2.0f);
	shape.setPosition(position);
}

float StandardBullet::getDamage()
{
	return damage;
}

sf::Shape const &StandardBullet::getShape()
{
	return shape;
}

void StandardBullet::update()
{
	// Position
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);

	shape.setPosition(position);

	// Lifetime
	if (lifeTime-- == 0)
		state = EState::Dead;
}

void StandardBullet::draw()
{
	window.draw(shape);
}