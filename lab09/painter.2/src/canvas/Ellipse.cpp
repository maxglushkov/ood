#include <cmath>
#include "Ellipse.hpp"

struct EllipseInfo
{
	double rx, ry, cx, cy;

	constexpr EllipseInfo(BoundingBox const& bounds)
		:rx((bounds.xMax - bounds.xMin) / 2.0)
		,ry((bounds.yMax - bounds.yMin) / 2.0)
		,cx(bounds.xMin + rx)
		,cy(bounds.yMin + ry)
	{}
};

bool Ellipse::HitTest(Point const& point)const
{
	const EllipseInfo info = m_bounds;
	return pow(point.x - info.cx, 2.0) / pow(info.rx, 2.0) + pow(point.y - info.cy, 2.0) / pow(info.ry, 2.0) <= 1;
}

void Ellipse::DrawPath(ICanvas & canvas)const
{
	const EllipseInfo info = m_bounds;
	canvas.DrawEllipse(info.cx, info.cy, info.rx, info.ry);
}
