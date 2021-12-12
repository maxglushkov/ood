#include "../CHasQuarterState.hpp"
#include "FakeGumballMachine.hpp"

TEST_CASE("HasQuarter {quarterCount: 1} x InsertQuarter -> HasQuarter {quarterCount: 2}")
{
	MACHINE_ARRANGE(HasQuarter, 1, 1)
	MACHINE_ACT(InsertQuarter)
	MACHINE_ASSERT(HasQuarter, 1, 2)
}

TEST_CASE("HasQuarter {quarterCount: 2} x EjectQuarters -> NoQuarter {quarterCount: 0}")
{
	MACHINE_ARRANGE(HasQuarter, 1, 2)
	MACHINE_ACT(EjectQuarters)
	MACHINE_ASSERT(NoQuarter, 1, 0)
}

TEST_CASE("HasQuarter {quarterCount: 2} x TurnCrank -> Sold {quarterCount: 1}")
{
	MACHINE_ARRANGE(HasQuarter, 1, 2)
	MACHINE_ACT(TurnCrank)
	MACHINE_ASSERT(Sold, 1, 1)
}

TEST_CASE("HasQuarter x Dispense -> HasQuarter")
{
	MACHINE_ARRANGE(HasQuarter, 1, 1)
	MACHINE_ACT(Dispense)
	MACHINE_ASSERT(HasQuarter, 1, 1)
}
