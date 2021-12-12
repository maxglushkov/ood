#pragma once
#include <iostream>
#include "IGumballMachine.hpp"
#include "IState.hpp"

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine & gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		m_gumballMachine.AddQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarters() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}
private:
	IGumballMachine & m_gumballMachine;
};
