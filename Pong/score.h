#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
	class RenderWindow;
}

class Score
{
	private:
		int score = 0;

		sf::Vector2f const textPosition = { 20, 15 };
		int const textSize = 30;
		sf::Font scoreFont;
		sf::Text scoreText;
		sf::Color scoreColor = sf::Color::White;

		sf::RenderWindow &window;

	public:
		Score(sf::RenderWindow& window);

		void add(int amount);

		void draw();
};