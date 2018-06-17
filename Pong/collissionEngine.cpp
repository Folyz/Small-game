#include "stdafx.h"
#include "collissionEngine.h"

#include <iostream>

#include "score.h"
#include "player.h"
#include "entityPool.h"

CollissionEngine::CollissionEngine(EntityPool<Bullet> &bullets, EntityPool<Enemy> &enemies, Score &score, Player &player)
:
	bullets{ bullets },
	enemies{ enemies },
	score{ score },
	player{ player }
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
				bullet->setState(Bullet::State::dead);
				enemy->setState(Enemy::State::dead);
				score.add(enemy->getWorthPoints());
			}

	// Collissions between the player and enemies
	for (auto &enemy : enemies.list)
		if (checkCollission(enemy))
		{
			player.setState(Player::State::dead);
			std::cerr << "Player died" << std::endl;
		}
}