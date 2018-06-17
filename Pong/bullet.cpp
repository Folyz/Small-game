#include "stdafx.h"
#include "bullet.h"

Bullet::Bullet(sf::RenderWindow &window, sf::Vector2f &iniPosition, float iniDirection)
:
	window{ window }
{
	position = iniPosition;
	direction = iniDirection;
}