#include "stdafx.h"
#include "growGun.h"
#include "growBullet.h"

#include "bullet.h"
#include "entityPool.h"

GrowGun::GrowGun(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool)
:
	Gun(window, entity, bulletPool)
{ }

void GrowGun::shoot()
{
	if (reloadTimer == 0)
	{
		bulletPool.add(std::make_unique<GrowBullet>(window, owner.getPosition(), owner.getDirection()));
		reloadTimer = RELOAD_TIME;
	}
}

void GrowGun::update()
{
	if (reloadTimer > 0)
		reloadTimer--;
}