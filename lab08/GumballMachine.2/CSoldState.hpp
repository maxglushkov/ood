#pragma once
#include <iostream>
#include "IGumballMachine.hpp"
#include "IState.hpp"

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() override
	{}
	void EjectQuarters() override
	{}
	void TurnCrank() override
	{}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetQuarterCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}
private:
	IGumballMachine & m_gumballMachine;
};
