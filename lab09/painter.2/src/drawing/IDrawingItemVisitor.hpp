#pragma once

struct BoundingBox;

struct IDrawingItemVisitor
{
	virtual ~IDrawingItemVisitor() = default;

	virtual void VisitEllipse(double cx, double cy, double rx, double ry) = 0;

	virtual void VisitRectangle(BoundingBox const& rect) = 0;

	virtual void VisitTriangle(double xTop, double yTop, double xBottomLeft, double xBottomRight, double yBottom) = 0;
};
