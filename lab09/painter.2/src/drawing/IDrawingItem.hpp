#pragma once
#include "types.hpp"

struct IDrawingItemVisitor;
struct IHistory;

struct IDrawingItem
{
	virtual ~IDrawingItem() = default;

	virtual BoundingBox GetBoundingBox()const = 0;

	virtual void SetBoundingBox(BoundingBox const& bounds) = 0;

	virtual void BeginBoundingBoxOperation(IHistory & history) = 0;

	virtual void AcceptVisitor(IDrawingItemVisitor & visitor)const = 0;
};
