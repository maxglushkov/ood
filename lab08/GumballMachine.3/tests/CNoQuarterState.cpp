#include "../CNoQuarterState.hpp"
#include "FakeGumballMachine.hpp"

TEST_CASE("NoQuarter {quarterCount: 0} x InsertQuarter -> HasQuarter {quarterCount: 1}")
{
	MACHINE_ARRANGE(NoQuarter, 1, 0)
	MACHINE_ACT(InsertQuarter)
	MACHINE_ASSERT(HasQuarter, 1, 1)
}

TEST_CASE("NoQuarter x EjectQuarters -> NoQuarter")
{
	MACHINE_ARRANGE(NoQuarter, 1, 0)
	MACHINE_ACT(EjectQuarters)
	MACHINE_ASSERT(NoQuarter, 1, 0)
}

TEST_CASE("NoQuarter x TurnCrank -> NoQuarter")
{
	MACHINE_ARRANGE(NoQuarter, 1, 0)
	MACHINE_ACT(TurnCrank)
	MACHINE_ASSERT(NoQuarter, 1, 0)
}

TEST_CASE("NoQuarter x Dispense -> NoQuarter")
{
	MACHINE_ARRANGE(NoQuarter, 1, 0)
	MACHINE_ACT(Dispense)
	MACHINE_ASSERT(NoQuarter, 1, 0)
}
