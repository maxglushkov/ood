#include "../CSoldOutState.hpp"
#include "gumball-machine.hpp"

TEST_CASE("SoldOut x InsertQuarter -> SoldOut")
{
	TEST_TRANSITION(SoldOut, InsertQuarter, SoldOut)
}

TEST_CASE("SoldOut x EjectQuarter -> SoldOut")
{
	TEST_TRANSITION(SoldOut, EjectQuarter, SoldOut)
}

TEST_CASE("SoldOut x TurnCrank -> SoldOut")
{
	TEST_TRANSITION(SoldOut, TurnCrank, SoldOut)
}

TEST_CASE("SoldOut x Dispense -> SoldOut")
{
	TEST_TRANSITION(SoldOut, Dispense, SoldOut)
}

TEST_CASE("SoldOut description")
{
	GumballMachine machine;
	REQUIRE(CSoldOutState(machine).ToString() == GetStateName(State::SoldOut));
}
