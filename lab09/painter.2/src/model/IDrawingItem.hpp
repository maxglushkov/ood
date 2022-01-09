#pragma once
#include "IDrawable.hpp"

struct IDrawingItem: public IDrawable
{
	virtual bool HitTest(Point const& point)const = 0;

	virtual BoundingBox GetBoundingBox()const = 0;

	virtual void MoveBoundsRelative(BoundingBox const& delta) = 0;
};
