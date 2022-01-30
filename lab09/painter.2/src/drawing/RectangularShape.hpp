#pragma once
#include "IDrawingItem.hpp"

struct Ellipse;
struct Rectangle;
struct Triangle;

template<typename T>
class RectangularShape final: public IDrawingItem
{
public:
	explicit RectangularShape(BoundingBox const& bounds)
		:m_bounds(bounds)
	{}

	T GetInfo()const
	{
		return m_bounds;
	}

	BoundingBox GetBoundingBox()const override
	{
		return m_bounds;
	}

	void SetBoundingBox(BoundingBox const& bounds)override
	{
		m_bounds = bounds;
	}

	void BeginBoundingBoxOperation(IHistory & history)override;

	void AcceptVisitor(IDrawingItemVisitor & visitor)const override;

private:
	BoundingBox m_bounds;
};

extern template class RectangularShape<Ellipse>;
extern template class RectangularShape<Rectangle>;
extern template class RectangularShape<Triangle>;
