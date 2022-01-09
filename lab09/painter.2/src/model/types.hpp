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

	constexpr Rect(double x, double y, double width, double height)
		:x(x)
		,y(y)
		,width(width)
		,height(height)
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
