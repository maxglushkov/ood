#pragma once
#include "IDrawingItem.hpp"

class CanonicalShape: public IDrawingItem
{
public:
	explicit CanonicalShape(BoundingBox const& bounds)
		:m_bounds(bounds)
	{}

	void Draw(ICanvas & canvas)const override;

	BoundingBox GetBoundingBox()const override
	{
		return m_bounds;
	}

	void MoveBoundsRelative(BoundingBox const& delta)override;

protected:
	BoundingBox m_bounds;

private:
	virtual void DrawPath(ICanvas & canvas)const = 0;
};
