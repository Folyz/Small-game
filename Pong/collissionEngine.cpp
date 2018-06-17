#include "stdafx.h"
#include "collissionEngine.h"

#include <iostream>

#include "score.h"
#include "player.h"
#include "entityPool.h"
#include "database.h"

CollissionEngine::CollissionEngine(EntityPool<Bullet> &bullets, EntityPool<Enemy> &enemies, Score &score, Player &player, Database &dbHighscores)
:
	bullets{ bullets },
	enemies{ enemies },
	score{ score },
	player{ player },
	dbHighscores{ dbHighscores }
{ }

bool CollissionEngine::checkCollission(std::unique_ptr<Bullet> &bullet, std::unique_ptr<Enemy> &enemy)
{
	// Detect collision bullets and enemies
	sf::Vector2f bulletPos = bullet->getPosition();
	sf::Vector2f enemyPos = enemy->getPosition();

	float sqrDistance = (bulletPos.x - enemyPos.x) * (bulletPos.x - enemyPos.x) + (bulletPos.y - enemyPos.y) * (bulletPos.y - enemyPos.y);
	float sqrRadius = bullet->getRadius() * bullet->getRadius() + enemy->getRadius() * enemy->getRadius();

	if (sqrDistance < sqrRadius)
		return true;
	else
		return false;
}

bool CollissionEngine::checkCollission(std::unique_ptr<Enemy> &enemy)
{
	// Detect collision between the player and enemies
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f playerPos = player.getPosition();

	float sqrDistance = (enemyPos.x - playerPos.x) * (enemyPos.x - playerPos.x) + (enemyPos.y - playerPos.y) * (enemyPos.y - playerPos.y);
	float sqrRadius = enemy->getRadius() * enemy->getRadius() + player.getRadius() * player.getRadius();

	if (sqrDistance < sqrRadius)
		return true;
	else
		return false;
}

void CollissionEngine::update()
{
	// Colissions between bullets and enemies
	for (auto &bullet : bullets.list)
		for (auto &enemy : enemies.list)
			if (checkCollission(bullet, enemy))
			{
				bullet->die();
				enemy->die();
				score.add(enemy->getWorthPoints());
			}

	// Collissions between the player and enemies
	for (auto &enemy : enemies.list)
		if (checkCollission(enemy))
		{
			player.die();
			std::cerr << "Player died" << std::endl;
			//dbHighscores.addScore("Joost", score.getValue());
			break;
		}
}