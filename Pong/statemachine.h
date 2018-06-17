#pragma once

#include <memory>
#include <stack>
#include <string>

class State;

namespace sf
{
	class RenderWindow;
}

class StateMachine
{
	private:
		// The stack of states
		std::stack<std::unique_ptr<State>> states;

		bool resume;
		bool isRunning;

	public:
		StateMachine();

		void run(std::unique_ptr<State> state);

		void nextState();
		void lastState();

		void input();
		void update();
		void draw();

		bool running();

		void quit();

		template <typename T>
		static std::unique_ptr<T> build(StateMachine &machine, sf::RenderWindow &window, bool replace = true);
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine &machine, sf::RenderWindow &window, bool replace)
{
	return std::make_unique<T>(machine, window, replace);
}