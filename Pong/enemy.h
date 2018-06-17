#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "entity.h"

namespace sf
{
	class RenderWindow;
}

class Enemy : public Entity
{
	// Shape
	float const INITIAL_SPEED = 2;
	float const INITIAL_RADIUS = 15;
	size_t const VERTICES = 5;

	// Visual
	float angle = 0;
	float animationSpeed = 3;
	sf::Color color = sf::Color::White;
	sf::CircleShape shape;

	// Other
	int const POINTS_WORTH = 100;

	sf::RenderWindow &window;

public:
	Enemy(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection);

	sf::Shape const &getShape() override;
	int getWorthPoints();

	void update() override;
	void draw() override;
};