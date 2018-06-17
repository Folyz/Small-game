#pragma once

#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
	class RenderWindow;
}

class Enemy
{
public:
	enum class State {
		alive,
		dead
	};

private:
	// Physics
	sf::Vector2f position;
	float speed = 2;
	float direction;

	State state = State::alive;

	// Visual
	float angle = 0;
	float animationSpeed = 3;
	size_t const vertices = 5;
	float const radius = 15;
	sf::Color color = sf::Color::White;
	sf::CircleShape shape;

	// Other
	int const worthPoints = 100;

	sf::RenderWindow &window;

public:
	Enemy(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection);

	void setState(State newState);

	State getState();
	sf::CircleShape const &getShape();
	sf::Vector2f const &getPosition();
	float getRadius();
	int getWorthPoints();

	void update();
	void draw();
};