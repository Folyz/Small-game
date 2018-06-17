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

class IntroState final : public State
{
	private:
		// Intro text
		const int horTextSpacing = 50;
		sf::Font font;
		sf::Text title;
		sf::Text pressSpace;

		uint8_t counter = 0;

		// Fader
		Fader fader{ window, sf::Color{ 26, 128, 182, 0 } };

	public:
		IntroState(StateMachine& game, sf::RenderWindow& window, bool replace = true);

		void pause();
		void resume();

		void input();
		void update();
		void draw();
};