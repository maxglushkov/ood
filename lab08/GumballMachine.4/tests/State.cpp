#include <catch2/catch.hpp>
#include "../CHasQuarterState.hpp"
#include "../CNoQuarterState.hpp"
#include "../CSoldOutState.hpp"
#include "../CSoldState.hpp"
#include "DummyGumballMachine.hpp"
#include "State.hpp"

#define TEST_STATE_DESCRIPTION(state) \
	TEST_CASE(#state" description is correct")\
	{\
		DummyGumballMachine machine;\
		REQUIRE(C##state##State(machine).ToString() == GetStateName(State::state));\
	}

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

TEST_STATE_DESCRIPTION(SoldOut)
TEST_STATE_DESCRIPTION(NoQuarter)
TEST_STATE_DESCRIPTION(Sold)
TEST_STATE_DESCRIPTION(HasQuarter)
