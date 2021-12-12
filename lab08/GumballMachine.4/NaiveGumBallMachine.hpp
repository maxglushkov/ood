#pragma once
#include <boost/format.hpp>
#include <iostream>

namespace naive
{

class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,    // ballCount == 0
		NoQuarter,  // ballCount > 0 && quarterCount == 0
		HasQuarter, // ballCount > 0 && quarterCount > 0
		Sold,       // private state
	};
	constexpr static unsigned MAX_QUARTER_COUNT = 5;

	CGumballMachine(unsigned count)
		: m_ballCount(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			m_state = State::HasQuarter;
		case State::HasQuarter:
			if (m_quarterCount < MAX_QUARTER_COUNT)
			{
				cout << "You inserted a quarter\n";
				++m_quarterCount;
			}
			else
			{
				cout << "You can't insert another quarter\n";
			}
			break;
		case State::Sold:;
		}
	}

	void EjectQuarters()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			m_state = State::NoQuarter;
		case State::SoldOut:
			cout << m_quarterCount << " quarter" << (m_quarterCount == 1 ? "" : "s") << " returned\n";
			m_quarterCount = 0;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			cout << "You turned...\n";
			--m_quarterCount;
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_ballCount = numBalls;
		m_state =
			m_ballCount == 0    ? State::SoldOut :
			m_quarterCount == 0 ? State::NoQuarter :
			                      State::HasQuarter;
	}

	std::string ToString() const
	{
		std::string state =
			(m_state == State::SoldOut)    ? "sold out" :
			(m_state == State::NoQuarter)  ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
			                               : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Quarters inserted: %3%
Machine is %4%
)");
		return (fmt % m_ballCount % (m_ballCount != 1 ? "s" : "") % m_quarterCount % state).str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_ballCount;
			if (m_ballCount == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = m_quarterCount == 0 ? State::NoQuarter : State::HasQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
		}
	}

	unsigned m_ballCount, m_quarterCount = 0;
	State m_state = State::SoldOut;
};

}
