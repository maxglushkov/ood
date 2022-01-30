#pragma once
#include "../drawing/types.hpp"

class Drawing;

class BoundsMovementState
{
public:
	bool IsActive()const
	{
		return m_state != State::Inactive;
	}

	void BeginMovement(Point const& pos);

	void Move(Drawing & drawing, Point const& pos, Direction movingDir);

	void EndMovement(Drawing & drawing);

private:
	enum class State
	{
		Inactive,
		ActiveUnchanged,
		Changed
	};

	State m_state = State::Inactive;
	Point m_anchor;
};
