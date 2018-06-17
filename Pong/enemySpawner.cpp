#include "stdafx.h"
#include "enemySpawner.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <stdlib.h>
#include <iostream>

#include "player.h"

EnemySpawner::EnemySpawner(sf::RenderWindow &window, EntityPool<Enemy> &enemies, Player &player)
:
	window{ window },
	enemies{ enemies },
	player{ player }
{ }

void EnemySpawner::spawn(int amount)
{
	for (int idx = amount; idx > 0; --idx)
		if (enemies.getAmount() < maxEnemies)
			enemies.create(getRandomEnemyPosition(minSpawnDistance), getRandomDirection());
		else
			break;
}

sf::Vector2f EnemySpawner::getRandomEnemyPosition(float minPlayerDistance)
{
	float sqrDistance = 0;
	sf::Vector2f position;
	sf::Vector2f playerPos = player.getPosition();
	
	while (sqrDistance < minSpawnDistance * minSpawnDistance)
	{
		position.x = rand() % window.getSize().x;
		position.y = rand() % window.getSize().y;
		
		sqrDistance = (playerPos.x - position.x) * (playerPos.x - position.x) + (playerPos.y - position.y) * (playerPos.y - position.y);
	}

	return position;
}

float EnemySpawner::getRandomDirection()
{
	return rand() % 360;
}

void EnemySpawner::update()
{
	if (--spawnTimer <= 0)
	{
		spawn(spawnSize);
		spawnTimer = spawnTime;
		std::cerr << "Spawn!" << std::endl;
	}
}