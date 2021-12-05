#pragma once
#include <catch2/catch.hpp>
#include "../IGumballMachine.hpp"
#include "state.hpp"

#define TEST_TRANSITION_WITH_BALL_COUNT(count, from, on, into) {\
	GumballMachine machine(State::from, count);\
	C##from##State(machine).on();\
	REQUIRE(machine.GetState() == State::into);\
}
#define TEST_TRANSITION(from, on, into) TEST_TRANSITION_WITH_BALL_COUNT(0, from, on, into)

struct GumballMachine: public IGumballMachine
{
public:
	GumballMachine(State state = State::SoldOut, unsigned count = 0)
		:m_state(state)
		,m_count(count)
	{}

	State GetState()const
	{
		return m_state;
	}
	unsigned GetBallCount()const override
	{
		return m_count;
	}

private:
	State m_state;
	unsigned m_count;

	void ReleaseBall()override
	{
		if (!m_count)
		{
			throw std::logic_error("no balls to release");
		}
		--m_count;
	}

	void SetSoldOutState()override
	{
		m_state = State::SoldOut;
	}
	void SetNoQuarterState()override
	{
		m_state = State::NoQuarter;
	}
	void SetSoldState()override
	{
		m_state = State::Sold;
	}
	void SetHasQuarterState()override
	{
		m_state = State::HasQuarter;
	}
};
