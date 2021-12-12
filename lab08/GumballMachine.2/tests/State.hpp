#pragma once

enum class State
{
	SoldOut,
	NoQuarter,
	Sold,
	HasQuarter
};

char const* GetStateName(State state);
