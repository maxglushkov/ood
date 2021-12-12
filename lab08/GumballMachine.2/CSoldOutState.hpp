#pragma once
#include <iostream>
#include "IGumballMachine.hpp"
#include "IState.hpp"

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarters() override
	{
		m_gumballMachine.ReturnQuarters();
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}
private:
	IGumballMachine & m_gumballMachine;
};
