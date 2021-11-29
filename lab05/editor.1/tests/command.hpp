#pragma once
#include <catch2/catch.hpp>
#include "../ICommand.hpp"

struct Command: public ICommand
{
	enum class State
	{
		NonexistentDestroyed,
		CreatedUndone,
		Done
	};

	Command(State & state)
		:m_state(state)
	{
		m_state = State::CreatedUndone;
	}

	~Command()
	{
		m_state = State::NonexistentDestroyed;
	}

	void Do()noexcept override
	{
		switch (m_state)
		{
			case State::CreatedUndone:
				m_state = State::Done;
				break;
			case State::Done:
				m_state = State::CreatedUndone;
				break;
			default:
				REQUIRE(false);
		}
	}

private:
	State & m_state;
};
