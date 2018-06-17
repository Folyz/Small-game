#pragma once

#include <memory>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class State
{
	protected:
		StateMachine &machine;
		sf::RenderWindow &window;

		bool replacing;

		std::unique_ptr<State> nextState;

	public:
		State(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		virtual ~State() = default;

		State(const State &) = delete;
		State& operator= (const State &) = delete;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void input() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

		std::unique_ptr<State> next();

		bool isReplacing();
};