#include "../CNoQuarterState.hpp"
#include "gumball-machine.hpp"

TEST_CASE("NoQuarter x InsertQuarter -> HasQuarter")
{
	TEST_TRANSITION(NoQuarter, InsertQuarter, HasQuarter)
}

TEST_CASE("NoQuarter x EjectQuarter -> NoQuarter")
{
	TEST_TRANSITION(NoQuarter, EjectQuarter, NoQuarter)
}

TEST_CASE("NoQuarter x TurnCrank -> NoQuarter")
{
	TEST_TRANSITION(NoQuarter, TurnCrank, NoQuarter)
}

TEST_CASE("NoQuarter x Dispense -> NoQuarter")
{
	TEST_TRANSITION(NoQuarter, Dispense, NoQuarter)
}

TEST_CASE("NoQuarter description")
{
	GumballMachine machine;
	REQUIRE(CNoQuarterState(machine).ToString() == GetStateName(State::NoQuarter));
}
