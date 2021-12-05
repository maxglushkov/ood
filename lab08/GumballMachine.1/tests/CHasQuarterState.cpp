#include "../CHasQuarterState.hpp"
#include "gumball-machine.hpp"

TEST_CASE("HasQuarter x InsertQuarter -> HasQuarter")
{
	TEST_TRANSITION(HasQuarter, InsertQuarter, HasQuarter)
}

TEST_CASE("HasQuarter x EjectQuarter -> NoQuarter")
{
	TEST_TRANSITION(HasQuarter, EjectQuarter, NoQuarter)
}

TEST_CASE("HasQuarter x TurnCrank -> Sold")
{
	TEST_TRANSITION(HasQuarter, TurnCrank, Sold)
}

TEST_CASE("HasQuarter x Dispense -> HasQuarter")
{
	TEST_TRANSITION(HasQuarter, Dispense, HasQuarter)
}

TEST_CASE("HasQuarter description")
{
	GumballMachine machine;
	REQUIRE(CHasQuarterState(machine).ToString() == GetStateName(State::HasQuarter));
}
