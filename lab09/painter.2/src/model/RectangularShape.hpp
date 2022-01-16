#pragma once
#include "IDrawingItem.hpp"

class RectangularShape: public IDrawingItem
{
public:
	RectangularShape(Type type, BoundingBox const& bounds)
		:m_type(type)
		,m_bounds(bounds)
	{}

	Type GetType()const override
	{
		return m_type;
	}

	BoundingBox GetBoundingBox()const override
	{
		return m_bounds;
	}

	void MoveBoundsRelative(BoundingBox const& delta)override;

private:
	Type m_type;
	BoundingBox m_bounds;
};
