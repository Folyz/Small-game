#pragma once

#include "entityPool.h"
#include "bullet.h"
#include "enemy.h"

class Score;
class Player;
class Database;

class CollissionEngine
{
	private:
		EntityPool<Bullet> &bullets;
		EntityPool<Enemy> &enemies;
		Player &player;
		Score &score;
		Database &dbHighscores;

	public:
		CollissionEngine(EntityPool<Bullet> &bullets, EntityPool<Enemy> &enemies, Score &score, Player &player, Database &dbHighscores);

		void update();

	private:
		bool checkCollission(std::unique_ptr<Bullet> &bullet, std::unique_ptr<Enemy> &enemy);
		bool checkCollission(std::unique_ptr<Enemy> &enemy);
};