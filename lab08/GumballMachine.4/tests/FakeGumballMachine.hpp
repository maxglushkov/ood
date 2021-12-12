#pragma once
#include <catch2/catch.hpp>
#include "../IGumballMachine.hpp"
#include "State.hpp"

#define MACHINE_ARRANGE(state, ballCount, quarterCount) \
	FakeGumballMachine machine(State::state, ballCount, quarterCount);\
	C##state##State(machine)

#define MACHINE_ACT(action) .action();

#define MACHINE_ASSERT(state, ballCount, quarterCount) \
	REQUIRE(machine.GetState() == State::state);\
	REQUIRE(machine.GetBallCount() == ballCount);\
	REQUIRE(machine.GetQuarterCount() == quarterCount);

class FakeGumballMachine: public IGumballMachine
{
public:
	FakeGumballMachine(State state, unsigned ballCount, unsigned quarterCount)
		:m_state(state)
		,m_ballCount(ballCount)
		,m_quarterCount(quarterCount)
	{}

	State GetState()const
	{
		return m_state;
	}
	unsigned GetBallCount()const override
	{
		return m_ballCount;
	}
	unsigned GetQuarterCount()const override
	{
		return m_quarterCount;
	}

private:
	State m_state;
	unsigned m_ballCount, m_quarterCount;

	void AddQuarter()override
	{
		++m_quarterCount;
	}
	void ReturnQuarters()override
	{
		m_quarterCount = 0;
	}
	void SellBall()override
	{
		if (!m_quarterCount)
		{
			throw std::logic_error("can't sell with no quarters");
		}
		--m_quarterCount;
	}
	void ReleaseBall()override
	{
		if (!m_ballCount)
		{
			throw std::logic_error("no balls to release");
		}
		--m_ballCount;
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
