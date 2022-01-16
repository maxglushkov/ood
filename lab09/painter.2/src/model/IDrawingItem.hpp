#pragma once
#include "types.hpp"

struct IDrawingItem
{
	enum class Type
	{
		Ellipse,
		Rectangle,
		Triangle
	};

	virtual ~IDrawingItem() = default;

	virtual Type GetType()const = 0;

	virtual BoundingBox GetBoundingBox()const = 0;

	virtual void MoveBoundsRelative(BoundingBox const& delta) = 0;
};
