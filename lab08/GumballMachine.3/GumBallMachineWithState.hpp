#pragma once
#include <boost/format.hpp>
#include "CHasQuarterState.hpp"
#include "CNoQuarterState.hpp"
#include "CSoldOutState.hpp"
#include "CSoldState.hpp"

namespace with_state
{

class CGumballMachine : private IGumballMachine
{
public:
	constexpr static unsigned MAX_QUARTER_COUNT = 5;

	CGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_ballCount(numBalls)
	{
		if (m_ballCount > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarters()
	{
		m_state->EjectQuarters();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
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
		return (fmt % m_ballCount % (m_ballCount != 1 ? "s" : "") % m_quarterCount % m_state->ToString()).str();
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
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

	unsigned m_ballCount, m_quarterCount = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState * m_state;
};

}
