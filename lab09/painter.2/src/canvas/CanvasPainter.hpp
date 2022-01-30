#pragma once
#include "../drawing/IDrawingItemVisitor.hpp"

struct ICanvas;

class CanvasPainter: public IDrawingItemVisitor
{
public:
	explicit CanvasPainter(ICanvas & canvas)
		:m_canvas(canvas)
	{}

private:
	ICanvas & m_canvas;

	void FillAndStroke();

	void Visit(RectangularShape<Ellipse> const& ellipse)override;

	void Visit(RectangularShape<Rectangle> const& rectangle)override;

	void Visit(RectangularShape<Triangle> const& triangle)override;
};
