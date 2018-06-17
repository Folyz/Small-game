#include "stdafx.h"
#include "state.h"

State::State(StateMachine& machine, sf::RenderWindow &window, bool replace)
: 
	machine{ machine },
	window{ window },
	replacing{ replace }
{ }

std::unique_ptr<State> State::next()
{
	return std::move(nextState);
}

bool State::isReplacing()
{
	return replacing;
}