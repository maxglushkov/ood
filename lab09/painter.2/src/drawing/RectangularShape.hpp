#pragma once
#include "IDrawingItem.hpp"

class RectangularShape: public IDrawingItem
{
public:
	RectangularShape(Type type, BoundingBox const& bounds)
		:m_type(type)
		,m_bounds(bounds)
	{}

	Type GetType()const override
	{
		return m_type;
	}

	BoundingBox GetBoundingBox()const override
	{
		return m_bounds;
	}

	void SetBoundingBox(IHistory * history, BoundingBox const& bounds)override;

	IDrawingItem * GetInner()override
	{
		return nullptr;
	}

	IDrawingItemPtr IntoInner()override
	{
		return {};
	}

	void AcceptVisitor(IDrawingItemVisitor & visitor, Acceptor const& acceptor = {})const override;

private:
	Type m_type;
	BoundingBox m_bounds;
};
