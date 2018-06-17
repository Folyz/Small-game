#include "stdafx.h"
#include "growBullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <math.h>

#define PI 3.14159265

GrowBullet::GrowBullet(sf::RenderWindow &window, sf::Vector2f iniPosition, float iniDirection)
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

float GrowBullet::getDamage()
{
	return damage;
}

sf::Shape const &GrowBullet::getShape()
{
	return shape;
}

void GrowBullet::update()
{
	// Position
	position.x += speed * cos(direction * PI / 180);
	position.y += speed * sin(direction * PI / 180);

	// Physics
	float lifeTimeRatio = (INITIAL_LIFETIME - lifeTime) / INITIAL_LIFETIME;
	damage = INITIAL_DAMAGE + (FINAL_DAMAGE - INITIAL_DAMAGE) * lifeTimeRatio;
	radius = INITIAL_RADIUS + (FINAL_RADIUS - INITIAL_RADIUS) * lifeTimeRatio;

	// Update shape
	shape.setPosition(position);
	shape.setRadius(radius);

	// Lifetime
	if (lifeTime-- == 0)
		state = EState::Dead;
}

void GrowBullet::draw()
{
	window.draw(shape);
}