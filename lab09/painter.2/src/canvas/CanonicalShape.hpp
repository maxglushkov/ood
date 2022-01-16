#pragma once
#include "ICanvasPresenterItem.hpp"

class CanonicalShape: public ICanvasPresenterItem
{
public:
	explicit CanonicalShape(BoundingBox const& bounds)
		:m_bounds(bounds)
	{}

	void Draw(ICanvas & canvas)const override;

protected:
	BoundingBox m_bounds;

private:
	virtual void DrawPath(ICanvas & canvas)const = 0;
};
