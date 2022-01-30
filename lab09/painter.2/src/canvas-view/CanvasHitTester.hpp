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

	void Visit(RectangularShape<Ellipse> const& ellipse)override;

	void Visit(RectangularShape<Rectangle> const& rectangle)override;

	void Visit(RectangularShape<Triangle> const& triangle)override;
};
