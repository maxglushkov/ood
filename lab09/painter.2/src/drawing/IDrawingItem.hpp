#pragma once
#include <memory>
#include "types.hpp"

struct IDrawingItemVisitor;
struct IHistory;

struct IDrawingItem;
typedef std::unique_ptr<IDrawingItem> IDrawingItemPtr;

struct IDrawingItem
{
protected:
	struct Acceptor
	{
		BoundingBox const* m_bounds;
	};

public:
	enum class Type
	{
		Ellipse,
		Rectangle,
		Triangle
	};

	virtual ~IDrawingItem() = default;

	virtual Type GetType()const = 0;

	virtual BoundingBox GetBoundingBox()const = 0;

	virtual void SetBoundingBox(IHistory * history, BoundingBox const& bounds) = 0;

	virtual IDrawingItem * GetInner() = 0;

	virtual IDrawingItemPtr IntoInner() = 0;

	virtual void AcceptVisitor(IDrawingItemVisitor & visitor, Acceptor const& acceptor = {})const = 0;
};
