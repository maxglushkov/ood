#include "Rectangle.hpp"

bool Rectangle::HitTest(Point const& point)const
{
	return point.x >= m_bounds.xMin
	    && point.y >= m_bounds.yMin
	    && point.x <= m_bounds.xMax
	    && point.y <= m_bounds.yMax;
}
