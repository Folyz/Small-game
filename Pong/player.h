#pragma once

#include <SFML/Graphics/ConvexShape.hpp>

namespace sf
{
	class RenderWindow;
}

class Player
{
	public:
		enum class State {
			alive,
			dead
		};

	private:
		// Physics
		sf::Vector2f position;
		float speed = 0;
		float direction = 90;
		float const rotationSpeed = 5;

		State state = State::alive;

		// Visual
		float const radius = 2;
		sf::ConvexShape shape;

		sf::RenderWindow &window;

	public:
		Player(sf::RenderWindow &window);

		void setState(State newState);
		void setSpeed(float newSpeed);

		sf::ConvexShape const &getShape();
		sf::Vector2f const &getPosition();
		float getDirection();
		float getRadius();
		State getState();

		void rotate(bool rotateLeft);

		void update();
		void draw();
};