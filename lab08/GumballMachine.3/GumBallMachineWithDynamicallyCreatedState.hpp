#pragma once
#include <boost/format.hpp>
#include "CHasQuarterState.hpp"
#include "CNoQuarterState.hpp"
#include "CSoldOutState.hpp"
#include "CSoldState.hpp"

namespace with_dynamic_state
{

class CGumballMachine : private IGumballMachine
{
public:
	constexpr static unsigned MAX_QUARTER_COUNT = 5;

	CGumballMachine(unsigned numBalls)
		: m_ballCount(numBalls)
	{
		if (m_ballCount > 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetSoldOutState();
		}
	}
	void EjectQuarters()
	{
		m_currentState->EjectQuarters();
	}
	void InsertQuarter()
	{
		m_currentState->InsertQuarter();
	}
	void TurnCrank()
	{
		m_currentState->TurnCrank();
		m_currentState->Dispense();
	}
	void Refill(unsigned numBalls)
	{
		if (m_ballCount == 0)
		{
			if (numBalls != 0)
			{
				m_quarterCount == 0 ? SetNoQuarterState() : SetHasQuarterState();
			}
		}
		else
		{
			if (numBalls == 0)
			{
				SetSoldOutState();
			}
		}
		m_ballCount = numBalls;
	}
	std::string ToString() const
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quarters inserted: %3%
Machine is %4%
)");
		return (fmt % m_ballCount % (m_ballCount != 1 ? "s" : "") % m_quarterCount % m_currentState->ToString()).str();
	}
private:
	unsigned GetBallCount() const override
	{
		return m_ballCount;
	}
	unsigned GetQuarterCount() const override
	{
		return m_quarterCount;
	}
	void AddQuarter() override
	{
		if (m_quarterCount < MAX_QUARTER_COUNT)
		{
			std::cout << "You inserted a quarter\n";
			++m_quarterCount;
		}
		else
		{
			std::cout << "You can't insert another quarter\n";
		}
	}
	void ReturnQuarters() override
	{
		std::cout << m_quarterCount << " quarter" << (m_quarterCount == 1 ? "" : "s") << " returned\n";
		m_quarterCount = 0;
	}
	void SellBall() override
	{
		if (m_quarterCount != 0)
		{
			--m_quarterCount;
		}
	}
	void ReleaseBall() override
	{
		if (m_ballCount != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_ballCount;
		}
	}
	void SetSoldOutState() override
	{
		m_currentState.reset(new CSoldOutState(*this));
	}
	void SetNoQuarterState() override
	{
		m_currentState.reset(new CNoQuarterState(*this));
	}
	void SetSoldState() override
	{
		m_currentState.reset(new CSoldState(*this));
	}
	void SetHasQuarterState() override
	{
		m_currentState.reset(new CHasQuarterState(*this));
	}

	unsigned m_ballCount, m_quarterCount = 0;
	std::unique_ptr<IState> m_currentState;
};

}
