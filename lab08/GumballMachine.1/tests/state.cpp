#include "state.hpp"

char const* GetStateName(State state)
{
	constexpr static char const* STATE_NAMES[] = {
		"sold out",
		"waiting for quarter",
		"delivering a gumball",
		"waiting for turn of crank"
	};
	return STATE_NAMES[int(state)];
}
