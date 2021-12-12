#pragma once

struct IGumballMachine
{
	virtual void AddQuarter() = 0;
	virtual void ReturnQuarters() = 0;
	virtual void SellBall() = 0;
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount()const = 0;
	virtual unsigned GetQuarterCount()const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};
