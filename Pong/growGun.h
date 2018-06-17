#pragma once

#include "gun.h"
#include "entityPool.h"

class Entity;
class Bullet;

class GrowGun : public Gun
{
private:
	// Properties
	int const RELOAD_TIME = 15;

public:
	GrowGun(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool);

	void shoot() override;

	void update() override;
};