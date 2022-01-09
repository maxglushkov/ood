#pragma once
#include "CanonicalShape.hpp"

class Rectangle: public CanonicalShape
{
public:
	explicit Rectangle(BoundingBox const& bounds)
		:CanonicalShape(bounds)
	{}

	bool HitTest(Point const& point)const override;

private:
	void DrawPath(ICanvas & canvas)const override
	{
		canvas.DrawRectangle(m_bounds);
	}
};
