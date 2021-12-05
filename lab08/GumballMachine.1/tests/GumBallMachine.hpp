#pragma once
#include <catch2/catch.hpp>
#include <sstream>
#include "state.hpp"

static void TestMachineState(CGumballMachine const& machine, State state, unsigned count)
{
	std::ostringstream desc;
	desc << "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016 (with state)\nInventory: "
	     << count << " gumball" << (count == 1 ? "" : "s") << "\nMachine is " << GetStateName(state) << '\n';
	REQUIRE(machine.ToString() == desc.str());
}

TEST_CASE(TEST_NAMESPACE"CGumballMachine with no gumballs")
{
	TestMachineState(CGumballMachine(0), State::SoldOut, 0);
}

TEST_CASE(TEST_NAMESPACE"CGumballMachine with 1 gumball")
{
	TestMachineState(CGumballMachine(1), State::NoQuarter, 1);
}

TEST_CASE(TEST_NAMESPACE"CGumballMachine: inserting quarter")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	TestMachineState(machine, State::HasQuarter, 1);
}

TEST_CASE(TEST_NAMESPACE"CGumballMachine: ejecting quarter")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	machine.EjectQuarter();
	TestMachineState(machine, State::NoQuarter, 1);
}

TEST_CASE(TEST_NAMESPACE"CGumballMachine with 1 gumball: turning crank")
{
	CGumballMachine machine(1);
	machine.InsertQuarter();
	machine.TurnCrank();
	TestMachineState(machine, State::SoldOut, 0);
}

TEST_CASE(TEST_NAMESPACE"CGumballMachine with 2 gumballs: turning crank")
{
	CGumballMachine machine(2);
	machine.InsertQuarter();
	machine.TurnCrank();
	TestMachineState(machine, State::NoQuarter, 1);
}
