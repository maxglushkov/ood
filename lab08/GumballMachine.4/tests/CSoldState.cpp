#include "../CSoldState.hpp"
#include "FakeGumballMachine.hpp"

TEST_CASE("Sold x InsertQuarter -> Sold")
{
	MACHINE_ARRANGE(Sold, 1, 2)
	MACHINE_ACT(InsertQuarter)
	MACHINE_ASSERT(Sold, 1, 2)
}

TEST_CASE("Sold x EjectQuarters -> Sold")
{
	MACHINE_ARRANGE(Sold, 1, 2)
	MACHINE_ACT(EjectQuarters)
	MACHINE_ASSERT(Sold, 1, 2)
}

TEST_CASE("Sold x TurnCrank -> Sold")
{
	MACHINE_ARRANGE(Sold, 1, 2)
	MACHINE_ACT(TurnCrank)
	MACHINE_ASSERT(Sold, 1, 2)
}

TEST_CASE("Sold {ballCount: 1} x Dispense -> SoldOut {ballCount: 0}")
{
	MACHINE_ARRANGE(Sold, 1, 2)
	MACHINE_ACT(Dispense)
	MACHINE_ASSERT(SoldOut, 0, 2)
}

TEST_CASE("Sold {ballCount: 2, quarterCount: 0} x Dispense -> NoQuarter {ballCount: 1}")
{
	MACHINE_ARRANGE(Sold, 2, 0)
	MACHINE_ACT(Dispense)
	MACHINE_ASSERT(NoQuarter, 1, 0)
}

TEST_CASE("Sold {ballCount: 2, quarterCount: 1} x Dispense -> HasQuarter {ballCount: 1}")
{
	MACHINE_ARRANGE(Sold, 2, 1)
	MACHINE_ACT(Dispense)
	MACHINE_ASSERT(HasQuarter, 1, 1)
}
