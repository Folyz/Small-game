#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.h"
#include "fader.h"
#include "database.h"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class HighscoreState final : public State
{
	private:
		// Intro text
		const int horTextSpacing = 50;
		sf::Font font;

		const int maxNameLength = 16;

		const int scoreHeadingTextYPos = 150;
		const int scoreTextYPos = 90;
		const int nameHeadingTextYPos = -20;
		const int nameTextYPos = -80;
		const int pressEnterTextYPos = -180;

		sf::Text scoreHeadingText;
		sf::Text scoreText;
		sf::Text nameHeadingText;
		sf::Text nameText;
		sf::Text pressEnterText;

		uint8_t counter = 0;

		// Fader
		Fader fader{ window, sf::Color{ 26, 128, 182, 0 } };

	public:
		HighscoreState(StateMachine& game, sf::RenderWindow& window, bool replace = true);

		void pause();
		void resume();

		void input();
		void update();
		void draw();

	private:
		void initializeText(sf::Text *text, sf::Font const &font, std::string content, int fontSize, int YPos);
};