#pragma once

struct Ellipse;
struct Rectangle;
struct Triangle;

template<typename T>
class RectangularShape;

struct IDrawingItemVisitor
{
	virtual ~IDrawingItemVisitor() = default;

	virtual void Visit(RectangularShape<Ellipse> const& ellipse) = 0;

	virtual void Visit(RectangularShape<Rectangle> const& rectangle) = 0;

	virtual void Visit(RectangularShape<Triangle> const& triangle) = 0;
};
