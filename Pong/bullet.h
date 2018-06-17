#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "entity.h"
#include <memory>

class Bullet : public Entity
{
protected:
	// Physics
	float lifeTime;
	float damage;

	// Window
	sf::RenderWindow &window;

public:
	Bullet(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection);

	virtual sf::Shape const &getShape() override = 0;
	virtual float getDamage() = 0;

	virtual void update() override = 0;
	virtual void draw() override = 0;

	template <typename T>
	static std::unique_ptr<T> create(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection);
};

template <typename T>
static std::unique_ptr<T> Bullet::create(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection)
{
	return std::make_unique<T>(window, iniPosition, iniDirection);
}