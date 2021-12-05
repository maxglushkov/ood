#include "../CSoldState.hpp"
#include "gumball-machine.hpp"

TEST_CASE("Sold x InsertQuarter -> Sold")
{
	TEST_TRANSITION(Sold, InsertQuarter, Sold)
}

TEST_CASE("Sold x EjectQuarter -> Sold")
{
	TEST_TRANSITION(Sold, EjectQuarter, Sold)
}

TEST_CASE("Sold x TurnCrank -> Sold")
{
	TEST_TRANSITION(Sold, TurnCrank, Sold)
}

TEST_CASE("1 gumball: Sold x Dispense -> SoldOut")
{
	TEST_TRANSITION_WITH_BALL_COUNT(1, Sold, Dispense, SoldOut)
}

TEST_CASE("2 gumballs: Sold x Dispense -> NoQuarter")
{
	TEST_TRANSITION_WITH_BALL_COUNT(2, Sold, Dispense, NoQuarter)
}

TEST_CASE("Sold description")
{
	GumballMachine machine;
	REQUIRE(CSoldState(machine).ToString() == GetStateName(State::Sold));
}
