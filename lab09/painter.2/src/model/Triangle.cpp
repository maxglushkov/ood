#include "Triangle.hpp"

bool Triangle::HitTest(Point const& point)const
{
	if (point.y <= m_bounds.yMin || point.y > m_bounds.yMax)
	{
		return false;
	}
	const double cx = (m_bounds.xMax + m_bounds.xMin) / 2.0;
	return (point.x - cx) / ((point.x <= cx ? m_bounds.xMin : m_bounds.xMax) - cx) * (m_bounds.yMax - m_bounds.yMin) / (point.y - m_bounds.yMin) <= 1;
}

void Triangle::DrawPath(ICanvas & canvas)const
{
	canvas.MoveTo((m_bounds.xMin + m_bounds.xMax) / 2.0, m_bounds.yMin);
	canvas.LineTo(m_bounds.xMax, m_bounds.yMax);
	canvas.LineTo(m_bounds.xMin, m_bounds.yMax);
	canvas.ClosePath();
}
