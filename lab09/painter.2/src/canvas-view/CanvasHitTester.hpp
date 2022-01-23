#pragma once
#include "../drawing/IDrawingItemVisitor.hpp"
#include "../drawing/types.hpp"

class CanvasHitTester: public IDrawingItemVisitor
{
public:
	explicit CanvasHitTester(Point const& pos)
		:m_pos(pos)
	{}

	bool IsHit()const
	{
		return m_isHit;
	}

private:
	Point m_pos;
	bool m_isHit = false;

	void VisitEllipse(double cx, double cy, double rx, double ry)override;

	void VisitRectangle(BoundingBox const& rect)override;

	void VisitTriangle(double xTop, double yTop, double xBottomLeft, double xBottomRight, double yBottom)override;
};
