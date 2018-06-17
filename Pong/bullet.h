#pragma once

#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
	class RenderWindow;
}

class Bullet
{
	public:
		enum class State {
			alive,
			dead
		};

	private:
		// Physics
		sf::Vector2f position;
		float const speed = 6.0;
		float direction;

		int lifeTime = 60;

		State state = State::alive;

		// Visual
		float const radius = 2;
		sf::CircleShape shape;

		sf::RenderWindow &window;
		
	public:
		Bullet(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection);

		void setState(State newState);

		State getState();
		sf::CircleShape const &getShape();
		sf::Vector2f const &getPosition();
		float getRadius();

		void update();
		void draw();
};