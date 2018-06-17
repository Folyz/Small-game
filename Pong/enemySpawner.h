#pragma once

#include <SFML/System/Vector2.hpp>

#include "entityPool.h"
#include "enemy.h"

namespace sf
{
	class RenderWindow;
}

class Player;

class EnemySpawner
{
	private:
		EntityPool<Enemy> &enemies;
		Player &player;

		int spawnSize = 5;
		int const maxEnemies = 30;
		int spawnTimer = 120;
		int const spawnTime = 600;
		float const minSpawnDistance = 250;

		sf::RenderWindow &window;

	public:
		EnemySpawner(sf::RenderWindow &window, EntityPool<Enemy> &enemies, Player &player);

		void spawn(int amount);

		void update();

	private:
		sf::Vector2f getRandomEnemyPosition(float minPlayerDistance);
		float getRandomDirection();
};