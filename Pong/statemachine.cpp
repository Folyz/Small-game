#include "stdafx.h"
#include "statemachine.h"

#include <iostream>

#include "state.h"

StateMachine::StateMachine()
:
	resume{ false },
	isRunning{ false }
{
	std::cerr << "State machine initialized..." << std::endl;
}

void StateMachine::run(std::unique_ptr<State> state)
{
	isRunning = true;

	states.push(std::move(state));	// Push state to onto the stack of states
}

void StateMachine::nextState()
{
	if (resume)
	{
		// Cleanup the current state and resume previous state
		if (!states.empty())
		{
			states.pop();
			states.top()->resume();
		}

		resume = false;
	}

	// There needs to be a state
	if (!states.empty())
	{
		std::unique_ptr<State> temp = states.top()->next();

		// Only change states if there's a next one existing
		if (temp != nullptr)
		{
			// Replace the running state
			if (temp->isReplacing())
				states.pop();
			// Pause the running state
			else
				states.top()->pause();

			states.push(std::move(temp));
		}
	}
}

void StateMachine::lastState()
{
	resume = true;
}

void StateMachine::input()
{
	states.top()->input();
}

void StateMachine::update()
{
	// Let the state update the game
	states.top()->update();
}

void StateMachine::draw()
{
	// Let the state draw the screen
	states.top()->draw();
}

bool StateMachine::running()
{
	return isRunning;
}

void StateMachine::quit()
{
	isRunning = false;
}