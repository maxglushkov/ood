#include <algorithm>
#include "../drawing/Drawing.hpp"
#include "BoundsMovementState.hpp"

static void FixDimension(double & min, double & max, bool preserveMin = true)
{
	constexpr static double MIN_DIMENSION = 1.0;
	if (max - min < MIN_DIMENSION)
	{
		if (preserveMin)
		{
			max = min + MIN_DIMENSION;
		}
		else
		{
			min = max - MIN_DIMENSION;
		}
	}
}

static BoundingBox & operator +=(BoundingBox & bounds, BoundingBox const& delta)
{
	bounds.xMin += delta.xMin;
	bounds.yMin += delta.yMin;
	bounds.xMax += delta.xMax;
	bounds.yMax += delta.yMax;
	FixDimension(bounds.xMin, bounds.xMax, !bool(delta.xMin));
	FixDimension(bounds.yMin, bounds.yMax, !bool(delta.yMin));
	return bounds;
}

void BoundsMovementState::BeginMovement(Point const& pos)
{
	m_state = State::ActiveUnchanged;
	m_anchor = pos;
}

void BoundsMovementState::Move(Drawing & drawing, Point const& pos, Direction movingDir)
{
	if (m_state != State::Changed)
	{
		if (!drawing.HasSelection())
		{
			m_state = State::Inactive;
			return;
		}
		m_state = State::Changed;
		drawing.BeginSelectionBoundsMovement();
	}

	const Point absPos{
		std::clamp(pos.x, 0.0, drawing.GetSize().width),
		std::clamp(pos.y, 0.0, drawing.GetSize().height)
	};
	const Point relPos = absPos - m_anchor;
	m_anchor = absPos;

	BoundingBox bounds = drawing.GetSelection()->GetBoundingBox();
	bounds += {
		movingDir[Direction::Left] ? relPos.x : 0.0,
		movingDir[Direction::Top] ? relPos.y : 0.0,
		movingDir[Direction::Right] ? relPos.x : 0.0,
		movingDir[Direction::Bottom] ? relPos.y : 0.0
	};
	drawing.SetSelectionBounds(bounds);
}

void BoundsMovementState::EndMovement(Drawing & drawing)
{
	if (m_state == State::Changed)
	{
		drawing.EndSelectionBoundsMovement();
	}
	m_state = State::Inactive;
}
