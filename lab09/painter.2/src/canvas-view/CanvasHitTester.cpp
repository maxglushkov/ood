#include <cmath>
#include "CanvasHitTester.hpp"

void CanvasHitTester::VisitEllipse(double cx, double cy, double rx, double ry)
{
	m_isHit = pow(m_pos.x - cx, 2.0) / pow(rx, 2.0) + pow(m_pos.y - cy, 2.0) / pow(ry, 2.0) <= 1.0;
}

void CanvasHitTester::VisitRectangle(BoundingBox const& rect)
{
	m_isHit = m_pos.x >= rect.xMin && m_pos.x <= rect.xMax
	       && m_pos.y >= rect.yMin && m_pos.y <= rect.yMax;
}

void CanvasHitTester::VisitTriangle(double xTop, double yTop, double xBottomLeft, double xBottomRight, double yBottom)
{
	if (m_pos.y <= yTop || m_pos.y > yBottom)
	{
		m_isHit = false;
		return;
	}
	m_isHit = (m_pos.x - xTop) / ((m_pos.x <= xTop ? xBottomLeft : xBottomRight) - xTop)
	        * (yBottom - yTop) / (m_pos.y - yTop) <= 1.0;
}
