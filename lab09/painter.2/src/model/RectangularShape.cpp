#include "RectangularShape.hpp"

static void FixDimension(double & min, double & max, bool preserveMin = true)
{
	constexpr static double MIN_DIMENSION = 1.0;
	if (max - min < MIN_DIMENSION)
	{
		if (preserveMin)
		{
			max = min + MIN_DIMENSION;
		}
		else
		{
			min = max - MIN_DIMENSION;
		}
	}
}

void RectangularShape::MoveBoundsRelative(BoundingBox const& delta)
{
	m_bounds.xMin += delta.xMin;
	m_bounds.yMin += delta.yMin;
	m_bounds.xMax += delta.xMax;
	m_bounds.yMax += delta.yMax;
	FixDimension(m_bounds.xMin, m_bounds.xMax, !bool(delta.xMin));
	FixDimension(m_bounds.yMin, m_bounds.yMax, !bool(delta.yMin));
}
