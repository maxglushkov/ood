#include "../CSoldOutState.hpp"
#include "FakeGumballMachine.hpp"

TEST_CASE("SoldOut x InsertQuarter -> SoldOut")
{
	MACHINE_ARRANGE(SoldOut, 0, 2)
	MACHINE_ACT(InsertQuarter)
	MACHINE_ASSERT(SoldOut, 0, 2)
}

TEST_CASE("SoldOut {quarterCount: 2} x EjectQuarters -> SoldOut {quarterCount: 0}")
{
	MACHINE_ARRANGE(SoldOut, 0, 2)
	MACHINE_ACT(EjectQuarters)
	MACHINE_ASSERT(SoldOut, 0, 0)
}

TEST_CASE("SoldOut x TurnCrank -> SoldOut")
{
	MACHINE_ARRANGE(SoldOut, 0, 2)
	MACHINE_ACT(TurnCrank)
	MACHINE_ASSERT(SoldOut, 0, 2)
}

TEST_CASE("SoldOut x Dispense -> SoldOut")
{
	MACHINE_ARRANGE(SoldOut, 0, 2)
	MACHINE_ACT(Dispense)
	MACHINE_ASSERT(SoldOut, 0, 2)
}
