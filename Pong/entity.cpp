#include "stdafx.h"
#include "entity.h"

#include <SFML/Graphics/RenderWindow.hpp>

void Entity::die()
{
	state = EState::Dead;
}

float Entity::getDirection()
{
	return direction;
}

sf::Vector2f const &Entity::getPosition()
{
	return position;
}

float Entity::getRadius()
{
	return radius;
}

Entity::EState Entity::getState()
{
	return state;
}