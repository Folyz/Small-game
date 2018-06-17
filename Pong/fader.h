#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
	class RenderWindow;
}

class Fader
{
	private:
		sf::RenderWindow &window;
		sf::RectangleShape background;

		// Current color of the fader
		float currentRed;
		float currentGreen;
		float currentBlue;
		float currentAlpha;

		// Target color of the fader
		float targetRed;
		float targetGreen;
		float targetBlue;
		float targetAlpha;

		// Transition speed variables used to go from current to target color
		float transitionSpeedRed = 0;
		float transitionSpeedGreen = 0;
		float transitionSpeedBlue = 0;
		float transitionSpeedAlpha = 0;

		// How many steps to go to next color
		int transitionSteps = 60;

		// Is the fader currently doing a transition
		bool doingTransition = false;

	public:
		Fader(sf::RenderWindow &window, sf::Color const &iniColor);

		void setTargetColor(sf::Color const &targetColor);
		void setTransitionSteps(int steps);

		bool getDoingTransition();
		sf::Color getColor();

		void update();
		void draw();
};