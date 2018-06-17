#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include "entity.h"
#include "entityPool.h"
#include "gun.h"

namespace sf
{
	class RenderWindow;
}

class Bullet;

class Player : public Entity
{
public:
	enum class ERotation
	{
		Left,
		Right
	};

private:
	// Physics
	int const INITIAL_DIRECTION = 90;
	float const INITIAL_RADIUS = 2;
	float const INITIAL_SPEED = 0;

	float const ROTATION_SPEED = 5;

	// Gun
	std::unique_ptr<Gun> gun;
	
	// Visual
	sf::ConvexShape shape;

	// Other
	sf::RenderWindow &window;

public:
	Player(sf::RenderWindow &window, EntityPool<Bullet> &bulletPool);

	sf::Shape const &getShape() override;

	void moveForward();
	void moveBackward();

	void rotate(ERotation rotation);

	void shoot();

	void update() override;
	void draw() override;
};