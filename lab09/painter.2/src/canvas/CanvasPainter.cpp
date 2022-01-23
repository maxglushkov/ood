#include "CanvasPainter.hpp"
#include "ICanvas.hpp"

void CanvasPainter::FillAndStroke()
{
	m_canvas.SetColor(Color::YELLOW);
	m_canvas.FillPreserve();
	m_canvas.SetColor(Color::RED);
	m_canvas.Stroke();
}

void CanvasPainter::VisitEllipse(double cx, double cy, double rx, double ry)
{
	m_canvas.DrawEllipse(cx, cy, rx, ry);
	FillAndStroke();
}

void CanvasPainter::VisitRectangle(BoundingBox const& rect)
{
	m_canvas.DrawRectangle(rect);
	FillAndStroke();
}

void CanvasPainter::VisitTriangle(double xTop, double yTop, double xBottomLeft, double xBottomRight, double yBottom)
{
	m_canvas.MoveTo(xTop, yTop);
	m_canvas.LineTo(xBottomRight, yBottom);
	m_canvas.LineTo(xBottomLeft, yBottom);
	m_canvas.ClosePath();
	FillAndStroke();
}
