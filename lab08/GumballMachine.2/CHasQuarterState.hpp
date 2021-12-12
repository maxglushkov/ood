#pragma once
#include <iostream>
#include "IGumballMachine.hpp"
#include "IState.hpp"

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		m_gumballMachine.AddQuarter();
	}
	void EjectQuarters() override
	{
		m_gumballMachine.ReturnQuarters();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SellBall();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}
private:
	IGumballMachine & m_gumballMachine;
};
