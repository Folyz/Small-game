#pragma once
#include "bullet.h"

class GrowBullet final : public Bullet
{
private:
	// Properties
	float const INITIAL_DAMAGE = 10;
	float const INITIAL_LIFETIME = 40;
	float const INITIAL_RADIUS = 3;
	float const INITIAL_SPEED = 6;

	float const FINAL_DAMAGE = 10;
	float const FINAL_RADIUS = 15;

	// Visual
	sf::CircleShape shape;

public:
	GrowBullet(sf::RenderWindow &window, sf::Vector2f iniPosition, float iniDirection);

	float getDamage() override;
	sf::Shape const &getShape() override;

	void update() override;
	void draw() override;
};