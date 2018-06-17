#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderWindow;
	class Shape;
}

class Entity
{
public:
	enum class EState {
		Alive,
		Dead
	};

protected:
	// Physics
	sf::Vector2f position;
	float speed;
	float direction;

	// State
	EState state = EState::Alive;

	// Visual
	float radius;

public:
	void die();

	float getDirection();
	sf::Vector2f const &getPosition();
	float getRadius();
	virtual sf::Shape const &getShape() = 0;
	EState getState();

	virtual void update() = 0;
	virtual void draw() = 0;
};