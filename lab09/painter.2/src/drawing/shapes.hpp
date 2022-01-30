#pragma once
#include "types.hpp"

struct Ellipse
{
	double rx, ry, cx, cy;

	constexpr Ellipse(double cx, double cy, double rx, double ry)
		:rx(rx)
		,ry(ry)
		,cx(cx)
		,cy(cy)
	{}

	constexpr Ellipse(BoundingBox const& bounds)
		:rx((bounds.xMax - bounds.xMin) / 2.0)
		,ry((bounds.yMax - bounds.yMin) / 2.0)
		,cx(bounds.xMin + rx)
		,cy(bounds.yMin + ry)
	{}
};

struct Rectangle
{
	double x, y, width, height;

	constexpr Rectangle(Point const& point, Size const& size)
		:x(point.x)
		,y(point.y)
		,width(size.width)
		,height(size.height)
	{}

	constexpr Rectangle(BoundingBox const& bounds)
		:x(bounds.xMin)
		,y(bounds.yMin)
		,width(bounds.xMax - bounds.xMin)
		,height(bounds.yMax - bounds.yMin)
	{}
};

struct Triangle
{
	double xTop, yTop, xBottomLeft, xBottomRight, yBottom;

	constexpr Triangle(BoundingBox const& bounds)
		:xTop((bounds.xMax + bounds.xMin) / 2.0)
		,yTop(bounds.yMin)
		,xBottomLeft(bounds.xMin)
		,xBottomRight(bounds.xMax)
		,yBottom(bounds.yMax)
	{}
};
