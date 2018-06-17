#pragma once

#include "gun.h"
#include "entityPool.h"

class Entity;
class Bullet;

class StandardGun : public Gun
{
private:
	// Properties
	int const RELOAD_TIME = 8;

public:
	StandardGun(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool);

	void shoot() override;

	void update() override;
};