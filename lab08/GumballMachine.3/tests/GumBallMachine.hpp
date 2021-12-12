#pragma once
#include <catch2/catch.hpp>
#include <sstream>
#include "State.hpp"

static void TestMachineState(CGumballMachine const& machine, State state, unsigned ballCount, unsigned quarterCount)
{
	std::ostringstream desc;
	desc << MACHINE_ISSUE
		     "Inventory: " << ballCount << " gumball" << (ballCount == 1 ? "" : "s")
		<< "\nQuarters inserted: " << quarterCount
		<< "\nMachine is " << GetStateName(state) << '\n';
	REQUIRE(machine.ToString() == desc.str());
}

TEST_CASE(TEST_SUITE_NAME" {0} -> SoldOut, 0, 0")
{
	TestMachineState(0, State::SoldOut, 0, 0);
}

TEST_CASE(TEST_SUITE_NAME" {1} -> NoQuarter, 1, 0")
{
	TestMachineState(1, State::NoQuarter, 1, 0);
}

TEST_CASE(TEST_SUITE_NAME": SoldOut x InsertQuarter -> SoldOut")
{
	CGumballMachine machine(0);
	machine.InsertQuarter();
	TestMachineState(machine, State::SoldOut, 0, 0);
}

TEST_CASE(TEST_SUITE_NAME" (has gumballs): up to MAX_QUARTER_COUNT can be inserted")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	TestMachineState(machine, State::HasQuarter, 1, 1);
	machine.InsertQuarter();
	TestMachineState(machine, State::HasQuarter, 1, 2);
	for (int quarter = 2; quarter < CGumballMachine::MAX_QUARTER_COUNT; ++quarter)
	{
		machine.InsertQuarter();
	}
	TestMachineState(machine, State::HasQuarter, 1, CGumballMachine::MAX_QUARTER_COUNT);
	machine.InsertQuarter();
	TestMachineState(machine, State::HasQuarter, 1, CGumballMachine::MAX_QUARTER_COUNT);
}

TEST_CASE(TEST_SUITE_NAME": NoQuarter x EjectQuarters -> NoQuarter")
{
	CGumballMachine machine(1);
	machine.EjectQuarters();
	TestMachineState(machine, State::NoQuarter, 1, 0);
}

TEST_CASE(TEST_SUITE_NAME": HasQuarter x EjectQuarters -> NoQuarter")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.EjectQuarters();
	TestMachineState(machine, State::NoQuarter, 1, 0);
}

TEST_CASE(TEST_SUITE_NAME": SoldOut, 0, 2 x EjectQuarters -> SoldOut, 0, 0")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	TestMachineState(machine, State::SoldOut, 0, 2);
	machine.EjectQuarters();
	TestMachineState(machine, State::SoldOut, 0, 0);
}

TEST_CASE(TEST_SUITE_NAME": NoQuarter x TurnCrank -> NoQuarter")
{
	CGumballMachine machine(1);
	machine.TurnCrank();
	TestMachineState(machine, State::NoQuarter, 1, 0);
}

TEST_CASE(TEST_SUITE_NAME": HasQuarter, 1, 2 x TurnCrank -> SoldOut, 0, 1")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	TestMachineState(machine, State::SoldOut, 0, 1);
}

TEST_CASE(TEST_SUITE_NAME": HasQuarter, 2, 1 x TurnCrank -> NoQuarter, 1, 0")
{
	CGumballMachine machine(2);
	machine.InsertQuarter();
	machine.TurnCrank();
	TestMachineState(machine, State::NoQuarter, 1, 0);
}

TEST_CASE(TEST_SUITE_NAME": HasQuarter, 2, 2 x TurnCrank -> HasQuarter, 1, 1")
{
	CGumballMachine machine(2);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	TestMachineState(machine, State::HasQuarter, 1, 1);
}

TEST_CASE(TEST_SUITE_NAME": SoldOut x TurnCrank -> SoldOut")
{
	CGumballMachine machine(0);
	machine.TurnCrank();
	TestMachineState(machine, State::SoldOut, 0, 0);
}
