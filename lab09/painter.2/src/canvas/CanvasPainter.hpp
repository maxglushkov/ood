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

	void VisitEllipse(double cx, double cy, double rx, double ry)override;

	void VisitRectangle(BoundingBox const& rect)override;

	void VisitTriangle(double xTop, double yTop, double xBottomLeft, double xBottomRight, double yBottom)override;
};
