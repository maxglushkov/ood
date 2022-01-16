#pragma once
#include "CanonicalShape.hpp"

class Ellipse: public CanonicalShape
{
public:
	explicit Ellipse(BoundingBox const& bounds)
		:CanonicalShape(bounds)
	{}

	bool HitTest(Point const& point)const override;

private:
	void DrawPath(ICanvas & canvas)const override;
};
