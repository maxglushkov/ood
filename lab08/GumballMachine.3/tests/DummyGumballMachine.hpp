#pragma once
#include "../IGumballMachine.hpp"

struct DummyGumballMachine: public IGumballMachine
{
private:
	void AddQuarter()override
	{}
	void ReturnQuarters()override
	{}
	void SellBall()override
	{}
	void ReleaseBall()override
	{}
	unsigned GetBallCount()const override
	{
		return {};
	}
	unsigned GetQuarterCount()const override
	{
		return {};
	}

	void SetSoldOutState()override
	{}
	void SetNoQuarterState()override
	{}
	void SetSoldState()override
	{}
	void SetHasQuarterState()override
	{}
};
