#include <cmath>
#include "../drawing/RectangularShape.hpp"
#include "../drawing/shapes.hpp"
#include "CanvasHitTester.hpp"

void CanvasHitTester::Visit(RectangularShape<Ellipse> const& ellipse)
{
	const Ellipse info = ellipse.GetInfo();
	m_isHit = pow(m_pos.x - info.cx, 2.0) / pow(info.rx, 2.0) + pow(m_pos.y - info.cy, 2.0) / pow(info.ry, 2.0) <= 1.0;
}

void CanvasHitTester::Visit(RectangularShape<Rectangle> const& rectangle)
{
	const BoundingBox bounds = rectangle.GetBoundingBox();
	m_isHit = m_pos.x >= bounds.xMin && m_pos.x <= bounds.xMax
	       && m_pos.y >= bounds.yMin && m_pos.y <= bounds.yMax;
}

void CanvasHitTester::Visit(RectangularShape<Triangle> const& triangle)
{
	const Triangle info = triangle.GetInfo();
	if (m_pos.y <= info.yTop || m_pos.y > info.yBottom)
	{
		m_isHit = false;
		return;
	}
	m_isHit = (m_pos.x - info.xTop) / ((m_pos.x <= info.xTop ? info.xBottomLeft : info.xBottomRight) - info.xTop)
	        * (info.yBottom - info.yTop) / (m_pos.y - info.yTop) <= 1.0;
}
