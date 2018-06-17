#include "stdafx.h"
#include "standardGun.h"
#include "standardBullet.h"

#include "bullet.h"
#include "entityPool.h"

StandardGun::StandardGun(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool)
:
	Gun(window, entity, bulletPool)
{ }

void StandardGun::shoot()
{
	if (reloadTimer == 0)
	{
		bulletPool.add(std::make_unique<StandardBullet>(window, owner.getPosition(), owner.getDirection()));
		reloadTimer = RELOAD_TIME;
	}
}

void StandardGun::update()
{
	if (reloadTimer > 0)
		reloadTimer--;
}