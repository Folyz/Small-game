#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "bullet.h"

class StandardBullet : public Bullet
{
private:
	// Properties
	float const INITIAL_DAMAGE = 10;
	float const INITIAL_LIFETIME = 60;
	float const INITIAL_RADIUS = 2;
	float const INITIAL_SPEED = 6;
	
	// Visual
	sf::CircleShape shape;

public:
	StandardBullet(sf::RenderWindow &window, sf::Vector2f iniPosition, float iniDirection);

	float getDamage() override;
	sf::Shape const &getShape() override;
	
	void update() override;
	void draw() override;
};