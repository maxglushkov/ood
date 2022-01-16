#pragma once
#include "CanonicalShape.hpp"

class Triangle: public CanonicalShape
{
public:
	explicit Triangle(BoundingBox const& bounds)
		:CanonicalShape(bounds)
	{}

	bool HitTest(Point const& point)const override;

private:
	void DrawPath(ICanvas & canvas)const override;
};
