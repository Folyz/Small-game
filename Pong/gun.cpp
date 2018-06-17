#include "stdafx.h"
#include "gun.h"

Gun::Gun(sf::RenderWindow &window, Entity &entity, EntityPool<Bullet> &bulletPool)
:
	window{ window },
	owner{ entity },
	bulletPool{ bulletPool }
{ }