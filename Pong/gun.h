#pragma once

#include "entityPool.h"
#include <memory>

class Entity;
class Bullet;

class Gun
{
public:
	enum EBullet
	{
		Standard,
		Grow
	};

protected:
	// Properties
	int reloadTimer = 0;

	EBullet bulletType;

	// Other
	Entity &owner;
	EntityPool<Bullet> &bulletPool;

	// Other
	sf::RenderWindow &window;

public:
	Gun(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool);
	
	template <typename T>
	static std::unique_ptr<T> create(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool);

	virtual void shoot() = 0;

	virtual void update() = 0;
};

template <typename T>
static std::unique_ptr<T> Gun::create(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool)
{
	return std::make_unique<T>(window, entity, bulletPool);
}