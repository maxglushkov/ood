#include "../drawing/RectangularShape.hpp"
#include "CanvasPainter.hpp"
#include "ICanvas.hpp"

void CanvasPainter::FillAndStroke()
{
	m_canvas.SetColor(Color::YELLOW);
	m_canvas.FillPreserve();
	m_canvas.SetColor(Color::RED);
	m_canvas.Stroke();
}

void CanvasPainter::Visit(RectangularShape<Ellipse> const& ellipse)
{
	m_canvas.DrawEllipse(ellipse.GetInfo());
	FillAndStroke();
}

void CanvasPainter::Visit(RectangularShape<Rectangle> const& rectangle)
{
	m_canvas.DrawRectangle(rectangle.GetInfo());
	FillAndStroke();
}

void CanvasPainter::Visit(RectangularShape<Triangle> const& triangle)
{
	const Triangle info = triangle.GetInfo();
	m_canvas.MoveTo(info.xTop, info.yTop);
	m_canvas.LineTo(info.xBottomRight, info.yBottom);
	m_canvas.LineTo(info.xBottomLeft, info.yBottom);
	m_canvas.ClosePath();
	FillAndStroke();
}
