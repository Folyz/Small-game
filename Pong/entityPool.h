#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <memory>

namespace sf
{
	class RenderWindow;
}

template<class T>
class EntityPool
{
	friend class CollissionEngine;

private:
	std::vector<std::unique_ptr<T>> list = {};
	sf::RenderWindow &window;

public:
	EntityPool(sf::RenderWindow &window);

	void create(sf::Vector2f position, float direction);

	int getAmount();

	void update();
	void draw();
};

template<class T>
void EntityPool<T>::update()
{
	// Update all bullets in the list
	for (auto &entity : list)
		entity->update();

	// Remove bullets in state::dead
	list.erase(std::remove_if(list.begin(), list.end(),
		[&](std::unique_ptr<T> const& entity)
	{
		return (entity.get()->getState() == T::State::dead);
	}), list.end());
}

template<class T>
EntityPool<T>::EntityPool(sf::RenderWindow &window)
	:
	window{ window }
{ }

template<class T>
void EntityPool<T>::create(sf::Vector2f position, float direction)
{
	std::unique_ptr<T> tmp = std::make_unique<T>(window, position, direction);
	list.push_back(std::move(tmp));
}

template<class T>
int EntityPool<T>::getAmount()
{
	return list.size();
}

template<class T>
void EntityPool<T>::draw()
{
	for (auto &entity : list)
		entity->draw();
}