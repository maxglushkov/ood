#pragma once
#include "IDrawingItem.hpp"

class BoundsMovement: public IDrawingItem
{
public:
	explicit BoundsMovement(IDrawingItemPtr && item)
		:m_item(std::move(item))
		,m_bounds(m_item->GetBoundingBox())
	{}

	Type GetType()const override
	{
		return m_item->GetType();
	}

	BoundingBox GetBoundingBox()const override
	{
		return m_bounds;
	}

	void SetBoundingBox(IHistory *, BoundingBox const& bounds)override
	{
		m_bounds = bounds;
	}

	IDrawingItem * GetInner()override
	{
		return m_item.get();
	}

	IDrawingItemPtr IntoInner()override
	{
		return std::move(m_item);
	}

	void AcceptVisitor(IDrawingItemVisitor & visitor, Acceptor const& acceptor = {})const override
	{
		m_item->AcceptVisitor(visitor, {acceptor.m_bounds ?: &m_bounds});
	}

private:
	IDrawingItemPtr m_item;
	BoundingBox m_bounds;
};
