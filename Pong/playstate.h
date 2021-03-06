#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.h"
#include "fader.h"
#include "score.h"
#include "player.h"
#include "collissionEngine.h"
#include "enemySpawner.h"
#include "entityPool.h"
#include "database.h"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PlayState final : public State
{
	private:
		// Texts and fonts
		sf::Font font;
		sf::Text title;
		sf::Text pressSpace;
		Fader fader{ window, sf::Color{ 26, 128, 182, 252 } };

		// Score
		Score score{ window };

		// Database for highscores
		Database dbHighscores;

		// Entity handlers
		EntityPool<Bullet> bulletPool{ window };
		EntityPool<Enemy> enemyPool{ window };

		// Entities
		Player player{ window , bulletPool };

		EnemySpawner enemySpawner{ window, enemyPool, player };
		CollissionEngine collissionEngine{ bulletPool, enemyPool, score, player, dbHighscores};

	public:
		PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

		void pause();
		void resume();

		void input();
		void update();
		void draw();
};