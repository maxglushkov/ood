#pragma once
#include <bitset>

struct Point
{
	double x, y;
};
inline Point operator -(Point const& lhs, Point const& rhs)
{
	return {lhs.x - rhs.x, lhs.y - rhs.y};
}

struct Size
{
	double width, height;
};

struct BoundingBox
{
	double xMin, yMin, xMax, yMax;
};

struct Rect
{
	double x, y, width, height;

	constexpr Rect(Point const& point, Size const& size)
		:x(point.x)
		,y(point.y)
		,width(size.width)
		,height(size.height)
	{}

	constexpr Rect(BoundingBox const& bounds)
		:x(bounds.xMin)
		,y(bounds.yMin)
		,width(bounds.xMax - bounds.xMin)
		,height(bounds.yMax - bounds.yMin)
	{}
};

struct Direction: public std::bitset<4>
{
	enum Pos
	{
		Left,
		Top,
		Right,
		Bottom
	};
};

struct RGBAColor
{
	double r, g, b, a;

	constexpr RGBAColor(double r, double g, double b, double a = 1.0)
		:r(r)
		,g(g)
		,b(b)
		,a(a)
	{}
};

namespace Color
{
	constexpr static RGBAColor BLACK(0.0, 0.0, 0.0);
	constexpr static RGBAColor RED(1.0, 0.0, 0.0);
	constexpr static RGBAColor YELLOW(1.0, 1.0, 0.0);
	constexpr static RGBAColor GREEN(0.0, 0.75, 0.0);
	constexpr static RGBAColor WHITE(1.0, 1.0, 1.0);
}
